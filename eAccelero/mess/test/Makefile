include ../../Makefile.inc

CXXFLAGS += -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include -I.
LIBS += -L${PROTOBUF_PATH}/.libs -lmess -lblocks -lprotobuf

BINDIR := ./bin/$(DBGDIR)/

toptest_BIN := toptest
toptest_OFILES := TopologyTest.o

messclient_BIN := messclient
messclient_OFILES := testing.pb.o MeSSClient.o 

messserver_BIN := messserver
messserver_OFILES := testing.pb.o MeSSServer.o 

unitmessserver_BIN := unitmessserver
unitmessserver_OFILES := unit_MeSSServer.o

utesting_BIN := utesting
utesting_OFILES := utesting.o

TARGETS_BIN := toptest messserver messclient unitmessserver utesting
#TARGETS_BIN := messserver messclient


include ../../Makefile.rules



