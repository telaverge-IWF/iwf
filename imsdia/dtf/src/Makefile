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
#
# Include the standard definitions
#
include $(IMS_ROOT)/make.dirs

DEFINES:=$(ITS_DEFINES) $(DEFINES) -D_$(PLATFORM)

CXXFLAGS+= -DJSON_IS_AMALGAMATION  -std=c++0x

INCLS:= -I../include \
		-I$(EACC_ROOT)/blocks/include \
        -I$(IMS_ROOT)/val/c++/include \
        -I$(IMS_ROOT)/vendors/IntelliNet/include \
        -I$(IMS_ROOT)/api/c++/include \
        -I$(IMS_ROOT)/common/include \
        $(ITS_INCLS) \
        -I../dcca/include \
        -I$(ITS_ROOT)/ENGINE/include \
        -I$(ITS_ROOT)/tls/include \
        -I$(IMS_ROOT)/api/c++/include/diameter/base \
		-I$(EACC_ROOT)/3rdparty/jsoncpp_0.6.0-rc2 \
		-I$(EACC_ROOT)/utils/rule/include \
		-I$(EACC_ROOT)/blocks/include

#SOURCES=$(wildcard *.cpp)

#SO_OBJS=$(SOURCES:.cpp=.o)

SO_OBJS= DictionaryTable.o dtf.o 

#
# Library base name
#
LIBRARY=../lib/libdtf


#
# Targets
#
.PHONY: all clean

all: $(LIBRARY)$(DBGSUFFIX).so 

clean:
	rm -f $(LIBRARY)$(DBGSUFFIX).so $(SO_OBJS)

$(LIBRARY)$(DBGSUFFIX).so: $(SO_OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS)  $(LIBRARY)$(DBGSUFFIX).so \
	$(SO_OBJS)  $(NOWHOLEARCHIVE) 

