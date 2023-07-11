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
# ID: $Id: Makefile,v 3.1.70.1 2013/04/18 07:04:30 jvikram Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.1.70.1  2013/04/18 07:04:30  jvikram
# LOG: Included changes relatd to log segregation.
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:22  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.3  2006/10/17 05:37:58  tpanda
# LOG: Minor changes
# LOG:
# LOG: Revision 2.2  2006/10/17 05:34:06  tpanda
# LOG: Merging with ITS-Diameter
# LOG:
# LOG: Revision 2.1  2006/09/13 09:22:42  yranade
# LOG: Start GA 1.1
# LOG:
# LOG: Revision 1.3  2006/06/21 10:41:27  nvijikumar
# LOG: Modification for Copyright info.
# LOG:
# LOG:
############################################################################
#
# Include the standard definitions
#
include $(IMS_ROOT)/make.dirs

DEFINES:=$(DEFINES) $(ITS_DEFINES)

INCLS:=$(ITS_INCLS) -I../include \
       -I$(ITS_ROOT)/common/include \
       -I$(EACC_ROOT)/blocks/include \
       -I$(ITS_ROOT)/ENGINE/include \


STACK=ITS
ifeq ($(STACK),ITS)
INCLS:=$(INCLS) -I../../vendors/IntelliNet/include
else
INCLS:=$(INCLS) -I../../vendors/opendiameter/include
endif

         
CMN_OBJS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: ../lib/libdiacommon$(DBGSUFFIX).a

clean:
	rm -f $(CMN_OBJS) \
           ../lib/libdiacommon$(DBGSUFFIX).a

../lib/libdiacommon$(DBGSUFFIX).a: $(CMN_OBJS)
	$(CXXAR) $(CXXARFLAGS) \
        ../lib/libdiacommon$(DBGSUFFIX).a \
        $(CMN_OBJS)

