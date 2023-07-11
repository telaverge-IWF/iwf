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
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *  ID:$Id  $
 *
 *  $Log: load.c,v $
 *  Revision 9.1  2005/03/23 12:54:28  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.3  2005/03/21 13:53:27  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.2.2.1  2004/12/28 14:04:09  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.2  2004/06/30 14:06:31  sjaddu
 *  Testing goingon.
 *
 *  Revision 1.1  2004/06/28 07:42:35  sjaddu
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

#include <sys/timeb.h>

#if defined(DEBUG)
int _debug = 1;
#else
int _debug = 0;
#endif

/* sending side stats */
int oksinvites = 0;
int byes       = 0;


/*receiving side stats */
int invites = 0;
int acks    = 0;
int oksbye  = 0;

int  whichside = 0;

extern ITS_SHORT thrInstance;

/* globals */
char*  remIpAddr;
char*  remPort; 
int    STOP = 1;
ITS_SEMAPHORE timerSem;
int callsPerSec = 0;
int totNocalls = 0;

static int  
APP_TestSendInvite(char *callId, char *remHost, char *remPort , char *lport)
{
    SIP_MSG *msg;
    SIP_URI_OBJ uriObj;
    SIP_HOST_INFO hostInfo, viaHostInfo;
    int ret;
    SIP_CONTENTTYPE_INFO contentTypeInfo;

    ret = SIP_InitMsg(&msg);
    if (ret == ITS_SUCCESS)
    {
            
        if (_debug)
        printf("\n$$ SIP INIT successful $$\n");
    }
    /* Set hostInfo for the startline - lxserver in this case */
    SIP_SetHostinfo(&hostInfo, 1, remHost, remPort);

    /* Set req URI for the startline */
    SIP_SetUri(&uriObj, "sip", "suresh", NULL, &hostInfo);
    SIP_SetStartLine(msg, "SIP/2.0", 0, NULL, "INVITE", &uriObj);

    /* Set To Header */
    SIP_SetToHeader(msg, &uriObj, "Bob", NULL, 0, NULL);
    SIP_SetFromHeader(msg, &uriObj, "Alice", "1928301774", 0, NULL);
    SIP_SetCallidHeader(msg, callId, remHost);
    SIP_SetCseqHeader(msg, rand(), "INVITE");

    SIP_SetContentTypeInfo(&contentTypeInfo, "application",
                             "sdp", NULL, 0, NULL);
    SIP_SetContentHeader(msg, &contentTypeInfo, 100, NULL);

    SIP_SetHostinfo(&viaHostInfo, 1, "172.16.1.25", lport);
    SIP_SetViaHeader(msg, "2.0", "udp", &viaHostInfo, 0, NULL);

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
        return ret;
    }

    totNocalls++;
    if (_debug) 
    printf("\n$$ INVITE msg sent successfuly to STACK $$$ \n\n");

    return ret;
}

