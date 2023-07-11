include $(EACC_ROOT)/Makefile.inc

INCLS:= -I$(EACC_ROOT)/mess/include \
	-I$(EACC_ROOT)/blocks/include \
	-I$(EACC_ROOT)/common/include \
	-I$(EACC_ROOT)/3rdparty/include \
	-I$(EACC_ROOT)/cmapi/idl \
	-I$(EACC_ROOT)/cmapi/common \
	-I$(EACC_ROOT)/cmapi/dreconfig/include 

CXXFLAGS += -std=c++0x -I. $(INCLS)

DRECONFIG_AR := libdrecmapi.a
DRECONFIG_OFILES := CMAPILib.o CMAPIPlatform.o CMAPIKpi.o CMAPICmf.o

TARGETS_AR := DRECONFIG

include $(EACC_ROOT)/Makefile.rules

