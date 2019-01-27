BUILD_DIRECTORIES= protos share src


all:
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )

install: all
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )

clean:
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )
	cd bin; rm -rf *
	cd lib; rm -rf *

test: install
	$(MAKE) -C ./test test
