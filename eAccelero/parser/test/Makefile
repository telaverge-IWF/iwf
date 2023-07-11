include ../../Makefile.inc

CXXFLAGS += -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include -I$(EACC_ROOT)/parser/test/include -Isrc
LIBS += -lmess -lblocks -lprotobuf

BINDIR := ./bin/$(DBGDIR)/

testserver_BIN := testserver
testserver_OFILES := test.pb.o test.o MeSSServer.o

testclient_BIN := testclient
testclient_OFILES := test.pb.o FlatUserAccess_caller.o UserAccess_caller.o MeSSClient.o

TARGETS_BIN := testserver testclient

include ../../Makefile.rules

