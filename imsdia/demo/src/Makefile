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
# ID: $Id: Makefile,v 3.1.30.1 2012/07/23 10:27:43 brajappa Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.1.30.1  2012/07/23 10:27:43  brajappa
# LOG: Added dependencies for multicore compilation
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:23  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.1  2006/09/13 09:22:42  yranade
# LOG: Start GA 1.1
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

DEFINES:=$(DEFINES) $(ITS_DEFINES) 

INCLS:=$(INCLS) $(ITS_INCLS) \
         $(ACE_INC) $(DIA_INC) $(BST_INC) \
        -I../include \
        -I$(ITS_ROOT)/common/include \
        -I../../api/c++/include \
        -I../../api/c++/include/diameter/base \
        -I../../api/c++/include/diameter/sh \
        -I../../api/c++/include/diameter/cxdx \
        -I../../api/c++/include/diameter/gqgqprime \
        -I../../common/include \
        -I../../dframe/include \
        -I../../val/c++/include \
        -I../../vendors/opendiameter/include
         
APP_OBJS:=app.o app_common.o app_trace.o app_callbacks.o \
          sample_base.o sample_sh.o   \
          sample_cxdx.o sample_gq.o sample_sender.o \
          app_stats.o app_mml.o sample_rfro.o

OBJS:= app_main.o

STAT_LIBS:=../../api/c++/lib/libdiaapi$(DBGSUFFIX).a \
           ../../val/c++/lib/libdiaval$(DBGSUFFIX).a

LIBS:=$(ACE_LIB) $(XER_LIB) -L$(ITS_ROOT)/common/lib \
      -L../lib \
      -L../../dframe/lib \
      -L../../vendors/opendiameter/lib \
      -lENGINE$(DBGSUFFIX) \
      -lDRIVER++$(DBGSUFFIX) \
      -ldiavendor$(DBGSUFFIX) \
      -lDFrame$(DBGSUFFIX)  \
      -ldiaapp$(DBGSUFFIX)  \
      -lACE -lACE_SSL -lxerces-c

all: ../lib/libdiaapp$(DBGSUFFIX).so \
     ../bin/sampleApp$(DBGSUFFIX)

clean:
	rm -f $(OBJS) $(APP_OBJS) \
           ../lib/libdiaapp$(DBGSUFFIX).so \
           ../bin/sampleApp$(DBGSUFFIX)

../lib/libdiaapp$(DBGSUFFIX).so: $(APP_OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
        ../lib/libdiaapp$(DBGSUFFIX).so \
        $(APP_OBJS) $(STAT_LIBS)

../bin/sampleApp$(DBGSUFFIX): $(OBJS) ../lib/libdiaapp$(DBGSUFFIX).so
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJS) \
        $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS) $(LIBS)


