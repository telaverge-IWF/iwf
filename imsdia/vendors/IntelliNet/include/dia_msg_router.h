/*********************************-*HPP*-************************************
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
 * LOG: $Log: dia_msg_router.h,v $
 * LOG: Revision 3.11.6.1.4.1.4.4.8.1.4.1  2014/10/27 08:28:39  millayaraja
 * LOG: changes for HA HotStandBy
 * LOG:
 * LOG: Revision 3.11.6.1.4.1.4.4.8.1  2014/07/02 06:37:11  millayaraja
 * LOG: updated to handle answer message without mandatory field missing
 * LOG:
 * LOG: Revision 3.11.6.1.4.1.4.4  2013/12/13 09:34:58  vsarath
 * LOG: Merged the session-splict changes
 * LOG:
 * LOG: Revision 3.11.6.1.4.1.4.3  2013/12/09 04:52:43  ncshivakumar
 * LOG: Fixed bug 2439,2443,2368,1898
 * LOG:
 * LOG: Revision 3.11.6.1.4.1.4.2  2013/10/26 07:42:21  ncshivakumar
 * LOG: RFC 6733 changes
 * LOG:
 * LOG: Revision 3.11.6.1.4.1.4.1  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 3.11.6.1.4.1  2013/04/04 09:03:53  mallikarjun
 * LOG: MemLeak Fixes Bug 1205 1298
 * LOG:
 * LOG: Revision 3.11.6.1  2012/12/03 08:40:52  ncshivakumar
 * LOG: Changes done for adding static routing table
 * LOG:
 * LOG: Revision 3.11  2010/08/19 11:21:26  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 3.10  2009/07/13 06:09:23  rajeshak
 * LOG: Reverting back session table changes.
 * LOG:
 * LOG:
 * LOG: Revision 2.8  2006/11/09 14:20:29  tpanda
 * LOG: clientId handling for IDS at the stack level
 * LOG:
 * LOG: Revision 2.7  2006/10/30 15:57:41  yranade
 * LOG: ReleaseSession API is Asychronous.
 * LOG:
 * LOG: Revision 2.6  2006/10/24 14:20:21  yranade
 * LOG: ValidateMessage updates.
 * LOG:
 * LOG: Revision 2.5  2006/10/17 18:08:06  yranade
 * LOG: Add ValidateMessage API.
 * LOG:
 * LOG: Revision 2.4  2006/10/13 16:36:22  yranade
 * LOG: Error Handling related updates.
 * LOG:
 * LOG: Revision 2.3  2006/10/05 13:00:22  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.2  2006/09/26 06:12:20  nvijikumar
 * LOG: Added return statement ( issue with Sun CC Compilation)
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 *
 * ID: $Id: dia_msg_router.h,v 3.11.6.1.4.1.4.4.8.1.4.1 2014/10/27 08:28:39 millayaraja Exp $
 ****************************************************************************/
#ident "$Id: dia_msg_router.h,v 3.11.6.1.4.1.4.4.8.1.4.1 2014/10/27 08:28:39 millayaraja Exp $"

#ifndef DIA_MSG_ROUTER_H
#define DIA_MSG_ROUTER_H

#include <dia_defines.h>
#include <dia_module.h>
#include <dia_msghandler.h>

#include <dia_cmn.h>
#include <dia_err.h>
#include <dia_upstream.h>
#include <dia_downstream.h>
#include <dia_timer_handler.h>
#include <dia_ip_trans.h>
#include <dia_session_table.h>
#include <dia_realm_table.h>
#include <dia_incoming_msg_q.h>

/*.Interface: DiaMsgSender
 *****************************************************************************
 *  Interface:
 *      DiaMsgSender Class
 *
 *  Purpose:
 *      Implement the Diameter Msg Sender Functionality
 *****************************************************************************/
