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
 * ID: $Id: MsgHandlerClient.h,v 1.1 2005/07/05 11:30:55 mmanikandan Exp $
 *
 * LOG: $Log: MsgHandlerClient.h,v $
 * LOG: Revision 1.1  2005/07/05 11:30:55  mmanikandan
 * LOG: Changes for ISUP Redundancy.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ifndef _MUL_APP_MSG_HANDLER_CLIENT_H_
#define _MUL_APP_MSG_HANDLER_CLIENT_H_

#include <ClientInterface.h>

#if defined(CCITT)
#define SL_HANDLE ISS7_CCITT_Stack
#elif defined(ANSI)
#define SL_HANDLE ISS7_ANSI_Stack
#endif

class MsgHandlerClient
{
public:
    virtual ~MsgHandlerClient() {};
    virtual int ProcessAppMsg(MABCL_MESSAGE* msg) = 0;
    virtual int ProcessStackMsg(its::ITS_Event* evt) = 0;
    virtual int ProcessGcsMsg(its::ITS_Event* evt) { return ITS_SUCCESS; }
};

#endif

