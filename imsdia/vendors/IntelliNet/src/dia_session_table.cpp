/*********************************-*CPP*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: dia_session_table.cpp,v $
 * LOG: Revision 3.13.4.1.36.2.4.3.12.1  2014/10/27 08:28:39  millayaraja
 * LOG: changes for HA HotStandBy
 * LOG:
 * LOG: Revision 3.13.4.1.36.2.4.3  2014/01/06 09:22:32  cprem
 * LOG: Changes in diameter stack to support session replication. Review request 1611.
 * LOG:
 * LOG: Revision 3.13.4.1.36.2.4.2  2013/12/19 10:01:13  ncshivakumar
 * LOG: fix for Bug 2655
 * LOG:
 * LOG: Revision 3.13.4.1.36.2.4.1  2013/12/13 09:34:58  vsarath
 * LOG: Merged the session-splict changes
 * LOG:
 * LOG: Revision 3.13.4.1.36.2  2013/03/22 05:56:57  jvikram
 * LOG: Corrected the issues related to message handling related to same session id
 * LOG: by queuing the messages. Also included debug logs.
 * LOG:
 * LOG: Revision 3.13.4.1.36.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.13.4.1  2012/03/07 13:23:08  brajappa
 * LOG: Changes made for the DRE demo
 * LOG:
 * LOG: Revision 3.13  2010/07/07 08:24:46  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 3.12  2009/12/08 08:19:28  sureshj
 * LOG: IDS Core dump when destination-realm and destination-Host AVPs
 * LOG: in command.
 * LOG:
 * LOG: Revision 3.11  2009/11/26 08:37:09  sureshj
 * LOG: mutex lock introduced in RemoveEntry to avoid race condition
 * LOG: Motorola helpdesk ticket  2266.
 * LOG:
 * LOG: Revision 3.10  2009/11/12 12:17:35  sureshj
 * LOG: AUTH_SESSION_TIMER Id is printed negative. changed to +ve value.
 * LOG: Motorola ticket 2263.
 * LOG:
 * LOG: Revision 3.9  2009/07/13 06:56:25  rajeshak
 * LOG: Reverting back session table changes.
 * LOG:
 * LOG: Revision 3.8  2009/06/29 14:54:53  rajeshak
 * LOG: Changes done for performance enhancement (splitting the session table).
 * LOG:
 * LOG: Revision 3.7  2009/03/19 12:36:10  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.6  2008/12/23 08:32:38  rajeshak
 * LOG: Moved and renamed InitNInsertAcctSession & InitNInsertAuthSession function
 * LOG: from dia_utils to dia_session_table
 * LOG:
 * LOG: Revision 3.5  2008/12/12 18:30:48  rajeshak
 * LOG: Lightweight Decode for base AVPS
* LOG: New Command class is introduced (BaseCommand)
    * LOG:
    * LOG: Revision 3.4  2008/10/31 05:55:55  nvijikumar
    * LOG: IssueID:1189
    * LOG: FeatureID:none
    * LOG: Description: Code Optimization and  stack tunning
    * LOG:
    * LOG: Revision 3.3  2008/10/28 12:06:28  nvijikumar
    * LOG: IssueID: none
    * LOG: FeatureID: none
    * LOG: Description: Porting Performance changes from 3.0 branch
    * LOG:
    * LOG: Revision 3.2  2008/08/21 06:07:08  yranade
    * LOG: Added APIs to print QSize, SessionTable size and SessionTable details.
    * LOG:
    * LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
    * LOG: Start GA 3.0
    * LOG:
    * LOG: Revision 2.18  2008/03/27 12:14:08  hbhatnagar
    * LOG: Converting 2.1 branch to CURRENT
    * LOG:
    * LOG: Revision 2.16.6.2  2007/05/28 14:29:56  nvijikumar
    * LOG: Set Proper value for AuthLifeTime timer if SessionTimeout and AuthLifetime
    * LOG: values are same.
    * LOG:
    * LOG: Revision 2.16.6.1  2007/05/25 03:54:33  nvijikumar
    * LOG: 1. Modification for ReStartAllAuthTimers fun to Start perticular timer if
    * LOG:    either of SessionTimeout AuthorizationLifetime AVPs exist.
    * LOG: 2. Provided new fun called ReStartAuthTimers which restarts timers only
    * LOG:    if perticular AVP exists in the msg.
    * LOG:
    * LOG: Revision 2.16  2006/12/20 15:54:05  nvijikumar
    * LOG: Elimination of multiple ITS_FindFeature function calls(DCCA & Redundancy).
    * LOG:
    * LOG: Revision 2.15  2006/11/26 19:45:35  tpanda
    * LOG: Inbound and outbound session index syncronisation
    * LOG:
    * LOG: Revision 2.14  2006/11/25 03:57:20  tpanda
    * LOG: Changes for Msg based redundancy
    * LOG:
    * LOG: Revision 2.13  2006/11/16 14:49:16  tpanda
    * LOG: Redundancy support for ITS-Diameter--Baseline code
    * LOG:
    * LOG: Revision 2.12  2006/10/30 12:14:05  yranade
    * LOG: If SessionTimeout is less than LifeTime, reset lifetime to 2 secs less
    * LOG: than SessionTimeout.
    * LOG:
    * LOG: Revision 2.11  2006/10/27 09:39:24  yranade
    * LOG: Added method to ReStart all AuthTimers.
    * LOG:
    * LOG: Revision 2.10  2006/10/24 14:15:26  yranade
    * LOG: Update trace. Don't start timer when inserting new entry.
    * LOG:
    * LOG: Revision 2.9  2006/10/16 06:30:22  yranade
    * LOG: Generate Client/Server Session Index. Will need update for redundancy.
    * LOG: Add API's to stop all timers.
    * LOG:
    * LOG: Revision 2.7  2006/10/09 13:33:41  yranade
    * LOG: StopTimer while removing entry.
    * LOG:
    * LOG: Revision 2.6  2006/10/09 11:31:08  yranade
    * LOG: Add local cache for SessionTable.
    * LOG:
    * LOG: Revision 2.5  2006/10/09 06:26:51  yranade
    * LOG: Timer related updates. Still to be finished.
    * LOG:
    * LOG: Revision 2.4  2006/10/07 12:24:55  yranade
    * LOG: Today's round of updates.
    * LOG:
    * LOG: Revision 2.3  2006/10/05 13:21:54  yranade
    * LOG: Getting there.
    * LOG:
    * LOG: Revision 2.2  2006/09/14 09:43:12  nvijikumar
    * LOG: Implementation of Print function.
    * LOG:
    * LOG: Revision 2.1  2006/09/13 09:22:44  yranade
    * LOG: Start GA 1.1
    * LOG:
    * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
* LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
    * LOG:
    * ID: $Id: dia_session_table.cpp,v 3.13.4.1.36.2.4.3.12.1 2014/10/27 08:28:39 millayaraja Exp $
    ****************************************************************************/
#ident "$Id: dia_session_table.cpp,v 3.13.4.1.36.2.4.3.12.1 2014/10/27 08:28:39 millayaraja Exp $"

#include <stdlib.h>
#include <iostream>

#include <its++.h>
#include <engine++.h>
#include <its_timers.h>

#include <dia_err.h>
#include <dia_trace.h>
#include <dia_session_table.h>
#include <dia_session_auth_fsm.h>
#include <dia_session_acct_fsm.h>
#include <dia_msg_router.h>
#include <dia_incoming_msg_q.h>

