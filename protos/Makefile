PBC=protoc
CCP=$(shell which grpc_cpp_plugin)


PRS_DIR=$(shell pwd) 
PROTOS=$(wildcard *.proto)
GENC=$(subst .proto,.pb.cc,$(PROTOS))
GENH=$(subst .proto,.pb.h,$(PROTOS))

$(GENC): $(PROTOS)
	$(PBC) -I. --grpc_out=../src/ --plugin=protoc-gen-grpc=$(CCP) $<
	$(PBC) -I. --cpp_out=../src/ $< 
