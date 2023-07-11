#ifndef _IWF_TIMER_H_
#define _IWF_TIMER_H_

#include <its++.h>
#include <engine++.h>
#include <its_timers.h>
#include <iwf_timer_defines.h>
#include <sys/time.h>



using namespace std;

class IwfTimer
{
    public:
        IwfTimer();
        virtual ~IwfTimer();
        IwfTimer(const IwfTimer&);
        unsigned int StartTimer(ETimerType eType, STimerContext osCtxt, unsigned int uiTimeoutSecs);
        int StopTimer(unsigned int uiTimerId);
        int GetElapsedTime(STimerInfo& osTimerInfo, unsigned int& uiElapsedTime);
};//End of IwfTimerManager

#endif //End of _IWF_TIMER_MANAGER_