#if defined(ITS_STD_NAMESPACE)
    using namespace std;
    using namespace its;
    using namespace engine;
    using namespace diameter::base;
#endif

    /*
     * For the redundancy
     */


#define DSM_LockTable             DSM_LockTableLocal
#define DSM_UnlockTable           DSM_UnlockTableLocal
#define DSM_AllocNoLock           DSM_AllocNoLockLocal
#define DSM_FindNoLock            DSM_FindNoLockLocal
#define DSM_FreeNoLock            DSM_FreeNoLockLocal
#define DSM_CommitNoLock          DSM_CommitNoLockLocal
#define DSM_Alloc                 DSM_AllocLocal
#define DSM_Find                  DSM_FindLocal
#define DSM_Free                  DSM_FreeLocal
#define DSM_Commit                DSM_CommitLocal 


    ITS_Mutex SessionTable::guard(0);
    ITS_Mutex SessionTable::lock(0);

    static SessionTable *sTable = NULL;
    static ITS_Mutex  __SESServGate(0);
    static ITS_Mutex  __SESGate(0);

    bool SessionTable::replicateSessions = false;
    createSessionCbk SessionTable::sessCreateCbk = NULL;
    deleteSessionCbk SessionTable::sessDeleteCbk = NULL;
    updateSessionCbk SessionTable::sessUpdateCbk = NULL;
    fetchSessionCbk SessionTable::sessFetchCbk = NULL;

SessionTable::SessionTable()
{}

SessionTable::~SessionTable()
{
}

    SessionTable*
SessionTable::GetSessionTable()
{

    if (sTable == NULL)
    {
        /* Moved inside if Due to Performance issue */
        const_cast<ITS_Mutex&>(guard).Acquire();

        sTable = new SessionTable;

        const_cast<ITS_Mutex&>(guard).Release();
    }

    return sTable;
}

    int 
SessionTable::AllocateClientSessionIndex(unsigned int& sessId)
{
    int i;
    static ITS_UINT nextSessionId = 0;
    static bool fFirstTime = true;
    static ITS_Class redunClass = itsDiaConfig.GetRedundancyFeature();

    if (fFirstTime)
    {
        void* ret=NULL;
        int error;
        fFirstTime = false;
        ITS_UINT sessIdxkey = ITS_DIA_OUTBOUND_SESS_INDEX_ENTRY;
        while (((ret = DSM_Find(SESSION_TABLE_FT_GROUP_ID,
                            SESSION_TABLE_ID,
                            (ITS_OCTET*)&sessIdxkey,
                            sizeof(ITS_UINT),
                            &error)) == NULL) &&
                (error == ITS_EINUSE))
        {
            TIMERS_USleep(100);
        }
        if (ret)
        {
            nextSessionId = *((ITS_UINT*)ret);
        }
    }

    const_cast<ITS_Mutex&>(__SESGate).Acquire();

    for (i = 0; i < DIA_DIR_BIT; i++)
    {
        nextSessionId++;
        sessId = nextSessionId;
        if (redunClass && 
                REDUNDANCY_CONFIGURED_TYPE(redunClass) == ITS_ACTIVE_ACTIVE)
        {
            switch (DSM_GetNodeId())
            {
                case 2 :
                    sessId += (sessId % 2); //even index
                    break;
                case 1 : //odd index
                    {
                        if ((sessId % 2) == 0)
                        {
                            sessId ++;
                        }
                    }
            }
        }

        /* The leading ++ ensures that nextSessionId is never 0 */
        if (sessId >= DIA_DIR_BIT)
        {
            nextSessionId = 0;

            continue;
        }
        const_cast<ITS_Mutex&>(__SESGate).Release();
        return (ITS_SUCCESS);
    }
    const_cast<ITS_Mutex&>(__SESGate).Release();
    return (ITS_ENOMSGSPACE);
}

    int
SessionTable::AllocateServerSessionIndex(unsigned int& sessId)
{
    int i;
    static ITS_UINT nextSid = DIA_DIR_BIT;
    static bool fFirstTime = true;
    ITS_Class redunClass = itsDiaConfig.GetRedundancyFeature();

    if (fFirstTime)
    {
        void* ret=NULL;
        int error;
        fFirstTime = false;
        ITS_UINT sessIdxkey = ITS_DIA_INBOUND_SESS_INDEX_ENTRY;
        while (((ret = DSM_Find(SESSION_TABLE_FT_GROUP_ID,
                            SESSION_TABLE_ID,
                            (ITS_OCTET*)&sessIdxkey,
                            sizeof(ITS_UINT),
                            &error)) == NULL) &&
                (error == ITS_EINUSE))
        {
            TIMERS_USleep(100);
        }
        if (ret)
        {
            nextSid = *((ITS_UINT*)ret);
        }
    }
    const_cast<ITS_Mutex&>(__SESServGate).Acquire();

    for (i = 0; i < DIA_DIR_BIT; i++)
    {
        nextSid++;
        sessId = nextSid;
        if (redunClass && 
                REDUNDANCY_CONFIGURED_TYPE(redunClass) == ITS_ACTIVE_ACTIVE)
        {
            switch (DSM_GetNodeId())
            {
                case 2 :
                    sessId += (sessId % 2); //even index
                    break;
                case 1 : //odd index
                    {
                        if ((sessId % 2) == 0)
                        {
                            sessId ++;
                        }
                    }
            }
        }
        if (sessId  > 0xFFFF)
        {
            nextSid = DIA_DIR_BIT;
            continue;
        }
        const_cast<ITS_Mutex&>(__SESServGate).Release();
        return (ITS_SUCCESS);
    }
    const_cast<ITS_Mutex&>(__SESServGate).Release();
    return (ITS_ENOMSGSPACE);
}


    unsigned int 
SessionTable::GenerateSessionIndex(const char* ph)
{
    unsigned int h = 0;
    unsigned int g;

    for(; *ph ; ph++)
    {
        h = (h << 4) + *ph;
        if( (g = h & 0xF0000000) != 0)
            h = (h ^ (g >> 24)) & ~0xF0000000;
    }

    return (h % 19997);
}

    static ITS_BOOLEAN
IsTimerValid(ITS_SERIAL timer)
{
    if (timer != TIMER_BAD_SERIAL)
    {
        return ITS_TRUE;
    }
    return ITS_FALSE;
}

void
SessionTable::Lock() const
{
    int res = const_cast<ITS_Mutex&>(lock).Acquire();

    if (res != ITS_SUCCESS)
    {
        ITS_THROW_ERROR(res);
    }
}

void
SessionTable::Unlock() const
{
    int res = const_cast<ITS_Mutex&>(lock).Release();

    if (res != ITS_SUCCESS)
    {
        ITS_THROW_ERROR(res);
    }
}

/* Stops and Restarts all Auth Timers, either based on
   AVP's in the msg, or thru configuration
   */

    int
