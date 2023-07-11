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
 * CONTRACT: INTERNAL Demo                                                  *
 *                                                                          *
 ****************************************************************************
 *  ID:$Id  $
 *      
 *  $Log: followme_app_lib.c,v $
 *  Revision 9.1  2005/03/23 12:54:28  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.3  2005/03/21 13:53:27  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.2.2.1  2004/12/28 14:04:09  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.2  2004/06/28 07:42:35  sjaddu
 *  Load test added and SIP_StackHandle also added.
 *
 *  Revision 1.1  2004/05/27 15:15:32  sjaddu
 *  Files created for followme app.
 *
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
#include <its_types.h>

#include <sip_defines.h>

static int
APP_ReceiveMsg(ITS_HANDLE handle, ITS_EVENT *event);

ITS_SHORT thrInstance = 0;
SIP_MSG *sip_last_msg;

typedef struct _app_contact_list
{
    struct _app_contact_list *next;
    ITS_CHAR *contactNo;
}
APP_CONTACT_LIST;

typedef struct _app_contact_info
{
    struct _app_contact_info *next; 

    ITS_CHAR            *callId;
    ITS_CHAR            *userName;
    APP_CONTACT_LIST    *contactList;
}
APP_CALL_INFO;

typedef struct
{
    APP_CALL_INFO *callInfo;    
}
APP_CALL_INFO_LIST;

typedef struct
{
    ITS_CHAR *callId;
    ITS_CHAR *userName;
}
APP_TIMER_INFO;

static APP_CALL_INFO_LIST *callInfoList;

/* Function Declaration */
static int
APP_HandleINVITEIndication(ITS_HANDLE handle, ITS_EVENT *event);
static int
APP_Handle200OkIndication(ITS_HANDLE handle, ITS_EVENT *event);
static int
APP_Handle302Indication(ITS_HANDLE handle, ITS_EVENT *event);
static void
APP_WorkerThreadDispatchFunction(TPOOL_THREAD *thr, ITS_HANDLE handle);

/* Call back routing function */
int
RouteApp(ITS_HDR *hdr,ITS_EVENT *event)
{
    return  thrInstance;
}

