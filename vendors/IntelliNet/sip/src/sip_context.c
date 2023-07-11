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
 *  ID: $Id: sip_context.c,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
 *
 *  $Log: sip_context.c,v $
 *  Revision 9.1  2005/03/23 12:54:27  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.21  2005/03/21 13:53:24  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.20.2.3  2005/03/09 07:00:01  mkrishna
 *  Bug fixing cycle
 *
 *  Revision 1.20.2.2  2005/02/07 14:04:44  mkrishna
 *  Modified for PRACK message.
 *
 *  Revision 1.20.2.1  2004/12/28 14:00:33  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.20  2004/07/19 14:40:32  sjaddu
 *  Changed shared to normal timers, giving some problem in load.
 *
 *  Revision 1.19  2004/06/28 07:33:13  sjaddu
 *  Bug fixes during load, SIP_Stackhandle is also added.
 *
 *  Revision 1.18  2004/06/24 06:00:44  akumar
 *  Minor Bug Fix.
 *
 *  Revision 1.17  2004/05/28 10:26:08  sjaddu
 *  Debug console support added & few bug fixes.
 *
 *  Revision 1.16  2004/05/16 08:47:46  sjaddu
 *  Added TCP support.
 *
 *  Revision 1.15  2004/05/06 05:43:41  akumar
 *  Bug fix.
 *
 *  Revision 1.14  2004/05/05 13:07:57  akumar
 *  Little modification.
 *
 *  Revision 1.13  2004/05/03 07:14:58  akumar
 *  Bug fix.
 *
 *  Revision 1.12  2004/04/29 09:54:58  akumar
 *  Added 400 Bad Req handling.
 *
 *  Revision 1.11  2004/04/27 11:15:39  sjaddu
 *  Transport layer revamping, no more dumps.
 *
 *  Revision 1.10  2004/04/23 13:19:44  sjaddu
 *  Testing going on.
 *
 *  Revision 1.9  2004/04/22 11:38:46  akumar
 *  Some modifications after testing.
 *
 *  Revision 1.8  2004/04/21 06:45:04  sjaddu
 *  Fixed some bugs.
 *
 *  Revision 1.7  2004/04/15 12:16:15  sjaddu
 *  Added indications & state machine revamping.
 *
 *  Revision 1.6  2004/04/08 13:39:48  akumar
 *  Modified as per SIP_MSG struct.
 *
 *  Revision 1.5  2004/04/05 07:47:24  sjaddu
 *  More testing, one complete call works fine.
 *
 *  Revision 1.4  2004/04/01 09:21:07  akumar
 *  FT going on.
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
#include <sip_intern.h>
#include <sip_defines.h>
#include <sip.h>

#include <ctype.h>

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The SIP stack has received a msg from the transport or the
 *      application. It will perform the common job, before forwarding
 *      the msg to the appropriate module.
 *
 *  Input Parameters:
 *      event - pointer to the SIP event we just received. Event will have
 *      src - the source of the event TRANS or APP).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS.
 *
 ****************************************************************************/
