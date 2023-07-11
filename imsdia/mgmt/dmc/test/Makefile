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
# $Id: Makefile,v 1.1 2009/03/02 04:39:44 nvijikumar Exp $ 
#
# $Log: Makefile,v $
# Revision 1.1  2009/03/02 04:39:44  nvijikumar
# Initial draft for MML API Support
#
#
############################################################################

include	$(IMS_ROOT)/make.dirs

DEFINES:=$(DEFINES) -DDUMP $(ITS_DEFINES)

CXXFLAGS:=$(CXXFLAGS) -g -I./include -DUNIX \
        $(ACE_INC) $(DIA_INC) $(BST_INC)\
        -I../include \
	-I$(ITS_ROOT)/common/include 


LIBS:= -L$(ITS_ROOT)/common/lib  \
        -L../lib \
	-lDMClient$(DBGSUFFIX) 

        

OBJS:= dmc_test.o

# Restrict the user to give explicit targets
all: dmcTest

dmcTest: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) -o \
	$@ $(OBJS) $(LIBS) -lpthread $(SOCKLIBS) $(SYSLIBS) -ldl -lresolv

clean:
	$(RM) dmcTest $(OBJS) 

