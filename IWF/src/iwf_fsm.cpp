#include "iwf_state.h"
#include "iwf_fsm.h"
#include "iwf_prot_utils.h"

#ifdef GCC_LESS_THAN_4_3
//using namespace std::tr1;
using namespace std;
#else
using namespace std;
#endif

//To ensure a sequential access ONLY to state transition
//TODO: A more optimal mechanism may be put in place in the future
//static pthread_mutex_t s_mutex = PTHREAD_MUTEX_INITIALIZER;
ITS_Mutex s_mutex(0);

static Mapping s_stateTransitionTable[ MAX_STATES * IWF_MAX_EVENTS ] = {
    /* state, event, next state, action before state transition, action after state transition */
    /* CLOSED */

    {CLOSED, RECV_UPSTRM_REQ, UPSTRM_REQ_SENT, &State::SendUpstrmReq, NULL},
    {CLOSED, RECV_DNSTRM_REQ, CLOSED, NULL, &State::ProcessErr},
    {CLOSED, RECV_DNSTRM_RESP, CLOSED, NULL, &State::ProcessErr},
    {CLOSED, RECV_CBDNSTRM_RESP, CLOSED, NULL, &State::ProcessErr},
    {CLOSED, RECV_UPSTRM_RESP, CLOSED, NULL, &State::ProcessErr},
    {CLOSED, RECV_INTRM_DNSTRM_RESP, CLOSED, NULL, &State::ProcessErr},
    {CLOSED, RECV_INTRM_UPSTRM_RESP, CLOSED, NULL, &State::ProcessErr}, // Add a method to gracefully consume it.
    {CLOSED, RECV_INTRM_DNSTRM_REQ, CLOSED, NULL, &State::ProcessErr},
    {CLOSED, TIMEOUT, CLOSED, NULL, &State::ProcessErr},
    {CLOSED, ERROR, CLOSED, NULL, &State::ProcessErr},
    /* UPSTRM_REQ_SENT */

    {UPSTRM_REQ_SENT, RECV_UPSTRM_REQ, CLOSED, NULL, &State::ProcessErr},
    {UPSTRM_REQ_SENT, RECV_DNSTRM_REQ, UPSTRM_RESP_SENT, &State::SendUpstrmResp, NULL},
    {UPSTRM_REQ_SENT, RECV_DNSTRM_RESP, CLOSED, &State::SendDnstrmResp, &State::CheckForRollback},
    {UPSTRM_REQ_SENT, RECV_CBDNSTRM_RESP, DNSTRM_REQ_SENT, &State::SendDnstrmReq, NULL},
    {UPSTRM_REQ_SENT, RECV_UPSTRM_RESP, UPSTRM_REQ_SENT, NULL, &State::SendUpstrmReq},
    {UPSTRM_REQ_SENT, RECV_INTRM_DNSTRM_RESP, DNSTRM_INTRM_REQ_SENT, NULL, &State::SendIntrmDnstrmReq},
    {UPSTRM_REQ_SENT, RECV_INTRM_UPSTRM_RESP, UPSTRM_INTRM_REQ_SENT, NULL, &State::SendIntrmUpstrmReq},
    {UPSTRM_REQ_SENT, RECV_INTRM_DNSTRM_REQ, UPSTRM_REQ_SENT, NULL, &State::SendIntrmUpstrmResp},
    {UPSTRM_REQ_SENT, TIMEOUT, CLOSED, NULL, &State::ProcessErr},
    {UPSTRM_REQ_SENT, ERROR, CLOSED, NULL, &State::ProcessErr},
    /* UPSTRM_RESP_SENT */

    {UPSTRM_RESP_SENT, RECV_UPSTRM_REQ, CLOSED, NULL, &State::ProcessErr},
    {UPSTRM_RESP_SENT, RECV_DNSTRM_REQ, UPSTRM_RESP_SENT, &State::SendUpstrmResp, NULL},
    {UPSTRM_RESP_SENT, RECV_DNSTRM_RESP, CLOSED, &State::SendDnstrmResp, &State::CheckForRollback},
    {UPSTRM_RESP_SENT, RECV_CBDNSTRM_RESP, CLOSED, NULL, &State::ProcessErr},
    {UPSTRM_RESP_SENT, RECV_UPSTRM_RESP, CLOSED, NULL, &State::ProcessErr},
    {UPSTRM_RESP_SENT, RECV_INTRM_DNSTRM_RESP, CLOSED, NULL, &State::ProcessErr},
    {UPSTRM_RESP_SENT, RECV_INTRM_UPSTRM_RESP, UPSTRM_INTRM_REQ_SENT, NULL, &State::SendIntrmUpstrmReq},
    {UPSTRM_RESP_SENT, RECV_INTRM_DNSTRM_REQ, UPSTRM_RESP_SENT, NULL, &State::SendIntrmUpstrmResp},
    {UPSTRM_RESP_SENT, TIMEOUT, CLOSED, NULL, &State::ProcessErr},
    {UPSTRM_RESP_SENT, ERROR, CLOSED, NULL, &State::ProcessErr},

    /* DNSTRM_REQ_SENT */
    {DNSTRM_REQ_SENT, RECV_UPSTRM_REQ, CLOSED, NULL, &State::ProcessErr},
    {DNSTRM_REQ_SENT, RECV_DNSTRM_REQ, CLOSED, NULL, &State::ProcessErr },
    {DNSTRM_REQ_SENT, RECV_DNSTRM_RESP, CLOSED, NULL, &State::ProcessErr },
    {DNSTRM_REQ_SENT, RECV_CBDNSTRM_RESP, CLOSED, NULL, &State::ProcessErr},
    {DNSTRM_REQ_SENT, RECV_UPSTRM_RESP, CLOSED, &State::SendDnstrmResp, &State::CheckForRollback},
    {DNSTRM_REQ_SENT, RECV_INTRM_DNSTRM_RESP, CLOSED, NULL, &State::ProcessErr},
    {DNSTRM_REQ_SENT, RECV_INTRM_UPSTRM_RESP, UPSTRM_INTRM_REQ_SENT, NULL, &State::SendIntrmUpstrmReq},
    {DNSTRM_REQ_SENT, RECV_INTRM_DNSTRM_REQ, DNSTRM_REQ_SENT, NULL, &State::SendIntrmUpstrmResp},
    {DNSTRM_REQ_SENT, TIMEOUT, CLOSED, NULL, &State::ProcessErr},
    {DNSTRM_REQ_SENT, ERROR, CLOSED, NULL, &State::ProcessErr},


    /* DNSTRM_INTERIM_REQ_SENT */
    {DNSTRM_INTRM_REQ_SENT, RECV_UPSTRM_REQ, CLOSED, NULL, &State::ProcessErr},
    {DNSTRM_INTRM_REQ_SENT, RECV_DNSTRM_REQ, CLOSED, NULL, &State::ProcessErr },
    {DNSTRM_INTRM_REQ_SENT, RECV_DNSTRM_RESP, CLOSED, &State::SendDnstrmResp, &State::CheckForRollback },
    {DNSTRM_INTRM_REQ_SENT, RECV_CBDNSTRM_RESP, CLOSED, NULL, &State::ProcessErr},
    {DNSTRM_INTRM_REQ_SENT, RECV_UPSTRM_RESP, UPSTRM_REQ_SENT,NULL, &State::SendUpstrmReq},
    {DNSTRM_INTRM_REQ_SENT, RECV_INTRM_DNSTRM_RESP, DNSTRM_INTRM_REQ_SENT, &State::SendIntrmDnstrmReq, NULL},
    {DNSTRM_INTRM_REQ_SENT, RECV_INTRM_UPSTRM_RESP, UPSTRM_INTRM_REQ_SENT, NULL, &State::SendIntrmUpstrmReq},
    {DNSTRM_INTRM_REQ_SENT, RECV_INTRM_DNSTRM_REQ, DNSTRM_INTRM_REQ_SENT, NULL, &State::SendIntrmUpstrmResp},
    {DNSTRM_INTRM_REQ_SENT, TIMEOUT, CLOSED, NULL, &State::ProcessErr},
    {DNSTRM_INTRM_REQ_SENT, ERROR, CLOSED, NULL, &State::ProcessErr},


    /* UPSTRM_INTERIM_REQ_SENT */
    {UPSTRM_INTRM_REQ_SENT, RECV_UPSTRM_REQ, CLOSED, NULL, &State::ProcessErr},
    {UPSTRM_INTRM_REQ_SENT, RECV_DNSTRM_REQ, CLOSED, NULL, &State::ProcessErr },
    {UPSTRM_INTRM_REQ_SENT, RECV_DNSTRM_RESP, CLOSED, &State::SendDnstrmResp, &State::CheckForRollback },
    {UPSTRM_INTRM_REQ_SENT, RECV_CBDNSTRM_RESP, CLOSED, NULL, &State::ProcessErr},
    {UPSTRM_INTRM_REQ_SENT, RECV_UPSTRM_RESP, UPSTRM_REQ_SENT,NULL, &State::SendUpstrmReq},
    {UPSTRM_INTRM_REQ_SENT, RECV_INTRM_DNSTRM_RESP, DNSTRM_INTRM_REQ_SENT, NULL, &State::SendIntrmDnstrmReq},
    {UPSTRM_INTRM_REQ_SENT, RECV_INTRM_UPSTRM_RESP, UPSTRM_INTRM_REQ_SENT, NULL, &State::SendIntrmUpstrmReq},
    {UPSTRM_INTRM_REQ_SENT, RECV_INTRM_DNSTRM_REQ, UPSTRM_INTRM_REQ_SENT, NULL, &State::SendIntrmUpstrmResp},
    {UPSTRM_INTRM_REQ_SENT, TIMEOUT, CLOSED, NULL, &State::ProcessErr},
    {UPSTRM_INTRM_REQ_SENT, ERROR, CLOSED, NULL, &State::ProcessErr}

};

