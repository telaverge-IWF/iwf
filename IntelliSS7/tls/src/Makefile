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
#ID: $Id: Makefile,v 1.1.4.2 2013/11/12 07:51:34 jvikram Exp $
#
############################################################################

#
# get the vars
#

include $(ITS_ROOT)/config.vars

CXXFLAGS := $(CXXFLAGS) $(TLSINCLS) -I../include -I/usr/sfw/include

ifeq ($(USE_ONLY_SSL),yes)
CXXFLAGS := $(CXXFLAGS) -DUSE_ONLY_SSL
TLSLIB=libITS-SSLTLS
TLSOBJS= its_tls_factory.o its_ssl_tls_session.o CAu.o CRL.o its_ssl_tls_thread_support.o
TLSLIBS:= -L/usr/sfw/lib -L$(OPENSSL_ROOT) -lssl 
else
TLSOBJS= its_tls_factory.o its_gnu_tls_session.o its_ssl_tls_session.o CRL.o CAu.o its_ssl_tls_thread_support.o
TLSLIB=libITS-TLS
endif


.PHONY: links

all: links  ../lib/$(TLSLIB)$(DBGSUFFIX).a  ../lib/$(TLSLIB)$(DBGSUFFIX).so
clean:
	$(RM) *.o .depend \
		../lib/$(TLSLIB)$(DBGSUFFIX).a \
		../lib/$(TLSLIB)$(DBGSUFFIX).so 

../lib/$(TLSLIB)$(DBGSUFFIX).a: $(TLSOBJS)
	$(CXXAR) $(CXXARFLAGS) $@ $(TLSOBJS) 

../lib/$(TLSLIB)$(DBGSUFFIX).so: $(TLSOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $@ $(TLSOBJS) $(TLSLIBS) $(NOWHOLEARCHIVE)


