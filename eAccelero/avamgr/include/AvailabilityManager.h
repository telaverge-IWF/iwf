/********************************-*-H-*-*************************************
 *                                                                          *
 *     Copyright 2012 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *    This product and related documentation is protected by copyright and  *
 *    distributed under licenses restricting its use, copying, distribution *
 *    and decompilation.  No part of this product or related documentation  *
 *    may be reproduced in any form by any means without prior written      *
 *    authorization of IntelliNet Technologies and its licensors, if any.   *
 *                                                                          *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     *
 *    government is subject to restrictions as set forth in subparagraph    *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software      *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                       *
 *                                                                          *
 * Author: adey
 *
 * Created on June 14, 2012, 9:55 AM
 ****************************************************************************/
#ifndef AVAILABILITYMANAGER_H
#define	AVAILABILITYMANAGER_H

#include "HAMeSSComponent.h"
#include "ComponentDefines.h"
#include "InterfaceDefines.h"

#include "HA.h"
#include "CMAPIConfig.h"

#include "ConfigReader.h"

#include <string>
#include <set>
#include <queue>
#include <vector>

#include <json.h>

#include <net/if.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <bits/sockaddr.h>
#include <asm/types.h>
#include <linux/rtnetlink.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "AvailabilityManagerAlarms.h"
#include "AvaMgr.h"
#include "AvaMgrPeerStatusInterface_caller.h"
#include "ClusterManager.h"
#include "KPI.h"

#include "AvaMgrProcessStatusInterface_caller.h"
#include "AvaMgrComponentStatusInterface_caller.h"

class ManagementInterface;

namespace eAccelero {

    class Pinger;


#ifdef STANDALONE_TEST
#define CONFIG_PING_PERIODICITY_FOR_PEER                                                        5000
#define CONFIG_MINIMUM_PING_PERIODICITY_FOR_ARBITRATOR                                          32
#define CONFIG_PROCESS_RESTART_MAXIMUM_ALLOWED_INTERVAL                                         120
#define CONFIG_PROCESS_RESTART_MAXIMUM_ALLOWED_INTERVAL_HP                                      240

#define I_REPLICATION_MANAGER_DUMMY                                                             (I_REPLICATION_MANAGER + 100)
#define COMP_REPLICATION_MANAGER_DUMMY                                                          (COMP_REPLICATION_MANAGER + 100)
#define I_CLI_PROC_DUMMY                                                                        (I_CLI_PROC + 100)
#define COMP_CLI_PROC_DUMMY                                                                     (COMP_CLI_PROC + 100)
#define I_CONFIG_MANAGER_DUMMY                                                                  (I_CONFIG_MANAGER + 100)
#define COMP_CONFIG_MANAGER_DUMMY                                                               (COMP_CONFIG_MANAGER + 100)
#define I_DRE_APP_DUMMY                                                                         (I_DRE_APP + 100)
#define COMP_DRE_APP_DUMMY                                                                      (COMP_DRE_APP + 100)
#else
#define CONFIG_PING_PERIODICITY_FOR_PEER                                                        512
#define CONFIG_MINIMUM_PING_PERIODICITY_FOR_ARBITRATOR                                          32
#define CONFIG_PROCESS_RESTART_MAXIMUM_ALLOWED_INTERVAL                                         5
#define CONFIG_PROCESS_RESTART_MAXIMUM_ALLOWED_INTERVAL_HP                                      10
#endif

#define CONFIG_NUMBER_OF_CONSECUTIVE_PING_ACKNOWLEDGMENT_RECEIVE_FAILURES_FROM_PEER             3
#define CONFIG_NUMBER_OF_CONSECUTIVE_PING_ACKNOWLEDGMENT_RECEIVE_FAILURES_FROM_ARBITRATOR       3

#define CONFIG_NO_HB_ACK_FAILURES                                                               10

#define CONFIG_MAXIMUM_NUMBER_OF_BEARERS                                                        16

#define CONFIG_PROCESS_RESTART_MAXIMUM_ALLOWED_COUNT                                            3
#define CONFIG_PROCESS_RESTART_MAXIMUM_ALLOWED_COUNT_HP                                         4

#define PROCESS_PRIORITY_HIGH                                                                   1
#define PROCESS_PRIORITY_LOW                                                                    3

#define CONFIG_MAX_PROCESSES                                                                    4

#define CONFIG_TIME_TO_LAUNCH_PROCESSES                                                         256

#define MAX_INSTANCES                                                                           2
#define PEER_INITIAL_SEQUENCE_ID                                                                0
#define PEER_INVALID_INSTANCE_ID                                                                65535
#define HOSTNAME_LEN                                                                            256
#define ARGUMENT_LEN                                                                            256
#define ARGUMENT_COUNT                                                                          32

#define GET_NODESTATUS                                                                          1
#define HA_SWITCHOVER                                                                           2

#define SWITCHOVER_SUCCESS                                                                      0

#define TIPC_TYPE_RESERVED_MAX                                                                  63

#define COMPONENT_RESTART_LIMIT_REACHED                                                         0

#define ETH_INTF_NUM_GRAT_ARP_COUNT_STANDBY '0'
#define ETH_INTF_NUM_GRAT_ARP_COUNT_ACTIVE '1'

#define ARP_IGNORE_DONOT_REPLY_FOR_LOCAL_ADDRESSES '8'
#define ARP_IGNORE_DEFAULT  '0'

#define ARP_MECHANISM_NOAP_FLAG_ON_INTERFACE 0
#define ARP_MECHANISM_ARP_ANNOUNCE 1
#define ARP_MECHANISM_ARPTABLES 2

#define NODE_STATUS_SIZE 2048
#define MAX_WAIT_COUNT_FOR_ICMP_PING_FROM_PEER 3

//These values are time in milliseconds.
#define CONFIG_MAX_TIME_TO_WAIT_BEFORE_SENDING_SIGKILL 5000
#define TIME_TO_WAIT_AFTER_SIGKILL	300

#define INTF_NAME_LEN 64
#define IP_ADDR_LEN 64

