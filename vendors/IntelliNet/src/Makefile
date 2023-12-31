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
#  ID: $Id: Makefile,v 9.11.28.1.4.1 2013/11/18 11:41:40 jsarvesh Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.11.28.1.4.1  2013/11/18 11:41:40  jsarvesh
# LOG: Iwf_Productization Changes done for Dynamic Sigtran Configuration
# LOG:
# LOG: Revision 9.11.28.1  2012/12/18 16:11:58  brajappa
# LOG: Initial IWF branch creation and linux compilation changes
# LOG:
# LOG: Revision 9.11  2008/06/18 07:47:57  nvijikumar
# LOG: USE_ITU_TCAP define for COP and COT support
# LOG:
# LOG: Revision 9.10  2008/06/17 08:15:07  ssingh
# LOG: cleaning of TCAP lin and 16bit
# LOG:
# LOG: Revision 9.9  2008/06/17 06:43:00  nvijikumar
# LOG: Updated for ITU over TTC and ITU over PRC support (split Stacks).
# LOG: ACC-CG-SDS-SS7-V1.0.02::D7030,D7040, D7070,D7080
# LOG:
# LOG: Revision 9.8  2008/06/12 12:51:49  nvijikumar
# LOG: Renaming from COT to CPOT (CCITT prime - 16bit)
# LOG: ACC-CG-SDS-SS7-V1.0.02::ID:: D6030
# LOG:
# LOG: Revision 9.7  2008/06/11 12:00:10  ssingh
# LOG: Reference Document:: ACC-CG-SDS-SS7-V1.0.02
# LOG: D9070::ANSI+ITU TCAP over ANSI/ITU SCCP
# LOG:
# LOG: Revision 9.6  2008/06/06 06:00:09  ssingh
# LOG: VARIANTS uncommented
# LOG:
# LOG: Revision 9.5  2008/06/04 11:23:07  ssingh
# LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
# LOG:
# LOG: Revision 9.4  2007/02/01 13:25:18  yranade
# LOG: 2nd round of merge
# LOG:
# LOG: Revision 9.1.10.5  2007/10/15 10:59:31  ssingh
# LOG: Makefile pure ANSI build uncommented
# LOG:
# LOG: Revision 9.1.10.4  2007/10/05 10:32:13  mshanmugam
# LOG: ported CPOT support changes from B-0100SL-CBSG-RST16 branch
# LOG:
# LOG: Revision 9.1.10.3  2007/07/27 13:08:46  kramesh
# LOG: Ported the 16 bit pc changes from B-0100SL-CBSG-RST16 branch.
# LOG: Ref SDS : ACC-FemtoBSG-16BitPC-SDS-GEN-V1.0
# LOG:
# LOG: Revision 9.1.10.2  2007/01/25 10:59:33  randresol
# LOG: Modify PRC stack to allow it to run in parallel with ITU, TTC or ANSI stacks
# LOG:
# LOG: Revision 9.1.10.1  2006/12/23 10:05:36  randresol
# LOG: Modifications to allow TTC and ITU stacks to run in parallel
# LOG:
# LOG: Revision 9.3  2006/01/09 06:35:25  omayor
# LOG: Added support for ITU ISUP 99.(skatta)
# LOG:
# LOG: Revision 9.2  2005/07/05 11:43:25  mmanikandan
# LOG: isup distributed files are added.
# LOG:
# LOG: Revision 9.1  2005/03/23 12:54:28  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.5  2005/03/21 13:53:28  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.3.26.3  2005/02/18 11:36:15  dsatish
# LOG: Commit after TTC related Changes
# LOG:
# LOG: Revision 7.3.26.2  2005/01/31 09:32:45  dsatish
# LOG: ANSI over TTC, ANSI over PRC split stack changes merged in DVLP branch.
# LOG:
# LOG: Revision 7.3.26.1  2004/12/17 03:57:43  randresol
# LOG: Add JAPAN variant implementation
# LOG:
# LOG: Revision 7.3.20.1  2004/10/25 20:34:11  randresol
# LOG: Start Japan SS7 Implementation
# LOG:
# LOG: Revision 7.3  2003/02/04 07:36:35  yranade
# LOG: Manual TCAP Codec Integration.
# LOG:
# LOG: Revision 7.2  2002/11/05 22:51:11  omayor
# LOG: Coding standards!
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.8  2002/08/16 22:07:08  mmiers
# LOG: Include China variant.
# LOG:
# LOG: Revision 6.7  2002/08/01 15:57:46  ssharma
# LOG: Merge from ISUP_PR7 branch.
# LOG:
# LOG: Revision 6.6.2.6  2002/07/12 14:05:26  hbalimid
# LOG: CQM moved to CSC.
# LOG:
# LOG: Revision 6.6.2.5  2002/07/05 14:31:07  ssingh
# LOG: Traces fixed.
# LOG:
# LOG: Revision 6.6.2.4  2002/07/01 22:24:42  hbalimid
# LOG: Updated with ISUP ANSI 92 & 95.
# LOG:
# LOG: Revision 6.6.2.3  2002/07/01 20:19:48  hbalimid
# LOG: Added ansi_generic_92 to variants.
# LOG:
# LOG: Revision 6.6.2.2  2002/06/28 23:35:32  hbalimid
# LOG: corrected ansi_generic_95
# LOG:
# LOG: Revision 6.6.2.1  2002/06/28 23:33:04  hbalimid
# LOG: Added ansi_generic_95 to VARIANTS.
# LOG:
# LOG: Revision 6.6  2002/05/22 15:42:26  fkong
# LOG: Add ANSI ISUP files to build.
# LOG:
# LOG: Revision 6.5  2002/05/20 16:18:58  sjaddu
# LOG: Merge from PR6.
# LOG:
# LOG: Revision 6.4  2002/04/12 19:14:53  yranade
# LOG: Removed unwanted object files.
# LOG:
# LOG: Revision 6.3  2002/03/20 20:06:44  mmiers
# LOG: Move the ASNC library to VFrame (as on UNIX).
# LOG:
# LOG: Revision 6.2  2002/03/12 23:37:17  mmiers
# LOG: Standardize alarms.
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.26.2.2  2002/05/13 22:57:11  hbalimid
# LOG: updated with ITU ISUP 97 variant
# LOG:
# LOG: Revision 5.26.2.1  2002/04/18 18:51:19  ssanyal
# LOG: New file added for first shot at ANSI ISUP: ansi-isup_context.c
# LOG:
# LOG: Revision 5.26  2002/02/13 23:43:23  mmiers
# LOG: Get the make right.
# LOG:
# LOG: Revision 5.25  2002/02/13 23:36:43  mmiers
# LOG: Build the variants better.
# LOG:
# LOG: Revision 5.24  2002/02/13 23:24:24  mmiers
# LOG: Debugging
# LOG:
# LOG: Revision 5.23  2002/02/13 18:28:32  mmiers
# LOG: Finish off the ISUP integration.  Still need to add CHINA
# LOG: variant lib.
# LOG:
# LOG: Revision 5.22  2002/02/09 00:17:16  mmiers
# LOG: Dead code elimination.
# LOG:
# LOG: Revision 5.21  2002/02/06 23:43:59  mmiers
# LOG: Continue ISUP integration.
# LOG:
# LOG: Revision 5.20  2002/02/01 22:12:26  mmiers
# LOG: ISUP integration
# LOG:
# LOG: Revision 5.19  2002/02/01 21:57:12  mmiers
# LOG: Missing include, corrections.
# LOG:
# LOG: Revision 5.18  2002/02/01 20:07:30  ssharma
# LOG: Start work on IntelliNet ISUP stack.
# LOG:
# LOG: Revision 5.17  2002/01/11 21:37:28  mmiers
# LOG: Build cleanup
# LOG:
# LOG: Revision 5.16  2002/01/10 16:50:07  mmiers
# LOG: Switch to refcounting transports.
# LOG:
# LOG: Revision 5.15  2002/01/02 21:18:02  mmiers
# LOG: Fix the build system
# LOG:
# LOG: Revision 5.14  2001/12/18 19:17:47  mmiers
# LOG: Build on solaris
# LOG:
# LOG: Revision 5.13  2001/12/17 21:09:22  mmiers
# LOG: Finish the vendor framework.  Works with NMS MTP2.
# LOG:
# LOG: Revision 5.12  2001/12/17 00:15:35  mmiers
# LOG: Get this building on UNIX
# LOG:
# LOG: Revision 5.11  2001/11/09 21:19:38  mmiers
# LOG: Try to actually get this right?
# LOG:
# LOG: Revision 5.10  2001/11/09 21:13:54  mmiers
# LOG: Extra backslash
# LOG:
# LOG: Revision 5.9  2001/11/09 20:30:21  mmiers
# LOG: stack as shared lib.
# LOG:
# LOG: Revision 5.8  2001/10/06 23:54:18  mmiers
# LOG: Missed a few things yesterday.  Fix makefile as well.
# LOG:
# LOG: Revision 5.7  2001/09/17 23:49:02  mmiers
# LOG: Syntax build.
# LOG:
# LOG: Revision 5.6  2001/08/23 19:49:02  mmiers
# LOG: Missing file.
# LOG:
# LOG: Revision 5.5  2001/08/23 19:48:34  mmiers
# LOG: Again.
# LOG:
# LOG: Revision 5.4  2001/08/23 19:48:13  mmiers
# LOG: reformat
# LOG:
# LOG: Revision 5.3  2001/08/23 19:47:03  mmiers
# LOG: Add itu mtp3 files.
# LOG:
# LOG: Revision 5.2  2001/08/21 23:42:38  mmiers
# LOG: Double include of ansi-mtp3.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:26  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.2  2001/08/08 00:44:26  mmiers
# LOG: Cross platform build.
# LOG:
# LOG: Revision 4.1  2001/05/04 16:22:02  mmiers
# LOG: Start PR5.
# LOG:
# LOG: Revision 3.3  2001/01/03 17:18:26  mmiers
# LOG: Script to batch build
# LOG:
# LOG: Revision 3.2  2000/09/01 20:56:48  mmiers
# LOG:
# LOG:
# LOG: Debugging zero copy.
# LOG:
# LOG: Revision 3.1  2000/08/16 00:09:24  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.2  2000/07/21 14:28:01  labuser
# LOG:
# LOG: Make it compile on solaris.
# LOG:
# LOG: Revision 2.1  2000/02/02 15:54:20  mmiers
# LOG:
# LOG:
# LOG: Modify stack startup to class initialize.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:31:20  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.25  1999/10/06 17:12:16  mmiers
# LOG:
# LOG:
# LOG: Commit minor type fix to dha, Makefile for split stack
# LOG:
# LOG: Revision 1.24  1999/10/06 17:05:27  mmiers
# LOG:
# LOG:
# LOG: Get our split stack configuration to build.
# LOG:
# LOG: Revision 1.23  1999/10/06 16:59:10  mmiers
# LOG:
# LOG:
# LOG: Update for split stack build.
# LOG:
# LOG: Revision 1.22  1999/08/26 23:44:51  labuser
# LOG:
# LOG:
# LOG: Alter GTT to include original PC (if any) and SSN (if any).
# LOG:
# LOG: Revision 1.21  1999/08/07 01:26:44  mmiers
# LOG:
# LOG:
# LOG: Add stubs into UNIX build.
# LOG:
# LOG: Revision 1.20  1999/08/04 01:35:05  mmiers
# LOG:
# LOG:
# LOG: Update this to correctly reflect the sources.
# LOG:
# LOG: Revision 1.19  1999/08/04 00:53:26  mmiers
# LOG:
# LOG:
# LOG: Correct the build target to not remove .c files on clean.
# LOG:
# LOG: Revision 1.18  1999/05/25 00:30:23  mmiers
# LOG:
# LOG:
# LOG: Update for UNIX build.
# LOG:
# LOG: Revision 1.17  1999/05/24 20:43:48  mmiers
# LOG:
# LOG:
# LOG: Remove the codec, add in the rest of CCITT TCAP.
# LOG:
# LOG: Revision 1.16  1999/03/23 21:03:51  mmiers
# LOG:
# LOG:
# LOG: Update so that it builds on UNIX.
# LOG:
# LOG: Revision 1.15  1999/02/26 04:10:21  mmiers
# LOG:
# LOG:
# LOG: Compile with CC.
# LOG:
# LOG: Revision 1.14  1999/02/13 04:22:38  mmiers
# LOG:
# LOG:
# LOG: Add specification file for ITU TCAP.
# LOG:
# LOG: Revision 1.13  1998/11/18 00:35:11  jrao
# LOG: Changed Library Suffix (LIBSUFFIX) to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.12  1998/11/17 16:54:32  jrao
# LOG: Added facility to produce Release and Debug versions of the library.
# LOG:
# LOG: Revision 1.11  1998/11/13 02:49:41  mmiers
# LOG: Do SST.
# LOG:
# LOG: Revision 1.10  1998/10/22 14:45:34  mmiers
# LOG: Forgot to add sccp_cvt to build for UNIX.
# LOG:
# LOG: Revision 1.9  1998/10/21 20:31:16  mmiers
# LOG: Update unix build for automatic ASN generation.
# LOG:
# LOG: Revision 1.8  1998/10/19 00:40:36  mmiers
# LOG: Strengthen for PCLASS_3
# LOG:
# LOG: Revision 1.7  1998/10/15 03:39:28  mmiers
# LOG: Get the names right (source), make sure GTT is present (Makefile).
# LOG:
# LOG: Revision 1.6  1998/10/02 14:50:45  mmiers
# LOG: Clean this up a bit
# LOG:
# LOG: Revision 1.5  1998/09/28 20:42:12  jrao
# LOG: Add MTP3 source
# LOG:
# LOG: Revision 1.4  1998/09/26 02:54:48  mmiers
# LOG: Update for Linux, modified filenames in Makefile.
# LOG:
# LOG: Revision 1.3  1998/09/17 21:36:06  jrao
# LOG: Connection-oriented control was missing from the OBJ list.
# LOG:
# LOG: Revision 1.2  1998/06/30 01:51:01  mmiers
# LOG: Update for Linux build.
# LOG:
# LOG: Revision 1.1  1998/06/23 01:45:28  mmiers
# LOG: Move things around for Solaris builds.
# LOG:
#
############################################################################

