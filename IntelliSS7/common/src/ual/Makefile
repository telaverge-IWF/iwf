 ############################################################################
 #                                                                          #
 #     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
 #
 # CONTRACT: INTERNAL
 #
 #  ID: $Id: Makefile,v 9.3.40.1 2013/11/18 11:40:19 jsarvesh Exp $
 #  LOG: $Log: Makefile,v $
 #  LOG: Revision 9.3.40.1  2013/11/18 11:40:19  jsarvesh
 #  LOG: Iwf_Productization Changes done for Dynamic UAL Configuration
 #  LOG:
 #  LOG: Revision 9.3  2008/06/17 07:02:00  ssingh
 #  LOG: More on CPOT (CCITT prime - 16bit PC) compilation
 #  LOG:
 #  LOG: Revision 9.2  2008/05/09 14:48:51  kramesh
 #  LOG: NOWHOLEARCHIVE flag added for ES4.0 compilation.
 #  LOG:
 #  LOG: Revision 9.1  2005/03/23 12:53:47  cvsadmin
 #  LOG: Begin PR6.5
 #  LOG:
 #  LOG: Revision 8.3  2005/03/21 13:52:17  cvsadmin
 #  LOG: PR6.4.2 Source Propagated to Current
 #  LOG:
 #  LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 #  LOG: Begin PR6.2
 #  LOG:
 #  LOG: Revision 6.4  2002/07/09 21:03:12  lbana
 #  LOG: add config manager file
 #  LOG:
 #  LOG: Revision 6.3  2002/07/08 16:11:51  ngoel
 #  LOG: add ual alarms
 #  LOG:
 #  LOG: Revision 6.2  2002/05/14 18:55:09  lbana
 #  LOG: fix compiler errors in macros
 #  LOG:
 #  LOG: Revision 6.1  2002/05/13 20:30:41  lbana
 #  LOG: uals in current starts from here...
 #  LOG:
 #
 #############################################################################

include $(ITS_ROOT)/config.vars

#Ported from ALU branch (CPOT) changes
ifeq ($(CCITT_USE_16_BIT_PC), yes)
AppLib = lib16BIT-UAL$(DBGSUFFIX)
else
AppLib = libUAL$(DBGSUFFIX)
endif

CFLAGS:=$(CFLAGS) -I. -I$(ITS_ROOT)/common/include \
         -I$(ITS_ROOT)/MTP2/include \
         -I$(ITS_ROOT)/MTP3/include \
         -I$(ITS_ROOT)/SCCP/include \
		 -I$(EACC_ROOT)/cmapi/common \
         -D$(PLATFORM)

OBJS = ual_support.o ual.o ual_codec.o ual_asp_mgnt.o ual_route_handler.o \
       ual_layer_mgnt.o ual_rk_mgnt.o ual_sctp_mgnt.o ual_sua_snm.o \
       ual_config_mgnt.o ual_alarms.o

all : ../../lib/$(AppLib).so

../../lib/$(AppLib).so : $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) $@ $(OBJS) $(NOWHOLEARCHIVE)

clean :
	$(RM) $(OBJS) ../../lib/$(AppLib).so

include $(ITS_ROOT)/config.rules

