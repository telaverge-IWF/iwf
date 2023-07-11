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
# ID: $Id: make.dirs.cc,v 3.1 2008/03/31 10:33:15 nvijikumar Exp $
#
# LOG: $Log: make.dirs.cc,v $
# LOG: Revision 3.1  2008/03/31 10:33:15  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.3  2008/03/27 11:47:56  hbhatnagar
# LOG: Converting 2.1 branch to CURRENT
# LOG:
# LOG: Revision 2.2.2.1  2007/03/15 05:02:21  rrath
# LOG: Changes for Solaris
# LOG:
# LOG: Revision 2.4  2007/02/19 06:24:05  nvijikumar
# LOG: Remove libssl library linking from all libs (Bridgewater issue).
# LOG:
# LOG: Revision 2.3  2006/11/03 13:53:03  nvijikumar
# LOG: 64 bit compilation support.
# LOG:
# LOG: Revision 2.2  2006/10/24 11:59:51  nvijikumar
# LOG: Included -lsctp library for SCTP support.
# LOG:
# LOG: Revision 2.1  2006/09/13 09:13:24  yranade
# LOG: Start GA 1.1
# LOG:
# LOG: Revision 1.2  2006/06/21 10:36:24  nvijikumar
# LOG: Modification for Copyright info.
# LOG:
# LOG: Revision 1.1  2006/06/02 12:48:56  yranade
# LOG: Added solaris flags
# LOG:
# LOG: Revision 1.2  2006/05/29 10:11:31  yranade
# LOG: Fix typo
# LOG:
# LOG: Revision 1.1  2006/05/26 14:26:33  yranade
# LOG: Add CC Compiler options
# LOG:
#
############################################################################
# Java Specifics
JAVACMD=java -jar
DIAJARFILE=$(IMS_ROOT)/mag/bin/diamag.jar

#
# Plaform Specifics... for Solaris 32bit 
#
ifeq ($(PLATFORM),solaris)
CXX=CC
CXXAR=CC
CXXARFLAGS=-xar -o
CXXSHAREDAR=CC
CXXSHAREDARFLAGS=-G -z allextract -o
ITS_DEFINES=-DUSE_HEAP -DHAVE_NAMESPACES -DHAVE_STD_NAMESPACE -DHAVE_THROW_SPECS -D_MIT_POSIX_THREADS -DHAVE_STL
DEFINES= -D_REENTRANT -DPLATFORM=$(PLATFORM) -D$(PLATFORM)
ITS_INCLS=-I$(ITS_ROOT)/common/include
INCLS=-I$(IMS_ROOT)/val/c++/include
CP=/bin/cp
SOFLAGS=-KPIC
SOCKLIBS=-lnsl -lsocket -lsctp
THREADLIBS=-lthread -lmtmalloc
SYSLIBS=-ldl -lrt 
CXXSHAREDARFLAGS=-G -z allextract -o
endif

#
# Plaform Specifics... for Solaris 64bit
#
ifeq ($(PLATFORM),solaris64)
CXX=CC -xtarget=ultra -xarch=v9
CXXAR=CC
CXXARFLAGS=-xar -o
CXXSHAREDAR=CC -xtarget=ultra -xarch=v9
CXXSHAREDARFLAGS=-G -z allextract -o
ITS_DEFINES=-DUSE_HEAP -DHAVE_NAMESPACES -DHAVE_STD_NAMESPACE -DHAVE_THROW_SPECS -D_MIT_POSIX_THREADS -DHAVE_STL
DEFINES= -D_REENTRANT -DPLATFORM=$(PLATFORM) -D$(PLATFORM)
ITS_INCLS=-I$(ITS_ROOT)/common/include
INCLS=-I$(IMS_ROOT)/val/c++/include
CP=/bin/cp
SOFLAGS=-KPIC
SOCKLIBS=-lnsl -lsocket -lsctp
THREADLIBS=-lthread -lmtmalloc
SYSLIBS=-ldl -lrt
CXXSHAREDARFLAGS=-G -z allextract -o
endif

# Plaform Specifics... for Linux
ifeq ($(PLATFORM),linux)
SOFLAGS=-fpic
SOCKLIBS=
THREADLIBS=-lpthread
SYSLIBS=-ldl -lrt 
CXXSHAREDARFLAGS=-shared -Wl,--whole-archive -o
endif

ifeq ($(DEBUG_BUILD),yes)
CXXFLAGS=    -g -w $(INCLS) $(DEFINES) -DDEBUG $(SOFLAGS)
DBGSUFFIX= D
else
CXXFLAGS=    -O $(INCLS) $(DEFINES) -DNDEBUG $(SOFLAGS)
DBGSUFFIX=
endif

