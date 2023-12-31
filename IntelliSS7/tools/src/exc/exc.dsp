# Microsoft Developer Studio Project File - Name="exc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=exc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "exc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "exc.mak" CFG="exc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "exc - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "exc - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "exc - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "." /I "$(ITS_ROOT)/common/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "FLEX" /D "YY_USE_PROTOS" /D "C_FLEX" /U "YYPURE" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "exc - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)/common/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "FLEX" /D "YY_USE_PROTOS" /D "C_FLEX" /U "YYPURE" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"..\..\bin\exc.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "exc - Win32 Release"
# Name "exc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "c;cpp"
# Begin Source File

SOURCE=.\exc_assert.cpp
# End Source File
# Begin Source File

SOURCE=.\exc_generate.cpp
# End Source File
# Begin Source File

SOURCE=.\exc_lex.yy.cpp

!IF  "$(CFG)" == "exc - Win32 Release"

# SUBTRACT CPP /D "YY_USE_PROTOS"

!ELSEIF  "$(CFG)" == "exc - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\exc_main.cpp
# End Source File
# Begin Source File

SOURCE=.\exc_yacc.tab.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\exc_assert.h
# End Source File
# Begin Source File

SOURCE=.\exc_generate.h
# End Source File
# Begin Source File

SOURCE=.\exc_lex.h
# End Source File
# Begin Source File

SOURCE=.\exc_parse_types.h
# End Source File
# Begin Source File

SOURCE=.\exc_yacc.tab.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\exc_lex.l

!IF  "$(CFG)" == "exc - Win32 Release"

# Begin Custom Build
InputPath=.\exc_lex.l

".\exc_lex.yy.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if not exist \tmp mkdir \tmp 
	flex exc_lex.l 
	copy .\lex.yy.c .\exc_lex.yy.c 
	del .\lex.yy.c 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "exc - Win32 Debug"

USERDEP__EXC_L="exc_lex.l"	
# Begin Custom Build - Compiling lex file...
InputPath=.\exc_lex.l

".\exc_lex.yy.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if not exist \tmp mkdir \tmp 
	flex exc_lex.l 
	copy .\lex.yy.c .\exc_lex.yy.cpp 
	del .\lex.yy.c 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\exc_yacc.y

!IF  "$(CFG)" == "exc - Win32 Release"

# Begin Custom Build
InputPath=.\exc_yacc.y

BuildCmds= \
	if not exist \tmp mkdir \tmp \
	bison  -d exc_yacc.y -o exc_yacc.tab.cpp \
	copy .\exc_yacc.tab.cpp.h .\exc_yacc.tab.h \
	del .\exc_yacc.tab.cpp.h \
	

".\exc_yacc.tab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\exc_yacc.tab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "exc - Win32 Debug"

USERDEP__EXC_Y="exc_yacc.y"	
# Begin Custom Build - Compiling yacc file...
InputPath=.\exc_yacc.y

BuildCmds= \
	if not exist \tmp mkdir \tmp \
	bison -d exc_yacc.y -o exc_yacc.tab.cpp \
	copy .\exc_yacc.tab.cpp.h .\exc_yacc.tab.h \
	del .\exc_yacc.tab.cpp.h \
	

".\exc_yacc.tab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\exc_yacc.tab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
