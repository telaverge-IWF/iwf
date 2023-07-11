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
# ID: $Id: Makefile,v 3.17.4.1.2.5.4.3.2.1.2.1.4.1 2014/02/12 07:13:41 millayaraja Exp $ 
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.17.4.1.2.5.4.3.2.1.2.1.4.1  2014/02/12 07:13:41  millayaraja
# LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
# LOG:
# LOG: Revision 3.17.4.1.2.5.4.3.2.1.2.1  2013/10/26 07:42:21  ncshivakumar
# LOG: RFC 6733 changes
# LOG:
# LOG: Revision 3.17.4.1.2.5.4.3.2.1  2013/07/04 10:54:43  ncshivakumar
# LOG: Updated for TPS based licensning
# LOG:
# LOG: Revision 3.17.4.1.2.5.4.3  2013/04/18 11:35:27  cprem
# LOG: Fixed compilation
# LOG:
# LOG: Revision 3.17.4.1.2.5.4.2  2013/04/18 07:05:21  jvikram
# LOG: Included changes related to log segregation.
# LOG:
# LOG: Revision 3.17.4.1.2.5.4.1  2013/03/22 05:46:12  jvikram
# LOG: Includes files to be compiled related to message queue implementation for handling of incoming messages within
# LOG: same session.
# LOG:
# LOG: Revision 3.17.4.1.2.5  2013/01/08 02:24:07  cprem
# LOG: Added include path for Errors.
# LOG:
# LOG: Revision 3.17.4.1.2.4  2012/12/21 05:31:54  ncshivakumar
# LOG: Modified for tracing
# LOG:
# LOG: Revision 3.17.4.1.2.3  2012/12/03 08:41:20  ncshivakumar
# LOG: Changes done for adding static routing table
# LOG:
# LOG: Revision 3.17.4.1.2.2  2012/09/06 11:30:45  jvikas
# LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
# LOG:
# LOG: Revision 3.17.4.1.2.1.2.2  2012/08/27 11:05:00  cprem
# LOG: Added json.h includes for compilation.
# LOG:
# LOG: Revision 3.17.4.1.2.1.2.1  2012/08/21 06:16:25  jvikas
# LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
# LOG:
# LOG: Revision 3.17.4.1.2.1  2012/08/10 10:23:15  jvikas
# LOG: "Added dia_msg_flow"
# LOG:
# LOG: Revision 3.17.4.1  2012/06/22 03:55:30  ncshivakumar
# LOG: TLS compilation changes
# LOG:
# LOG: Revision 3.17  2010/06/30 08:54:26  nvijikumar
# LOG: TLS dynamic lib not required to link here
# LOG:
# LOG: Revision 3.16  2009/06/29 14:54:53  rajeshak
# LOG: Changes done for performance enhancement (splitting the session table).
# LOG:
# LOG: Revision 3.15  2009/04/14 08:45:35  rajeshak
# LOG: changes for compilation error on windriver.
# LOG:
# LOG: Revision 3.14  2009/04/13 13:38:57  rajeshak
# LOG: Peer Discovery changes.
# LOG:
# LOG: Revision 3.13  2009/02/05 05:23:54  nvijikumar
# LOG: Compile time option to make USE_SELECT define
# LOG:
# LOG: Revision 3.12  2009/02/04 06:18:28  nvijikumar
# LOG: making libdiaredirect as static instead of shared lib
# LOG:
# LOG: Revision 3.11  2009/02/03 10:21:11  ssaxena
# LOG: Modifications done for Redirect Agent functionality.
# LOG:
# LOG: Revision 3.10  2009/01/02 09:17:59  nvijikumar
# LOG: Fix for TLS compilation/linking issue
# LOG:
# LOG: Revision 3.9  2008/12/12 08:02:50  sureshj
# LOG: Support for Stack statistics
# LOG:
# LOG: Revision 3.8  2008/12/07 09:52:23  rajeshak
# LOG: Added dia_relay.cpp and dia_proxy.cpp under compilation targets
# LOG:
# LOG: Revision 3.7  2008/08/12 04:23:52  nvijikumar
# LOG: Defined NOWHOLEARCHIVE to remove libc_nonshared dependency. gdalawai
# LOG:
# LOG: Revision 3.6  2008/08/06 11:48:51  vnarang
# LOG: Changes to build seperate lib and bin for TLS
# LOG:
# LOG: Revision 3.5  2008/07/31 06:15:21  sureshj
# LOG: Tls Path Inclusion is Put into condition
# LOG:
# LOG: Revision 3.4  2008/07/14 06:32:06  vnarang
# LOG: Removing inclusion of third party libraries as ssl & gnutls liraries are already included in ITS-TLS
# LOG:
# LOG: Revision 3.3  2008/07/09 14:07:44  vnarang
# LOG: TLS Compilation is put under copilation option TLS
# LOG:
# LOG: Revision 3.2  2008/06/13 11:20:36  hbhatnagar
# LOG: Made changes to add the gnutls library and headers path
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.15  2008/03/27 12:14:08  hbhatnagar
# LOG: Converting 2.1 branch to CURRENT
# LOG:
# LOG: Revision 2.13.4.1  2007/12/14 11:24:48  hbhatnagar
# LOG: Removed the DeviceWatchDog Timer related functionality and added
# LOG: WatchDog Transport Thread related functionality.
# LOG:
# LOG: Revision 2.13  2007/01/22 07:32:49  nanaparthi
# LOG: Target added for Dynamic Configuration support
# LOG:
# LOG: Revision 2.12  2007/01/04 14:33:29  nvijikumar
# LOG: Setting correct falg for DEFINES.
# LOG:
# LOG: Revision 2.11  2006/12/20 14:57:42  tpanda
# LOG: Other bug fixes related to redundancy(Issue#5075,5073,5069,5057 etc)
# LOG:
# LOG: Revision 2.10  2006/12/11 13:51:25  tpanda
# LOG: REDUNDANCY_SLOT_CHANGES are removed and code seems to be stable
# LOG:
# LOG: Revision 2.9  2006/12/10 13:42:42  tpanda
# LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
# LOG:
# LOG: Revision 2.8  2006/11/16 14:49:16  tpanda
# LOG: Redundancy support for ITS-Diameter--Baseline code
# LOG:
# LOG: Revision 2.7  2006/11/07 11:43:30  tpanda
# LOG: codec so generation target removed
# LOG:
# LOG: Revision 2.6  2006/11/07 11:18:01  tpanda
# LOG: codec library separated from stack library
# LOG:
# LOG: Revision 2.5  2006/10/28 07:46:42  yranade
# LOG: Library linking reorganisation, codec lib separated from stack
# LOG:
# LOG: Revision 2.4  2006/10/25 05:50:38  hbhatnagar
# LOG: Integration with ITS_Diameter First Cut (badri)
# LOG:
# LOG: Revision 2.3  2006/10/05 13:30:26  yranade
# LOG: Add Copyright info.
# LOG:
#
###########################################################################
#
# Include the standard definitions
#
include $(IMS_ROOT)/make.dirs

