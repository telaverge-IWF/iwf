# Microsoft Developer Studio Project File - Name="vendor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=vendor - Win32 ANSI over CCITT Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vendor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vendor.mak" CFG="vendor - Win32 ANSI over CCITT Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vendor - Win32 ANSI Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "vendor - Win32 ANSI Release" (based on "Win32 (x86) Static Library")
!MESSAGE "vendor - Win32 CCITT Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "vendor - Win32 CCITT Release" (based on "Win32 (x86) Static Library")
!MESSAGE "vendor - Win32 CCITT over ANSI Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "vendor - Win32 CCITT over ANSI Release" (based on "Win32 (x86) Static Library")
!MESSAGE "vendor - Win32 ANSI over CCITT Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "vendor - Win32 ANSI over CCITT Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vendor__"
# PROP BASE Intermediate_Dir "vendor__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSIVendorD"
# PROP Intermediate_Dir "ANSIVendorD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../include/ansi" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ANSI" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include/ansi" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "PEPSY_CODEC" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\vendor.lib"
# ADD LIB32 /nologo /out:"../lib/ANSIVendorD.lib"
# Begin Custom Build
InputPath=\cvsroot\PR6.4\vendors\IntelliNet\lib\ANSIVendorD.lib
SOURCE="$(InputPath)"

"gendoc.out" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bash -x generate

# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vendor_0"
# PROP BASE Intermediate_Dir "vendor_0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSIVendor"
# PROP Intermediate_Dir "ANSIVendor"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "PEPSY_CODEC" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/ANSIVendor.lib"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vendor_1"
# PROP BASE Intermediate_Dir "vendor_1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITTVendorD"
# PROP Intermediate_Dir "CCITTVendorD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../include/ansi" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ANSI" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "PEPSY_CODEC" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\vendor.lib"
# ADD LIB32 /nologo /out:"../lib/CCITTVendorD.lib"
# Begin Custom Build
InputPath=..\lib\CCITTVendorD.lib
SOURCE="$(InputPath)"

"gendoc.out" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bash -x generate

# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vendor_2"
# PROP BASE Intermediate_Dir "vendor_2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITTVendor"
# PROP Intermediate_Dir "CCITTVendor"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "PEPSY_CODEC" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/CCITTVendor.lib"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vendor__"
# PROP BASE Intermediate_Dir "vendor__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITT-ANSID"
# PROP Intermediate_Dir "CCITT-ANSID"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "_DEBUG" /D "USE_ANSI_SCCP" /D "SPLIT_STACK" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "PEPSY_CODEC" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/ANSIVendorD.lib"
# ADD LIB32 /nologo /out:"../lib/CCITT-ANSIVendorD.lib"
# Begin Custom Build
InputPath=\cvsroot\PR6.4\vendors\IntelliNet\lib\CCITT-ANSIVendorD.lib
SOURCE="$(InputPath)"

"gendoc.out" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bash -x generate

# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vendor_0"
# PROP BASE Intermediate_Dir "vendor_0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITT-ANSI"
# PROP Intermediate_Dir "CCITT-ANSI"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "NDEBUG" /D "USE_ANSI_SCCP" /D "SPLIT_STACK" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "PEPSY_CODEC" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/ANSIVendor.lib"
# ADD LIB32 /nologo /out:"../lib/CCITT-ANSIVendor.lib"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vendor_1"
# PROP BASE Intermediate_Dir "vendor_1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI-CCITTD"
# PROP Intermediate_Dir "ANSI-CCITTD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /D "_DEBUG" /D "INCLUDE_CODEC" /D "WIN32" /D "_WINDOWS" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "_DEBUG" /D "USE_ITU_SCCP" /D "SPLIT_STACK" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "PEPSY_CODEC" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITTVendorD.lib"
# ADD LIB32 /nologo /out:"../lib/ANSI-CCITTVendorD.lib"
# Begin Custom Build
InputPath=\cvsroot\PR6.4\vendors\IntelliNet\lib\ANSI-CCITTVendorD.lib
SOURCE="$(InputPath)"

"gendoc.out" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bash -x generate

# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vendor_2"
# PROP BASE Intermediate_Dir "vendor_2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI-CCITT"
# PROP Intermediate_Dir "ANSI-CCITT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/ansi" /I "../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "NDEBUG" /D "USE_ITU_SCCP" /D "SPLIT_STACK" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /D "PEPSY_CODEC" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITTVendor.lib"
# ADD LIB32 /nologo /out:"../lib/ANSI-CCITTVendor.lib"

!ENDIF 

# Begin Target

# Name "vendor - Win32 ANSI Debug"
# Name "vendor - Win32 ANSI Release"
# Name "vendor - Win32 CCITT Debug"
# Name "vendor - Win32 CCITT Release"
# Name "vendor - Win32 CCITT over ANSI Debug"
# Name "vendor - Win32 CCITT over ANSI Release"
# Name "vendor - Win32 ANSI over CCITT Debug"
# Name "vendor - Win32 ANSI over CCITT Release"
# Begin Group "MTP3"

# PROP Default_Filter "*.c *.h"
# Begin Source File

SOURCE=".\ansi-mgmt.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-mtp3.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-mtp3_ifc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-slm.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-slt.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-smh.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-srm.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-stm.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-mgmt.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-mtp3.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-mtp3_ifc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-slt.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-smh.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-srm.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-stm.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mtp3_intern.h
# End Source File
# End Group
# Begin Group "SCCP"

