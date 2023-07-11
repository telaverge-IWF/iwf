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
# ID: $Id: Makefile,v 3.2 2008/12/04 11:37:02 gdalawai Exp $
#
#
############################################################################

include	$(IMS_ROOT)/make.dirs

DEFINES:=$(DEFINES) -DDUMP $(ITS_DEFINES)

CXXFLAGS:=$(CXXFLAGS) -g -I./ -DUNIX \
        -I$(ITS_ROOT)/common/include \
        -I$(IMS_ROOT)/common/include \
        -I$(IMS_ROOT)/include \
        -I$(IMS_ROOT)/include \
        -I../include \
        -I$(IMS_ROOT)/aim/client/include \
        -I$(IMS_ROOT)/api/c++/include \
        -I$(ITS_ROOT)/include \
        -I$(IMS_ROOT)/api/include 

ifeq ($(PLATFORM),solaris)
LIBS_OS:= \
         -ldiaval$(DBGSUFFIX) \
         -lIDSClient$(DBGSUFFIX)
endif
ifeq ($(PLATFORM),solaris64)
LIBS_OS:= \
         -ldiaval$(DBGSUFFIX) \
         -lIDSClient$(DBGSUFFIX)
endif
ifeq ($(PLATFORM),linux)
LIBS_OS:= \
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
            -lIDSClient$(DBGSUFFIX)

OBJS:= app_common.o app_main.o sample_base.o

# Restrict the user to give explicit targets
all: ../lib/libdistdiaapp$(DBGSUFFIX).so

../lib/libdistdiaapp$(DBGSUFFIX).so: $(OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
        ../lib/libdistdiaapp$(DBGSUFFIX).so $(OBJS) $(LIBS) -lpthread -ldl $(NOWHOLEARCHIVE)

clean:
	rm -f ../lib/libdistdiaapp$(DBGSUFFIX).so $(OBJS) 