/* Call back pre intialization function */
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

    ret = TPOOL_DispatchOnThread(thread,APP_WorkerThreadDispatchFunction,
                                       WORKER_BACK_PTR(thread));
    if (ret != ITS_SUCCESS)
    {
        thrInstance = ITS_INVALID_SRC;
    }
    else
    {
        thrInstance = ( ((WORKER_Control*)thread)->worker.instance );
    }

    /* Initialize the call info structure */
    callInfoList = ITS_Malloc(sizeof(APP_CALL_INFO_LIST));
    callInfoList->callInfo = NULL;

    printf("---- Started SIP redirect server application \n");
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function removes spaces in the given string
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
static char* 
APP_remove_space(char *str)
{
    int j =0, i = 0;
    char *str2 =  malloc(strlen(str));

    while(str[i] != '\0')
    {
        if (str[i] != ' ' && str[i] != '\n')
        {
            str2[j] = str[i];
            j++;
        }
        i++;
    }

    str2[j] = '\0';

    if (strlen(str2) == 0)
    {
        free(str2);
        return NULL;
    }
    return str2;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function deletes the call context on time out
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
static void 
APP_DeleteCallContext(ITS_CHAR *usrName, ITS_CHAR *callId)
{
    APP_CALL_INFO *info;
    APP_CALL_INFO *before = NULL;
    ITS_BOOLEAN found = ITS_FALSE;

    for (info = callInfoList->callInfo; info != NULL; info = info->next)
    {
        if (strcmp(info->userName, usrName) ==  0)
        {
            found = ITS_TRUE;
            printf("Entry found for user %s , callId  %s\n", usrName, callId);
            break;
        }
        before = info;
    }

    if (found)
    {
        /*Delete the call context */
        if (before)
        {
            before->next = info->next;
            /* Delete call list & inside contact list */
            {
                APP_CONTACT_LIST *cList = info->contactList ;
                while(cList != NULL)
                {
                    APP_CONTACT_LIST *tmp;
                    ITS_Free(cList->contactNo);
                    tmp = cList;
                    cList = cList->next;
                    ITS_Free(tmp);
                }
                ITS_Free(info);
            }
        }
        else
        {
            printf("First Entry  %s , callId  %s\n", usrName, callId);

            if (info->next)
            {
                callInfoList->callInfo = info->next;
            }
            else
            {
                callInfoList->callInfo = 0;
            }
                
            /* Delete call list & inside contact list */
            {
                APP_CONTACT_LIST *cList = info->contactList ;
                while(cList != NULL)
                {
                    APP_CONTACT_LIST *tmp;
                    printf("Deleting %s contact  %s\n", usrName, cList->contactNo);
                    ITS_Free(cList->contactNo);
                    tmp = cList;
                    cList = cList->next;
                    ITS_Free(tmp);
                }
                ITS_Free(info);
            }
        }
    }
    else
    {
        printf("Entry not found =========\n");
    }
    return;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is thread entry funtion & waits for events
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
static void
APP_WorkerThreadDispatchFunction(TPOOL_THREAD *thr, ITS_HANDLE handle)
{
    ITS_USHORT workerInstance;
    ITS_EVENT event;
    ITS_INT ret;

    WORKER_Control* worker = (WORKER_Control*)thr;
    workerInstance = worker->worker.instance;
    while(1)
    {
        event.data = 0;
        ret = WORKER_GetNextEvent(worker, &event);
        if (ret != ITS_SUCCESS)
        {
                printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
        }

        if ( event.src == ITS_SIP_SRC )
        {
            printf("Application:: Worker Thread: SIP msg receive \n");
            APP_ReceiveMsg((ITS_HANDLE)itsINTELLISIP_Class, &event);
        }
        else if (event.src == ITS_TIMER_SRC)
        {
            ITS_TimerData *timerData;
            APP_TIMER_INFO timerInfo;
            printf("Application:: Worker Thread: Timer msg received \n");

            timerData = (ITS_TimerData*)event.data;
            memcpy( (char *)&timerInfo, (char *)timerData->context,
                    sizeof(APP_TIMER_INFO));

            APP_DeleteCallContext(timerInfo.userName, timerInfo.callId);
        }
    }

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
APP_ReceiveMsg(ITS_HANDLE handle, ITS_EVENT *event)
{
   ITS_OCTET       msgId;
   SIP_EVENT_TYPE  evType;
   SIP_ERROR_TYPE  errType;
   SIP_PARSER_ERROR_DATA *parseErrData;
   SIP_ERROR_DATA *errData;
   SIP_TRANSACTION_ERROR_DATA *trnErrData;
   SIP_TRANSPORT_ERROR_DATA *tranErrData;
   SIP_INDICATION_DATA *indData;
   SIP_TIMEOUT_DATA *timeoutData;

    /* Get Event type, whether INVITE, 180 etc */
    evType = SIP_GetEventType(event);
    switch(evType)
    {
    case SIP_DATA_EVENT:
        msgId = SIP_GetMsgType(event);
        sip_last_msg = (SIP_MSG *)SIP_GET_MSG_INFO((SIP_GET_SIPEVENT(event)));
        switch(msgId)
        {
        case SIP_MSG_REGISTER:
            break;

        case SIP_MSG_INVITE:
            printf("\n ******* Received message::: INVITE  *******\n");
            APP_HandleINVITEIndication(handle, event);
            break;

        case SIP_MSG_ACK:
            printf("\n***** Received message::: ACK *******\n");
            /* Received ACK means endof transaction */
            SIP_MsgFree(sip_last_msg);
            sip_last_msg = NULL;
            break;

        case SIP_MSG_180:
            printf("\nReceived message::: 180 \n");
            break;

        case SIP_MSG_200:
            printf("\nReceived message::: 200 \n");
            APP_Handle200OkIndication(handle, event);
            break;

        case SIP_MSG_302:
            printf("\nReceived message::: 302 \n");
            APP_Handle302Indication(handle, event);
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
 *  Purpose:
 *      This function sends the redirect contact numberin 302 msg
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
APP_DivertCall(SIP_MSG *lastReq, ITS_CHAR *contUsr)
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
    SIP_SetUri(&contactUri, "sip", contUsr, NULL, &contactHostInfo);
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

    ret = SIP_SendResponse((ITS_HANDLE)itsINTELLISIP_Class, msg3xx);
    if (ret == ITS_SUCCESS)
    {
        printf("302 moved temp msg sent successfully to Stack\n");
    }
    else
    {
        printf("302 moved temp msg sent failed ret %d to Stack\n", ret);
    }
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function creates the contact list when a new call
 *      arrives here.
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
static APP_CONTACT_LIST *
APP_CreateContactList(ITS_CHAR *userName)
{
    FILE *_file = NULL;
    char *fileName = "followme.conf";
    char buf[100];
    APP_CONTACT_LIST *list = NULL;
    APP_CONTACT_LIST *first = NULL;

    _file = fopen(fileName, "r");
    if (_file == NULL)
    {
        perror("fopen failed \n");
        exit(0);
    }

    while(1)
    {
        char *a=NULL;
        if ((a = fgets(buf, 100, _file)) == NULL)
        {
            printf("End of file  \n");
            return ITS_SUCCESS;
        }

        a = APP_remove_space(buf);
        if (!a) continue;
        if (strncmp(a, userName, strlen(userName)) == 0)
        {
            printf("Found the user in the contact list %s \n", userName);
            while(1)
            {
                if (fgets(buf, 100, _file) == NULL) break;
                a = APP_remove_space(buf);
                if (!a) continue;
                if (strncmp(a, "END", strlen(buf)) == 0) break;

                if (list == NULL)
                {
                    list = ITS_Malloc(sizeof(APP_CONTACT_LIST));
                    list->contactNo  = strdup(a);
                    first = list;
                }
                else
                {
                    list->next = ITS_Malloc(sizeof(APP_CONTACT_LIST));
                    list->next->contactNo  = strdup(a);
                    list = list->next;
                }
            }
            list->next  = NULL;
            break;
        }
    }
    fclose(_file);
    return first;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function creartes call context for the new calls
 *      returns exiting context if call context already exists 
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
static APP_CALL_INFO * 
APP_CreateCallContext(ITS_CHAR *usrName, ITS_CHAR *callId)
{
    APP_CALL_INFO *info = callInfoList->callInfo;
    APP_CALL_INFO *before = NULL;

    if (info == NULL)
    {
        /* This is first call */
        info = ITS_Malloc(sizeof(APP_CALL_INFO));
        info->callId = strdup(callId);
        info->userName = strdup(usrName);
        info->next = NULL;
        info->contactList = APP_CreateContactList(usrName);
        callInfoList->callInfo = info;

        /* Start Timer */
        {
            APP_TIMER_INFO tInfo;
            tInfo.callId = info->callId;
            tInfo.userName = info->userName;

            TIMERS_StartTimer(thrInstance, 30, (void *)&tInfo, sizeof(APP_TIMER_INFO));
        }
                
        return info;
    }

    for (info = callInfoList->callInfo; info != NULL; info = info->next)
    {
        if ( strcmp(info->userName, usrName) ==  0)
        {
            return info;
        }
        
        before = info;
    }

    /* Add next entry to the list */
    {
        /*Create the new call context */
        info = ITS_Malloc(sizeof(APP_CALL_INFO));
        info->callId = strdup(callId);
        info->userName = strdup(usrName);
        info->next = NULL;
        info->contactList = APP_CreateContactList(usrName);

        if (before)
        {
            before->next = info;
        }

        /* Start Timer */
        {
            APP_TIMER_INFO tInfo;
            tInfo.callId = info->callId;
            tInfo.userName = info->userName;

            TIMERS_StartTimer(thrInstance, 100, (void *)&tInfo, sizeof(APP_TIMER_INFO));
        }
        return info;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function return the contact number according to the
 *      the priority given in the file.
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
APP_GetCurrentContact(APP_CALL_INFO *info, ITS_CHAR **contact)
{
    APP_CONTACT_LIST *contList = NULL;
    
    if (info->contactList)
    {
        contList = info->contactList;
        *contact = strdup(contList->contactNo);

        /*Delete from the list */
        info->contactList = info->contactList->next;
        ITS_Free(contList->contactNo);
        ITS_Free(contList);
    } 

    if (contList != NULL)
    {
        return ITS_SUCCESS;
    }
    return !ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function Handles the invite msg received.
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

    /* Check the request URI, find the name & find the list */
    {
        ITS_CHAR *scheme = NULL, *userName = NULL, *password = NULL;   
        SIP_HOST_INFO *hostInfo = NULL;
        ITS_CHAR *catactNo = NULL;
        APP_CALL_INFO *info = NULL;
        

        SIP_GetUri(&msg->reqUri, &scheme,  &userName, &password, &hostInfo);
        printf("call received for user %s  \n", userName);

        info = APP_CreateCallContext(userName, msg->callId.number);

        ret = APP_GetCurrentContact(info, &catactNo);
        if (ret != ITS_SUCCESS)
        {
            printf("End of contact list play announcement \n");
            catactNo = strdup("999");
        }
        printf("Got the Next contact %s \n", catactNo);

        APP_DivertCall(msg, catactNo);

        SIP_MsgFree(msg);
        ITS_Free(catactNo);
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the 200k received
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
APP_Handle200OkIndication(ITS_HANDLE handle, ITS_EVENT *event)
{
    printf("APP_Handle200OkIndication:: Received 200 ok \n");
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the 302 received
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
APP_Handle302Indication(ITS_HANDLE handle, ITS_EVENT *event)
{
    printf("APP_Handle302Indication:: Received 302 \n");
    return ITS_SUCCESS;
}
