#include "iwf_timer.h"

IwfTimer::IwfTimer()
{
}/* End of Constructor */

IwfTimer::~IwfTimer()
{
}/* End of Constructor */

IwfTimer::IwfTimer(const IwfTimer& ocTimerMgr)
{
}/* End of Copy Constructor */

unsigned int IwfTimer::StartTimer(ETimerType eType, STimerContext osCtxt, unsigned uiDuration)
{
   unsigned int uiTimerId = TIMERS_StartTimer(ITS_DEFAULT_USER_SRC, 
                                      uiDuration,
                                      &osCtxt,  
                                      sizeof(STimerContext));

   return uiTimerId;
}/* End of IwfTimer::StartTimer() */

int IwfTimer::StopTimer(unsigned int uiTimerId)
{
   TIMERS_CancelTimer(uiTimerId);
   return 0; 
}/* End of IwfTimer::StopTimer() */

int IwfTimer::GetElapsedTime(STimerInfo& osTimerInfo, unsigned int& uiElapsedDuration)
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
}/* End of IwfTimer::GetElapsedTime() */

#if 0
int IwfTimer::StopAllTimers()
{
   map<unsigned int, STimerInfo>::iterator itrMap = m_mapTimerInfo.begin();
   while (itrMap != m_mapTimerInfo.end())
       TIMERS_CancelTimer(itrMap->first);

   m_mapTimerInfo.clear();
}/* End of IwfTimer::StopAllTimers() */
#endif
