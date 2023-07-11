############################################################################
#                                                                          #
#     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
#                                                                          #
############################################################################
#
# ID: $Id: Makefile,v 3.12.4.5.8.1.2.1.4.1 2014/05/12 05:49:43 millayaraja Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.12.4.5.8.1.2.1.4.1  2014/05/12 05:49:43  millayaraja
# LOG: merged changes for Hop-By-Hop Id fix from B-DRE-0400-01-AICENT-POC branch
# LOG:
# LOG: Revision 3.12.4.5.8.1.2.1  2013/10/26 07:46:27  ncshivakumar
# LOG: RFC 6733 changes
# LOG:
# LOG: Revision 3.12.4.5.8.1  2013/07/04 10:44:20  ncshivakumar
# LOG: included eAccelero library to resolve linking issues because of TPS based licensing
# LOG:
# LOG: Revision 3.12.4.5  2012/11/20 17:39:44  pramana
# LOG: Merged from CMAPI branch for 212-07 release
# LOG:
# LOG: Revision 3.12.4.2.8.1  2012/11/20 10:14:46  rgovardhan
# LOG: merge from 00 Nov20Rel
# LOG:
# LOG: Revision 3.12.4.3  2012/11/06 16:31:20  pramana
# LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
# LOG:
# LOG: Revision 3.12.4.2.12.1  2012/11/05 03:43:39  vsarath
# LOG: Added for TLS enhancements
# LOG:
# LOG: Revision 3.12.4.2  2012/10/11 08:52:18  vsarath
# LOG: DTF::Rearranged -lblocks to resolve linker problems
# LOG:
# LOG: Revision 3.12.4.1  2012/09/06 11:30:45  jvikas
# LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
# LOG:
# LOG: Revision 3.12.6.2  2012/08/28 04:48:57  cprem
# LOG: Added jsoncpp library path.
# LOG:
# LOG: Revision 3.12.6.1  2012/08/22 12:58:37  jvikas
# LOG: Fixed Linking and Compilation Issues
# LOG:
# LOG: Revision 3.12  2011/03/23 03:52:04  mdinesh
# LOG: DNSLIB included
# LOG:
# LOG: Revision 3.11  2009/03/02 04:49:28  nvijikumar
# LOG: Linking with dms lib for MML API support
# LOG:
# LOG: Revision 3.10  2009/01/29 04:44:24  nvijikumar
# LOG: Updated with Quantify compilation options
# LOG:
# LOG: Revision 3.9  2009/01/07 07:21:06  nvijikumar
# LOG: Print TPS if MOTO_PERF_PRINT defined exists
# LOG:
# LOG: Revision 3.8  2009/01/04 06:28:24  nvijikumar
# LOG: Added new file ids_idcManager.cpp
# LOG:
# LOG: Revision 3.7  2009/01/02 06:02:11  nvijikumar
# LOG: Fix for linking issue with TLS libs
# LOG:
# LOG: Revision 3.6  2008/08/12 04:25:24  nvijikumar
# LOG: Defined NOWHOLEARCHIVE to remove libc_nonshared dependency. gdalawai
# LOG:
# LOG: Revision 3.5  2008/08/06 11:47:09  vnarang
# LOG: Changes to build seperate lib and bin for TLS
# LOG:
# LOG: Revision 3.4  2008/07/31 06:22:23  sureshj
# LOG: Giving Tls header File Path
# LOG:
# LOG: Revision 3.3  2008/07/09 14:13:38  vnarang
# LOG: TLS Linking is removed as TLS library is linking with Dia Stack Lib
# LOG:
# LOG: Revision 3.2  2008/06/13 11:05:24  hbhatnagar
# LOG: Adding TLS wrapper Lib for compilation
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.16  2008/03/27 11:21:05  hbhatnagar
# LOG: Converting 2.1 branch to CURRENT
# LOG:
# LOG: Revision 2.14.4.2  2007/03/22 12:11:02  nvijikumar
# LOG: Changing library order to work with linux and Solaris.
# LOG:
# LOG: Revision 2.14.4.1  2007/03/22 07:41:40  nvijikumar
# LOG: Fix for library linking issue Bridgewater issue.
# LOG:
# LOG: Revision 2.14  2007/01/30 05:24:58  nanaparthi
# LOG: Added target for MML application
# LOG:
# LOG: Revision 2.13  2006/11/30 07:28:02  kamakshilk
# LOG: linking to GCS-CLIENTD.so removed
# LOG:
# LOG: Revision 2.12  2006/11/29 04:15:05  kamakshilk
# LOG: rfroapi & dccapi lib removed
# LOG:
# LOG: Revision 2.11  2006/11/26 07:36:41  yranade
# LOG: Updated Makefile per recent DCCA Changes.
# LOG:
# LOG: Revision 2.10  2006/11/24 15:42:58  kamakshilk
# LOG: Changes for redundancy support
# LOG:
# LOG: Revision 2.9  2006/11/17 06:06:31  kamakshilk
# LOG: dccaapi library linked
# LOG:
# LOG: Revision 2.8  2006/11/14 09:00:30  kamakshilk
# LOG: ids_sessiondb.o removed
# LOG:
# LOG: Revision 2.7  2006/11/08 08:47:46  kamakshilk
# LOG: 64 bit compilation support
# LOG:
# LOG: Revision 2.6  2006/11/08 06:09:25  kamakshilk
# LOG: Linked with dcca libraries
# LOG:
# LOG: Revision 2.5  2006/10/31 10:04:44  kamakshilk
# LOG: DUMP option removed
# LOG:
# LOG: Revision 2.4  2006/10/29 05:43:02  kamakshilk
# LOG: libbaseapiD.so linked
# LOG:
# LOG: Revision 2.3  2006/10/24 11:34:03  kamakshilk
# LOG: Changes to compile on solaris
# LOG:
# LOG: Revision 2.2  2006/10/16 14:17:44  kamakshilk
# LOG: Changes to work with ITS-Diameter
# LOG:
# LOG: Revision 2.1  2006/09/13 09:22:39  yranade
# LOG: Start GA 1.1
# LOG:
# LOG: Revision 1.8  2006/06/21 10:01:11  kamakshilk
# LOG: Modification for Copyright info.
# LOG:
# LOG:
############################################################################
#
# Include the standard definitions
#
include $(IMS_ROOT)/make.dirs

