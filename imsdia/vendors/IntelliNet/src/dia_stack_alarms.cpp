/*********************************-*-CPP-*-**********************************
 **                                                                          *
 **             Copyright 2012 IntelliNet Technologies, Inc.                 *
 **                            All Rights Reserved.                          *
 **             Manufactured in the United States of America.                *
 **       1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.       *
 **                                                                          *
 **   This product and related documentation is protected by copyright and   *
 **   distributed under licenses restricting its use, copying, distribution  *
 **   and decompilation.  No part of this product or related documentation   *
 **   may be reproduced in any form by any means without prior written       *
 **   authorization of IntelliNet Technologies and its licensors, if any.    *
 **                                                                          *
 **   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 **   government is subject to restrictions as set forth in subparagraph     *
 **   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 **   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 **                                                                          *
 ****************************************************************************/

#include<dia_stack_alarms.h>
#include<dia_cmn.h>
#include<MeSSComponent.h>

#if defined(ITS_STD_NAMESPACE)
using namespace its;
#endif
#define COMP_DRE_STACK 10

DiaStackAlarms* DiaStackAlarms::m_diaStackAlarmObj = NULL;

/*.implementation:static
 *****************************************************************************
 **  Purpose: Static method to create the object.DiaStackAlarms is a
 **           singleton class
 **
 **  Input Parameters:
 **     None.  
 **
 **  Input/Output Parameters:
 **      None.
 **
 **  Output Parameters:
 **      None
 **  Return Value:
 **        Returns the DiaStackAlarms object.
 **
 **  Notes:
 **
 **  See Also:
 *****************************************************************************/

DiaStackAlarms*
DiaStackAlarms::GetDiaStackAlarmsObj()
{
    if (m_diaStackAlarmObj == NULL)
    {
        m_diaStackAlarmObj = new DiaStackAlarms();

    }
    return m_diaStackAlarmObj;
}

/*.implementation:static
 *****************************************************************************
 **  Purpose:Method to Raise the alarm 
 **
 **  Input Parameters:
 **     sub-component Id,sub-component alarm id,alarm string.  
 **
 **  Input/Output Parameters:
 **      Variablesi in alarm string.
 **
 **  Output Parameters:
 **      None
 **  Return Value:
 **        None.
 **
 **  Notes:
 **
 **  See Also:
 *****************************************************************************/

void DiaStackAlarms::RaiseAlarm(uint32_t subComponentId,uint32_t subComponentAlarmId,
                                std::string addText, std::vector<std::string> &variables)
{
    AlarmReq Req;
    AlarmResp Resp;
    uint32_t compnetId = COMP_DRE_STACK;
    Req.set_componentid(compnetId);
    Req.set_subcomponentid(subComponentId);
    Req.set_subcomponentalarmid(subComponentAlarmId);
    Req.set_addtext(addText);
    for ( unsigned int i=0; i< variables.size(); i++ )
    {
        Req.add_variables(variables[i]);
    }

    uint16_t instanceId = eAccelero::MeSSComponent::Instance().MeSSObj().Self().instance;
    DT_DBG(("Instance id = %u",instanceId));
    if(m_alarmapi->RaiseAlarm(instanceId,Req,Resp) == CMAPI_SUCCESS)
    {
        DT_DBG(("Succesfully Sent an alarm with alarm Id %d%d and additional text using CMAPI",
                 subComponentId,subComponentAlarmId));
    } else {
        DT_ERR(("Failed to raise an alarm using CMAPI, AlarmId:%d%d,AddText:",
                    subComponentId,subComponentAlarmId));
    }
}
