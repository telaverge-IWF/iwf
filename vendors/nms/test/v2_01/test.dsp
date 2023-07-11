# Microsoft Developer Studio Project File - Name="test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=test - Win32 Debug ANSI V2_01
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test.mak" CFG="test - Win32 Debug ANSI V2_01"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test - Win32 Debug ANSI V2_12" (based on "Win32 (x86) Console Application")
!MESSAGE "test - Win32 Debug CCITT V2_12" (based on "Win32 (x86) Console Application")
!MESSAGE "test - Win32 Debug CCITT V2_01" (based on "Win32 (x86) Console Application")
!MESSAGE "test - Win32 Debug ANSI V2_01" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test - Win32 Debug ANSI V2_12"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "test___Win32_Debug_ANSI_V2_12"
# PROP BASE Intermediate_Dir "test___Win32_Debug_ANSI_V2_12"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_ANSI_V2_12"
# PROP Intermediate_Dir "Debug_ANSI_V2_12"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(VENDOR_ROOT)/nms/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/tools/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /D "DEBUG" /FR /YX /FD /GZ /c
# SUBTRACT BASE CPP /X
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(VENDOR_ROOT)/nms/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/tools/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /D "DEBUG" /FR /YX /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_12"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "test___Win32_Debug_CCITT_V2_12"
# PROP BASE Intermediate_Dir "test___Win32_Debug_CCITT_V2_12"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_CCITT_V2_12"
# PROP Intermediate_Dir "Debug_CCITT_V2_12"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(VENDOR_ROOT)/nms/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/tools/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /D "DEBUG" /FR /YX /FD /GZ /c
# SUBTRACT BASE CPP /X
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(VENDOR_ROOT)/nms/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/tools/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /D "DEBUG" /FR /YX /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_01"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "test___Win32_Debug_CCITT_V2_01"
# PROP BASE Intermediate_Dir "test___Win32_Debug_CCITT_V2_01"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_CCITT_V2_01"
# PROP Intermediate_Dir "Debug_CCITT_V2_01"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(VENDOR_ROOT)/nms/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/tools/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /D "DEBUG" /FR /YX /FD /GZ /c
# SUBTRACT BASE CPP /X
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(VENDOR_ROOT)/nms/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/tools/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /D "DEBUG" /FR /YX /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "test - Win32 Debug ANSI V2_01"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "test___Win32_Debug_ANSI_V2_01"
# PROP BASE Intermediate_Dir "test___Win32_Debug_ANSI_V2_01"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_ANSI_V2_01"
# PROP Intermediate_Dir "Debug_ANSI_V2_01"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(VENDOR_ROOT)/nms/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/tools/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /D "DEBUG" /FR /YX /FD /GZ /c
# SUBTRACT BASE CPP /X
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(VENDOR_ROOT)/nms/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/tools/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /D "DEBUG" /FR /YX /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "test - Win32 Debug ANSI V2_12"
# Name "test - Win32 Debug CCITT V2_12"
# Name "test - Win32 Debug CCITT V2_01"
# Name "test - Win32 Debug ANSI V2_01"
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

!IF  "$(CFG)" == "test - Win32 Debug ANSI V2_12"

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_12"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_01"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug ANSI V2_01"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\ISUP\lib\CCITT-ISUPD.lib"

!IF  "$(CFG)" == "test - Win32 Debug ANSI V2_12"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_12"

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_01"

!ELSEIF  "$(CFG)" == "test - Win32 Debug ANSI V2_01"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\SupportD.lib
# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\MTP3\lib\CCITT-MTP3D.lib"

!IF  "$(CFG)" == "test - Win32 Debug ANSI V2_12"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_12"

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_01"

!ELSEIF  "$(CFG)" == "test - Win32 Debug ANSI V2_01"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\MTP3\lib\ANSI-MTP3D.lib"

!IF  "$(CFG)" == "test - Win32 Debug ANSI V2_12"

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_12"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_01"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug ANSI V2_01"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\CORED.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\tools\lib\UnitTestD.lib
# End Source File
# Begin Source File

SOURCE=..\lib\ANSI_NMSVendor_V2_01D.lib

!IF  "$(CFG)" == "test - Win32 Debug ANSI V2_12"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_12"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_01"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug ANSI V2_01"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\lib\CCITT_NMSVendor_V2_01D.lib

!IF  "$(CFG)" == "test - Win32 Debug ANSI V2_12"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_12"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_01"

!ELSEIF  "$(CFG)" == "test - Win32 Debug ANSI V2_01"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\nms_v2_12\lib\CCITT_NMSVendor_V2_12D.lib

!IF  "$(CFG)" == "test - Win32 Debug ANSI V2_12"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_12"

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_01"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug ANSI V2_01"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\nms_v2_12\lib\ANSI_NMSVendor_V2_12D.lib

!IF  "$(CFG)" == "test - Win32 Debug ANSI V2_12"

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_12"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug CCITT V2_01"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug ANSI V2_01"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
