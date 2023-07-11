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
 * ID: $Id: ansi-isup_dis.c,v 1.4 2007/01/30 06:24:46 yranade Exp $
 *
 * LOG: $Log: ansi-isup_dis.c,v $
 * LOG: Revision 1.4  2007/01/30 06:24:46  yranade
 * LOG: Get things to compile.
 * LOG:
 * LOG: Revision 1.3  2007/01/11 12:43:35  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 1.2.6.1  2006/07/17 22:40:47  omayor
 * LOG: Added ISUPDIS prefix to disrtibuted ISUP connection state enum.
 * LOG:
 * LOG: Revision 1.2  2005/07/19 09:30:12  mmanikandan
 * LOG: Compiler Errors are resolved.
 * LOG:
 * LOG: Revision 1.1  2005/07/05 11:42:55  mmanikandan
 * LOG: Initial commit for ISUP distributed.
 * LOG:
 *
 ****************************************************************************/

#undef ANSI
#undef CCITT
#define ANSI

#include <isup_dis_client.h>
#include <its_transports.h>

#include <ansi/isup.h>

static ITS_HANDLE ISUPPrimaryHand_ = NULL;
static ITS_HANDLE ISUPBackupHand_ = NULL;

typedef enum
{
    ISUPDIS_CONNECTED,
    ISUPDIS_REGISTERED,
    ISUPDIS_IDLE
}CONNECTION_STATE;

CONNECTION_STATE PrimaryConnectionState = ISUPDIS_IDLE;
CONNECTION_STATE BackupConnectionState = ISUPDIS_IDLE;

ITS_UINT clientID = 0;

ISUPDIS_DLLAPI ITS_INT
ISUPDIS_Encode(ISUPDIS_MESSAGE *msg, ITS_EVENT *event)
{
    /* structure to event */
    ITS_INT index=0, i;

    if(event->data == NULL)
    {
        return !ITS_SUCCESS;
    }
   
    event->data[index++] = msg->clientID & 0x000000FF;
    event->data[index++] = (msg->clientID & 0x0000FF00) >> 8;
    event->data[index++] = (msg->clientID & 0x00FF0000) >> 16;
    event->data[index++] = (msg->clientID & 0xFF000000) >> 24;

    event->data[index++] = msg->msg_type;
    switch(msg->msg_type)
    {
        case REGISTER_MSG:
        {
            event->src = ISUPDIS_APP_SRC;

            event->data[index++] = msg->u.regInfo.routing_criteria;
            event->data[index++] = msg->u.regInfo.numOfRecords;

            for (i = 0; i < msg->u.regInfo.numOfRecords; i++)
            {
                switch(msg->u.regInfo.routing_criteria)
                {
                    case ISUPDIS_ISUP_RT_LPC_CIC_RANGE:
                    {
                        event->data[index++] = msg->u.regInfo.isup[i].regType;
                        memcpy(&event->data[index], 
                               &msg->u.regInfo.isup[i].lpc,
                               sizeof(MTP3_POINT_CODE));
          
                        index += sizeof(MTP3_POINT_CODE);

                        event->data[index++] = 
                        msg->u.regInfo.isup[i].lcic & 0x00FF;
                        event->data[index++] = 
                          (msg->u.regInfo.isup[i].lcic & 0xFF00) >> 8;
    
                        event->data[index++] = 
                          msg->u.regInfo.isup[i].ucic & 0x00FF;
                        event->data[index++] = 
                          (msg->u.regInfo.isup[i].ucic & 0xFF00) >> 8;
                        break;
                    } 
                    case ISUPDIS_ISUP_RT_DPC_CIC_RANGE:
                    {
                        event->data[index++] = msg->u.regInfo.isup[i].regType;
                        memcpy(&event->data[index], 
                              &msg->u.regInfo.isup[i].dpc,
                              sizeof(MTP3_POINT_CODE));
    
                        index += sizeof(MTP3_POINT_CODE);
    
                        event->data[index++] = 
                           msg->u.regInfo.isup[i].lcic & 0x00FF;
                        event->data[index++] = 
                           (msg->u.regInfo.isup[i].lcic & 0xFF00) >> 8;
    
                        event->data[index++] = 
                            msg->u.regInfo.isup[i].ucic & 0x00FF;
                        event->data[index++] = 
                            (msg->u.regInfo.isup[i].ucic & 0xFF00) >> 8;
                        break;
                    }
                    case ISUPDIS_ISUP_RT_LPC:
                    {
                        event->data[index++] = msg->u.regInfo.isup[i].regType;
                        memcpy(&event->data[index], 
                               &msg->u.regInfo.isup[i].lpc,
                               sizeof(MTP3_POINT_CODE));
    
                        index += sizeof(MTP3_POINT_CODE);
    
                        break;
                    }
                    case ISUPDIS_ISUP_RT_DPC:
                    {
                        event->data[index++] = msg->u.regInfo.isup[i].regType;
                        memcpy(&event->data[index], 
                               &msg->u.regInfo.isup[i].dpc,
                               sizeof(MTP3_POINT_CODE));
    
                        index += sizeof(MTP3_POINT_CODE);
    
                        break;
                    }
                }       
            }
            break;
        } 
        case DEREGISTER_MSG:
        {
            event->src = ISUPDIS_APP_SRC;
            event->data[index++] = 
                    msg->u.regInfo.routing_criteria;
            break;
        }
        case MANAGEMENT_MSG:
        {
            event->src = ISUPDIS_MGMT_SRC;
            event->data[index++] = msg->u.mgmtInfo.mgmtMsg; 
            switch(msg->u.mgmtInfo.mgmtMsg)
            {
                case ISUPDIS_MTP3_MSG_PAUSE:
                case ISUPDIS_MTP3_MSG_RESUME:
                case ISUPDIS_MTP3_MSG_STATUS:
                { 
                    memcpy(&event->data[index], 
                           &msg->u.mgmtInfo.pc,
                           sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);
                    break;
                }
            }
            break; 
        }
        case REGISTER_ACK_MSG:
        {
            event->data[index++] = msg->u.regAck.routing_criteria;
            event->data[index++] = msg->u.regAck.result;
            event->data[index++] = msg->u.regAck.errorCode & 0x00FF;
            event->data[index++] = 
                (msg->u.regAck.errorCode & 0xFF00) >> 8;
            break;
        }
        case DERGISTER_ACK_MSG: 
        {
            event->data[index++] = msg->u.deregAck.routing_criteria;
            event->data[index++] = msg->u.deregAck.result;
            event->data[index++] = msg->u.deregAck.errorCode & 0x00FF;
            event->data[index++] = 
                (msg->u.deregAck.errorCode & 0xFF00) >> 8;
            break;
        }
        case MTP3_MSG:
        {
            memcpy(&event->data[index],
                   msg->u.isupInfo.data,
                   msg->u.isupInfo.len);

            index += msg->u.isupInfo.len;
            break;
        }
    }/* switch end */
    
    event->len = index;
    return ITS_SUCCESS; 
}

