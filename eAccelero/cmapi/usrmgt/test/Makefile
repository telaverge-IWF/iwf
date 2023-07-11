include $(EACC_ROOT)/Makefile.inc

IDLLIBS := -L$(EACC_ROOT)/cmapi/idl/lib -L$(EACC_ROOT)/cmapi/dreconfig/lib
LIBS += $(IDLLIBS) -lmess -lblocks -lprotobuf -ldrecmapi -ldreidl -lusrmgtcmapi -lusrmgtidl -L$(EACC_ROOT)/cmapi/idl/lib -lStatsidl

INCLS:= -I$(EACC_ROOT)/mess/include -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/common/include -I$(EACC_ROOT)/3rdparty/include -I$(EACC_ROOT)/cmapi/idl \
	-I$(EACC_ROOT)/cmapi/common -I$(EACC_ROOT)/cmapi/usrmgt/include

#BINDIR := ./bin/$(DBGDIR)/

CXXFLAGS += -std=c++0x -I. $(INCLS) $(LIBS) 

TESTAGENT_BIN := TestAgent
TESTAGENT_OFILES := TestAgent.o

TARGETS_BIN := TESTAGENT

include $(EACC_ROOT)/Makefile.rules