static int
APP_TestSendBye(SIP_MSG *lasrReq)
{
    SIP_MSG *ack;
    int ret = 0, pos = 0;
    SIP_HOST_INFO fromHostInfo, toHostInfo,  *host;
    SIP_URI_OBJ uri, fromUri, toUri;
    SIP_HOST_INFO hostInfo;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;


    SIP_InitMsg(&ack);

    /* start line must */

    /* Set hostInfo for the startline  lxserver here */
    SIP_SetHostinfo(&hostInfo, 1, "172.16.1.25", "5080");

    /* Set req URI for the startline */
    /* FIXME - Get these things from contact header */
    SIP_SetUri(&uri, "sip", "bob", NULL, &hostInfo);

    SIP_SetStartLine(ack, "SIP/2.0", 0, NULL, "BYE", &uri);

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, lasrReq->from.url.hostInfo.type,
                    lasrReq->from.url.hostInfo.address,
                    lasrReq->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, lasrReq->from.url.scheme, lasrReq->from.url.userName,
               lasrReq->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(ack, &fromUri, lasrReq->from.displayName, NULL,
                      lasrReq->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetHostinfo(&toHostInfo, lasrReq->to.url.hostInfo.type,
                    lasrReq->to.url.hostInfo.address,
                    lasrReq->to.url.hostInfo.port);
    SIP_SetUri(&toUri, lasrReq->to.url.scheme, lasrReq->to.url.userName,
               lasrReq->to.url.password, &toHostInfo);
    SIP_SetToHeader(ack, &toUri, lasrReq->to.displayName, NULL,
                      lasrReq->to.numGenparams, NULL);

    SIP_SetCallidHeader(ack, lasrReq->callId.number, lasrReq->callId.host);
    
    /* This is the only change increment +1 */
    SIP_SetCseqHeader(ack, lasrReq->cseq.number + 1, "BYE");

    /* Get Vias one by one and put in trying msg */
    while (!SIP_LISTEol(lasrReq->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(lasrReq->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        strcpy(host->port, "5081"); 
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

    return ret;
}

static int
APP_TestSend200Ok(SIP_MSG *lastReq)
{
    SIP_MSG *msgOk;
    int ret = 0, pos = 0;
    SIP_HOST_INFO fromHostInfo, toHostInfo,  *host;
    SIP_URI_OBJ  fromUri, toUri;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;
    if (_debug)printf("\nInside APP_Send200Ok function \n");

    /* Build 200 OK and send to SIP stack */
    SIP_InitMsg(&msgOk);
    ret = SIP_SetStartLine(msgOk, "SIP/2.0", 200, "Ok", NULL, NULL);
    if (ret != ITS_SUCCESS)
    {
        if (_debug)printf("APP_Send200Ok:: SIP_SetStartLine fail \n");
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

    ret = SIP_SendResponse(SIP_StackHandle, msgOk);
    if (ret == ITS_SUCCESS)
    {
        if (_debug)printf("200 Ok msg sent successfully to Stack\n");
    }
    
    return ret;
}   

static int
APP_TestSend180Ringing(SIP_MSG *lastRequest)
{
    SIP_MSG *msgRing;
    SIP_HOST_INFO fromHostInfo, toHostInfo, *host;
    SIP_URI_OBJ fromUri, toUri;

    int ret = 0, pos = 0;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;

    if (_debug)printf("\nInside APP_Send180Ringing function \n");

    /* Build 180 Ringing and send to SIP stack */
    SIP_InitMsg(&msgRing);
    ret = SIP_SetStartLine(msgRing, "SIP/2.0", 180, "Ringing", NULL, NULL);
    if (ret != ITS_SUCCESS)
    {
        if (_debug)printf("HandleINVITEIndication:: SIP_SetStartLine fail \n");
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

    ret = SIP_SendResponse(SIP_StackHandle, msgRing);
    if (ret == ITS_SUCCESS)
    {
        if (_debug)printf("180 Ringing msg sent successfully to Stack\n");
    }

    return ret;
}

static int
APP_TestSendAck(SIP_MSG *lasrReq)
{
    SIP_MSG *ack;
    int ret = 0, pos = 0;
    SIP_HOST_INFO fromHostInfo, toHostInfo,  *host;
    SIP_URI_OBJ uri, fromUri, toUri;
    SIP_HOST_INFO hostInfo;
    ITS_CHAR *version, *protocol;
    SIP_GENERIC_PARAM *genParam[3];
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;


    SIP_InitMsg(&ack);

    /* start line must */

    /* Set hostInfo for the startline  lxserver here */
    SIP_SetHostinfo(&hostInfo, 1, "172.16.1.25", "5061");

    /* Set req URI for the startline */
    /* FIXME - Get these things from contact header */
    SIP_SetUri(&uri, "sip", "bob", NULL, &hostInfo);

    SIP_SetStartLine(ack, "SIP/2.0", 0, NULL, "ACK", &uri);

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, lasrReq->from.url.hostInfo.type,
                    lasrReq->from.url.hostInfo.address,
                    lasrReq->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, lasrReq->from.url.scheme, lasrReq->from.url.userName,
               lasrReq->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(ack, &fromUri, lasrReq->from.displayName, NULL,
                      lasrReq->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetHostinfo(&toHostInfo, lasrReq->to.url.hostInfo.type,
                    lasrReq->to.url.hostInfo.address,
                    lasrReq->to.url.hostInfo.port);
    SIP_SetUri(&toUri, lasrReq->to.url.scheme, lasrReq->to.url.userName,
               lasrReq->to.url.password, &toHostInfo);
    SIP_SetToHeader(ack, &toUri, lasrReq->to.displayName, NULL,
                      lasrReq->to.numGenparams, NULL);

    SIP_SetCallidHeader(ack, lasrReq->callId.number, lasrReq->callId.host);
    SIP_SetCseqHeader(ack, lasrReq->cseq.number, "INVITE");

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

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function retrieves the SIP msg, error, indication,
 *      timeout datat from received ITS event
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
APP_LoadReceiveMsg(ITS_HANDLE handle, ITS_EVENT *event)
{
    ITS_OCTET       msgId;
    SIP_EVENT_TYPE  evType;

    /* Get Event type, whether INVITE, 180 etc */
    evType = SIP_GetEventType(event);
    switch(evType)
    {
    case SIP_DATA_EVENT:
    {
        SIP_MSG *sip_last_msg = 0;

        msgId = SIP_GetMsgType(event);
        sip_last_msg = (SIP_MSG *)SIP_GET_MSG_INFO((SIP_GET_SIPEVENT(event)));
        switch(msgId)
        {
        case SIP_MSG_REGISTER:
            break;

        case SIP_MSG_INVITE:
            if (_debug)printf("\n ******* Received message::: INVITE  *******\n");
            /* Send 180 ringing */
            APP_TestSend180Ringing(sip_last_msg);

            /*Send 200 ok */
            APP_TestSend200Ok(sip_last_msg);

            invites++;
            break;

        case SIP_MSG_ACK:
            if (_debug)printf("\n***** Received message::: ACK *******\n");

            /* Send BYE, remember it will have defferent Cseq num  */
            APP_TestSendBye(sip_last_msg);
            acks++;

            break;

        case SIP_MSG_100:
            if (_debug)printf("\nReceived message::: 100 \n");
            break;

        case SIP_MSG_180:
            if (_debug)printf("\nReceived message::: 180 \n");
            break;

        case SIP_MSG_200:
            if (strcmp(sip_last_msg->cseq.method, "INVITE") == 0)
            {
                if (_debug)printf("\nReceived message::: 200 OK for INVITE \n");
                /*send ACK, if it is for invite */
                APP_TestSendAck(sip_last_msg);
                oksinvites++;
            }
            else
            {
                if (_debug)printf("\nReceived message::: 200 OK for BYE \n");
                oksbye++;
            }
            break;

        case SIP_MSG_302:
            if (_debug)printf("\nReceived message::: 302 \n");
            break;

        case SIP_MSG_BYE:
                if (_debug)printf("\nReceived message::: BYE \n");

            /* Send 200 ok for Bye */
            APP_TestSend200Ok(sip_last_msg);
            byes++;
            break;

        default:
            printf("\nReceived Unrecognized msg Id is %d \n", msgId);
            break;
        }
        SIP_MsgFree(sip_last_msg);
        break;
    }
    case SIP_ERROR_EVENT:
    {
        SIP_ERROR_TYPE  errType;
        SIP_PARSER_ERROR_DATA *parseErrData;
        SIP_ERROR_DATA *errData;
        SIP_TRANSACTION_ERROR_DATA *trnErrData;
        SIP_TRANSPORT_ERROR_DATA *tranErrData;

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
    }
    case SIP_INDICATION_EVENT:
    {
        SIP_INDICATION_DATA *indData;
        indData = SIP_ReceiveIndicationData(handle, event);
        printf("SIP_INDICATION_EVENT:: Indication Event Received, id = %d\n",
                                       indData->reason);
        break;
    }
    case SIP_TIMEOUT_EVENT:
    {
        SIP_TIMEOUT_DATA *timeoutData;
        timeoutData = SIP_ReceiveTimeoutData(handle, event);
        printf("SIP_TIMEOUT_EVENT:: Timeout Event Received, reason = %d"
                " callId =  %s\n", timeoutData->reason, 
                timeoutData->callId.number);
        break;
    default:
        printf("\nReceived Unrecognized Event, ID is %d \n", evType);
        break;
    }
    }

    /* FIXME - Free SIP msg after done with processing */
     SIP_EVENT_TERM(SIP_GET_SIPEVENT(event));

    return ITS_SUCCESS;
}

static void
APP_InviteDispatchFunction(TPOOL_THREAD *thr, ITS_HANDLE handle)
{
    int callId1 = 0;
    int callId2 = 0;
    char *lport = "5080";
    char buf[128];

    int callCount = 0;

    printf("Started Invite dispatch thread \n");

    /* Post the sema, so that timer thread will start */
     if( SEMA_PostSemaphore(&timerSem) != ITS_SUCCESS )
     {
         return;
     }


    while(STOP)
    {
printf("Call/sec  = %d\n", callsPerSec);
        for(callCount = 0; callCount < callsPerSec; callCount++)
        {
            /* We can never exuast callId, just go on incrementing */
            callId1 = rand();
            callId2 = rand();
            sprintf(buf, "%d%d", callId1, callId2);
            if (_debug)printf("CallId for this call  = %s\n", buf);

            /*Send invite in time intervals, local port 5060? */
            APP_TestSendInvite(buf, remIpAddr, remPort, lport);

            TIMERS_USleep(1000000/(2 * callsPerSec));

        }

        if( SEMA_WaitSemaphore(&timerSem) != ITS_SUCCESS )
        {
            printf("SEMA_WaitSemaphore failed \n");
            return;
        }
    }
}

static void
APP_LoadReceiver(TPOOL_THREAD *thr, ITS_HANDLE handle)
{
    ITS_USHORT workerInstance;
    ITS_EVENT event;
    ITS_INT ret;

    WORKER_Control* worker = (WORKER_Control*)thr;
    workerInstance = worker->worker.instance;
    while(1)
    {
        if (_debug)printf("Waiting =====\n");
        event.data = 0;
        ret = WORKER_GetNextEvent(worker, &event);
        if (ret != ITS_SUCCESS)
        {
                printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
        }

        if ( event.src == ITS_SIP_SRC )
        {
            if (_debug)printf("Load Tester:: SIP msg receive success\n");
                APP_LoadReceiveMsg(SIP_StackHandle, &event);
        }
    }

}

static void
APP_TimerThread(TPOOL_THREAD *thr, ITS_HANDLE handle)
{

    int timerDuration = 1;

    if (SEMA_CreateSemaphore(&timerSem, 0) != ITS_SUCCESS)
    {
        printf("Failed to create Load Semaphore!\n");
        exit (1);
    }

    if( SEMA_WaitSemaphore(&timerSem) != ITS_SUCCESS )
    {
        printf("Failure in SEMA_WaitSemaphore() in Timer Thread!\n");
        return;
    }

    for(;;)
    {
        sleep(timerDuration); /* sleep for a second */
        if( SEMA_PostSemaphore(&timerSem) != ITS_SUCCESS )
        {
            return;
        }
    }
}

void StatLoadReceiver()
{
    ITS_INT ret = 0;
    TPOOL_THREAD* thread = NULL;

    printf("Receiver load test started ... \n");
    whichside = 0;
    /* enter timings*/
    {
        
        time_t  t_loc;
        FILE *_file = NULL;
        char *ind = "\n===== Receiving side stats ==========\n";

        t_loc = time(&t_loc);
        _file = fopen("result", "a+");
        fwrite(ind, 1, strlen(ind), _file); 
        fprintf(_file, "Load Start time = %s\n", ctime(&t_loc));
        fprintf(_file, "Start calls/sec = %d\n", callsPerSec);
    }

    if((ret = TPOOL_GetFirstAvailThread(workerPool, &thread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        thrInstance= ITS_INVALID_SRC;
    }

    printf("Ftest: RouteApp: Dispatching receive thread\n");

    ret = TPOOL_DispatchOnThread(thread,APP_LoadReceiver,
                                       WORKER_BACK_PTR(thread));
    if (ret != ITS_SUCCESS)
    {
        thrInstance = ITS_INVALID_SRC;
    }
    else
    {
        thrInstance = ( ((WORKER_Control*)thread)->worker.instance );
    }
}

void StatLoadSender(char * ipAddr, char *port, int calls)
{
    ITS_INT ret = 0;
    TPOOL_THREAD* thread1 = NULL;
    TPOOL_THREAD* thread2 = NULL;
    TPOOL_THREAD* thread3 = NULL;

    whichside = 1;

    /* Get remote IP & port where we have to send the load */
    remIpAddr = strdup(ipAddr);
    remPort   = strdup(port);
    callsPerSec = calls;

    /* enter timings*/
    {
        
        time_t  t_loc;
        FILE *_file = NULL;
        char *ind = "\n======  Sending side stats =========\n";

        t_loc = time(&t_loc);
        _file = fopen("result", "a+");
        fwrite(ind, 1, strlen(ind), _file); 
        fprintf(_file, "Load Start time = %s\n", ctime(&t_loc));
        fprintf(_file, "Start calls/sec = %d\n", callsPerSec);
    }
        
    

    /*Timer thread */
    if((ret = TPOOL_GetFirstAvailThread(workerPool, &thread3)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
    }

    printf("Ftest: RouteApp: Dispatching receive thread\n");

    ret = TPOOL_DispatchOnThread(thread3,APP_TimerThread,
                                       WORKER_BACK_PTR(thread3));
    if (ret != ITS_SUCCESS)
    {
        printf("Fialed to create Timer thread \n");
        exit(1);
    }

    /*Receiver thread */
    if((ret = TPOOL_GetFirstAvailThread(workerPool, &thread1)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        thrInstance= ITS_INVALID_SRC;
    }

    printf("Ftest: RouteApp: Dispatching receive thread\n");

    ret = TPOOL_DispatchOnThread(thread1,APP_LoadReceiver,
                                       WORKER_BACK_PTR(thread1));
    if (ret != ITS_SUCCESS)
    {
        thrInstance = ITS_INVALID_SRC;
    }
    else
    {
        thrInstance = ( ((WORKER_Control*)thread1)->worker.instance );
    }

    /* Invite dispatch thread */
    if((ret = TPOOL_GetFirstAvailThread(workerPool, &thread2)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        thrInstance= ITS_INVALID_SRC;
    }

    printf("Ftest: RouteApp: Dispatching Invite thread\n");

    ret = TPOOL_DispatchOnThread(thread2,APP_InviteDispatchFunction,
                                       WORKER_BACK_PTR(thread2));
    if (ret != ITS_SUCCESS)
    {
        thrInstance = ITS_INVALID_SRC;
    }
    printf("---- Started SIP application \n");
}

void LoadPostFunc()
{
    time_t  t_loc;
    FILE *_file = NULL;

    t_loc = time(&t_loc);
    _file = fopen("result", "a+");
    
    if (whichside)
    {
        fprintf(_file, "End calls/sec  = %d\n", callsPerSec);
        fprintf(_file, "No# calls made = %d\n", totNocalls);
        fprintf(_file, "200 ok received for inv = %d\n", oksinvites);
        fprintf(_file, "No# bye received = %d\n", byes);
    }
    else
    {
        fprintf(_file, "No# invites = %d\n", invites);
        fprintf(_file, "No# ack for 200ok received = %d\n", acks);
        fprintf(_file, "No# 200 ok for bye received = %d\n", oksbye);
    }
        
    fprintf(_file, "Load End time = %s\n", ctime(&t_loc));
}
