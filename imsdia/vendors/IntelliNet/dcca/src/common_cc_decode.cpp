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
 *
 *
 * LOG: $Log: common_cc_decode.cpp,v $
 * LOG: Revision 3.3.60.1.8.1.2.1  2014/06/26 10:17:41  millayaraja
 * LOG:  validation for CCFH avp values at the application
 * LOG:
 * LOG: Revision 3.3.60.1.8.1  2014/05/06 13:09:12  jkchaitanya
 * LOG: changes for ccfh feature
 * LOG:
 * LOG: Revision 3.3.60.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.3  2009/03/19 13:04:03  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.2  2008/12/12 18:06:08  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.10  2007/01/23 07:43:46  hbhatnagar
 * LOG: Fix for SendIndicationToApp:SessionIndex was missing
 * LOG:
 *                                                                          *
 *
 * ID: $Id: common_cc_decode.cpp,v 3.3.60.1.8.1.2.1 2014/06/26 10:17:41 millayaraja Exp $
 *
 ****************************************************************************
 */

#ident "$Id: common_cc_decode.cpp,v 3.3.60.1.8.1.2.1 2014/06/26 10:17:41 millayaraja Exp $"

#include <dia_cmn.h>
#include <dcca_common.h>
#include <dia_stack.h>
#include <itsdiameter.h>
#include <its_dia_config.h>

/**
 * Namespace
 */
#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