#
# get the vars
#
include $(VENDOR_ROOT)/config.vars

vLib = VENDOR
coaVLib = libCCITT-ANSI-VENDOR
ifeq ($(CCITT_USE_16_BIT_PC), yes)
ifneq ($(USE_CPOT_STACK), yes)
vLib = 16BIT-VENDOR
coaVLib = libCCITT-16BIT-ANSI-VENDOR
endif
endif

CFLAGS :=  $(CFLAGS) \
          -I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
	  -I$(ITS_ROOT)/SNMM/include -I$(ITS_ROOT)/SLTM/include \
	  -I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/common/include \
	  -I$(EACC_ROOT)/cmapi/common \
	  -I../include -I../include/ansi -I../include/itu \
          -DINCLUDE_CODEC -DTCAP_CODEC

COMMONOBJS  =
ANSIMTP3OBJS=ansi-mtp3.o     ansi-mgmt.o   ansi-mtp3_ifc.o ansi-slm.o \
             ansi-slt.o      ansi-smh.o    ansi-srm.o      ansi-stm.o \
             ansi-mtp3_alarms.o
ANSIISUPOBJS=ansi-isup.o     ansi-isup_ifc.o  ansi-isup_data.o \
             ansi-isup_context.o  ansi-sprc.o ansi-isup_alarms.o ansi-isup_dis.o
