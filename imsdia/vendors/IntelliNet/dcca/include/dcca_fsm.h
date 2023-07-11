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
 * LOG: $Log: dcca_fsm.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2006/11/24 16:28:04  hbhatnagar
 * LOG: made changes for the key as Session Index and proper indentation done
 * LOG:
 * LOG: Revision 2.2  2006/11/14 10:14:33  hbhatnagar
 * LOG: shifted the namespace to .cpp
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:55  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:28:09  nvijikumar
 * LOG: Converted the files from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_fsm.h,v 3.1 2008/03/31 10:33:30 nvijikumar Exp $
 *
 ****************************************************************************/

#ifndef DCCA_FSM_H
#define DCCA_FSM_H

/**
 * Includes
 */
#include <its++.h>
#include <dcca_conf.h>
#include <dcca_api.h>
#include <dia_defines.h>
#include <dcca_common.h>
#include <dcca_context.h>
#include <dcca_defines.h>

/**
 * Defines
 */
#define DCCA_MAX_FSM           0x08 
#define DCCA_MAX_STATE         0x08 

#define DCCA_CLIENT_FSM_AAA    0x00 
#define DCCA_CLIENT_FSM_CCR    0x02 
#define DCCA_CLIENT_FSM_FIN    0x03 
#define DCCA_CLIENT_FSM_EVE    0x04
#define DCCA_SERVER_FSM_SES    0x05

#define DCCA_FSM_STATE_IDLE    0x00
#define DCCA_FSM_STATE_OPEN    0x01
#define DCCA_FSM_STATE_PENI    0x02
#define DCCA_FSM_STATE_PENU    0x03
#define DCCA_FSM_STATE_PENT    0x04
#define DCCA_FSM_STATE_PENE    0x05
#define DCCA_FSM_STATE_PENB    0x06

/****************************************************************************
 *
 *  Interface: DCCAFsmStatemachine Class
 *      
 *  Purpose  : To implement DCCA Fsm statemachine
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAFsmStatemachine
{
public:        
    /**
     * To process an event in this statemachine
     */
    virtual ITS_INT SubmitToStatemachine(DCCA_EVENT*, DCCA_CONTEXT*) = 0;
};

/****************************************************************************
 *
 *  Interface: DCCAFsm Class
 *      
 *  Purpose  : To implement DCCA Fsm
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAFsm
{
public:
    /**
     * Constructor
     */
    DCCAFsm();
    /**
     * Destructor
     */
    ~DCCAFsm();
    /**
     * To process an event in a particular statemachine
     */
    ITS_INT SubmitToFsm(DCCA_EVENT*, DCCA_CONTEXT*);

private:
    /**
     * DCCAFsmStatemachine objects 
     */            
    DCCAFsmStatemachine* dccaFsmStatemachine[DCCA_MAX_FSM];
};

