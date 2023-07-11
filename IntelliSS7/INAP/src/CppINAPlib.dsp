# Microsoft Developer Studio Project File - Name="CppINAPlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CppINAPlib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CppINAPlib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CppINAPlib.mak" CFG="CppINAPlib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CppINAPlib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "CppINAPlib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe

!IF  "$(CFG)" == "CppINAPlib - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include/itu" /I "../../common/include" /I "../../common/include/asn-cpp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "CCITT" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\INAP++.lib"

!ELSEIF  "$(CFG)" == "CppINAPlib - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /I "../include/itu" /I "../../common/include" /I "../../common/include/asn-cpp" /I "$(ITS_ROOT)\INAP" /I "$(ITS_ROOT)\INAP\include\itu" /I "$(ITS_ROOT)\common\include\asn-cpp" /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\tools\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "CCITT" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\INAP++D.lib"

!ENDIF 

# Begin Target

# Name "CppINAPlib - Win32 Release"
# Name "CppINAPlib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\AccessCode.cpp
# End Source File
# Begin Source File

SOURCE=.\AChBillingChargingCharacteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\ActivateServiceFilteringArg.cpp
# End Source File
# Begin Source File

SOURCE=.\AdditionalCallingPartyNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\AlertingPattern.cpp
# End Source File
# Begin Source File

SOURCE=.\AnalysedInformationArg.cpp
# End Source File
# Begin Source File

SOURCE=.\AnalyseInformationArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ApplicationTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\ApplyChargingArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ApplyChargingReportArg.cpp
# End Source File
# Begin Source File

SOURCE=.\AssistingSSPIPRoutingAddress.cpp
# End Source File
# Begin Source File

SOURCE=.\AssistRequestInstructionsArg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCSMEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\BearerCapability.cpp
# End Source File
# Begin Source File

SOURCE=.\CalledPartyBusinessGroupID.cpp
# End Source File
# Begin Source File

SOURCE=.\CalledPartyNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\CalledPartySubaddress.cpp
# End Source File
# Begin Source File

SOURCE=.\CallGapArg.cpp
# End Source File
# Begin Source File

SOURCE=.\CallInformationReportArg.cpp
# End Source File
# Begin Source File

SOURCE=.\CallInformationRequestArg.cpp
# End Source File
# Begin Source File

SOURCE=.\CallingPartyBusinessGroupID.cpp
# End Source File
# Begin Source File

SOURCE=.\CallingPartyNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\CallingPartysCategory.cpp
# End Source File
# Begin Source File

SOURCE=.\CallingPartySubaddress.cpp
# End Source File
# Begin Source File

SOURCE=.\CallResult.cpp
# End Source File
# Begin Source File

SOURCE=.\CancelArg.cpp
# End Source File
# Begin Source File

SOURCE=.\CancelStatusReportRequestArg.cpp
# End Source File
# Begin Source File

SOURCE=.\Carrier.cpp
# End Source File
# Begin Source File

SOURCE=.\Cause.cpp
# End Source File
# Begin Source File

SOURCE=.\CGEncountered.cpp
# End Source File
# Begin Source File

SOURCE=.\ChargeNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\ChargingEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\CollectedDigits.cpp
# End Source File
# Begin Source File

SOURCE=.\CollectedInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CollectedInformationArg.cpp
# End Source File
# Begin Source File

SOURCE=.\CollectInformationArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectToResourceArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlType.cpp
# End Source File
# Begin Source File

SOURCE=.\CorrelationID.cpp
# End Source File
# Begin Source File

SOURCE=.\CounterAndValue.cpp
# End Source File
# Begin Source File

SOURCE=.\CounterID.cpp
# End Source File
# Begin Source File

SOURCE=.\CountersValue.cpp
# End Source File
# Begin Source File

SOURCE=.\CutAndPaste.cpp
# End Source File
# Begin Source File

SOURCE=.\DateAndTime.cpp
# End Source File
# Begin Source File

