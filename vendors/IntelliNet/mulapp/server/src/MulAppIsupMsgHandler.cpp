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
 * ID: $Id: MulAppIsupMsgHandler.cpp,v 1.1 2005/07/05 11:28:05 mmanikandan Exp $
 *
 * LOG: $Log: MulAppIsupMsgHandler.cpp,v $
 * LOG: Revision 1.1  2005/07/05 11:28:05  mmanikandan
 * LOG: Changes for ISUP Distributed.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <math.h>
#include <MulAppIsupMsgHandler.h>

#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#endif

IsupMsgHandler::IsupMsgHandler()
{
    cHandler_ = ClientHandler::GetClientHandler();
}

IsupMsgHandler::~IsupMsgHandler()
{
    cHandler_ = NULL;
}

ITS_INT
IsupMsgHandler::ReserveCIC(MABCL_MESSAGE* msg)
{
    ITS_OCTET sio =0, cic_state =0;
    ITS_UINT  opc,dpc;
    ITS_USHORT cic =0;
    ITS_CTXT vcic =0;
    ITS_INT ret = 0;

    opc = MTP3_RL_GET_OPC_VALUE(msg->u.rsvInfo.mtp3.label);
    dpc = MTP3_RL_GET_DPC_VALUE(msg->u.rsvInfo.mtp3.label);
    sio = MTP3_HDR_GET_SIO(msg->u.rsvInfo.mtp3) & (MTP3_SIO_UP_MASK | MTP3_NIC_MASK);
    cic = msg->u.rsvInfo.cic;

    ret = ISUP_ReserveCIC(SL_HANDLE, sio, opc, 
                               dpc, cic, &cic_state,
                               &vcic);

    if (ret != ITS_SUCCESS)
    {
        printf("Error in Assigning CIC %d\n", cic);
    }

    MABCL_MESSAGE rsvcicAck;
    rsvcicAck.clientID = msg->clientID;
    rsvcicAck.msg_type = ISUP_RSV_CIC_ACK_MSG;
    rsvcicAck.u.rsvInfo.mtp3 = msg->u.rsvInfo.mtp3;
    rsvcicAck.u.rsvInfo.cic = msg->u.rsvInfo.cic;
    rsvcicAck.u.rsvInfo.cic_state = cic_state;
    rsvcicAck.u.rsvInfo.vcic = vcic;
    rsvcicAck.u.rsvInfo.ret = ret;

    return cHandler_->SendMsg(&rsvcicAck);
}

ITS_INT
IsupMsgHandler::UnReserveCIC(MABCL_MESSAGE* msg)
{
    ITS_OCTET sio =0;
    ITS_UINT  opc,dpc;
    ITS_USHORT cic =0;
    ITS_INT ret = 0;

    opc = MTP3_RL_GET_OPC_VALUE(msg->u.unrsvInfo.mtp3.label);
    dpc = MTP3_RL_GET_DPC_VALUE(msg->u.unrsvInfo.mtp3.label);
    sio = MTP3_HDR_GET_SIO(msg->u.unrsvInfo.mtp3) & (MTP3_SIO_UP_MASK | MTP3_NIC_MASK);
    cic = msg->u.unrsvInfo.cic;

    ret = ISUP_UnReserveCIC(SL_HANDLE, sio, opc,
                               dpc, cic);

    if (ret != ITS_SUCCESS)
    {
        printf("Error in UnReserve CIC %d\n", cic);
    }

    MABCL_MESSAGE unrsvcicAck;
    unrsvcicAck.clientID = msg->clientID;
    unrsvcicAck.msg_type = ISUP_URSV_CIC_ACK_MSG;
    unrsvcicAck.u.unrsvInfo.mtp3 = msg->u.unrsvInfo.mtp3;
    unrsvcicAck.u.unrsvInfo.cic = msg->u.unrsvInfo.cic;
    unrsvcicAck.u.unrsvInfo.ret = ret;

    return cHandler_->SendMsg(&unrsvcicAck);
}

int IsupMsgHandler::ProcessAppMsg(MABCL_MESSAGE* msg)
{
    ITS_EVENT evt;
    int ret = ITS_SUCCESS;

    switch (msg->msg_type)
    {
    case ISUP_MSG:
        {
            ITS_EVENT_INIT(&evt, MABCL_ISUP_SRC, msg->u.isupInfo.len);
            memcpy(evt.data, msg->u.isupInfo.data, msg->u.isupInfo.len);
            ret = TRANSPORT_PutEvent(ITS_ISUP_SRC, &evt);
            if (ret != ITS_SUCCESS)
            {
                ITS_EVENT_TERM(&evt);
            }
            break;
        }
    case ISUP_RSV_CIC_MSG:
        {
            ret = ReserveCIC(msg);
            break;
        }
    case ISUP_URSV_CIC_ACK_MSG:
        {
            ret = UnReserveCIC(msg);
            break;
        }
    }
    return ret;
}

int IsupMsgHandler::ProcessStackMsg(its::Event* evt)
{
    MTP3_HEADER mtp3;
    MABCL_MESSAGE msg;
    int cid = 0, i ,offset = 0;
    ITS_EVENT* event = &evt->GetEvent();

    memset((char*)&mtp3, 0, sizeof(MTP3_HEADER));

    memcpy(&mtp3, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT) +
                             sizeof(ITS_USHORT)], sizeof(MTP3_HEADER));

    printf("Data received on isup msg handler\n");
    for (i = 0 ;i < event->len; i++)
    {
        printf("%02x ", event->data[i]);
        if ((i+1) % 16 == 0)
            printf("\n");
    }

    printf("\n");

    MABCL_ISUP isupInfo;
    MTP3_RL_GET_DPC(mtp3.label, isupInfo.lpc);
    MTP3_RL_GET_OPC(mtp3.label, isupInfo.dpc);

    offset = sizeof(ITS_OCTET) + sizeof(ITS_CTXT);
    isupInfo.lcic = 0;
    isupInfo.lcic = ((event->data[offset++]) & 0x00FF);
    isupInfo.lcic |= ((event->data[offset++] << 8) & 0xFF00);

    printf("OPC : %d DPC : %d LCIC : %d\n", MTP3_PC_GET_VALUE(isupInfo.lpc), 
              MTP3_PC_GET_VALUE(isupInfo.dpc), isupInfo.lcic);

    cid = cHandler_->FindBestISUPClient(&isupInfo); 
    printf("Finding Client %d\n",cid);

    if (cid)
    {
        msg.msg_type = ISUP_MSG;
        msg.clientID = cid;
        msg.u.isupInfo.len = evt->GetLength();
        msg.u.isupInfo.data = (ITS_OCTET*)malloc(evt->GetLength());
        memcpy(msg.u.isupInfo.data, evt->GetData(), evt->GetLength());

        return cHandler_->SendMsg(&msg);
    }

    return ITS_SUCCESS;
}

