# gRPCDataExchange
PoC app using the gRPC protocol.

# Description
A command line client is provided that makes RPC calls to the gRPC server.
The client is capable of uploading and downlading file to and from the server.
Files are streamed by chunking; the current max chunk size is 2048 and gzip streaming compression is used in both directions.
Also the client can set and retrieve values (a numeric and a string, grouped in the same message), to demonstrate non-streaming functionality.

# Requirements:
* Debian/Raspbian development environment with the following isntalled:
`apt install git`
`apt install g++ `
`apt install make`
`apt install cmake`
`apt install curl wget`
`apt install autogen`
`apt install autoconf`
`apt install libtool`

# Environment
If you are to run the client/server binaries manually, then the following env vars are needed:
* PATH must include the gRPC/bin directory.
* 'LD_LIBRARY_PATH' must also point to gRPC/lib directory.
Please note that the test .bash script has been amended not require the above.

# How to Build & Automatically Test
cd into the cloned repo and issue
"make test"
This should download and build all the peripheral packages, such as gRPC itself and Google Protocol Buffers.
Once everything is build, (make) test will run the .bash script inside the test directory that will perform all possible actions on the server. The output of the script is tee'ed to a file too.
Look for .log and .out files inside the "client_dir" and "server_dir" under the test directory. 
If you enounter any problems, please contact me.

# How to manually test
In the bin directory, there are the following binaries, apart from all the others installed there by the peripheral packages:
* grpcClient
* grpcServer
Please use the "-h" option for a usage/help menu of each command.

# Running the Server
1. Start the server:
2. `grpcServer &`
3. It should be displaying the IP and port the server is listening at.
Please note that the directory you start the server and the client in, does matter. This where all uploaded files are placed. Also this is the place to put files in for downloading off the server as well as for uploading via the client.
DO NOT START the client and the server in the same directory.
ALSO please refrain to local, to the directories files, i.e. no paths used either relative or absolute.

# Running the client
1. `grpcClient -h` displays the help/usage menu of the client. There are several poarameters, some for non-streaming calls and some for streaming calls.
2. To upload a file please issue:
`grpcClient -uf filename`
3. To download a file please issue:
`grpcClient -df filename`
NOTE that the filename should not contain any path info and the file must reside with the client directory.

# Black Box Tests VS Unit Tests
## Black Box Tests
The script test/grpcClientServerTest.bash generates 3 files, 2GB, 56MB and the file you are currently reading, as test data.
All the files are uploaded to and downloaded from the server. The generation is done using /dev/urandom and a cp command.
The first two files are binary while the last one is (obviosuly) text/ASCII. The command cmp is used to compare the original with its uploaded/downloaded counterpart; diff is no good with binary files. Thus ensuring integrity and clarity in terms of testing, against the requirements.
At the end of the tests you should have the same data files (.file suffix) in both test/server_dir and test/client_dir. Feel free to cmp them to verify that there was no loss or corruption of the data.
## Unit Tests
Although GoogleTest is fetched and built by "make" separately to grpc which has the gtest option disabled, there is not really any substantial code to be unit tested, apart from the logger class. This and only one unit test were included for completeness.
#NB
DO NOT START THE CLIENT IN THE SAME DIRECTORY YOU STARTED THE SERVER. This will cause a mess when streaming.
DO NOT USE ANY FULL OR RELATIVE PATHS WHEN SPECIFYING FILE NAMES; the proggies were made and kept simple.

# Developed on: 
* Linux 4.14.79-v7+ #1159 SMP Sun Nov 4 17:50:20 GMT 2018 armv7l GNU/Linux
* Flavour: Raspbian GNU/Linux 9 (stretch)
* Created in Vim

# Also Tested on
* Linux debian 4.9.0-8-amd64 #1 SMP Debian 4.9.130-2 (2018-10-27) x86_64 GNU/Linux
