#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <grpc++/grpc++.h>
#include <grpc++/server_builder.h>
#include <DataExchange-Server.h>

#include <unistd.h>

#include <utils/Logger.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;


void usage()
{
  Logger log("Usage", "Function");
  log.log("Invalida command line parameter.");

  std::cout 
    << "grpcServer -i [IP address] -p [port]" << std::endl
    << "  -i = The IP address to bind to." << std::endl
    << "  -p = The port to listen to." << std::endl;
    exit(-100);
}

// Enable the log
bool Logger::enabled = true;

int main(int argc, char **argv)
{
	// initialise the logger: redirect std::clog to a log file
	std::stringstream logFileName;
	logFileName << "gRPC_Server.log";
	std::ofstream logFile(logFileName.str());
	std::streambuf *clogBuff = std::clog.rdbuf();
	std::clog.rdbuf(logFile.rdbuf());
	{
		Logger log("Main", "DataExchange-Server");

		std::map<std::string, std::string> params = 
		{ 
			{"-i", "0.0.0.0"},
			{"-p", "50051"}, 
		};

		{ // parse args
			for(int i = 1; i < argc; ++i)
			{
				if( params.find(argv[i]) == params.end() || i + 1 > argc )
				{
					std::cout << "Unrecognised parameter [" << argv[i] << "]" << std::endl;
					usage();
				}

				std::stringstream str;
				str << argv[i + 1];
				std::string value("");
				str >> value;
				params[argv[i]] = value;
				++i;
			}
		}

		// Start the server
		std::stringstream connStr;
		connStr << params["-i"] << ":" << params["-p"];

		std::string server_address(connStr.str());
		log.log("Starting server at: " + server_address);
		std::cout << "Starting server at " << server_address << "\n";

		Exercise::DXServiceImpl service;
		grpc::ServerBuilder builder;
		builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
		builder.RegisterService(&service);
		std::unique_ptr<Server> server(builder.BuildAndStart());

		log.log("Server started succeffully\n");
		std::cout << "Server started on " << server_address << std::endl;
		server->Wait();

		std::clog.rdbuf(clogBuff);
	}
	return 0;
}


