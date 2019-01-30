PBC=../bin/protoc
CCP=../bin/grpc_cpp_plugin


PRS_DIR=$(shell pwd) 
PROTOS=$(wildcard *.proto)
GEN_SRV_C=$(subst .proto,.grpc.pb.cc,$(PROTOS))
GEN_SRV_H=$(subst .proto,.grpc.pb.h,$(PROTOS))
GEN_CLT_C=$(subst .proto,.pb.cc,$(PROTOS))
GEN_CLT_H=$(subst .proto,.pb.h,$(PROTOS))

all: $(GEN_SRV_C) $(GEN_SRV_H) $(GEN_CLT_C) $(GEN_CLT_H)

$(GEN_SRV_C) $(GEN_SRV_H): $(PROTOS)
	$(PBC) -I. --grpc_out=../src/ --plugin=protoc-gen-grpc=$(CCP) $<

$(GEN_CLT_C) $(GEN_CLT_H): $(PROTOS)
	$(PBC) -I. --cpp_out=../src/ $< 
