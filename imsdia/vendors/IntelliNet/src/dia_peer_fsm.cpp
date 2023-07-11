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
 * LOG: $Log: dia_peer_fsm.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * LOG:
 *
 * ID: $Id: dia_peer_fsm.cpp,v 3.1 2008/03/31 10:33:32 nvijikumar Exp $
 ****************************************************************************/
 #ident "$Id: dia_peer_fsm.cpp,v 3.1 2008/03/31 10:33:32 nvijikumar Exp $"


/**
 * Includes
 */

#include <dia_trace.h>

#include <dia_peer_fsm.h>
#include <dia_peer_table.h>

using namespace its;
using namespace std;

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
PeerFsm::PeerFsm():DiaSM(PEER_FSM)
{
    /**
     * Add PEER state handlers to PEER statemachine
     **/
    states.assign(PEER_ST_MAX, NULL);
    AddStateToStateMachine(new Closed(PEER_ST_CLOSED));
    AddStateToStateMachine(new WaitConnAck(PEER_ST_WAIT_CONN_ACK));
    AddStateToStateMachine(new WaitICEA(PEER_ST_WAIT_I_CEA));
    AddStateToStateMachine(new WaitConnAckElect(PEER_ST_WAIT_CONN_ACK_ELECT));
    AddStateToStateMachine(new IOpen(PEER_ST_I_OPEN));
    AddStateToStateMachine(new WaitReturns(PEER_ST_WAIT_RETURNS));
    AddStateToStateMachine(new ROpen(PEER_ST_R_OPEN));
    AddStateToStateMachine(new Closing(PEER_ST_CLOSING));
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
PeerFsm::~PeerFsm()
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
 *      Add states to the Peer State Machine.
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
PeerFsm::AddStateToStateMachine(DiaState *st)
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
 *      Submit to Peer State machine.
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      void *vctxt, ITS_EVENT *evt.
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
PeerFsm::SubmitToSM(void *vctxt, ITS_EVENT *evt)
{
    PEER_STATE_CTXT* ctxt = (PEER_STATE_CTXT*)vctxt;

    if(states[ctxt->pEntry->statusT])
    {
        return (states[ctxt->pEntry->statusT])->ProcessEvent(ctxt, evt);
    }
    else
    {
        DT_ERR((" Failed to Process the given state "));
        return !ITS_SUCCESS; 
    }
}