static void timeoutCallback(int fd, short event, void *arg) {
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    struct timeval currentTimeVal, difference;
    double elapsed;

    evutil_gettimeofday(&currentTimeVal, NULL);
    evutil_timersub(&currentTimeVal, static_cast<IwfFsm *> (arg)->GetTimerInvokeTimeVal(), &difference);

    elapsed = difference.tv_sec + (difference.tv_usec / 1.0e6);

    DLOG_DEBUG("TIMEOUT occurred after %.3f seconds", elapsed);

    static_cast<IwfFsm *> (arg)->MakeStateTransition(TIMEOUT, NULL, NULL, NULL);
}

static void* invokeTimer(void *params) {
    
    event_init();

    evtimer_set(static_cast<IwfFsm *> (params)->GetEvent(), timeoutCallback, static_cast<IwfFsm *> (params));

    evtimer_add(static_cast<IwfFsm *> (params)->GetEvent(), static_cast<IwfFsm *> (params)->GetConfigTimeVal());

    static_cast<IwfFsm *> (params)->SetTimerStarted(true);

    evutil_gettimeofday(static_cast<IwfFsm *> (params)->GetTimerInvokeTimeVal(), NULL);

    event_dispatch();

    static_cast<IwfFsm *> (params)->SetTimerStarted(false);

    return NULL;
}

IwfFsm::IwfFsm(TransactionManager *txnMgr):ReplicableData(&(this->m_pbIwfFsmRepData)) 
{
    m_pbIwfFsmRepData.Clear(); 
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("IwfFsm::IwfFsm() Entry");

    for (uint8_t i = 0; i < MAX_STATES; i++) {
        m_graph[i] = new State(i);
    }

    Mapping *map = s_stateTransitionTable;

    for (int j = 0; j < MAX_STATES * IWF_MAX_EVENTS; j++, map++) {
        (m_graph[map->from])->m_transition[map->input] = m_graph[map->to];
        (m_graph[map->from])->m_before[map->input] = map->before;
        (m_graph[map->from])->m_after[map->input] = map->after;
    }

    m_current = m_graph[0];

    m_isTimerStarted = false;

    m_configTimeVal = (struct timeval *) malloc(sizeof (struct timeval));
    evutil_timerclear(m_configTimeVal);
    m_configTimeVal->tv_sec = FSM_CLEANUP_TIME;

    m_timerEvent = (struct event *) malloc(sizeof (struct event));
    memset(m_timerEvent, 0, sizeof (struct event));

    m_timerInvokeTimeVal = (struct timeval *) malloc(sizeof (struct timeval));
    evutil_timerclear(m_timerInvokeTimeVal);

    m_txnMgr = txnMgr;
    
    m_currRcvdDiaMsg = NULL;
    
    m_currRcvdTcapDlg = NULL;
    
    m_currRcvdTcapCpt = NULL;

    m_storedUserData = NULL;

    m_currTcapBeginDlg = NULL;

    m_translator = NULL;

    m_routingLabel = NULL;

    m_timerList.clear();

    m_outGoingInvokeIdList.clear();

    m_acrossSwitchover = false;

#if 0
    
    m_isCurrSendErr = false;

    m_errCode = 0;

    m_tcapDialogueId = 0;

    m_diaSessionIdx = 0;

    m_isroutebyGT = false;

    m_dnstrmReqProtocol = MAP_GR;

    m_upstrmReqProtocol = DIAMETER_S6A;

    m_IntmdteisdSent = false;

    m_invokeId = 0;

    m_bIsDiaRespSent = false;
	
    invoke_id = 0;

    m_isTCAPEnd = false;

    m_startNoEventTimer = false;
    
    m_isFinalUpstrmReqSent = false;

    m_markForRollback = false;

    m_flowFailure = false;
    
    m_isCloseState = false;
#endif

    m_isSessionPurged = false;

    m_markedForDeletion = false;

    txnMgr->IncrementFSMCount();

    m_isEUTRANRcvdinReq = false;

    m_isUTRANRcvdinReq = false;

    m_originHostFromCLRSet = false;

    //DLOG_DEBUG("IwfFsm::IwfFsm() Exit");
}

