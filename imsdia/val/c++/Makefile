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
# ID: $Id: Makefile,v 3.2 2008/08/12 04:22:45 nvijikumar Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.2  2008/08/12 04:22:45  nvijikumar
# LOG: Defined NOWHOLEARCHIVE to remove libc_nonshared dependency. gdalawai
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:29  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.6  2008/03/27 12:12:01  hbhatnagar
# LOG: Converting 2.1 branch to CURRENT
# LOG:
# LOG: Revision 2.4  2007/03/02 06:04:09  nvijikumar
# LOG: Reverting back the JAVA changes which are committed before Branch tag.
# LOG:
# LOG: Revision 2.3  2007/02/26 08:08:28  sumag
# LOG: t
# LOG: :q
# LOG:
# LOG: Revision 2.2  2006/11/07 11:21:09  kamakshilk
# LOG: so library generation added to val
# LOG:
# LOG: Revision 2.1  2006/09/13 09:22:43  yranade
# LOG: Start GA 1.1
# LOG:
# LOG: Revision 1.4  2006/08/13 09:53:09  brianhu
# LOG: New DEBUG_VERBOSE flag and lib initializer to control debugging logs
# LOG:
# LOG: Revision 1.3  2006/06/21 10:16:35  kamakshilk
# LOG: Modification for Copyright info.
# LOG:
# LOG: Revision 1.2  2006/06/21 10:12:32  kamakshilk
# LOG: Modification for Copyright info.
# LOG:
# LOG: Revision 1.1.1.1  2006/02/16 12:16:39  yranade
# LOG: Create baseline imsdia project in CVS.
# LOG:
#
############################################################################
#
# Makefile for IntelliNet Diameter Messaging API Libraries
#
include $(IMS_ROOT)/make.dirs

#
# Debugging ?
#
ifdef DEBUG_VERBOSE
CXXFLAGS := $(CXXFLAGS) -DDEBUG_VERBOSE
ifdef DEBUG_VALCPP
CXXFLAGS := $(CXXFLAGS) -DDEBUG_VALCPP
endif
endif

#
# Protocols to be built
#
NAMESPACES=diameter \

HEADERS=$(wildcard $(patsubst %,include/%/*.h,$(subst .,/,$(NAMESPACES))))

SOURCES=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(NAMESPACES))))

OBJECTS=$(SOURCES:.cpp=.o)

#
# Library base name
#
LIBRARY=lib/libdiaval

#
# Targets
#
.PHONY: all clean

all: $(LIBRARY)$(DBGSUFFIX).a $(LIBRARY)$(DBGSUFFIX).so

realclean clean:
	rm -f $(LIBRARY)$(DBGSUFFIX).a $(OBJECTS) \
        $(LIBRARY)$(DBGSUFFIX).so

$(LIBRARY)$(DBGSUFFIX).a: $(OBJECTS)
	$(CXXAR) $(CXXARFLAGS) $(LIBRARY)$(DBGSUFFIX).a $(OBJECTS)

$(LIBRARY)$(DBGSUFFIX).so: $(OBJECTS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) $(LIBRARY)$(DBGSUFFIX).so $(OBJECTS) $(NOWHOLEARCHIVE)
#
# Dependency
#
$(OBJECTS): $(HEADERS)

