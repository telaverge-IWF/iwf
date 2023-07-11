/*********************************-*-C++-*-************************************
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

#include "AlarmId.h"
#include "ComponentDefines.h"
#include "Alarms_def.h"
#include "CMAPICommon.h"
#include "AvailabilityManagerAlarms.h"
#include <utility>
#include <iostream>
#define AVAMGR_PROCESS_NAME "avamgr"

using namespace std;

namespace eAccelero {

    AvailabilityManagerAlarms::AvailabilityManagerAlarms(uint16_t instanceId,uint32_t componentId) {
        m_alarmapi = new CMAPIAlarms();
        m_alarmapi->InitializeLibrary();
        m_componentId = componentId-COMPONENT_ID_START;
        currentInstanceId = instanceId;
        int returnCode = gethostname(m_hostName,MAX_HOST_NAME_LENGTH);

        if(returnCode != 0)
        {
            CLOG_ERROR("Failed to Fetch Hostname.errno =",errno);
        }

        CLOG_DEBUG("Entered AvailabilityManagerAlarms::AvailabilityManagerAlarms()");
    }


    AvailabilityManagerAlarms::~AvailabilityManagerAlarms() {

    }

    void AvailabilityManagerAlarms::UpdateDestInstanceId(uint16_t instanceId)
    {
        CLOG_INFO("Modifying destInstance Id for Alarms to %d",instanceId);
        currentInstanceId = instanceId;
    }
    uint32_t AvailabilityManagerAlarms::FetchAndUpdateAlarmKeys(std::string keyToAlarmKey,bool isClearKey)
    {
        uint32_t alarmKey = 0;
        unordered_map<std::string,uint32_t>::iterator it = m_avMgrAlarmKeys.find(keyToAlarmKey);
        if(it!=m_avMgrAlarmKeys.end())
        {
            alarmKey = it->second;
            if(isClearKey)
            {
                it->second = 0;
            }
            else
            {
                if(it->second == 0)
                {
                    it->second = m_randomNumberObj.getRandomNumber();
                }
                alarmKey = it->second;
            }
            CLOG_DEBUG("Key to alarmKey found.AlarmKey is %u",alarmKey);

        }
        else
        {
            //If alarm for clear and no key stored for previous raises dont inlcude key
            if(!isClearKey)
            {
                alarmKey = m_randomNumberObj.getRandomNumber();
                CLOG_DEBUG("Key to alarmKey generated.AlarmKey is %u",alarmKey);
                //m_avMgrAlarmKeys.insert(std::make_pair<std::string,uint32_t>(keyToAlarmKey,alarmKey));
                m_avMgrAlarmKeys.insert(std::make_pair(keyToAlarmKey,alarmKey));
            }
        }
        return alarmKey;
    }
    void AvailabilityManagerAlarms::RaiseAlarm(uint32_t subComponentId,uint32_t subComponentAlarmId,
                               std::string addText, std::vector<std::string> &variables,uint32_t alarmKey)
    {
        AlarmReq Req;
        AlarmResp Resp;
        if(alarmKey)
        {
            std::stringstream keyString;
            keyString <<m_hostName<<":"<<AVAMGR_PROCESS_NAME<<":"<<alarmKey ;
            Req.set_alarmkey(keyString.str());
        }
        Req.set_componentid(m_componentId);
        Req.set_subcomponentid(subComponentId);
        Req.set_subcomponentalarmid(subComponentAlarmId);
        Req.set_addtext(addText);
        for ( unsigned int i=0; i< variables.size(); i++ )
        {
            Req.add_variables(variables[i]);
        }

        if(m_alarmapi->RaiseAlarm(currentInstanceId,Req,Resp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG("Succesfully Sent an alarm with alarm Id %d%d and additional text %s \
                    using CMAPI",subComponentId,subComponentAlarmId,addText.c_str());
        } else {
            CLOG_ERROR("Failed to raise an alarm using CMAPI, AlarmId:%d%d,AddText:%s",subComponentId,subComponentAlarmId,addText.c_str());
        }
    }

    void AvailabilityManagerAlarms::RaiseIntfDownAlarm(std::string interfaceName){
        int subComponentId = AVAMGR_SUB_COMP_INTERFACE_MONITORING;
        int alarmId = CONFIGURED_ETH_INTERFACE_DOWN;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_CONFIGURED_ETH_INTERFACE_DOWN);
        variables.push_back(interfaceName);

        //Since interfcae is mentioned while going donw and not metioned while its up
        //Mentioning only this.Need to change it to interface name when implemented
        uint32_t alarmKey = FetchAndUpdateAlarmKeys("interface");
        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }
    void AvailabilityManagerAlarms::RaiseIntfUpAlarm(std::string interfaceName,bool includeAlarmKey){
        int subComponentId = AVAMGR_SUB_COMP_INTERFACE_MONITORING;
        int alarmId = CONFIGURED_ETH_INTERFACE_UP;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_CONFIGURED_ETH_INTERFACE_UP);
        variables.push_back(interfaceName);

        //Since interfcae is mentioned while going donw and not metioned while its up
        //Mentioning only this.Need to change it to interface name when implemented
        if(includeAlarmKey)
        {
            alarmKey = FetchAndUpdateAlarmKeys("interface",true);
        }
        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }
    void AvailabilityManagerAlarms::RaiseHighPriorityProcessDownAlarm(std::string processName){
        int subComponentId = AVAMGR_SUB_COMP_PROCESS_MONITORING;
        int alarmId = HIGH_PRIORITY_PROC_DOWN ;
        std::vector<std::string> variables;
        CleanupProcessName(&processName);
        std::string alarmText(ALARM_DEF_TEXT_HIGH_PRIORITY_PROC_DOWN);
        variables.push_back(processName);

        std::stringstream keyString;
        keyString << processName.c_str() << HIGH_PRIORITY_PROC_DOWN;
        std::string keyToAlarmKey = keyString.str();
        uint32_t alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey);

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }
    void AvailabilityManagerAlarms::RaiseHighPriorityProcessUpAlarm(std::string processName,bool includeAlarmKey){
        int subComponentId = AVAMGR_SUB_COMP_PROCESS_MONITORING;
        int alarmId = HIGH_PRIORITY_PROC_UP;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        CleanupProcessName(&processName);
        std::string alarmText(ALARM_DEF_TEXT_HIGH_PRIORITY_PROC_UP);
        variables.push_back(processName);

        if(includeAlarmKey)
        {
            std::stringstream keyString;
            //Use same alarm id for clearing also
            keyString << processName.c_str() << HIGH_PRIORITY_PROC_DOWN;
            std::string keyToAlarmKey = keyString.str();
            alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey,true);
        }

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }
    void AvailabilityManagerAlarms::RaiseLowPriorityProcessDownAlarm(std::string processName){
        int subComponentId = AVAMGR_SUB_COMP_PROCESS_MONITORING;
        int alarmId = LOW_PRIORITY_PROC_DOWN;
        std::vector<std::string> variables;
        CleanupProcessName(&processName);
        std::string alarmText(ALARM_DEF_TEXT_LOW_PRIORITY_PROC_DOWN);
        variables.push_back(processName);

        std::stringstream keyString;
        keyString << processName.c_str() << LOW_PRIORITY_PROC_DOWN;
        std::string keyToAlarmKey = keyString.str();
        uint32_t alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey);

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }
    void AvailabilityManagerAlarms::RaiseLowPriorityProcessUpAlarm(std::string processName,bool includeAlarmKey){
        int subComponentId = AVAMGR_SUB_COMP_PROCESS_MONITORING;
        int alarmId = LOW_PRIORITY_PROC_UP;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        CleanupProcessName(&processName);
        std::string alarmText(ALARM_DEF_TEXT_LOW_PRIORITY_PROC_UP);
        variables.push_back(processName);

        if(includeAlarmKey)
        {
            std::stringstream keyString;
            //Use same alarm id for clearing also
            keyString << processName.c_str() << LOW_PRIORITY_PROC_DOWN;
            std::string keyToAlarmKey = keyString.str();
            alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey,true);
        }

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }
    void AvailabilityManagerAlarms::RaiseProcessRestartLimitReachedAlarm(std::string processName){
        /* int alarmId = HIGH_PRIORITY_PROC_DOWN ;
           std::string alarmText(processName);
           alarmText.append(" :Maximum restarts for the process is reached.");
           RaiseAlarm(alarmId,alarmText);*/
    }

    void AvailabilityManagerAlarms::RaiseDREDownAlarm(std::string hostName){
        int subComponentId = AVAMGR_SUB_COMP_PROCESS_MONITORING;
        int alarmId = DRE_GRACEFUL_SHUTDOWN;
        std::vector<std::string> variables;
        variables.push_back(hostName);
        std::string alarmText(ALARM_DEF_TEXT_DRE_GRACEFUL_SHUTDOWN);

        std::stringstream keyString;
        keyString << hostName.c_str() << DRE_GRACEFUL_SHUTDOWN;
        std::string keyToAlarmKey = keyString.str();
        uint32_t alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey);

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }

    void AvailabilityManagerAlarms::RaiseDREBringupAlarm(std::string hostName,bool includeAlarmKey){
        int subComponentId = AVAMGR_SUB_COMP_PROCESS_MONITORING;
        int alarmId = DRE_UP_AFTER_SHUTDOWN;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        variables.push_back(hostName);
        std::string alarmText(ALARM_DEF_TEXT_DRE_UP_AFTER_SHUTDOWN);
        CLOG_DEBUG( "Raised an alarm for DRE_UP_AFTER_SHUTDOWN");

        if(includeAlarmKey)
        {
            std::stringstream keyString;
            //Use same alarm id for clearing also
            keyString << hostName.c_str() << DRE_GRACEFUL_SHUTDOWN;
            std::string keyToAlarmKey = keyString.str();
            alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey,true);
        }

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }

    void AvailabilityManagerAlarms::UnplannedSwitchoverInitiatedAlarm(std::string selfHostname)
    {
        int subComponentId = AVAMGR_SUB_COMP_AVAILABILITY;
        int alarmId = UNPLANNED_SWITCHOVER_TO_STANDBY_INITIATED;
        std::vector<std::string> variables;
        std::string alarmText;
        alarmText.append(ALARM_DEF_TEXT_UNPLANNED_SWITCHOVER_TO_STANDBY_INITIATED);
        CLOG_DEBUG( "Raised an alarm for UNPLANNED_SWITCHOVER_TO_STANDBY_INITIATED");

        std::stringstream keyString;
        keyString << selfHostname.c_str() << DRE_GRACEFUL_SHUTDOWN;
        std::string keyToAlarmKey = keyString.str();
        uint32_t alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey);

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }

    void AvailabilityManagerAlarms::UnplannedSwitchoverCompletedAlarm(std::string selfHostname,bool includeAlarmKey)
    {
        int subComponentId = AVAMGR_SUB_COMP_AVAILABILITY;
        int alarmId = UNPLANNED_SWITCHOVER_TO_STANDBY_SUCCESS;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_UNPLANNED_SWITCHOVER_TO_STANDBY_SUCCESS);
        CLOG_DEBUG( "Raised an alarm for UNPLANNED_SWITCHOVER_TO_STANDBY_SUCCESS");

        if(includeAlarmKey)
        {
            std::stringstream keyString;
            //Use same alarm id for clearing also
            keyString << selfHostname.c_str() << UNPLANNED_SWITCHOVER_TO_STANDBY_INITIATED;
            std::string keyToAlarmKey = keyString.str();
            alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey,true);
        }

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }

    void AvailabilityManagerAlarms::PlannedSwitchoverInitiatedAlarm(std::string selfHostname)
    {
        int subComponentId = AVAMGR_SUB_COMP_AVAILABILITY;
        int alarmId = PLANNED_SWITCHOVER_TO_STANDBY_INITIATED;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_PLANNED_SWITCHOVER_TO_STANDBY_INITIATED);
        CLOG_DEBUG( "Raised an alarm for PLANNED_SWITCHOVER_TO_STANDBY_INITIATED.");

        std::stringstream keyString;
        keyString << selfHostname.c_str() << PLANNED_SWITCHOVER_TO_STANDBY_INITIATED;
        std::string keyToAlarmKey = keyString.str();
        uint32_t alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey);

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }

    void AvailabilityManagerAlarms::PlannedSwitchoverCompletedAlarm(std::string selfHostname,bool includeAlarmKey)
    {
        int subComponentId = AVAMGR_SUB_COMP_AVAILABILITY;
        int alarmId = PLANNED_SWITCHOVER_TO_STANDBY_SUCCESS;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_PLANNED_SWITCHOVER_TO_STANDBY_SUCCESS);
        CLOG_DEBUG( "Raised an alarm for PLANNED_SWITCHOVER_TO_STANDBY_SUCCESS");

        if(includeAlarmKey)
        {
            std::stringstream keyString;
            //Use same alarm id for clearing also
            keyString << selfHostname.c_str() << PLANNED_SWITCHOVER_TO_STANDBY_INITIATED;
            std::string keyToAlarmKey = keyString.str();
            alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey,true);
        }

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }

    void AvailabilityManagerAlarms::StandbyNodeDownInActiveStandbyAlarm(std::string selfHostname)
    {
        int subComponentId = AVAMGR_SUB_COMP_AVAILABILITY;
        int alarmId = STANDBY_NOT_AVAILABLE;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_STANDBY_NOT_AVAILABLE);
        CLOG_DEBUG( "Raised an alarm for STANDBY_NOT_AVAILABLE");

        std::stringstream keyString;
        keyString << selfHostname.c_str() << STANDBY_NOT_AVAILABLE;
        std::string keyToAlarmKey = keyString.str();
        uint32_t alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey);

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }

    void AvailabilityManagerAlarms::StandbyNodeUpInActiveStandbyAlarm(std::string selfHostname,bool includeAlarmKey)
    {
        int subComponentId = AVAMGR_SUB_COMP_AVAILABILITY;
        int alarmId = STANDBY_AVAILABLE;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_STANDBY_AVAILABLE);
        CLOG_DEBUG( "Raised an alarm for STANDBY_AVAILABLE");

        if(includeAlarmKey)
        {
            std::stringstream keyString;
            //Use same alarm id for clearing also
            keyString << selfHostname.c_str() << STANDBY_NOT_AVAILABLE;
            std::string keyToAlarmKey = keyString.str();
            alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey,true);
        }

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }

    void AvailabilityManagerAlarms::RaiseLicenseViolationAlarm(const char* alaramString,bool includeAlarmKey)
    {
        int subComponentId = AVAMGR_SUB_COMP_PROCESS_MONITORING;
        int alarmId = DRE_LICENSE_VIOLATION;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        variables.push_back(alaramString);
        std::string alarmText("Raised an alarm for License violation");
        CLOG_DEBUG( "Raised an alarm for License violation");

        if(includeAlarmKey)
        {
            std::stringstream keyString;
            keyString << DRE_LICENSE_VIOLATION;
            std::string keyToAlarmKey = keyString.str();
            alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey);
        }

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }
   void  AvailabilityManagerAlarms::RaiseLicenseViolationClearAlarm()
    {
        int subComponentId = AVAMGR_SUB_COMP_PROCESS_MONITORING;
        int alarmId = DRE_CLEAR_LICENSE_VIOLATION;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        std::string alarmText("Raised an alarm for clearing license violation");
        variables.push_back(alarmText);
        CLOG_DEBUG( "Raised an alarm for clearing license violation");

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }


    void AvailabilityManagerAlarms::CleanupProcessName(std::string* processDetails)
    {
        size_t pos = processDetails->find_first_of(' ');
        if(pos!=string::npos)
        {
            CLOG_DEBUG("processDetails is %s",processDetails->c_str());
            processDetails->erase(pos);
        }
        CLOG_DEBUG("processDetails after erase is %s",processDetails->c_str());
        size_t pos1 = processDetails->find_last_of('/');
        if(pos1!=string::npos)
        {
            processDetails->erase(0,pos1+1);
        }
        CLOG_DEBUG("processDetails after second erase is %s",processDetails->c_str());

    }

    void AvailabilityManagerAlarms::RaiseSessionReplicationDisabledAlarm(bool includeAlarmKey)
    {
        int subComponentId = AVAMGR_SUB_COMP_REPLICATION;
        int alarmId = REPLICATION_DISABLED;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_REPLICATION_DISABLED);
        CLOG_DEBUG( "Raised an alarm for Disabling Replication, alarmKey=%u",alarmKey);

        if(includeAlarmKey)
        {
            std::stringstream keyString;
            keyString << REPLICATION_DISABLED;
            std::string keyToAlarmKey = keyString.str();
            alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey);
        }

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }

    void AvailabilityManagerAlarms::RaiseSessionReplicaionRestoredAlarm(bool includeAlarmKey)
    {
        int subComponentId = AVAMGR_SUB_COMP_REPLICATION;
        int alarmId = REPLICATION_RESTORED;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_REPLICATION_RESTORED);
        CLOG_DEBUG( "Raised an alarm for Enabling Replication, alarmKey=%d",alarmKey);

        if(includeAlarmKey)
        {
            std::stringstream keyString;
            keyString << REPLICATION_DISABLED;
            std::string keyToAlarmKey = keyString.str();
            alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey,true);
        }

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }
    void AvailabilityManagerAlarms::RaiseCouchaseDownAlarm(bool includeAlarmKey)
    {
        int subComponentId = AVAMGR_SUB_COMP_REPLICATION;
        int alarmId = COUCHBASE_DOWN ;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_COUCHBASE_DOWN);
        CLOG_DEBUG( "Raised an alarm for Couchhbase down");

        if(includeAlarmKey)
        {
            std::stringstream keyString;
            keyString << COUCHBASE_DOWN;
            std::string keyToAlarmKey = keyString.str();
            alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey);
        }

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }

    void AvailabilityManagerAlarms::RaiseCouchbaseIsBackUpAlarm(bool includeAlarmKey)
    {
        int subComponentId = AVAMGR_SUB_COMP_REPLICATION;
        int alarmId = COUCHBASE_UP;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_COUCHBASE_UP);
        CLOG_DEBUG( "Raised an alarm for Couchbase is back up");

        if(includeAlarmKey)
        {
            std::stringstream keyString;
            keyString << COUCHBASE_DOWN;
            std::string keyToAlarmKey = keyString.str();
            alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey,true);
        }

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }


    void AvailabilityManagerAlarms::RaiseCouchbaseRebalanceStuckAlarm(bool includeAlarmKey)
    {
        int subComponentId = AVAMGR_SUB_COMP_REPLICATION;
        int alarmId = COUCHBASE_REBALANCE_STUCK ;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_CB_REBALANCE_STUCK);
        CLOG_DEBUG( "Raised an alarm for Couchhbase Rebalance stuck");

        if(includeAlarmKey)
        {
            std::stringstream keyString;
            keyString << COUCHBASE_REBALANCE_STUCK;
            std::string keyToAlarmKey = keyString.str();
            alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey);
        }

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }

    void AvailabilityManagerAlarms::RaiseCouchbaseRebalanceRestoredAlarm(bool includeAlarmKey)
    {
        int subComponentId = AVAMGR_SUB_COMP_REPLICATION;
        int alarmId = COUCHBASE_REBALANCE_RESTORED;
        uint32_t alarmKey = 0;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_CB_REBALANCE_RESTORED);
        CLOG_DEBUG( "Raised an alarm for Couchbase Rebalance Restored");

        if(includeAlarmKey)
        {
            std::stringstream keyString;
            keyString << COUCHBASE_REBALANCE_STUCK;
            std::string keyToAlarmKey = keyString.str();
            alarmKey = FetchAndUpdateAlarmKeys(keyToAlarmKey,true);
        }

        RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    }


} //namespace eAccelero