IwfFsm::IwfFsm(TransactionManager *txnMgr, States initialState):ReplicableData(&(this->m_pbIwfFsmRepData)) 
{

    m_pbIwfFsmRepData.Clear(); 
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("IwfFsm::IwfFsm() Entry");

    for (uint8_t i = 0; i < MAX_STATES; i++) {
        m_graph[i] = new State(i);
    }

    Mapping *map = s_stateTransitionTable;

    for (int j = 0; j < MAX_STATES * IWF_MAX_EVENTS; j++, map++) {
        (m_graph[map->from])->m_transition[map->input] = m_graph[map->to];
        (m_graph[map->from])->m_before[map->input] = map->before;
        (m_graph[map->from])->m_after[map->input] = map->after;
    }

    if (initialState < 0 || initialState >= MAX_STATES)
        m_current = m_graph[0];
    else
        m_current = m_graph[initialState];

    m_isTimerStarted = false;

    m_configTimeVal = (struct timeval *) malloc(sizeof (struct timeval));
    evutil_timerclear(m_configTimeVal);
    m_configTimeVal->tv_sec = FSM_CLEANUP_TIME;

    m_timerEvent = (struct event *) malloc(sizeof (struct event));
    memset(m_timerEvent, 0, sizeof (struct event));

    m_timerInvokeTimeVal = (struct timeval *) malloc(sizeof (struct timeval));
    evutil_timerclear(m_timerInvokeTimeVal);

    m_txnMgr = txnMgr;
    
    m_currRcvdDiaMsg = NULL;
    
    m_currRcvdTcapDlg = NULL;
    
    m_currRcvdTcapCpt = NULL;

    m_storedUserData = NULL;

    m_currTcapBeginDlg = NULL;

    m_translator = NULL;

    m_routingLabel = NULL;

    m_timerList.clear();

    m_outGoingInvokeIdList.clear();

    m_acrossSwitchover = false;

#if 0
    
    m_isCurrSendErr = false;

    m_errCode = 0;

    m_tcapDialogueId = 0;

    m_diaSessionIdx = 0;

    m_isroutebyGT = false;

    m_dnstrmReqProtocol = MAP_GR;

    m_upstrmReqProtocol = DIAMETER_S6A;

    m_IntmdteisdSent = false;

    m_invokeId = 0;

    m_bIsDiaRespSent = false;
	
    invoke_id = 0;

    m_isTCAPEnd = false;

    m_startNoEventTimer = false;
    
    m_isFinalUpstrmReqSent = false;

    m_markForRollback = false;

    m_flowFailure = false;
    
    m_isCloseState = false;
#endif
    
    m_isSessionPurged = false;

    m_markedForDeletion = false;

    txnMgr->IncrementFSMCount();

    m_isEUTRANRcvdinReq = false;

    m_isUTRANRcvdinReq = false;

    m_originHostFromCLRSet = false;

    //DLOG_DEBUG("IwfFsm::IwfFsm() Exit");
}

IwfFsm::~IwfFsm() {

   // ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
   // DLOG_DEBUG("IwfFsm::~IwfFsm() Entry");
    
    this->StopAllTimers();

    for (uint8_t i = 0; i < MAX_STATES; i++) {
        if (m_graph[i] != NULL) {
            delete m_graph[i];
            m_graph[i] = NULL;
        }
    }

    if (m_timerEvent != NULL) {
        free(m_timerEvent);
        m_timerEvent = NULL;
    }

    if (m_configTimeVal != NULL) {
        free(m_configTimeVal);
        m_configTimeVal = NULL;
    }

    if (m_timerInvokeTimeVal != NULL) {
        free(m_timerInvokeTimeVal);
        m_timerInvokeTimeVal = NULL;
    }

    if(m_storedUserData != NULL){
        delete m_storedUserData;
        m_storedUserData = NULL;
    }

    if(m_routingLabel != NULL)
    {
        delete m_routingLabel;
        m_routingLabel = NULL;
    }

    m_timerList.clear();

    m_outGoingInvokeIdList.clear();

    m_txnMgr->DecrementFSMCount();

    for(ProxyInfoList::iterator it = m_pxyInfoList.begin();
            it != m_pxyInfoList.end();)
    {
        delete *it;
        it = m_pxyInfoList.erase(it);
    }

    //DLOG_DEBUG("IwfFsm::~IwfFsm() Exit");
}

States IwfFsm::GetCurrentStateId() {
    return m_current->GetStateId();
}

void IwfFsm::SetCurrentState(States currState)
{
    m_current = m_graph[currState];
}

void IwfFsm::SetPreviousState(States prevState)
{
    m_prevState = m_graph[prevState];
}

bool IwfFsm::IsMovingToCloseState()
{
    return m_pbIwfFsmRepData.isclosestate();
}

void IwfFsm::MoveToCloseState(bool state)
{
    m_pbIwfFsmRepData.set_isclosestate(state);
}

const char* IwfFsm::GetCurrentStateName() {
    return m_current->GetStateName();
}

void IwfFsm::MakeStateTransition(Events event, DIA_BASE_CMD *diaCmd, TCAP_Dialogue *tcapDlg, TCAP_Component *tcapCpt) {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("IwfFsm::makeStateTransition() Entry");

    //pthread_mutex_lock(&s_mutex);
    //s_mutex.Acquire();

    if ((event < 0) || (event >= IWF_MAX_EVENTS)) {
        //DLOG_DEBUG("Unexpected Event received");
        //pthread_mutex_unlock(&s_mutex);
       //s_mutex.Release();
        return;
    }

    if (diaCmd != NULL)
        m_currRcvdDiaMsg = diaCmd;

    if (tcapDlg != NULL)
        m_currRcvdTcapDlg = tcapDlg;       

    if (tcapCpt != NULL)
        m_currRcvdTcapCpt = tcapCpt;        

    string str = s_eventNames[event];

    /*DLOG_DEBUG("Processing Event %s, in State %s",
            str.c_str(),
            this->GetCurrentStateName());*/

    Action action;

    //Do "before" action
    action = m_current->m_before[event];
    if (action != NULL) (m_current->*action)(this);

    m_prevState = m_current;

    //Prepare for "after" action
    action = m_current->m_after[event];
    //Do state transition
    m_current = m_current->m_transition[event];

    //DLOG_DEBUG("New State: %s", m_current->GetStateName());

    //Do "after" action
    if (action != NULL) (m_current->*action)(this);

    // Reset the rollback mark if any
    this->SetMarkForRollback(false);

    //pthread_mutex_unlock(&s_mutex);
    //s_mutex.Release();

    //DLOG_DEBUG("IwfFsm::makeStateTransition() Exit");
}