# PROP Default_Filter "*.c *.h"
# Begin Source File

SOURCE=".\ansi-sccp.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-sccp_gtt.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-sccp_ifc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-sclc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-scmg.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-scoc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-scrc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-sccp.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-sccp_gtt.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-sccp_ifc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-sclc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-scmg.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-scoc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-scrc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sccp_intern.h
# End Source File
# End Group
# Begin Group "ISUP"

# PROP Default_Filter "*.c *.h"
# Begin Source File

SOURCE=".\ansi-isup.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-isup_ifc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\isup_intern.h
# End Source File
# Begin Source File

SOURCE=".\itu-isup.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-isup_context.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-isup_data.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-isup_ifc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-sprc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# End Group
# Begin Group "TCAP"

# PROP Default_Filter "*.c *.h"
# Begin Source File

SOURCE=".\ansi-cmp.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# ADD CPP /D "USE_CCITT_SCCP"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# ADD CPP /D "USE_CCITT_SCCP"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-tcap.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# ADD CPP /D "USE_CCITT_SCCP"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# ADD CPP /D "USE_CCITT_SCCP"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-tcap_context.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# ADD CPP /D "USE_CCITT_SCCP"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# ADD CPP /D "USE_CCITT_SCCP"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-tcap_ifc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# ADD CPP /D "USE_CCITT_SCCP"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# ADD CPP /D "USE_CCITT_SCCP"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ANSI-TCAP_tables.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-tpcpi.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# ADD CPP /D "USE_CCITT_SCCP"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# ADD CPP /D "USE_CCITT_SCCP"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-trp.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP BASE Exclude_From_Build 1
# ADD CPP /D "USE_CCITT_SCCP"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP BASE Exclude_From_Build 1
# ADD CPP /D "USE_CCITT_SCCP"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-cco.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-dha.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ITU-TCAP-APDU_tables.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-tcap.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-tcap_context.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-tcap_ifc.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ITU-TCAP_tables.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-tco.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-tsm.c"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\tcap_intern.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ansi.c

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ansiTCAP.asn

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# Begin Custom Build
InputPath=.\ansiTCAP.asn

"ANSI-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ansiTCAP.asn 
	copy ANSI-TCAP-types.h ..\include\ansi 
	del ANSI-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# Begin Custom Build
InputPath=.\ansiTCAP.asn

"ANSI-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ansiTCAP.asn 
	copy ANSI-TCAP-types.h ..\include\ansi 
	del ANSI-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

# Begin Custom Build
InputPath=.\ansiTCAP.asn

"ANSI-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ansiTCAP.asn 
	copy ANSI-TCAP-types.h ..\include\ansi 
	del ANSI-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# Begin Custom Build
InputPath=.\ansiTCAP.asn

"ANSI-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ansiTCAP.asn 
	copy ANSI-TCAP-types.h ..\include\ansi 
	del ANSI-TCAP-types.h 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\itu.c

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ituTCAP-APDU.asn"

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# Begin Custom Build
InputPath=".\ituTCAP-APDU.asn"

"ITU-TCAP-APDU_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP-APDU.asn 
	copy ITU-TCAP-APDU-types.h ..\include\itu 
	del ITU-TCAP-APDU-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# Begin Custom Build
InputPath=".\ituTCAP-APDU.asn"

"ITU-TCAP-APDU_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP-APDU.asn 
	copy ITU-TCAP-APDU-types.h ..\include\itu 
	del ITU-TCAP-APDU-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# Begin Custom Build
InputPath=".\ituTCAP-APDU.asn"

"ITU-TCAP-APDU_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP-APDU.asn 
	copy ITU-TCAP-APDU-types.h ..\include\itu 
	del ITU-TCAP-APDU-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# Begin Custom Build
InputPath=".\ituTCAP-APDU.asn"

"ITU-TCAP-APDU_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP-APDU.asn 
	copy ITU-TCAP-APDU-types.h ..\include\itu 
	del ITU-TCAP-APDU-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ituTCAP.asn

!IF  "$(CFG)" == "vendor - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Debug"

# Begin Custom Build
InputPath=.\ituTCAP.asn

"ITU-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP.asn 
	copy ITU-TCAP-types.h ..\include\itu 
	del ITU-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT Release"

# Begin Custom Build
InputPath=.\ituTCAP.asn

"ITU-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP.asn 
	copy ITU-TCAP-types.h ..\include\itu 
	del ITU-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Debug"

# Begin Custom Build
InputPath=.\ituTCAP.asn

"ITU-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP.asn 
	copy ITU-TCAP-types.h ..\include\itu 
	del ITU-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 CCITT over ANSI Release"

# Begin Custom Build
InputPath=.\ituTCAP.asn

"ITU-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP.asn 
	copy ITU-TCAP-types.h ..\include\itu 
	del ITU-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "vendor - Win32 ANSI over CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ss7_alarms.c
# End Source File
# Begin Source File

SOURCE=..\include\ss7_alarms.h
# End Source File
# Begin Source File

SOURCE=..\include\ss7_mgmt.h
# End Source File
# Begin Source File

SOURCE=.\ss7_pegs.c
# End Source File
# Begin Source File

SOURCE=..\include\ss7_pegs.h
# End Source File
# End Target
# End Project
