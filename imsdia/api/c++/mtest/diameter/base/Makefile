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
# ID: $Id: Makefile,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.1  2008/03/31 10:33:07  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.1  2006/09/13 09:22:41  yranade
# LOG: Start GA 1.1
# LOG:
# LOG: Revision 1.3  2006/03/02 13:47:34  tpanda
# LOG: Remove explicit ACE and ACE_SSL library linking. This is assuming
# LOG: LD_LIBRARY_PATH contains the path to these libs. In the future we will
# LOG: link libdiavendor with .a's of both of these.
# LOG:
# LOG: Revision 1.2  2006/02/28 13:47:04  nvijikumar
# LOG: Updates after code changes in val and api.
# LOG:
# LOG: Revision 1.1.1.1  2006/02/16 12:16:44  yranade
# LOG: Create baseline imsdia project in CVS.
# LOG:
#
############################################################################
#
#get the vars
#
include $(IMS_ROOT)/make.dirs

CXXFLAGS := $(CXXFLAGS) \
	-I../../../../../api/c++/include \
	-I../../../../../api/c++/include/diameter/base

LIBS     :=-L../../../lib \
           -L$(IMS_ROOT)/val/c++/lib \
           -L$(IMS_ROOT)/vendors/opendiameter/lib \
	   -ldiaapi$(DBGSUFFIX) \
           -ldiaval$(DBGSUFFIX) \
           -ldiavendor$(DBGSUFFIX) 

CPPOBJS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: TestBase

TestBase: $(CPPOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(CPPOBJS) \
	$(LIBS) $(SOCKLIBS) $(SYSLIBS)

clean:
	$(RM) *.o TestBase

