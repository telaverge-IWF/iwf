################################################################################
#                                                                              #
#      Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.       #
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
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:54:21 cvsadmin Exp $
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

CXXOBJS=main.o                                \
        test13_feature_result.o               \
        test13_alert_code.o                   \
        test13_group_information.o            \
        test13_carrier_digits.o               \
        test13_local_termination.o            \
        test13_destination_digits.o           \
        test13_pstn_termination.o             \
        test13_electronic_serial_number.o     \
        test13_termination_list.o             \
        test13_feature_request_rrl.o
        
CXXSRCS=main.cpp                                \
        test13_feature_result.cpp               \
        test13_alert_code.cpp                   \
        test13_group_information.cpp            \
        test13_carrier_digits.cpp               \
        test13_local_termination.cpp            \
        test13_destination_digits.cpp           \
        test13_pstn_termination.cpp             \
        test13_electronic_serial_number.cpp     \
        test13_termination_list.cpp             \
        test13_feature_request_rrl.cpp

CPPSRCSAUX=test13_feature_result.cpp            \
        test13_alert_code.cpp                   \
        test13_group_information.cpp            \
        test13_carrier_digits.cpp               \
        test13_local_termination.cpp            \
        test13_destination_digits.cpp           \
        test13_pstn_termination.cpp             \
        test13_electronic_serial_number.cpp     \
        test13_termination_list.cpp             \
        test13_feature_request_rrl.cpp

        
ITS_LIBS = -lASN++$(DBGSUFFIX) -lCORE++$(DBGSUFFIX) \
	       -lSUPPORT++$(DBGSUFFIX) -lCORE++$(DBGSUFFIX) 

LINK_FLAG = -L$(ITS_ROOT)/common/lib

CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/common/include/asn-cpp

all: test13$(DBGSUFFIX)

test13$(DBGSUFFIX): $(CPPSRCSAUX) $(CXXOBJS)
	$(CXX) -g $(LDFLAGS) \
	$(LINK_FLAG) -o test13$(DBGSUFFIX) $(CXXOBJS) \
	$(ITS_LIBS) $(SOCKLIBS) $(THREADLIBS)

$(CPPSRCSAUX): $(ITS_ROOT)/tools/bin/asncc_useful.asn
	$(ITS_ROOT)/tools/bin/asncc_v2$(DBGSUFFIX) -cpp -cppNamespace test13 \
	-u $(ITS_ROOT)/tools/bin/asncc_useful.asn test13.asn

clean:
	$(RM) $(CXXOBJS) test13$(DBGSUFFIX) $(CPPSRCSAUX) *.err .depend
            
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
