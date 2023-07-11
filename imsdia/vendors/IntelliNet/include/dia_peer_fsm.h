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
 * LOG: $Log: dia_peer_fsm.h,v $
 * LOG: Revision 3.2  2010/10/11 05:08:57  nvijikumar
 * LOG: Motorola's changes incorporation for field compilation issue
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.2  2006/09/14 09:39:11  nvijikumar
 * LOG: Added TO_TEXT macros for Event and States enum.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * LOG:
 *
 * ID: $Id: dia_peer_fsm.h,v 3.2 2010/10/11 05:08:57 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: dia_peer_fsm.h,v 3.2 2010/10/11 05:08:57 nvijikumar Exp $"


#if !defined DIA_PEER_FSM_H
#define DIA_PEER_FSM_H


/**
 * Includes
 */
#include <iostream>
#include <dia_fsm.h>

#define PEER_STATE_TO_TEXT(x) \
    ((x==PEER_ST_CLOSED)             ? "PEER_ST_CLOSED"               : \
    ((x==PEER_ST_WAIT_CONN_ACK)      ? "PEER_ST_WAIT_CONN_ACK"        : \
    ((x==PEER_ST_WAIT_I_CEA)         ? "PEER_ST_WAIT_I_CEA"           : \
    ((x==PEER_ST_WAIT_CONN_ACK_ELECT)? "PEER_ST_WAIT_CONN_ACK_ELECT"  : \
    ((x==PEER_ST_WAIT_RETURNS)       ? "PEER_ST_WAIT_RETURNS"         : \
    ((x==PEER_ST_I_OPEN)             ? "PEER_ST_I_OPEN"               : \
    ((x==PEER_ST_R_OPEN)             ? "PEER_ST_R_OPEN"               : \
    ((x==PEER_ST_CLOSING)            ? "PEER_ST_CLOSING"              : \
    ((x==PEER_ST_MAX)                ? "PEER_ST_MAX"                  : \
    "INVALID")))))))))

typedef enum 
{
    PEER_ST_CLOSED,
    PEER_ST_WAIT_CONN_ACK,
    PEER_ST_WAIT_I_CEA,
    PEER_ST_WAIT_CONN_ACK_ELECT,
    PEER_ST_WAIT_RETURNS,
    PEER_ST_I_OPEN,
    PEER_ST_R_OPEN,
    PEER_ST_CLOSING,
    PEER_ST_MAX
}PEER_STATE;

#define PEER_EVENT_TO_TEXT(x) \
    ((x==PEER_EVT_START)           ? "PEER_EVT_START"           : \
    ((x==PEER_EVT_R_CONN_CER)      ? "PEER_EVT_R_CONN_CER"      : \
    ((x==PEER_EVT_I_RCV_CONN_ACK)  ? "PEER_EVT_I_RCV_CONN_ACK"  : \
    ((x==PEER_EVT_I_RCV_CONN_NACK) ? "PEER_EVT_I_RCV_CONN_NACK" : \
    ((x==PEER_EVT_TIMEOUT)         ? "PEER_EVT_TIMEOUT"         : \
    ((x==PEER_EVT_I_RCV_CER)       ? "PEER_EVT_I_RCV_CER"       : \
    ((x==PEER_EVT_R_RCV_CER)       ? "PEER_EVT_R_RCV_CER"       : \
    ((x==PEER_EVT_I_RCV_CEA)       ? "PEER_EVT_I_RCV_CEA"       : \
    ((x==PEER_EVT_R_RCV_CEA)       ? "PEER_EVT_R_RCV_CEA"       : \
    ((x==PEER_EVT_I_RCV_NON_CEA)   ? "PEER_EVT_I_RCV_NON_CEA"   : \
    ((x==PEER_EVT_RCV_NONCEA)      ? "PEER_EVT_RCV_NONCEA"      : \
    ((x==PEER_EVT_I_PEER_DISC)     ? "PEER_EVT_I_PEER_DISC"     : \
    ((x==PEER_EVT_R_PEER_DISC)     ? "PEER_EVT_R_PEER_DISC"     : \
    ((x==PEER_EVT_I_RCV_DPR)       ? "PEER_EVT_I_RCV_DPR"       : \
    ((x==PEER_EVT_R_RCV_DPR)       ? "PEER_EVT_R_RCV_DPR"       : \
    ((x==PEER_EVT_I_RCV_DPA)       ? "PEER_EVT_I_RCV_DPA"       : \
    ((x==PEER_EVT_R_RCV_DPA)       ? "PEER_EVT_R_RCV_DPA"       : \
    ((x==PEER_EVT_WIN_ELECTION)    ? "PEER_EVT_WIN_ELECTION"    : \
    ((x==PEER_EVT_SEND_MESSAGE)    ? "PEER_EVT_SEND_MESSAGE"    : \
    ((x==PEER_EVT_I_RCV_MESSAGE)   ? "PEER_EVT_I_RCV_MESSAGE"   : \
    ((x==PEER_EVT_R_RCV_MESSAGE)   ? "PEER_EVT_R_RCV_MESSAGE"   : \
    ((x==PEER_EVT_I_RCV_DWR)       ? "PEER_EVT_I_RCV_DWR"       : \
    ((x==PEER_EVT_R_RCV_DWR)       ? "PEER_EVT_R_RCV_DWR"       : \
    ((x==PEER_EVT_I_RCV_DWA)       ? "PEER_EVT_I_RCV_DWA"       : \
    ((x==PEER_EVT_R_RCV_DWA)       ? "PEER_EVT_R_RCV_DWA"       : \
    ((x==PEER_EVT_STOP)            ? "PEER_EVT_STOP"            : \
    ((x==PEER_EVT_MAX)             ? "PEER_EVT_MAX"             : \
    "INVALID")))))))))))))))))))))))))))

