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
#ifndef _ALARM_API_IMPL_H_
#define _ALARM_API_IMPL_H_

#include "Alarms.h"
namespace dre {

#define ALARM_SRC_DRE 2

class AlarmAPIImpl: public Alarms {
        public:
            AlarmAPIImpl();

            ~AlarmAPIImpl();

            int RaiseAlarm(AlarmReq *req,AlarmResp *resp);

        private:

            void FormEvent(AlarmReq *req,ITS_EVENT *evt);

            int ProcessRaiseAlarm(AlarmReq *req);
            
    };
}

#endif //#ifndef _ALARM_API_IMPL_H_