ISUPDIS_DLLAPI ITS_INT
ISUPDIS_Decode(ISUPDIS_MESSAGE *msg, ITS_EVENT *event)
{
    ITS_INT index = 0, i = 0;

    msg->clientID = 0;
    msg->clientID |= event->data[index++];
    msg->clientID |= event->data[index++] << 8;
    msg->clientID |= event->data[index++] << 16;
    msg->clientID |= event->data[index++] << 24;

    msg->msg_type = event->data[index++];

    switch(msg->msg_type)
    {
        case REGISTER_MSG:
        {
            msg->u.regInfo.routing_criteria = event->data[index++];
            msg->u.regInfo.numOfRecords = event->data[index++];

            for (i = 0; i < msg->u.regInfo.numOfRecords; i++)
            {
                switch(msg->u.regInfo.routing_criteria)
                {
                    case ISUPDIS_ISUP_RT_LPC_CIC_RANGE:
                    { 
                        memcpy(&msg->u.regInfo.isup[i].lpc, 
                               &event->data[index], 
                               sizeof(MTP3_POINT_CODE));
                        index += sizeof(MTP3_POINT_CODE);
    
                        msg->u.regInfo.isup[i].lcic = 0;
                        msg->u.regInfo.isup[i].lcic |= 
                            event->data[index++];
                        msg->u.regInfo.isup[i].lcic |= 
                            event->data[index++] << 8;
    
                        msg->u.regInfo.isup[i].ucic = 0;
                        msg->u.regInfo.isup[i].ucic |= 
                            event->data[index++];
                        msg->u.regInfo.isup[i].ucic |= 
                            event->data[index++] << 8;
                        break;
                    } 
                    case ISUPDIS_ISUP_RT_DPC_CIC_RANGE:
                    {
                        memcpy(&msg->u.regInfo.isup[i].dpc, 
                               &event->data[index], 
                               sizeof(MTP3_POINT_CODE));
                        index += sizeof(MTP3_POINT_CODE);
        
                        msg->u.regInfo.isup[i].lcic = 0;
                        msg->u.regInfo.isup[i].lcic |= 
                           event->data[index++];
                        msg->u.regInfo.isup[i].lcic |= 
                           event->data[index++] << 8;
    
    
                        msg->u.regInfo.isup[i].ucic =0;
                        msg->u.regInfo.isup[i].ucic |= 
                           event->data[index++];
                        msg->u.regInfo.isup[i].ucic |= 
                           event->data[index++] << 8;
                        break;
                    }
                    case ISUPDIS_ISUP_RT_LPC:
                    { 
                        memcpy(&msg->u.regInfo.isup[i].lpc, 
                               &event->data[index], 
                               sizeof(MTP3_POINT_CODE));
    
                        index += sizeof(MTP3_POINT_CODE);
                        break;
                    }
                    case ISUPDIS_ISUP_RT_DPC:
                    {
                        memcpy(&msg->u.regInfo.isup[i].dpc, 
                               &event->data[index], 
                               sizeof(MTP3_POINT_CODE));
                        index += sizeof(MTP3_POINT_CODE);
                        break;
                    }
                }
            }
            break;
        }
        case DEREGISTER_MSG:
        {
            msg->u.regInfo.routing_criteria = 
               event->data[index++];
            break;
        }
        case MANAGEMENT_MSG:
        {
            msg->u.mgmtInfo.mgmtMsg = event->data[index++];
            switch(msg->u.mgmtInfo.mgmtMsg)
            {
                case ISUPDIS_MTP3_MSG_PAUSE:
                case ISUPDIS_MTP3_MSG_RESUME:
                case ISUPDIS_MTP3_MSG_STATUS:
                {
                    memcpy(&msg->u.mgmtInfo.pc, 
                           &event->data[index],
                           sizeof(MTP3_POINT_CODE)); 

                    index += sizeof(MTP3_POINT_CODE);
                    break;
                } 
            }
            break;
        }
        case REGISTER_ACK_MSG:
        {
            msg->u.regAck.routing_criteria = 
               event->data[index++];
            msg->u.regAck.result = event->data[index++];
            msg->u.regAck.errorCode =0;
            msg->u.regAck.errorCode |= event->data[index++];
            msg->u.regAck.errorCode |= event->data[index++] << 8;
            break;
        }
        case DERGISTER_ACK_MSG:
        {
            msg->u.deregAck.routing_criteria = event->data[index++];
            msg->u.deregAck.result = event->data[index++];
            msg->u.deregAck.errorCode =0;
            msg->u.deregAck.errorCode |= event->data[index++];
            msg->u.deregAck.errorCode |= event->data[index++] << 8;
            break;
        }
        case MTP3_MSG:
        {
            msg->u.isupInfo.len = (event->len - index); 
            msg->u.isupInfo.data = 
              (ITS_OCTET *)malloc(msg->u.isupInfo.len);

            memcpy(msg->u.isupInfo.data, &event->data[index], msg->u.isupInfo.len);

            index += msg->u.isupInfo.len;
            break;
        }
    }
    return ITS_SUCCESS;
}