ANSISCCPOBJS=ansi-sccp.o     ansi-sclc.o   ansi-scoc.o     ansi-scrc.o \
             ansi-scmg.o     ansi-sccp_gtt.o ansi-sccp_ifc.o \
             ansi-sccp_alarms.o
ANSITCAPOBJS=ansi-tcap_ifc.o ansi-cmp.o  ansi-tpcpi.o  ansi-trp.o \
             ansi-tcap.o     ansi-tcap_context.o \
             ansi-tcap_alarms.o
ITUMTP3OBJS=itu-mtp3.o      itu-mgmt.o     itu-mtp3_ifc.o  itu-slm.o \
            itu-slt.o       itu-smh.o      itu-srm.o       itu-stm.o \
            itu-mtp3_alarms.o
TTCMTP3OBJS=ttc-mtp3.o      ttc-mgmt.o     ttc-mtp3_ifc.o  ttc-slm.o \
            ttc-slt.o       ttc-smh.o      ttc-srm.o       ttc-stm.o \
            ttc-mtp3_alarms.o

PRCMTP3OBJS=prc-mtp3.o      prc-mgmt.o     prc-mtp3_ifc.o  prc-slm.o \
            prc-slt.o       prc-smh.o      prc-srm.o       prc-stm.o \
            prc-mtp3_alarms.o

