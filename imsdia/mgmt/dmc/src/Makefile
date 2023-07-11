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
# ID: $Id: Makefile,v 1.5 2010/04/29 06:42:59 nvijikumar Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 1.5  2010/04/29 06:42:59  nvijikumar
# LOG: Fix for compilation issue on Sun CC - version 12 [Viji]
# LOG:
# LOG: Revision 1.4  2009/10/16 05:47:18  sureshj
# LOG: removing dm_msgs.h from dmc/include in make clean.
# LOG:
# LOG: Revision 1.3  2009/04/11 05:33:53  nvijikumar
# LOG: Provided realclean target
# LOG:
# LOG: Revision 1.2  2009/03/04 11:41:12  nvijikumar
# LOG: FIx for Compilation issue
# LOG:
# LOG: Revision 1.1  2009/03/02 04:39:44  nvijikumar
# LOG: Initial draft for MML API Support
# LOG:
# LOG:
############################################################################
#
# get the vars
#
include $(IMS_ROOT)/make.dirs

CXXFLAGS:=$(CXXFLAGS) $(ITS_DEFINES) -g -I./include -DUNIX \
	-I$(ITS_ROOT)/common/include    \
        -I../include -DIDS_PATTERN

LIBS:= -L$(ITS_ROOT)/common/lib \
       -lCORE$(DBGSUFFIX) \
       -lSUPPORT$(DBGSUFFIX) -lresolv 

SOURCES=$(wildcard *.cpp)
COBJS:= $(SOURCES:.cpp=.o)

# Restrict the user to give explicit targets
all:  links ../lib/libDMClient$(DBGSUFFIX).so 

links:
	if [ -d $(IMS_ROOT)/mgmt/dms ]; then				\
		if [ ! -f $(IMS_ROOT)/mgmt/dmc/include/dm_msgs.h ]; then\
			ln $(IMS_ROOT)/mgmt/dms/include/dm_msgs.h 	\
			 $(IMS_ROOT)/mgmt/dmc/include/dm_msgs.h;	\
		fi							\
	fi;


../lib/libDMClient$(DBGSUFFIX).so: $(COBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
	$@ $(COBJS) $(LIBS) $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS) \
	$(NOWHOLEARCHIVE)


clean:
	$(RM) ../lib/libDMClient$(DBGSUFFIX).so $(COBJS) 
	$(RM) $(IMS_ROOT)/mgmt/dmc/include/dm_msgs.h

realclean:
	$(RM) ../lib/libDMClient$(DBGSUFFIX).so $(COBJS) \	
	$(RM) $(IMS_ROOT)/mgmt/dmc/include/dm_msgs.h
