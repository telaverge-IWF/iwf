include $(EACC_ROOT)/Makefile.inc

INCLS:= -I$(EACC_ROOT)/mess/include \
	-I$(EACC_ROOT)/blocks/include \
	-I$(EACC_ROOT)/common/include \
	-I$(EACC_ROOT)/3rdparty/include \
	-I$(EACC_ROOT)/cmapi/idl \
	-I$(EACC_ROOT)/cmapi/common \
	-I$(EACC_ROOT)/cmapi/components/include 

CXXFLAGS += -std=c++0x -I. $(INCLS)

CMAPICOMP_AR := libcmapicomp.a
CMAPICOMP_OFILES := CMApiComp.o CMApiDTF.o CMApiASF.o

CMAPIHA_AR := libcmapiHA.a
CMAPIHA_OFILES := CMApiHA.o

TARGETS_AR := CMAPICOMP CMAPIHA

include $(EACC_ROOT)/Makefile.rules

