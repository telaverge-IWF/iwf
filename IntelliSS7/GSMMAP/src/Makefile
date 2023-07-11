################################################################################
#                                                                              #
#   Copyright 2000 - 2002 IntelliNet Technologies, Inc. All Rights Reserved.   #
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
#  ID: $Id: Makefile,v 9.4.30.2 2012/12/20 21:11:06 brajappa Exp $
#
# LOG: >> see end of file.
#
################################################################################

#
# Get the vars.
#
include $(ITS_ROOT)/config.vars

#
# Don't build if not CCITT.
#
ifeq ($(PROTOCOL),CCITT)


#
# Switch according to version or multi-version.
#
ifeq ($(TARGET), MAP-V13)

include map_v13_cpp_targets

else

ifeq ($(TARGET),MAP-REL9)

include map_rel9_cpp_targets

else

ifeq ($(TARGET),MAP-V6-TO-V1)

include map_v6_to_v1_cpp_targets

else

ifeq ($(TARGET),MAP-V8)

include map_v8_cpp_targets

else

ifeq ($(TARGET),MAP-V9)

include map_v9_cpp_targets

else
ifeq ($(TARGET),MAP-V7)

include map_v7_cpp_targets

else

ifeq ($(TARGET),MAP-V6)

include map_v6_cpp_targets

else

ifeq ($(TARGET),MAP-V5)

include map_v5_cpp_targets

else

ifeq ($(TARGET),MAP-V4-TO-V1)

include map_v4_to_v1_cpp_targets

else

ifeq ($(TARGET),MAP-V4)

include map_v4_cpp_targets

else

ifeq ($(TARGET),MAP-V4-JETCELL-VB)

include map_v4_cpp_jetcell_vb_targets

else

ifeq ($(TARGET),MAP-V3)

include map_v3_cpp_targets

else

ifeq ($(TARGET),MAP-V2)

include map_v2_cpp_targets

else

ifeq ($(TARGET),MAP-V1)

include map_v1_cpp_targets

endif
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif

ifneq ($(TARGET),)

#
# Common library for all C++ versions.
#

CXXLIBTARGETCOMMON=../lib/libMAP-COMMON++$(DBGSUFFIX).a

CXXOBJSCOMMON=map_cpp.o
        
CXXSRCSCOMMON=map_cpp.cpp
        
CXXHDRSCOMMON=map_cpp.h



CXXFLAGS := $(ASNRTCXXFLAGS) -I../include -I../include/itu -UANSI -DCCITT \
          -I../../TCAP/include -I../../SCCP/include -I../../MTP3/include \
          -I../../MTP2/include -I../../common/include/asn-cpp

CXXOBJS := map_user_info.o $(CXXOBJS)

all: $(CXXLIBTARGET) $(CXXLIBTARGETCOMMON) $(CXXSOLIBTARGET) $(PRINTTARGET)


$(CXXSRCSAUX) $(CXXHDRSAUX): $(CXXSRCASN)
	$(ASNCC) $(ASNCCFLAGS) $(CXXSRCASN)
	$(MV) $(CXXHDRSAUX) ../include/itu

$(CXXLIBTARGET): $(CXXOBJS) $(CXXHLPOBJS)
	$(CXXAR) $(CXXARFLAGS) $(CXXLIBTARGET) $(CXXOBJS) $(CXXHLPOBJS)
	sh ./generate

$(CXXSOLIBTARGET): $(CXXOBJS) $(CXXHLPOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(CXXSOLIBTARGET) $(CXXOBJS) $(CXXHLPOBJS) $(NOWHOLEARCHIVE)

$(CXXLIBTARGETCOMMON): $(CXXOBJSCOMMON)
	$(CXXAR) $(CXXARFLAGS) $(CXXLIBTARGETCOMMON) $(CXXOBJSCOMMON)

$(PRINTTARGET): print.o $(CXXOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(PRINTTARGET) \
    print.o $(CXXOBJS) ../../common/lib/libASN++$(DBGSUFFIX).so

clean:
	$(RM) -r   $(CXXOBJS) $(CXXHLPOBJS) $(SRCSAUX) $(LIBTARGET) \
                $(CXXLIBTARGET) $(CXXOBJSAUX) $(CXXSRCSAUX) \
                $(CXXLIBTARGETCOMMON) $(CXXOBJSCOMMON) \
                $(CXXSOLIBTARGET) $(PRINTTARGET) *.err .depend           
	for file in $(CXXHDRSAUX);   \
	do					\
		$(RM) -f ../include/itu/$$file;	\
	done

#
# get the rules
#
include $(ITS_ROOT)/config.rules

endif
endif
#
# Don't build if not CCITT
#

all:

clean:






################################################################################
################################################################################
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.4.30.2  2012/12/20 21:11:06  brajappa
# LOG: MAP Release 10 (verison 13) addition
# LOG:
# LOG: Revision 9.4.30.1  2012/12/18 16:11:57  brajappa
# LOG: Initial IWF branch creation and linux compilation changes
# LOG:
# LOG: Revision 9.4.14.1  2010/08/25 08:26:14  haltaf
# LOG: Initial commit for GSMMAP Release 9
# LOG:
# LOG: Revision 9.4  2008/05/01 14:27:06  kramesh
# LOG: Propagated Sigvalue & Starhome Issues 1311 & 1403.Included map_user_info.o.
# LOG:
# LOG: Revision 9.3  2007/01/10 11:14:59  yranade
# LOG: Merge changes from 6.5.3 and Lucent branches
# LOG:
# LOG: Revision 9.2  2005/06/02 13:40:00  adutta
# LOG: Changes for MAP_V8
# LOG:
# LOG: Revision 9.1  2005/03/23 12:51:25  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.6  2005/03/21 13:49:25  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1.46.3  2005/03/01 11:59:37  mmanikandan
# LOG: Modified for CTF.
# LOG:
# LOG: Revision 7.1.46.2  2005/01/31 13:32:32  mmanikandan
# LOG: clean updated with the shared object.
# LOG:
# LOG: Revision 7.1.46.1  2005/01/31 12:07:36  mmanikandan
# LOG: PPrint for MAP-V7
# LOG:
# LOG: Revision 7.1  2002/08/26 22:08:45  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.2  2002/06/21 02:00:39  pmandal
# LOG: Reorganize if conditions
# LOG:
# LOG: Revision 5.4.2.2  2002/06/21 01:40:49  pmandal
# LOG: Reorganize if conditions
# LOG:
# LOG: Revision 5.4.2.1  2002/06/20 21:56:28  pmandal
# LOG: Merge from PR5 to get rid of C targets and dependencies
# LOG:
# LOG: Revision 4.1.2.4  2002/02/12 22:18:38  hdivoux
# LOG: Update for sync with current.
# LOG:
# LOG: Revision 5.4  2002/02/12 22:17:12  hdivoux
# LOG: Update for clean target.
# LOG:
# LOG: Revision 5.3  2002/02/12 21:39:36  hdivoux
# LOG: Complete review of MAP V7 and update of MAP V6.
# LOG:
# LOG: Revision 5.2  2001/11/26 16:37:07  hdivoux
# LOG: Update for new compilation flags.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:45:17  mmiers
# LOG: Start PR6.
# LOG:
################################################################################
################################################################################

