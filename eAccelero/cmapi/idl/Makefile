
include $(EACC_ROOT)/Makefile.inc

DBGDIR:=debug
LIBSDIR:= -L$(EACC_ROOT)/lib/$(DBGDIR)/ -L$(EACC_ROOT)/3rdparty/lib
LIBS:= $(LIBSDIR) -lblocks -lmess -lprotobuf -lprotoc
PARSERDIR:=$(EACC_ROOT)/parser
INCLS:= -Iinclude \
    -I$(EACC_ROOT)/mess/include \
    -I$(EACC_ROOT)/blocks/include \
	-I$(EACC_ROOT)/common/include \
	-I$(EACC_ROOT)/3rdparty/include \

CXXFLAGS+= -std=c++0x -I. $(INCLS)

#COMPOOBJS:= CmgrErlbf_caller.o  Compo.o  DreErlbf_caller.o Compo.pb.o
#DREOBJS:= CMgrMethods_caller.o  DiaMgtMethods_caller.o  dreconfig.o  dreconfig.pb.o
#CFGFETCHOBJS:= DreFetch_caller.o ErlbfFetch_caller.o

all: clean gencode lib/libcompoidl.a lib/libdreidl.a lib/libcfgfetch.a lib/libHAidl.a lib/libStatsidl.a lib/libAlarmsidl.a lib/libHAComponentidl.a lib/libavamgridl.a lib/libreplicationidl.a lib/libiwfidl.a lib/libiwfcfgfetch.a lib/libkpiidl.a lib/libusrmgtidl.a lib/libdrealarmsidl.a lib/libresourcenotify.a 
#all: clean gencode lib/libcompoidl.a lib/libdreidl.a lib/libcfgfetch.a lib/libHAidl.a lib/libStatsidl.a lib/libAlarmsidl.a lib/libHAComponentidl.a lib/libavamgridl.a lib/libreplicationidl.a lib/libusrmgtidl.a lib/libdrealarmsidl.a lib/libresourcenotify.a

gencode:
	@echo ">>>>>>>>Generating IDL Classes "
	#python $(PARSERDIR)/dq_idl_parser.py Common.idl HACommon.idl dreconfig.idl Compo.idl HA.idl PeerStats.idl Alarms.idl HAComponent.idl AvaMgr.idl InterfaceStat.idl diameterstack.idl StackStats.idl StaticRoutingTable.idl Replication.idl iwfconfig.idl KPI.idl
	python $(PARSERDIR)/dq_idl_parser.py Common.idl HACommon.idl dreconfig.idl Compo.idl HA.idl PeerStats.idl Alarms.idl HAComponent.idl AvaMgr.idl InterfaceStat.idl diameterstack.idl StackStats.idl StaticRoutingTable.idl Replication.idl iwfconfig.idl OverloadControl.idl UserManagement.idl KPI.idl DreAlarms.idl ResourceNotifier.idl
	@echo ">>>>>>> Protocol Compiler "
	protoc -I=. --cpp_out=. *.proto

lib/libdrealarmsidl.a: DreAlarms.o DreAlarms.pb.o DreAlarmsInfo_caller.o
	$(AR) $@ DreAlarms.o DreAlarms.pb.o DreAlarmsInfo_caller.o
DreAlarmsInfo_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DreAlarmsInfo_caller.cpp
DreAlarms.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DreAlarms.cpp
DreAlarms.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DreAlarms.pb.cc

lib/libresourcenotify.a:ResourceNotifier.o ResourceNotifier.pb.o Publisher_caller.o Subscriber_caller.o Common.pb.o
	$(AR) $@ ResourceNotifier.o ResourceNotifier.pb.o Publisher_caller.o Subscriber_caller.o Common.pb.o
ResourceNotifier.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c ResourceNotifier.cpp
ResourceNotifier.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c ResourceNotifier.pb.cc
Publisher_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c Publisher_caller.cpp
Subscriber_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c Subscriber_caller.cpp
Common.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c Common.pb.cc

