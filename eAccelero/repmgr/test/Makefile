include ../../Makefile.inc

CXXFLAGS += -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include -I$(EACC_ROOT)/cli/include -I$(EACC_ROOT)/repmgr/include -I${EACC_ROOT}/repmgr/test/include -I${EACC_ROOT}/utils/hash/include
LIBS +=  -L$(EACC_ROOT)/lib/debug -lReplicationClient -lmess  -lblocks -lprotobuf  -lcouchbase -lhash

BINDIR := ./bin/$(DBGDIR)/

#SampCliApp_BIN := SampCliApp
#SampCliApp_OFILES := SampCliApp.o

#SampDreApp_BIN := SampDREApp
#SampDreApp_OFILES := SampDREApp.o

#SampDre_BIN := SampDre
#SampDre_OFILES := SampDre.o

SampleReplClientApp_BIN := SampleReplClientApp
SampleReplClientApp_OFILES :=SampleReplClientApp.o Serialize.o

TARGETS_BIN := SampleReplClientApp

include ../../Makefile.rules

