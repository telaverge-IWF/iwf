# Microsoft Developer Studio Project File - Name="vendor_dll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=vendor_dll - Win32 CCITT Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vendor_dll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vendor_dll.mak" CFG="vendor_dll - Win32 CCITT Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vendor_dll - Win32 CCITT over ANSI Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vendor_dll - Win32 CCITT over ANSI Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vendor_dll - Win32 ANSI over CCITT Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vendor_dll - Win32 ANSI over CCITT Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vendor_dll - Win32 ANSI Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vendor_dll - Win32 CCITT Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vendor_dll - Win32 ANSI Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vendor_dll - Win32 CCITT Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CCITT over ANSI Debug"
# PROP BASE Intermediate_Dir "CCITT over ANSI Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "COADLLDebug"
# PROP Intermediate_Dir "COADLLDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "../../vframe/include" /D "_DEBUG" /D "USE_ANSI_SCCP" /D "SPLIT_STACK" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "TCAP_CODEC" /D "TRACE_IMPLEMENTATION" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\lib\CCITT-ANSIVendorD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy COADLLDebug\CCITT-ANSIVendorD.exp ..\lib	copy COADLLDebug\CCITT-ANSIVendorD.lib ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CCITT over ANSI Release"
# PROP BASE Intermediate_Dir "CCITT over ANSI Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "COADLLRelease"
# PROP Intermediate_Dir "COADLLRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "../../vframe/include" /D "NDEBUG" /D "USE_ANSI_SCCP" /D "SPLIT_STACK" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "TCAP_CODEC" /D "TRACE_IMPLEMENTATION" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\lib\CCITT-ANSIVendor.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy COADLLRelease\CCITT-ANSIVendor.exp ..\lib	copy COADLLRelease\CCITT-ANSIVendor.lib ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ANSI over CCITT Debug"
# PROP BASE Intermediate_Dir "ANSI over CCITT Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AOCDLLDebug"
# PROP Intermediate_Dir "AOCDLLDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "../../vframe/include" /D "_DEBUG" /D "USE_ITU_SCCP" /D "SPLIT_STACK" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "TCAP_CODEC" /D "TRACE_IMPLEMENTATION" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\lib\ANSI-CCITTVendorD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy AOCDLLDebug\ANSI-CCITTVendorD.exp ..\lib	copy AOCDLLDebug\ANSI-CCITTVendorD.lib ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ANSI over CCITT Release"
# PROP BASE Intermediate_Dir "ANSI over CCITT Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AOCDLLRelease"
# PROP Intermediate_Dir "AOCDLLRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "../../vframe/include" /D "NDEBUG" /D "USE_ITU_SCCP" /D "SPLIT_STACK" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "TCAP_CODEC" /D "TRACE_IMPLEMENTATION" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\lib\ANSI-CCITTVendor.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy AOCDLLRelease\ANSI-CCITTVendor.exp ..\lib	copy AOCDLLRelease\ANSI-CCITTVendor.lib ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vendor_dll___Win32_ANSI_Debug"
# PROP BASE Intermediate_Dir "vendor_dll___Win32_ANSI_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSIDebug"
# PROP Intermediate_Dir "ANSIDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "../include/ansi" /I "../include/itu" /I "../../vframe/include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "../include/ansi" /I "../include/itu" /I "../../vframe/include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "TCAP_CODEC" /D "TRACE_IMPLEMENTATION" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\lib\BothVendorD.dll" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\lib\ANSIVendorD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ANSIDebug\ANSIVendorD.exp ..\lib	copy ANSIDebug\ANSIVendorD.lib ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vendor_dll___Win32_CCITT_Debug"
# PROP BASE Intermediate_Dir "vendor_dll___Win32_CCITT_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITTDebug"
# PROP Intermediate_Dir "CCITTDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "../include/ansi" /I "../include/itu" /I "../../vframe/include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "../include/ansi" /I "../include/itu" /I "../../vframe/include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "TCAP_CODEC" /D "TRACE_IMPLEMENTATION" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\lib\BothVendorD.dll" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\lib\CCITTVendorD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy CCITTDebug\CCITTVendorD.exp ..\lib	copy CCITTDebug\CCITTVendorD.lib ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vendor_dll___Win32_ANSI_Release"
# PROP BASE Intermediate_Dir "vendor_dll___Win32_ANSI_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSIRelease"
# PROP Intermediate_Dir "ANSIRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /D "INCLUDE_CODEC" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/ansi" /I "../include/itu" /I "../../vframe/include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "TCAP_CODEC" /D "TRACE_IMPLEMENTATION" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\lib\BothVendor.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\lib\ANSIVendor.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ANSIRelease\ANSIVendor.exp ..\lib	copy ANSIRelease\ANSIVendor.lib ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vendor_dll___Win32_CCITT_Release"
# PROP BASE Intermediate_Dir "vendor_dll___Win32_CCITT_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITTRelease"
# PROP Intermediate_Dir "CCITTRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /D "INCLUDE_CODEC" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/ansi" /I "../include/itu" /I "../../vframe/include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "TCAP_CODEC" /D "TRACE_IMPLEMENTATION" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\lib\BothVendor.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\lib\CCITTVendor.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy CCITTRelease\CCITTVendor.exp ..\lib	copy CCITTRelease\CCITTVendor.lib ..\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "vendor_dll - Win32 CCITT over ANSI Debug"
# Name "vendor_dll - Win32 CCITT over ANSI Release"
# Name "vendor_dll - Win32 ANSI over CCITT Debug"
# Name "vendor_dll - Win32 ANSI over CCITT Release"
# Name "vendor_dll - Win32 ANSI Debug"
# Name "vendor_dll - Win32 CCITT Debug"
# Name "vendor_dll - Win32 ANSI Release"
# Name "vendor_dll - Win32 CCITT Release"
# Begin Group "MTP3"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\ansi-mgmt.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-mtp3.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-mtp3_alarms.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-mtp3_ifc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-slm.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-slt.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-smh.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-srm.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-stm.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-mgmt.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-mtp3.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-mtp3_alarms.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-mtp3_ifc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-slm.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-slt.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-smh.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-srm.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-stm.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\include\mtp3_intern.h
# End Source File
# End Group
# Begin Group "SCCP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\ansi-sccp.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-sccp_alarms.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-sccp_gtt.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-sccp_ifc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-sclc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-scmg.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-scoc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-scrc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-sccp.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-sccp_alarms.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-sccp_gtt.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-sccp_ifc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-sclc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-scmg.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-scoc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-scrc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\include\sccp_intern.h
# End Source File
# End Group
# Begin Group "ISUP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\ansi-isup.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-isup_alarms.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-isup_context.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-isup_data.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-isup_ifc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-sprc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\include\isup_intern.h
# End Source File
# Begin Source File

SOURCE=".\itu-isup.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-isup_alarms.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-isup_context.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-isup_data.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-isup_ifc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-sprc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# End Group
# Begin Group "TCAP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\ansi-cmp.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-tcap.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-tcap_alarms.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-tcap_context.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-tcap_ifc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-tpcpi.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-trp.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-cco.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-dha.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-tcap.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-tcap_alarms.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-tcap_context.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-tcap_ifc.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-tco.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-tsm.c"

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\include\tcap_intern.h
# End Source File
# End Group
# Begin Group "Libraries"

# PROP Default_Filter "lib"
# Begin Source File

SOURCE="..\..\..\IntelliSS7\common\include\asn-c\AsnC.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\ENGINE.lib

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\ENGINED.lib

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\VFrameD.lib

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\AOCVFrameD.lib

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\COAVFrame.lib

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\COAVFrameD.lib

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\VFrame.lib

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\AOCVFrame.lib

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\AsnC.lib

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\AsnCD.lib

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\ansi.c

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\itu.c

!IF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor_dll - Win32 CCITT Release"

!ENDIF 

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
# End Target
# End Project
