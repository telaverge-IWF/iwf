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
# ID: $Id: Makefile,v 3.3 2009/03/25 05:08:21 nvijikumar Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.3  2009/03/25 05:08:21  nvijikumar
# LOG: Removing sctp dependency for IDC
# LOG:
# LOG: Revision 3.2  2008/08/12 04:25:57  nvijikumar
# LOG: Defined NOWHOLEARCHIVE to remove libc_nonshared dependency. gdalawai
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:03  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.9  2008/03/27 11:18:29  hbhatnagar
# LOG: Converting 2.1 branch to CURRENT
# LOG:
# LOG: Revision 2.7  2006/11/16 12:40:57  kamakshilk
# LOG: Added EXPAT library for dictionary parsing
# LOG:
# LOG: Revision 2.6  2006/11/14 09:18:58  kamakshilk
# LOG: included path api/c++/include
# LOG:
# LOG: Revision 2.5  2006/11/07 11:56:41  kamakshilk
# LOG: Codec library linked
# LOG:
# LOG: Revision 2.4  2006/10/31 10:02:20  kamakshilk
# LOG: DUMP option removed
# LOG:
# LOG: Revision 2.3  2006/10/17 12:04:28  kamakshilk
# LOG: Removed link to vendors/IntelliNet/lib
# LOG:
# LOG: Revision 2.2  2006/10/16 14:22:50  kamakshilk
# LOG: Changes to work with ITS-Diameter
# LOG:
# LOG: Revision 2.1  2006/09/13 09:22:39  yranade
# LOG: Start GA 1.1
# LOG:
# LOG: Revision 1.9  2006/06/21 10:07:47  kamakshilk
# LOG: Modification for Copyright info.
# LOG:
############################################################################
#
# get the vars
#
include $(IMS_ROOT)/make.dirs

CXXFLAGS:=$(CXXFLAGS) $(ITS_DEFINES) -g -I./include -DUNIX \
	-I$(ITS_ROOT)/common/include    \
        -I$(IMS_ROOT)/common/include \
        -I$(IMS_ROOT)/api/c++/include \
        -I$(IMS_ROOT)/vendors/IntelliNet/include \
        -I../include 


LIBS:= -L$(ITS_ROOT)/common/lib \
       -L$(IMS_ROOT)/common/lib \
       -L$(IMS_ROOT)/vendors/IntelliNet/lib \
       -ldiacommon$(DBGSUFFIX) \
       -lCORE$(DBGSUFFIX) \
       -lSUPPORT$(DBGSUFFIX) \
       -lEXPAT$(DBGSUFFIX) \
       -lDBGServer$(DBGSUFFIX) -lresolv
    

SOURCES=$(wildcard *.cpp)
COBJS:= $(SOURCES:.cpp=.o)

# Restrict the user to give explicit targets
all:  ../lib/libIDSClient$(DBGSUFFIX).so 

../lib/libIDSClient$(DBGSUFFIX).so: $(COBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
	$@ $(COBJS) $(LIBS) $(THREADLIBS) $(SYSLIBS) \
	$(IMS_ROOT)/vendors/IntelliNet/lib/libdiacodec$(DBGSUFFIX).a $(NOWHOLEARCHIVE)


clean:
	$(RM) ../lib/libIDSClient$(DBGSUFFIX).so $(COBJS) 

