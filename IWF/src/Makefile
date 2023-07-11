############################################################################
#                                                                          #
#     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    #
#             Manufactured in the United States of America.                #
#       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       #
#                                                                          #
#   This product and related documentation is protected by copyright and   #
#   distributed under licenses restricting its use, copying, distribution  #
#   and decompilation.  No part of this product or related documentation   #
#   may be reproduced in any form by any means without prior written       #
#   authorization of IntelliNet Technologies and its licensors, if any.    #
#                                                                          #
#   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      #
#   government is subject to restrictions as set forth in subparagraph     #
#   (c)(1)(ii) of the Rights in Technical Data and Computer Software       #
#   clause at DFARS 252.227-7013 and FAR 52.227-19.                        #
#                                                                          #
############################################################################
#                                                                          #
# CONTRACT: INTERNAL                                                       #
#                                                                           #
# ###########################################################################
# 
# ID: $Id: Makefile,v 1.1.1.1.2.8.2.2.2.2.2.1.4.3.6.2.2.5 2023/05/05 09:34:13 jkchaitanya Exp $
# LOG: $Log: Makefile,v $
# LOG: Revision 1.1.1.1.2.8.2.2.2.2.2.1.4.3.6.2.2.5  2023/05/05 09:34:13  jkchaitanya
# LOG: Added multithread support
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.2.2.2.2.1.4.3.6.2.2.4  2015/03/20 09:54:09  jkchaitanya
# LOG: changes for bug fixes and Couchbase issues in HA
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.2.2.2.2.1.4.3.6.2.2.3  2015/02/17 07:19:01  jkchaitanya
# LOG: changes merged from B-IWF-0400-00 for HA changes
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.2.2.2.2.1.4.3.6.2.2.2  2014/12/04 11:59:16  pramana
# LOG: Added subscriber context replication support
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.2.2.2.2.1.4.3.6.2.2.1  2014/11/20 11:54:17  pramana
# LOG: *** empty log message ***
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.2.2.2.2.1.4.3.6.2  2014/10/27 08:30:34  millayaraja
# LOG: changes for HA HotStandBy and selection criteria enhancements
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.2.2.2.2.1.4.3.6.1  2014/09/19 07:18:53  jkchaitanya
# LOG: changes for translator specific license validation and alarm implementation in IWF application
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.2.2.2.2.1.4.3  2014/05/06 13:11:02  jkchaitanya
# LOG: changes for ccfh feature
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.2.2.2.2.1.4.2  2014/03/24 06:52:19  millayaraja
# LOG: IWF integrated code for CDR and ActivityTest
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.2.2.2.2.1.4.1  2014/03/07 13:38:16  jsarvesh
# LOG: Implmentation for Voice CallFlows
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.2.2.2.2.1  2014/02/12 10:58:49  jkchaitanya
# LOG: changes for TSL
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.2.2.2  2013/12/03 09:47:00  millayaraja
# LOG: initial code checkin for IWF productization
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.2.2.1  2013/11/08 06:43:43  jsarvesh
# LOG: Commiting the changes for Configfetch and UAL Library
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.2  2013/10/04 13:43:07  millayaraja
# LOG: changes for RHEL machine dependent compilation flags and dependencies in IWF code
# LOG:
# LOG: Revision 1.1.1.1.2.8.2.1  2013/07/15 05:41:05  jsarvesh
# LOG: IWF-Phase-III Code CAP-Ro Implementation
# LOG:
# LOG: Revision 1.1.1.1.2.8  2013/05/22 15:21:21  jsarvesh
# LOG: IWF Phase-II Changes
# LOG:
# LOG: Revision 1.1.1.1.2.7  2013/03/15 21:22:45  brajappa
# LOG: SCCP CCITT support for IWF
# LOG:
# LOG: Revision 1.1.1.1.2.6  2013/02/04 06:02:07  brajappa
# LOG: Loading order change for Makefile
# LOG:
# LOG: Revision 1.1.1.1.2.5  2013/01/17 21:00:15  brajappa
# LOG: Using -std=gnu++0x instead of -std=c++0x, which defines 'linux' macro
# LOG:
# LOG: Revision 1.1.1.1.2.4  2013/01/17 20:52:40  brajappa
# LOG: Added translation for Tracing and IDR
# LOG:
# LOG: Revision 1.1.1.1.2.3  2013/01/15 16:00:42  arnabd
# LOG: IWF State Machine Changes & Enhancements
# LOG:
# LOG: Revision 1.1.1.1.2.2  2013/01/15 15:50:15  brajappa
# LOG: Added s13 interface to Makefile
# LOG:
# LOG: Revision 1.1.1.1.2.1  2013/01/11 22:22:58  brajappa
# LOG: IWF config reading using json and Abstract base Translator addition
# LOG:
# LOG: Revision 1.1.1.1  2013/01/09 16:41:36  brajappa
# LOG: Initial import
# LOG:
# LOG: Revision 1.3.2.4  2013/01/02 22:51:22  brajappa
# LOG: Initial checkin for S6a to MAP protocol converter
# LOG:
# LOG: Revision 1.3.2.3  2013/01/01 20:37:52  arnabd
# LOG: IWF State Machine first check-in
# LOG:
# LOG: Revision 1.3.2.2  2012/12/22 18:07:23  lakshman
# LOG: update transport framework changes and have few stubs ready for later
# LOG: additions.
# LOG:
# LOG: Revision 1.3.2.1  2012/12/18 16:11:58  brajappa
# LOG: Initial IWF branch creation and linux compilation changes
# LOG:
# LOG: Revision 1.3  2011/04/19 09:18:38  nvijikumar
# LOG: UT updates
# LOG:
# LOG: Revision 1.2  2011/04/15 11:34:07  nvijikumar
# LOG: UT Updates
# LOG:
# LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
# LOG: Initial Draft for SSG
# LOG:
# LOG: 
#
#
# ############################################################################
#
#
# Include the standard definitions
#
PROTOCOL=CCITT
#SCCP_PROT=ANSI
USE_CAP_V1=yes
USE_CAP_V2=yes
USE_CAP_V3=yes
include $(ITS_ROOT)/config.vars