lib/libkpiidl.a: KPI.o KPI.pb.o ResourceUsageStat_caller.o AvaMgrKPIInterface_caller.o DreKPIInterface_caller.o
	$(AR) $@ KPI.o KPI.pb.o ResourceUsageStat_caller.o AvaMgrKPIInterface_caller.o DreKPIInterface_caller.o
ResourceUsageStat_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c ResourceUsageStat_caller.cpp
AvaMgrKPIInterface_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c AvaMgrKPIInterface_caller.cpp
DreKPIInterface_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DreKPIInterface_caller.cpp
KPI.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c KPI.pb.cc
KPI.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c KPI.cpp

lib/libusrmgtidl.a: CMgrUserManagementMethods_caller.o UserManagement.pb.o UserManagement.o
	$(AR) $@ CMgrUserManagementMethods_caller.o UserManagement.pb.o UserManagement.o
CMgrUserManagementMethods_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c CMgrUserManagementMethods_caller.cpp
UserManagement.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c  UserManagement.pb.cc
UserManagement.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c  UserManagement.cpp

lib/libreplicationidl.a: RepMgrReplicationInterface_caller.o ApplicationReplicationInterface_caller.o RepMgrInterface_caller.o  Replication.pb.o Replication.o
	$(AR) $@ RepMgrReplicationInterface_caller.o ApplicationReplicationInterface_caller.o RepMgrInterface_caller.o  Replication.pb.o Replication.o
RepMgrReplicationInterface_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c RepMgrReplicationInterface_caller.cpp
ApplicationReplicationInterface_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c ApplicationReplicationInterface_caller.cpp
RepMgrInterface_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c RepMgrInterface_caller.cpp
Replication.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c	Replication.pb.cc
Replication.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c	Replication.cpp


lib/libHAComponentidl.a: AvaMgrProcessStatusInterface_caller.o HAComponent.pb.o HAComponent.o HACommon.pb.o AvaMgrComponentStatusInterface_caller.o
	$(AR) $@ AvaMgrProcessStatusInterface_caller.o HAComponent.pb.o HAComponent.o HACommon.pb.o AvaMgrComponentStatusInterface_caller.o
AvaMgrProcessStatusInterface_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c AvaMgrProcessStatusInterface_caller.cpp
HAComponent.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c HAComponent.pb.cc
HAComponent.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c HAComponent.cpp
HACommon.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c HACommon.pb.cc
AvaMgrComponentStatusInterface_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c AvaMgrComponentStatusInterface_caller.cpp

lib/libavamgridl.a: AvaMgrPeerStatusInterface_caller.o AvaMgr.pb.o AvaMgr.o HACommon.pb.o
	$(AR) $@ AvaMgrPeerStatusInterface_caller.o AvaMgr.pb.o AvaMgr.o HACommon.pb.o
AvaMgrPeerStatusInterface_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c AvaMgrPeerStatusInterface_caller.cpp
AvaMgr.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c AvaMgr.pb.cc
AvaMgr.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c AvaMgr.cpp
HACommon.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c HACommon.pb.cc

lib/libcompoidl.a: CmgrComponents_caller.o  ErlbfStats_caller.o Compo.o  DreErlbf_caller.o DreDTF_caller.o Compo.pb.o Common.pb.o CompConfigResults_caller.o LoggingConf_caller.o DreASF_caller.o
	$(AR) $@ CmgrComponents_caller.o  ErlbfStats_caller.o Compo.o  DreErlbf_caller.o DreDTF_caller.o Compo.pb.o Common.pb.o CompConfigResults_caller.o LoggingConf_caller.o DreASF_caller.o
CmgrComponents_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c CmgrComponents_caller.cpp
ErlbfStats_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c ErlbfStats_caller.cpp
CompConfigResults_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c CompConfigResults_caller.cpp
Compo.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c Compo.cpp
DreErlbf_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DreErlbf_caller.cpp
Compo.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c Compo.pb.cc
DreDTF_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DreDTF_caller.cpp
Common.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c Common.pb.cc
LoggingConf_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c LoggingConf_caller.cpp
DreASF_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DreASF_caller.cpp


