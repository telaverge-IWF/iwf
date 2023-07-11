# Microsoft Developer Studio Project File - Name="CppGSMMAPlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CppGSMMAPlib - Win32 P2 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CppGSMMAPlib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CppGSMMAPlib.mak" CFG="CppGSMMAPlib - Win32 P2 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CppGSMMAPlib - Win32 P2P Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "CppGSMMAPlib - Win32 P2P Release" (based on "Win32 (x86) Static Library")
!MESSAGE "CppGSMMAPlib - Win32 P2 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "CppGSMMAPlib - Win32 P2 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CppGSMMAPlib - Win32 P2P Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CppGSMMA"
# PROP BASE Intermediate_Dir "CppGSMMA"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CppGSMMAPP2PD"
# PROP Intermediate_Dir "CppGSMMAPP2PD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\GSMMAP++D.lib"
# ADD LIB32 /nologo /out:"..\lib\GSMMAPP2P++D.lib"

!ELSEIF  "$(CFG)" == "CppGSMMAPlib - Win32 P2P Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CppGSMM0"
# PROP BASE Intermediate_Dir "CppGSMM0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CppGSMMAPP2P"
# PROP Intermediate_Dir "CppGSMMAPP2P"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\GSMMAP++.lib"
# ADD LIB32 /nologo /out:"..\lib\GSMMAPP2P++.lib"

!ELSEIF  "$(CFG)" == "CppGSMMAPlib - Win32 P2 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CppGSMM1"
# PROP BASE Intermediate_Dir "CppGSMM1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CppGSMMAPP2D"
# PROP Intermediate_Dir "CppGSMMAPP2D"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\GSMMAP++D.lib"
# ADD LIB32 /nologo /out:"..\lib\GSMMAPP2++D.lib"

!ELSEIF  "$(CFG)" == "CppGSMMAPlib - Win32 P2 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CppGSMM2"
# PROP BASE Intermediate_Dir "CppGSMM2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CppGSMMAPP2"
# PROP Intermediate_Dir "CppGSMMAPP2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\GSMMAP++.lib"
# ADD LIB32 /nologo /out:"..\lib\GSMMAPP2++.lib"

!ENDIF 

# Begin Target

# Name "CppGSMMAPlib - Win32 P2P Debug"
# Name "CppGSMMAPlib - Win32 P2P Release"
# Name "CppGSMMAPlib - Win32 P2 Debug"
# Name "CppGSMMAPlib - Win32 P2 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\AbsentSubscriberDiagnosticSM.cpp
# End Source File
# Begin Source File

SOURCE=.\AbsentSubscriberParam.cpp
# End Source File
# Begin Source File

SOURCE=.\AbsentSubscriberReason.cpp
# End Source File
# Begin Source File

SOURCE=.\AbsentSubscriberSM_Param.cpp
# End Source File
# Begin Source File

SOURCE=.\ActivateTraceModeArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ActivateTraceModeRes.cpp
# End Source File
# Begin Source File

SOURCE=.\Additional_Number.cpp
# End Source File
# Begin Source File

SOURCE=.\AddressString.cpp
# End Source File
# Begin Source File

SOURCE=.\AgeOfLocationInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\AlertingPattern.cpp
# End Source File
# Begin Source File

SOURCE=.\AlertReason.cpp
# End Source File
# Begin Source File

SOURCE=.\AlertServiceCentreArg.cpp
# End Source File
# Begin Source File

SOURCE=.\AnyTimeInterrogationArg.cpp
# End Source File
# Begin Source File

SOURCE=.\AnyTimeInterrogationRes.cpp
# End Source File
# Begin Source File

SOURCE=.\APN.cpp
# End Source File
# Begin Source File

SOURCE=.\ASCI_CallReference.cpp
# End Source File
# Begin Source File

SOURCE=.\ATI_NotAllowedParam.cpp
# End Source File
# Begin Source File

SOURCE=.\AuthenticationSet.cpp
# End Source File
# Begin Source File

SOURCE=.\AuthenticationSetList.cpp
# End Source File
# Begin Source File

SOURCE=.\BasicServiceCode.cpp
# End Source File
# Begin Source File

SOURCE=.\BasicServiceCriteria.cpp
# End Source File
# Begin Source File

SOURCE=.\BasicServiceGroupList.cpp
# End Source File
# Begin Source File

SOURCE=.\BasicServiceList.cpp
# End Source File
# Begin Source File