void IwfFsm::StartTimer() {

#if 0
    DLOG_DEBUG("IwfFsm::startTimer() Entry");

    pthread_t thread;

    pthread_create(&thread, NULL, invokeTimer, this);

    DLOG_DEBUG("IwfFsm::startTimer() Exit");
#endif

}

void IwfFsm::CancelTimer() {

#if 0
    DLOG_DEBUG("IwfFsm::cancelTimer() Entry");

    if (m_isTimerStarted) {

        evtimer_del(m_timerEvent);

        memset(m_timerEvent, 0, sizeof (struct event));

        m_isTimerStarted = false;
    }

    DLOG_DEBUG("IwfFsm::cancelTimer() Exit");
#endif

}

void IwfFsm::SetTimerStarted(bool isTimerStarted) {
    m_isTimerStarted = isTimerStarted;
}

bool IwfFsm::GetIsTimerStarted() {
    return m_isTimerStarted;
}

struct timeval* IwfFsm::GetConfigTimeVal() {
    return m_configTimeVal;
}

struct event* IwfFsm::GetEvent() {
    return m_timerEvent;
}

struct timeval* IwfFsm::GetTimerInvokeTimeVal() {
    return m_timerInvokeTimeVal;
}

TransactionManager* IwfFsm::GetTransactionManager() {
    return m_txnMgr;
}

void IwfFsm::SetUpstrmReqProtocol(pbProtocol upstrmReqProtocol) {
    m_pbIwfFsmRepData.set_upstrmreqprotocol(upstrmReqProtocol);
}

pbProtocol IwfFsm::GetUpstrmReqProtocol() {
    return m_pbIwfFsmRepData.upstrmreqprotocol();
}

void IwfFsm::SetDnstrmReqProtocol(pbProtocol dnstrmReqProtocol) {
    m_pbIwfFsmRepData.set_dnstrmreqprotocol(dnstrmReqProtocol);
}

pbProtocol IwfFsm::GetDnstrmReqProtocol() {
    return m_pbIwfFsmRepData.dnstrmreqprotocol();
}

void IwfFsm::SetDiaSessionId(std::string diaSessionId) {
    m_pbIwfFsmRepData.set_diasessionid(diaSessionId);
}

std::string& IwfFsm::GetDiaSessionId() {
    return const_cast<std::string&>(m_pbIwfFsmRepData.diasessionid());
}

void IwfFsm::SetDiaSessionIdx(unsigned int diaSessionIdx) {
    m_pbIwfFsmRepData.set_diasessionidx(diaSessionIdx);
}

unsigned int IwfFsm::GetDiaSessionIdx() {
    return m_pbIwfFsmRepData.diasessionidx();
}

void IwfFsm::SetTcapDlgId(ITS_CTXT tcapDlgId) {
    m_pbIwfFsmRepData.set_tcapdialogueid(tcapDlgId);
}

ITS_CTXT IwfFsm::GetTcapDlgId() {
    return m_pbIwfFsmRepData.tcapdialogueid();
}

void IwfFsm::SetCurrRcvdDiaMsg(DIA_BASE_CMD *diaCmd) {
    m_currRcvdDiaMsg = diaCmd;
}

DIA_BASE_CMD* IwfFsm::GetCurrRcvdDiaMsg() {
    return m_currRcvdDiaMsg;
}

void IwfFsm::SetCurrRcvdTcapDlg(TCAP_Dialogue *tcapDlg) {
    m_currRcvdTcapDlg = tcapDlg;
}

TCAP_Dialogue* IwfFsm::GetCurrRcvdTcapDlg() {
    return m_currRcvdTcapDlg;
}

void IwfFsm::SetTcapBeginDlg(TCAP_Begin *tcapbegin) {
    m_currTcapBeginDlg = tcapbegin;
}

TCAP_Begin* IwfFsm::GetTcapBeginDlg() {
    return m_currTcapBeginDlg;
}

void IwfFsm::SetCurrRcvdTcapCpt(TCAP_Component *tcapCpt) {
    m_currRcvdTcapCpt = tcapCpt;
}

TCAP_Component* IwfFsm::GetCurrRcvdTcapCpt() {
    return m_currRcvdTcapCpt;
}

bool IwfFsm::IsCurrRcvdMsgDia() {
    if (m_currRcvdDiaMsg != NULL)
        return true;
    else
        return false;
}

bool IwfFsm::IsCurrRcvdMsgTcap() {
    if ((m_currRcvdTcapDlg != NULL) && (m_currRcvdTcapCpt != NULL))
        return true;
    else
        return false;
}

void IwfFsm::SetCurrSendErr(bool isCurrSendErr) {
    m_pbIwfFsmRepData.set_iscurrsenderr(isCurrSendErr);
}

void IwfFsm::SetErrorCode(int errorCode)
{
    m_pbIwfFsmRepData.set_errcode(errorCode);
}

int IwfFsm::GetErrorCode()
{
    return m_pbIwfFsmRepData.errcode();
}

void IwfFsm::SetImsi(std::string username)
{
    m_pbIwfFsmRepData.set_username(username);
}

std::string& IwfFsm::GetImsi()
{
    return const_cast<std::string&>(m_pbIwfFsmRepData.username());
}

void IwfFsm::SetIntmdteIsdSent(bool IsdSent)
{
    m_IntmdteisdSent = IsdSent;
}

bool IwfFsm::GetIntmdteIsdSent()
{
    return m_IntmdteisdSent;
}

bool IwfFsm::IsCurrSendErr() {
    return m_pbIwfFsmRepData.iscurrsenderr();
}

void IwfFsm::SetTranslator(IwfTranslator* trnsltr)
{   
    m_translator = trnsltr;
}   

IwfTranslator* IwfFsm::GetTranslator()
{   
    return m_translator;
}   