    enum InterfaceType
    {
        TRAFFIC =1,
        MANAGEMENT

    };

    struct PeerPingReqObj {
        uint32_t selfSequenceId;
        uint16_t selfInstanceId;
        InstanceAvailabilityStatus selfInstanceAvailabilityStatus;
        char selfHostname[HOSTNAME_LEN];
        struct timeval selfLastGoActiveTime;
        bool selfIsAnyEthernetInterfaceNotOperational;
        uint32_t selfCbNodeStatus;
    };

    struct PeerPingRespObj {
        uint32_t peerSequenceId;
        uint16_t peerInstanceId;
        InstanceAvailabilityStatus peerInstanceAvailabilityStatus;
        char peerHostname[HOSTNAME_LEN];
        struct timeval peerLastGoActiveTime;
        bool peerIsAnyEthernetInterfaceNotOperational;
        uint32_t peerCbNodeStatus;
    };

    struct ActivateSwitchoverReqObj {
        uint32_t reqSequenceId;
    };

    struct ActivateSwitchoverRespObj {
        uint32_t respSequenceId;
    };

    struct ProcessAttributes {
        std::string processName;
        pid_t pid;
        uint8_t priority;
        __time_t secondsToNextSigChld;
        __time_t secondsToShutdownApplication;
        uint8_t processRestartCounter;
        uint8_t processRestartCounterForShutdownApplication;
        uint8_t heartBeatMissCounter;
        HAComponentStatus currentComponentStatus;
        bool pauseHeartBeat;
        EventHandlerId sigtermTimerHandle;
        EventHandlerId sigkillTimerHandle;
        uint8_t sigkillTimerCount;
    };


    struct SignalEventInfo {
        int errorno;
        int code;
        pid_t pid;
        uid_t uid;
        int status;
        clock_t utime;
        clock_t stime;
    };

    struct InterfaceGroupAttributes {
        std::vector<std::string> interfaceName;
        bool failureLeadsToSwitchOver;
    };

    struct InterfaceAttributes {
        std::vector<std::string> ipAddresses;
        bool addRoute;
        InterfaceType interfaceType;
        std::vector<struct Route> routes;
        char bondingOptionNumGratArp;
        char arpIgnoreOption;
        bool failureLeadsToSwitchOver;
    };

    struct Route {
        std::string destination;
        std::string gateway;
        int metric;
        std::string tableId;
    };

    enum ROUTE_OPERATION {
        ADD = 1,
        DELETE = 2
    };

    struct RtNetlinkIpAddressReq {
        struct nlmsghdr nl;
        struct ifaddrmsg rt;
        char buf[8192];
    };

