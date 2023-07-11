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
#include "CMgrAlarms.h"
#include <RandomNumber.h>

#define CMGR_PROCESS_NAME "cmgr"
using namespace std;


ConfigManagerAlarms::ConfigManagerAlarms(uint16_t instanceId,uint32_t componentId) {
    m_alarmapi = new CMAPIAlarms();
    m_alarmapi->InitializeLibrary();
    m_mysqlAlreadyRaise = 0;
    m_componentId = componentId-COMPONENT_ID_START;
    currentInstanceId = instanceId;
    m_alarmKey = 0;
    m_duringRestart = false;

    int returnCode = gethostname(m_hostName,MAX_HOST_NAME_LENGTH);

    if(returnCode != 0)
    {
        DLOG_ERROR("Failed to Fetch Hostname.errno =",errno);
    }
    CLOG_DEBUG("Entered ConfigManagerAlarms::ConfigManagerAlarms()");
}


ConfigManagerAlarms::~ConfigManagerAlarms() {
    if(m_alarmapi)
        delete m_alarmapi;
}

void ConfigManagerAlarms::UpdateDestInstanceId(uint16_t instanceId)
{
    CLOG_INFO("Modifying destInstance Id for Alarms to %d",instanceId);
    currentInstanceId = instanceId;
}

void ConfigManagerAlarms::RaiseAlarm(uint32_t subComponentId,uint32_t subComponentAlarmId,
                std::string addText, std::vector<std::string> &variables,uint32_t alarmKey) {
    CLOG_DEBUG("> %s\n",__FUNCTION__);
    AlarmReq Req;
    AlarmResp Resp;
    Req.set_componentid(m_componentId);
    Req.set_subcomponentid(subComponentId);
    Req.set_subcomponentalarmid(subComponentAlarmId);
    Req.set_addtext(addText);
    for ( unsigned int i=0; i< variables.size(); i++ )
    {
        Req.add_variables(variables[i]);
    }

    if(alarmKey)
    {
        std::stringstream keyString;
        keyString <<m_hostName<<":"<<CMGR_PROCESS_NAME<<":"<<alarmKey ;
        Req.set_alarmkey(keyString.str());
    }

    if(m_alarmapi->RaiseAlarm(currentInstanceId,Req,Resp) == CMAPI_SUCCESS)
    {
        CLOG_DEBUG("Succesfully Sent an alarm with alarm Id %d%d and additional text %s \
                using CMAPI",subComponentId,subComponentAlarmId,addText.c_str());
    } else {
        CLOG_ERROR("Failed to raise an alarm using CMAPI, AlarmId:%d%d,AddText:%s",subComponentId,subComponentAlarmId,addText.c_str());
    }
    CLOG_DEBUG("< %s\n",__FUNCTION__);
}

void ConfigManagerAlarms::RaiseReplicationNotInSyncAlarm(){
    int subComponentId = CONFIGMGR_MYSQL_SUB_COMP;
    int alarmId = MYSQL_REPLICATION_NOT_IN_SYNC;
    CLOG_DEBUG("> %s\n",__FUNCTION__);

    if(!m_replicationNotInSyncKey)
    {
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_MYSQL_REPLICATION_NOT_IN_SYNC);
        m_replicationNotInSyncKey = m_randomNumberObj.getRandomNumber();
        RaiseAlarm(subComponentId,alarmId,alarmText,variables,m_replicationNotInSyncKey);
    }

    CLOG_DEBUG("< %s\n",__FUNCTION__);
}

void ConfigManagerAlarms::RaiseReplicationDownAlarm(){
    int subComponentId = CONFIGMGR_MYSQL_SUB_COMP;
    int alarmId = MYSQL_REPLICATION_FAILED;
    CLOG_DEBUG("> %s\n",__FUNCTION__);

    if(!m_replicationAlarmKey)
    {
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_MYSQL_REPLICATION_FAILED);
        m_replicationAlarmKey = m_randomNumberObj.getRandomNumber();
        RaiseAlarm(subComponentId,alarmId,alarmText,variables,m_replicationAlarmKey);
    }

    CLOG_DEBUG("< %s\n",__FUNCTION__);
}

void ConfigManagerAlarms::RaiseReplicationUpAlarm(){
    int subComponentId = CONFIGMGR_MYSQL_SUB_COMP;
    int alarmId = MYSQL_REPLICATION_RESTORED;
    CLOG_DEBUG("> %s\n",__FUNCTION__);
    //m_duringRestart true means cmgr or all dre process restarted.
    // so clear alarm blindly.
    if(m_replicationAlarmKey)
    {
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_MYSQL_CONNECTIVITY_RESTORED);
        RaiseAlarm(subComponentId,alarmId,alarmText,variables,m_replicationAlarmKey);
        m_replicationAlarmKey= 0;
    }

    CLOG_DEBUG("< %s\n",__FUNCTION__);
}

void ConfigManagerAlarms::RaiseMysqlDownAlarm(){
    int subComponentId = CONFIGMGR_MYSQL_SUB_COMP;
    int alarmId = MYSQL_CONNECTIVITY_LOST;
    CLOG_DEBUG("> %s\n",__FUNCTION__);

    if(!m_mysqlAlreadyRaise)
    {
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_MYSQL_CONNECTIVITY_LOST);
        m_alarmKey = m_randomNumberObj.getRandomNumber();
        RaiseAlarm(subComponentId,alarmId,alarmText,variables,m_alarmKey);
        m_mysqlAlreadyRaise = 1;
    }

    CLOG_DEBUG("< %s\n",__FUNCTION__);
}

void ConfigManagerAlarms::RaiseMysqlUpAlarm(){
    int subComponentId = CONFIGMGR_MYSQL_SUB_COMP;
    int alarmId = MYSQL_CONNECTIVITY_RESTORED;
    CLOG_DEBUG("> %s\n",__FUNCTION__);
    //m_duringRestart true means cmgr or all dre process restarted.
    // so clear alarm blindly.
    if(m_mysqlAlreadyRaise || m_duringRestart)
    {
        m_duringRestart = false;
        std::vector<std::string> variables;
        std::string alarmText(ALARM_DEF_TEXT_MYSQL_CONNECTIVITY_RESTORED);
        RaiseAlarm(subComponentId,alarmId,alarmText,variables,m_alarmKey);
        m_mysqlAlreadyRaise = 0;
    }

    CLOG_DEBUG("< %s\n",__FUNCTION__);
}

void ConfigManagerAlarms::RaiseConfigRetryAlarm(){
    int subComponentId = CONFIGMGR_SUB_COMP;
    int alarmId = COMP_CONFIG_RETRY;
    CLOG_DEBUG("> %s\n",__FUNCTION__);
    std::vector<std::string> variables;
    std::string alarmText(ALARM_DEF_TEXT_COMP_CONFIG_RETRY);
    uint32_t alarmKey = m_randomNumberObj.getRandomNumber();
    RaiseAlarm(subComponentId,alarmId,alarmText,variables,alarmKey);
    CLOG_DEBUG("< %s\n",__FUNCTION__);
}

void ConfigManagerAlarms::CleanupProcessName(std::string* processDetails)
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

