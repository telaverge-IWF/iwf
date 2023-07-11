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
#  ID: $Id: Makefile,v 9.3.16.1 2012/12/18 16:11:58 brajappa Exp $
#
################################################################################
#
#  ID: $Id: Makefile,v 9.3.16.1 2012/12/18 16:11:58 brajappa Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.3.16.1  2012/12/18 16:11:58  brajappa
# LOG: Initial IWF branch creation and linux compilation changes
# LOG:
# LOG: Revision 9.3  2008/05/13 11:42:28  kramesh
# LOG: Included INAP Ericsson target.
# LOG:
# LOG: Revision 9.2  2005/06/03 07:27:29  adutta
# LOG: Changed for Nokia CS1
# LOG:
# LOG: Revision 9.1  2005/03/23 12:51:42  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.6  2005/03/21 13:49:39  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1.14.2.4.1  2005/01/31 13:32:58  mmanikandan
# LOG: clean updated with the shared object.
# LOG:
# LOG: Revision 7.1.14.2  2004/09/21 10:06:54  mmanikandan
# LOG: Propagating pprint from current.
# LOG:
# LOG: Revision 7.1.14.1  2004/05/31 13:31:38  mmanikandan
# LOG: Common object inap_cpp.o is added.
# LOG:
# LOG: Revision 7.1  2002/08/26 22:08:56  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.5  2002/06/27 21:44:12  hdivoux
# LOG: Update for INAP ETSI CS1.
# LOG:
# LOG: Revision 6.1  2002/02/28 16:13:33  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.3  2002/02/15 22:37:29  hdivoux
# LOG: Correction (major) for working INAP CS2 build procedure.
# LOG:
# LOG: Revision 4.1.2.3  2002/02/15 22:04:17  hdivoux
# LOG: Removed INAP CS1 C target.
# LOG:
# LOG: Revision 4.1.2.2  2002/02/15 21:53:05  fchouinard
# LOG: Correction.
# LOG:
# LOG: Revision 4.1.2.1  2001/11/28 21:21:49  hdivoux
# LOG: Update for sync with current.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:04  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.2  2000/11/13 18:29:31  mmiers
# LOG: Try to recover repository.
# LOG:
# LOG: Revision 3.3  2000/10/30 16:43:25  salaoui
# LOG: added missing endif
# LOG:
# LOG: Revision 3.1  2000/08/15 23:57:50  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.2  2000/03/30 21:50:30  hdivoux
# LOG: Finish port for Unix.
# LOG:
# LOG: Revision 2.1  2000/03/30 21:18:52  hdivoux
# LOG: Creation and port to Unix of new C API.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:19:47  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.23  1999/07/12 20:32:09  skarmakar
# LOG: *** empty log message ***
# LOG:
# LOG: Revision 1.22  1999/07/02 01:35:05  mmiers
# LOG:
# LOG:
# LOG: Fix the clean rule
# LOG:
# LOG: Revision 1.21  1999/07/02 01:18:03  mmiers
# LOG:
# LOG:
# LOG: Make sure dbgsuffix is included
# LOG:
# LOG: Revision 1.20  1999/07/01 16:51:08  mmiers
# LOG:
# LOG:
# LOG: C++ build
# LOG:
# LOG: Revision 1.19  1999/07/01 16:36:41  mmiers
# LOG:
# LOG:
# LOG: Update this for a clean build.
# LOG:
# LOG: Revision 1.18  1999/07/01 02:29:12  mmiers
# LOG:
# LOG: On Solaris, you build C++ libraries with the compiler, of all
# LOG: things.  Add new make variables accordingly.
# LOG:
# LOG: Revision 1.17  1999/06/29 19:04:50  skarmakar
# LOG:
# LOG:
# LOG: Build on DEC
# LOG:
# LOG: Revision 1.16  1999/06/15 23:20:07  labuser
# LOG:
# LOG: added sh ./generate to generate Doc files
# LOG:
# LOG: Revision 1.15  1999/03/02 22:16:22  mmiers
# LOG:
# LOG:
# LOG: Custom build steps (relevant protocol family only).
# LOG:
# LOG: Revision 1.14  1998/11/18 00:23:39  jrao
# LOG: Changed Library Suffix (LIBSUFFIX) to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.13  1998/11/17 23:57:39  jrao
# LOG: Changed Library Suffix (DBGSUFFIX) wherever it occured to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.12  1998/11/17 16:41:43  jrao
# LOG: Added facility to produce Release and Debug versions of the library.
# LOG:
# LOG: Revision 1.11  1998/10/21 19:31:17  mmiers
# LOG: Update for automatic building from ASN modules.
# LOG:
# LOG: Revision 1.10  1998/10/21 19:30:05  mmiers
# LOG: Generate using asn compiler.
# LOG:
# LOG: Revision 1.9  1998/09/26 16:05:42  mmiers
# LOG: Update unix build.
# LOG:
# LOG: Revision 1.8  1998/09/22 23:56:24  jrao
# LOG: Changes made to accomodate HPUX code
# LOG:
# LOG: Revision 1.7  1998/05/21 02:15:24  mmiers
# LOG: General cleanup to reflect TCAP changes (INAP, IS41).  Some missing
# LOG: files in builds.  Update the test to include the SCCP library.  I'll
# LOG: have to modify TCAP tomorrow to use SCCP_SendEvent instead of
# LOG: TRANSPORT_PutEvent().  Less efficient, but more useable with someone
# LOG: else's SCCP.
# LOG:
# LOG: Revision 1.6  1998/05/05 02:06:29  mmiers
# LOG: Add .depend target to clean rule.
# LOG:
# LOG: Revision 1.5  1998/05/05 01:58:58  mmiers
# LOG: Sanitize the build environment a bit.  This gets the Solaris
# LOG: environment to build cleanly.
# LOG:
# LOG: Revision 1.4  1998/04/24 01:41:29  mmiers
# LOG: General cleanup of the build system.  Need to verify on Digital Unix
# LOG: to make sure this is ok.
# LOG:
# LOG: Revision 1.3  1998/02/05 15:50:22  mmiers
# LOG: Fixup.
# LOG:
# LOG: Revision 1.2  1998/02/05 15:39:05  mmiers
# LOG: Update for cleanup.
# LOG:
# LOG: Revision 1.1  1998/02/05 15:30:47  mmiers
# LOG: Cleaning up the tree.  The inap library had disappeared, add it back.
# LOG: Move the test files to the test directory.
# LOG:
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

