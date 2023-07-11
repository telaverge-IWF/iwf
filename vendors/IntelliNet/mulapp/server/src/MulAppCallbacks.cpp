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
 * ID: $Id: MulAppCallbacks.cpp,v 1.5 2005/07/05 11:28:05 mmanikandan Exp $
 *
 * LOG: $Log: MulAppCallbacks.cpp,v $
 * LOG: Revision 1.5  2005/07/05 11:28:05  mmanikandan
 * LOG: Changes for ISUP Distributed.
 * LOG:
 * LOG: Revision 1.4  2005/06/08 07:17:02  mmanikandan
 * LOG: GCS CPP Binding.
 * LOG:
 * LOG: Revision 1.3  2005/06/02 13:38:48  adutta
 * LOG: Changes done for redundancy
 * LOG:
 * LOG: Revision 1.2  2005/05/30 11:01:52  mmanikandan
 * LOG: Initial commit for Redundancy.
 * LOG:
 * LOG: Revision 1.1  2005/05/25 10:13:59  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/

#include <math.h>
#include <iostream>
#include <string>
#include <ClientInterface.h>
#include <MulAppMsgHandler.h>
#include <mab_dbc.h>
#include <MulAppTcapMsgHandler.h>
#include <MulAppIsupMsgHandler.h>
#include <MulAppMtp3MsgHandler.h>

#if defined(PRC)
#include <china/isup.h>
#include <china/tcap.h>
#elif defined (CCITT)
#include <itu/isup.h>
#include <itu/tcap.h>
#elif defined (ANSI)
#include <ansi/isup.h>
#include <ansi/tcap.h>
#endif

#include <its_redundancy.h>
#include <isup_intern.h>

#define MAB_NUM_OF_THREADS  2
#define MAB_WORKITEM_QUEUE  20000

#if defined (ANSI)
   DEFINE_MTP3_POST_INIT_ANSI_CPP
   DEFINE_MTP3_INTERNODE_ANSI_CPP
#elif defined (CCITT)
   DEFINE_MTP3_POST_INIT_CCITT_CPP
   DEFINE_MTP3_INTERNODE_CCITT_CPP
#endif

its::WorkItemPool *MabWorkItemPool =NULL;

