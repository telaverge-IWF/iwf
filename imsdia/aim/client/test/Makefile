############################################################################
#                                                                          #
#     Copyright 2003 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
#     FILE: Makefile                                                       #
#                                                                          #
############################################################################
#                                                                          #
# $Id: Makefile,v 3.1 2008/03/31 10:33:03 nvijikumar Exp $ 
#
# $Log: Makefile,v $
# Revision 3.1  2008/03/31 10:33:03  nvijikumar
# Start GA 3.0
#
# Revision 2.1  2006/09/13 09:22:39  yranade
# Start GA 1.1
#
# Revision 1.6  2006/05/08 13:02:32  yranade
# Updates to build client library and test program.
#
# Revision 1.5  2006/04/07 14:06:17  adutta
# Included Boost header path
#
# Revision 1.4  2006/03/16 13:12:06  nvijikumar
# Included IMSTOOLS include dirs to make it work with ACE static libs
#
# Revision 1.3  2006/03/14 09:49:09  adutta
# Libs added
#
# Revision 1.2  2006/03/02 12:46:54  adutta
# Remove ITS config.vars
#
# Revision 1.1  2006/03/02 12:14:25  adutta
# First cut
#
# Revision 1.1  2005/05/25 10:13:59  mmanikandan
# Initial Commit Multiple Application Binding.
#
#
############################################################################

include	$(IMS_ROOT)/make.dirs

DEFINES:=$(DEFINES) -DDUMP $(ITS_DEFINES)

CXXFLAGS:=$(CXXFLAGS) -g -I./include -DUNIX \
        $(ACE_INC) $(DIA_INC) $(BST_INC)\
        -I../include \
	-I$(ITS_ROOT)/common/include \
	-I$(IMS_ROOT)/common/include \
	-I$(IMS_ROOT)/dframe/include \
        -I$(IMS_ROOT)/api/c++/include/ \
	-I$(IMS_ROOT)/vendors/opendiameter/include 


LIBS:= -L$(ITS_ROOT)/common/lib  \
	-L$(IMS_ROOT)/dframe/lib  \
	-L$(IMS_ROOT)/api/c++/lib  \
	-L$(IMS_ROOT)/val/c++/lib  \
	-L$(IMS_ROOT)/vendors/opendiameter/lib  \
        -L../lib \
	$(XER_LIB) $(ACE_LIB) \
	-ldiaapi$(DBGSUFFIX) \
	-ldiaval$(DBGSUFFIX) \
	-ldiavendor$(DBGSUFFIX) \
	-lACE -lACE_SSL  -lxerces-c \
	-lIDSClient$(DBGSUFFIX)
        

OBJS:= client.o

# Restrict the user to give explicit targets
all: client

client: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) -o \
	$@ $(OBJS) $(LIBS) -lpthread $(SOCKLIBS) $(SYSLIBS) -ldl -lresolv

clean:
	$(RM) client $(OBJS) 

