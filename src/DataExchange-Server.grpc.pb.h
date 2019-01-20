#pragma once

#include <string>
#include <sstream>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include <helper.h>

// Server implementation definitions
class DXServiceImpl : public DataExchange::Service
{
public:

	::grpc::Status GetParameters(::grpc::ServerContext* context, const ::Excercise::Empty* request, ::Excercise::Parameters* response);
	::grpc::Status SetParameters(::grpc::ServerContext* context, const ::Excercise::Parameters* request, ::Excercise::Empty* response);
	::grpc::Status GetFile(::grpc::ServerContext* context, const ::Excercise::Empty* request, ::grpc::ServerWriter< ::Excercise::File>* writer);
	::grpc::Status SetFile(::grpc::ServerContext* context, ::grpc::ServerReader< ::Excercise::File>* reader, ::Excercise::Empty* response);


private:
	static int _sm_number;
	static std::string _sm_string;
	static std::stringstream _sm_file;
};

