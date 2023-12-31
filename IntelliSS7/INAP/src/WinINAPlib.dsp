# Microsoft Developer Studio Project File - Name="WinINAPlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=WinINAPlib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WinINAPlib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinINAPlib.mak" CFG="WinINAPlib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinINAPlib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "WinINAPlib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinINAPlib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinINAPlib_Release"
# PROP Intermediate_Dir "WinINAPlib_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/itu" /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../MTP3/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "CCITT" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/INAP.lib"

!ELSEIF  "$(CFG)" == "WinINAPlib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinINAPl"
# PROP BASE Intermediate_Dir "WinINAPl"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinINAPlib_Debug"
# PROP Intermediate_Dir "WinINAPlib_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../include/itu" /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../MTP3/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "CCITT" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/INAPD.lib"

!ENDIF 

# Begin Target

# Name "WinINAPlib - Win32 Release"
# Name "WinINAPlib - Win32 Debug"
# Begin Source File

SOURCE=.\inap.asn

!IF  "$(CFG)" == "WinINAPlib - Win32 Release"

!ELSEIF  "$(CFG)" == "WinINAPlib - Win32 Debug"

# Begin Custom Build
InputPath=.\inap.asn

BuildCmds= \
	..\..\tools\bin\asnc -A -a -f inap.asn \
	copy inap-types.h ..\include\itu \
	del inap-types.h \
	

".\inap_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\include\itu\inap-types.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\inap.c
# End Source File
# Begin Source File

SOURCE=.\INAP_tables.c
# End Source File
# End Target
# End Project
