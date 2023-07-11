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
 * LOG: $Log: dia_session_auth_fsm.h,v $
 * LOG: Revision 3.3.54.1  2013/08/15 05:24:11  ncshivakumar
 * LOG: Chnages for generic state machine
 * LOG:
 * LOG: Revision 3.3  2010/10/11 05:08:57  nvijikumar
 * LOG: Motorola's changes incorporation for field compilation issue
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:14:26  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.8  2006/10/30 21:34:04  yranade
 * LOG: Fix issues. (Early morning 31st, Oct)
 * LOG:
 * LOG: Revision 2.7  2006/10/30 15:59:11  yranade
 * LOG: Updates to Handle RAR/RAA.
 * LOG:
 * LOG: Revision 2.6  2006/10/16 06:29:00  yranade
 * LOG: Add event AUTH_SESSION_EVT_RX_ASA_FAIL
 * LOG:
 * LOG: Revision 2.5  2006/10/13 16:38:05  yranade
 * LOG: Added Event RAR to depict Server Inititated ReAuth
 * LOG:
 * LOG: Revision 2.4  2006/10/05 13:00:22  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.3  2006/09/20 13:47:26  nvijikumar
 * LOG: Changes to take State ID has states vector Index.
 * LOG:
 * LOG: Revision 2.2  2006/09/14 09:37:28  nvijikumar
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
 * ID: $Id: dia_session_auth_fsm.h,v 3.3.54.1 2013/08/15 05:24:11 ncshivakumar Exp $
 ****************************************************************************/
#ident "$Id: dia_session_auth_fsm.h,v 3.3.54.1 2013/08/15 05:24:11 ncshivakumar Exp $"


#if !defined DIA_SESSION_AUTH_FSM_H
#define DIA_SESSION_AUTH_FSM_H


/**
 * Includes
 */
#include <iostream>
#include <dia_fsm.h>
#include <dia_session_table.h>

typedef enum
{
    AUTH_SESSION_EVT_REQUEST_ACCESS,
    AUTH_SESSION_EVT_RX_SSAA_OK,
    AUTH_SESSION_EVT_RX_SSAA_FAIL,
    AUTH_SESSION_EVT_TX_SSAA_OK,
    AUTH_SESSION_EVT_TX_SSAA_FAIL,
    AUTH_SESSION_EVT_TX_STR,
    AUTH_SESSION_EVT_RX_STR,
    AUTH_SESSION_EVT_TX_STA,
    AUTH_SESSION_EVT_RX_STA,
    AUTH_SESSION_EVT_TX_ASR,
    AUTH_SESSION_EVT_TX_ASR_FAIL,
    AUTH_SESSION_EVT_RX_ASR,
    AUTH_SESSION_EVT_TX_ASA,
    AUTH_SESSION_EVT_TX_ASA_OK,
    AUTH_SESSION_EVT_TX_ASA_FAIL,
    AUTH_SESSION_EVT_RX_ASA,
    AUTH_SESSION_EVT_RX_ASA_OK,
    AUTH_SESSION_EVT_RX_ASA_FAIL,
    AUTH_SESSION_EVT_TX_RAR,
    AUTH_SESSION_EVT_RX_RAR,
    AUTH_SESSION_EVT_TX_RAA_OK,
    AUTH_SESSION_EVT_TX_RAA_FAIL,
    AUTH_SESSION_EVT_RX_RAA_OK,
    AUTH_SESSION_EVT_RX_RAA_FAIL,
    AUTH_SESSION_EVT_SESSION_TOUT_ST,   
    AUTH_SESSION_EVT_LIFETIME_TOUT,
    AUTH_SESSION_EVT_STOP,             /*  Service to user is terminated */
    AUTH_SESSION_EVT_TX_SSAA_AGENT,   
    AUTH_SESSION_EVT_RX_SSAA_AGENT,
    AUTH_SESSION_EVT_TX_APP_SPECIFIC_REQ_MSG,
    AUTH_SESSION_EVT_RX_APP_SPECIFIC_REQ_MSG,
    AUTH_SESSION_EVT_TX_APP_SPECIFIC_RES_MSG
}
AUTH_SESSION_EVENT;