class DiaMsgSender:public DIAModule
{
public:
    /*.implementation:public,inline,DiaMsgSender
    ************************************************************************
    *  Purpose:
    *       DiaMsgSender Module Derived Class Constructor.
    *
    *  Input Parameters:
    *       numThreads - Number of threads/workers for this module
    *
    *
    ************************************************************************/
    DiaMsgSender(int numThreads)
    : DIAModule(numThreads, DIASTACK_SENDER_TQ_NAME, DIASTACK_SENDER_TQ_INST)
    {
        diaDownStream    = new DiaDownStreamMsgHandler();
        diads            = new DiaDownStreamMsgHandler(DIA_APP_REM_SESS_INST);
        diaGcsDwnStrm    = new DiaDownStreamMsgHandler(DIA_GCS_APP_INST);
        diadsGcs         = new DiaDownStreamMsgHandler(DIA_GCS_APP_REM_SESS_INST);
        diaIdsDownStrm   = new DiaDownStreamMsgHandler(DIA_IDS_APP_INST);
        diaRepEvtHandler   = new DiaDownStreamMsgHandler(ITS_REP_EVENT_FROM_APP);

        RegisterMessageHandler(diaDownStream, DIA_APP_INST);
        RegisterMessageHandler(diads, DIA_APP_REM_SESS_INST);
        RegisterMessageHandler(diaGcsDwnStrm, DIA_GCS_APP_INST);
        RegisterMessageHandler(diadsGcs, DIA_GCS_APP_REM_SESS_INST);
        RegisterMessageHandler(diaIdsDownStrm, DIA_IDS_APP_INST);
        RegisterMessageHandler(diaRepEvtHandler, ITS_REP_EVENT_FROM_APP);
    }

    /*.implementation:public,inline,DiaMsgSender
    ************************************************************************
    *  Purpose:
    *       Destruct Diameter Stack module
    *
    ************************************************************************/
    ~DiaMsgSender()
    {
        delete diaDownStream;
        delete diads;
        delete diaGcsDwnStrm;
        delete diadsGcs;
        delete diaIdsDownStrm;
        delete diaRepEvtHandler;
    }

    MessageHandler *GetDownStream()
    {
        return diaDownStream;
    }

    /*.implementation:public,inline,DiaMsgSender
    ************************************************************************
    *  Purpose:
    *       Stop Diameter Stack module
    *
    ************************************************************************/
    int Stop()
    {
        its::Event ev;
        ev.SetSource(DIASTACK_SENDER_TQ_INST);
        its::ITS_Transport::PutEvent(DIASTACK_SENDER_TQ_INST, ev);
        return (ITS_SUCCESS);
    }

private:
    MessageHandler      *diaDownStream;
    MessageHandler      *diads;
    MessageHandler      *diaGcsDwnStrm;
    MessageHandler      *diadsGcs;
    MessageHandler      *diaIdsDownStrm;
    MessageHandler      *diaRepEvtHandler;

};

/*.Interface: DiaMsgRouter 
 *****************************************************************************
 *  Interface:
 *      DiaMsgRouter Class
 *      
 *  Purpose:
 *      Implement the Diameter Msg Router Functionality
 *****************************************************************************/
