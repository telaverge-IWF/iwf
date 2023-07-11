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
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:51:47 cvsadmin Exp $
#
############################################################################

include $(ITS_ROOT)/config.vars

ifeq ($(PROTOCOL),CCITT)

all: test_send_engine$(DBGSUFFIX)

ITS_LIBS = -lVFrame$(DBGSUFFIX)          \
	   -lENGINE$(DBGSUFFIX)          \
           -lDISPATCH++$(DBGSUFFIX)      \
           -lDRIVER++$(DBGSUFFIX)        \
           -lCCITT-VENDOR$(DBGSUFFIX)    \
           -lDSM-STUB$(DBGSUFFIX)        \
           -lINAP-ETSI-CS1++$(DBGSUFFIX) \
           -lASN++$(DBGSUFFIX)
                      
CXXOBJS = test_send_engine_main.o \
          test_encode_connect_arg.o \
          test_encode_connect_to_resource_arg.o \
          test_encode_establish_temporary_connection_arg.o \
          test_encode_play_announcement_arg.o \
          test_encode_prompt_and_collect_user_information_arg.o \
          test_encode_send_charging_information_arg.o \
          test_encode_event_report_bcsm_arg.o
 
LDFLAGS := $(LDFLAGS) -L$(ITS_ROOT)/common/lib -L$(ITS_ROOT)/INAP/lib

CFLAGS := $(CFLAGS) -I. -I$(ITS_ROOT)/common/include            \
                        -I$(ITS_ROOT)/common/include/asn-cpp    \
                        -I$(ITS_ROOT)/TCAP/include              \
                        -I$(ITS_ROOT)/ISUP/include              \
                        -I$(ITS_ROOT)/SCCP/include              \
                        -I$(ITS_ROOT)/MTP3/include              \
                        -I$(ITS_ROOT)/MTP2/include              \
                        -I$(ITS_ROOT)/INAP/include/itu

ifeq ($(SS7), yes)
ITS_LIBS:=$(ITS_LIBS) -L$(VENDOR_ROOT)/nms_v3_6/lib \
              -l$(PROTOCOL)-NMSVENDORD \
              -lcta -lcpi -lisupapi -lmtp3api -lhmimgr -lhmiapi
endif

test_send_engine$(DBGSUFFIX): $(CXXOBJS)
	$(CXX) $(LDFLAGS) $(CXXOBJS) -o test_send_engine$(DBGSUFFIX)    \
                    $(OBJS)                                         \
                    $(ITS_LIBS)                                     \
                    $(SOCKLIBS)                                     \
                    $(THREADLIBS)                                   \
                    $(SYSLIBS)
                    

clean:
	$(RM) test_send_engine$(DBGSUFFIX)  \
          $(CXXOBJS) .depend

include $(ITS_ROOT)/config.rules


else

all:
	echo "missing PROTOCOL (must be CCITT)!"

endif


