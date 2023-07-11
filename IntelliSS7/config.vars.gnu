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
#  ID: $Id: config.vars.gnu,v 9.2.20.1 2011/04/13 07:47:03 nvijikumar Exp $
#
# LOG: $Log: config.vars.gnu,v $
# LOG: Revision 9.2.20.1  2011/04/13 07:47:03  nvijikumar
# LOG: Updates for compilation
# LOG:
# LOG: Revision 9.2  2008/05/09 14:48:50  kramesh
# LOG: NOWHOLEARCHIVE flag added for ES4.0 compilation.
# LOG:
# LOG: Revision 9.1  2005/03/23 12:51:01  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:49:06  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.7  2002/11/04 20:24:35  mmiers
# LOG: Get GCC flags right
# LOG:
# LOG: Revision 7.6  2002/10/30 20:39:56  mmiers
# LOG:
# LOG: Fix flags
# LOG:
# LOG: Revision 7.5  2002/10/30 20:34:08  mmiers
# LOG: Fix linkage issues.
# LOG:
# LOG: Revision 7.4  2002/10/28 20:00:53  mmiers
# LOG: Finish 64 bit cleanup.
# LOG:
# LOG: Revision 7.3  2002/10/25 21:54:20  mmiers
# LOG: Get the flags right
# LOG:
# LOG: Revision 7.2  2002/10/25 20:25:46  mmiers
# LOG: Kill dead file, add 64 bit target
# LOG:
# LOG: Revision 7.1  2002/08/26 22:08:32  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 1.2  2002/05/20 15:40:59  sjaddu
# LOG: Merge from PR6.
# LOG:
# LOG: Revision 1.1.2.1  2002/04/19 20:26:05  labuser
# LOG: Baseline.
# LOG:
#
############################################################################

#
# these variables must be set elsewhere
#
# PROTOCOL=[CCITT|ANSI] - which protocol family to use
# PLATFORM=[solaris|QNX|HPUX|DECUNIX|linux] - platform dependent flags
# ITS_ROOT=[?] - the directory containing this file
# ENABLE_DNS=[yes|no] - whether socket calls should use the resolver lib
# DEBUG_BUILD=[yes|no] - whether to include symbols and extra debug emit
#
# some of these will be defaulted:
#
# PROTOCOL=ANSI
# ENABLE_DNS=no
# DEBUG_BUILD=no
#

#
# whose version?
#
ifeq ($(PROTOCOL),)
PROTOCOL=ANSI
endif

#
# about DNS...
#
ifeq ($(ENABLE_DNS),yes)
DNSDEFS= -DUSE_DNS
else
DNSDEFS=
endif

#
# need to set the DSM type.  Usually this will be stub
#
DSMTYPE=STUB

#
# the platform must be set in the environment.  The structure of this file
# assumes a "make" that understands conditionals.  That may be only GNU
# make, but as we assume GNU C++ or compatible, that's ok.
#

#
# for QNX
#
ifeq ($(PLATFORM),QNX)

AR=        ar
CXXAR=     ar
ARFLAGS=   cruv
CXXARFLAGS=cruv
CP=        cp
RM=        rm -f
CC=        cc
LD=        ld
CXX=
ASNC=      $(ITS_ROOT)/tools/bin/asnc
ASNCFLAGS= -A -a -f
MV=        mv
LN=        ln -s
MKDIR=     mkdir
INCLS=     -I. -I$(ITS_ROOT)/common/include
DEFINES=   -DDATAKIN -D$(PROTOCOL) -DPLATFORM=$(PLATFORM) $(DNSDEFS)
SOCKLIBS=
THREADLIBS=
SYSLIBS=   
OEXT=      o
YACC=      yacc
LEX=       lex
LEXLIB=    -ll
EXC=       $(ITS_ROOT)/tools/bin/exc