class DiaMsgRouter:public DIAModule
{
public:
    /*.implementation:public,inline,DiaMsgRouter
    ************************************************************************
    *  Purpose:
    *       DiaMsgRouter Module Derived Class Constructor.
    *       
    *  Input Parameters:
    *       numThreads - Number of threads/workers for this module
    *       
    *       
    ************************************************************************/
    DiaMsgRouter(int numThreads, int tqInstance, char* tqName)
    : DIAModule(numThreads, tqName, tqInstance, true )
    {
        // Initialize DiaMsgRouter Table
        // UpStream Handlers

        diaUpStream      = new DiaUpStreamMsgHandler();
        diaGcsUpStrm     = new DiaUpStreamMsgHandler(DIA_GCS_NET_INST);
        /* This is used only to set the isRedundany flag */
        diaGcsNoSrc      = new DiaUpStreamMsgHandler(DIA_GCS_NO_SRC_INST);
        //Timer Handlers

        diaTimerHandler  = new DiaTimerMsgHandler();

        RegisterMessageHandler(diaUpStream, DIA_NET_INST);
        RegisterMessageHandler(diaGcsUpStrm, DIA_GCS_NET_INST);
        RegisterMessageHandler(diaGcsNoSrc, DIA_GCS_NO_SRC_INST);
        RegisterMessageHandler(diaTimerHandler, ITS_TIMER_SRC);

        /* No Confusion:: Following are Initialized / Registered by default,
                          but used only if single thread */
        diaDownStream  = new DiaDownStreamMsgHandler();
        diads          = new DiaDownStreamMsgHandler(DIA_APP_REM_SESS_INST);
        diaGcsDwnStrm  = new DiaDownStreamMsgHandler(DIA_GCS_APP_INST);
        diadsGcs       = new DiaDownStreamMsgHandler(DIA_GCS_APP_REM_SESS_INST);
        diaIdsDownStrm   = new DiaDownStreamMsgHandler(DIA_IDS_APP_INST);
        diaRepEvtHandler   = new DiaDownStreamMsgHandler(ITS_REP_EVENT_FROM_APP);

        diaInMsgQ      = new IncomingMsgQ;
        RegisterMessageHandler(diaDownStream, DIA_APP_INST);
        RegisterMessageHandler(diads, DIA_APP_REM_SESS_INST);
        RegisterMessageHandler(diaGcsDwnStrm, DIA_GCS_APP_INST);
        RegisterMessageHandler(diadsGcs, DIA_GCS_APP_REM_SESS_INST);
        RegisterMessageHandler(diaIdsDownStrm, DIA_IDS_APP_INST);
        RegisterMessageHandler(diaRepEvtHandler, ITS_REP_EVENT_FROM_APP);

    }

    MessageHandler *GetDownStream()
    {
        return diaDownStream;
    }

    /*.implementation:public,inline,DiaMsgRouter
    ************************************************************************
    *  Purpose:
    *       Destruct Diameter Stack module
    *           
    ************************************************************************/
    ~DiaMsgRouter()
    {
        delete diaUpStream;
        delete diaGcsUpStrm;
        delete diaGcsNoSrc;
        delete diaTimerHandler;

        /* Initialized by default, but used only incase of single thread */
        delete diaDownStream;
        delete diads;
        delete diaGcsDwnStrm;
        delete diadsGcs;
        delete diaIdsDownStrm;
        delete diaInMsgQ;
        delete diaRepEvtHandler;
    }
    
    /*.implementation:public,inline,DiaMsgRouter
    ************************************************************************
    *  Purpose:
    *       Stop Diameter Stack module
    *           
    ************************************************************************/       
    int Stop()
    {
        its::Event ev;
        ev.SetSource(DIASTACK_TQ_INST);
        its::ITS_Transport::PutEvent(DIASTACK_TQ_INST, ev);
        return (ITS_SUCCESS);
    }

    static int SendIndication( SESSION_ENTRY* ent, PEER_ENTRY* peer, 
                             char* sessionId, int indicType);

    static int SendToPeer(ITS_USHORT inst, ITS_EVENT *cEvt);

    static int SendToPeer(ITS_HANDLE handle, ITS_OCTET *buff, int len);

    static int SendCmdToPeer(ITS_USHORT inst, DIA_HDR* hdr, DIA_CMD *cmd, 
                             ITS_UINT evtType = PEER_EVT_SEND_MESSAGE,bool errFlag=false);

    static int SendCmdToPeer(ITS_USHORT inst, DIA_HDR* hdr, DIA_BASE_CMD *cmd, 
                             ITS_UINT evtType = PEER_EVT_SEND_MESSAGE);

    static int SendMsgToApp(SESSION_ENTRY *ctxt, ITS_EVENT *evt,
                            ITS_UINT msgType = ITS_DIA_MSG_TYPE_DATA);

    static int SendMsgToApp(ITS_UINT msgType, ITS_UINT sessIndx,
                            ITS_UINT appId, ITS_OCTET *payload,
                            ITS_UINT payloadLen, ITS_UINT clientId=0);

    static int SendPeerMsgToApp(DIA_GEN_CMD *gCmd,
                            ITS_UINT msgType = ITS_DIA_MSG_TYPE_IND_WITH_DATA);

