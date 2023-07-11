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
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:51:41 cvsadmin Exp $
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

CXXOBJS=test_send_main.o
        
CXXSRCS=test_send_main.cpp
        
ITS_LIBS = -lCORE++$(DBGSUFFIX) \
           -lSUPPORT++$(DBGSUFFIX) -lCORE++$(DBGSUFFIX) \
           -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
	   -lMAP-COMMON++$(DBGSUFFIX) -lMAP-v6++$(DBGSUFFIX) \
	   -l$(PROTOCOL)-TCAP$(DBGSUFFIX) \
	   -l$(PROTOCOL)-SCCP$(DBGSUFFIX) -l$(PROTOCOL)-MTP3$(DBGSUFFIX) \
           -lASN++$(DBGSUFFIX) -lASN$(DBGSUFFIX) \
	   -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) 

LINK_FLAG = -L$(ITS_ROOT)/common/lib -L$(ITS_ROOT)/GSMMAP/lib \
	    -L$(VENDOR_ROOT)/IntelliNet/lib -L$(ITS_ROOT)/TCAP/lib \
	    -L$(ITS_ROOT)/SCCP/lib -L$(ITS_ROOT)/MTP3/lib

CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/common/include/asn-cpp \
          -I$(ITS_ROOT)/GSMMAP/include/itu \
	  -I$(ITS_ROOT)/TCAP/include \
	  -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/MTP3/include \
	  -DUSE_INTELLINET_STACK     \
	  -DUSE_SOCKETS

all: test_send$(DBGSUFFIX)

test_send$(DBGSUFFIX): $(CXXOBJS)
	$(CXX) -g $(LDFLAGS) \
        $(LINK_FLAG) -o test_send$(DBGSUFFIX) $(CXXOBJS) \
        $(ITS_LIBS) $(SOCKLIBS) $(THREADLIBS)

clean:
	$(RM) $(CXXOBJS) test_send$(DBGSUFFIX) *.err .depend
            
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
