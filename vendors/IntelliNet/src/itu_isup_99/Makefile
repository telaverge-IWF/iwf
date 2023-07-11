#
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
#  ID: $Id: Makefile,v 1.2 2006/01/09 06:44:52 omayor Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 1.2  2006/01/09 06:44:52  omayor
# LOG: Added support for ITU ISUP 99.(skatta)
# LOG:
#
############################################################################

#
# get the vars
#
include $(VENDOR_ROOT)/config.vars

CFLAGS :=  $(CFLAGS) \
          -I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
	  -I$(ITS_ROOT)/SNMM/include -I$(ITS_ROOT)/SLTM/include \
	  -I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/common/include \
	  -I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/ISUP/include/itu \
	  -I../../include -I../../include/itu -DINCLUDE_CODEC

OBJS	=itu-isup_99.o                \
         itu-idle_itu_99.o            \
         itu-wait_in_acm_itu_99.o     \
         itu-wait_in_anm_itu_99.o     \
         itu-rcvd_in_anm_itu_99.o     \
         itu-wait_in_rlc_itu_99.o     \
         itu-wait_in_res_itu_99.o     \
         itu-wait_out_acm_itu_99.o    \
         itu-wait_out_anm_itu_99.o    \
         itu-sent_out_anm_itu_99.o    \
         itu-wait_out_rlc_itu_99.o    \
         itu-wait_out_res_itu_99.o    \
         itu-wait_in_cot_itu_99.o     \
         itu-wait_cot_report_itu_99.o \
         itu-wait_out_rel_itu_99.o    \
         itu-wait_out_rsc_itu_99.o    \
         itu-wait_out_gra_itu_99.o

#
# PROTOCOL type
#
ifeq ($(PROTOCOL),CCITT)
all: ../../lib/libITU_ISUP_99$(DBGSUFFIX).a \
     ../../lib/libITU_ISUP_99$(DBGSUFFIX).so
else
all:
endif

../../lib/libITU_ISUP_99$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../lib/libITU_ISUP_99$(DBGSUFFIX).a $(OBJS)

../../lib/libITU_ISUP_99$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../lib/libITU_ISUP_99$(DBGSUFFIX).so \
		$(OBJS)

ifeq ($(PROTOCOL),CCITT)
clean:
	$(RM) $(OBJS) \
		../../lib/libITU_ISUP_99$(DBGSUFFIX).a \
		../../lib/libITU_ISUP_99$(DBGSUFFIX).so
else
clean:
endif

#
# get the rules
#
include $(VENDOR_ROOT)/config.rules
