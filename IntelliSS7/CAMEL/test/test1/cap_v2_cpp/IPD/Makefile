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
include $(ITS_ROOT)/config/config.vars

CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/include \

CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/include \
	-I$(ITS_ROOT)/include/itu -I$(ITS_ROOT)/include/asn-cpp \
        -I$(ITS_ROOT)/include/itu/

LIBS = -L$(ITS_ROOT)/CAMEL/lib \
     -L$(ITS_ROOT)/GSMMAP/lib -L. \
     -lENGINED -lDISPATCH++D -lDRIVER++D \
     -lENGINED \
     -lASN++D -lCAP-V2++D -lposix4 

all : libAPPITU.so libAPP.so test

libAPPITU.so: appitu.o
	$(CXX) $(CXXSHAREDARFLAGS) libAPPITU.so appitu.o $(LIBS)

libAPP.so: app_trace.o app.o 
	$(CXX) $(CXXSHAREDARFLAGS) libAPP.so app_trace.o app.o -lAPPITU  $(LIBS)

test: test.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test test.cpp $(LIBS) \
        $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)
#
# get the rules
#
include $(ITS_ROOT)/config/config.rules

.PHONY: clean
clean:
	rm -f *.o *.so test