extern "C"
{

MULAPP_DLLAPI ITS_USHORT 
RouteAllToApp(ITS_HDR* h, ITS_EVENT* ev)
{
    printf("Inside RouteAllToApp............\n");
    return MAP_MSG_QUEUE;
}

MULAPP_DLLAPI ITS_USHORT 
RouteNoneToApp(ITS_HDR* h, ITS_EVENT* ev)
{
    printf("Inside RouteNoneToApp..........\n");

    if (ev->src == ITS_MAB_SRC)
    {
       return MAP_MSG_QUEUE;
    }
    else
    { 
       return ITS_NO_SRC;
    }
}

MULAPP_DLLAPI ITS_USHORT 
RouteOddToApp(ITS_HDR* hdr, ITS_EVENT* event)
{
    printf("Inside RouteOddToApp..........\n");

    int          offset = 0;
    ITS_USHORT   cic = 0;

    if (event->src == ITS_ISUP_SRC)
    {
        if ((event->data[0] == ISUP_MSG_STAT)  ||
            (event->data[0] == ISUP_MSG_LCONG))
        {
            return MAP_MSG_QUEUE;
        }

        cic = ((event->data[3]) & 0x00FF);
        cic |= ((event->data[4] << 8) & 0xFF00);
    }
    else if (event->src == ISUP_SRC_APP)
    {
        #if defined(ANSI)
          cic = ((event->data[9]) & 0x00FF);
          cic |= ((event->data[10] << 8) & 0xFF00);
        #else
          cic = ((event->data[6]) & 0x00FF);
          cic |= ((event->data[7] << 8) & 0xFF00);
        #endif
    }
    else if (event->src == ITS_GCS_EVENT_TO_NETWORK)
    {
        if (hdr->type == ITS_TCAP)
        {
          cic = hdr->context.dialogue_id;
        }
    }
    else if (event->src == ITS_TCAP_SRC)
    {
       cic = hdr->context.dialogue_id;
    }
    else
    {
        return ITS_NO_SRC;
    }

    if (cic % 2)
    {
        return MAP_MSG_QUEUE;
    }
    else
    {
        return ITS_NO_SRC;
    }
}

MULAPP_DLLAPI ITS_USHORT 
RouteEvenToApp(ITS_HDR* hdr, ITS_EVENT* event)
{
    int          offset = 0;
    ITS_USHORT   cic = 0;

    printf("Inside RouteEvenToApp........\n");

    if (event->src == ITS_ISUP_SRC)
    {
        if ((event->data[0] == ISUP_MSG_STAT)  ||
            (event->data[0] == ISUP_MSG_LCONG))
        {
            return MAP_MSG_QUEUE;
        }

        cic = ((event->data[3]) & 0x00FF);
        cic |= ((event->data[4] << 8) & 0xFF00);
    }
    else if (event->src == ISUP_SRC_APP)
    {
        #if defined(ANSI)
          cic = ((event->data[9]) & 0x00FF);
          cic |= ((event->data[10] << 8) & 0xFF00);
        #else
          cic = ((event->data[6]) & 0x00FF);
          cic |= ((event->data[7] << 8) & 0xFF00);
        #endif
    }
    else if (event->src == ITS_GCS_EVENT_TO_NETWORK)
    {
        if (hdr->type == ITS_TCAP)
        {
          cic = hdr->context.dialogue_id;
        }
    }
    else if (event->src == ITS_TCAP_SRC)
    {
       cic = hdr->context.dialogue_id;
    }
    else
    {
        return ITS_NO_SRC;
    }

    if (cic % 2 == 0)
    {
        return MAP_MSG_QUEUE;
    }
    else
    {
        return ITS_NO_SRC;
    }
}

MULAPP_DLLAPI void
MTP3ManagementCallback(ITS_POINTER object,
                       ITS_POINTER userData,
                       ITS_POINTER callData)
{
}

MessageHandler* msgHandler = NULL;
MAB_DbcServer* dbcServ = NULL;
MsgHandlerClient* isupHandler = NULL;
MsgHandlerClient* tcapHandler = NULL;
MsgHandlerClient* mtp3Handler = NULL;
ITS_INT isRouter = 0;

MULAPP_DLLAPI void
AppPreFunc()
{
    static its::ResourceManager res(APPL_GetConfigFileName());
    MabWorkItemPool = new its::WorkItemPool(MAB_WORKITEM_QUEUE,
                                        MAB_NUM_OF_THREADS, 0);
    msgHandler = new MessageHandler;

    MabWorkItemPool->AddWorkItem(msgHandler);

    std::string dbcName = "MulAppBinding";
    dbcServ = MAB_DbcServer::GetDBCServer(dbcName);
    std::string section = "";
    std::string hold = "";

    if (res.GetKeyValueOf(section, "AppStart", hold) == ITS_SUCCESS)
    {
        if (hold == "MTP3")
        {
            isRouter = 1;
        }
    }

    if (!isRouter)
    {
        isupHandler = new IsupMsgHandler;
        tcapHandler = new TcapMsgHandler;
        msgHandler->SetIsupMsgHandler(isupHandler);
        msgHandler->SetTcapMsgHandler(tcapHandler);
    }
    else
    {
        mtp3Handler = new Mtp3MsgHandler;
        msgHandler->SetMtp3MsgHandler(mtp3Handler);
        MTP3_EnableUserPart(MTP3_SIO_ISUP, ITS_MAB_SRC);
    }
}

MULAPP_DLLAPI void
AppPostFunc()
{
    delete msgHandler;
    delete MabWorkItemPool;
    delete dbcServ;

    if (tcapHandler)
    {
        delete tcapHandler;
    }

    if (isupHandler)
    {
        delete isupHandler;
    }

    if (mtp3Handler)
    {
        delete mtp3Handler;
    }
}

MULAPP_DLLAPI int 
SL_PostNextEvent(TPOOL_THREAD *thr, ITS_EVENT *event)
{
    its::Event* ev = (its::Event*)event;
    ITS_EVENT* evt = &ev->GetEvent();
    if ((evt->len > 5) && (evt->data[4] == REGISTER_MSG))
    {
        (ClientHandler::GetClientHandler())->Register(thr, evt);
    }
    else if ((evt->len > 5) && (evt->data[4] == DEREGISTER_MSG))
    {
        (ClientHandler::GetClientHandler())->DeRegister(thr, evt);
    }
    else
    {
        printf("Message received from client\n");

        printf("SL_PostNextEvent : Message from client event len:%d\n",evt->len);
        for(int i=0;i<evt->len;i++)
        {
            if ((i + 1) % 16 == 0) printf("\n");
            printf("%02x ",evt->data[i]);
        }
        printf("\n");

        TRANSPORT_PutEvent(MAP_MSG_QUEUE, evt);
    }
    return ITS_SUCCESS;
}

MULAPP_DLLAPI int 
SL_NextEventFailed(TPOOL_THREAD *thr, int pReturn)
{
    return (!ITS_SUCCESS);
}

MULAPP_DLLAPI void
SL_PostTerminate(TPOOL_THREAD *thr)
{
    printf("\n\n#############  Post Terminate Called ######\n\n");
    (ClientHandler::GetClientHandler())->CleanUP(thr);
}

}

