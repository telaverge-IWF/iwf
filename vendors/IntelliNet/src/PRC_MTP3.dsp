# Microsoft Developer Studio Project File - Name="PRC_MTP3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=PRC_MTP3 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PRC_MTP3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PRC_MTP3.mak" CFG="PRC_MTP3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PRC_MTP3 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "PRC_MTP3 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PRC_MTP3 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "PRC_MTP3___Win32_Release"
# PROP BASE Intermediate_Dir "PRC_MTP3___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "PRCRelease"
# PROP Intermediate_Dir "PRCRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "ITSSS7_IMPLEMENTATION" /D "PRC" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\PRC_MTP3_LAYER.lib"

!ELSEIF  "$(CFG)" == "PRC_MTP3 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "PRC_MTP3___Win32_Debug"
# PROP BASE Intermediate_Dir "PRC_MTP3___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "PRCDebug"
# PROP Intermediate_Dir "PRCDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "ITSSS7_IMPLEMENTATION" /D "PRC" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\PRC_MTP3_LAYERD.lib"

!ENDIF 

# Begin Target

# Name "PRC_MTP3 - Win32 Release"
# Name "PRC_MTP3 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\itu-mgmt.c"
# End Source File
# Begin Source File

SOURCE=".\itu-mtp3.c"
# End Source File
# Begin Source File

SOURCE=".\itu-mtp3_alarms.c"
# End Source File
# Begin Source File

SOURCE=".\itu-mtp3_ifc.c"
# End Source File
# Begin Source File

SOURCE=".\itu-slm.c"
# End Source File
# Begin Source File

SOURCE=".\itu-slt.c"
# End Source File
# Begin Source File

SOURCE=".\itu-smh.c"
# End Source File
# Begin Source File

SOURCE=".\itu-srm.c"
# End Source File
# Begin Source File

SOURCE=".\itu-stm.c"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\mtp3_intern.h
# End Source File
# Begin Source File

SOURCE=..\include\ss7_alarms.h
# End Source File
# Begin Source File

SOURCE=..\include\ss7_behaviors.h
# End Source File
# Begin Source File

SOURCE=..\include\ss7_mgmt.h
# End Source File
# Begin Source File

SOURCE=..\include\ss7_pegs.h
# End Source File
# Begin Source File

SOURCE=..\include\ss7_timers.h
# End Source File
# End Group
# End Target
# End Project
