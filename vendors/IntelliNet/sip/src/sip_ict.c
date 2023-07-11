/***************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *  ID: $Id: sip_ict.c,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
 *
 *  $Log: sip_ict.c,v $
 *  Revision 9.1  2005/03/23 12:54:27  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.12  2005/03/21 13:53:25  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.11.2.3  2005/03/09 07:02:19  mkrishna
 *  Bug fixing cycle
 *
 *  Revision 1.11.2.2  2005/02/07 14:08:20  mkrishna
 *  Modified for PRACK message.
 *
 *  Revision 1.11.2.1  2004/12/28 14:00:33  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.11  2004/07/19 14:38:40  sjaddu
 *  Added Handle2345xx function in terminated state.
 *
 *  Revision 1.10  2004/04/29 09:54:58  akumar
 *  Added 400 Bad Req handling.
 *
 *  Revision 1.9  2004/04/27 11:15:39  sjaddu
 *  Transport layer revamping, no more dumps.
 *
 *  Revision 1.8  2004/04/23 13:19:44  sjaddu
 *  Testing going on.
 *
 *  Revision 1.7  2004/04/19 10:30:47  akumar
 *  Minor bug fix while testing 302 moved temporarily msg.
 *
 *  Revision 1.6  2004/04/15 12:16:15  sjaddu
 *  Added indications & state machine revamping.
 *
 *  Revision 1.5  2004/04/05 12:48:31  akumar
 *  Bug fix cycle.
 *
 *  Revision 1.4  2004/04/05 07:47:25  sjaddu
 *  More testing, one complete call works fine.
 *
 *  Revision 1.3  2004/04/01 06:44:03  sjaddu
 *  Testing is in progress.
 *
 *  Revision 1.2  2004/03/30 11:51:42  sjaddu
 *  Commit after some unit testing is done.
 *
 *  Revision 1.1  2004/03/19 06:02:11  sjaddu
 *  Added first revsion for sip, work in progress.
 *
 ****************************************************************************/
#include  <sip_intern.h>

#define ICT_MAX_FSM_STATES   5

/* fsm for ICT transactions */
static SIP_FSM_MAP_TABLE ICT_mapTable[ICT_MAX_FSM_STATES][SIP_MAX_MSGS];

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Unexpected msg handling here
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int 
ICT_UnExpectedMsg(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    if (msg)
    {
        SIP_WARNING(("ICT_UnExpectedMsg:Received unexpected msg %d\n", msg->msgId));
    }
    else
    {
        SIP_WARNING(("ICT_UnExpectedMsg::Unexpected timeout \n"));
    }
    return SIP_TRANSACTION_UNEXPECTED_MSG;
}

/*
 *  IDLE  IDLE  IDLE  IDLE  IDLE  IDLE  IDLE
 */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Invite handling in idle state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int 