ITUISUPOBJS=itu-isup.o      itu-isup_ifc.o itu-isup_data.o  \
            itu-isup_context.o  itu-sprc.o itu-isup_alarms.o itu-isup_dis.o
ITUSCCPOBJS=itu-sccp.o      itu-sclc.o     itu-scoc.o      itu-scrc.o \
            itu-scmg.o      itu-sccp_gtt.o itu-sccp_ifc.o \
            itu-sccp_alarms.o
TTCSCCPOBJS=ttc-sccp.o      ttc-sclc.o     ttc-scoc.o      ttc-scrc.o \
            ttc-scmg.o      ttc-sccp_gtt.o ttc-sccp_ifc.o \
            ttc-sccp_alarms.o

PRCSCCPOBJS=prc-sccp.o      prc-sclc.o     prc-scoc.o      prc-scrc.o \
            prc-scmg.o      prc-sccp_gtt.o prc-sccp_ifc.o \
            prc-sccp_alarms.o

ITUTCAPOBJS=itu-tcap_ifc.o  itu-tcap.o     itu-tco.o       itu-dha.o \
            itu-cco.o       itu-tsm.o      itu-tcap_context.o \
            itu-tcap_alarms.o
TTCTCAPOBJS=ttc-tcap_ifc.o  ttc-tcap.o     ttc-tco.o       ttc-dha.o \
            ttc-cco.o       ttc-tsm.o      ttc-tcap_context.o \
            ttc-tcap_alarms.o

PRCTCAPOBJS=prc-tcap_ifc.o  prc-tcap.o     prc-tco.o       prc-dha.o \
            prc-cco.o       prc-tsm.o      prc-tcap_context.o \
            prc-tcap_alarms.o

ANSIOBJS=ansi.o
ITUOBJS=itu.o
PRCOBJS=prc.o
TTCOBJS=ttc.o

VARIANTS=   itu_generic_93 itu_isup_97 itu_isup_99 itu_china ansi_generic_92 ansi_isup_95

#
# libs For Multiple TCAPs (ITU+ANSI) over CCITT/ANSI SCCP 
#
ifeq ($(DUAL_TCAP), yes)

CFLAGS:=$(CFLAGS) -DDUAL_TCAP
TOBJ=itu-ansi-tcap.o

ifeq ($(SCCP_PROT),$(PROTOCOL))

ifeq ($(PROTOCOL), CCITT)
all: ../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).a \
     ../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).so
../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).a: $(COMMONOBJS) $(TOBJ) \
               $(ITUTCAPOBJS)
	$(AR) $(ARFLAGS) ../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).a \
                $(COMMONOBJS) $(TOBJ) \
                $(ITUTCAPOBJS)
../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).so: $(COMMONOBJS) $(TOBJ) \
               $(ITUTCAPOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).so \
                $(COMMONOBJS) $(TOBJ) \
                $(ITUTCAPOBJS) $(NOWHOLEARCHIVE)
endif

ifeq ($(PROTOCOL),ANSI)
all: ../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).a \
     ../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).so