/****************************************************************************
 *
 *  Interface: DCCAState Class
 *      
 *  Purpose  : To implement DCCA Fsm state
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAFsmState
{
public:        
    /**
     * To process an event in this state
     */
    virtual ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*) = 0;
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmAaa Class
 *      
 *  Purpose  : To implement session based first interrogation within AA Fsm
 *             for DCCA client
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmAaa : public DCCAFsmStatemachine
{
public:
    /**
     * Constructor
     */
    DCCAClientFsmAaa();
    /**
     * Destructor
     */
    ~DCCAClientFsmAaa();
    /**
     * To process an event in this statemachine
     */
    ITS_INT SubmitToStatemachine(DCCA_EVENT*, DCCA_CONTEXT*);

 private:
    /**
     * State objects 
     */            
    DCCAFsmState* dccaFsmState[DCCA_MAX_STATE];
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmCcr Class
 *      
 *  Purpose  : To implement session based first interrogation with CCR Fsm
 *             for DCCA client
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmCcr : public DCCAFsmStatemachine
{
public:
    /**
     * Constructor
     */
    DCCAClientFsmCcr();
    /**
     * Destructor
     */
    ~DCCAClientFsmCcr();
    /**
     * To process an event in this statemachine
     */
    ITS_INT SubmitToStatemachine(DCCA_EVENT*, DCCA_CONTEXT*);

private:
    /**
     * State objects 
     */            
    DCCAFsmState* dccaFsmState[DCCA_MAX_STATE];
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmFin Class
 *      
 *  Purpose  : To implement session based intermediate and final 
 *             interrogation Fsm for DCCA client
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmFin : public DCCAFsmStatemachine 
{
public:
    /**
     * Constructor
     */
    DCCAClientFsmFin();
    /**
     * Destructor
     */
    ~DCCAClientFsmFin();
    /**
     * To process an event in this statemachine
     */
    ITS_INT SubmitToStatemachine(DCCA_EVENT*, DCCA_CONTEXT*);

private:
    /**
     * State objects 
     */            
    DCCAFsmState* dccaFsmState[DCCA_MAX_STATE];
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmEve Class
 *      
 *  Purpose  : To implement event based Fsm for DCCA client 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmEve : public DCCAFsmStatemachine 
{
public:
    /**
     * Constructor
     */
    DCCAClientFsmEve();
    /**
     * Destructor
     */
    ~DCCAClientFsmEve();
    /**
     * To process an event in this statemachine
     */
    ITS_INT SubmitToStatemachine(DCCA_EVENT*, DCCA_CONTEXT*);

private:
    /**
     * State objects 
     */            
    DCCAFsmState* dccaFsmState[DCCA_MAX_STATE];
};

/****************************************************************************
 *
 *  Interface: DCCAServerFsmSes Class
 *      
 *  Purpose  : To implement session and event based Fsm for DCCA server 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAServerFsmSes : public DCCAFsmStatemachine
{
public:
    /**
     * Constructor
     */
    DCCAServerFsmSes();
    /**
     * Destructor
     */
    ~DCCAServerFsmSes();
    /**
     * To process an event in this statemachine
     */
    ITS_INT SubmitToStatemachine(DCCA_EVENT*, DCCA_CONTEXT*);

private:
    /**
     * State objects 
     */            
    DCCAFsmState* dccaFsmState[DCCA_MAX_STATE];
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmAaaStateIdle Class
 *      
 *  Purpose  : To process an event in idle state of DCCAClientFsmAaa 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmAaaStateIdle : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmAaaStatePenI Class
 *      
 *  Purpose  : To process an event in pending initial state of
 *             DCCAClientFsmAaa 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmAaaStatePenI : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmAaaStateOpen Class
 *      
 *  Purpose  : To process an event in open state of DCCAClientFsmAaa
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmAaaStateOpen : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmCcrStateIdle Class
 *      
 *  Purpose  : To process an event in idle state of DCCAClientFsmCcr 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmCcrStateIdle : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmCcrStatePenI Class
 *      
 *  Purpose  : To process an event in pending initial state of
 *             DCCAClientFsmCcr 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmCcrStatePenI : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmCcrStateOpen Class
 *      
 *  Purpose  : To process an event in open state of DCCAClientFsmCcr
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmCcrStateOpen : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmFinStateIdle Class
 *      
 *  Purpose  : To process an event in idle state of DCCAClientFsmFin 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmFinStateIdle : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmFinStatePenU Class
 *      
 *  Purpose  : To process an event in pending initial state of
 *             DCCAClientFsmFin 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmFinStatePenU : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmFinStatePenT Class
 *      
 *  Purpose  : To process an event in pending initial state of
 *             DCCAClientFsmFin 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmFinStatePenT : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmFinStateOpen Class
 *      
 *  Purpose  : To process an event in open state of DCCAClientFsmFin
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmFinStateOpen : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmEveStateIdle Class
 *      
 *  Purpose  : To process an event in idle state of DCCAClientFsmEve 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmEveStateIdle : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmEveStatePenB Class
 *      
 *  Purpose  : To process an event in pending initial state of
 *             DCCAClientFsmEve 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmEveStatePenB : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAClientFsmEveStatePenE Class
 *      
 *  Purpose  : To process an event in pending initial state of
 *             DCCAClientFsmEve 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAClientFsmEveStatePenE : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAServerFsmSesStateIdle Class
 *      
 *  Purpose  : To process an event in idle state of DCCAServerFsmSes 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAServerFsmSesStateIdle : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

/****************************************************************************
 *
 *  Interface: DCCAServerFsmSesStateOpen Class
 *      
 *  Purpose  : To process an event in idle state of DCCAServerFsmSes 
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAServerFsmSesStateOpen : public DCCAFsmState
{
public:
    /**
     * To process an event in this state
     */
    ITS_INT SubmitToState(DCCA_EVENT*, DCCA_CONTEXT*);  
};

#endif