void IwfFsm::SetRoutingLabel(pbRoutingLabel routinglabel)
{
    pbRoutingLabel* routingLabel;
    if(m_pbIwfFsmRepData.has_routinglabel())
    {
        m_pbIwfFsmRepData.clear_routinglabel();
    }
    routingLabel = m_pbIwfFsmRepData.mutable_routinglabel();
    routingLabel->CopyFrom(routinglabel);
}

const pbRoutingLabel& IwfFsm::GetRoutingLabel()
{
    return m_pbIwfFsmRepData.routinglabel();
}


void IwfFsm::SetStoredUserData(StoredUserData *storedUserData) {
    m_storedUserData = storedUserData;
}

StoredUserData* IwfFsm::GetStoredUserData() {
    return m_storedUserData;
}

void IwfFsm::SetInvokeId(ITS_OCTET ivkId)
{
    m_pbIwfFsmRepData.set_invokeid(ivkId);
}

ITS_OCTET IwfFsm::GetInvokeId()
{
    return m_pbIwfFsmRepData.invokeid();
}

void IwfFsm::SetSelfSccpAddr(SCCP_CalledPartyAddr& selfSccpAddr)
{
#ifdef USE_FULL_SCCP_ADDRESS
    // The below methods are used only in the old way of storing SCCP address
    // Its not required to store them entirely, it takes 4KB of memory unnecessarily
    m_selfSccpAddr = selfSccpAddr;
#else
    DLOG_DEBUG("has_selfsccpaddr: %d\n", m_pbIwfFsmRepData.has_selfsccpaddr());
    if (m_pbIwfFsmRepData.has_selfsccpaddr())
    {
        m_pbIwfFsmRepData.clear_selfsccpaddr();
    }
    pbSccpAddress* pbSelfSccpAddr = m_pbIwfFsmRepData.mutable_selfsccpaddr();

    DLOG_DEBUG("HasPointCode: %d\n", selfSccpAddr.HasPointCode());
    pbSelfSccpAddr->set_haspc(selfSccpAddr.HasPointCode());
    if ( selfSccpAddr.HasPointCode())
    {
        DLOG_DEBUG("PointCode: %d\n", selfSccpAddr.GetPointCode());
        pbSelfSccpAddr->set_pointcode(selfSccpAddr.GetPointCode());
    }
    DLOG_DEBUG("HasSSN: %d\n", selfSccpAddr.HasSSN());
    pbSelfSccpAddr->set_hasssn(selfSccpAddr.HasSSN());
    if (selfSccpAddr.HasSSN())
    {
        DLOG_DEBUG("SSN: %d\n", selfSccpAddr.GetSSN());
        pbSelfSccpAddr->set_ssn(selfSccpAddr.GetSSN());
    }
    DLOG_DEBUG("IsRoutedByPCSSN: %d\n", selfSccpAddr.IsRoutedByPCSSN());
    pbSelfSccpAddr->set_routepcssn(selfSccpAddr.IsRoutedByPCSSN());
    DLOG_DEBUG("IsInternationalRouting: %d\n", selfSccpAddr.IsInternationalRouting());
    pbSelfSccpAddr->set_internationalroute(selfSccpAddr.IsInternationalRouting());
    DLOG_DEBUG("Globaltitle: %d\n", selfSccpAddr.HasGlobalTitle());
    pbSelfSccpAddr->set_globaltitle(selfSccpAddr.HasGlobalTitle());
    if (selfSccpAddr.HasGlobalTitle())
    {
        ITS_OCTET gttype = 0;
        ITS_USHORT gttLen = 0;
        ITS_OCTET gttInfo[64] = {0};
        // Get gloabal title from address
        selfSccpAddr.GetGlobalTitle(gttype, gttInfo, gttLen);
#if 0
        DLOG_DEBUG("extraced GT digits using GetGlobalTitle() type :%d , length :%d , gtdigits :%s",
                gttype,gttLen,gttInfo);
        pbSelfSccpAddr->set_gttlen(gttLen);
        string gtdigits = ""; 
        IWFUtils::TBCDToString(&gttInfo[0], gttLen , gtdigits); 

        DLOG_DEBUG("Copied GT Address Digits : %s",gtdigits.c_str());
        pbSelfSccpAddr->set_globtitle(gtdigits);
        pbSelfSccpAddr->set_gtttype(gttype);
        DLOG_DEBUG("Copied SCCP Address : %s",pbSelfSccpAddr->DebugString().c_str());
#endif
        pbSelfSccpAddr->set_globaltitle(true);
        pbSelfSccpAddr->set_gtttype(gttype);
        pbSelfSccpAddr->set_gttlen(gttLen);
        pbSelfSccpAddr->set_globtitle((void*)gttInfo, gttLen);
    }
#endif
}

SCCP_CalledPartyAddr IwfFsm::GetSelfSccpAddr() {
#ifdef USE_FULL_SCCP_ADDRESS
    return m_selfSccpAddr;
#else
    SCCP_CalledPartyAddr m_selfSccpAddr;
    return m_selfSccpAddr;
#endif
}


void IwfFsm::SetSelfSccpAddr(pbSccpAddress pbSelfSccpAddr)
{
    if (m_pbIwfFsmRepData.has_selfsccpaddr())
    {
        m_pbIwfFsmRepData.clear_selfsccpaddr();
        pbSccpAddress* pbSelfAddr = m_pbIwfFsmRepData.mutable_selfsccpaddr();
        pbSelfAddr->CopyFrom(pbSelfSccpAddr);
    }
    else
    {
        pbSccpAddress* pbSelfAddr = m_pbIwfFsmRepData.mutable_selfsccpaddr();
        pbSelfAddr->CopyFrom(pbSelfSccpAddr);
    }
}

bool IwfFsm::GetSelfSccpAddr(SCCP_CalledPartyAddr& selfSccpAddr)
{
    if (m_pbIwfFsmRepData.has_selfsccpaddr())
    {
        pbSccpAddress pbSelfAddr = m_pbIwfFsmRepData.selfsccpaddr();

        if (pbSelfAddr.has_pointcode())
        {
            selfSccpAddr.SetPointCode(pbSelfAddr.pointcode());
        }

        if (pbSelfAddr.has_ssn())
        {
            selfSccpAddr.SetSSN(pbSelfAddr.ssn());
        }

        selfSccpAddr.SetRouteByPCSSN(pbSelfAddr.routepcssn());
        selfSccpAddr.SetInternationalRouting(pbSelfAddr.internationalroute());
        std::string gtdigits = pbSelfAddr.globtitle();
        CLOG_DEBUG("GTT digits : %s",gtdigits.c_str());
        //ITS_OCTET gttInfo[32] = {0};
        //int gttLen = IWFUtils::StringToTBCD(gtdigits, gttInfo, gtdigits.length());

        //selfSccpAddr.SetGlobalTitle(pbSelfAddr.gtttype(), gttInfo,gttLen);
        selfSccpAddr.SetGlobalTitle(pbSelfAddr.gtttype(), (const ITS_OCTET*)gtdigits.c_str() , gtdigits.length());
        return true;
    }
    return false;
}


