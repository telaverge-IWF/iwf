###########################################################################
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
#  ID: $Id: Makefile,v 9.2.12.1.8.1 2011/04/13 07:45:46 nvijikumar Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.2.12.1.8.1  2011/04/13 07:45:46  nvijikumar
# LOG: Merging from Diameter
# LOG:
# LOG: Revision 9.2.12.1  2009/09/29 06:51:59  ssingh
# LOG: commenting out CTF from linking - SMLC
# LOG:
# LOG: Revision 9.2  2008/05/09 14:48:51  kramesh
# LOG: NOWHOLEARCHIVE flag added for ES4.0 compilation.
# LOG:
# LOG: Revision 9.1  2005/03/23 12:51:18  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.5  2005/03/21 13:49:21  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.3.14.1.6.2  2005/01/10 11:53:01  ssingh
# LOG: ITS-REDUNDANCY lib added.
# LOG:
# LOG: Revision 7.3.14.1.6.1  2005/01/04 13:48:03  mmanikandan
# LOG: Changes for CTF.
# LOG:
# LOG: Revision 7.3.14.1  2004/09/15 05:25:52  mmanikandan
# LOG: XML Persistency propagation.
# LOG:
# LOG: Revision 7.3  2002/11/13 23:23:38  lbana
# LOG: added DSM C++ object in libDRIVER++
# LOG:
# LOG: Revision 7.2  2002/10/30 20:39:36  mmiers
# LOG: Don't need faulty syntax anymore
# LOG:
# LOG: Revision 7.1  2002/08/26 22:08:41  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.3  2002/08/22 20:34:03  omayor
# LOG: Missing CHINA in Getting the mask for GlobalStart.
# LOG:
# LOG: Revision 6.2  2002/04/16 21:21:09  hdivoux
# LOG: FT/HA integration.
# LOG:
# LOG: Revision 6.1  2002/02/28 16:13:18  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.4  2001/11/21 00:47:00  mmiers
# LOG: DBG in engine.
# LOG:
# LOG: Revision 5.3  2001/11/16 02:33:56  mmiers
# LOG: Warning removal
# LOG:
# LOG: Revision 5.2  2001/11/09 20:29:48  mmiers
# LOG: stack as separate lib.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:45:15  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.2  2001/07/19 16:20:12  mmiers
# LOG: Add DSM to the ENGINE build.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:02  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 1.2  2001/04/29 00:05:39  mmiers
# LOG: A few changes required by the validating parser.
# LOG:
# LOG: Revision 1.1  2001/04/28 23:38:20  mmiers
# LOG: Rearrange this to standard form.
# LOG:
# LOG: Revision 1.3  2001/04/12 20:42:04  salaoui
# LOG: corrected
# LOG:
# LOG: Revision 1.2  2001/04/12 20:40:19  salaoui
# LOG: modified for relocation
# LOG:
# LOG: Revision 1.1  2001/04/12 20:10:26  salaoui
# LOG: Move to a more logical location.
# LOG:
# LOG: Revision 1.13  2001/04/03 01:11:57  mmiers
# LOG:
# LOG: Debugging.
# LOG:
# LOG: Revision 1.12  2001/04/02 19:50:41  mmiers
# LOG: Solaris cleanup.
# LOG:
# LOG: Revision 1.11  2001/03/30 23:38:00  mmiers
# LOG: More engine debugging.
# LOG:
# LOG: Revision 1.10  2001/03/30 21:03:34  mmiers
# LOG: Testing.
# LOG:
# LOG: Revision 1.9  2001/03/29 17:08:44  mmiers
# LOG: Missing entry points detected by correct engine build.
# LOG:
# LOG: Revision 1.8  2001/03/29 16:23:40  mmiers
# LOG: Add expat to common build.
# LOG: Split UALs into different libs (avoids symbol collisions).
# LOG: Change shared lib flags.
# LOG:
# LOG: Revision 1.7  2001/03/29 03:07:33  mmiers
# LOG: Start debugging.
# LOG:
# LOG: Revision 1.6  2001/03/17 01:12:15  mmiers
# LOG: Small cleanups for portability.
# LOG:
# LOG: Revision 1.5  2001/03/15 01:27:10  mmiers
# LOG: Updates for portability (fsm).  I think these were required anyway,
# LOG: but VC doesn't complain if they aren't there.  The rest is thinking
# LOG: about the thread pools.  I think I have a handle on this if I can
# LOG: remember it tomorrow.  The comments should help.
# LOG:
# LOG: Revision 1.4  2001/03/14 01:58:37  mmiers
# LOG: Work on the implementation.  If I could get 3-4 uninterrupted
# LOG: hours, this would be done.  TODO: the trace levels and the
# LOG: thread pools.  The only other thing to do is the syntax tree
# LOG: creator.
# LOG:
# LOG: Revision 1.3  2001/03/13 23:21:13  mmiers
# LOG: Various updates for the engine.
# LOG:
# LOG: Revision 1.2  2001/03/13 02:26:22  mmiers
# LOG: UNIX build is a heck of a lot easier to set up.
# LOG:
# LOG: Revision 1.1  2001/03/01 01:22:51  mmiers
# LOG: Add trace config obj.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

COBJS=engine.o engine_commit.o
DCOBJS=driver.o
DCPPOBJS=driver++.o dsm_ops.o
CFLAGS:=$(CFLAGS) -I../include \
	-I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
	-I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
	-I$(ITS_ROOT)/TCAP/include
LIBS=	$(ITS_ROOT)/common/lib/libDBGServer$(DBGSUFFIX).a \
	$(ITS_ROOT)/common/lib/libEXPAT$(DBGSUFFIX).a \
	$(ITS_ROOT)/common/lib/libSUPPORT$(DBGSUFFIX).a \
	$(ITS_ROOT)/common/lib/libCORE$(DBGSUFFIX).a \
	$(ITS_ROOT)/common/lib/libITS-REDUNDANCY$(DBGSUFFIX).a \
	$(ITS_ROOT)/common/lib/libSCTP$(DBGSUFFIX).a \


all: ../../common/lib/libENGINE$(DBGSUFFIX).so \
     ../../common/lib/libDRIVER$(DBGSUFFIX).so \
     ../../common/lib/libDRIVER++$(DBGSUFFIX).so


clean:
	$(RM) *.o .depend ../../common/lib/libENGINE$(DBGSUFFIX).so \
		../../common/lib/libDRIVER$(DBGSUFFIX).so \
		../../common/lib/libDRIVER++$(DBGSUFFIX).so

../../common/lib/libENGINE$(DBGSUFFIX).so: $(COBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
		../../common/lib/libENGINE$(DBGSUFFIX).so \
		$(COBJS) $(LIBS) $(NOWHOLEARCHIVE)

../../common/lib/libDRIVER$(DBGSUFFIX).so: $(DCOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
		../../common/lib/libDRIVER$(DBGSUFFIX).so \
		$(DCOBJS) $(NOWHOLEARCHIVE)

../../common/lib/libDRIVER++$(DBGSUFFIX).so: $(DCPPOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) \
		../../common/lib/libDRIVER++$(DBGSUFFIX).so \
		$(DCPPOBJS) $(NOWHOLEARCHIVE)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
