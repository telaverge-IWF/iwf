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

#ifndef _ALARM_INFO_H_
#define _ALARM_INFO_H_

#include "string"

namespace dre {

enum AlarmProbableCause 
{
    cpuhigherthresholdcrossed = 1,
    cpusecondlevelthresholdcrossed,
    cpuminimumthresholdcrossed,
    cpuusagebacktonormal,
    memoryhigherthresholdcrossed,
    memorysecondlevelthresholdcrossed,
    memoryminimumthresholdcrossed,
    memoryusagebacktonormal,
    diskhigherthresholdcrossed,
    diskusagebacktonormal,
    mysqlConnectivityLost,
    mysqlConnectivityRestored,
    highpriorityProcessDown,
    highpriorityProcessUp,
    lowpriorityProcessDown,
    lowpriorityProcessUp,
    unplannedswitchovertostandby,
    unplannedswitchovercomplete,
    plannedswitchoverinitiated,
    plannedswitchovercomplete,
    configuredintefacedown,
    configuredintefaceup,
    dregracefulshutdown,
    dreup,
    bothnodesactiveinactivestandbyconfig,
    activestandbyconfigrestored,
    bothnodesstandbyinactivestandbyconfig,
    standbynodenotavailable,
    standbynodeavailable,
    admininvalidcredentialscountreached,
    messageratethresholdcrossedlicenseprovided,
    messageratenowunderlicenseprovided,
    dprreceivedwithcausedonotwanttotalktoyou,
    dprreceivedwithcausebusy,
    dprreceivedwithcausereboot,
    licenseviolationerror,
    dictionarytransformpluginprovisonorunload,
    MaxProbableCause
};

enum AlarmType {
    systemResourcesAlarm = 1,
    processStatusAlarm,
    connectivityAlarm,
    availabilityAlarm
};

typedef struct StackAlarm
{
    std::string alarmId;
    uint32_t stackAlarmId;
}stackAlarmInfo;

class AlarmInfo {
    public:
	void SetAlarmId(const char * alarmId)
	{
	    this->alarmId = std::string(alarmId);
	}
        std::string GetAlarmId()
	{
	    return alarmId;
	}
       
        severity GetAlarmSeverity()
        {
            return alarmSeverity;
        }

        void SetAlarmSeverity(severity sev)
        {
            this->alarmSeverity = sev;
        }
        AlarmProbableCause GetAlarmProbableCause()
        {
            return cause;
        }

        void SetAlarmProbableCause(AlarmProbableCause cause)
        {
            this->cause = cause;
        }
        AlarmType GetAlarmType()
        {
            return type;
        }
        void SetAlarmType(AlarmType type)
        {
            this->type = type;
        }

        std::string& GetFaultName()
        {
            return FaultName;
        }

        void SetFaultName(const char * fault)
        {
            this->FaultName = std::string(fault);
        }

    private: 
	std::string alarmId;
        severity alarmSeverity;
        AlarmProbableCause cause;
        AlarmType type;
        std::string FaultName;
};

} //namespace dre

#endif //_ALARM_INFO_H_