ifeq  ($(PROTOCOL), CCITT)
ifeq ($(SCCP_PROT), ANSI)
DEFINES:= $(DEFINES) -DSPLIT_STACK -DUSE_ANSI_SCCP
VENDORS_LIB := -l$(PROTOCOL)-$(SCCP_PROT)-VENDOR$(DBGSUFFIX) \
               -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
			   -l$(SCCP_PROT)-VENDOR$(DBGSUFFIX)

VFRAMR_LIB:= -lCOAVFrame$(DBGSUFFIX) $(ITS_ROOT)/MTP3/lib/libCCITT-MTP3$(DBGSUFFIX).a

# Ccitt Over Ansi
APP_SUFFIX:= COA
endif

ifeq ($(SCCP_PROT), CCITT)
DEFINES:= $(DEFINES) -DUSE_CCITT_SCCP
VENDORS_LIB := -l$(PROTOCOL)-VENDOR$(DBGSUFFIX)

VFRAMR_LIB:= -lVFrame$(DBGSUFFIX) $(ITS_ROOT)/MTP3/lib/libCCITT-MTP3$(DBGSUFFIX).a
APP_SUFFIX:= CCITT
endif

endif

ifeq ($(GCC_LIB_VERSION_LESS_THAN_4_3), yes)
DEFINES:= $(DEFINES) -DGCC_LESS_THAN_4_3
endif

ifeq ($(USE_CAP_V1),yes)
DEFINES:= $(DEFINES) -DUSE_CAP_V1
PROTLIBS:= $(PROTLIBS) $(ITS_ROOT)/CAMEL/lib/libCAP-V1++$(DBGSUFFIX).a 
endif
ifeq ($(USE_CAP_V2),yes)
DEFINES:= $(DEFINES) -DUSE_CAP_V2
PROTLIBS:= $(PROTLIBS) $(ITS_ROOT)/CAMEL/lib/libCAP-V2++$(DBGSUFFIX).a 
endif
ifeq ($(USE_CAP_V3),yes)
DEFINES:= $(DEFINES) -DUSE_CAP_V3
PROTLIBS:= $(PROTLIBS) $(ITS_ROOT)/CAMEL/lib/libCAP-V3++$(DBGSUFFIX).a 
endif