../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).a: $(COMMONOBJS) $(TOBJ) \
               $(ANSITCAPOBJS)
	$(AR) $(ARFLAGS) ../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).a \
                $(COMMONOBJS) $(TOBJ) \
                $(ANSITCAPOBJS)
../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).so: $(COMMONOBJS) $(TOBJ) \
               $(ANSITCAPOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).so \
                $(COMMONOBJS) $(TOBJ) \
                $(ANSITCAPOBJS) $(NOWHOLEARCHIVE)
endif

clean:
	$(RM) $(COMMONOBJS) \
                ../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).a \
                ../lib/lib$(PROTOCOL)-TCAP-VENDOR$(DBGSUFFIX).so \
                $(TOBJ) $(COMMONOBJS) \
                $(ANSITCAPOBJS) $(ITUTCAPOBJS)
endif

else

#
# SCCP type
#

ifeq ($(PROTOCOL),PRC)
CFLAGS := $(CFLAGS) -DPRC
all: ../lib/libPRC-VENDOR$(DBGSUFFIX).a \
     ../lib/libPRC-VENDOR$(DBGSUFFIX).so
else
ifeq ($(PROTOCOL),TTC)
CFLAGS := $(CFLAGS) -DTTC
all: ../lib/libTTC-VENDOR$(DBGSUFFIX).a \
     ../lib/libTTC-VENDOR$(DBGSUFFIX).so
else
ifeq ($(SCCP_PROT),$(PROTOCOL))
ifneq ($(USE_CPOT_STACK), yes)
all: ../lib/libCCITT-$(vLib)$(DBGSUFFIX).a \
     ../lib/libCCITT-$(vLib)$(DBGSUFFIX).so \
     ../lib/libANSI-VENDOR$(DBGSUFFIX).a \
     ../lib/libANSI-VENDOR$(DBGSUFFIX).so \
     variants
endif
else

ifeq ($(PROTOCOL),CCITT)
ifeq ($(SCCP_PROT),ANSI)
all: ../lib/$(coaVLib)$(DBGSUFFIX).a \
     ../lib/$(coaVLib)$(DBGSUFFIX).so \
     variants
endif
endif

ifeq ($(PROTOCOL),CCITT)
ifeq ($(SCCP_PROT),TTC)
CFLAGS:=$(CFLAGS) -DUSE_ITU_TCAP
all: ../lib/libCCITT-TTC-VENDOR$(DBGSUFFIX).a \
     ../lib/libCCITT-TTC-VENDOR$(DBGSUFFIX).so \
     variants
endif
endif

ifeq ($(PROTOCOL),CCITT)
ifeq ($(SCCP_PROT),PRC)
CFLAGS:=$(CFLAGS) -DUSE_ITU_TCAP
all: ../lib/libCCITT-PRC-VENDOR$(DBGSUFFIX).a \
     ../lib/libCCITT-PRC-VENDOR$(DBGSUFFIX).so \
     variants
endif
endif

ifeq ($(PROTOCOL),ANSI)
ifeq ($(SCCP_PROT),CCITT)
all: ../lib/libANSI-CCITT-VENDOR$(DBGSUFFIX).a \
     ../lib/libANSI-CCITT-VENDOR$(DBGSUFFIX).so \
     variants
endif
endif

ifeq ($(PROTOCOL),ANSI)
ifeq ($(SCCP_PROT),TTC)
all: ../lib/libANSI-TTC-VENDOR$(DBGSUFFIX).a \
     ../lib/libANSI-TTC-VENDOR$(DBGSUFFIX).so
endif
endif

ifeq ($(PROTOCOL),ANSI)
ifeq ($(SCCP_PROT),PRC)
all: ../lib/libANSI-PRC-VENDOR$(DBGSUFFIX).a \
     ../lib/libANSI-PRC-VENDOR$(DBGSUFFIX).so

endif
endif

endif
endif
endif

ifeq ($(CCITT_USE_16_BIT_PC), yes)
ifeq ($(USE_CPOT_STACK), yes)
all: ../lib/libCPOT-VENDOR$(DBGSUFFIX).a \
     ../lib/libCPOT-VENDOR$(DBGSUFFIX).so
endif
endif

../lib/libANSI-VENDOR$(DBGSUFFIX).a: $(COMMONOBJS) $(ANSIOBJS) \
                $(ANSIMTP3OBJS) $(ANSIISUPOBJS) $(ANSISCCPOBJS) \
                $(ANSITCAPOBJS)
	$(AR) $(ARFLAGS) ../lib/libANSI-VENDOR$(DBGSUFFIX).a \
		$(COMMONOBJS) $(ANSIOBJS) \
                $(ANSIMTP3OBJS) $(ANSIISUPOBJS) $(ANSISCCPOBJS) \
                $(ANSITCAPOBJS)

