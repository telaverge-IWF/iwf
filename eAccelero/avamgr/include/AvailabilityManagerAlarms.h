/*********************************-*-H-*-**************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/
#ifndef _AVAILABILITY_MANAGER_ALARMS_H_
#define _AVAILABILITY_MANAGER_ALARMS_H_
#include "CMAPIAlarms.h"
#include <RandomNumber.h>
#include <vector>

#define MAX_HOST_NAME_LENGTH 256
namespace eAccelero {

#define ALARM_DEF_TEXT_STANDBY_NOT_AVAILABLE \
    "Standby node is not available in a Active-Standby Configuration."
#define ALARM_DEF_TEXT_STANDBY_AVAILABLE \
    "Standby Node is back up in a Active-Standby Configuration."
#define ALARM_DEF_TEXT_PLANNED_SWITCHOVER_TO_STANDBY_SUCCESS \
    "Planned/Manual Switchover to Standby Node completed successfully."
#define ALARM_DEF_TEXT_PLANNED_SWITCHOVER_TO_STANDBY_INITIATED \
    "Planned/Manual Switchover to Standby Node has been initiated."
#define ALARM_DEF_TEXT_UNPLANNED_SWITCHOVER_TO_STANDBY_SUCCESS \
    "Unplanned Switchover to Standby Node completed successfully."
#define ALARM_DEF_TEXT_UNPLANNED_SWITCHOVER_TO_STANDBY_INITIATED \
        "Unplanned Switchover to Standby Node has been initiated."
#define ALARM_DEF_TEXT_CONFIGURED_ETH_INTERFACE_DOWN \
    "interface is down"
#define ALARM_DEF_TEXT_CONFIGURED_ETH_INTERFACE_UP \
    "All configured interfaces are back up"
#define ALARM_DEF_TEXT_HIGH_PRIORITY_PROC_DOWN \
    "high priority process is down"
#define ALARM_DEF_TEXT_HIGH_PRIORITY_PROC_UP \
    "high priority process is back up"
#define ALARM_DEF_TEXT_LOW_PRIORITY_PROC_DOWN \
    "low priority process is down"
#define ALARM_DEF_TEXT_LOW_PRIORITY_PROC_UP \
    "low priority process is back up"
#define ALARM_DEF_TEXT_DRE_GRACEFUL_SHUTDOWN \
    "DRE has gracefully shutdown."
#define ALARM_DEF_TEXT_DRE_UP_AFTER_SHUTDOWN \
    "DRE has come up successfully."

#define ALARM_DEF_TEXT_REPLICATION_DISABLED \
    "Session Replication is disabled."

#define ALARM_DEF_TEXT_REPLICATION_RESTORED \
    "Session Replication is restored."

#define ALARM_DEF_TEXT_COUCHBASE_DOWN \
    "Couchbase is down"
#define ALARM_DEF_TEXT_COUCHBASE_UP \
    "Couchbase is back up"

#define ALARM_DEF_TEXT_CB_REBALANCE_STUCK \
    "Couchbase Rebalance stuck"

#define ALARM_DEF_TEXT_CB_REBALANCE_RESTORED \
    "Couchbase Rebalance in progress"

class AvailabilityManagerAlarms {

    public:
        AvailabilityManagerAlarms(uint16_t instanceId,uint32_t componentId);
        ~AvailabilityManagerAlarms();
        void RaiseAlarm(uint32_t subComponentId, uint32_t subComponentAlarmId,
                        std::string addText,std::vector<std::string> &variables,uint32_t alarmKey);
        void RaiseIntfDownAlarm(std::string interfaceName);
        void RaiseIntfUpAlarm(std::string interfaceName,bool includeAlarmKey = true);
        void RaiseHighPriorityProcessDownAlarm(std::string processName);
        void RaiseHighPriorityProcessUpAlarm(std::string processName,bool includeAlarmKey = true);
        void RaiseLowPriorityProcessDownAlarm(std::string processName);
        void RaiseLowPriorityProcessUpAlarm(std::string processName,bool includeAlarmKey = true);
        void RaiseDREDownAlarm(std::string hostName);
        void RaiseDREBringupAlarm(std::string hostName,bool includeAlarmKey = true);
        void RaiseProcessRestartLimitReachedAlarm(std::string processName);
        void UnplannedSwitchoverInitiatedAlarm(std::string selfHostname);
        void UnplannedSwitchoverCompletedAlarm(std::string selfHostname,bool includeAlarmKey = true);
        void PlannedSwitchoverInitiatedAlarm(std::string selfHostname);
        void PlannedSwitchoverCompletedAlarm(std::string selfHostname,bool includeAlarmKey = true);
        void StandbyNodeDownInActiveStandbyAlarm(std::string selfHostname);
        void StandbyNodeUpInActiveStandbyAlarm(std::string selfHostname,bool includeAlarmKey = true);
        void UpdateDestInstanceId(uint16_t instanceId);
        void RaiseLicenseViolationAlarm(const char* alaramString,bool includeAlarmKey = true);
        void RaiseLicenseViolationClearAlarm();
        void RaiseSessionReplicationDisabledAlarm(bool includeAlarmKey = true);
        void RaiseSessionReplicaionRestoredAlarm(bool includeAlarmKey = true);
        void RaiseCouchaseDownAlarm(bool includeAlarmKey=true);
        void RaiseCouchbaseIsBackUpAlarm(bool includeAlarmKey=true);
        void RaiseCouchbaseRebalanceStuckAlarm(bool includeAlarmKey=true);
        void RaiseCouchbaseRebalanceRestoredAlarm(bool includeAlarmKey=true);

        uint32_t FetchAndUpdateAlarmKeys(std::string keyToAlarmKey,bool isClearKey=false);
    private:
        CMAPIAlarms* m_alarmapi;
        uint32_t m_componentId;
        uint16_t currentInstanceId;
        void CleanupProcessName(std::string* processDetails);
        RandomNumberGenerator m_randomNumberObj;
        std::unordered_map<std::string,uint32_t> m_avMgrAlarmKeys;
        char m_hostName[MAX_HOST_NAME_LENGTH];


}; //class AvailabilityManagerAlarms

} // namespace eAccelero

#endif
