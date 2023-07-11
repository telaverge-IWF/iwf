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
############################################################################
#
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:52:43 cvsadmin Exp $
# LOG: Revision 6.2  2002/06/27 15:15:49  pmandal
# LOG: Remove c targets and dependencies
# LOG:
# LOG: Revision 1.2.2.1  2001/11/28 21:15:07  hdivoux
# LOG: Re-added to PR5. Update for new compilation flags.
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

#
# Don't build if not ANSI
#
ifeq ($(PROTOCOL),ANSI)


#
# Switch according to version
#

ifeq ($(TARGET),ANSI-WIN)

include ansi_win_cpp_targets

CXXSRCASN=./win_lrf.asn

CXXLIBTARGET=../lib/libWIN++$(DBGSUFFIX).a

CXXSOLIBTARGET=$(ITS_ROOT)/WIN/lib/libWIN++$(DBGSUFFIX).so

PRINTTARGET=../lib/libWINPrint$(DBGSUFFIX).so

CXXFLAGS := $(ASNRTCXXFLAGS) -I../../common/include -I../include/ansi -DANSI \
          -I../../TCAP/include -I../../SCCP/include -I../../MTP3/include \
          -I../../MTP2/include -I../../common/include/asn-cpp

all: $(CXXLIBTARGET) $(CXXSOLIBTARGET) $(PRINTTARGET)


$(CXXSRCSAUX) $(CXXHDRSAUX): $(CXXSRCASN)
	$(ASNCC) $(ASNCCFLAGS) $(CXXSRCASN)
	$(MV) $(CXXHDRSAUX) ../include/ansi

$(CXXLIBTARGET): $(CXXOBJS)
	$(CXXAR) $(CXXARFLAGS) $(CXXLIBTARGET) $(CXXOBJS)

$(CXXSOLIBTARGET): $(CXXOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(CXXSOLIBTARGET) $(CXXOBJS)

$(PRINTTARGET): print.o $(CXXSOLIBTARGET)
	$(CXX) $(CXXSHAREDARFLAGS) $(PRINTTARGET) \
        print.o $(CXXSOLIBTARGET) \
        $(ITS_ROOT)/common/lib/libASN++$(DBGSUFFIX).so

clean:
	$(RM) -r    $(CXXOBJS) $(SRCSAUX) $(LIBTARGET) \
                $(CXXLIBTARGET) $(CXXOBJSAUX) $(CXXSRCSAUX) \
                $(CXXSOLIBTARGET) $(PRINTTARGET) *.err .depend
	for file in $(CXXHDRSAUX);			    \
	do					                    \
		$(RM) -f ../include/ansi/$$file;	\
	done

#
# get the rules
#
include $(ITS_ROOT)/config.rules

#
# Don't build if not ANSI
#
endif
endif

all:

clean:

