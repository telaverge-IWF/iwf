#ifndef _CMAPI_DRE_ALARMS_H_
#define _CMAPI_DRE_ALARMS_H_

#include "DreAlarmsInfo_caller.h"

class CMAPIDreAlarms : public Stub::DreAlarmsInfoRespCbk {

    public:
        CMAPIDreAlarms() {}
        ~CMAPIDreAlarms() {}

        int SendDreAlarmInfoReq(uint16_t destInstanceId,DreAlarmInfoReq& req, DreAlarmInfoResp& resp);
        int InitializeLibrary();
    private:
        int SendDreAlarmInfoRespCbk(DreAlarmInfoResp *resp);
        int IsResponseOK(DreAlarmInfoResp *Resp);

};

#endif //_CMAPI_DRE_ALARMS_H_
