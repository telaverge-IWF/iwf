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
# LOG: $Log: Makefile,v $
# LOG: Revision 9.2  2008/05/09 14:48:51  kramesh
# LOG: NOWHOLEARCHIVE flag added for ES4.0 compilation.
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:24  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.3  2005/03/21 13:51:40  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:53  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.6  2002/08/20 15:53:04  mmiers
# LOG: Update the clean target for china
# LOG:
# LOG: Revision 6.5  2002/05/07 15:43:36  wweng
# LOG: Don't link with SUPPORT and CORE (link with ENGINE instead).
# LOG:
# LOG: Revision 6.4  2002/04/16 21:20:30  hdivoux
# LOG: FT/HA integration.
# LOG:
# LOG: Revision 6.3  2002/04/11 21:17:01  hdivoux
# LOG: Work in progress: upcoming FT/HA.
# LOG:
# LOG: Revision 6.2  2002/04/11 21:10:09  hdivoux
# LOG: Work in progress: upcoming FT/HA.
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:05  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 1.7  2001/07/19 16:13:08  mmiers
# LOG: Unix build.
# LOG:
# LOG: Revision 1.6  2001/07/10 16:12:18  mmiers
# LOG: Cross platform build.
# LOG:
# LOG: Revision 1.5  2001/07/05 21:30:27  mmiers
# LOG: These are .a's again.
# LOG:
# LOG: Revision 1.4  2001/07/03 21:16:22  mmiers
# LOG: Move RM and DSM.
# LOG:
# LOG: Revision 1.2  2001/06/26 15:20:48  mmiers
# LOG: Build into common
# LOG:
# LOG: Revision 1.1  2001/06/22 18:33:27  mmiers
# LOG: Move DSM to ENGINE.
# LOG:
# LOG: Revision 1.2  2001/06/21 00:58:29  mmiers
# LOG: UNIX build.
# LOG:
# LOG: Revision 1.1  2001/06/20 21:06:25  mmiers
# LOG: Add stub DSM implementation (no redundancy)
# LOG:
# LOG: Revision 1.1  2001/06/20 19:55:41  mmiers
# LOG: Split DSM out into a separate library.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars


OBJS=dsm_stub_impl.o

CFLAGS := $(CFLAGS) -DDSM_IMPLEMENTATION

all: ../../lib/libDSM-STUB$(DBGSUFFIX).so

clean:
	$(RM) *.o \
		../../lib/libDSM-STUB$(DBGSUFFIX).so \
		../../lib/libDSM-STUB$(DBGSUFFIX).a

../../lib/libDSM-STUB$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	../../lib/libDSM-STUB$(DBGSUFFIX).so \
	$(OBJS) $(NOWHOLEARCHIVE)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
