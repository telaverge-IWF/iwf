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
# ID: $Id: Makefile,v 1.9 2011/04/08 08:56:32 vnagender Exp $
#
#
############################################################################
#
# Include the standard definitions
#

include $(ITS_ROOT)/config.vars

CFLAGS:=$(CFLAGS) -I. -I$(ITS_ROOT)/common/include -I$(SUBAGENT_PATH)/include \
                  -I../include 

ifeq ($(USE_SOL_SNMP),yes)
ifeq ($(PLATFORM),solaris64)
SNMP_BUILDLIBS=-L/usr/sfw/lib/sparcv9/ -lnetsnmp
SNMP_BUILDAGENTLIBS=/usr/sfw/lib/sparcv9/libnetsnmpagent.a \
                    /usr/sfw/lib/sparcv9/libnetsnmpmibs.a \
                    /usr/sfw/lib/sparcv9/libnetsnmphelpers.a \
                    $(SNMP_BUILDLIBS)
CFLAGS:=$(CFLAGS) -I. -I/usr/sfw/include -D_SOL_SNMP_
else
SNMP_BUILDLIBS=-L/usr/sfw/lib/ -lnetsnmp
SNMP_BUILDAGENTLIBS=/usr/sfw/lib/libnetsnmpagent.a \
                    /usr/sfw/lib/libnetsnmpmibs.a \
                    /usr/sfw/lib/libnetsnmphelpers.a \
                    $(SNMP_BUILDLIBS)
CFLAGS:=$(CFLAGS) -I. -I/usr/sfw/include -D_SOL_SNMP_
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
CFLAGS:=$(CFLAGS) -I. -I/usr/include/net-snmp
else
SNMP_BUILDLIBS=-L$(SNMP_ROOT)/snmplib/.libs/ -lnetsnmp
SNMP_BUILDAGENTLIBS=$(SNMP_ROOT)/agent/.libs/libnetsnmpagent.a \
                    $(SNMP_ROOT)/agent/.libs/libnetsnmpmibs.a \
                    $(SNMP_ROOT)/agent/helpers/.libs/libnetsnmphelpers.a \
                    $(SNMP_BUILDLIBS)
CFLAGS:=$(CFLAGS) -I. -I$(SNMP_ROOT)/include
endif
endif


MAIN_OBJ = subagent.o

OBJS = stacks.o

ITS_LIBS := -L$(ITS_ROOT)/common/lib \
            -lSUPPORT$(DBGSUFFIX) \
            -lCORE$(DBGSUFFIX) \
             $(ITS_LIBS) $(THREADLIBS) $(SYSLIBS) $(SOCKLIBS) -lsctp 

all: ../lib/libsubagent.so ../bin/subagent

../lib/libsubagent.so : $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) $@ $(OBJS) $(ITS_LIBS) ${NOWHOLEARCHIVE}

../bin/subagent : $(OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(LD_FLAGS) -o $@ $(OBJS) $(MAIN_OBJ) $(ITS_LIBS) \
        $(SNMP_BUILDLIBS) $(SNMP_BUILDAGENTLIBS) ../lib/libsubagent.so

clean :
	$(RM) $(OBJS) $(MAIN_OBJ) ../lib/libsubagent.so ../bin/subagent