ifeq ($(DEBUG_BUILD),yes)
CFLAGS=    -Oile=100 -g2 $(INCLS) -DDEBUG
CXXFLAGS=  -Oile=100 -g2 $(INCLS) -DDEBUG
ASNRTCFLAGS=    -Oile=100 $(INCLS) -DDEBUG
ASNRTCXXFLAGS=  -Oile=100 $(INCLS) -DDEBUG
DBGSUFFIX= D
else
CFLAGS=    -Oile=100 $(INCLS)
CXXFLAGS=  -Oile=100 $(INCLS)
ASNRTCFLAGS=    $(CFLAGS)
ASNRTCXXFLAGS=  $(CXXFLAGS)
DBGSUFFIX=
endif

#
# end QNX
#
endif

#
# for NMS
#
ifeq ($(PLATFORM),NT)
AR=        echo
CXXAR=     echo
ARFLAGS=
CXXARFLAGS=
CP=        cp
RM=        rm -f
CC=        cl.exe
CXX=       cl.exe
ASNC=      $(ITS_ROOT)/tools/bin/asnc
ASNCFLAGS= -A -a -f
LD=        link.exe
MV=        copy
LN=        copy
MKDIR=     mkdir
INCLS=     -I. -I$(ITS_ROOT)/common/include
DEFINES=   -DNMS -D$(PROTOCOL) -Dalloca=_alloca \
           -DWIN32 -D_DEBUG -D_CONSOLE -D_MBCS -DPLATFORM=$(PLATFORM) \
           -DHAVE_NAMESPACES -DHAVE_STD_NAMESPACE -DHAVE_THROW_SPECS \
           -DHAVE_STL $(DNSDEFS)
ifeq ($(DEBUG_BUILD),yes)
CFLAGS=    $(INCLS) $(DEFINES) -nologo -MLd -W3 -Gm -GX -Zi -Od \
           -YX -FD
CXXFLAGS=  $(CFLAGS)
ASNRTCFLAGS=    $(CFLAGS)
ASNRTCXXFLAGS=  $(CXXFLAGS)
else
CFLAGS=    $(INCLS) $(DEFINES) -nologo -MLd -W3 -Gm -GX -Zi -Od \
           -YX -FD
CXXFLAGS=  $(CFLAGS)
ASNRTCFLAGS=    $(CFLAGS)
ASNRTCXXFLAGS=  $(CXXFLAGS)
endif
LDFLAGS=   -nologo -subsystem:console -incremental:yes \
           -debug -machine:I386 -pdbtype:sept 
SOCKLIBS=
THREADLIBS=
SYSLIBS=   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib \
           advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib \
           odbc32.lib odbccp32.lib
OEXT=      obj
YACC=      bison
LEX=       flex
LEXLIB=
EXC=       $(ITS_ROOT)/tools/bin/exc
DBGSUFFIX= D
endif

#
# for Alpha
#
ifeq ($(PLATFORM),DECUNIX)
AR=        ar
CXXAR=     ar
ARFLAGS=   cruv
CXXARFLAGS=cruv
CP=        cp
RM=        rm -f
CC=        cc
LD=        cxx
MV=        mv
LN=        ln -s
MKDIR=     mkdir
CXX=       cxx
ASNC=      $(ITS_ROOT)/tools/bin/asnc
ASNCFLAGS= -A -a -f
INCLS=     -I. -I$(ITS_ROOT)/common/include
DEFINES=   -DDECSS7 -D$(PROTOCOL) -DPLATFORM=$(PLATFORM) -D$(PLATFORM) \
           -Dunix -D_REENTRANT \
           -DHAVE_NAMESPACES -DHAVE_STD_NAMESPACE -DHAVE_THROW_SPECS \
           -DHAVE_STL -DUSING_FLEX $(DNSDEFS)
SOCKLIBS=
THREADLIBS=
SYSLIBS=   -ldl
OEXT=      o
YACC=      bison
LEX=       flex
LEXLIB=
EXC=       $(ITS_ROOT)/tools/bin/exc