#define AUTH_SESSION_EVENT_TO_TEXT(x) \
    ((x==AUTH_SESSION_EVT_REQUEST_ACCESS)  ? "AUTH_SESSION_EVT_REQUEST_ACCESS"  : \
    ((x==AUTH_SESSION_EVT_RX_SSAA_OK)      ? "AUTH_SESSION_EVT_RX_SSAA_OK"      : \
    ((x==AUTH_SESSION_EVT_RX_SSAA_FAIL)    ? "AUTH_SESSION_EVT_RX_SSAA_FAIL"    : \
    ((x==AUTH_SESSION_EVT_TX_SSAA_OK)      ? "AUTH_SESSION_EVT_TX_SSAA_OK"      : \
    ((x==AUTH_SESSION_EVT_TX_SSAA_FAIL)    ? "AUTH_SESSION_EVT_TX_SSAA_FAIL"    : \
    ((x==AUTH_SESSION_EVT_TX_STR)          ? "AUTH_SESSION_EVT_TX_STR"          : \
    ((x==AUTH_SESSION_EVT_RX_STR)          ? "AUTH_SESSION_EVT_RX_STR"          : \
    ((x==AUTH_SESSION_EVT_TX_STA)          ? "AUTH_SESSION_EVT_TX_STA"          : \
    ((x==AUTH_SESSION_EVT_RX_STA)          ? "AUTH_SESSION_EVT_RX_STA"          : \
    ((x==AUTH_SESSION_EVT_TX_ASR)          ? "AUTH_SESSION_EVT_TX_ASR"          : \
    ((x==AUTH_SESSION_EVT_TX_ASR_FAIL)     ? "AUTH_SESSION_EVT_TX_ASR_FAIL"     : \
    ((x==AUTH_SESSION_EVT_RX_ASR)          ? "AUTH_SESSION_EVT_RX_ASR"          : \
    ((x==AUTH_SESSION_EVT_TX_ASA_OK)       ? "AUTH_SESSION_EVT_TX_ASA_OK"       : \
    ((x==AUTH_SESSION_EVT_TX_ASA_FAIL)     ? "AUTH_SESSION_EVT_TX_ASA_FAIL"     : \
    ((x==AUTH_SESSION_EVT_RX_ASA)          ? "AUTH_SESSION_EVT_RX_ASA"          : \
    ((x==AUTH_SESSION_EVT_RX_ASA_OK)       ? "AUTH_SESSION_EVT_RX_ASA_OK"       : \
    ((x==AUTH_SESSION_EVT_RX_ASA_FAIL)     ? "AUTH_SESSION_EVT_RX_ASA_FAIL"     : \
    ((x==AUTH_SESSION_EVT_TX_RAR)          ? "AUTH_SESSION_EVT_TX_RAR"          : \
    ((x==AUTH_SESSION_EVT_RX_RAR)          ? "AUTH_SESSION_EVT_RX_RAR"          : \
    ((x==AUTH_SESSION_EVT_TX_RAA_OK)       ? "AUTH_SESSION_EVT_TX_RAA_OK"       : \
    ((x==AUTH_SESSION_EVT_TX_RAA_FAIL)     ? "AUTH_SESSION_EVT_TX_RAA_FAIL"     : \
    ((x==AUTH_SESSION_EVT_RX_RAA_OK)       ? "AUTH_SESSION_EVT_RX_RAA_OK"       : \
    ((x==AUTH_SESSION_EVT_RX_RAA_FAIL)     ? "AUTH_SESSION_EVT_RX_RAA_FAIL"     : \
    ((x==AUTH_SESSION_EVT_SESSION_TOUT_ST) ? "AUTH_SESSION_EVT_SESSION_TOUT_ST" : \
    ((x==AUTH_SESSION_EVT_LIFETIME_TOUT)   ? "AUTH_SESSION_EVT_LIFETIME_TOUT"   : \
    ((x==AUTH_SESSION_EVT_STOP)            ? "AUTH_SESSION_EVT_STOP"            : \
    ((x==AUTH_SESSION_EVT_TX_SSAA_AGENT)   ? "AUTH_SESSION_EVT_TX_SSAA_AGENT"   : \
    ((x==AUTH_SESSION_EVT_RX_SSAA_AGENT)   ? "AUTH_SESSION_EVT_RX_SSAA_AGENT"   : \
    ((x==AUTH_SESSION_EVT_TX_APP_SPECIFIC_REQ_MSG)   ? "AUTH_SESSION_EVT_TX_APP_SPECIFIC_REQ_MSG"   : \
    ((x==AUTH_SESSION_EVT_RX_APP_SPECIFIC_REQ_MSG)   ? "AUTH_SESSION_EVT_RX_APP_SPECIFIC_REQ_MSG"   : \
    ((x==AUTH_SESSION_EVT_TX_APP_SPECIFIC_RES_MSG)   ? "AUTH_SESSION_EVT_TX_APP_SPECIFIC_RES_MSG"   : \
    "INVALID")))))))))))))))))))))))))))))))

class StatefulServerAuthFsm;
class StatefulClientAuthFsm;
class StatelessClientAuthFsm;
extern StatefulServerAuthFsm statefulServerAuthFsm;
extern StatefulClientAuthFsm statefulClientAuthFsm;
extern StatelessClientAuthFsm statelessClientAuthFsm;


/****************************************************************************
 *  Interface:
 *      StatefulServerAuthFsm Class
 *      
 *  Purpose:
 *      To implement Stateful Server Auth statemachine.
 *
 *
 ****************************************************************************/
