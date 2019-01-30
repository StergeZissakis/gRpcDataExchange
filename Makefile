BUILD_DIRECTORIES=share protos src test

all:
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )

install: all
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )


clean:
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )
	find . -name "*.log" -type f | xargs rm -f
	find . -name "*.out" -type f | xargs rm -f
	find . -name "*.file" -type f | xargs rm -f
	git ls-files bin --others | xargs rm -rf 
	git ls-files include --others | xargs rm -rf 	
	git ls-files lib --others | xargs rm -rf 
	git ls-files share --others | xargs rm -rf 
	git ls-files src --others | xargs rm -rf 

test: install
	$(MAKE) -C ./test test
