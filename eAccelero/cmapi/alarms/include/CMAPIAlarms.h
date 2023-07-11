#ifndef _CMAPI_ALARMS_H_
#define _CMAPI_ALARMS_H_

#include "Alarms_caller.h"

class CMAPIAlarms : public Stub::AlarmsRespCbk {

    public:
        CMAPIAlarms() {}
        ~CMAPIAlarms() {}
        int RaiseAlarm(uint16_t destInstanceId, AlarmReq &req, AlarmResp &Resp);
        int InitializeLibrary();
    private:
        int SendAlarmRequest(uint16_t destInstanceId, AlarmReq &Req, AlarmResp *Resp);
        int RaiseAlarmRespCbk(AlarmResp*);
        int IsResponseOK(AlarmResp *Resp);

};

#endif //_CMAPI_ALARMS_H_
