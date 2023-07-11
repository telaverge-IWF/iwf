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
 * LOG: $Log: dcca_message_handler.cpp,v $
 * LOG: Revision 3.2.6.1.30.1.8.2.2.1.2.2  2014/11/17 05:03:39  jkchaitanya
 * LOG: changes for HA Bug Fixes
 * LOG:
 * LOG: Revision 3.2.6.1.30.1.8.2.2.1.2.1  2014/10/27 08:28:37  pramana
 * LOG: changes for HA HotStandBy
 * LOG:
 * LOG: Revision 3.2.6.1.30.1.8.2.2.1  2014/07/11 13:54:01  jsarvesh
 * LOG: Changes done for sending CCR-T for AuthSessionTimer expiry
 * LOG:
 * LOG: Revision 3.2.6.1.30.1.8.2  2014/05/06 13:09:12  jkchaitanya
 * LOG: changes for ccfh feature
 * LOG:
 * LOG: Revision 3.2.6.1.30.1.8.1  2014/04/01 13:04:02  millayaraja
 * LOG: modified to remain in OPEN state when CCFH=TERMINATE after TX timeout and send indication to Application
 * LOG:
 * LOG: Revision 3.2.6.1.30.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.2.6.1  2012/09/06 11:30:45  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 * LOG:
 * LOG: Revision 3.2.8.1  2012/08/28 03:52:43  cprem
 * LOG: Added include for json.
 * LOG:
 * LOG: Revision 3.2  2010/08/06 06:58:23  nvijikumar
 * LOG: Changes to send TX TIMEOUT indication to the application (Fix for TCS)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.14  2007/02/21 13:02:24  hbhatnagar
 * LOG: made changes for the proper return values for add,modify and remove.
 * LOG:
 * LOG: Revision 2.13  2007/01/23 07:43:46  hbhatnagar
 * LOG: Fix for SendIndicationToApp:SessionIndex was missing
 * LOG:
 * LOG: Revision 2.12  2006/11/30 10:15:18  hbhatnagar
 * LOG: made changes for the error handling
 * LOG:
 * LOG: Revision 2.11  2006/11/27 04:14:50  yranade
 * LOG: Stop CC Compiler complaining.
 * LOG:
 * LOG: Revision 2.10  2006/11/24 16:36:30  hbhatnagar
 * LOG: Made changes for SessionId as Key and corresponding changes
 * LOG:
 * LOG: Revision 2.9  2006/11/15 12:23:31  tpanda
 * LOG: Fix for dcca context removal if STA recieved(for client only)
 * LOG:
 * LOG: Revision 2.8  2006/11/14 10:26:33  hbhatnagar
 * LOG: made changes for error response and cleanup
 * LOG:
 * LOG: Revision 2.7  2006/11/13 06:46:18  hbhatnagar
 * LOG: Proper indentation and cleanup done.
 * LOG:
 * LOG: Revision 2.6  2006/11/06 09:30:47  hbhatnagar
 * LOG: made changes for the separation of BCGI and RFRO related functionality with core.
 * LOG:
 * LOG: Revision 2.5  2006/10/31 10:26:12  yranade
 * LOG: Disable out AAR/AAA handling, since it's not supported.
 * LOG:
 * LOG: Revision 2.4  2006/10/31 09:41:27  hbhatnagar
 * LOG: Made changes for the Server side Base stack Context to Release for CCA Event
 * LOG:
 * LOG: Revision 2.3  2006/10/31 08:39:36  hbhatnagar
 * LOG: Made changes for the BCGI ReleaseStackSession.
 * LOG:
 * LOG: Revision 2.2  2006/10/30 15:35:58  hbhatnagar
 * LOG: Changes for DCCA to work with ITSDEMO
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:56  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.5  2006/09/29 06:22:27  nvijikumar
 * LOG: Cleaning done (badri)
 * LOG:
 * LOG: Revision 1.1.2.4  2006/09/25 13:02:32  nvijikumar
 * LOG: Bug Fix for ID: 4360, 4362 and 4372
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/25 08:45:51  nvijikumar
 * LOG: Converted file from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:33:36  nvijikumar
 * LOG: Created DCCA configuration object (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_message_handler.cpp,v 3.2.6.1.30.1.8.2.2.1.2.2 2014/11/17 05:03:39 jkchaitanya Exp $
 *
 ****************************************************************************/

/**
 * Includes
 */
#include <json/json.h>
#include <dcca_message_handler.h>
#include <dia_stack.h>

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
 *  Input Parameters       : dccaFsm          - DCCAFsm object
 *                           dccaContextTable - DCCAContextTable object
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
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
DCCADiaMessageHandler::DCCADiaMessageHandler(
DCCAFsm *dccaFsm, DCCAContextTable *dccaContextTable)
:MessageHandler(ITS_DIA_SRC)
{    
    this->dccaFsm          = dccaFsm;
    this->dccaContextTable = dccaContextTable;
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
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
DCCADiaMessageHandler::~DCCADiaMessageHandler()
{
    dccaFsm          = NULL;
    dccaContextTable = NULL;
}

/****************************************************************************
 *
 *  Purpose                : To handle indication messages
 *
 *  Input Parameters       : eve - The DCCA_EVENT
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
ITS_INT 
DCCADiaMessageHandler::IndicationMessageHandling(DCCA_EVENT* eve)
{
    DCCA_CONTEXT *pctx = NULL;
    ITS_OCTET* key = (ITS_OCTET*) eve->sessId;
    ITS_UINT len = strlen((char*)eve->sessId);
    
    /**
     * Just print what indication is
     */
    string str;
    switch(eve->ind)
    {
        case ABORT_IND_FROM_STACK:
        {
            str = "ABORT_IND_FROM_STACK";
            break;
        }
        case TIME_OUT_IND_FROM_STACK:
        {
            str = "TIME_OUT_IND_FROM_STACK";
            break;
        }
        case DISCONECT_IND_FROM_STACK:
        {
            str = "DISCONECT_IND_FROM_STACK";
            break;
        }
        case AUTH_LIFE_TIME_OUT_IND_FROM_STACK:
        {
            str = "AUTH_LIFE_TIME_OUT_IND_FROM_STACK";
            break;
        }
        case AUTH_GRACE_TIME_OUT_IND_FROM_STACK:
        {
            str = "AUTH_GRACE_TIME_OUT_IND_FROM_STACK";
            break;
        }
        case APP_REL_SESS_IND_FROM_STACK:
        {
            str = "APP_REL_SESS_IND_FROM_STACK";
            break;
        }
        case APP_CREATE_SESS_IND_FROM_STACK:
        {
            str = "APP_CREATE_SESS_IND_FROM_STACK";
            break;
        }
    }
    DCCA_TRACE_DEBUG((
    "DCCA: DCCADiaMessageHandler::IndicationMessageHandling: " \
    "Received %s indication for session: %s ...", 
    str.c_str(), eve->sessId));    
    
    /**
     * Fetch the context
     */
    if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
    DCCA_CONTEXT_FETCH, pctx, key, len) && 
            eve->ind != APP_CREATE_SESS_IND_FROM_STACK)
    {
        /*DCCA_TRACE_DEBUG((
        "DCCA: DCCADiaMessageHandler::IndicationMessageHandling: " \
        "Could not fetch context for session: %s ...", eve->sessId));*/

        /**
         * If the context is not available then return success
         * this would had already been deleted in previous
         * SessionTerminationMessageHandling
         */
        return ITS_SUCCESS;//This remains as success             
    }

    if ( eve->ind == AUTH_LIFE_TIME_OUT_IND_FROM_STACK)
    {
        return ITS_SUCCESS;//This remains as success
    }

    /* This is done to avoid DCCA removing the SessionEntry so that 
     * application can send CCR-T followed by ReleaseSessionEntry */
    else if ( eve->ind == TIME_OUT_IND_FROM_STACK || 
            eve->ind == AUTH_GRACE_TIME_OUT_IND_FROM_STACK)
    {
        return ITS_SUCCESS;//This remains as success
    }

    else if (eve->ind == APP_REL_SESS_IND_FROM_STACK )        
    {
        /**
         * There is no timer started for this session and 
         * so delete the context
         */
        if(!pctx->timer)
        {
            if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
            DCCA_CONTEXT_REMOVE, pctx,key,len))
            {
                DCCA_TRACE_DEBUG((
                "DCCA: DCCADiaMessageHandler::IndicationMessageHandling: " \
                "Could not Remove context for session: %s ...", eve->sessId));
                return ITS_DIA_DCCA_ERROR; 
            }

            DCCA_TRACE_DEBUG((
            "DCCA: DCCADiaMessageHandler::SessionTerminationMessageHandling: " \
            "Context removed for session: %s ...", eve->sessId));

            return ITS_SUCCESS;
        }

        /**
         * Mark the context as invalid
         * It will automatically get deleted in corresponding timer expiry
         */
         pctx->mark = 1;
         DCCA_TRACE_DEBUG((
         "DCCA: DCCADiaMessageHandler::IndicationMessageHandling: " \
         "Marked the session as invalid for session: %s ...", eve->sessId));
    
        /**
         * Update the context
         */
        if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
        DCCA_CONTEXT_MODIFY, pctx,key,len))
        {
            DCCA_TRACE_WARNING((
            "DCCA: DCCADiaMessageHandler::IndicationMessageHandling: " \
            "Could not update context for session: %s ...", eve->sessId));
            return ITS_DIA_DCCA_ERROR; 
        }
    }
    else if (eve->ind == APP_CREATE_SESS_IND_FROM_STACK)
    {
        DCCA_TRACE_DEBUG(("received APP_CREATE_SESS_IND_FROM_STACK, recreating Session Context"));
        DCCA_CONTEXT ctx;
        DCCA_CONTEXT *pctx = &ctx;

        ITS_OCTET* key = (ITS_OCTET*) eve->sessId;
        ITS_UINT len = strlen((char*)eve->sessId);

        memset(&ctx, 0x00, sizeof(ctx));
        ctx.state           = DCCA_FSM_STATE_OPEN;
        ctx.session         = eve->sin;    
        ctx.statemachine    = DCCA_CLIENT_FSM_FIN;    
        ctx.applicationid   = eve->app;
        ctx.requestedaction = eve->act;
        ctx.requestType     = eve->typ;
        ctx.newlyReplicatedSession = ITS_TRUE;
        ctx.ccfh            = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_CCFH);
        ctx.clientId        = eve->clientId; 
        //Correcting Calling Risky Function
        strncpy((char *)ctx.sessionId, (char *)eve->sessId, SESSION_ID_LENGTH - 1);

        // Create the DCCA context
        if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
                             DCCA_CONTEXT_ADD, pctx, key, len))
        {
            DCCA_TRACE_WARNING((
                        "DCCA:DCCADiaMessageHandler::IndicationMessageHandling:"
                        "Could not add context for session: [%s] ...",
                        eve->sessId));
            return ITS_DIA_DCCA_ERROR; 
        }

    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *
 *  Purpose                : To handle session termination messages
 *
 *  Input Parameters       : eve - The DCCA_EVENT
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
ITS_INT 
DCCADiaMessageHandler::SessionTerminationMessageHandling(DCCA_EVENT* eve)
{    
    DCCA_CONTEXT *pctx = NULL;
    ITS_OCTET* key = (ITS_OCTET*) eve->sessId;
    ITS_UINT len = strlen((char*)eve->sessId);
    
    if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
    DCCA_CONTEXT_FETCH, pctx,key,len))
    {
        /*DCCA_TRACE_DEBUG((
        "DCCA: DCCADiaMessageHandler::SessionTerminationMessageHandling: " \
        "Could not fetch context for session: %s ...", eve->sessId));*/

        /**
         * If the context is not available then return success
         * this would had already been deleted in previous
         * corresponding FSM state
         */
        return ITS_SUCCESS;//this remains success        
    }
    
    /**
     * There is no timer started for this session and 
     * so delete the context
     */
    if(!pctx->timer || (pctx->statemachine != DCCA_SERVER_FSM_SES))
    {
        if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
        DCCA_CONTEXT_REMOVE, pctx,key,len))
        {
            DCCA_TRACE_WARNING((
            "DCCA: DCCADiaMessageHandler::SessionTerminationMessageHandling: " \
            "Could not Remove context for session: %s ...", eve->sessId));
            return ITS_DIA_DCCA_ERROR; 
        }

        DCCA_TRACE_DEBUG((
        "DCCA: DCCADiaMessageHandler::SessionTerminationMessageHandling: " \
        "Context removed for session: %s ...", eve->sessId));

        return ITS_SUCCESS;
    }

    /**
     * Mark the context as invalid
     * It will automatically get deleted in corresponding timer expiry
     */
    pctx->mark = 1;
    DCCA_TRACE_DEBUG((
    "DCCA: DCCADiaMessageHandler::SessionTerminationMessageHandling: " \
    "Marked the session as invalid for session: %s ...", eve->sessId));
    
    /**
     * Update the context
     */
    if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
    DCCA_CONTEXT_MODIFY, pctx,key,len))
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::SessionTerminationMessageHandling: " \
        "Could not update context for session: %s ...", eve->sessId));
        return ITS_DIA_DCCA_ERROR; 
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *
 *  Purpose                : To handle ERR message
 *
 *  Input Parameters       : eve - The DCCA_EVENT
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
ITS_INT 
DCCADiaMessageHandler::ERRMessageHandling(DCCA_EVENT* eve)
{    
    DCCA_CONTEXT *pctx = NULL;
    ITS_OCTET* key = (ITS_OCTET*) eve->sessId;
    ITS_UINT len = strlen((char*)eve->sessId);
    
    if(ITS_SUCCESS == dccaContextTable->SubmitToCtx(
    DCCA_CONTEXT_FETCH, pctx, key,len))
    {
        DCCA_TRACE_DEBUG((
        "DCCA: DCCADiaMessageHandler::ERRMessageHandling: " \
        "Context fetched successfully for session: %s ...", eve->sessId));
                     
    }
    else 
    {
        return ITS_SUCCESS;
    }

    
    if( pctx->timer )
    {
        if(ITS_SUCCESS != TIMERS_CancelTimer(pctx->timerkey))
        {
            DCCA_TRACE_DEBUG((
            "DCCA: DCCADiaMessageHandler: ERRMessageHandling: " \
            "Could not stop timer Tx for session: %s ...", pctx->sessionId));
        }
        else
        {
            pctx->timer = 0;
            DCCA_TRACE_DEBUG((
            "DCCA: DCCADiaMessageHandler: ERRMessageHandling: " \
            "Timer Tx stopped for session: %s ...", pctx->sessionId));
        }
    }

    if(ITS_SUCCESS == dccaContextTable->SubmitToCtx(
    DCCA_CONTEXT_REMOVE , pctx, key,len))
        {
            DCCA_TRACE_DEBUG((
            "DCCA: DCCADiaMessageHandler::ERRMessageHandling: " \
            "Error command received and context cleared "
            "for session: %s ...", eve->sessId));
            // Previously DCCA_RELEASE_SESSION_IND was returned, 
            // now changed to ITS_SUCCESS
            return ITS_SUCCESS;
        }
        else
        {
            DCCA_TRACE_WARNING((
            "DCCA: DCCADiaMessageHandler::ERRMessageHandling: " \
            "Could not update context for session: %s ...", eve->sessId));
            return ITS_DIA_DCCA_ERROR; 
        }
    
    return ITS_SUCCESS;
}

