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
# LOG: Revision 9.1  2005/03/23 12:53:20  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.3  2005/03/21 13:51:36  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1.14.1  2004/01/05 09:25:43  sjaddu
# LOG: Merged code from tcs isup branch.
# LOG:
# LOG: Revision 7.1.10.1  2003/09/05 10:22:40  akumar
# LOG: Work with msg based redundancy.
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:53  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.5  2002/08/20 15:53:04  mmiers
# LOG: Update the clean target for china
# LOG:
# LOG: Revision 6.4  2002/05/08 18:34:28  mmiers
# LOG: Don't include SUPPORT and CORE in the build.  Rather, link
# LOG: with libENGINE when testing.
# LOG:
# LOG: Revision 6.3  2002/04/16 21:20:30  hdivoux
# LOG: FT/HA integration.
# LOG:
# LOG: Revision 6.2  2002/04/11 21:25:51  hdivoux
# LOG: Work in progress: upcoming FT/HA.
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:04  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 1.3  2001/07/11 20:23:32  hdivoux
# LOG: Work in progress.
# LOG:
# LOG: Revision 1.2  2001/07/05 14:54:17  hdivoux
# LOG: Build on Solaris.
# LOG:
# LOG: Revision 1.1  2001/07/05 14:35:59  hdivoux
# LOG: Move dsm-gcs to common/src.
# LOG:
# LOG: Revision 1.1  2001/06/27 21:56:19  hdivoux
# LOG: Creation.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars


OBJS=dsm_gcs_impl.o

CFLAGS := $(CFLAGS) -DDSM_IMPLEMENTATION -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include

all: ../../lib/libDSM-GCS$(DBGSUFFIX).so

clean:
	$(RM) *.o \
		../../lib/libDSM-GCS$(DBGSUFFIX).so \
		../../lib/libDSM-GCS$(DBGSUFFIX).a

../../lib/libDSM-GCS$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	../../lib/libDSM-GCS$(DBGSUFFIX).so $(OBJS) $(NOWHOLEARCHIVE)


#
# get the rules
#
include $(ITS_ROOT)/config.rules
