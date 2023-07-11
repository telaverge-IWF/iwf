
#include "CMAPICommon.h"
#include "CMAPIAlarms.h"
#include "ComponentDefines.h"

// This Method initializes the CMAPI Library
int CMAPIAlarms::InitializeLibrary() {

    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMAPIAlarms: InitializeLibrary\n");
    CLOG_DEBUG("InitializeLibrary: Initializing SubAgent Interface");
    //As of now hard-coding to MESS_MIN_ACTIVE_INSTANCE
    //destInstanceId = MESS_MIN_ACTIVE_INSTANCE;
    /*MeSSEndpoint dest = {COMP_SUB_AGENT, destInstanceId};
    m_alarmsObj = new Stub::Alarms(dest,0);*/
    Stub::AlarmsRespCbk::RegisterAlarmsRespHandler();

    return retVal;
}

int CMAPIAlarms::RaiseAlarm(uint16_t destInstanceId, AlarmReq &Req, AlarmResp &Resp) 
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMAPIAlarms: RaiseAlarm");
    Req.set_requestid(RAISE_ALARM);
    retVal = SendAlarmRequest(destInstanceId, Req,&Resp);
    return retVal;
}


int CMAPIAlarms::SendAlarmRequest(uint16_t destInstanceId, AlarmReq &Req, AlarmResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    MeSSEndpoint dest = {COMP_SUB_AGENT, destInstanceId};
    Stub::Alarms m_alarmsObj(dest,0);

    CLOG_DEBUG("Sending RaiseAlarm Request to SubAgent");
    m_alarmsObj.RaiseAlarm(Req,
            new CMAPICookie(Req.requestid(), (void *) &Req));
    CLOG_DEBUG("SendAlarmRequest::RaiseAlarm Waiting for Response");

    return retVal;

}

int CMAPIAlarms::RaiseAlarmRespCbk(AlarmResp *Resp) {
     CLOG_DEBUG(">RaiseAlarmRespCbk");
     int retVal = IsResponseOK(Resp);
	if (retVal == CMAPI_SUCCESS)
    {
       CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
       delete lCookie;
       std::string StrVal;
       Resp->SerializeToString(&StrVal);
	}
    return retVal;

}

int CMAPIAlarms::IsResponseOK(AlarmResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG(">CMAPIAlarms: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        AlarmResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);
		CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        if ( Resp!=NULL && Resp->has_responseid() )
        {
            retVal = Resp->responseid();
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            ErrResp.SerializeToString(&StrVal);
        }

        delete lCookie;
    }

	return retVal;
}
