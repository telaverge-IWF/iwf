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
 * $Id: serverlayer.c,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
 *
 * $Log: serverlayer.c,v $
 * Revision 9.1  2005/03/23 12:54:27  cvsadmin
 * Begin PR6.5
 *
 * Revision 1.2  2005/03/23 09:41:22  cvsadmin
 * PR6.4.2 sources propagated to Current.
 *
 * Revision 1.1.2.3.6.2.12.2  2005/01/05 10:31:31  craghavendra
 * Critical Trace before abort().
 *
 * Revision 1.1.2.3.6.2.12.1  2004/12/15 05:53:21  mmanikandan
 * Windows Build Support.
 *
 * Revision 1.1.2.3.6.2  2004/01/27 14:30:59  sjaddu
 * Changes for active-backup configuration.
 *
 * Revision 1.1.2.3.6.1  2004/01/05 10:01:25  sjaddu
 * Merged code from tcs isup branch.
 *
 * Revision 1.1.2.3.2.11  2003/12/03 11:14:27  ssingh
 * Node1RouteToApp and Node2RouteToApp app-selectors are modified to
 * pass PAUSE-RESUME and Local-congestion Indication to both copies of
 * apps. Selection of worker-instance changed from vcic based to cic based.
 *
 * Revision 1.1.2.3.2.10  2003/11/24 06:44:23  akumar
 * Removed ISUP_ERROR statement.
 *
 * Revision 1.1.2.3.2.9  2003/11/03 13:34:08  sjaddu
 * Removed c++ style comments.
 *
 * Revision 1.1.2.3.2.8  2003/10/31 06:03:23  sjaddu
 * memset added before getnext event.
 *
 * Revision 1.1.2.3.2.7  2003/10/21 06:23:44  akumar
 * Pause/Resume/status ind modification done.
 *
 * Revision 1.1.2.3.2.6  2003/10/13 10:23:28  akumar
 * Code cleanup operation.
 *
 * Revision 1.1.2.3.2.5  2003/10/10 14:34:08  sjaddu
 * Ual call back is added to get trans id.
 *
 * Revision 1.1.2.3.2.4  2003/09/15 11:40:56  akumar
 * Misc modifications.
 *
 * Revision 1.1.2.3.2.3  2003/09/13 06:42:42  akumar
 * Replaced printf with Trace Macros.
 *
 * Revision 1.1.2.3.2.2  2003/08/29 09:51:31  akumar
 * Modifications for Routing and Deregistration APi.
 *
 * Revision 1.1.2.3.2.1  2003/08/26 12:48:45  sjaddu
 * Redunadnacy changes done.
 *
 * Revision 1.1.2.3  2003/06/20 11:17:20  sjaddu
 * changed printf to ISUP_DEBUG.
 *
 * Revision 1.1.2.2  2003/06/18 08:21:24  tsanthosh
 * Added Request & Response functionality.
 *
 * Revision 1.1.2.1  2003/06/05 05:43:46  sjaddu
 * Added first revision of files for isupserver.
 *
 *
 ****************************************************************************/

#include <serverimpl.h>

#include <its.h>
#include <its_thread_pool.h>
#include <its_worker.h>
#include <engine.h>

#if defined(PRC)
#include <china/isup.h>
#elif defined (CCITT)
#include <itu/isup.h>
#elif defined (ANSI)
#include <ansi/isup.h>
#endif

#include <its_ual.h>
#include <its_redundancy.h>

void
ApplicationMembershipChangeCb( ITS_POINTER object, ITS_POINTER userData,
                               ITS_POINTER callData);
/* global sctp trans ids */
ITS_UINT __ISUP_SCTP_TARNS_ID_1 =0;
ITS_UINT __ISUP_SCTP_TARNS_ID_2 =0;

static ITS_UINT _ISUP_routing_worker_inst1;
static ITS_UINT _ISUP_routing_worker_inst2;
static ITS_UINT _ISUP_routing_worker_inst3;

/*
 *  This file contains implementations Callback functions PreFunc and others 
 */

/*
 * Route app function stack will call this function
 * when event arrrives
 */