ifeq ($(DEBUG_BUILD),yes)
CFLAGS=    -pthread -std1 -g2 $(INCLS) $(DEFINES) -DDEBUG
CXXFLAGS=  -pthread -g -std strict_ansi -ptr $(ITS_ROOT)/cxx_repository \
           $(INCLS) $(DEFINES) -DDEBUG
ASNRTCFLAGS=    -pthread -std1 $(INCLS) $(DEFINES) -DDEBUG
ASNRTCXXFLAGS=  -pthread -std strict_ansi -ptr $(ITS_ROOT)/cxx_repository \
                $(INCLS) $(DEFINES) -DDEBUG
DBGSUFFIX= D
else
CFLAGS=    -pthread -std1 -O $(INCLS) $(DEFINES)
CXXFLAGS=  -pthread -O -std strict_ansi -ptr $(ITS_ROOT)/cxx_repository \
           $(INCLS) $(DEFINES)
ASNRTCFLAGS=    $(CFLAGS)
ASNRTCXXFLAGS=  $(CXXFLAGS)
DBGSUFFIX=
endif
LDFLAGS=   -pthread -ptr $(ITS_ROOT)/cxx_repository
endif

#
# for Solaris
#
ifeq ($(PLATFORM),solaris)

AR=        ar
CXXAR=     ar
ARFLAGS=   cruv
CXXARFLAGS=cruv
SHAREDAR=  gcc
SHAREDARFLAGS=-shared -shared-libgcc -Wl,--whole-archive -o
CXXSHAREDAR=g++
CXXSHAREDARFLAGS=-shared -Wl,--whole-archive -o
CP=        cp
RM=        rm -f
CC=        gcc
CXX=       g++ -Wno-deprecated
ASNC=      $(ITS_ROOT)/tools/bin/asnc
ASNCFLAGS= -A -a -f
LD=        g++ -Wno-deprecated
MV=        mv
LN=        ln -s
MKDIR=     mkdir
INCLS=     -I. -I$(ITS_ROOT)/common/include
DEFINES=   -D$(PROTOCOL) -D_REENTRANT -DUSING_FLEX -DPLATFORM=$(PLATFORM) \
           -D$(PLATFORM) \
           -DHAVE_NAMESPACES -DHAVE_STD_NAMESPACE -DHAVE_THROW_SPECS \
           -DHAVE_STL $(DNSDEFS)
SOCKLIBS=  -lnsl -lsocket
THREADLIBS=-lthread -lmtmalloc
SYSLIBS=   -ldl -lrt
OEXT=      o
YACC=      bison
LEX=       flex
LEXLIB=
EXC=       $(ITS_ROOT)/tools/bin/exc
SOFLAGS=   -fPIC
ifeq ($(DEBUG_BUILD),yes)
CFLAGS=    -g $(INCLS) $(DEFINES) -DDEBUG $(SOFLAGS) 
CXXFLAGS=  $(CFLAGS)
ASNRTCFLAGS=    $(INCLS) $(DEFINES) -DDEBUG $(SOFLAGS) 
ASNRTCXXFLAGS=  $(ASNRTCFLAGS)
DBGSUFFIX= D
else
CFLAGS=    -O $(INCLS) $(DEFINES) $(SOFLAGS) 
CXXFLAGS=  $(CFLAGS)
ASNRTCFLAGS=    $(CFLAGS)
ASNRTCXXFLAGS=  $(CXXFLAGS)
DBGSUFFIX=
LDFLAGS=
endif


#
# end solaris
#
endif

#
# for Solaris-64
#
ifeq ($(PLATFORM),solaris64)