/****************************************************************************
 *
 *  Purpose                : To release the diameter stack session.
 *
 *  Input Parameters       : eve - The address of DCCA Event 
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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT DCCAReleaseStackSession(DCCA_EVENT *eve)
{
#ifdef _BCGI
    if (eve->releaseSession )
    {
        return DCCA_RELEASE_SESSION_IND;
    }  

#else 
    if ( eve->cmd == DCCA_COMMAND_CCA && 
         eve->req == 0                && 
         eve->typ == DCCA_EVE_REQUEST)
    {
        return DCCA_RELEASE_SESSION_IND; 
    }
#endif       
    return ITS_SUCCESS;
}


/****************************************************************************
 *
 *  Purpose                : To release the diameter stack session.
 *
 *  Input Parameters       : sessionId- ITS_OCTET* (Session String).
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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/

ITS_INT DCCAReleaseStackSessionWithSessionId(ITS_OCTET *sessionId)
{
#ifdef _BCGI
    DCCA_TRACE_DEBUG(("ReleaseSessionWithStack\n"));
    Event remev(DIA_APP_REM_SESS_INST, strlen((const char*)sessionId) + 1, sessionId);
    if (itsDiaConfig.IsMsgRedundancyEnabled())
    {
        remev.SetSource(DIA_GCS_APP_REM_SESS_INST);
    }
    its::Transport::PutEvent(DIASTACK_TQ_INST, remev);

    return DCCA_RELEASE_SESSION_IND;
#endif        
    return ITS_SUCCESS;
}

/****************************************************************************
 *
 *  Purpose                : To prepare DCCA_EVENT from diameter::Command
 *
 *  Input Parameters       : com - The command
 *
 *  Input/Output Parameters: eve - The event
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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/

ITS_INT CcDecode(DIA_BASE_CMD *gCmd, DCCA_EVENT *eve)
{
    try
    {
        //Warning Fix - suggest parentheses around assignment used as truth value
        if( (eve->req = gCmd->isRequest() ) !=0)
        {
        /**
         * CCR CC-Request-Type
         */
            if( DCCA_COMMAND_CCR == eve->cmd )
            {
                diameter::BaseCommand* implderived = (DIA_BASE_CMD*) gCmd;

                /**
                 * CCR CC-Request-Type
                 */
                int typ = 0;
                if(implderived->getAvpValue(CC_REQUEST_TYPE_AVP_CODE, &typ,
                                              diameter::EnumeratedType)==0)
                {
                    if (typ >= DCCA_INI_REQUEST && typ <= DCCA_EVE_REQUEST)
                        eve->typ = typ;
                    else
                        return ITS_DIA_INVALID_AVP_VALUE;
                }
                else
                {
                     DCCA_TRACE_DEBUG(("getAvpValue FAILED\n"));

                     /* This should return missing AVP code 5005
                      * ITS_DIA_MISSING_AVP
                      */
                     return ITS_DIA_MISSING_AVP; 
                } 
    
                /**
                 * CCR Requested-Action
                 */
                eve->act = OUTSIDE_RANGE;
                int act = 0; 
                if(implderived->getAvpValue(REQUESTED_ACTION_AVP_CODE, &act,
                                               diameter::EnumeratedType)==0)
                {   
                    /* Check the value of requested action 
                     * if not applicable return ITS_DIA_INVALID_AVP_VALUE
                     */
                    if (act >= DCCA_DIRECT_DEBITING && act <= DCCA_PRICE_ENQUIRY)
                        eve->act = act;
                    else
                        return ITS_DIA_INVALID_AVP_VALUE;
                }
            /* This clientId is for the distributed mode */
            eve->clientId = gCmd->getClientId();
            }
        }
        else if( !eve->req  ) /* Answer command */
        {
            if( DCCA_COMMAND_CCA == eve->cmd )
            {
                diameter::BaseCommand* implderived = (DIA_BASE_CMD*) gCmd;

                /**
                 * get CCR Result-Code from Base Generic command instead of
                 * getAvpValue 
                */
                if(gCmd->getResultCode())
                {
                    eve->cod = gCmd->getResultCode()->value();
                }
                else
                {
                     DCCA_TRACE_ERROR(("Result code Failed\n"));

                     /* if result code is not found return missing avp
                      * code 5005 ITS_DIA_MISSING_AVP
                      */ 
                     return ITS_DIA_MISSING_AVP;
                }

                /* The Request type AVP for CCA*/
                int typ = 0;
                if(implderived->getAvpValue(CC_REQUEST_TYPE_AVP_CODE, &typ,
                                              diameter::EnumeratedType)==0)
                {
                    if (typ >= DCCA_INI_REQUEST && typ <= DCCA_EVE_REQUEST)
                        eve->typ = typ;
                    else
                        return ITS_DIA_INVALID_AVP_VALUE;
                }
                else
                {
                    // For error messages, CC_REQUEST_TYPE may not be present
                    if (!eve->err)
                    {
                        DCCA_TRACE_DEBUG(("getAvpValue FAILED\n"));

                        /* This should return missing AVP code 5005
                         * return ITS_DIA_MISSING_AVP
                         */
                        return ITS_DIA_MISSING_AVP; 
                    }
                }
 
                /**
                 * CCA CCFH
                 */
                int ccf = 0;
                if(implderived->getAvpValue(CCFH_AVP_CODE, &ccf,
                                   diameter::EnumeratedType)==0)
                {
                    /* Check for the value whether it is a valid value
                     * if not return invalid AVP value code 5004
                     */

                     if (ccf >= DCCA_CCFH_TERMINATE && 
                         ccf <= DCCA_CCFH_RETRY_TERMINATE)
                     {
                         eve->ccf = ccf;
                     }
                     /* Received CCFH values is not valid, retain
                      * locally configured CCFH value in the event and send
                      * the message to Applicaiton */
                     else
                     {
                        DCCA_TRACE_WARNING(("Received invalid CCFH value :%d,retaining locally configured CCFH value",ccf));
                     }
                }

                /* This clientId is for the distributed mode */
                eve->clientId = gCmd->getClientId();
            }
        }
    }
    catch(...)
    {
        DCCA_TRACE_ERROR(("Unknown Exception Caught"));
        return ITS_DIA_DCCA_ERROR;
    }
    return ITS_SUCCESS;
}
