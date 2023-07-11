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
#     FILE: Makefile                                                       #
#                                                                          #
############################################################################
#
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.1  2005/03/23 12:54:27  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 1.4  2005/03/21 13:53:24  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 1.3.2.1  2004/12/28 14:00:33  mkrishna
# LOG: SIP code propagated from Current Branch
# LOG:
# LOG: Revision 1.3  2004/03/30 15:35:08  sjaddu
# LOG: commited after some unit testing.
# LOG:
# LOG: Revision 1.1  2004/03/19 06:03:02  sjaddu
# LOG: Added first revsion for sip, work in progress.
# LOG:
#
############################################################################

#
# get the vars
#
include $(VENDOR_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I ../include -I$(ITS_ROOT)/SIP/include \
          -I$(ITS_ROOT)/common/include


OBJS= sip_ifc.o sip_transaction.o sip_ict.o sip_ist.o \
      sip_nict.o sip_nist.o sip_context.o sip_transport.o

#
#
all: ../../lib/libSIP-VENDOR$(DBGSUFFIX).a \
     ../../lib/libSIP-VENDOR$(DBGSUFFIX).so

../../lib/libSIP-VENDOR$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../lib/libSIP-VENDOR$(DBGSUFFIX).a $(OBJS)

../../lib/libSIP-VENDOR$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
		../../lib/libSIP-VENDOR$(DBGSUFFIX).so \
		$(OBJS)

clean:
	$(RM) -rf *.o ../../lib/libSIP-VENDOR$(DBGSUFFIX).a \
    ../../lib/libSIP-VENDOR$(DBGSUFFIX).so


#
# get the rules
#
include $(VENDOR_ROOT)/config.rules
