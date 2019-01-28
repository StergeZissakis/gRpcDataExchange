BUILD_DIRECTORIES= protos share src


all:
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )

install: all
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )

clean:
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )
	cd bin; rm -rf *
	cd lib; rm -rf *
	find . -name "*.log" -type f | xargs rm
	find . -name "*.out" -type f | xargs rm
	rm -rf `git ls-files include --others | sed -e 's/\/.*$//' | sort | uniq`	

test: install
	$(MAKE) -C ./test test
