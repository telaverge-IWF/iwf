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
 * ID: $Id: MulAppMtp3MsgHandler.h,v 1.1 2005/07/05 11:30:55 mmanikandan Exp $
 *
 * LOG: $Log: MulAppMtp3MsgHandler.h,v $
 * LOG: Revision 1.1  2005/07/05 11:30:55  mmanikandan
 * LOG: Changes for ISUP Redundancy.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ifndef _MTP3_MSG_HANDLER_CLIENT_H_
#define _MTP3_MSG_HANDLER_CLIENT_H_

#include <MsgHandlerClient.h>

class Mtp3MsgHandler : public MsgHandlerClient
{
public:
    Mtp3MsgHandler();
    ~Mtp3MsgHandler();

    int ProcessAppMsg(MABCL_MESSAGE* msg);
    int ProcessStackMsg(its::ITS_Event* evt);

private:

    ClientHandler* cHandler_;
};

#endif

