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
#  ID: $Id: Makefile,v 9.2 2008/05/09 14:48:51 kramesh Exp $
#
#  LOG: $Log: Makefile,v $
#  LOG: Revision 9.2  2008/05/09 14:48:51  kramesh
#  LOG: NOWHOLEARCHIVE flag added for ES4.0 compilation.
#  LOG:
#  LOG: Revision 9.1  2005/03/23 12:53:33  cvsadmin
#  LOG: Begin PR6.5
#  LOG:
#  LOG: Revision 1.2  2005/03/23 07:26:10  cvsadmin
#  LOG: PR6.4.2 Source Propagated to Current
#  LOG:
#  LOG: Revision 1.1.2.2  2004/01/27 13:44:18  sjaddu
#  LOG: Added file for active-backup redundancy.
#  LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I $(ITS_ROOT)/ISUP/include  -I $(ITS_ROOT)/MTP3/include \
          -I  $(ITS_ROOT)/MTP2/include
OBJS= its_redundancy.o

all: ../../lib/libITS-REDUNDANCY$(DBGSUFFIX).a ../../lib/libITS-REDUNDANCY$(DBGSUFFIX).so

clean:
	$(RM) *.o ../../lib/libITS-REDUNDANCY$(DBGSUFFIX).a  \
    ../../lib/libITS-REDUNDANCY$(DBGSUFFIX).so

../../lib/libITS-REDUNDANCY$(DBGSUFFIX).a: $(OBJS) 
	$(AR) $(ARFLAGS) ../../lib/libITS-REDUNDANCY$(DBGSUFFIX).a $(OBJS)

../../lib/libITS-REDUNDANCY$(DBGSUFFIX).so: $(OBJS) 
	$(SHAREDAR) $(SHAREDARFLAGS) ../../lib/libITS-REDUNDANCY$(DBGSUFFIX).so \
        $(OBJS) $(NOWHOLEARCHIVE)
#
# get the rules
#
include $(ITS_ROOT)/config.rules
