include ../../../Makefile.inc

CXXFLAGS += -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include -I$(EACC_ROOT)/cmapi/idl -I$(EACC_ROOT)/cmapi/common -I$(EACC_ROOT)/cmapi/configfetch/include
LIBS += -lmess -lblocks -ldl -L$(EACC_ROOT)/cmapi/idl/lib -lcmapicomp  -lcmapiconfig -ldrecmapi -lcfgfetch  -lcompoidl  -ldreidl -lprotobuf 
DBGDIR:=debug
BINDIR := ./bin/$(DBGDIR)/
TestAgent_BIN := TestAgent
TestAgent_OFILES := TestAgent.o
TARGETS_BIN := TestAgent


include ../../../Makefile.rules