AR=        ar
CXXAR=     ar
ARFLAGS=   cruv
CXXARFLAGS=cruv
SHAREDAR=  gcc -m64
SHAREDARFLAGS=-shared -shared-libgcc -Wl,-melf64_sparc -Wl,--whole-archive -o
CXXSHAREDAR=g++ -m64
CXXSHAREDARFLAGS=-shared -Wl,-melf64_sparc -Wl,--whole-archive -o
CP=        cp
RM=        rm -f
CC=        gcc -m64
CXX=       g++ -m64 -Wno-deprecated
ASNC=      $(ITS_ROOT)/tools/bin/asnc
ASNCFLAGS= -A -a -f
LD=        g++ -m64 -Wno-deprecated
MV=        mv
LN=        ln -s
MKDIR=     mkdir
INCLS=     -I. -I$(ITS_ROOT)/common/include
DEFINES=   -D$(PROTOCOL) -D_REENTRANT -DUSING_FLEX -DPLATFORM=$(PLATFORM) \
           -D$(PLATFORM) \
           -DHAVE_NAMESPACES -DHAVE_STD_NAMESPACE -DHAVE_THROW_SPECS \
           -DHAVE_STL $(DNSDEFS)
SOCKLIBS=  -lnsl -lsocket
THREADLIBS=-lthread -lmtmalloc
SYSLIBS=   -ldl -lrt
OEXT=      o
YACC=      bison
LEX=       flex
LEXLIB=
EXC=       $(ITS_ROOT)/tools/bin/exc
SOFLAGS=   -fPIC
ifeq ($(DEBUG_BUILD),yes)
CFLAGS=    -g $(INCLS) $(DEFINES) -DDEBUG $(SOFLAGS) 
CXXFLAGS=  $(CFLAGS)
ASNRTCFLAGS=    $(INCLS) $(DEFINES) -DDEBUG $(SOFLAGS) 
ASNRTCXXFLAGS=  $(ASNRTCFLAGS)
DBGSUFFIX= D
else
CFLAGS=    -O $(INCLS) $(DEFINES) $(SOFLAGS) 
CXXFLAGS=  $(CFLAGS)
ASNRTCFLAGS=    $(CFLAGS)
ASNRTCXXFLAGS=  $(CXXFLAGS)
DBGSUFFIX=
LDFLAGS= -m64
endif


#
# end solaris
#
endif

#
# for Linux
#
ifeq ($(PLATFORM),linux)
AR=        ar
CXXAR=     ar
ARFLAGS=   cruv
CXXARFLAGS=cruv
SHAREDAR=  gcc
NOWHOLEARCHIVE=-Wl,--no-whole-archive
SHAREDARFLAGS=-z muldefs -shared -shared-libgcc -Wl,--whole-archive -o
CXXSHAREDAR=g++
CXXSHAREDARFLAGS=-z muldefs -shared -Wl,--whole-archive -o 
CP=        cp
RM=        rm -f
CC=        gcc -D_GNU_SOURCE -pipe
CXX=       g++ -D_GNU_SOURCE -pipe
LD=        g++ -D_GNU_SOURCE -pipe -z muldefs
ASNC=      $(ITS_ROOT)/tools/bin/asnc
ASNCFLAGS= -A -a -f
MV=        mv
LN=        ln -s
MKDIR=     mkdir
INCLS=     -I. -I$(ITS_ROOT)/common/include
DEFINES=   -D$(PROTOCOL) -D_REENTRANT -DUSING_FLEX -DUSE_HEAP \
           -DPLATFORM=$(PLATFORM) -D_MIT_POSIX_THREADS \
           -DHAVE_NAMESPACES -DHAVE_STD_NAMESPACE -DHAVE_THROW_SPECS \
           -DHAVE_STL $(DNSDEFS)