/****************************************************************************
 *
 *  Purpose                : To handle CCR message
 *
 *  Input Parameters       : eve - The DCCA_EVENT
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
ITS_INT 
DCCADiaMessageHandler::CCRMessageHandling(DCCA_EVENT* eve)
{    
    /**
     * For server side CCR EVENT no fsm 
     */
    if( eve->dir && eve->typ == DCCA_EVE_REQUEST )
    {        
        return ITS_SUCCESS;    
    }

    /**
     * For all CCR UPDATE and TERMINATION 
     * fetch and submit to fsm and update context
     */    
    DCCA_CONTEXT ctx;
    DCCA_CONTEXT *pctx = NULL;

    ITS_OCTET* key = (ITS_OCTET*) eve->sessId;
    ITS_UINT len = strlen((char*)eve->sessId);

    if( eve->typ == DCCA_UPD_REQUEST || eve->typ == DCCA_TER_REQUEST )
    {
        if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
        DCCA_CONTEXT_FETCH, pctx,key,len))
        {
            DCCA_TRACE_WARNING((
            "DCCA: DCCADiaMessageHandler::CCRMessageHandling: " \
            "Could not fetch context for session: %s ...", eve->sessId));
            return ITS_DIA_UNKNOWN_SESSION_ID;             
        }
                     
        if (pctx->newlyReplicatedSession)
        {
            pctx->newlyReplicatedSession = ITS_FALSE;
        }

        ITS_UINT ret = dccaFsm->SubmitToFsm(eve, pctx);

        ITS_UINT retfromstc =  dccaContextTable->SubmitToCtx(ret, pctx,key,len);
        if (retfromstc != ITS_SUCCESS)
        {
            DCCA_TRACE_WARNING((
            "DCCA: DCCADiaMessageHandler::CCRMessageHandling: " \
            "Could not update context for session: %s ...", eve->sessId));
            return ITS_DIA_DCCA_ERROR; 
        }

        if( ret == DCCA_CONTEXT_REMOVE )
        {
            return DCCA_RELEASE_SESSION_IND;
        }
        return ITS_SUCCESS;
    }        

    /**
     * For client side CCR EVENT 
     */    
    if( eve->typ == DCCA_EVE_REQUEST )
    {
        memset(&ctx, 0x00, sizeof(ctx));
        ctx.state           = DCCA_FSM_STATE_IDLE;
        ctx.session         = eve->sin;        
        ctx.statemachine    = DCCA_CLIENT_FSM_EVE;
        ctx.applicationid   = eve->app;
        ctx.requestedaction = eve->act;
        ctx.requestType     = eve->typ;
        ctx.ccfh            = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_CCFH);
        ctx.clientId        = eve->clientId;
        strcpy((char *)ctx.sessionId, (char *)eve->sessId);
    }
    
    /**
     * For server side CCR INITIAL 
     */
    else if(eve->dir && eve->typ == DCCA_INI_REQUEST )
    {
        memset(&ctx, 0x00, sizeof(ctx));
        ctx.state           = DCCA_FSM_STATE_IDLE;
        ctx.session         = eve->sin;    
        ctx.statemachine    = DCCA_SERVER_FSM_SES;    
        ctx.applicationid   = eve->app;
        ctx.requestedaction = eve->act;
        ctx.requestType     = eve->typ;
        ctx.ccfh            = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_CCFH);
        ctx.clientId        = eve->clientId; 
        //Correcting Calling Risky Function
        strncpy((char *)ctx.sessionId, (char *)eve->sessId, SESSION_ID_LENGTH - 1);
    }
    
    /**
     * For client side CCR INITIAL 
     */
    else if(!eve->dir && eve->typ == DCCA_INI_REQUEST )
    {
        memset(&ctx, 0x00, sizeof(ctx));
        ctx.state           = DCCA_FSM_STATE_IDLE;
        ctx.session         = eve->sin;    
        ctx.statemachine    = DCCA_CLIENT_FSM_CCR;        
        ctx.applicationid   = eve->app;
        ctx.requestedaction = eve->act;
        ctx.requestType     = eve->typ;
        ctx.ccfh            = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_CCFH);
        ctx.clientId        = eve->clientId; 
        strcpy((char *)ctx.sessionId, (char *)eve->sessId);
    }

    /**
     * It should not come here
     */
    else
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::CCRMessageHandling: " \
        "Unknown CC-Request-Type for session: %s ...", eve->sessId));

        return ITS_DIA_DCCA_ERROR;
    }
    
    /**
     * For all CCR add and submit to fsm and update context
     */
    pctx = &ctx; // passing &ctx does not work ,hence passing as pointer.  
    if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
       DCCA_CONTEXT_ADD, pctx, key, len))
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::CCRMessageHandling: " \
        "Could not add context for session: %s ...", eve->sessId));
        return ITS_DIA_DCCA_ERROR; 
    }
                      
    ITS_UINT ret = dccaFsm->SubmitToFsm(eve, pctx);

    ITS_UINT retfromstc =  dccaContextTable->SubmitToCtx(ret, pctx,key,len);
    if(retfromstc == ITS_DIA_DCCA_ERROR)
    {
        return ITS_DIA_DCCA_ERROR;
    }
    else if (retfromstc != ITS_SUCCESS)
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::CCRMessageHandling: " \
        "Could not update context for session: %s ...", eve->sessId));
        return ITS_DIA_UNKNOWN_SESSION_ID;             
    } 

    if ( ret == DCCA_CONTEXT_REMOVE )
    {
        return DCCA_RELEASE_SESSION_IND;
    }
    return ITS_SUCCESS;
}

