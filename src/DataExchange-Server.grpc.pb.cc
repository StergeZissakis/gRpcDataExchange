#include <iostream>
#include <fstream>
#include <DataExchange.grpc.pb.h>
#include <utils/Logger.h>


// Statics
int DXServiceImpl::_sm_number = 0;
std::string DXServiceImpl::_sm_string;
std::stringstream DXServiceImpl::_sm_file;

::grpc::Status DXServiceImpl::GetParameters(::grpc::ServerContext* context, const ::Excercise::Empty* request, ::Excercise::Parameters* response) {
  (void) context;
  (void) request;
	response->set_number(_sm_number);
	response->set_text(_sm_string);
  return ::grpc::Status(::grpc::StatusCode::OK, "");
}

::grpc::Status DXServiceImpl::SetParameters(::grpc::ServerContext* context, const ::Excercise::Parameters* request, ::Excercise::Empty* response) {
  (void) context;
  (void) response;

  _sm_number = request->get_number();
	_sm_string = request->get_text();
  return ::grpc::Status(::grpc::StatusCode::OK, "");
}

::grpc::Status DXServiceImpl::GetFile(::grpc::ServerContext* context, const ::Excercise::Empty* request, ::grpc::ServerWriter< ::Excercise::File>* writer) {
  (void) context;
  (void) request;
  return ::grpc::Status(::grpc::StatusCode::OK, "");
}

::grpc::Status DXServiceImpl::SetFile(::grpc::ServerContext* context, ::grpc::ServerReader< ::Excercise::File>* reader, ::Excercise::Empty* response) {
  (void) context;
  (void) reader;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::OK, "");
}