ITS_USHORT SL_Node1RouteToApp(ITS_HDR *hdr,ITS_EVENT *event)
{
    int          offset = 0;
    ITS_USHORT   cic = ITS_ISUP_INV_CIC;

    ISUP_DEBUG(("Calling SL_Node1RouteToApp functions\n"));

    if ((event->data[0] == ISUP_MSG_STAT)  ||
        (event->data[0] == ISUP_MSG_LCONG))
    {
            return _ISUP_routing_worker_inst1;
    }

    if (event->src == ITS_ISUP_SRC)
    {
        offset += sizeof(ITS_OCTET) + sizeof(ITS_CTXT);
        cic = ((event->data[offset++]) & 0x00FF);
        cic |= ((event->data[offset] << 8) & 0xFF00);
    }
    else if (event->src == ISUP_SRC_APP)
    {
        offset += sizeof(ITS_OCTET) + sizeof(MTP3_HEADER);
        cic = ((event->data[offset++]) & 0x00FF);
        cic |= ((event->data[offset] << 8) & 0xFF00);
    }

    if (cic % 2 == 0)
    {
        if (event->src == ITS_ISUP_SRC)
        {
            return _ISUP_routing_worker_inst1;
        }
        else if (event->src == ISUP_SRC_APP)
        {
            return ITS_ISUP_SRC;
        }
        else
        {
            return ITS_NO_SRC;
        }
    }
    else
    {
        return ITS_NO_SRC;
    }
}

/*
 * Routing thread function which does the routing and puts
 * on to the socket
 */
static void
Node1RoutingThreadFunction(TPOOL_THREAD* thr, ITS_HANDLE handle)
{
    int ret = 0;
    ITS_USHORT inst = 0;
    MTP3_HEADER mtp3;
    MTP3_HEADER reverse_mtp3;
    SL_ISUP_ROUTING_INFO rInfo;
    ITS_EVENT event;

    WORKER_Control* worker = (WORKER_Control*)thr;

    ISUP_DEBUG(("RoutingThreadFunction: Entering function\n"));
    memset(&event, 0, sizeof(ITS_EVENT));

    while(1)
    {
        ret = WORKER_GetNextEvent(worker, &event);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret)));
            continue;
        }

        memset((char*)&mtp3, 0, sizeof(MTP3_HEADER));
        memcpy(&mtp3, &event.data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT) +
                                  sizeof(ITS_USHORT)], sizeof(MTP3_HEADER));

        switch (event.data[0])
        {
        case ISUP_MSG_TIM:
        case ISUP_MSG_ERR:
        case ISUP_MSG_IND:
        case ISUP_MSG_LCONG:
            break;
        case ITS_STATE_CHANGE_EVENT:
            /* Send the event to all primary appications registered*/
             SL_HandleStateChangeEventFromStack(&event);
             ITS_EVENT_TERM(&event);
             continue;
        case ISUP_MSG_STAT:
            ISUP_DEBUG(("Received Management Msg-- \n"));
            break;
        default:
            /* will be a isup message */
            memset((char*)&reverse_mtp3, 0, sizeof(MTP3_HEADER));
            MTP3_RL_SET_OPC_VALUE(reverse_mtp3.label,
                                  MTP3_RL_GET_DPC_VALUE(mtp3.label));
            MTP3_RL_SET_DPC_VALUE(reverse_mtp3.label,
                                  MTP3_RL_GET_OPC_VALUE(mtp3.label));
            reverse_mtp3.sio = MTP3_HDR_GET_SIO(mtp3) & (MTP3_SIO_UP_MASK |
                               MTP3_NIC_MASK);
            mtp3 = reverse_mtp3;
            break;
        }

        ret = SL_FindISUPRoutingInfo(mtp3, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ISUP_WARNING(("Node1RoutingThreadFunction: Could not find Routing "
                          "Info for:\n"));
            /* Return default one, will see later*/
            ISUP_WARNING(("OPC %d DPC %d SIO %d\n",
                        MTP3_RL_GET_OPC_VALUE(mtp3.label),
                        MTP3_RL_GET_DPC_VALUE(mtp3.label),
                        MTP3_HDR_GET_SIO(mtp3) & (MTP3_SIO_UP_MASK |
                                   MTP3_NIC_MASK)));
            inst = 1;
        }
        else
        {
            ISUP_DEBUG(("Node1RoutingThreadFunction:Sending ISUP msg OPC %d "
                        "DPC %d SIO %d\n",
                        MTP3_RL_GET_OPC_VALUE(mtp3.label),
                        MTP3_RL_GET_DPC_VALUE(mtp3.label),
                        MTP3_HDR_GET_SIO(mtp3) & (MTP3_SIO_UP_MASK |
                        MTP3_NIC_MASK)));

            if (rInfo.primCon.isUp)
            {
                inst = rInfo.primCon.client_id;
            }
            else if (rInfo.backupCon.isUp)
            {
                inst = rInfo.backupCon.client_id;
            }
            else
            { /* This is like not getting the rInfo, will never be here */
                ISUP_WARNING(("Node1RoutingThreadFunction: This Should not happen \n"));
            }

            ret =  TRANSPORT_PutEvent(inst, &event);
            if (ret != ITS_SUCCESS)
            {
                ITS_EVENT_TERM(&event);
            }
        }
    }
}

