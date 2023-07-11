#*********************************-*-Makefile-*-****************************
#                                                                          *
#          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
#            Manufactured in the United States of America.                 *
#      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
#                                                                          *
#   This product and related documentation is protected by copyright and   *
#   distributed under licenses restricting its use, copying, distribution  *
#   and decompilation.  No part of this product or related documentation   *
#   may be reproduced in any form by any means without prior written       *
#   authorization of Diametriq and its licensors, if any.                  *
#                                                                          *
#   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
#   government is subject to restrictions as set forth in subparagraph     *
#   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
#   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
#                                                                          *
#***************************************************************************

# Include the standard definitions
#

include $(ITS_ROOT)/config.vars

CXXFLAGS:=$(CXXFLAGS) -I. -I$(ITS_ROOT)/common/include -I$(SUBAGENT_PATH)/include \
                  -I../include 

ifeq ($(USE_SOL_SNMP),yes)
ifeq ($(PLATFORM),solaris64)
SNMP_BUILDLIBS=-L/usr/sfw/lib/sparcv9/ -lnetsnmp
SNMP_BUILDAGENTLIBS=/usr/sfw/lib/sparcv9/libnetsnmpagent.a \
                    /usr/sfw/lib/sparcv9/libnetsnmpmibs.a \
                    /usr/sfw/lib/sparcv9/libnetsnmphelpers.a \
                    $(SNMP_BUILDLIBS)
CXXFLAGS:=$(CXXFLAGS) -I. -I/usr/sfw/include -D_SOL_SNMP_
else
SNMP_BUILDLIBS=-L/usr/sfw/lib/ -lnetsnmp
SNMP_BUILDAGENTLIBS=/usr/sfw/lib/libnetsnmpagent.a \
                    /usr/sfw/lib/libnetsnmpmibs.a \
                    /usr/sfw/lib/libnetsnmphelpers.a \
                    $(SNMP_BUILDLIBS)
CXXFLAGS:=$(CXXFLAGS) -I. -I/usr/sfw/include -D_SOL_SNMP_
endif
else
ifeq ($(USE_GNU_SNMP),yes)
SNMP_BUILDLIBS=-L/usr/lib64/ -lnetsnmp
SNMP_BUILDAGENTLIBS=/usr/lib64/libnetsnmpagent.so \
                    /usr/lib64/libnetsnmpmibs.so \
                    /usr/lib64/libnetsnmphelpers.so \
                    /usr/lib64/perl5/5.8.8/x86_64-linux-thread-multi/auto/DynaLoader/DynaLoader.a \
                    -L/usr/lib64/perl5/5.8.8/x86_64-linux-thread-multi/CORE \
                    $(SNMP_BUILDLIBS) -lwrap -lperl -lm -ldl \
                    -lcrypt -lpthread -lcrypto -lsensors -lrpm
CXXFLAGS:=$(CXXFLAGS) -I. -I/usr/include/net-snmp
else
SNMP_BUILDLIBS=-L$(SNMP_ROOT)/snmplib/.libs/ -lnetsnmp
SNMP_BUILDAGENTLIBS=-L$(SNMP_ROOT)/lib64/ -lnetsnmpagent \
                    -lnetsnmpmibs \
                    -lnetsnmphelpers \
                    $(SNMP_BUILDLIBS)
CXXFLAGS:=$(CXXFLAGS) -I../include -I$(SNMP_ROOT)/include 
endif
endif

SHAREDARFLAGS:= $(SHAREDARFLAGS)

EACC_INCLS = -I$(EACC_ROOT)/blocks/include  -I$(EACC_ROOT)/mess/include \
			 -I$(EACC_ROOT)/3rdparty/include -I$(EACC_ROOT)/cmapi/idl/ \
			 -I$(EACC_ROOT)/avamgr/hacomponent/include -I$(EACC_ROOT)/3rdparty/include/json/

CFLAGS:=$(CFLAGS) -Dlinux -x c++ -std=c++0x -I../include $(EACC_INCLS) -DJSON_IS_AMALGAMATION
CXXFLAGS:=$(CXXFLAGS) -DJSON_IS_AMALGAMATION

CXXFLAGS:=$(CXXFLAGS) $(EACC_INCLS) -std=c++0x -Dlinux

MAIN_OBJ = SubAgentMeSS.o subagent.o AlarmAPIImpl.o

OBJS:= stacks.o dremib.o

ITS_LIBS := -L$(ITS_ROOT)/common/lib \
            -lSUPPORT$(DBGSUFFIX) \
            -lCORE$(DBGSUFFIX) \
			-lDBGServer$(DBGSUFFIX) \
             $(ITS_LIBS) $(THREADLIBS) $(SYSLIBS) $(SOCKLIBS) -lsctp 

EACC_LIBS= -L$(EACC_ROOT)/cmapi/idl/lib -lHAComponent -lHAComponentidl -lAlarmsidl \
			-L$(EACC_ROOT)/lib/debug -lmess -lblocks -ljsoncpp\
			-L$(EACC_ROOT)/3rdparty/lib -lprotobuf

SUBAGENT_LIB=-L$(IWF_ROOT)/subagent/lib \
			 -lsubagent

all: ../lib/libsubagent.so ../bin/subagent

../lib/libsubagent.so : $(OBJS)
	$(CXXSHAREDAR) $(SHAREDARFLAGS) $@ $(OBJS) $(ITS_LIBS) ${NOWHOLEARCHIVE}

../bin/subagent : $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $(LD_FLAGS) -o $@ $(OBJS) $(MAIN_OBJ) $(ITS_LIBS) \
      $(EACC_LIBS) $(SNMP_BUILDLIBS) $(SNMP_BUILDAGENTLIBS) $(SUBAGENT_LIB)

clean :
	$(RM) $(OBJS) $(MAIN_OBJ) ../lib/libsubagent.so ../bin/subagent

