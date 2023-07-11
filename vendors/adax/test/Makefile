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
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:55:28 cvsadmin Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.1  2005/03/23 12:55:28  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:54:41  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:41  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:52  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 1.1  2001/10/24 14:38:49  ngoel
# LOG: first commit
# LOG:
# LOG:
#
############################################################################

#
# get the vars
#

include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/SCCP/include \
       	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include 

CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include  \
	-I$(ITS_ROOT)/common/include \
	-I$(ITS_ROOT)/IS41/include/ansi -I../include \
	-L$(ITS_ROOT)/TCAP/lib -L$(ITS_ROOT)/SCCP/lib -L$(ITS_ROOT)/MTP3/lib \
	-L$(ITS_ROOT)/IS41/lib


INTELLILIBS= -L$(VENDOR_ROOT)/adax/lib \
		-lCCITT-ADAXVENDORD -lDSM-STUB \
  		-lCORED -lSUPPORTD -lCORED \
       		-lSUPPORTD -lCORED -lSUPPORTD \
                -lDSM-STUB \
       		-lSUPPORTD -lCORED -lSUPPORTD \
       		-lmtmalloc


test: test.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test test.cpp ../src/transport.o $(INTELLILIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS) -lrt


#
# get the rules
#
include $(ITS_ROOT)/config.rules