/*
 * Route app function stack will call this function
 * when event arrrives at Node 2
 */

ITS_USHORT SL_Node2RouteToApp(ITS_HDR *hdr,ITS_EVENT *event)
{
    int          offset = 0; 
    ITS_USHORT   cic;

    ISUP_DEBUG(("Calling SL_Node2RouteToApp functions\n"));

    if ((event->data[0] == ISUP_MSG_STAT)  ||
        (event->data[0] == ISUP_MSG_LCONG))
    {
        return _ISUP_routing_worker_inst2;
    }

    if (event->src == ITS_ISUP_SRC)
    {
        offset += sizeof(ITS_OCTET) + sizeof(ITS_CTXT);
        cic = ((event->data[offset++]) & 0x00FF);
        cic |= ((event->data[offset] << 8) & 0xFF00);
    }
    else if (event->src == ISUP_SRC_APP)
    {
        offset += sizeof(ITS_OCTET) + sizeof(MTP3_HEADER);
        cic = ((event->data[offset++]) & 0x00FF);
        cic |= ((event->data[offset] << 8) & 0xFF00);
    }

    if (cic % 2 != 0)
    {
        if (event->src == ITS_ISUP_SRC)
        {
            return _ISUP_routing_worker_inst2;
        }
        else if (event->src == ISUP_SRC_APP)
        {
            return ITS_ISUP_SRC;
        }
        else
        {
            return ITS_NO_SRC;
        }
    }
    else
    {
        return ITS_NO_SRC;
    }
}

/*
 * Routing thread function which does the routing and puts
 * on to the socket
 */
static void
Node2RoutingThreadFunction(TPOOL_THREAD* thr, ITS_HANDLE handle)
{
    int ret = 0;
    ITS_USHORT inst = 0;
    MTP3_HEADER mtp3;
    MTP3_HEADER reverse_mtp3;
    SL_ISUP_ROUTING_INFO rInfo;
    ITS_EVENT event;

    WORKER_Control* worker = (WORKER_Control*)thr;

    ISUP_DEBUG(("Node2RoutingThreadFunction: Entering function\n"));
    memset(&event, 0, sizeof(ITS_EVENT));

    while(1)
    {
        ret = WORKER_GetNextEvent(worker, &event);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret)));
            continue;
        }

        memset((char*)&mtp3, 0, sizeof(MTP3_HEADER));
        memcpy(&mtp3, &event.data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT) +
                                  sizeof(ITS_USHORT)], sizeof(MTP3_HEADER));

        switch (event.data[0])
        {
        case ISUP_MSG_TIM:
        case ISUP_MSG_ERR:
        case ISUP_MSG_IND:
        case ISUP_MSG_LCONG:
            break;
        case ITS_STATE_CHANGE_EVENT:
            /* Send the event to all primary appications registered*/
             SL_HandleStateChangeEventFromStack(&event);
             ITS_EVENT_TERM(&event);
             continue;
        case ISUP_MSG_STAT:
            ISUP_DEBUG(("Received Management Msg-- \n"));
            break;

        default:
            /* will be a isup message */
            memset((char*)&reverse_mtp3, 0, sizeof(MTP3_HEADER));
            MTP3_RL_SET_OPC_VALUE(reverse_mtp3.label,
                                  MTP3_RL_GET_DPC_VALUE(mtp3.label));
            MTP3_RL_SET_DPC_VALUE(reverse_mtp3.label,
                                  MTP3_RL_GET_OPC_VALUE(mtp3.label));
            reverse_mtp3.sio = MTP3_HDR_GET_SIO(mtp3) & (MTP3_SIO_UP_MASK |
                               MTP3_NIC_MASK);
            mtp3 = reverse_mtp3;
            break;
        }

        ret = SL_FindISUPRoutingInfo(mtp3, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ISUP_WARNING(("Node2RoutingThreadFunction: Could not find "
                          "Routing Info for:\n"));
            /* Return default one, will see later*/
            ISUP_WARNING(("OPC %d DPC %d SIO %d\n",
                        MTP3_RL_GET_OPC_VALUE(mtp3.label),
                        MTP3_RL_GET_DPC_VALUE(mtp3.label),
                        MTP3_HDR_GET_SIO(mtp3) & (MTP3_SIO_UP_MASK |
                                   MTP3_NIC_MASK)));
            inst = 1;
        }
        else
        {
            ISUP_DEBUG(("Node2RoutingThreadFunction:Sending ISUP msg OPC "
                        "%d DPC %d SIO %d\n",
                        MTP3_RL_GET_OPC_VALUE(mtp3.label),
                        MTP3_RL_GET_DPC_VALUE(mtp3.label),
                        MTP3_HDR_GET_SIO(mtp3) & (MTP3_SIO_UP_MASK |
                        MTP3_NIC_MASK)));

            if (rInfo.primCon.isUp)
            {
                inst = rInfo.primCon.client_id;
            }
            else if (rInfo.backupCon.isUp)
            {
                inst = rInfo.backupCon.client_id;
            }
            else
            {
                ISUP_WARNING(("Node2RoutingThreadFunction:: This Should not happen \n"));
            }

            ret =  TRANSPORT_PutEvent(inst, &event);
            if (ret != ITS_SUCCESS)
            {
                ITS_EVENT_TERM(&event);
            }
        }
    }
}