SessionTable::ReStartAllAuthTimers(SESSION_ENTRY *entry, DIA_BASE_CMD *msg)
{
    ITS_UINT st = 0, lt = 0, gp = 0;

    if (entry == NULL || msg == NULL)
    {
        return (!ITS_SUCCESS);
    }

    string sessionId = msg->getSessionId()->value();

    SESSION_TABLE->StopAllAuthTimers(entry);

    if (msg->getSessionTimeout())
    {
        DT_DBG(("Msg Contains Session Timeout"));
        st = msg->getSessionTimeout()->value();
    }
    else
    {
        st = itsDiaConfig.GetAuthSessionConfig().GetTimeout();
    }

    if (msg->getAuthorizationLifetime())
    {
        DT_DBG(("Msg Contains AuthLifetime"));
        lt = msg->getAuthorizationLifetime()->value();
    }
    else
    {
        lt = itsDiaConfig.GetAuthSessionConfig().GetLifeTime();
    }
    if (msg->getAuthGracePeriod())
    {
        DT_DBG(("Msg Contains AuthGracePeriod"));
        gp = msg->getAuthGracePeriod()->value();
    }
    else
    {
        gp = itsDiaConfig.GetAuthSessionConfig().GetGracePeriod();
    }

    if ((msg->getSessionTimeout() && msg->getAuthorizationLifetime()) ||
            (!msg->getSessionTimeout() && !msg->getAuthorizationLifetime()))
    {
        if (st <= lt)
        {
            DT_WRN(("SessionTimeout %d Less Than LifeTime %d...Overriding",
                        st, lt));

            lt = st - 2;

            DT_WRN(("New Values:: SessionTimeout %d, LifeTime %d",st, lt));
        }

        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_TIMER,
                st,
                entry);

        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_LIFETIME,
                lt,
                entry);

        DT_DBG(("SessionTimeout = %d , AuthLifetime = %d, AuthGracePeriod = %d",
                    st, lt, gp));
    }
    else if (msg->getSessionTimeout())
    {
        DT_DBG(("Msg Contains Session Timeout"));
        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_TIMER,
                st,
                entry);
        DT_DBG((" SessionTimeout = %d",st));
    }
    else
    {
        DT_DBG(("Msg Contains AuthLifetime"));
        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_LIFETIME,
                lt,
                entry);
        DT_DBG((" AuthLifetime = %d",lt));
    }

    DIA_SE_AUTH_TIMERS(entry).gracePeriod = gp;

    return (ITS_SUCCESS);
}


    int
SessionTable::ReStartAllAuthTimers(SESSION_ENTRY *entry, DIA_GEN_CMD *msg)
{
    ITS_UINT st = 0, lt = 0, gp = 0;

    if (entry == NULL || msg == NULL)
    {
        return (!ITS_SUCCESS);
    }

    string sessionId = msg->getSessionId()->value();

    SESSION_TABLE->StopAllAuthTimers(entry);

    if (msg->getSessionTimeout())
    {
        DT_DBG(("Msg Contains Session Timeout"));
        st = msg->getSessionTimeout()->value();
    }
    else
    {
        st = itsDiaConfig.GetAuthSessionConfig().GetTimeout();
    }

    if (msg->getAuthorizationLifetime())
    {
        DT_DBG(("Msg Contains AuthLifetime"));
        lt = msg->getAuthorizationLifetime()->value();
    }
    else
    {
        lt = itsDiaConfig.GetAuthSessionConfig().GetLifeTime();
    }

    if (msg->getAuthGracePeriod())
    {
        DT_DBG(("Msg Contains AuthGracePeriod"));
        gp = msg->getAuthGracePeriod()->value();
    }
    else
    {
        gp = itsDiaConfig.GetAuthSessionConfig().GetGracePeriod();
    }

    if ((msg->getSessionTimeout() && msg->getAuthorizationLifetime()) ||
            (!msg->getSessionTimeout() && !msg->getAuthorizationLifetime()))
    {
        if (st <= lt)
        {
            DT_WRN(("SessionTimeout %d Less Than LifeTime %d...Overriding",
                        st, lt));

            lt = st - 2;

            DT_WRN(("New Values:: SessionTimeout %d, LifeTime %d",st, lt));
        }

        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_TIMER,
                st,
                entry);

        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_LIFETIME,
                lt,
                entry);

        DT_DBG(("SessionTimeout = %d , AuthLifetime = %d, AuthGracePeriod = %d",
                    st, lt, gp));
    }
    else if (msg->getSessionTimeout())
    {
        DT_DBG(("Msg Contains Session Timeout"));
        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_TIMER,
                st,
                entry);
        DT_DBG((" SessionTimeout = %d",st));
    }
    else 
    {
        DT_DBG(("Msg Contains AuthLifetime"));
        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_LIFETIME,
                lt,
                entry);
        DT_DBG((" AuthLifetime = %d",lt));
    }

    DIA_SE_AUTH_TIMERS(entry).gracePeriod = gp;

    return (ITS_SUCCESS);
}

/*
 * Stops and starts Auth Timers, based on AVP's values.
 */
    int
SessionTable::ReStartAuthTimers(SESSION_ENTRY *entry, DIA_GEN_CMD *msg)
{
    ITS_UINT st = 0, lt = 0, gp = 0;

    if (entry == NULL || msg == NULL)
    {
        return (!ITS_SUCCESS);
    }

    string sessionId = msg->getSessionId()->value();

    if (msg->getSessionTimeout() && msg->getAuthorizationLifetime())
    {
        DT_DBG(("Msg Contains both SessionTimeout and AuthorizationLifetime"));
        st = msg->getSessionTimeout()->value();
        lt = msg->getAuthorizationLifetime()->value();

        if (st <= lt)
        {
            DT_WRN(("SessionTimeout %d Less Than LifeTime %d...Overriding",
                        st, lt));
            lt = st - 2;
            DT_WRN(("New Values:: SessionTimeout %d, LifeTime %d",st, lt));
        }

        /* Stop Timer */
        SESSION_TABLE->StopAllAuthTimers(entry);

        /* Start Timer */
        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_TIMER,
                st, entry);
        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_LIFETIME,
                lt, entry);

        DT_DBG((" SessionTimeout = %d, LifeTime %d",st, lt));
    }
    else if (msg->getSessionTimeout())
    {
        DT_DBG(("Msg Contains Session Timeout"));
        st = msg->getSessionTimeout()->value();

        /* Stop Timer */
        SESSION_TABLE->StopAllAuthTimers(entry);

        /* Start Timer */
        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_TIMER,
                st, entry);
        DT_DBG((" SessionTimeout = %d",st));
    }
    else if (msg->getAuthorizationLifetime())
    {
        DT_DBG(("Msg Contains AuthLifetime"));
        lt = msg->getAuthorizationLifetime()->value();

        /* Stop Timer */
        SESSION_TABLE->StopAllAuthTimers(entry);

        /* Start Timer */
        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_LIFETIME,
                lt, entry);

        DT_DBG((" AuthLifetime = %d",lt));
    }

    if (msg->getAuthGracePeriod())
    {
        DT_DBG(("Msg Contains AuthGracePeriod"));
        gp = msg->getAuthGracePeriod()->value();
        DT_DBG((" AuthGracePeriod = %d",gp));
    }
    else
    {
        gp = itsDiaConfig.GetAuthSessionConfig().GetGracePeriod();
    }

    DIA_SE_AUTH_TIMERS(entry).gracePeriod = gp;

    return (ITS_SUCCESS);
}

    int
