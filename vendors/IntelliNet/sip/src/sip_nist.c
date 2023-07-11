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
 *  ID: $Id: sip_nist.c,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
 *
 *  $Log: sip_nist.c,v $
 *  Revision 9.1  2005/03/23 12:54:27  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.10  2005/03/21 13:53:26  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.9.2.2  2005/03/09 07:08:04  mkrishna
 *  Bug fixing cycle
 *
 *  Revision 1.9.2.1  2004/12/28 14:00:33  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.9  2004/06/25 10:33:47  akumar
 *  OPTIONS msg handling upgraded.
 *
 *  Revision 1.8  2004/05/06 07:33:10  akumar
 *  Minor mod in print.
 *
 *  Revision 1.7  2004/04/27 11:15:39  sjaddu
 *  Transport layer revamping, no more dumps.
 *
 *  Revision 1.6  2004/04/15 12:16:16  sjaddu
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

#define NIST_MAX_FSM_STATES   4

/* fsm for NIST transactions */
static SIP_FSM_MAP_TABLE NIST_mapTable[NIST_MAX_FSM_STATES][SIP_MAX_MSGS];

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
NIST_UnExpectedMsg(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    if (msg)
    {
        SIP_ERROR(("NIST_UnExpectedMsg:: msg Id = %d \n", msg->msgId));
    }
    else
    {
        SIP_ERROR(("NIST_UnExpectedMsg:: time out  received \n"));
    }

    return SIP_TRANSACTION_UNEXPECTED_MSG;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Register handling in idle state
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
IDLE_HandleRegister(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    SIP_EVENT *sipEvt = NULL;
    int ret = 0;

    /* Change state ti trying */
    SIP_DEBUG(("IDLE_HandleRegister:: Received \n"));
    
    /* Change state to trying */
    ctxt->fsmState = SIP_NIST_PROCEEDING;

    /* Start timer J */
    SIP_StartTimer(ctxt, SIP_TIMER_T1, SIP_configInfo.trnTimer);
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
    ret = SIP_SendEventToApp(sipEvt);

    return ITS_SUCCESS;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Bye handling in idle state
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
IDLE_HandleBye(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    SIP_EVENT *sipEvt = NULL;
    int ret = 0;

    SIP_DEBUG(("IDLE_HandleBye:: Received \n"));

    /* Change state to trying */
    ctxt->fsmState = SIP_NIST_PROCEEDING;

    /* Start timer J */
    SIP_StartTimer(ctxt, SIP_TIMER_T1, SIP_configInfo.trnTimer);
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
    ret = SIP_SendEventToApp(sipEvt);

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Notify handling in idle state
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
IDLE_HandleNotify(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    SIP_EVENT *sipEvt = NULL;
    int ret = 0;

    SIP_DEBUG(("IDLE_HandleNotify:: Received \n"));

    /* Change state to trying */
    ctxt->fsmState = SIP_NIST_PROCEEDING;

    /* Start timer J */
    SIP_StartTimer(ctxt, SIP_TIMER_T1, SIP_configInfo.trnTimer);
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
    ret = SIP_SendEventToApp(sipEvt);

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Notify handling in idle state
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
IDLE_HandleOptions(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    SIP_EVENT *sipEvt = NULL;
    int ret = 0;

    SIP_DEBUG(("IDLE_HandleOptions:: Received \n"));

    /* Change state to trying */
    ctxt->fsmState = SIP_NIST_PROCEEDING;

    /* Start timer J */
    SIP_StartTimer(ctxt, SIP_TIMER_T1, SIP_configInfo.trnTimer);
    if (ret != ITS_SUCCESS)
    {
        SIP_ERROR(("Failed to start timer, terminating transaction\n"));
        ctxt->purge  = ITS_TRUE;
        return ret;
    }

    sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
    sipEvt->type = SIP_DATA_EVENT;
    sipEvt->type = SIP_DATA_EVENT;
    sipEvt->msg = (void*)msg;
    sipEvt->buf = NULL;

    /* Send to app*/
    ret = SIP_SendEventToApp(sipEvt);

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in NIST idle state
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
NIST_GetMsgProcIdle(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_MSG_REGISTER:
        return IDLE_HandleRegister;
    case SIP_MSG_OPTIONS:
        return IDLE_HandleOptions;
    case SIP_MSG_BYE:
        return IDLE_HandleBye;
    case SIP_MSG_NOTIFY:
        return IDLE_HandleNotify;
    default :
        return NIST_UnExpectedMsg;

    }
}

/*
 *  TRYING   TRYING    TRYING     TRYING     TRYING     TRYING 
 */
static SIP_TransactionHandler
NIST_GetMsgProcTrying(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    default :
        return NIST_UnExpectedMsg;
    }
}


/*
 *   PROCEEDING    PROCEEDING    PROCEEDING    PROCEEDING    PROCEEDING 
 */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      23456xx  handling in proceeding state
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
PROCEEDING_Handle23456xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg,
                         ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_ERROR(("PROCEEDING_Handle23456xx::Received 23456x from remote \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }   
    else
    {
        SIP_DEBUG(("PROCEEDING_Handle23456xx:: 23456xx from app \n"));
        /* Go to proceeding */
        ctxt->fsmState = SIP_NIST_COMPLETED;

        /* Send to remote */
        ret = SIP_SendEventToNet(ctxt);
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Bye handling in proceeding state
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
PROCEEDING_HandleBye(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    SIP_EVENT *sipEvt = NULL;

    SIP_DEBUG(("PROCEEDING_HandleBye:: send to app again\n"));
    
    sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
    sipEvt->type = SIP_DATA_EVENT;
    sipEvt->msg = (void*)msg;
    sipEvt->buf = NULL;

    /* send response */
    ret = SIP_SendEventToApp(sipEvt);

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Register handling in proceeding state
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
PROCEEDING_HandleRegister(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg,
                           ITS_USHORT src)
{
    int ret = 0;
    SIP_EVENT *sipEvt = NULL;
    SIP_DEBUG(("PROCEEDING_HandleRegister:: send to app again\n"));

    sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
    sipEvt->type = SIP_DATA_EVENT;
    sipEvt->msg = (void*)msg;
    sipEvt->buf = NULL;

    ret = SIP_SendEventToApp(sipEvt);
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Register handling in proceeding state
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
PROCEEDING_HandleOptions(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg,
                           ITS_USHORT src)
{
    int ret = 0;
    SIP_EVENT *sipEvt = NULL;
    SIP_DEBUG(("PROCEEDING_HandleOptions:: send to app again\n"));

    sipEvt = (SIP_EVENT *) ITS_Malloc(sizeof(SIP_EVENT));
    sipEvt->type = SIP_DATA_EVENT;
    sipEvt->msg = (void*)msg;
    sipEvt->buf = NULL;

    ret = SIP_SendEventToApp(sipEvt);
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Time out handling in proceeding state
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
    SIP_DEBUG(("PROCEEDING_HandleTimeout:: Deleting the ctxt \n"));

    /*Send indication to app*/
    ret =  SIP_SendTimeoutToApp(ctxt, SIP_NO_RESPONSE_FROM_APP);

    /* This means we never get 2,3 xxx from application */
    ctxt->purge = ITS_TRUE;

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in NIST Proceeding state
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
NIST_GetMsgProcProceeding(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_MSG_200:
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
        return PROCEEDING_Handle23456xx; 
    case SIP_MSG_BYE:
        return PROCEEDING_HandleBye;
    case SIP_MSG_REGISTER:
        return PROCEEDING_HandleRegister;
    case SIP_MSG_OPTIONS:
        return PROCEEDING_HandleOptions;
    case SIP_TIMER_T1:
        return PROCEEDING_HandleTimeout;
    default :
        return NIST_UnExpectedMsg;
    }
}

/*
 *  COMPLETED   COMPLETED   COMPLETED   COMPLETED   COMPLETED   COMPLETED
 */ 

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Bye handling in completed state
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
COMPLETED_HandleBye(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    SIP_DEBUG(("COMPLETED_HandleBye:: retransmited bye\n"));

    /* send response */
    SIP_DEBUG(("COMPLETED_HandleBye:: Sending Resp= \n\n%s\n", ctxt->msgBuf));
    ret = SIP_SendEventToNet(ctxt);

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Register handling in completed state
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
COMPLETED_HandleRegister(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg,
                           ITS_USHORT src)
{
    int ret = 0;
    SIP_DEBUG(("COMPLETED_HandleBye:: Ignoring retransmited register\n"));

    /* send response */
    ret = SIP_SendEventToNet(ctxt);

    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      time out handling in complted state
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
    SIP_DEBUG(("COMPLETED_HandleTimeout:: Received time out \n"));

    /* We are done with this transaction */
    ctxt->purge = ITS_TRUE;
 
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in NIST Completed state
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
NIST_GetMsgProcCompleted(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_TIMER_T1:
        return COMPLETED_HandleTimeout;
    case SIP_MSG_REGISTER:
        return COMPLETED_HandleRegister;
    case SIP_MSG_BYE:
        return COMPLETED_HandleBye;
    default :
        return NIST_UnExpectedMsg;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in NIST Terminated state
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
NIST_GetMsgProcTerminated(SIP_MSG_TYPE msg)
{
    switch(msg)
    {

    case SIP_MSG_INVITE:
    default :
        return NIST_UnExpectedMsg;
    }

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      FSM load function to nist transaction layer
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
NIST_GetMsgProc(SIP_FSM_STATE state, SIP_MSG_TYPE msg)
{
    switch(state)
    {
    case SIP_IDLE:
        return NIST_GetMsgProcIdle(msg);
        break;

    case SIP_NIST_TRYING:
         return NIST_GetMsgProcTrying(msg);
         break;

    case SIP_NIST_PROCEEDING:
        return NIST_GetMsgProcProceeding(msg);
        break;
    
    case SIP_NIST_COMPLETED:
        return NIST_GetMsgProcCompleted(msg);
        break;

    case SIP_NIST_TERMINATED:
        return NIST_GetMsgProcTerminated(msg);
        break;

    default :
        SIP_ERROR(("SIP_NISTGetMsgProc:: Error, invalied fsm state \n"));
    }
    
    return NIST_UnExpectedMsg;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      FSM load function to nist transaction layer
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
SIP_NISTLoadFsm()
{
    SIP_FSM_STATE state = 0;
    SIP_MSG_TYPE msg = 0;

    SIP_DEBUG(("SIP_NISTLoadFsm:: loading \n"));

    for (state =0 ; state < NIST_MAX_FSM_STATES; ++state)
    {
        for (msg =0; msg < SIP_MAX_MSGS; ++msg)
        {
            NIST_mapTable[state][msg].transProc  =  NIST_GetMsgProc(state, msg);
        }
    }


    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This is sip entry function to nist transaction layer
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
SIP_NISTEntry(SIP_TRANSACTION_CTXT *ctxt,
                 SIP_MSG_TYPE type,
                 SIP_MSG *msg, ITS_USHORT src)
{
    int ret;

    SIP_DEBUG(("SIP_NISTEntry:: Entry ---\n"));

    if (ctxt->fsmState > NIST_MAX_FSM_STATES || type > SIP_MAX_MSGS)
    {
        return SIP_TRANSACTION_INVALID_MSG;
    }

    ret = (NIST_mapTable[ctxt->fsmState][type].transProc)(ctxt, msg, src);

    SIP_DEBUG(("SIP_NISTEntry:: Exit ---\n"));
    return ret;
}
