
LDLIBS=-pthread

SRC_DIR=$(shell pwd)
BIN=$(SRC_DIR)/unitTests
STATICS=libgtest.a


include ../Makefile.base


test: 
	./unitTests | tee unitTests.out
	./grpcClientServerTest.bash | tee grpcClientServerTest.out