int IwfFsm::GetTimerInfo(ETimerType& timerType, STimerInfo& o_sTimerInfo)
{
    for(unsigned int i = 0; i < m_timerList.size(); i++)
    {
        if(m_timerList[i].m_eTimerType == timerType)
        {
            o_sTimerInfo =  m_timerList[i];
            return ITS_SUCCESS;
        }
    }
    return !ITS_SUCCESS;
}

void IwfFsm::SetTimerInfo(STimerInfo& timerInfo)
{
    m_timerList.push_back(timerInfo);
}

void IwfFsm::RemoveTimerInfo(unsigned int& uiTimerId)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());


    vector<STimerInfo>::iterator Itr = m_timerList.begin();

    while (Itr != m_timerList.end())
    {
        if(uiTimerId == (*Itr).m_uiTimerId)            
        {
            DLOG_DEBUG("IwfFsm::RemoveTimerInfo() TimerId: %u, TimerType : %d removed.",
                    (*Itr).m_uiTimerId, (*Itr).m_eTimerType);            
            Itr = m_timerList.erase(Itr);
            break;
        }
        else
            Itr++;
    }
}

void IwfFsm::StopAllTimers()
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    DLOG_DEBUG("StopAllTimers:: Current timerList size : %d, stopping allTimers & clearing the list.",
            m_timerList.size());
    vector<STimerInfo>::iterator Itr = m_timerList.begin();

    while (Itr != m_timerList.end())
    {

        IwfTimer timerObj;
        STimerInfo timerinfo = *Itr;
        if(ITS_SUCCESS == timerObj.StopTimer(timerinfo.m_uiTimerId))
        {
            DLOG_DEBUG("StopAllTimers:: TimerType : %d, TimerId : %u stopped.",
                    timerinfo.m_eTimerType,
                    timerinfo.m_uiTimerId);
        }
        else
        {
            DLOG_INFO("StopAllTimers:: Failed to stop TimerType : %d, TimerId : %u.",timerinfo.m_uiTimerId);
        }
        Itr++;
    }
    m_timerList.clear();    


}

void IwfFsm::GotoPrevState()
{
    DLOG_DEBUG("Rollback State %s -> %s", m_current->GetStateName(), 
            m_prevState->GetStateName());
    m_current = m_prevState;
}

void IwfFsm::ResetTimerInfo()
{
    m_timerList.clear();
}

void IwfFsm::SetIsTCAPEnd(bool isTCAPEnd)
{
    m_pbIwfFsmRepData.set_istcapend(isTCAPEnd);
}

bool IwfFsm::IsTCAPEnd()
{
    return m_pbIwfFsmRepData.istcapend();
}

void IwfFsm::SetStartNoEventTimer(bool noEventTimer)
{
    m_pbIwfFsmRepData.set_startnoeventtimer(noEventTimer);
}

bool IwfFsm::IsStartNoEventTimerSet()
{
    return m_pbIwfFsmRepData.startnoeventtimer();
}

void IwfFsm::SetTcapCptList(TcapCptList &tcapcptlist)
{
    m_tcapCptList = tcapcptlist;
}

TcapCptList* IwfFsm::GetTcapCptList()
{
    return &m_tcapCptList;
}

void IwfFsm::SetFinalUpstrmReqSent(bool isFinalReponseSent)
{
    m_pbIwfFsmRepData.set_isfinalupstrmreqsent(isFinalReponseSent);
}

bool IwfFsm::IsFinalUpstrmReqSent()
{
    return m_pbIwfFsmRepData.isfinalupstrmreqsent();
}

void IwfFsm::StoreOutgoingInvokeId(ITS_OCTET invokeId)
{
    m_outGoingInvokeIdList.push_back(invokeId);
}

vector<ITS_OCTET>& IwfFsm::GetStoredOutGoingInvokeIdList()
{
    return m_outGoingInvokeIdList;
}

void IwfFsm::ResetInvokeIdVector()
{
    if(!m_outGoingInvokeIdList.empty())
    {
        m_outGoingInvokeIdList.clear();
    }
}

void IwfFsm::PurgeSession(bool purge)
{
    m_isSessionPurged = purge;
}

bool IwfFsm::IsSessionPurged()
{
    return m_isSessionPurged;
}

States IwfFsm::GetPreviousStateId() {
    return m_prevState->GetStateId();
}   

const char* IwfFsm::GetPreviousStateName() {
    return m_prevState->GetStateName();
} 

/* This method will update required replicable data which are not moved in
 * protocolBuffer format since they are stored as pointers/entire messages.
 * This method MUST be invoked before the Replicable data is pushed into the
 * ReplicationManager(Couchbase)
 */
