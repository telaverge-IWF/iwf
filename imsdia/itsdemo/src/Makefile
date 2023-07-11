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
# ID: $Id: Makefile,v 3.9.4.4 2012/12/21 05:53:29 ncshivakumar Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.9.4.4  2012/12/21 05:53:29  ncshivakumar
# LOG: Modified for tracing
# LOG:
# LOG: Revision 3.9.4.3  2012/10/11 09:12:19  vsarath
# LOG: DTF::Rearranged -lblocks to resolve linker problems
# LOG:
# LOG: Revision 3.9.4.2  2012/09/06 11:30:45  jvikas
# LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
# LOG:
# LOG: Revision 3.9.4.1.2.3  2012/08/28 04:49:44  cprem
# LOG: Added JsonCPP lib and includes.
# LOG:
# LOG: Revision 3.9.4.1.2.2  2012/08/28 03:58:05  cprem
# LOG: Added Json include path.
# LOG:
# LOG: Revision 3.9.4.1.2.1  2012/08/22 12:58:37  jvikas
# LOG: Fixed Linking and Compilation Issues
# LOG:
# LOG: Revision 3.9.4.1  2012/07/23 10:27:43  brajappa
# LOG: Added dependencies for multicore compilation
# LOG:
# LOG: Revision 3.9  2011/03/23 02:51:56  nvijikumar
# LOG: DNS library included
# LOG:
# LOG: Revision 3.8  2010/07/07 08:34:13  nvijikumar
# LOG: TCS compilation flags support
# LOG:
# LOG: Revision 3.7  2010/06/30 08:57:22  nvijikumar
# LOG: USE_ONLY_SSL option provided
# LOG:
# LOG: Revision 3.6  2009/01/02 06:03:33  nvijikumar
# LOG: Fix for linking issue with TLS libs
# LOG:
# LOG: Revision 3.5  2008/08/12 04:25:03  nvijikumar
# LOG: Defined NOWHOLEARCHIVE to remove libc_nonshared dependency. gdalawai
# LOG:
# LOG: Revision 3.4  2008/08/06 11:21:47  vnarang
# LOG: Changes to link libdiastackt only with TLS option
# LOG:
# LOG: Revision 3.3  2008/07/09 14:10:19  vnarang
# LOG: TLS Linking is removed as TLS library is linking with Dia Stack Lib
# LOG:
# LOG: Revision 3.2  2008/06/13 11:13:05  hbhatnagar
# LOG: Added TLS Wrapper library
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:26  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 1.8  2007/01/17 06:58:11  nvijikumar
# LOG: Linking with nasreqapi shared library.
# LOG:
# LOG: Revision 1.7  2006/11/30 08:10:24  kamakshilk
# LOG: linking to GCS-CLIENTD.so removed
# LOG:
# LOG: Revision 1.6  2006/11/24 16:18:13  hbhatnagar
# LOG: made changes for only including Dcca core library, removing other
# LOG: plugin libraries.
# LOG:
# LOG: Revision 1.5  2006/11/20 08:51:04  nvijikumar
# LOG: Chnages for Redundancy support.
# LOG:
# LOG: Revision 1.4  2006/11/03 13:57:25  nvijikumar
# LOG: 64 bit compilation support.
# LOG:
# LOG: Revision 1.3  2006/10/30 15:28:48  hbhatnagar
# LOG: made changes for dcca to include the libraries.
# LOG:
# LOG: Revision 1.2  2006/10/28 07:48:21  yranade
# LOG: Library linking reorganisation, codec so linked
# LOG:
# LOG: Revision 1.1  2006/10/17 06:28:20  tpanda
# LOG: Baseline ITS Demo.
# LOG:
# LOG: Revision 1.8  2006/06/21 09:57:29  kamakshilk
# LOG: Modification for Copyright info.
# LOG:
# LOG: Revision 1.7  2006/06/02 04:51:01  kamakshilk
# LOG: RfRo source added to Makefile
# LOG:
# LOG: Revision 1.6  2006/04/17 16:25:57  yranade
# LOG: Statistics and MML Support.
# LOG:
# LOG: Revision 1.5  2006/04/03 22:24:23  brianhu
# LOG: Add -f to "rm" in "clean" target.
# LOG:
# LOG: Revision 1.4  2006/03/18 12:29:30  nvijikumar
# LOG: Added app.o it is common for all protocol
# LOG:
# LOG:
#
############################################################################
#
# Include the standard definitions
#
include $(IMS_ROOT)/make.dirs

