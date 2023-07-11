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

#include "subagent.h"
#include "ComponentDefines.h"
#include "InterfaceDefines.h"
#include "AlarmAPIImpl.h"
#include "SubAgentMeSS.h"
#include "AlarmIdString.h"
#include "Statistics.h"

extern ITS_INT DIASA_PutEventOnTaskQue(ITS_EVENT *evt);

using namespace std;
using namespace eAccelero;

Json::Reader dre::SubAgentMeSS::m_jsonConfigFileReader;
Json::Value dre::SubAgentMeSS::m_jsonRoot;
dre::SubAgentMeSS::AlarmConfigMap  dre::SubAgentMeSS::m_alarmConfigMap;
//Default is 10
char* instance_id = "10";


namespace dre {
const char *FaultNames[MaxProbableCause] = {
    "dummy",
    "CPU Usage crossed 80%.",
    "CPU Usage crossed 60%.",
    "CPU Usage crossed 40%.",
    "CPU usage back to normal.",
    "Memory usage crossed 80%",
    "Memory Usage crossed 60%.",
    "Memory Usage crossed 40%.",
    "Memory usage back to normal.",
    "Disk usage crossed 80%.",
    "Disk usage back to normal.",
    "Connectivity to MySQL Database Lost.",
    "Connectivity to MySQL Database Restored.",
    "A high priority process went down.",
    "A high priority process came back up.",
    "A low priority process went down.",
    "A low priority process came back up.",
    "An unplanned switch-over to standby node initiated.",
    "The unplanned switch-over to standby node was completed successfully.",
    "A planned switch-over to standby node initiated.",
    "The planned switch-over to standby node was completed successfully.",
    "A Configured interface is down.",
    "All configured interfaces are up.",
    "DRE shutdown gracefully.",
    "DRE up after graceful shutdown.",
    "Both nodes have become active in Active-Standby configuration.",
    "Active-Standby configuration restored",
    "Both nodes have become standby in Active-Standby configuration.",
    "Standby Node not available in Active-Standby configuration.",
    "Standby Node is available in Active-Standby configuration.",
    "Maximum retries for admin login reached.",
    "Message rate threshold crossed license provided.",
    "Message rate now under license provided.",
    "DPR received with cause as DO_NOT_WANT_TO_TALK_TO_YOU.",
    "DPR received with cause as Busy",
    "DPR received with cause as REBOOT",
    "License violation error.",
    "Transform plugin provisioned or unloaded."
};

SubAgentMeSS::SubAgentMeSS():
        HAMeSSComponent(SUBAGENT_PROCESS_NAME, COMP_SUB_AGENT),
        m_syslogChannel("SUBAGENT",(LOG_PID),LOG_LOCAL6)
{
    apiImpl = new AlarmAPIImpl();
    this->GetLogger().SetLogChannel(&m_syslogChannel);
}


SubAgentMeSS::~SubAgentMeSS()
{
    if(apiImpl)
        delete apiImpl;
}

void SubAgentMeSS::Initialize()
{
    HAMeSSComponent::Initialize();
    SubAgentMeSS::ParseAlarmsJson();
    /*Populate the ALarmStack map which maps between stack alarmid and the newly
      defined alarm ids */
    PopulateAlarmStackMap();
    //Populate the AlarmInfo MAp
    PopulateAlarmInfoMap();
    //Update AM that component is initialized
    UpdateComponentSelfStatus(COMPONENT_STATUS_INITIALIZED);
}

void SubAgentMeSS::Terminate()
{
    HAMeSSComponent::Terminate();
    //Terminate Sub-Agent
    agent_terminate();
}


void SubAgentMeSS::RegisterMethods()
{
}


void SubAgentMeSS::Run(void *) {
    const char* argv[] = {SUBAGENT_PROCESS_NAME, "-i", instance_id , "-l", DEFAULT_LOG_LEVEL};
    CLOG_DEBUG("SubAgentMeSS Thread Run.");
    Init(5, (const_cast<char**>(argv)));
    m_cond.signal();
    HAMeSSComponent::Run();
        //Just looping around 
    ComponentBase::Stop();
    usleep(1050000);
    _exit(0);
}


void SubAgentMeSS::PopulateAlarmInfoMap()
{
    AlarmInfo alarmInfo;

    //CPU_USAGE_HIGHER_THRESHOLD_CROSSED
    alarmInfo.SetAlarmSeverity(critical);
    alarmInfo.SetAlarmProbableCause(cpuhigherthresholdcrossed);
    alarmInfo.SetAlarmType(systemResourcesAlarm);
    alarmInfo.SetFaultName(FaultNames[cpuhigherthresholdcrossed]);
    alarmInfo.SetAlarmId(CPU_USAGE_HIGHER_THRESHOLD_CROSSED_STR);
    m_alarmMap[CPU_USAGE_HIGHER_THRESHOLD_CROSSED_STR] = alarmInfo;

    //CPU_USAGE_SECOND_THRESHOLD_CROSSED
    alarmInfo.SetAlarmSeverity(major);
    alarmInfo.SetAlarmProbableCause(cpusecondlevelthresholdcrossed);
    alarmInfo.SetAlarmType(systemResourcesAlarm);
    alarmInfo.SetFaultName(FaultNames[cpusecondlevelthresholdcrossed]);
    alarmInfo.SetAlarmId(CPU_USAGE_SECOND_THRESHOLD_CROSSED_STR);
    m_alarmMap[CPU_USAGE_SECOND_THRESHOLD_CROSSED_STR] = alarmInfo;

    ////CPU_USAGE_MINIMUM_THRESHOLD_CROSSED
    alarmInfo.SetAlarmSeverity(warning);
    alarmInfo.SetAlarmProbableCause(cpuminimumthresholdcrossed);
    alarmInfo.SetAlarmType(systemResourcesAlarm);
    alarmInfo.SetFaultName(FaultNames[cpuminimumthresholdcrossed]);
    alarmInfo.SetAlarmId(CPU_USAGE_MINIMUM_THRESHOLD_CROSSED_STR);
    m_alarmMap[CPU_USAGE_MINIMUM_THRESHOLD_CROSSED_STR] = alarmInfo;

    //CPU_USAGE_NORMAL
    alarmInfo.SetAlarmSeverity(cleared);
    alarmInfo.SetAlarmProbableCause(cpuusagebacktonormal);
    alarmInfo.SetAlarmType(systemResourcesAlarm);
    alarmInfo.SetFaultName(FaultNames[cpuusagebacktonormal]);
    alarmInfo.SetAlarmId(CPU_USAGE_NORMAL_STR);
    m_alarmMap[CPU_USAGE_NORMAL_STR] = alarmInfo;


    //MEM_USAGE_HIGHER_THRESHOLD_CROSSED
    alarmInfo.SetAlarmSeverity(critical);
    alarmInfo.SetAlarmProbableCause(memoryhigherthresholdcrossed);
    alarmInfo.SetAlarmType(systemResourcesAlarm);
    alarmInfo.SetFaultName(FaultNames[memoryhigherthresholdcrossed]);
    alarmInfo.SetAlarmId(MEM_USAGE_HIGHER_THRESHOLD_CROSSED_STR);
    m_alarmMap[MEM_USAGE_HIGHER_THRESHOLD_CROSSED_STR] = alarmInfo;

    //MEM_USAGE_SECOND_THRESHOLD_CROSSED
    alarmInfo.SetAlarmSeverity(major);
    alarmInfo.SetAlarmProbableCause(memorysecondlevelthresholdcrossed);
    alarmInfo.SetAlarmType(systemResourcesAlarm);
    alarmInfo.SetFaultName(FaultNames[memorysecondlevelthresholdcrossed]);
    alarmInfo.SetAlarmId(MEM_USAGE_SECOND_THRESHOLD_CROSSED_STR);
    m_alarmMap[MEM_USAGE_SECOND_THRESHOLD_CROSSED_STR] = alarmInfo;

    //MEM_USAGE_MINIMUM_THRESHOLD_CROSSED
    alarmInfo.SetAlarmSeverity(warning);
    alarmInfo.SetAlarmProbableCause(memoryminimumthresholdcrossed);
    alarmInfo.SetAlarmType(systemResourcesAlarm);
    alarmInfo.SetFaultName(FaultNames[memoryminimumthresholdcrossed]);
    alarmInfo.SetAlarmId(MEM_USAGE_MINIMUM_THRESHOLD_CROSSED_STR);
    m_alarmMap[MEM_USAGE_MINIMUM_THRESHOLD_CROSSED_STR] = alarmInfo;

    //MEM_USAGE_NORMAL
    alarmInfo.SetAlarmSeverity(cleared);
    alarmInfo.SetAlarmProbableCause(memoryusagebacktonormal);
    alarmInfo.SetAlarmType(systemResourcesAlarm);
    alarmInfo.SetFaultName(FaultNames[memoryusagebacktonormal]);
    alarmInfo.SetAlarmId(MEM_USAGE_NORMAL_STR);
    m_alarmMap[MEM_USAGE_NORMAL_STR] = alarmInfo;

    //DISK_USAGE_HIGHER_THRESHOLD_CROSSED
    alarmInfo.SetAlarmSeverity(critical);
    alarmInfo.SetAlarmProbableCause(diskhigherthresholdcrossed);
    alarmInfo.SetAlarmType(systemResourcesAlarm);
    alarmInfo.SetFaultName(FaultNames[diskhigherthresholdcrossed]);
    alarmInfo.SetAlarmId(DISK_USAGE_HIGHER_THRESHOLD_CROSSED_STR);
    m_alarmMap[DISK_USAGE_HIGHER_THRESHOLD_CROSSED_STR] = alarmInfo;

    //DISK_USAGE_NORMAL
    alarmInfo.SetAlarmSeverity(cleared);
    alarmInfo.SetAlarmProbableCause(diskusagebacktonormal);
    alarmInfo.SetAlarmType(systemResourcesAlarm);
    alarmInfo.SetFaultName(FaultNames[diskusagebacktonormal]);
    alarmInfo.SetAlarmId(DISK_USAGE_NORMAL_STR);
    m_alarmMap[DISK_USAGE_NORMAL_STR] = alarmInfo;

    //MYSQL_CONNECTIVITY_LOST
    alarmInfo.SetAlarmSeverity(critical);
    alarmInfo.SetAlarmProbableCause(mysqlConnectivityLost);
    alarmInfo.SetAlarmType(connectivityAlarm);
    alarmInfo.SetFaultName(FaultNames[mysqlConnectivityLost]);
    alarmInfo.SetAlarmId(MYSQL_CONNECTIVITY_LOST_STR);
    m_alarmMap[MYSQL_CONNECTIVITY_LOST_STR] = alarmInfo;


    //MYSQL_CONNECTIVITY_RESTORED
    alarmInfo.SetAlarmSeverity(cleared);
    alarmInfo.SetAlarmProbableCause(mysqlConnectivityRestored);
    alarmInfo.SetAlarmType(connectivityAlarm);
    alarmInfo.SetFaultName(FaultNames[mysqlConnectivityRestored]);
    alarmInfo.SetAlarmId(MYSQL_CONNECTIVITY_RESTORED_STR);
    m_alarmMap[MYSQL_CONNECTIVITY_RESTORED_STR] = alarmInfo;

    //HIGH_PRIORITY_PROC_DOWN
    alarmInfo.SetAlarmSeverity(critical);
    alarmInfo.SetAlarmProbableCause(highpriorityProcessDown);
    alarmInfo.SetAlarmType(processStatusAlarm);
    alarmInfo.SetFaultName(FaultNames[highpriorityProcessDown]);
    alarmInfo.SetAlarmId(HIGH_PRIORITY_PROC_DOWN_STR);
    m_alarmMap[HIGH_PRIORITY_PROC_DOWN_STR] = alarmInfo;


    //HIGH_PRIORITY_PROC_UP
    alarmInfo.SetAlarmSeverity(cleared);
    alarmInfo.SetAlarmProbableCause(highpriorityProcessUp);
    alarmInfo.SetAlarmType(processStatusAlarm);
    alarmInfo.SetFaultName(FaultNames[highpriorityProcessUp]);
    alarmInfo.SetAlarmId(HIGH_PRIORITY_PROC_UP_STR);
    m_alarmMap[HIGH_PRIORITY_PROC_UP_STR] = alarmInfo;

    //LOW_PRIORITY_PROC_DOWN
    alarmInfo.SetAlarmSeverity(major);
    alarmInfo.SetAlarmProbableCause(lowpriorityProcessDown);
    alarmInfo.SetAlarmType(processStatusAlarm);
    alarmInfo.SetFaultName(FaultNames[lowpriorityProcessDown]);
    alarmInfo.SetAlarmId(LOW_PRIORITY_PROC_DOWN_STR);
    m_alarmMap[LOW_PRIORITY_PROC_DOWN_STR] = alarmInfo;


    //LOW_PRIORITY_PROC_UP
    alarmInfo.SetAlarmSeverity(cleared);
    alarmInfo.SetAlarmProbableCause(lowpriorityProcessUp);
    alarmInfo.SetAlarmType(processStatusAlarm);
    alarmInfo.SetFaultName(FaultNames[lowpriorityProcessUp]);
    alarmInfo.SetAlarmId(LOW_PRIORITY_PROC_UP_STR);
    m_alarmMap[LOW_PRIORITY_PROC_UP_STR] = alarmInfo;

    //UNPLANNED_SWITCHOVER_TO_STANDBY_INITIATED
    alarmInfo.SetAlarmSeverity(critical);
    alarmInfo.SetAlarmProbableCause(unplannedswitchovertostandby);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[unplannedswitchovertostandby]);
    alarmInfo.SetAlarmId(UNPLANNED_SWITCHOVER_TO_STANDBY_INITIATED_STR);
    m_alarmMap[UNPLANNED_SWITCHOVER_TO_STANDBY_INITIATED_STR] = alarmInfo;


