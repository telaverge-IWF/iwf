####################################################################
# 
#  Makefile file for TCAP_Test program using engine.
#  define IMAL_SUPPORT to send config connect message
# 
#                  README 
#
# Define REALTIME_CLASS if doing performance and want to set
# scheduling priority (testMain.cpp)
# Define INTELLINET_MTP3 or NMS_MTP3 when using either
# Define SS7=YES when configuring with SS7 Border Transport
# Define Q=YES if want to QUANTIFY
# Define P=YES if want to PURIFY
#
####################################################################
# ID: $Id: Makefile,v 1.1.2.1 2014/07/29 09:49:58 jkchaitanya Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 1.1.2.1  2014/07/29 09:49:58  jkchaitanya
# LOG: added a new directory cap_sample useful for load testing
# LOG:
# LOG: Revision 1.1.1.1.2.3.2.1  2013/10/04 13:43:07  millayaraja
# LOG: changes for RHEL machine dependent compilation flags and dependencies in IWF code
# LOG:
# LOG: Revision 1.1.1.1.2.3  2013/03/15 21:22:45  brajappa
# LOG: SCCP CCITT support for IWF
# LOG:
# LOG: Revision 1.1.1.1.2.2  2013/03/08 04:22:39  jsarvesh
# LOG: implementation for map message through json
# LOG:
# LOG: Revision 1.1.1.1.2.1  2013/02/05 08:36:17  brajappa
# LOG: Test checkin
# LOG:
# LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
# LOG: Initial import
# LOG:
# LOG: Revision 1.1.2.1  2012/12/28 13:45:14  lakshman
# LOG: checkin first version of MAP test along with CAP.
# LOG:
# LOG: Revision 1.2.2.1  2012/12/18 16:11:58  brajappa
# LOG: Initial IWF branch creation and linux compilation changes
# LOG:
# LOG: Revision 1.2  2011/04/19 09:19:09  nvijikumar
# LOG: UT updates
# LOG:
# LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
# LOG: Initial Draft for SSG
# LOG:
# LOG: 
####################################################################

include $(ITS_ROOT)/config.vars

PROTOCOL=CCITT
#SCCP_PROT=ANSI

DEFINES:= $(DEFINES) -DINTELLINET_MTP3 
ifeq ($(USE_CAP_V2),yes)
DEFINES:= $(DEFINES) -DUSE_CAP_V2
PROTLIBS:= $(PROTLIBS) $(ITS_ROOT)/CAMEL/lib/libCAP-V2++$(DBGSUFFIX).a
else
DEFINES:= $(DEFINES) -DUSE_CAP_V3
PROTLIBS:= $(PROTLIBS) $(ITS_ROOT)/CAMEL/lib/libCAP-V3++$(DBGSUFFIX).a
endif
ifeq ($(GCC_LIB_VERSION_LESS_THAN_4_3), yes)
DEFINES:= $(DEFINES) -DGCC_LESS_THAN_4_3
endif


#GSMLIBS:= -L$(ITS_ROOT)/GSMMAP/lib 

CPP_OBJS=appMain.o app_dbc.o

CB_OBJS=app_callbacks.o app_const.o app_common.o app_trace.o app_stats.o cap_prot_utils.o jsoncpp.o 

ifeq ($(USE_NMS), yes)
NMS_LIB=-L/opt/nms/lib \
	-L/opt/nmstx/lib -lcta \
	-lctal \
	-lctacl \
	-lcpi \
	-lss7cpi \
	-lmtp2mapi \
	-lss7mapi
endif

ifeq  ($(PROTOCOL), CCITT)
APP_NAME=CCITT
DEFINES:= $(DEFINES) -DDEF_CCITT
CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/CAMEL/include/itu 
#PROTLIBS := $(PROTLIBS) -L$(ITS_ROOT)/GSMMAP/lib -lMAP-V6++$(DBGSUFFIX)
CB_SUPPORT_OBJS= app_itu_msgs.o
VENDORS_LIB := -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) 
endif

vfLib=VFrame

ifeq  ($(PROTOCOL), CCITT)
ifeq ($(SCCP_PROT), ANSI)
APP_NAME=COA
DEFINES:= $(DEFINES) -DSPLIT_STACK -DUSE_ANSI_SCCP
CFLAGS := $(CFLAGS) $(DEFINES)
VENDORS_LIB := -l$(PROTOCOL)-$(SCCP_PROT)-VENDOR$(DBGSUFFIX) \
               -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
		-l$(SCCP_PROT)-VENDOR$(DBGSUFFIX) \
	$(ITS_ROOT)/MTP3/lib/libCCITT-MTP3$(DBGSUFFIX).a
endif
endif