SOURCE=.\DestinationRoutingAddress.cpp
# End Source File
# Begin Source File

SOURCE=.\Digits.cpp
# End Source File
# Begin Source File

SOURCE=.\DisplayInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\DpSpecificCommonParameters.cpp
# End Source File
# Begin Source File

SOURCE=.\DpSpecificCriteria.cpp
# End Source File
# Begin Source File

SOURCE=.\Duration.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorTreatment.cpp
# End Source File
# Begin Source File

SOURCE=.\EstablishTemporaryConnectionArg.cpp
# End Source File
# Begin Source File

SOURCE=.\EventNotificationChargingArg.cpp
# End Source File
# Begin Source File

SOURCE=.\EventReportBCSMArg.cpp
# End Source File
# Begin Source File

SOURCE=.\EventSpecificInformationBCSM.cpp
# End Source File
# Begin Source File

SOURCE=.\EventSpecificInformationCharging.cpp
# End Source File
# Begin Source File

SOURCE=.\EventTypeBCSM.cpp
# End Source File
# Begin Source File

SOURCE=.\EventTypeCharging.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtensionField.cpp
# End Source File
# Begin Source File

SOURCE=.\FacilityGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\FacilityGroupMember.cpp
# End Source File
# Begin Source File

SOURCE=.\FCIBillingChargingCharacteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\FeatureCode.cpp
# End Source File
# Begin Source File

SOURCE=.\FeatureRequestIndicator.cpp
# End Source File
# Begin Source File

SOURCE=.\FilteredCallTreatment.cpp
# End Source File
# Begin Source File

SOURCE=.\FilteringCharacteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\FilteringCriteria.cpp
# End Source File
# Begin Source File

SOURCE=.\FilteringTimeOut.cpp
# End Source File
# Begin Source File

SOURCE=.\ForwardCallIndicators.cpp
# End Source File
# Begin Source File

SOURCE=.\ForwardingCondition.cpp
# End Source File
# Begin Source File

SOURCE=.\FurnishChargingInformationArg.cpp
# End Source File
# Begin Source File

SOURCE=.\GapCriteria.cpp
# End Source File
# Begin Source File

SOURCE=.\GapIndicators.cpp
# End Source File
# Begin Source File

SOURCE=.\GapOnService.cpp
# End Source File
# Begin Source File

SOURCE=.\GapTreatment.cpp
# End Source File
# Begin Source File

SOURCE=.\HighLayerCompatibility.cpp
# End Source File
# Begin Source File

SOURCE=.\HoldCallInNetworkArg.cpp
# End Source File
# Begin Source File

SOURCE=.\HoldCause.cpp
# End Source File
# Begin Source File

SOURCE=.\InbandInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\InformationToSend.cpp
# End Source File
# Begin Source File

SOURCE=.\InitialDPArg.cpp
# End Source File
# Begin Source File

SOURCE=.\InitiateCallAttemptArg.cpp
# End Source File
# Begin Source File

SOURCE=.\Integer4.cpp
# End Source File
# Begin Source File

SOURCE=.\Interval.cpp
# End Source File
# Begin Source File

SOURCE=.\InvokeID.cpp
# End Source File
# Begin Source File

SOURCE=.\IPAvailable.cpp
# End Source File
# Begin Source File

SOURCE=.\IPRoutingAddress.cpp
# End Source File
# Begin Source File

SOURCE=.\IPSSPCapabilities.cpp
# End Source File
# Begin Source File

SOURCE=.\ISDNAccessRelatedInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\LegID.cpp
# End Source File
# Begin Source File

SOURCE=.\LegType.cpp
# End Source File
# Begin Source File

SOURCE=.\LocationNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\MaximumNumberOfCounters.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageID.cpp
# End Source File
# Begin Source File

SOURCE=.\MidCallArg.cpp
# End Source File
# Begin Source File

SOURCE=.\MiscCallInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MonitorMode.cpp
# End Source File
# Begin Source File