    //UNPLANNED_SWITCHOVER_TO_STANDBY_SUCCESS
    alarmInfo.SetAlarmSeverity(cleared);
    alarmInfo.SetAlarmProbableCause(unplannedswitchovercomplete);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[unplannedswitchovercomplete]);
    alarmInfo.SetAlarmId(UNPLANNED_SWITCHOVER_TO_STANDBY_SUCCESS_STR);
    m_alarmMap[UNPLANNED_SWITCHOVER_TO_STANDBY_SUCCESS_STR] = alarmInfo;

    //PLANNED_SWITCHOVER_TO_STANDBY_INITIATED
    alarmInfo.SetAlarmSeverity(info);
    alarmInfo.SetAlarmProbableCause(plannedswitchoverinitiated);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[plannedswitchoverinitiated]);
    alarmInfo.SetAlarmId(PLANNED_SWITCHOVER_TO_STANDBY_INITIATED_STR);
    m_alarmMap[PLANNED_SWITCHOVER_TO_STANDBY_INITIATED_STR] = alarmInfo;


    //PLANNED_SWITCHOVER_TO_STANDBY_SUCCESS
    alarmInfo.SetAlarmSeverity(cleared);
    alarmInfo.SetAlarmProbableCause(plannedswitchovercomplete);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[plannedswitchovercomplete]);
    alarmInfo.SetAlarmId(PLANNED_SWITCHOVER_TO_STANDBY_SUCCESS_STR);
    m_alarmMap[PLANNED_SWITCHOVER_TO_STANDBY_SUCCESS_STR] = alarmInfo;

    //BOTH_ACTIVE_IN_ACTIVE_STANDBY_MODE
    alarmInfo.SetAlarmSeverity(critical);
    alarmInfo.SetAlarmProbableCause(bothnodesactiveinactivestandbyconfig);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[bothnodesactiveinactivestandbyconfig]);
    alarmInfo.SetAlarmId(BOTH_ACTIVE_IN_ACTIVE_STANDBY_MODE_STR);
    m_alarmMap[BOTH_ACTIVE_IN_ACTIVE_STANDBY_MODE_STR] = alarmInfo;


    //ACTIVE_STANDBY_RESTORED
    alarmInfo.SetAlarmSeverity(cleared);
    alarmInfo.SetAlarmProbableCause(activestandbyconfigrestored);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[activestandbyconfigrestored]);
    alarmInfo.SetAlarmId(ACTIVE_STANDBY_RESTORED_STR);
    m_alarmMap[ACTIVE_STANDBY_RESTORED_STR] = alarmInfo;

    //BOTH_STANDBY_IN_ACTIVE_STANDBY_MODE
    alarmInfo.SetAlarmSeverity(critical);
    alarmInfo.SetAlarmProbableCause(bothnodesstandbyinactivestandbyconfig);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[bothnodesstandbyinactivestandbyconfig]);
    alarmInfo.SetAlarmId(BOTH_STANDBY_IN_ACTIVE_STANDBY_MODE_STR);
    m_alarmMap[BOTH_STANDBY_IN_ACTIVE_STANDBY_MODE_STR] = alarmInfo;

    //STANDBY_NOT_AVAILABLE
    alarmInfo.SetAlarmSeverity(major);
    alarmInfo.SetAlarmProbableCause(standbynodenotavailable);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[standbynodenotavailable]);
    alarmInfo.SetAlarmId(STANDBY_NOT_AVAILABLE_STR);
    m_alarmMap[STANDBY_NOT_AVAILABLE_STR] = alarmInfo;

    //STANDBY_AVAILABLE
    alarmInfo.SetAlarmSeverity(cleared);
    alarmInfo.SetAlarmProbableCause(standbynodeavailable);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[standbynodeavailable]);
    alarmInfo.SetAlarmId(STANDBY_AVAILABLE_STR);
    m_alarmMap[STANDBY_AVAILABLE_STR] = alarmInfo;

    //DRE_GRACEFUL_SHUTDOWN
    alarmInfo.SetAlarmSeverity(critical);
    alarmInfo.SetAlarmProbableCause(dregracefulshutdown);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[dregracefulshutdown]);
    alarmInfo.SetAlarmId(DRE_GRACEFUL_SHUTDOWN_STR);
    m_alarmMap[DRE_GRACEFUL_SHUTDOWN_STR] = alarmInfo;

    //DRE_UP_AFTER_SHUTDOWN
    alarmInfo.SetAlarmSeverity(cleared);
    alarmInfo.SetAlarmProbableCause(dreup);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[dreup]);
    alarmInfo.SetAlarmId(DRE_UP_AFTER_SHUTDOWN_STR);
    m_alarmMap[DRE_UP_AFTER_SHUTDOWN_STR] = alarmInfo;

    //MAX_ADMIN_LOGIN_RETRY
    alarmInfo.SetAlarmSeverity(critical);
    alarmInfo.SetAlarmProbableCause(admininvalidcredentialscountreached);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[admininvalidcredentialscountreached]);
    alarmInfo.SetAlarmId(MAX_ADMIN_LOGIN_RETRY_STR);
    m_alarmMap[MAX_ADMIN_LOGIN_RETRY_STR] = alarmInfo;

    //CONFIGURED_ETH_INTERFACE_DOWN
    alarmInfo.SetAlarmSeverity(critical);
    alarmInfo.SetAlarmProbableCause(configuredintefacedown);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[configuredintefacedown]);
    alarmInfo.SetAlarmId(CONFIGURED_ETH_INTERFACE_DOWN_STR);
    m_alarmMap[CONFIGURED_ETH_INTERFACE_DOWN_STR] = alarmInfo;

    //CONFIGURED_ETH_INTERFACE_UP
    alarmInfo.SetAlarmSeverity(cleared);
    alarmInfo.SetAlarmProbableCause(configuredintefaceup);
    alarmInfo.SetAlarmType(availabilityAlarm);
    alarmInfo.SetFaultName(FaultNames[configuredintefaceup]);
    alarmInfo.SetAlarmId(CONFIGURED_ETH_INTERFACE_UP_STR);
    m_alarmMap[CONFIGURED_ETH_INTERFACE_UP_STR] = alarmInfo;


    //MESSAGE_RATE_THRESHOLD_CROSSED_LICENSE_PROVIDED
    alarmInfo.SetAlarmSeverity(critical);
    alarmInfo.SetAlarmProbableCause(messageratethresholdcrossedlicenseprovided);
    alarmInfo.SetAlarmType(systemResourcesAlarm);
    alarmInfo.SetFaultName(FaultNames[messageratethresholdcrossedlicenseprovided]);
    alarmInfo.SetAlarmId(MESSAGE_RATE_THRESHOLD_CROSSED_LICENSE_PROVIDED_STR);
    m_alarmMap[MESSAGE_RATE_THRESHOLD_CROSSED_LICENSE_PROVIDED_STR] = alarmInfo;

    //MESSAGE_RATE_NOW_UNDER_LICENSE_PROVIDED
    alarmInfo.SetAlarmSeverity(cleared);
    alarmInfo.SetAlarmProbableCause(messageratenowunderlicenseprovided);
    alarmInfo.SetAlarmType(systemResourcesAlarm);
    alarmInfo.SetFaultName(FaultNames[messageratenowunderlicenseprovided]);
    alarmInfo.SetAlarmId(MESSAGE_RATE_NOW_UNDER_LICENSE_PROVIDED_STR);
    m_alarmMap[MESSAGE_RATE_NOW_UNDER_LICENSE_PROVIDED_STR] = alarmInfo;

    //TRANSFORM_PLUGIN_PROVISIONED_OR_UNLOADED
    alarmInfo.SetAlarmSeverity(info);
    alarmInfo.SetAlarmProbableCause(dictionarytransformpluginprovisonorunload);
    alarmInfo.SetAlarmType(systemResourcesAlarm);
    alarmInfo.SetFaultName(FaultNames[dictionarytransformpluginprovisonorunload]);
    alarmInfo.SetAlarmId(TRANSFORM_PLUGIN_PROVISIONED_OR_UNLOADED_STR);
    m_alarmMap[TRANSFORM_PLUGIN_PROVISIONED_OR_UNLOADED_STR] = alarmInfo;

    //DPR_WITH_CAUSE_DO_NOT_WANT_TO_TALK_TO_YOU
    alarmInfo.SetAlarmSeverity(info);
    alarmInfo.SetAlarmProbableCause(dprreceivedwithcausedonotwanttotalktoyou);
    alarmInfo.SetAlarmType(connectivityAlarm);
    alarmInfo.SetFaultName(FaultNames[dprreceivedwithcausedonotwanttotalktoyou]);
    alarmInfo.SetAlarmId(DPR_WITH_CAUSE_DO_NOT_WANT_TO_TALK_TO_YOU_STR);
    m_alarmMap[DPR_WITH_CAUSE_DO_NOT_WANT_TO_TALK_TO_YOU_STR] = alarmInfo;

    //DPR_WITH_CAUSE_BUSY
    alarmInfo.SetAlarmSeverity(info);
    alarmInfo.SetAlarmProbableCause(dprreceivedwithcausebusy);
    alarmInfo.SetAlarmType(connectivityAlarm);
    alarmInfo.SetFaultName(FaultNames[dprreceivedwithcausebusy]);
    alarmInfo.SetAlarmId(DPR_WITH_CAUSE_BUSY_STR);
    m_alarmMap[DPR_WITH_CAUSE_BUSY_STR] = alarmInfo;

    //DPR_WITH_CAUSE_REBOOT
    alarmInfo.SetAlarmSeverity(info);
    alarmInfo.SetAlarmProbableCause(dprreceivedwithcausereboot);
    alarmInfo.SetAlarmType(connectivityAlarm);
    alarmInfo.SetFaultName(FaultNames[dprreceivedwithcausereboot]);
    alarmInfo.SetAlarmId(DPR_WITH_CAUSE_REBOOT_STR);
    m_alarmMap[DPR_WITH_CAUSE_REBOOT_STR] = alarmInfo;

    //DRE_LICENSE_VIOLATION_ERROR
    alarmInfo.SetAlarmSeverity(critical);
    alarmInfo.SetAlarmProbableCause(licenseviolationerror);
    alarmInfo.SetAlarmType(processStatusAlarm);
    alarmInfo.SetFaultName(FaultNames[licenseviolationerror]);
    alarmInfo.SetAlarmId(DRE_LICENSE_VIOLATION_ERROR_STR);
    m_alarmMap[DRE_LICENSE_VIOLATION_ERROR_STR] = alarmInfo;
}

