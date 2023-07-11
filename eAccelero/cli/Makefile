include ../Makefile.inc

CXXFLAGS += -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include -I$(EACC_ROOT)/common/include -I$(EACC_ROOT)/cmapi/idl/  -I$(EACC_ROOT)/avamgr/include -g -O2 -fno-strict-aliasing -I$(EACC_ROOT)/cli/include -I$(EACC_ROOT)/cmapi/idl/ -I$(EACC_ROOT)/cmapi/components/include -I$(EACC_ROOT)/cmapi/iwfconfig/include -I$(EACC_ROOT)/cmapi/dreconfig/include -I$(EACC_ROOT)/cmapi/common -I$(EACC_ROOT)/avamgr/hacomponent/include -I$(EACC_ROOT)/cmapi/configfetch/include

CFLAGS += -I$(EACC_ROOT)/3rdparty/include -I$(EACC_ROOT)/blocks/include  -I$(EACC_ROOT)/cmapi/idl/ -I$(EACC_ROOT)/avamgr/hacomponent/include -I$(EACC_ROOT)/mess/include -I$(EACC_ROOT)/common/include -I$(EACC_ROOT)/avamgr/include  -lpthread -Wall -Wformat-security -Wno-format-zero-length -I$(EACC_ROOT)/cli/include 
 
LIBS += -L$(EACC_ROOT)/cmapi/idl/lib -lmgmtApi -lHAComponent -lHAComponentidl -lcrypt -lmess -lblocks -luserAuth -lprotobuf -lcmapiHA -lHAidl -lcmapicomp  -lcmapiconfig -lcompoidl -lcfgfetch -ldrecmapi -liwfcmapi -liwfidl -ldreidl -lStatsidl -lusrmgtcmapi -lusrmgtidl -lkpiidl -lrt
BINDIR := ./bin/$(DBGDIR)/


cli_BIN := cli
cli_OFILES := CliMain.o LibCli.o CliRegister.o CliParser.o CliCallback.o MessInterface.o dre_cli.o repmgr_cli.o Display.o AvailabilityManager_cli.o iwf_cli.o iwf_CliCallback.o


TARGETS_BIN := cli 

include ../Makefile.rules

