
LDLIBS=-lgpr -lgrpc++ -lgrpc++_cronet -lgrpc++_error_details -lgrpcpp_channelz -lgrpc++_reflection -lgrpc++_unsecure 
STATICS=protobuf/libprotobuf.a protobuf/libprotoc.a  #libgrpc++.a libgrpc++_core_stats.a libgrpc++_cronet.a  libgrpc++_error_details.a libgrpcpp_channelz.a libgrpc++_reflection.a libgrpc++_unsecure.a

SRC_DIR=$(shell pwd)
SRV_SRCS=$(wildcard ./*.grpc.pb.cc ./DataExchange-Server*.cc,)
CLT_SRCS=$(wildcard ./DataExchange.pb.cc ./*-Client*.cc)
SRV_BIN=$(SRC_DIR)/grpcServer
CLT_BIN=$(SRC_DIR)/grpcClient

include ../Makefile.base
