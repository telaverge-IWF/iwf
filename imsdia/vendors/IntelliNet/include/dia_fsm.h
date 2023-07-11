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
 * LOG: $Log: dia_fsm.h,v $
 * LOG: Revision 3.3  2009/03/19 16:23:08  ssaxena
 * LOG: Modification done to add Redirect Agent Application.
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:20:01  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2006/10/24 14:19:09  yranade
 * LOG: Minor updates.
 * LOG:
 * LOG: Revision 2.3  2006/10/05 13:00:22  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.2  2006/09/14 09:35:21  nvijikumar
 * LOG: Added TO_TEXT macro.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * LOG:
 *
 * ID: $Id: dia_fsm.h,v 3.3 2009/03/19 16:23:08 ssaxena Exp $
 ****************************************************************************/
#ident "$Id: dia_fsm.h,v 3.3 2009/03/19 16:23:08 ssaxena Exp $"

#ifndef DIA_STATE_MACHINE_H
#define DIA_STATE_MACHINE_H

#include <its++.h>

/* NOTE: Start off with 2, as 
   ITS_SUCCESS and !ITS_SUCCESS are 0 and 1
   respectively
*/
enum
{
    FSM_STATE_UPDATE = 2,
    FSM_NO_STATE_UPDATE
};

#define STATE_MACHINE_TYPE_TO_TEXT(x) \
    ((x==PEER_FSM)                       ? "PEER_FSM"                      : \
    ((x==STATEFUL_CLIENT_AUTH_FSM)       ? "STATEFUL_CLIENT_AUTH_FSM"      : \
    ((x==STATEFUL_SERVER_AUTH_FSM)       ? "STATEFUL_SERVER_AUTH_FSM"      : \
    ((x==STATELESS_CLIENT_AUTH_FSM)      ? "STATELESS_CLIENT_AUTH_FSM"     : \
    ((x==STATELESS_SERVER_AUTH_FSM)      ? "STATELESS_SERVER_AUTH_FSM"     : \
    ((x==STATEFUL_SERVER_ACCT_FSM)       ? "STATEFUL_SERVER_ACCT_FSM"      : \
    ((x==STATELESS_SERVER_ACCT_FSM)      ? "STATELESS_SERVER_ACCT_FSM"     : \
    ((x==CLIENT_ACCT_FSM)                ? "CLIENT_ACCT_FSM"               : \
    ((x==STATEFUL_SERVER_AUTH_PXY_FSM)   ? "STATEFUL_SERVER_AUTH_PXY_FSM"  : \
    ((x==STATELESS_SERVER_AUTH_PXY_FSM)  ? "STATELESS_SERVER_AUTH_PXY_FSM" : \
    ((x==STATEFUL_SERVER_ACCT_PXY_FSM)   ? "STATEFUL_SERVER_ACCT_PXY_FSM"  : \
    ((x==STATELESS_SERVER_ACCT_PXY_FSM)  ? "STATELESS_SERVER_ACCT_PXY_FSM" : \
    ((x==RELAY_AGENT_FSM)                ? "RELAY_AGENT_FSM"               : \
    "INVALID")))))))))))))

typedef enum 
{
    PEER_FSM = 0,
    /*
     * Client / Server Handling
     */
    STATEFUL_CLIENT_AUTH_FSM,
    STATEFUL_SERVER_AUTH_FSM,
    STATELESS_CLIENT_AUTH_FSM,
    STATELESS_SERVER_AUTH_FSM,
    STATEFUL_SERVER_ACCT_FSM,
    STATELESS_SERVER_ACCT_FSM,
    CLIENT_ACCT_FSM,
    /*
     * Proxy Handling
     */
    STATEFUL_SERVER_AUTH_PXY_FSM,
    STATELESS_SERVER_AUTH_PXY_FSM,
    STATEFUL_SERVER_ACCT_PXY_FSM,
    STATELESS_SERVER_ACCT_PXY_FSM,
    /*
     * Relay Handling
     */
    RELAY_AGENT_FSM,
    /*
     * Redirect Handling
     */
    REDIRECT_AGENT_FSM
}STATE_MACHINE_TYPE;

/****************************************************************************
 *  Interface:
 *      DiaSM Class
 *
 *  Purpose:
 *      To implement DiaSM Base class and all State Machines derives from
 *      This Class.
 *
 *
 ****************************************************************************/
class DiaSM
{
public:
    /**
     * Constructor.
     */
    DiaSM(STATE_MACHINE_TYPE stMacType)
    {
        type = stMacType;
    }
    /**
     * Method to Get the machine type.
     */
    STATE_MACHINE_TYPE GetStateMachine()
    {
       return type;
    }
    /**
     * Distructor.
     */
    virtual ~DiaSM(){}
    /**
     * Method to Submit the event to State machine.
     */
    virtual int SubmitToSM(void *ctxt, ITS_EVENT *evt=0)=0;

private:
    STATE_MACHINE_TYPE type;
};

/****************************************************************************
 *  Interface:
 *      DiaState Class
 *
 *  Purpose:
 *      To implement DiaState Base(abstract) class.
 *
 *
 ****************************************************************************/
class DiaState
{
public:
    /**
     * Constructor.
     */
    DiaState(ITS_OCTET statId):stateId(statId){}
    /**
     * Method to Process the event in the state machine.
     */
    virtual int ProcessEvent(void *ctxt, ITS_EVENT *evt)=0;
    /**
     * Method to Get the State Id.
     */
    ITS_OCTET GetStateID() const
    {
       return stateId;
    }

private:
    ITS_OCTET stateId;
};

#endif  //DIA_STATE_MACHINE_H