SessionTable::ReStartAuthTimers(SESSION_ENTRY *entry, DIA_BASE_CMD *msg)
{
    ITS_UINT st = 0, lt = 0, gp = 0;

    if (entry == NULL || msg == NULL)
    {
        return (!ITS_SUCCESS);
    }

    string sessionId = msg->getSessionId()->value();

    if (msg->getSessionTimeout() && msg->getAuthorizationLifetime())
    {
        DT_DBG(("Msg Contains both SessionTimeout and AuthorizationLifetime"));
        st = msg->getSessionTimeout()->value();
        lt = msg->getAuthorizationLifetime()->value();

        if (st <= lt)
        {
            DT_WRN(("SessionTimeout %d Less Than LifeTime %d...Overriding",
                        st, lt));
            lt = st - 2;
            DT_WRN(("New Values:: SessionTimeout %d, LifeTime %d",st, lt));
        }

        /* Stop Timer */
        SESSION_TABLE->StopAllAuthTimers(entry);

        /* Start Timer */
        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_TIMER,
                st, entry);
        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_LIFETIME,
                lt, entry);

        DT_DBG((" SessionTimeout = %d, LifeTime %d",st, lt));
    }
    else if (msg->getSessionTimeout())
    {
        DT_DBG(("Msg Contains Session Timeout"));
        st = msg->getSessionTimeout()->value();

        /* Stop Timer */
        SESSION_TABLE->StopAllAuthTimers(entry);

        /* Start Timer */
        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_TIMER,
                st, entry);
        DT_DBG((" SessionTimeout = %d",st));
    }
    else if (msg->getAuthorizationLifetime())
    {
        DT_DBG(("Msg Contains AuthLifetime"));
        lt = msg->getAuthorizationLifetime()->value();

        /* Stop Timer */
        SESSION_TABLE->StopAllAuthTimers(entry);

        /* Start Timer */
        SESSION_TABLE->StartTimer(sessionId.c_str(),
                AUTH_SESSION_LIFETIME,
                lt, entry);

        DT_DBG((" AuthLifetime = %d",lt));
    }

    if (msg->getAuthGracePeriod())
    {
        DT_DBG(("Msg Contains AuthGracePeriod"));
        gp = msg->getAuthGracePeriod()->value();
        DT_DBG((" AuthGracePeriod = %d",gp));
    }
    else
    {
        gp = itsDiaConfig.GetAuthSessionConfig().GetGracePeriod();
    }

    DIA_SE_AUTH_TIMERS(entry).gracePeriod = gp;

    return (ITS_SUCCESS);
}

    int
SessionTable::StopAllAuthTimers(SESSION_ENTRY *entry)
{
    DT_DBG(("StopAllAuthTimers"));

    if (DIA_SE_AUTH_TIMERS(entry).timeout != TIMER_BAD_SERIAL)
    {
        TIMERS_CancelTimer(DIA_SE_AUTH_TIMERS(entry).timeout);
        DIA_SE_AUTH_TIMERS(entry).timeout = TIMER_BAD_SERIAL;
    }
    if (DIA_SE_AUTH_TIMERS(entry).lifetime != TIMER_BAD_SERIAL)
    {
        TIMERS_CancelTimer(DIA_SE_AUTH_TIMERS(entry).lifetime);
        DIA_SE_AUTH_TIMERS(entry).lifetime = TIMER_BAD_SERIAL;
    }
    if (DIA_SE_AUTH_TIMERS(entry).gracePeriod != TIMER_BAD_SERIAL)
    {
        TIMERS_CancelTimer(DIA_SE_AUTH_TIMERS(entry).gracePeriod);
        DIA_SE_AUTH_TIMERS(entry).gracePeriod = TIMER_BAD_SERIAL;
    }
    if (DIA_SE_AUTH_TIMERS(entry).retryAbort != TIMER_BAD_SERIAL)
    {
        TIMERS_CancelTimer(DIA_SE_AUTH_TIMERS(entry).retryAbort);
        DIA_SE_AUTH_TIMERS(entry).retryAbort = TIMER_BAD_SERIAL;
    }
    return (ITS_SUCCESS);
}

    int
SessionTable::StopAllAcctTimers(SESSION_ENTRY *entry)
{
    if (DIA_SE_ACCT_TIMERS(entry).timeout != TIMER_BAD_SERIAL)
    {
        TIMERS_CancelTimer(DIA_SE_ACCT_TIMERS(entry).timeout);
        DIA_SE_ACCT_TIMERS(entry).timeout = TIMER_BAD_SERIAL;
    }
    if (DIA_SE_ACCT_TIMERS(entry).interim != TIMER_BAD_SERIAL)
    {
        TIMERS_CancelTimer(DIA_SE_ACCT_TIMERS(entry).interim);
        DIA_SE_ACCT_TIMERS(entry).interim = TIMER_BAD_SERIAL;
    }
    if (DIA_SE_ACCT_TIMERS(entry).realTime != TIMER_BAD_SERIAL)
    {
        TIMERS_CancelTimer(DIA_SE_ACCT_TIMERS(entry).realTime);
        DIA_SE_ACCT_TIMERS(entry).realTime = TIMER_BAD_SERIAL;
    }
    return (ITS_SUCCESS);
}

    int
SessionTable::StopTimer(DIA_TIMER_TYPE type, SESSION_ENTRY *entry)
{
    switch (type)
    {
        case AUTH_SESSION_TIMER:
            DT_DBG(("StopTimer Type = %s Id = %d", 
                        TIMER_TO_TEXT(type), DIA_SE_AUTH_TIMERS(entry).timeout));
            TIMERS_CancelTimer(DIA_SE_AUTH_TIMERS(entry).timeout);
            DIA_SE_AUTH_TIMERS(entry).timeout = TIMER_BAD_SERIAL;
            break;
        case AUTH_SESSION_LIFETIME:
            DT_DBG(("StopTimer Type = %s Id = %d", 
                        TIMER_TO_TEXT(type), DIA_SE_AUTH_TIMERS(entry).lifetime));
            TIMERS_CancelTimer(DIA_SE_AUTH_TIMERS(entry).lifetime);
            DIA_SE_AUTH_TIMERS(entry).lifetime = TIMER_BAD_SERIAL;
            break;
        case AUTH_SESSION_GRACE_PERIOD:
            DT_DBG(("StopTimer Type = %s Id = %d", 
                        TIMER_TO_TEXT(type), DIA_SE_AUTH_TIMERS(entry).gracePeriod));
            TIMERS_CancelTimer(DIA_SE_AUTH_TIMERS(entry).gracePeriod);
            DIA_SE_AUTH_TIMERS(entry).gracePeriod = TIMER_BAD_SERIAL;
            break;
        case AUTH_SESSION_RETRY_ABORT:
            DT_DBG(("StopTimer Type = %s Id = %d", 
                        TIMER_TO_TEXT(type), DIA_SE_AUTH_TIMERS(entry).retryAbort));
            TIMERS_CancelTimer(DIA_SE_AUTH_TIMERS(entry).retryAbort);
            DIA_SE_AUTH_TIMERS(entry).retryAbort = TIMER_BAD_SERIAL;
            break;
        case ACCT_SESSION_TIMER:
            DT_DBG(("StopTimer Type = %s Id = %d", 
                        TIMER_TO_TEXT(type), DIA_SE_ACCT_TIMERS(entry).timeout));
            TIMERS_CancelTimer(DIA_SE_ACCT_TIMERS(entry).timeout);
            DIA_SE_ACCT_TIMERS(entry).timeout = TIMER_BAD_SERIAL;
            break;
        case ACCT_SESSION_INTERIM_INTERVAL:
            DT_DBG(("StopTimer Type = %s Id = %d", 
                        TIMER_TO_TEXT(type), DIA_SE_ACCT_TIMERS(entry).interim));
            TIMERS_CancelTimer(DIA_SE_ACCT_TIMERS(entry).interim);
            DIA_SE_ACCT_TIMERS(entry).interim = TIMER_BAD_SERIAL;
            break;
        case ACCT_SESSION_REALTIME:
            DT_DBG(("StopTimer Type = %s Id = %d", 
                        TIMER_TO_TEXT(type), DIA_SE_ACCT_TIMERS(entry).realTime));
            TIMERS_CancelTimer(DIA_SE_ACCT_TIMERS(entry).realTime);
            DIA_SE_ACCT_TIMERS(entry).realTime = TIMER_BAD_SERIAL;
            break;
        default:
            DT_ERR(("Invalid Timer"));
            return (!ITS_SUCCESS);
    }

    return (ITS_SUCCESS);
}

    int