/*
 * Route app function stack will call this function
 * when event arrrives at a node when other node is down
 */

SRVDLLAPI
ITS_USHORT SL_AllNodeRouteToApp(ITS_HDR *hdr,ITS_EVENT *event)
{
    ISUP_DEBUG(("Calling SL_AllNodeRouteToApp functions\n"));

    if (event->src == ITS_ISUP_SRC)
    {
        return _ISUP_routing_worker_inst3;
    }
    else if (event->src == ISUP_SRC_APP)
    {
        return ITS_ISUP_SRC;
    }
    else
    {
        /* Should never reach here */
        return ITS_NO_SRC;
    }
}

/*
 * Routing thread function which does the routing and puts
 * on to the socket, in case one of the nodes go down
 */
static void
AllNodeRoutingThreadFunction(TPOOL_THREAD* thr, ITS_HANDLE handle)
{
    int ret = 0;
    ITS_USHORT inst = 0;
    MTP3_HEADER mtp3;
    MTP3_HEADER reverse_mtp3;
    SL_ISUP_ROUTING_INFO rInfo;
    ITS_EVENT event;
    ITS_CTXT vcic = 0;

    WORKER_Control* worker = (WORKER_Control*)thr;

    ISUP_DEBUG(("AllNodeRoutingThreadFunction: Entering function\n"));
    memset(&event, 0, sizeof(ITS_EVENT));

    while(1)
    {
        ret = WORKER_GetNextEvent(worker, &event);
        if (ret != ITS_SUCCESS)
        {
            ISUP_DEBUG(("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret)));
            continue;
        }

        memset((char*)&mtp3, 0, sizeof(MTP3_HEADER));
        memcpy(&mtp3, &event.data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT) +
                                  sizeof(ITS_USHORT)], sizeof(MTP3_HEADER));

        switch (event.data[0])
        {
        case ISUP_MSG_TIM:
        case ISUP_MSG_ERR:
        case ISUP_MSG_IND:
        case ISUP_MSG_LCONG:
            break;
        case ITS_STATE_CHANGE_EVENT:
            /* Send the event to all primary appications registered*/
             SL_HandleStateChangeEventFromStack(&event);
             ITS_EVENT_TERM(&event);
             continue;
        case ISUP_MSG_STAT:
            ISUP_DEBUG(("Received Management Msg-- \n"));
            break;
        default:
            /* will be a isup message */
            memset((char*)&reverse_mtp3, 0, sizeof(MTP3_HEADER));
            MTP3_RL_SET_OPC_VALUE(reverse_mtp3.label,
                                  MTP3_RL_GET_DPC_VALUE(mtp3.label));
            MTP3_RL_SET_DPC_VALUE(reverse_mtp3.label,
                                  MTP3_RL_GET_OPC_VALUE(mtp3.label));
            reverse_mtp3.sio = MTP3_HDR_GET_SIO(mtp3) & (MTP3_SIO_UP_MASK |
                               MTP3_NIC_MASK);
            mtp3 = reverse_mtp3;
            break;
        }

        ret = SL_FindISUPRoutingInfo(mtp3, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ISUP_WARNING(("AllNodeRoutingThreadFunction: Could not find "
                          "Routing Info for:\n"));
            /* Return default one, will see later*/
            ISUP_WARNING(("OPC %d DPC %d SIO %d\n",
                        MTP3_RL_GET_OPC_VALUE(mtp3.label),
                        MTP3_RL_GET_DPC_VALUE(mtp3.label),
                        MTP3_HDR_GET_SIO(mtp3) & (MTP3_SIO_UP_MASK |
                                   MTP3_NIC_MASK)));
            inst = 1;
        }
        else
        {
            ISUP_DEBUG(("AllNodeRoutingThreadFunction:Sending ISUP msg "
                        "OPC %d DPC %d SIO %d\n",
                        MTP3_RL_GET_OPC_VALUE(mtp3.label),
                        MTP3_RL_GET_DPC_VALUE(mtp3.label),
                        MTP3_HDR_GET_SIO(mtp3) & (MTP3_SIO_UP_MASK |
                        MTP3_NIC_MASK)));

            memcpy(&vcic, &event.data[1], sizeof(ITS_CTXT));

            if (DSM_GetNodeId() == 1)
            {
   
                /* Both the applications are up */
                if (rInfo.primCon.isUp && rInfo.backupCon.isUp)
                {
                   if (vcic % 2 == 0)
                   {
                      inst = rInfo.primCon.client_id;
                   }
                   else
                   {
                      inst = rInfo.backupCon.client_id;
                   }
                }
      
                /* Only primary or secondary is up */
                else if (rInfo.primCon.isUp)
                {
                   inst = rInfo.primCon.client_id;
                }
                else if (rInfo.backupCon.isUp)
                {
                   inst = rInfo.backupCon.client_id;
                }
                else
                {
                    /* No application is up - Fatal */
                    ISUP_CRITICAL(("No Application is up, Fatal"));
                }
            }
            else
            {  /* Node 2 is up */
    
                /* Both the applications are up */
                if (rInfo.primCon.isUp && rInfo.backupCon.isUp)
                {
                   if (vcic % 2 != 0)
                   {
                      inst = rInfo.primCon.client_id;
                   }
                   else
                   {
                      inst = rInfo.backupCon.client_id;
                   }
                }
      
                /* Only primary or secondary is up */
                else if (rInfo.primCon.isUp)
                {
                   inst = rInfo.primCon.client_id;
                }
                else if (rInfo.backupCon.isUp)
                {
                   inst = rInfo.backupCon.client_id;
                }
                else
                {
                    /* No application is up */
                    ISUP_CRITICAL(("No Application is up, Fatal"));
                }
            }

            ret =  TRANSPORT_PutEvent(inst, &event);
            if (ret != ITS_SUCCESS)
            {
                ITS_EVENT_TERM(&event);
            }
        }
    }
}

