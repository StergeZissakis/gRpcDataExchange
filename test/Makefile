
LDLIBS=-pthread

SRC_DIR=$(shell pwd)
BIN=$(SRC_DIR)/unitTests
STATICS=libgtest.a

include ../Makefile.base

test: 
	$(shell ./unitTests | tee unitTests.out 2>&1)
	$(shell ./grpcClientServerTest.bash 2>&1 | tee grpcClientServerTest.out )
	$(shell tail -f grpcClientServerTest.out)