    struct RtNetlinkNetworkInterfaceReq {
        struct nlmsghdr nl;
        struct ifinfomsg rt;
        char buf[8192];
    };


    typedef struct _HeartBeatInfo_ {
        uint8_t HBMissCount;
    }HeartBeatInfo;


    typedef struct _ICMPPayloadData_ {
        PeerPingReqObj peerData;
        char signatureBuff[15]; //length of DIAMETRIQ_PING
    }ICMPPayloadData;


#define MAX_SIGNAL_INFO     50
    class SignalInfoEventList
    {
        private:
            uint8_t iPushIndex;
            uint8_t iGetIndex;
            uint8_t iTotalCount;

            SignalEventInfo SignalInfoList[MAX_SIGNAL_INFO];
        public:
            int GetSize() {
                CLOG_DEBUG("TotalCount in SignalInfoEventList = %d",iTotalCount);
                return iTotalCount;
            }

            SignalInfoEventList() {
                iPushIndex = 0;
                iGetIndex = 0;
                iTotalCount = 0;
            }

            int GetFirstSignalData(SignalEventInfo &Info) {
                if(iTotalCount == 0) {
                    CLOG_DEBUG("TotalCount in SignalInfoEventList = %d,Nothing in the list so returning -1",iTotalCount);
                    return -1;
                }

                iTotalCount--;

                int iLocalIndex = iGetIndex;
                Info.errorno = SignalInfoList[iLocalIndex].errorno;
                Info.code = SignalInfoList[iLocalIndex].code;
                Info.pid = SignalInfoList[iLocalIndex].pid;
                Info.uid = SignalInfoList[iLocalIndex].uid;
                Info.status = SignalInfoList[iLocalIndex].status;
                Info.utime = SignalInfoList[iLocalIndex].utime;
                Info.stime = SignalInfoList[iLocalIndex].stime;
                iGetIndex++;
                iGetIndex = iGetIndex%MAX_SIGNAL_INFO;

                return 1;
            }

            int InsertData(SignalEventInfo &Info) {
                if(iTotalCount >= MAX_SIGNAL_INFO -1) {
                    CLOG_DEBUG("TotalCount in SignalInfoEventList = %d, List is full so returning -1",iTotalCount);
                    return -1;
                }

                iTotalCount++;

                int iLocalIndex = iPushIndex;
                SignalInfoList[iLocalIndex].errorno = Info.errorno;
                SignalInfoList[iLocalIndex].code = Info.code;
                SignalInfoList[iLocalIndex].pid = Info.pid;
                SignalInfoList[iLocalIndex].uid = Info.uid;
                SignalInfoList[iLocalIndex].status = Info.status;
                SignalInfoList[iLocalIndex].utime = Info.utime;
                SignalInfoList[iLocalIndex].stime = Info.stime;
                iPushIndex++;
                iPushIndex = iPushIndex%MAX_SIGNAL_INFO;

                return 1;
            }
    };