/*
 * Call back for UAL mgmt
 */
static void
ISUP_UAL_Callback(ITS_POINTER object,
                  ITS_POINTER userData,
                  ITS_POINTER callData)
{
    UAL_CB_Context *ctxt;

    /* store the routing key as transportInstanceParam, and transport as
     *  transportId
     */
    if (callData == NULL)
    {
        ISUP_ERROR(("ISUP_UAL_Callback context data NULL \n"));
        return;
    }

    ctxt = (UAL_CB_Context *)callData;

    if (UAL_CB_CTXT_TYPE(ctxt) == UAL_CB_AS_CTXT)
    {
        if (UAL_CB_CTXT_AS_STATE(ctxt) == UAL_AS_ACTIVE)
        {
            if (__ISUP_SCTP_TARNS_ID_1 == 0)
            {
                __ISUP_SCTP_TARNS_ID_1 = UAL_CB_CTXT_TRANS_ID(ctxt);
                ISUP_DEBUG(("--- Received Transport active -- ID_1 %d\n",
                        __ISUP_SCTP_TARNS_ID_1));
            }
            else if (__ISUP_SCTP_TARNS_ID_2 == 0)
            {
                __ISUP_SCTP_TARNS_ID_2 = UAL_CB_CTXT_TRANS_ID(ctxt);
                ISUP_DEBUG(("--- Received Transport active -- ID_2 %d\n",
                        __ISUP_SCTP_TARNS_ID_2));
            }
            else
            {
                printf("--- Received Transport active -- ID %d\n",
                        UAL_CB_CTXT_TRANS_ID(ctxt));
            }

            ISUP_DEBUG((" --- Received Transport active ---\n"));

        }
        else if (UAL_CB_CTXT_AS_STATE(ctxt) == UAL_AS_INACTIVE)
        {
            if (__ISUP_SCTP_TARNS_ID_1 == UAL_CB_CTXT_TRANS_ID(ctxt))
            {
                __ISUP_SCTP_TARNS_ID_1 = 0;
            }
            else if (__ISUP_SCTP_TARNS_ID_2 ==  UAL_CB_CTXT_TRANS_ID(ctxt))
            {
                __ISUP_SCTP_TARNS_ID_2 = 0;
            }
            ISUP_CRITICAL((" --- Received Transport inactive ---\n"));
        }
    }
}


