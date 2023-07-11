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
#  LOG: Revision 1.3  2008/05/09 14:48:51  kramesh
#  LOG: NOWHOLEARCHIVE flag added for ES4.0 compilation.
#  LOG:
#  LOG: Revision 1.2  2007/01/10 11:15:10  yranade
#  LOG: Merge changes from 6.5.3 and Lucent branches
#  LOG:
#  LOG: Revision 1.1.2.1  2006/03/15 11:00:12  dsatish
#  LOG: Intial Makefile for Solaris Kernel SCTP.
#  LOG:
#
#  ID: $Id: Makefile,v 1.3 2008/05/09 14:48:51 kramesh Exp $
#
############################################################################


#
# get the vars
#
include $(ITS_ROOT)/config.vars

COBJS=its_sksctp.o

SK-LIBS=/usr/lib/libsctp.so

all: ../../lib/libSKSCTP$(DBGSUFFIX).so

clean:
	$(RM) $(COBJS) .depend ../../lib/libSKSCTP$(DBGSUFFIX).so

../../lib/libSKSCTP$(DBGSUFFIX).so: $(COBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../lib/libSKSCTP$(DBGSUFFIX).so $(COBJS) $(SK-LIBS) $(NOWHOLEARCHIVE)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
