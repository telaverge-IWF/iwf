include ../Makefile.inc

CXXFLAGS += -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include -I$(EACC_ROOT)/common/include -I$(DRE_ROOT)/controller/include -I$(EACC_ROOT)/cmapi/idl/ -I$(EACC_ROOT)/cmapi/components/include -I$(EACC_ROOT)/cmapi/dreconfig/include -I$(EACC_ROOT)/cmapi/iwfconfig/include -I$(EACC_ROOT)/cmapi/common -I$(EACC_ROOT)/cli/include -I$(EACC_ROOT)/avamgr/hacomponent/include -I$(EACC_ROOT)/avamgr/include -I$(EACC_ROOT)/cmapi/configfetch/include

CFLAGS += -I$(EACC_ROOT)/common/include -I$(EACC_ROOT)/cli/include -I$(EACC_ROOT)/avamgr/include -lpthread -Wall -fPIC
LIBS += -lHAComponent -lHAComponentidl -lmess -lblocks -L$(EACC_ROOT)/lib/debug -lcmapicomp -L$(EACC_ROOT)/cmapi/idl/lib/ -ldreidl -lHAidl -lcmapiHA -lcmapiconfig -lcompoidl -lcfgfetch -liwfcmapi -liwfidl

BINDIR := ./bin/$(DBGDIR)/


USERAUTH_AR := libuserAuth.a
USERAUTH_OFILES := utils.o ConfigReader.o UserAuth.o  md5c.o

COMMON_MGMT_API_AR := libmgmtApi.a
COMMON_MGMT_API_OFILES := utils.o ConfigReader.o CommonMeSS.o MgmtInterface.o

TARGETS_AR := USERAUTH COMMON_MGMT_API

include ../Makefile.rules