SessionTable::StartTimer(const char* sessionId, DIA_TIMER_TYPE type, int duration, SESSION_ENTRY *entry)
{
    DIA_TIMER_CTXT timerCtxt;

    timerCtxt.timerType = type;
    //Fixing Copy into fixed size buffer
    strncpy(timerCtxt.data.sessionInfo.sessionId, sessionId, ITS_DIA_TIMER_CXT_SIZE-1);

    int tqInst = DIASTACK_TQ_INST;
    if (itsDiaConfig.IsQueueMgmtEnabled())
    {
        tqInst = DIAThreadIdList::GetTQInstance();
    }

    switch (type)
    {
        case AUTH_SESSION_TIMER:
            DIA_SE_AUTH_TIMERS(entry).timeoutDuration = duration;
            DIA_SE_AUTH_TIMERS(entry).timeout = 
                TIMERS_StartTimer(tqInst, 
                        duration,
                        &timerCtxt,  
                        sizeof(DIA_TIMER_CTXT));

            DT_DBG(("StartTimer Type = %s Id = %u", 
                        TIMER_TO_TEXT(type), DIA_SE_AUTH_TIMERS(entry).timeout));

            break;
        case AUTH_SESSION_LIFETIME:
            DIA_SE_AUTH_TIMERS(entry).lifetimeDuration = duration;
            DIA_SE_AUTH_TIMERS(entry).lifetime = 
                TIMERS_StartTimer(tqInst, 
                        duration,
                        &timerCtxt,  
                        sizeof(DIA_TIMER_CTXT));
            DT_DBG(("StartTimer Type = %s Id = %d", 
                        TIMER_TO_TEXT(type), DIA_SE_AUTH_TIMERS(entry).lifetime));
            break;
        case AUTH_SESSION_GRACE_PERIOD:
            DIA_SE_AUTH_TIMERS(entry).gracePeriodDuration = duration;
            DIA_SE_AUTH_TIMERS(entry).gracePeriod = 
                TIMERS_StartTimer(tqInst, 
                        duration,
                        &timerCtxt,  
                        sizeof(DIA_TIMER_CTXT));
            DT_DBG(("StartTimer Type = %s Id = %d", 
                        TIMER_TO_TEXT(type), DIA_SE_AUTH_TIMERS(entry).gracePeriod));
            break;
        case AUTH_SESSION_RETRY_ABORT:
            DIA_SE_AUTH_TIMERS(entry).retryAbortDuration = duration;
            DIA_SE_AUTH_TIMERS(entry).retryAbort = 
                TIMERS_StartTimer(tqInst, 
                        duration,
                        &timerCtxt,  
                        sizeof(DIA_TIMER_CTXT));
            DT_DBG(("StartTimer Type = %s Id = %d", 
                        TIMER_TO_TEXT(type), DIA_SE_AUTH_TIMERS(entry).retryAbort));
            break;
        case ACCT_SESSION_TIMER:
            DIA_SE_ACCT_TIMERS(entry).timeoutDuration = duration;
            DIA_SE_ACCT_TIMERS(entry).timeout = 
                TIMERS_StartTimer(tqInst, 
                        duration,
                        &timerCtxt,  
                        sizeof(DIA_TIMER_CTXT));
            DT_DBG(("StartTimer Type = %s Id = %d", 
                        TIMER_TO_TEXT(type), DIA_SE_ACCT_TIMERS(entry).timeout));
            break;
        case ACCT_SESSION_INTERIM_INTERVAL:
            DIA_SE_ACCT_TIMERS(entry).interimDuration = duration;
            DIA_SE_ACCT_TIMERS(entry).interim = 
                TIMERS_StartTimer(tqInst, 
                        duration,
                        &timerCtxt,  
                        sizeof(DIA_TIMER_CTXT));
            DT_DBG(("StartTimer Type = %s Id = %d", 
                        TIMER_TO_TEXT(type), DIA_SE_ACCT_TIMERS(entry).interim));
            break;
        case ACCT_SESSION_REALTIME:
            DIA_SE_ACCT_TIMERS(entry).realTimeDuration = duration;
            DIA_SE_ACCT_TIMERS(entry).realTime = 
                TIMERS_StartTimer(tqInst, 
                        duration,
                        &timerCtxt,  
                        sizeof(DIA_TIMER_CTXT));
            DT_DBG(("StartTimer Type = %s Id = %d", 
                        TIMER_TO_TEXT(type), DIA_SE_ACCT_TIMERS(entry).realTime));
            break;
        default:
            DT_ERR(("Invalid Timer"));
            return (!ITS_SUCCESS);    
    }

    return (ITS_SUCCESS);    
}

    int 
SessionTable::InsertEntry(SESSION_ENTRY &sessionInfo, ITS_OCTET *key, ITS_UINT keyLen, bool replicateInsertion)
{
    void *ret;
    int error;
    int res;
    ITS_Class redunClass = itsDiaConfig.GetRedundancyFeature();

    int tableId = SESSION_TABLE_ID; 
    if (itsDiaConfig.IsQueueMgmtEnabled())
    {
        tableId = DIAThreadIdList::GetTableId();
    }
    DT_DBG(("SessionTable::InsertEntry::SessionId %s", (char *)key));

    while (((ret = DSM_FindNoLock(SESSION_TABLE_FT_GROUP_ID,
                        tableId,
                        key,
                        keyLen,
                        &error)) == NULL) &&
            (error == ITS_EINUSE))
    {
        TIMERS_USleep(100);

        /* Eventually either the lock will be released by the other node which
         * will cause ret to be NON-NULL or the row will be deleted which will
         * cause ret to be NULL and error = ITS_ENOTFOUND
         * If the lock is not released by the other node for a specific
         * interval it will be busted by DSM_Find and ret will be NON-NULL
         */
        //Fixing Unused Pointer Value
        (void)ret;
    }

    if (error == ITS_ENOTFOUND)
    {
        // Row is not present
        ret = DSM_AllocNoLock(SESSION_TABLE_FT_GROUP_ID,
                tableId,
                key,
                keyLen,
                sizeof(SESSION_ENTRY),
                &error);

        if (ret == NULL)
        {
            DT_ERR(("InsertEntry: alloc failed for %s", (char *)key));
            return ITS_DIA_ALLOCFAIL;
        }
        else
        {
            SESSION_ENTRY *entry = (SESSION_ENTRY *)ret;
            memcpy(entry, &sessionInfo, sizeof(SESSION_ENTRY));

            res = DSM_CommitNoLock(SESSION_TABLE_FT_GROUP_ID,
                    tableId,
                    key,
                    keyLen,
                    ret);

            if (res != ITS_SUCCESS)
            {
                DT_ERR(("InsertEntry: commit failed for %s", (char*)key));
                return ITS_DIA_ALLOCFAIL;
            }

            //Replicate Session: if replication of sessions is enabled
            //then invoke the createReplica Callback.Also check if session 
            //has to be replicated.
            if( (SessionTable::replicateSessions) &&
                    (replicateInsertion) &&
                    (SessionTable::sessCreateCbk!= NULL))
            {
                SessionTable::sessCreateCbk((char *)key,entry);
            }
            /*else
            {
                DT_DBG(("STACK REPLICATION DISABLED!!"));
            } */
            if (redunClass &&
                    REDUNDANCY_GET_NODE_STATE(redunClass) == ITS_STATE_BACKUP)
            {
                ITS_UINT sessIdxkey = ITS_DIA_OUTBOUND_SESS_INDEX_ENTRY;
                //check if outbound or inbound session
                if(DIA_SE_SINDX(&sessionInfo) & 0x8000)
                {
                    sessIdxkey = ITS_DIA_INBOUND_SESS_INDEX_ENTRY;
                }
                while (((ret = DSM_FindNoLock(SESSION_TABLE_FT_GROUP_ID,
                                    tableId,
                                    (ITS_OCTET*)&sessIdxkey,
                                    sizeof(ITS_UINT),
                                    &error)) == NULL) &&
                        (error == ITS_EINUSE))
                {
                    TIMERS_USleep(100);
                }
                if (error == ITS_ENOTFOUND)
                {
                    ret = DSM_AllocNoLock(SESSION_TABLE_FT_GROUP_ID,
                            tableId,
                            (ITS_OCTET*)&sessIdxkey,
                            sizeof(ITS_UINT),
                            sizeof(ITS_UINT),
                            &error);

                }
                if (ret == NULL)
                {
                    DT_ERR(("InsertEntry Session Index: alloc failed for %d", DIA_SE_SINDX(&sessionInfo)));
                }
                else
                {
                    memcpy((ITS_UINT*)ret, &DIA_SE_SINDX(&sessionInfo), sizeof(ITS_UINT));
                    DSM_CommitNoLock(SESSION_TABLE_FT_GROUP_ID,
                            tableId,
                            (ITS_OCTET*)&sessIdxkey,
                            sizeof(ITS_UINT),
                            ret);
                }
            }
        }
    }
    else
    {
        DT_ERR(("Duplicate Entry exists"));
        return (ITS_EDUPLENTRY);
    }

    return (ITS_SUCCESS);
}

    int 