IDLE_HandleInvite(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    SIP_DEBUG(("IDLE_HandleInvite:: Received Invite from APP \n"));

    /* Start timer A, and then send event to remote asap */
    /* Send to remote */
    ret = SIP_SendEventToNet(ctxt);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set flag for reliable responses with prack */
    if ((msg->require[0] != 0) && strcmp(msg->require, "100rel") == 0)
    {
        ctxt->isReliableResp = ITS_TRUE;
    }
    else
    {
        ctxt->isReliableResp = ITS_FALSE;
    } 

    ctxt->fsmState = SIP_ICT_CALLING;

    SIP_StartTimer(ctxt, SIP_TIMER_T1, ctxt->reTranstimer);
    
    ctxt->reTranstimer += ctxt->reTranstimer;

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Prack handling in idle state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
IDLE_HandlePrack(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    SIP_TRANSACTION_KEY key;
    SIP_TRANSACTION_CTXT *ctxt_invite = NULL;
 
    SIP_DEBUG(("IDLE_HandlePrack:: Received Prack from APP \n"));

    /* search for invite transaction. if doesn't exist close prack 
       transaction also. */
    SIP_TransactionKeyFromMsg(msg, &key);
    key.cSeq.number = msg->rack.cseqNum;
    ctxt_invite = SIP_FindTransactionCtxt(&key, &ret);
  
    if (ctxt_invite != NULL && ctxt_invite->isReliableResp)
    {
        /* Start timer A, and then send event to remote asap */
        /* Send to remote */
        ret = SIP_SendEventToNet(ctxt);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        ctxt->fsmState = SIP_ICT_CALLING;

        SIP_StartTimer(ctxt, SIP_TIMER_T2, ctxt->reTranstimer);

        ctxt->reTranstimer += ctxt->reTranstimer;
    }
    else
    {
        SIP_ERROR(("IDLE_HandlePrack:: invite context not found \n"));
        ctxt->purge  = ITS_TRUE;
        return SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    SIP_CommitTransactionCtxt(ctxt_invite);

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in ICT idle state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static SIP_TransactionHandler
ICT_GetMsgProcIdle(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_MSG_INVITE:
        return IDLE_HandleInvite;
    case SIP_MSG_PRACK:
        return IDLE_HandlePrack; 
    default :
        return ICT_UnExpectedMsg;
    }
}

/*
 *  CALLING CALLING CALLING CALLING CALLING
 */ 
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handles 1xx msg in calling state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int 
CALLING_Handle1xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_EVENT *sipEvt = NULL;

        SIP_DEBUG(("CALLING_Handle1xx:: Received 1xx from remote \n"));

        /* double check for remote 1xx msg */
        if (ctxt->isReliableResp && msg->rseq == 0)
        {
            SIP_DEBUG(("CALLING_Handle1xx:: Received 1xx from remote"
                       " without mandatory header \n"));
            return SIP_TRANSACTION_UNEXPECTED_MSG;
        }

        /* Stop timer A */
        SIP_StopTimer(ctxt);

        ret  = SIP_StartTimer(ctxt, SIP_TIMER_T1,
                        (SIP_configInfo.trnTimer - ctxt->reTranstimer));
        if (ret != ITS_SUCCESS)
        {
            SIP_ERROR(("Failed to start timer, terminating transaction\n")); 
            ctxt->purge  = ITS_TRUE;
            return ret;
        }
        
        /* Change to proceeding , that's it don't need to start timer? */
        ctxt->fsmState = SIP_ICT_PROCEEDING;

        sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
        sipEvt->type = SIP_DATA_EVENT;
        sipEvt->msg = (void*)msg;
        sipEvt->buf = NULL;

        /* Send to app*/
        SIP_SendEventToApp(sipEvt);
        
    }
    else
    {
        SIP_ERROR(("CALLING_Handle1xx:: Received 1xx from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handles 400 msg in calling state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
CALLING_Handle400(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_EVENT *sipEvt = NULL;
        SIP_DEBUG(("CALLING_Handle400:: Received 400 from remote \n"));

        /* Stop timer A */
        SIP_StopTimer(ctxt);

        SIP_StartTimer(ctxt, SIP_TIMER_T1,
                        (SIP_configInfo.trnTimer - ctxt->reTranstimer));

        /* Change to proceeding , that's it don't need to start timer? */
        ctxt->fsmState = SIP_ICT_TERMINATED;

        sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
        sipEvt->type = SIP_DATA_EVENT;
        sipEvt->msg = (void*)msg;
        sipEvt->buf = NULL;

        /* Send to app*/
        SIP_SendEventToApp(sipEvt);
    }
    else
    {
        SIP_ERROR(("CALLING_Handle400:: Received 400 from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    return ret;
}   

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handles 2xx msg in calling state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int 
CALLING_Handle2xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_EVENT *sipEvt = NULL;
        SIP_DEBUG(("CALLING_Handle2xx:: Received 2xx from remote \n"));

        if (strcmp(msg->cseq.method, ctxt->cSeq.method) == 0)
        {
            /* Stop timer A */
            SIP_StopTimer(ctxt);

            /* go to completed state */
            ctxt->fsmState = SIP_ICT_COMPLETED;
            ret = SIP_StartTimer(ctxt, SIP_TIMER_T1,
                            (SIP_configInfo.trnTimer - ctxt->reTranstimer));
            if (ret != ITS_SUCCESS)
            {
                SIP_ERROR(("Failed to start timer, terminating transaction\n")); 
                ctxt->purge  = ITS_TRUE;
                return ret;
            }

            sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
            sipEvt->type = SIP_DATA_EVENT;
            sipEvt->msg = (void*)msg;
            sipEvt->buf = NULL;
            
            /* Send to app*/
            SIP_SendEventToApp(sipEvt);
        }
        else
        {
            ret = SIP_TRANSACTION_UNEXPECTED_MSG;
            SIP_ERROR(("CALLING_Handle2xx:: Received 2xx with method %s\n",
                        msg->cseq.method));
        }
    }
    else
    {
        SIP_ERROR(("CALLING_Handle2xx:: Received 2xx from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handles 3,4,5,5,6 xxx msg in calling state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int 
CALLING_Handle3456xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;

    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_EVENT *sipEvt = NULL;
        SIP_DEBUG(("CALLING_Handle3456xx:: Received 3456xx from remote \n"));


        if (strcmp(msg->cseq.method, ctxt->cSeq.method) == 0)
        {
            /* Stop timer A */
            SIP_StopTimer(ctxt);
            if (strcmp(msg->cseq.method, "PRACK") == 0)
            {
                ctxt->purge  = ITS_TRUE;
                sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
                sipEvt->type = SIP_DATA_EVENT;
                sipEvt->msg = (void*)msg;
                sipEvt->buf = NULL;

                /* Send to app*/
                SIP_SendEventToApp(sipEvt);
                return ret;
            }

            /* go to completed state */
            ctxt->fsmState = SIP_ICT_COMPLETED;

            /* start timer D, no timerrequire for TCP */
            ret = SIP_StartTimer(ctxt, SIP_TIMER_T1,
                            (SIP_configInfo.trnTimer - ctxt->reTranstimer));
            if (ret != ITS_SUCCESS)
            {
                SIP_ERROR(("Failed to start timer, terminating transaction\n")); 
                ctxt->purge  = ITS_TRUE;
                return ret;
            }

            sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
            sipEvt->type = SIP_DATA_EVENT;
            sipEvt->msg = (void*)msg;
            sipEvt->buf = NULL;

            /* Send to app*/
            SIP_SendEventToApp(sipEvt);
        }
        else
        {
            ret = SIP_TRANSACTION_UNEXPECTED_MSG;
            SIP_ERROR(("CALLING_Handle3xx:: Received 3xx with method %s\n",
                        msg->cseq.method));
        }
    }
    else
    {
        SIP_DEBUG(("CALLING_Handle3456xx:: Received 3456xx from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handles timeout msg in calling state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int 
CALLING_HandleTimeout(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;

    SIP_DEBUG(("CALLING_HandleTimeout:: Time out \n"));


    if (ctxt->reTranstimer < SIP_configInfo.trnTimer)
    {
        /* start timer A */
        ret = SIP_StartTimer(ctxt, SIP_TIMER_T1, ctxt->reTranstimer);
        if (ret != ITS_SUCCESS)
        {
            SIP_ERROR(("Failed to start timer, terminating transaction\n")); 
            ctxt->purge  = ITS_TRUE;
            return ret;
        }

        ctxt->reTranstimer += ctxt->reTranstimer;

        /* retrasmit to remote */
        ret = SIP_SendEventToNet(ctxt);
    }
    else
    {
        ret = SIP_SendTimeoutToApp(ctxt, SIP_NO_RESPONSE_FROM_NET);

        /* delete the transaction */
        ctxt->purge = ITS_TRUE;
    }
    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handles prack timeout msg in calling state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
CALLING_HandlePrackTimeout(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, 
                           ITS_USHORT src)
{
    int ret = 0;
    SIP_TRANSACTION_KEY key;
    SIP_TRANSACTION_CTXT *ctxt_invite = NULL;
    

    /* fill up key with prack ctxt info */
    strcpy(key.callId.number, ctxt->callId.number);
    strcpy(key.callId.host, ctxt->callId.host);
    strcpy(key.cSeq.method, ctxt->cSeq.method);
    key.cSeq.number = ctxt->rack.cseqNum;

    ctxt_invite = SIP_FindTransactionCtxt(&key, &ret);
    if (ctxt_invite != NULL)
    {
        if ((ctxt_invite->fsmState == SIP_ICT_PROCEEDING) || 
            (ctxt_invite->fsmState == SIP_ICT_TERMINATED))
        {
            SIP_ERROR(("CALLING_HandlePrackTimeout::closing prack trans\n"));
            ctxt->purge = ITS_TRUE;
        }
    }
    else
    {
        SIP_ERROR(("CALLING_HandlePrackTimeout::invite context not found\n"));
        ctxt->purge = ITS_TRUE;  
        return SIP_NO_TRANSACTION_FOR_MSG_IND;
    }
    SIP_CommitTransactionCtxt(ctxt_invite);

 
    if (ctxt->reTranstimer < SIP_configInfo.trnTimer)
    {
        SIP_DEBUG(("CALLING_HandlePrackTimeout:: time out G \n"));

        /* This is time out G*/
        if (ctxt->reTranstimer < SIP_configInfo.T2)
        {
            SIP_StartTimer(ctxt, SIP_TIMER_T2, ctxt->reTranstimer);
        }
        else
        {
            SIP_StartTimer(ctxt, SIP_TIMER_T2, SIP_configInfo.T2);
        }

        ctxt->reTranstimer +=  ctxt->reTranstimer;

        /* retransmit response to remote */
        ret = SIP_SendEventToNet(ctxt);
    }
    else
    {
        SIP_WARNING(("CALLING_HandlePrackTimeout:: Max retransmissions reached"
                     " deleting the entry \n"));
        /* This is time  out H*/
        ret = SIP_SendTimeoutToApp(ctxt, SIP_NO_RESPONSE_FROM_NET);
        ctxt->purge = ITS_TRUE;
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handles cancel msg in calling state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int 
CALLING_HandleCancel(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_ERROR(("CALLING_HandleCancel:: Received Cancel from remote \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    else
    {
        SIP_DEBUG(("CALLING_HandleCancel:: Received Cancel from app \n"));

        /* Stop timer A */
        SIP_StopTimer(ctxt);
        
        /* No state change here, copy the headers of cancel req */
        SIP_CopyHeadersToCtxt(msg, ctxt);

        SIP_StartTimer(ctxt, SIP_TIMER_T1, SIP_configInfo.T1);

        /* Send to app*/
        ret = SIP_SendEventToNet(ctxt);
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in ICT Calling  state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static SIP_TransactionHandler
ICT_GetMsgProcCalling(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_MSG_100:
    case SIP_MSG_180:
    case SIP_MSG_181:
    case SIP_MSG_182:
    case SIP_MSG_183:
        return CALLING_Handle1xx;
    case SIP_MSG_200:
        return CALLING_Handle2xx;
    case SIP_MSG_400:
        return CALLING_Handle400;
    case SIP_MSG_300:
    case SIP_MSG_301:
    case SIP_MSG_302:
    case SIP_MSG_305:
    case SIP_MSG_380:
    case SIP_MSG_401:
    case SIP_MSG_402:
    case SIP_MSG_403:
    case SIP_MSG_404:
    case SIP_MSG_405:
    case SIP_MSG_406:
    case SIP_MSG_407:
    case SIP_MSG_408:
    case SIP_MSG_410:
    case SIP_MSG_413:
    case SIP_MSG_414:
    case SIP_MSG_415:
    case SIP_MSG_416:
    case SIP_MSG_420:
    case SIP_MSG_421:
    case SIP_MSG_423:
    case SIP_MSG_480:
    case SIP_MSG_481:
    case SIP_MSG_482:
    case SIP_MSG_483:
    case SIP_MSG_484:
    case SIP_MSG_485:
    case SIP_MSG_486:
    case SIP_MSG_487:
    case SIP_MSG_488:
    case SIP_MSG_491:
    case SIP_MSG_493:
    case SIP_MSG_500:
    case SIP_MSG_501:
    case SIP_MSG_502:
    case SIP_MSG_503:
    case SIP_MSG_504:
    case SIP_MSG_505:
    case SIP_MSG_513:
    case SIP_MSG_600:
    case SIP_MSG_603:
    case SIP_MSG_604:
    case SIP_MSG_606:
        return CALLING_Handle3456xx; 
    case SIP_TIMER_T1:
        return CALLING_HandleTimeout;
    case SIP_TIMER_T2:
        return CALLING_HandlePrackTimeout;
    case SIP_MSG_CANCEL:
        return CALLING_HandleCancel;
    case SIP_MSG_INVITE:
    case SIP_MSG_PRACK:
    default :
        return ICT_UnExpectedMsg;
        
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles 1xx in ICT Proceeding state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PROCEEDING_Handle1xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    SIP_EVENT *sipEvt = NULL;

    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_DEBUG(("PROCEEDING_Handle1xx:: Received 1xx from remote \n"));
        sipEvt  = ITS_Malloc(sizeof(SIP_EVENT));
        sipEvt->type  = SIP_DATA_EVENT;
        sipEvt->msg   = (void *)msg;

        ret = SIP_SendEventToApp(sipEvt);
    }
    else
    {
        SIP_ERROR(("PROCEEDING_Handle1xx:: Received 1xx from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles 2xx in ICT Proceeding state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PROCEEDING_Handle2xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_EVENT *sipEvt = NULL;
        SIP_DEBUG(("PROCEEDING_Handle2xx:: Received 2xx from remote \n"));

        if (strcmp(msg->cseq.method, ctxt->cSeq.method) == 0)
        {
            /* Chnage to complted state and start timer D */

            /* go to completed state */
            ctxt->fsmState = SIP_ICT_COMPLETED;

            sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
            sipEvt->type = SIP_DATA_EVENT;
            sipEvt->msg = (void*)msg;
            sipEvt->buf = NULL;

            /* Send to app*/
            ret = SIP_SendEventToApp(sipEvt);
        }
        else
        {
            ret = SIP_TRANSACTION_UNEXPECTED_MSG;
            SIP_ERROR(("PROCEEDING_Handle2xx:: Method mismatch %s \n",
                        msg->cseq.method));
        }
    }
    else
    {
        SIP_ERROR(("PROCEEDING_Handle2xx:: Received 2xx from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles 3456xx in ICT Proceeding state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PROCEEDING_Handle3456xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_EVENT *sipEvt = NULL;
        SIP_DEBUG(("PROCEEDING_Handle3456xx:: Received 3456xx from remote \n"));

        if (strcmp(msg->cseq.method, ctxt->cSeq.method) == 0)
        {
         
            /* Chnage to complted state and start timer D */
            /* go to completed state */
            ctxt->fsmState = SIP_ICT_COMPLETED;

            sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
            sipEvt->type = SIP_DATA_EVENT;
            sipEvt->msg = (void*)msg;
            sipEvt->buf = NULL;

            /* Send to app*/
            SIP_SendEventToApp(sipEvt);
        }
        else
        {
            ret = SIP_TRANSACTION_UNEXPECTED_MSG;
            SIP_ERROR(("PROCEEDING_Handle3456xx:: Method mismatch %s \n",
                        msg->cseq.method));
        }
    }
    else
    {
        SIP_ERROR(("PROCEEDING_Handle3456xx:: Received 3456xx from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handles cancel msg in proceeding state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int 
PROCEEDING_HandleCancel(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg,
                        ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_ERROR(("PROCEEDING_HandleCancel:: Received Cancel from remote \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    else
    {
        SIP_DEBUG(("PROCEEDING_HandleCancel:: Received Cancel from app \n"));

        /* 
         * here we have to see, what is the last response recvd, it should be
         * 100 trying, if that was 180 ringing then cancel is invalid
         * message here
         */

        /* No state change here, copy the headers of cancel req */
        SIP_CopyHeadersToCtxt(msg, ctxt);

        /* Send to app*/
        ret = SIP_SendEventToNet(ctxt);
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles time out in ICT proceeding state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PROCEEDING_HandleTimeout(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;

    SIP_DEBUG(("PROCEEDING_HandleTimeout:: received \n"));

    ctxt->purge = ITS_TRUE;

    /* didn't received 2345xxx from NET, purge tr, send timeout indication */
    ret = SIP_SendTimeoutToApp(ctxt, SIP_NO_RESPONSE_FROM_NET);
    
    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in ICT Proceeding state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static SIP_TransactionHandler
ICT_GetMsgProcProceeding(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_MSG_100:
    case SIP_MSG_180:
    case SIP_MSG_181:
    case SIP_MSG_182:
    case SIP_MSG_183:
        return PROCEEDING_Handle1xx;
    case SIP_MSG_200:
        return PROCEEDING_Handle2xx;
    case SIP_MSG_300:
    case SIP_MSG_301:
    case SIP_MSG_302:
    case SIP_MSG_305:
    case SIP_MSG_380:
    case SIP_MSG_400:
    case SIP_MSG_401:
    case SIP_MSG_402:
    case SIP_MSG_403:
    case SIP_MSG_404:
    case SIP_MSG_405:
    case SIP_MSG_406:
    case SIP_MSG_407:
    case SIP_MSG_408:
    case SIP_MSG_410:
    case SIP_MSG_413:
    case SIP_MSG_414:
    case SIP_MSG_415:
    case SIP_MSG_416:
    case SIP_MSG_420:
    case SIP_MSG_421:
    case SIP_MSG_423:
    case SIP_MSG_480:
    case SIP_MSG_481:
    case SIP_MSG_482:
    case SIP_MSG_483:
    case SIP_MSG_484:
    case SIP_MSG_485:
    case SIP_MSG_486:
    case SIP_MSG_487:
    case SIP_MSG_488:
    case SIP_MSG_491:
    case SIP_MSG_493:
    case SIP_MSG_500:
    case SIP_MSG_501:
    case SIP_MSG_502:
    case SIP_MSG_503:
    case SIP_MSG_504:
    case SIP_MSG_505:
    case SIP_MSG_513:
    case SIP_MSG_600:
    case SIP_MSG_603:
    case SIP_MSG_604:
    case SIP_MSG_606:
        return PROCEEDING_Handle3456xx; 
    case SIP_MSG_CANCEL:
        return PROCEEDING_HandleCancel;
    case SIP_TIMER_T1: 
        return PROCEEDING_HandleTimeout;
    default :
        return ICT_UnExpectedMsg;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles ACK in ICT Proceeding state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
COMPLETED_HandleACK(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
        SIP_ERROR(("COMPLETED_HandleACK:: Received ACK from remote \n"));
    }
    else
    {
        SIP_DEBUG(("COMPLETED_HandleACK:: Received ACK from app \n"));
        
        /* If we receive ack go to terminated state */
        ctxt->fsmState = SIP_ICT_TERMINATED;

        /* Send to remote */
        ret = SIP_SendEventToNet(ctxt);
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles 3456xx in ICT complted state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
COMPLETED_Handle3456xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    SIP_EVENT *sipEvt = NULL;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_DEBUG(("COMPLETED_Handle3456xx:: Received 3456xx from remote \n"));
        sipEvt = ITS_Malloc(sizeof(SIP_EVENT));
        sipEvt->type = SIP_DATA_EVENT;
        sipEvt->msg = (void *)msg;

        SIP_SendEventToApp(sipEvt);
        /*Not yet received ack from app */
    }
    else
    {
        SIP_ERROR(("COMPLETED_Handle3456xx:: Received 3456xx from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles time out in ICT completed state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
COMPLETED_HandleTimeout(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;

    SIP_DEBUG(("COMPLETED_HandleTimeout:: received \n"));

    /* didn't received ACK from application,purge tr, send timeout indication */
    ret = SIP_SendTimeoutToApp(ctxt, SIP_NO_RESPONSE_FROM_APP);
    
    ctxt->purge = ITS_TRUE;

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles 200 ok in ICT completed state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
COMPLETED_Handle2xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    SIP_DEBUG(("COMPLETED_Handle2xx::received, must be transmission igone \n"));
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in ICT Completed state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static SIP_TransactionHandler
ICT_GetMsgProcCompleted(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_MSG_200:
        return COMPLETED_Handle2xx;
    case SIP_MSG_300:
    case SIP_MSG_301:
    case SIP_MSG_302:
    case SIP_MSG_305:
    case SIP_MSG_380:
    case SIP_MSG_400:
    case SIP_MSG_401:
    case SIP_MSG_402:
    case SIP_MSG_403:
    case SIP_MSG_404:
    case SIP_MSG_405:
    case SIP_MSG_406:
    case SIP_MSG_407:
    case SIP_MSG_408:
    case SIP_MSG_410:
    case SIP_MSG_413:
    case SIP_MSG_414:
    case SIP_MSG_415:
    case SIP_MSG_416:
    case SIP_MSG_420:
    case SIP_MSG_421:
    case SIP_MSG_423:
    case SIP_MSG_480:
    case SIP_MSG_481:
    case SIP_MSG_482:
    case SIP_MSG_483:
    case SIP_MSG_484:
    case SIP_MSG_485:
    case SIP_MSG_486:
    case SIP_MSG_487:
    case SIP_MSG_488:
    case SIP_MSG_491:
    case SIP_MSG_493:
    case SIP_MSG_500:
    case SIP_MSG_501:
    case SIP_MSG_502:
    case SIP_MSG_503:
    case SIP_MSG_504:
    case SIP_MSG_505:
    case SIP_MSG_513:
    case SIP_MSG_600:
    case SIP_MSG_603:
    case SIP_MSG_604:
    case SIP_MSG_606:
        return COMPLETED_Handle3456xx; 
    case SIP_TIMER_T1:
        return COMPLETED_HandleTimeout;
    case SIP_MSG_ACK:
        return COMPLETED_HandleACK;
    default :
        return ICT_UnExpectedMsg;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles time out in ICT terminated state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
TERMINATED_HandleTimeout(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg,
                         ITS_USHORT src)
{
    int ret = 0;
    SIP_DEBUG(("TERMINATED_HandleTimeout:: received \n"));

    ctxt->purge = ITS_TRUE;

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles 2345xxx in ICT terminated state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
TERMINATED_Handle2345xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg,
                         ITS_USHORT src)
{
    SIP_DEBUG(("TERMINATED_2345xx:: received \n"));
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in ICT Terminated state
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static SIP_TransactionHandler 
ICT_GetMsgProcTerminated(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_TIMER_T1:
        return TERMINATED_HandleTimeout; 
    case SIP_MSG_200:
        return  TERMINATED_Handle2345xx;
    default :
        return ICT_UnExpectedMsg;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      FSM load function to ict transaction layer
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static SIP_TransactionHandler 
ICT_GetMsgProc(SIP_FSM_STATE state, SIP_MSG_TYPE msg)
{
    switch(state)
    {
    case SIP_IDLE:
        return ICT_GetMsgProcIdle(msg);

    case SIP_ICT_CALLING:
         return ICT_GetMsgProcCalling(msg);

    case SIP_ICT_PROCEEDING:
        return ICT_GetMsgProcProceeding(msg);
    
    case SIP_ICT_COMPLETED:
        return ICT_GetMsgProcCompleted(msg);

    case SIP_ICT_TERMINATED:
        return ICT_GetMsgProcTerminated(msg);

    default :
        SIP_ERROR(("SIP_ICTGetMsgProc:: Error, invalied fsm state \n"));
    }
    
    return ICT_UnExpectedMsg;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      FSM load function to ict transaction layer
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int 
SIP_ICTLoadFsm()
{
    SIP_FSM_STATE state = 0;
    SIP_MSG_TYPE msg = 0;

    SIP_DEBUG(("SIP_ICTLoadFsm:: loading \n"));

    for (state =0 ; state < ICT_MAX_FSM_STATES; ++state)
    {
        for (msg =0; msg < SIP_MAX_MSGS; ++msg)
        {
            ICT_mapTable[state][msg].transProc  =  ICT_GetMsgProc(state, msg);
        }
    }
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This is sip entry function to ict transaction layer
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int 
SIP_ICTEntry(SIP_TRANSACTION_CTXT *ctxt,
                 SIP_MSG_TYPE type,
                 SIP_MSG *msg, ITS_USHORT src)
{
    int ret;

    SIP_DEBUG(("SIP_ICTEntry:: Entry -----\n"));

    if (ctxt->fsmState > ICT_MAX_FSM_STATES || type > SIP_MAX_MSGS)
    {
        ret = SIP_TRANSACTION_INVALID_MSG;
    }

    ret = (ICT_mapTable[ctxt->fsmState][type].transProc)(ctxt, msg, src);

    SIP_DEBUG(("SIP_ICTEntry:: Exit -----\n"));
    return ret;
}