#ifeq ($(USE_INAP_CS2),yes)
#DEFINES:= $(DEFINES) -DUSE_INAP_CS2
#PROTLIBS:= $(PROTLIBS) $(ITS_ROOT)/INAP/lib/libINAP-CS2++$(DBGSUFFIX).a
#else
#DEFINES:= $(DEFINES) -DUSE_INAP_CS1
#PROTLIBS:= $(PROTLIBS) $(ITS_ROOT)/INAP/lib/libINAP-CS1++$(DBGSUFFIX).a
#endif
PROTLIBS:= $(PROTLIBS) -L$(ITS_ROOT)/GSMMAP/lib -lMAP-COMMON++$(DBGSUFFIX) -lMAP-V13++$(DBGSUFFIX)

DIA_INCLS:=$(INCLS) $(ITS_INCLS) \
        -I../include \
        -I../ahocorasick \
        -I$(IMS_ROOT)/api/c++/include/diameter/dcca \
        -I$(IMS_ROOT)/api/c++/include \
        -I$(IMS_ROOT)/common/include \
        -I$(IMS_ROOT)/dframe/include \
        -I$(IMS_ROOT)/val/c++/include \
        -I$(IMS_ROOT)/vendors/IntelliNet/dcca/include \
        -I$(IMS_ROOT)/vendors/IntelliNet/include \
		-I$(IMS_ROOT)/dtf/include 

DIA_LIB_PATH:=-L$(IMS_ROOT)/common/lib \
        -L$(IMS_ROOT)/dframe/lib \
		-L$(IMS_ROOT)/api/c++/lib \
        -L$(IMS_ROOT)/val/c++/lib \
        -L$(IMS_ROOT)/vendors/IntelliNet/dcca/lib \
        -L$(IMS_ROOT)/vendors/IntelliNet/lib

ifeq ($(GCC_LIB_VERSION_LESS_THAN_4_3), yes)
INCLS:= -fPIC $(INCLS) $(DIA_INCLS) -I../include \
	    -I../common/include \
        -I$(ITS_ROOT)/common/include \
        -I$(ITS_ROOT)/common/include/asn-cpp \
        -I$(ITS_ROOT)/common/src/ual \
        -I$(ITS_ROOT)/GSMMAP/include/itu \
        -I$(ITS_ROOT)/CAMEL/include/itu \
        -I$(ITS_ROOT)/SCCP/include \
        -I$(ITS_ROOT)/TCAP/include \
        -I$(ITS_ROOT)/MTP3/include \
        -I$(ITS_ROOT)/MTP2/include \
		-I$(ITS_ROOT)/GSMMAP/include \
		-I$(ITS_ROOT)/GSMMAP/include/itu \
		-I$(ITS_ROOT)/CAMEL/include \
		-I$(ITS_ROOT)/CAMEL/include/itu \
		-I$(ITS_ROOT)/tls/include \
        -I$(VENDOR_ROOT)/IntelliNet/include \
		-I$(EACC_ROOT)/mess/include \
		-I$(EACC_ROOT)/blocks/include \
		-I$(EACC_ROOT)/utils/rule/include \
		-I$(EACC_ROOT)/3rdparty/include \
		-I$(EACC_ROOT)/3rdparty/mysql-connector-c++-1.1.0 \
		-I$(EACC_ROOT)/common/include \
		-I$(EACC_ROOT)/cmapi/components \
		-I$(EACC_ROOT)/cmapi/configfetch/include \
		-I$(EACC_ROOT)/cmapi/common \
		-I$(EACC_ROOT)/cmapi/idl \
		-I$(EACC_ROOT)/3rdparty/jsoncpp_0.6.0-rc2/json \
		-I$(EACC_ROOT)/repmgr/include \
		-I$(EACC_ROOT)/avamgr/include \
		-I$(EACC_ROOT)/utils/hash/include
