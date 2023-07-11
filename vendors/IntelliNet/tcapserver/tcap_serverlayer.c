/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * $Id: tcap_serverlayer.c,v 9.1 2005/03/23 12:55:02 cvsadmin Exp $
 *
 * $Log: tcap_serverlayer.c,v $
 * Revision 9.1  2005/03/23 12:55:02  cvsadmin
 * Begin PR6.5
 *
 * Revision 1.8  2003/11/11 05:56:06  ssingh
 * Code changed for handling of AppInitiated response and PostNext.
 *
 * Revision 1.7  2003/10/23 06:41:47  ssingh
 * Changes done for message routing to respective clients
 * based on RouteInfo stored.
 *
 * Revision 1.6  2003/10/22 06:05:58  ssingh
 * Changes done to handle LID table finding based on DID and
 * DID to LID table entry for appInitiated message on receive
 * of Dialouge from Client. LID to DID structure changed.
 *
 * Revision 1.5  2003/10/15 04:55:31  ssingh
 * More Changes for TCAP msg handling from App.
 *
 * Revision 1.4  2003/10/13 11:28:33  ssingh
 * Changes done in PostNextEvent.
 *
 * Revision 1.3  2003/10/11 09:55:42  ssingh
 * Code changes done for Application initiated and response
 * from Remote for Application Initiated message.
 *
 * Revision 1.2  2003/10/10 06:43:34  vjatti
 * For app initiated range corrected the range check while routing
 * as < 32768
 *
 * Revision 1.1  2003/10/10 04:50:58  vjatti
 * TCAP ServerLayer Implementation initial commit.
 *
 ****************************************************************************/

#include <tcap_serverimpl.h>

#include <its.h>
#include <its_thread_pool.h>
#include <its_worker.h>
#include <engine.h>

#if defined(PRC)
#include <china/tcap.h>
#elif defined (CCITT)
#include <itu/tcap.h>
#elif defined (ANSI)
#include <ansi/tcap.h>
#include <tcap_intern.h>

#endif
#if defined(ANSI)
SS7TRAN_Manager* ISS7_ANSI_Stack;
#define ISS7_Stack         ISS7_ANSI_Stack
#endif

static ITS_USHORT workerInstanceR, workerInstanceA;
static ITS_USHORT workerInstance1, workerInstance2;
static ITS_CTXT   lDid;

/*
 *  This file contains implementations Callback functions PreFunc and others 
 */

/*
 * Route app function stack will call this function
 * when event arrrives
 */
ITS_USHORT SL_RouteToApp(ITS_HDR *hdr,ITS_EVENT *event)
{
    ITS_USHORT inst = 0;
    ITS_CTXT   did;
 
    TCAP_DEBUG(("SL_RouteToApp :: \n"));

    /* Get the DID*/
    did = ITS_GET_CTXT(&event->data[1]);

    if (did > 0 && did < 32768)
    {
        inst = workerInstance1;
    }
    else if (did == 0 || did > 32768)
    {
        inst = workerInstance2;
    }

    TCAP_DEBUG(("SL_RouteToApp :: DID = %d inst = %d\n", did, inst));

    return(inst);
}

