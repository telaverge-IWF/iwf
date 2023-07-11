/*********************************-*-C-*-************************************
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
 * LOG: $Log: dcca_fsm.cpp,v $
 * LOG: Revision 3.1.94.2.2.1.6.1  2015/03/20 07:26:56  jkchaitanya
 * LOG: changes for stopping tx timer for CCAT cases
 * LOG:
 * LOG: Revision 3.1.94.2.2.1  2014/06/26 10:31:32  millayaraja
 * LOG: changes made to allow only CCR-T in PenI and PenU state
 * LOG:
 * LOG: Revision 3.1.94.2  2014/05/06 13:09:12  jkchaitanya
 * LOG: changes for ccfh feature
 * LOG:
 * LOG: Revision 3.1.94.1  2014/02/12 07:12:15  millayaraja
 * LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
 * LOG:
 * LOG: Revision 3.1.82.1  2013/08/12 13:08:52  jsarvesh
 * LOG: Overriding DCCA feature not to clear the Session and allow sending CCR-T in case of CCA-U with Error Code
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.7  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.5.8.1  2007/04/19 09:53:36  hbhatnagar
 * LOG: Dont remove context if Rc=2xxx (BCGI requirement)
 * LOG:
 * LOG: Revision 2.5  2006/11/30 10:12:56  hbhatnagar
 * LOG: clean up done
 * LOG:
 * LOG: Revision 2.4  2006/11/24 16:36:30  hbhatnagar
 * LOG: Made changes for SessionId as Key and corresponding changes
 * LOG:
 * LOG: Revision 2.3  2006/11/14 10:23:05  hbhatnagar
 * LOG: shifted the namespace here from corresponding .h file
 * LOG:
 * LOG: Revision 2.2  2006/11/13 06:45:20  hbhatnagar
 * LOG: Proper Indentation and cleanup done
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:55  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/25 08:45:51  nvijikumar
 * LOG: Converted file from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:38:20  nvijikumar
 * LOG: Getting the Tx and Tcc timers from DCCAConf instead of global (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_fsm.cpp,v 3.1.94.2.2.1.6.1 2015/03/20 07:26:56 jkchaitanya Exp $
 *
 ****************************************************************************/

/**
 * Includes
 */
#include <dcca_fsm.h>

/**
 * Namespace
 */
#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

