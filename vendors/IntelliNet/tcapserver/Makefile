############################################################################
#                                                                          #
#     Copyright 2003 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
# $Id: Makefile,v 9.1 2005/03/23 12:55:02 cvsadmin Exp $
#
# $Log: Makefile,v $
# Revision 9.1  2005/03/23 12:55:02  cvsadmin
# Begin PR6.5
#
# Revision 1.1  2003/10/07 12:35:47  sswami
# Make file for TCAP server [Multiple applications binding]
#
#
#
############################################################################


#
# get the vars
#
include	$(ITS_ROOT)/config.vars

DEFINES:=$(DEFINES) 

CFLAGS:=$(CFLAGS) -g -I./include -DUNIX -DSOLARIS -D$(PROTOCOL)\
	-I$(ITS_ROOT)/common/include    \
        -I$(VENDOR_ROOT)/IntelliNet/include    \
        -I$(ITS_ROOT)/MTP2/include      \
        -I$(ITS_ROOT)/MTP3/include      \
	-I$(ITS_ROOT)/SCCP/include      \
        -I$(ITS_ROOT)/ISUP/include      \
        -I$(ITS_ROOT)/TCAP/include      \
        -I../include \
	-I$(ITS_ROOT)/tools/include

LIBS:= -L$(ITS_ROOT)/common/lib  \
       -L$(ITS_ROOT)/ISUP/lib  \
       -L$(ITS_ROOT)/TCAP/lib  \
       -lCORE$(DBGSUFFIX) \
       -lSUPPORT$(DBGSUFFIX) \
       -l$(PROTOCOL)-ISUP$(DBGSUFFIX) \
       -l$(PROTOCOL)-TCAP$(DBGSUFFIX)

ELIBS:= -L$(ITS_ROOT)/common/lib  \
       -L$(ITS_ROOT)/tools/lib \
       -L$(ITS_ROOT)/MTP3/lib  \
       -L$(ITS_ROOT)/ISUP/lib  \
       -L$(ITS_ROOT)/SCCP/lib  \
       -L$(ITS_ROOT)/TCAP/lib  \
       -L$(ITS_ROOT)/SLTM/lib  \
       -L$(ITS_ROOT)/SNMM/lib  \
       -L$(VENDOR_ROOT)/IntelliNet/lib \
       -lDSM-STUB$(DBGSUFFIX) \
       -lDRIVER$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       -lVFrame$(DBGSUFFIX) \
       -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
       $(VARLIBS) -lthread -lsocket -lnsl

#NMSLIBS:= -L$(VENDOR_ROOT)/nms/lib \
          -L/opt/nmstx/lib         \
          -L/opt/nms/lib           \
          -lcta -lctal -lctacl -lcpi \
          -lss7mapi -lhmiapi -lhmimgr

SCTPLIBS:=-lUAL$(DBGSUFFIX) -l$(PROTOCOL)-M3UA$(DBGSUFFIX) -lUAL$(DBGSUFFIX)


OBJS:= tcap_servermain.o tcap_serverimpl.o tcap_serverlayer.o 
LIBOBJS:= 


# Restrict the user to give explicit targets
all: ../bin/run_TCAP

../bin/run_TCAP: $(OBJS) $(LIBOBJS)
			$(CC) $(CFLAGS) -o \
			$@ $(OBJS) $(LIBOBJS) $(ELIBS) $(NMSLIBS) -ldl -lrt -lmtmalloc

clean:
	$(RM) $(OBJS) ../bin/run_TCAP 

#
# get the rules
#
include	$(ITS_ROOT)/config.rules
