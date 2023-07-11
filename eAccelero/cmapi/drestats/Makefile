include $(EACC_ROOT)/Makefile.inc

INCLS:= -I$(EACC_ROOT)/mess/include \
	-I$(EACC_ROOT)/blocks/include \
	-I$(EACC_ROOT)/common/include \
	-I$(EACC_ROOT)/3rdparty/include \
	-I$(EACC_ROOT)/cmapi/idl \
	-I$(EACC_ROOT)/cmapi/common \
	-I$(EACC_ROOT)/cmapi/drestats/include 

CXXFLAGS += -std=c++0x -I. $(INCLS)

DRESTATS_AR := libdrestatscmapi.a
DRESTATS_OFILES := CMAPIStatsLib.o

TARGETS_AR := DRESTATS

include $(EACC_ROOT)/Makefile.rules