SOURCE=.\NumberingPlan.cpp
# End Source File
# Begin Source File

SOURCE=.\NumberOfDigits.cpp
# End Source File
# Begin Source File

SOURCE=.\OAnswerArg.cpp
# End Source File
# Begin Source File

SOURCE=.\OCalledPartyBusyArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ODisconnectArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ONoAnswerArg.cpp
# End Source File
# Begin Source File

SOURCE=.\OriginalCalledPartyID.cpp
# End Source File
# Begin Source File

SOURCE=.\OriginationAttemptAuthorizedArg.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayAnnouncementArg.cpp
# End Source File
# Begin Source File

SOURCE=.\PromptAndCollectUserInformationArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReceivedInformationArg.cpp
# End Source File
# Begin Source File

SOURCE=.\RedirectingPartyID.cpp
# End Source File
# Begin Source File

SOURCE=.\RedirectionInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\ReleaseCallArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportCondition.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestCurrentStatusReportArg.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestCurrentStatusReportResultArg.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestedInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestedInformationList.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestedInformationType.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestedInformationTypeList.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestedInformationValue.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestEveryStatusChangeReportArg.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestFirstStatusMatchReportArg.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestNotificationChargingEventArg.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestReportBCSMEventArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ResetTimerArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourceID.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourceStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\ResponseCondition.cpp
# End Source File
# Begin Source File

SOURCE=.\RouteList.cpp
# End Source File
# Begin Source File

SOURCE=.\RouteSelectFailureArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScfID.cpp
# End Source File
# Begin Source File

SOURCE=.\SCIBillingChargingCharacteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectFacilityArg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectRouteArg.cpp
# End Source File
# Begin Source File

SOURCE=.\SendChargingInformationArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceAddressInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceFilteringResponseArg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceInteractionIndicators.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceKey.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceProfileIdentifier.cpp
# End Source File
# Begin Source File

SOURCE=.\ServingAreaID.cpp
# End Source File
# Begin Source File

SOURCE=.\SFBillingChargingCharacteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecializedResourceReportArg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusReportArg.cpp
# End Source File
# Begin Source File

SOURCE=.\TAnswerArg.cpp
# End Source File
# Begin Source File

SOURCE=.\TBusyArg.cpp
# End Source File
# Begin Source File

SOURCE=.\TDisconnectArg.cpp
# End Source File
# Begin Source File

SOURCE=.\TermAttemptAuthorizedArg.cpp
# End Source File
# Begin Source File

SOURCE=.\TerminalType.cpp
# End Source File
# Begin Source File

SOURCE=.\TimerID.cpp
# End Source File
# Begin Source File

SOURCE=.\TimerValue.cpp
# End Source File
# Begin Source File

SOURCE=.\TNoAnswerArg.cpp
# End Source File
# Begin Source File

SOURCE=.\Tone.cpp
# End Source File
# Begin Source File

SOURCE=.\TravellingClassMark.cpp
# End Source File
# Begin Source File

SOURCE=.\TriggerType.cpp
# End Source File
# Begin Source File

SOURCE=.\UnavailableNetworkResource.cpp
# End Source File
# Begin Source File