/****************************************************************************
 *
 *  Purpose                : Constructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAFsm::DCCAFsm()
{        
    dccaFsmStatemachine[DCCA_CLIENT_FSM_AAA] = new DCCAClientFsmAaa();
    dccaFsmStatemachine[DCCA_CLIENT_FSM_CCR] = new DCCAClientFsmCcr();
    dccaFsmStatemachine[DCCA_CLIENT_FSM_FIN] = new DCCAClientFsmFin();
    dccaFsmStatemachine[DCCA_CLIENT_FSM_EVE] = new DCCAClientFsmEve();
    dccaFsmStatemachine[DCCA_SERVER_FSM_SES] = new DCCAServerFsmSes();
}

/****************************************************************************
 *
 *  Purpose                : Destructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAFsm::~DCCAFsm()
{
    delete dccaFsmStatemachine[DCCA_CLIENT_FSM_AAA];
    delete dccaFsmStatemachine[DCCA_CLIENT_FSM_CCR];
    delete dccaFsmStatemachine[DCCA_CLIENT_FSM_FIN];
    delete dccaFsmStatemachine[DCCA_CLIENT_FSM_EVE];
    delete dccaFsmStatemachine[DCCA_SERVER_FSM_SES];

    dccaFsmStatemachine[DCCA_CLIENT_FSM_AAA] = NULL;
    dccaFsmStatemachine[DCCA_CLIENT_FSM_CCR] = NULL;
    dccaFsmStatemachine[DCCA_CLIENT_FSM_FIN] = NULL;
    dccaFsmStatemachine[DCCA_CLIENT_FSM_EVE] = NULL;
    dccaFsmStatemachine[DCCA_SERVER_FSM_SES] = NULL;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in a particular statemachine
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAFsm::SubmitToFsm(DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    return dccaFsmStatemachine[ctx->statemachine]->SubmitToStatemachine(eve, ctx);
}

/****************************************************************************
 *
 *  Purpose                : Constructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAClientFsmAaa::DCCAClientFsmAaa()
{
    dccaFsmState[DCCA_FSM_STATE_IDLE] = new DCCAClientFsmAaaStateIdle();
    dccaFsmState[DCCA_FSM_STATE_PENI] = new DCCAClientFsmAaaStatePenI();
    dccaFsmState[DCCA_FSM_STATE_OPEN] = new DCCAClientFsmAaaStateOpen();
}

/****************************************************************************
 *
 *  Purpose                : Destructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAClientFsmAaa::~DCCAClientFsmAaa()
{
    delete dccaFsmState[DCCA_FSM_STATE_IDLE];
    delete dccaFsmState[DCCA_FSM_STATE_PENI];
    delete dccaFsmState[DCCA_FSM_STATE_OPEN];    

    dccaFsmState[DCCA_FSM_STATE_IDLE] = NULL;    
    dccaFsmState[DCCA_FSM_STATE_PENI] = NULL;
    dccaFsmState[DCCA_FSM_STATE_OPEN] = NULL;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this statemachine
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmAaa::SubmitToStatemachine(DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    return dccaFsmState[ctx->state]->SubmitToState(eve, ctx);
}

/****************************************************************************
 *
 *  Purpose                : Constructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAClientFsmCcr::DCCAClientFsmCcr()
{
    dccaFsmState[DCCA_FSM_STATE_IDLE] = new DCCAClientFsmCcrStateIdle();
    dccaFsmState[DCCA_FSM_STATE_PENI] = new DCCAClientFsmCcrStatePenI();
    dccaFsmState[DCCA_FSM_STATE_OPEN] = new DCCAClientFsmCcrStateOpen();    
}

/****************************************************************************
 *
 *  Purpose                : Destructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAClientFsmCcr::~DCCAClientFsmCcr()
{
    delete dccaFsmState[DCCA_FSM_STATE_IDLE];
    delete dccaFsmState[DCCA_FSM_STATE_PENI];
    delete dccaFsmState[DCCA_FSM_STATE_OPEN];    

    dccaFsmState[DCCA_FSM_STATE_IDLE] = NULL;    
    dccaFsmState[DCCA_FSM_STATE_PENI] = NULL;
    dccaFsmState[DCCA_FSM_STATE_OPEN] = NULL;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this statemachine
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmCcr::SubmitToStatemachine(DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    return dccaFsmState[ctx->state]->SubmitToState(eve, ctx);
}

/****************************************************************************
 *
 *  Purpose                : Constructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAClientFsmFin::DCCAClientFsmFin()
{
    dccaFsmState[DCCA_FSM_STATE_IDLE] = new DCCAClientFsmFinStateIdle();
    dccaFsmState[DCCA_FSM_STATE_PENU] = new DCCAClientFsmFinStatePenU();
    dccaFsmState[DCCA_FSM_STATE_PENT] = new DCCAClientFsmFinStatePenT();
    dccaFsmState[DCCA_FSM_STATE_OPEN] = new DCCAClientFsmFinStateOpen();    
}

/****************************************************************************
 *
 *  Purpose                : Destructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAClientFsmFin::~DCCAClientFsmFin()
{
    delete dccaFsmState[DCCA_FSM_STATE_IDLE];
    delete dccaFsmState[DCCA_FSM_STATE_PENU];
    delete dccaFsmState[DCCA_FSM_STATE_PENT];
    delete dccaFsmState[DCCA_FSM_STATE_OPEN];    

    dccaFsmState[DCCA_FSM_STATE_IDLE] = NULL;    
    dccaFsmState[DCCA_FSM_STATE_PENU] = NULL;
    dccaFsmState[DCCA_FSM_STATE_PENT] = NULL;
    dccaFsmState[DCCA_FSM_STATE_OPEN] = NULL;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this statemachine
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmFin::SubmitToStatemachine(DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    return dccaFsmState[ctx->state]->SubmitToState(eve, ctx);
}

/****************************************************************************
 *
 *  Purpose                : Constructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAClientFsmEve::DCCAClientFsmEve()
{
    dccaFsmState[DCCA_FSM_STATE_IDLE] = new DCCAClientFsmEveStateIdle();
    dccaFsmState[DCCA_FSM_STATE_PENB] = new DCCAClientFsmEveStatePenB();
    dccaFsmState[DCCA_FSM_STATE_PENE] = new DCCAClientFsmEveStatePenE();
}

/****************************************************************************
 *
 *  Purpose                : Destructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAClientFsmEve::~DCCAClientFsmEve()
{
    delete dccaFsmState[DCCA_FSM_STATE_IDLE];
    delete dccaFsmState[DCCA_FSM_STATE_PENB];
    delete dccaFsmState[DCCA_FSM_STATE_PENE];

    dccaFsmState[DCCA_FSM_STATE_IDLE] = NULL;    
    dccaFsmState[DCCA_FSM_STATE_PENB] = NULL;
    dccaFsmState[DCCA_FSM_STATE_PENE] = NULL;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this statemachine
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmEve::SubmitToStatemachine(DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    return dccaFsmState[ctx->state]->SubmitToState(eve, ctx);
}

/****************************************************************************
 *
 *  Purpose                : Constructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAServerFsmSes::DCCAServerFsmSes()
{
    dccaFsmState[DCCA_FSM_STATE_IDLE] = new DCCAServerFsmSesStateIdle();
    dccaFsmState[DCCA_FSM_STATE_OPEN] = new DCCAServerFsmSesStateOpen();
}

/****************************************************************************
 *
 *  Purpose                : Destructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAServerFsmSes::~DCCAServerFsmSes()
{
    delete dccaFsmState[DCCA_FSM_STATE_IDLE];
    delete dccaFsmState[DCCA_FSM_STATE_OPEN];

    dccaFsmState[DCCA_FSM_STATE_IDLE] = NULL;    
    dccaFsmState[DCCA_FSM_STATE_OPEN] = NULL;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this statemachine
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAServerFsmSes::SubmitToStatemachine(DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    return dccaFsmState[ctx->state]->SubmitToState(eve, ctx);
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmAaaStateIdle::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    /**
     * Only AAR is allowed
     */
    if( !(eve->req && eve->cmd == DCCA_COMMAND_AAR) )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_AAA: DCCA_FSM_STATE_IDLE: " \
        "Unsupported command for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }

    /**
     * Only AAR with CREDIT_AUTHORIZATION is allowed
     */
    if( eve->ccl != DCCA_CREDIT_AUTHORIZATION )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_AAA: DCCA_FSM_STATE_IDLE: " \
        "Unsupported CreditControl for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }

    /**
     * Start the timer Tx
     */    
    ITS_UINT txTimer = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_TX_TIMER);
    if((ctx->timerkey = TIMERS_StartTimer(
    ITS_DCCA_SRC, txTimer, (void*)ctx, sizeof(DCCA_CONTEXT))) == 0)
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_AAA: DCCA_FSM_STATE_IDLE: " \
        "Could not start timer Tx for session: %s ...", ctx->sessionId));
        
        return DCCA_CONTEXT_ERROR;
    }
    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_CLIENT_FSM_AAA: DCCA_FSM_STATE_IDLE: " \
    "Timer Tx started for session: %s ...", ctx->sessionId));

    /**
     * Update the context
     */
    ctx->state  = DCCA_FSM_STATE_PENI;
    ctx->timer  = DCCA_TIMER_TX_TIME_OUT;

    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_CLIENT_FSM_AAA: DCCA_FSM_STATE_IDLE: " \
    "State changed from Idle to PendingI " \
    "for session: %s ...", ctx->sessionId));

    return DCCA_CONTEXT_MODIFY;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmAaaStatePenI::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    /**
     * Only AAA is allowed
     */
    if( !(!eve->req && eve->cmd == DCCA_COMMAND_AAA) )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_AAA: DCCA_FSM_STATE_PENI: " \
        "Unsupported command for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }

    /**
     * Stop the timer Tx
     */
    if( ctx->timer )
    {
        if(ITS_SUCCESS != TIMERS_CancelTimer(ctx->timerkey))
        {
            DCCA_TRACE_DEBUG((
            "DCCA: DCCA_CLIENT_FSM_AAA: DCCA_FSM_STATE_PENI: " \
            "Could not stop timer Tx for session: %s ...", 
            ctx->sessionId));
        }
        else 
        {
            ctx->timer = 0;
            DCCA_TRACE_DEBUG((
            "DCCA: DCCA_CLIENT_FSM_AAA: DCCA_FSM_STATE_PENI: " \
            "Timer Tx stopped for session: %s ...", ctx->sessionId));
        }
    }

    /**
     * Error AAA
     */
    if( eve->cod < DCCA_DIAMETER_SUCCESS_MIN_RANGE || 
        eve->cod > DCCA_DIAMETER_SUCCESS_MAX_RANGE )
    {
        DCCA_TRACE_DEBUG((
        "DCCA: DCCA_CLIENT_FSM_AAA: DCCA_FSM_STATE_PENI: " \
        "State changed from PendingI to Idle " \
        "for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_REMOVE;
    }
    
    /**
     * Good AAA and update the context
     */
    ctx->state        = DCCA_FSM_STATE_OPEN;
    ctx->statemachine = DCCA_CLIENT_FSM_FIN;

    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_CLIENT_FSM_AAA: DCCA_FSM_STATE_PENI: " \
    "State changed from PendingI to Open " \
    "for session: %s ...", ctx->sessionId));

    return DCCA_CONTEXT_MODIFY;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmAaaStateOpen::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    return DCCA_CONTEXT_NONE;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmCcrStateIdle::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    /**
     * Only CCR is allowed
     */
    if( !(eve->req && eve->cmd == DCCA_COMMAND_CCR) )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_IDLE: " \
        "Unsupported command for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }
        
    /**
     * Only CCR with INITIAL is allowed
     */
    if( eve->typ != DCCA_INI_REQUEST )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_IDLE: " \
        "Unsupported CCRequestType for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }

    /**
     * Start the timer Tx
     */    
    ITS_UINT txTimer = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_TX_TIMER);
    if((ctx->timerkey = TIMERS_StartTimer(
    ITS_DCCA_SRC, txTimer, (void*)ctx, sizeof(DCCA_CONTEXT))) == 0)
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_IDLE: " \
        "Could not start timer Tx for session: %s ...", ctx->sessionId));
        
        return DCCA_CONTEXT_ERROR;
    }
    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_IDLE: " \
    "Timer Tx started for session: %s ...", ctx->sessionId));

    /**
     * Update the context
     */    
    ctx->state  = DCCA_FSM_STATE_PENI;
    ctx->timer  = DCCA_TIMER_TX_TIME_OUT;

    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_IDLE: " \
    "State changed from Idle to PendingI " \
    "for session: %s ...", ctx->sessionId));

    return DCCA_CONTEXT_MODIFY;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmCcrStatePenI::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{    
    /**
     * Only CCA is allowed
     */
    if( !(!eve->req && eve->cmd == DCCA_COMMAND_CCA) )
    {
        /* Only CCR-T is allowed so that Session can be terminated
         * Cancel the Timer and move state to Open */
        if (eve->typ == DCCA_TER_REQUEST)
        {
            if(ctx->timer)
            {
                if(ITS_SUCCESS != TIMERS_CancelTimer(ctx->timerkey))
                {
                    DCCA_TRACE_DEBUG((
                                "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_PENI: " \
                                "Could not stop timer Tx for session: %s ...", 
                                ctx->sessionId));
                }
                else
                {
                    ctx->timer = 0;
                    DCCA_TRACE_DEBUG((
                                "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_PENI: " \
                                "Timer Tx stopped for session: %s ...", ctx->sessionId));
                }
            }

            /*
             * Start the timer Tx for CCR-T
            */
            ITS_UINT txTimer = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_TX_TIMER);
            if((ctx->timerkey = TIMERS_StartTimer(
                            ITS_DCCA_SRC, txTimer, (void*)ctx, sizeof(DCCA_CONTEXT))) == 0)
            {
                DCCA_TRACE_WARNING((
                            "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENI: " \
                            "Could not start timer Tx for session: %s ...", ctx->sessionId));

                return DCCA_CONTEXT_ERROR;
            }    
            DCCA_TRACE_DEBUG((
                        "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENI: " \
                        "Timer Tx started for session: %s ...", ctx->sessionId));
            ctx->timer  = DCCA_TIMER_TX_TIME_OUT;
            /**
             * CCR-T update the context
             */
            ctx->state  = DCCA_FSM_STATE_PENT;
            ctx->statemachine = DCCA_CLIENT_FSM_FIN;

            DCCA_TRACE_DEBUG((
                        "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENU: " \
                        "State changed from PendingI to PendingT " \
                        "for session: %s ...", ctx->sessionId));

            return DCCA_CONTEXT_MODIFY;
        }
        else
        {
            DCCA_TRACE_WARNING((
                        "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_PENI: " \
                        "Unsupported command for session: %s ...", ctx->sessionId));

            return DCCA_CONTEXT_ERROR;
        }

    }        

    /**
     * Only CCA with INITIAL is allowed
     */
    if( eve->typ != DCCA_INI_REQUEST && eve->typ != DCCA_TYPE_NOT_SET)
    {
        DCCA_TRACE_WARNING((
                    "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_PENI: " \
                    "Unsupported CCRequestType for session: %s ...", ctx->sessionId));
        if(ctx->timer)
        {
            TIMERS_CancelTimer(ctx->timerkey);
            ctx->timer = 0;
        }

        return DCCA_CONTEXT_ERROR;
    }

    /**
     * Stop the timer Tx
     */
    if(ctx->timer)
    {
        if(ITS_SUCCESS != TIMERS_CancelTimer(ctx->timerkey))
        {
            DCCA_TRACE_DEBUG((
                        "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_PENI: " \
                        "Could not stop timer Tx for session: %s ...", 
                        ctx->sessionId));
        }
        else
        {
            ctx->timer = 0;
            DCCA_TRACE_DEBUG((
                        "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_PENI: " \
                        "Timer Tx stopped for session: %s ...", ctx->sessionId));
        }
    }

    /**
     * Error CCA
     */
    if( eve->cod < DCCA_DIAMETER_SUCCESS_MIN_RANGE || 
            eve->cod > DCCA_DIAMETER_SUCCESS_MAX_RANGE )
    {
        DCCA_TRACE_DEBUG((
                    "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_PENI: " \
                    "State changed from PendingI to Idle " \
                    "for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_REMOVE;
    }

    /**
     * Good CCA and update the context
     */
    ctx->state        = DCCA_FSM_STATE_OPEN;
    ctx->statemachine = DCCA_CLIENT_FSM_FIN;

    DCCA_TRACE_DEBUG((
                "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_PENI: " \
                "State changed from PendingI to Open " \
                "for session: %s ...", ctx->sessionId));

    return DCCA_CONTEXT_MODIFY;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmCcrStateOpen::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    return DCCA_CONTEXT_NONE;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmFinStateIdle::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{    
    return DCCA_CONTEXT_MODIFY;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmFinStatePenU::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    /**
     * Only CCA is allowed
     */
    if( !(!eve->req && eve->cmd == DCCA_COMMAND_CCA) )
    {
        /* Only CCR-T is allowed so that Session can be terminated
         * Cancel the Timer and change the  state to PENT */
        if (eve->typ == DCCA_TER_REQUEST)
        {
            if(ctx->timer)
            {
                if(ITS_SUCCESS != TIMERS_CancelTimer(ctx->timerkey))
                {
                    DCCA_TRACE_DEBUG((
                                "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENU: " \
                                "Could not stop timer Tx for session: %s ...",
                                ctx->sessionId));
                }
                else
                {
                    ctx->timer = 0;
                    DCCA_TRACE_DEBUG((
                                "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENU: " \
                                "Timer Tx stopped for session: %s ...", ctx->sessionId));
                }
            }
            /*
             * Start the timer Tx for CCR-T
            */
            ITS_UINT txTimer = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_TX_TIMER);
            if((ctx->timerkey = TIMERS_StartTimer(
                            ITS_DCCA_SRC, txTimer, (void*)ctx, sizeof(DCCA_CONTEXT))) == 0)
            {
                DCCA_TRACE_WARNING((
                            "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENU: " \
                            "Could not start timer Tx for session: %s ...", ctx->sessionId));

                return DCCA_CONTEXT_ERROR;
            }    
            DCCA_TRACE_DEBUG((
                        "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENU: " \
                        "Timer Tx started for session: %s ...", ctx->sessionId));
            ctx->timer  = DCCA_TIMER_TX_TIME_OUT;
            /**
             * CCR-T update the context
             */
            ctx->state  = DCCA_FSM_STATE_PENT;

            DCCA_TRACE_DEBUG((
                        "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENU: " \
                        "State changed from PendingU to PendingT " \
                        "for session: %s ...", ctx->sessionId));

            return DCCA_CONTEXT_MODIFY;
        }
        else
        {
            DCCA_TRACE_WARNING((
                        "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENU: " \
                        "Unsupported command for session: %s ...", ctx->sessionId));
            return DCCA_CONTEXT_ERROR;
        }
    }
    
    /**
     * Stop the timer Tx
     */
    if(ctx->timer)
    {
        if(ITS_SUCCESS != TIMERS_CancelTimer(ctx->timerkey))
        {
            DCCA_TRACE_DEBUG((
            "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENU: " \
            "Could not stop timer Tx for session: %s ...",
            ctx->sessionId));
        }
        else
        {
            ctx->timer = 0;
            DCCA_TRACE_DEBUG((
            "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENU: " \
            "Timer Tx stopped for session: %s ...", ctx->sessionId));
        }
    }

    /**
     * Error CCA
     */
    if( eve->cod < DCCA_DIAMETER_SUCCESS_MIN_RANGE ||
        eve->cod > DCCA_DIAMETER_SUCCESS_MAX_RANGE )
    {
        DCCA_TRACE_DEBUG((
        "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENU: " \
        "State changed from PendingU to Idle " \
        "for session: %s ...", ctx->sessionId));
        
        /* changes made to send CCR-T incase of Error CCA-U 
         * received specific to RANCORE Customer
         * */
        if( ( DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_RETAIN_SESSION) ) != 0)
        {
            DCCA_TRACE_DEBUG(("DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENU:"\
            "State chaged from PendingU to Open" \
            "for session: %s...", ctx->sessionId));
            ctx->state = DCCA_FSM_STATE_OPEN;
            return DCCA_CONTEXT_MODIFY;
        }
        else
        {
            return DCCA_CONTEXT_REMOVE;
        }
    }
    
    /**
     * Good CCA and update the context
     */
    ctx->state = DCCA_FSM_STATE_OPEN;

    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENU: " \
    "State changed from PendingU to Open " \
    "for session: %s ...", ctx->sessionId));

    return DCCA_CONTEXT_MODIFY;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmFinStatePenT::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    /**
     * Only CCA is allowed
     */
    if( !(!eve->req && eve->cmd == DCCA_COMMAND_CCA) )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_PENT: " \
        "Unsupported command for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }        

    /* Ignore if the CCA-I/CCA-U is received in PendingT state, Ignore it hence
     * message will not be given to application */
    if (eve->typ == DCCA_UPD_REQUEST || eve->typ == DCCA_INI_REQUEST)
    {
        DCCA_TRACE_WARNING((
                    "DCCA: DCCA_CLIENT_FSM_CCR: DCCA_FSM_STATE_PENT:" \
                    "Received CCA-I/U dropping the message"));
        //return DCCA_CONTEXT_NONE;
        return DCCA_CONTEXT_ERROR;
    }

    /**
     * Stop the timer Tx
     */
    if(ctx->timer)
    {
        if(ITS_SUCCESS != TIMERS_CancelTimer(ctx->timerkey))
        {
            DCCA_TRACE_DEBUG((
            "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENT: " \
            "Could not stop timer Tx for session: %s ...",
            ctx->sessionId));
        }
        else
        {
            ctx->timer = 0;
            DCCA_TRACE_DEBUG((
            "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENT: " \
            "Timer Tx stopped for session: %s ...", ctx->sessionId));
        }
    }

    /**
     * Error CCA
     */
    if( eve->cod < DCCA_DIAMETER_SUCCESS_MIN_RANGE ||
        eve->cod > DCCA_DIAMETER_SUCCESS_MAX_RANGE )
    {
        DCCA_TRACE_DEBUG((
        "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENT: " \
        "State changed from PendingT to Idle " \
        "for session: %s ...", ctx->sessionId));

        // Retain the session. Let the context deletion decision be taken by the
        // application. To allow retry of CCR-T to alternate server.
        if( ( DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_RETAIN_SESSION) ) != 0)
        {
            DCCA_TRACE_DEBUG(("DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENT:"\
            "Retain the context" \
            "for session: %s...", ctx->sessionId));
            ctx->state = DCCA_FSM_STATE_OPEN;
            return DCCA_CONTEXT_MODIFY;
        }
        else
        {
            return DCCA_CONTEXT_REMOVE;
        }
    }
   
    ITS_INT res = DCCA_CONTEXT_REMOVE;
    /**
     * Good CCA and update the context
     */
    if( ( DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_RETAIN_SESSION) ) != 0)
    {
        DCCA_TRACE_DEBUG(("DCCA: PendingT to Open for session %s", 
                        ctx->sessionId));
        ctx->state = DCCA_FSM_STATE_OPEN;
        res = DCCA_CONTEXT_MODIFY;
    }
    else
    {
        ctx->state = DCCA_FSM_STATE_IDLE;
        DCCA_TRACE_DEBUG((
                    "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_PENT: " \
                    "State changed from PendingT to Idle " \
                    "for session: %s ...", ctx->sessionId));
    }


    return res;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmFinStateOpen::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{        
    /**
     * Only CCR is allowed
     */
    if( !(eve->req && eve->cmd == DCCA_COMMAND_CCR) )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_OPEN: " \
        "Unsupported command for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }

    /**
     * Only CCR with UPDATE or TERMINATION is allowed
     */
    if( eve->typ != DCCA_UPD_REQUEST && eve->typ != DCCA_TER_REQUEST )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_OPEN: " \
        "Unsupported CCRequestType for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }

    /**
     * Start the timer Tx for both CCR-U and T
     */    
    ITS_UINT txTimer = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_TX_TIMER);     
    if((ctx->timerkey = TIMERS_StartTimer(
                    ITS_DCCA_SRC, txTimer, (void*)ctx, sizeof(DCCA_CONTEXT))) == 0)
    {
        DCCA_TRACE_WARNING((
                    "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_OPEN: " \
                    "Could not start timer Tx for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }
    DCCA_TRACE_DEBUG((
                "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_OPEN: " \
                "Timer Tx started for session: %s ...", ctx->sessionId));
    ctx->timer  = DCCA_TIMER_TX_TIME_OUT;

    /**
     * Good CCR with UPDATE
     */
    if( eve->typ == DCCA_UPD_REQUEST )
    {
        /**
         * Update the context
         */        
        ctx->state  = DCCA_FSM_STATE_PENU;

        DCCA_TRACE_DEBUG((
        "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_OPEN: " \
        "State changed from Open to PendingU " \
        "for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_MODIFY;
    }
    
    /**
     * Good CCR with TERMINATION and so update the context
     */
    ctx->state  = DCCA_FSM_STATE_PENT;

    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_CLIENT_FSM_FIN: DCCA_FSM_STATE_OPEN: " \
    "State changed from Open to PendingT " \
    "for session: %s ...", ctx->sessionId));

    return DCCA_CONTEXT_MODIFY;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmEveStateIdle::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    /**
     * Only CCR is allowed
     */
    if( !(eve->req && eve->cmd == DCCA_COMMAND_CCR) )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_EVE: DCCA_FSM_STATE_IDLE: " \
        "Unsupported command for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }        

    /**
     * Only CCR with EVENT is allowed
     */
    if( eve->typ != DCCA_EVE_REQUEST )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_EVE: DCCA_FSM_STATE_IDLE: " \
        "Unsupported CCRequestType for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }

    /**
     * Start the timer Tx
     */    
    ITS_UINT txTimer = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_TX_TIMER);
    if((ctx->timerkey = TIMERS_StartTimer(
    ITS_DCCA_SRC, txTimer, (void*)ctx, sizeof(DCCA_CONTEXT))) == 0)
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_EVE: DCCA_FSM_STATE_IDLE: " \
        "Could not start timer Tx for session: %s ...", ctx->sessionId));
        
        return DCCA_CONTEXT_ERROR;
    }
    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_CLIENT_FSM_EVE: DCCA_FSM_STATE_IDLE: " \
    "Timer Tx started for session: %s ...", ctx->sessionId));

    /**
     * Update the context
     */    
    ctx->state  = DCCA_FSM_STATE_PENE;
    ctx->timer  = DCCA_TIMER_TX_TIME_OUT;

    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_CLIENT_FSM_EVE: DCCA_FSM_STATE_IDLE: " \
    "State changed from Idle to PendingE " \
    "for session: %s ...", ctx->sessionId));

    return DCCA_CONTEXT_MODIFY;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmEveStatePenB::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    return DCCA_CONTEXT_NONE;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAClientFsmEveStatePenE::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    /**
     * Only CCA or ERR is allowed
     */
    if( !(!eve->req && eve->cmd == DCCA_COMMAND_CCA) )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_CLIENT_FSM_EVE: DCCA_FSM_STATE_PENE: " \
        "Unsupported command for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }
    
    /**
     * Stop the timer Tx
     */
    if( ctx->timer )
    {
        if(ITS_SUCCESS != TIMERS_CancelTimer(ctx->timerkey))
        {
            DCCA_TRACE_DEBUG((
            "DCCA: DCCA_CLIENT_FSM_EVE: DCCA_FSM_STATE_PENE: " \
            "Could not stop timer Tx for session: %s ...", 
            ctx->sessionId));
        }
        else
        {
            ctx->timer = 0;
            DCCA_TRACE_DEBUG((
            "DCCA: DCCA_CLIENT_FSM_EVE: DCCA_FSM_STATE_PENE: " \
            "Timer Tx stopped for session: %s ...", ctx->sessionId));
        }
    }

    /**
     * Diameter base protocol error or error CCA
     */
    if( eve->cod < DCCA_DIAMETER_SUCCESS_MIN_RANGE || 
        eve->cod > DCCA_DIAMETER_SUCCESS_MAX_RANGE )
    {
        DCCA_TRACE_DEBUG((
        "DCCA: DCCA_CLIENT_FSM_EVE: DCCA_FSM_STATE_PENE: " \
        "State changed from PendingE to Idle " \
        "for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_REMOVE;
    }
    
    /**
     * Good CCA and update the context
     */
    ctx->state = DCCA_FSM_STATE_IDLE;

    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_CLIENT_FSM_EVE: DCCA_FSM_STATE_PENE: " \
    "State changed from PendingE to Idle " \
    "for session: %s ...", ctx->sessionId));

    return DCCA_CONTEXT_REMOVE;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAServerFsmSesStateIdle::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{    
    /**
     * Only CCR or CCA or ERR is allowed
     */
    if( !(eve->req && eve->cmd == DCCA_COMMAND_CCR) &&
        !(!eve->req && eve->cmd == DCCA_COMMAND_CCR) )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_IDLE: " \
        "Unsupported command for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;        
    }
    
    /**
     * Good CCR and update the context
     */
    if( eve->req && eve->cmd == DCCA_COMMAND_CCR )
    {
        return DCCA_CONTEXT_NONE;
    }

    /**
     * Only CCA with INITIAL is allowled
     */
    if( eve->typ != DCCA_INI_REQUEST )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_IDLE: " \
        "Unsupported CCRequestType for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }

    /**
     * Error CCA
     */
    if( eve->cod < DCCA_DIAMETER_SUCCESS_MIN_RANGE ||
        eve->cod > DCCA_DIAMETER_SUCCESS_MAX_RANGE )
    {
        DCCA_TRACE_DEBUG((
        "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_IDLE: " \
        "State changed from Idle to Idle " \
        "for session: %s ...", ctx->sessionId));
        return DCCA_CONTEXT_REMOVE;
    }
    
    /**
     * Good CCA and start the timer Tcc
     */    
    ITS_UINT tccTimer = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_TCC_TIMER);
    if((ctx->timerkey = TIMERS_StartTimer(
    ITS_DCCA_SRC, tccTimer, (void*)ctx, sizeof(DCCA_CONTEXT))) == 0)
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_IDLE: " \
        "Could not start timer Tcc for session: %s ...", ctx->sessionId));
        
        return DCCA_CONTEXT_ERROR;
    }
    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_IDLE: " \
    "Timer Tcc started for session: %s ...", ctx->sessionId));

    /**
     * Update the context
     */
    ctx->state        = DCCA_FSM_STATE_OPEN;    
    ctx->timer        = DCCA_TIMER_TCC_TIME_OUT;

    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_IDLE: " \
    "State changed from Idle to Open " \
    "for session: %s ...", ctx->sessionId));

    return DCCA_CONTEXT_MODIFY;
}