SOCKLIBS=
THREADLIBS=-lpthread
SYSLIBS=   -ldl -lsctp
OEXT=      o
YACC=      bison
LEX=       flex
LEXLIB=    -lfl
EXC=       $(ITS_ROOT)/tools/bin/exc
SOFLAGS=   -fpic
ifeq ($(DEBUG_BUILD),yes)
CFLAGS=    -g -Wall $(INCLS) $(DEFINES) -DDEBUG $(SOFLAGS)
CXXFLAGS=  $(CFLAGS) -z muldefs
ASNRTCFLAGS=    -Wall $(INCLS) $(DEFINES) -DDEBUG $(SOFLAGS)
ASNRTCXXFLAGS=  $(ASNRTCFLAGS)
DBGSUFFIX= D
else
CFLAGS=    -O -Wall $(INCLS) $(DEFINES) -DNDEBUG $(SOFLAGS)
CXXFLAGS=  $(CFLAGS) -z muldefs
ASNRTCFLAGS=    $(CFLAGS)
ASNRTCXXFLAGS=  $(CXXFLAGS)
DBGSUFFIX=
endif

#
# end linux
#
endif

#
#
# for HPUX
#
ifeq ($(PLATFORM),hpux)
AR=        ar
CXXAR=     ar
ARFLAGS=   cruv
CXXARFLAGS=cruv
CP=        cp
RM=        rm -f
CC=        cc
CXX=       /opt/aCC/bin/aCC +W749
ASNC=      $(ITS_ROOT)/tools/bin/asnc
ASNCFLAGS= -A -a -f
LD=        /opt/aCC/bin/aCC
MV=        mv
LN=        ln -s
MKDIR=     mkdir
INCLS=     -I. -I$(ITS_ROOT)/common/include
DEFINES=   -D$(PROTOCOL) -D_REENTRANT -DRW_MULTI_THREAD -DUSING_FLEX \
           -DPLATFORM=$(PLATFORM) -DHPUX -D_MIT_POSIX_THREADS \
	   -Dunix $(DNSDEFS)
SOCKLIBS=
THREADLIBS=-ldce
SYSLIBS=   -ldl
OEXT=      o
YACC=      bison
LEX=       flex
LEXLIB=
LDFLAGS=
EXC=       $(ITS_ROOT)/tools/bin/exc

# old stuff
#
# CXX=       /opt/CC/bin/CC
# LD=        /opt/CC/bin/CC
# INCLS=     -I. -I$(ITS_ROOT)/common/include -I/opt/aCC/include -I/usr
# DEFINES=   -D$(PROTOCOL) -D_REENTRANT -DRW_MULTI_THREAD -DUSING_FLEX \
#            -DPLATFORM=$(PLATFORM) -DHPUX -D_MIT_POSIX_THREADS
# CFLAGS=    +DAportable +eh -Ae -g $(INCLS) $(DEFINES)
# CXXFLAGS=  +DAportable +eh -g $(INCLS) $(DEFINES)

ifeq ($(DEBUG_BUILD),yes)
CFLAGS=    +DAportable -Ae -g $(INCLS) $(DEFINES) -DDEBUG
CXXFLAGS=  +DAportable -g $(INCLS) $(DEFINES)
ASNRTCFLAGS=    +DAportable -Ae $(INCLS) $(DEFINES) -DDEBUG
ASNRTCXXFLAGS=  +DAportable $(INCLS) $(DEFINES)

DBGSUFFIX= D
else
CFLAGS=    +DAportable -Ae -O $(INCLS) $(DEFINES)
CXXFLAGS=  +DAportable +O1 $(INCLS) $(DEFINES)
ASNRTCFLAGS=    $(CFLAGS)
ASNRTCXXFLAGS=  $(CXXFLAGS)
DBGSUFFIX= 
endif

#
# end hpux
#
endif

#
#
# for vxworks
#
#
ifeq ($(PLATFORM),vxworks)
#
# Core Information
# Application type to build project
# For more information on processor and tool
# specific variable see vxconfig.vars.

include $(ITS_ROOT)/vxconfig.vars

AR=                 arpentium
AS=                 ccpentium
CXXAR=              arpentium
ARFLAGS=            crusv
CXXARFLAGS=         crusv
#
## Macros specific to the vxworks
#
OPTION_DEFINE_MACRO=-D
OPTION_INCLUDE_DIR= -I
POST_BUILD_RULE= 
PRJ_LIBS= 
SIZE=               sizepentium
VX_CFLAGS=          -mpentium -ansi -DRW_MULTI_THREAD \
                    -fvolatile -nostdlib -fno-builtin \
                    -fno-defer-pop