lib/libdreidl.a: CMgrMethods_caller.o  DiaMgtMethods_caller.o  dreconfig.o  dreconfig.pb.o Common.pb.o DREConfigResults_caller.o TraceConfigFetch_caller.o diameterstack.pb.o StaticRoutingTableConfigFetch_caller.o DREStaticRoutingConfigResults_caller.o DreStaticRoutingConfigFetch_caller.o DiaMgtForStaticRoutingMethods_caller.o CMgrStaticRoutingTableMethods_caller.o StaticRoutingTable.o StaticRoutingTable.pb.o OverloadControl.o OverloadControl.pb.o CMgrTemplateMethods_caller.o CMFConfigFetch_caller.o CMgrCMFConfig_caller.o DiaMgtTemplateMethods_caller.o DreTemplateFetch_caller.o DREConfigTemplateResults_caller.o DiaMgmtCMFConfig_caller.o DRECMfConfigResults_caller.o CMFStats_caller.o
	$(AR) $@ CMgrMethods_caller.o  DiaMgtMethods_caller.o  dreconfig.o  dreconfig.pb.o Common.pb.o DREConfigResults_caller.o TraceConfigFetch_caller.o diameterstack.pb.o StaticRoutingTableConfigFetch_caller.o DREStaticRoutingConfigResults_caller.o DreStaticRoutingConfigFetch_caller.o DiaMgtForStaticRoutingMethods_caller.o CMgrStaticRoutingTableMethods_caller.o StaticRoutingTable.o StaticRoutingTable.pb.o OverloadControl.o OverloadControl.pb.o CMgrTemplateMethods_caller.o CMFConfigFetch_caller.o CMgrCMFConfig_caller.o DiaMgtTemplateMethods_caller.o DreTemplateFetch_caller.o DREConfigTemplateResults_caller.o DiaMgmtCMFConfig_caller.o DRECMfConfigResults_caller.o CMFStats_caller.o
CMFStats_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c CMFStats_caller.cpp
CMgrMethods_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c CMgrMethods_caller.cpp
DiaMgtMethods_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DiaMgtMethods_caller.cpp
DREConfigResults_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DREConfigResults_caller.cpp
TraceConfigFetch_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c TraceConfigFetch_caller.cpp
dreconfig.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c dreconfig.cpp
dreconfig.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c dreconfig.pb.cc
Common.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c Common.pb.cc
diameterstack.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c diameterstack.pb.cc
StaticRoutingTable.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c StaticRoutingTable.cpp
StaticRoutingTable.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c StaticRoutingTable.pb.cc
StaticRoutingTableConfigFetch_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c StaticRoutingTableConfigFetch_caller.cpp
DREStaticRoutingConfigResults_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DREStaticRoutingConfigResults_caller.cpp
DreStaticRoutingConfigFetch_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DreStaticRoutingConfigFetch_caller.cpp
DiaMgtForStaticRoutingMethods_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DiaMgtForStaticRoutingMethods_caller.cpp
CMgrStaticRoutingTableMethods_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c CMgrStaticRoutingTableMethods_caller.cpp
OverloadControl.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c OverloadControl.cpp
OverloadControl.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c OverloadControl.pb.cc
DiaMgtTemplateMethods_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DiaMgtTemplateMethods_caller.cpp
DreTemplateFetch_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DreTemplateFetch_caller.cpp
CMgrTemplateMethods_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c CMgrTemplateMethods_caller.cpp
CMFConfigFetch_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c CMFConfigFetch_caller.cpp
CMgrCMFConfig_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c CMgrCMFConfig_caller.cpp
DREConfigTemplateResults.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DREConfigTemplateResults.cpp
DREConfigTemplateResults_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DREConfigTemplateResults_caller.cpp
DiaMgmtCMFConfig_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DiaMgmtCMFConfig_caller.cpp
DRECMfConfigResults_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DRECMfConfigResults_caller.cpp

