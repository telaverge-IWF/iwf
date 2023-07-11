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
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:54:28 cvsadmin Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.1  2005/03/23 12:54:28  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 1.9  2005/03/21 13:53:27  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 1.8.2.1  2004/12/28 14:04:09  mkrishna
# LOG: SIP code propagated from Current Branch
# LOG:
# LOG: Revision 1.8  2004/06/28 07:42:35  sjaddu
# LOG: Load test added and SIP_StackHandle also added.
# LOG:
# LOG: Revision 1.7  2004/06/24 09:14:35  akumar
# LOG: Changed makefile to work for linux.
# LOG:
# LOG: Revision 1.6  2004/05/27 15:17:43  sjaddu
# LOG: chanegs made for follow me application.
# LOG:
# LOG: Revision 1.5  2004/04/23 06:21:04  sjaddu
# LOG: Added debug console utility for test app.
# LOG:
# LOG: Revision 1.4  2004/04/21 06:15:26  akumar
# LOG: Modified.
# LOG:
# LOG: Revision 1.3  2004/04/01 09:26:29  akumar
# LOG: FT going on.
# LOG:
# LOG: Revision 1.2  2004/03/30 15:53:56  sjaddu
# LOG: Added new for app lib
# LOG:
# LOG: Revision 1.1  2004/03/19 06:05:38  sjaddu
# LOG: Added first revsion for sip, work in progress.
# LOG:
############################################################################

#
# get the vars
#
include $(VENDOR_ROOT)/config.vars

PROTOCOL=ANSI

CFLAGS := $(CFLAGS) \
          -I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
      -I$(ITS_ROOT)/SNMM/include -I$(ITS_ROOT)/SLTM/include \
      -I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
      -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/common/include \
      -I$(ITS_ROOT)/SIP/include \
      -I../../include -I../../include/ansi -DINCLUDE_CODEC

OBJS= sip_test.o

SIP_LIBS=-lSIP-VENDORD -lSIPD

LIBS:= -L ./ -L ../../lib  \
       -L $(ITS_ROOT)/common/lib \
       -L $(ITS_ROOT)/tools/lib \
       -L $(ITS_ROOT)/SIP/lib  \
       -L $(VENDOR_ROOT)/IntelliNet/lib \
       -L $(VENDOR_ROOT)/IntelliNet/lib \
       -lDRIVER$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       $(SIP_LIBS) 

ifeq ($(PLATFORM),linux)
LIBS:= $(LIBS) -lpthread -lnsl -lrt 
else
LIBS:= $(LIBS) -lthread -lnsl -lrt -lmtmalloc -lsocket
endif

#
# PROTOCOL type
#
all:libSIP-APP$(DBGSUFFIX).so sip_exe

sip_exe: $(OBJS)
	$(CC) $(CFLAGS) -o \
            $@ $(OBJS) $(LIBS) -lSIP-APP$(DBGSUFFIX)  -ldl -lrt

LIB_OBJS=app_lib.o app_handl_msg.o app_send_msg.o load.o

libSIP-APP$(DBGSUFFIX).so: $(LIB_OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) libSIP-APP$(DBGSUFFIX).so $(LIB_OBJS)


followme:libFollowMe$(DBGSUFFIX).so followMe$(DBGSUFFIX)


FOLLOWME_LIB_OBJS=followme_app_lib.o 

libFollowMe$(DBGSUFFIX).so: $(FOLLOWME_LIB_OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) libFollowMe$(DBGSUFFIX).so $(FOLLOWME_LIB_OBJS)

FOLLOWME_OBJS=followme_app_main.o

followMe$(DBGSUFFIX): $(FOLLOWME_OBJS)
	$(CC) $(CFLAGS) -o \
            $@ $(FOLLOWME_OBJS) $(LIBS) -lFollowMe$(DBGSUFFIX)  -ldl -lrt

clean:
	$(RM) -rf *.o *.so sip_exe followMe$(DBGSUFFIX)


#
# get the rules
#
include $(VENDOR_ROOT)/config.rules
