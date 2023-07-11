/***************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * CONTRACT: INTERNA                                                        *
 *                                                                          *
 ****************************************************************************
 *  ID:$Id  $
 *
 *  $Log: app_lib.c,v $
 *  Revision 9.1  2005/03/23 12:54:28  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.17  2005/03/21 13:53:27  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.16.2.5  2005/02/18 05:08:21  mkrishna
 *  Bug fix
 *
 *  Revision 1.16.2.4  2005/02/16 14:10:12  mkrishna
 *  added CANCEL, BYE, REGISTER msg's
 *
 *  Revision 1.16.2.3  2005/02/09 10:43:20  mkrishna
 *  Added contact header in INVITE and final 200 OK messages
 *
 *  Revision 1.16.2.2  2005/02/07 14:18:27  mkrishna
 *  Modified for PRACK message.
 *
 *  Revision 1.16.2.1  2004/12/28 14:04:09  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.16  2004/09/07 10:31:58  mkrishna
 *  Added function history blocks.
 *
 *  Revision 1.15  2004/06/28 07:42:35  sjaddu
 *  Load test added and SIP_StackHandle also added.
 *
 ****************************************************************************/
#include <stdio.h>

#include <its.h>
#include <engine.h>
#include <its_app.h>
#include <its_timers.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_thread_pool.h>
#include <its_worker.h>

#include <sip_defines.h>
#include <app_sendmsg.h>

extern int
APP_ReceiveMsg(ITS_HANDLE handle, ITS_EVENT *event);
int APP_SendInvite();

ITS_SHORT thrInstance = 0;

/*.implementation:static
 ****************************************************************************
 *  Purpose: WorkerThreadDispatchFunction to receive incoming events from SIP 
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
static void
WorkerThreadDispatchFunction(TPOOL_THREAD *thr, ITS_HANDLE handle)
{
    ITS_USHORT workerInstance;
    ITS_EVENT event;
    ITS_INT ret;

    WORKER_Control* worker = (WORKER_Control*)thr;
    workerInstance = worker->worker.instance;
    printf("Application:: Instance Number of Worker is ... %d\n",workerInstance);
    while (1)
    {
        event.data = 0;
        ret = WORKER_GetNextEvent(worker, &event);
        if (ret != ITS_SUCCESS)
        {
            printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
        }

        if ( event.src == ITS_SIP_SRC )
        {
            printf("Application:: Worker Thread: SIP msg receive success\n");
            APP_ReceiveMsg(SIP_StackHandle, &event);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: PreFunc is an application registered Callback, which is invoked
 *  as application initialization routine. 
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
void AppPreFunc(void)
{
    ITS_INT ret = 0;
    TPOOL_THREAD* thread = NULL;

    ITS_HDR routeHeader;

    routeHeader.context.cic = 0;


    if((ret = TPOOL_GetFirstAvailThread(workerPool, &thread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        thrInstance= ITS_INVALID_SRC;
    }

    printf("Ftest: RouteApp: Dispatching worker thread\n");

    ret = TPOOL_DispatchOnThread(thread,WorkerThreadDispatchFunction,
                                       WORKER_BACK_PTR(thread));
    if (ret != ITS_SUCCESS)
    {
        thrInstance = ITS_INVALID_SRC;
    }
    else
    {
        thrInstance = ( ((WORKER_Control*)thread)->worker.instance );
    }
    printf("---- Started SIP application \n");
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: RouteApp is an application selector, used for routing msg from
 *  SIP Stack. 
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
RouteApp(ITS_HDR *hdr,ITS_EVENT *event)
{
#if 0
    ITS_INT ret = 0;
    TPOOL_THREAD* thread = NULL;

    ITS_HDR routeHeader;

    routeHeader.context.cic = hdr->context.cic;


    if((ret = TPOOL_GetFirstAvailThread(workerPool, &thread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        return ITS_INVALID_SRC;
    }

    printf("Ftest: RouteApp: Dispatching worker thread\n");

    ret = TPOOL_DispatchOnThread(thread,WorkerThreadDispatchFunction,
                                       WORKER_BACK_PTR(thread));
    if (ret != ITS_SUCCESS)
    {
        return ITS_INVALID_SRC;
    }
    else
    {
        return ( ((WORKER_Control*)thread)->worker.instance );
    }
#endif

    return  thrInstance;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose: Sends Invite to SIP Stack. 
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
TestSendInvite(char *callId, char *remHost, char *remPort , char *lhost,
                    char *lport)
{
    SIP_MSG *msg;
    SIP_URI_OBJ uriObj, contactUri;
    SIP_HOST_INFO hostInfo, frmHostInfo, viaHostInfo, contactHostInfo;
    int ret;
    SIP_CONTENTTYPE_INFO contentTypeInfo;

    ret = SIP_InitMsg(&msg);
    if (ret == ITS_SUCCESS)
    {
        printf("\n$$ SIP INIT successful $$\n");
    }
    /* Build startline */
    SIP_SetHostinfo(&hostInfo, 1, remHost, remPort);
    /* Set req URI for the startline */
    SIP_SetUri(&uriObj, "sip", "suresh", NULL, &hostInfo);

    SIP_SetStartLine(msg, "SIP/2.0", 0, NULL, "INVITE", &uriObj);

    /* Set To Header */
    SIP_SetToHeader(msg, &uriObj, "Bob", NULL, 0, NULL);

    /* Set HostInfo for from Header */
    SIP_SetHostinfo(&frmHostInfo, 1, lhost, lport);
    SIP_SetUri(&uriObj, "sip", "alice", NULL, &frmHostInfo);
    SIP_SetFromHeader(msg, &uriObj, "Alice", "1928301774", 0, NULL);

    SIP_SetCallidHeader(msg, callId, remHost);
    SIP_SetCseqHeader(msg, 314159, "INVITE");

    SIP_SetContentTypeInfo(&contentTypeInfo, "application",
                             "sdp", NULL, 0, NULL);
    SIP_SetContentHeader(msg, &contentTypeInfo, 100, NULL);

    SIP_SetHostinfo(&viaHostInfo, 1, lhost, lport);
    SIP_SetViaHeader(msg, "2.0", "UDP", &viaHostInfo, 0, NULL);

    /* Send Contact(s), Add carefully */
    SIP_SetHostinfo(&contactHostInfo, SIP_HOST_TYPE_HOSTNAME,
                    "intellinet-india.com", NULL);
    SIP_SetUri(&contactUri, "sip", "227", NULL, &contactHostInfo);
    SIP_SetContactHeader(msg, &contactUri, "Arun", NULL, 0, NULL);