SessionTable::FindEntry(SESSION_ENTRY *&sessionInfo, ITS_OCTET *key, ITS_UINT keyLen)
{
    SESSION_ENTRY *entry = NULL;
    void *ret;
    int error;

    DT_DBG(("SessionTable::FindEntry::SessionId %s Size = %d", (char *)key, keyLen));
    int tableId = SESSION_TABLE_ID;
    if (itsDiaConfig.IsQueueMgmtEnabled())
    {
        tableId = DIAThreadIdList::GetTableId();
    }

    while (((ret = DSM_FindNoLock(SESSION_TABLE_FT_GROUP_ID,
                        tableId,     //tableId
                        key,                  //key
                        keyLen,               //keylen
                        &error)) == NULL) &&
            (error == ITS_EINUSE))
    {
        TIMERS_USleep(100);

        /* Eventually either the lock will be released by the other node which
         * will cause ret to be NON-NULL or the row will be deleted which will
         * cause ret to be NULL and error = ITS_ENOTFOUND
         * If the lock is not released by the other node for a specific
         * interval it will be busted by DSM_Find and ret will be NON-NULL
         */
    }
    if (ret == NULL)
    {
        // Row is not present
        DT_DBG(("FindEntry: SessionId %s is not present", (char*)key));
        //Since entry is not present in local table check for the replica cache
        //Replicate Session: if replication of sessions is enabled
        //then invoke the createReplica Callback.
        if( (SessionTable::replicateSessions) && 
                (SessionTable::sessFetchCbk!= NULL))
        {
            SESSION_ENTRY ent;
            if(SessionTable::sessFetchCbk((char *)key,&ent) != ITS_SUCCESS)
            {
                //Entry not present in replica.
                return (!ITS_SUCCESS);
            }else {
                //Entry is present in replica,
                //hence create the same in local table.
                DT_DBG(("FindEntry:Found entry in replica, SessionId %s is present", (char*)key));
                if(InsertEntry(ent,key,keyLen,false) != ITS_SUCCESS)
                {
                    return !(ITS_SUCCESS);
                }
                while (((ret = DSM_FindNoLock(SESSION_TABLE_FT_GROUP_ID,
                                    tableId,     //tableId
                                    key,                  //key
                                    keyLen,               //keylen
                                    &error)) == NULL) &&
                        (error == ITS_EINUSE))
                {
                    TIMERS_USleep(100);

                    /* Eventually either the lock will be released by the other node which
                     * will cause ret to be NON-NULL or the row will be deleted which will
                     * cause ret to be NULL and error = ITS_ENOTFOUND
                     * If the lock is not released by the other node for a specific
                     * interval it will be busted by DSM_Find and ret will be NON-NULL
                     */
                }
                sessionInfo = (SESSION_ENTRY *)ret;
                return (ITS_SUCCESS);
            }
        }
        else
        {
            DT_DBG(("STACK REPLICATION DISABLED!!"));
        } 

    }
    else
    {
        // Row is present, the data is in "ret"
        DT_DBG(("FindEntry: SessionId %s is present", (char*)key));
        sessionInfo = (SESSION_ENTRY *)(ret);
        return (ITS_SUCCESS);
    }
    return (!ITS_SUCCESS);
}

    int 
SessionTable::RemoveEntry(SESSION_ENTRY *sessionInfo, ITS_OCTET *key, ITS_UINT keyLen)
{
    void *ret;
    int error;
    int res;
    std::string keyStr=(char*)key;

    int tableId = SESSION_TABLE_ID;
    if (itsDiaConfig.IsQueueMgmtEnabled())
    {
        tableId = DIAThreadIdList::GetTableId();
    }

    DT_DBG(("SessionTable::RemoveEntry::SessionId %s", (char *)key));

    ITS_UINT sesIndex=DIA_SE_SINDX(sessionInfo);
    // INCOMING_MESSAGEQ->RemoveMsgEventEntry(sesIndex);
    DiaMsgRouter::RemoveMsgQEventEntry(sesIndex);

    while (((ret = DSM_FindNoLock(SESSION_TABLE_FT_GROUP_ID,
                        tableId,        //tableId
                        key,                     //key
                        keyLen,                  //keylen
                        &error)) == NULL) &&
            (error == ITS_EINUSE))
    {
        TIMERS_USleep(100);

        /* Eventually either the lock will be released by the other node which
         * will cause ret to be NON-NULL or the row will be deleted which will
         * cause ret to be NULL and error = ITS_ENOTFOUND
         * If the lock is not released by the other node for a specific
         * interval it will be busted by DSM_Find and ret will be NON-NULL
         */
    }

    if (ret == NULL)
    {
        // Row is not present
        DT_ERR(("RemoveEntry: SessionId %s is not present", (char*)key));
        return (!ITS_SUCCESS);
    }
    else
    {
        if (DIA_SE_STYPE(sessionInfo) == DIA_AUTHORIZATION)
        {
            StopAllAuthTimers(sessionInfo);
        }
        else
        {
            StopAllAcctTimers(sessionInfo);
        }

        // Row is present, the data is in "ret"
        res = DSM_FreeNoLock(SESSION_TABLE_FT_GROUP_ID,
                tableId,
                key,
                keyLen,
                ret);

        if (res != ITS_SUCCESS)
        {
            DT_ERR(("RemoveEntry: Free failed"));
            return (!ITS_SUCCESS);
        }
        //Replicate Session: if replication of sessions is enabled
        //then invoke the deleteReplica Callback.
        if( (SessionTable::replicateSessions) && 
                (SessionTable::sessDeleteCbk!= NULL))
        {
           // SessionTable::sessDeleteCbk((char *)key);
            SessionTable::sessDeleteCbk(keyStr);
        }
        else
        {
            DT_DBG(("STACK REPLICATION DISABLED!!"));
        } 
    }

    return (ITS_SUCCESS);
}

    int 
