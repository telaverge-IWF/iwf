############################################################################
#                                                                          #
#     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
# ID: $Id: Makefile,v 3.3.4.1 2012/12/21 05:48:36 ncshivakumar Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.3.4.1  2012/12/21 05:48:36  ncshivakumar
# LOG: modified for tracing
# LOG:
# LOG: Revision 3.3  2011/04/19 05:57:27  nvijikumar
# LOG: Makefile
# LOG:
# LOG: Revision 3.2  2010/07/07 08:34:46  nvijikumar
# LOG: TCS compilation flags support
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:28  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.1  2006/09/13 09:22:43  yranade
# LOG: Start GA 1.1
# LOG:
# LOG: Revision 1.2  2006/06/21 10:39:04  nvijikumar
# LOG: Modification for Copyright info.
# LOG:
# LOG:
#
############################################################################
#
include $(IMS_ROOT)/make.dirs

DEFINES:=$(DEFINES) $(ITS_DEFINES) -Dunix

INCLS:=$(INCLS) $(ITS_INCLS) -I../include
	 
OBJS:=DIAMon.o DIAMon_trace.o DIAMon_alarm.o

LIBS:=-L$(ITS_ROOT)/common/lib \
       -lSUPPORT$(DBGSUFFIX) \
       -lSCORE$(DBGSUFFIX) \
       -lCORE$(DBGSUFFIX) \
       -lSUPPORT$(DBGSUFFIX) \
       -lCORE$(DBGSUFFIX) \
       -lSCORE$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       -lEXPAT$(DBGSUFFIX)

all: DIAMon

clean:
	$(RM) $(OBJS) DIAMon

DIAMon: $(OBJS)
	$(CXX) $(CXXFLAGS) -o DIAMon $(OBJS) \
		$(LIBS) $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)
