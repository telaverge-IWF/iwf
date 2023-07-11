include $(EACC_ROOT)/Makefile.inc

INCLS:= -I$(EACC_ROOT)/mess/include \
	-I$(EACC_ROOT)/blocks/include \
	-I$(EACC_ROOT)/common/include \
	-I$(EACC_ROOT)/3rdparty/include \
	-I$(EACC_ROOT)/cmapi/idl \
	-I$(EACC_ROOT)/cmapi/configfetch/include \
	-I$(EACC_ROOT)/cmapi/common

CXXFLAGS += -std=c++0x -I. $(INCLS)

CONFIGFETCH_AR := libcmapiconfig$(DBGSUFFIX).a
CONFIGFETCH_OFILES := CMAPIConfig.o

IWFCONFIGFETCH_AR := libiwfconfigfetch$(DBSUFFIX).a
IWFCONFIGFETCH_OFILES := IWFConfigFetch.o

TARGETS_AR := CONFIGFETCH IWFCONFIGFETCH

include $(EACC_ROOT)/Makefile.rules

