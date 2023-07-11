############################################################################
#                                                                          #
#     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
# LOG: $Log: Makefile,v $
# LOG: Revision 9.2  2008/05/09 14:48:51  kramesh
# LOG: NOWHOLEARCHIVE flag added for ES4.0 compilation.
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:26  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.3  2005/03/21 13:51:42  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:05  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 1.3  2001/06/28 17:22:51  hdivoux
# LOG: Update for Sun cc port.
# LOG:
# LOG: Revision 1.2  2001/06/28 16:43:44  hdivoux
# LOG: Work in progress. Temp (need review).
# LOG:
# LOG: Revision 1.1  2001/06/28 15:21:54  hdivoux
# LOG: Creation.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

COBJS=gcs_client.o alarm.o events.o memory.o sp.o

all: ../../lib/libGCS-CLIENT$(DBGSUFFIX).so


clean:
	$(RM) $(COBJS) .depend ../../lib/libGCS-CLIENT$(DBGSUFFIX).so

../../lib/libGCS-CLIENT$(DBGSUFFIX).so: $(COBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../lib/libGCS-CLIENT$(DBGSUFFIX).so $(COBJS) $(NOWHOLEARCHIVE)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
