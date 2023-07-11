include ../Makefile.inc

CXXFLAGS += -I/home/sandbox/curl-7.33.0/include/ -I$(EACC_ROOT)/repmgr/include -I$(EACC_ROOT)/avamgr/include -I$(EACC_ROOT)/cli/include -I$(EACC_ROOT)/common/include -I$(EACC_ROOT)/avamgr/hacomponent/include -I$(EACC_ROOT)/cmapi/idl -I$(EACC_ROOT)/cmapi/common -I$(EACC_ROOT)/3rdparty/include -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include -DJSON_IS_AMALGAMATION  -I$(EACC_ROOT)/3rdparty/jsoncpp_0.6.0-rc2/json/ -I$(EACC_ROOT)/utils/hash/include
LIBS +=  -L$(EACC_ROOT)/cmapi/idl/lib -ljsoncpp -L$(EACC_ROOT)/lib/debug -lreplicationidl -lHAComponent -lHAComponentidl -lcompoidl -lmess -lblocks -lprotobuf -lhash
BINDIR := ./bin/$(DBGDIR)/

#SHM_AR:= libshm.a
#SHM_OFILES:= shm.o

#repmgr_BIN := repmgr
#repmgr_OFILES := ReplicationManager.o shm.o
REPLICATIONCLIENT_AR:= libReplicationClient.a
REPLICATIONCLIENT_OFILES:=CouchbaseConnector.o ReplicationClient.o  ReplicationConnectorThreadPool.o  ReplicationSyncConnectorPool.o

CBADMINCLIENT_AR:= libCouchbaseAdminClient.a
CBADMINCLIENT_OFILES:=CouchbaseMgmtClient.o

TARGETS_AR:= CBADMINCLIENT REPLICATIONCLIENT

#TARGETS_AR:= CBADMINCLIENT REPLICATIONCLIENT
#TARGETS_AR:= SHM CBADMINCLIENT

#TARGETS_BIN := repmgr
include ../Makefile.rules
