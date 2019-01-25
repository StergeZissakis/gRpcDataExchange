#ifndef ___DATAX_SERVER__HH__
#define ___DATAX_SERVER__HH__

#include <string>
#include <sstream>

//#include <DataExchange.pb.h>
#include <DataExchange.grpc.pb.h>

namespace Exercise
{
	// Server implementation definitions
	class DXServiceImpl final : public ::Exercise::DataExchange::Service
	{
		public:
			DXServiceImpl() {}
			virtual ~DXServiceImpl() {}

			::grpc::Status GetParameters(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::Exercise::Parameters* response) override;
			::grpc::Status SetParameters(::grpc::ServerContext* context, const ::Exercise::Parameters* request, ::google::protobuf::Empty* response) override;
			::grpc::Status GetFile(::grpc::ServerContext* context, const ::Exercise::File* request, ::grpc::ServerWriter< ::Exercise::File>* writer) override;
			::grpc::Status SetFile(::grpc::ServerContext* context, ::grpc::ServerReader< ::Exercise::File>* reader, ::google::protobuf::Empty* response) override;


		private:
			static int _sm_number;
			static std::string _sm_string;
	};
}

#endif