typedef enum 
{
    PEER_EVT_START = 0,
    PEER_EVT_R_CONN_CER,
    PEER_EVT_I_RCV_CONN_ACK,
    PEER_EVT_I_RCV_CONN_NACK,
    PEER_EVT_TIMEOUT,
    PEER_EVT_I_RCV_CER,
    PEER_EVT_R_RCV_CER,
    PEER_EVT_I_RCV_CEA,
    PEER_EVT_R_RCV_CEA,
    PEER_EVT_I_RCV_NON_CEA,
    PEER_EVT_RCV_NONCEA,
    PEER_EVT_I_PEER_DISC,
    PEER_EVT_R_PEER_DISC,
    PEER_EVT_I_RCV_DPR,
    PEER_EVT_R_RCV_DPR,
    PEER_EVT_I_RCV_DPA,
    PEER_EVT_R_RCV_DPA,
    PEER_EVT_WIN_ELECTION,
    PEER_EVT_SEND_MESSAGE,
    PEER_EVT_I_RCV_MESSAGE,
    PEER_EVT_R_RCV_MESSAGE,
    PEER_EVT_I_RCV_DWR,
    PEER_EVT_R_RCV_DWR,
    PEER_EVT_I_RCV_DWA,
    PEER_EVT_R_RCV_DWA,
    PEER_EVT_STOP,
    PEER_EVT_MAX
}PEER_EVENT;

/****************************************************************************
 *  Interface:
 *      PeerFsm Class
 *      
 *  Purpose:
 *      To implement PEER statemachine.
 *
 *
 ****************************************************************************/
class PeerFsm:public DiaSM
{
public:
    /**
     * Constructor
     */
    PeerFsm();
    /**
     * Destructor
     */
    ~PeerFsm();
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
 *      Closed Class
 *      
 *  Purpose:
 *      To implement Closed state
 *
 *
 ****************************************************************************/
class Closed:public DiaState
{
public:
    /**
     * Constructor
     */
    Closed(PEER_STATE stateId):DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process Event in the State.
     */    
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};


/****************************************************************************
 *  Interface:
 *      WaitConnAck Class
 *      
 *  Purpose:
 *      To implement Wait-Conn-Ack state
 *
 *
 ****************************************************************************/
class WaitConnAck:public DiaState
{
public:
    /**
     * Constructor
     */
    WaitConnAck(PEER_STATE stateId):DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to process the event in the Wait-Conn-Ack State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};


/****************************************************************************
 *  Interface:
 *      Wait-I-CEA Class
 *      
 *  Purpose:
 *      To implement Wait-I-CEA state
 *
 *
 ****************************************************************************/
class WaitICEA:public DiaState
{
public:
    /**
     * Constructor
     */
    WaitICEA(PEER_STATE stateId):DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to process the event in the Wait-I-CEA State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      Wait-Conn-Ack/Elect Class
 *
 *  Purpose:
 *      To implement Wait-Conn-Ack/Elect state
 *
 *
 ****************************************************************************/
class WaitConnAckElect:public DiaState
{
public:
    /**
     * Constructor
     */
    WaitConnAckElect(PEER_STATE stateId):DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the Wait-Conn-Ack/Elect State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      I-Open Class
 *
 *  Purpose:
 *      To implement I-Open state
 *
 *
 ****************************************************************************/
class IOpen:public DiaState
{
public:
    /**
     * Constructor
     */
    IOpen(PEER_STATE stateId):DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to process the event in the I-Open State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      Wait-Returns Class
 *
 *  Purpose:
 *      To implement Wait-Returns state
 *
 *
 ****************************************************************************/
class WaitReturns:public DiaState
{
public:
    /**
     * Constructor
     */
    WaitReturns(PEER_STATE stateId):DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the Wait-Returns State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      R-Open Class
 *
 *  Purpose:
 *      To implement R-Open state
 *
 *
 ****************************************************************************/
class ROpen:public DiaState
{
public:
    /**
     * Constructor
     */
    ROpen(PEER_STATE stateId):DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to process the event in the R-Open State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};

/****************************************************************************
 *  Interface:
 *      Closing Class
 *
 *  Purpose:
 *      To implement Closing state
 *
 *
 ****************************************************************************/
class Closing:public DiaState
{
public:
    /**
     * Constructor
     */
    Closing(PEER_STATE stateId):DiaState((ITS_OCTET)stateId)
    {
    }
    /**
     * Method to Process the event in the Closing State.
     */
    int ProcessEvent(void *ctxt, ITS_EVENT *evt);
};
#endif 