ITSDLLAPI int 
SIP_HandleMsg(ITS_EVENT* event, ITS_USHORT src)
{
    int ret  =0;
    SIP_TRANSACTION_CTXT *ctxt = NULL;
    SIP_EVENT *sipEvt = SIP_GET_SIPEVENT(event);
    SIP_MSG *msg = NULL;
    SIP_TRANSACTION_KEY key;

    SIP_GET_SIPEVENT(event) = 0;

    if (src ==  ITS_SIP_TRANSPORT_SRC)
    {
        SIP_DEBUG(("SIP_HandleMsgNetWork ::Received data :\n\n%s",
                sipEvt->buf));

        /*First decode the msg */
        ret = SIP_Parse(&msg, sipEvt->buf);
        if (ret == ITS_SUCCESS || ret == SIP_PARSE_HDR_CALLID_ERR ||
            ret == SIP_PARSE_HDR_CSEQ_ERR ||
            ret == SIP_PARSE_MSG_MISSINGCALLID_ERR ||
            ret == SIP_PARSE_MSG_MISSINGCSEQ_ERR)
        {
            /* parse success or partial success */
            ret = SIP_HandleMsgFromTransport(sipEvt, msg, ret);
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }
        }
        else
        {
            /* Parsing fail */
            SIP_ERROR(("SIP_HandleMsg:: Parsing fail, for msg received" 
                       " from network, errCode=%d\n", ret));
            ret = SIP_SendErrorResponseToNet(sipEvt, NULL, ret);
            if (ret != ITS_SUCCESS)
            {
                SIP_ERROR(("SIP_HandleMsg:: Error in sending response"
                           " to network, errCode=%d\n", ret));
            }
            ITS_Free(sipEvt->buf);
            return ret;
        }
        ITS_Free(sipEvt->buf);
    }
    else
    {
        msg = (SIP_MSG*)SIP_GET_MSG_INFO(sipEvt);
        SIP_DEBUG(("SIP_HandleMsgFromApp ::Received data :\n\n%s",
                sipEvt->buf));
    }

    /*No memory allocated here for key, so don't touch it */
    SIP_TransactionKeyFromMsg(msg, &key);

    ctxt = SIP_FindTransactionCtxt(&key, &ret);
    while (ret == ITS_EINUSE)
    {
        /* sleep for some time */
        TIMERS_USleep(100);

        /* do a find again */
        ctxt = SIP_FindTransactionCtxt(&key, &ret);
    }

    if (ret == ITS_ENOTFOUND)
    {
        SIP_DEBUG(("Could not find the tr ctxt for msg Id %d\n", msg->msgId));

        /*Now see what msg type if its any of the msg create new tr */
        switch (msg->msgId)
        {
        case SIP_MSG_INVITE:
        case SIP_MSG_REGISTER:
        case SIP_MSG_BYE:
        case SIP_MSG_OPTIONS:
        case SIP_MSG_PRACK:
        case SIP_MSG_NOTIFY:
            ctxt = SIP_CreateTransactionCtxt(msg, &ret);
            if (ret != ITS_SUCCESS)
            {
                SIP_ERROR(("Failed to create transaction ret = %d \n", ret));
                SIP_MsgFree(msg);
                SIP_EVENT_TERM(sipEvt);
                return ret;
            }
            ctxt->sipTransaction = SIP_GetTransactionType(msg, src);
            ctxt->entryFunc = SIP_GetTransactionEntryFunc(ctxt->sipTransaction);
            break;
        default:
            SIP_ERROR(("HandleMsg:: Unexpected msg received Id %d\n",
                        msg->msgId));
            /* Send Indication to app */
            SIP_SendIndicationToApp(SIP_NO_TRANSACTION_FOR_MSG_IND, 
                                    &msg->callId, &msg->cseq, msg->msgId, 
                                    SIP_GET_DEST_INFO(sipEvt).ipAddr);

            ret = SIP_SendErrorResponseToNet(sipEvt, msg, 
                                             SIP_NO_TRANSACTION_FOR_MSG_IND);
            if (ret != ITS_SUCCESS)
            {
                SIP_ERROR(("SIP_HandleMsg:: Error in sending response"
                           " to network, errCode=%d\n", ret));
            }
            SIP_MsgFree(msg);
            SIP_EVENT_TERM(sipEvt);
            return ret;
        }
    }

    if (ctxt == NULL)
    {
        SIP_ERROR(("We are in trouble failed find/create transaction"
                    "ret =  %d \n", ret));
        SIP_MsgFree(msg);
        SIP_EVENT_TERM(sipEvt);
        return ret;
    }

    /* here we are, so populate ctxt with dest and required info */ 
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        /*Do specific stuff here, for incomming transactions */

        /* get dest info also */
        memcpy(&ctxt->destInfo, &SIP_GET_DEST_INFO(sipEvt),
               sizeof(SIP_DEST_INFO));
    }
    else
    {
        /*Do specific stuff here, for outbound transactions */

        /* This check is required to prevent for any incoming msg
           if already one reliable provisional response is waiting for PRACK.
           for example 180 is waiting for PRACK and 200 OK (final response)  
           has come */
                
        if (ctxt->lastRes == 0)  
        { 
            /*store encoded buf into the ctxt */
            if (ctxt->msgBuf != NULL)
            {
                /* So this must be the previous req/resp */
                ITS_Free(ctxt->msgBuf);
            }
            ctxt->msgBuf = SIP_GET_MSG_BUF(sipEvt);

            if (ctxt->sipMsg != NULL)
            {
                /* So this must be the previous req/resp msg */ 
                SIP_MsgFree(ctxt->sipMsg);
            } 
            ctxt->sipMsg = msg;
        }      

        switch (msg->msgId)
        {
        case SIP_MSG_INVITE:
        case SIP_MSG_REGISTER:
        case SIP_MSG_BYE:
        case SIP_MSG_OPTIONS:
        case SIP_MSG_PRACK:
        case SIP_MSG_NOTIFY:
            /* get dest info also */
            memcpy(&ctxt->destInfo, &SIP_GET_DEST_INFO(sipEvt),
                   sizeof(SIP_DEST_INFO));

            /* Get local transport also, it returns index */
            ret = SIP_GetLocalTransportForCall(ctxt, msg);
            if (ret < ITS_SUCCESS)
            {
                SIP_ERROR(("Could not get Transport , Drop the request \n"));

               /* Don't free here. we done it in SIP_FreeTransaction function
                  in sip_transaction.c
                SIP_MsgFree(msg); */

                SIP_EVENT_TERM(sipEvt);

                /* Delete this transaction */
                SIP_DeleteTransactionCtxt(ctxt);

                return ITS_ENOTRANSPORT;
            }

            /* store index for future msgs */
            ctxt->destInfo.transIndex = ret;
        }
    }

    /* Then give the msg to FSM */
    ret = ctxt->entryFunc(ctxt, msg->msgId, msg, src);
    if (ret != ITS_SUCCESS)
    {
        SIP_SendTransactionErrorToApp(ctxt, ret);
        SIP_ERROR(("Transaction failed ret =  %d \n", ret));
        switch (msg->msgId)
        {
        case SIP_MSG_INVITE:
        case SIP_MSG_REGISTER:
        case SIP_MSG_BYE:
        case SIP_MSG_OPTIONS:
        case SIP_MSG_PRACK:
        case SIP_MSG_NOTIFY:
            SIP_TransportDelete(ctxt->destInfo.transIndex,
                                SIP_configInfo.transInfo);
        }
    }

    if (ctxt->purge)
    {
        /* Delete the transport */
        SIP_TransportDelete(ctxt->destInfo.transIndex,
                            SIP_configInfo.transInfo);

        /* Delete the transaction context */
        ret = SIP_DeleteTransactionCtxt(ctxt);
    }
    else    
    {
        /* Went well, Commit transaction */
        ret = SIP_CommitTransactionCtxt(ctxt);
    }

    SIP_EVENT_TERM(sipEvt);
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function will handle a timeout event received from the ITS.
 *
 *  Input Parameters:
 *      event: The event holding the timeout.
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS.
 ****************************************************************************/
