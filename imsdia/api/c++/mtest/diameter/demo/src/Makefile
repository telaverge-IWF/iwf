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
# ID: $Id: Makefile,v 1.1.2.1 2013/03/04 04:44:05 pramana Exp $
#
#
############################################################################
#ident "$Id: Makefile,v 1.1.2.1 2013/03/04 04:44:05 pramana Exp $"

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
	-I$(EACC_ROOT)/blocks/include
         
OBJS:= app_trace.o app_common.o app_callbacks.o \
       sample_sender.o app_mml.o app_main.o sample_base.o

all: ../lib/libdiasim$(DBGSUFFIX).so 

clean:
	rm -f $(OBJS)  \
           ../lib/libdiasim$(DBGSUFFIX).so 

../lib/libdiasim$(DBGSUFFIX).so: $(OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
        ../lib/libdiasim$(DBGSUFFIX).so \
 	$(OBJS) $(NOWHOLEARCHIVE)
