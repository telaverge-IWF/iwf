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
 * LOG: $Log: dia_wd_trans.cpp,v $
 * LOG: Revision 3.22.6.1.6.4.18.1  2020/02/14 11:36:11  jkchaitanya
 * LOG: TCP Timeout fix ported from DRE
 * LOG:
 * LOG: Revision 3.22.6.1.6.4  2013/04/07 03:54:21  cprem
 * LOG: Changes made to fix HA bugs. Review Request 784
 * LOG:
 * LOG: Revision 3.22.6.1.6.3  2013/04/04 09:06:11  mallikarjun
 * LOG: MemLeak Fixes Bug 1205 1298
 * LOG:
 * LOG: Revision 3.22.6.1.6.2  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.22.6.1.6.1  2013/02/25 13:15:54  mallikarjun
 * LOG: Bug 623 changes
 * LOG:
 * LOG: Revision 3.22.6.1  2012/11/20 17:39:45  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.22.28.1  2012/11/14 08:35:28  millayaraja
 * LOG: modified to accomdate Peer stack stats
 * LOG:
 * LOG: Revision 3.22  2010/10/06 04:02:48  nvijikumar
 * LOG: In solaris GCC SCTP setup some peers found OPEN state even after transport
 * LOG: failure detection due to no EOF indication from kernel.
 * LOG: Introduced logic to cleanup such peer context
 * LOG:
 * LOG: Revision 3.21  2009/09/07 06:23:10  rajeshak
 * LOG: Introduced micro second sleep instead of 1sec sleep
 * LOG:
 * LOG: Revision 3.20  2009/06/29 14:52:26  rajeshak
 * LOG: HMI Changes to improve the performance.
 * LOG:
 * LOG: Revision 3.19  2009/04/10 06:27:57  sureshj
 * LOG: Removed compilation flag HMI_ENABLE and added dyamic configuration
 * LOG: for HMI.
 * LOG:
 * LOG: Revision 3.18  2009/04/07 13:31:34  sureshj
 * LOG: HMI Monitoring enabled for watchDog Thread.
 * LOG:
 * LOG: Revision 3.17  2009/03/19 12:30:23  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.16  2009/03/19 08:08:06  nvijikumar
 * LOG: Reverting back HMI changes (App hangs and drop in TPS)
 * LOG:
 * LOG: Revision 3.15  2009/03/16 10:50:44  sureshj
 * LOG: FeatureId: Health Monitoring Inerface support added.
 * LOG: Desciption: HMI monitoring for watchdog.
 * LOG:
 * LOG: Revision 3.14  2009/01/13 10:55:04  nvijikumar
 * LOG: Fix to fire DWR at exact time (without too much delay than configured)
 * LOG:
 * LOG: Revision 3.13  2009/01/03 06:00:48  rajeshak
 * LOG: Introduced common func to send all indications
 * LOG:
 * LOG: Revision 3.12  2008/12/23 12:14:47  sureshj
 * LOG: Updates for statistics. Fix for incrementing count DWRout.
 * LOG:
 * LOG: Revision 3.11  2008/12/18 09:52:59  nvijikumar
 * LOG: Sleep for full device watchdog time instead of every sec
 * LOG: Performance optimization
 * LOG:
 * LOG: Revision 3.10  2008/12/12 12:29:02  nvijikumar
 * LOG: Peg increment is moved to common place
 * LOG:
 * LOG: Revision 3.9  2008/12/12 08:02:50  sureshj
 * LOG: Support for Stack statistics
 * LOG:
 * LOG: Revision 3.8  2008/11/13 12:58:54  ssaxena
 * LOG: Fix for whizible issue id 1227. ( issue due to improper merge from
 * LOG: Dia-ProductionRelease2_1) Hemant
 * LOG:
 * LOG: Revision 3.7  2008/10/28 12:06:28  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.6  2008/09/10 04:53:45  ssaxena
 * LOG: Fix for whizibile Issue Id 1144. Added check before sending Failover
 * LOG: Indication.
 * LOG:
 * LOG: Revision 3.5  2008/09/05 15:38:04  ssaxena
 * LOG: Fix for whizible Issue ID 1137.Release mutex before return.
 * LOG:
 * LOG: Revision 3.4  2008/09/02 17:05:14  ssaxena
 * LOG: Changes made to provide partial fix for whizible issue ID: 1119.
 * LOG:
 * LOG: Revision 3.3  2008/08/25 05:47:55  ssaxena
 * LOG: 1. Failover indication to application
 * LOG: 2. Updates to InitiateFailover procedure
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:45:06  hbhatnagar
 * LOG: Avoid frequent prints
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 1.1.2.5  2008/01/07 18:06:34  hbhatnagar
 * LOG: Changes made to provide partial fix for issues 20, 22, 23 raised by
 * LOG: Dhiranand. Moved the pthread_kill() API to dia_wd_trans.h for
 * LOG: both linux and solaris respectively.
 * LOG:
 * LOG: Revision 1.1.2.4  2008/01/07 13:04:19  avinashks
 * LOG: Fix for Issue No.16 raised by Dhirananda during
 * LOG: validation of BCGI ticket 1807.
 * LOG:
 * LOG: Revision 1.1.2.3  2008/01/05 16:01:20  avinashks
 * LOG: Fix for Issue No.18 raised by Dhirananda during validation
 * LOG: of BCGI ticket 1807.
 * LOG:
 * LOG: Revision 1.1.2.2  2007/12/16 06:14:09  hbhatnagar
 * LOG: Commented out else in Execute as is not needed.
 * LOG:
 * LOG: Revision 1.1.2.1  2007/12/14 11:21:13  hbhatnagar
 * LOG: Baselined the DeviceWatchDog Transport thread functionality removing the
 * LOG: DW Timer functionality.
 * LOG:
 * ID: $Id: dia_wd_trans.cpp,v 3.22.6.1.6.4.18.1 2020/02/14 11:36:11 jkchaitanya Exp $
 ****************************************************************************/
