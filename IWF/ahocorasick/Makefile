LIBNAME := libahocorasick.so
CFLAGS := -Wall -Werror -fpic 
HEADERS := actypes.h ahocorasick.h node.h
BUILD_DIRECTORY := ../lib

all: $(LIBNAME)
 
$(LIBNAME): mkbuilddir ahocorasick.o node.o
	#ar -cvq $(BUILD_DIRECTORY)/$(LIBNAME) $(BUILD_DIRECTORY)/ahocorasick.o $(BUILD_DIRECTORY)/node.o
	gcc -shared -o $(BUILD_DIRECTORY)/$(LIBNAME) $(BUILD_DIRECTORY)/node.o $(BUILD_DIRECTORY)/ahocorasick.o

ahocorasick.o: ahocorasick.c $(HEADERS)
	cc -o $(BUILD_DIRECTORY)/ahocorasick.o -c ahocorasick.c $(CFLAGS)

node.o: node.c $(HEADERS)
	cc -o $(BUILD_DIRECTORY)/node.o -c node.c $(CFLAGS)

mkbuilddir:
	mkdir -p $(BUILD_DIRECTORY)

clean:
	rm -rf $(BUILD_DIRECTORY)
