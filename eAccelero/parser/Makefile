
.PHONY: all clean

all: idl proto
	$(MAKE) -C test

idl:
	-rm interface_index
	./dq_idl_parser.py --src=test/idl --cpp=test --proto=test/proto -b

proto:
	cd test/proto; protoc --cpp_out=../src test.proto; cd -

clean:
	-rm -f interface_index
	-rm -rf test/proto test/include/*_caller.h test/src/*_caller.cpp
	-rm -f test/include/test_def.h test/include/test.h test/src/test.cpp
	$(MAKE) -C test clean 

