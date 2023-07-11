#include "app_timer.h"

AppTimer::AppTimer()
{
}/* End of Constructor */

AppTimer::~AppTimer()
{
}/* End of Constructor */

AppTimer::AppTimer(const AppTimer& ocTimerMgr)
{
}/* End of Copy Constructor */

unsigned int AppTimer::StartTimer(ETimerType eType, STimerContext osCtxt, unsigned uiDuration)
{
   unsigned int uiTimerId = TIMERS_StartTimer(ITS_DEFAULT_USER_SRC, 
                                      uiDuration,
                                      &osCtxt,  
                                      sizeof(STimerContext));

   return uiTimerId;
}/* End of AppTimer::StartTimer() */

int AppTimer::StopTimer(unsigned int uiTimerId)
{
   TIMERS_CancelTimer(uiTimerId);
   return 0; 
}/* End of AppTimer::StopTimer() */

int AppTimer::GetElapsedTime(STimerInfo& osTimerInfo, unsigned int& uiElapsedDuration)
{
   int iRetVal = 0;
   struct timeval tv;
   gettimeofday(&tv, 0);

   if(osTimerInfo.m_tStartTime != 0)
   {
       //DLOG_DEBUG("osTimerInfo.m_tStartTime : %d", osTimerInfo.m_tStartTime);
       uiElapsedDuration = tv.tv_sec - osTimerInfo.m_tStartTime;
   }
   return iRetVal; 
}/* End of AppTimer::GetElapsedTime() */