SOURCE=.\BearerServiceCode.cpp
# End Source File
# Begin Source File

SOURCE=.\BearerServiceList.cpp
# End Source File
# Begin Source File

SOURCE=.\BearerServNotProvParam.cpp
# End Source File
# Begin Source File

SOURCE=.\BusySubscriberParam.cpp
# End Source File
# Begin Source File

SOURCE=.\CallBarredParam.cpp
# End Source File
# Begin Source File

SOURCE=.\CallBarringCause.cpp
# End Source File
# Begin Source File

SOURCE=.\CallBarringFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\CallBarringFeatureList.cpp
# End Source File
# Begin Source File

SOURCE=.\CallBarringInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CallDirection.cpp
# End Source File
# Begin Source File

SOURCE=.\CallOutcome.cpp
# End Source File
# Begin Source File

SOURCE=.\CallReferenceNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\CallReportData.cpp
# End Source File
# Begin Source File

SOURCE=.\CallTypeCriteria.cpp
# End Source File
# Begin Source File

SOURCE=.\CamelCapabilityHandling.cpp
# End Source File
# Begin Source File

SOURCE=.\CamelInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CamelRoutingInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CancellationType.cpp
# End Source File
# Begin Source File

SOURCE=.\CancelLocationArg.cpp
# End Source File
# Begin Source File

SOURCE=.\CancelLocationRes.cpp
# End Source File
# Begin Source File

SOURCE=.\Category.cpp
# End Source File
# Begin Source File

SOURCE=.\CCBS_Data.cpp
# End Source File
# Begin Source File

SOURCE=.\CCBS_Feature.cpp
# End Source File
# Begin Source File

SOURCE=.\CCBS_FeatureList.cpp
# End Source File
# Begin Source File

SOURCE=.\CCBS_Index.cpp
# End Source File
# Begin Source File

SOURCE=.\CCBS_Indicators.cpp
# End Source File
# Begin Source File

SOURCE=.\CCBS_SubscriberStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\CellIdFixedLength.cpp
# End Source File
# Begin Source File

SOURCE=.\CellIdOrLAI.cpp
# End Source File
# Begin Source File

SOURCE=.\CipheringAlgorithm.cpp
# End Source File
# Begin Source File

SOURCE=.\CliRestrictionOption.cpp
# End Source File
# Begin Source File

SOURCE=.\CODEC_Info.cpp
# End Source File
# Begin Source File

SOURCE=.\ContextId.cpp
# End Source File
# Begin Source File

SOURCE=.\ContextIdList.cpp
# End Source File
# Begin Source File

SOURCE=.\CUG_CheckInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CUG_Feature.cpp
# End Source File
# Begin Source File

SOURCE=.\CUG_FeatureList.cpp
# End Source File
# Begin Source File

SOURCE=.\CUG_Index.cpp
# End Source File
# Begin Source File

SOURCE=.\CUG_Info.cpp
# End Source File
# Begin Source File

SOURCE=.\CUG_Interlock.cpp
# End Source File
# Begin Source File

SOURCE=.\CUG_RejectCause.cpp
# End Source File
# Begin Source File

SOURCE=.\CUG_RejectParam.cpp
# End Source File
# Begin Source File

SOURCE=.\CUG_Subscription.cpp
# End Source File
# Begin Source File

SOURCE=.\CUG_SubscriptionList.cpp
# End Source File
# Begin Source File

SOURCE=.\DataMissingParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DeactivateTraceModeArg.cpp
# End Source File
# Begin Source File

SOURCE=.\DeactivateTraceModeRes.cpp
# End Source File
# Begin Source File

SOURCE=.\DefaultCallHandling.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteSubscriberDataArg.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteSubscriberDataRes.cpp
# End Source File
# Begin Source File

SOURCE=.\DestinationNumberCriteria.cpp
# End Source File
# Begin Source File

SOURCE=.\DestinationNumberLengthList.cpp
# End Source File
# Begin Source File

SOURCE=.\DestinationNumberList.cpp
# End Source File
# Begin Source File

SOURCE=.\EMLPP_Info.cpp
# End Source File
# Begin Source File

SOURCE=.\EMLPP_Priority.cpp
# End Source File
# Begin Source File

SOURCE=.\EquipmentStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\EraseCC_EntryArg.cpp
# End Source File
# Begin Source File

