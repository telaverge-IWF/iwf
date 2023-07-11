
############################################################################
#                                                                          #
#     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
#  ID: $Id: Makefile,v 1.2 2008/06/27 14:10:08 mpatri Exp $
#  LOG: $Log: Makefile,v $
#  LOG: Revision 1.2  2008/06/27 14:10:08  mpatri
#  LOG: Accelero CGI Phase I: To support SCTP Configuration APIs & move to new directory sctp-cm
#  LOG:
#  LOG: Revision 1.1  2008/06/27 13:37:24  mpatri
#  LOG: new directory is created for sctp configuration manager files
#  LOG:
#  LOG:
############################################################################

#
# get the vars
#

include $(ITS_ROOT)/config.vars

SOURCES := $(wildcard *.c) $(wildcard *.cpp)

OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))

INCL_DIR= ../include
LIB_DIR=$(ITS_ROOT)/common/lib


CFLAGS:=$(CFLAGS) -I../lksctp


all: $(LIB_DIR)/libSCTPConfigMgr$(DBGSUFFIX).so

$(LIB_DIR)/libSCTPConfigMgr$(DBGSUFFIX).so: $(OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) $@ $^ $(NOWHOLEARCHIVE)


clean :
	$(RM) $(OBJS) $(LIB_DIR)/libSCTPConfigMgr$(DBGSUFFIX).so


#
# get the rules
#
include $(ITS_ROOT)/config.rules


