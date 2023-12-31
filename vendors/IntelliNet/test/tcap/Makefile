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
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:55:23 cvsadmin Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.1  2005/03/23 12:55:23  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:54:37  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 1.1  2002/11/10 00:07:46  randresol
# LOG: Add ITU test file for TCAP/SCCP/MTP3 stack
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 1.1  2002/07/25 14:27:35  randresol
# LOG: Add mtp3 test files
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:29  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:16  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:18  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 1.6  2001/04/04 22:01:31  mmiers
# LOG: Finish debugging.
# LOG:
# LOG: Revision 1.5  2001/04/03 23:56:56  mmiers
# LOG: Debugging.
# LOG:
# LOG: Revision 1.4  2001/04/03 01:11:57  mmiers
# LOG:
# LOG: Debugging.
# LOG:
# LOG: Revision 1.3  2001/03/30 23:38:00  mmiers
# LOG: More engine debugging.
# LOG:
# LOG: Revision 1.2  2001/03/30 21:03:34  mmiers
# LOG: Testing.
# LOG:
# LOG: Revision 1.1  2001/03/29 03:07:34  mmiers
# LOG: Start debugging.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include \
          -I$(VENDOR_ROOT)/IntelliNet/include \
          -I$(ITS_ROOT)/common/include/asn-cpp \
          -I$(ITS_ROOT)/INAP/include/itu 

LIBS=-L../../lib  -L/opt/nms/lib -L/opt/nmstx/lib -L$(VENDOR_ROOT)/nms/lib \
            -lENGINED -lDRIVERD  \
            -lVFrameD \
            -lDSM-GCS$(DBGSUFFIX)  \
            -lDSM-STUB$(DBGSUFFIX) \
            -lGCS-CLIENT$(DBGSUFFIX) \
#            -lcta \
#            -lctal \
#            -lctacl \
#            -lhmiapi \
#            -lhmimgr \
#            -ltsi \
#            -lss7mapi \
            -lcpi \
            -lmtmalloc 

CCITTLIBS= -lCCITT-VENDOR$(DBGSUFFIX)
#          -lCCITT-NMSVENDOR$(DBGSUFFIX)

ANSILIBS=  -lANSI-VENDOR$(DBGSUFFIX)
#          -lANSI-NMSVENDOR$(DBGSUFFIX)

APPLLIBS= -L$(ITS_ROOT)/INAP/lib -lINAP-ETSI-CS1++D -lASN++D


all: test-itu

clean:
	$(RM) -r *.o test-itu SunWS_cache

test-itu: test-itu.c
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test-itu test-itu.c $(LIBS) \
	       $(APPLLIBS) $(CCITTLIBS) $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