SOURCE=.\EraseCC_EntryRes.cpp
# End Source File
# Begin Source File

SOURCE=.\EventReportData.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_BasicServiceCode.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_BasicServiceGroupList.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_BearerServiceCode.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_CallBarFeatureList.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_CallBarInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_CallBarringFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_ForwFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_ForwFeatureList.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_ForwInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_ForwOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_NoRepCondTime.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_SS_Data.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_SS_Info.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_SS_InfoList.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_SS_Status.cpp
# End Source File
# Begin Source File

SOURCE=.\Ext_TeleserviceCode.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtendedRoutingInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtensibleCallBarredParam.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtensibleSystemFailureParam.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtensionContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtensionSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ExternalSignalInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\FacilityNotSupParam.cpp
# End Source File
# Begin Source File

SOURCE=.\FailureReportArg.cpp
# End Source File
# Begin Source File

SOURCE=.\FailureReportRes.cpp
# End Source File
# Begin Source File

SOURCE=.\ForwardGroupCallSignallingArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ForwardingData.cpp
# End Source File
# Begin Source File

SOURCE=.\ForwardingFailedParam.cpp
# End Source File
# Begin Source File

SOURCE=.\ForwardingFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\ForwardingFeatureList.cpp
# End Source File
# Begin Source File

SOURCE=.\ForwardingInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ForwardingOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\ForwardingReason.cpp
# End Source File
# Begin Source File

SOURCE=.\ForwardingViolationParam.cpp
# End Source File
# Begin Source File

SOURCE=.\GenericServiceInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\GeographicalInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobalCellId.cpp
# End Source File
# Begin Source File

SOURCE=.\GmscCamelSubscriptionInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\GPRSDataList.cpp
# End Source File
# Begin Source File

SOURCE=.\GPRSSubscriptionData.cpp
# End Source File
# Begin Source File

SOURCE=.\GPRSSubscriptionDataWithdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupId.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupKeyNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\GSMMAPP2P.cpp
# End Source File
# Begin Source File

SOURCE=.\GSN_Address.cpp
# End Source File
# Begin Source File

SOURCE=.\GuidanceInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\HLR_Id.cpp
# End Source File
# Begin Source File

SOURCE=.\HLR_List.cpp
# End Source File
# Begin Source File

SOURCE=.\Identity.cpp
# End Source File
# Begin Source File

SOURCE=.\IllegalEquipmentParam.cpp
# End Source File
# Begin Source File

SOURCE=.\IllegalSubscriberParam.cpp
# End Source File
# Begin Source File

SOURCE=.\IMEI.cpp
# End Source File
# Begin Source File

SOURCE=.\IMSI.cpp
# End Source File
# Begin Source File

SOURCE=.\IMSI_WithLMSI.cpp
# End Source File
# Begin Source File

SOURCE=.\IncompatibleTerminalParam.cpp
# End Source File
# Begin Source File

SOURCE=.\InformServiceCentreArg.cpp
# End Source File
# Begin Source File

SOURCE=.\InsertSubscriberDataArg.cpp
# End Source File
# Begin Source File

SOURCE=.\InsertSubscriberDataRes.cpp
# End Source File
# Begin Source File

SOURCE=.\InterCUG_Restrictions.cpp
# End Source File
# Begin Source File

SOURCE=.\InterrogateSS_Res.cpp
# End Source File
# Begin Source File

SOURCE=.\InterrogationType.cpp
# End Source File
# Begin Source File

SOURCE=.\IntraCUG_Options.cpp
# End Source File
# Begin Source File

SOURCE=.\ISDN_AddressString.cpp
# End Source File
# Begin Source File

SOURCE=.\ISDN_SubaddressString.cpp
# End Source File
# Begin Source File

SOURCE=.\Kc.cpp
# End Source File
# Begin Source File

SOURCE=.\LAIFixedLength.cpp
# End Source File
# Begin Source File

SOURCE=.\LMSI.cpp
# End Source File
# Begin Source File

SOURCE=.\LocationInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\LocationInfoWithLMSI.cpp
# End Source File
# Begin Source File

SOURCE=.\LocationNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\LongTermDenialParam.cpp
# End Source File
# Begin Source File

SOURCE=.\MAP_AcceptInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MAP_CloseInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MAP_DialoguePDU.cpp
# End Source File
# Begin Source File