#ident "$Id: dia_wd_trans.cpp,v 3.22.6.1.6.4.18.1 2020/02/14 11:36:11 jkchaitanya Exp $"

#include <dia_wd_trans.h>
#include <its_dia_config.h>
#include <dia_cmn.h>  
#include <dia_trace.h>
#include <dia_fsm.h>
#include <dia_utils.h>
#include <dia_connector.h>
#include <dia_session_auth_fsm.h>
#include <dia_session_acct_fsm.h>
#include <dia_timer_handler.h>
#include <dia_session_table.h>
#include <dia_ip_trans.h>
#include <dia_msg_router.h>
#include <dia_stack_statistics.h>

#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      To Send the DWR Message for a particular Peer.   
 *  Input Parameters:
 *      Transport Instance
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS (0) :- in case of  DWR sent Successfully
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Yogesh        13-12-07    Created                 To Send DWR Message
 *   / Hemant
 *
 ****************************************************************************/
int
DiaWatchDogTransport::SendDWR(ITS_USHORT inst)
{
    int ret;
    DIA_CER *lcer;
    PEER_ENTRY *peerEntry = NULL;
    DiaSocketTransport *tr = NULL;
    lcer = itsDiaConfig.GetLocalCER();
    int len;
        ITS_OCTET *buff;
 tr = (DiaSocketTransport *)trTable.getAt(inst);

    DIA_DWR dwr(false, false);
    DIA_HDR &hdr = (DIA_HDR &)((DIA_GEN_CMD &)dwr).getHeader();

    hdr.hh = DiaUtils::GenerateHopByHopId();
    hdr.ee = DiaUtils::GenerateEndToEndId();

    dwr.setOriginHost(lcer->getOriginHost());
    dwr.setOriginRealm(lcer->getOriginRealm());

    if(itsDiaConfig.GetOriginStateIdOpt())
    {
       OriginStateId oid(itsDiaConfig.GetOriginStateId());
       dwr.setOriginStateId(oid);
    }

        DiaUtils::EncodeMsg(&dwr, &buff, len);


        ret = DiaMsgRouter::SendToPeer(tr, buff, len);
    if(ret == ITS_SUCCESS)
    {
        DT_DBG(("Successfully Sent DWR to Peer"));
        UPDATE_DIA_STATS_REQOUT(DIA_MSG_DW);
        tr = trTable[inst];
        if(tr != NULL)
        {
            peerEntry = tr->GetPeer();
            DIA_INC_PEER_DWR_SENT(peerEntry);
        }
    }
    else
    {
        DT_ERR(("Failed to send DWR : ret = %d", ret));
    }

        free((char*) buff);
    buff = NULL;
    return (ITS_SUCCESS);
}
/*
int
DiaWatchDogTransport::SendDWR(ITS_USHORT inst)
{
    int ret;
    DIA_CER *lcer;
    PEER_ENTRY *peerEntry = NULL;
    DiaSocketTransport *tr = NULL;
    lcer = itsDiaConfig.GetLocalCER();

    DIA_DWR dwr(false, false);
    DIA_HDR &hdr = (DIA_HDR &)((DIA_GEN_CMD &)dwr).getHeader();

    hdr.hh = DiaUtils::GenerateHopByHopId();
    hdr.ee = DiaUtils::GenerateEndToEndId();

    dwr.setOriginHost(lcer->getOriginHost());
    dwr.setOriginRealm(lcer->getOriginRealm());

     
     Origin-State-Id
    
    if(itsDiaConfig.GetOriginStateIdOpt())
    {
       OriginStateId oid(itsDiaConfig.GetOriginStateId());
       dwr.setOriginStateId(oid);
    }

    //Warning fix - suggest parentheses around assignment used as truth value
    if ((ret = DiaMsgRouter::SendCmdToPeer(inst,
                                          &hdr, 
                                          &dwr)) == ITS_SUCCESS)
    {
        DT_DBG(("Successfully Sent DWR to Peer"));
        UPDATE_DIA_STATS_REQOUT(DIA_MSG_DW); 
        tr = trTable[inst];
        if(tr != NULL)
        {
            peerEntry = tr->GetPeer();
            DIA_INC_PEER_DWR_SENT(peerEntry);
        }
    }
    else
    {
        DT_ERR(("Failed to send DWR : ret = %d", ret));
    }
    return (ITS_SUCCESS);
}*/

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      To Start Failover Procedures for particular peer.   
 *  Input Parameters:
 *      Transport Instance
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS (0) :- if success
        ITS_EBADTRANSPORT,ITS_ENOTFOUND:- in case of error 
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Yogesh        13-12-07    Created                 To Start Failover
 *   / Hemant                                          procedure for peer.
 *
 ****************************************************************************/
