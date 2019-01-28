BUILD_DIRECTORIES=share protos src


all:
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )

install: all
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )

clean:
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )
	cd bin; rm -rf *
	cd lib; rm -rf *
	find . -name "*.log" -type f | xargs rm -f
	find . -name "*.out" -type f | xargs rm -f
	cd include; rm -rf `git ls-files . --others | sed -e 's/\/.*//' | sort | uniq`	
	cd lib; rm -rf *

test: install
	$(MAKE) -C ./test test