class StatefulServerAuthFsm:public DiaSM
{
public:
    /**
     * Constructor
     */
    StatefulServerAuthFsm();
    /**
     * Destructor
     */
    ~StatefulServerAuthFsm();
    /*
     *  SubmitToStMc
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
 *      StatefulClientAuthFsm Class
 *      
 *  Purpose:
 *      To implement Stateful Client Auth statemachine.
 *
 *
 ****************************************************************************/
class StatefulClientAuthFsm:public DiaSM
{
public:
    /**
     * Constructor
     */
    StatefulClientAuthFsm();
    /**
     * Destructor
     */
    ~StatefulClientAuthFsm();
    /*
     *  SubmitToStMachine
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
 *      StatelessClientAuthFsm Class
 *      
 *  Purpose:
 *      To implement Stateless Client Auth statemachine.
 *
 *
 ****************************************************************************/
class StatelessClientAuthFsm:public DiaSM
{
public:
    /**
     * Constructor
     */
    StatelessClientAuthFsm();
    /**
     * Destructor
     */
    ~StatelessClientAuthFsm();
    /*
     *  SubmitToStMachine
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
 *      Idle Class for StatefulServerAuthFsm State Machine.
 *      
 *  Purpose:
 *      To implement Closed state for StatefulServerAuthFsm State Machine.
 *
 *
 ****************************************************************************/
class StatefulServerAuthFsm_Idle:public DiaState
{
public:
    /**
     * Constructor
     */
    StatefulServerAuthFsm_Idle(SESSION_STATE stateId):
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
 *      Open Class for StatefulServerAuth State machine.
 *      
 *  Purpose:
 *      To implement Open state StatefulServerAuthFsm State Machine.
 *
 *
 ****************************************************************************/
class StatefulServerAuthFsm_Open:public DiaState
{
public:
    /**
     * Constructor
     */
    StatefulServerAuthFsm_Open(SESSION_STATE stateId):
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
 *      Discon Class for StatefulServerAuth State machine.
 *      
 *  Purpose:
 *      To implement Discon state StatefulServerAuth State machine.
 *
 *
 ****************************************************************************/
class StatefulServerAuthFsm_Discon:public DiaState
{
public:
    /**
     * Constructor
     */
    StatefulServerAuthFsm_Discon(SESSION_STATE stateId):
                                DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to process the event in the Discon State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      StatefulClientAuthFsm_Idle Class
 *
 *  Purpose:
 *      To implement Idle state for StatefulClientAuthFsm.
 *
 *
 ****************************************************************************/
class StatefulClientAuthFsm_Idle:public DiaState
{
public:
    /**
     * Constructor
     */
    StatefulClientAuthFsm_Idle(SESSION_STATE stateId):
                              DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to process the event in the StatefulClientAuthFsm_Idle State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      StatefulClientAuthFsm_Pending Class
 *
 *  Purpose:
 *      To implement Pending state for StatefulClientAuthFsm.
 *
 *
 ****************************************************************************/
class StatefulClientAuthFsm_Pending:public DiaState
{
public:
    /**
     * Constructor
     */
    StatefulClientAuthFsm_Pending(SESSION_STATE stateId):
                                 DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the StatefulClientAuthFsm_Pending State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      StatefulClientAuthFsm_Open Class
 *
 *  Purpose:
 *      To implement Pending state for StatefulClientAuthFsm.
 *
 *
 ****************************************************************************/
class StatefulClientAuthFsm_Open:public DiaState
{
public:
    /**
     * Constructor
     */
    StatefulClientAuthFsm_Open(SESSION_STATE stateId):
                                 DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the StatefulClientAuthFsm_Open State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      StatefulClientAuthFsm_Discon Class
 *
 *  Purpose:
 *      To implement Pending state for StatefulClientAuthFsm.
 *
 *
 ****************************************************************************/
class StatefulClientAuthFsm_Discon:public DiaState
{
public:
    /**
     * Constructor
     */
    StatefulClientAuthFsm_Discon(SESSION_STATE stateId):
                                 DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the StatefulClientAuthFsm_Discon State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      StatelessClientAuthFsm_Idle Class
 *
 *  Purpose:
 *      To implement Idle state for StatelessClientAuthFsm.
 *
 *
 ****************************************************************************/
class StatelessClientAuthFsm_Idle:public DiaState
{
public:
    /**
     * Constructor
     */
    StatelessClientAuthFsm_Idle(SESSION_STATE stateId):
                              DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to process the event in the StatelessClientAuthFsm_Idle State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      StatelessClientAuthFsm_Pending Class
 *
 *  Purpose:
 *      To implement Pending state for StatelessClientAuthFsm.
 *
 *
 ****************************************************************************/
class StatelessClientAuthFsm_Pending:public DiaState
{
public:
    /**
     * Constructor
     */
    StatelessClientAuthFsm_Pending(SESSION_STATE stateId):
                                 DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the StatelessClientAuthFsm_Pending State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      StatelessClientAuthFsm_Open Class
 *
 *  Purpose:
 *      To implement Pending state for StatelessClientAuthFsm.
 *
 *
 ****************************************************************************/
class StatelessClientAuthFsm_Open:public DiaState
{
public:
    /**
     * Constructor
     */
    StatelessClientAuthFsm_Open(SESSION_STATE stateId):
                                 DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the StatelessClientAuthFsm_Open State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

#endif 