DEFINES:=$(ITS_DEFINES) $(DEFINES) -D_$(PLATFORM) -DJSON_IS_AMALGAMATION -std=c++0x

ifeq ($(USE_SELECT),yes)
DEFINES := $(DEFINES) -DUSE_SELECT
endif

ifeq ($(TLS),yes)
DEFINES:=$(DEFINES) -DTLS_ENABLED
#TLSLIBS:= -L$(ITS_ROOT)/tls/lib/  -lITS-TLS$(DBGSUFFIX)
TLSLIBS:= -L$(ITS_ROOT)/tls/lib/  -lITS-TLS$(DBGSUFFIX)
TLSINCLS= -I$(ITS_ROOT)/tls/include \
          -I$(OPENSSL_ROOT)/include \
          -I$(GNUTLS_ROOT)/includes 
endif

INCLS:=$(ITS_INCLS) $(TLSINCLS) \
        -I../include \
        -I../dcca/include \
        -I../../../common/include \
        -I$(ITS_ROOT)/common/include \
        -I$(ITS_ROOT)/ENGINE/include \
        -I../../../val/c++/include  \
        -I../../../api/c++/include  \
        -I../../../api/c++/include/diameter/base \
        -I$(IMS_ROOT)/dtf/include \
	-I$(EACC_ROOT)/blocks/include \
		-I$(EACC_ROOT)/3rdparty/jsoncpp_0.6.0-rc2 \
		-I$(EACC_ROOT)/3rdparty/include \
		-I$(EACC_ROOT)/utils/rule/include \
		-I$(EACC_ROOT)/cmapi/common \
		-I$(EACC_ROOT)/cmapi/alarms/include \
		-I$(EACC_ROOT)/mess/include \
		-I$(EACC_ROOT)/cmapi/idl