SessionTable::ModifyEntry(SESSION_ENTRY *sessionInfo, ITS_OCTET *key, ITS_UINT keyLen)
{
    void *ret;
    int res, error;

    DT_DBG(("SessionTable::ModifyEntry::SessionId %s", (char *)key));

    int tableId = SESSION_TABLE_ID;
    if (itsDiaConfig.IsQueueMgmtEnabled())
    {
        tableId = DIAThreadIdList::GetTableId();
    }

    while (((ret = DSM_FindNoLock(SESSION_TABLE_FT_GROUP_ID,
                        tableId,        //tableId
                        key,                     //key
                        keyLen,                  //keylen
                        &error)) == NULL) &&
            (error == ITS_EINUSE))
    {
        TIMERS_USleep(100);

        /* Eventually either the lock will be released by the other node which
         * will cause ret to be NON-NULL or the row will be deleted which will
         * cause ret to be NULL and error = ITS_ENOTFOUND
         * If the lock is not released by the other node for a specific
         * interval it will be busted by DSM_Find and ret will be NON-NULL
         */
    }
    if (ret == NULL)
    {
        DT_ERR(("ModifyEntry: SessionId %s is not present", (char*)key));
        //Unlock();

        return !ITS_SUCCESS;
    }
    else
    {
        DT_DBG(("ModifyEntry: SessionId %s is present", (char*)key));

        SESSION_ENTRY *entry = (SESSION_ENTRY *)ret;

        if (entry != sessionInfo)
            memcpy(entry, sessionInfo, sizeof(SESSION_ENTRY));

        res = DSM_CommitNoLock(SESSION_TABLE_FT_GROUP_ID,
                tableId,
                key,
                keyLen,
                ret);

        if (res != ITS_SUCCESS)
        {
            DT_ERR(("ModifyEntry: commit failed for %s", (char*)key));
            //Unlock();

            return !ITS_SUCCESS;
        }
    }
    //Unlock();
    return (ITS_SUCCESS);
}

    void
SessionTable::IterateTable(void *in, void *out, DSM_IterateEntryProc iterateFunc, int index)
{
    int tableId = SESSION_TABLE_ID + index;

    DSM_TableIterate(SESSION_TABLE_FT_GROUP_ID, 
            tableId, 
            in, 
            out, 
            iterateFunc);
}

    void
SessionTable::IterateTable(void *in, void *out, DSM_IterateEntryProc iterateFunc)
{
    DSM_TableIterate(SESSION_TABLE_FT_GROUP_ID, 
            SESSION_TABLE_ID, 
            in, 
            out, 
            iterateFunc);
}

    static int 
GetDSMEntry(ITS_POINTER data, void *in, void *out)
{
    std::ostream *os = (std::ostream *)in;
    SESSION_ENTRY *sessEntry = (SESSION_ENTRY *)data;

    *os<< "Session Entry :" << sessEntry->sState<<endl;
    *os<< "SessionIndex  :"<< sessEntry->sessIndx<<endl;
    *os<< "SessionType   :"<< sessEntry->sType<<endl;
    *os<< "SessionSMType :"<< sessEntry->fsmType<<endl;
    *os << "--------------------------------------------------" << endl;

    return (ITS_SUCCESS);
}

    int
SessionTable::GetTableSize()
{
    ITS_UINT size = 0;
    DSM_TableGetSize(SESSION_TABLE_FT_GROUP_ID,
            SESSION_TABLE_ID,
            &size);
    return size;
}

    int
SessionTable::GetTableSize(int index)
{
    ITS_UINT size = 0;

    DSM_TableGetSize(SESSION_TABLE_FT_GROUP_ID,
            SESSION_TABLE_ID + index,
            &size);
    return size;
}

    void
SessionTable::Print(std::ostream& os)
{

    int numThreads = 1;
    if (itsDiaConfig.IsQueueMgmtEnabled())
    {
        numThreads = itsDiaConfig.GetQueueMgmt().GetMsgRouterThreadCount(); 
    }
    for (int i=0; i<numThreads; i++)
    {
        os << "------------------------------------------------------------" << endl;
        os << "-- Session Table Begin --" << endl;
        os << "------------------------------------------------------------" << endl;
        os << "Size: <" << GetTableSize() << ">" << endl;
        os << endl;
        os << endl;
        os << "Entries:" << endl;
        os << "--------------------------------------------------" << endl;
        IterateTable((void *)&os, NULL, GetDSMEntry, i);
    }
}

    ostream&
operator<< (ostream& os, SessionTable& table)
{
    table.Print(os);
    return os;
}


// init session entry , session index allocation, submitToServerAcctSm
    int
