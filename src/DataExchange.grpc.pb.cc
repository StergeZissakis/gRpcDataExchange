// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: DataExchange.proto

#include "DataExchange.pb.h"
#include "DataExchange.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace Excercise {

static const char* DataExchange_method_names[] = {
  "/Excercise.DataExchange/GetParameters",
  "/Excercise.DataExchange/SetParameters",
  "/Excercise.DataExchange/GetFile",
  "/Excercise.DataExchange/SetFile",
};

std::unique_ptr< DataExchange::Stub> DataExchange::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< DataExchange::Stub> stub(new DataExchange::Stub(channel));
  return stub;
}

DataExchange::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_GetParameters_(DataExchange_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_SetParameters_(DataExchange_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetFile_(DataExchange_method_names[2], ::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_SetFile_(DataExchange_method_names[3], ::grpc::internal::RpcMethod::CLIENT_STREAMING, channel)
  {}

::grpc::Status DataExchange::Stub::GetParameters(::grpc::ClientContext* context, const ::Excercise::Empty& request, ::Excercise::Parameters* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetParameters_, context, request, response);
}

void DataExchange::Stub::experimental_async::GetParameters(::grpc::ClientContext* context, const ::Excercise::Empty* request, ::Excercise::Parameters* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetParameters_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::Excercise::Parameters>* DataExchange::Stub::AsyncGetParametersRaw(::grpc::ClientContext* context, const ::Excercise::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Excercise::Parameters>::Create(channel_.get(), cq, rpcmethod_GetParameters_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::Excercise::Parameters>* DataExchange::Stub::PrepareAsyncGetParametersRaw(::grpc::ClientContext* context, const ::Excercise::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Excercise::Parameters>::Create(channel_.get(), cq, rpcmethod_GetParameters_, context, request, false);
}

::grpc::Status DataExchange::Stub::SetParameters(::grpc::ClientContext* context, const ::Excercise::Parameters& request, ::Excercise::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_SetParameters_, context, request, response);
}

void DataExchange::Stub::experimental_async::SetParameters(::grpc::ClientContext* context, const ::Excercise::Parameters* request, ::Excercise::Empty* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_SetParameters_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::Excercise::Empty>* DataExchange::Stub::AsyncSetParametersRaw(::grpc::ClientContext* context, const ::Excercise::Parameters& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Excercise::Empty>::Create(channel_.get(), cq, rpcmethod_SetParameters_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::Excercise::Empty>* DataExchange::Stub::PrepareAsyncSetParametersRaw(::grpc::ClientContext* context, const ::Excercise::Parameters& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Excercise::Empty>::Create(channel_.get(), cq, rpcmethod_SetParameters_, context, request, false);
}

::grpc::ClientReader< ::Excercise::File>* DataExchange::Stub::GetFileRaw(::grpc::ClientContext* context, const ::Excercise::Empty& request) {
  return ::grpc::internal::ClientReaderFactory< ::Excercise::File>::Create(channel_.get(), rpcmethod_GetFile_, context, request);
}

void DataExchange::Stub::experimental_async::GetFile(::grpc::ClientContext* context, ::Excercise::Empty* request, ::grpc::experimental::ClientReadReactor< ::Excercise::File>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::Excercise::File>::Create(stub_->channel_.get(), stub_->rpcmethod_GetFile_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::Excercise::File>* DataExchange::Stub::AsyncGetFileRaw(::grpc::ClientContext* context, const ::Excercise::Empty& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::Excercise::File>::Create(channel_.get(), cq, rpcmethod_GetFile_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::Excercise::File>* DataExchange::Stub::PrepareAsyncGetFileRaw(::grpc::ClientContext* context, const ::Excercise::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::Excercise::File>::Create(channel_.get(), cq, rpcmethod_GetFile_, context, request, false, nullptr);
}

::grpc::ClientWriter< ::Excercise::File>* DataExchange::Stub::SetFileRaw(::grpc::ClientContext* context, ::Excercise::Empty* response) {
  return ::grpc::internal::ClientWriterFactory< ::Excercise::File>::Create(channel_.get(), rpcmethod_SetFile_, context, response);
}

void DataExchange::Stub::experimental_async::SetFile(::grpc::ClientContext* context, ::Excercise::Empty* response, ::grpc::experimental::ClientWriteReactor< ::Excercise::File>* reactor) {
  ::grpc::internal::ClientCallbackWriterFactory< ::Excercise::File>::Create(stub_->channel_.get(), stub_->rpcmethod_SetFile_, context, response, reactor);
}

::grpc::ClientAsyncWriter< ::Excercise::File>* DataExchange::Stub::AsyncSetFileRaw(::grpc::ClientContext* context, ::Excercise::Empty* response, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::Excercise::File>::Create(channel_.get(), cq, rpcmethod_SetFile_, context, response, true, tag);
}

::grpc::ClientAsyncWriter< ::Excercise::File>* DataExchange::Stub::PrepareAsyncSetFileRaw(::grpc::ClientContext* context, ::Excercise::Empty* response, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::Excercise::File>::Create(channel_.get(), cq, rpcmethod_SetFile_, context, response, false, nullptr);
}

DataExchange::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataExchange_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataExchange::Service, ::Excercise::Empty, ::Excercise::Parameters>(
          std::mem_fn(&DataExchange::Service::GetParameters), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataExchange_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataExchange::Service, ::Excercise::Parameters, ::Excercise::Empty>(
          std::mem_fn(&DataExchange::Service::SetParameters), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataExchange_method_names[2],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< DataExchange::Service, ::Excercise::Empty, ::Excercise::File>(
          std::mem_fn(&DataExchange::Service::GetFile), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataExchange_method_names[3],
      ::grpc::internal::RpcMethod::CLIENT_STREAMING,
      new ::grpc::internal::ClientStreamingHandler< DataExchange::Service, ::Excercise::File, ::Excercise::Empty>(
          std::mem_fn(&DataExchange::Service::SetFile), this)));
}

DataExchange::Service::~Service() {
}

::grpc::Status DataExchange::Service::GetParameters(::grpc::ServerContext* context, const ::Excercise::Empty* request, ::Excercise::Parameters* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataExchange::Service::SetParameters(::grpc::ServerContext* context, const ::Excercise::Parameters* request, ::Excercise::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataExchange::Service::GetFile(::grpc::ServerContext* context, const ::Excercise::Empty* request, ::grpc::ServerWriter< ::Excercise::File>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataExchange::Service::SetFile(::grpc::ServerContext* context, ::grpc::ServerReader< ::Excercise::File>* reader, ::Excercise::Empty* response) {
  (void) context;
  (void) reader;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace Excercise

