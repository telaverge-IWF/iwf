# Microsoft Developer Studio Project File - Name="v3_8_dll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=v3_8_dll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "v3_8_dll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "v3_8_dll.mak" CFG="v3_8_dll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "v3_8_dll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "v3_8_dll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "v3_8_dll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "v3_8_dll___Win32_Release"
# PROP BASE Intermediate_Dir "v3_8_dll___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "V3_8_DLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../vframe/include" /I "../include" /I "../include/v3_8" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/MTP2/include" /D "NDEBUG" /D "VSS7_IMPLEMENTATION" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "NMS" /D NMS_VERSION=3080 /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\lib\NMSVendor.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\NMSVendor.lib ..\lib	copy Release\NMSVendor.exp ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "v3_8_dll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "V3_8_DLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../vframe/include" /I "../include" /I "../include/v3_8" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/MTP2/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "NMS" /D NMS_VERSION=3080 /D "VSS7_IMPLEMENTATION" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\lib\NMSVendorD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\NMSVendorD.lib ..\lib	copy Debug\NMSVendorD.exp ..\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "v3_8_dll - Win32 Release"
# Name "v3_8_dll - Win32 Debug"
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

SOURCE=.\its_vendor.h
# End Source File
# Begin Source File

SOURCE=..\include\its_vmi.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\ENGINED.lib

!IF  "$(CFG)" == "v3_8_dll - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "v3_8_dll - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\VFrame.lib

!IF  "$(CFG)" == "v3_8_dll - Win32 Release"

!ELSEIF  "$(CFG)" == "v3_8_dll - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\ENGINE.lib

!IF  "$(CFG)" == "v3_8_dll - Win32 Release"

!ELSEIF  "$(CFG)" == "v3_8_dll - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\VFrameD.lib

!IF  "$(CFG)" == "v3_8_dll - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "v3_8_dll - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\lib\v3_8\tcapapi.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\nms\lib\v3_8\cpi.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\nms\lib\v3_8\cta.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\nms\lib\v3_8\ctacl.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\nms\lib\v3_8\ctal.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\nms\lib\v3_8\hmiapi.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\nms\lib\v3_8\hmimgr.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\nms\lib\v3_8\isupapi.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\nms\lib\v3_8\isupmgmt.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\nms\lib\v3_8\mtp3api.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\nms\lib\v3_8\ss7mapi.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\nms\lib\v3_8\tsi.lib
# End Source File
# End Target
# End Project