ifeq ($(Q), yes)
DEFINES:= $(DEFINES) -DQ
CXXFLAGS:=$(CXXFLAGS) -I`quantify -print-home-dir`
QFLAGS = -max-threads=120 -record-system-calls=no
QUANTIFY = quantify $(QFLAGS)
LIBS:=$(LIBS) -L`quantify -print-home-dir`
endif

ifeq ($(P), yes)
DEFINES:= $(DEFINES) -DP
CXXFLAGS:=$(CXXFLAGS) -I`purify -print-home-dir`
QFLAGS = -cache-dir=./cache -max-threads=120 -chain-length=15 -show-directory=ye
s
QUANTIFY = purify $(QFLAGS)
LIBS:=$(LIBS) -L`purify -print-home-dir`
endif

LIB_OBJS=ids_callbacks.o ids_common.o ids_heartbeat.o ids_routedb.o \
          ids_clientinterface.o ids_conndb.o ids_msghandler.o ids_mml.o \
          ids_idcManager.o
SRC_OBJS=ids_main.o

ifeq ($(TLS),yes)
TLSLIBS:= -L$(ITS_ROOT)/tls/lib/  -lITS-TLS$(DBGSUFFIX)
DIALIB=-ldiastackt
IDSLIB=DiaServert
IDSBIN=DiaServert
else
DIALIB=-ldiastack
IDSLIB=DiaServer
IDSBIN=DiaServer
endif

ifeq ($(USE_SELECT),yes)
CXXFLAGS := $(CXXFLAGS) -DUSE_SELECT
endif

CXXFLAGS := $(CXXFLAGS) $(ITS_DEFINES) -I../include \
            -I$(ITS_ROOT)/common/include \
            -I$(ITS_ROOT)/ENGINE/include \
            -I$(ITS_ROOT)/tls/include \
            -I../../../common/include \
            -I../../../api/c++/include \
            -I../../../dframe/include \
            -I../../../val/c++/include \
            -I../../../vendors/IntelliNet/include \
            -I$(IMS_ROOT)/dtf/include \
            -I$(EACC_ROOT)/blocks/include

IMS_LIBS:= \
        -lbaseapi$(DBGSUFFIX) \
        -lcua$(DBGSUFFIX) \
        -ldccacore$(DBGSUFFIX)
        
ifeq ($(PLATFORM),solaris)
LIBS_OS:=-lITSDFrame$(DBGSUFFIX) \
         $(IMS_LIBS) \
         $(DIALIB)$(DBGSUFFIX)  
endif
ifeq ($(PLATFORM),solaris64)
LIBS_OS:=-lITSDFrame$(DBGSUFFIX) \
         $(IMS_LIBS) \
         $(DIALIB)$(DBGSUFFIX)  
endif
ifeq ($(PLATFORM),linux)
LIBS_OS:=$(DIALIB)$(DBGSUFFIX)  \
         $(IMS_LIBS) \
         -lITSDFrame$(DBGSUFFIX) 
endif

ITS_LIBS := $(ITS_LIBS) \
            -L$(ITS_ROOT)/common/lib \
            -L$(ITS_ROOT)/tls/lib \
            -L../lib \
            -L../../../dframe/lib \
            -L../../../api/c++/lib \
            -L../../../vendors/IntelliNet/lib \
            -L../../../vendors/IntelliNet/dcca/lib \
            -lENGINE$(DBGSUFFIX) \
            -lDRIVER++$(DBGSUFFIX) \
            $(LIBS_OS)             \
            -l$(IDSLIB)$(DBGSUFFIX) \
            $(TLSLIBS) \
            -L$(IMS_ROOT)/dtf/lib -ldtf$(DBGSUFFIX) \
            -L$(EACC_ROOT)/lib/debug -lblocks -lcmapialarms -lmess -lblocks \
            -L$(EACC_ROOT)/cmapi/idl/lib -lAlarmsidl \
            -L$(EACC_ROOT)/3rdparty/lib -lprotobuf \
			-L$(DRE_ROOT)/erlbf/json/lib -ljsoncpp

DM_LIBS := -L../../../mgmt/dms/lib \
            -lDms$(DBGSUFFIX)     

all: ../lib/lib$(IDSLIB)$(DBGSUFFIX).so \
     ../bin/$(IDSBIN)$(DBGSUFFIX)

../bin/$(IDSBIN)$(DBGSUFFIX): $(SRC_OBJS)
	$(QUANTIFY) $(CXX) $(CXXFLAGS) -o $@ \
	$(SRC_OBJS) \
	$(SYSLIBS) $(THREADLIBS) $(ITS_LIBS) $(SOCKLIBS) $(DM_LIBS) $(DNSLIB_S)

../lib/lib$(IDSLIB)$(DBGSUFFIX).so: $(LIB_OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) $@ $(LIB_OBJS) $(NOWHOLEARCHIVE)

clean :
	$(RM) ../lib/lib$(IDSLIB)$(DBGSUFFIX).so \
        $(RM) ../bin/$(IDSBIN)$(DBGSUFFIX) \
        $(LIB_OBJS) $(SRC_OBJS)