    static int SendPeerMsgToApp(DIA_BASE_CMD *gCmd,
                            ITS_UINT msgType = ITS_DIA_MSG_TYPE_IND_WITH_DATA);

    static int UpdatePeerStateMachine(DIA_BASE_CMD *cmd, PEER_ENTRY* pEntry,
                            ITS_UINT evtType, ITS_HANDLE trHandle,
                            ITS_EVENT *event);

    static int UpdatePeerSM(DIA_CMD *cmd, PEER_ENTRY* pEntry,
                            ITS_UINT evtType, ITS_HANDLE trHandle,
                            ITS_EVENT *event);

    static int IsLocalRouting(DIA_BASE_CMD *&cmd, REALM_ENTRY* &rEntry);

    static int RequestForwarding(DIA_BASE_CMD *&cmd, SESSION_ENTRY *&sessInfo,
                                 ITS_USHORT &peerInstance);
    static int IsLocalMatchFound(DIA_BASE_CMD *&cmd);

    static int StaticRouting(DIA_BASE_CMD *&cmd, SESSION_ENTRY *&sessInfo,
                             ITS_USHORT &peerInstance,REALM_ENTRY *rEntry);

    static int RequestRouting(DIA_BASE_CMD *&cmd, SESSION_ENTRY *&sessInfo,
                              ITS_USHORT &peerInstance,
                              REALM_ENTRY *rEntry);

    static int AnswerForwarding(DIA_CMD *&cmd, ITS_EVENT *evt,
                                ITS_USHORT &peerInstance);

    static int AnswerRouting(DIA_CMD *&cmd, ITS_EVENT *evt,
                             ITS_USHORT &peerInstance);

    static int ValidateMessage(DIA_GEN_CMD *ce, DIA_GEN_CMD *msg);
    static int ValidateMessage(DIA_GEN_CMD *ce, DIA_BASE_CMD *msg);

    static int Failover(PEER_ENTRY* peer);
    static int Failback(PEER_ENTRY* peer);

    /**
     * API added for agents to check the Loop in path.
     */   
    static ITS_BOOLEAN IsLoopDetected(DIA_BASE_CMD *&gCmd);

    /**
     * API added to check if the destination peer is directly
     * connected to the node and RequestForwarding is posssible.
     */   
    static ITS_BOOLEAN VerifyIfReqForwarding(DIA_BASE_CMD *&gCmd);
    
    /**
     * API added for agents to check the Predictive Loop in path.
     */   
    static ITS_BOOLEAN IsPredectiveLoopDetected(DIA_BASE_CMD *&msg,
                                                const char * destHost);

    static int SelectAlternatePeerToRoute(const char *destHost,DIA_BASE_CMD *&cmd,
                                                  SESSION_ENTRY *e,ITS_USHORT &peerInstance);
    static int SendCUR(unsigned int* authorizationAppId,unsigned int numOfAuthAppId,
                       unsigned int* accountingAppId, unsigned int numOfAcctAppId);
    static IncomingMsgQ        *diaInMsgQ;
    IncomingMsgQ* GetInMsgQ(){return diaInMsgQ;};

    static int CheckIfMsgTobeQueued(DIA_BASE_CMD *msg,
                                     SESSION_ENTRY *ent,ITS_EVENT &ev);

    static ITS_INT RepostPendingMessageOfSession(SESSION_ENTRY* aSessEntry,
                                     ITS_OCTET * sessionId);
    static ITS_INT RemoveMsgQEventEntry(ITS_UINT sesIndex);

    static int IsCapabilityUpdated(unsigned int AppId,bool isAuthAppId=false);
private:
    MessageHandler      *diaDownStream;    
    MessageHandler      *diaUpStream;
    MessageHandler      *diaTimerHandler;
    MessageHandler      *diads;
    MessageHandler      *diaGcsDwnStrm;
    MessageHandler      *diadsGcs;
    MessageHandler      *diaGcsNoSrc;
    MessageHandler      *diaGcsUpStrm;
    MessageHandler      *diaIdsDownStrm;
    MessageHandler      *diaRepEvtHandler;
    
};

#endif
