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
# ID: $Id: Makefile,v 1.2 2010/08/19 11:22:23 nvijikumar Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 1.2  2010/08/19 11:22:23  nvijikumar
# LOG: Porting changes from B-MOTO-IDIA-0421-00
# LOG: 1. New Overload implimentation changes are not being ported.
# LOG: 2. Force disconnect changes are not being ported
# LOG:
# LOG: Revision 1.1  2009/03/02 04:39:44  nvijikumar
# LOG: Initial draft for MML API Support
# LOG:
# LOG:
############################################################################
#
# Include the standard definitions
#
include $(IMS_ROOT)/make.dirs

LIB_OBJS=dms_transports.o dms_common.o 

CXXFLAGS := $(CXXFLAGS) $(ITS_DEFINES) -I../include \
            -I$(ITS_ROOT)/common/include \
            -I../../../common/include  \
            -I../../../aim/server/include  \
            -I../../../vendors/IntelliNet/include 

all: ../lib/libDms$(DBGSUFFIX).so 

../lib/libDms$(DBGSUFFIX).so: $(LIB_OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) $@ $(LIB_OBJS) $(NOWHOLEARCHIVE)

clean :
	$(RM) ../lib/libDms$(DBGSUFFIX).so \
        $(LIB_OBJS) 

