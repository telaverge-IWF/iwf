include $(EACC_ROOT)/Makefile.inc

INCLS:= -I$(EACC_ROOT)/mess/include \
	-I$(EACC_ROOT)/blocks/include \
	-I$(EACC_ROOT)/common/include \
	-I$(EACC_ROOT)/3rdparty/include \
	-I$(EACC_ROOT)/cmapi/idl \
	-I$(EACC_ROOT)/cmapi/common \
	-I$(EACC_ROOT)/cmapi/usrmgt/include 

CXXFLAGS += -std=c++0x -I. $(INCLS)

USRMGT_AR := libusrmgtcmapi.a
USRMGT_OFILES := CMAPIUsrMgtLib.o 

TARGETS_AR := USRMGT

include $(EACC_ROOT)/Makefile.rules

