###############################################################################
#                                                                              #
#      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.       #
#              Manufactured in the United States of America.                   #
#        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.          #
#                                                                              #
#     This product and related documentation is protected by copyright and     #
#     distributed under licenses restricting its use, copying, distribution    #
#     and decompilation.  No part of this product or related documentation     #
#     may be reproduced in any form by any means without prior written         #
#     authorization of IntelliNet Technologies and its licensors, if any.      #
#                                                                              #
#     RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the        #
#     government is subject to restrictions as set forth in subparagraph       #
#     (c)(1)(ii) of the Rights in Technical Data and Computer Software         #
#     clause at DFARS 252.227-7013 and FAR 52.227-19.                          #
#                                                                              #
################################################################################
#                                                                              #
# CONTRACT: Internal                                                           #
#                                                                              #
################################################################################
#
#                           README
#  1.) Need to specify M3UA version to build binaries. default is M3UA ver 10.
#
#  ID: $Id: Makefile,v 1.2 2005/07/19 00:43:19 randresol Exp $
#
################################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

#stats_record.o
SGAS_OBJS=sua_common.o sua_sgp.o sua_asp.o sua_sccp_msgs.o sua_sccp_test.o sccp_pprint.o
MAIN_OBJS=sua_main.o
#TEMP_OBJS=fix.o

ITS_LIBS=-L. -L../../lib  -L$(VENDOR_ROOT)/IntelliNet/lib -L$(ITS_ROOT)/common/lib \
            -lENGINE$(DBGSUFFIX) -lDRIVER++$(DBGSUFFIX)  \
            -lDISPATCH++$(DBGSUFFIX) \
            -lVFrame$(DBGSUFFIX) \
            -lDBGServer$(DBGSUFFIX)\
            -lUAL$(DBGSUFFIX) \
            -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
            -lrt

LINK_FLAG = -L$(ITS_ROOT)/common/lib -L$(ITS_ROOT)/GSMMAP/lib \
	    -L$(VENDOR_ROOT)/IntelliNet/lib -L$(ITS_ROOT)/TCAP/lib \
            -L$(ITS_ROOT)/ISUP/lib \
	    -L$(ITS_ROOT)/SCCP/lib -L$(ITS_ROOT)/MTP3/lib \
            -L$(ITS_ROOT)/MTP2/lib


CXXFLAGS := $(CXXFLAGS) -D$(PROTOCOL) -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/common/include/asn-cpp \
          -I$(ITS_ROOT)/GSMMAP/include/itu \
	  -I$(ITS_ROOT)/TCAP/include \
	  -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/ISUP/include \
	  -I$(ITS_ROOT)/MTP3/include \
	  -I$(ITS_ROOT)/MTP2/include \
	  -I../include \
	  -DUSE_INTELLINET_STACK \
	  -DUSE_SOCKETS \
          -D$(PROTOCOL)

all : $(TEMP_OBJS) libSUA-TEST$(DBGSUFFIX).so sua_test$(DBGSUFFIX)

sua_test$(DBGSUFFIX) : $(MAIN_OBJS)
	$(CXX) $(LD_FLAGS) $(LINK_FLAG) -o $@ $(MAIN_OBJS) $(ITS_LIBS) $(SOCKLIBS) \
        $(THREADLIBS) $(SYSLIBS) libSUA-TEST$(DBGSUFFIX).so

libSUA-TEST$(DBGSUFFIX).so: $(SGAS_OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) $@ $(SGAS_OBJS) $(ITS_LIBS)

clean :
	$(RM) $(SGAS_OBJS) sua_test$(DBGSUFFIX) libSUA-TEST$(DBGSUFFIX).so
#
# get the rules
#
include $(ITS_ROOT)/config.rules

