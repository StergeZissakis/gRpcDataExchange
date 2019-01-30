#!/bin/bash

function checkResult () {
	result=$1
	OK=$2
	KO=$3

	if [[ "$result" == "0" ]]; then
		echo "$OK"
		return 0
	else 
		echo "$KO"
		return -1
	fi
}

function binaryCompareFiles () {
	file1=$1
	file2=$2

	cmp "$file1" "$file2"
	checkResult "$?" "The files $file1 and $file2 are IDENTICAL" "The files $file1 and $file2 DIFFER"
	if [[ "$?" -ne "0" ]]; then
		exit -1
	fi
}

function uploadFileAndCompare () {
	clt_dir=$1
	clt_bin=$2
	uld_file=$3
	srv_dir=$4

	cd "$clt_dir"
	$clt_bin -uf "$uld_file"
	res="$?"
	cd -

	checkResult "$res" "File $clt_dir/$uld_file uploaded OK." "File upload FAILED for $clt_dir/$uld_file"
	if [[ "$?" ==  "0" ]]; then 
		echo "Checking if $clt_dir/$uld_file and $srv_dir/$uld_file files are identical: no data loss during the TX"
		binaryCompareFiles "$clt_dir/$uld_file" "$srv_dir/$uld_file"
	fi
}

function downloadFileAndCompare () {
	clt_dir=$1
	clt_bin=$2
	dld_file=$3
	srv_dir=$4

	cd "$clt_dir"
	$clt_bin -df "$dld_file"
	res="$?"
	cd -

	checkResult "$res" "File $clt_dir/$dld_file downloaded OK." "File download FAILED for $clt_dir/$dld_file"
	if [[ "$?" == "0" ]]; then 
		echo "Checking if $srv_dir/$dld_file and $clt_dir/$dld_file files are identical: no data loss during the TX"
		binaryCompareFiles "$srv_dir/$dld_file" "$clt_dir/$dld_file"
	fi
}

BIN_DIR="$(dirname $PWD)/bin"
CLT_BIN="$BIN_DIR/grpcClient"
SRV_BIN="$BIN_DIR/grpcServer"

SRV_DIR="server_dir"
CLT_DIR="client_dir"

BIG_FILE="big.file"
REG_FILE="regular.file"
SML_FILE="small.file"

#
# Set up
#
pkill "$SRV_BIN" # just in case
mkdir -p ./$SRV_DIR 
mkdir -p ./$CLT_DIR

echo "Starting Server..."
$(cd "$SRV_DIR"; nohup "$SRV_BIN" > grpcServer.out 2>&1&)
echo "Generating test data files. Please be wait, it may take several minutes...."
$(cd $CLT_DIR; head -c 2G < /dev/urandom > $BIG_FILE)
$(cd $CLT_DIR; head -c 56M < /dev/urandom > $REG_FILE)
$(cp "../README.md" "./$CLT_DIR/$SML_FILE") # use our README.md as a small file; it is smaller than the current buffer size

#
# Numeric and text attributes manipulation
#
echo "Testing Parameter passing..."
echo "-- Default parameters: num and text are intially 0 and blank."
cd "$CLT_DIR"; 
"$CLT_BIN"
echo "-- Set num and text to 10 and \"Stergio\", respectively. The inital values must be as per the previous call."
"$CLT_BIN" -num 10 -text "Stergio)"
cd -


#
# Upload files
#
echo "Testing upload..."
echo "Uploading big file (size > 1GB)"
uploadFileAndCompare "$CLT_DIR" "$CLT_BIN" "$BIG_FILE" "$SRV_DIR"
echo "Uploading regular file (size > 50MB)"
uploadFileAndCompare "$CLT_DIR" "$CLT_BIN" "$REG_FILE" "$SRV_DIR"
echo "Uploading small file (size < 1KB)"
uploadFileAndCompare "$CLT_DIR" "$CLT_BIN" "$SML_FILE" "$SRV_DIR"

# Delete all data files in $CLT_DIR
$(cd $CLT_DIR; rm -f ./$BIG_FILE ./$REG_FILE ./$SML_FILE)

#
# Download the files back into the client dir, from the server dir
#

echo "Testing download..."
echo "Download big file (size > 1GB)"
downloadFileAndCompare "$CLT_DIR" "$CLT_BIN" "$BIG_FILE" "$SRV_DIR"
echo "Download regular file (size > 50MB)"
downloadFileAndCompare "$CLT_DIR" "$CLT_BIN" "$REG_FILE" "$SRV_DIR"
echo "Download small file (size < 1KB)"
downloadFileAndCompare "$CLT_DIR" "$CLT_BIN" "$SML_FILE" "$SRV_DIR"

pkill "$SRV_BIN"