SessionTable::InsertAcctSession(DIA_BASE_CMD *&cmd, const char* sessionId, 
        SESSION_ENTRY*& ent, its::Event &ev, 
        bool isStateless)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dRlen = 0;
    DIA_BASE_CMD* msg = (DIA_BASE_CMD*) cmd;
    ITS_CHAR *destRlm = NULL;
    ITS_USHORT trInst = ITS_GET_CTXT(ev.GetData());

    DIA_SE_RX_FLAGS(ent)     = msg->getHeader().flags;
    DIA_SE_RX_HH(ent)        = msg->getHeader().hh;
    DIA_SE_RX_EE(ent)        = msg->getHeader().ee;
    DIA_SE_PEER_INST(ent)    = trInst;
    DIA_SE_ACC_STATE(ent)    = ACCT_SESSION_ST_IDLE;
    DIA_SE_STYPE(ent)        = DIA_ACCOUNTING;

    DIA_SE_EVT_TYPE(ent)     = ACCT_SESSION_EVT_REQUEST_ACCESS;
    DIA_SE_CLIENTID(ent)     = 0;

    /**
     * Destination Realm in session entry populated from the message.
     * Parial fix for issue 720 in Whizible.
     */
    if (msg->getDestinationRealm() != NULL)
    {
        destRlm = (ITS_CHAR*)(msg->getDestinationRealm())->value().c_str();
    }
    else
    {
        DT_CRT(("The Destination Realm Name in the Message is NULL"));
        return !(ITS_SUCCESS);
    }

    if ((dRlen = strlen (destRlm)) <= SESSION_DEST_REALM_MAX_SIZE)
    {
        memcpy(DIA_SE_DEST_REALM(ent), destRlm, dRlen);
        DT_DBG(("The Destination-Realm in the Message is: %s", destRlm));
    }
    else
    {
        DT_CRT(("The Destination Realm Name in the Message Exceeds" \
                    " size defined in session entry"));
        return !(ITS_SUCCESS);
    }
    if (AllocateServerSessionIndex(DIA_SE_SINDX(ent))
            != ITS_SUCCESS)
    {
        ret = DiaErrHandler::HandleError(trInst, msg,
                SEND_ERROR_TO_PEER,
                ITS_DIA_UNKNOWN_SESSION_ID);
        delete cmd;
        cmd = NULL;
        return ret;
    }
    /* Set the saved clientid in the message */
    msg->setClientId(DIA_SE_CLIENTID(ent));

    /* Set SessionIndex in the payload */
    msg->setSessionIndex(DIA_SE_SINDX(ent));

    if (msg->getAuthApplicationId())
    {
        DIA_SE_APP_ID(ent) = msg->getAuthApplicationId()->value();
    }
    else
    {
        DIA_SE_APP_ID(ent) = msg->getHeader().appId;
    }
    /* Check AccountingRealtimeRequired AVP from the ACR
       if exists and value is DELIVER_AND_GRANT then stateful
       default server side SM stateless
       */
    if (isStateless)
    {
        DT_DBG(("AccountingRealtimeRequired != DELIVER_AND_GRANT"));

        ITS_UINT st = itsDiaConfig.GetAuthSessionConfig().GetTimeout();

        StartTimer(sessionId, ACCT_SESSION_TIMER,
                st, ent);

        if (InsertEntry(*ent, (ITS_OCTET *)sessionId,
                    strlen((const char*)sessionId))
                == ITS_SUCCESS)
        {
            DT_DBG(("Created Session Context for :: %s",
                        sessionId));
            ret = DiaMsgRouter::SendMsgToApp(ent, &ev.GetEvent());
            return (ITS_SUCCESS);
        }
        else
        {
            DT_ERR(("Failed to create session context for :: %s", 
                        sessionId));
            StopTimer(ACCT_SESSION_TIMER, ent);
            return (!ITS_SUCCESS);
        }
    }
    else
    {
        ITS_UINT recType = msg->getAccountingRecordType()->value();

        if (recType == AccountingRecordType::INTERIM_RECORD ||
                recType == AccountingRecordType::STOP_RECORD)
        {
            DT_ERR((" Invalid Session Id"));

            ret = DiaErrHandler::HandleError(trInst, msg,
                    SEND_ERROR_TO_PEER,
                    ITS_DIA_UNKNOWN_SESSION_ID);
            delete cmd;
            cmd = NULL;
            return ret;
        }

        DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_REQUEST_ACCESS;

        ret = statefulServerAcctFsm.SubmitToSM(ent, &ev.GetEvent());

        if (InsertEntry(*ent, (ITS_OCTET *)sessionId,
                    strlen((const char*)sessionId))
                == ITS_SUCCESS)
        {
            DT_DBG(("Created Session Context for :: %s",
                        sessionId)); 
            return (ITS_SUCCESS);
        }
        else
        {
            DT_ERR(("Failed to create session context for :: %s",
                        sessionId));
            return (!ITS_SUCCESS);
        }
    }
}

    int
SessionTable::InsertAuthSession(DIA_BASE_CMD *&cmd, const char* sessionId, 
        SESSION_ENTRY *&ent, its::Event &ev, 
        bool isStateless)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dRlen = 0;
    DIA_BASE_CMD* msg = (DIA_BASE_CMD*) cmd;
    ITS_CHAR *destRlm = NULL;
    ITS_USHORT trInst = ITS_GET_CTXT(ev.GetData());

    /* This is the first inbound request */
    DIA_SE_RX_FLAGS(ent) = msg->getHeader().flags;
    DIA_SE_RX_HH(ent)    = msg->getHeader().hh;
    DIA_SE_RX_EE(ent)    = msg->getHeader().ee;
    DIA_SE_PEER_INST(ent)= trInst;
    DIA_SE_STATE(ent)    = AUTH_SESSION_ST_IDLE;
    DIA_SE_STYPE(ent)    = DIA_AUTHORIZATION;
    DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_REQUEST_ACCESS;
    DIA_SE_CLIENTID(ent) = 0;

    /**
     * Destination Realm in session entry populated from the message.
     * Parial fix for issue 720 in Whizible.
     */
    if (msg->getDestinationRealm() != NULL)
    {
        destRlm = (ITS_CHAR*)(msg->getDestinationRealm())->value().c_str();
    }
    else
    {
        DT_CRT(("The Destination Realm Name in the Message is NULL"));
        return !(ITS_SUCCESS);
    }

    //Fixing Out-of-bounds write
    if ((dRlen = strlen (destRlm)) < SESSION_DEST_REALM_MAX_SIZE)
    {
        memcpy(DIA_SE_DEST_REALM(ent), destRlm, dRlen);
        DIA_SE_DEST_REALM(ent)[dRlen] = '\0';
        DT_DBG(("The Destination-Realm in the Message is: %s", destRlm));
    }
    else
    {
        DT_CRT(("The Destination Realm Name in the Message Exceeds" \
                    " size defined in session entry"));
        return !(ITS_SUCCESS);
    }
    if (AllocateServerSessionIndex(DIA_SE_SINDX(ent)) 
            != ITS_SUCCESS)
    {
        ret = DiaErrHandler::HandleError(trInst, msg,
                SEND_ERROR_TO_PEER,
                ITS_DIA_UNKNOWN_SESSION_ID);
        delete msg;
        cmd = NULL;
        return ret;
    }
    /* Set the saved clientid in the message */
    msg->setClientId(DIA_SE_CLIENTID(ent));

    /* Set SessionIndex in the payload */
    msg->setSessionIndex(DIA_SE_SINDX(ent));

    if (msg->getAuthApplicationId())
    {
        DIA_SE_APP_ID(ent) = msg->getAuthApplicationId()->value();
    }
    else
    {
        DIA_SE_APP_ID(ent) = msg->getHeader().appId;
    }

    /* Server states based on existence (or lack of) 
       Auth-Session-State AVP 
       If AuthSessionState AVP is present and
       the value is NO_STATE_MAINTAINED then it's
       Stateless Server else Stateful Server
       */
    if (isStateless)
    {
        StartTimer(sessionId, AUTH_SESSION_TIMER,
                itsDiaConfig.GetAuthSessionConfig().GetTimeout(),
                ent);

        if (InsertEntry(*ent, (ITS_OCTET *)sessionId,
                    strlen(sessionId)) == ITS_SUCCESS)
        {
            DT_DBG(("Created Session Context for :: %s", 
                        sessionId));
            ret = DiaMsgRouter::SendMsgToApp(ent, &ev.GetEvent());
        }
        else
        {
            DT_ERR(("Failed to create session context for :: %s", 
                        sessionId));
            StopTimer(AUTH_SESSION_TIMER, ent);
            return (!ITS_SUCCESS);
        }
    }
    else
    {
        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_REQUEST_ACCESS;

        if (InsertEntry(*ent, (ITS_OCTET *)sessionId,
                    strlen(sessionId)) == ITS_SUCCESS)
        {
            SESSION_ENTRY* e = NULL;
            DT_DBG(("Created Session Context for :: %s", 
                        sessionId));

            // Passing the ent will not modify the entry in the table.
            // ent is on the stack. Get the entry on the table
            ret = this->FindEntry(e,  (ITS_OCTET *)sessionId,
                    strlen(sessionId));
            if (ret == ITS_SUCCESS)
            {
                ret = statefulServerAuthFsm.SubmitToSM(e, &ev.GetEvent());
            }
            // TODO should do a modify session entry for redundancy
            // TODO better do modify inside the statemachines before sending it
            // to the other Worker to avoid race conditions
        }
        else
        {
            DT_ERR(("Failed to create session context for :: %s", 
                        sessionId));
            ret = !ITS_SUCCESS;
        }
    }
    return (ret);
}