../lib/libCCITT-$(vLib)$(DBGSUFFIX).a: $(COMMONOBJS) $(ITUOBJS) \
               $(ITUMTP3OBJS) $(ITUISUPOBJS) $(ITUSCCPOBJS) \
               $(ITUTCAPOBJS)
	$(AR) $(ARFLAGS) ../lib/libCCITT-$(vLib)$(DBGSUFFIX).a \
		$(COMMONOBJS) $(ITUOBJS) \
                $(ITUMTP3OBJS) $(ITUISUPOBJS) $(ITUSCCPOBJS) \
                $(ITUTCAPOBJS)

#remove ITUISUPOBJS
../lib/libPRC-VENDOR$(DBGSUFFIX).a: $(COMMONOBJS) $(PRCOBJS) \
               $(PRCMTP3OBJS) $(PRCSCCPOBJS) \
               $(PRCTCAPOBJS)
	$(AR) $(ARFLAGS) ../lib/libPRC-VENDOR$(DBGSUFFIX).a \
		$(COMMONOBJS) $(PRCOBJS) \
                $(PRCMTP3OBJS) $(PRCSCCPOBJS) \
                $(PRCTCAPOBJS)

# remove TTCISUPOBJS
../lib/libTTC-VENDOR$(DBGSUFFIX).a: $(COMMONOBJS) $(TTCOBJS) \
               $(TTCMTP3OBJS) $(TTCSCCPOBJS) \
               $(TTCTCAPOBJS)
	$(AR) $(ARFLAGS) ../lib/libTTC-VENDOR$(DBGSUFFIX).a \
		$(COMMONOBJS) $(TTCOBJS) \
                $(TTCMTP3OBJS) $(TTCSCCPOBJS) \
                $(TTCTCAPOBJS)


../lib/$(coaVLib)$(DBGSUFFIX).a: $(COMMONOBJS) $(ANSIOBJS) \
                $(ANSIMTP3OBJS) $(ANSIISUPOBJS) $(ANSISCCPOBJS) $(ITUTCAPOBJS)
	$(AR) $(ARFLAGS) ../lib/$(coaVLib)$(DBGSUFFIX).a \
		$(COMMONOBJS) $(ANSIOBJS) \
                $(ANSIMTP3OBJS) $(ANSIISUPOBJS) $(ANSISCCPOBJS) \
                $(ITUTCAPOBJS)

# To support ITU-16 bit SCCP over TTC MTP3
../lib/libCPOT-VENDOR$(DBGSUFFIX).a: $(ITUOBJS) $(TTCMTP3OBJS) \
                 $(ITUSCCPOBJS) $(ITUTCAPOBJS)
	$(AR) $(ARFLAGS) ../lib/libCPOT-VENDOR$(DBGSUFFIX).a \
		$(ITUOBJS) $(TTCMTP3OBJS) \
		$(ITUSCCPOBJS) $(ITUTCAPOBJS)

../lib/libANSI-CCITT-VENDOR$(DBGSUFFIX).a: $(COMMONOBJS) $(ITUOBJS) \
                $(ITUMTP3OBJS) $(ITUISUPOBJS) $(ITUSCCPOBJS) \
                $(ANSITCAPOBJS)
	$(AR) $(ARFLAGS) ../lib/libANSI-CCITT-VENDOR$(DBGSUFFIX).a \
		$(COMMONOBJS) $(ITUOBJS) \
                $(ITUMTP3OBJS) $(ITUISUPOBJS) $(ITUSCCPOBJS) \
                $(ANSITCAPOBJS)

../lib/libANSI-TTC-VENDOR$(DBGSUFFIX).a: $(COMMONOBJS) $(TTCOBJS) \
		$(TTCMTP3OBJS) $(ITUISUPOBJS) $(ITUSCCPOBJS) \
		$(ANSITCAPOBJS)
	$(AR) $(ARFLAGS) ../lib/libANSI-TTC-VENDOR$(DBGSUFFIX).a \
                $(COMMONOBJS) $(TTCOBJS) \
		$(TTCMTP3OBJS) $(ITUISUPOBJS) $(ITUSCCPOBJS) \
		$(ANSITCAPOBJS)

# $(ITUISUPOBJS)
../lib/libANSI-PRC-VENDOR$(DBGSUFFIX).a: $(COMMONOBJS) $(PRCOBJS) \
		$(PRCMTP3OBJS) $(PRCSCCPOBJS) \
		$(ANSITCAPOBJS)
	$(AR) $(ARFLAGS) ../lib/libANSI-PRC-VENDOR$(DBGSUFFIX).a \
		$(COMMONOBJS) $(PRCOBJS) \
		$(PRCMTP3OBJS)  $(PRCSCCPOBJS) \
		$(ANSITCAPOBJS)

