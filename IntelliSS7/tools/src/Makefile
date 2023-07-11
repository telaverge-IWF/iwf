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
#     FILE: Makefile                                                       #
#                                                                          #
############################################################################
#
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:54:07 cvsadmin Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.1  2005/03/23 12:54:07  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:52:47  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:17  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:30  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.2  2001/08/17 16:47:21  hdivoux
# LOG: Update after removing  asncc, asn-cpp and asn-java dirs.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:19  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:22  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.2  2000/09/01 15:35:53  mmiers
# LOG: Fix a bunch of Makefiles and make the C++ hash interface public.
# LOG:
# LOG: Revision 3.1  2000/08/16 00:07:06  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.1  2000/07/05 17:26:06  mmiers
# LOG:
# LOG:
# LOG: ip_trans: avoid DoS
# LOG: Makefile: add asncc_v2
# LOG:
# LOG: Revision 2.0  1999/12/03 23:29:40  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.17  1999/09/20 17:00:26  labuser
# LOG:
# LOG:
# LOG: Change "make" to dollar-make
# LOG:
# LOG: Revision 1.16  1999/06/29 21:52:38  mmiers
# LOG:
# LOG:
# LOG: Build release and debug in one step.
# LOG:
# LOG: Revision 1.15  1999/06/29 17:14:12  skarmakar
# LOG:
# LOG:
# LOG: Portability fixes.
# LOG:
# LOG: Revision 1.14  1999/05/13 22:12:20  mmiers
# LOG:
# LOG:
# LOG: Temporary until dual building works.
# LOG:
# LOG: Revision 1.13  1999/05/11 01:27:36  mmiers
# LOG:
# LOG:
# LOG: Start on dual debug/release build rules.
# LOG:
# LOG: Revision 1.12  1998/11/17 23:33:51  jrao
# LOG: asn-java does not have a Makefile
# LOG:
# LOG: Revision 1.11  1998/11/17 19:04:14  jrao
# LOG: Corrections pending after the move of dbc from tools to common are now made.
# LOG:
# LOG: Revision 1.10  1998/11/17 17:46:44  jrao
# LOG: dbc no longer in tools.
# LOG:
# LOG: Revision 1.9  1998/11/17 16:44:59  jrao
# LOG: No entries for dbc.
# LOG:
# LOG: Revision 1.8  1998/10/21 19:33:51  mmiers
# LOG: Tweaks for autobuild.
# LOG:
# LOG: Revision 1.7  1998/10/01 01:55:41  mmiers
# LOG: Disable compiler targets
# LOG:
# LOG: Revision 1.6  1998/10/01 01:27:23  mmiers
# LOG: Remove bison, add unittester
# LOG:
# LOG: Revision 1.5  1998/09/22 23:56:34  jrao
# LOG: Changes made to accomodate HPUX code
# LOG:
# LOG: Revision 1.4  1998/05/20 02:47:55  mmiers
# LOG: Cleanup for the Makefile.
# LOG:
# LOG: Revision 1.3  1998/05/20 02:45:21  mmiers
# LOG: Back port to UNIX from that wannabe OS.
# LOG:
# LOG: Revision 1.2  1998/05/20 02:04:21  mmiers
# LOG: Tree cleanup.
# LOG:
# LOG: Revision 1.1  1998/05/20 01:54:34  mmiers
# LOG: General tree cleanup.
# LOG:
#
############################################################################

all:
	(cd unittest && $(MAKE) DEBUG_BUILD=yes clean)
	(cd unittest && $(MAKE) DEBUG_BUILD=yes all)
	(cd unittest && $(MAKE) DEBUG_BUILD=no clean)
	(cd unittest && $(MAKE) DEBUG_BUILD=no all)
	(cd exc && $(MAKE) DEBUG_BUILD=yes clean)
	(cd exc && $(MAKE) DEBUG_BUILD=yes all)
	(cd exc && $(MAKE) DEBUG_BUILD=no clean)
	(cd exc && $(MAKE) DEBUG_BUILD=no all)
	(cd asnc && $(MAKE) DEBUG_BUILD=yes clean)
	(cd asnc && $(MAKE) DEBUG_BUILD=yes all)
	(cd asnc && $(MAKE) DEBUG_BUILD=no clean)
	(cd asnc && $(MAKE) DEBUG_BUILD=no all)
	(cd asncc_v2 && $(MAKE) DEBUG_BUILD=yes clean)
	(cd asncc_v2 && $(MAKE) DEBUG_BUILD=yes all)
	(cd asncc_v2 && $(MAKE) DEBUG_BUILD=no clean)
	(cd asncc_v2 && $(MAKE) DEBUG_BUILD=no all)

debug:
	(cd unittest && $(MAKE) DEBUG_BUILD=yes clean)
	(cd unittest && $(MAKE) DEBUG_BUILD=yes all)
	(cd exc && $(MAKE) DEBUG_BUILD=yes clean)
	(cd exc && $(MAKE) DEBUG_BUILD=yes all)
	(cd asnc && $(MAKE) DEBUG_BUILD=yes clean)
	(cd asnc && $(MAKE) DEBUG_BUILD=yes all)
	(cd asncc_v2 && $(MAKE) DEBUG_BUILD=yes clean)
	(cd asncc_v2 && $(MAKE) DEBUG_BUILD=yes all)

release:
	(cd unittest && $(MAKE) DEBUG_BUILD=no clean)
	(cd unittest && $(MAKE) DEBUG_BUILD=no all)
	(cd exc && $(MAKE) DEBUG_BUILD=no clean)
	(cd exc && $(MAKE) DEBUG_BUILD=no all)
	(cd asnc && $(MAKE) DEBUG_BUILD=no clean)
	(cd asnc && $(MAKE) DEBUG_BUILD=no all)
	(cd asncc_v2 && $(MAKE) DEBUG_BUILD=no clean)
	(cd asncc_v2 && $(MAKE) DEBUG_BUILD=no all)

depend:
	(cd unittest && $(MAKE) depend)
	(cd exc && $(MAKE) depend)
	(cd asnc && $(MAKE) depend)
	(cd asncc_v2 && $(MAKE) depend)

clean:
	(cd unittest && $(MAKE) DEBUG_BUILD=yes clean)
	(cd unittest && $(MAKE) DEBUG_BUILD=no clean)
	(cd exc && $(MAKE) DEBUG_BUILD=yes clean)
	(cd exc && $(MAKE) DEBUG_BUILD=no clean)
	(cd asnc && $(MAKE) DEBUG_BUILD=yes clean)
	(cd asnc && $(MAKE) DEBUG_BUILD=no clean)
	(cd asncc_v2 && $(MAKE) DEBUG_BUILD=yes clean)
	(cd asncc_v2 && $(MAKE) DEBUG_BUILD=no clean)
