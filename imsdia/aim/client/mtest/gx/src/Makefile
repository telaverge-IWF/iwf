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
# FILE: Makefile                                                           #
#                                                                          #
############################################################################
#                                                                          #
# ID: $Id: Makefile,v 3.1 2008/03/31 10:33:01 nvijikumar Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.1  2008/03/31 10:33:01  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 1.5  2006/11/23 09:48:48  kamakshilk
# LOG: option for 64 bit compilation
# LOG:
# LOG: Revision 1.4  2006/11/17 06:54:02  kamakshilk
# LOG: ITS_ROOT/include added for package
# LOG:
# LOG: Revision 1.3  2006/11/16 13:44:10  kamakshilk
# LOG: EXPAT library linking removed
# LOG:
# LOG: Revision 1.2  2006/11/07 13:12:37  kamakshilk
# LOG: Changes to work with ITS-Diameter
# LOG:
# LOG: Revision 1.1  2006/10/03 09:21:28  rrath
# LOG: Baseline distributed demo for new IMS Interfaces.
# LOG:
#
############################################################################

include	$(IMS_ROOT)/make.dirs

DEFINES:=$(DEFINES) -DDUMP $(ITS_DEFINES)

CXXFLAGS:=$(CXXFLAGS) -g -I./ -DUNIX \
        -I$(ITS_ROOT)/common/include \
        -I$(IMS_ROOT)/common/include \
        -I../include \
        -I$(IMS_ROOT)/aim/client/include \
        -I$(IMS_ROOT)/api/c++/include \
        -I$(ITS_ROOT)/include \
        -I$(IMS_ROOT)/api/include 

IMS_LIBS:=-lbaseapi$(DBGSUFFIX) \
          -lgxapi$(DBGSUFFIX)

ifeq ($(PLATFORM),solaris)
LIBS_OS:= \
         -ldiaval$(DBGSUFFIX) \
         $(IMS_LIBS) \
         -lIDSClient$(DBGSUFFIX)
endif
ifeq ($(PLATFORM),solaris64)
LIBS_OS:= \
         -ldiaval$(DBGSUFFIX) \
         $(IMS_LIBS) \
         -lIDSClient$(DBGSUFFIX)
endif
ifeq ($(PLATFORM),linux)
LIBS_OS:= \
         $(IMS_LIBS) \
         -ldiaval$(DBGSUFFIX) \
         -lIDSClient$(DBGSUFFIX)
endif

LIBS:= $(ITS_LIBS) \
            -L$(ITS_ROOT)/common/lib \
            -L$(IMS_ROOT)/aim/client/lib \
            -L../lib \
            -L$(IMS_ROOT)/api/c++/lib \
            -L$(IMS_ROOT)/api/lib \
            -L$(IMS_ROOT)/lib \
            -L$(IMS_ROOT)/val/c++/lib \
            $(LIBS_OS)

OBJS:= app.o CCTest.o RATest.o sample_gx.o app_main.o

# Restrict the user to give explicit targets
all: ../bin/sampleGxClient$(DBGSUFFIX)

../bin/sampleGxClient$(DBGSUFFIX): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) -o \
	$@ $(OBJS) $(LIBS) -lpthread $(SOCKLIBS) $(SYSLIBS) -ldl

clean:
	$(RM) ../bin/sampleGxClient$(DBGSUFFIX) $(OBJS) 