/****************************************************************************
 *
 *  Purpose                : To handle CCA message
 *
 *  Input Parameters       : eve - The DCCA_EVENT
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
ITS_INT 
DCCADiaMessageHandler::CCAMessageHandling(DCCA_EVENT* eve)
{    
    /**
     * For server side CCA EVENT no fsm
     */     
    if( !eve->dir && eve->typ == DCCA_EVE_REQUEST )
    {        
        //For Event based CCA Base Stack context should be removed.
        return DCCA_RELEASE_SESSION_IND;    
    }
        
    DCCA_CONTEXT *pctx = NULL;
    ITS_OCTET* key = (ITS_OCTET*) eve->sessId;
    ITS_UINT len = strlen((char*)eve->sessId);
    
    if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
    DCCA_CONTEXT_FETCH, pctx,key,len))
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::CCAMessageHandling: " \
        "Could not fetch context for session: %s ...", eve->sessId));
        return ITS_DIA_UNKNOWN_SESSION_ID;             
    }

    if(  eve->ccf != OUTSIDE_RANGE )
    {
        /**
         * CCFH is changed only when the CCFH is in CCA
         * Otherwise it is the configured value
         */
        pctx->ccfh = eve->ccf;
    }
                 
    if (pctx->newlyReplicatedSession)
    {
        pctx->state = DCCA_FSM_STATE_PENU;
        pctx->newlyReplicatedSession = ITS_FALSE;
    }

    ITS_UINT ret   = dccaFsm->SubmitToFsm(eve, pctx);
    /* client Id not set, set it for the 1st answer received from App.*/
    if (pctx->clientId == 0 && 
       (eve->dir == 0 && eve->typ == DCCA_INI_REQUEST))
    {
       pctx->clientId = eve->clientId; 
    }

    ITS_UINT retfromstc =  dccaContextTable->SubmitToCtx(ret, pctx,key,len);
    if(retfromstc == ITS_DIA_DCCA_ERROR)
    {
        return ITS_DIA_DCCA_ERROR;
    }
    else if (retfromstc != ITS_SUCCESS)
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::CCAMessageHandling: " \
        "Could not update context for session: %s ...", eve->sessId));
        return ITS_DIA_UNKNOWN_SESSION_ID;             
    }

    if ( ret == DCCA_CONTEXT_REMOVE)
    {
        return DCCA_RELEASE_SESSION_IND;
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *
 *  Purpose                : To handle AAR message
 *
 *  Input Parameters       : eve - The DCCA_EVENT
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
ITS_INT 
DCCADiaMessageHandler::AARMessageHandling(DCCA_EVENT* eve)
{    
#if 0
    /**
     * It should not come here
     */
    if( eve->dir )
    {    
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::AARMessageHandling: " \
        "Unknown message for session: %s ...", eve->sessId));

        return ITS_DIA_UNKNOWN_SESSION_ID;    
    }
    
    /**
     * For AAR with RE_AUTHORIZATION
     */
    if( eve->ccl == DCCA_RE_AUTHORIZATION )
    {
        return ITS_SUCCESS;
    }

    /**
     * It should not come here
     */
    if( eve->ccl != DCCA_CREDIT_AUTHORIZATION )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::AARMessageHandling: " \
        "Unknown CreditControl for session: %s ...", eve->sessId));

        return ITS_DIA_UNKNOWN_SESSION_ID;    
    }

    /**
     * For all AAR with CREDIT_AUTHORIZATION
     */
    DCCA_CONTEXT ctx;
    memset(&ctx, 0x00, sizeof(ctx));

    ctx.state         = DCCA_FSM_STATE_IDLE;
    ctx.session       = eve->sin;    
    ctx.statemachine  = DCCA_CLIENT_FSM_AAA;
    ctx.applicationid = eve->app;
    
    DCCA_CONTEXT *pctx = NULL;
    ITS_OCTET* key = (ITS_OCTET*) eve->sessId;
    ITS_UINT len = strlen((char*)eve->sessId);
    
    /**
     * For all AAR add and submit to fsm and update context
     */
    pctx = &ctx;
    if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
    DCCA_CONTEXT_ADD, pctx,key,len))
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::AARMessageHandling: " \
        "Could not add context for session: %s ...", eve->sessId));
        return ITS_DIA_UNKNOWN_SESSION_ID;             
    }

    ret = dccaFsm->SubmitToFsm(eve, pctx);

    ITS_UINT retfromstc =  dccaContextTable->SubmitToCtx(ret, pctx,key,len);
    if(retfromstc == ITS_DIA_DCCA_ERROR)
    {
        return ITS_DIA_DCCA_ERROR;
    }
    elseif (retfromstc != ITS_SUCCESS)
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::AARMessageHandling: " \
        "Could not update context for session: %s ...", eve->sessId));
        return ITS_DIA_UNKNOWN_SESSION_ID;             
    }
 
    if ( ret == DCCA_CONTEXT_REMOVE)
    {
        return DCCA_RELEASE_SESSION_IND;
    }
    
