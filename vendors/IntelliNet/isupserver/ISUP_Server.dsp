# Microsoft Developer Studio Project File - Name="ISUP_Server" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ISUP_Server - Win32 ANSI Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ISUP_Server.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ISUP_Server.mak" CFG="ISUP_Server - Win32 ANSI Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ISUP_Server - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ISUP_Server - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "ISUP_Server - Win32 CCITT Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "ISUP_Server - Win32 CCITT Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ISUP_Server - Win32 ANSI Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ISUP_Server - Win32 ANSI Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ISUP_Server - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"../bin/Run_ISUP_CCITT.exe" /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../bin/Run_ISUP_CCITTD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CCITT Debug"
# PROP BASE Intermediate_Dir "CCITT Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITTDebug"
# PROP Intermediate_Dir "CCITTDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /D "ISUP_SERVER_IMPLEMENTATION" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../bin/Run_ISUP_CCITTD.exe" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../bin/Run_ISUP_CCITTD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CCITT Release"
# PROP BASE Intermediate_Dir "CCITT Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITTRelease"
# PROP Intermediate_Dir "CCITTRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /D "ISUP_SERVER_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"../bin/Run_ISUP_CCITT.exe" /IGNORE:4089
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"../bin/Run_ISUP_CCITT.exe" /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ANSI Release"
# PROP BASE Intermediate_Dir "ANSI Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSIRelease"
# PROP Intermediate_Dir "ANSIRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /D "ISUP_SERVER_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"../bin/Run_ISUP_CCITT.exe" /IGNORE:4089
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"../bin/Run_ISUP_ANSI.exe" /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ANSI Debug"
# PROP BASE Intermediate_Dir "ANSI Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSIDebug"
# PROP Intermediate_Dir "ANSIDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /D "ISUP_SERVER_IMPLEMENTATION" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../bin/Run_ISUP_CCITTD.exe" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../bin/Run_ISUP_ANSID.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ISUP_Server - Win32 Release"
# Name "ISUP_Server - Win32 Debug"
# Name "ISUP_Server - Win32 CCITT Debug"
# Name "ISUP_Server - Win32 CCITT Release"
# Name "ISUP_Server - Win32 ANSI Release"
# Name "ISUP_Server - Win32 ANSI Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\serverimpl.c
# End Source File
# Begin Source File

SOURCE=.\serverlayer.c
# End Source File
# Begin Source File

SOURCE=.\servermain.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\serverimpl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\ENGINED.lib

!IF  "$(CFG)" == "ISUP_Server - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 Debug"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\VFrameD.lib

!IF  "$(CFG)" == "ISUP_Server - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 Debug"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\lib\CCITTVendorD.lib

!IF  "$(CFG)" == "ISUP_Server - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 Debug"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\DRIVERD.lib

!IF  "$(CFG)" == "ISUP_Server - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 Debug"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\VFrame.lib

!IF  "$(CFG)" == "ISUP_Server - Win32 Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\DRIVER.lib

!IF  "$(CFG)" == "ISUP_Server - Win32 Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\ENGINE.lib

!IF  "$(CFG)" == "ISUP_Server - Win32 Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\lib\CCITTVendor.lib

!IF  "$(CFG)" == "ISUP_Server - Win32 Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\lib\ANSIVendorD.lib

!IF  "$(CFG)" == "ISUP_Server - Win32 Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 Debug"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\lib\ANSIVendor.lib

!IF  "$(CFG)" == "ISUP_Server - Win32 Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 Debug"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "ISUP_Server - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
