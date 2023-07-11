#ifndef _APP_TIMER_H_
#define _APP_TIMER_H_
/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: app_timer.h,v $
 * LOG: Revision 1.1.4.2.4.1  2014/07/28 11:01:06  jkchaitanya
 * LOG: changes for ACH timer handling
 * LOG:
 * LOG: Revision 1.1.4.2  2013/12/06 09:46:09  jkchaitanya
 * LOG: PerfSim is taken from B-IWF-0100-01 branch
 * LOG:
 * LOG: Revision 1.1.2.1  2013/11/15 11:05:25  jsarvesh
 * LOG: IWF Performance for CAP-Ro
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/31 14:52:10  lakshman
 * LOG: add includes.
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_timer.h,v 1.1.4.2.4.1 2014/07/28 11:01:06 jkchaitanya Exp $"


#include <its++.h>
#include <engine++.h>
#include <its_timers.h>
#include <app_timer_defines.h>
#include <sys/time.h>

using namespace std;

class AppTimer
{
    public:
        AppTimer();
        virtual ~AppTimer();
        AppTimer(const AppTimer&);
        unsigned int StartTimer(ETimerType eType, STimerContext osCtxt, unsigned int uiTimeoutSecs);
        int StopTimer(unsigned int uiTimerId);
        int GetElapsedTime(STimerInfo& osTimerInfo, unsigned int& uiElapsedTime);
};//End of AppTimerManager

#endif //End of _APP_TIMER_MANAGER_