int
DiaWatchDogTransport::InitiateFailover(ITS_USHORT inst)
{
    DiaSocketTransport *tr = NULL;
    PEER_ENTRY *peer = NULL;
    PEER_ENTRY *altPeer = NULL;
    tr = trTable.getAt(inst);
    if (tr == NULL)
    {
       return (ITS_EBADTRANSPORT);
    }
    peer = tr->GetPeer();

    if (peer == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    MUTEX_AcquireMutex(&DIA_PE_MUX(peer));

    /* Disconnect Connection */
    tr->SetExit();

    DT_DBG(("Setting the Transport Down for peer:%s", DIA_PE_HOST(peer)));

    DT_DBG(("Initiate Failover"));

    if (DIA_PE_PENDING_Q(peer))
    {
        /* Set Failback false */
        DIA_PE_PENDING_Q(peer)->SetStopFailover(false);

        /*
         * Retransmit the pending messages.
         * Fix for whizible Issue ID 1137.
         */
        if (DiaMsgRouter::Failover(peer) != ITS_SUCCESS)
        {
            DT_ERR(("Failover::NOT SUCCEED"));
            MUTEX_ReleaseMutex(&DIA_PE_MUX(peer));
            return (!ITS_SUCCESS);
        }
    }
    else
    {
        DT_ERR(("Failover is not enabled to the peer" ));
    }
 
    MUTEX_ReleaseMutex(&DIA_PE_MUX(peer));

    return (ITS_SUCCESS);
}

void 
DiaWatchDogTransport::Execute(void *arg)
{
    HMIThread_Info* hmiInfo = NULL;
    int ret;
    int wDog;
    DiaPeerSockTransport *tr = NULL;
    ITSDiaConfig *cfg = &itsDiaConfig;

    DT_DBG(("DiaWatchDogTransport::Execute"));
    ITS_INT thrID = THREAD_GetCurrentThreadID();

    hmiInfo = HMI_AddToMonList(&monList, "DiaWatchDogTransport", (ITS_THREAD*)thrID);

    while (!_doExit)
    {
        if(cfg->IsHMIEnabled())
        {
            HMI_ResetCounter(hmiInfo);
        }  
        /**
         * Putting the timer sleep of 1 second 
         */ 
        //TIMERS_Sleep(1);
        TIMERS_USleep(999000);
        //Check if we are DeActivated and don't do anything.
        if(m_bDeActivated)
        {
            continue;
        }

        PEER_ENTRY *entry = PeerTable::GetPeerTable()->FindFirstEntry();

        while (entry != NULL)
        {
            if (DIA_PE_STATE(entry) == PEER_ST_I_OPEN || 
                DIA_PE_STATE(entry) == PEER_ST_R_OPEN)
            {
                ITS_USHORT inst = DIA_PE_INST(entry);
		wDog = ( (DIA_PE_DW_TIME_VAL(entry) > DEFAULT_DW_TIMER) ? DIA_PE_DW_TIME_VAL(entry):DEFAULT_DW_TIMER);
 
                /**
                 * Fix for Issue No.18 raised by Dhirananda during validation
                 * of BCGI ticket 1807.
                 * Directly getting Transport Instance from the Transport Table
                 * instead of getting from Peer Entry Handle.
                 */
                tr = (DiaPeerSockTransport *)trTable.getAt(inst);
        
                if (tr)
                {
                    ITS_UINT updateCount = tr->GetLastUpdate();

                    /* If check holds good for 1 sec sleep, if sleep duration
                       changes update accordingly
                     */
                    if (updateCount >= (wDog-1))
                    {
                        if (DIA_PE_DWA_PENDING(entry) < 1)
                        {
                            /**
			     * Fix for Issue No.16 raised by Dhirananda during
			     * validation of BCGI ticket 1807.
			     * Format of debug print is changed.
			     */
                            DT_DBG(("WatchDog TimeOut:No activity on Transport"\
                                     " since %d, for: %s.",updateCount,
                                     DIA_PE_HOST(entry)));
                            DT_DBG(("DiaWatchDogTransport::Sending DWR Msg."));
                            /* Timeout: Send Watchdog */
                            SendDWR(inst);

                            tr->IncrementLastUpdate();
                            MUTEX_AcquireMutex(&DIA_PE_MUX(entry));
                            DIA_PE_DWA_PENDING(entry)++;
                            MUTEX_ReleaseMutex(&DIA_PE_MUX(entry));
                        } 
                        /**
                         * Checking if DWA is pending and no activity on
                         * transport since 2 DeviceWatchDog Timers. 
                         */  
                        /* check holds good for 1 sec sleep,if sleep duration                           
                         * changes update accordingly
                         */
                        else if (updateCount >= ((2*wDog)-1))
                        {
                            /**
                             * Fix for Issue No.16 raised by Dhirananda during
                             * validation of BCGI ticket 1807.
                             * Format of debug print is changed.
                             */
                            DT_DBG(("WatchDog TimeOut:No activity on Transport"\
                                     " since %d, for: %s.", updateCount,
                                     DIA_PE_HOST(entry)));
                            DT_DBG(("DiaWatchDogTransport::No activity on "\
                                  "Transport for: %s.",DIA_PE_HOST(entry)));

                            tr->IncrementLastUpdate();

                             /* Disconnect and Initiate Failover */

                             
                            /**
                             * Added check for FailoverEnabled.
                             * Partial fix for issue Id:1119.
                             */ 
                            if (DIA_PEER_CHK_IS_FAILOVER_ENABLED(entry))                           
                            {
                              if ((ret = InitiateFailover(tr->GetInstance()))
                                                              == ITS_SUCCESS)
                              {
                                DIA_PEER_CHK_IS_FAILOVERED(entry) = true;
                                DT_DBG(("InitiateFailover::SUCCESS"));

                                if(itsDiaConfig.
                                             IsPeerMsgToAppEnabled())
                                {
                                     SendFailoverIndToApp(entry);
                                }
                              }
                              else
                              {
                                DT_ERR(("InitiateFailover::Failed:%d",ret));
                              }
                            }
                            else
                            {
                              DT_DBG(("FAILOVER::NOT Enabled"));
                              tr->SetExit();
                            }

                            /* Check if peer stayed in OPEN state even after failure detected */ 
                            if (updateCount >= ((3*wDog)))
                            {
                              /* Some thing wrong EOF is not received for socket */
                              /* Force cleanup */
                              ITS_UINT evtType = PEER_EVT_I_PEER_DISC;
                              if (DIA_PE_STATE(entry) == PEER_ST_I_OPEN)
                              {
                                  evtType = PEER_EVT_I_PEER_DISC;
                              }
                              else
                              {
                                  evtType = PEER_EVT_R_PEER_DISC;
                              }

                              if ((ret = DiaMsgRouter::UpdatePeerSM(NULL, entry,
                                      evtType,DIA_PE_HANDLE(entry),
                                        NULL)) == ITS_SUCCESS)
                              {
                                  DT_DBG(("Succesfully Submitted Message to Peer SM"));
                              }
                              else
                              {
                                  DT_ERR(("Failed to Handle Message in Peer SM = %d", ret));
                                  /* Start Retry Timer after the state machine returns failure
                                   */
                                  if (DIA_PE_RETRY_TIMER(entry) != TIMER_BAD_SERIAL)
                                  {
                                      PeerTable::StopTimer(RETRY, entry);
                                  }
                                  PeerTable::StartTimer(RETRY, entry);
                              }
                            }
                        }
                        else
                        {
                            if (tr)
                            {
                                /* Increament the LastUpdate Count after every
                                   second
                                 */
                                 tr->IncrementLastUpdate();
                            }
                        }

                    }
                    
                    /**
                     * Fix for Issue No.16 raised by Dhirananda during 
                     * validation of BCGI ticket 1807.
                     * Previously commented else statement is uncommented.
                     * Check for pending DWA entry is added. If it is nonzero 
                     * only then set it to zero.
                     */
                    else
                    {
                        /**
                         * Fix for whizible issueid 1227.(Merge from 
                         * Dia-ProductionRelease2_1 branch). 
                         */
                        if (tr)
                        {
                            /* Increament the LastUpdate Count after every 
                               second
                             */
                             tr->IncrementLastUpdate();
                        }

                        if(DIA_PE_DWA_PENDING(entry))
                        {
                            MUTEX_AcquireMutex(&DIA_PE_MUX(entry));
                            DIA_PE_DWA_PENDING(entry) = 0;
                            MUTEX_ReleaseMutex(&DIA_PE_MUX(entry));
                        }  
                    }
		    
                    MUTEX_AcquireMutex(tr->getWriteLock());

                    /* Check if socket flush has to be kicked for the peer */
                    if (tr->IsSocketCongested())
                    {
                        if (tr->GetSockFlushLastUpdate() >= (DIA_PE_SOCK_FLUSH_TIMER_VAL(entry) - 1))
                        {
                            ITS_BOOLEAN isPeerToBeDisconnected = ITS_FALSE;

                            ret = tr->FlushData(isPeerToBeDisconnected, ITS_FALSE);

                            if (isPeerToBeDisconnected)
                            {
                                DT_WRN(("Disconnecting the peer due to SockFlush retry count"));

                                ITS_UINT evtType = PEER_EVT_I_PEER_DISC;

                                if (DIA_PE_STATE(entry) == PEER_ST_I_OPEN)
                                {
                                    evtType = PEER_EVT_I_PEER_DISC;
                                }
                                else
                                {
                                    evtType = PEER_EVT_R_PEER_DISC;
                                }

                                if ( (ret = DiaMsgRouter::UpdatePeerSM(NULL, entry,
                                                evtType, DIA_PE_HANDLE(entry),
                                                NULL)) == ITS_SUCCESS)
                                {
                                    DT_DBG(("Succesfully Submitted Message to Peer SM"));
                                }
                                else
                                {
                                    DT_ERR(("Failed to Handle Message in Peer SM = %d", ret));

                                    /* Start Retry Timer after the state machine returns failure
                                    */
                                    if (DIA_PE_RETRY_TIMER(entry) != TIMER_BAD_SERIAL)
                                    {
                                        PeerTable::StopTimer(RETRY, entry);
                                    }

                                    PeerTable::StartTimer(RETRY, entry);
                                }
                            }
                        }
                        else
                        {
                            tr->IncrementSockFlushLastUpdate();

                            DT_DBG(("SockFlushLastUpdate: %d", tr->GetSockFlushLastUpdate()));
                        }
                    }

                    MUTEX_ReleaseMutex(tr->getWriteLock());

                }
                /**
                 * Fix for Issue No.18 raised by Dhirananda during validation
                 * of BCGI ticket 1807.
                 * Changing the state to Close as the Transport no longer exists.
                 */ 
                else
                {
                    DT_DBG(("DiaWatchDogTransport::Transport Unavailable."));
                    MUTEX_AcquireMutex(&DIA_PE_MUX(entry));
                    DIA_PE_STATE(entry) = PEER_ST_CLOSED;
                    MUTEX_ReleaseMutex(&DIA_PE_MUX(entry));
                }    
            }

            entry = PeerTable::GetPeerTable()->FindNextEntry(entry);
        }
    }
    HMI_RemoveFromMonList(&monList, (ITS_THREAD*)thrID);
}

int
DiaWatchDogTransport::SendFailoverIndToApp(PEER_ENTRY *peer)
{                            
    /* Send Indication to Application */                     

    if (DiaMsgRouter::SendIndication(NULL, peer, NULL, 
                                     FAILOVER_IND_FROM_STACK) == ITS_SUCCESS)
    {
        DT_DBG(("SUCCESS: Indication to Application"));
        return (ITS_SUCCESS);
    }
    else
    {
        DT_ERR(("Failed To Send Indication to Application"));
        return (!ITS_SUCCESS);
    }

}

