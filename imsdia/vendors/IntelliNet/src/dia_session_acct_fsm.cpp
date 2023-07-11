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
 * LOG: $Log: dia_session_acct_fsm.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2007/01/04 11:20:20  nvijikumar
 * LOG: Changes: seperate fsmType and sState for Accounting SM.
 * LOG:
 * LOG: Revision 2.2  2006/10/16 16:56:43  nvijikumar
 * LOG: Baseline Accounting Statemachine implementation.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * LOG:
 *
 * ID: $Id: dia_session_acct_fsm.cpp,v 3.1 2008/03/31 10:33:32 nvijikumar Exp $
 ****************************************************************************/
 #ident "$Id: dia_session_acct_fsm.cpp,v 3.1 2008/03/31 10:33:32 nvijikumar Exp $"


/**
 * Includes
 */

#include <dia_trace.h>

#include <dia_session_acct_fsm.h>


#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

ClientAcctFsm clientAcctFsm;
StatefulServerAcctFsm statefulServerAcctFsm;

/****************************************************************************
 *  Purpose:
 *        Constructor.
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
 *        None.
 *  
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
StatefulServerAcctFsm::StatefulServerAcctFsm():DiaSM(STATEFUL_SERVER_ACCT_FSM)
{
    /**
     * Add states handler to the Stateful ServerAcct state machine.
     */
    states.assign(SESSION_ST_MAX, NULL);
    AddStateToStateMachine(new 
                           StatefulServerAcctFsm_Idle(ACCT_SESSION_ST_IDLE));
    AddStateToStateMachine(new 
                          StatefulServerAcctFsm_Open(ACCT_SESSION_ST_OPEN));
}

/****************************************************************************
 *  Purpose:
 *        Destructor
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
 *        None.
 *  
 *  Notes:
 *        None.
 *  
 *  See Also:
 *        None
 *
 ****************************************************************************/
StatefulServerAcctFsm::~StatefulServerAcctFsm()
{
   std::vector<DiaState*>::iterator it = states.begin();
    for(; it !=states.end();++it)
    {
        if(*it)
        {
            delete (*it);
        }
    }
}

/********************************************************************/
/** Purpose:
 *      Add states to the StatefulServerAccth State Machine.
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      DiaState *st.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for Sucessful.
 *
 *  Notes:
 *      None
 *
 *  See Also:
 *      None
 *
 **/
 /* Revision History:
 *
 *********************************************************************/
int 
StatefulServerAcctFsm::AddStateToStateMachine(DiaState *st)
{
    if(states.size())
    {
        states[st->GetStateID()]=st;
        return ITS_SUCCESS;
    }
    return !ITS_SUCCESS;
}

/********************************************************************/
/** Purpose:
 *      Submit to Stateful Server Acct State machine.
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      void *vctxt, ITS_EVENT *evt
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for Sucessful.
 *
 *  Notes:
 *      None
 *
 *  See Also:
 *      None
 *
 **/
 /* Revision History:
 *
 *********************************************************************/
int 
StatefulServerAcctFsm::SubmitToSM(void *vctxt, ITS_EVENT *evt)
{
    SESSION_ENTRY* ctxt = (SESSION_ENTRY *)vctxt;

    if(states[DIA_SE_ACC_STATE(ctxt)])
    {
        return states[DIA_SE_ACC_STATE(ctxt)]->ProcessEvent(ctxt, evt);
    }
    else
    {
        DT_ERR((" Failed to Process the given state "));
        return !ITS_SUCCESS;
    }

}

/****************************************************************************
 *  Purpose:
 *        Constructor.
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
 *        None.
 *  
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ClientAcctFsm::ClientAcctFsm():DiaSM(CLIENT_ACCT_FSM)
{
    /**
     * Add states handler to the ClientAcct state machine.
     */
    states.assign(SESSION_ST_MAX, NULL);
    AddStateToStateMachine(new ClientAcctFsm_Idle(ACCT_SESSION_ST_IDLE));
    AddStateToStateMachine(new ClientAcctFsm_Open(ACCT_SESSION_ST_OPEN));
    AddStateToStateMachine(new 
                     ClientAcctFsm_Pending_S(ACCT_SESSION_ST_PENDING_S));
    AddStateToStateMachine(new 
                     ClientAcctFsm_Pending_E(ACCT_SESSION_ST_PENDING_E));
    AddStateToStateMachine(new 
                     ClientAcctFsm_Pending_B(ACCT_SESSION_ST_PENDING_B));
    AddStateToStateMachine(new 
                     ClientAcctFsm_Pending_I(ACCT_SESSION_ST_PENDING_I));
    AddStateToStateMachine(new 
                     ClientAcctFsm_Pending_L(ACCT_SESSION_ST_PENDING_L));
}

/****************************************************************************
 *  Purpose:
 *        Destructor
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
 *        None.
 *  
 *  Notes:
 *        None.
 *  
 *  See Also:
 *        None
 *
 ****************************************************************************/
ClientAcctFsm::~ClientAcctFsm()
{
    std::vector<DiaState*>::iterator it = states.begin();
    for(; it !=states.end();++it)
    {
        if(*it)
        {
            delete (*it);
        }
    }
}

/********************************************************************/
/** Purpose:
 *      Add states to the Client Accounting State Machine.
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      DiaState *st.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for Sucessful.
 *
 *  Notes:
 *      None
 *
 *  See Also:
 *      None
 *
 **/
 /* Revision History:
 *
 *********************************************************************/
int 
ClientAcctFsm::AddStateToStateMachine(DiaState *st)
{
    if(states.size())
    {
        states[st->GetStateID()]=st;
        return ITS_SUCCESS;
    }
    return !ITS_SUCCESS;
}
/********************************************************************/
/** Purpose:
 *      Submit to Client Accounting State machine.
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      void *vctxt, ITS_EVENT *evt
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for Sucessful.
 *
 *  Notes:
 *      None
 *
 *  See Also:
 *      None
 *
 **/
 /* Revision History:
 *
 *********************************************************************/
int 
ClientAcctFsm::SubmitToSM(void *vctxt, ITS_EVENT *evt)
{
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;
    if (states[DIA_SE_ACC_STATE(ctxt)])
    {
        return states[DIA_SE_ACC_STATE(ctxt)]->ProcessEvent(ctxt, evt);
    }
    else
    {
        DT_ERR((" Failed to Process the given state "));
        return !ITS_SUCCESS;
    }

}



