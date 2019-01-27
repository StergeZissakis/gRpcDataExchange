#include <iostream>
#include <fstream>
#include <iterator>
#include <memory>
#include <algorithm>
#include <DataExchange-Client.h>
#include <utils/Logger.h>

google::protobuf::Empty DXServiceClient::EmptyObj;
#define BUFFER_SIZE  2048

Exercise::File MakeFile(const std::string& name)
{
	Exercise::File f;
	f.set_filename(name);
	return f;
}

Exercise::Parameters MakeParameters(long long num, const std::string& str)
{
	Exercise::Parameters params;
	params.set_number(num);
	params.set_text(str);
	return params;
}


bool DXServiceClient::connectToServer()
{
	Logger log("connectToServer", "DXServiceClient");
	std::stringstream url;
	url << _serverAddress << ":" << _serverPort;
	_connection = grpc::CreateChannel(url.str(), grpc::InsecureChannelCredentials());
	_stub = Exercise::DataExchange::NewStub(_connection);
	return (_stub)? true : false;
}

bool DXServiceClient::SetParameters(long long num, const std::string& str) const
{
	Logger log("SetParameters", "DXServiceClient");
	grpc::ClientContext context;
	Exercise::Parameters params = MakeParameters(num, str);
	grpc::Status status = _stub->SetParameters(&context, params, &EmptyObj);
	return status.ok();
}

bool DXServiceClient::GetParameters(long long& num, std::string& str) const
{
	Logger log("GetParameters", "DXServiceClient");
	grpc::ClientContext context;
	Exercise::Parameters params;
	grpc::Status status = _stub->GetParameters(&context, EmptyObj, &params);
	num = params.number();
	str = params.text();
	return status.ok();
}

bool DXServiceClient::DownloadFile(const std::string& filename) // calls DownloadFile on the server, thus it is a server downstream flow.
{
	Logger log("DownloadFile", "DXServiceClient");

	grpc::ClientContext context;
	context.set_compression_algorithm(GRPC_COMPRESS_STREAM_GZIP);
	Exercise::File file = MakeFile(filename);
	std::unique_ptr<grpc::ClientReader<Exercise::File > > reader(_stub->DownloadFile(&context, file));
	std::fstream fd(file.filename(), std::ios::binary | std::ios::out);
	if( !fd )
	{
		log.log("Failed to write to file: " + file.filename());
		return false;
	}

	bool hasMore = true;
	do
	{
		hasMore = reader->Read(&file);
		if(!fd.write(file.chunk().c_str(), file.chunk().size()))
		{
			log.log("Failed to write data to file");	
			return false;
		}
	}while(hasMore);
	return true;
}

bool DXServiceClient::UploadFile(const std::string& filename) // calls UploadFile on the server, thus it is a server upstream flow.
{
	Logger log("UploadFile", "DXServiceClient");

	grpc::ClientContext context;
	//context.set_compression_algorithm(GRPC_COMPRESS_STREAM_GZIP);
	std::unique_ptr<grpc::ClientWriter<Exercise::File > > writer(_stub->UploadFile(&context, &EmptyObj));
	Exercise::File file = MakeFile(filename);

	writer->WaitForInitialMetadata();

	std::fstream fd(filename, std::ios::binary | std::ios::in);
	if( !fd )
	{
		log.log("Failed to read from file: " + filename);
		return false;
	}

	// Send the file name
	if( !writer->Write(file) )
	{
		log.log("Failed to send file name to the server");	
		return false;
	}

	// upload the file
	char buff[BUFFER_SIZE + 1] = { '\0' };
	do
	{
		fd.read(buff, std::min(fd.rdbuf()->in_avail(), BUFFER_SIZE));
		if( fd.gcount() )
		{
			std::string tmp(buff, fd.gcount());
			file.set_chunk(tmp);
			if( !writer->Write(file) )
			{
				log.log("Failed to send data to the server");	
				return false;
			}
		}
	}while(!fd.eof() && fd.gcount());

	bool status = writer->WritesDone();
	writer->Finish();
	return status;
}
