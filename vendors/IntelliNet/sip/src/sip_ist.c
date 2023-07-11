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
 *  ID: $Id: sip_ist.c,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
 *
 *  $Log: sip_ist.c,v $
 *  Revision 9.1  2005/03/23 12:54:27  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.13  2005/03/21 13:53:25  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.12.2.3  2005/03/09 07:06:04  mkrishna
 *  Bug fixing cycle
 *
 *  Revision 1.12.2.2  2005/02/07 14:11:19  mkrishna
 *  Modified for PRACK message.
 *
 *  Revision 1.12.2.1  2004/12/28 14:00:33  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.12  2004/07/19 14:37:39  sjaddu
 *  Removed bye hanlding in confirmed state.
 *
 *  Revision 1.11  2004/05/28 10:26:09  sjaddu
 *  Debug console support added & few bug fixes.
 *
 *  Revision 1.10  2004/05/16 08:47:46  sjaddu
 *  Added TCP support.
 *
 *  Revision 1.9  2004/05/05 13:05:16  akumar
 *  Small Correction.
 *
 *  Revision 1.8  2004/04/27 11:15:39  sjaddu
 *  Transport layer revamping, no more dumps.
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

#define IST_MAX_FSM_STATES   4

/* fsm for IST transactions */
static SIP_FSM_MAP_TABLE IST_mapTable[IST_MAX_FSM_STATES][SIP_MAX_MSGS];

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
IST_UnExpectedMsg(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    if (msg)
    {
        SIP_ERROR(("IST_UnExpectedMsg:: msg Id %d \n", msg->msgId));
    }
    else
    {
        SIP_ERROR(("IST_UnExpected time out  received \n"));
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
    SIP_EVENT *sipEvt = NULL;
    SIP_DEBUG((" Received Invite from  remote \n"));

    /* Send 100 trying immediately so there won't be any retrasmission */
    /* in case of reliable PRACK required, stop sending 100 trying */  
    if ((msg->require[0] != 0) && strcmp(msg->require, "100rel") == 0)
    {
        ctxt->isReliableResp = ITS_TRUE;
    }
    else
    {
        SIP_Send100TryingToNet(ctxt, msg);
        ctxt->isReliableResp = ITS_FALSE; /* Set flag for reliable response */
    } 

    /* Change the state to PROCEEDING */
    ctxt->fsmState = SIP_IST_PROCEEDING;

    sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
    sipEvt->type = SIP_DATA_EVENT;
    sipEvt->msg = (void*)msg;
    sipEvt->buf = NULL;

    /*start T1 * 64 timer */
    SIP_StartTimer(ctxt, SIP_TIMER_T1, SIP_configInfo.trnTimer);

    /* Send to app*/
    ret = SIP_SendEventToApp(sipEvt);

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
    SIP_EVENT *sipEvt = NULL;
    SIP_TRANSACTION_KEY key;
    SIP_TRANSACTION_CTXT *ctxt_invite = NULL;

    SIP_DEBUG((" Received Prack from  remote \n"));

    if (msg->cseq.number != msg->rack.cseqNum)
    {
        /* get cseq no from rack, and find the invite trn */
        SIP_TransactionKeyFromMsg(msg, &key);
        key.cSeq.number = msg->rack.cseqNum;
        ctxt_invite = SIP_FindTransactionCtxt(&key, &ret);

        /* put the RAck details in prack ctxt. will be used if time out 
           happend while sending 200 OK for PRACK */ 
        strcpy(ctxt->callId.number, msg->callId.number);
        strcpy(ctxt->callId.host, msg->callId.host);
        strcpy(ctxt->cSeq.method, msg->cseq.method); 
        ctxt->rack.cseqNum = msg->rack.cseqNum;

        if (ctxt_invite != NULL)
        {
            SIP_DEBUG(("IDLE_HandlePrack:: invite context found \n"));
            SIP_StopTimer(ctxt_invite);

            /*start T1 * 64 timer */
            SIP_StartTimer(ctxt, SIP_TIMER_T1, SIP_configInfo.trnTimer);

            sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
            sipEvt->type = SIP_DATA_EVENT;
            sipEvt->msg = (void*)msg;
            sipEvt->buf = NULL;

            /* Change the state to PROCEEDING */
            ctxt->fsmState = SIP_IST_PROCEEDING;

            /* Send to app*/
            ret = SIP_SendEventToApp(sipEvt);
        }
        else
        {
            SIP_ERROR(("IDLE_HandlePrack:: invite context not found \n"));
            SIP_Send481ResponseToNet(ctxt, msg);
            ctxt->purge  = ITS_TRUE;
            return SIP_TRANSACTION_UNEXPECTED_MSG;
        }
        SIP_CommitTransactionCtxt(ctxt_invite);
    }
    else
    {
        SIP_DEBUG(("IDLE_HandlePrack:: Received Prack from remote \n"));
        ctxt->purge  = ITS_TRUE;
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in IST idle state
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
IST_GetMsgProcIdle(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_MSG_INVITE:
        return IDLE_HandleInvite;
    case SIP_MSG_PRACK:
        return IDLE_HandlePrack;
   
    default :
        return IST_UnExpectedMsg;
    }
}

/*
 *   PROCEEDING    PROCEEDING    PROCEEDING    PROCEEDING    PROCEEDING 
 */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles 1xx in IST Proceeding state
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
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_ERROR(("PROCEEDING_Handle1xx:: Received 1xx from remote \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    else
    {
        SIP_DEBUG(("PROCEEDING_Handle1xx:: Received 1xx from app \n"));
        
        /* first check is it reliable response */ 
        if (ctxt->isReliableResp)
        {
            if(msg->rseq != 0)
            { 
                /* we allow one reliable provisional response at a time */
                if (ctxt->lastRes == 0)
                {
                    ctxt->lastRes = msg->msgId;
                }
                else
                {
                    SIP_WARNING(("PROCEEDING_Handle1xx:: Already one response" 
                                 " is in progress \n"));
                    SIP_SendIndicationToApp(SIP_WAIT_FOR_PRACK_IND,
                                            &msg->callId, &msg->cseq, 
                                            msg->msgId, ctxt->destInfo.ipAddr); 
                    return ret;
                } 
                SIP_StopTimer(ctxt);

                ret = SIP_StartTimer(ctxt, SIP_TIMER_T2, ctxt->reTranstimer);
                if (ret != ITS_SUCCESS)
                {
                    SIP_ERROR(("Failed to state timer G \n"));
                }

                ctxt->reTranstimer += ctxt->reTranstimer;
            }
            else   
            {
                /* Don't make isReliableResp = ITS_FALSE. still it is in 
                   reliable response state */ 
                SIP_ERROR(("PROCEEDING_Handle1xx:: Received 1xx from app"
                           " without mandatory headers\n"));
                return SIP_MISSING_RSEQ_HDR_IND; 
            } 
        }

        /* Send to remote */
        ret = SIP_SendEventToNet(ctxt);
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles 2xx in IST Proceeding state
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
    SIP_TRANSACTION_KEY key;
    SIP_TRANSACTION_CTXT *ctxt_invite = NULL;

    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_ERROR(("PROCEEDING_Handle2xx:: Received 2xx from remote \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    else
    {
        SIP_DEBUG(("PROCEEDING_Handle2xx:: Received 2xx from app \n"));

        /*go to completed state & start timer G */
        if (strcmp(msg->cseq.method, "PRACK") != 0)
        {
            /* we should not allow 200 OK (final response) until reliable
               provisional responses acknowledged */
            if (ctxt->lastRes != 0)
            {
                SIP_WARNING(("PROCEEDING_Handle2xx:: waiting for reliable"
                             " provisional resp acknowledment \n"));
                SIP_SendIndicationToApp(SIP_WAIT_FOR_PRACK_IND,
                                        &msg->callId, &msg->cseq,
                                        msg->msgId, ctxt->destInfo.ipAddr);
                return SIP_TRANSACTION_UNEXPECTED_MSG;
            }

            SIP_StopTimer(ctxt);

            ctxt->fsmState = SIP_IST_COMPLETED;

            ret = SIP_StartTimer(ctxt, SIP_TIMER_T1, ctxt->reTranstimer);
            if (ret != ITS_SUCCESS)
            {
                SIP_ERROR(("Failed to state timer G \n"));
            }
        
            ctxt->reTranstimer += ctxt->reTranstimer;
        }
        else
        {
            /* change to completed state */
            ctxt->fsmState = SIP_IST_COMPLETED;

            /* fill up key with prack ctxt info */
            strcpy(key.callId.number, ctxt->callId.number);
            strcpy(key.callId.host, ctxt->callId.host);
            strcpy(key.cSeq.method, ctxt->cSeq.method);
            key.cSeq.number = ctxt->rack.cseqNum;           
            
            ctxt_invite = SIP_FindTransactionCtxt(&key, &ret); 
            if (ctxt_invite != NULL)
            {
                SIP_StartTimer(ctxt_invite, SIP_TIMER_T1,              
                               SIP_configInfo.trnTimer);
            } 
            else
            {
                SIP_ERROR(("PROCEEDING_Handle2xx::invite context not found\n"));
                return SIP_TRANSACTION_UNEXPECTED_MSG;
            } 
            SIP_CommitTransactionCtxt(ctxt_invite);

            /* once 200 OK for PRACK sent, make lastRes = 0. Hence another 
               reliable response can be processed */  
            ctxt_invite->lastRes = 0;
        }

        /* Send to remote */
        ret = SIP_SendEventToNet(ctxt);
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles 3456xx in IST Proceeding state
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
        SIP_DEBUG(("PROCEEDING_Handle3456xx:: Received 3456xx from remote \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    else
    {
        SIP_DEBUG(("PROCEEDING_Handle3456xx:: Received 3456xx from app \n"));

        /* stop the tr timer running */
        SIP_StopTimer(ctxt);

        /*go to completed state & start timer G */
        if (strcmp(msg->cseq.method, "CANCEL") != 0)
        {
            ctxt->fsmState = SIP_IST_COMPLETED;
            ret = SIP_StartTimer(ctxt, SIP_TIMER_T1, ctxt->reTranstimer);
            if (ret != ITS_SUCCESS)
            {
                SIP_ERROR(("Failed to state timer G \n"));
            }

            ctxt->reTranstimer += ctxt->reTranstimer;
        }
        else
        {
            /* Jump to confirmed, we don't expect ack here */
            ctxt->fsmState = SIP_IST_CONFIRMED;

            /* Then start timer I */
            SIP_StartTimer(ctxt, SIP_TIMER_T1, SIP_configInfo.trnTimer);
            if (ret != ITS_SUCCESS)
            {
                SIP_ERROR(("Failed to start timer, terminating transaction\n")); 
                ctxt->purge  = ITS_TRUE;
                return ret;
            }
        }

        /* Send to remote */
        ret = SIP_SendEventToNet(ctxt);
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles Invite in IST Proceeding state
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
PROCEEDING_HandleInvite(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_DEBUG(("PROCEEDING_HandleInvite:: Received Invite from remote \n"));

        /* Send 100 trying immediately so there won't be any retrasmission */
        if (msg->require[0] == 0)
        { 
            SIP_Send100TryingToNet(ctxt, msg);
        }

        /* No state change of state here */
    }
    else
    {
        SIP_DEBUG(("PROCEEDING_HandleInvite:: Received Invite from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles Prack in IST Proceeding state
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
PROCEEDING_HandlePrack(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src
)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_DEBUG(("PROCEEDING_HandlePrack:: Received Prack from remote \n"));

        /* No state change of state here */
    }
    else
    {
        SIP_DEBUG(("PROCEEDING_HandlePrack:: Received Prack from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles CANCEL in IST Proceeding state
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
        SIP_EVENT *sipEvt = NULL;
        SIP_DEBUG(("PROCEEDING_HandleCancel:: Received Cancel from net \n"));

        /* stop invite timer */
        SIP_StopTimer(ctxt); 

        /* No state change here, copy the headers of cancel req */
        SIP_CopyHeadersToCtxt(msg, ctxt);
        
        sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
        sipEvt->type = SIP_DATA_EVENT;
        sipEvt->msg = (void*)msg;
        sipEvt->buf = NULL;
        memcpy(&SIP_GET_DEST_INFO(sipEvt), &ctxt->destInfo,
               sizeof(SIP_DEST_INFO)); 
        /* Send error response */
        ret = SIP_SendErrorResponseToNet(sipEvt, msg, SIP_RESPONSE_MSG_IND); 
        if (ret != ITS_SUCCESS)
        {
            SIP_ERROR(("SIP_HandleMsg:: Error in sending response"
                       " to network, errCode=%d\n", ret));
        }
        /* Send to app*/
        SIP_SendEventToApp(sipEvt);
        ctxt->purge = ITS_TRUE;
    }
    else
    {
        SIP_DEBUG(("PROCEEDING_HandleCancel:: Received Cancel from app \n"));
        /* Send to remote */
        ret = SIP_SendEventToNet(ctxt);
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles time out
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
PROCEEDING_HandleTimeout(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg,
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
        ctxt_invite->purge  = ITS_TRUE;
    }
    else
    {
        SIP_ERROR(("PROCEEDING_HandleTimeout:: invite context not found \n"));
    }
     
    /* didn't received resp from application,purge tr,send timeout indication */
    ret = SIP_SendTimeoutToApp(ctxt, SIP_NO_RESPONSE_FROM_APP);

    ctxt->purge = ITS_TRUE;

    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles time out for reliable provisional response
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
PROCEEDING_HandleRelProvRespTimeout(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg,
                                    ITS_USHORT src)
{
    int ret = 0;

    if (ctxt->reTranstimer < SIP_configInfo.trnTimer)
    {
        SIP_DEBUG(("PROCEEDING_HandleRelProvRespTimeout:: time out G \n"));

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
        SIP_WARNING(("PROCEEDING_HandleRelProvRespTimeout:: Max retransmissions"
                     " reached deleting the entry \n"));
        SIP_Send504ResponseToNet(ctxt, ctxt->sipMsg);
        /* This is time  out H*/
        ret = SIP_SendTimeoutToApp(ctxt, SIP_NO_RESPONSE_FROM_NET);
        ctxt->purge = ITS_TRUE;
    }
    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in IST Proceeding state
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
IST_GetMsgProcProceeding(SIP_MSG_TYPE msg)
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
    case SIP_MSG_INVITE:
        return PROCEEDING_HandleInvite; 
    case SIP_MSG_CANCEL:
        return PROCEEDING_HandleCancel; 
    case SIP_TIMER_T1:
        return PROCEEDING_HandleTimeout;
    case SIP_TIMER_T2:
        return PROCEEDING_HandleRelProvRespTimeout;
    case SIP_MSG_PRACK:
        return PROCEEDING_HandlePrack;
    default :
        return IST_UnExpectedMsg;
        
    }
}

/*
 *  COMPLETED   COMPLETED   COMPLETED   COMPLETED   COMPLETED   COMPLETED
 */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles Invite in IST Proceeding state
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
COMPLETED_HandleInvite(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_DEBUG(("COMPLETED_HandleInvite:: Received Invite from remote \n"));

        /* Send to remote, retransmit last resp */
        ret = SIP_SendEventToNet(ctxt);
        /* No state change here */
    }
    else
    {
        SIP_ERROR(("COMPLETED_HandleInvite:: Received Invite from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles Prack in IST Proceeding state
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
COMPLETED_HandlePrack(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_DEBUG(("COMPLETED_HandlePrack:: Received Prack from remote \n"));

        /* No state change here */
    }
    else
    {
        /* Send to remote */
        ret = SIP_SendEventToNet(ctxt); 

        SIP_ERROR(("COMPLETED_HandlePrack:: Received Prack from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }

    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles time out in IST Proceeding state
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
    
    if (ctxt->reTranstimer < SIP_configInfo.trnTimer)
    {
        SIP_DEBUG(("COMPLETED_HandleTimeout:: time out G \n"));

        /* This is time out G*/
        if (ctxt->reTranstimer < SIP_configInfo.T2)
        {
            SIP_StartTimer(ctxt, SIP_TIMER_T1, ctxt->reTranstimer);
        }
        else
        {
            SIP_StartTimer(ctxt, SIP_TIMER_T1, SIP_configInfo.T2);
        }

        ctxt->reTranstimer +=  ctxt->reTranstimer;

        /* retransmit response to remote */
        ret = SIP_SendEventToNet(ctxt);
    }
    else
    {
        SIP_WARNING(("COMPLETED_HandleTimeout:: Max retransmissions reached"
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
 *      Handles ACK in IST Proceeding state
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
        SIP_EVENT *sipEvt = NULL;
        SIP_DEBUG(("COMPLETED_HandleACK:: Received ACK from remote \n"));
        
        /* stop if any timer is running */
        ret = SIP_StopTimer(ctxt);
        if (ret != ITS_SUCCESS)
        {
            SIP_ERROR(("Fialed stop timer G \n"));
        }

        ctxt->fsmState = SIP_IST_CONFIRMED;

        /* Then start timer I */
        ret = SIP_StartTimer(ctxt, SIP_TIMER_T1, 
                        SIP_configInfo.trnTimer - ctxt->reTranstimer);
        if (ret != ITS_SUCCESS)
        {
            ctxt->purge = ITS_TRUE;
            SIP_ERROR(("Failed to start timer I \n"));
        }


        sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
        sipEvt->type = SIP_DATA_EVENT;
        sipEvt->msg = (void*)msg;
        sipEvt->buf = NULL;
        
        ret = SIP_SendEventToApp(sipEvt);

    }
    else
    {
        SIP_ERROR(("COMPLETED_HandleACK:: Received ACK from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    return ret;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in IST Completed state
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
IST_GetMsgProcCompleted(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_TIMER_T1:
        return COMPLETED_HandleTimeout;
    case SIP_MSG_INVITE:
        return COMPLETED_HandleInvite;
    case SIP_MSG_PRACK:
        return COMPLETED_HandlePrack; 
    case SIP_MSG_ACK:
        return COMPLETED_HandleACK;
    default :
        return IST_UnExpectedMsg;
    }
}

/*
 *  CONFIRMED CONFIRMED CONFIRMED CONFIRMED CONFIRMED
 */ 
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles CANCEL in IST CONFIRMED state
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
CONFIRMED_HandleCancel(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg,
                        ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_DEBUG(("CONFIRMED_HandleCancel:: Received Cancel from net \n"));
        
        /* must be retransmission send last response */
        ret = SIP_SendEventToNet(ctxt);
    }
    else
    {
        SIP_ERROR(("CONFIRMED_HandleCancel:: Received Cancel from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handles Tim out msg in confirmed state
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
CONFIRMED_HandleTimeout(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;

    SIP_DEBUG(("CONFIRMED_HandleTimeout:: Received Timeout I \n"));

    /* Means end of transaction */
    ctxt->purge = ITS_TRUE;
    
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handles ack  msg in confirmed  state
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
CONFIRMED_HandleACK(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;

    SIP_DEBUG(("CONFIRMED_HandleACK:: Received ACK \n"));

    /*Just ignore it and continue to wait for timer H expiry */
    
    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in IST Calling  state
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
IST_GetMsgProcConfirmed(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_MSG_ACK:
        return CONFIRMED_HandleACK;
    case SIP_TIMER_T1:
        return CONFIRMED_HandleTimeout; 
    case SIP_MSG_CANCEL:
        return CONFIRMED_HandleCancel;
    default :
        return IST_UnExpectedMsg;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in IST Terminated state
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
IST_GetMsgProcTerminated(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_MSG_INVITE:
    case SIP_MSG_PRACK:
    default :
        return IST_UnExpectedMsg;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      FSM load function to ist transaction layer
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
IST_GetMsgProc(SIP_FSM_STATE state, SIP_MSG_TYPE msg)
{
    switch(state)
    {
    case SIP_IDLE:
        return IST_GetMsgProcIdle(msg);
        break;

    case SIP_IST_PROCEEDING:
        return IST_GetMsgProcProceeding(msg);
        break;
    
    case SIP_IST_COMPLETED:
        return IST_GetMsgProcCompleted(msg);
        break;

    case SIP_IST_CONFIRMED:
         return IST_GetMsgProcConfirmed(msg);
         break;

    case SIP_IST_TERMINATED:
        return IST_GetMsgProcTerminated(msg);
        break;

    default :
        SIP_ERROR(("SIP_ISTGetMsgProc:: Error, invalied fsm state \n"));
    }
    
    return IST_UnExpectedMsg;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      FSM load function to ist transaction layer
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
SIP_ISTLoadFsm()
{
    SIP_FSM_STATE state = 0;
    SIP_MSG_TYPE msg = 0;

    SIP_DEBUG(("SIP_ISTLoadFsm:: loading \n"));

    for (state =0 ; state < IST_MAX_FSM_STATES; ++state)
    {
        for (msg =0; msg < SIP_MAX_MSGS; ++msg)
        {
            IST_mapTable[state][msg].transProc  =  IST_GetMsgProc(state, msg);
        }
    }
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This is sip entry function to ist transaction layer
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
SIP_ISTEntry(SIP_TRANSACTION_CTXT *ctxt,
                 SIP_MSG_TYPE type,
                 SIP_MSG *msg, ITS_USHORT src)
{
    int ret;
    SIP_DEBUG(("SIP_ISTEntry:: Entry func \n"));

    if (ctxt->fsmState > IST_MAX_FSM_STATES || type > SIP_MAX_MSGS)
    {
        return SIP_TRANSACTION_INVALID_MSG;
    }
        
    ret = (IST_mapTable[ctxt->fsmState][type].transProc)(ctxt, msg, src);

    SIP_DEBUG(("SIP_ISTEntry:: Exiting func \n"));

    return ret;
}