../lib/libANSI-VENDOR$(DBGSUFFIX).so: $(COMMONOBJS) $(ANSIOBJS) \
                $(ANSIMTP3OBJS) $(ANSIISUPOBJS) $(ANSISCCPOBJS) \
                $(ANSITCAPOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/libANSI-VENDOR$(DBGSUFFIX).so \
		$(COMMONOBJS) $(ANSIOBJS) \
                $(ANSIMTP3OBJS) $(ANSIISUPOBJS) $(ANSISCCPOBJS) \
                $(ANSITCAPOBJS)

../lib/libCCITT-$(vLib)$(DBGSUFFIX).so: $(COMMONOBJS) $(ITUOBJS) \
               $(ITUMTP3OBJS) $(ITUISUPOBJS) $(ITUSCCPOBJS) \
               $(ITUTCAPOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/libCCITT-$(vLib)$(DBGSUFFIX).so \
		$(COMMONOBJS) $(ITUOBJS) \
                $(ITUMTP3OBJS) $(ITUISUPOBJS) $(ITUSCCPOBJS) \
                $(ITUTCAPOBJS)

# remove $(ITUISUPOBJS) 
../lib/libPRC-VENDOR$(DBGSUFFIX).so: $(COMMONOBJS) $(PRCOBJS) \
               $(PRCMTP3OBJS)  $(PRCSCCPOBJS) \
               $(PRCTCAPOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/libPRC-VENDOR$(DBGSUFFIX).so \
		$(COMMONOBJS) $(PRCOBJS) \
                $(PRCMTP3OBJS) $(PRCISUPOBJS) $(PRCSCCPOBJS) \
                $(PRCTCAPOBJS)

../lib/libTTC-VENDOR$(DBGSUFFIX).so: $(COMMONOBJS) $(TTCOBJS) \
               $(TTCMTP3OBJS)  $(TTCSCCPOBJS) \
               $(TTCTCAPOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/libTTC-VENDOR$(DBGSUFFIX).so \
		$(COMMONOBJS) $(TTCOBJS) \
                $(TTCMTP3OBJS)  $(TTCSCCPOBJS) \
                $(TTCTCAPOBJS)


../lib/$(coaVLib)$(DBGSUFFIX).so: $(COMMONOBJS) $(ANSIOBJS) \
                $(ANSIMTP3OBJS) $(ANSIISUPOBJS) $(ANSISCCPOBJS) \
                $(ITUTCAPOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/$(coaVLib)$(DBGSUFFIX).so \
		$(COMMONOBJS) $(ANSIOBJS) \
                $(ANSIMTP3OBJS) $(ANSIISUPOBJS) $(ANSISCCPOBJS) \
                $(ITUTCAPOBJS)

#To support 16bit ITU SCCP over TTC MTP3
../lib/libCPOT-VENDOR$(DBGSUFFIX).so: $(ITUOBJS) $(TTCMTP3OBJS) \
                 $(ITUSCCPOBJS) $(ITUTCAPOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/libCPOT-VENDOR$(DBGSUFFIX).so \
		$(ITUOBJS) $(TTCMTP3OBJS) \
		$(ITUSCCPOBJS) $(ITUTCAPOBJS)

../lib/libANSI-CCITT-VENDOR$(DBGSUFFIX).so: $(COMMONOBJS) $(ITUOBJS) \
                $(ITUMTP3OBJS) $(ITUISUPOBJS) $(ITUSCCPOBJS) \
                $(ANSITCAPOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/libANSI-CCITT-VENDOR$(DBGSUFFIX).so \
		$(COMMONOBJS) $(ITUOBJS) \
                $(ITUMTP3OBJS) $(ITUISUPOBJS) $(ITUSCCPOBJS) \
                $(ANSITCAPOBJS)
../lib/libANSI-TTC-VENDOR$(DBGSUFFIX).so: $(COMMONOBJS) $(TTCOBJS) \
                $(TTCMTP3OBJS) $(ITUISUPOBJS) $(TTCSCCPOBJS) \
                $(ANSITCAPOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/libANSI-TTC-VENDOR$(DBGSUFFIX).so \
                $(COMMONOBJS) $(TTCOBJS) \
                $(TTCMTP3OBJS) $(ITUISUPOBJS) $(TTCSCCPOBJS) \
                $(ANSITCAPOBJS)

# remove $(ITUISUPOBJS)
../lib/libANSI-PRC-VENDOR$(DBGSUFFIX).so: $(COMMONOBJS) $(PRCOBJS) \
                $(PRCMTP3OBJS) $(PRCSCCPOBJS) \
                $(ANSITCAPOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/libANSI-PRC-VENDOR$(DBGSUFFIX).so \
                $(COMMONOBJS) $(PRCOBJS) \
                $(PRCMTP3OBJS) $(PRCSCCPOBJS) \
                $(ANSITCAPOBJS)

#To support ITU TCAP over TTC/PRC SCCP
../lib/libCCITT-TTC-VENDOR$(DBGSUFFIX).so: $(COMMONOBJS) $(TTCOBJS) \
		$(TTCMTP3OBJS) $(TTCISUPOBJS) $(TTCSCCPOBJS) \
		$(ITUTCAPOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/libCCITT-TTC-VENDOR$(DBGSUFFIX).so \
		$(COMMONOBJS) $(TTCOBJS) \
		$(TTCMTP3OBJS) $(TTCISUPOBJS) $(TTCSCCPOBJS) \
		$(ITUTCAPOBJS)

../lib/libCCITT-PRC-VENDOR$(DBGSUFFIX).so: $(COMMONOBJS) $(PRCOBJS) \
		$(PRCMTP3OBJS) $(PRCISUPOBJS) $(PRCSCCPOBJS) \
		$(ITUTCAPOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/libCCITT-PRC-VENDOR$(DBGSUFFIX).so \
		$(COMMONOBJS) $(PRCOBJS) \
		$(PRCMTP3OBJS) $(PRCISUPOBJS) $(PRCSCCPOBJS) \
		$(ITUTCAPOBJS)

../lib/libCCITT-TTC-VENDOR$(DBGSUFFIX).a: $(COMMONOBJS) $(TTCOBJS) \
		$(TTCMTP3OBJS) $(TTCSCCPOBJS) \
		$(ITUTCAPOBJS)
		$(AR) $(ARFLAGS) ../lib/libCCITT-TTC-VENDOR$(DBGSUFFIX).a \
		$(COMMONOBJS) $(TTCOBJS) \
		$(TTCMTP3OBJS)  $(TTCSCCPOBJS) \
		$(ITUTCAPOBJS)

../lib/libCCITT-PRC-VENDOR$(DBGSUFFIX).a: $(COMMONOBJS) $(PRCOBJS) \
		$(PRCMTP3OBJS) $(PRCSCCPOBJS) \
		$(ITUTCAPOBJS)
		$(AR) $(ARFLAGS) ../lib/libCCITT-PRC-VENDOR$(DBGSUFFIX).a \
		$(COMMONOBJS) $(PRCOBJS) \
		$(PRCMTP3OBJS)  $(PRCSCCPOBJS) \
		$(ITUTCAPOBJS)

variants:
	for dir in $(VARIANTS);						\
	do								\
		(cd $$dir && $(MAKE) PROTOCOL=$(PROTOCOL) 		\
				     DEBUG_BUILD=$(DEBUG_BUILD));	\
	done

clean:
	for dir in $(VARIANTS);						\
	do								\
		(cd $$dir && $(MAKE) PROTOCOL=$(PROTOCOL)		\
				     DEBUG_BUILD=$(DEBUG_BUILD) clean);	\
	done
	$(RM) $(COMMONOBJS) \
		../lib/libANSI-VENDOR$(DBGSUFFIX).a \
		../lib/libCCITT-$(vLib)$(DBGSUFFIX).a \
		../lib/$(coaVLib)$(DBGSUFFIX).a \
		../lib/libCPOT-VENDOR$(DBGSUFFIX).a \
		../lib/libANSI-CCITT-VENDOR$(DBGSUFFIX).a \
		../lib/libPRC-VENDOR$(DBGSUFFIX).a \
		../lib/libTTC-VENDOR$(DBGSUFFIX).a \
		../lib/libCCITT-TTC-VENDOR$(DBGSUFFIX).a \
		../lib/libCCITT-PRC-VENDOR$(DBGSUFFIX).a \
		../lib/libCCITT-TCAP-VENDOR$(DBGSUFFIX).a \
		../lib/libANSI-TCAP-VENDOR$(DBGSUFFIX).a \
		../lib/libCCITT-16BIT-VENDOR$(DBGSUFFIX).a \
		../lib/libANSI-VENDOR$(DBGSUFFIX).so \
		../lib/libCCITT-$(vLib)$(DBGSUFFIX).so \
		../lib/$(coaVLib)$(DBGSUFFIX).so \
		../lib/libCPOT-VENDOR$(DBGSUFFIX).so \
		../lib/libANSI-CCITT-VENDOR$(DBGSUFFIX).so \
		../lib/libPRC-VENDOR$(DBGSUFFIX).so \
		../lib/libTTC-VENDOR$(DBGSUFFIX).so \
		../lib/libANSI-TCAP-VENDOR$(DBGSUFFIX).so \
		../lib/libCCITT-TCAP-VENDOR$(DBGSUFFIX).so \
		../lib/libCCITT-TTC-VENDOR$(DBGSUFFIX).so \
		../lib/libCCITT-PRC-VENDOR$(DBGSUFFIX).so \
		../lib/libCCITT-TCAP-VENDOR$(DBGSUFFIX).so \
		../lib/libANSI-TCAP-VENDOR$(DBGSUFFIX).so \
		../lib/libCCITT-16BIT-VENDOR$(DBGSUFFIX).so \
		$(ITUMTP3OBJS) $(ITUISUPOBJS) $(ITUSCCPOBJS) $(ITUTCAPOBJS) \
		$(ANSIMTP3OBJS) $(ANSIISUPOBJS) $(ANSISCCPOBJS) $(ANSITCAPOBJS) \
		$(TTCMTP3OBJS) $(TTCISUPOBJS) $(TTCSCCPOBJS) $(TTCTCAPOBJS) \
		$(PRCMTP3OBJS) $(PRCISUPOBJS) $(PRCSCCPOBJS) $(PRCTCAPOBJS) \
                $(ANSIOBJS) $(ITUOBJS) $(TTCOBJS) $(PRCOBJS)

endif

#
# get the rules
#
include $(VENDOR_ROOT)/config.rules