ISUPDIS_DLLAPI ITS_INT
ISUPDIS_SendMsg_ANSI(ITS_EVENT *evt)
{
    ISUPDIS_MESSAGE msg;
    ITS_EVENT event;

    ITS_EVENT_INIT(&event, ISUPDIS_ISUP_SRC, evt->len + 10);

    msg.clientID = clientID;
    msg.msg_type = MTP3_MSG;
    msg.u.isupInfo.data = evt->data;
    msg.u.isupInfo.len = evt->len;

    ISUPDIS_Encode(&msg, &event);

    if ((PrimaryConnectionState == ISUPDIS_REGISTERED) && ISUPPrimaryHand_)
    {
        TRANSPORT_PutEvent (TRANSPORT_INSTANCE(ISUPPrimaryHand_), &event);
    }
    else if ((BackupConnectionState == ISUPDIS_REGISTERED) && ISUPBackupHand_)
    {
        TRANSPORT_PutEvent (TRANSPORT_INSTANCE(ISUPBackupHand_), &event);
    }

    return ITS_SUCCESS;
}

ISUPDIS_DLLAPI ITS_INT
ISUPDIS_Register_ANSI(ISUPDIS_MESSAGE *ctxt)
{
    int i = 0;
    ITS_EVENT evt;

    if (!clientID)
    {
        clientID = ctxt->clientID;
    }

    ITS_EVENT_INIT(&evt, ISUPDIS_APP_SRC, sizeof(ISUPDIS_REGISTER) + 8);
    ISUPDIS_Encode(ctxt, &evt);

    printf("Register Message to server %d\n", evt.len);
    for (i = 0 ; i < evt.len; i++)
    {
        printf("%02x ", evt.data[i]);
        if (((i+1) % 16) == 0)
            printf("\n");
    }
    printf("\n");

    if (PrimaryConnectionState == ISUPDIS_CONNECTED)
    {
        TRANSPORT_PutEvent (TRANSPORT_INSTANCE(ISUPPrimaryHand_), &evt);
    }

    if (BackupConnectionState == ISUPDIS_CONNECTED)
    {
        TRANSPORT_PutEvent (TRANSPORT_INSTANCE(ISUPBackupHand_), &evt);
    }

    return ITS_SUCCESS;
}

