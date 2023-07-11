include $(EACC_ROOT)/Makefile.inc

INCLS:= -I$(EACC_ROOT)/mess/include \
	-I$(EACC_ROOT)/blocks/include \
	-I$(EACC_ROOT)/common/include \
	-I$(EACC_ROOT)/3rdparty/include \
	-I$(EACC_ROOT)/cmapi/idl \
	-I$(EACC_ROOT)/cmapi/common \
	-I$(EACC_ROOT)/cmapi/components/include 

CXXFLAGS += -std=c++0x -I. $(INCLS)

CMAPIDREALARMS_AR := libcmapidrealarms.a
CMAPIDREALARMS_OFILES := CMAPIDreAlarms.o

TARGETS_AR := CMAPIDREALARMS

include $(EACC_ROOT)/Makefile.rules

