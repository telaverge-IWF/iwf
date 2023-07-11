/****************************************************************************
 *                                                                          *
 *     Copyright 2008 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * ID: $Id: subagent.h,v 1.1.2.1 2014/07/03 06:00:46 millayaraja Exp $
 *
 * LOG: $Log: subagent.h,v $
 * LOG: Revision 1.1.2.1  2014/07/03 06:00:46  millayaraja
 * LOG: integrated SNMP/Subagent with IWF
 * LOG:
 * LOG: Revision 1.1.2.1.2.2.6.1  2014/03/16 14:45:43  cprem
 * LOG: Code changes for Congestion Management Framework.
 * LOG:
 * LOG: Revision 1.1.2.1.2.2  2013/03/08 08:41:17  vsarath
 * LOG: Fix for issues reported by coverity
 * LOG:
 * LOG: Revision 1.1.2.1.2.1  2013/02/15 15:04:19  rsanjay
 * LOG: AlarmId changes
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/20 16:13:27  cprem
 * LOG: SubAgent process for DRE. This is for raising alarms.
 * LOG:
 * LOG: Revision 1.14  2010/08/19 11:21:26  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 1.13  2009/09/07 04:54:01  rajeshak
 * LOG: Alarm Added for HMI Heartbeat.
 * LOG:
 * LOG: Revision 1.12  2009/08/31 05:52:51  rajeshak
 * LOG: New Alarm for Connection close after DPA sent/receive (AlarmID:15010).
 * LOG:
 * LOG: Revision 1.11  2009/08/28 12:15:38  rajeshak
 * LOG: Fix for Issue-2341 (IDS is not raising Alarm for DPA/DWA for failed
 * LOG: result codes)
 * LOG: Handling of new Alarm codes
 * LOG:
 * LOG: Revision 1.10  2009/04/17 15:33:24  rajeshak
 * LOG: Missing bracket.
 * LOG:
 * LOG: Revision 1.9  2009/04/17 08:52:19  rajeshak
 * LOG: Raising an Alarm if Destination Host is not there in Peer Table.
 * LOG:
 * LOG: Revision 1.8  2009/03/19 12:39:01  sureshj
 * LOG: Version Mismatch Alarm definition added
 * LOG:
 * LOG: Revision 1.7  2009/03/19 06:16:05  chandrashekharbs
 * LOG: Alarm ids 15005 and 15006 are updated in macro definations
 * LOG:
 * LOG: Revision 1.6  2009/03/17 04:29:55  chandrashekharbs
 * LOG: Alarm raised by HMI for hungthreads is handled
 * LOG:
 * LOG: Revision 1.5  2008/12/31 11:33:40  chandrashekharbs
 * LOG: Typo in alarm definitions corrected
 * LOG:
 * LOG: Revision 1.4  2008/12/22 12:41:40  chandrabs
 * LOG: Fault name changed to DynamicConfiguration_DeletedOrDisabledPeer from DynamicConfiguration_FailedToDeleteOrDisablePeer
 * LOG:
 * LOG: Revision 1.3  2008/12/12 06:50:54  chandrabs
 * LOG: Severity and AlarmId Mismatch is set right
 * LOG:
 * LOG: Revision 1.2  2008/12/11 13:25:42  chandrabs
 * LOG: Updated AlarmId as per changes in diameter stack  width 50
 * LOG:
 * LOG: Revision 1.1  2008/12/10 07:20:43  chandrabs
 * LOG: Initial draft for Alarm Support
 * LOG:
****************************************************************************/
#ident "$Id: subagent.h,v 1.1.2.1 2014/07/03 06:00:46 millayaraja Exp $"
#ifndef _SUBAGENT_H_
#define _SUBAGENT_H_
#include <stdint.h>
#include <its.h>
#include <its_trace.h>
#define MAX_SEQUENCE_NUMBER 5000
#define NOTIFPORT  7777
#define OAM_ALARM_SRC 0x00001
#define ALARM_ID_LEN 11

typedef struct SAClientInfo
{
    ITS_CHAR ipAddr[20];
    ITS_INT port;
}SAClientInfo;

typedef struct StackAlarmInfo
{
    ITS_INT stackAlarmId;
    ITS_CHAR alarmIdString[ALARM_ID_LEN];

}StackAlarmInfo;


enum severity
{
    cleared = 1,
    warning,
    minor,
    major,
    critical,
    info
};

