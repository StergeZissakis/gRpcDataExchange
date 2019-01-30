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
	find . -name "*.file" -type f | xargs rm -f
	rm -rf `git ls-files include --others | sed -e 's/\/.*//' | sort | uniq`	
	cd lib; rm -rf *
	rm -f `git ls-files share --others`
	rm -f `git ls-files src --others`


test: install
	$(MAKE) -C ./test test
