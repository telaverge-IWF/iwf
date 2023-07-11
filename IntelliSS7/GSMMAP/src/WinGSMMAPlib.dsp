# Microsoft Developer Studio Project File - Name="WinGSMMAPlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=WinGSMMAPlib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WinGSMMAPlib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinGSMMAPlib.mak" CFG="WinGSMMAPlib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinGSMMAPlib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "WinGSMMAPlib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinGSMMAPlib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/itu" /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../MTP3/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "CCITT" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/GSMMAP.lib"

!ELSEIF  "$(CFG)" == "WinGSMMAPlib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../include/itu" /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../MTP3/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "DEBUG" /D "CCITT" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/GSMMAPD.lib"

!ENDIF 

# Begin Target

# Name "WinGSMMAPlib - Win32 Release"
# Name "WinGSMMAPlib - Win32 Debug"
# Begin Source File

SOURCE=.\GSMMAP.asn

!IF  "$(CFG)" == "WinGSMMAPlib - Win32 Release"

# Begin Custom Build
InputPath=.\GSMMAP.asn

BuildCmds= \
	..\..\tools\bin\asnc -A -a -f GSMMAP.asn \
	copy GSMMAP-types.h ..\include\itu \
	del GSMMAP-types.h \
	

"GSMMAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\include\itu\GSMMAP-types.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "WinGSMMAPlib - Win32 Debug"

# Begin Custom Build
InputPath=.\GSMMAP.asn

BuildCmds= \
	..\..\tools\bin\asnc -A -a -f GSMMAP.asn \
	copy GSMMAP-types.h ..\include\itu \
	del GSMMAP-types.h \
	

"GSMMAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\include\itu\GSMMAP-types.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GSMMAP_tables.c
# End Source File
# Begin Source File

SOURCE=.\GSMSMS.c
# End Source File
# Begin Source File

SOURCE=.\its_GSMMAP.c
# End Source File
# End Target
# End Project
