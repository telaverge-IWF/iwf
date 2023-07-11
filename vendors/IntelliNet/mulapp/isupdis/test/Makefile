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
# $Id: Makefile,v 1.1 2005/07/05 11:33:46 mmanikandan Exp $
#
# $Log: Makefile,v $
# Revision 1.1  2005/07/05 11:33:46  mmanikandan
# ISUP Distributed test code.
#
#
############################################################################


#
# get the vars
#
include	$(ITS_ROOT)/config.vars

DEFINES:=$(DEFINES) -DITU_ISUP_97

CFLAGS:=$(CFLAGS) -I./include \
	    -I$(ITS_ROOT)/common/include    \
        -I$(VENDOR_ROOT)/IntelliNet/include    \
        -I$(ITS_ROOT)/MTP2/include      \
        -I$(ITS_ROOT)/MTP3/include      \
	    -I$(ITS_ROOT)/SCCP/include      \
        -I$(ITS_ROOT)/ISUP/include      \
        -I$(ITS_ROOT)/TCAP/include 

LIBS:= -L$(ITS_ROOT)/common/lib  \
       -L$(ITS_ROOT)/ISUP/lib \
       -L$(VENDOR_ROOT)/IntelliNet/lib \
       -lDSM-STUB$(DBGSUFFIX) \
       -lDSM-GCS$(DBGSUFFIX) \
       -lGCS-CLIENT$(DBGSUFFIX) \
       -lDRIVER$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       -lVFrame$(DBGSUFFIX) \
       -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
       -l$(PROTOCOL)-ISUP$(DBGSUFFIX)

ifeq ($(PROTOCOL),CCITT)
LIBS:= $(LIBS) -lITU_GENERIC_93$(DBGSUFFIX) \
       -lITU_ISUP_97$(DBGSUFFIX)
endif

ifeq ($(PROTOCOL),ANSI)
LIBS:= $(LIBS) -lANSI_GENERIC_92$(DBGSUFFIX) \
       -lANSI_ISUP_95$(DBGSUFFIX)
endif

OBJS:= sendISUPMsg.o printISUPMsg.o readISUPMsg.o

LIBOBJS:= ftest.o

# Restrict the user to give explicit targets
all: ISUPDIS-$(PROTOCOL)$(DBGSUFFIX) \
         libISUPDIS-$(PROTOCOL)$(DBGSUFFIX).so

libISUPDIS-$(PROTOCOL)$(DBGSUFFIX).so: $(LIBOBJS) $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) $@ $(LIBOBJS) $(OBJS)

ISUPDIS-$(PROTOCOL)$(DBGSUFFIX): main.o $(FROM)printCic.o \
                              libISUPDIS-$(PROTOCOL)$(DBGSUFFIX).so
	$(CC) $(CFLAGS) -o $@ main.o printCic.o \
           -L. $(LIBS) -lISUPDIS-$(PROTOCOL)$(DBGSUFFIX) \
           $(SYSLIBS) $(SOCKLIBS) $(THREADLIBS)

clean:
	$(RM) $(LIBOBJS) libISUPDIS-$(PROTOCOL)$(DBGSUFFIX).so
	$(RM) main.o $(OBJS) $(FROM)printCic.o ISUPDIS-$(PROTOCOL)$(DBGSUFFIX)
#
# get the rules
#
include	$(ITS_ROOT)/config.rules
