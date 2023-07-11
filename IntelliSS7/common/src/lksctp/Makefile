
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
#
#  LOG: $Log: Makefile,v $
#  LOG: Revision 1.4.16.1.2.1.4.1  2013/10/04 13:37:52  millayaraja
#  LOG: changes for RHEL machine dependent compilation flags
#  LOG:
#  LOG: Revision 1.4.16.1.2.1  2012/12/18 16:11:58  brajappa
#  LOG: Initial IWF branch creation and linux compilation changes
#  LOG:
#  LOG: Revision 1.4.16.1  2011/04/13 07:37:34  nvijikumar
#  LOG: Merging Diameter specific changes
#  LOG:
#  LOG: Revision 1.4  2008/06/27 14:28:30  mpatri
#  LOG: Accelero CGI Phase I: Modification to adopt code review comments & Fixing other issues
#  LOG:
#  LOG: Revision 1.3  2008/06/23 06:01:21  mpatri
#  LOG: Accelero CGI Phase I Makefile changes
#  LOG:
#  LOG: Revision 1.2  2008/05/09 14:48:51  kramesh
#  LOG: NOWHOLEARCHIVE flag added for ES4.0 compilation.
#  LOG:
#  LOG: Revision 1.1  2005/06/02 06:54:35  yranade
#  LOG: Linux Kernel SCTP Integration as per ACC652-SDS-LKSC-V1.0.02.
#  LOG:
#
#  ID: $Id: Makefile,v 1.4.16.1.2.1.4.1 2013/10/04 13:37:52 millayaraja Exp $
#
############################################################################

#ident "$Id: Makefile,v 1.4.16.1.2.1.4.1 2013/10/04 13:37:52 millayaraja Exp $"

#
# get the vars
#
include $(ITS_ROOT)/config.vars

LIB_DIR=$(ITS_ROOT)/common/lib
COBJS=its_lksctp.o

LK-LIBS=-lsctp


CFLAGS:= $(CFLAGS) -I .\
         -I ../../include\

ifeq ($(D13PLUS), yes)
CFLAGS:= $(CFLAGS) -D_SCTP_SCOKET_IETF_DRAFT_13_AND_ABOVE_
endif

ifeq ($(D11PLUS), yes)
CFLAGS:= $(CFLAGS) -D_SCTP_SCOKET_IETF_DRAFT_11_AND_ABOVE_
endif

ifeq ($(SCTP_LIB_VERSION_LESS_THAN_1_0_10), yes)
CFLAGS:= $(CFLAGS) -D_SCTP_SCOKET_IETF_DRAFT_10_AND_BELOW_
endif



all: $(LIB_DIR)/libLKSCTP$(DBGSUFFIX).so

clean:
	$(RM) $(COBJS) .depend ../../lib/libLKSCTP$(DBGSUFFIX).so

$(LIB_DIR)/libLKSCTP$(DBGSUFFIX).so: $(COBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) $@ $^ $(LK-LIBS) $(NOWHOLEARCHIVE)

#
# get the rules
#
include $(ITS_ROOT)/config.rules

