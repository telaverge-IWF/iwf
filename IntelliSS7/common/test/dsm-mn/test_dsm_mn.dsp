# Microsoft Developer Studio Project File - Name="test_dsm_mn" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=test_dsm_mn - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "test_dsm_mn.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test_dsm_mn.mak" CFG="test_dsm_mn - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test_dsm_mn - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "test_dsm_mn - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "test_dsm_mn___Win32_Debug"
# PROP BASE Intermediate_Dir "test_dsm_mn___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Win32_Debug"
# PROP Intermediate_Dir "Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "../../include" /I "../../include/mnt" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ITS_IMPLEMENTATION" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "../../include" /I "../../include/mnt" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /out:"./test_dsm_mn_stubD.exe" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /out:"./test_dsm_mnD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "test_dsm_mn___Win32_Release"
# PROP BASE Intermediate_Dir "test_dsm_mn___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win32_Release"
# PROP Intermediate_Dir "Win32_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "." /I "../../include" /I "../../include/mnt" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "ITS_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "../../include" /I "../../include/mnt" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /machine:I386 /out:"./test_dsm_mn_stub.exe"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /machine:I386 /out:"./test_dsm_mn.exe"

!ENDIF 

# Begin Target

# Name "test_dsm_mn - Win32 Debug"
# Name "test_dsm_mn - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\test_dsm_mn_main.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Libraries"

# PROP Default_Filter "lib"
# Begin Source File

SOURCE=..\..\lib\ENGINED.lib

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\DRIVER++D.lib"

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\MNT-FOR-ENGINED.lib"

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\GCS-CLIENT-FOR-ENGINED.lib"

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\DSM-STUBD.lib"

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\DSM-GCSD.lib"

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\DSM-SCID.lib"

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\lib\ENGINE.lib

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\DRIVER++.lib"

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\MNT-FOR-ENGINE.lib"

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\GCS-CLIENT-FOR-ENGINE.lib"

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\DSM-STUB.lib"

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\DSM-GCS.lib"

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\DSM-SCI.lib"

!IF  "$(CFG)" == "test_dsm_mn - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test_dsm_mn - Win32 Release"

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
