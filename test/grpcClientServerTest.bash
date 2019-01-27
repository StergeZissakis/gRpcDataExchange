#!/bin/bash

function checkResult {
	result=$1
	OK=$2
	KO=$3

	if [ "$result" -eq 0 ]; then
		echo "$OK"
		return 0
	else 
		echo "$KO"
		return -1
	fi
}

function binaryCompareFiles {
	cmp $1 $2
	res=$?
	res=checkResult $res "The files [$1] and [$2] are IDENTICAL" "The files [$1] and [$2] DIFFER"
	if [ "$res" -ne 0 ]; then
		exit -1
	fi
}

function uploadFileAndCompare {
	CLT_DIR=$1
	CLT_BIN=$2
	ULD_FILE=$3
	SRV_DIR=$4

	$(cd $CLT_DIR; $CLT_BIN -uf $ULD_FILE)
	res=$?
	checkResult $res "File [$CLT_DIR/$ULD_FILE] uploaded OK." "File upload FAILED for [$CLT_DIR/$ULD_FILE]"
	if [ "$?" -eq 0]; then 
		echo "Checking if [$CLT_DIR/$ULD_FILE] and [$SRV_DIR/$ULD_FILE] files are identical; no data loss during the TX"
		binaryCompareFiles $CLT_DIR/$ULD_FILE $SRV_DIR/$ULD_FILE
	fi
}


function downloadFileAndCompare {
	CLT_DIR=$1
	CLT_BIN=$2
	DLD_FILE=$3
	SRV_DIR=$4

	$(cd $CLT_DIR; $CLT_BIN -df $DLD_FILE)
	res=$?
	checkResult $res "File [$CLT_DIR/$DLD_FILE] downloaded OK." "File download FAILED for [$CLT_DIR/$DLD_FILE]"
	if [ "$?" -eq 0]; then 
		echo "Checking if [$SRV_DIR/$DLD_FILE] and [$CLT_DIR/$DLD_FILE] files are identical; no data loss during the TX"
		binaryCompareFiles $SRV_DIR/$DLD_FILE $CLT_DIR/$DLD_FILE
	fi
}

BIN_DIR=$(dirname $PWD)/bin
CLT_BIN=$BIN_DIR/grpcClient
SRV_BIN=$BIN_DIR/grpcServer

SRV_DIR=server_dir
CLT_DIR=client_dir

BIG_FILE=big.file
REG_FILE=regular.file
SML_FILE=small.file

#
# Set up
#
mkdir -p ./$SRV_DIR 
mkdir -p ./$CLT_DIR

echo "Starting Server..."
$(cd $SRV_DIR; nohup ../bin/grpcServer > grpcServer.out 2>&1&)
echo "Generating test data files. Please be wait, it may take several minutes...."
$(cd $CLT_DIR; head -c 2G < /dev/urandom > $BIG_FILE)
$(cd $CLT_DIR; head -c 56M < /dev/urandom > $REG_FILE)
$(cd $CLT_DIR; cp ../../README.md ./$SML_FILE) # use our README.md as a small file; it is smaller than the current buffer size

#
# Numeric and text attributes manipulation
#
echo "Testing Parameter passing..."
echo "-- Default parameters: num and text are intially 0 and blank."
$(cd $CLT_DIR; $CLT_BIN)
echo "-- Set num and text to 10 and \"Stergio\", respectively. The inital values must be as per the previous call."
$(cd $CLT_DIR; $CLT_BIN -num 10 -text Stergio)


#
# Upload files
#
echo "Testing upload..."
echo "Uploading big file (size > 1GB)"
uploadFileAndCompare $CLT_DIR $CLT_BIN $BIG_FILE $SRV_DIR
echo "Uploading regular file (size > 50MB)"
uploadFileAndCompare $CLT_DIR $CLT_BIN $REG_FILE $SRV_DIR
echo "Uploading small file (size < 1KB)"
uploadFileAndCompare $CLT_DIR $CLT_BIN $SML_FILE $SRV_DIR

# Delete all data files in $CLT_DIR
$(cd $CLT_DIR; rm -f ./$BIG_FILE ./$REG_FILE ./$SML_FILE)

#
# Download the files back into the client dir, from the server dir
#

echo "Testing download..."
echo "Download big file (size > 1GB)"
downloadFileAndCompare $CLT_DIR $CLT_BIN $BIG_FILE $SRV_DIR
echo "Download regular file (size > 50MB)"
downloadFileAndCompare $CLT_DIR $CLT_BIN $REG_FILE $SRV_DIR
echo "Download small file (size < 1KB)"
downloadFileAndCompare $CLT_DIR $CLT_BIN $SML_FILE $SRV_DIR

pkill grpcServer


