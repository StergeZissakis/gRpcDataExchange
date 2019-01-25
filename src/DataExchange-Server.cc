#include <iostream>
#include <fstream>
#include <DataExchange-Server.h>
#include <utils/Logger.h>

namespace Exercise
{

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
		Logger log("GetFile", "DXServiceImpl");
		(void) context;
		std::string fname = request->filename();
		std::ifstream f(fname, std::ios::binary | std::ios::in);
		if( !f.is_open() )
		{
			std::stringstream error;
			error << "File [" << fname << "] does not exist on the server";
			log.log(error.str());
			return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, error.str());
		}

		std::string buff(1024, '\0');
		File file;
		file.set_filename(fname);

		while(!f.eof())
		{
			f.read(&buff[0], 1024);
			file.set_chunk(buff);
			writer->Write(file);
		}
		
		return grpc::Status::OK;
	}

	::grpc::Status DXServiceImpl::UploadFile(::grpc::ServerContext* context, ::grpc::ServerReader< ::Exercise::File>* reader, ::google::protobuf::Empty* response)  
	{
		Logger log("UploadFile", "DXServiceImpl");
		(void) context;
		(void) response;

		File file;
		reader->Read(&file);
		std::ofstream fd(file.filename().c_str(), std::ios::binary | std::ios::out);
		if( !fd.is_open() )
		{
			std::stringstream error;
			error << "File [" << file.filename() << "] cannot be opened for writing";
			log.log(error.str());
			return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, error.str());
		}
		fd.write(file.chunk().c_str(), file.chunk().size()); // ensure the first batch of bytes find their way into the server side file.:w
		while(reader->Read(&file) )
		{
			if( !fd.write(file.chunk().c_str(), file.chunk().size()) )
			{
				std::stringstream error;
				error << "File [" << file.filename() << "] cannot be written to";
				log.log(error.str());
				return ::grpc::Status(::grpc::StatusCode::UNKNOWN, error.str());
			}
		}
		fd.close();
		return grpc::Status::OK;
	}
}
