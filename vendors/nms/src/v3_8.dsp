# Microsoft Developer Studio Project File - Name="v3_8" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=v3_8 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "v3_8.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "v3_8.mak" CFG="v3_8 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "v3_8 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "v3_8 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "v3_8 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "v3_8___Win32_Release"
# PROP BASE Intermediate_Dir "v3_8___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "v3_8___Win32_Release"
# PROP Intermediate_Dir "v3_8___Win32_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/v3_8" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "NMS" /D "ITS_IMPLEMENTATION" /D NMS_VERSION=3080 /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/NMSVendor.lib"

!ELSEIF  "$(CFG)" == "v3_8 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "v3_8___Win32_Debug"
# PROP BASE Intermediate_Dir "v3_8___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "v3_8___Win32_Debug"
# PROP Intermediate_Dir "v3_8___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "../include/v3_8" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NMS" /D "ITS_IMPLEMENTATION" /D NMS_VERSION=3080 /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/NMSVendorD.lib"

!ENDIF 

# Begin Target

# Name "v3_8 - Win32 Release"
# Name "v3_8 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\hmi.c
# End Source File
# Begin Source File

SOURCE=.\isup.c
# End Source File
# Begin Source File

SOURCE=.\isup_translate.c
# End Source File
# Begin Source File

SOURCE=.\mtp2.c
# End Source File
# Begin Source File

SOURCE=.\mtp3.c
# End Source File
# Begin Source File

SOURCE=.\sccp.c
# End Source File
# Begin Source File

SOURCE=.\tcap.c
# End Source File
# Begin Source File

SOURCE=.\transport.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\its_intern.h
# End Source File
# Begin Source File

SOURCE=..\include\its_vmi.h
# End Source File
# End Group
# Begin Group "Library Files"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=..\include\configuration.template.sample
# End Source File
# Begin Source File

SOURCE=..\lib\v3_8\cpi.lib
# End Source File
# End Target
# End Project