ISUPDIS_DLLAPI ITS_INT
ISUPDIS_Deregister_ANSI(ISUPDIS_MESSAGE *ctxt)
{
    ITS_EVENT evt;
    ITS_EVENT_INIT(&evt, ISUPDIS_APP_SRC, sizeof(ISUPDIS_DEREGISTER) + 8);
    ISUPDIS_Encode(ctxt, &evt);

    if (PrimaryConnectionState == ISUPDIS_REGISTERED)
    {
        TRANSPORT_PutEvent (TRANSPORT_INSTANCE(ISUPPrimaryHand_), &evt);
    }

    if (BackupConnectionState == ISUPDIS_REGISTERED)
    {
        TRANSPORT_PutEvent (TRANSPORT_INSTANCE(ISUPBackupHand_), &evt);
    }

    return ITS_SUCCESS;
}

ISUPDIS_DLLAPI ITS_INT
ISUPDIS_PriPostInit_ANSI(TPOOL_THREAD* thr, ITS_HANDLE hnd)
{
    ISUPPrimaryHand_ = hnd;
    PrimaryConnectionState = ISUPDIS_CONNECTED;

    return ITS_SUCCESS;
}

ISUPDIS_DLLAPI ITS_INT
ISUPDIS_BkPostInit_ANSI(TPOOL_THREAD* thr, ITS_HANDLE hnd)
{
    ISUPBackupHand_ = hnd;
    BackupConnectionState = ISUPDIS_CONNECTED;

    return ITS_SUCCESS;
}

ISUPDIS_DLLAPI ITS_INT
ISUPDIS_PriRecvMsg_ANSI(TPOOL_THREAD *thr, ITS_EVENT *event)
{
    ITS_INT ret = ITS_SUCCESS; 
    ISUPDIS_MESSAGE msg;

    ret = ISUPDIS_Decode(&msg, event);

    if (ret != ITS_SUCCESS)
        return ret;

    switch (msg.msg_type)
    {
        case MTP3_MSG:
        {
            ITS_EVENT evt;
            ITS_EVENT_INIT(&evt, ITS_MTP3_SRC, msg.u.isupInfo.len);
            memcpy(evt.data, msg.u.isupInfo.data, msg.u.isupInfo.len);
            TRANSPORT_PutEvent(ITS_ISUP_ANSI_SRC, &evt);
            break;
        }
        case MANAGEMENT_MSG:
        {
            break;
        }
        case REGISTER_ACK_MSG:
        {
            PrimaryConnectionState = ISUPDIS_REGISTERED;
            break;
        }
        case DERGISTER_ACK_MSG:
        {
            PrimaryConnectionState = ISUPDIS_CONNECTED;
            break;
        }
        default:
            break;
    }

    return ITS_SUCCESS;
}

ISUPDIS_DLLAPI ITS_INT
ISUPDIS_BkRecvMsg_ANSI(TPOOL_THREAD *thr, ITS_EVENT *event)
{
    ITS_INT ret = ITS_SUCCESS;
    ISUPDIS_MESSAGE msg;

    ret = ISUPDIS_Decode(&msg, event);

    if (ret != ITS_SUCCESS)
        return ret;

    switch (msg.msg_type)
    {
        case MTP3_MSG:
        {
            ITS_EVENT evt;
            ITS_EVENT_INIT(&evt, ITS_MTP3_SRC, msg.u.isupInfo.len);
            memcpy(evt.data, msg.u.isupInfo.data, msg.u.isupInfo.len);
            TRANSPORT_PutEvent(ITS_ISUP_ANSI_SRC, &evt);
            break;
        }
        case MANAGEMENT_MSG:
        {
            break;
        }
        case REGISTER_ACK_MSG:
        {
            BackupConnectionState = ISUPDIS_REGISTERED;
            break;
        }
        case DERGISTER_ACK_MSG:
        {
            BackupConnectionState = ISUPDIS_CONNECTED;
            break;
        }
        default:
            break;
    }

    return ITS_SUCCESS;
}