DEFINES:=$(DEFINES) $(ITS_DEFINES) -DJSON_IS_AMALGAMATION

INCLS:=$(INCLS) $(ITS_INCLS) \
        -I../include \
        -I$(ITS_ROOT)/common/include \
        -I../../api/c++/include/diameter/dcca \
        -I../../api/c++/include \
        -I../../common/include \
        -I../../dframe/include \
        -I../../val/c++/include \
        -I../../vendors/IntelliNet/include \
        -I$(IMS_ROOT)/dtf/include \
        -I$(EACC_ROOT)/blocks/include \
		-I$(EACC_ROOT)/3rdparty/jsoncpp_0.6.0-rc2
        
ifeq ($(TLS),yes)
TLSLIBS:= -L$(ITS_ROOT)/tls/lib/  -lITS-TLS$(DBGSUFFIX)
DIALIB=-ldiastackt
ifeq ($(USE_ONLY_SSL),yes)
TLSLIBS:= -L$(ITS_ROOT)/tls/lib/  -lITS-SSLTLS$(DBGSUFFIX)
endif
else
DIALIB=-ldiastack
endif
 
APP_OBJS:=app.o app_common.o app_trace.o app_callbacks.o \
          sample_base.o sample_sh.o   \
          sample_cxdx.o sample_gq.o sample_sender.o \
          app_stats.o app_mml.o sample_rfro.o

OBJS:= app_main.o

IMS_LIBS:=-lbaseapi$(DBGSUFFIX) \
          -lcxdxapi$(DBGSUFFIX) \
          -lshapi$(DBGSUFFIX)   \
          -lgqgqapi$(DBGSUFFIX) \
          -lrfroapi$(DBGSUFFIX) \
          -lnasreqapi$(DBGSUFFIX) \
          -ldccacore$(DBGSUFFIX) 

ifeq ($(PLATFORM),solaris)    
LIBS_OS:=-lITSDFrame$(DBGSUFFIX)   \
         $(IMS_LIBS)               \
         $(DIALIB)$(DBGSUFFIX)    \
         -ldiaapp$(DBGSUFFIX)
endif

ifeq ($(PLATFORM),solaris64)    
LIBS_OS:=-lITSDFrame$(DBGSUFFIX)   \
         $(IMS_LIBS)               \
         $(DIALIB)$(DBGSUFFIX)    \
         -ldiaapp$(DBGSUFFIX)
endif

ifeq ($(PLATFORM),linux)    
LIBS_OS:=$(DIALIB)$(DBGSUFFIX)    \
         $(IMS_LIBS)               \
         -lITSDFrame$(DBGSUFFIX)   \
         -ldiaapp$(DBGSUFFIX)
endif         



LIBS:=-L$(ITS_ROOT)/common/lib            \
      -L../lib                            \
      -L../../api/c++/lib                 \
      -L../../dframe/lib                  \
      -L../../vendors/IntelliNet/lib      \
      -L../../vendors/IntelliNet/dcca/lib \
      -lENGINE$(DBGSUFFIX)                \
      -lDRIVER++$(DBGSUFFIX)              \
      $(LIBS_OS)                          \
      $(TLSLIBS)                          \
      -L$(IMS_ROOT)/dtf/lib -ldtf$(DBGSUFFIX) \
      -L$(EACC_ROOT)/lib/debug -lblocks   \
	   -L$(DRE_ROOT)/erlbf/json/lib -ljsoncpp
      

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
QFLAGS = -cache-dir=./cache -max-threads=120 -chain-length=15 -show-directory=yes 
QUANTIFY = purify $(QFLAGS)
LIBS:=$(LIBS) -L`purify -print-home-dir`
endif

all: ../lib/libdiaapp$(DBGSUFFIX).so \
     ../bin/sampleApp$(DBGSUFFIX)

clean:
	rm -f $(OBJS) $(APP_OBJS) \
           ../lib/libdiaapp$(DBGSUFFIX).so \
           ../bin/sampleApp$(DBGSUFFIX)

../lib/libdiaapp$(DBGSUFFIX).so: $(APP_OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
        ../lib/libdiaapp$(DBGSUFFIX).so \
        $(APP_OBJS) $(NOWHOLEARCHIVE)

../bin/sampleApp$(DBGSUFFIX): $(OBJS) ../lib/libdiaapp$(DBGSUFFIX).so
	$(QUANTIFY) $(CXX) $(CXXFLAGS) -o $@ $(OBJS) \
        $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS) $(LIBS) $(DNSLIB_S)

