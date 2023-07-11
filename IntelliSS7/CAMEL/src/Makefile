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
#  ID: $Id: Makefile,v 9.1.86.1.10.1 2014/02/17 09:53:48 millayaraja Exp $
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


#
# Switch according to version
#
ifeq ($(TARGET),CAP-V1)

include cap_v1_cpp_targets

endif

ifeq ($(TARGET),CAP-V2)

include cap_v2_cpp_targets

endif

ifeq ($(TARGET),CAP-V3)

include cap_v3_cpp_targets

endif

ifeq ($(TARGET),CAP-V4)

include cap_v4_cpp_targets

endif

ifneq ($(TARGET),)

CXXFLAGS := $(ASNRTCXXFLAGS) -I../include -I../include/itu -UANSI -DCCITT \
          -I../../TCAP/include -I../../SCCP/include -I../../MTP3/include \
          -I../../MTP2/include -I../../common/include/asn-cpp

CXXOBJS := cap_cpp.o $(CXXOBJS)

all: $(CXXLIBTARGET) $(CXXSOLIBTARGET) $(PRINTTARGET)


$(CXXSRCSAUX) $(CXXHDRSAUX): $(CXXSRCASN)
	$(ASNCC) $(ASNCCFLAGS) $(CXXSRCASN)
	$(MV) $(CXXHDRSAUX) ../include/itu

$(CXXLIBTARGET): cap_init.o $(CXXOBJS) 
	$(CXXAR) $(CXXARFLAGS) $(CXXLIBTARGET) $(CXXOBJS) cap_init.o
	sh ./generate

$(CXXSOLIBTARGET): $(CXXOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(CXXSOLIBTARGET) $(CXXOBJS) $(NOWHOLEARCHIVE)

$(PRINTTARGET): print.o $(CXXLIBTARGET)
	$(CXX) $(CXXSHAREDARFLAGS) $(PRINTTARGET) \
    print.o $(CXXSOLIBTARGET) ../../common/lib/libASN++$(DBGSUFFIX).so

clean:
	$(RM) -r    $(CXXOBJS) $(CXXLIBTARGET) $(CXXOBJSAUX) $(CXXSRCSAUX) \
                $(CXXSOLIBTARGET) $(PRINTTARGET) *.err .depend
	for file in $(CXXHDRSAUX);			\
	do					\
		$(RM) -f ../include/itu/$$file;	\
	done

#
# get the rules
#
include $(ITS_ROOT)/config.rules

#
# Don't build if not CCITT
#
endif
endif

all:

clean:

