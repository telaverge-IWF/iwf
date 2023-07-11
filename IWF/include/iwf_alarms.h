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

#ifndef __IWF_ALARM_H__
#define __IWF_ALARM_H__

#include "CMAPIAlarms.h"
#include <vector>

#define ALARM_IWF_TEXT_LICENSE_VIOLATED_FOR_CAP_RO_TRANSLATOR\
        "License violated for CAP-Ro Translator."

#define ALARM_IWF_TEXT_LICENSE_VIOLATED_FOR_CAP_RO_TSL_TRANSLATOR\
        "License violated for CAP-Ro-TSL Translator."

#define ALARM_IWF_TEXT_LICENSE_VIOLATED_FOR_MAP_S6A_TRANSLATOR\
        "License violated for MAP-s6a Translator."

#define ALARM_IWF_TEXT_LICENSE_VIOLATED_FOR_S6A_MAP_TRANSLATOR\
        "License violated for s6a-MAP Translator."

class IwfAlarms {
    public:
        IwfAlarms(uint16_t instanceId,uint32_t componentId);
        ~IwfAlarms();
        void RaiseAlarm(uint32_t subComponentId, uint32_t subComponentAlarmId, std::string addText,std::vector<std::string> &variables);
        void RaiseTranslatorLicenceViolationAlarm(uint32_t subComponentAlarmId, std::string translator);
    private:
        CMAPIAlarms* m_alarmapi;
        uint32_t m_componentId;
        uint16_t currentInstanceId;
};

#endif // __IWF_ALARM_H__

