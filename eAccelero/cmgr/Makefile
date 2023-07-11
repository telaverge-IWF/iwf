include ../Makefile.inc
DB_CONN:=$(EACC_ROOT)/3rdparty/mysql-connector-c++-1.1.0

ifeq ($(DEBUG_BUILD),yes)
	DBGSUFFIX:=D
endif

CXXFLAGS+= -I$(EACC_ROOT)/3rdparty/include -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include -I$(DB_CONN)/driver/ -I$(DB_CONN) -I$(DB_CONN)/cppconn -I$(EACC_ROOT)/common/include -I$(EACC_ROOT)/cmapi/idl -I$(EACC_ROOT)/cmapi/common -I$(EACC_ROOT)/cmapi/components/include -I$(EACC_ROOT)/cmapi/dreconfig/include -I$(EACC_ROOT)/cmgr/include -I$(EACC_ROOT)/avamgr/hacomponent/include -I$(EACC_ROOT)/cmapi/alarms/include 

LIBS += -I$(EACC_ROOT)/3rdparty/lib -L$(EACC_ROOT)/cmapi/idl/lib -lHAComponent -lHAComponentidl -lcompoidl -L$(EACC_ROOT)/3rdparty/mysql/lib -L$(DB_CONN)/driver -lmess -lblocks -lmysqlcppconn -lmysqlclient_r -lprotobuf -L$(EACC_ROOT)/cmapi/idl/lib  -lcompoidl -ldreidl -lcmapiHA -lHAidl  -lcmapialarms -lAlarmsidl -lusrmgtidl -liwfidl -liwfcfgfetch -lsctp -lrt

INCL += -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include -I$(DB_CONN)/driver/ -I$(DB_CONN) -I$(DB_CONN)/cppconn -I$(EACC_ROOT)/common/include -I$(EACC_ROOT)/cmapi/common -I$(EACC_ROOT)/cmapi/components -I$(EACC_ROOT)/cmapi/components/include -I$(EACC_ROOT)/cmapi/idl -I$(EACC_ROOT)/cmgr/include

BINDIR := ./bin/$(DBGDIR)/

