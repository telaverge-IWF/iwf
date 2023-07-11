#include "iwf_state.h"
#include "iwf_fsm.h"
#include "iwf_transaction_manager.h"
#include "iwf_prot_utils.h"

#ifdef GCC_LESS_THAN_4_3
//using namespace std::tr1;
using namespace std;
#else
using namespace std;
#endif

State::State(uint16_t id) {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("State::State() Entry");

    m_id = id;

    memset(m_name, 0, sizeof (m_name));
    strncpy(m_name, s_stateNames[m_id], sizeof (m_name) - 1);
    m_name[(sizeof(m_name) - 1)] = '\0';

    memset(m_transition, 0, sizeof(m_transition));
    memset(m_before, 0 , sizeof(m_before));
    memset(m_after, 0, sizeof(m_after));
    //DLOG_DEBUG("State::State() Exit");
}

State::~State() {
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("State::~State() Entry");

    //DLOG_DEBUG("State::~State() Exit");
}

void State::SendUpstrmReq(IwfFsm* iwfFsm) {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("State::sendUpstrmReq() Entry");

    if (iwfFsm->GetUpstrmReqProtocol() == DIAMETER_S6A) {

        if (iwfFsm->GetTransactionManager()->SendTcapBegin(iwfFsm) != ITS_SUCCESS)
            iwfFsm->SetCurrSendErr(true);
        else
            iwfFsm->SetCurrSendErr(false);

    } 
    else if(iwfFsm->GetUpstrmReqProtocol() == CAP_GE || iwfFsm->GetUpstrmReqProtocol() == MAP_GR)
    {
        if (iwfFsm->GetTransactionManager()->SendDiaMsg(iwfFsm) != ITS_SUCCESS)
            iwfFsm->SetCurrSendErr(true);
        else
            iwfFsm->SetCurrSendErr(false);
    }

    //DLOG_DEBUG("State::sendUpstrmReq() Exit");
}

void State::SendDnstrmReq(IwfFsm* iwfFsm) {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("State::sendDnstrmReq() Entry");

    if (iwfFsm->GetUpstrmReqProtocol() == MAP_GR) {

        if (iwfFsm->GetTransactionManager()->SendTcapContinue(iwfFsm) != ITS_SUCCESS)
        {
            iwfFsm->SetCurrSendErr(true);
        }
        else
            iwfFsm->SetCurrSendErr(false);

    } else if (iwfFsm->GetUpstrmReqProtocol() == DIAMETER_S6A) {
        
        if (iwfFsm->GetTransactionManager()->SendDiaMsg(iwfFsm) != ITS_SUCCESS)
            iwfFsm->SetCurrSendErr(true);
        else
            iwfFsm->SetCurrSendErr(false);
    }

    //DLOG_DEBUG("State::sendUpstrmReq() Exit");
}

void State::SendUpstrmResp(IwfFsm* iwfFsm) {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("State::sendUpstrmResp() Entry");

    if (iwfFsm->GetUpstrmReqProtocol() == DIAMETER_S6A) {
        
        if (iwfFsm->GetTransactionManager()->SendTcapContinue(iwfFsm) != ITS_SUCCESS)
            iwfFsm->SetCurrSendErr(true);
        else
            iwfFsm->SetCurrSendErr(false);
    } else if (iwfFsm->GetUpstrmReqProtocol() == MAP_GR) {
        
        DLOG_ERROR("SendUpstrmResp() not applicable for MAP_GR upstream request protocol, in state %s",
                iwfFsm->GetCurrentStateName());
        
        iwfFsm->SetCurrSendErr(true);
    }

    //DLOG_DEBUG("State::sendUpstrmResp() Exit");
}

void State::SendDnstrmResp(IwfFsm* iwfFsm) {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("State::sendDnstrmResp() Entry");

    if (iwfFsm->GetUpstrmReqProtocol() == MAP_GR || iwfFsm->GetUpstrmReqProtocol() == CAP_GE) 
    {
        if (iwfFsm->GetTransactionManager()->SendTcapEnd(iwfFsm) != ITS_SUCCESS)
            iwfFsm->SetCurrSendErr(true);
        else
            iwfFsm->SetCurrSendErr(false);
    } 
    else if (iwfFsm->GetUpstrmReqProtocol() == DIAMETER_S6A) 
    {
        if (iwfFsm->GetTransactionManager()->SendDiaMsg(iwfFsm) != ITS_SUCCESS)
            iwfFsm->SetCurrSendErr(true);
        else
            iwfFsm->SetCurrSendErr(false);
    }

    //DLOG_DEBUG("State::sendDnstrmResp() Exit");
}

