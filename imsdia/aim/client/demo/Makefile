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
#     FILE: Makefile                                                       #
#                                                                          #
############################################################################
#                                                                          #
# $Id: Makefile,v 3.2 2009/03/25 05:12:11 nvijikumar Exp $ 
#
# $Log: Makefile,v $
# Revision 3.2  2009/03/25 05:12:11  nvijikumar
# Removing sctp dependency for IDC
#
# Revision 3.1  2008/03/31 10:33:00  nvijikumar
# Start GA 3.0
#
# Revision 2.8  2007/01/17 06:57:18  nvijikumar
# Linking with nasreqapi shared library.
#
# Revision 2.7  2006/11/16 12:33:06  kamakshilk
# Removed EXPAT library linking
#
# Revision 2.6  2006/11/08 08:48:28  kamakshilk
# 64-bit compilation support
#
# Revision 2.5  2006/11/07 11:57:50  kamakshilk
# dframe and diastack libraries removed
#
# Revision 2.4  2006/10/29 05:45:02  kamakshilk
# API libraries for each interface linked
#
# Revision 2.3  2006/10/24 11:32:51  kamakshilk
# Changes to compile on solaris
#
# Revision 2.2  2006/10/16 14:23:57  kamakshilk
# Changes to work with ITS-Diameter APIs
#
# Revision 2.1  2006/09/13 09:22:38  yranade
# Start GA 1.1
#
# Revision 1.6  2006/06/22 05:54:55  yranade
# Correct path.
#
# Revision 1.5  2006/06/21 09:22:45  yranade
# Split diavendor into 2 libraries. libitsdia.a contains all vendor
# abstraction code, and the new libdiavendor contains linking of only
# open source libraries.
#
# Revision 1.4  2006/06/09 13:49:06  kamakshilk
# RfRo compilation addition
#
# Revision 1.3  2006/06/07 07:34:14  yranade
# No need to link ACE and ACE_SSL here
#
# Revision 1.2  2006/05/22 10:44:49  nvijikumar
# Changes for Binary Name.
#
# Revision 1.1  2006/04/13 11:08:06  nvijikumar
# Baseline demo programs
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

CXXFLAGS:=$(CXXFLAGS) -g -I./ -DUNIX \
        -I../include \
	-I$(ITS_ROOT)/common/include \
	-I$(IMS_ROOT)/common/include \
        -I$(IMS_ROOT)/api/c++/include 

IMS_LIBS:=-lbaseapi$(DBGSUFFIX) \
          -lcxdxapi$(DBGSUFFIX) \
          -lshapi$(DBGSUFFIX)   \
          -lgqgqapi$(DBGSUFFIX) \
          -lrfroapi$(DBGSUFFIX) \
          -lnasreqapi$(DBGSUFFIX)

ifeq ($(PLATFORM),solaris)
LIBS_OS:= -ldiaval$(DBGSUFFIX) \
	 $(IMS_LIBS) \
         -lIDSClient$(DBGSUFFIX)
endif
ifeq ($(PLATFORM),solaris64)
LIBS_OS:= -ldiaval$(DBGSUFFIX) \
	 $(IMS_LIBS) \
         -lIDSClient$(DBGSUFFIX)
endif
ifeq ($(PLATFORM),linux)
LIBS_OS:= $(IMS_LIBS) \
         -ldiaval$(DBGSUFFIX) \
         -lIDSClient$(DBGSUFFIX)
endif

LIBS:= $(ITS_LIBS) \
            -L$(ITS_ROOT)/common/lib \
            -L../lib \
            -L../../../api/c++/lib \
            -L../../../val/c++/lib \
            $(LIBS_OS) \

OBJS:= app.o sample_base.o sample_cxdx.o sample_sh.o sample_gq.o sample_rfro.o app_main.o

# Restrict the user to give explicit targets
all: sampleClient$(DBGSUFFIX)

sampleClient$(DBGSUFFIX): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) -o \
	$@ $(OBJS) $(LIBS) -lpthread $(SYSLIBS) -ldl

clean:
	$(RM) client $(OBJS) 