AlarmInfo* SubAgentMeSS::fetchAlarmInfo(std::string alarmId)
{
    AlarmInfoMap::iterator it = m_alarmMap.find(alarmId);
    if(it!=m_alarmMap.end())
    {
        CLOG_DEBUG("Found Alarm with Alarm id %s",alarmId.c_str());
        return &(it->second);
    }
    else
    {
        CLOG_ERROR("Alarm with Alarm id <%s> not found",alarmId.c_str());
        return NULL;
    }
}



int SubAgentMeSS::ParseAlarmsJson()
{
    CLOG_DEBUG("Parsing alarm.json file...");
    char *iwfRoot = getenv("IWF_ROOT");
    AlarmConfig alarmConfigItem;
    if(iwfRoot == NULL )
    {
	    CLOG_ERROR("Environment variable IWF_ROOT not exported");
  	    exit(1);
    }
    std::string jsonFile(iwfRoot);
    jsonFile.append("/config/alarm.json");
    std::ifstream doc(jsonFile);
    if(!(m_jsonConfigFileReader.parse(doc,m_jsonRoot)))
    {
        CLOG_CRITICAL("Failed to parse alarm.json configuration %s\n"
            ,m_jsonConfigFileReader.getFormattedErrorMessages().c_str());

	exit(1);
    }


    const Json::Value alarmConfig = m_jsonRoot["alarms-config"];
    std::string alarmIdVal;
    CLOG_DEBUG("Number of alarms in json=%d",alarmConfig.size());
    for( int i=0; i< (int)alarmConfig.size(); i++)
    {
        alarmIdVal = alarmConfig[i]["alarm-id"].asString();

        alarmConfigItem.alarmString = alarmConfig[i]["alarm-string"].asString();
        m_alarmConfigMap[alarmIdVal]=alarmConfigItem;
        CLOG_DEBUG("Alarm-Id= %s \n Alarm-string= %s", alarmIdVal.c_str(), alarmConfigItem.alarmString.c_str());
    }

    const Json::Value logConfig = m_jsonRoot["Logging"];
    unsigned int logLevel = logConfig[0]["logLevel"].asInt();

    //Setting the log level
    eAccelero::ComponentBase::Instance().GetLogger().SetLevel((eAccelero::Logger::Level)logLevel);

    return ITS_SUCCESS;
}