lib/libcfgfetch.a: DreFetch_caller.o FetchConfiguration_caller.o
	$(AR) $@ DreFetch_caller.o FetchConfiguration_caller.o
DreFetch_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DreFetch_caller.cpp
FetchConfiguration_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c FetchConfiguration_caller.cpp

lib/libiwfidl.a: CMgrIwfMethods_caller.o iwfconfig.o iwfconfig.pb.o IwfSigtranMethods_caller.o IwfConfigResults_caller.o Common.pb.o
	$(AR) $@ CMgrIwfMethods_caller.o iwfconfig.o iwfconfig.pb.o IwfSigtranMethods_caller.o IwfConfigResults_caller.o Common.pb.o
CMgrIwfMethods_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c CMgrIwfMethods_caller.cpp
iwfconfig.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c iwfconfig.cpp
iwfconfig.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c iwfconfig.pb.cc
IwfSigtranMethods_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c IwfSigtranMethods_caller.cpp
IwfConfigResults_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c IwfConfigResults_caller.cpp
Common.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c Common.pb.cc

lib/libiwfcfgfetch.a: IwfFetch_caller.o
	$(AR) $@ IwfFetch_caller.o
IwfFetch_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c IwfFetch_caller.cpp

lib/libHAidl.a: HA.pb.o HA.o AvaMgrHAInterface_caller.o RepMgrHAInterface_caller.o DreHAInterface_caller.o CMgrHAInterface_caller.o  Common.pb.o
	$(AR) $@ HA.pb.o HA.o AvaMgrHAInterface_caller.o RepMgrHAInterface_caller.o DreHAInterface_caller.o CMgrHAInterface_caller.o Common.pb.o
HA.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c HA.pb.cc
HA.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c HA.cpp
AvaMgrHAInterface_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c AvaMgrHAInterface_caller.cpp
RepMgrHAInterface_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c RepMgrHAInterface_caller.cpp
DreHAInterface_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c DreHAInterface_caller.cpp
CMgrHAInterface_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c CMgrHAInterface_caller.cpp
Common.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c Common.pb.cc

lib/libStatsidl.a: PeerStats_caller.o PeerStats.o PeerStats.pb.o InterfaceStat_caller.o InterfaceStat.o InterfaceStat.pb.o Common.pb.o StackStats_caller.o StackStats.o StackStats.pb.o Common.pb.o
	$(AR) $@ PeerStats_caller.o PeerStats.o PeerStats.pb.o InterfaceStat_caller.o InterfaceStat.o InterfaceStat.pb.o Common.pb.o  StackStats_caller.o StackStats.o StackStats.pb.o Common.pb.o
PeerStats_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c PeerStats_caller.cpp
PeerStats.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c PeerStats.cpp
PeerStats.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c PeerStats.pb.cc
InterfaceStat_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c InterfaceStat_caller.cpp
InterfaceStat.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c InterfaceStat.cpp
InterfaceStat.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c InterfaceStat.pb.cc
StackStats_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c StackStats_caller.cpp
StackStats.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c StackStats.cpp
StackStats.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c StackStats.pb.cc
Common.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c Common.pb.cc

lib/libAlarmsidl.a: Alarms_caller.o Alarms.o Alarms.pb.o
	$(AR) $@ Alarms_caller.o Alarms.o Alarms.pb.o
Alarms_caller.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c Alarms_caller.cpp
Alarms.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c Alarms.cpp
Alarms.pb.o:
	$(CXX) $(CXXFLAGS) -rdynamic $(LIBS) -c Alarms.pb.cc

clean:
	rm -rf *.h *.cc *.cpp *.a
	rm -rf lib/*.a *.o
	rm -rf *.proto
	rm -rf *.h *.cc *.cpp
	rm -rf interface_index

