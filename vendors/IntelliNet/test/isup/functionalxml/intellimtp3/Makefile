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
# $Id: Makefile,v 9.4 2008/05/11 05:09:14 kramesh Exp $
#
# $Log: Makefile,v $
# Revision 9.4  2008/05/11 05:09:14  kramesh
# Added NOWHOLEARCHIVE flag for ES4.0 compilation.
#
# Revision 9.3  2006/01/09 06:40:06  omayor
# Added support for ITU ISUP 99.(skatta)
#
# Revision 9.2  2005/04/05 09:53:57  adutta
# commit for commit permission.
#
# Revision 9.1  2005/03/23 12:55:08  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:54:21  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.4.10.1  2004/02/11 08:36:28  sjaddu
# Changes done for testing active-stand by config
#
# Revision 7.4  2002/12/17 15:28:17  sjaddu
# Changes for Adax.
#
# Revision 7.3  2002/11/25 04:10:09  sjaddu
# Don mot need NMS mtp3 libriary.
#
# Revision 7.2  2002/10/30 10:24:06  sjaddu
# Added ANSI95 flag.
#
# Revision 7.1  2002/08/26 22:10:39  mmiers
# Begin PR6.2
#
# Revision 1.5  2002/08/02 16:35:56  ssingh
# modified for ANSI95
#
# Revision 1.4  2002/06/27 18:56:36  hbalimid
# common Makefile for ANSI and ITU
#
# Revision 1.3  2002/06/22 20:43:35  hbalimid
# variant specific makefile for test application
#
# Revision 1.2  2002/05/20 15:58:49  sjaddu
# Merge from PR6, remove unwanted directories.
#
# Revision 1.1.2.4  2002/05/15 21:33:01  hbalimid
# Updated to let 97 variant compile
#
# Revision 1.1.2.3  2002/05/09 18:40:21  labuser
# Merge from ISUP_APR_19_2002 to PR6.
#
# Revision 1.1.2.2.2.1  2002/04/24 22:12:12  labuser
# modified to get CIC status
#
# Revision 1.1.2.2  2002/04/12 22:33:36  hbalimid
# updated to accomodate the new directory structure
#
# Revision 1.1.2.1  2002/04/12 20:22:28  hbalimid
# for ftest; ISUP with IntelliNet MTP3 and NMS MTP2
#
# Revision 1.1.2.1  2002/04/12 19:55:59  hbalimid
# Changed to accomodate multiple vendors at layer2
#
# Revision 1.1.2.1  2002/04/11 01:50:56  hbalimid
# Baseline for ISUP functional test - organized per MTP3 vendor
#
#
############################################################################


#
# get the vars
#
include	$(ITS_ROOT)/config.vars
#

DEFINES:=$(DEFINES) -DTRANSPORT_SS7 -DANSI_ISUP_95

FROM:= ../

CFLAGS:=$(CFLAGS) -g -I./include -DUNIX -DSOLARIS -D$(PROTOCOL) -DANSI_ISUP_95\
	-I$(ITS_ROOT)/common/include    \
        -I$(VENDOR_ROOT)/IntelliNet/include    \
        -I$(ITS_ROOT)/MTP2/include      \
        -I$(ITS_ROOT)/MTP3/include      \
	-I$(ITS_ROOT)/SCCP/include      \
        -I$(ITS_ROOT)/ISUP/include      \
        -I$(ITS_ROOT)/TCAP/include      \
	-I$(ITS_ROOT)/tools/include

NMSCFLAGS:= -I$(VENDOR_ROOT)/nms/include

SBECFLAGS:= -I$(VENDOR_ROOT)/sbe/include

ADAXCFLAGS:= -I$(VENDOR_ROOT)/adax/include

ifeq ($(PROTOCOL),ANSI)
VARLIBS=-lANSI_GENERIC_92$(DBGSUFFIX) -lANSI_ISUP_95$(DBGSUFFIX) -lm
else
VARLIBS=-lITU_GENERIC_93$(DBGSUFFIX)
endif

LIBS:= -L$(ITS_ROOT)/common/lib  \
       -L$(ITS_ROOT)/tools/lib \
       -L$(ITS_ROOT)/MTP3/lib  \
       -L$(ITS_ROOT)/ISUP/lib  \
       -L$(ITS_ROOT)/SCCP/lib  \
       -L$(ITS_ROOT)/TCAP/lib  \
       -L$(ITS_ROOT)/SLTM/lib  \
       -L$(ITS_ROOT)/SNMM/lib  \
       -L$(VENDOR_ROOT)/IntelliNet/lib \
       -lDSM-STUB$(DBGSUFFIX) \
       -lDSM-GCS$(DBGSUFFIX) \
       -lGCS-CLIENT$(DBGSUFFIX) \
       -lDRIVER$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       -lVFrame$(DBGSUFFIX) \
       -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
       -l$(PROTOCOL)-ISUP$(DBGSUFFIX) \
       -lITS-REDUNDANCY$(DBGSUFFIX) \
       $(VARLIBS) -lpthread -lnsl

