# Microsoft Developer Studio Project File - Name="bsslap" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=bsslap - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bsslap.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bsslap.mak" CFG="bsslap - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bsslap - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "bsslap - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bsslap - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "bsslap - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "." /I "..\..\..\include" /I "$(ITS_ROOT)\common\include" /I "$(HOME)\infra\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "bsslap - Win32 Release"
# Name "bsslap - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\abort.cpp
# End Source File
# Begin Source File

SOURCE=..\ie\cause.cpp
# End Source File
# Begin Source File

SOURCE=..\ie\cellidentity.cpp
# End Source File
# Begin Source File

SOURCE=..\ie\channeldescription.cpp
# End Source File
# Begin Source File

SOURCE=..\ie\deltatimer.cpp
# End Source File
# Begin Source File

SOURCE=..\ie\handoverreference.cpp
# End Source File
# Begin Source File

SOURCE=..\ie\handovertype.cpp
# End Source File
# Begin Source File

SOURCE=..\ie\infoelement.cpp
# End Source File
# Begin Source File

SOURCE=..\ie\measurementreport.cpp
# End Source File
# Begin Source File

SOURCE=..\message.cpp
# End Source File
# Begin Source File

SOURCE=..\ie\mspower.cpp
# End Source File
# Begin Source File

SOURCE=..\ie\neighborcellidentity.cpp
# End Source File
# Begin Source File

SOURCE=..\ie\neighborstarttime.cpp
# End Source File
# Begin Source File

SOURCE=..\reject.cpp
# End Source File
# Begin Source File

SOURCE=..\reset.cpp
# End Source File
# Begin Source File

SOURCE=..\ie\startingtime.cpp
# End Source File
# Begin Source File

SOURCE=..\tarequest.cpp
# End Source File
# Begin Source File

SOURCE=..\taresponse.cpp
# End Source File
# Begin Source File

SOURCE=..\ie\timingadvance.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\include\bsslap\abort.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\cause.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\cellidentity.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\channeldescription.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\deltatimer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\exceptions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\frequencylist.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\handoverreference.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\handovertype.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\infoelement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\measurementreport.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\message.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\mspositioncommand.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\mspositionresponse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\mspower.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\neighborcellidentity.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\neighborstarttime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\reject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\reset.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\startingtime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\talayer3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\tarequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\taresponse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\ie\timingadvance.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\toarequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\bsslap\toaresponse.h
# End Source File
# End Group
# End Target
# End Project