SOURCE=.\VariablePart.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\include\itu\AccessCode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AChBillingChargingCharacteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ActivateServiceFilteringArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AdditionalCallingPartyNumber.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AlertingPattern.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AnalysedInformationArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AnalyseInformationArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ApplicationTimer.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ApplyChargingArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ApplyChargingReportArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AssistingSSPIPRoutingAddress.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\AssistRequestInstructionsArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\BCSMEvent.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\BearerCapability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CalledPartyBusinessGroupID.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CalledPartyNumber.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CalledPartySubaddress.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallGapArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallInformationReportArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallInformationRequestArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallingPartyBusinessGroupID.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallingPartyNumber.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallingPartysCategory.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallingPartySubaddress.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CallResult.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CancelArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CancelStatusReportRequestArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Carrier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CGEncountered.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ChargeNumber.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ChargingEvent.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CollectedDigits.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CollectedInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CollectedInformationArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CollectInformationArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ConnectArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ConnectToResourceArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ControlType.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CorrelationID.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CounterAndValue.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CounterID.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CountersValue.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\CutAndPaste.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DateAndTime.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DestinationRoutingAddress.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Digits.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DisplayInformation.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DpSpecificCommonParameters.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\DpSpecificCriteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Duration.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ErrorTreatment.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\EstablishTemporaryConnectionArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\EventNotificationChargingArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\EventReportBCSMArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\EventSpecificInformationBCSM.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\EventSpecificInformationCharging.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\EventTypeBCSM.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\EventTypeCharging.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ExtensionField.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\FacilityGroup.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\FacilityGroupMember.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\FCIBillingChargingCharacteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\FeatureCode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\FeatureRequestIndicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\FilteredCallTreatment.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\FilteringCharacteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\FilteringCriteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\FilteringTimeOut.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ForwardCallIndicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ForwardingCondition.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\FurnishChargingInformationArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GapCriteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GapIndicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GapOnService.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\GapTreatment.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\HighLayerCompatibility.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\HoldCallInNetworkArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\HoldCause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\InbandInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\InformationToSend.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\InitialDPArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\InitiateCallAttemptArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Integer4.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Interval.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\InvokeID.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\IPAvailable.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\IPRoutingAddress.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\IPSSPCapabilities.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ISDNAccessRelatedInformation.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\LegID.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\LegType.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\LocationNumber.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MaximumNumberOfCounters.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MessageID.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MidCallArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MiscCallInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\MonitorMode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NumberingPlan.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\NumberOfDigits.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\OAnswerArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\OCalledPartyBusyArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ODisconnectArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ONoAnswerArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\OriginalCalledPartyID.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\OriginationAttemptAuthorizedArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PlayAnnouncementArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\PromptAndCollectUserInformationArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ReceivedInformationArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RedirectingPartyID.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RedirectionInformation.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ReleaseCallArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ReportCondition.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RequestCurrentStatusReportArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RequestCurrentStatusReportResultArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RequestedInformation.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RequestedInformationList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RequestedInformationType.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RequestedInformationTypeList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RequestedInformationValue.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RequestEveryStatusChangeReportArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RequestFirstStatusMatchReportArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RequestNotificationChargingEventArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RequestReportBCSMEventArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ResetTimerArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ResourceID.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ResourceStatus.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ResponseCondition.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RouteList.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\RouteSelectFailureArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ScfID.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SCIBillingChargingCharacteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SelectFacilityArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SelectRouteArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SendChargingInformationArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ServiceAddressInformation.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ServiceFilteringResponseArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ServiceInteractionIndicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ServiceKey.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ServiceProfileIdentifier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\ServingAreaID.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SFBillingChargingCharacteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\SpecializedResourceReportArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\StatusReportArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TAnswerArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TBusyArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TDisconnectArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TermAttemptAuthorizedArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TerminalType.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TimerID.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TimerValue.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TNoAnswerArg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\Tone.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TravellingClassMark.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\TriggerType.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\UnavailableNetworkResource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\VariablePart.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\INAP_LRF.asn

!IF  "$(CFG)" == "CppINAPlib - Win32 Release"

# Begin Custom Build
InputPath=.\INAP_LRF.asn

"ActivateServiceFilteringArg.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc INAP_LRF.asn -cpp -explicitChoice -u\
  $(ITS_ROOT)\tools\bin\asncc_useful.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "CppINAPlib - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\INAP_LRF.asn

".\ActivateServiceFilteringArg.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc INAP_LRF.asn -cpp -explicitChoice -u\
  $(ITS_ROOT)\tools\bin\asncc_useful.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
