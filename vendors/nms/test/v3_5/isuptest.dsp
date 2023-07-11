# Microsoft Developer Studio Project File - Name="isuptest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=isuptest - Win32 Debug ANSI
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "isuptest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "isuptest.mak" CFG="isuptest - Win32 Debug ANSI"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "isuptest - Win32 Debug CCITT" (based on "Win32 (x86) Console Application")
!MESSAGE "isuptest - Win32 Debug ANSI" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "isuptest - Win32 Debug CCITT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug CCITT"
# PROP BASE Intermediate_Dir "Debug CCITT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug CCITT"
# PROP Intermediate_Dir "Debug CCITT"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(VENDOR_ROOT)/nms/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/tools/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "isuptest - Win32 Debug ANSI"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug ANSI"
# PROP BASE Intermediate_Dir "Debug ANSI"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug ANSI"
# PROP Intermediate_Dir "Debug ANSI"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(VENDOR_ROOT)/nms/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/tools/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "isuptest - Win32 Debug CCITT"
# Name "isuptest - Win32 Debug ANSI"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\printISUPMsg.c
# End Source File
# Begin Source File

SOURCE=.\readISUPMsg.c
# End Source File
# Begin Source File

SOURCE=.\sendISUPMsg.c
# End Source File
# Begin Source File

SOURCE=.\test.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\printISUPMsg.h
# End Source File
# Begin Source File

SOURCE=.\readISUPMsg.h
# End Source File
# Begin Source File

SOURCE=.\sendISUPMsg.h
# End Source File
# End Group
# Begin Group "libraries"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\IntelliSS7\ISUP\lib\ANSI-ISUPD.lib"

!IF  "$(CFG)" == "isuptest - Win32 Debug CCITT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isuptest - Win32 Debug ANSI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\MTP3\lib\ANSI-MTP3D.lib"

!IF  "$(CFG)" == "isuptest - Win32 Debug CCITT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isuptest - Win32 Debug ANSI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\lib\CCITT_NMSVendor_V3_5D.lib

!IF  "$(CFG)" == "isuptest - Win32 Debug CCITT"

!ELSEIF  "$(CFG)" == "isuptest - Win32 Debug ANSI"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\lib\ANSI_NMSVendor_V3_5D.lib

!IF  "$(CFG)" == "isuptest - Win32 Debug CCITT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isuptest - Win32 Debug ANSI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\CORED.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\SupportD.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\tools\lib\UnitTestD.lib
# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\ISUP\lib\CCITT-ISUPD.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\MTP3\lib\CCITT-MTP3D.lib"
# End Source File
# End Group
# End Target
# End Project
