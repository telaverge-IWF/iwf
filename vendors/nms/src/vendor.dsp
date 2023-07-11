# Microsoft Developer Studio Project File - Name="vendor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=vendor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vendor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vendor.mak" CFG="vendor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vendor - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "vendor - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vendor - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vendor__"
# PROP BASE Intermediate_Dir "vendor__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MDd /W3 /GX /Z7 /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/MTP3/include" /D "_DEBUG" /D "DEBUG" /D "CCITT" /D "INCLUDE_MTP3" /D "WIN32" /D "_WINDOWS" /D "NMS" /D "WITH_TOOLKIT" /YX /FD /c
# ADD CPP /nologo /Zp1 /MDd /W3 /GX /Z7 /Od /I "../include" /I "../include/orig" /I "$(ITS_ROOT)/include" /I "$(ITS_ROOT)/SCCP/include C:\NMS\include" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS" /D "NMS" /D "ITS_IMPLEMENTATION" /D NMS_VERSION=2000 /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\NMSVendorINT-CCITT-MTP3D.lib"
# ADD LIB32 /nologo /out:"..\lib\NMSVendorD.lib"

!ELSEIF  "$(CFG)" == "vendor - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vendor_0"
# PROP BASE Intermediate_Dir "vendor_0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MD /W3 /GX /O2 /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/MTP3/include" /D "NDEBUG" /D "CCITT" /D "INCLUDE_MTP3" /D "WITH_TOOLKIT" /D "_NDEBUG" /D "WIN32" /D "_WINDOWS" /D "NMS" /U "DEBUG" /YX /FD /c
# ADD CPP /nologo /Zp1 /MD /W3 /GX /O2 /I "../include" /I "../include/orig" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /D "NDEBUG" /D "_NDEBUG" /D "WIN32" /D "_WINDOWS" /D "NMS" /D "ITS_IMPLEMENTATION" /D NMS_VERSION=2000 /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/NMSVendorINT-CCITT-MTP3.lib"
# ADD LIB32 /nologo /out:"../lib/NMSVendor.lib"

!ENDIF 

# Begin Target

# Name "vendor - Win32 Debug"
# Name "vendor - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "c"
# Begin Source File

SOURCE=.\isup.c
# End Source File
# Begin Source File

SOURCE=.\isup_ifc.c
# End Source File
# Begin Source File

SOURCE=.\isup_stubs.c
# End Source File
# Begin Source File

SOURCE=.\mtp3.c
# End Source File
# Begin Source File

SOURCE=.\mtp3_ifc.c
# End Source File
# Begin Source File

SOURCE=.\mtp3_stubs.c
# End Source File
# Begin Source File

SOURCE=.\sccp.c
# End Source File
# Begin Source File

SOURCE=.\sccp_ifc.c
# End Source File
# Begin Source File

SOURCE=.\sccp_stubs.c
# End Source File
# Begin Source File

SOURCE=.\tcap.c
# End Source File
# Begin Source File

SOURCE=.\tcap_ifc.c
# End Source File
# Begin Source File

SOURCE=.\tcap_stubs.c
# End Source File
# Begin Source File

SOURCE=.\transport.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\include\its_intern.h
# End Source File
# End Group
# Begin Group "Library Files"

# PROP Default_Filter "lib"
# Begin Source File

SOURCE=..\lib\orig\tcapapi.lib
# End Source File
# Begin Source File

SOURCE=..\lib\orig\sccpapi.lib

!IF  "$(CFG)" == "vendor - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\lib\orig\mtp3api.lib

!IF  "$(CFG)" == "vendor - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 Release"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=..\include\configuration.template
# End Source File
# Begin Source File

SOURCE=..\include\configuration.template.sample

!IF  "$(CFG)" == "vendor - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 Release"

!ENDIF 

# End Source File
# End Target
# End Project
