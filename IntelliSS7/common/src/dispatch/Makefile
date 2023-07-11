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
#  ID: $Id: Makefile,v 9.2 2008/05/09 14:48:51 kramesh Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.2  2008/05/09 14:48:51  kramesh
# LOG: NOWHOLEARCHIVE flag added for ES4.0 compilation.
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:13  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.3  2005/03/21 13:51:27  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1.46.1  2004/12/16 03:30:35  randresol
# LOG: Add JAPAN variant implementation
# LOG:
# LOG: Revision 7.1.42.1  2004/10/25 20:39:57  randresol
# LOG: Start Implementation for Japan SS7
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:51  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.2  2002/08/22 14:21:38  mmiers
# LOG: Add china dispatcher
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.2  2001/09/21 22:58:57  mmiers
# LOG: Add handlers for SS7 ISUP
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:04  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 1.3  2001/03/07 01:16:02  mmiers
# LOG: Shared lib template.  Need to test to see what happens to
# LOG: symbols in the .so that are defined in the app.
# LOG:
# LOG: Revision 1.2  2001/03/02 23:04:04  mmiers
# LOG: Cross platform cleanup.
# LOG:
# LOG: Revision 1.1  2001/01/16 21:39:25  mmiers
# LOG: Reorganize so that support is completely standalone
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
		    -I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
		    -I$(ITS_ROOT)/TCAP/include
CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
			-I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
			-I$(ITS_ROOT)/TCAP/include

OBJS=its_dispatch.o \
     its_disp_ss7_ansi.o its_disp_ss7_ccitt.o its_disp_ss7_prc.o its_disp_ss7_ttc.o
CPPOBJS=its_dispatch++.o \
     its_disp_ss7_ansi++.o its_disp_ss7_ccitt++.o its_disp_ss7_prc++.o its_disp_ss7_ttc++.o

all: ../../lib/libDISPATCH$(DBGSUFFIX).so \
           ../../lib/libDISPATCH++$(DBGSUFFIX).so

clean:
	$(RM) *.o ../../lib/libDISPATCH$(DBGSUFFIX).so .depend \
                ../../lib/libDISPATCH++$(DBGSUFFIX).so

../../lib/libDISPATCH$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
		../../lib/libDISPATCH$(DBGSUFFIX).so $(OBJS) $(NOWHOLEARCHIVE)

../../lib/libDISPATCH++$(DBGSUFFIX).so: $(CPPOBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
		../../lib/libDISPATCH++$(DBGSUFFIX).so $(CPPOBJS) $(NOWHOLEARCHIVE)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
