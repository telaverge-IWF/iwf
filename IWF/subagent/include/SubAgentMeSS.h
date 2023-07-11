/*********************************-*-H-*-************************************
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

#ifndef _SUBAGENT_MESS_H_
#define _SUBAGENT_MESS_H_

#include <stdint.h>
#include "Sync.h"
#include "HAMeSSComponent.h"
#include "ComponentDefines.h"
#include "Alarms.h"
#include "AlarmId.h"
#include "AlarmInfo.h"
#include <json.h>

using namespace eAccelero;

namespace dre {

#define SUBAGENT_PROCESS_NAME "SUBAGENT"
#define SUBAGENT_INSTANCE_ID "10"
#define DEFAULT_LOG_LEVEL "3"

typedef struct AlarmCfg
{
    std::string alarmString;

}AlarmConfig;

class SubAgentMeSS: public eAccelero::HAMeSSComponent, public eAccelero::Runnable{
public:
    SubAgentMeSS();
	~SubAgentMeSS(); 

	void Initialize();
	void Terminate();
    void Run(void *);
    void RegisterMethods();
    AlarmInfo* fetchAlarmInfo(std::string alarmId);
    int MapStackAlarm(uint32_t,char *);
    typedef std::map<std::string,AlarmConfig> AlarmConfigMap;
    static int ParseAlarmsJson();
    static std::string FormAlarmString( AlarmReq *req ,std::string &alarmId); 
    static void FormAlarmId( uint32_t componentId, uint32_t subComponentId, 
            uint32_t subComponentAlarmId, std::string &alarmIdString);
    //Over-riding HAMeSSComponent functions.
    int ProcessAvailabilityStatusResetPreFunc(uint16_t newInstanceId);
    int ProcessAvailabilityStatusResetPostFunc();
    int ProcessComponentStatusUpdate(uint16_t componentId, eAccelero::HAComponentStatus newStatus);
private:
    void PopulateAlarmInfoMap();
    void PopulateAlarmStackMap();
    static void FillParamsInAlarmString( AlarmReq *req, std::string *alarmString );
    static void ConvertAlarmIdToString(uint32_t id, std::string &alarmIdString );
    eAccelero::CondVar m_cond;
    typedef std::map<std::string,AlarmInfo> AlarmInfoMap;
    typedef std::map<uint32_t, std::string> AlarmStackMap;
    AlarmInfoMap m_alarmMap;
    AlarmStackMap m_alarmStackMap;
    //contains the configurable string text entries
    static AlarmConfigMap m_alarmConfigMap;
    AlarmAPIImpl *apiImpl;
    static Json::Reader m_jsonConfigFileReader;
    static Json::Value m_jsonRoot;
    SyslogChannel m_syslogChannel;
};
}

#endif
