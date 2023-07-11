####################################################################
# 
#  Makefile file for Polaris gateway using engine.
#                  README 
#
####################################################################
#
# ID : $Id     $
#
# LOG : $Log   $
#
####################################################################

include $(ITS_ROOT)/config.vars

LIB_OBJS := ClientInterface.o MulAppCallbacks.o MulAppMsgHandler.o \
            mab_cmn.o mab_dbc.o MulAppMtp3MsgHandler.o \
            MulAppTcapMsgHandler.o MulAppIsupMsgHandler.o

SRC_OBJS = MulAppMain.o

CXXFLAGS := $(CXXFLAGS) -I../include \
            -I$(ITS_ROOT)/common/include \
            -I$(ITS_ROOT)/common/include/asn-cpp \
            -I$(ITS_ROOT)/TCAP/include \
            -I$(ITS_ROOT)/SCCP/include \
            -I$(ITS_ROOT)/MTP3/include \
            -I$(ITS_ROOT)/MTP2/include \
            -I$(ITS_ROOT)/ISUP/include \
            -I$(VENDOR_ROOT)/IntelliNet/include \
            -I../include -DINCLUDE_CODEC -DTCAP_CODEC

ITS_LIBS := $(ITS_LIBS) \
            -L$(ITS_ROOT)/common/lib \
            -L$(VENDOR_ROOT)/IntelliNet/lib \
            -L../bin \
            -lENGINE$(DBGSUFFIX) \
            -lDSM-GCS$(DBGSUFFIX) \
            -lGCS-CLIENT$(DBGSUFFIX) \
            -lDRIVER++$(DBGSUFFIX) \
            -lDISPATCH++$(DBGSUFFIX) \
            -lVFrame$(DBGSUFFIX) \
            -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
            -lMulAppServer_$(PROTOCOL)$(DBGSUFFIX)

ifeq ($(CARD),nms)
ITS_LIBS := $(ITS_LIBS) \
            -L/opt/nms/lib \
            -L/opt/nmstx/lib \
            -lcta -lctal -lctacl -lcpi
endif

ifeq ($(P), yes)
CXXFLAGS := $(CXXFLAGS) -DP -I`purify -print-home-dir`
QFLAGS =-cache-dir=../bin/cache -max-threads=120 -chain-length=15 -show-directory=yes
 
PURIFY = purify $(QFLAGS)
ITS_LIBS:=$(ITS_LIBS) -L`purify -print-home-dir`
endif

all:../bin/MulAppServer_$(PROTOCOL)$(DBGSUFFIX) \
    ../bin/libMulAppServer_$(PROTOCOL)$(DBGSUFFIX).so

../bin/MulAppServer_$(PROTOCOL)$(DBGSUFFIX): $(SRC_OBJS) \
               ../bin/libMulAppServer_$(PROTOCOL)$(DBGSUFFIX).so
	$(PURIFY) $(CXX) $(CXXFLAGS) -o $@ $(SRC_OBJS) \
          $(ITS_LIBS) $(NMSLIBS) $(SYSLIBS) $(SOCKLIBS) $(THREADLIBS)

../bin/libMulAppServer_$(PROTOCOL)$(DBGSUFFIX).so: $(LIB_OBJS)
	$(PURIFY) $(CXXSHAREDAR) $(CXXSHAREDARFLAGS) $@ $(LIB_OBJS)

clean :
	$(RM) ../bin/libMulAppServer_$(PROTOCOL)$(DBGSUFFIX).so \
     ../bin/MulAppServer_$(PROTOCOL)$(DBGSUFFIX) $(SRC_OBJS) $(LIB_OBJS)

#
# the rules
#
include $(ITS_ROOT)/config.rules
