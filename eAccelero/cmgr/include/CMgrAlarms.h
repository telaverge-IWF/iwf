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
#ifndef _CMGR_ALARMS_H_
#define _CMGR_ALARMS_H_
#include "CMAPIAlarms.h"
#include <vector>
#include <RandomNumber.h>
#define MAX_HOST_NAME_LENGTH 256

#define ALARM_DEF_TEXT_MYSQL_CONNECTIVITY_LOST\
    "Mysql Connectivity Lost."
#define ALARM_DEF_TEXT_MYSQL_CONNECTIVITY_RESTORED\
    "Mysql Connectivity Restored."
#define ALARM_DEF_TEXT_MYSQL_REPLICATION_FAILED\
    "Mysql Replication Failed, New configuration will not be replicated to standby node."
#define ALARM_DEF_TEXT_MYSQL_REPLICATION_RESTORED\
    "Mysql Replication Restored."
#define ALARM_DEF_TEXT_COMP_CONFIG_RETRY\
    "Configuration Retry."
#define ALARM_DEF_TEXT_MYSQL_REPLICATION_NOT_IN_SYNC\
    "Mysql database is not in sync, When Standby is ready please to switchover."

class ConfigManagerAlarms {

    public:
        ConfigManagerAlarms(uint16_t instanceId,uint32_t componentId);
        ~ConfigManagerAlarms();
        void RaiseAlarm(uint32_t subComponentId, uint32_t subComponentAlarmId,
                        std::string addText,std::vector<std::string> &variables,uint32_t alarmKey);
        void RaiseMysqlDownAlarm();
        void RaiseReplicationDownAlarm();
        void RaiseReplicationNotInSyncAlarm();
        void RaiseMysqlUpAlarm();
        void RaiseReplicationUpAlarm();
        void RaiseConfigRetryAlarm();
        void UpdateDestInstanceId(uint16_t instanceId);

    private:
        CMAPIAlarms* m_alarmapi;
        uint32_t m_componentId;
        uint16_t currentInstanceId;
        uint16_t m_mysqlAlreadyRaise;
        void CleanupProcessName(std::string* processDetails);
        RandomNumberGenerator m_randomNumberObj;
        uint32_t m_alarmKey;
        uint32_t m_replicationAlarmKey;
        uint32_t m_replicationNotInSyncKey;
        char m_hostName[MAX_HOST_NAME_LENGTH];
        bool m_duringRestart;


}; //class ConfigManagerAlarms


#endif