int IwfFsm::UpdateIwfFsmReplicableData()
{
    int ret = ITS_SUCCESS;
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::UpdateIwfFsmReplicableData() Entry");
    /*Copy only required data which cannot be moved into ProtoBuff 
     * m_current(only State-Id and Name)
     * m_prevState(only State-Id and Name)
     * m_currRcvdDiaMsg
     * m_currRcvdTcapDlg
     * m_currRcvdTcapCpt
     * m_translator(only Translator-Id & Name)
     * vector<STimerInfo> m_timerList
     */
    try {
        if (m_pbIwfFsmRepData.has_current())
        {
            m_pbIwfFsmRepData.clear_current();
        }
        pbState* currState = m_pbIwfFsmRepData.mutable_current();
        currState->set_id(this->GetCurrentStateId());
        currState->set_name(this->GetCurrentStateName());

        if (m_pbIwfFsmRepData.has_prevstate())
        {
            m_pbIwfFsmRepData.clear_prevstate();
        }
        pbState* prevState = m_pbIwfFsmRepData.mutable_prevstate();
        prevState->set_id(this->GetPreviousStateId());
        prevState->set_name(this->GetPreviousStateName());

        DIA_BASE_CMD *diaCmd = this->GetCurrRcvdDiaMsg();
        if( diaCmd != NULL)
        {
            diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(diaCmd))->GetBaseGenCommand();
            uint32_t authLifeTime = 0;
            uint32_t authGraceTime = 0;
            if (m_pbIwfFsmRepData.has_currrcvddiamsg())
            {
                m_pbIwfFsmRepData.clear_currrcvddiamsg();
            }
            pbDiaMsg *currDiaMsg = m_pbIwfFsmRepData.mutable_currrcvddiamsg();
            currDiaMsg->set_sessionid(diaBaseGenCmd->getSessionId()->value());
            currDiaMsg->set_commandcode(diaBaseGenCmd->getCommandCode());
            currDiaMsg->set_requestbit(diaBaseGenCmd->isRequest());
            if (diaBaseGenCmd->getUserName())
            {
                currDiaMsg->set_username(diaBaseGenCmd->getUserName()->value());
            }

            if (m_pbIwfFsmRepData.has_diameterinfo())
            {
                authLifeTime = m_pbIwfFsmRepData.diameterinfo().lifetime();
                authGraceTime = m_pbIwfFsmRepData.diameterinfo().graceperiod();
                m_pbIwfFsmRepData.clear_diameterinfo();
            }
            pbDiameterSessionData* diameterInfo = m_pbIwfFsmRepData. mutable_diameterinfo();
            diameterInfo->set_peerinst(diaCmd->GetIncomingPeerInst());
            if (diaBaseGenCmd->countAuthorizationLifetime())
            {
                diameterInfo->set_lifetime(diaBaseGenCmd->getAuthorizationLifetime(0)->value());
            }
            else
            {
                diameterInfo->set_lifetime(authLifeTime);
            }
            if (diaBaseGenCmd->countAuthGracePeriod())
            {
                diameterInfo->set_graceperiod(diaBaseGenCmd->getAuthGracePeriod(0)->value());
            }
            else
            {
                diameterInfo->set_graceperiod(authGraceTime);
            }
        }
        TCAP_Dialogue *tcapDlg = this->GetCurrRcvdTcapDlg();
        if (tcapDlg != NULL)
        {
            if (m_pbIwfFsmRepData.has_currrcvdtcapdlg())
            {
                m_pbIwfFsmRepData.clear_currrcvdtcapdlg();
            }
            pbTcapDialogue *currTcapDlg = m_pbIwfFsmRepData.mutable_currrcvdtcapdlg();
            currTcapDlg->set_dialogueid(tcapDlg->GetDialogueID());
            currTcapDlg->set_dialoguetype(tcapDlg->GetDialogueType());
            std::vector<byte> appCtxt;
            tcapDlg->GetApplicationContext(appCtxt);
            std::string context = IWFUtils::VectorToString(appCtxt);
            currTcapDlg->set_applicationcontext(context);
            ITS_OCTET flags = 0x00;
            ITS_OCTET slsK  = 0x00;
            ITS_OCTET prio  = 0x00;
            ITS_OCTET nind  = 0x00;
            tcapDlg->GetQualityOfService(flags, slsK, prio, nind);
            if (currTcapDlg->has_qos())
            {
                currTcapDlg->clear_qos();
            }
            QualityOfService* qos = currTcapDlg->mutable_qos();
            qos->set_flags(flags);
            qos->set_slskey(slsK);
            qos->set_priority(prio);
            qos->set_networkind(nind);
        }
        TCAP_Component *tcapCpt = this->GetCurrRcvdTcapCpt();
        if (tcapCpt != NULL)
        {
            if (m_pbIwfFsmRepData.has_currrcvdtcapcpt())
            {
                m_pbIwfFsmRepData.clear_currrcvdtcapcpt();
            }
            pbTcapComponent *currTcapCpt = m_pbIwfFsmRepData.mutable_currrcvdtcapcpt();
            currTcapCpt->set_lastcomponent(tcapCpt->GetLast());
            currTcapCpt->set_invokeid(tcapCpt->GetInvokeID());
            currTcapCpt->set_componenttype(tcapCpt->GetComponentType());
            //unsigned int opCode;
            //tcapCpt->GetOperation(opCode);
            //currTcapCpt->set_opcode(opCode);
        }

        IwfTranslator* translator = this->GetTranslator();
        if (translator != NULL)
        {
            if (!m_pbIwfFsmRepData.has_translator())
            {
                pbIwfTranslator* trans = m_pbIwfFsmRepData.mutable_translator();
                trans->set_id(translator->Id());
                trans->set_name(translator->Name());
            }
        }

        if (m_pbIwfFsmRepData.timerinfo_size())
        {
            m_pbIwfFsmRepData.clear_timerinfo();
        }
        vector<STimerInfo>::iterator itr = m_timerList.begin();
        while (itr != m_timerList.end())
        {
            STimerInfo timerinfo = *itr;
            /*CLOG_DEBUG("Stored Timer info timerType : %d, TimerKey : %d, StartTime :%d,Duration :%d,Timeout :%d",
                    timerinfo.m_eTimerType,pbIwfTimerData_EKeyType_DIALOG_ID,
                    timerinfo.m_tStartTime,timerinfo.m_uiDuration,timerinfo.m_uiTimerId);*/
            pbIwfTimerData* timerData = m_pbIwfFsmRepData.add_timerinfo();
            timerData->set_m_etimertype((pbIwfTimerData_ETimerType)timerinfo.m_eTimerType);
            timerData->set_m_ekeytype(pbIwfTimerData_EKeyType_DIALOG_ID);
            timerData->set_m_tstarttime((uint32_t)timerinfo.m_tStartTime);
            timerData->set_m_uiduration(timerinfo.m_uiDuration);
            timerData->set_m_uitimerid(timerinfo.m_uiTimerId);
            itr++;
        }

#ifdef USE_FULL_SCCP_ADDRESS
        SCCP_CalledPartyAddr selfSccp = this->GetSelfSccpAddr();
        if (!m_pbIwfFsmRepData.has_selfsccpaddr())
        {
            //DLOG_DEBUG("Self SCCP_CalledParty Address replicating");
            m_pbIwfFsmRepData.clear_selfsccpaddr();
            //DLOG_DEBUG("Creating Mutable_SelfSCCPADDR");
            pbSccpAddress* pbSelfSccpAddr = m_pbIwfFsmRepData.mutable_selfsccpaddr();

            //DLOG_DEBUG("Before Setting hasPc");
            pbSelfSccpAddr->set_haspc(selfSccp.HasPointCode());
            if ( selfSccp.HasPointCode())
            {
                pbSelfSccpAddr->set_pointcode(selfSccp.GetPointCode());
            }
            pbSelfSccpAddr->set_hasssn(selfSccp.HasSSN());
            if (selfSccp.HasSSN())
            {
                pbSelfSccpAddr->set_ssn(selfSccp.GetSSN());
            }
            pbSelfSccpAddr->set_routepcssn(selfSccp.IsRoutedByPCSSN());
            pbSelfSccpAddr->set_internationalroute(selfSccp.IsInternationalRouting());
            pbSelfSccpAddr->set_globaltitle(selfSccp.HasGlobalTitle());
            if (selfSccp.HasGlobalTitle())
            {
                ITS_OCTET gttype = 0;
                ITS_USHORT gttLen = 0;
                ITS_OCTET gttInfo[64] = {0};
                // Get gloabal title from address
                selfSccp.GetGlobalTitle(gttype, gttInfo, gttLen);
                /*DLOG_DEBUG("extraced GT digits using GetGlobalTitle() type :%d , length :%d , gtdigits :%s",
                        gttype,gttLen,gttInfo);*/
                pbSelfSccpAddr->set_gttlen(gttLen);
                string gtdigits = ""; 
                IWFUtils::TBCDToString(&gttInfo[0], gttLen , gtdigits); 

                //DLOG_DEBUG("Copied GT Address Digits : %s",gtdigits.c_str());
                pbSelfSccpAddr->set_globtitle(gtdigits);
                pbSelfSccpAddr->set_gtttype(gttype);
                //DLOG_DEBUG("Copied SCCP Address : %s",pbSelfSccpAddr->DebugString().c_str());
            }
        }
#endif
    }
    catch(diameter::CodecExceptionToApp& e) 
    {
        DLOG_ERROR("Exception: %s, Error Cause: %s ", e.name(), e.what());
        DLOG_ERROR("errorcode for sessionId %s is %d", e.sessionId(), e.errcode());
        std::vector<int> missingAvpList = e.getMissingAVPList();
        for(unsigned int i = 0 ; i<missingAvpList.size() ; i++)
        {     
            DLOG_ERROR("Missing avp : %d",missingAvpList[i]);
        }
    }
    catch(AsnDecodeError &exc) 
    {
        DLOG_ERROR("### ASN Decode Error ### <%s>", exc.GetDescription().c_str());
        ret = !ITS_SUCCESS;
    }
    catch(std::exception& e)
    {
        DLOG_ERROR("### Exception on decode %s ###", e.what());
        ret = !ITS_SUCCESS;
    }
    catch(...)
    {
        DLOG_ERROR("### Unknown exception on Decode ###");
        ret = !ITS_SUCCESS;
    }

    //DLOG_DEBUG("TransactionManager::UpdateIwfFsmReplicableData() Exit");
    return ret;
}