void
TCAP_GetRouteKeyContext(SL_TCAP_DID_TO_LID_INFO didToLidInfo, 
                        SL_ROUTE_KEY *routeKey)
{
    ITS_OCTET ssn, sio;

    memset(routeKey, 0, sizeof(SL_ROUTE_KEY));

    routeKey->route_style = (ITS_OCTET)GetRouteStyle(style);

    ssn = didToLidInfo.lidXport.ssn;
    sio = 0x83;

    switch(routeKey->route_style)
    {
    case DPC:
        MTP3_RL_SET_DPC_VALUE(*routeKey, 
                MTP3_RL_GET_DPC_VALUE (didToLidInfo.lidXport));
        break;

    case SSN:
        routeKey->ssn = ssn;
        break;

    case OPC_DPC:
        MTP3_RL_SET_OPC_VALUE(*routeKey, 
                MTP3_RL_GET_OPC_VALUE (didToLidInfo.lidXport));
        MTP3_RL_SET_DPC_VALUE(*routeKey,
                MTP3_RL_GET_DPC_VALUE (didToLidInfo.lidXport));
        break;

    case DPC_SIO:
        MTP3_RL_SET_DPC_VALUE(*routeKey,
                MTP3_RL_GET_DPC_VALUE (didToLidInfo.lidXport));
        MTP3_HDR_SET_SIO(*routeKey, (sio & (MTP3_SIO_UP_MASK | 
                                            MTP3_NIC_MASK)));
        break;

    case DPC_SSN:
        MTP3_RL_SET_DPC_VALUE(*routeKey,
                MTP3_RL_GET_DPC_VALUE (didToLidInfo.lidXport));
        routeKey->ssn = ssn;
        break;

    case OPC_DPC_SIO:
        MTP3_RL_SET_OPC_VALUE(*routeKey,
                MTP3_RL_GET_OPC_VALUE (didToLidInfo.lidXport));
        MTP3_RL_SET_DPC_VALUE(*routeKey,
                MTP3_RL_GET_DPC_VALUE (didToLidInfo.lidXport));
        MTP3_HDR_SET_SIO(*routeKey, (sio & (MTP3_SIO_UP_MASK | 
                                            MTP3_NIC_MASK)));
        break;

    case OPC_DPC_SSN:
        MTP3_RL_SET_OPC_VALUE(*routeKey,
                MTP3_RL_GET_OPC_VALUE (didToLidInfo.lidXport));
        MTP3_RL_SET_DPC_VALUE(*routeKey, 
                MTP3_RL_GET_DPC_VALUE (didToLidInfo.lidXport));
        routeKey->ssn = ssn;
        break;

    case OPC_DPC_SIO_SSN:
        MTP3_RL_SET_OPC_VALUE(*routeKey,
                MTP3_RL_GET_OPC_VALUE (didToLidInfo.lidXport));
        MTP3_RL_SET_DPC_VALUE(*routeKey,
                MTP3_RL_GET_DPC_VALUE (didToLidInfo.lidXport));
        MTP3_HDR_SET_SIO(*routeKey,(sio & (MTP3_SIO_UP_MASK | 
                                           MTP3_NIC_MASK)));
        routeKey->ssn = ssn;
        break;

    default:
        TCAP_DEBUG(("Invalid Global style\n"));
        break;
    }
}

static void
SL_DispatchToAPP_RemoteInitiated(TPOOL_THREAD *thr, ITS_HANDLE handle)
{ 
    ITS_EVENT event;
    ITS_INT ret = 0;
    SL_TCAP_ROUTING_INFO rInfo;
    SL_ROUTE_KEY rKey;

    SL_TCAP_DID_TO_LID_INFO didToLidInfo;
    ITS_CTXT                dlgId;
    TCAP_DLG                dlg;

    WORKER_Control* worker = (WORKER_Control*)thr;

    memset(&event,0,sizeof(event));

    while(1)
    {
        ret = WORKER_GetNextEvent(worker, &event);
        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("IntelliSS7 Error <%s>\n", ITS_GetErrorText(ret)));
        }
        TCAP_DEBUG(("SL_DispatchToAPP_RemoteInitiated:: Received message "
                    "from Stack\n"));

        dlgId = ITS_GET_CTXT(&event.data[1]);

#if defined(CCITT)
        if (event.src == ITS_TCAP_CCITT_SRC)
#else
        if (event.src == ITS_TCAP_ANSI_SRC)