    class AvailabilityManager : public MeSSComponent,
    public AvaMgrPeerStatusInterface,
    public AvaMgrComponentStatusInterface,
    public Stub::AvaMgrProcessStatusInterfaceRespCbk,
    public Stub::AvaMgrPeerStatusInterfaceRespCbk
    {

        public:

            AvailabilityManager();

            ~AvailabilityManager();

            void Initialize();

            void Terminate();

            int ActivateSwitchover();

            std::string GetNodeStatus();

            int AvaMgrSetConfiguration(AvaMgrConfig *req, AvaMgrConfigResp *resp);

            int AvaMgrGetConfiguration(ComponentActionReq *req, AvaMgrConfigResp *resp);

            int AvaMgrSwitchOverRequest(ComponentActionReq *req, AvaMgrConfigResp *resp);

            int FetchClusterInfo(ClusterInfoReq *req, ClusterInfoResp *resp);

            int FetchProcessState(ProcessStateReq *req, ProcessStateResp *resp);

            Logger::Channel GetLogChannel();

            void SetLogChannel(Logger::Channel logChannel);

            Logger::Level GetLogLevel();

            void SetLogLevel(Logger::Level logLevel);

            std::string GetLogFileLocation();

            void SetLogFileLocation(std::string strCfgLogFileLocation);

            void RegisterMethods();

            int OnNodeEvent(TopologyEvent &event);

            int OnComponentEvent(TopologyEvent &event);

            int OnSigChld(SignalEvent &event);

            int OnIcmpSocketEvent(SockEvent &event);

            int OnRecurringTimerExpiry(TimerEvent &ev);

            int OnPeriodicTimerExpiry(TimerEvent &event);

            void UpdateAvailabilityStatus();

            void SendAvailabilityStatusResetReq(
                    uint16_t componentId,
                    uint16_t destInstanceId,
                    uint16_t newInstanceId, bool switchOver);

            void SendAvailabilityStatusGetReq(
                    uint16_t componentId,
                    uint16_t destInstanceId);

            int AvailabilityStatusGetRequestRespCbk(AvailabilityStatusGetResp *response);

            int AvailabilityStatusResetRequestRespCbk(AvailabilityStatusResetResp *response);

            int AvailabilityPeerPingRequest(PeerPingReq *request,PeerPingResp *response);

            int AvailabilityPeerPingRequestRespCbk(PeerPingResp *response);

            int ComponentStatusUpdate(ComponentStatusUpdateReq *Request,ComponentStatusUpdateResp *Response);

            int ComponentStatusUpdateBroadcastRespCbk(ComponentStatusUpdateResp *Response);

            void SendPeerPingReq(uint16_t instanceId);

            int OnSwitchoverCompleteEvent(TimerEvent &ev);

            void RegisterPinger(int16_t iPingFd);

            void RegisterTimer(uint32_t uiPeriodicTimerMiliSec);

            void SetPeerCurrentStatus(eAccelero::InstanceAvailabilityStatus Status);

            InstanceAvailabilityStatus GetPeerCurrentStatus();

            InstanceAvailabilityStatus GetSelfCurrentStatus();

            uint8_t GetCfgNumConsecutivePingAckRcvFailuresFromPeer();

            int AddCouchbaseNodeToCluster(AddToClusterReq *Request,AddToClusterResp *Response);

            int AddCouchbaseNodeToClusterRespCbk(AddToClusterResp *Response);

            uint32_t SendAddNodeToClusterRequest(std::string couchbaseHostName);

            uint32_t GetSelfTipcNodeId();

            void UnRegisterEvent(EventHandlerId Id,unsigned eventType);

            EventHandlerId GetIcmpSocketHandlerId();

            EventHandlerId GetPeriodicTimerId();

            void SetIcmpSocketHandlerId(EventHandlerId Id);

            void SetPeriodicTimerId(EventHandlerId Id);

            std::string GetArbitratorIpAddress();

            uint16_t GetPingPeriodicityForArbitrator();

            uint16_t GetWaitingForIcmpPingFromPeer();

            void ResetWaitingForIcmpPingFromPeer();

            void SetPeerInstanceId(uint16_t InstaceId);

            uint16_t GetSelfInstanceId();

            void SetPeerHostname(char *pHostname);

            void SetLastPeerAckTime(struct timeval tmVal);

            char* GetSelfHostname();

            void SetPeerLastGoActiveTime(struct timeval tmVal);

            struct timeval GetSelfLastGoActiveTime();

            void SetPeerEthernetInterfaceNotOperational(bool val);

            bool GetSelfEthernetInterfaceNotOperational();

            uint32_t GetSelfCbNodeStatus();

            void SetSelfCbNodeStatus(uint32_t cbNodeStatus);

            uint32_t GetPeerCbNodeStatus();

            void SetPeerCbNodeStatus(uint32_t cbNodeStatus);

            void VerifyExitStatus(uint32_t status,std::string ProcessName="");

            void PrintExitMsgToFile(const char* errorString,bool isItLicenseError = false);

            void ClearAllAvalabilityAlarms();

            void StartSigtermTimer(uint16_t, uint32_t);

            int HandleSigtermTimeout(eAccelero::TimerEvent&);

            int HandleSigkillTimeout(eAccelero::TimerEvent&);

            void StopSigtermTimer(uint16_t);

        private:

            void SendComponentStatusUpdate(uint16_t componentId);

            void BeActiveInstance();

            void BeStandbyInstance();

            void MakeActiveInstance(bool switchOver);

            void MakeStandbyInstance(bool switchOver);

            bool SwitchChildProcessesToActive(bool switchOver);

            bool SwitchChildProcessesToStandby(bool switchOver);

            bool IsEthernetInterfaceOperational(const char *interfaceName);

            int AssignIpAddressToInterface(const char *interfaceName, const char *ipAddress,
                    unsigned char routingPrefix, bool assign = true);

            int PerformRouteOpOnInterface(std::string interfaceName, std::string srcAddress,
                    ROUTE_OPERATION op);

            int SetArpAttribOnInterface(const char *interfaceName, bool isEnableArp);

            void SendGratuitousArp(const char *interfaceName, const char *ipAddress, bool useBroadCastIp);

            void SendGratuitousArpForAllVirtualAddresses();

            bool SetGratArpCountAttribOnInterface(unsigned char count,const char* interfaceName);

            char GetGratArpCountAttribOfInterface(const char* interfaceName);

            char GetArpIgnoreValueOfInterface(const char* interfaceName);

            bool SetArpIgnoreFlagOnInterface(unsigned char flag, const char* interfaceName);

            void AddArpTableRulesForTrafficVIPs(bool enableArp);

            void AddArpTableRulesForInterface(const char* ipAddress, bool direction, bool enableArp);

            void FlushArpTables();

            void LaunchProcess(const char *processName, const char *processArgs, pid_t &pid);

            void UtilityThread(void* arg);

            int LaunchProcessAndWait(const char *processName, const char *processArgs,
                    int64_t timeout=3000000);

            bool StartComponent(uint16_t componentId,bool isRestart=false);

            bool TerminateAllComponents(bool highPriority=false);

            bool StartAllComponents(bool lowPriority=false);

            void CheckHeartBeatStatusOfChildProcesses();

            void CheckComponentStatusAndUpdateHeartBeatFlag(InstanceAvailabilityStatus currentNodeStatus);

            void ReadConfiguration();

            void PopulateConfiguration();

            void PopulateConfig();

            void PopulateConfigErrorMap();

            void ProcessIpAddressCidr();

            string GetFileNameFromPath(string path, string &filename);

            std::vector<std::string> Split(const char *str, char c);

            uint32_t GetTipcNodeId(TIPCAddr addr);

            int GetAddrFamily(const char *ipAddress);

            bool isArbitratorEnabled();

            bool isNodeActive();

            int SendComponentStatusRequest(uint16_t componentId,
                    uint16_t destInstanceId,ComponentStatusUpdateReq req);

            uint16_t HandleQueuedSignalInfo(SignalEventInfo& sigInfo);

            void CreateAndQueueDummySignal(pid_t pid);

            int CheckAndUpdateComponentStatusFlag();

            void UpdateComponentStatus(uint16_t componentId, HAComponentStatus componentStatus);


            int StartReplicationRespCbk(ReplicationResp *Response);

            int StopReplicationRespCbk(ReplicationResp *Response);

            int AvailabilityActiveUpdateBroadcastRespCbk(AvailabilityActiveResp *Response);
            int SendAvailabilityActiveUpdateReqToComponents(uint16_t destInstanceId);
            int AssignIPAddresses(std::vector<std::string> &ipAddresses,
                    const char *interface,
                    bool assign);

            uint32_t PerformClusterOperation(ClusterManagementEvent event);

            uint32_t CheckAndHandleCbCluster(bool isPeerNodeDown,bool isManagementInterfaceDown);

            struct CmdArgs {

                CmdArgs()
                    : mode("m", "mode", "Whether instance should be started in standalone mode", false) {
                    }
                CmdOption<std::string> mode;
            } m_cmdArgs;

            bool m_bAllComponentsInitialized;

            EventHandlerId m_objRecurringTimerId;
            EventHandlerId m_objSigChldHandlerId;
            EventHandlerId m_objIcmpSocketHandlerId;
            EventHandlerId m_objPeriodicTimerId;
            PeerPingReqObj m_objSelfCurrentStatus;
            PeerPingRespObj m_objPeerCurrentStatus;
            uint32_t m_uiTipcSequenceId;
            std::set<std::string> m_objHostnameSet;
            struct timeval m_objLastPeerAckTime;
            bool m_isPeerAvailable;
            bool m_isPeerStandby;
            bool m_OneTimePeerActiveBroadCast;
            Pinger *m_objPinger;
            std::unordered_map<uint16_t, ProcessAttributes> m_objProcessMap;
            std::vector<uint16_t> m_objComponentIdVector;
            //std::queue<SignalEventInfo> m_queueSignalEvents;
            uint32_t m_uiOwnTipcNodeId;
            std::map<uint16_t, InstanceAvailabilityStatus> m_objComponentIdAvailabilityStatusMap;
            std::map<std::string, std::string> m_objVirtualIpAddressEthernetInterfaceMap;
            std::map<std::string, unsigned char> m_objVirtualIpAddressRoutingPrefixMap;
            std::set<std::string> m_objEthernetInterfaceSet;
            //Contains all of interface details.
            std::map<std::string,InterfaceAttributes> m_objInterfaceMap;
            std::map<std::string,InterfaceGroupAttributes> m_objInterfaceGroupMap;

            bool m_bIsNeedToAssignIpAddressToInterface;
            std::map<uint16_t, HeartBeatInfo> m_objComponentIdHBInfoMap;
            bool m_bStopComponentHeartBeat;
            bool m_bIsHeartbeatEnabled;
            bool m_bProcessTerminationInProgress;
            uint32_t m_iInstanceStartMode;
            bool m_bSwitchoverInProgress;
            EventHandlerId m_objSwitchoverTimerId;
            bool m_isPlannedSwitchOver;
            bool m_isRebalanceStuck;
            uint8_t m_uiArpMechanism;
            uint8_t m_uiWaitCountForIcmpPingFromPeer;

            std::map<std::string, std::string> m_objCfgReaderMap;

            Json::Reader m_jsonConfigFileReader;
            Json::Value m_jsonRoot;

            uint16_t m_uiCfgPingPeriodicityForPeer;
            uint16_t m_uiCfgMinPingPeriodicityForArbitrator;
            uint8_t m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer;
            uint8_t m_uiCfgNumConsecutivePingAckRcvFailuresFromArbitrator;
            uint16_t m_uiCfgProcessRestartMaxAllowedInterval;
            uint16_t m_uiCfgProcessRestartMaxAllowedIntervalHp;
            uint8_t m_uiCfgProcessRestartMaxAllowedCount;
            uint8_t m_uiCfgProcessRestartMaxAllowedCountHp;
            uint8_t m_uiCfgMaxProcessHBAckFailures;
            uint32_t m_uiCfgMaxTimeToWaitBeforeSendingSigkill;
            uint32_t m_uiCfgMaxTimeToWaitAfterSendingSigkill;
            std::vector<unsigned char> m_ucCfgRoutingPrefixVector;
            std::string m_strCfgArbitratorIpAddress;
            uint8_t m_uiCfgMaxProcesses;
            uint16_t m_uiCfgTimeToLaunchProcesses;
            uint8_t m_uiCfgLogChannel;
            std::string m_strCfgLogFileLocation;


            bool m_bComponentsRunning;

            std::map<int,std::string> m_cfgErrorMap;

            SyslogChannel *m_objSyslogChannel;
            FileLogChannel *m_objFileLogChannel;

            ManagementInterface *m_objMgmtIface;

            AvailabilityManagerAlarms* m_avaMgrAlarm;

            //Replication related items.
            eAccelero::Thread* cmThread;

            ClusterManager* m_clMgr;
            ClusterManagementStatus m_CmStatus;
            ReplicationConfig m_replicationConfig;

            uint32_t SendStartReplicationToComponents(uint16_t destInstanceId);

            uint32_t SendStopReplicationToComponents(uint16_t destInstanceId);
            bool m_bSuppressHigPriorityProcessAlarm;
            struct timeval  m_secondsToPurgeUnwantedData;
            SignalInfoEventList m_signalList;

            struct SendGARPEventData {
                char intfName[INTF_NAME_LEN];
                char ipAddress[IP_ADDR_LEN];
            };

            enum UtilityEventType {
                UTILITY_SENDGARP_VIP,
                UTILITY_BLOCK_ARP_VIP,
                UTILITY_UNBLOCK_ARP_VIP,
                UTILITY_FLUSH_ARP_TABLES
            };
            class UtilityEvent {
                public:
                    UtilityEventType ev_type;
                    void* data;
            };


            Thread* m_utilityThread;
            ThreadQueue<UtilityEvent> m_utility_q;
            bool m_utilityThreadrunning;

        public:
            static bool stopReplication;
    };
}

#endif	/* AVAILABILITYMANAGER_H */

