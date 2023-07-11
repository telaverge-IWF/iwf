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
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:55:26 cvsadmin Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.1  2005/03/23 12:55:26  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.3  2005/03/21 13:54:39  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.2.4.1.8.1.14.2  2005/01/03 15:14:45  snagesh
# LOG: MTP2 OAM changes
# LOG:
# LOG: Revision 7.2.4.1.8.1.14.1  2004/12/16 12:19:42  adutta
# LOG: Removed -g option from CFLAGS
# LOG:
# LOG: Revision 7.2.4.1.8.1  2004/03/17 12:50:45  kannanp
# LOG: Changes for new file mtp2_alarms.c.
# LOG:
# LOG: Revision 7.2.4.1  2003/03/28 17:16:27  randresol
# LOG: Add linux defined
# LOG:
# LOG: Revision 7.2  2002/11/10 01:59:31  randresol
# LOG: Build with $(PROTOCOL)
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:52  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 1.6  2002/01/10 16:50:07  mmiers
# LOG: Switch to refcounting transports.
# LOG:
# LOG: Revision 1.5  2001/12/18 21:34:51  mmiers
# LOG: Interim version
# LOG:
# LOG: Revision 1.4  2001/10/25 17:24:46  ngoel
# LOG: remove STANDALONE flag
# LOG:
# LOG: Revision 1.3  2001/10/24 15:34:29  ngoel
# LOG: adax vendor library
# LOG:
#
############################################################################
include $(VENDOR_ROOT)/config.vars

#
# set this to the appropriate subdirectory (ADAX release)
#
ADAXVER=v3_8
#
# set this for the software part (major times 1000, minor
# times 10
#
ADAX_VERSION=3080
DEFINES:=$(DEFINES) -D$(PLATFORM)
CFLAGS:=$(CFLAGS) -I../include -I../include \
       -I$(ITS_ROOT)/common/include \
       -I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
       -I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
       -I$(ITS_ROOT)/TCAP/include \
       -I$(VENDOR_ROOT)/IntelliNet/include

OBJS:=transport.o \
	mtp2.o \
        mtp2_alarms.o

all: ../lib/lib$(PROTOCOL)-ADAXVendor$(DBGSUFFIX).a \
     ../lib/lib$(PROTOCOL)-ADAXVendor$(DBGSUFFIX).so

clean:
	$(RM) $(OBJS) ../lib/lib$(PROTOCOL)-ADAXVendor$(DBGSUFFIX).a \
                      ../lib/lib$(PROTOCOL)-ADAXVendor$(DBGSUFFIX).so

../lib/lib$(PROTOCOL)-ADAXVendor$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../lib/lib$(PROTOCOL)-ADAXVendor$(DBGSUFFIX).a $(OBJS)

../lib/lib$(PROTOCOL)-ADAXVendor$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/lib$(PROTOCOL)-ADAXVendor$(DBGSUFFIX).so $(OBJS)
 
#
# get the rules
#
#include $(VENDOR_ROOT)/config.rules


