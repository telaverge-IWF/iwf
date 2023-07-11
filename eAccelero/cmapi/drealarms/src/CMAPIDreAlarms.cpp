#include "CMAPICommon.h"
#include "CMAPIDreAlarms.h"
#include "ComponentDefines.h"

// This Method initializes the CMAPI Library
int CMAPIDreAlarms::InitializeLibrary() {

    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMAPIDreAlarms: InitializeLibrary\n");
    Stub::DreAlarmsInfoRespCbk::RegisterDreAlarmsInfoRespHandler();

    return retVal;
}


int CMAPIDreAlarms::SendDreAlarmInfoReq(uint16_t destInstanceId,DreAlarmInfoReq& req, DreAlarmInfoResp& resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    //MeSSEndpoint dest = {COMP_WEBAGENT_PROC, destInstanceId};
    MeSSEndpoint activeDest = {COMP_WEBAGENT_PROC, MESS_MULTICAST_ACTIVE};
    MeSSEndpoint standbyDest = {COMP_WEBAGENT_PROC, MESS_MULTICAST_STANDBY};

    //Stub::DreAlarmsInfo dreAlarmObj(dest,0);
    Stub::DreAlarmsInfo dreAlarmObjActive(activeDest,0);
    Stub::DreAlarmsInfo dreAlarmObjStandby(standbyDest,0);
    req.set_requestid(GET_PEERGENERALSTATS);
    CLOG_DEBUG("Sending Alarm info to CPPWebAgent");
    dreAlarmObjActive.SendDreAlarmInfo(req, (void *)NULL);

    dreAlarmObjStandby.SendDreAlarmInfo(req, (void *)NULL);

    return retVal;
}

int CMAPIDreAlarms::SendDreAlarmInfoRespCbk(DreAlarmInfoResp *resp) {
    CLOG_DEBUG(">SendDreAlarmInfoRespCbk");
    int retVal = IsResponseOK(resp);
    return retVal;
}

int CMAPIDreAlarms::IsResponseOK(DreAlarmInfoResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    CLOG_DEBUG(">CMAPIDreAlarms: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !resp->IsInitialized() ||
            resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        DreAlarmInfoResp errResp;
        errResp.set_responseid(CMAPI_ERROR);
        if ( resp!=NULL && resp->has_responseid() )
        {
            retVal = resp->responseid();
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            errResp.SerializeToString(&strVal);
        }
    }

	return retVal;
}
