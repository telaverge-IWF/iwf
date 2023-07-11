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
 * LOG: $Log: dia_session_acct_fsm.h,v $
 * LOG: Revision 3.3  2010/10/11 05:08:57  nvijikumar
 * LOG: Motorola's changes incorporation for field compilation issue
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:14:26  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.5  2007/01/16 07:18:55  nvijikumar
 * LOG: Fix for PBN Bug Id 5175.
 * LOG:
 * LOG: Revision 2.4  2006/10/16 16:51:21  nvijikumar
 * LOG: Baseline Accounting implementation.
 * LOG:
 * LOG: Revision 2.3  2006/09/20 13:47:56  nvijikumar
 * LOG: Changes to take State ID has states vector Index.
 * LOG:
 * LOG: Revision 2.2  2006/09/14 09:40:21  nvijikumar
 * LOG: Added TO_TEXT macro for Event enum.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * LOG:
 *
 * ID: $Id: dia_session_acct_fsm.h,v 3.3 2010/10/11 05:08:57 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: dia_session_acct_fsm.h,v 3.3 2010/10/11 05:08:57 nvijikumar Exp $"


#if !defined DIA_SESSION_ACCT_FSM_H
#define DIA_SESSION_ACCT_FSM_H

/**
 * Includes
 */
#include <iostream>
#include <dia_fsm.h>
#include <dia_session_table.h>

#define ACCT_SESSION_EVENT_TO_TEXT(x) \
    ((x==ACCT_SESSION_EVT_REQUEST_ACCESS)? "ACCT_SESSION_EVT_REQUEST_ACCESS" : \
    ((x==ACCT_SESSION_EVT_REQUEST_ONETIME_ACCESS)? "ACCT_SESSION_EVT_REQUEST_ONETIME_ACCESS" : \
    ((x==ACCT_SESSION_EVT_REC_IN_STORAGE)? "ACCT_SESSION_EVT_REC_IN_STORAGE" : \
    ((x==ACCT_SESSION_EVT_FTS_NOT_DAG)   ? "ACCT_SESSION_EVT_FTS_NOT_DAG"    : \
    ((x==ACCT_SESSION_EVT_FTS_NOT_GAL)   ? "ACCT_SESSION_EVT_FTS_NOT_GAL"    : \
    ((x==ACCT_SESSION_EVT_FTS_AND_GAL)   ? "ACCT_SESSION_EVT_FTS_AND_GAL"    : \
    ((x==ACCT_SESSION_EVT_RX_ACA_FAIL_AND_GAL)? "ACCT_SESSION_EVT_RX_ACA_FAIL_AND_GAL" : \
    ((x==ACCT_SESSION_EVT_RX_ACA_FAIL_NOT_GAL)? "ACCT_SESSION_EVT_RX_ACA_FAIL_NOT_GAL" : \
    ((x==ACCT_SESSION_EVT_STOP)          ? "ACCT_SESSION_EVT_STOP"           : \
    ((x==ACCT_SESSION_EVT_INT_EXPIRE)    ? "ACCT_SESSION_EVT_INT_EXPIRE"     : \
    ((x==ACCT_SESSION_EVT_RX_ACA_OK)     ? "ACCT_SESSION_EVT_RX_ACA_OK"      : \
    ((x==ACCT_SESSION_EVT_FTS_BUF)       ? "ACCT_SESSION_EVT_FTS_BUF"        : \
    ((x==ACCT_SESSION_EVT_FTS_NO_BUF)    ? "ACCT_SESSION_EVT_FTS_NO_BUF"     : \
    ((x==ACCT_SESSION_EVT_RX_ACA_FAIL)   ? "ACCT_SESSION_EVT_RX_ACA_FAIL"    : \
    ((x==ACCT_SESSION_EVT_FTS)           ? "ACCT_SESSION_EVT_FTS"            : \
    ((x==ACCT_SESSION_EVT_RX_ACR_START_OK)? "ACCT_SESSION_EVT_RX_ACR_START_OK" : \
    ((x==ACCT_SESSION_EVT_RX_ACR_EV_OK)  ? "ACCT_SESSION_EVT_RX_ACR_EV_OK"   : \
    ((x==ACCT_SESSION_EVT_RX_ACR_INT_OK) ? "ACCT_SESSION_EVT_RX_ACR_INT_OK"  : \
    ((x==ACCT_SESSION_EVT_RX_ACR_STOP_OK)? "ACCT_SESSION_EVT_RX_ACR_STOP_OK" : \
    ((x==ACCT_SESSION_EVT_RX_ACR_NO_BUF) ? "ACCT_SESSION_EVT_RX_ACR_NO_BUF"  : \
    ((x==ACCT_SESSION_EVT_SESSION_TOUT)  ? "ACCT_SESSION_EVT_SESSION_TOUT"   : \
    ((x==ACCT_SESSION_EVT_RX_ACR_FAIL)   ? "ACCT_SESSION_EVT_RX_ACR_FAIL"    : \
    ((x==ACCT_SESSION_EVT_MAX)           ? "ACCT_SESSION_EVT_MAX"            : \
    ((x==ACCT_SESSION_EVT_ACCESS_TX_AGENT)  ? "ACCT_SESSION_EVT_ACCESS_TX_AGENT" : \
    ((x==ACCT_SESSION_EVT_ACCESS_RX_AGENT)  ? "ACCT_SESSION_EVT_ACCESS_RX_AGENT" : \
    "INVALID")))))))))))))))))))))))))


