#ifndef ___DATAX_CLIENT__HH__
#define ___DATAX_CLIENT__HH__

#include <string>
#include <sstream>	
#include <memory>

#include <grpc++/grpc++.h>
#include <DataExchange.grpc.pb.h>

Exercise::File MakeFile(const std::string& name);
Exercise::Parameters MakeParameters(long long numeric, const std::string& str);

class DXServiceClient 
{
	public:
		DXServiceClient(const std::string& addr, int port)
		: _serverAddress(addr), _serverPort(port)
		{
		}

		virtual ~DXServiceClient() {}

		bool connectToServer();

		bool SetParameters(long long num, const std::string& str) const;
		bool GetParameters(long long& num, std::string& str) const;

		static google::protobuf::Empty EmptyObj;
	private:
		DXServiceClient();
		typedef ::Exercise::DataExchange::Stub StubType;
		typedef ::grpc::Channel ChannelType;
		std::shared_ptr<ChannelType> _connection;
		std::unique_ptr<StubType> _stub;

		std::string _serverAddress;
		int _serverPort;
};

#endif
