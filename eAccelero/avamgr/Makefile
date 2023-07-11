include ../Makefile.inc

CXXFLAGS += -USTANDALONE_TEST -I$(ITS_ROOT)/common/include -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include -Ihacomponent/include -I$(EACC_ROOT)/cmapi/idl -I$(EACC_ROOT)/cmapi/configfetch/include/ -I$(EACC_ROOT)/cmapi/common/ -I$(EACC_ROOT)/cmapi/components/include -I$(EACC_ROOT)/cmapi/alarms/include -DJSON_IS_AMALGAMATION  -I$(EACC_ROOT)/3rdparty/jsoncpp_0.6.0-rc2/json/ -I$(EACC_ROOT)/repmgr/include
LIBS +=  -L$(EACC_ROOT)/cmapi/idl/lib -lavamgridl -lHAComponentidl -lmess -lblocks -lprotobuf -lHAidl -lcmapialarms -lAlarmsidl -lcompoidl -L$(EACC_ROOT)/lib/debug -ljsoncpp -lCouchbaseAdminClient -lcurl  -lrt -lkpiidl

BINDIR := ./bin/$(DBGDIR)/

avamgr_BIN := avamgr
avamgr_OFILES := AvailabilityManager.o Pinger.o ConfigReader.o ManagementInterface.o AvailabilityManagerAlarms.o AvailabilityManagerConfig.o AvailabilityManagerComponentStatus.o AvailabilityManagerInterfaceMonitor.o AvailabilityManagerPeerMonitor.o  AvailabilityManagerSignalHandler.o AvailabilityManagerActiveInstance.o AvailabilityManagerStandbyInstance.o AvailabilityManagerUtils.o ClusterManager.o

TARGETS_BIN := avamgr

include ../Makefile.rules
