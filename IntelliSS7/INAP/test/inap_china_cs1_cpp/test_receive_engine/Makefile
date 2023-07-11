############################################################################
#                                                                          #
#     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:51:45 cvsadmin Exp $
#
############################################################################

include $(ITS_ROOT)/config.vars

ifeq ($(PROTOCOL),CCITT)

all: test_receive_engine$(DBGSUFFIX)

ITS_LIBS = -lENGINE$(DBGSUFFIX)     \
           -lDRIVER++$(DBGSUFFIX)
                      
CXXOBJS = test_receive_engine_main.o
 
LDFLAGS := $(LDFLAGS) -L$(ITS_ROOT)/common/lib

CFLAGS := $(CFLAGS) -I. -I$(ITS_ROOT)/common/include            \
                        -I$(ITS_ROOT)/common/include/asn-cpp    \
                        -I$(ITS_ROOT)/TCAP/include              \
                        -I$(ITS_ROOT)/SCCP/include              \
                        -I$(ITS_ROOT)/MTP3/include              \
                        -I$(ITS_ROOT)/MTP2/include              \
                        -I$(ITS_ROOT)/INAP/include/itu

test_receive_engine$$(DBGSUFFIX): $(CXXOBJS)
	$(CXX) $(LDFLAGS) $(CXXOBJS) -o test_receive_engine$(DBGSUFFIX) \
                    $(OBJS)                                         \
                    $(ITS_LIBS)                                     \
                    $(SOCKLIBS)                                     \
                    $(THREADLIBS)                                   \
                    $(SYSLIBS)
                    

clean:
	$(RM) test_receive_engine$(DBGSUFFIX)  \
          $(CXXOBJS) .depend

include $(ITS_ROOT)/config.rules


else

all:
	echo "missing PROTOCOL (must be CCITT)!"

endif