ifeq ($(TARGET),INAP-CS2)

include inap_cs2_cpp_targets

endif

ifeq ($(TARGET),INAP-CS1)

include inap_cs1_cpp_targets

endif

ifeq ($(TARGET),INAP-NOKIA-CS1)

include inap_nokia_cs1_cpp_targets

endif

ifeq ($(TARGET),INAP-CHINA-CS1)

include inap_china_cs1_cpp_targets

endif

ifeq ($(TARGET),INAP-ETSI-CS1)

include inap_etsi_cs1_cpp_targets

endif

ifeq ($(TARGET),INAP-ERIC-CS1)
 
include inap_eric_cpp_targets
 
endif


ifneq ($(TARGET),)

# Protocol is CCITT ONLY


CXXFLAGS := $(ASNRTCXXFLAGS) -I../../common/include -I../include/itu -UANSI -DCCITT \
          -I../../TCAP/include -I../../SCCP/include -I../../MTP3/include \
          -I../../MTP2/include \
          -I../../common/include/asn-cpp

CXXOBJS := inap_cpp.o $(CXXOBJS)

all: $(CXXLIBTARGET) $(CXXSOLIBTARGET) $(PRINTTARGET)



$(CXXSRCSAUX) $(CXXHDRSAUX): $(CXXSRCASN)
	$(ASNCC) $(ASNCCFLAGS) $(CXXSRCASN)
	$(MV) $(CXXHDRSAUX) ../include/itu

$(CXXLIBTARGET): $(CXXOBJS)
	$(CXXAR) $(CXXARFLAGS) $(CXXLIBTARGET) $(CXXOBJS)
	sh ./generate

$(CXXSOLIBTARGET): $(CXXOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(CXXSOLIBTARGET) $(CXXOBJS) $(NOWHOLEARCHIVE)

$(PRINTTARGET): print.o $(CXXSOLIBTARGET)
	$(CXX) $(CXXSHAREDARFLAGS) $(PRINTTARGET) \
        print.o $(CXXSOLIBTARGET) \
        $(ITS_ROOT)/common/lib/libASN++$(DBGSUFFIX).so $(NOWHOLEARCHIVE)

clean:
	$(RM) -r    $(CXXOBJS) $(SRCSAUX) $(LIBTARGET) \
                $(CXXLIBTARGET) $(CXXOBJSAUX) $(CXXSRCSAUX) \
                $(CXXSOLIBTARGET) $(PRINTTARGET) *.err .depend
	for file in $(CXXHDRSAUX);			\
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

