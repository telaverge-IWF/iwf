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
#include "AlarmAPIImpl.h"
#include "AlarmId.h"
#include "AlarmInfo.h"
#include "SubAgentMeSS.h"
extern ITS_INT DIASA_PutEventOnTaskQue(ITS_EVENT *evt);

using namespace std;
using namespace eAccelero;

namespace dre {


AlarmAPIImpl::AlarmAPIImpl():Alarms()
{
}

AlarmAPIImpl::~AlarmAPIImpl()
{
}


int AlarmAPIImpl::RaiseAlarm(AlarmReq *req,AlarmResp *resp) {

    CLOG_INFO("Raise Alarm Request received.");
    CLOG_INFO("Alarm Additional Text %s",req->addtext().c_str());
    ProcessRaiseAlarm(req);

    resp->set_responseid(0);
    CLOG_INFO("<<<<Exiting RaiseAlarm.");
    return 0;

}


int AlarmAPIImpl::ProcessRaiseAlarm(AlarmReq *req)
{
    ITS_EVENT evt;
    ITS_INT ret;
    
    FormEvent(req,&evt);

    ret = DIASA_PutEventOnTaskQue(&evt);
    if(ret == ITS_SUCCESS)
    {
        CLOG_DEBUG("Posted Alarm event into task Queue successfully.");
        return ITS_SUCCESS;
    }
    else
    {
        CLOG_ERROR("Failed to put alarm event onto task queue");
        return -1;
    }
}

void AlarmAPIImpl::FormEvent(AlarmReq *req,ITS_EVENT *evt)
{
    unsigned char *alarmstr = (unsigned char*)malloc(1024);
    std::string alarmIdString;
    CLOG_INFO("CompId=%d, subCompId=%d, subCompAlarmId=%d", req->componentid(),req->subcomponentid(),req->subcomponentalarmid());
    //form alarmid using componentId, subComponentId and Subcomponent alarm id
    SubAgentMeSS::FormAlarmId(req->componentid(), req->subcomponentid(), 
			      req->subcomponentalarmid(), alarmIdString);     
    //form the request to form the alarm string according to alarm.json configuration
    std::string formattedAlarmString = SubAgentMeSS::FormAlarmString( req ,alarmIdString);    
    snprintf((char*)alarmstr,1024,"%s|DRE| | | | | |%s",alarmIdString.c_str(),formattedAlarmString.c_str());
    CLOG_INFO("Formatted Alarm String: %s",alarmstr);
    alarmstr[strlen((const char*)alarmstr)] = '\0';
    
    evt->src = ALARM_SRC_DRE; //DRE
    evt->len = strlen((const char*)alarmstr);
    evt->data = (ITS_OCTET *)malloc((evt->len) + 1);
    memcpy(evt->data,alarmstr,evt->len);
    free(alarmstr);
}

}//namespace dre