NMSLIBS:=
#NMSLIBS:= -L$(VENDOR_ROOT)/nms/lib \
          -L/opt/nmstx/lib         \
          -L/opt/nms/lib           \
          -lcta -lctal -lctacl -lcpi \
          -lss7mapi -lhmiapi -lhmimgr

SBELIBS:= -L$(VENDOR_ROOT)/sbe/lw/lib \
          -lSBEVendor$(DBGSUFFIX) -lsbe

ADAXLIBS:= -L$(VENDOR_ROOT)/adax/lib \
          -lANSI-ADAXVendor$(DBGSUFFIX)


OBJS:= $(FROM)sendISUPMsg.o $(FROM)printISUPMsg.o $(FROM)readISUPMsg.o

LIBOBJS:= ftest.o

# Restrict the user to give explicit targets
all:
	@echo "\nPlease specify one of the following targets:"
	@echo "nmsmtp2 sbemtp2 adaxmtp2\n"
	@echo "Note: To build packages, use \"make pkg\"\n"

# ISUP with IntelliNet MTP3 and NMS MTP2
nmsmtp2: nmsmtp2/ftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX) \
         nmsmtp2/libftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX).so

nmsmtp2/libftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX).so: $(LIBOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	$@ $(LIBOBJS) $(NOWHOLEARCHIVE)

nmsmtp2/ftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX): $(OBJS) $(LIBOBJS) main.o $(FROM)printCic.o
	$(CC) $(CFLAGS) $(NMSCFLAGS) -o $@ $(OBJS) $(LIBOBJS) main.o $(FROM)printCic.o \
	$(LIBS) $(NMSLIBS) $(SOCKLIBS) $(THREADLIBS) -ldl -lrt


# ISUP with IntelliNet MTP3 and SBE MTP2
sbemtp2: sbemtp2/ftest-intelli3-sbe2-$(PROTOCOL)$(DBGSUFFIX) \
         sbemtp2/libftest-intelli3-sbe2-$(PROTOCOL)$(DBGSUFFIX).so

sbemtp2/libftest-intelli3-sbe2-$(PROTOCOL)$(DBGSUFFIX).so: $(LIBOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	$@ $(LIBOBJS) $(NOWHOLEARCHIVE)

sbemtp2/ftest-intelli3-sbe2-$(PROTOCOL)$(DBGSUFFIX): $(OBJS) main.o $(FROM)printCic.o
	$(CC) $(CFLAGS) $(SBEFLAGS) -o $@ $(OBJS) main.o $(FROM)printCic.o \
	$(LIBS) $(SBELIBS) $(SOCKLIBS) $(THREADLIBS) -ldl -lrt


# ISUP with IntelliNet MTP3 and ADAX MTP2
adaxmtp2: adaxmtp2/ftest-intelli3-adax2-$(PROTOCOL)$(DBGSUFFIX) \
         adaxmtp2/libftest-intelli3-adax2-$(PROTOCOL)$(DBGSUFFIX).so

adaxmtp2/libftest-intelli3-adax2-$(PROTOCOL)$(DBGSUFFIX).so: $(LIBOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	$@ $(LIBOBJS) $(NOWHOLEARCHIVE)

adaxmtp2/ftest-intelli3-adax2-$(PROTOCOL)$(DBGSUFFIX): $(OBJS) main.o $(FROM)printCic.o
	$(CC) $(CFLAGS) $(SBEFLAGS) -o $@ $(OBJS) main.o $(FROM)printCic.o \
	$(LIBS) $(ADAXLIBS) $(SOCKLIBS) $(THREADLIBS) -ldl -lrt

# All cleans here

clean:
	@echo "\nPlease specify one of the following targets:"
	@echo "nmsclean sbeclean adaxclean\n"

nmsclean:
	$(RM) $(LIBOBJS) nmsmtp2/libftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX).so
	$(RM) main.o $(OBJS) $(FROM)printCic.o nmsmtp2/ftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX)

sbeclean:
	$(RM) $(LIBOBJS) sbemtp2/libftest-intelli3-sbe2-$(PROTOCOL)$(DBGSUFFIX).so
	$(RM) main.o $(OBJS) $(FROM)printCic.o sbemtp2/ftest-intelli3-sbe2-$(PROTOCOL)$(DBGSUFFIX)

adaxclean:
	$(RM) $(LIBOBJS) adaxmtp2/libftest-intelli3-adax2-$(PROTOCOL)$(DBGSUFFIX).so
	$(RM) main.o $(OBJS) $(FROM)printCic.o adaxmtp2/ftest-intelli3-adax2-$(PROTOCOL)$(DBGSUFFIX)
#
# get the rules
#
include	$(ITS_ROOT)/config.rules