ITSDLLAPI int 
SIP_HandleTimeOut(ITS_EVENT* event)
{
    SIP_TIMER_CTXT timerInfo;
    ITS_TimerData *timerData;
    SIP_TRANSACTION_CTXT *ctxt;
    int error =0;

    SIP_DEBUG(("SIP_HandleTimeOut::Received time out event \n"));

    timerData = (ITS_TimerData*)event->data;
    memcpy( (char *)&timerInfo, (char *)timerData->context,
            sizeof(SIP_TIMER_CTXT));

    /*Now find transaction from key*/
    ctxt = SIP_FindTransactionCtxt(&timerInfo.transKey, &error);         
    if (error == ITS_SUCCESS)
    {
        if (ctxt != NULL)
        {
            /*Set the time key to zero */
            ctxt->timerKey = 0;

            SIP_DEBUG(("SIP_HandleTimeOut:: Found tr ctxt from time out\n"));
            error = ctxt->entryFunc(ctxt, timerInfo.timerId, NULL, 
                                     ITS_TIMER_SRC);
            if (error != ITS_SUCCESS)
            {
                SIP_ERROR(("SIP_HandleTimeOut:: Failed to handle time out "
                           " timer Id %d  in fsm state  %d\n",
                            timerInfo.timerId, ctxt->fsmState)); 
            }
        }
    }
    else
    {
        SIP_ERROR(("SIP_HandleTimeOut:: Failed to handle time out "
                   " timer Id %d \n", timerInfo.timerId)); 
        return error;
    }
    
    if (ctxt->purge)
    {
        SIP_TransportDelete(ctxt->destInfo.transIndex,
                            SIP_configInfo.transInfo);
        error = SIP_DeleteTransactionCtxt(ctxt);
    }
    else    
    {
        /* Unlocking the row, this must follow after every Find */
        error = SIP_CommitTransactionCtxt(ctxt);
    }

    ITS_EVENT_TERM(event);
    return error;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function will start new timer and updates the ctxt with serial 
 *
 *  Input Parameters:
 *      ctxt -  transaction context
 *      timerId timer Id
 *      tVal    timer value always in milli seconds
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS.
 ****************************************************************************/
ITSDLLAPI int 
SIP_StartTimer(SIP_TRANSACTION_CTXT *ctxt, ITS_OCTET timerId, ITS_UINT tVal)
{
    SIP_TIMER_CTXT timerInfo;
    int timeKey = 0;
    int secs = 0;

    if (ctxt == NULL || tVal == 0 )
    {
        ctxt->purge = ITS_TRUE;
        return ITS_EINVALIDARGS;
    }

    if (ctxt->timerKey != 0)
    {
        SIP_WARNING(("SIP_StartTimer:: Timer already running \n"));
        return ITS_EINVALIDARGS;
    }

    timerInfo.tranId = ctxt->tId;
    timerInfo.timerId = timerId;

    /* This is should be ok,timer never runs with out transaction*/
    timerInfo.transKey.callId =  ctxt->callId; 
    timerInfo.transKey.cSeq   =  ctxt->cSeq; 

    if ((secs = tVal/1000) != 0)
    { 
        timeKey = TIMERS_StartTimer(ITS_SIP_SRC, (int)secs, 
                                          (void*)&timerInfo, 
                                          sizeof(SIP_TIMER_CTXT));
    }
    else
    {
        timeKey = TIMERS_StartUTimer(ITS_SIP_SRC, (int)tVal * 1000,
                                          (void*)&timerInfo,
                                          sizeof(SIP_TIMER_CTXT));
    }

    if (timeKey == 0)
    {
        SIP_ERROR(("SIP_StartTimer: Failed start timerId %d \n", timerId));
        ctxt->purge = ITS_TRUE;
        return ITS_ETIMERSTARTFAIL;
    }

    SIP_DEBUG(("SIP_StartTimer:: Started timer Key = %d \n", timeKey));

    /*Update the ctxt with timer key */
    ctxt->timerKey = timeKey;

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function will start stop timer, for this ctxt
 *      and updates the ctxt. 
 *
 *  Input Parameters:
 *      event: The event holding the timeout.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS.
 ****************************************************************************/
ITSDLLAPI int 
SIP_StopTimer(SIP_TRANSACTION_CTXT *ctxt)
{
    int ret = ITS_SUCCESS;

    if (ctxt == NULL)
    {
        return ITS_EINVALIDARGS;
    }
    
    if (ctxt->timerKey == 0)
    {
        SIP_ERROR(("No timer is running for this transaction \n"));
        return ITS_EINVALIDARGS;
    }

    ret = TIMERS_CancelTimer(ctxt->timerKey);
    if (ret != ITS_SUCCESS)
    {
        SIP_ERROR(("SIP_StopTimer:: Failed key = %d \n", ctxt->timerKey));
    }
    else
    {
        SIP_DEBUG(("SIP_StopTimer:: Success for key %d \n", ctxt->timerKey));
    }

    /* set timerKer to 0*/
    ctxt->timerKey = 0;
    
    /* don't delete transaction key */

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      This function sends msg to network
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
SIP_SendEventToNet(SIP_TRANSACTION_CTXT *ctxt)
{
    int ret = 0;

    /*send event to network */
    ret = SIP_TransportSend(&ctxt->destInfo, ctxt->destInfo.transIndex,
                      ctxt->msgBuf, SIP_configInfo.transInfo);
    if (ret != ITS_SUCCESS)
    {
        SIP_EVENT *sipEvt = NULL;
        SIP_ERROR_DATA *errorData = NULL;
        SIP_TRANSPORT_ERROR_DATA *data = NULL;

        SIP_ERROR(("SIP_SendEventToNet:: transport error =  %d \n", ret));

        data = (SIP_TRANSPORT_ERROR_DATA *)
                            ITS_Malloc(sizeof(SIP_TRANSPORT_ERROR_DATA));
        data->errorCode = ret;
        data->localPort = ctxt->port;
        data->remotePort = ctxt->destInfo.portNo;

        errorData = (SIP_ERROR_DATA *) ITS_Malloc(sizeof(SIP_ERROR_DATA));
        errorData->type = SIP_TRANSPORT_ERROR;
        errorData->callId = ITS_Malloc(sizeof(SIP_CALLID_HDR));
        errorData->cseq = ITS_Malloc(sizeof(SIP_CSEQ_HDR));
        memcpy(errorData->callId, &ctxt->callId, sizeof(SIP_CALLID_HDR)); 
        memcpy(errorData->cseq, &ctxt->cSeq, sizeof(SIP_CSEQ_HDR)); 
        SOCK_IPv4AddrToName(errorData->remIpAddr, ctxt->destInfo.ipAddr);
        errorData->data =  (void*)data;

        sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
        sipEvt->type = SIP_ERROR_EVENT;
        sipEvt->msg  = (void*)errorData;

        SIP_SendEventToApp(sipEvt);
    }

    return ret;
}
 
/****************************************************************************
 *  Purpose:
 *      This function sends event to application
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
SIP_SendEventToApp(SIP_EVENT *sipEvt)
{
    int ret = 0;
    ITS_USHORT dest = 0;
    ITS_HDR header;
    ITS_EVENT evt;

    /* Setting the Header */
    memset((char*)&header, 0, sizeof(ITS_HDR));
    header.type = 0; /* just for now keep it like this */
    header.context.cic = 0;

    evt.src = ITS_SIP_SRC;
    evt.len = 0;
    evt.data =  (ITS_OCTET*) sipEvt;

    dest = ROUTE_SelectApplication(&header, &evt, ITS_TRUE);

    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        SIP_DEBUG(("Forward SIP msg to App thread \n"));

        ret = TRANSPORT_PutEvent(dest, &evt);
        if (ret != ITS_SUCCESS)
        {
            /* msg free, sipEvt free , its evt free */
            SIP_EVENT_TERM(sipEvt);
        }
    }
    else
    {
        SIP_ERROR(("Send failed to APP \n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      This function sends time out indication
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
SIP_SendTimeoutToApp(SIP_TRANSACTION_CTXT *ctxt, SIP_TIMEOUT_REASON reason)
{
    SIP_TIMEOUT_DATA *data;
    SIP_EVENT *sipEvt;

    data = ITS_Malloc(sizeof(SIP_TIMEOUT_DATA));

    data->reason = reason;
    memcpy(&data->callId, &ctxt->callId, sizeof(SIP_CALLID_HDR));
    memcpy(&data->cseq, &ctxt->cSeq, sizeof(SIP_CSEQ_HDR));
    SOCK_IPv4AddrToName(data->remIpAddr, ctxt->destInfo.ipAddr);

    sipEvt = ITS_Malloc(sizeof(SIP_EVENT));
    
    sipEvt->type = SIP_TIMEOUT_EVENT;
    sipEvt->msg  = (void *)data;
    sipEvt->buf  = NULL;

    return SIP_SendEventToApp(sipEvt);
}

/****************************************************************************
 *  Purpose:
 *      This function sends transaction error ind to app
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
SIP_SendTransactionErrorToApp(SIP_TRANSACTION_CTXT *ctxt, ITS_UINT reason)
{
    /* This is a transaction failure */
    SIP_TRANSACTION_ERROR_DATA *data;
    SIP_ERROR_DATA *errorData;
    SIP_EVENT *sipEvt = NULL;

    data = ITS_Malloc(sizeof(SIP_TRANSACTION_ERROR_DATA));
    data->reason = reason;

    errorData = ITS_Malloc(sizeof(SIP_ERROR_DATA));
    errorData->type = SIP_TRANSACTION_ERROR;
    errorData->callId = ITS_Malloc(sizeof(SIP_CALLID_HDR));
    memcpy(errorData->callId, &ctxt->callId, sizeof(SIP_CALLID_HDR));
    errorData->cseq = ITS_Malloc(sizeof(SIP_CSEQ_HDR));
    memcpy(errorData->cseq, &ctxt->cSeq, sizeof(SIP_CSEQ_HDR));
    SOCK_IPv4AddrToName(errorData->remIpAddr, ctxt->destInfo.ipAddr);
    errorData->data = (void *)data;

    sipEvt = ITS_Malloc(sizeof(SIP_EVENT));
    sipEvt->type = SIP_ERROR_EVENT;
    sipEvt->msg  = (void *)errorData;

    return SIP_SendEventToApp(sipEvt);
}
/****************************************************************************
 *  Purpose:
 *      This function sends transaction error indication to app
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
SIP_SendIndicationToApp(ITS_UINT reason, SIP_CALLID_HDR *callId, 
                        SIP_CSEQ_HDR *cseq, SIP_MSG_TYPE msgId,
                        SOCK_IPv4Addr remIPAddr)
{
    SIP_INDICATION_DATA *data;
    SIP_EVENT *sipEvt;

    data = ITS_Malloc(sizeof(SIP_INDICATION_DATA));

    data->reason = reason;

    if (callId)
        memcpy(&data->callId, callId, sizeof(SIP_CALLID_HDR));
    if (cseq)
        memcpy(&data->cseq, cseq, sizeof(SIP_CSEQ_HDR));
        
    data->msgId = msgId;

    SOCK_IPv4AddrToName(data->remIpAddr, remIPAddr);

    sipEvt = ITS_Malloc(sizeof(SIP_EVENT));
    
    sipEvt->type = SIP_INDICATION_EVENT;
    sipEvt->msg  = (void *)data;
    sipEvt->buf  = NULL;

    return SIP_SendEventToApp(sipEvt);
}
/****************************************************************************
 *  Purpose:
 *      This function builds the message for 100 trying
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
SIP_Send100TryingToNet(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg)
{
    SIP_MSG *trying;
    int ret = 0, pos = 0;
    ITS_CHAR * resp = "trying";
    ITS_CHAR *data = NULL;
    SIP_HOST_INFO fromHostInfo, toHostInfo, *host;
    SIP_URI_OBJ fromUri, toUri;
    ITS_CHAR *version, *protocol; 
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;


    SIP_InitMsg(&trying);

    /* start line must */
    SIP_SetStartLine(trying, msg->sipVersion, 100, resp, NULL, NULL);

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, msg->from.url.hostInfo.type,
                    msg->from.url.hostInfo.address,
                    msg->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, msg->from.url.scheme, msg->from.url.userName,
               msg->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(trying, &fromUri, msg->from.displayName, NULL,
                      msg->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetHostinfo(&toHostInfo, msg->to.url.hostInfo.type,
                    msg->to.url.hostInfo.address,
                    msg->to.url.hostInfo.port);
    SIP_SetUri(&toUri, msg->to.url.scheme, msg->to.url.userName,
               msg->to.url.password, &toHostInfo);
    SIP_SetToHeader(trying, &toUri, msg->to.displayName, NULL,
                      msg->to.numGenparams, NULL);

    /* Get Vias one by one and put in trying msg */
    while (!SIP_LISTEol(msg->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(msg->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        if (numViaparams != 0)
        {
            SIP_SetViaHeader(trying, version, protocol, host,
                             numViaparams, *genParam);
        }
        else
        {
            SIP_SetViaHeader(trying, version, protocol, host,
                             0, NULL);
        }
        pos++;
    }
        
    SIP_SetCallidHeader(trying, msg->callId.number, msg->callId.host);
    SIP_SetCseqHeader(trying, msg->cseq.number, msg->cseq.method);

    ret = SIP_Encode(trying, &data);
    if (ret != ITS_SUCCESS)
    {
        SIP_ERROR(("100 trying encode failed  ret = %d \n", ret ));
        SIP_MsgFree(trying);
        return ret;
    } 

    /* Free msg we don't require it */
    SIP_MsgFree(trying);

    /* set this data to msgBuf, this will used for retransmission */
    if (ctxt->msgBuf != NULL)
    {
        /* This is previous buffer */
        ITS_Free(ctxt->msgBuf);
    }
    ctxt->msgBuf = data;

    ret = SIP_SendEventToNet(ctxt);
    
    SIP_DEBUG(("Sending 100 Trying to Network ret = %d,  buf = \n%s\n",ret, data ));

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      This function builds the message for 481 tracsaction does't exist
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
SIP_Send481ResponseToNet(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg)
{
    SIP_MSG *transResp;
    int ret = 0, pos = 0;
    ITS_CHAR * resp = "Call/Transaction Does Not Exist";
    ITS_CHAR *data = NULL;
    SIP_HOST_INFO fromHostInfo, toHostInfo, *host;
    SIP_URI_OBJ fromUri, toUri;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;


    SIP_InitMsg(&transResp);

    /* start line must */
    SIP_SetStartLine(transResp, msg->sipVersion, 481, resp, NULL, NULL);

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, msg->from.url.hostInfo.type,
                    msg->from.url.hostInfo.address,
                    msg->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, msg->from.url.scheme, msg->from.url.userName,
               msg->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(transResp, &fromUri, msg->from.displayName, NULL,
                      msg->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetHostinfo(&toHostInfo, msg->to.url.hostInfo.type,
                    msg->to.url.hostInfo.address,
                    msg->to.url.hostInfo.port);
    SIP_SetUri(&toUri, msg->to.url.scheme, msg->to.url.userName,
               msg->to.url.password, &toHostInfo);
    SIP_SetToHeader(transResp, &toUri, msg->to.displayName, NULL,
                      msg->to.numGenparams, NULL);

    /* Get Vias one by one and put in transResp msg */
    while (!SIP_LISTEol(msg->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(msg->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        if (numViaparams != 0)
        {
            SIP_SetViaHeader(transResp, version, protocol, host,
                             numViaparams, *genParam);
        }
        else
        {
            SIP_SetViaHeader(transResp, version, protocol, host,
                             0, NULL);
        }
        pos++;
    }

    SIP_SetCallidHeader(transResp, msg->callId.number, msg->callId.host);
    SIP_SetCseqHeader(transResp, msg->cseq.number, msg->cseq.method);

    ret = SIP_Encode(transResp, &data);
    if (ret != ITS_SUCCESS)
    {
        SIP_ERROR(("481 Response encode failed  ret = %d \n", ret ));
        SIP_MsgFree(transResp);
        return ret;
    }

    /* Free msg we don't require it */
    SIP_MsgFree(transResp);

    /* set this data to msgBuf, this will used for retransmission */
    if (ctxt->msgBuf != NULL)
    {
        /* This is previous buffer */
        ITS_Free(ctxt->msgBuf);
    }
    ctxt->msgBuf = data;

    ret = SIP_SendEventToNet(ctxt);

    SIP_DEBUG(("Sending 481 Response to Network ret = %d,  buf =\n%s\n",ret, data ));

    return ret;
}
/****************************************************************************
 *  Purpose:
 *      This function builds the message for 504 server time-out response
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
SIP_Send504ResponseToNet(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg)
{
    SIP_MSG *serverTimeout;
    int ret = 0, pos = 0;
    ITS_CHAR * resp = "Server Time-out";
    ITS_CHAR *data = NULL;
    SIP_HOST_INFO fromHostInfo, toHostInfo, *host;
    SIP_URI_OBJ fromUri, toUri;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;


    SIP_InitMsg(&serverTimeout);

    /* start line must */
    SIP_SetStartLine(serverTimeout, msg->sipVersion, 504, resp, NULL, NULL);

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, msg->from.url.hostInfo.type,
                    msg->from.url.hostInfo.address,
                    msg->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, msg->from.url.scheme, msg->from.url.userName,
               msg->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(serverTimeout, &fromUri, msg->from.displayName, NULL,
                      msg->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetHostinfo(&toHostInfo, msg->to.url.hostInfo.type,
                    msg->to.url.hostInfo.address,
                    msg->to.url.hostInfo.port);
    SIP_SetUri(&toUri, msg->to.url.scheme, msg->to.url.userName,
               msg->to.url.password, &toHostInfo);
    SIP_SetToHeader(serverTimeout, &toUri, msg->to.displayName, NULL,
                      msg->to.numGenparams, NULL);

    /* Get Vias one by one and put in serverTimeout msg */
    while (!SIP_LISTEol(msg->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(msg->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        if (numViaparams != 0)
        {
            SIP_SetViaHeader(serverTimeout, version, protocol, host,
                             numViaparams, *genParam);
        }
        else
        {
            SIP_SetViaHeader(serverTimeout, version, protocol, host,
                             0, NULL);
        }
        pos++;
    }

    SIP_SetCallidHeader(serverTimeout, msg->callId.number, msg->callId.host);
    SIP_SetCseqHeader(serverTimeout, msg->cseq.number, msg->cseq.method);

    ret = SIP_Encode(serverTimeout, &data);
    if (ret != ITS_SUCCESS)
    {
        SIP_ERROR(("504 Response encode failed  ret = %d \n", ret ));
        SIP_MsgFree(serverTimeout);
        return ret;
    }

    /* Free msg we don't require it */
    SIP_MsgFree(serverTimeout);

    /* set this data to msgBuf, this will used for retransmission */
    if (ctxt->msgBuf != NULL)
    {
        /* This is previous buffer */
        ITS_Free(ctxt->msgBuf);
    }
    ctxt->msgBuf = data;

    ret = SIP_SendEventToNet(ctxt);

    SIP_DEBUG(("Sending 504 Response to Network ret = %d,  buf =\n%s\n",ret, data ));

    return ret;
}
/****************************************************************************
 *  Purpose:
 *      This function builds the message for ack 
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
int
SIP_SendAck(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg)
{   
    SIP_MSG *ack;
    int ret = 0;
    ITS_CHAR *method = "ACK";
    ITS_CHAR *data = NULL;
    SIP_HOST_INFO fromHostInfo, toHostInfo;
    SIP_URI_OBJ uri, fromUri, toUri;
    SIP_HOST_INFO hostInfo;


    SIP_InitMsg(&ack);
    
    /* Set hostInfo for the startline */ 
    SIP_SetHostinfo(&hostInfo, 1, "lxserver", "5060");

    /* Set req URI for the startline */
    /* FIXME - Get these things from contact header */
    SIP_SetUri(&uri, "sip", "bob", NULL, &hostInfo);

    SIP_SetStartLine(ack, msg->sipVersion, 0, NULL, method, &uri);

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, msg->from.url.hostInfo.type,
                    msg->from.url.hostInfo.address,
                    msg->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, msg->from.url.scheme, msg->from.url.userName,
               msg->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(ack, &fromUri, msg->from.displayName, NULL,
                      msg->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetHostinfo(&toHostInfo, msg->to.url.hostInfo.type,
                    msg->to.url.hostInfo.address,
                    msg->to.url.hostInfo.port);
    SIP_SetUri(&toUri, msg->to.url.scheme, msg->to.url.userName,
               msg->to.url.password, &toHostInfo);
    SIP_SetToHeader(ack, &toUri, msg->to.displayName, NULL,
                      msg->to.numGenparams, NULL); 
    
    SIP_SetCallidHeader(ack, msg->callId.number, msg->callId.host);
    SIP_SetCseqHeader(ack, msg->cseq.number, method);

    SIP_Encode(ack, &data);
    
    /* set this data to msgBuf, this will used for retransmission */
    if (ctxt->msgBuf != NULL)
    {
        ITS_Free(ctxt->msgBuf);
    }
    ctxt->msgBuf = data;

    SIP_MsgFree(ack);

    ret = SIP_SendEventToNet(ctxt);
    return ret;
}

/****************************************************************************
 *  Purpose:
 *      This function builds the message for 400 
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
SIP_Send400Response(SIP_EVENT *sipEvt, SIP_MSG *msg, ITS_UINT code)
{   
    SIP_MSG *respMsg;
    int ret = 0, pos = 0;
    ITS_CHAR *data = NULL;
    ITS_CHAR *reasonPhrase = NULL;
    SIP_HOST_INFO fromHostInfo, toHostInfo, *host;
    SIP_URI_OBJ fromUri, toUri;
    ITS_CHAR *version, *protocol;
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;
    SIP_GENERIC_PARAM *genParam[3];

    SIP_InitMsg(&respMsg);

    /* Build 400 msg out of message we got from parser */
    switch(code)
    {
    case SIP_PARSE_HDR_CALLID_ERR:
        reasonPhrase = "Call-ID header field syntax error";
        break;
    case SIP_PARSE_MSG_MISSINGCALLID_ERR:
        reasonPhrase = "Missing Call-ID header";
        break;
    case SIP_PARSE_HDR_CSEQ_ERR:
        reasonPhrase = "C-Seq header field syntax error";
        break;
    case SIP_PARSE_MSG_MISSINGCSEQ_ERR:
        reasonPhrase = "Missing C-Seq header";
        break;
    default:
        break;
    }
     
    SIP_SetStartLine(respMsg, msg->sipVersion, 400, reasonPhrase,
                     NULL, NULL); 

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, msg->from.url.hostInfo.type,
                    msg->from.url.hostInfo.address,
                    msg->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, msg->from.url.scheme, msg->from.url.userName,
               msg->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(respMsg, &fromUri, msg->from.displayName, NULL,
                      msg->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetHostinfo(&toHostInfo, msg->to.url.hostInfo.type,
                    msg->to.url.hostInfo.address,
                    msg->to.url.hostInfo.port);
    SIP_SetUri(&toUri, msg->to.url.scheme, msg->to.url.userName,
               msg->to.url.password, &toHostInfo);
    SIP_SetToHeader(respMsg, &toUri, msg->to.displayName, NULL,
                      msg->to.numGenparams, NULL);

    /* Get Vias one by one and put in 400 msg */
    while (!SIP_LISTEol(msg->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(msg->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        if (numViaparams != 0)
        {
            SIP_SetViaHeader(respMsg, version, protocol, host,
                             numViaparams, *genParam);
        }
        else
        {
            SIP_SetViaHeader(respMsg, version, protocol, host,
                             0, NULL);
        }
        pos++;
    }

    /* For CallId and Cseq */
    if ((code == SIP_PARSE_HDR_CALLID_ERR) || 
        (code == SIP_PARSE_MSG_MISSINGCALLID_ERR))
    {
        respMsg->callId.host[0] = 0;
    }
    else
    {
        SIP_SetCallidHeader(respMsg, msg->callId.number, msg->callId.host);
    }

    if ((code == SIP_PARSE_HDR_CSEQ_ERR) ||
        (code == SIP_PARSE_MSG_MISSINGCSEQ_ERR))
    {
        respMsg->cseq.method[0] = 0;
    }
    else
    {
        SIP_SetCseqHeader(respMsg, msg->cseq.number, msg->cseq.method);
    }

    ret = SIP_Encode(respMsg, &data);
    SIP_MsgFree(respMsg);

    if (ret != ITS_SUCCESS)
    {
        SIP_ERROR(("SIP_Send400Response:: Encode failed, reason=%d\n", ret));
        return ret;
    }
       
    SIP_DEBUG(("SIP_Send400Response:: Sending "
                "data = \n\n%s\n", data)); 
    ret = SIP_TransportSend(&SIP_GET_DEST_INFO(sipEvt), 0,
                      data, SIP_configInfo.transInfo);
    if (ret != ITS_SUCCESS)
    {
        SIP_ERROR(("SIP_Send400Response: TransportSend failed, reason=%d\n",
                    ret));
    }
    return ret;
}

/****************************************************************************
 *  Purpose:
 *      This function builds the error response messages 
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
SIP_SendErrorResponseToNet(SIP_EVENT *sipEvt, SIP_MSG *msg, ITS_UINT errorCode)
{   
    SIP_MSG *respMsg = NULL;
    int ret = 0, pos = 0;
    ITS_CHAR *data = NULL;
    ITS_CHAR *reasonPhrase = NULL;
    SIP_HOST_INFO fromHostInfo, toHostInfo, *host;
    SIP_URI_OBJ fromUri, toUri;
    ITS_CHAR *version, *protocol;
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams, statusCode = 0;
    SIP_GENERIC_PARAM *genParam[3];

    /* fill up reasonPhrase and statusCode based on parsing error */
    switch(errorCode)
    {
    case SIP_PARSE_SDP_BODY_ERR:
        reasonPhrase = "Body Length Mismatch";
        statusCode = 400;
        break;

    case SIP_PARSE_STARTLINE_METHOD_ERR:
        reasonPhrase = "Method Not Allowed";
        statusCode = 405;
        break;

    case SIP_PARSE_STARTLINE_URI_ERR:
        reasonPhrase = "Request-URI Too Large";
        statusCode = 414; 
        break;

    case SIP_PARSE_SCHEME_ERR:
        reasonPhrase = "Unsupported URI Scheme";
        statusCode = 416;
        break;

    case SIP_PARSE_REQUIRE_ERR:
        reasonPhrase = "Bad Extension";
        statusCode = 420;
        break;

    case SIP_NO_TRANSACTION_FOR_MSG_IND:
        reasonPhrase = "Call Leg/Transaction Does Not Exist";
        statusCode = 481; 
        break;

    case SIP_RESPONSE_MSG_IND:
        reasonPhrase = "Request Terminated";
        statusCode = 487;
        break;
 
    case SIP_PARSE_STARTLINE_VERSION_ERR:
    case SIP_PARSE_VIA_VERSION_ERR: 
        reasonPhrase = "SIP Version not supported";
        statusCode = 505; 
        break;

    default:
        break;
    }

    /* Build error resp message for particular errors, ignore for the rest */
    if (reasonPhrase != NULL)
    {
        /* if msg is having parse error, validate mand headers 
           else use same msg to build error response */ 
        if (msg == NULL)
        {
            ret = SIP_ParseMandatoryHeaders(&msg, sipEvt->buf);
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }
        } 

        /* reject if it receive response msg in parsing error */
        if (msg->isRequest == ITS_FALSE)
        {
            SIP_MsgFree(msg);
            return SIP_TRANSACTION_INVALID_MSG;
        }

        SIP_InitMsg(&respMsg);

        SIP_SetStartLine(respMsg, msg->sipVersion, statusCode, reasonPhrase,
                         NULL, NULL); 

        /* Set Uri for From Header */
        SIP_SetHostinfo(&fromHostInfo, msg->from.url.hostInfo.type,
                        msg->from.url.hostInfo.address,
                        msg->from.url.hostInfo.port);
        SIP_SetUri(&fromUri, msg->from.url.scheme, msg->from.url.userName,
                   msg->from.url.password, &fromHostInfo);
        SIP_SetFromHeader(respMsg, &fromUri, msg->from.displayName, NULL,
                          msg->from.numGenparams, NULL);

        /* Set Uri for To Header */
        SIP_SetHostinfo(&toHostInfo, msg->to.url.hostInfo.type,
                        msg->to.url.hostInfo.address,
                        msg->to.url.hostInfo.port);
        SIP_SetUri(&toUri, msg->to.url.scheme, msg->to.url.userName,
                   msg->to.url.password, &toHostInfo);
        SIP_SetToHeader(respMsg, &toUri, msg->to.displayName, NULL,
                          msg->to.numGenparams, NULL);

        /* Get Vias one by one and put in error resp msg */
        while (!SIP_LISTEol(msg->vias, pos))
        {
            sipVia = (SIP_VIA_HDR *) SIP_ListGet(msg->vias, pos);
            SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                             &numViaparams, genParam);
            if (numViaparams != 0)
            {
                SIP_SetViaHeader(respMsg, version, protocol, host,
                                 numViaparams, *genParam);
            }
            else
            {
                SIP_SetViaHeader(respMsg, version, protocol, host,
                                 0, NULL);
            }
            pos++;
        }

        /* Careful while filling up. this two should present in request 
           other wise encoding error will raise */
        SIP_SetCallidHeader(respMsg, msg->callId.number, msg->callId.host);
        SIP_SetCseqHeader(respMsg, msg->cseq.number, msg->cseq.method);

        ret = SIP_Encode(respMsg, &data);
        SIP_MsgFree(respMsg);

        if (ret != ITS_SUCCESS)
        {
            SIP_ERROR(("SIP_SendErrorResponseToNet:: Encode failed, "
                       "reason=%d\n", ret));
            return ret;
        }
       
        SIP_DEBUG(("SIP_SendErrorResponseToNet:: Sending "
                   "data = \n\n%s\n", data)); 
        ret = SIP_TransportSend(&SIP_GET_DEST_INFO(sipEvt), 0,
                              data, SIP_configInfo.transInfo);
        if (ret != ITS_SUCCESS)
        {
            SIP_ERROR(("SIP_SendErrorResponseToNet:: TransportSend failed, "
                       "reason=%d\n", ret));
        }
    }
    return ret;
}

/****************************************************************************
 *  Purpose:
 *      This function create transport if required & update ctxt
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
SIP_GetLocalTransportForCall(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg)
{
    int ret = 0;
    SIP_VIA_HDR *via = NULL;

    SIP_GetNextVia(msg, &via, 0);

    if (isalpha((int)via->host.port[0]))
    {
        SIP_ERROR(("SIP_GetLocalTransportForCall:: Invalid port no %s", 
                    via->host.port));
        return !ITS_SUCCESS;
    }

    SIP_DEBUG(("SIP_GetLocalTransportForCall:: >>>>>>>>>>>>>>>>>>>>>>>>>"
               "IP Addr = %s   PortNo  =  %d  TranType =  %s\n",
                via->host.address, atoi(via->host.port), via->protocol ));
    ctxt->port = atoi(via->host.port);

    if (strcmp(via->protocol, "udp") == 0 || 
        strcmp(via->protocol, "UDP") == 0)
    {
        /* Use local IP address only */
        ret = SIP_TransportCreate(SIP_configInfo.transInfo->ipAddr,
                                  atoi(via->host.port), SIP_UDP, 
                                  SIP_configInfo.transInfo);

        ctxt->destInfo.transType = SIP_UDP;
    }
    else
    {
        /* This is ok for now */
        /* Use remote IP address and port */
        ret = SIP_TransportCreate(ctxt->destInfo.ipAddr,
                                  SOCK_NToHS(ctxt->destInfo.portNo), 
                                  SIP_TCP_CLIENT, SIP_configInfo.transInfo);
        ctxt->destInfo.transType = SIP_TCP_CLIENT;
    }
    
    if (ret < ITS_SUCCESS)
    {
        /* send indication to app */
        SIP_EVENT *sipEvt = NULL;
        SIP_ERROR_DATA *errorData = NULL;
        SIP_TRANSPORT_ERROR_DATA *data = NULL;

        SIP_ERROR(("Create transport failed \n"));

        data = (SIP_TRANSPORT_ERROR_DATA *)
                            ITS_Malloc(sizeof(SIP_TRANSPORT_ERROR_DATA));
        data->errorCode = SIP_TRANSPORT_CREATE_FAILED;
        data->localPort = ctxt->port;
        data->remotePort = ctxt->destInfo.portNo;

        errorData = (SIP_ERROR_DATA *) ITS_Malloc(sizeof(SIP_ERROR_DATA));
        errorData->type = SIP_TRANSPORT_ERROR;
        errorData->callId = ITS_Malloc(sizeof(SIP_CALLID_HDR));
        errorData->cseq = ITS_Malloc(sizeof(SIP_CSEQ_HDR));
        memcpy(errorData->callId, &ctxt->callId, sizeof(SIP_CALLID_HDR)); 
        memcpy(errorData->cseq, &ctxt->cSeq, sizeof(SIP_CSEQ_HDR)); 
        SOCK_IPv4AddrToName(errorData->remIpAddr, ctxt->destInfo.ipAddr);
        errorData->data =  (void*)data;

        sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
        sipEvt->type = SIP_ERROR_EVENT;
        sipEvt->msg  = (void*)errorData;

        SIP_SendEventToApp(sipEvt);
     }
     return ret;
}

/****************************************************************************
 *  Purpose:
 *      This function sends handles msg received from transport layer. 
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
SIP_HandleMsgFromTransport(SIP_EVENT *sipEvt, SIP_MSG *msg, int retCode)
{
    int ret = retCode;

    if (retCode != ITS_SUCCESS)
    {
        SIP_PARSER_ERROR_DATA *parserData = NULL;
        SIP_ERROR_DATA *errorData = NULL;

        SIP_ERROR(("SIP_HandleMsg:: Decoding failed, ErrorCode=%d\n",
                   retCode));
        SIP_ERROR(("SIP_HandleMsg:: Decoding Failed for msg \n%s\n",
                         sipEvt->buf));
        parserData = (SIP_PARSER_ERROR_DATA *)
                            ITS_Malloc(sizeof(SIP_PARSER_ERROR_DATA));

        parserData->errorCode = ret;
        parserData->buf = sipEvt->buf;

        errorData = (SIP_ERROR_DATA *) ITS_Malloc(sizeof(SIP_ERROR_DATA));
        errorData->type   =   SIP_PARSER_ERROR;
        errorData->callId = NULL;
        errorData->cseq = NULL;
        SOCK_IPv4AddrToName(errorData->remIpAddr,
                            SIP_GET_DEST_INFO(sipEvt).ipAddr);
        errorData->data   =   (void*) parserData;
        sipEvt->type = SIP_ERROR_EVENT;
        sipEvt->msg  = (void*)errorData;
        sipEvt->buf  = NULL;

        /* Send Indication to application */
        SIP_SendEventToApp(sipEvt);

        /* As of now, we are handling only this much for 400 */
        if (msg->isRequest)
        {
            if (ret == SIP_PARSE_HDR_CALLID_ERR ||
                ret == SIP_PARSE_HDR_CSEQ_ERR ||
                ret == SIP_PARSE_MSG_MISSINGCALLID_ERR ||
                ret == SIP_PARSE_MSG_MISSINGCSEQ_ERR)
            {
                /* Send 400 bad request to remote */
                SIP_Send400Response(sipEvt, msg, ret);
            }
        }
        /* Drop msg, we are not doing anything for other type of
         * parser err eg startline syntax error
         */
        SIP_MsgFree(msg);
        ITS_Free(sipEvt->buf);
        ITS_Free(sipEvt);
        return ret;
    }
    if (msg->msgId == SIP_MSG_400)
    {
        if (msg->callId.host[0] == 0 || msg->cseq.method[0] == 0)
        {
            sipEvt->type = SIP_DATA_EVENT;
            sipEvt->msg = (void*)msg;
            sipEvt->buf = NULL;
            SIP_SendEventToApp(sipEvt);
            return !ITS_SUCCESS;
        }
    }

    return ITS_SUCCESS;
}
