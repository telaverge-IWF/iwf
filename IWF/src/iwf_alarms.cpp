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
#include "iwf_alarms.h"

using namespace std;


IwfAlarms::IwfAlarms(uint16_t instanceId,uint32_t componentId) {
    m_alarmapi = new CMAPIAlarms();
    m_alarmapi->InitializeLibrary();
    m_componentId = componentId-COMPONENT_ID_START;
    currentInstanceId = instanceId;
    CLOG_DEBUG("Entered IwfAlarms::IwfAlarms()");
}


IwfAlarms::~IwfAlarms() {
    if(m_alarmapi)
        delete m_alarmapi;
}

void IwfAlarms::RaiseAlarm(uint32_t subComponentId,uint32_t subComponentAlarmId, std::string addText, std::vector<std::string> &variables) {
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

    if(m_alarmapi->RaiseAlarm(currentInstanceId,Req,Resp) == CMAPI_SUCCESS)
    {
        CLOG_DEBUG("Succesfully Sent an alarm using CMAPI with componentId:%d-alarm Id:%d and additional text %s",
                subComponentId,subComponentAlarmId,addText.c_str());
    } else {
        CLOG_ERROR("Failed to raise an alarm using CMAPI, AlarmId:%d%d,AddText:%s",subComponentId,subComponentAlarmId,addText.c_str());
    }
    CLOG_DEBUG("< %s\n",__FUNCTION__);
}

void IwfAlarms::RaiseTranslatorLicenceViolationAlarm(uint32_t alarmId, std::string alarmText)
{
    int subComponentId = IWF_TRANSLATOR_SUB_COMP;
    CLOG_DEBUG("> %s\n",__FUNCTION__);
    std::vector<std::string> variables;
    RaiseAlarm(subComponentId,alarmId,alarmText,variables);
}
