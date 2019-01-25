#include <iostream>
#include <fstream>
#include <DataExchange-Client.h>
#include <utils/Logger.h>


Exercise::File MakeFile(const std::string& name)
{
	Exercise::File f;
	f.set_filename(name);
	f.set_chunk(std::string());
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

bool DXServiceClient::UploadFile(const std::string& filename) // calls UploadFile on the server, thus it is a server upstream flow.
{
	Logger log("UploadFile", "DXServiceClient");

	grpc::ClientContext context;
	Exercise::File file = MakeFile(filename);
	std::unique_ptr<grpc::ClientWriter<Exercise::File > > writer(_stub->UploadFile(&context, &EmptyObj));

	std::ifstream fd(filename, std::ios::binary | std::ios::in);
	if( !fd.is_open() )
	{
		log.log("Failed to read from file: " + filename);
		return false;
	}


	char buff[1024];
	while(!fd.eof())
	{
		fd.read(buff, 1024);
		file.set_chunk(buff);
		if( !writer->Write(file) )
		{
			log.log("Failed to send to the server");	
			return false;
		}
	}
	return writer->WritesDone();
}

bool DXServiceClient::DownloadFile(const std::string& filename) // calls DownloadFile on the server, thus it is a server downstream flow.
{
	Logger log("DownloadFile", "DXServiceClient");

	grpc::ClientContext context;
	Exercise::File file = MakeFile(filename);
	std::unique_ptr<grpc::ClientReader<Exercise::File > > reader(_stub->DownloadFile(&context, file));
	if( !reader->Read(&file) )
	{
		log.log("Failed to read the first packet");	
		return false;
	}
	std::ofstream fd(file.filename(), std::ios::binary | std::ios::out);
	if( !fd.is_open() )
	{
		log.log("Failed to write to file: " + file.filename());
		return false;
	}

	fd.write(file.chunk().c_str(), file.chunk().size());
	while(reader->Read(&file)) 
	{
		fd.write(file.chunk().c_str(), file.chunk().size());
	}
	return reader->Finish().ok();
}

google::protobuf::Empty DXServiceClient::EmptyObj;