#SOURCES=$(wildcard *.cpp)

#SO_OBJS=$(SOURCES:.cpp=.o)

SO_OBJS=dia_acceptor.o dia_connector.o dia_downstream.o dia_incoming_msg_q.o\
	dia_err_handler.o dia_ip_trans.o dia_msg_router.o \
        dia_parse.o dia_peer_fsm.o dia_peer_states.o \
        dia_peer_table.o dia_pending_q.o dia_proxy.o dia_realm_table.o \
        dia_relay.o dia_session_acct_fsm.o dia_session_acct_states.o \
        dia_session_auth_fsm.o dia_session_auth_states.o \
        dia_session_table.o dia_stack.o dia_timer_handler.o \
        dia_upstream.o dia_utils.o its_dia_config.o  \
        dia_mgmt.o dia_wd_trans.o dia_stack_stats.o dia_cache_table.o \
        dia_dns_query.o dia_peer_discovery.o dia_msg_flow.o dia_tracer.o\
		dia_static_routing_table.o dia_rate_filter.o dia_stack_alarms.o \
		dia_capabilities_update_application.o

#
# Library base name
#
ifeq ($(TLS),yes)
LIBRARY=../lib/libdiastackt
else
LIBRARY=../lib/libdiastack
endif

CODEC_LIBRARY :=../lib/libdiacodec

REDIRECT_LIBRARY :=../lib/libdiaredirect


#
# Targets
#
.PHONY: all clean

all: $(CODEC_LIBRARY)$(DBGSUFFIX).a $(REDIRECT_LIBRARY)$(DBGSUFFIX).a \
	$(LIBRARY)$(DBGSUFFIX).so 

clean:
	rm -f $(LIBRARY)$(DBGSUFFIX).so $(SO_OBJS) \
        itsdiameter.o dia_dict_parse.o \
        $(CODEC_LIBRARY)$(DBGSUFFIX).a \
	$(REDIRECT_LIBRARY)$(DBGSUFFIX).a \
	dia_redirect.o

$(LIBRARY)$(DBGSUFFIX).so: $(SO_OBJS)
	$(CXXSHAREDAR) $(SOFLAGS) $(CXXSHAREDARFLAGS)  $(LIBRARY)$(DBGSUFFIX).so \
	$(SO_OBJS)  $(NOWHOLEARCHIVE) $(CODEC_LIBRARY)$(DBGSUFFIX).a  \
        $(REDIRECT_LIBRARY)$(DBGSUFFIX).a $(TLSLIBS) $(DNSLIB) -L$(IMS_ROOT)/common/lib -ldiacommon$(DBGSUFFIX) -L$(ITS_ROOT)/common/lib -lCORE

$(CODEC_LIBRARY)$(DBGSUFFIX).a:itsdiameter.o dia_dict_parse.o
	$(CXXAR) $(CXXARFLAGS) $@ $^

$(REDIRECT_LIBRARY)$(DBGSUFFIX).a:dia_redirect.o
	$(CXXAR) $(CXXARFLAGS) $@ $^
