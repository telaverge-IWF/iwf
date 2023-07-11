############################################################################
#                                                                          #
#     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
# $Id: Makefile,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
#
# $Log: Makefile,v $
# Revision 9.1  2005/03/23 12:54:27  cvsadmin
# Begin PR6.5
#
# Revision 1.2  2005/03/23 09:41:22  cvsadmin
# PR6.4.2 sources propagated to Current.
#
# Revision 1.1.2.3.6.2  2004/01/27 14:30:59  sjaddu
# Changes for active-backup configuration.
#
# Revision 1.1.2.3.6.1  2004/01/05 10:01:25  sjaddu
# Merged code from tcs isup branch.
#
# Revision 1.1.2.3.2.6  2003/11/03 04:58:30  sjaddu
# Added denug suffix for exe.
#
# Revision 1.1.2.3.2.5  2003/10/31 06:03:23  sjaddu
# memset added before getnext event.
#
# Revision 1.1.2.3.2.4  2003/10/15 09:06:51  akumar
# Modified to accomodate both ANSI and ITU variants.
#
# Revision 1.1.2.3.2.3  2003/10/10 14:34:58  sjaddu
# Added compile time flag for transport.
#
# Revision 1.1.2.3.2.2  2003/09/25 09:49:18  akumar
# Updated Makefile.
#
# Revision 1.1.2.3.2.1  2003/08/29 09:46:45  akumar
# Added Few Flags to work in redundancy mode.
#
# Revision 1.1.2.3  2003/06/27 07:53:31  sjaddu
# Update makefile.
#
# Revision 1.1.2.2  2003/06/18 08:15:38  tsanthosh
# Added SCTP libs.
#
# Revision 1.1.2.1  2003/06/05 05:43:46  sjaddu
# Added first revision of files for isupserver.
#
#
############################################################################


#
# get the vars
#
include	$(ITS_ROOT)/config.vars

WHAT_TRANSPORT=ISUP_O_SS7

ifeq ($(WHAT_TRANSPORT),ISUP_O_SCTP)
#SCTPLIBS:=-lUAL$(DBGSUFFIX)
#-l$(PROTOCOL)-M3UA$(DBGSUFFIX)
endif


DEFINES:=$(DEFINES) -D$(WHAT_TRANSPORT) 

CFLAGS:=$(CFLAGS) -g -I./include -DUNIX -DUSE_HEAP -DSOLARIS -D$(PROTOCOL)\
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
       -lCORE$(DBGSUFFIX) \
       -lSUPPORT$(DBGSUFFIX) \
       -l$(PROTOCOL)-ISUP$(DBGSUFFIX)

ifeq ($(PROTOCOL),ANSI)
VARLIBS=-lANSI_GENERIC_92$(DBGSUFFIX)
else
VARLIBS=-lITU_GENERIC_93$(DBGSUFFIX)
endif

ELIBS:= -L$(ITS_ROOT)/common/lib  \
       -L$(ITS_ROOT)/tools/lib \
       -L$(ITS_ROOT)/MTP3/lib  \
       -L$(ITS_ROOT)/ISUP/lib  \
       -L$(ITS_ROOT)/SCCP/lib  \
       -L$(ITS_ROOT)/TCAP/lib  \
       -L$(ITS_ROOT)/SLTM/lib  \
       -L$(ITS_ROOT)/SNMM/lib  \
       -L$(VENDOR_ROOT)/IntelliNet/lib \
       -lDSM-GCS$(DBGSUFFIX) \
       -lGCS-CLIENT$(DBGSUFFIX) \
       -lDRIVER$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       -lVFrame$(DBGSUFFIX) \
       -lm \
       -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
       $(VARLIBS) $(SCTPLIBS) -lthread -lsocket -lnsl -lmtmalloc

NMSLIBS:= -L$(VENDOR_ROOT)/nms/lib \
          -L/opt/nmstx/lib         \
          -L/opt/nms/lib           \
          -lcta -lctal -lctacl -lcpi \
          -lss7mapi -lhmiapi -lhmimgr



OBJS:= servermain.o serverimpl.o serverlayer.o 
LIBOBJS:= 


# Restrict the user to give explicit targets
all: ../bin/run_ISUP_$(PROTOCOL)$(DBGSUFFIX)

../bin/run_ISUP_$(PROTOCOL)$(DBGSUFFIX): $(OBJS) $(LIBOBJS)
		       	     $(CC) $(CFLAGS) -o \
			     $@ $(OBJS) $(LIBOBJS) $(ELIBS) $(NMSLIBS) -ldl -lrt

clean:
	$(RM) $(OBJS) ../bin/run_ISUP_$(PROTOCOL)$(DBGSUFFIX) 

#
# get the rules
#
include	$(ITS_ROOT)/config.rules