INCLS=              -I$(ITS_ROOT)/common/include -I$(WIND_BASE)/target/h \
                    -I$(ITS_ROOT)/MTP3/include \
		            -I$(ITS_ROOT)/SCCP/include -I$(ITS_ROOT)/TCAP/include \
                    -I$(ITS_ROOT)/ISUP/include -I.

CFLAGS_AS=          -g -mpentium -ansi -nostdinc -fvolatile \
                    -nostdlib -fno-builtin -fno-defer-pop -P \
                    -x assembler-with-cpp -I$(WIND_BASE)/target/h \
                    -DCPU=PENTIUM $(INCLS)

RM=                 rm -f
CC=                 ccpentium
CXX=                ccpentium 
SHAREDAR=           arpentium
SHAREDARFLAGS=      $(ARFLAGS) 
CXXSHAREDAR=        arpentium
CXXSHAREDARFLAGS=   $(ARFLAGS) 
LD_PARTIAL_FLAGS=   -X -r
LDDEPS= 
LDFLAGS=            -X -N
LD=                 ldpentium
NM=                 nmpentium -g	   
ASNC=               $(ITS_ROOT)/tools/bin/asnc
ASNCFLAGS=          -A -a -f
MV=                 mv
LN=                 ln -s
MKDIR=              mkdir
VPATH=              $(WIND_BASE)/target/h $(ITS_ROOT)/common/include \
                    $(ITS_ROOT)/MTP3/include $(ITS_ROOT)/SCCP/include \
                    $(ITS_ROOT)/TCAP/include $(ITS_ROOT)/ISUP/include


DEFINES=            -D$(PROTOCOL) -Dvxworks -D_REENTRANT -DUSING_FLEX \
                    -D_MIT_POSIX_THREADS \
                    -DHAVE_NAMESPACES -DHAVE_STD_NAMESPACE \
                    -DHAVE_THROW_SPECS -DHAVE_STL $(DNSDEFS)
SOCKLIBS=
THREADLIBS=
SYSLIBS=   
OEXT=               o
YACC=               bison
LEX=                flex
LEXLIB=             -lfl
EXC=                $(ITS_ROOT)/tools/bin/exc.exe

ifeq ($(DEBUG_BUILD),yes)
CFLAGS=    -g -c -DCPU=$(CPU) $(VX_CFLAGS) $(INCLS) $(DEFINES) -DDEBUG
CXXFLAGS=  -g $(CFLAGS) -DINCLUDE_CPLUS_STL $(CFLAGS) \
           -I$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/i586-wrs-vxworks/2.96-PentiumIII-991112/include
ASNRTCFLAGS=    -c -DCPU=$(CPU) $(VX_CFLAGS) $(INCLS) $(DEFINES) -DDEBUG
ASNRTCXXFLAGS=  $(ASNRTCFLAGS) -DINCLUDE_CPLUS_STL $(ASNRTCFLAGS) \
           -I$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/i586-wrs-vxworks/2.96-PentiumIII-991112/include

DBGSUFFIX= D
else
CFLAGS=    -DCPU=$(CPU) -O1 -c $(VX_CFLAGS) $(INCLS) $(DEFINES)
CXXFLAGS=  $(CFLAGS) -DINCLUDE_CPLUS_STL \
          -I$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/i586-wrs-vxworks/2.96-PentiumIII-991112/include
ASNRTCFLAGS=    $(CFLAGS)
ASNRTCXXFLAGS=  $(CXXFLAGS)

DBGSUFFIX=
endif
#
# end VxWorks
#
endif

#
# Globally shared stuff
#
BUILDDIR=.
ifeq ($(DEBUG_BUILD),yes)
BUILDDIR=Debug
else
ifeq ($(DEBUG_BUILD),no)
BUILDDIR=Release
endif
endif