SOURCE=.\MAP_OpenInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MAP_ProviderAbortInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MAP_ProviderAbortReason.cpp
# End Source File
# Begin Source File

SOURCE=.\MAP_RefuseInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MAP_UserAbortChoice.cpp
# End Source File
# Begin Source File

SOURCE=.\MAP_UserAbortInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MAP_UserInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MAP_UserInfoHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\MatchType.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageWaitListFullParam.cpp
# End Source File
# Begin Source File

SOURCE=.\MO_ForwardSM_Arg.cpp
# End Source File
# Begin Source File

SOURCE=.\MO_ForwardSM_Res.cpp
# End Source File
# Begin Source File

SOURCE=.\MonitoringMode.cpp
# End Source File
# Begin Source File

SOURCE=.\MT_ForwardSM_Arg.cpp
# End Source File
# Begin Source File

SOURCE=.\MT_ForwardSM_Res.cpp
# End Source File
# Begin Source File

SOURCE=.\MW_Status.cpp
# End Source File
# Begin Source File

SOURCE=.\NAEA_CIC.cpp
# End Source File
# Begin Source File

SOURCE=.\NAEA_PreferredCI.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkAccessMode.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkResource.cpp
# End Source File
# Begin Source File

SOURCE=.\NoGroupCallNbParam.cpp
# End Source File
# Begin Source File

SOURCE=.\NoReplyConditionTime.cpp
# End Source File
# Begin Source File

SOURCE=.\NoRoamingNbParam.cpp
# End Source File
# Begin Source File

SOURCE=.\NoSubscriberReplyParam.cpp
# End Source File
# Begin Source File

SOURCE=.\NoteMsPresentForGprsArg.cpp
# End Source File
# Begin Source File

SOURCE=.\NoteMsPresentForGprsRes.cpp
# End Source File
# Begin Source File

SOURCE=.\NotReachableReason.cpp
# End Source File
# Begin Source File

SOURCE=.\NumberChangedParam.cpp
# End Source File
# Begin Source File

SOURCE=.\NumberOfForwarding.cpp
# End Source File
# Begin Source File

SOURCE=.\O_BcsmCamelTDP_Criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\O_BcsmCamelTDPData.cpp
# End Source File
# Begin Source File

SOURCE=.\O_BcsmCamelTDPDataList.cpp
# End Source File
# Begin Source File

SOURCE=.\O_BcsmTriggerDetectionPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\O_CSI.cpp
# End Source File
# Begin Source File

SOURCE=.\ODB_Data.cpp
# End Source File
# Begin Source File

SOURCE=.\ODB_GeneralData.cpp
# End Source File
# Begin Source File

SOURCE=.\ODB_HPLMN_Data.cpp
# End Source File
# Begin Source File

SOURCE=.\OR_NotAllowedParam.cpp
# End Source File
# Begin Source File

SOURCE=.\OR_Phase.cpp
# End Source File
# Begin Source File

SOURCE=.\OverrideCategory.cpp
# End Source File
# Begin Source File

SOURCE=.\Password.cpp
# End Source File
# Begin Source File

SOURCE=.\PCS_Extensions.cpp
# End Source File
# Begin Source File

SOURCE=.\PDP_Address.cpp
# End Source File
# Begin Source File

SOURCE=.\PDP_Context.cpp
# End Source File
# Begin Source File

SOURCE=.\PDP_Type.cpp
# End Source File
# Begin Source File

SOURCE=.\PrepareGroupCallArg.cpp
# End Source File
# Begin Source File

SOURCE=.\PrepareGroupCallRes.cpp
# End Source File
# Begin Source File

SOURCE=.\PrepareHO_Arg.cpp
# End Source File
# Begin Source File

SOURCE=.\PrepareHO_Res.cpp
# End Source File
# Begin Source File

SOURCE=.\PrepareSubsequentHO_Arg.cpp
# End Source File
# Begin Source File

SOURCE=.\PrivateExtension.cpp
# End Source File
# Begin Source File

SOURCE=.\PrivateExtensionList.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcedureCancellationReason.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcessGroupCallSignallingArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProtocolId.cpp
# End Source File
# Begin Source File

SOURCE=.\ProvideRoamingNumberArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProvideRoamingNumberRes.cpp
# End Source File
# Begin Source File

SOURCE=.\ProvideSIWFSNumberArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProvideSIWFSNumberRes.cpp
# End Source File
# Begin Source File

SOURCE=.\ProvideSubscriberInfoArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProvideSubscriberInfoRes.cpp
# End Source File
# Begin Source File

SOURCE=.\PurgeMS_Arg.cpp
# End Source File
# Begin Source File

SOURCE=.\PurgeMS_Res.cpp
# End Source File
# Begin Source File

SOURCE=.\PW_RegistrationFailureCause.cpp
# End Source File
# Begin Source File

SOURCE=.\QoS_Subscribed.cpp
# End Source File
# Begin Source File

SOURCE=.\RAND.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadyForSM_Arg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadyForSM_Res.cpp
# End Source File
# Begin Source File

SOURCE=.\Reason.cpp
# End Source File
# Begin Source File

SOURCE=.\RegionalSubscriptionResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\RegisterCC_EntryArg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegisterCC_EntryRes.cpp
# End Source File
# Begin Source File

SOURCE=.\RegisterSS_Arg.cpp
# End Source File
# Begin Source File

SOURCE=.\RemoteUserFreeArg.cpp
# End Source File
# Begin Source File

SOURCE=.\RemoteUserFreeRes.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportingState.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportSM_DeliveryStatusArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportSM_DeliveryStatusRes.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestedInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ResetArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourceLimitationParam.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourceUnavailableReason.cpp
# End Source File
# Begin Source File

SOURCE=.\RestoreDataArg.cpp
# End Source File
# Begin Source File

SOURCE=.\RestoreDataRes.cpp
# End Source File
# Begin Source File

SOURCE=.\ResumeCallHandlingArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ResumeCallHandlingRes.cpp
# End Source File
# Begin Source File

SOURCE=.\RoamingNotAllowedCause.cpp
# End Source File
# Begin Source File

SOURCE=.\RoamingNotAllowedParam.cpp
# End Source File
# Begin Source File

SOURCE=.\RoutingInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\RoutingInfoForSM_Arg.cpp
# End Source File
# Begin Source File

SOURCE=.\RoutingInfoForSM_Res.cpp
# End Source File
# Begin Source File

SOURCE=.\RUF_Outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\SendAuthenticationInfoArg.cpp
# End Source File
# Begin Source File

SOURCE=.\SendAuthenticationInfoRes.cpp
# End Source File
# Begin Source File

SOURCE=.\SendGroupCallEndSignalArg.cpp
# End Source File
# Begin Source File

SOURCE=.\SendGroupCallEndSignalRes.cpp
# End Source File
# Begin Source File

SOURCE=.\SendIdentificationRes.cpp
# End Source File
# Begin Source File

SOURCE=.\SendRoutingInfoArg.cpp
# End Source File
# Begin Source File

SOURCE=.\SendRoutingInfoForGprsArg.cpp
# End Source File
# Begin Source File

SOURCE=.\SendRoutingInfoForGprsRes.cpp
# End Source File
# Begin Source File

SOURCE=.\SendRoutingInfoRes.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceIndicator.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceKey.cpp
# End Source File
# Begin Source File

SOURCE=.\SetReportingStateArg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetReportingStateRes.cpp
# End Source File
# Begin Source File

SOURCE=.\ShortTermDenialParam.cpp
# End Source File
# Begin Source File

SOURCE=.\SignalInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\SIWFSSignallingModifyArg.cpp
# End Source File
# Begin Source File

SOURCE=.\SIWFSSignallingModifyRes.cpp
# End Source File
# Begin Source File

SOURCE=.\SM_DeliveryFailureCause.cpp
# End Source File
# Begin Source File

SOURCE=.\SM_DeliveryOutcome.cpp
# End Source File
# Begin Source File

SOURCE=.\SM_EnumeratedDeliveryFailureCause.cpp
# End Source File
# Begin Source File

SOURCE=.\SM_RP_DA.cpp
# End Source File
# Begin Source File

SOURCE=.\SM_RP_MTI.cpp
# End Source File
# Begin Source File

SOURCE=.\SM_RP_OA.cpp
# End Source File
# Begin Source File

SOURCE=.\SM_RP_SMEA.cpp
# End Source File
# Begin Source File

SOURCE=.\SRES.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_CamelData.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_Code.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_CSI.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_Data.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_EventList.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_EventSpecification.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_ForBS_Code.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_IncompatibilityCause.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_Info.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_InfoList.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_InvocationNotificationArg.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_InvocationNotificationRes.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_List.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_Status.cpp
# End Source File
# Begin Source File

