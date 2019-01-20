
all: grpc gtest

grpc: grpc_get grpc_build grpc_install

gtest: gtest_get googletest/libgtest.a gtest_install

clean: gtest_clean grpc_clean

gtest_get: 
	git clone https://github.com/google/googletest.git

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
	git clone   https://github.com/grpc/grpc -b $(shell curl -L https://grpc.io/release)
	cd grpc; git submodule update --init

pwd=$(shell pwd)
prfx=$(shell dirname $(pwd)  )

grpc_build:
	cd grpc/third_party/protobuf/cmake; cmake -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX:PATH=$(prfx) .; make all 
	cd grpc/cmake; cmake -DCMAKE_INSTALL_PREFIX:PATH=$(prfx) ..; make all
	#$(MAKE) -C grpc

grpc_install:
	$(MAKE) -C grpc/third_party/protobuf/cmake install
	$(MAKE) -C grpc install
	#cp -Raf grpc/bins/opt/grpc_* ../bin/
	#cp -Raf grpc/bins/opt/protobuf/* ../bin/
	#cp -Raf grpc/libs/opt/lib* ../lib/
	#crm -rf ./grpcp -Raf grpc/include/* ../include/


grpc_clean:
	$(MAKE) -C grpc clean
	$(MAKE) -C grpc/third_party/protobuf/cmake clean
