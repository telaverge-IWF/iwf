############################################################################
#                                                                          #
#     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
# ID: $Id: Makefile,v 1.1.1.1.2.2.16.2.2.1 2015/03/20 09:54:09 jkchaitanya Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 1.1.1.1.2.2.16.2.2.1  2015/03/20 09:54:09  jkchaitanya
# LOG: changes for bug fixes and Couchbase issues in HA
# LOG:
# LOG: Revision 1.1.1.1.2.2.16.2  2014/11/04 09:11:56  jkchaitanya
# LOG: changes for HA bug fixes
# LOG:
# LOG: Revision 1.1.1.1.2.2.16.1  2014/10/27 08:30:34  millayaraja
# LOG: changes for HA HotStandBy and selection criteria enhancements
# LOG:
# LOG: Revision 1.1.1.1.2.2  2013/03/15 21:22:45  brajappa
# LOG: SCCP CCITT support for IWF
# LOG:
# LOG: Revision 1.1.1.1.2.1  2013/01/11 22:22:57  brajappa
# LOG: IWF config reading using json and Abstract base Translator addition
# LOG:
# LOG: Revision 1.1.1.1  2013/01/09 16:41:38  brajappa
# LOG: Initial import
# LOG:
# LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
# LOG: Initial Draft for SSG
# LOG:
# LOG:
############################################################################
#
# get the vars
#

include $(ITS_ROOT)/config.vars
include $(IMS_ROOT)/make.dirs

DEFINES:= $(DEFINES) $(ITS_DEFINES)

CXXFLAGS+= -std=c++0x -fPIC

# Make this runtime option somehow..
PROTOCOL=CCITT

DIA_INCLS:=$(INCLS) $(ITS_INCLS) \
		-I$(IMS_ROOT)/api/c++/include/diameter/dcca \
		-I$(IMS_ROOT)/api/c++/include \
		-I$(IMS_ROOT)/common/include \
		-I$(IMS_ROOT)/dframe/include \
		-I$(IMS_ROOT)/val/c++/include \
		-I$(IMS_ROOT)/vendors/IntelliNet/dcca/include \
		-I$(IMS_ROOT)/vendors/IntelliNet/include \
		-I$(IMS_ROOT)/dtf/include

CXXFLAGS:=$(CXXFLAGS) $(ITS_DEFINES) -g -DUNIX -DCCITT -DJSON_IS_AMALGAMATION \
		$(DIA_INCLS) -I ../include -I$(ITS_ROOT)/common/include \
		-I ../include -I$(ITS_ROOT)/common/include/asn-cpp \
		-I$(ITS_ROOT)/common/include \
		-I$(ITS_ROOT)/common/include/asn-cpp \
		-I$(ITS_ROOT)/common/src/ual \
		-I$(ITS_ROOT)/GSMMAP/include/itu \
		-I$(ITS_ROOT)/CAMEL/include/itu \
		-I$(ITS_ROOT)/SCCP/include \
		-I$(ITS_ROOT)/TCAP/include \
		-I$(ITS_ROOT)/MTP3/include \
		-I$(ITS_ROOT)/MTP2/include \
		-I$(ITS_ROOT)/GSMMAP/include \
		-I$(ITS_ROOT)/GSMMAP/include/itu \
		-I$(ITS_ROOT)/CAMEL/include \
		-I$(ITS_ROOT)/CAMEL/include/itu \
		-I$(ITS_ROOT)/tls/include \
		-I$(VENDOR_ROOT)/IntelliNet/include \
		-I$(EACC_ROOT)/mess/include \
		-I$(EACC_ROOT)/blocks/include \
		-I$(EACC_ROOT)/utils/hash/include \
		-I$(EACC_ROOT)/common/include \
		-I$(EACC_ROOT)/avamgr/hacomponent/include \
		-I$(EACC_ROOT)/3rdparty/include \
		-I$(EACC_ROOT)/3rdparty/mysql-connector-c++-1.1.0 \
		-I$(EACC_ROOT)/3rdparty/jsoncpp_0.6.0-rc2/json \
		-I$(ITS_ROOT)/include \
		-I$(ITS_ROOT)/common/include \
		-I$(EACC_ROOT)/cmapi/idl \
		-I$(EACC_ROOT)/cmapi/alarms/include \
		-I$(EACC_ROOT)/cmapi/configfetch/include \
		-I$(EACC_ROOT)/cmapi/common/ \
		-I$(EACC_ROOT)/cmapi/components/include \
		-I$(EACC_ROOT)/avamgr/include \
		-I$(EACC_ROOT)/repmgr/include \
		-I$(IWF_ROOT)/include


ifeq ($(PROTOCOL), CCITT)
  ifeq ($(SCCP_PROT), ANSI)
	APP_SUFFIX:= COA
  endif
  ifeq ($(SCCP_PROT), CCITT)
  	APP_SUFFIX:= CCITT
  endif
endif

#INCLS:=$(INCLS) $(ITS_INCLS) \
	-I ../include \
	-I$(EACC_ROOT)/mess/include \
	-I$(EACC_ROOT)/blocks/include \
	-I$(EACC_ROOT)/utils/hash/include \
	-I$(EACC_ROOT)/common/include \
	-I$(EACC_ROOT)/avamgr/hacomponent/include \
	-I$(EACC_ROOT)/3rdparty/include \
	-I$(EACC_ROOT)/3rdparty/mysql-connector-c++-1.1.0 \
	-I$(EACC_ROOT)/cmapi/idl \
	-I$(EACC_ROOT)/cmapi/configfetch/include \
	-I$(EACC_ROOT)/cmapi/common/ \
	-I$(EACC_ROOT)/cmapi/components/include \
	-I$(EACC_ROOT)/repmgr/include 


SOURCES=$(wildcard *.cpp)
COBJS:= $(SOURCES:.cpp=.o)

CCSOURCES=$(wildcard *.cc)
CCOBJS:= $(CCSOURCES:.cc=.o)

# Restrict the user to give explicit targets
all:  generate ../lib/libIWFCmn-$(APP_SUFFIX)$(DBGSUFFIX).so

generate: 
	protoc -I=. --cpp_out=.  iwf.proto
	mv -f iwf.pb.h ../include/

../lib/libIWFCmn-$(APP_SUFFIX)$(DBGSUFFIX).so: $(COBJS) $(CCOBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
	$@ -fPIC $(COBJS) $(CCOBJS) $(LIBS) $(SYSLIBS) $(THREADLIBS) $(NOWHOLEARCHIVE) 

iwf.pb.o:
	$(CXX) $(CXXFLAGS) $(LIBS) -c iwf.pb.cc

clean:
	-rm -f *.o
	-rm -f *.pb.*
	$(RM) ../lib/libIWFCmn-$(APP_SUFFIX)$(DBGSUFFIX).so $(COBJS) 

