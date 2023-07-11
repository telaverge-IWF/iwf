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
# ID: $Id: Makefile,v 3.4.2.1.2.2 2012/09/06 11:30:45 jvikas Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.4.2.1.2.2  2012/09/06 11:30:45  jvikas
# LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
# LOG:
# LOG: Revision 3.4.2.1.2.1.2.1  2012/08/22 12:58:37  jvikas
# LOG: Fixed Linking and Compilation Issues
# LOG:
# LOG: Revision 3.4.2.1.2.1  2012/07/23 10:27:43  brajappa
# LOG: Added dependencies for multicore compilation
# LOG:
# LOG: Revision 3.4.2.1  2012/06/22 03:55:30  ncshivakumar
# LOG: TLS compilation changes
# LOG:
# LOG: Revision 3.4  2011/03/23 03:50:41  mdinesh
# LOG: DNSLIB included
# LOG:
# LOG: Revision 3.3  2010/07/07 08:28:22  nvijikumar
# LOG: TCS compilation flags support
# LOG:
# LOG: Revision 3.2  2009/01/08 08:35:09  nvijikumar
# LOG: Includeed NOWHOLEARCHIVE to remove libc_nonshared.a dependancy
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:08  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.5  2006/11/24 20:13:08  hbhatnagar
# LOG: Made changes as per the new application and interface independent Dcca
# LOG: Module and cleanup
# LOG:
# LOG: Revision 2.4  2006/10/30 15:42:24  hbhatnagar
# LOG: made changes for new Libraries.
# LOG:
# LOG: Revision 2.3  2006/10/29 11:10:17  hbhatnagar
# LOG: Made changes according to new mtest Makefile and compilation setup for BCGI.(Hemant)
# LOG:
# LOG: Revision 2.2  2006/10/26 15:07:57  hbhatnagar
# LOG: made changes to compile for BCGI (Hemant)
# LOG:
# LOG: Revision 2.1  2006/10/25 10:49:43  hbhatnagar
# LOG: Integration with ITS_Diameter
# LOG:
# LOG: Revision 1.1.2.3  2006/09/27 15:10:30  hbhatnagar
# LOG: Modified for bcgi demo (badri)
# LOG:
# LOG: Revision 1.1.2.2  2006/09/27 09:39:21  hbhatnagar
# LOG: Added support for bcgi namespace (badri)
# LOG:
# LOG: Revision 1.1.2.1  2006/09/16 07:37:17  nvijikumar
# LOG: DCCA mtest First Cut (badri)
# LOG:
# LOG: Revision 1.2  2006/08/01 07:23:00  nvijikumar
# LOG: Common Makefile for both CVS and Package dir structure.
# LOG:
# LOG: Revision 1.1  2006/07/25 04:56:35  kamakshilk
# LOG: Baseline demo application for Tx Interface.
# LOG:
# LOG:
#
############################################################################
#
# Include the standard definitions
#
include $(IMS_ROOT)/make.dirs

DEFINES:=$(DEFINES) $(ITS_DEFINES) 

#-D_BCGI 

INCLS:=$(INCLS) $(ITS_INCLS) \
        -I../include \
        -I../../app/include \
        -I$(IMS_ROOT)/include \
        -I$(IMS_ROOT)/api/c++/include \
        -I$(IMS_ROOT)/common/include \
        -I$(IMS_ROOT)/dframe/include \
        -I$(IMS_ROOT)/vendors/IntelliNet/include\
        -I$(IMS_ROOT)/vendors/IntelliNet/dcca/include \
	 -I$(IMS_ROOT)/dtf/include \
	 -I$(EACC_ROOT)/blocks/include
         
APP_OBJS:=dcca_callbacks.o dcca_mml.o sample_dcca.o \
          sample_sender.o dcca_stats.o dcca_test.o
       

OBJS:=dcca_main.o

IMS_LIBS:=-lbaseapi$(DBGSUFFIX) \
          -ldccaapi$(DBGSUFFIX)

ifeq ($(PLATFORM),solaris)
LIBS_OS:=-lITSDFrame$(DBGSUFFIX)   \
         $(IMS_LIBS)               \
         -ldiastack$(DBGSUFFIX)    \
         -lcmndiaapp$(DBGSUFFIX) \
         -ldccaapp$(DBGSUFFIX)
endif
ifeq ($(PLATFORM),linux)
ifeq ($(TLS),yes)
LIBS_OS:=-ldiastackt$(DBGSUFFIX)    \
         $(IMS_LIBS)               \
         -lITSDFrame$(DBGSUFFIX)   \
         -lcmndiaapp$(DBGSUFFIX) \
         -ldccaapp$(DBGSUFFIX)
else
LIBS_OS:=-ldiastack$(DBGSUFFIX)    \
         $(IMS_LIBS)               \
         -lITSDFrame$(DBGSUFFIX)   \
         -lcmndiaapp$(DBGSUFFIX) \
         -ldccaapp$(DBGSUFFIX)
endif
endif

LIBS:=-L$(ITS_ROOT)/common/lib \
      -L../../app/lib \
      -L../lib \
      -L$(IMS_ROOT)/api/c++/lib \
      -L$(IMS_ROOT)/dframe/lib \
      -L$(IMS_ROOT)/vendors/IntelliNet/lib \
      -L$(IMS_ROOT)/vendors/IntelliNet/dcca/lib \
      -lENGINE$(DBGSUFFIX) \
      -lDRIVER++$(DBGSUFFIX) \
      -ldccacore$(DBGSUFFIX) \
      $(LIBS_OS) \
	-L$(EACC_ROOT)/lib/debug -lblocks \
	-L$(IMS_ROOT)/dtf/lib -ldtf$(DBGSUFFIX)


all: ../lib/libdccaapp$(DBGSUFFIX).so \
     ../bin/sampleDccaApp$(DBGSUFFIX) 

clean:
	rm -f $(OBJS) $(APP_OBJS) \
      	../bin/sampleDccaApp$(DBGSUFFIX) \
	../lib/libdccaapp$(DBGSUFFIX).so	

../lib/libdccaapp$(DBGSUFFIX).so: $(APP_OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
	../lib/libdccaapp$(DBGSUFFIX).so \
   	$(APP_OBJS) $(NOWHOLEARCHIVE)

../bin/sampleDccaApp$(DBGSUFFIX): $(OBJS) ../lib/libdccaapp$(DBGSUFFIX).so
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) \
        $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS) $(LIBS) $(DNSLIB_S)



