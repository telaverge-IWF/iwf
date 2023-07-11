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
 * ID: $Id: MulAppMsgHandler.cpp,v 1.6 2005/07/05 11:28:05 mmanikandan Exp $
 *
 * LOG: $Log: MulAppMsgHandler.cpp,v $
 * LOG: Revision 1.6  2005/07/05 11:28:05  mmanikandan
 * LOG: Changes for ISUP Distributed.
 * LOG:
 * LOG: Revision 1.5  2005/06/02 13:38:20  adutta
 * LOG: Changes done for redundancy.
 * LOG:
 * LOG: Revision 1.4  2005/05/31 10:44:08  adutta
 * LOG: Fix for TCAP cdp/clp len.
 * LOG:
 * LOG: Revision 1.3  2005/05/30 11:02:59  mmanikandan
 * LOG: Initial Commit for Redundancy.
 * LOG:
 * LOG: Revision 1.2  2005/05/25 14:13:37  mmanikandan
 * LOG: Changes for CCITT.
 * LOG:
 * LOG: Revision 1.1  2005/05/25 10:13:59  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <math.h>
#include <MulAppMsgHandler.h>
#include <engine++.h>
#include <tcap++.h>
#include <vframe.h>
#include <its_dsm.h>




MessageHandler::MessageHandler()
{
    msgQ_ = new its::TaskQueueTransport (
                  "MSG Queue", MAP_MSG_QUEUE, ITS_TRANSPORT_TQUEUE);
    ITS_THROW_ASSERT (msgQ_ != NULL);

    cHandler_ = ClientHandler::GetClientHandler();

    isupMsgHandler_ = NULL;
    tcapMsgHandler_ = NULL;
    sccpMsgHandler_ = NULL;
    mtp3MsgHandler_ = NULL;
}

MessageHandler::~MessageHandler()
{
    delete msgQ_;
    cHandler_ = NULL;
}

void MessageHandler::Execute()
{
    int ret = ITS_SUCCESS;

    while (1)
    {
        its::Event evt;
        ret = msgQ_->GetNextEvent(evt);
        
        if (ret != ITS_SUCCESS)
        {
            continue;
        }

        printf("Received Event\n");

        ITS_EVENT* event = &evt.GetEvent();

        if (evt.GetSource() == MABCL_APP_SRC ||
            evt.GetSource() == MABCL_TCAP_SRC ||
            evt.GetSource() == MABCL_ISUP_SRC ||
            evt.GetSource() == MABCL_MGMT_SRC)
        {
        printf("Message from client event len:%d\n",event->len);
        for(int i=0;i<event->len;i++)
        {
            if ((i + 1) % 16 == 0) printf("\n");
            printf("%02x ",event->data[i]);
        }
        printf("\n");
        }
        
        switch (evt.GetSource())
        {
        case ITS_TCAP_SRC:
            if (tcapMsgHandler_)
            {
                printf("Process TCAP Message from Stack\n");
                ret = tcapMsgHandler_->ProcessStackMsg(&evt);
            }
            break;
        case ITS_ISUP_SRC:
            printf("~~~~~~~~~~~~~~~~~~ Got event from stack ~~~~~~~~\n");
            if (isupMsgHandler_)
            {
            printf("~~~~~~~~~~~~~~~~~~ Got event from stack1 ~~~~~~~~\n");
                ret = isupMsgHandler_->ProcessStackMsg(&evt);
            }
            break;
        case ITS_MTP3_SRC:
            if (mtp3MsgHandler_)
            {
                printf("Process MTP3 Message from Stack\n");
                ret = mtp3MsgHandler_->ProcessStackMsg(&evt);
            }
            break;
        case ITS_SCCP_SRC:
            if (sccpMsgHandler_)
            {
                ret = sccpMsgHandler_->ProcessStackMsg(&evt);
            }
            break;
        case MABCL_APP_SRC:
        case MABCL_TCAP_SRC:
        case MABCL_ISUP_SRC:
        case MABCL_MTP3_SRC:
        case MABCL_MGMT_SRC:
            ProcessAppMsg (&evt);
            break;
        case ITS_MAB_SRC:
        {
            if (tcapMsgHandler_)
            {
                ret = tcapMsgHandler_->ProcessGcsMsg(&evt);
            }
            
            break;
        }
        }
    }
}

int MessageHandler::ProcessAppMsg(its::ITS_Event* evt)
{
    MABCL_MESSAGE msg;
    ITS_INT ret = ITS_SUCCESS;

    MABCL_Decode(&msg, &evt->GetEvent());

    switch(msg.msg_type)
    {
    case ISUP_MSG:
    case ISUP_RSV_CIC_MSG:
    case ISUP_URSV_CIC_ACK_MSG:
        if (isupMsgHandler_)
        {
            ret = isupMsgHandler_->ProcessAppMsg(&msg);
        }
        break;
    case TCAP_MSG:
        if (tcapMsgHandler_)
        {
            ret = tcapMsgHandler_->ProcessAppMsg(&msg);
        }
        break;
    case SCCP_MSG:
        if (sccpMsgHandler_)
        {
            ret = sccpMsgHandler_->ProcessAppMsg(&msg);
        }
        break;
    case MTP3_MSG:
        if (mtp3MsgHandler_)
        {
            ret = mtp3MsgHandler_->ProcessAppMsg(&msg);
        }
        break;
    case MANAGEMENT_MSG:
        break;
    default:
        ret = cHandler_->SendMsg(&msg);
        break;
    }

    return ret;
}

void 
MessageHandler::SetMtp3MsgHandler(MsgHandlerClient* mtp3MsgHandler)
{
    mtp3MsgHandler_ = mtp3MsgHandler;
}

void 
MessageHandler::SetSccpMsgHandler(MsgHandlerClient* sccpMsgHandler)
{
    sccpMsgHandler_ = sccpMsgHandler;
}

void 
MessageHandler::SetTcapMsgHandler(MsgHandlerClient* tcapMsgHandler)
{
    tcapMsgHandler_ = tcapMsgHandler;
}

void 
MessageHandler::SetIsupMsgHandler(MsgHandlerClient* isupMsgHandler)
{
    isupMsgHandler_ = isupMsgHandler;
}

MsgHandlerClient* 
MessageHandler::GetMtp3MsgHandler()
{
    return mtp3MsgHandler_;
}

MsgHandlerClient* 
MessageHandler::GetTcapMsgHandler()
{
    return tcapMsgHandler_;
}

MsgHandlerClient* 
MessageHandler::GetSccpMsgHandler()
{
    return sccpMsgHandler_;
}

MsgHandlerClient* 
MessageHandler::GetIsupMsgHandler()
{
    return isupMsgHandler_;
}




