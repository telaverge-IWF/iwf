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
 * ID: $Id: MulAppMtp3MsgHandler.cpp,v 1.1 2005/07/05 11:28:05 mmanikandan Exp $
 *
 * LOG: $Log: MulAppMtp3MsgHandler.cpp,v $
 * LOG: Revision 1.1  2005/07/05 11:28:05  mmanikandan
 * LOG: Changes for ISUP Distributed.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <math.h>
#include <MulAppMtp3MsgHandler.h>

#if defined(CCITT)
#include <itu/mtp3.h>
#elif defined(ANSI)
#include <ansi/mtp3.h>
#endif

Mtp3MsgHandler::Mtp3MsgHandler()
{
    cHandler_ = ClientHandler::GetClientHandler();
}

Mtp3MsgHandler::~Mtp3MsgHandler()
{
    cHandler_ = NULL;
}

int Mtp3MsgHandler::ProcessAppMsg(MABCL_MESSAGE* msg)
{
    ITS_EVENT evt;
    int ret = ITS_SUCCESS;

#if defined(CCITT)
    ITS_EVENT_INIT(&evt, ITS_ISUP_CCITT_SRC, msg->u.mtp3Info.len);
#elif defined(ANSI)
    ITS_EVENT_INIT(&evt, ITS_ISUP_ANSI_SRC, msg->u.mtp3Info.len);
#endif
    memcpy(evt.data, msg->u.mtp3Info.data, msg->u.mtp3Info.len);

    printf("Message to ftest client\n");
    for (int i = 0; i < evt.len; i++)
    {
        printf("%02x ", evt.data[i]);
        if (((i+1) % 16) == 0)
            printf("\n");
    }
    printf("\n");
    ret = TRANSPORT_PutEvent(ITS_MTP3_SRC, &evt);
    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&evt);
    }

    return ret;
}

int Mtp3MsgHandler::ProcessStackMsg(its::Event* evt)
{
    MTP3_HEADER mtp3;
    MABCL_MESSAGE msg;
    int cid = 0, offset = 1;
    ITS_EVENT* event = &evt->GetEvent();

    printf("\nMulApp Mtp3 Message Received......\n\n");
    for (int i = 0; i < event->len; i++)
    {
        printf("%02x ", event->data[i]);

        if ((i+1) % 16 == 0)
            printf("\n");
    }

    printf("\n");

    memset((char*)&mtp3, 0, sizeof(MTP3_HEADER));
    memcpy(&mtp3, &event->data[offset], sizeof(MTP3_HEADER));

    offset += sizeof(MTP3_HEADER);

    MABCL_ISUP isupInfo;
    MTP3_RL_GET_DPC(mtp3.label, isupInfo.lpc);
    MTP3_RL_GET_OPC(mtp3.label, isupInfo.dpc);

    isupInfo.lcic = event->data[offset];
    isupInfo.lcic |= ((event->data[offset + 1]) << 8);

    cid = cHandler_->FindBestMTP3Client(&isupInfo); 

    if (cid)
    {
        msg.msg_type = MTP3_MSG;
        msg.clientID = cid;
        msg.u.mtp3Info.len = event->len;
        msg.u.mtp3Info.data = (ITS_OCTET*)malloc(event->len);
        memcpy(msg.u.mtp3Info.data, event->data, event->len);

        return cHandler_->SendMsg(&msg);
    }

    return ITS_SUCCESS;
}

