################################################################################
#                                                                              #
#      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.       #
#              Manufactured in the United States of America.                   #
#        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.          #
#                                                                              #
#     This product and related documentation is protected by copyright and     #
#     distributed under licenses restricting its use, copying, distribution    #
#     and decompilation.  No part of this product or related documentation     #
#     may be reproduced in any form by any means without prior written         #
#     authorization of IntelliNet Technologies and its licensors, if any.      #
#                                                                              #
#     RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the        #
#     government is subject to restrictions as set forth in subparagraph       #
#     (c)(1)(ii) of the Rights in Technical Data and Computer Software         #
#     clause at DFARS 252.227-7013 and FAR 52.227-19.                          #
#                                                                              #
################################################################################
#                                                                              #
# CONTRACT: Internal                                                           #
#                                                                              #
################################################################################
#
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:51:46 cvsadmin Exp $
#
################################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

#
# Don't build if not CCITT
#
ifeq ($(PROTOCOL),CCITT)

OBJS=test_codec_main.o
        
SRCS=test_codec_main.c
        
ITS_LIBS = -lINAP-CS1$(DBGSUFFIX) \
	   -lASN_V2$(DBGSUFFIX) \
	   -lCORE$(DBGSUFFIX) -lSUPPORT$(DBGSUFFIX) -lCORE$(DBGSUFFIX) 

LDFLAGS := $(LDFLAGS) -L$(ITS_ROOT)/common/lib -L$(ITS_ROOT)/INAP/lib

CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/common/include/asn-c \
          -I$(ITS_ROOT)/INAP/include/itu

all: test_codec$(DBGSUFFIX)

test_codec$(DBGSUFFIX): $(OBJS)
	$(CC) $(CFLAGS) \
        $(LDFLAGS) -o test_codec$(DBGSUFFIX) $(OBJS) \
        $(ITS_LIBS) $(SOCKLIBS) $(THREADLIBS)

clean:
	$(RM) $(OBJS) test_codec$(DBGSUFFIX) *.err .depend
            
#
# get the rules
#
include $(ITS_ROOT)/config.rules

#
# Don't build if not CCITT
#
else

all:

clean:

endif
