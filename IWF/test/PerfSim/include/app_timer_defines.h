#ifndef _APP_TIMER_DEFINES_H_
#define _APP_TIMER_DEFINES_H_



enum ETimerType
{
    ALLOCATED_GSU_TIMER = 1,
    FOLLOW_ON_IVR_TIMER,
    INVALID_TIMER=-1
};

enum EKeyType
{
    INVLAID_KEY = -1,
    DIALOG_ID
};

struct STimerContext
{
    ETimerType m_eTimerType;
    EKeyType m_eKeyType;
    unsigned int m_uiDlgId;
    STimerContext():m_uiDlgId(0)
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

#endif //End of _APP_TIMER_DEFINES_H_