/*
    SIP_SetRquireHeader(msg, "100rel");
    SIP_SetSupportedHeader(msg, "100rel"); 
*/
    ret = SIP_SendRequest(SIP_StackHandle, msg);
    if ( ret == -1)
    {
        /* Free SIP_MSG */
        SIP_MsgFree(msg);
        return ret;
    }
    else if (ret == ITS_EMISSINGMANDHDR)
    {
        /* Free SIP_MSG */
        SIP_MsgFree(msg);
        printf("Failed ret = %d \n", ret );
        return ret;
    }
    sip_last_msg = msg;

    printf("\n$$ INVITE msg sent successfuly to STACK $$$ \n\n");
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: This function will send Cancel message to STACK
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
TestSendCancel(SIP_MSG *lastResp)
{
    SIP_MSG *cancelMsg;
    int ret = 0, pos = 0;
    SIP_HOST_INFO fromHostInfo, toHostInfo,  *host;
    SIP_URI_OBJ fromUri, toUri;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;

    SIP_InitMsg(&cancelMsg);
    /* start line must */

    /* Set hostInfo for the startline */

    SIP_SetHostinfo(&toHostInfo, lastResp->to.url.hostInfo.type,
                    lastResp->to.url.hostInfo.address,
                    lastResp->to.url.hostInfo.port);
    SIP_SetUri(&toUri, lastResp->to.url.scheme, lastResp->to.url.userName,
               lastResp->to.url.password, &toHostInfo);

    SIP_SetStartLine(cancelMsg, lastResp->sipVersion, 0, NULL, "CANCEL", &toUri);

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, lastResp->from.url.hostInfo.type,
                    lastResp->from.url.hostInfo.address,
                    lastResp->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, lastResp->from.url.scheme, lastResp->from.url.userName,
               lastResp->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(cancelMsg, &fromUri, lastResp->from.displayName, NULL,
                      lastResp->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetToHeader(cancelMsg, &toUri, lastResp->to.displayName, NULL,
                      lastResp->to.numGenparams, NULL);

    SIP_SetCallidHeader(cancelMsg, lastResp->callId.number, lastResp->callId.host);
    SIP_SetCseqHeader(cancelMsg, lastResp->cseq.number, lastResp->cseq.method);

    /* Get Vias one by one and put in trying msg */
    while (!SIP_LISTEol(lastResp->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(lastResp->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        if (numViaparams != 0)
        {
            SIP_SetViaHeader(cancelMsg, version, protocol, host,
                             numViaparams, *genParam);
        }
        else
        {
            SIP_SetViaHeader(cancelMsg, version, protocol, host,
                             0, NULL);
        }
        pos++;
    }

    /*send event to stack */

    ret = SIP_SendRequest(SIP_StackHandle, cancelMsg);
    if (ret == ITS_SUCCESS)
    {
        printf("CANCEL msg sent successfully to Stack\n");
    }
    else
    {
        printf("CANCEL msg sent unsuccessful to Stack. Reason:: %d\n", ret);
    }

    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose: This function will send BYE message to STACK
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
TestSendBye(char *callId, char *remHost, char *remPort , char *lhost,
                    char *lport)
{
    SIP_MSG *msgBye;
    SIP_URI_OBJ uriObj;
    SIP_HOST_INFO hostInfo, frmHostInfo, viaHostInfo;
    int ret;
    SIP_CONTENTTYPE_INFO contentTypeInfo;

    ret = SIP_InitMsg(&msgBye);
    if (ret == ITS_SUCCESS)
    {
        printf("\n$$ SIP INIT successful $$\n");
    }
    /* Build startline */
    SIP_SetHostinfo(&hostInfo, 1, remHost, remPort);
    /* Set req URI for the startline */
    SIP_SetUri(&uriObj, "sip", "suresh", NULL, &hostInfo);

    SIP_SetStartLine(msgBye, "SIP/2.0", 0, NULL, "BYE", &uriObj);

    /* Set To Header */
    SIP_SetToHeader(msgBye, &uriObj, "Bob", NULL, 0, NULL);

    /* Set HostInfo for from Header */
    SIP_SetHostinfo(&frmHostInfo, 1, lhost, lport);
    SIP_SetUri(&uriObj, "sip", "alice", NULL, &frmHostInfo);
    SIP_SetFromHeader(msgBye, &uriObj, "Alice", "1928301774", 0, NULL);

    SIP_SetCallidHeader(msgBye, callId, remHost);
    SIP_SetCseqHeader(msgBye, 314159, "BYE");

    SIP_SetContentTypeInfo(&contentTypeInfo, "application",
                             "sdp", NULL, 0, NULL);
    /*SIP_SetContentHeader(msgBye, &contentTypeInfo, 100, NULL);*/

    SIP_SetContentHeader(msgBye, &contentTypeInfo, 100, NULL);
    SIP_SetHostinfo(&viaHostInfo, 1, lhost, lport);
    SIP_SetViaHeader(msgBye, "2.0", "UDP", &viaHostInfo, 0, NULL);

    ret = SIP_SendRequest(SIP_StackHandle, msgBye);
    if ( ret == -1)
    {
        /* Free SIP_MSG */
        SIP_MsgFree(msgBye);
        return ret;
    }
    else if (ret == ITS_EMISSINGMANDHDR)
    {
        /* Free SIP_MSG */
        SIP_MsgFree(msgBye);
        printf("Failed ret = %d \n", ret );
        return ret;
    }
    sip_last_msg = msgBye;

    printf("\n$$ BYE msg sent successfuly to STACK $$$ \n\n");
    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose: Sends REGISTER to SIP Stack.
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
TestSendRegister(char *callId, char *remHost, char *remPort, char *lHost, char *lPort )
{
    SIP_MSG *msgReg;
    SIP_URI_OBJ uriObj;
    SIP_HOST_INFO hostInfo, frmHostInfo, viaHostInfo;
    int ret;

    ret = SIP_InitMsg(&msgReg);
    if (ret == ITS_SUCCESS)
    {
        printf("\n$$ SIP INIT successful $$\n");
    }
    /* Build startline */
    SIP_SetHostinfo(&hostInfo, 1, remHost, remPort);
    /* Set req URI for the startline */
    SIP_SetUri(&uriObj, "sip", "suresh", NULL, &hostInfo);

    SIP_SetStartLine(msgReg, "SIP/2.0", 0, NULL, "REGISTER", &uriObj);

    /* When To address is same as From */
    SIP_SetHostinfo(&hostInfo, 1, lHost, lPort);
    /* Set req URI for the startline */
    SIP_SetUri(&uriObj, "sip", "suresh", NULL, &hostInfo);
    /* When To address is same as From */

    /* Set To Header */
    SIP_SetToHeader(msgReg, &uriObj, "suresh", NULL, 0, NULL);
    /*SIP_SetToHeader(msgReg, &uriObj, "Bob", NULL, 0, NULL);*/

    /* Set HostInfo for from Header */
    SIP_SetHostinfo(&frmHostInfo, 1, lHost, lPort);
    SIP_SetUri(&uriObj, "sip", "suresh", NULL, &frmHostInfo);
    SIP_SetFromHeader(msgReg, &uriObj, "Suresh", "NULL", 0, NULL);

    SIP_SetCallidHeader(msgReg, callId, lHost);
    SIP_SetCseqHeader(msgReg, 1, "REGISTER");

    SIP_SetHostinfo(&viaHostInfo, 1, lHost, lPort);
    SIP_SetViaHeader(msgReg, "2.0", "UDP", &viaHostInfo, 0, NULL);

    /*SIP_SetContactHeader(msgReg, &uriObj, "Suresh", "NULL", 0, NULL);*/

    ret = SIP_SendRequest(SIP_StackHandle, msgReg);
    if ( ret == -1)
    {
        /* Free SIP_MSG */
        SIP_MsgFree(msgReg);
        return ret;
    }
    else if (ret == ITS_EMISSINGMANDHDR)
    {
        /* Free SIP_MSG */
        SIP_MsgFree(msgReg);
        printf("Failed ret = %d \n", ret );
        return ret;
    }
    sip_last_msg = msgReg;

    printf("\n$$ REGISTER msg sent successfuly to STACK $$$ \n\n");
    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose: Sends 200 OK to SIP Stack.
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
TestSend200Ok(SIP_MSG *lastReq)
{
    SIP_MSG *msgOk;
    int ret = 0, pos = 0;
    SIP_HOST_INFO fromHostInfo, toHostInfo, contactHostInfo, *host;
    SIP_URI_OBJ  fromUri, toUri, contactUri;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;
    printf("\nInside APP_Send200Ok function \n");

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

    /* Send Contact(s), Add carefully */
    SIP_SetHostinfo(&contactHostInfo, SIP_HOST_TYPE_HOSTNAME,
                    "intellinet-india.com", NULL);
    SIP_SetUri(&contactUri, "sip", "227", NULL, &contactHostInfo);
    SIP_SetContactHeader(msgOk, &contactUri, "Arun", NULL, 0, NULL);   

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

    ret = SIP_SendResponse(SIP_StackHandle, msgOk);
    if (ret == ITS_SUCCESS)
    {
        printf("200 Ok msg sent successfully to Stack\n");
    }
    
    /* Free Received msg */
    if (sip_prov_msg != NULL)
    {
        SIP_MsgFree(sip_prov_msg);
    }
    return ret;
}   

/*.implementation:static
 ****************************************************************************
 *  Purpose: Sends 180Ringing to SIP Stack.
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
TestSend180Ringing(SIP_MSG *lastRequest)
{
    SIP_MSG *msgRing;
    SIP_HOST_INFO fromHostInfo, toHostInfo, *host;
    SIP_URI_OBJ fromUri, toUri;

    int ret = 0, pos = 0;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;

    /* Build 180 Ringing and send to SIP stack */
    SIP_InitMsg(&msgRing);
    ret = SIP_SetStartLine(msgRing, "SIP/2.0", 180, "Ringing", NULL, NULL);
    if (ret != ITS_SUCCESS)
    {
        printf("HandleINVITEIndication:: SIP_SetStartLine fail \n");
        return ret;
    }

    /* Set Uri for From Header */
    ret = SIP_SetHostinfo(&fromHostInfo, lastRequest->from.url.hostInfo.type,
                    lastRequest->from.url.hostInfo.address,
                    lastRequest->from.url.hostInfo.port);
    ret = SIP_SetUri(&fromUri, lastRequest->from.url.scheme, lastRequest->from.url.userName,
               lastRequest->from.url.password, &fromHostInfo);
    ret = SIP_SetFromHeader(msgRing, &fromUri, lastRequest->from.displayName, NULL,
                      lastRequest->from.numGenparams, NULL);

    /* Set Uri for To Header */
    ret = SIP_SetHostinfo(&toHostInfo, lastRequest->to.url.hostInfo.type,
                    lastRequest->to.url.hostInfo.address,
                    lastRequest->to.url.hostInfo.port);
    ret = SIP_SetUri(&toUri, lastRequest->to.url.scheme, lastRequest->to.url.userName,
               lastRequest->to.url.password, &toHostInfo);
    ret = SIP_SetToHeader(msgRing, &toUri, lastRequest->to.displayName, NULL,
                      lastRequest->to.numGenparams, NULL);

    ret = SIP_SetCallidHeader(msgRing, lastRequest->callId.number, lastRequest->callId.host);
    ret = SIP_SetCseqHeader(msgRing, lastRequest->cseq.number, lastRequest->cseq.method);

    while (!SIP_LISTEol(lastRequest->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(lastRequest->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        if (numViaparams != 0)
        {
            SIP_SetViaHeader(msgRing, version, protocol, host,
                             numViaparams, *genParam);
        }
        else
        {
            SIP_SetViaHeader(msgRing, version, protocol, host,
                             0, NULL);
        }
        pos++;
    }
/*
    if (lastRequest->require[0] != 0)
    {
        SIP_SetRSeqHeader(msgRing, 200);
    }
*/
    ret = SIP_SendResponse(SIP_StackHandle, msgRing);
    if (ret == ITS_SUCCESS)
    {
        printf("180 Ringing msg sent successfully to Stack\n");
    }

    /* Free Received msg */

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Sends 3XX to SIP Stack.
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
TestSend3XX(SIP_MSG *lastReq)
{
    SIP_MSG *msg3xx;
    SIP_HOST_INFO fromHostInfo, toHostInfo, contactHostInfo, *host;
    SIP_URI_OBJ fromUri, toUri, contactUri;
    int ret = 0, pos = 0;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;

    printf("\nInside APP_Send3XX function \n");

    /* Build 3xx and send to SIP stack */
    SIP_InitMsg(&msg3xx);
    ret = SIP_SetStartLine(msg3xx, "SIP/2.0", 302, "Moved Temporarily",
                           NULL, NULL);
    if (ret != ITS_SUCCESS)
    {
        printf("APP_Send3XX:: SIP_SetStartLine fail \n");
        return ret;
    }
    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, lastReq->from.url.hostInfo.type,
                    lastReq->from.url.hostInfo.address,
                    lastReq->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, lastReq->from.url.scheme, lastReq->from.url.userName,
               lastReq->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(msg3xx, &fromUri, lastReq->from.displayName, NULL,
                      lastReq->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetHostinfo(&toHostInfo, lastReq->to.url.hostInfo.type,
                    lastReq->to.url.hostInfo.address,
                    lastReq->to.url.hostInfo.port);
    SIP_SetUri(&toUri, lastReq->to.url.scheme, lastReq->to.url.userName,
               lastReq->to.url.password, &toHostInfo);
    SIP_SetToHeader(msg3xx, &toUri, lastReq->to.displayName, NULL,
                      lastReq->to.numGenparams, NULL);

    SIP_SetCallidHeader(msg3xx, lastReq->callId.number, lastReq->callId.host);
    SIP_SetCseqHeader(msg3xx, lastReq->cseq.number, lastReq->cseq.method);
    
    /* Send Contact(s), Add carefully */
    SIP_SetHostinfo(&contactHostInfo, SIP_HOST_TYPE_HOSTNAME,
                    "intellinet-india.com", NULL);
    SIP_SetUri(&contactUri, "sip", "227", NULL, &contactHostInfo);
    SIP_SetContactHeader(msg3xx, &contactUri, "Arun", NULL, 0, NULL);

    /* Set Content type and content length aswell for 200 OK
    SIP_SetContentlenHeader(msg3xx, lastReq->contentLen.value);  */


    while (!SIP_LISTEol(lastReq->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(lastReq->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        if (numViaparams != 0)
        {
            SIP_SetViaHeader(msg3xx, version, protocol, host,
                             numViaparams, *genParam);
        }
        else
        {
            SIP_SetViaHeader(msg3xx, version, protocol, host,
                             0, NULL);
        }
        pos++;
    }

    ret = SIP_SendResponse(SIP_StackHandle, msg3xx);
    if (ret == ITS_SUCCESS)
    {
        printf("302 moved temp msg sent successfully to Stack\n");
    }
    /* Free Received msg */

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: This function will send ACK message to STACK. 
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
TestSendAck(SIP_MSG *lasrReq)
{
    SIP_MSG *ack;
    int ret = 0, pos = 0;
    SIP_HOST_INFO fromHostInfo, toHostInfo,  *host;
    SIP_URI_OBJ fromUri, toUri;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;

    SIP_InitMsg(&ack);

    /* start line must */

    /* Set hostInfo for the startline */

    SIP_SetHostinfo(&toHostInfo, lasrReq->to.url.hostInfo.type,
                    lasrReq->to.url.hostInfo.address,
                    lasrReq->to.url.hostInfo.port);
    SIP_SetUri(&toUri, lasrReq->to.url.scheme, lasrReq->to.url.userName,
               lasrReq->to.url.password, &toHostInfo);

    SIP_SetStartLine(ack, lasrReq->sipVersion, 0, NULL, "ACK", &toUri);

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, lasrReq->from.url.hostInfo.type,
                    lasrReq->from.url.hostInfo.address,
                    lasrReq->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, lasrReq->from.url.scheme, lasrReq->from.url.userName,
               lasrReq->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(ack, &fromUri, lasrReq->from.displayName, NULL,
                      lasrReq->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetToHeader(ack, &toUri, lasrReq->to.displayName, NULL,
                      lasrReq->to.numGenparams, NULL);

    SIP_SetCallidHeader(ack, lasrReq->callId.number, lasrReq->callId.host);
    SIP_SetCseqHeader(ack, lasrReq->cseq.number, "ACK");

    /* Get Vias one by one and put in trying msg */
    while (!SIP_LISTEol(lasrReq->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(lasrReq->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        if (numViaparams != 0)
        {
            SIP_SetViaHeader(ack, version, protocol, host,
                             numViaparams, *genParam);
        }
        else
        {
            SIP_SetViaHeader(ack, version, protocol, host,
                             0, NULL);
        }
        pos++;
    }

    /*send event to stack */

    SIP_SendRequest(SIP_StackHandle, ack);
    if (ret == ITS_SUCCESS)
    {
        printf("ACK msg sent successfully to Stack\n");
    }

    /* creating problem while deleting msg in sip_context.c under 
       ITS_SIP_APP_SRC section. It holds and deletes every msg coming in 
       from app.  SIP_MsgFree(sip_last_msg); */  

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: This function will send OPTIONS message to STACK 
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
TestSendOptions(char *callId, char *remHost, char *remPort , char *lhost,
                char *lport)
{
    int ret;
    SIP_MSG *msg;
    SIP_URI_OBJ uriObj;
    SIP_HOST_INFO hostInfo, frmHostInfo, viaHostInfo;
    SIP_CONTENTTYPE_INFO contentTypeInfo;

    ret = SIP_InitMsg(&msg);
    if (ret == ITS_SUCCESS)
    {
        printf("\n$$ SIP INIT successful $$\n");
    }
    /* Build startline */
    SIP_SetHostinfo(&hostInfo, 1, remHost, remPort);
    SIP_SetUri(&uriObj, "sip", "bob", NULL, &hostInfo);
    SIP_SetStartLine(msg, "SIP/2.0", 0, NULL, "OPTIONS", &uriObj);

    /* Set To Header */
    SIP_SetToHeader(msg, &uriObj, "Bob", NULL, 0, NULL);

    /* Set From Header */
    SIP_SetHostinfo(&frmHostInfo, 1, lhost, lport);
    SIP_SetUri(&uriObj, "sip", "alice", NULL, &frmHostInfo);
    SIP_SetFromHeader(msg, &uriObj, "Alice", "1928301774", 0, NULL);

    SIP_SetCallidHeader(msg, callId, remHost);
    SIP_SetCseqHeader(msg, 314128, "OPTIONS");

    SIP_SetContentTypeInfo(&contentTypeInfo, "application",
                             "sdp", NULL, 0, NULL);
    SIP_SetContentHeader(msg, &contentTypeInfo, 100, NULL);

    SIP_SetHostinfo(&viaHostInfo, 1, lhost, lport);
    SIP_SetViaHeader(msg, "2.0", "UDP", &viaHostInfo, 0, NULL);
    SIP_SetAcceptHeader(msg, 0, 0, "application", "sdp", 0, NULL);
    ret = SIP_SendRequest((ITS_HANDLE)itsINTELLISIP_Class, msg);

    if (ret == -1 || ret == ITS_EMISSINGMANDHDR)
    {
        /* Free SIP_MSG */
        SIP_MsgFree(msg);
        return ret;
    }
    sip_last_msg = msg;

    printf("\n$$ INVITE msg sent successfuly to STACK $$$ \n\n");
    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose: This function will send PRACK message to STACK
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
TestSendPrack(SIP_MSG *lastResp)
{
    SIP_MSG *prack;
    int ret = 0, pos = 0;
    SIP_HOST_INFO fromHostInfo, toHostInfo,  *host;
    SIP_URI_OBJ fromUri, toUri;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;

    SIP_InitMsg(&prack);
    /* start line must */

    /* Set hostInfo for the startline */

    SIP_SetHostinfo(&toHostInfo, lastResp->to.url.hostInfo.type,
                    lastResp->to.url.hostInfo.address,
                    lastResp->to.url.hostInfo.port);
    SIP_SetUri(&toUri, lastResp->to.url.scheme, lastResp->to.url.userName,
               lastResp->to.url.password, &toHostInfo);

    SIP_SetStartLine(prack, lastResp->sipVersion, 0, NULL, "PRACK", &toUri);

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, lastResp->from.url.hostInfo.type,
                    lastResp->from.url.hostInfo.address,
                    lastResp->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, lastResp->from.url.scheme, lastResp->from.url.userName,
               lastResp->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(prack, &fromUri, lastResp->from.displayName, NULL,
                      lastResp->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetToHeader(prack, &toUri, lastResp->to.displayName, NULL,
                      lastResp->to.numGenparams, NULL);

    SIP_SetCallidHeader(prack, lastResp->callId.number, lastResp->callId.host);
    SIP_SetCseqHeader(prack, 314154, "PRACK");

    SIP_SetRAckHeader(prack, lastResp->rseq, lastResp->cseq.number, 
                      lastResp->cseq.method);

    /* Get Vias one by one and put in trying msg */
    while (!SIP_LISTEol(lastResp->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(lastResp->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        if (numViaparams != 0)
        {
            SIP_SetViaHeader(prack, version, protocol, host,
                             numViaparams, *genParam);
        }
        else
        {
            SIP_SetViaHeader(prack, version, protocol, host,
                             0, NULL);
        }
        pos++;
    }

    /*send event to stack */

    ret = SIP_SendRequest(SIP_StackHandle, prack);
    if (ret == ITS_SUCCESS)
    {
        printf("PRACK msg sent successfully to Stack\n");
    }
    else
    {
        printf("PRACK msg sent unsuccessful to Stack. Reason:: %d\n", ret);
    }

    return ret;
}

