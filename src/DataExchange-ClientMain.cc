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
    << "" << std::endl
    << "" << std::endl
    << "" << std::endl;
    exit(-1);
}

// Enable the log
bool Logger::enabled = true;

int main(int argc, char **argv)
{
  // initialise the logger: redirect std::clog to a log file
  std::stringstream logFileName;
  logFileName << "GetHurricaneLoss." << ::getpid() << ".log";
  std::ofstream logFile(logFileName.str());
  std::streambuf *clogBuff = std::clog.rdbuf();
  std::clog.rdbuf(logFile.rdbuf());
  {
    Logger log("Main", "Function");

    std::map<std::string, std::string> params = { 
      {"", 0},
      {"", 0},
      {"", 0},
      {"", 0},
      {"", 0},
      {"", 0},
      {"", 0} };

    for(int i = 1; i < argc; ++i)
    {
      if( params.find(argv[i]) == params.end() || i + 1 > argc )
      {
        std::cout << "Unrecognised parameter [" << argv[i] << "]" << std::endl;
        usage();
      }

      std::stringstream str;
      str << argv[i + 1];
			std::string value = 0;
      str >> value;
      params[argv[i]] = value;
      ++i;
    }

  }

	// Start the server
	//std::string server_address("0.0.0.0:50051");
	
  std::clog.rdbuf(clogBuff);
  return 0;
}


