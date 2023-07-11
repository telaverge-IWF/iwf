/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 2004 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 *
 *  ID: $Id: app_handl_msg.c,v 9.1 2005/03/23 12:54:28 cvsadmin Exp $
 *
 *  $Log: app_handl_msg.c,v $
 *  Revision 9.1  2005/03/23 12:54:28  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.12  2005/03/21 13:53:27  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.11.2.3  2005/02/16 14:16:53  mkrishna
 *  added BYE message.
 *
 *  Revision 1.11.2.2  2005/02/07 14:16:04  mkrishna
 *  Modified for PRACK message.
 *
 *  Revision 1.11.2.1  2004/12/28 14:04:09  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.11  2004/09/08 05:43:50  mkrishna
 *  More cleanup(akumar).
 *
 *  Revision 1.10  2004/09/07 10:59:12  akumar
 *  This file has functions for handling SIP msg received from STACK.
 *
 *
 ****************************************************************************/

#include <stdio.h>
#include <sip_defines.h>
#include <sip.h>

#include "app_sendmsg.h"

/* Function Declaration */
int
APP_HandleINVITEIndication(ITS_HANDLE handle, ITS_EVENT *event);
int
APP_Handle200OkIndication(ITS_HANDLE handle, ITS_EVENT *event);
int
APP_Handle302Indication(ITS_HANDLE handle, ITS_EVENT *event);
int
APP_Handle481Indication(ITS_HANDLE handle, ITS_EVENT *event);
int
APP_Handle504Indication(ITS_HANDLE handle, ITS_EVENT *event);
int
APP_HandleOPTIONSIndication(ITS_EVENT *event);
int
APP_HandlePRACKIndication(ITS_EVENT *event);

