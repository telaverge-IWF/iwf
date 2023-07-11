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
 * ID: $Id: MulAppMsgHandler.h,v 1.3 2005/07/05 11:30:55 mmanikandan Exp $
 *
 * LOG: $Log: MulAppMsgHandler.h,v $
 * LOG: Revision 1.3  2005/07/05 11:30:55  mmanikandan
 * LOG: Changes for ISUP Redundancy.
 * LOG:
 * LOG: Revision 1.2  2005/05/30 11:05:10  mmanikandan
 * LOG: Initial Commit for Redundancy.
 * LOG:
 * LOG: Revision 1.1  2005/05/25 10:13:59  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/

#ifndef _MUL_APP_MSG_HANDLER_H_
#define _MUL_APP_MSG_HANDLER_H_

#include <iostream>
#include <ClientInterface.h>

#include <MsgHandlerClient.h>

/*
 *****************************************************************************
 *  Interface:
 *      MessageHandler
 *
 *  Purpose:
 *
 *
 *  Usage:
 *      
 *
 *****************************************************************************/

class MessageHandler: public its::WorkItem
{
public:
    MessageHandler();
    ~MessageHandler();

    virtual void Execute ();

    int ProcessAppMsg(its::ITS_Event* evt);

    void SetMtp3MsgHandler(MsgHandlerClient* mtp3MsgHandler);
    void SetSccpMsgHandler(MsgHandlerClient* sccpMsgHandler);
    void SetTcapMsgHandler(MsgHandlerClient* tcapMsgHandler);
    void SetIsupMsgHandler(MsgHandlerClient* isupMsgHandler);

    MsgHandlerClient* GetMtp3MsgHandler();
    MsgHandlerClient* GetTcapMsgHandler();
    MsgHandlerClient* GetSccpMsgHandler();
    MsgHandlerClient* GetIsupMsgHandler();

private:

    ClientHandler* cHandler_;
    its::TaskQueueTransport* msgQ_;
    MsgHandlerClient* mtp3MsgHandler_;
    MsgHandlerClient* sccpMsgHandler_;
    MsgHandlerClient* tcapMsgHandler_;
    MsgHandlerClient* isupMsgHandler_;
};

#endif