#define ALARM_SEVERITY(x) \
    ((x==15000)                         ? major     : \
    ((x==15001)                         ? major     : \
    ((x==15002)                         ? info      : \
    ((x==15003)                         ? info      : \
    ((x==15004)                         ? info      : \
    ((x==15005)                         ? info      : \
    ((x==15006)                         ? info      : \
    ((x==15007)                         ? info      : \
    ((x==15008)                         ? info      : \
    ((x==15010)                         ? info      : \
    ((x==15011)                         ? info      : \
    ((x==15050)                         ? major     : \
    ((x==15051)                         ? major     : \
    ((x==15052)                         ? info      : \
    ((x==15100)                         ? minor     : \
    ((x==15101)                         ? minor     : \
    ((x==15102)                         ? minor     : \
    ((x==15103)                         ? minor     : \
    ((x==15104)                         ? major     : \
    ((x==15150)                         ? critical  : \
    ((x==15151)                         ? critical  : \
    ((x==15200)                         ? critical  : \
    ((x==15201)                         ? critical  : \
    ((x==15250)                         ? major     : \
    ((x==15251)                         ? major     : \
    ((x==15252)                         ? major     : \
    ((x==15253)                         ? major     : \
    ((x==15300)                         ? critical  : \
    ((x==15300)                         ? major     : \
    ((x==15301)                         ? major     : \
    ((x==15302)                         ? critical  : \
    ((x==15303)                         ? critical  : \
    ((x==15304)                         ? major     : \
    ((x==15306)                         ? info      : \
    ((x==15307)                         ? cleared      : \
    ((x==15308)                         ? major     : \
    ((x==15309)                         ? cleared     : \
    ((x==15310)                         ? critical  : \
    ((x==15311)                         ? cleared  : \
    ((x==15312)                         ? info      : \
    ((x==15313)                         ? cleared      : \
    ((x==15314)                         ? major     : \
    ((x==15315)                         ? cleared     : \
    ((x==15316)                         ? critical  : \
    ((x==15317)                         ? cleared  : \
    ((x==15318)                         ? info      : \
    ((x==15319)                         ? cleared      : \
    ((x==15320)                         ? major     : \
    ((x==15321)                         ? cleared     : \
    ((x==15322)                         ? info      : \
    ((x==15323)                         ? cleared      : \
    ((x==15324)                         ? major     : \
    ((x==15325)                         ? cleared     : \
    ((x==15326)                         ? critical  : \
    ((x==15327)                         ? cleared  : \
    ((x==15328)                         ? critical  : \
    ((x==15350)                         ? critical  : \
    ((x==15400)                         ? critical  : \
    ((x==15450)                         ? info      : \
    info)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

enum probablecause
{
    sctportcpconnectionfailureassocloss,
    sctportcpconnectionclosedassocclosed,
    tcpconnectionfailandfailovertopeer,
    sctportcpconnectionestablished,
    tcpconnectionestablishandfailbacktoprimary,
    cerorceaexchangefailure,
    clientRegFailure,
    tcpcommunicationfailurewithbackendapplication,
    tcpcommunicationestablishedwithbackendapplication,
    recievemsgfailurefrompeer,
    peerstateclosed,
    failedtotransmitmsgtopeer,
    receivemsgfailfromIDC,
    failedtotransmitmsgtoIDC,
    diskfailure,
    cpuutilisationmore,
    queuefull,
    unknowncause,
    hungthread,
    resultcodenotsuccess,
    mismatchoriginhostororiginrealmwithpeertables,
    versionmismatch, 
    messageForwardingFailure,
    hmiHeartbeat,
    peerTPSExceededLevel1,
    peerTPSLevel1Abated,
    peerTPSExceededLevel2,
    peerTPSLevel2Abated,
    peerTPSExceededLevel3,
    peerTPSLevel3Abated,
    overallTPSExceededLevel1,
    overallTPSLevel1Abated,
    overallTPSExceededLevel2,
    overallTPSLevel2Abated,
    overallTPSExceededLevel3,
    overallTPSLevel3Abated,
    sessionTableSizeExceededLevel1,
    sessionTableSizeLevel1Abated,
    sessionTableSizeExceededLevel2,
    sessionTableSizeLevel2Abated,
    routerQueueSizeExceededLevel1,
    routerQueueSizeLevel1Abated,
    routerQueueSizeExceededLevel2,
    routerQueueSizeLevel2Abated,
    routerQueueSizeExceededLevel3,
    routerQueueSizeLevel3Abated,
    peerDisconnectedDueToFlooding

};



#define ALARM_PROBABLECAUSE(x) \
    ((x==15000)         ? cerorceaexchangefailure                           : \
    ((x==15001)         ? sctportcpconnectionfailureassocloss               : \
    ((x==15002)         ? sctportcpconnectionestablished                    : \
    ((x==15003)         ? tcpconnectionfailandfailovertopeer                : \
    ((x==15004)         ? tcpconnectionestablishandfailbacktoprimary        : \
    ((x==15005)         ? resultcodenotsuccess                              : \
    ((x==15006)         ? mismatchoriginhostororiginrealmwithpeertables     : \
    ((x==15007)         ? resultcodenotsuccess                              : \
    ((x==15008)         ? resultcodenotsuccess                              : \
    ((x==15010)         ? sctportcpconnectionclosedassocclosed              : \
    ((x==15011)         ? peerstateclosed              : \
    ((x==15050)         ? clientRegFailure                                  : \
    ((x==15051)         ? tcpcommunicationfailurewithbackendapplication     : \
    ((x==15052)         ? tcpcommunicationestablishedwithbackendapplication : \
    ((x==15100)         ? recievemsgfailurefrompeer                         : \
    ((x==15101)         ? failedtotransmitmsgtopeer                         : \
    ((x==15102)         ? receivemsgfailfromIDC                             : \
    ((x==15103)         ? failedtotransmitmsgtoIDC                          : \
    ((x==15104)         ? messageForwardingFailure                          : \
    ((x==15150)         ? unknowncause                                      : \
    ((x==15151)         ? unknowncause                                      : \
    ((x==15200)         ? unknowncause                                      : \
    ((x==15201)         ? unknowncause                                      : \
    ((x==15250)         ? unknowncause                                      : \
    ((x==15251)         ? unknowncause                                      : \
    ((x==15252)         ? unknowncause                                      : \
    ((x==15253)         ? unknowncause                                      : \
    ((x==15300)         ? diskfailure                                       : \
    ((x==15301)         ? diskfailure                                       : \
    ((x==15302)         ? cpuutilisationmore                                : \
    ((x==15303)         ? cpuutilisationmore                                : \
    ((x==15304)         ? queuefull                                         : \
    ((x==15305)         ? queuefull                                         : \
    ((x==15306)         ? peerTPSExceededLevel1                             : \
    ((x==15307)         ? peerTPSLevel1Abated                               : \
    ((x==15308)         ? peerTPSExceededLevel2                             :\
    ((x==15309)         ? peerTPSLevel2Abated   :\
    ((x==15310)         ? peerTPSExceededLevel3                             : \
    ((x==15311)         ? peerTPSLevel3Abated   : \
    ((x==15312)         ? overallTPSExceededLevel1                          : \
    ((x==15313)         ? overallTPSLevel1Abated    : \
    ((x==15314)         ? overallTPSExceededLevel2                          : \
    ((x==15315)         ? overallTPSLevel2Abated    : \
    ((x==15316)         ? overallTPSExceededLevel3                          : \
    ((x==15317)         ? overallTPSLevel3Abated    : \
    ((x==15318)         ? sessionTableSizeExceededLevel1                    : \
    ((x==15319)         ? sessionTableSizeLevel1Abated  : \
    ((x==15320)         ? sessionTableSizeExceededLevel2                    : \
    ((x==15321)         ? sessionTableSizeLevel2Abated  : \
    ((x==15322)         ? routerQueueSizeExceededLevel1                     : \
    ((x==15323)         ? routerQueueSizeLevel1Abated   : \
    ((x==15324)         ? routerQueueSizeExceededLevel2                     : \
    ((x==15325)         ? routerQueueSizeLevel2Abated   : \
    ((x==15326)         ? routerQueueSizeExceededLevel3                     : \
    ((x==15327)         ? routerQueueSizeLevel3Abated   : \
    ((x==15328)         ? peerDisconnectedDueToFlooding                     : \
    ((x==15350)         ? hungthread                                        : \
    ((x==15400)         ? versionmismatch                                   : \
    ((x==15450)         ? hmiHeartbeat                                      : \
    unknowncause)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

enum alarmtype
{
    communicationsAlarm = 1,
    qualityofServiceAlarm,
    processingErrorAlarm,
    hmiHeartbeatAlarm,
    unknown,
    congestionIndicationAlarm
};


#define ALARM_TYPE(x) \
    ((x==15000)                         ? communicationsAlarm   : \
    ((x==15001)                         ? communicationsAlarm   : \
    ((x==15002)                         ? communicationsAlarm   : \
    ((x==15003)                         ? communicationsAlarm   : \
    ((x==15004)                         ? communicationsAlarm   : \
    ((x==15005)                         ? processingErrorAlarm  : \
    ((x==15006)                         ? processingErrorAlarm  : \
    ((x==15007)                         ? processingErrorAlarm  : \
    ((x==15008)                         ? processingErrorAlarm  : \
    ((x==15010)                         ? communicationsAlarm   : \
    ((x==15011)                         ? communicationsAlarm   : \
    ((x==15050)                         ? communicationsAlarm   : \
    ((x==15051)                         ? communicationsAlarm   : \
    ((x==15052)                         ? communicationsAlarm   : \
    ((x==15100)                         ? processingErrorAlarm  : \
    ((x==15101)                         ? processingErrorAlarm  : \
    ((x==15102)                         ? processingErrorAlarm  : \
    ((x==15103)                         ? processingErrorAlarm  : \
    ((x==15104)                         ? processingErrorAlarm  : \
    ((x==15150)                         ? communicationsAlarm   : \
    ((x==15151)                         ? communicationsAlarm   : \
    ((x==15200)                         ? communicationsAlarm   : \
    ((x==15201)                         ? communicationsAlarm   : \
    ((x==15250)                         ? communicationsAlarm   : \
    ((x==15251)                         ? communicationsAlarm   : \
    ((x==15252)                         ? communicationsAlarm   : \
    ((x==15253)                         ? communicationsAlarm   : \
    ((x==15300)                         ? unknown               : \
    ((x==15301)                         ? unknown               : \
    ((x==15302)                         ? unknown               : \
    ((x==15303)                         ? unknown               : \
    ((x==15304)                         ? unknown               : \
    ((x==15305)                         ? unknown               : \
    ((x==15306)                         ? congestionIndicationAlarm: \
    ((x==15307)                         ? congestionIndicationAlarm: \
    ((x==15308)                         ? congestionIndicationAlarm: \
    ((x==15309)                         ? congestionIndicationAlarm: \
    ((x==15310)                         ? congestionIndicationAlarm: \
    ((x==15311)                         ? congestionIndicationAlarm: \
    ((x==15312)                         ? congestionIndicationAlarm: \
    ((x==15313)                         ? congestionIndicationAlarm: \
    ((x==15314)                         ? congestionIndicationAlarm: \
    ((x==15315)                         ? congestionIndicationAlarm: \
    ((x==15316)                         ? congestionIndicationAlarm: \
    ((x==15317)                         ? congestionIndicationAlarm: \
    ((x==15318)                         ? congestionIndicationAlarm: \
    ((x==15319)                         ? congestionIndicationAlarm: \
    ((x==15320)                         ? congestionIndicationAlarm: \
    ((x==15321)                         ? congestionIndicationAlarm: \
    ((x==15322)                         ? congestionIndicationAlarm: \
    ((x==15323)                         ? congestionIndicationAlarm: \
    ((x==15324)                         ? congestionIndicationAlarm: \
    ((x==15325)                         ? congestionIndicationAlarm: \
    ((x==15326)                         ? congestionIndicationAlarm: \
    ((x==15327)                         ? congestionIndicationAlarm: \
    ((x==15328)                         ? congestionIndicationAlarm: \
    ((x==15350)                         ? qualityofServiceAlarm : \
    ((x==15400)                         ? communicationsAlarm   : \
    ((x==15450)                         ? hmiHeartbeatAlarm     : \
    unknowncause)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

#define ALARM_FAULTNAME(x) \
    ((x==15000) ? "PeerConnectivity_CerOrCeaExchangeFailure"                   : \
    ((x==15001) ? "PeerConnectivity_SctpAssociationLossOrTcpConnectFailure"    : \
    ((x==15002) ? "PeerConnectivity_SctpAssociationOrTcpConnectEstablished"    : \
    ((x==15003) ? "PeerConnectivity_FailoverToAlternatePeer"                   : \
    ((x==15004) ? "PeerConnectivity_ConnectionEstablishAndFailbackToPrimary"   : \
    ((x==15005) ? "PeerConnectivity_TranFailDetectionWrongResultCode"          : \
    ((x==15006) ? "PeerConnectivity_TranFailDetectionMismatchOriginHostRealm"  : \
    ((x==15007) ? "PeerConnectivity_TranFailDetectionWrongResultCode"          : \
    ((x==15008) ? "PeerConnectivity_TranFailDetectionWrongResultCode"          : \
    ((x==15010) ? "PeerConnectivity_SctpAssociationClosedOrTcpDisconnect"      : \
    ((x==15011) ? "PeerStateClosed"      : \
    ((x==15050) ? "BackEndIdcConnectivity_ClientRegigistrationFailed"          : \
    ((x==15051) ? "BackEndIdcConnectivity_TcpCommunicationFailure"             : \
    ((x==15052) ? "BackEndIdcConnectivity_TcpCommunicationestablished"         : \
    ((x==15100) ? "MessageProcessing_RecieveMsgFailureFromPeer"                : \
    ((x==15101) ? "MessageProcessing_TransmitMsgToPeerFail"                    : \
    ((x==15102) ? "MessageProcessing_ReceiveMsgFailFromIDC"                    : \
    ((x==15103) ? "MessageProcessing_TransmitMsgToIDCFail"                     : \
    ((x==15104) ? "MessageProcessing_MsgForUnknownPeer"                        : \
    ((x==15150) ? "Redundancy_FailOver"                                        : \
    ((x==15151) ? "Redundancy_GcsCommunicationDown"                            : \
    ((x==15200) ? "Start_DiameterStackFailedToInitialise"                      : \
    ((x==15201) ? "ShutDown_DiamterStackTermination"                           : \
    ((x==15250) ? "DynamicConfiguration_FailedToAddPeer"                       : \
    ((x==15251) ? "DynamicConfiguration_DeletedOrDisabledPeer"                 : \
    ((x==15252) ? "DynamicConfiguration_FailedToAddDestination"                 : \
    ((x==15253) ? "DynamicConfiguration_FailedToAddRealm"                 : \
    ((x==15300) ? "Overload_DiskFailure"                                       : \
    ((x==15301) ? "Overload_DiskFailure"                                       : \
    ((x==15302) ? "Overload_CpuUtilisationMore"                                : \
    ((x==15303) ? "Overload_CpuUtilisationMore"                                : \
    ((x==15304) ? "Overload_QueueFull"                                         : \
    ((x==15305) ? "Overload_QueueFull"                                         : \
    ((x==15306) ? "PeerTPS_Exceeded_Level1"                                         : \
    ((x==15307) ? "PeerTPS_Abated_Level1"                                         : \
    ((x==15308) ? "PeerTPS_Exceeded_Level2"                                         : \
    ((x==15309) ? "PeerTPS_Abated_Level2"                                         : \
    ((x==15310) ? "PeerTPS_Exceeded_Level3"                                         : \
    ((x==15311) ? "PeerTPS_Abated_Level3"                                         : \
    ((x==15312) ? "OverallTPS_Exceeded_Level1"                                         : \
    ((x==15313) ? "OverallTPS_Abated_Level1"                                         : \
    ((x==15314) ? "OverallTPS_Exceeded_Level2"                                         : \
    ((x==15315) ? "OverallTPS_Abated_Level2"                                         : \
    ((x==15316) ? "OverallTPS_Exceeded_Level3"                                         : \
    ((x==15317) ? "OverallTPS_Abated_Level3"                                         : \
    ((x==15318) ? "SessionTable_Size_Exceeded_Level1"                                         : \
    ((x==15319) ? "SessionTable_Size_Level1_Abated"                                         : \
    ((x==15320) ? "SessionTable_Size_Exceeded_Level2"                                         : \
    ((x==15321) ? "SessionTable_Size_Level2_Abated"                                         : \
    ((x==15322) ? "RouterQueue_Size_Exceeded_Level1"                                         : \
    ((x==15323) ? "RouterQueue_Size_Level1_Abated"                                         : \
    ((x==15324) ? "RouterQueue_Size_Exceeded_Level2"                                         : \
    ((x==15325) ? "RouterQueue_Size_Level2_Abated"                                         : \
    ((x==15326) ? "RouterQueue_Size_Exceeded_Level3"                                         : \
    ((x==15327) ? "RouterQueue_Size_Level3_Abated"                                         : \
    ((x==15328) ? "Peer_Disconnected_DueToFlooding"                                         : \
    ((x==15350) ? "HungThread"                                                 : \
    ((x==15400) ? "General_VersionMismatch"                                    : \
    ((x==15450) ? "HmiHeartbeatMessage"                                        : \
    "unknowncause")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))


ITS_INT agent_meSSInitialize();

//function Prototypes
ITS_INT DIASA_Connect(SAClientInfo *ClientInfo);

void send_alarm(char * alarmId,char* alarmText);

void agent_terminate();
#endif 