#endif
    return ITS_SUCCESS;
}

/****************************************************************************
 *
 *  Purpose                : To handle AAA message
 *
 *  Input Parameters       : eve - The DCCA_EVENT
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
ITS_INT 
DCCADiaMessageHandler::AAAMessageHandling(DCCA_EVENT* eve)
{
#if 0
    /**
     * It should not come here
     */
    if( eve->dir )
    {    
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::AAAMessageHandling: " \
        "Unknown message for session: %s ...", eve->sessId));

        return ITS_DIA_UNKNOWN_SESSION_ID;    
    }
    
    /**
     * For AAA with RE_AUTHORIZATION
     */
    if( eve->ccl == DCCA_RE_AUTHORIZATION )
    {
        return ITS_SUCCESS;
    }
    
    /**
     * It should not come here
     */
    if( eve->ccl != DCCA_CREDIT_AUTHORIZATION )
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::AAAMessageHandling: " \
        "Unknown CreditControl for session: %s ...", eve->sessId));

        return ITS_DIA_UNKNOWN_SESSION_ID;    
    }

    /**
     * For all other AAA fetch and submit to fsm and update context
     */    
    DCCA_CONTEXT *pctx = NULL;
    ITS_OCTET* key = (ITS_OCTET*) eve->sessId;
    ITS_UINT len = strlen((char*)eve->sessId);

    if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
    DCCA_CONTEXT_FETCH, pctx,key,len))
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::AAAMessageHandling: " \
        "Could not fetch context for session: %s ...", eve->sessId));
        return ITS_DIA_UNKNOWN_SESSION_ID;             
    }
        
    ITS_UINT ret = dccaFsm->SubmitToFsm(eve, pctx);

    ITS_UINT retfromstc =  dccaContextTable->SubmitToCtx(ret, pctx,key,len);
    if(retfromstc == ITS_DIA_DCCA_ERROR)
    {
        return ITS_DIA_DCCA_ERROR;
    }
    elseif (retfromstc != ITS_SUCCESS)
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCADiaMessageHandler::AAAMessageHandling: " \
        "Could not update context for session: %s ...", eve->sessId));
        return ITS_DIA_UNKNOWN_SESSION_ID;             
    }

    if ( ret == DCCA_CONTEXT_REMOVE)
    {
        return DCCA_RELEASE_SESSION_IND;
    }

