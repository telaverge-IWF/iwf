#
# get the vars
#
include $(ITS_ROOT)/config.vars


CXXOBJS=test_receive_sctp.o

CXXSRCS=test_receive_sctp.cpp

ITS_LIBS=-lCCITT-VENDORD \
         -lMAP-COMMON++ -lMAP-V4++ \
         -lCCITT-TCAPD \
         -lCCITT-VENDORD \
         -lCCITT-SCCPD \
         -lCCITT-MTP3D \
         -lCORED \
         -lASN++D -lASND \
         -lCCITT-M3UAD \
         -lSCTPD \
         -lSUPPORTD -lCORED
 

LINK_FLAG = -L$(ITS_ROOT)/common/lib -L$(ITS_ROOT)/GSMMAP/lib \
            -L$(VENDOR_ROOT)/IntelliNet/lib -L$(ITS_ROOT)/TCAP/lib \
            -L$(ITS_ROOT)/SCCP/lib -L$(ITS_ROOT)/MTP3/lib


CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/common/include/asn-cpp \
          -I$(ITS_ROOT)/GSMMAP/include/itu \
          -I$(ITS_ROOT)/TCAP/include \
          -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include \
          -I$(ITS_ROOT)/MTP2/include \
          -DUSE_INTELLINET_STACK     \
          -DUSE_SOCKETS


all: receive$(DBGSUFFIX)

receive$(DBGSUFFIX): $(CXXOBJS)
	$(CXX) -g $(LDFLAGS) \
	$(LINK_FLAG) -o receive$(DBGSUFFIX) $(CXXOBJS) \
	$(ITS_LIBS) $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

clean:
	$(RM) $(CXXOBJS) receive$(DBGSUFFIX) *.err .depend

#
# get the rules
#
include $(ITS_ROOT)/config.rules
