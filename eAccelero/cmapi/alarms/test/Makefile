include $(EACC_ROOT)/Makefile.inc

CXXFLAGS += -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include -I$(EACC_ROOT)/cmapi/idl -I$(EACC_ROOT)/cmapi/common -I$(EACC_ROOT)/cmapi/alarms/include 
LIBS += -lmess -lblocks -ldl -L$(EACC_ROOT)/cmapi/idl/lib -lcmapialarms -lAlarmsidl -lprotobuf 
DBGDIR:=debug
BINDIR := ./bin/$(DBGDIR)/
TestAgent_BIN := TestAgent
TestAgent_OFILES := TestAgent.o
TARGETS_BIN := TestAgent


include $(EACC_ROOT)/Makefile.rules