/*
 * Pre func do Initialization stuff
 */
SRVDLLAPI
void SL_PreFunc(void)
{
    int ret = 0;
    TPOOL_THREAD* thread1, *thread2, *thread3;

    ret = SL_Init_HashTables();
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SL_PreFunc:  SL_Init_HashTables Fialed aborting\n"));
        abort();
    }

    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread1)) != ITS_SUCCESS )
    {
        ISUP_ERROR(("***No more worker threads *******\n"));
        return ;
    }

    ret = TPOOL_DispatchOnThread(thread1,
                                 Node1RoutingThreadFunction,
                                 WORKER_TRANSPORT(thread1));
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("---- Fialed to diapatch Routing thread ----\n"));
        exit(1);
    }

    _ISUP_routing_worker_inst1 = ((WORKER_Control*)thread1)->worker.instance;

    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread2)) != ITS_SUCCESS )
    {
        ISUP_ERROR(("***No more worker threads *******\n"));
        return ;
    }

    ret = TPOOL_DispatchOnThread(thread2,
                                 Node2RoutingThreadFunction,
                                 WORKER_TRANSPORT(thread2));
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("---- Fialed to diapatch Routing thread ----\n"));
        exit(1);
    }

    _ISUP_routing_worker_inst2 = ((WORKER_Control*)thread2)->worker.instance;

    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread3)) != ITS_SUCCESS )
    {
        ISUP_ERROR(("***No more worker threads *******\n"));
        return ;
    }

    ret = TPOOL_DispatchOnThread(thread3,
                                 AllNodeRoutingThreadFunction,
                                 WORKER_TRANSPORT(thread3));
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("---- Fialed to diapatch Routing thread ----\n"));
        exit(1);
    }

    _ISUP_routing_worker_inst3 = ((WORKER_Control*)thread3)->worker.instance;

#if defined(ISUP_O_SCTP)
    if (CALLBACK_AddCallback(__UAL_MgntCallBack,
                             ISUP_UAL_Callback, NULL) != ITS_SUCCESS)
    {
        exit(0);
    }
#endif

    ISUP_DEBUG(("SL_PreFunc: Exiting function .....\n"));
}

/*
 * Post Function to clean up
 */
SRVDLLAPI
void SL_PostFunc(void)
{
    /* Clean up */
    SL_Term_HashTables();
    ISUP_DEBUG(("SL_PostFunc: --- Clean up ----\n"));
}


/*
 * This function is called by iterative socket when it recieves 
 * an event  from client
 */
