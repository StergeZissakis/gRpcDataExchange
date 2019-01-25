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
	_connection = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
	_stub = Exercise::DataExchange::NewStub(_connection);
	return (_stub)? true : false;
}

bool DXServiceClient::SetParameters(long long num, const std::string& str) const
{
	grpc::ClientContext context;
	Exercise::Parameters params = MakeParameters(num, str);
	grpc::Status status = _stub->SetParameters(&context, params, &EmptyObj);
	return status.ok();
}

bool DXServiceClient::GetParameters(long long& num, std::string& str) const
{
	grpc::ClientContext context;
	Exercise::Parameters params;
	grpc::Status status = _stub->GetParameters(&context, EmptyObj, &params);
	num = params.number();
	str = params.text();
	return status.ok();
}


google::protobuf::Empty DXServiceClient::EmptyObj;
