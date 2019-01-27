#include <iostream>
#include <fstream>
#include <DataExchange-Server.h>
#include <utils/Logger.h>
#include <memory>

namespace Exercise
{

#define BUFFER_SIZE  2048

	// Statics
	int DXServiceImpl::_sm_number = 0;
	std::string DXServiceImpl::_sm_string;

	::grpc::Status DXServiceImpl::GetParameters(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::Exercise::Parameters* response) 
	{
		Logger log("GetParameters", "DXServiceImpl");
		(void) context;
		(void) request;
		response->set_number(_sm_number);
		response->set_text(_sm_string);
		return ::grpc::Status(::grpc::StatusCode::OK, "");
	}

	::grpc::Status DXServiceImpl::SetParameters(::grpc::ServerContext* context, const ::Exercise::Parameters* request, ::google::protobuf::Empty* response)  
	{
		Logger log("SetParameters", "DXServiceImpl");
		(void) context;
		(void) response;

		_sm_number = request->number();
		_sm_string = request->text();
		return ::grpc::Status(::grpc::StatusCode::OK, "");
	}

	::grpc::Status DXServiceImpl::DownloadFile(::grpc::ServerContext* context, const ::Exercise::File* request, ::grpc::ServerWriter< ::Exercise::File>* writer)  
	{
		Logger log("DownloadFile", "DXServiceImpl");
		context->set_compression_algorithm(GRPC_COMPRESS_STREAM_GZIP);
		std::string fname = request->filename();
		std::fstream f(fname, std::ios::binary | std::ios::in);

		if( !f )
		{
			std::stringstream error;
			error << "File [" << fname << "] does not exist on the server";
			log.log(error.str());
			return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, error.str());
		}

		writer->SendInitialMetadata();

		// upload the file
		File file;
		char buff[BUFFER_SIZE + 1] = { '\0' };
		do
		{
			f.read(buff, std::min(f.rdbuf()->in_avail(), BUFFER_SIZE));
			if( f.gcount() )
			{
				std::string tmp(buff, f.gcount());
				file.set_chunk(tmp);
				if( !writer->Write(file) )
				{
					log.log("Failed to send data to the client");	
					return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "Write failed");
				}
			}
		}while(!f.eof() && f.gcount());

		return ::grpc::Status(::grpc::Status::OK);
	}

	::grpc::Status DXServiceImpl::UploadFile(::grpc::ServerContext* context, ::grpc::ServerReader< ::Exercise::File>* reader, ::google::protobuf::Empty* response)  
	{
		Logger log("UploadFile", "DXServiceImpl");
		(void) response;
		context->set_compression_algorithm(GRPC_COMPRESS_STREAM_GZIP);

		reader->SendInitialMetadata();

		File file;
		// read the filename
		bool hasMore = reader->Read(&file);
		std::fstream fd(file.filename().c_str(), std::ios::binary | std::ios::out);
		if( !fd )
		{
			std::stringstream error;
			error << "File [" << file.filename() << "] cannot be opened for writing";
			log.log(error.str());
			return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, error.str());
		}
		// perform the upload
		file.set_chunk("");
		file.chunk();
		do
		{
			if( hasMore =  reader->Read(&file) )
			{
				if( !fd.write(file.chunk().c_str(), file.chunk().size()) )
				{
					std::stringstream error;
					error << "File [" << file.filename() << "] cannot be written to";
					log.log(error.str());
					return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, error.str());
				}
			}
		}while(hasMore);

		return grpc::Status(grpc::Status::OK);
	}
}
