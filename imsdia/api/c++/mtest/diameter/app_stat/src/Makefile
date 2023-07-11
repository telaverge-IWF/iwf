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
# ID: $Id: Makefile,v 3.2.24.1.30.1 2013/04/18 07:04:30 jvikram Exp $
#
#
############################################################################
#ident "$Id: Makefile,v 3.2.24.1.30.1 2013/04/18 07:04:30 jvikram Exp $"

#
# Include the standard definitions
#
include $(IMS_ROOT)/make.dirs

DEFINES:=$(DEFINES) $(ITS_DEFINES) 

INCLS:=$(INCLS) $(ITS_INCLS) \
        -I../include \
        -I$(IMS_ROOT)/include \
        -I$(ITS_ROOT)/include \
        -I$(IMS_ROOT)/dframe/include \
        -I$(IMS_ROOT)/common/include \
        -I$(IMS_ROOT)/api/c++/include \
        -I$(IMS_ROOT)/api/include \
        -I$(IMS_ROOT)/api/include/diameter/base \
	-I$(IMS_ROOT)/api/c++/include/diameter/base \
	-I$(IMS_ROOT)/vendors/IntelliNet/include \
	-I$(IMS_ROOT)/dtf/include \
	-I$(EACC_ROOT)/blocks/include \
	-I$(EACC_ROOT)/3rdparty/include \
	-I$(EACC_ROOT)/mess/include
         
OBJS:= app_trace.o app_common.o app_callbacks.o \
       sample_sender.o app_mml.o app_main.o sample_base.o

all: ../lib/libstatdiaapp$(DBGSUFFIX).so 

clean:
	rm -f $(OBJS)  \
           ../lib/libstatdiaapp$(DBGSUFFIX).so 

../lib/libstatdiaapp$(DBGSUFFIX).so: $(OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) ../lib/libstatdiaapp$(DBGSUFFIX).so $(OBJS) $(NOWHOLEARCHIVE) -L$(EACC_ROOT)/lib/debug -lblocks -lmess -L$(EACC_ROOT)/3rdparty/lib -lprotobuf
