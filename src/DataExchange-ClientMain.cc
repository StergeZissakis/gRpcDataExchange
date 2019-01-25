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
    << "grpcClient -i [IP address] -p [port] -num [number] -text [string] -f [filename]" << std::endl
    << "  -i    = The IP address to connect to." << std::endl
    << "  -p    = The port to connect to." << std::endl
    << "  -num  = The number to pass to the server." << std::endl
    << "  -text = The string-text to pass to the server." << std::endl
    << "  -uf   = The name of the file to upload to the server." << std::endl
    << "  -df   = The name of the file to download from the server." << std::endl;

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
			{"-num", "5"}, 
			{"-text", "Sterge"}, 
			{"-uf", ""}, 
			{"-df", ""}, 
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
			log.log("Connected to: " + connStr.str());
			long long i = 0;
			std::string t("");
			if( client.GetParameters(i, t) )
			{
				log.log("Initially read parameters [" + std::to_string(i) + std::string("] and [") + t + std::string("] from server"));
				std::cout	<< "Server initially returned parameters as [" << i << "] and [" << t << "]\n";
			}
			else
			{
				log.log("Failed to retrieve initial values");
				std::cout << "Initial values retrieval Faield!\n";
				return -2;
			}
			if( client.SetParameters(std::atoi(params["-num"].c_str()), params["-text"] ) )
			{
				log.log("Parameters set successfull to [" + params["-num"] + std::string("] & [") +  params["-text"]);
				std::cout << "Set number to [" << params["-num"] << "] & [" << params["-text"] << "]\n";
			}
			else
			{
				log.log("Failed to set parameters");
				std::cout << "Parameter setting Faield!\n";
				return -3;
			}
			if( client.GetParameters(i, t) )
			{
				log.log("Read parameters [" + std::to_string(i) + std::string("] and [") + t + std::string("] from server"));
				std::cout	<< "Server returned parameters as [" << i << "] and [" << t << "]\n";
			}
			else
			{
				log.log("Failed to retrieve parameters");
				std::cout << "Parameter retrieval Faield!\n";
				return -4;
			}

			// Upload a file
			if( params["-uf"].size() ) 
			{
				std::cout << "Uploading file : " << params["-uf"] << "\n";
				if( !client.UploadFile(params["-uf"])) 
					log.log("Failed to upload file : " + params["-uf"]);
				else
					log.log("Uploaded file : " + params["-uf"]);
			}

			// Download a file
			if( params["-df"].size() ) 
			{
				std::cout << "Downloading file : " << params["-df"] << "\n";
				if( !client.DownloadFile(params["-df"])) 
					log.log("Failed to download file : " + params["-uf"]);
				else
					log.log("Downloaded file : " +  params["-df"]);
			}
		}
		else
		{
			log.log("Failed to connect to server @ " + connStr.str());
			std::cout << "Connection to server Failed @ " << connStr.str() << "!\n";
			return -1;
		}

		

	}
	std::clog.rdbuf(clogBuff);
  return 0;
}