SRVDLLAPI
int SL_PostNextEvent(TPOOL_THREAD *thr, ITS_EVENT *evt)
{
    int ret =0;
    WORKER_Control* worker = (WORKER_Control*)thr;

    switch (evt->src)
    {
    case SL_APP_ISUP_SRC:
        /* This is app msg pass on to ISUP*/
        ISUP_DEBUG(("SL_PostNextEvent: Recieved ISUP msg from cleint \n"));
        ret = TRANSPORT_PutEvent(ITS_ISUP_SRC, evt);
        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT_TERM(evt);
        }
        break;

    case SL_APP_TCAP_SRC:
        /* This is app msg pass on to SCCP*/

        ISUP_DEBUG(("SL_PostNextEvent: Recieved TCAP msg from cleint \n"));
        ret = TRANSPORT_PutEvent(ITS_SCCP_SRC, evt);
        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT_TERM(evt);
        }
        break;

    case SL_SRC_SERVER:
        /* This for server*/

        if (evt->data[0] == SL_ISUP_REGISTER_EVENT || 
            evt->data[0] == SL_ISUP_REGISTER_BACKUP_EVENT)
        {
            ISUP_DEBUG(("SL_PostNextEvent: Recieved Registration Event from Client\n"));
            /*registration event recieved*/
            ret = SL_Register(worker->worker.instance, evt);
        }
        else if (evt->data[0] == SL_ISUP_DEREGISTER_EVENT ||
                 evt->data[0] == SL_TCAP_DEREGISTER_EVENT ||
                 evt->data[0] == SL_ISUP_DEREGISTER_BACKUP_EVENT)
        {
            ISUP_DEBUG(("SL_PostNextEvent: Recieved Deregistration Event from Client\n"));
            ret = SL_Deregister(worker->worker.instance, evt);
        }
        else if (evt->data[0] == SL_ISUP_RESERVE_CIC_REQ )
        {
             /* Handle Reserve Cic Request Event */
             ret = SL_HandleReserveCICReq(worker->worker.instance, 
                                          evt);
        }
        else if (evt->data[0] == ITS_STATE_CHANGE_EVENT)
        {
            ret = SL_HandleStateChangeEventFromApp(evt);        
        }
        else if (evt->data[0] == SL_ISUP_UNRESERVE_CIC_REQ )
        {
             /* Handle UnReserve Cic Request Event */
             ret = SL_HandleUnReserveCICReq(worker->worker.instance, evt);
        }
        else
        {
            ISUP_ERROR(("SL_PostNextEvent: Unknown Server Events is Recieved ...\n"));
        }

        ITS_EVENT_TERM(evt);
        break;

    default:
        ISUP_ERROR(("SL_PostNextEvent: Message Recieved with unknown src\n"));
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
SRVDLLAPI
int SL_NextEventFailed(TPOOL_THREAD *thr, int pReturn)
{
    ITS_INT sockId;
    WORKER_Control *worker = (WORKER_Control*)thr;

    sockId = worker->worker.instance;

    ISUP_WARNING(("SL_NextEventFailed: For Transport ID = %d\n", sockId));

    SL_DeleteClientRoutingInfo(sockId);

    return (!ITS_SUCCESS);
}

/*
 * This function is called when Server accepts client connection
 */
SRVDLLAPI
int SL_OnAccept(TPOOL_THREAD *thr, int pReturn)
{
    ISUP_DEBUG(("SL_OnAccept: Client Connected \n"));
    return (ITS_SUCCESS);
}

#if 0
/*
 * This function will take care of switchover and subsequent routing
 */
void
ApplicationMembershipChangeCb(
    ITS_POINTER object,
    ITS_POINTER userData,
    ITS_POINTER callData)
{
    DSM_MembershipChangeCbData*
        membershipChangeCbData =
            (DSM_MembershipChangeCbData*)callData;

    ITS_USHORT concernedNodeId = membershipChangeCbData->memberNodeId;

    /* Two nodes system only. */
    /*if (membershipChangeCbData->memberNodeId != DSM_GetNodeId()) */
        if (membershipChangeCbData->
                membershipChangeType ==
                    DSM_FT_GROUP_MEMBER_LEAVE)
        {
            printf("$$$$ DSM_FT_GROUP_MEMBER_LEAVE: NODEID = %d\n",
                        concernedNodeId);

            ROUTE_SetApplicationSelector(SL_AllNodeRouteToApp);

        }
        else if (membershipChangeCbData->
                     membershipChangeType ==
                        DSM_FT_GROUP_MEMBER_JOIN)
        {

            printf("$$$$ DSM_FT_GROUP_MEMBER_JOIN: NODEID = %d\n",
                        concernedNodeId);

            if (DSM_GetNodeId() == 1)
            {
                ROUTE_SetApplicationSelector(SL_Node1RouteToApp);
            }
            else
            {
                ROUTE_SetApplicationSelector(SL_Node2RouteToApp);
            }
        }
        else if (membershipChangeCbData->
                     membershipChangeType ==
                        DSM_FT_GROUP_MEMBER_ALIVE)
        {

            printf("$$$$ DSM_FT_GROUP_MEMBER_ALIVE: NODEID = %d\n",
                        concernedNodeId);
        }
}
#endif