/****************************************************************************
 *
 *  Purpose                : To process an event in this state
 *
 *  Input Parameters       : eve - The event to process
 *                           ctx - The context associated with this event
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The context action
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAServerFsmSesStateOpen::SubmitToState(
DCCA_EVENT *eve, DCCA_CONTEXT *ctx)
{
    /**
     * Only CCR or CCA or ERR is allowed
     */
    if( !(eve->req && eve->cmd == DCCA_COMMAND_CCR) &&
        !(!eve->req && eve->cmd == DCCA_COMMAND_CCR) )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_OPEN: " \
        "Unsupported command for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;        
    }
    
    /**
     * Good CCR and update the context
     */
    if( eve->req && eve->cmd == DCCA_COMMAND_CCR )
    {
        return DCCA_CONTEXT_NONE;
    }
    
    /**
     * Only CCA with UPDATE or TERMINATION is allowled
     */
    if( eve->typ != DCCA_UPD_REQUEST && eve->typ != DCCA_TER_REQUEST )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_OPEN: " \
        "Unsupported CCRequestType for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_ERROR;
    }    

    /**
     * Stop the timer Tcc
     */
    if( ctx->timer )
    {
        if(ITS_SUCCESS != TIMERS_CancelTimer(ctx->timerkey))
        {
            DCCA_TRACE_DEBUG((
            "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_OPEN: " \
            "Could not stop timer Tcc for session: %s ...",
            ctx->sessionId));
        }
        else
        {
            ctx->timer = 0;
            DCCA_TRACE_DEBUG((
            "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_OPEN: " \
            "Timer Tcc stopped for session: %s ...", ctx->sessionId));
        }
    }

    /**
     * Error CCA or good CCA with TERMINATION
     */
    if( eve->typ == DCCA_TER_REQUEST ||
        (eve->cod < DCCA_DIAMETER_SUCCESS_MIN_RANGE ||
         eve->cod > DCCA_DIAMETER_SUCCESS_MAX_RANGE) )
    {
        DCCA_TRACE_DEBUG((
        "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_OPEN: " \
        "State changed from Open to Idle " \
        "for session: %s ...", ctx->sessionId));

        return DCCA_CONTEXT_REMOVE;
    }

    /**
     * Good CCA with UPDATE and so restart the timer Tcc
     */    
    ITS_UINT tccTimer = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_TCC_TIMER);
    if((ctx->timerkey = TIMERS_StartTimer(
    ITS_DCCA_SRC, tccTimer, (void*)ctx, sizeof(DCCA_CONTEXT))) == 0)
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_OPEN: " \
        "Could not start timer Tcc for session: %s ...", ctx->sessionId));
        
        return DCCA_CONTEXT_ERROR;
    }
    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_OPEN: " \
    "Timer Tcc re-started for session: %s ...", ctx->sessionId));

    DCCA_TRACE_DEBUG((
    "DCCA: DCCA_SERVER_FSM_SES: DCCA_FSM_STATE_OPEN: " \
    "State changed from Open to Open " \
    "for session: %s ...", ctx->sessionId));

    ctx->timer = DCCA_TIMER_TCC_TIME_OUT;

    return DCCA_CONTEXT_MODIFY;
}
