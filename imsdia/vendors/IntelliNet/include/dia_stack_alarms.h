/*********************************-*-H-*-**********************************
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
*****************************************************************************/

#if !defined DIA_STACK_ALARMS_H_
#define DIA_STACK_ALARMS_H_
#include <its++.h>
#include <its_mutex.h>
#include <AlarmId.h>
#include <ComponentDefines.h>
#include <Alarms_def.h>
#include <CMAPICommon.h>
#include <CMAPIAlarms.h>

class DiaStackAlarms
{
    public:
        static DiaStackAlarms* GetDiaStackAlarmsObj();
        void RaiseAlarm(uint32_t subComponentId,uint32_t subComponentAlarmId,
                        std::string addText, std::vector<std::string> &variables);
    private:
        CMAPIAlarms* m_alarmapi;
        static DiaStackAlarms* m_diaStackAlarmObj;
        DiaStackAlarms()
        {
            m_alarmapi = new CMAPIAlarms();
            m_alarmapi->InitializeLibrary();

        }
};

#define DIA_STACK_ALARM   DiaStackAlarms::GetDiaStackAlarmsObj()

#endif 
