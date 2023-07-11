# Microsoft Developer Studio Project File - Name="gcs_daemon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=gcs_daemon - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gcs_daemon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gcs_daemon.mak" CFG="gcs_daemon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gcs_daemon - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "gcs_daemon - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "gcs_daemon_Win32_Release"
# PROP Intermediate_Dir "gcs_daemon_Win32_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "ARCH_PC_WIN95" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /machine:I386 /out:"../bin/gcs_daemon.exe"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "gcs_daemon_Win32_Debug"
# PROP Intermediate_Dir "gcs_daemon_Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ARCH_PC_WIN95" /D "HAVE_STRERROR" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../bin/gcs_daemonD.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "gcs_daemon - Win32 Release"
# Name "gcs_daemon - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\acm.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\acp-permit.c"

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\alarm.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\arch.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\auth-ip.c"

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\auth-null.c"

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\config_lexer.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\config_parser.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\configuration.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\data_link.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\events.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\flow_control.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\groups.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\log.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\membership.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\memory.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\message.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\network.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\protocol.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\session.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\skiplist.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\spread.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\status.c

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# ADD CPP /D "HAVE_STRERROR"

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\acm.h
# End Source File
# Begin Source File

SOURCE=.\alarm.h
# End Source File
# Begin Source File

SOURCE=.\arch.h
# End Source File
# Begin Source File

SOURCE=.\conf_body.h
# End Source File
# Begin Source File

SOURCE=.\config_parser.h
# End Source File
# Begin Source File

SOURCE=.\configuration.h
# End Source File
# Begin Source File

SOURCE=.\data_link.h
# End Source File
# Begin Source File

SOURCE=.\errors.h
# End Source File
# Begin Source File

SOURCE=.\flow_control.h
# End Source File
# Begin Source File

SOURCE=.\groups.h
# End Source File
# Begin Source File

SOURCE=.\log.h
# End Source File
# Begin Source File

SOURCE=.\membership.h
# End Source File
# Begin Source File

SOURCE=.\memory.h
# End Source File
# Begin Source File

SOURCE=.\message.h
# End Source File
# Begin Source File

SOURCE=.\net_types.h
# End Source File
# Begin Source File

SOURCE=.\network.h
# End Source File
# Begin Source File

SOURCE=.\objects.h
# End Source File
# Begin Source File

SOURCE=.\prot_body.h
# End Source File
# Begin Source File

SOURCE=.\prot_objs.h
# End Source File
# Begin Source File

SOURCE=.\protocol.h
# End Source File
# Begin Source File

SOURCE=.\scatter.h
# End Source File
# Begin Source File

SOURCE=.\sess_body.h
# End Source File
# Begin Source File

SOURCE=.\sess_types.h
# End Source File
# Begin Source File

SOURCE=.\session.h
# End Source File
# Begin Source File

SOURCE=.\skiplist.h
# End Source File
# Begin Source File

SOURCE=.\skiplist_p.h
# End Source File
# Begin Source File

SOURCE=.\sp_events.h
# End Source File
# Begin Source File

SOURCE=.\spread_params.h
# End Source File
# Begin Source File

SOURCE=.\status.h
# End Source File
# End Group
# Begin Group "Libraries"

# PROP Default_Filter "lib"
# End Group
# Begin Source File

SOURCE=.\config_gram.l

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# Begin Custom Build - Compiling Lex File...
InputPath=.\config_gram.l

"./config_lexer.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if not exist \tmp mkdir \tmp 
	flex -oconfig_lexer.c config_gram.l 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

# Begin Custom Build - Compiling Lex file...
InputPath=.\config_gram.l

"./config_lexer.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if not exist \tmp mkdir \tmp 
	flex -oconfig_lexer.c config_gram.l 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\config_parse.y

!IF  "$(CFG)" == "gcs_daemon - Win32 Release"

# Begin Custom Build - Compiling Yacc File....
InputPath=.\config_parse.y

BuildCmds= \
	if not exist \tmp mkdir \tmp \
	bison -d -o config_parser.c -S bison.simple config_parse.y \
	

"./config_parser.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"./config_parser.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "gcs_daemon - Win32 Debug"

# Begin Custom Build - Compiling Yacc file...
InputPath=.\config_parse.y

BuildCmds= \
	if not exist \tmp mkdir \tmp \
	bison -d -o config_parser.c -S bison.simple config_parse.y \
	

"./config_parser.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"./config_parser.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
