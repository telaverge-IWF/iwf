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
# ID: $Id: Makefile,v 1.2 2006/02/28 01:16:20 brianhu Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 1.2  2006/02/28 01:16:20  brianhu
# LOG: Disable copying of AVPs and commands.
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
	-I$(IMS_ROOT)/api/c++/include \
	-I$(IMS_ROOT)/api/c++/include/diameter/base

LIBS     :=-L$(IMS_ROOT)/api/c++/lib \
           -L$(IMS_ROOT)/val/c++/lib \
           -L$(IMS_ROOT)/vendors/opendiameter/lib \
	   -ldiaapi$(DBGSUFFIX) \
           -ldiaval$(DBGSUFFIX) \
           -ldiavendor$(DBGSUFFIX)

CPPOBJS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: TestBase

%: %.o
	$(CXX) $(CXXFLAGS) -o $@ $< \
	$(LIBS) $(SOCKLIBS) $(SYSLIBS)

clean:
	$(RM) *.o TestBase