#endif
    return ITS_SUCCESS;
}

/****************************************************************************
 *
 *  Purpose                : To handle DIA message
 *
 *  Input Parameters       : event - The message to handle
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCADiaMessageHandler:: HandleMessage(DIAThread *thr, its::Event &event)
{    
    DCCA_EVENT *eve = (DCCA_EVENT*)event.GetData();
    
    /**
     * Handle indications only
     */
    if(eve->ind)
    {
        return IndicationMessageHandling(eve);
    }

    // Following code removed. Error messages are not handled any different.
    // They are handled like normal responses. In most cases when error occurs
    // CCR-T needs to go. Deletion of DCCA Context will not allow this to 
    // happen. Changed for Cap-Ro translator for Transatel
#if 0
    /**
     * Handle ERR
     */
    if( eve->err )
    {
        return ERRMessageHandling(eve);
    }
#endif

    /**
     * Handle CCR
     */
    if( eve->req && eve->cmd == DCCA_COMMAND_CCR )
    {
        return CCRMessageHandling(eve);
    }
    
    /**
     * Handle CCA
     */
    if( !eve->req && eve->cmd == DCCA_COMMAND_CCA )
    {
        return CCAMessageHandling(eve);
    }
#if 0
    /**
     * Handle AAR
     */
    if( eve->req && eve->cmd == DCCA_COMMAND_AAR )
    {
        return AARMessageHandling(eve);
    }
    
    /**
     * Handle AAA
     */
    if( !eve->req && eve->cmd == DCCA_COMMAND_AAA )
    {
        return AAAMessageHandling(eve);
    }