SOURCE=.\SS_SubscriptionOption.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusReportArg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusReportRes.cpp
# End Source File
# Begin Source File

SOURCE=.\SubBusyForMT_SMS_Param.cpp
# End Source File
# Begin Source File

SOURCE=.\SubscriberData.cpp
# End Source File
# Begin Source File

SOURCE=.\SubscriberId.cpp
# End Source File
# Begin Source File

SOURCE=.\SubscriberIdentity.cpp
# End Source File
# Begin Source File

SOURCE=.\SubscriberInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\SubscriberState.cpp
# End Source File
# Begin Source File

SOURCE=.\SubscriberStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\SupportedCamelPhases.cpp
# End Source File
# Begin Source File

SOURCE=.\SupportedCCBS_Phase.cpp
# End Source File
# Begin Source File

SOURCE=.\SuppressionOfAnnouncement.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemFailureParam.cpp
# End Source File
# Begin Source File

SOURCE=.\T_BcsmCamelTDPData.cpp
# End Source File
# Begin Source File

SOURCE=.\T_BcsmCamelTDPDataList.cpp
# End Source File
# Begin Source File

SOURCE=.\T_BcsmTriggerDetectionPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\T_CSI.cpp
# End Source File
# Begin Source File

SOURCE=.\TBCD_STRING.cpp
# End Source File
# Begin Source File

SOURCE=.\TeleserviceCode.cpp
# End Source File
# Begin Source File

SOURCE=.\TeleserviceList.cpp
# End Source File
# Begin Source File

SOURCE=.\TeleservNotProvParam.cpp
# End Source File
# Begin Source File

SOURCE=.\TMSI.cpp
# End Source File
# Begin Source File

SOURCE=.\TraceReference.cpp
# End Source File
# Begin Source File

SOURCE=.\TraceType.cpp
# End Source File
# Begin Source File

SOURCE=.\TracingBufferFullParam.cpp
# End Source File
# Begin Source File

SOURCE=.\UnexpectedDataParam.cpp
# End Source File
# Begin Source File

SOURCE=.\UnidentifiedSubParam.cpp
# End Source File
# Begin Source File

SOURCE=.\UnknownSubscriberDiagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\UnknownSubscriberParam.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateGprsLocationArg.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateGprsLocationRes.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateLocationArg.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateLocationRes.cpp
# End Source File
# Begin Source File

SOURCE=.\USSD_Arg.cpp
# End Source File
# Begin Source File

SOURCE=.\USSD_DataCodingScheme.cpp
# End Source File
# Begin Source File

SOURCE=.\USSD_Res.cpp
# End Source File
# Begin Source File

SOURCE=.\USSD_String.cpp
# End Source File
# Begin Source File

SOURCE=.\VBSDataList.cpp
# End Source File
# Begin Source File

SOURCE=.\VGCSDataList.cpp
# End Source File
# Begin Source File

SOURCE=.\VLR_Capability.cpp
# End Source File
# Begin Source File

SOURCE=.\VlrCamelSubscriptionInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\VoiceBroadcastData.cpp
# End Source File
# Begin Source File