PBOBJS:=ConfigReader.o MysqlInterfacePB.o PeerTAndTimersTPB.o LocalHostConfigSingleRow.o DefaultRouteTRealmPB.o RealmRoutingTPB.o PeerTPB.o PeerTimersTPB.o CMAPICMgr.o PeerGroupMapTLbAlgorithmTPB.o PeerGroupTPB.o PeerGroupMapTPB.o LbAlgorithmTPB.o PeerDictionaryMapTPB.o DictionaryTPB.o DictionaryTPeerPB.o CMAPIErlbf.o RealmRoutingTAndDefaultRouteTPB.o CMgrHaDbInterface.o AvailabilityManagerConfigTPB.o CMAPIHa.o RealmTRealmRoutingTAndDefaultRouteTPB.o RealmTPB.o UserTPB.o UserTAndRoleTPB.o LoggingConfigTPB.o ApplicationGroupTAndLbAlgorithmTPB.o ApplicationGroupTPB.o AsfConfigTPB.o TracingFilterTPB.o TracingTPB.o 
cmgr_BIN := cmgr
cmgr_OFILES :=CMgrPeerDbInterface.o CMgrDbInterface.o ConfigManager.o  CMAPIDtf.o CMFDiaCCPriorityTPB.o LocalTransportTagTPB.o CMgrReqToTableMap.o CMgrLock.o IWFMapS6aVplmnIdSgsnMapTPB.o IWFMapS6aVplmnIdTPB.o IWFTranslatorRuleVplmnIdTPB.o IWFSigtranUalManagerTPB.o CMgrIwfUal.o CMgrIwfTimer.o CMAPIIwfUal.o CMgrIwfAssociationDbInterface.o IWFSigtranAssocAssocSetMappingTPB.o CMgrIwfErrors.o CMgrIwfCapRoDbInterface.o CMgrIwfMapS6aAndS6aMapDbInterface.o CMgrIwfTranslatorDbInterface.o CMAPIIwfTimers.o CMAPIIwfAssociation.o CMAPIIwfCMgr.o CMAPIIwfLocalHost.o CMAPIIwfRouting.o CMAPIIwfTranslator.o CMgrIwfLocalHostDbInterface.o IWFTimerTPB.o IWFS6aMapSgsnAddrMapTPB.o CapRoIdpSmsConfigTPB.o ExtBearerserviceToServiceIdMapTPB.o ExtTeleserviceToServiceIdMapTPB.o CapRoIdpConfigTPB.o IWFCapRoConfigTPB.o IWFS6aMapConfigTPB.o IWFMapS6aConfigTPB.o IWFTranslatorTPB.o IWFTranslatorTypeTPB.o IWFTranslatorRuleTPB.o IWFSigtranRemoteRouteTPB.o IWFSigtranAssocSetTPB.o IWFLocalConfigTPB.o IWFLocalSSNMappingTPB.o IWFSigtranAssociationTPB.o IWFSigtranDestinationTPB.o IWFSCTPEndpointTPB.o IWFSigtranSCTPProfileTPB.o IWFSigtranMultihomingTPB.o IWFSigtranAssocSetMappingTPB.o IWFProtocolFamilyTPB.o IWFLocalSSNTPB.o CMgrIwfRoutingDbInterface.o  CMgrIwfDbInterface.o  MonitorMysql.o CMgrAlarms.o PeerMultiHomingTPB.o MultiHomingTPB.o SCTPConfigTPB.o StackGeneralConfigTPB.o TLSConfigTPB.o TrustedCATPB.o CipherSuiteTPB.o CMAPIAsf.o CMAPITracing.o CMgrTracingDbInterface.o CMgrAsfDbInterface.o CMAPIStack.o CMgrStackDbInterface.o LocalTransportTPB.o LocalHostConfigTPB.o LocalHostTAndTransportTPB.o  CMgrErrors.o  CMgrMain.o CMgrRealmDbInterface.o CMgrLocalHostDbInterface.o CMgrDtfDbInterface.o CMAPIUserMgmt.o CMgrUserMgmtDbInterface.o CMAPILogging.o CMgrLoggingDbInterface.o StaticRouteTPB.o StaticRouteTAndPeerTPB.o IWFFeatureTPB.o CMgrIwfFeature.o CMAPIIwfFeatures.o IWFDccaGeneralTPB.o CMgrIwfDccaGeneralConfigDbInterface.o IWFDccaEndPointsTPB.o CMAPIIwfDccaConfig.o CMgrIwfDccaDestConfigDbInterface.o CMAPIIwfProtocolActions.o IWFProtocolActionTPB.o IWFCallScenarioMappingTPB.o IWFEventTypeMappingTPB.o IWFEventTypeDetailsTPB.o CMgrIwfProtocolActionDbInterface.o CMgrUtils.o CMFDiaAppIdPriorityTPB.o CMFTriggerActionMapTPB.o CMFLevelTPB.o CMFActionsTPB.o CMFTriggerTPB.o CongestionRulesTPB.o  TransformPluginTPB.o EmailContentTPB.o IdentityServerTPB.o EmailServerTPB.o RolePrevilegeMapTPB.o PrevilegeTPB.o UserDetailTPB.o RoleTPB.o CMAPIThf.o CMgrThfDbInterface.o ThfTPB.o ThfRealmTPB.o ThfVHostsTPB.o CMAPISdtf.o CMgrSdtfDbInterface.o SDTFRulesTPB.o FeatureStatusTPB.o CmfDiaPeerTemplateTPB.o CmfDiaRealmTemplateTPB.o CMAPICmf.o CMgrCmfDbInterface.o IWFS6aMapSgsnPrefixMapTPB.o $(PBOBJS)


TARGETS_BIN := cmgr

include ../Makefile.rules

