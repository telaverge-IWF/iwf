include ../../../Makefile.inc

CXXFLAGS += -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include -I$(EACC_ROOT)/cmapi/idl -I$(EACC_ROOT)/cmapi/common -I$(EACC_ROOT)/cmapi/configfetch/include -I$(EACC_ROOT)/cmapi/components/include -I$(EACC_ROOT)/cmapi/dreconfig/include
LIBS += -lmess -lblocks -ldl -L$(EACC_ROOT)/cmapi/idl/lib -lprotobuf -lcmapicomp  -lcompoidl -ldrecmapi -lStatsidl -ldreidl 
DBGDIR:=debug
BINDIR := ./bin/$(DBGDIR)/
PeerGrpTestAgent_BIN := PeerGrpTestAgent
PeerGrpTestAgent_OFILES := TestAgent.o
TARGETS_BIN := PeerGrpTestAgent


include ../../../Makefile.rules