uint32_t IwfFsm::GetTcapLocalTid()
{
    return m_pbIwfFsmRepData.tcapinfo().ltid();
}

void IwfFsm::SetTcapLocalTid(uint32_t ltid)
{
    m_pbIwfFsmRepData.mutable_tcapinfo()->set_ltid(ltid);
}

uint32_t IwfFsm::GetTcapRemoteTid()
{
    return m_pbIwfFsmRepData.tcapinfo().rtid();
}

void IwfFsm::SetTcapRemoteTid(const uint32_t rtid)
{
    m_pbIwfFsmRepData.mutable_tcapinfo()->set_rtid(rtid);
}

int IwfFsm::GetTcapOrgAddr(SCCP_ADDR& orgAddr)
{
    pbSCCP_ADDR pbOrgAddr = m_pbIwfFsmRepData.tcapinfo().oaddr();
    orgAddr.len = pbOrgAddr.addr().length();
    memcpy(orgAddr.data, pbOrgAddr.addr().c_str(),SCCP_MAX_ADDR_LEN);
    return ITS_SUCCESS;
}

void IwfFsm::SetTcapOrgAddr(SCCP_ADDR& oAddr)
{
    pbSCCP_ADDR* pbOrgAddr = m_pbIwfFsmRepData.mutable_tcapinfo()->mutable_oaddr();
    string orgAddr = "";
    IWFUtils::TBCDToString(&(oAddr.data[0]), oAddr.len , orgAddr);
    pbOrgAddr->set_addr(orgAddr);
    //std::string orgAddr((const char*)oAddr.data);
    //pbOrgAddr->set_addr(orgAddr);
    pbOrgAddr->set_length(oAddr.len);

    //CLOG_DEBUG("converted OrgAddr : %s",orgAddr.c_str());
    //CLOG_DEBUG("received OrgAddr : %x",oAddr.data);
}

int IwfFsm::GetTcapDestAddr(SCCP_ADDR& destAddr)
{
    pbSCCP_ADDR pbDestAddr = m_pbIwfFsmRepData.tcapinfo().daddr();
    destAddr.len = pbDestAddr.addr().length();
    memcpy(destAddr.data, pbDestAddr.addr().c_str(),SCCP_MAX_ADDR_LEN);
    return ITS_SUCCESS;
}

void IwfFsm::SetTcapDestAddr(SCCP_ADDR& dAddr)
{
    pbSCCP_ADDR* pbDestAddr = m_pbIwfFsmRepData.mutable_tcapinfo()->mutable_daddr();
    string destAddr = "";
    IWFUtils::TBCDToString(&(dAddr.data[0]), dAddr.len , destAddr);
    pbDestAddr->set_addr(destAddr);

    //pbDestAddr->set_addr((const char*)dAddr.data);
    pbDestAddr->set_length(dAddr.len);

    //CLOG_DEBUG("converted DestAddr : %s",destAddr.c_str());
    //CLOG_DEBUG("received DestAddr : %x",dAddr.data);
}

int IwfFsm::GetTcapMtp3Label(MTP3_HEADER& mtpHdr)
{
    pbMtp3_Header pbMtpHdr = m_pbIwfFsmRepData.tcapinfo().label();
    mtpHdr.sio = pbMtpHdr.sio();
#ifndef USE_ANSI_SCCP
    memcpy(mtpHdr.label.data, pbMtpHdr.label().c_str(),6);
#endif
    return ITS_SUCCESS;
}

void IwfFsm::SetTcapMtp3Label(MTP3_HEADER& label)
{
    pbMtp3_Header* pbMtpHdr = m_pbIwfFsmRepData.mutable_tcapinfo()->mutable_label();
    pbMtpHdr->set_sio(label.sio);
#ifndef USE_ANSI_SCCP
    pbMtpHdr->set_label((const char*)label.label.data);
#endif
}

void IwfFsm::SetReplicaIndexKey(uint32_t value)
{
    m_pbIwfFsmRepData.set_freelistkey(value);
}

uint32_t IwfFsm::GetReplicaIndexKey()
{
    return m_pbIwfFsmRepData.freelistkey();
}

void IwfFsm::SetSessionAcrossSwitchover(bool value)
{
    m_acrossSwitchover = value;
}

bool IwfFsm::IsSessionAcrossSwitchover()
{
    return m_acrossSwitchover;
}

void IwfFsm::SetActionRuleName(std::string& rrbRuleName)
{
    m_pbIwfFsmRepData.set_actionrulename(rrbRuleName);
}

std::string IwfFsm::GetActionRuleName()
{
    return m_pbIwfFsmRepData.actionrulename();
}