void SubAgentMeSS::FillParamsInAlarmString( AlarmReq *req, std::string *alarmString)
{
   string temp;
   int index = 0;
   size_t found;
   int pos = 0;
   for(;index < req->variables_size() ; index ++)
   {
       found = alarmString->find_first_of("{");
       if(found ==string::npos)
       {
           //Couldn't find any more vars to replace.
           break;
       }
       //TODO: For now only single digit variable indexes are suported.
            pos = atoi(&(*alarmString)[found+1]);
            if(pos < req->variables_size())
            {
               alarmString->replace(found,3,req->variables(pos).c_str(),req->variables(pos).length());
            }
            else
            {
                //If variable is not passed from backend then replace with blank string.
               string dummy("");
               alarmString->replace(found,3,dummy.c_str(),dummy.length());
            }
   }
}



std::string SubAgentMeSS::FormAlarmString( AlarmReq *req ,std::string &alarmId)
{
  // const Json::Value alarmConfig = m_jsonRoot["Alarm-config"];
    AlarmConfigMap::iterator it = m_alarmConfigMap.find(alarmId);
    if( it == m_alarmConfigMap.end() )
    {
        CLOG_ERROR("AlaramIdString not found %s",alarmId.c_str());
        return "";
    }

    string alarmString=it->second.alarmString;

    //fill in the parameters for the alarm string
    SubAgentMeSS::FillParamsInAlarmString( req, &alarmString );
    CLOG_DEBUG("Alarm string = %s", alarmString.c_str());
    return alarmString;

}

