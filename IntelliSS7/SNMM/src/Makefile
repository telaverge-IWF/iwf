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
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:52:32 cvsadmin Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.1  2005/03/23 12:52:32  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:50:33  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:33  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:45:52  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.2  2000/09/01 15:35:52  mmiers
# LOG: Fix a bunch of Makefiles and make the C++ hash interface public.
# LOG:
# LOG: Revision 3.1  2000/08/16 00:02:36  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 1.1  2000/04/24 20:44:14  mmiers
# LOG:
# LOG:
# LOG: Add SLTM and SNMM to build.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

OBJS=snmm.o
CPPOBJS=
CFLAGS := $(CFLAGS) -I../include -I../../MTP2/include -I../../MTP3/include \
		    -I../../common/include
CXXFLAGS := $(CXXFLAGS) -I../include -I../../MTP2/include -I../../MTP3/include \
			-I../../common/include

all: ../lib/lib$(PROTOCOL)-SNMM$(DBGSUFFIX).a

clean:
	$(RM) *.o ../lib/lib$(PROTOCOL)-SNMM$(DBGSUFFIX).a .depend

../lib/lib$(PROTOCOL)-SNMM$(DBGSUFFIX).a: $(OBJS) $(CPPOBJS)
	$(CXXAR) $(CXXARFLAGS) ../lib/lib$(PROTOCOL)-SNMM$(DBGSUFFIX).a \
		$(OBJS) $(CPPOBJS)
	sh ./generate
#
# get the rules
#
include $(ITS_ROOT)/config.rules