#endif
    /**
     * Handle  STA,
     */
    if( eve->cmd == DCCA_COMMAND_STA 
        && (eve->req == 0)
        && (eve->dir == 1))
    {
        return SessionTerminationMessageHandling(eve);
    }

    /**
     * RAR, RAA and other messages we do not process
     */
    return ITS_SUCCESS;
}

/****************************************************************************
 *
 *  Purpose                : Constructor
 *
 *  Input Parameters       : dccaFsm          - DCCAFsm object
 *                           dccaContextTable - DCCAContextTable object
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
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
DCCATimerMessageHandler::DCCATimerMessageHandler(
DCCAFsm *dccaFsm, DCCAContextTable *dccaContextTable)
:MessageHandler(ITS_TIMER_SRC)
{    
    this->dccaFsm          = dccaFsm;
    this->dccaContextTable = dccaContextTable;
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
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
DCCATimerMessageHandler::~DCCATimerMessageHandler()
{
    dccaFsm          = NULL;
    dccaContextTable = NULL;
}

/****************************************************************************
 *
 *  Purpose                : To handle timer message
 *
 *  Input Parameters       : event - The message to handle
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCATimerMessageHandler::HandleMessage(DIAThread *thr, its::Event &event)
{
    ITS_TimerData *tmd = (ITS_TimerData*)event.GetData();    
    ITS_UINT indic = 0;

    /**
     * For all time out remove context
     */
    DCCA_CONTEXT ctx;
    memset(&ctx, 0x00, sizeof(ctx));
    memcpy((char*)&ctx, (char*)tmd->context, sizeof(DCCA_CONTEXT));
    
    DCCA_CONTEXT *pctx = NULL;
    ITS_OCTET *key = (ITS_OCTET*)ctx.sessionId;
    ITS_UINT len   = strlen ((char*)ctx.sessionId);        

    /**
     * Fetch the context
     */
    if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
    DCCA_CONTEXT_FETCH, pctx,key,len))
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCATimerMessageHandler::HandleMessage: " \
        "Could not fetch context for session: %s ...", ctx.sessionId));
        return ITS_DIA_UNKNOWN_SESSION_ID;             
    }        

    indic = pctx->timer ;
    /**
     * Identify the type of timeout 
     */
    if( pctx->timer == DCCA_TIMER_TX_TIME_OUT )
    {
        DCCA_TRACE_DEBUG((
        "DCCA: DCCATimerMessageHandler::HandleMessage: " \
        "Tx timeout for session: %s ...", ctx.sessionId));
    }
    else if( pctx->timer == DCCA_TIMER_TCC_TIME_OUT )
    {    
        DCCA_TRACE_DEBUG((
        "DCCA: DCCATimerMessageHandler::HandleMessage: " \
        "Tcc timeout for session: %s ...", ctx.sessionId));
    }

    /**
     * For contexts that are already marked as invalid
     * do not indicate to application
     */
    if(pctx->mark)
    {
        DCCA_TRACE_DEBUG((
        "DCCA: DCCATimerMessageHandler::HandleMessage: " \
        "Timer expired but the indication is not given to application "
        "due to base protocol sessions termination sequence "
        "for session: %s ...", ctx.sessionId));

        if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
        DCCA_CONTEXT_REMOVE , pctx,key,len))
        {
            DCCA_TRACE_WARNING((
            "DCCA: DCCATimerMessageHandler::HandleMessage: " \
            "Could not remove context for session: %s ...", 
            ctx.sessionId));
            return ITS_DIA_UNKNOWN_SESSION_ID;             
        }

        DCCA_TRACE_WARNING((
        "DCCA: DCCATimerMessageHandler::HandleMessage: " \
        "State changed to Idle for session: %s ...", 
        ctx.sessionId));
                 
        return ITS_SUCCESS;
    }

    /**
     * Some peculiar handling; Here we depend on base protocol
     * session timeout for clearing the context
     */
        if(  pctx->timer == DCCA_TIMER_TX_TIME_OUT && 
             pctx->requestType == DCCA_EVE_REQUEST )
        {
            if( pctx->requestedaction == DCCA_DIRECT_DEBITING )
            {
                  pctx->timer = 0;
                  if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
                  DCCA_CONTEXT_MODIFY, pctx,key,len))
                  {
                       DCCA_TRACE_WARNING((
                       "DCCA: DCCATimerMessageHandler::HandleMessage: " \
                       "Could not fetch context for session: %s ...",
                       ctx.sessionId));
                       return ITS_DIA_UNKNOWN_SESSION_ID;
                  }

                   /**
                    * The event Tx expired; requested action
                    * DIRECT_DEBITING has occured
                    */
                   DCCA_TRACE_DEBUG((
                   "DCCA: DCCATimerMessageHandler::HandleMessage: " \
                   "Tx expired with Requested-Action DIRECT_DEBITING; " \
                   "Remaining in same state for session: %s ...",
                   ctx.sessionId));
                   goto _RETURN_;
                   //return ITS_SUCCESS;

            }
        }


    if( pctx->timer == DCCA_TIMER_TX_TIME_OUT &&
            pctx->requestType != DCCA_EVE_REQUEST)
    {    
        /**
         * Mark the timer as invalid and update the context
         * only if the context is persisted even after timeout
         */
        if( pctx->ccfh == DCCA_CCFH_CONTINUE   || 
                    pctx->ccfh == DCCA_CCFH_RETRY_TERMINATE )
        {
            pctx->timer = 0;

            // Move to open state to allow retries or CCR-T
            pctx->state = DCCA_FSM_STATE_OPEN;

            if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
            DCCA_CONTEXT_MODIFY, pctx,key,len))
            {
                DCCA_TRACE_WARNING((
                "DCCA: DCCATimerMessageHandler::HandleMessage: " \
                "Could not fetch context for session: %s ...", 
                ctx.sessionId));
                return ITS_DIA_UNKNOWN_SESSION_ID;             
            }        

            /**
             * The event Tx expired and CCFH equal to
             * CONTINUE or to RETRY_AND_TERMINATE
             */
            DCCA_TRACE_DEBUG((
            "DCCA: DCCATimerMessageHandler::HandleMessage: " \
            "Tx expired with CCFH equal to %d; " \
            "Moving to OPEN state for session: %s ...", 
            ctx.ccfh, ctx.sessionId));

            goto _RETURN_;
            //return ITS_SUCCESS;
        }
        else if ( pctx->ccfh == DCCA_CCFH_TERMINATE )
        {
            pctx->timer = 0;
            /* moving the state to OPEN after sending out CCR-I/U
             * upon timeout so that CCR-T can be sent */
            pctx->state = DCCA_FSM_STATE_OPEN;

            /* moving to another state(DCCA_CLIENT_FSM_FIN if only CCR-I 
             * is sent, for CCR-U statemachine will already be in 
             * DCCA_CLIENT_FSM_FIN*/
            if( pctx->requestType == DCCA_INI_REQUEST)
                pctx->statemachine = DCCA_CLIENT_FSM_FIN;

            if(ITS_SUCCESS != dccaContextTable->SubmitToCtx(
            DCCA_CONTEXT_MODIFY, pctx,key,len))
            {
                DCCA_TRACE_WARNING((
                "DCCA: DCCATimerMessageHandler::HandleMessage: " \
                "Could not fetch context for session: %s ...", 
                ctx.sessionId));
                return ITS_DIA_UNKNOWN_SESSION_ID;             
            }       

            /**
             * The event Tx expired and CCFH equal to
             * TERMINATE
             */
            DCCA_TRACE_DEBUG((
            "DCCA: DCCATimerMessageHandler::HandleMessage: " \
            "Tx expired with CCFH equal to %d; " \
            "moving to Open state for session: %s ...", 
            ctx.ccfh, ctx.sessionId));


            goto _RETURN_;
        }

    }
    
    /**
     * Normal timeout and remove the context
     */
    if(ITS_SUCCESS == dccaContextTable->SubmitToCtx(
    DCCA_CONTEXT_REMOVE, pctx,key,len))
    {
        DCCAReleaseStackSessionWithSessionId(pctx->sessionId);
    }
    else
    {
        DCCA_TRACE_WARNING((
        "DCCA: DCCATimerMessageHandler::HandleMessage: " \
        "Could not remove context for session: %s ...", 
        ctx.sessionId));
        return ITS_DIA_UNKNOWN_SESSION_ID;             
    }
    
    /**
     * Indicate the user about timeout
     */
    DCCA_TRACE_WARNING((
    "DCCA: DCCATimerMessageHandler::HandleMessage: " \
    "State changed to Idle for session: %s ...", 
    ctx.sessionId));

