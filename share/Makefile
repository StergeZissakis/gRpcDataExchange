
all: gtest grpc

grpc: grpc_get grpc_build grpc_install

gtest: gtest_get googletest/libgtest.a gtest_install

clean: gtest_clean grpc_clean

gtest_get: 
	if [ ! -d "./googletest" ]; then                        \
	  git clone https://github.com/google/googletest.git;   \
	fi

gtest_install: 
	install `find . -name libgtest\*.a -type f` ../lib
	cp -Raf googletest/googletest/include/* ../include/

gtest_clean: 
	rm -rf ./googletest
	rm -rf ../include/gtest
	rm -rf ../lib/libgtest*

googletest/libgtest.a: 
	cmake -B./googletest -H./googletest
	$(MAKE) -C googletest

grpc_get: 
	if [ ! -d "./grpc" ]; then                                                              \
	  git clone   https://github.com/grpc/grpc -b $(shell curl -L https://grpc.io/release); \
	fi
	cd grpc; git submodule update --init;                                                 

pwd=$(shell pwd)
prfx=$(shell dirname $(pwd)  )

grpc_build:
	cd grpc/third_party/protobuf; ./configure --prefix=$(prfx)
	$(MAKE) -C grpc/third_party/protobuf
	$(MAKE) -C grpc

grpc_install:
	cp -Raf grpc/bins/opt/grpc_* ../bin/
	cp -Raf grpc/bins/opt/protobuf/* ../bin/
	cp -Raf grpc/include/* ../include/
	cp -Raf grpc/libs/opt/* ../lib/


grpc_clean:
	$(MAKE) -C grpc clean
	$(MAKE) -C grpc/third_party/protobuf/cmake clean