SOURCE=.\VoiceGroupCallData.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneCode.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneCodeList.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\include\itu\AbsentSubscriberDiagnosticSM.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AbsentSubscriberParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AbsentSubscriberReason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AbsentSubscriberSM_Param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ActivateTraceModeArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ActivateTraceModeRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Additional_Number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AddressString.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AgeOfLocationInformation.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AlertingPattern.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AlertReason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AlertServiceCentreArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AnyTimeInterrogationArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AnyTimeInterrogationRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\APN.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ASCI_CallReference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ATI_NotAllowedParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AuthenticationSet.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AuthenticationSetList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\BasicServiceCode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\BasicServiceCriteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\BasicServiceGroupList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\BasicServiceList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\BearerServiceCode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\BearerServiceList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\BearerServNotProvParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\BusySubscriberParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallBarredParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallBarringCause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallBarringFeature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallBarringFeatureList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallBarringInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallDirection.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallOutcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallReferenceNumber.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallReportData.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallTypeCriteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CamelCapabilityHandling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CamelInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CamelRoutingInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CancellationType.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CancelLocationArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CancelLocationRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CCBS_Data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CCBS_Feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CCBS_FeatureList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CCBS_Index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CCBS_Indicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CCBS_SubscriberStatus.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CellIdFixedLength.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CellIdOrLAI.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CipheringAlgorithm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CliRestrictionOption.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CODEC_Info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ContextId.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ContextIdList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CUG_CheckInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CUG_Feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CUG_FeatureList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CUG_Index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CUG_Info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CUG_Interlock.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CUG_RejectCause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CUG_RejectParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CUG_Subscription.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CUG_SubscriptionList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DataMissingParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DeactivateTraceModeArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DeactivateTraceModeRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DefaultCallHandling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DeleteSubscriberDataArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DeleteSubscriberDataRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DestinationNumberCriteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DestinationNumberLengthList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DestinationNumberList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\EMLPP_Info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\EMLPP_Priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\EquipmentStatus.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\EraseCC_EntryArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\EraseCC_EntryRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\EventReportData.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_BasicServiceCode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_BasicServiceGroupList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_BearerServiceCode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_CallBarFeatureList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_CallBarInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_CallBarringFeature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_ForwFeature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_ForwFeatureList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_ForwInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_ForwOptions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_NoRepCondTime.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_SS_Data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_SS_Info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_SS_InfoList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_SS_Status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Ext_TeleserviceCode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ExtendedRoutingInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ExtensibleCallBarredParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ExtensibleSystemFailureParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ExtensionContainer.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ExtensionSet.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ExternalSignalInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\FacilityNotSupParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\FailureReportArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\FailureReportRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ForwardGroupCallSignallingArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ForwardingData.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ForwardingFailedParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ForwardingFeature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ForwardingFeatureList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ForwardingInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ForwardingOptions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ForwardingReason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ForwardingViolationParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GenericServiceInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GeographicalInformation.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GlobalCellId.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GmscCamelSubscriptionInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GPRSDataList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GPRSSubscriptionData.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GPRSSubscriptionDataWithdraw.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GroupId.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GroupKeyNumber.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GSMMAP.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\gsmmapcodetest.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GSMMAPP2P.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GSMSMS.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GSN_Address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GuidanceInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\HLR_Id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\HLR_List.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\IllegalEquipmentParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\IllegalSubscriberParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\IMEI.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\IMSI.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\IMSI_WithLMSI.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\IncompatibleTerminalParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\InformServiceCentreArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\InsertSubscriberDataArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\InsertSubscriberDataRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\InterCUG_Restrictions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\InterrogateSS_Res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\InterrogationType.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\IntraCUG_Options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ISDN_AddressString.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ISDN_SubaddressString.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Kc.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\LAIFixedLength.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\LMSI.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\LocationInformation.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\LocationInfoWithLMSI.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\LocationNumber.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\LongTermDenialParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MAP_AcceptInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MAP_CloseInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_cpp.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MAP_DialoguePDU.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MAP_OpenInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MAP_ProviderAbortInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MAP_ProviderAbortReason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MAP_RefuseInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MAP_UserAbortChoice.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MAP_UserAbortInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MAP_UserInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MAP_UserInfoHelper.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_user_info_helper.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MatchType.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MessageWaitListFullParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MO_ForwardSM_Arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MO_ForwardSM_Res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MonitoringMode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MT_ForwardSM_Arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MT_ForwardSM_Res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MW_Status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NAEA_CIC.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NAEA_PreferredCI.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NetworkAccessMode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NetworkResource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NoGroupCallNbParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NoReplyConditionTime.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NoRoamingNbParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NoSubscriberReplyParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NoteMsPresentForGprsArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NoteMsPresentForGprsRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NotReachableReason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NumberChangedParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NumberOfForwarding.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\O_BcsmCamelTDP_Criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\O_BcsmCamelTDPData.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\O_BcsmCamelTDPDataList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\O_BcsmTriggerDetectionPoint.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\O_CSI.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ODB_Data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ODB_GeneralData.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ODB_HPLMN_Data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\OR_NotAllowedParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\OR_Phase.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\OverrideCategory.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Password.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PCS_Extensions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PDP_Address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PDP_Context.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PDP_Type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PrepareGroupCallArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PrepareGroupCallRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PrepareHO_Arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PrepareHO_Res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PrepareSubsequentHO_Arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PrivateExtension.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PrivateExtensionList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ProcedureCancellationReason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ProcessGroupCallSignallingArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ProtocolId.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ProvideRoamingNumberArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ProvideRoamingNumberRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ProvideSIWFSNumberArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ProvideSIWFSNumberRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ProvideSubscriberInfoArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ProvideSubscriberInfoRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PurgeMS_Arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PurgeMS_Res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PW_RegistrationFailureCause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\QoS_Subscribed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RAND.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ReadyForSM_Arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ReadyForSM_Res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RegionalSubscriptionResponse.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RegisterCC_EntryArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RegisterCC_EntryRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RegisterSS_Arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RemoteUserFreeArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RemoteUserFreeRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ReportingState.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ReportSM_DeliveryStatusArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ReportSM_DeliveryStatusRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RequestedInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ResetArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ResourceLimitationParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ResourceUnavailableReason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RestoreDataArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RestoreDataRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ResumeCallHandlingArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ResumeCallHandlingRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RoamingNotAllowedCause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RoamingNotAllowedParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RoutingInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RoutingInfoForSM_Arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RoutingInfoForSM_Res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RUF_Outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SendAuthenticationInfoArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SendAuthenticationInfoRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SendGroupCallEndSignalArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SendGroupCallEndSignalRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SendIdentificationRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SendRoutingInfoArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SendRoutingInfoForGprsArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SendRoutingInfoForGprsRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SendRoutingInfoRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ServiceIndicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ServiceKey.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SetReportingStateArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SetReportingStateRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ShortTermDenialParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SignalInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SIWFSSignallingModifyArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SIWFSSignallingModifyRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SM_DeliveryFailureCause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SM_DeliveryOutcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SM_EnumeratedDeliveryFailureCause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SM_RP_DA.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SM_RP_MTI.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SM_RP_OA.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SM_RP_SMEA.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SRES.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_CamelData.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_Code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_CSI.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_Data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_EventList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_EventSpecification.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_ForBS_Code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_IncompatibilityCause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_Info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_InfoList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_InvocationNotificationArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_InvocationNotificationRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_List.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_Status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SS_SubscriptionOption.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\StatusReportArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\StatusReportRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SubBusyForMT_SMS_Param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SubscriberData.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SubscriberId.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SubscriberIdentity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SubscriberInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SubscriberState.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SubscriberStatus.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SupportedCamelPhases.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SupportedCCBS_Phase.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SuppressionOfAnnouncement.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SystemFailureParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\T_BcsmCamelTDPData.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\T_BcsmCamelTDPDataList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\T_BcsmTriggerDetectionPoint.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\T_CSI.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TBCD_STRING.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TeleserviceCode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TeleserviceList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TeleservNotProvParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TMSI.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TraceReference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TraceType.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TracingBufferFullParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\UnexpectedDataParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\UnidentifiedSubParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\UnknownSubscriberDiagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\UnknownSubscriberParam.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\UpdateGprsLocationArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\UpdateGprsLocationRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\UpdateLocationArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\UpdateLocationRes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\USSD_Arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\USSD_DataCodingScheme.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\USSD_Res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\USSD_String.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\VBSDataList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\VGCSDataList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\VLR_Capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\VlrCamelSubscriptionInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\VoiceBroadcastData.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\VoiceGroupCallData.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ZoneCode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ZoneCodeList.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\GSMMAPP2P_LRF.asn

!IF  "$(CFG)" == "CppGSMMAPlib - Win32 P2P Debug"

# PROP Intermediate_Dir "CppGSMMAPP2PD"
# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\GSMMAPP2P_LRF.asn

".\UpdateLocationArg.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -cpp -explicitChoice -cppNamespace its -cppFileNamesNoPrefix -cppFileNamesMixedCase -f -u $(ITS_ROOT)\tools\bin\asncc_useful.asn .\GSMMAPP2P_LRF.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "CppGSMMAPlib - Win32 P2P Release"

# PROP Intermediate_Dir "CppGSMMAPP2P"

!ELSEIF  "$(CFG)" == "CppGSMMAPlib - Win32 P2 Debug"

# PROP Intermediate_Dir "CppGSMMAPP2D"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "CppGSMMAPlib - Win32 P2 Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
