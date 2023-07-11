# Microsoft Developer Studio Project File - Name="itscore" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=itscore - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "itscore.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "itscore.mak" CFG="itscore - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "itscore - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "itscore - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "itscore - Win32 Standalone Release" (based on "Win32 (x86) Static Library")
!MESSAGE "itscore - Win32 Standalone Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "itscore - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CORE"
# PROP Intermediate_Dir "CORE"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "ITS_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/CORE.lib"

!ELSEIF  "$(CFG)" == "itscore - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CORED"
# PROP Intermediate_Dir "CORED"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /Gi- /GX /Z7 /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "ITS_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/CORED.lib"

!ELSEIF  "$(CFG)" == "itscore - Win32 Standalone Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "itscore_"
# PROP BASE Intermediate_Dir "itscore_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SCORE"
# PROP Intermediate_Dir "SCORE"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "ITS_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../lib/CORE++.lib"
# ADD LIB32 /nologo /out:"../../lib/SCORE.lib"

!ELSEIF  "$(CFG)" == "itscore - Win32 Standalone Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "itscore0"
# PROP BASE Intermediate_Dir "itscore0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SCORED"
# PROP Intermediate_Dir "SCORED"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "ITS_IMPLEMENTATION" /D "STANDALONE" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../lib/CORE++D.lib"
# ADD LIB32 /nologo /out:"../../lib/SCORED.lib"

!ENDIF 

# Begin Target

# Name "itscore - Win32 Release"
# Name "itscore - Win32 Debug"
# Name "itscore - Win32 Standalone Release"
# Name "itscore - Win32 Standalone Debug"
# Begin Group "Source Files"

# PROP Default_Filter "c,cpp"
# Begin Source File

SOURCE=.\its.c

!IF  "$(CFG)" == "itscore - Win32 Release"

!ELSEIF  "$(CFG)" == "itscore - Win32 Debug"

!ELSEIF  "$(CFG)" == "itscore - Win32 Standalone Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "itscore - Win32 Standalone Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\its_alarms.c
# End Source File
# Begin Source File

SOURCE=.\its_app.c
# End Source File
# Begin Source File

SOURCE=.\its_assertion.c
# End Source File
# Begin Source File

SOURCE=.\its_behaviors.c
# End Source File
# Begin Source File

SOURCE=.\its_callback.c
# End Source File
# Begin Source File

SOURCE=.\its_chksum.c
# End Source File
# Begin Source File

SOURCE=.\its_classes.c
# End Source File
# Begin Source File

SOURCE=.\its_crypt.c
# End Source File
# Begin Source File

SOURCE=.\its_dsm.c
# End Source File
# Begin Source File

SOURCE=.\its_dsmqueue.c
# End Source File
# Begin Source File

SOURCE=.\its_error.c
# End Source File
# Begin Source File

SOURCE=.\its_factory.c
# End Source File
# Begin Source File

SOURCE=.\its_features.c
# End Source File
# Begin Source File

SOURCE=.\its_hash.c
# End Source File
# Begin Source File

SOURCE=.\its_iniparse.c
# End Source File
# Begin Source File

SOURCE=.\its_license.c
# End Source File
# Begin Source File

SOURCE=.\its_list.c
# End Source File
# Begin Source File

SOURCE=.\its_lockable.c
# End Source File
# Begin Source File

SOURCE=.\its_mlist.c
# End Source File
# Begin Source File

SOURCE=.\platforms\WIN32\its_mutex.c
# End Source File
# Begin Source File

SOURCE=.\its_object.c
# End Source File
# Begin Source File

SOURCE=.\its_pegs.c
# End Source File
# Begin Source File

SOURCE=.\its_pprint.c
# End Source File
# Begin Source File

SOURCE=.\its_rb.c
# End Source File
# Begin Source File

SOURCE=.\its_ring_buf.c
# End Source File
# Begin Source File

SOURCE=.\its_splay.c
# End Source File
# Begin Source File

SOURCE=.\its_standalone.c

!IF  "$(CFG)" == "itscore - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "itscore - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "itscore - Win32 Standalone Release"

!ELSEIF  "$(CFG)" == "itscore - Win32 Standalone Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\its_time.c
# End Source File
# Begin Source File

SOURCE=.\its_trace.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE="..\..\include\its++.h"
# End Source File
# Begin Source File

SOURCE=..\..\include\its.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_alarm.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_app.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_assertion.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_behaviors.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_callback.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_chksum.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_consts.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_crypt.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_dsm.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_dsmqueue.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_factory.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_hash.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_iniparse.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_license.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_list.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_lockable.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_mlist.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_mutex.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_object.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_pegs.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_pprint.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_rb.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_ring_buf.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_splay.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_timers.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_trace.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_types.h
# End Source File
# Begin Source File

SOURCE=.\itscore.h
# End Source File
# End Group
# End Target
# End Project
