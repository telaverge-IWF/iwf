/*********************************-*-CPP*-***********************************
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
 * LOG: $Log: dia_session_auth_fsm.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.2  2006/10/09 11:32:17  yranade
 * LOG: Add missing states.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * LOG:
 *
 * ID: $Id: dia_session_auth_fsm.cpp,v 3.1 2008/03/31 10:33:32 nvijikumar Exp $
 ****************************************************************************/
 #ident "$Id: dia_session_auth_fsm.cpp,v 3.1 2008/03/31 10:33:32 nvijikumar Exp $"


/**
 * Includes
 */

#include <dia_trace.h>
#include <dia_session_auth_fsm.h>
#include <dia_session_table.h>


#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

StatefulServerAuthFsm statefulServerAuthFsm;
StatefulClientAuthFsm statefulClientAuthFsm;
StatelessClientAuthFsm statelessClientAuthFsm;


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
StatefulServerAuthFsm::StatefulServerAuthFsm():DiaSM(STATEFUL_SERVER_AUTH_FSM)
{
    /**
     * Add states handler to the Stateful ServerAuth state machine.
     */
    states.assign(SESSION_ST_MAX, NULL);
    AddStateToStateMachine(new 
                           StatefulServerAuthFsm_Idle(AUTH_SESSION_ST_IDLE));
    AddStateToStateMachine(new 
                          StatefulServerAuthFsm_Open(AUTH_SESSION_ST_OPEN));
    AddStateToStateMachine(new 
                          StatefulServerAuthFsm_Discon(AUTH_SESSION_ST_DISCON));
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
StatefulServerAuthFsm::~StatefulServerAuthFsm()
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
 *      Add states to the StatefulServerAuth State Machine.
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
StatefulServerAuthFsm::AddStateToStateMachine(DiaState *st)
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
 *      Submit to Stateful Server Auth State machine.
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
StatefulServerAuthFsm::SubmitToSM(void *vctxt, ITS_EVENT *evt)
{
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;

    if(states[DIA_SE_STATE(ctxt)])
    {
        return states[DIA_SE_STATE(ctxt)]->ProcessEvent(ctxt, evt);
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
StatefulClientAuthFsm::StatefulClientAuthFsm():DiaSM(STATEFUL_CLIENT_AUTH_FSM)
{
    /**
     * Add states handler to the Stateful ClientAuth state machine.
     */
    states.assign(SESSION_ST_MAX, NULL);
    AddStateToStateMachine(new 
                           StatefulClientAuthFsm_Idle(AUTH_SESSION_ST_IDLE));
    AddStateToStateMachine(new 
                     StatefulClientAuthFsm_Pending(AUTH_SESSION_ST_PENDING));
    AddStateToStateMachine(new 
                           StatefulClientAuthFsm_Open(AUTH_SESSION_ST_OPEN));
    AddStateToStateMachine(new 
                       StatefulClientAuthFsm_Discon(AUTH_SESSION_ST_DISCON));
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
StatefulClientAuthFsm::~StatefulClientAuthFsm()
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
 *      Add states to the StatefulClientAuth State Machine.
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
StatefulClientAuthFsm::AddStateToStateMachine(DiaState *st)
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
 *      Submit to Stateful Client Auth State machine.
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
StatefulClientAuthFsm::SubmitToSM(void *vctxt, ITS_EVENT *evt)
{
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;
    if(states[DIA_SE_STATE(ctxt)])
    {
        return states[DIA_SE_STATE(ctxt)]->ProcessEvent(ctxt, evt);
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
StatelessClientAuthFsm::StatelessClientAuthFsm():
                                          DiaSM(STATELESS_CLIENT_AUTH_FSM)
{
    /**
     * Add states handler to the Stateless ClientAuth state machine.
     */
    states.assign(SESSION_ST_MAX, NULL);
    AddStateToStateMachine(new 
                           StatelessClientAuthFsm_Idle(AUTH_SESSION_ST_IDLE));
    AddStateToStateMachine(new 
                           StatelessClientAuthFsm_Pending(AUTH_SESSION_ST_PENDING));
    AddStateToStateMachine(new 
                           StatelessClientAuthFsm_Open(AUTH_SESSION_ST_OPEN));
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
StatelessClientAuthFsm::~StatelessClientAuthFsm()
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
 *      Add states to the StatelessClientAuth State Machine.
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
StatelessClientAuthFsm::AddStateToStateMachine(DiaState *st)
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
 *      Submit to Stateless Client Auth State machine.
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
StatelessClientAuthFsm::SubmitToSM(void *vctxt, ITS_EVENT *evt)
{
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;
    if(states[DIA_SE_STATE(ctxt)])
    {
        return states[DIA_SE_STATE(ctxt)]->ProcessEvent(ctxt, evt);
    }
    else
    {
        DT_ERR((" Failed to Process the given state "));
        return !ITS_SUCCESS;
    }

}



