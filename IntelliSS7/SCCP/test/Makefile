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
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:52:25 cvsadmin Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.1  2005/03/23 12:52:25  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:50:23  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:23  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:02  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:45:48  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:11  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.1  2000/08/16 00:02:08  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:24:43  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.8  1998/11/13 16:15:54  mmiers
# LOG: Figure lib needs
# LOG:
# LOG: Revision 1.7  1998/10/29 00:36:24  mmiers
# LOG: Convert to new ASN library.
# LOG:
# LOG: Revision 1.6  1998/10/15 03:38:07  mmiers
# LOG: Update this to handle MTP3.
# LOG:
# LOG: Revision 1.5  1998/10/15 03:30:47  mmiers
# LOG: Add INI files for the basic tests.
# LOG:
# LOG: Revision 1.4  1998/10/15 02:07:08  mmiers
# LOG: Fixes for Alpha platform.
# LOG:
# LOG: Revision 1.3  1998/09/30 02:40:02  mmiers
# LOG: Updates for SCCP.  I think I've got the compromises for SCCP routing
# LOG: down.  Need to add the routing label everywhere.
# LOG:
# LOG: Revision 1.2  1998/09/22 23:56:30  jrao
# LOG: Changes made to accomodate HPUX code
# LOG:
# LOG: Revision 1.1  1998/06/23 02:31:07  mmiers
# LOG: Update Solaris build environment.  Part of getting SCCP working.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/TCAP/include/ansi \
          -I$(ITS_ROOT)/tools/include
CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/TCAP/include/ansi \
          -I$(ITS_ROOT)/tools/include
LIBS=     -lSUPPORT++ -lVENDOR -lASN -lSUPPORT++ -lUNITTEST -lMTP3 -lSCCP

all: test test2

clean:
	$(RM) test.o test2.o .depend

test: test.o
	$(CXX) -o test test.o -L../lib -L$(ITS_ROOT)/SCCP/lib \
          -L$(ITS_ROOT)/common/lib -L$(VENDOR_ROOT)/$(VENDOR)/lib \
          -L$(ITS_ROOT)/TCAP/lib -L$(ITS_ROOT)/tools/lib \
          -L$(ITS_ROOT)/MTP3/lib \
          $(LIBS) $(SYSLIBS) $(SOCKLIBS) $(THREADLIBS)

test2: test2.o
	$(CXX) -o test2 test2.o -L../lib -L$(ITS_ROOT)/SCCP/lib \
          -L$(ITS_ROOT)/common/lib -L$(VENDOR_ROOT)/$(VENDOR)/lib \
          -L$(ITS_ROOT)/TCAP/lib -L$(ITS_ROOT)/tools/lib \
          -L$(ITS_ROOT)/MTP3/lib \
          $(LIBS) $(LIBS) $(SYSLIBS) $(SOCKLIBS) $(THREADLIBS)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
