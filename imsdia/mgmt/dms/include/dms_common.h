/****************************************************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: dms_common.h,v 1.1.60.1 2013/02/27 08:49:07 jvikram Exp $
 *
 * LOG: $Log: dms_common.h,v $
 * LOG: Revision 1.1.60.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 1.1  2009/03/02 04:39:44  nvijikumar
 * LOG: Initial draft for MML API Support
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: dms_common.h,v 1.1.60.1 2013/02/27 08:49:07 jvikram Exp $"

#ifndef _DMS_COMMON_H
#define _DMS_COMMON_H 

#include <its.h>
#include <its_types.h>
#include <dm_msgs.h>

//#define MAX_ROUTE_SCHEME_LENGTH   50

class DmsMsgHandler : public DmCodecUtils
{
public:
    DmsMsgHandler(){};
    ~DmsMsgHandler(){};
    static void EncodeDmMsgStats(std::string &str, DM_MSG_STATS *mStats);
    static ITS_INT ProcessMsg(ITS_EVENT *ev);
    static ITS_INT Encode(DM_MSG *msg, ITS_EVENT *ev);
    static ITS_INT Decode(DM_MSG *msg, ITS_EVENT *ev);
};

#endif