#endif
        {
            switch (event.data[0])
            {
            case ITS_TCAP_DLG:
                TCAP_DEBUG(("SL_DispatchToAPP_RemoteInitiated: Dialog rcvd\n"));

                /* After getting begin/uni store the opc/dpc/ssn 
                 * from dialouge to did-to-lid table for routing
                 * other dialouge/component to given client
                 */
                memcpy(&dlg, &event.data[1+sizeof(ITS_CTXT)], sizeof(TCAP_DLG));

               switch (dlg.ptype)
               {
               case TCPPT_TC_QUERY_W_PERM:
               case TCPPT_TC_QUERY_WO_PERM:
               case TCPPT_TC_UNI:
                    /* Get the OPC/DPC/SSN out of dlg */
                    if(dlg.ptype == TCPPT_TC_QUERY_W_PERM ||
                       dlg.ptype == TCPPT_TC_QUERY_WO_PERM)
                    {
                       MTP3_RL_SET_DPC(didToLidInfo.lidXport, dlg.u.begin.opc);
                       MTP3_RL_SET_OPC(didToLidInfo.lidXport, dlg.u.begin.dpc);


                       SCCP_DecodeAddr(&dlg.u.begin.dest_addr, NULL, 
                                        NULL, &didToLidInfo.lidXport.ssn, NULL, NULL);
#if 0
                       if(dlg.u.begin.dest_addr.data[0] & SCCP_CPA_HAS_SSN)
                       {
                          didToLidInfo.lidXport.ssn = dlg.u.begin.dest_addr.data[1];
                       }
                       else
                       {
                          didToLidInfo.lidXport.ssn = SCCP_SSN_NONE;
                       }
#endif
                    }
                    else if (dlg.ptype == TCPPT_TC_UNI)
                    {
                       MTP3_RL_SET_DPC(didToLidInfo.lidXport, dlg.u.uni.opc);
                       MTP3_RL_SET_OPC(didToLidInfo.lidXport, dlg.u.uni.dpc);

                       SCCP_DecodeAddr(&dlg.u.begin.dest_addr, NULL, 
                                        NULL, &didToLidInfo.lidXport.ssn, NULL, NULL);
#if 0
                       if(dlg.u.begin.dest_addr.data[0] & SCCP_CPA_HAS_SSN)
                       {
                          didToLidInfo.lidXport.ssn = dlg.u.uni.dest_addr.data[1];
                       }
                       else
                       {
                          didToLidInfo.lidXport.ssn = SCCP_SSN_NONE;
                       }
#endif
                    }

                    SL_AllocTCAPDidToLid(didToLidInfo.lidXport, dlgId);
                    break;

                default:
                    ret = SL_FindTCAPDidToLid (&didToLidInfo, dlgId);

                    if(ret != ITS_SUCCESS)
                    {
                       TCAP_ERROR(("No Entry found\n"));
                    }
                    break;
                }

                TCAP_GetRouteKeyContext(didToLidInfo, &rKey);   

                /* Find routing context to route to client */
                ret = SL_FindTCAPRoutingInfo(rKey, &rInfo);
                if (ret != ITS_SUCCESS)
                {
                    TCAP_DEBUG(("SL_DispatchToAPP_RemoteInitiated:Couldnt "
                                "find Routing Info\n"));
                    workerInstanceR = 1;
                }
                else
                {
                    TCAP_DEBUG(("SL_DispatchToAPP_RemoteInitiated:Sending "
                                "TCAP msg\n"));
                } 

                workerInstanceR = rInfo.client_id;

                break;

            case ITS_TCAP_CPT:
                TCAP_DEBUG(("SL_DispatchToAPP_RemoteInitiated:: CPT rcvd\n"));

                ret = SL_FindTCAPDidToLid (&didToLidInfo, dlgId);

                if(ret != ITS_SUCCESS)
                {
                   TCAP_ERROR (("Unable to Route Component\n"));
                }
                
                break;

            default:
                break;
            }
        }
        ret = TRANSPORT_PutEvent(workerInstanceR, &event);
        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("Transport putevent failed ret = %d\n", ret));
        }
    }
}

/* This API handles Application initiated msgs' responses */

static void
SL_DispatchToAPP_AppInitiated(TPOOL_THREAD *thr, ITS_HANDLE handle)
{
    ITS_EVENT               event;
    ITS_INT                 ret = ITS_SUCCESS;
    SL_TCAP_ROUTING_INFO    rInfo;
    SL_ROUTE_KEY            rKey;
    TCAP_DLG                dlg;
    TCAP_CPT                cpt;
    ITS_CTXT                dlgId;
    SL_TCAP_DID_TO_LID_INFO didToLidInfo;
    SL_LID_XPORT_ID         lidXportKey;

    WORKER_Control* worker = (WORKER_Control*)thr;

    memset(&event,0,sizeof(event));

    while(1)
    {
        ret = WORKER_GetNextEvent(worker, &event);
        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("IntelliSS7 Error <%s>\n", ITS_GetErrorText(ret)));
        }

        TCAP_DEBUG(("SL_DispatchToAPP_AppInitiated:: Received message "
                    "from Stack\n"));

#if defined(CCITT)
        if (event.src == ITS_TCAP_CCITT_SRC)
#else
        if (event.src == ITS_TCAP_ANSI_SRC)