_RETURN_:
    DCCA_TRACE_DEBUG((
    "DCCA: DCCATimerMessageHandler::HandleMessage: " \
    "Sending timeout indication to application " \
    "for session: %s ...", pctx->sessionId));

    if(pctx->timer == 0)
    {
        pctx->timer = indic;
    }
    return DCCACommon::SendIndicationToApp(pctx->timer, pctx->sessionId, 
              pctx->applicationid, pctx->session, pctx->clientId);
}

/****************************************************************************
 *
 *  Purpose                : Constructor
 *
 *  Input Parameters       : dccaFsm          - DCCAFsm object
 *                           dccaContextTable - DCCAContextTable object
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
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
DCCAMessageHandler::DCCAMessageHandler(
DCCAFsm *dccaFsm, DCCAContextTable *dccaContextTable)
{
    dccaDiaMessageHandler   = 
        new DCCADiaMessageHandler(dccaFsm, dccaContextTable);
    dccaTimerMessageHandler = 
        new DCCATimerMessageHandler(dccaFsm, dccaContextTable);    
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
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
DCCAMessageHandler::~DCCAMessageHandler()
{
    delete dccaDiaMessageHandler;
    delete dccaTimerMessageHandler;

    dccaDiaMessageHandler   = NULL;
    dccaTimerMessageHandler = NULL;
}

/****************************************************************************
 *
 *  Purpose                : To handle DCCA message
 *
 *  Input Parameters       : eve - DCCA_EVENT
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAMessageHandler::HandleMessage(DCCA_EVENT *eve)
{
    /**
     * Prepare an ITS_EVENT from DCCA_EVENT
     */
    its::Event obj; 
    obj.SetSource(ITS_DIA_SRC);
    obj.SetData((ITS_OCTET*)eve, sizeof(DCCA_EVENT));

    ITS_UINT ret = dccaDiaMessageHandler->HandleMessage(0,obj);
    if(ret == DCCA_RELEASE_SESSION_IND)
    {
        eve->releaseSession = true;
        return ITS_SUCCESS;
    }
    else if ( ret == ITS_DIA_DCCA_ERROR )
    {
        /* Below release session needs to be uncommented after
         * the decision that state machine error should release
         * the Base stack session immediately
         */
        //eve->releaseSession = true;
    }
  
    return ret;
        
}

/****************************************************************************
 *
 *  Purpose                : To get message handler
 *
 *  Input Parameters       : type - The type of message handler
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : MessageHandler* or NULL
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
MessageHandler* 
DCCAMessageHandler::DCCAGetMessageHandler(ITS_USHORT type)
{
    if( type == ITS_DIA_SRC )
    {
        return dccaDiaMessageHandler;
    }

    if( type == ITS_TIMER_SRC )
    {
        return dccaTimerMessageHandler;
    }

    return NULL;
 }
