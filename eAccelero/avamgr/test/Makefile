include ../../Makefile.inc

ifeq ($(DEBUG),NO)
LIBS_MESS:=
        $(EACC_ROOT)/lib/release/libmess.a \
      $(EACC_ROOT)/lib/release/librule.a \
      $(EACC_ROOT)/lib/release/libblocks.a \
      $(EACC_ROOT)/lib/release/libmgmtApi.a \
      $(EACC_ROOT)/lib/release/libuserAuth.a \
      $(EACC_ROOT)/lib/release/libjson.a
else
LIBS_MESS:= $(EACC_ROOT)/lib/debug/libmess.a \
      $(EACC_ROOT)/lib/debug/librule.a \
      $(EACC_ROOT)/lib/debug/libblocks.a \
      $(EACC_ROOT)/lib/debug/libmgmtApi.a \
      $(EACC_ROOT)/lib/debug/libuserAuth.a \
      $(EACC_ROOT)/lib/debug/libjsoncpp.a
endif

CXXFLAGS += -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include -I$(EACC_ROOT)/avamgr/hacomponent/include -I$(EACC_ROOT)/cmapi/idl
LIBS += -L$(EACC_ROOT)/lib/debug \
	-L$(EACC_ROOT)/lib/release \
	-L$(EACC_ROOT)/3rdparty/lib \
	-L$(EACC_ROOT)/cmapi/idl/lib \
	-lprotobuf -lHAComponent -lHAComponentidl \
	$(LIBS_MESS)

BINDIR := ./bin/$(DBGDIR)/

repmgr_dummy_BIN := repmgr_dummy
repmgr_dummy_OFILES := ReplicationManager_Dummy.o

cliproc_dummy_BIN := cliproc_dummy
cliproc_dummy_OFILES := CliProc_Dummy.o

cnfmgr_dummy_BIN := cnfmgr_dummy
cnfmgr_dummy_OFILES := CnfMgr_Dummy.o

dreapp_dummy_BIN := dreapp_dummy
dreapp_dummy_OFILES := DreApp_Dummy.o

TARGETS_BIN := repmgr_dummy cliproc_dummy cnfmgr_dummy dreapp_dummy

include ../../Makefile.rules