#endif
        {
            switch (event.data[0])
            {
            case ITS_TCAP_DLG:
                TCAP_DEBUG(("SL_DispatchToAPP_AppInitiated ::Dialog rcvd\n"));

                dlgId = ITS_GET_CTXT(&event.data[1]);

                /* find entry in did to lid table */
                ret = SL_FindTCAPDidToLid(&didToLidInfo, dlgId);
                if (ret != ITS_SUCCESS)
                {
                    TCAP_DEBUG((" DID to LID conversion failed.\n"));
                    lDid = 0;
                }
                else
                {
                    lDid = didToLidInfo.lidXport.lid;
                }

                TCAP_GetRouteKeyContext(didToLidInfo, &rKey);

                ret = SL_FindTCAPRoutingInfo(rKey, &rInfo);
                if (ret != ITS_SUCCESS)
                {
                    TCAP_DEBUG(("SL_DispatchToAPP_AppInitiated: Couldnt find "
                                "Routing Info\n"));
                    workerInstanceA = 1;
                }
                else
                {
                    TCAP_DEBUG(("SL_DispatchToAPP_AppInitiated: Recovered "
                                "Routing Info\n"));
                }

                workerInstanceA = rInfo.client_id;

                /* Replace did by lid */
                ITS_SET_CTXT(&event.data[1], lDid);

                /* Find Dialouge type */
                memcpy(&dlg, &event.data[1 + sizeof(ITS_CTXT)],
                                             sizeof(TCAP_DLG));

                /* If abort/end */
                switch (dlg.ptype)
                {
                case TCPPT_TC_RESP:
                case TCPPT_TC_ABORT:
                     /* Delete DID_TO_LID entry */
                     SL_DeleteTCAPDidToLid(dlgId);

                     lidXportKey.lid       = lDid;
                     lidXportKey.client_id = (ITS_UINT) workerInstanceA;

                     /* Delete LID_TO_DID entry */
                     SL_DeleteTCAPLidToDid(lidXportKey);

                     break;

                default:
                     break;
                }
                break;

            case ITS_TCAP_CPT:
                TCAP_DEBUG(("SL_DispatchToAPP_AppInitiated:: CPT rcvd\n"));

                /* If there is no entry for this componet in did-to-lid
                   table and componet type is reject/cancel, its component
                   processing failed, route it to client after getting
                   client_id from lid-to-did table.
                */
                memcpy(&cpt, &event.data[1 + sizeof(ITS_CTXT)],
                                             sizeof(TCAP_CPT));

                if (cpt.ptype == TCPPT_TC_REJECT ||
                    cpt.ptype == TCPPT_TC_CANCEL)
                {
                    TCAP_DEBUG(("Reject or Cancel from STACK\n"));

                    dlgId = ITS_GET_CTXT(&event.data[1]);

                    /* Find entry in did to lid table */
                    ret = SL_FindTCAPDidToLid(&didToLidInfo, dlgId);
                    if (ret != ITS_SUCCESS)
                    {
                       /* Rejection from stack during component processing */
                       /* get the clientId and pass it to that */ 
                      ret = SL_FindClientRoutingInfo(dlgId, &workerInstanceA);
                      if (ret != ITS_SUCCESS)
                      {
                         TCAP_DEBUG(("Can't route only component\n"));
                      }
                      else
                      {
                         TCAP_DEBUG(("Routing to client Instance = %d\n",workerInstanceA));
                      }
                    }
                }
                break;

            default:
                break;
            }
        }

        ret = TRANSPORT_PutEvent(workerInstanceA, &event);
        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("Transport putevent failed ret = %d\n", ret));
        }
    }
}

/*
 * Pre func do Initialization stuff
 */
void SL_PreFunc(void)
{
    int ret = 0;
    TPOOL_THREAD* thread1, *thread2;
    WORKER_Control* worker;
    WORKER_Control* worker2;

    ret = SL_Init_HashTables();
    if (ret != ITS_SUCCESS)
    {
        TCAP_ERROR(("SL_PreFunc:  SL_Init_HashTables Fialed aborting\n"));

        abort();
    }

    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread1)) != ITS_SUCCESS )
    {
        TCAP_WARNING(("***No more worker threads!\n"));
        return;
    }

    ret = TPOOL_DispatchOnThread(thread1,SL_DispatchToAPP_AppInitiated,
                                 WORKER_BACK_PTR(thread1));

    worker = (WORKER_Control*)thread1;
    workerInstance1 = worker->worker.instance;
    TCAP_DEBUG(("workerInstance1 = %d\n", workerInstance1));

    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread2)) != ITS_SUCCESS )
    {
        TCAP_WARNING(("***No more worker threads!\n"));
        return;
    }

    ret = TPOOL_DispatchOnThread(thread2,SL_DispatchToAPP_RemoteInitiated,
                                 WORKER_BACK_PTR(thread2));

    worker2 = (WORKER_Control*)thread2;
    workerInstance2 = worker2->worker.instance;
    TCAP_DEBUG(("workerInstance2 = %d\n", workerInstance2));

    TCAP_DEBUG(("SL_PreFunc: Exiting function .....\n"));
}

