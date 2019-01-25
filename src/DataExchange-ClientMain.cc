#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <DataExchange-Client.h>

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
    << "grpcClient -i [IP address] -p [port]" << std::endl
    << "  -i = The IP address to connect to." << std::endl
    << "  -p = The port to connect to." << std::endl;
    exit(-100);
}

// Enable the log
bool Logger::enabled = true;

int main(int argc, char **argv)
{
  // initialise the logger: redirect std::clog to a log file
  std::stringstream logFileName;
  logFileName << "gRPC_Client.log";
  std::ofstream logFile(logFileName.str());
  std::streambuf *clogBuff = std::clog.rdbuf();
  std::clog.rdbuf(logFile.rdbuf());
	{
		Logger log("Main", "DataExchange-Client");

		std::map<std::string, std::string> params = 
		{ 
			{"-i", "localhost"},
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
		DXServiceClient client(params["-i"],std::atoi(params["-p"].c_str()));
		if( client.connectToServer() )
		{
			std::clog << "Connect to [" << connStr.str() << " successfull\n";
			long long i = 0;
			std::string t("");
			if( client.GetParameters(i, t) )
			{
				std::clog	<< "Initially read parameters [" << i << "] and [" << t << "] from server\n";
				std::cout	<< "Server initially returned parameters as [" << i << "] and [" << t << "]\n";
			}
			else
			{
				std::clog << "Failed to retrieve initial values\n";
				std::cout << "Initial values retrieval Faield!\n";
				return -2;
			}
			if( client.SetParameters(5, "Sterge") )
			{
				std::clog << "Parameters set successfull to [5] & [Sterge]\n";
				std::cout << "Set number to [5] and text to [Sterge]\n";
			}
			else
			{
				std::clog << "Failed to set parameters\n";
				std::cout << "Parameter setting Faield!\n";
				return -3;
			}
			if( client.GetParameters(i, t) )
			{
				std::clog	<< "Read parameters [" << i << "] and [" << t << "] from server\n";
				std::cout	<< "Server returned parameters as [" << i << "] and [" << t << "]\n";
			}
			else
			{
				std::clog << "Failed to retrieve parameters\n";
				std::cout << "Parameter retrieval Faield!\n";
				return -4;
			}
		}
		else
		{
			std::clog << "Failed to connect to server @ " << connStr.str() << "\n";
			std::cout << "Connection to server Failed @ " << connStr.str() << "!\n";
			return -1;
		}

	}
	std::clog.rdbuf(clogBuff);
  return 0;
}