typedef enum 
{
    ACCT_SESSION_EVT_REQUEST_ACCESS,          /* Client or device requests 
                                                 access */

    ACCT_SESSION_EVT_ACCESS_TX_AGENT,    /* Request coming from application
                                                 for agent sesssions*/  

    ACCT_SESSION_EVT_ACCESS_RX_AGENT,    /* Answer coming from peer  
                                                 for agent sesssions*/  

    ACCT_SESSION_EVT_REQUEST_ONETIME_ACCESS,  /* Client or device requests
                                                 a one-time service */

    ACCT_SESSION_EVT_REC_IN_STORAGE,          /* Records in storage */

   
    ACCT_SESSION_EVT_FTS_NOT_DAG,             /* Failure to send and buffer
                                                 space available and realtime 
                                                 not equal to DELIVER_AND_GRANT
                                               */
                                              /* Failure to send and (buffer 
                                                 space available or old record 
                                                 can be overwritten) and real
                                                 time not equal to            
                                                 DELIVER_AND_GRANT */

    ACCT_SESSION_EVT_FTS_NOT_GAL,             /* Failure to send and no buffer
                                                 space available and realtime
                                                 not equal to GRANT_AND_LOSE */

    ACCT_SESSION_EVT_FTS_AND_GAL,             /* Failure to send and no buffer
                                                 space available and realtime
                                                 equal to GRANT_AND_LOSE */

    ACCT_SESSION_EVT_RX_ACA_FAIL_AND_GAL,     /* Failed accounting start answer
                                                 received and realtime equal
                                                 to GRANT_AND_LOSE */
                                              /* Failed accounting interim 
                                                 answer received and realtime
                                                 equal to GRANT_AND_LOSE */

    ACCT_SESSION_EVT_RX_ACA_FAIL_NOT_GAL,     /* Failed accounting start answer
                                                 received and realtime not equal
                                                 to GRANT_AND_LOSE */
                                              /* Failed accounting interim 
                                                 answer received and realtime
                                                 not equal to GRANT_AND_LOSE */

    ACCT_SESSION_EVT_STOP,                    /* User service terminated */

    ACCT_SESSION_EVT_INT_EXPIRE,              /* Interim interval elapses */

    ACCT_SESSION_EVT_RX_ACA_OK,               /* Successful accounting interim
                                                 answer received */
                                              /* Successful accounting event
                                                 answer received */
                                              /* Successful accounting stop
                                                 answer received */

    ACCT_SESSION_EVT_FTS_BUF,                 /* Failure to send and buffer
                                                 space available */
                                              /* Failure to send and buffer
                                                 Idle space available */

    ACCT_SESSION_EVT_FTS_NO_BUF,              /* Failure to send and no buffer
                                                 space available */

    ACCT_SESSION_EVT_RX_ACA_FAIL,             /* Failed accounting event answer
                                                 received */
                                              /* Failed accounting answer 
                                                 received */
                                              /* Failed accounting stop answer 
                                                 received */

    ACCT_SESSION_EVT_FTS,                     /* Failure to send */

    ACCT_SESSION_EVT_RX_ACR_START_OK,         /* Accounting start request
                                                 received, and successfully
                                                 processed. */
                                              /* Successful accounting start
                                                 received */

    ACCT_SESSION_EVT_RX_ACR_EV_OK,            /* Accounting event request 
                                                 received, and successfully
                                                 processed. */
        
    ACCT_SESSION_EVT_RX_ACR_INT_OK,           /* Interim record received,
                                                 and successfully processed. */

    ACCT_SESSION_EVT_RX_ACR_STOP_OK,          /* Accounting stop request 
                                                 received, and successfully
                                                 processed. */

    ACCT_SESSION_EVT_RX_ACR_NO_BUF,           /* Accounting request received, no
                                                 space left to store records*/

    ACCT_SESSION_EVT_RX_ACR_FAIL,             /* Accounting request received, no
                                                 success result code*/

    ACCT_SESSION_EVT_SESSION_TOUT,            /* Session supervision timer Ts
                                                 expired */

    ACCT_SESSION_EVT_MAX
}ACCT_SESSION_EVENT;


class ClientAcctFsm;
class StatefulServerAcctFsm;
extern ClientAcctFsm clientAcctFsm;
extern StatefulServerAcctFsm statefulServerAcctFsm;


/****************************************************************************
 *  Interface:
 *      StatefulServerAcctFsm Class
 *
 *  Purpose:
 *      To implement Stateful Server Accounting statemachine.
 *
 *
 ****************************************************************************/