void State::SendIntrmUpstrmResp(IwfFsm* iwfFsm) 
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("State::sendIntrmUpstrmResp() Entry");
    
    if (iwfFsm->GetUpstrmReqProtocol() == CAP_GE) {

        if (iwfFsm->GetTransactionManager()->SendTcapContinue(iwfFsm) != ITS_SUCCESS)
            iwfFsm->SetCurrSendErr(true);
        else
            iwfFsm->SetCurrSendErr(false);

    } else if (iwfFsm->GetUpstrmReqProtocol() == DIAMETER_RO) {

        if (iwfFsm->GetTransactionManager()->SendDiaMsg(iwfFsm) != ITS_SUCCESS)
            iwfFsm->SetCurrSendErr(true);
        else
            iwfFsm->SetCurrSendErr(false);
    }   

    //DLOG_DEBUG("State::sendIntrmUpstrmResp() Exit");
}

void State::SendIntrmUpstrmReq(IwfFsm* iwfFsm) {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("State::SendIntrmUpstrmReq() Entry");

    if (iwfFsm->GetUpstrmReqProtocol() == CAP_GE) {

        if (iwfFsm->GetTransactionManager()->SendDiaMsg(iwfFsm) != ITS_SUCCESS)
            iwfFsm->SetCurrSendErr(true);
        else
            iwfFsm->SetCurrSendErr(false);
    } 

    //DLOG_DEBUG("State::SendIntrmUpstrmReq() Exit");
}

void State::SendIntrmDnstrmReq(IwfFsm* iwfFsm) {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("State::SendIntrmDnstrmReq() Entry");

    if (iwfFsm->GetUpstrmReqProtocol() == CAP_GE) {

        if (iwfFsm->GetTransactionManager()->SendTcapContinue(iwfFsm) != ITS_SUCCESS)
            iwfFsm->SetCurrSendErr(true);
        else
            iwfFsm->SetCurrSendErr(false);
    } 

    //DLOG_DEBUG("State::SendIntrmDnstrmReq() Exit");
}

void State::ProcessErr(IwfFsm* iwfFsm) {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("State::processError() Entry");
    
    if( iwfFsm->GetUpstrmReqProtocol() == CAP_GE 
            && (iwfFsm->GetErrorCode() == ITS_ETIMEOUT ||
                iwfFsm->GetErrorCode() == ITS_DIA_UNABLE_TO_DELIVER ||
                iwfFsm->GetErrorCode() == IWF_EAUTH_SESSION_TIMEOUT ||
                iwfFsm->GetErrorCode() == IWF_EBASE_MAND_AVP_MISSING))
    {
        // Let the ProcessErr take the decision and hence below code is
        // commented out
        // iwfFsm->GetTransactionManager()->ClearDiaAndTcapSession(iwfFsm);
    }
    else
    {
        if (iwfFsm->IsCurrRcvdMsgDia())
        {
            iwfFsm->GetTransactionManager()->SendDiaErrResp(iwfFsm);
        }

        if( iwfFsm->GetUpstrmReqProtocol() == CAP_GE && iwfFsm->GetErrorCode() == CAP_ERR_MISSING_PARAMETER)
        {
            if (iwfFsm->IsCurrRcvdMsgTcap())
                iwfFsm->GetTransactionManager()->SendTcapErrResp(iwfFsm);

            //DLOG_DEBUG("State::processError() Exit");
            return;
        }
        else if (iwfFsm->IsCurrRcvdMsgTcap())
        {
            iwfFsm->GetTransactionManager()->SendTcapErrResp(iwfFsm);
        }
    }

    iwfFsm->SetCurrSendErr(false);
    iwfFsm->GetTransactionManager()->ProcessErr(iwfFsm);

    //DLOG_DEBUG("State::processError() Exit");
}

void State::CheckForRollback(IwfFsm* iwfFsm)
{
    //DLOG_DEBUG("State: Checking for state rollback");
    if (iwfFsm->IsMarkedForRollback())
    {
        //DLOG_DEBUG("State: mark set in fsm, going to previous state");
        iwfFsm->GotoPrevState();
        iwfFsm->SetMarkForRollback(false);
    }
}

States State::GetStateId() {
    return (States) m_id;
}

const char* State::GetStateName() {
    return m_name;
}