void SubAgentMeSS::ConvertAlarmIdToString(uint32_t id ,std::string &alarmIdString )
{
    std::string s;
    std::stringstream convert;
    int prefixZeros=0;
    int digits=0;
    uint32_t num=id;
    while( num > 0 )
    {
	digits++;
	num /=10;
    }
    prefixZeros=3-digits;

    for( int i=0; i< prefixZeros ; i++ )
    {
	alarmIdString.append("0");
    }
    if( id != 0 )
    {
        convert << id;
        s = convert.str();
        alarmIdString.append(s);
    }

}

void SubAgentMeSS::FormAlarmId( uint32_t componentId,uint32_t subComponentId,
		  uint32_t subComponentAlarmId , std::string &alarmIdString)
{

    alarmIdString="";
    ConvertAlarmIdToString(componentId, alarmIdString);
    ConvertAlarmIdToString(subComponentId, alarmIdString);
    ConvertAlarmIdToString(subComponentAlarmId, alarmIdString);
    CLOG_DEBUG("AlarmIdString formed=%s",alarmIdString.c_str());


}

void SubAgentMeSS::PopulateAlarmStackMap()
{
    m_alarmStackMap[15000] = CER_OR_CEA_EXCHANGE_FAILURE;
    m_alarmStackMap[7002]  = SCTP_OR_TCP_CONNECTION_FAILURE;
    m_alarmStackMap[7001]  = SCTP_OR_TCP_CONNECTION_ESTABLISHED;
    m_alarmStackMap[15001] = SCTP_OR_TCP_CONNECTION_FAILURE;
    m_alarmStackMap[15002] = SCTP_OR_TCP_CONNECTION_ESTABLISHED;
    m_alarmStackMap[15003] = TCP_CONNECTION_FAIL_AND_FAILOVER_TO_PEER;
    m_alarmStackMap[15004] = TCP_CONNECTION_ESTABLISH_AND_FAILBACK_TO_PRIMARY;
    m_alarmStackMap[15005] = CEA_RECEIVED_WITH_WRONG_RESULT_CODE;
    m_alarmStackMap[15006] = MISMATCH_ORIGINHOST_OR_ORIGINREALM_WITH_PEERTABLES;
    m_alarmStackMap[15007] = DWA_RECEIVED_WITH_WRONG_RESULT_CODE;
    m_alarmStackMap[15008] = DPA_RECEIVED_WITH_INVALID_RESLUT_CODE;
    m_alarmStackMap[15010] = TRANSPORT_CONNECTION_CLOSED_WITH_PEER;
    m_alarmStackMap[15100] = RECIEVE_MSG_FAILURE_FROM_PEER;
    m_alarmStackMap[15101] = FAILED_TO_TRANSMIT_MSG_TO_PEER;
    m_alarmStackMap[15104] = MISMATCH_DESTHOST_OR_DESTREALM_WITH_PEERTABLES;
    m_alarmStackMap[15200] = DIAMETER_STACK_FAILED_TO_INITIALIZE;
    m_alarmStackMap[15201] = DIAMETER_STACK_TERMINATION;
    m_alarmStackMap[15251] = DIAMETER_STACK_PEER_DELETED_OR_DISABLED;
    m_alarmStackMap[15305] = QUEUE_FULL;
    m_alarmStackMap[15306] = PEER_TPS_EXCEEDED_LEVEL1;
    m_alarmStackMap[15307] = PEER_TPS_ABATED_LEVEL1;
    m_alarmStackMap[15308] = PEER_TPS_EXCEEDED_LEVEL2;
    m_alarmStackMap[15309] = PEER_TPS_ABATED_LEVEL2;
    m_alarmStackMap[15310] = PEER_TPS_EXCEEDED_LEVEL3;
    m_alarmStackMap[15311] = PEER_TPS_ABATED_LEVEL3;
    m_alarmStackMap[15312] = OVERALL_TPS_EXCEEDED_LEVEL1;
    m_alarmStackMap[15313] = OVERALL_TPS_ABATED_LEVEL1;
    m_alarmStackMap[15314] = OVERALL_TPS_EXCEEDED_LEVEL2;
    m_alarmStackMap[15315] = OVERALL_TPS_ABATED_LEVEL2;
    m_alarmStackMap[15316] = OVERALL_TPS_EXCEEDED_LEVEL3;
    m_alarmStackMap[15317] = OVERALL_TPS_ABATED_LEVEL3;
    m_alarmStackMap[15318] = SESSION_TABLE_EXCEEDED_LEVEL1;
    m_alarmStackMap[15319] = SESSION_TABLE_ABATED_LEVEL1;
    m_alarmStackMap[15320] = SESSION_TABLE_EXCEEDED_LEVEL2;
    m_alarmStackMap[15321] = SESSION_TABLE_ABATED_LEVEL2;
    m_alarmStackMap[15322] = ROUTER_QUEUE_EXCEEDED_LEVEL1;
    m_alarmStackMap[15323] = ROUTER_QUEUE_ABATED_LEVEL1;
    m_alarmStackMap[15324] = ROUTER_QUEUE_EXCEEDED_LEVEL2;
    m_alarmStackMap[15325] = ROUTER_QUEUE_ABATED_LEVEL2;
    m_alarmStackMap[15326] = ROUTER_QUEUE_EXCEEDED_LEVEL3;
    m_alarmStackMap[15327] = ROUTER_QUEUE_ABATED_LEVEL3;
    m_alarmStackMap[15328] = PEER_DISCONNECTED_DUE_TO_FLOODING;
    m_alarmStackMap[15400] = VERSION_MISMATCH;
}

int SubAgentMeSS::MapStackAlarm(uint32_t alarmId, char * alarmIdString)
{
    AlarmStackMap::iterator it = m_alarmStackMap.find(alarmId);
    if( it != m_alarmStackMap.end() )
    {
	strcpy(alarmIdString,it->second.c_str());
	return ITS_SUCCESS;
    }
    else
    {
        CLOG_ERROR("AlarmId not found = %s.MapStackAlarm failed",alarmIdString);
        return -1;
    }
}

int SubAgentMeSS::ProcessAvailabilityStatusResetPreFunc(uint16_t newInstanceId)
{
    return 0;
}
int SubAgentMeSS::ProcessAvailabilityStatusResetPostFunc()
{
    return 0;
}
int SubAgentMeSS::ProcessComponentStatusUpdate(uint16_t componentId, eAccelero::HAComponentStatus newStatus)
{
    return 0;
}



}