SIP_MSG *sip_last_msg = NULL;
SIP_MSG *sip_prov_msg = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose: This function checks message inside event and calls appropriate
 *  function to handle the msg.  
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
APP_ReceiveMsg(ITS_HANDLE handle, ITS_EVENT *event)
{
   ITS_OCTET                     msgId;
   SIP_EVENT_TYPE                evType;
   SIP_ERROR_TYPE                errType;
   SIP_PARSER_ERROR_DATA         *parseErrData;
   SIP_ERROR_DATA                *errData;
   SIP_TRANSACTION_ERROR_DATA    *trnErrData;
   SIP_TRANSPORT_ERROR_DATA      *tranErrData;
   SIP_INDICATION_DATA           *indData;
   SIP_TIMEOUT_DATA              *timeoutData;

    /* Get Event type, whether INVITE, 180 etc */
    evType = SIP_GetEventType(event);

    switch(evType)
    {
    case SIP_DATA_EVENT:
        msgId = SIP_GetMsgType(event);
        switch(msgId)
        {
        case SIP_MSG_REGISTER:
            printf("\nReceived message::: REGISTER \n");
            sip_last_msg=(SIP_MSG *)SIP_GET_MSG_INFO((SIP_GET_SIPEVENT(event)));
            break;

        case SIP_MSG_BYE:
            printf("\nReceived message::: BYE \n");
            sip_last_msg=(SIP_MSG *)SIP_GET_MSG_INFO((SIP_GET_SIPEVENT(event)));
            break;

        case SIP_MSG_INVITE:
            printf("\nReceived message::: INVITE \n");
            APP_HandleINVITEIndication(handle, event);
            sip_last_msg=(SIP_MSG *)SIP_GET_MSG_INFO((SIP_GET_SIPEVENT(event)));
            break;

        case SIP_MSG_ACK:
            printf("\nReceived message::: ACK \n");
            /* Received ACK means endof transaction */
            SIP_MsgFree(sip_last_msg);
            sip_last_msg = NULL;
            break;

        case SIP_MSG_OPTIONS:
            printf("\nReceived message::: OPTIONS \n");
            APP_HandleOPTIONSIndication(event);
            break;

        case SIP_MSG_PRACK:
            printf("\nReceived message::: PRACK \n");
            APP_HandlePRACKIndication(event);
            break;

        case SIP_MSG_100:
            printf("\nReceived message::: 100 \n");
            SIP_MsgFree((SIP_MSG *)SIP_GET_MSG_INFO((SIP_GET_SIPEVENT(event))));
            break;

        case SIP_MSG_180:
            printf("\nReceived message::: 180 \n");
            sip_prov_msg=(SIP_MSG *)SIP_GET_MSG_INFO((SIP_GET_SIPEVENT(event)));
           /* SIP_MsgFree((SIP_MSG *)SIP_GET_MSG_INFO((SIP_GET_SIPEVENT(event)))); */
            break;

        case SIP_MSG_200:
            printf("\nReceived message::: 200 \n");
            APP_Handle200OkIndication(handle, event);
            sip_last_msg=(SIP_MSG *)SIP_GET_MSG_INFO((SIP_GET_SIPEVENT(event)));
            if (sip_prov_msg)
            {
                SIP_MsgFree(sip_prov_msg);
                sip_prov_msg = NULL;
            }
            break;

        case SIP_MSG_302:
            printf("\nReceived message::: 302 \n");
            APP_Handle302Indication(handle, event);
            break;

        case SIP_MSG_481:
            printf("\nReceived message::: 481 \n");
            APP_Handle481Indication(handle, event);
            break;

        case SIP_MSG_504:
            printf("\nReceived message::: 504 \n");
            APP_Handle504Indication(handle, event);
            break;
 
        default:
            printf("\nReceived Unrecognized msg Id is %d \n", msgId);
            break;
        }
        break;
    case SIP_ERROR_EVENT:
        errData = SIP_ReceiveErrorData(handle, event);
        errType = SIP_GetErrorType(errData);

        switch(errType)
        {
        case SIP_PARSER_ERROR:
            printf("SIP_ERROR_EVENT:: Parser Error\n");
            parseErrData = SIP_GetParserError(errData);
            printf("SIP_ERROR_EVENT:: Parser Error is %d\n",
                                      parseErrData->errorCode);
            break;

        case SIP_TRANSPORT_ERROR:
            printf("SIP_ERROR_EVENT:: Transport Error\n");
            tranErrData = SIP_GetTransportError(errData);
            printf("SIP_ERROR_EVENT:: Transport errCode = %d,\
                                      localPort = %d remotePort = %d\n",
                                      tranErrData->errorCode,
                                      tranErrData->localPort,
                                      tranErrData->remotePort);
            break;

        case SIP_TRANSACTION_ERROR:
            printf("SIP_ERROR_EVENT:: Transaction Error\n");
            trnErrData = SIP_GetTransactionError(errData);
            printf("SIP_ERROR_EVENT:: Transaction ErrorCode = %d\n",
                                      trnErrData->reason);
            break;

        default:
            printf("SIP_ERROR_EVENT:: Unknown Error\n");
            break;
        }
        break;

    case SIP_INDICATION_EVENT:
        indData = SIP_ReceiveIndicationData(handle, event);
        printf("SIP_INDICATION_EVENT:: Indication Event Received, id = %d\n",
                                       indData->reason); 
        break;

    case SIP_TIMEOUT_EVENT:
        timeoutData = SIP_ReceiveTimeoutData(handle, event);
        printf("SIP_TIMEOUT_EVENT:: Timeout Event Received, reason = %d\n",
                                    timeoutData->reason);
        break;
    default:
        printf("\nReceived Unrecognized Event, ID is %d \n", evType);
        break;
    }
    
    /* FIXME - Free SIP msg after done with processing */

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: This function handle INVITE msg received from SIP Stack. 
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
APP_HandleINVITEIndication(ITS_HANDLE handle, ITS_EVENT *event)
{
    int ret;
    SIP_MSG *msg;
    SIP_EVENT *sipEvent;
    sipEvent = (SIP_EVENT *)event->data;
    msg = sipEvent->msg;

    ret = SIP_ReceiveMsg(handle, event, &msg);
    if (ret != ITS_SUCCESS)
    {
        printf("HandleINVITEIndication:: SIP_ReceiveMsg fail \n");
        return ret;
    }
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: This function handle 200OK msg received from SIP Stack. 
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
APP_Handle200OkIndication(ITS_HANDLE handle, ITS_EVENT *event)
{
    printf("APP_Handle200OkIndication:: Received 200 OK \n");
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: This function handle 302 msg received from SIP Stack. 
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
APP_Handle302Indication(ITS_HANDLE handle, ITS_EVENT *event)
{
    printf("APP_Handle302Indication:: Received 302 \n");
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: This function handle 481 msg received from SIP Stack.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
APP_Handle481Indication(ITS_HANDLE handle, ITS_EVENT *event)
{
    printf("APP_Handle481Indication:: Received 481 \n");
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: This function handle 504 msg received from SIP Stack.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
APP_Handle504Indication(ITS_HANDLE handle, ITS_EVENT *event)
{
    printf("APP_Handle504Indication:: Received 504 \n");
    return ITS_SUCCESS;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose: This function handles OPTIONS msg received from SIP Stack. 
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
APP_HandleOPTIONSIndication(ITS_EVENT *event)
{
    int ret, pos = 0;
    SIP_MSG *lastReq, *msgOk;
    SIP_HOST_INFO fromHostInfo, toHostInfo,  *host;
    SIP_URI_OBJ  fromUri, toUri;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;

    lastReq = (SIP_MSG *)SIP_GET_MSG_INFO((SIP_GET_SIPEVENT(event)));

    /* Build 200 OK and send to SIP stack */ 
    SIP_InitMsg(&msgOk);
    ret = SIP_SetStartLine(msgOk, "SIP/2.0", 200, "Ok", NULL, NULL);
    if (ret != ITS_SUCCESS)
    {
        printf("APP_Send200Ok:: SIP_SetStartLine fail \n");
        return ret;
    }

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, lastReq->from.url.hostInfo.type,
                    lastReq->from.url.hostInfo.address,
                    lastReq->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, lastReq->from.url.scheme, lastReq->from.url.userName,
               lastReq->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(msgOk, &fromUri, lastReq->from.displayName, NULL,
                      lastReq->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetHostinfo(&toHostInfo, lastReq->to.url.hostInfo.type,
                    lastReq->to.url.hostInfo.address,
                    lastReq->to.url.hostInfo.port);
    SIP_SetUri(&toUri, lastReq->to.url.scheme, lastReq->to.url.userName,
               lastReq->to.url.password, &toHostInfo);
    SIP_SetToHeader(msgOk, &toUri, lastReq->to.displayName, NULL,
                      lastReq->to.numGenparams, NULL);

    SIP_SetCallidHeader(msgOk, lastReq->callId.number, lastReq->callId.host);
    SIP_SetCseqHeader(msgOk, lastReq->cseq.number, lastReq->cseq.method);

    /* Set Content type and content length aswell for 200 OK
    SIP_SetContentlenHeader(msgOk, lastReq->contentLen.value);  */

    while (!SIP_LISTEol(lastReq->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(lastReq->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        if (numViaparams != 0)
        {
            SIP_SetViaHeader(msgOk, version, protocol, host,
                             numViaparams, *genParam);
        }
        else
        {
            SIP_SetViaHeader(msgOk, version, protocol, host,
                             0, NULL);
        }
        pos++;
    }

    /* Add the headers, what UAS is going to Allow/Options */
    SIP_SetAllowHeader(msgOk, "INVITE");
    SIP_SetAllowHeader(msgOk, "BYE");
    SIP_SetAllowHeader(msgOk, "CANCEL");
    SIP_SetAcceptHeader(msgOk, 0, 0, "application", "sdp", 0, NULL);
    SIP_SetAcceptEncodeHeader(msgOk, "gzip", 0, NULL);
    SIP_SetAcceptLanguageHeader(msgOk, "en", 0, NULL);
    SIP_SetSupportedHeader(msgOk, "100rel");
    SIP_SetUnsupportedHeader(msgOk, "foo");

    ret = SIP_SendResponse((ITS_HANDLE)itsINTELLISIP_Class, msgOk);
    if (ret == ITS_SUCCESS)
    {
        printf("200 Ok msg sent successfully to Stack\n");
    }

    /* Free Received msg */
    SIP_MsgFree(lastReq);

    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose: This function handles PRACK msg received from SIP Stack.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
APP_HandlePRACKIndication(ITS_EVENT *event)
{
    int ret, pos = 0;
    SIP_MSG *lastReq, *msgOk;
    SIP_HOST_INFO fromHostInfo, toHostInfo,  *host;
    SIP_URI_OBJ  fromUri, toUri;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;

    lastReq = (SIP_MSG *)SIP_GET_MSG_INFO((SIP_GET_SIPEVENT(event)));

    /* Build 200 OK and send to SIP stack */
    SIP_InitMsg(&msgOk);
    ret = SIP_SetStartLine(msgOk, "SIP/2.0", 200, "Ok", NULL, NULL);
    if (ret != ITS_SUCCESS)
    {
        printf("APP_Send200Ok:: SIP_SetStartLine fail \n");
        return ret;
    }

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, lastReq->from.url.hostInfo.type,
                    lastReq->from.url.hostInfo.address,
                    lastReq->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, lastReq->from.url.scheme, lastReq->from.url.userName,
               lastReq->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(msgOk, &fromUri, lastReq->from.displayName, NULL,
                      lastReq->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetHostinfo(&toHostInfo, lastReq->to.url.hostInfo.type,
                    lastReq->to.url.hostInfo.address,
                    lastReq->to.url.hostInfo.port);
    SIP_SetUri(&toUri, lastReq->to.url.scheme, lastReq->to.url.userName,
               lastReq->to.url.password, &toHostInfo);
    SIP_SetToHeader(msgOk, &toUri, lastReq->to.displayName, NULL,
                      lastReq->to.numGenparams, NULL);

    SIP_SetCallidHeader(msgOk, lastReq->callId.number, lastReq->callId.host);
    SIP_SetCseqHeader(msgOk, lastReq->cseq.number, lastReq->cseq.method);
    /* Set Content type and content length aswell for 200 OK
    SIP_SetContentlenHeader(msgOk, lastReq->contentLen.value);  */

    while (!SIP_LISTEol(lastReq->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(lastReq->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        if (numViaparams != 0)
        {
            SIP_SetViaHeader(msgOk, version, protocol, host,
                             numViaparams, *genParam);
        }
        else
        {
            SIP_SetViaHeader(msgOk, version, protocol, host,
                             0, NULL);
        }
        pos++;
    }

    /* Add the headers, what UAS is going to Allow/Options */
    SIP_SetAllowHeader(msgOk, "INVITE");
    SIP_SetAllowHeader(msgOk, "BYE");
    SIP_SetAllowHeader(msgOk, "CANCEL");
    SIP_SetAcceptHeader(msgOk, 0, 0, "application", "sdp", 0, NULL);
    SIP_SetAcceptEncodeHeader(msgOk, "gzip", 0, NULL);
    SIP_SetAcceptLanguageHeader(msgOk, "en", 0, NULL);

    ret = SIP_SendResponse((ITS_HANDLE)itsINTELLISIP_Class, msgOk);
    if (ret == ITS_SUCCESS)
    {
        printf("200 Ok msg sent successfully to Stack\n");
    }

    /* Free Received msg */
    SIP_MsgFree(lastReq);

    return ret;
}

