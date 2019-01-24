#include <iostream>
#include <fstream>
#include <DataExchange-Server.h>
#include <utils/Logger.h>

namespace Exercise
{

	// Statics
	int DXServiceImpl::_sm_number = 0;
	std::string DXServiceImpl::_sm_string;

	::grpc::Status DXServiceImpl::GetParameters(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::Excercise::Parameters* response) 
	{
		(void) context;
		(void) request;
		response->set_number(_sm_number);
		response->set_text(_sm_string);
		return ::grpc::Status(::grpc::StatusCode::OK, "");
	}

	::grpc::Status DXServiceImpl::SetParameters(::grpc::ServerContext* context, const ::Excercise::Parameters* request, ::google::protobuf::Empty* response)  
	{
		(void) context;
		(void) response;

		_sm_number = request->number();
		_sm_string = request->text();
		return ::grpc::Status(::grpc::StatusCode::OK, "");
	}

	::grpc::Status DXServiceImpl::GetFile(::grpc::ServerContext* context, const ::Excercise::File* request, ::grpc::ServerWriter< ::Excercise::File>* writer)  
	{
		(void) context;
		(void) request;
		std::string fname = request->filename();
		std::ifstream f(fname, std::ios::in);
		if( !f.is_open() )
		{
			std::stringstream error;
			error << "File [" << fname << "] does not exist on the server";
			return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, error.str());
		}



		return ::grpc::Status(::grpc::StatusCode::OK, "");
	}

	::grpc::Status DXServiceImpl::SetFile(::grpc::ServerContext* context, ::grpc::ServerReader< ::Excercise::File>* reader, ::google::protobuf::Empty* response)  
	{
		(void) context;
		(void) reader;
		(void) response;
		return ::grpc::Status(::grpc::StatusCode::OK, "");
	}
}
