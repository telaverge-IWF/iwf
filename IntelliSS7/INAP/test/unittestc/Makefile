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
# CONTRACT: ETRI                                                           #
#                                                                          #
############################################################################

PLATFORM=DECUNIX
PROTOCOL=CCITT

#
# for Alpha
#
AR=        ar
CXXAR=     ar
ARFLAGS=   cruv
CXXARFLAGS=cruv
CP=        cp
RM=        rm -f
CC=        cc
LD=        cxx
MV=        mv
MKDIR=     mkdir
CXX=       cxx
INCLS=     -I.
DEFINES=   -DDECSS7 -D$(PROTOCOL) -DPLATFORM=$(PLATFORM) -D$(PLATFORM) \
           -Dunix -D_REENTRANT \
           -DHAVE_NAMESPACES -DHAVE_STD_NAMESPACE -DHAVE_THROW_SPECS \
           -DUSING_FLEX $(DNSDEFS)
SOCKLIBS=
THREADLIBS=
SYSLIBS=   

#
# ifeq ($(DEBUG_BUILD),yes)
#
CFLAGS=    -pthread -std1 -g2 $(INCLS) $(DEFINES) -DDEBUG \
           -I../include -L../lib -L/usr/opt/SS7CCITT31C/shlib
DBGSUFFIX= D
#
# else
# CFLAGS=    -pthread -std1 -O $(INCLS) $(DEFINES)
#            -I../include -L../lib -L/usr/opt/SS7CCITT31C/shlib
 
# DBGSUFFIX=
# endif

LDFLAGS=   -pthread

SOBJS= INAPSendMain.o inaptest.o
ROBJS= INAPReceiveMain.o inaptest.o
 
LIBS = -lVENDOR$(DBGSUFFIX) -lSCORE$(DBGSUFFIX)  \
        -lINAP$(DBGSUFFIX) -lCCITT-TCAP$(DBGSUFFIX) \
	-lCCITT-SCCP$(DBGSUFFIX) -lCCITT-MTP3$(DBGSUFFIX) -lASN$(DBGSUFFIX) \
	-lss7_gtt_ccitt -lss7_netport_ccitt -lss7_tcapport_ccitt \
        -lpthread

all: send recv

clean:
	$(RM) $(ROBJS) $(SOBJS) send recv

send: $(SOBJS)  \
	$(ITS_ROOT)/INAP/lib/libINAPD.a \
	$(ITS_ROOT)/TCAP/lib/libCCITT-TCAP.a \
	$(ITS_ROOT)/SCCP/lib/libCCITT-SCCP.a \
	$(ITS_ROOT)/MTP3/lib/libCCITT-MTP3.a \
	$(ITS_ROOT)/common/lib/libSUPPORT.a \
	$(ITS_ROOT)/common/lib/libSCORE.a \
	$(ITS_ROOT)/common/lib/libASN.a \
        /usr/opt/SS7CCITT31C/shlib/libs7mp_bis_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libs7mp_cli_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libs7mp_iol_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_gtt_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_gupport_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_inap_srf_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_mgtport_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_netport_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_snmp.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_starlet.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_tcapport_ccitt.so \
	$(VENDOR_ROOT)/newalpha/lib/libVENDOR$(DBGSUFFIX).a 
	$(CC) $(CFLAGS) -o send $(SOBJS) \
		$(LIBS) $(SOCKLIBS) $(THREADLIBS)

recv: $(ROBJS)  \
	$(ITS_ROOT)/INAP/lib/libINAPD.a \
	$(ITS_ROOT)/TCAP/lib/libCCITT-TCAP.a \
	$(ITS_ROOT)/SCCP/lib/libCCITT-SCCP.a \
	$(ITS_ROOT)/MTP3/lib/libCCITT-MTP3.a \
	$(ITS_ROOT)/common/lib/libSUPPORT.a \
	$(ITS_ROOT)/common/lib/libSCORE.a \
	$(ITS_ROOT)/common/lib/libASN.a \
        /usr/opt/SS7CCITT31C/shlib/libs7mp_bis_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libs7mp_cli_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libs7mp_iol_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_gtt_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_gupport_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_inap_srf_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_mgtport_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_netport_ccitt.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_snmp.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_starlet.so \
        /usr/opt/SS7CCITT31C/shlib/libss7_tcapport_ccitt.so \
	$(VENDOR_ROOT)/newalpha/lib/libVENDOR$(DBGSUFFIX).a 
	$(CC) $(CFLAGS) -o recv $(ROBJS) \
		$(LIBS) $(SOCKLIBS) $(THREADLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