else
INCLS:=-std=gnu++0x -fPIC $(INCLS) $(DIA_INCLS) -I../include \
	    -I../common/include \
        -I$(ITS_ROOT)/common/include \
        -I$(ITS_ROOT)/common/include/asn-cpp \
        -I$(ITS_ROOT)/common/src/ual \
        -I$(ITS_ROOT)/GSMMAP/include/itu \
        -I$(ITS_ROOT)/CAMEL/include/itu \
        -I$(ITS_ROOT)/SCCP/include \
        -I$(ITS_ROOT)/TCAP/include \
        -I$(ITS_ROOT)/MTP3/include \
        -I$(ITS_ROOT)/MTP2/include \
		-I$(ITS_ROOT)/GSMMAP/include \
		-I$(ITS_ROOT)/GSMMAP/include/itu \
		-I$(ITS_ROOT)/CAMEL/include \
		-I$(ITS_ROOT)/CAMEL/include/itu \
		-I$(ITS_ROOT)/tls/include \
        -I$(VENDOR_ROOT)/IntelliNet/include \
		-I$(EACC_ROOT)/mess/include \
		-I$(EACC_ROOT)/avamgr/hacomponent/include \
		-I$(EACC_ROOT)/utils/rule/include \
		-I$(EACC_ROOT)/blocks/include \
		-I$(EACC_ROOT)/3rdparty/include \
		-I$(EACC_ROOT)/3rdparty/mysql-connector-c++-1.1.0 \
		-I$(EACC_ROOT)/common/include \
		-I$(EACC_ROOT)/cmapi/components \
		-I$(EACC_ROOT)/cmapi/configfetch/include \
		-I$(EACC_ROOT)/cmapi/common \
		-I$(EACC_ROOT)/cmapi/idl \
		-I$(EACC_ROOT)/cmapi/alarms/include \
		-I$(EACC_ROOT)/3rdparty/jsoncpp_0.6.0-rc2/json \
		-I$(EACC_ROOT)/repmgr/include \
		-I$(EACC_ROOT)/avamgr/include \
		-I$(EACC_ROOT)/utils/hash/include
endif

SO_OBJS:= ssg_callbacks.o \
		  ssg_configuration.o ssg_statistics.o ssg_dbc.o \
		  IwfCTrieImpl.o IwfCAhoCorasickImpl.o iwf_config.o iwf_state.o iwf_fsm.o iwf_timer.o iwf_session_context.o iwf_transaction_manager.o \
		  iwf_prot_utils.o iwf_prot_s6a_map.o iwf.o iwf_cdr.o iwf_prot_map_s6a.o \
          iwf_prot_cap_ro.o iwf_prot_cap_ro_transatel.o capv1_prot_cap_ro_transatel.o \
		  capv2_prot_cap_ro_transatel.o iwf_prot_default_translator.o iwf_dcca.o\
		  iwf_mess.o  CMAPIDreConfig.o CMAPIIwfConfig.o iwf_alarms.o iwf_transport_controller.o ThreadManager.o

OBJS:= ssg.o


IMS_LIBS:=-lbaseapi$(DBGSUFFIX) \
          -ldccaapi$(DBGSUFFIX) \
          -ldccacore$(DBGSUFFIX) \
          -lnasreqapi$(DBGSUFFIX) \
		  -lcua$(DBGSUFFIX) \
		  -ls6a_3gpp_r10_6$(DBGSUFFIX) \
		  -ls13_3gpp_r10_6$(DBGSUFFIX)\
		  -ltransatel_custom_avps$(DBGSUFFIX)\
		  -lro_3gpp_r10_5_transatel$(DBGSUFFIX)\
		  -lro_3gpp_r10_5$(DBGSUFFIX)

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


ifeq ($(PLATFORM),solaris)
DIA_LIBS:=$(DIA_LIB_PATH) -lITSDFrame$(DBGSUFFIX)   \
         $(IMS_LIBS) -ldiastack$(DBGSUFFIX)    
endif

#ifeq ($(PLATFORM),linux)
#DIA_LIBS:=$(DIA_LIB_PATH) -ldiastack$(DBGSUFFIX)\
#	     -lITSDFrame$(DBGSUFFIX) $(IMS_LIBS) 
#endif

ifeq ($(PLATFORM),linux)
DIA_LIBS:=$(DIA_LIB_PATH) \
         $(IMS_LIBS) -lITSDFrame$(DBGSUFFIX) -ldiastack$(DBGSUFFIX) 
endif


