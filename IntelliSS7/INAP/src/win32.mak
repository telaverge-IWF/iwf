#
# Copyright (C) 1999-2000 IntelliNet Technologies, Inc.  All rights reserved.
#


#
# $Id: win32.mak,v 9.1 2005/03/23 12:51:45 cvsadmin Exp $
#
# $Log: win32.mak,v $
# Revision 9.1  2005/03/23 12:51:45  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:49:41  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:08:57  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:13:34  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:45:27  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:53:04  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/15 23:57:57  mmiers
#
# Begin round 4.
#
# Revision 1.2  2000/03/28 16:23:35  npopov
# Added Id & Log macros for CVS
#
#


COMMON_INCLUDE = $(ITS_ROOT)\common\include
COMMON_LIB     = $(ITS_ROOT)\common\lib
INAP_INCLUDE   = $(ITS_ROOT)\inap\include
TCAP_INCLUDE   = $(ITS_ROOT)\TCAP\include
SCCP_INCLUDE   = $(ITS_ROOT)\SCCP\include
ISUP_INCLUDE   = $(ITS_ROOT)\ISUP\include
MTP3_INCLUDE   = $(ITS_ROOT)\MTP3\include
IMPLIB         = lib
CC             = cl
LINK           = link
IMPLIB         = lib

!ifndef debug
debug = yes
!endif

!if "$(debug)" == "yes"
!else if "$(debug)" == "no"
!else
!ERROR The macro "debug" incorrectly defined!
!endif

!ifndef msdebug
msdebug = yes
!endif

!if "$(msdebug)" == "yes"
RTSL = -MTd
RTDL = -MDd
LINKER = -debug
!else
RTSL = -MT
RTDL = -MD
LINKER = -release
!endif

CPU = ix86
POPT = -GB
OOPT = -GF -Gi- -Gm- -GR- -GX- -Gy -Oxsy -Zl

!if "$(debug)" == "yes"
MAINFLAGS = -c -W3 -Od -Z7 $(POPT) -Ze -D_WIN32 -DWIN32 -DCCITT\
		-I$(INAP_INCLUDE) -I$(INAP_INCLUDE)\itu -DWIN32_EXTRA_LEAN\
		-DVC_EXTRALEAN -I$(COMMON_INCLUDE) -I$(TCAP_INCLUDE)\
		-I$(SCCP_INCLUDE) -I$(ISUP_INCLUDE) -I$(MTP3_INCLUDE)
CONFLAGS = -pdb:none
LDEBUG   = -debug:full -debugtype:cv $(LINKER)
!else if "$(debug)" == "no"
MAINFLAGS = -c -W3 $(OOPT) $(POPT) -Ze -D_WIN32 -DWIN32 -DCCITT\
		-I$(INAP_INCLUDE) -I$(INAP_INCLUDE)\itu -DWIN32_EXTRA_LEAN\
		-DVC_EXTRALEAN -I$(COMMON_INCLUDE) -I$(TCAP_INCLUDE)\
		-I$(SCCP_INCLUDE) -I$(ISUP_INCLUDE) -I$(MTP3_INCLUDE)
CONFLAGS = -pdb:none
LDEBUG   =  $(LINKER)
!else
!ERROR The macro "debug" incorrectly defined!
!endif

!ifdef t
MTYPE = $(t)
!else
MTYPE = d
mt = d
!endif

!if "$(MTYPE)" == "s"
CFLAGS = $(RTSL) $(MAINFLAGS)
CPLUSPLUSFLAGS = $(RTSL) $(MAINFLAGS) -GX
!if "$(msdebug)" == "yes"
TYPE = d
CONLIBS = libcmtd.lib kernel32.lib advapi32.lib
!else
TYPE =
CONLIBS = libcmt.lib kernel32.lib advapi32.lib
!endif
!else if "$(MTYPE)" == "d"
CFLAGS = $(RTDL) $(MAINFLAGS)
CPLUSPLUSFLAGS = $(RTDL) $(MAINFLAGS) -GX
!if "$(msdebug)" == "yes"
CONLIBS = msvcrtd.lib kernel32.lib advapi32.lib ws2_32.lib
TYPE = mdd
!else
CONLIBS = msvcrt.lib kernel32.lib advapi32.lib ws2_32.lib
TYPE = md
!endif
!else
!ERROR The macro "t" incorrectly defined!
!endif

!message Current library is inap$(TYPE).lib...
!message

OBJECTS = inap_tables.obj inap.obj isup_rose.obj


.c.obj::
	$(CC) $(CFLAGS) $<
.cpp.obj::
	$(CC) $(CPLUSPLUSFLAGS) $<



all:	inap$(TYPE).lib


inap$(TYPE).lib: $(OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(OBJECTS)
		mv $@ $(ITS_ROOT)/runtime




dbgconsole$(TYPE).exe: $(COBJECTS)
		$(LINK) $(CONFLAGS) $(LDEBUG) -out:$@ $(COBJECTS)\
		$(COMMON_LIB)\core++$(TYPE).lib\
		$(COMMON_LIB)\support++$(TYPE).lib $(CONLIBS)
		cp $@ ../../bin


inap_tables.obj: inap_tables.c
inap_tables.c: inap.asn
		-..\..\tools\bin\asnc -A -a -f -h inap.asn
		mv INAP-types.h ..\include\itu


clean:
	@if exist *.obj                      rm *.obj
	@if exist *.pdb                      rm *.pdb
	@if exist inap_tables.c              rm inap_tables.c
	@if exist $(ITS_ROOT)/runtime/inap$(TYPE).lib rm $(ITS_ROOT)/runtime/inap$(TYPE).lib
	@if exist dbgconsole$(TYPE).exe      rm dbgconsole$(TYPE).exe
	@echo Done

