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
 *  ID: $Id: sip_nict.c,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
 *
 *  $Log: sip_nict.c,v $
 *  Revision 9.1  2005/03/23 12:54:27  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.11  2005/03/21 13:53:26  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.10.2.2  2005/03/09 07:07:04  mkrishna
 *  Bug fixing cycle
 *
 *  Revision 1.10.2.1  2004/12/28 14:00:33  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.10  2004/07/19 14:35:53  sjaddu
 *  Added Handle23456xx in completed state.
 *
 *  Revision 1.9  2004/06/28 07:33:13  sjaddu
 *  Bug fixes during load, SIP_Stackhandle is also added.
 *
 *  Revision 1.8  2004/06/25 10:33:47  akumar
 *  OPTIONS msg handling upgraded.
 *
 *  Revision 1.7  2004/04/27 11:15:39  sjaddu
 *  Transport layer revamping, no more dumps.
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

#define NICT_MAX_FSM_STATES   4

/* fsm for NICT transactions */
static SIP_FSM_MAP_TABLE NICT_mapTable[NICT_MAX_FSM_STATES][SIP_MAX_MSGS];

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
NICT_UnExpectedMsg(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    if (msg)
    {
        SIP_ERROR(("NICT_UnExpectedMsg:: msg Id %d d \n", msg->msgId));
    }
    else
    {
        SIP_ERROR(("NICT_UnExpectedMsg:: time out  received \n"));
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
    int ret = 0;

    SIP_DEBUG(("IDLE_HandleRegister:: Received Register in NICT \n"));

    /* Change state to trying */
    ctxt->fsmState = SIP_NICT_TRYING;

    /*start timer E */
    ret = SIP_StartTimer(ctxt, SIP_TIMER_T1, ctxt->reTranstimer);
    ctxt->reTranstimer =+ ctxt->reTranstimer; 

    /* Send to app*/
    ret = SIP_SendEventToNet(ctxt);

    return ret;
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
    int ret = 0;
    SIP_DEBUG(("IDLE_HandleBye:: Received bye in NICT \n"));
        
    /* Change state to trying */
    ctxt->fsmState = SIP_NICT_TRYING;

    /*start timer E */
    ret = SIP_StartTimer(ctxt, SIP_TIMER_T1, ctxt->reTranstimer);
    ctxt->reTranstimer =+ ctxt->reTranstimer; 

    /* Send to app*/
    ret = SIP_SendEventToNet(ctxt);

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Options handling in idle state
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
    int ret = 0;

    SIP_DEBUG(("IDLE_HandleOptions:: Received Options in NICT \n"));

    /* Change state to trying */
    ctxt->fsmState = SIP_NICT_TRYING;

    /*start timer E */
    ret = SIP_StartTimer(ctxt, SIP_TIMER_T1, ctxt->reTranstimer);
    ctxt->reTranstimer =+ ctxt->reTranstimer;

    ret = SIP_SendEventToNet(ctxt);
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in NICT idle state
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
NICT_GetMsgProcIdle(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_MSG_REGISTER:
        return IDLE_HandleRegister;
    case SIP_MSG_OPTIONS:
        return IDLE_HandleOptions;
    case SIP_MSG_BYE:
        return IDLE_HandleBye;

    default :
        return NICT_UnExpectedMsg;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      1xx handling in trying state
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
TRYING_Handle1xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_EVENT *sipEvt = NULL;
        SIP_DEBUG(("TRYING_Handle1xx:: Received 1xx from remote \n"));

        /* stop timer E */
        SIP_StopTimer(ctxt);

        /* Go to proceeding */
        ctxt->fsmState = SIP_NICT_PROCEEDING;

        /* Start timer E Again */
        SIP_StartTimer(ctxt, SIP_TIMER_T1, ctxt->reTranstimer);

        ctxt->reTranstimer += ctxt->reTranstimer;

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
        SIP_ERROR(("TRYING_Handle1xx:: Received 1xx from APP \n"));
    }
 
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      23456xx  handling in trying state
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
TRYING_Handle23456xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_EVENT *sipEvt = NULL;
        SIP_DEBUG(("TRYING_Handle23456xx::Received 23456x from remote \n"));

        /* stop timer E */
        SIP_StopTimer(ctxt);

        /* Go to proceeding */
        ctxt->fsmState = SIP_NICT_COMPLETED;

        /* Start timer K T4 */
        SIP_StartTimer(ctxt, SIP_TIMER_T1, SIP_configInfo.T4);
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
    }   
    else
    {
        SIP_ERROR(("TRYING_Handle23456xx::Received 23456x from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handling time out in trying state
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
TRYING_HandleTimeout(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    SIP_DEBUG(("TRYING_HandleTimeout:: Received time out \n"));
    
    if (ctxt->reTranstimer < SIP_configInfo.trnTimer)
    {
        if (ctxt->reTranstimer < SIP_configInfo.T2)
        {
            /* start timer A */
            ret = SIP_StartTimer(ctxt, SIP_TIMER_T1, ctxt->reTranstimer);
            if (ret != ITS_SUCCESS)
            {
                SIP_ERROR(("Failed to start timer E"));
            }
        }
        else
        {
            /* start timer wiht val T2 */
            ret = SIP_StartTimer(ctxt, SIP_TIMER_T1, SIP_configInfo.T2);
            if (ret != ITS_SUCCESS)
            {
                SIP_ERROR(("Failed to start timer T2"));
            }
        }

        ctxt->reTranstimer += ctxt->reTranstimer;

        /* Send to remote */
        ret = SIP_SendEventToNet(ctxt);
    }
    else
    {
        /*we are done with this, Delete */
        ctxt->purge = ITS_TRUE;

        /*Send indication to app*/
        ret =  SIP_SendTimeoutToApp(ctxt, SIP_NO_RESPONSE_FROM_NET);
    }
 
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in NICT Trying state
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
NICT_GetMsgProcTrying(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_MSG_100:
    case SIP_MSG_180:
    case SIP_MSG_181:
    case SIP_MSG_182:
    case SIP_MSG_183:
        return TRYING_Handle1xx;
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
        return TRYING_Handle23456xx; 
    case SIP_TIMER_T1:
        return TRYING_HandleTimeout;

    case SIP_MSG_INVITE:
    default :
        return NICT_UnExpectedMsg;
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
PROCEEDING_Handle23456xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    int ret = 0;
    if (src == ITS_SIP_TRANSPORT_SRC)
    {
        SIP_EVENT *sipEvt = NULL;
        SIP_DEBUG(("PROCEEDING_Handle23456xx::Received 23456x from remote \n"));

        /* stop timer E */
        SIP_StopTimer(ctxt);

        /* Go to proceeding */
        ctxt->fsmState = SIP_NICT_COMPLETED;

        /* Start timer K T4 */
        SIP_StartTimer(ctxt, SIP_TIMER_T1, SIP_configInfo.T4);
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
    }   
    else
    {
        SIP_DEBUG(("PROCEEDING_HandleACK:: Received ACK from app \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
 
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handling time out in proceeding state
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
    if (ctxt->reTranstimer < SIP_configInfo.trnTimer)
    {
        /* start timer E */
        ret = SIP_StartTimer(ctxt, SIP_TIMER_T1, ctxt->reTranstimer);
        if (ret != ITS_SUCCESS)
        {
            SIP_ERROR(("Failed to start timer E"));
        }

        ctxt->reTranstimer += ctxt->reTranstimer;

        /* Send to remote */
        ret = SIP_SendEventToNet(ctxt);
    }
    else
    {
        /*we are done with this, Delete */
        ctxt->purge = ITS_TRUE;

        /*Send indication to app*/
        ret =  SIP_SendTimeoutToApp(ctxt, SIP_NO_RESPONSE_FROM_NET);
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      1xx handling in proceeding state
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
        SIP_DEBUG(("PROCEEDING_Handle1xx:: Received 1xx from remote \n"));
        /*Ignore it */
    }   
    else
    {
        SIP_ERROR(("PROCEEDING_Handle1xx:: Received 1xx from APP \n"));
        ret = SIP_TRANSACTION_UNEXPECTED_MSG;
    }
 
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in NICT Proceeding state
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
NICT_GetMsgProcProceeding(SIP_MSG_TYPE msg)
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
    case SIP_TIMER_T1:
        return PROCEEDING_HandleTimeout;
    default :
        return NICT_UnExpectedMsg;
    }
}

/*
 *  COMPLETED   COMPLETED   COMPLETED   COMPLETED   COMPLETED   COMPLETED
 */ 
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      1xx handling in proceeding state
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
 *      1xx handling in proceeding state
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
COMPLETED_Handle23456xx(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg, ITS_USHORT src)
{
    SIP_DEBUG(("COMPLETED_HandleTimeout:: Received 23456xx \n"));
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in NICT Completed state
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
NICT_GetMsgProcCompleted(SIP_MSG_TYPE msg)
{
    switch(msg)
    {
    case SIP_TIMER_T1:
        return COMPLETED_HandleTimeout;
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
        return COMPLETED_Handle23456xx;

    default :
        return NICT_UnExpectedMsg;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the right msg proc for the right msg in NICT Terminated state
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
NICT_GetMsgProcTerminated(SIP_MSG_TYPE msg)
{
    switch(msg)
    {

    case SIP_MSG_INVITE:
    default :
        return NICT_UnExpectedMsg;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      FSM load function to nict transaction layer
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
NICT_GetMsgProc(SIP_FSM_STATE state, SIP_MSG_TYPE msg)
{
    switch(state)
    {
    case SIP_IDLE:
        return NICT_GetMsgProcIdle(msg);
        break;

    case SIP_NICT_TRYING:
         return NICT_GetMsgProcTrying(msg);
         break;

    case SIP_NICT_PROCEEDING:
        return NICT_GetMsgProcProceeding(msg);
        break;
    
    case SIP_NICT_COMPLETED:
        return NICT_GetMsgProcCompleted(msg);
        break;

    case SIP_NICT_TERMINATED:
        return NICT_GetMsgProcTerminated(msg);
        break;

    default :
        SIP_ERROR(("SIP_NICTGetMsgProc:: Error, invalied fsm state \n"));
    }
    
    return NICT_UnExpectedMsg;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      FSM load function to nict transaction layer
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
SIP_NICTLoadFsm()
{
    SIP_FSM_STATE state = 0;
    SIP_MSG_TYPE msg = 0;

    SIP_DEBUG(("SIP_NICTLoadFsm:: loading \n"));

    for (state =0 ; state < NICT_MAX_FSM_STATES; ++state)
    {
        for (msg =0; msg < SIP_MAX_MSGS; ++msg)
        {
            NICT_mapTable[state][msg].transProc  =  NICT_GetMsgProc(state, msg);
        }
    }


    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This is sip entry function to nict transaction layer
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
SIP_NICTEntry(SIP_TRANSACTION_CTXT *ctxt,
                 SIP_MSG_TYPE type,
                 SIP_MSG *msg, ITS_USHORT src)
{
    int ret;

    SIP_DEBUG(("SIP_NICTEntry:: Enter \n"));

    if (ctxt->fsmState > NICT_MAX_FSM_STATES || type > SIP_MAX_MSGS)
    {
        return SIP_TRANSACTION_INVALID_MSG;
    }
        
    ret = (NICT_mapTable[ctxt->fsmState][type].transProc)(ctxt, msg, src);

    SIP_DEBUG(("SIP_NICTEntry:: Exit \n"));
    return ret;
}