class StatefulServerAcctFsm:public DiaSM
{
public:
    /**
     * Constructor
     */
    StatefulServerAcctFsm();
    /**
     * Destructor
     */
    ~StatefulServerAcctFsm();
    /*
     *  Method to Submit to the StateMachine
     */
    int SubmitToSM(void *ctxt, ITS_EVENT *evt);
    /**
     * Add States to the State machine
     */
    int AddStateToStateMachine(DiaState *st);

private:
    std::vector<DiaState *> states;
};

/****************************************************************************
 *  Interface:
 *      ClientAcctFsm Class
 *      
 *  Purpose:
 *      To implement Client Accounting statemachine.
 *
 *
 ****************************************************************************/
class ClientAcctFsm:public DiaSM
{
public:
    /**
     * Constructor
     */
    ClientAcctFsm();
    /**
     * Destructor
     */
    ~ClientAcctFsm();
    /*
     *  SubmitToStateMachine
     */
    int SubmitToSM(void *ctxt, ITS_EVENT *evt);
    /**
     * Add States to the State machine
     */
    int AddStateToStateMachine(DiaState *st);
      
private:
    std::vector<DiaState *> states;
}; 

/****************************************************************************
 *  Interface:
 *      Idle Class for StatefulServerAcctFsm State Machine.
 *      
 *  Purpose:
 *      To implement Closed state for StatefulServerAcctFsm State Machine.
 *
 *
 ****************************************************************************/
class StatefulServerAcctFsm_Idle:public DiaState
{
public:
    /**
     * Constructor
     */
    StatefulServerAcctFsm_Idle(SESSION_STATE stateId):
                              DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process Event in the State.
     */    
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};


/****************************************************************************
 *  Interface:
 *      Open Class for StatefulServerAcct State machine.
 *      
 *  Purpose:
 *      To implement Open state StatefulServerAcctFsm State Machine.
 *
 *
 ****************************************************************************/
class StatefulServerAcctFsm_Open:public DiaState
{
public:
    /**
     * Constructor
     */
    StatefulServerAcctFsm_Open(SESSION_STATE stateId):
                              DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to process the event in the Open State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};


/****************************************************************************
 *  Interface:
 *      ClientAcctFsm_Idle Class
 *
 *  Purpose:
 *      To implement Idle state for ClientAcctFsm.
 *
 *
 ****************************************************************************/
class ClientAcctFsm_Idle:public DiaState
{
public:
    /**
     * Constructor
     */
    ClientAcctFsm_Idle(SESSION_STATE stateId):
                              DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to process the event in the ClientAcctFsm_Idle State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      ClientAcctFsm_Open Class
 *
 *  Purpose:
 *      To implement Pending state for ClientAcctFsm.
 *
 *
 ****************************************************************************/
class ClientAcctFsm_Open:public DiaState
{
public:
    /**
     * Constructor
     */
    ClientAcctFsm_Open(SESSION_STATE stateId):
                                 DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the ClientAcctFsm_Open State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      ClientAcctFsm_Pending_S Class
 *
 *  Purpose:
 *      To implement Pending_S state for ClientAcctFsm.
 *
 *
 ****************************************************************************/
class ClientAcctFsm_Pending_S:public DiaState
{
public:
    /**
     * Constructor
     */
    ClientAcctFsm_Pending_S(SESSION_STATE stateId):
                                 DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the ClientAcctFsm_Pending_S State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      ClientAcctFsm_Pending_E Class
 *
 *  Purpose:
 *      To implement Pending_E state for ClientAcctFsm.
 *
 *
 ****************************************************************************/
class ClientAcctFsm_Pending_E:public DiaState
{
public:
    /**
     * Constructor
     */
    ClientAcctFsm_Pending_E(SESSION_STATE stateId):
                                 DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the ClientAcctFsm_Pending_E State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      ClientAcctFsm_Pending_B Class
 *
 *  Purpose:
 *      To implement Pending_B state for ClientAcctFsm.
 *
 *
 ****************************************************************************/
class ClientAcctFsm_Pending_B:public DiaState
{
public:
    /**
     * Constructor
     */
    ClientAcctFsm_Pending_B(SESSION_STATE stateId):
                                 DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the ClientAcctFsm_Pending_B State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      ClientAcctFsm_Pending_I Class
 *
 *  Purpose:
 *      To implement Pending_I state for ClientAcctFsm.
 *
 *
 ****************************************************************************/
class ClientAcctFsm_Pending_I:public DiaState
{
public:
    /**
     * Constructor
     */
    ClientAcctFsm_Pending_I(SESSION_STATE stateId):
                                 DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the ClientAcctFsm_Pending_I State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      ClientAcctFsm_Pending_L Class
 *
 *  Purpose:
 *      To implement Pending_L state for ClientAcctFsm.
 *
 *
 ****************************************************************************/
class ClientAcctFsm_Pending_L:public DiaState
{
public:
    /**
     * Constructor
     */
    ClientAcctFsm_Pending_L(SESSION_STATE stateId):
                                 DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the ClientAcctFsm_Pending_L State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

#endif 