#-I$(ITS_ROOT)/GSMMAP/include/itu 
CFLAGS := -I../include $(CFLAGS) \
          -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/common/include/asn-cpp \
          -I$(ITS_ROOT)/TCAP/include \
          -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/ISUP/include \
          -I$(ITS_ROOT)/MTP3/include \
          -I$(ITS_ROOT)/SLTM/include \
          -I$(ITS_ROOT)/SNMM/include \
          -I$(ITS_ROOT)/MTP2/include \
          -I$(VENDOR_ROOT)/IntelliNet/include \
          -I$(ITS_ROOT)/include/ansi \
          -I$(ITS_ROOT)/include/itu \
          -I$(ITS_ROOT)/include/asn-cpp \
          -I$(ITS_ROOT)/include \
          -D$(PROTOCOL) -DUSE_INTELLINET_STACK \
          -DFILE_APP_TRACE \
          -DAPP_STDOUT_TRACE \
          -I$(ITS_ROOT)/include 


CXXFLAGS:= $(CXXFLAGS)

ifeq  ($(PLATFORM), linux) 
ifeq ($(GCC_LIB_VERSION_LESS_THAN_4_3), yes)                                         
CXXFLAGS:= $(CXXFLAGS) -z muldefs                                                    
else                                                                                 
CXXFLAGS:= $(CXXFLAGS) -z muldefs -std=gnu++0x 
endif
endif

LDFLAGS := -L. $(LDFLAGS) 

ITS_LIBS := -L$(ITS_ROOT)/common/lib -L../lib \
            -L$(VENDOR_ROOT)/IntelliNet/lib \
            -L$(ITS_ROOT)/JSTD/lib \
            -l$(vfLib)$(DBGSUFFIX) -lENGINE$(DBGSUFFIX) -lDRIVER$(DBGSUFFIX) \
             -lDISPATCH++$(DBGSUFFIX) -lDRIVER++$(DBGSUFFIX) \
            -lDSM-STUB$(DBGSUFFIX) \
            -lASN++$(DBGSUFFIX) \
            -lrt $(VENDORS_LIB) $(NMS_LIB) \
            -l$(APP_NAME)-TransCB$(DBGSUFFIX)



CB_LIBS = -l$(APP_NAME)-TransCB$(DBGSUFFIX)

SYSLIBS := -lrt $(SYSLIBS) -lsctp

ifeq ($(Q), yes)
DEFINES:= $(DEFINES) -DQ
CXXFLAGS:=$(CXXFLAGS) -I`quantify -print-home-dir`
QFLAGS = -cache-dir=./cache -max-threads=120 -record-system-calls=no
QUANTIFY = quantify $(QFLAGS)
LIBS:=$(LIBS) -L`quantify -print-home-dir`
endif

ifeq ($(P), yes)
DEFINES:= $(DEFINES) -DP
CXXFLAGS:=$(CXXFLAGS) -I`purify -print-home-dir`
QFLAGS = -cache-dir=./cache -max-threads=120 -chain-length=15 -show-directory=yes
QUANTIFY = purify $(QFLAGS)
LIBS:=$(LIBS) -L`purify -print-home-dir`
endif

ifeq ($(SS7), yes)
ITS_LIBS := $(ITS_LIBS) -L$(ITS_ROOT)/nms/lib \
            -L$(VENDOR_ROOT) \
        -l$(PROTOCOL)-NMSVENDORD
endif

all : ../lib/lib$(APP_NAME)-TransCB$(DBGSUFFIX).so ../bin/sampleApp$(APP_NAME)$(DBGSUFFIX)

#$(GSMLIBS)
../bin/sampleApp$(APP_NAME)$(DBGSUFFIX) : $(CPP_OBJS) 
	$(QUANTIFY) $(CXX) $(CXXFLAGS) $(LD_FLAGS) -o $@ $(CPP_OBJS) \
          $(ITS_LIBS) $(SYSLIBS) $(SOCKLIBS) $(THREADLIBS) 

../lib/lib$(APP_NAME)-TransCB$(DBGSUFFIX).so : $(CB_OBJS) $(CB_SUPPORT_OBJS)
	$(CXX) -z muldefs $(CXXFLAGS) $(CXXSHAREDARFLAGS) $@ $(CB_OBJS) $(CB_SUPPORT_OBJS) $(PROTLIBS) $(NOWHOLEARCHIVE)

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $<

clean :
	$(RM) $(CPP_OBJS) $(CB_SUPPORT_OBJS) $(CB_OBJS) \
	../bin/sampleApp$(APP_NAME)$(DBGSUFFIX) ../lib/lib$(APP_NAME)-TransCB$(DBGSUFFIX).so