/*
 * Post Function to clean up
 */
void SL_PostFunc(void)
{
    /* Clean up */
    SL_Term_HashTables();
    TCAP_DEBUG(("SL_PostFunc: --- Clean up ----\n"));
}


/*
 * This function is called by iterative socket when 
 * it recieves  an event  from client
 */
int SL_PostNextEvent(TPOOL_THREAD *thr, ITS_EVENT *evt)
{
    int                     ret = ITS_SUCCESS;
    TCAP_DLG                dlg;
    ITS_CTXT                did;
    SL_TCAP_LID_TO_DID_INFO lidToDidInfo;
    SL_TCAP_DID_TO_LID_INFO didToLidInfo;

    WORKER_Control* worker = (WORKER_Control*)thr; 

    switch (evt->src)
    {
    case SL_APP_TCAP_SRC:
        TCAP_DEBUG(("SL_PostNextEvent: TCAP msg rcvd from Client\n"));

        /* Check for App initiated msg/rsp of Remote initiated */

        if (ITS_GET_CTXT(&evt->data[1]) < 32768 &&
            ITS_GET_CTXT(&evt->data[1]) > 0)
        {
            lidToDidInfo.lidXportKey.lid = ITS_GET_CTXT(&evt->data[1]);
            lidToDidInfo.lidXportKey.client_id =
                                        (ITS_UINT) worker->worker.instance;

            /* Check for previous entry in LID+XPORT to DID table */
            ret = SL_FindTCAPLidToDid (&lidToDidInfo, lidToDidInfo.lidXportKey);
            if (ret != ITS_SUCCESS)
            {
                TCAP_DEBUG(("No entry exist in LID_TO_DID\n"));

                TCAP_AllocateDialogueId(ISS7_Stack, &did);

                /* Fill the entry in LID_TO_DID table */
                ret = SL_AllocTCAPLidToDid(did, lidToDidInfo.lidXportKey);

                if (ret != ITS_SUCCESS)
                {
                    TCAP_DEBUG(("Allocate DID failed; Msg dropped\n"));
                    return !ITS_SUCCESS;
                }

                ITS_SET_CTXT(&evt->data[1], did);
            }
            else
            {
                TCAP_DEBUG(("Entry found in LID_TO_DID\n"));

                ITS_SET_CTXT(&evt->data[1], lidToDidInfo.did);
            }

            if (evt->data[0] == ITS_TCAP_DLG)
            {
                memcpy(&dlg, &evt->data[1 + sizeof(ITS_CTXT)],
                                                   sizeof(TCAP_DLG));

                switch (dlg.ptype)
                {
                case TCPPT_TC_UNI  :
                     /* Delete LID_TO_DID entry */
                     SL_DeleteTCAPLidToDid(lidToDidInfo.lidXportKey);
                     break;
 
                case TCPPT_TC_QUERY_W_PERM:
                case TCPPT_TC_QUERY_WO_PERM:
                     MTP3_RL_SET_OPC(lidToDidInfo.lidXportKey, dlg.u.begin.opc);
                     MTP3_RL_SET_DPC(lidToDidInfo.lidXportKey, dlg.u.begin.dpc);

                     SCCP_DecodeAddr(&dlg.u.begin.orig_addr, NULL, NULL, 
                                     &lidToDidInfo.lidXportKey.ssn, NULL, NULL);

#if 0
                     if(dlg.u.begin.dest_addr.data[0] & SCCP_CPA_HAS_SSN)
                     {
                        lidToDidInfo.lidXportKey.ssn = dlg.u.begin.dest_addr.data[1];
                     }
                     else
                     {
                        lidToDidInfo.lidXportKey.ssn = SCCP_SSN_NONE;
                     }
#endif

                     /* Add the entry in DID_TO_LID table */
                     SL_AllocTCAPDidToLid(lidToDidInfo.lidXportKey,
                                                       lidToDidInfo.did);
                     break;

                case TCPPT_TC_CONV_W_PERM:
                case TCPPT_TC_CONV_WO_PERM:
                     if (SL_FindTCAPDidToLid(&didToLidInfo, lidToDidInfo.did)
                         != ITS_SUCCESS)
                     {
                        /* This is out of sequence message from app */
                        TCAP_ERROR(("SL_PostNetEvent: Out of Sequence msg\n"));
                        return (ITS_BADTCAPMESSAGE);
                     }
                     break;

                case TCPPT_TC_RESP:
                     if (SL_FindTCAPDidToLid(&didToLidInfo, lidToDidInfo.did)
                         != ITS_SUCCESS)
                     {
                        /* This is out of sequence message from app */
                        TCAP_ERROR(("SL_PostNetEvent: Out of Sequence msg\n"));
                        return (ITS_BADTCAPMESSAGE);
                     }
                     else
                     {
                         /* Delete LID_TO_DID entry */
                         SL_DeleteTCAPLidToDid(lidToDidInfo.lidXportKey);

                         /* Delete DID_TO_LID entry */
                         SL_DeleteTCAPDidToLid(lidToDidInfo.did);
                     }
                     break;

                case TCPPT_TC_ABORT:
                     /* Delete LID_TO_DID entry */
                     SL_DeleteTCAPLidToDid(lidToDidInfo.lidXportKey);

                     /* Delete DID_TO_LID entry */
                     SL_DeleteTCAPDidToLid(lidToDidInfo.did);
                     break;
 
                default:
                     break;
                }
            }
        }
        else
        {
            /* Delete DID to LID entry if End/Abort */
            if (evt->data[0] == ITS_TCAP_DLG)
            {
                memcpy(&dlg, &evt->data[1 + sizeof(ITS_CTXT)],
                                                   sizeof(TCAP_DLG));

                switch (dlg.ptype)
                {
                case TCPPT_TC_RESP:
                case TCPPT_TC_ABORT:
                     /* Delete DID_TO_LID entry */
                     SL_DeleteTCAPDidToLid(ITS_GET_CTXT(&evt->data[1]));
                     break;

                default:
                     break;       
                }
            }
        }

        if (TRANSPORT_PutEvent(ITS_TCAP_SRC, evt) != ITS_SUCCESS)
        {
            TCAP_WARNING(("Send Event to TCAP Stack failed."));
            ITS_EVENT_TERM(evt);
        }
        break;

    case SL_SRC_SERVER:
        /* This for server*/
        if (evt->data[0] == SL_TCAP_REGISTER_EVENT) 
        {
            TCAP_DEBUG(("SL_PostNextEvent: Registration event received\n"));

            ret = SL_Register(worker->worker.instance, evt);
        }
        else if (evt->data[0] == SL_TCAP_DEREGISTER_EVENT) 
        {
            TCAP_DEBUG(("SL_PostNextEvent: Deregistration event received\n"));

            ret = SL_Deregister(worker->worker.instance, evt);
        }
        else
        {
            TCAP_ERROR(("SL_PostNextEvent: Unknown Server event recieved \n"));
        }

        ITS_EVENT_TERM(evt);
        break;

    default:
        TCAP_DEBUG(("SL_PostNextEvent: UnknowMessage with Unknown SRC 0x%X\n", 
                                       evt->src));

        ITS_EVENT_TERM(evt);
        break;
    } 

    /* This must not ITS_SUCCESS*/
    return !ITS_SUCCESS;
}

/*
 * This is function is called when Write Event fails
 * For a that socket
 */
int SL_NextEventFailed(TPOOL_THREAD *thr, int pReturn)
{
    ITS_INT sockId;
    WORKER_Control *worker = (WORKER_Control*)thr;

    sockId = worker->worker.instance;

    TCAP_DEBUG(("SL_NextEventFailed: rcvd on Transport ID = %d\n", sockId));

    SL_DeleteClientRoutingInfo(sockId);

    return (!ITS_SUCCESS);
}

/*
 * This function is called when Server accepts client connection
 */
int SL_OnAccept(TPOOL_THREAD *thr, int pReturn)
{
    TCAP_DEBUG(("SL_OnAccept: Client Connected \n"));
    return (ITS_SUCCESS);
}
