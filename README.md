# gRPCDataExchange
PoC app using the gRPC protocol.

# Description
A command line client is provided that makes RPC calls to the gRPC server.
The client is capable of uploading and downlading file to and from the server.
Files are streamed by chunking; the current max chunk size is 2048 and gzip streaming compression is used in both directions.
Also the client can set and retrieve values (a numeric and a string, grouped in the same message), to demonstrate non-streaming functionality.

# Requirements:
* Debian/Raspbian dev env, e.g. g++, make, cmake, git, etc
* libssl-dev: OpenSSL Development libs
* c-ares lib

# Environment
* PATH must include the gRPC/bin directory.
* 'LD_LIBRARY_PATH' must also point to gRPC/lib directory.

# How to Build & Automatically Test
cd into the cloned repo and issue
"make install test"
This should download and build all the peripheral packages, such as gRPC itself and Google Protocol Buffers.
Once everything is build, (make) test will run the .bash script inside the test directory that will perform all possible actions on the server. The output of the script is tee'ed to a file too.
Look for .log and .out files inside the "client_dir" and "server_dir" under the test directory. 
If you enounter any problems, please contact me.

# How to manually test
In the bin directory, there are the following binaries, apart from all the others installed there by the peripheral packages:
* grpcClient
* grpcServer
Please use the "-h" option for a usage/help menu of each command.

* Start the server:
** "grpcServer &"
*** It should be displaying the IP and port the server is listening at.
*** Please note that the directory you start the server in, does matter. This where all uploaded files are placed. Also this is place to put files in for downloading off the server.

* Using the client
** "grpcClient -h"
*** will display the help/usage menu of the client. There are several poarameters, some for non-streaming calls and some for streaming calls.
*** To upload a file please issue:
*** "grpcClient -uf filename"

# Black Box Tests VS Unit Tests
* Black Box Tests
The script test/grpcClientServerTest.bash generates 3 files, 2GB, 56MB and the file you are currently reading, as test data.
All the files are uploaded to and downloaded from the server. The generation is done using /dev/urandom and a cp command.
The first two files are binary while the last one is (obviosuly) text/ASCII. The command cmp is used to compare the original with its uploaded/downloaded counterpart; diff is no good with binary files. Thus ensuring integrity and clarity in terms of testing, against the requirements.
At the of the tests you should have the same data files (.file suffix) in both test/server_dir and test/client_dir. Feel free to cmp them to verify that there was no loss or corruption of the data.
* Unit Tests
Although GoogleTest is fetched and built by "make" separately to grpc which has the gtest option disabled, there is not really any substantial code to be unit tested, apart from the logger class. This and only one unit test were included for completeness.
#NB
DO NOT START THE CLIENT IN THE SAME DIRECTORY YOU STARTED THE SERVER. This will cause a mess when streaming.
DO NOT USE ANY FULL OR RELATIVE PATHS WHEN SPECIFYING FILE NAMES; the proggies were made and kept simple.

## Developed on: 
* Linux 4.14.79-v7+ #1159 SMP Sun Nov 4 17:50:20 GMT 2018 armv7l GNU/Linux
** Flavour: Raspbian GNU/Linux 9 (stretch)
* Created in Vim