LIBS:=-L$(ITS_ROOT)/common/lib \
      -L../lib \
      -L../common/lib \
	  -L$(ITS_ROOT)/MTP3/lib \
      -L$(ITS_ROOT)/CAMEL/lib \
      -L$(ITS_ROOT)/INAP/lib \
      -L$(ITS_ROOT)/GSMMAP/lib \
      -L$(VENDOR_ROOT)/IntelliNet/lib \
      -lENGINE$(DBGSUFFIX) \
      -lDRIVER++$(DBGSUFFIX) \
      -lDISPATCH++$(DBGSUFFIX) \
	  -lUAL$(DBGSUFFIX) \
	  -lCCITT-M3UA$(DBGSUFFIX) \
      $(VFRAMR_LIB) \
      $(VENDORS_LIB) \
      -lASN++$(DBGSUFFIX) \
      $(PROTLIBS) \
      $(DIA_LIBS) \
      -levent \
	  -lprotobuf \
	  -lpcre \
	  -lmemcached \
	  -lahocorasick \
	  -L$(3PARTY_LIBDIR) -lclips++ \
	  -L$(EACC_ROOT)/3rdparty/lib \
	  -L$(EACC_ROOT)/3rdparty/mysql/lib \
	  -L$(EACC_ROOT)/3rdparty/mysql-connector-c++-1.1.0/driver \
	  -L$(EACC_ROOT)/3rdparty/mysql/lib \
	  -L$(IMS_ROOT)/dtf/lib \
	  -ldtf$(DBGSUFFIX) \
	  -L$(EACC_ROOT)/3rdparty/lib \
	  -lprotobuf \
	  -L$(EACC_ROOT)/lib/debug/ -lcmapiHA -lcmapiconfig -ldrecmapi -lcmapicomp -ldrestatscmapi -lcmapialarms -liwfcmapi -liwfconfigfetch -lReplicationClient -lhash \
	  -L$(EACC_ROOT)/cmapi/idl/lib/ -lHAComponent -lHAComponentidl -lHAidl -lcompoidl -ldreidl -lcfgfetch -lStatsidl -lAlarmsidl -liwfcfgfetch -liwfidl \
	  $(LIBS_MESS) \
	  -lReplicationClient -lcouchbase -L$(EACC_ROOT)/lib/debug -lCouchbaseAdminClient

CMAPILIBS:=-L$(EACC_ROOT)/lib/debug/ -lcmapiconfig -ldrecmapi -lcmapicomp -liwfcmapi -liwfconfigfetch -L$(EACC_ROOT)/cmapi/idl/lib/ -lHAComponent -lHAComponentidl -lcompoidl -ldreidl -lcfgfetch -liwfcfgfetch -liwfidl -lkpiidl 

all: ../lib/libIWF-$(APP_SUFFIX)$(DBGSUFFIX).so \
	../bin/IWF-$(APP_SUFFIX)$(DBGSUFFIX)

clean:
	$(RM) $(OBJS) $(SO_OBJS) ../bin/IWF-$(APP_SUFFIX)$(DBGSUFFIX) \
	../lib/libIWF-$(APP_SUFFIX)$(DBGSUFFIX).so 


../lib/libIWF-$(APP_SUFFIX)$(DBGSUFFIX).so: $(SO_OBJS)
	$(CXXSHAREDAR) -z muldefs $(CXXSHAREDARFLAGS) \
        ../lib/libIWF-$(APP_SUFFIX)$(DBGSUFFIX).so \
        $(SO_OBJS) $(PROTLIBS) $(LIBS) $(NOWHOLEARCHIVE) 


../bin/IWF-$(APP_SUFFIX)$(DBGSUFFIX): $(OBJS) ../lib/libIWF-$(APP_SUFFIX)$(DBGSUFFIX).so
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) \
	$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS) -lIWFCmn-$(APP_SUFFIX)$(DBGSUFFIX) $(LIBS) $(CMAPILIBS) \
	-lIWF-$(APP_SUFFIX)$(DBGSUFFIX) -lsctp  /usr/lib64/libresolv.a $(CMAPILIBS) -L$(EACC_ROOT)/lib/debug -lCouchbaseAdminClient -lcurl

#
# get the rules
#
include $(ITS_ROOT)/config.rules
