#ifndef _IWF_TIMER_DEFINES_H_
#define _IWF_TIMER_DEFINES_H_



enum ETimerType
{
    NO_EVENT_TIMER = 1,
    FAKE_ACH_TIMER,
    ACTIVITY_TIMER,
    ACH_DELTA_TIMER,
    ACR_TIMER,
    CONNECT_MAX_CALL_DURATION,
    ACTIVITY_RESPONSE_TIMER,
    IWF_SUBSCRIBER_AUDIT_TIMER,
    IWF_DCCA_TX_TIMER,
    IWF_BULK_FETCH_TIMER,
    IWF_PENDING_QUEUE_EXPIRY,
    INVALID_TIMER=-1
};

enum EKeyType
{
    INVLAID_KEY = -1,
    SESSION_ID = 1,
    DIALOG_ID,
    SUBSC_AUDIT,
    BULK_FETCH,
    PENDING_QUEUE_EXPIRY
};

struct STimerContext
{
    ETimerType m_eTimerType;
    EKeyType m_eKeyType;
    std::string  m_strSessionId;
    unsigned int m_uiDlgId;
    STimerContext():m_strSessionId(""),
                    m_uiDlgId(0)
    {
    }
};//End of STimerContext

struct STimerInfo
{
    ETimerType m_eTimerType;
    time_t m_tStartTime;
    unsigned int m_uiDuration;
    unsigned int m_uiTimerId;

    STimerInfo():m_tStartTime(0),
                 m_uiDuration(0),
                 m_uiTimerId(0)
    {
    }
};//End of STimerInfo

#endif //End of _IWF_TIMER_DEFINES_H_
