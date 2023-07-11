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
 * ID: $Id: ClientInterface.h,v 1.4 2005/07/05 11:30:55 mmanikandan Exp $
 *
 * LOG: $Log: ClientInterface.h,v $
 * LOG: Revision 1.4  2005/07/05 11:30:55  mmanikandan
 * LOG: Changes for ISUP Redundancy.
 * LOG:
 * LOG: Revision 1.3  2005/06/02 13:43:35  ssingh
 * LOG: Modified MAP_MSG_QUEUE value to ITS_MAB_SRC
 * LOG:
 * LOG: Revision 1.2  2005/05/30 11:05:10  mmanikandan
 * LOG: Initial Commit for Redundancy.
 * LOG:
 * LOG: Revision 1.1  2005/05/25 10:13:59  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/

#ifndef _CLIENT_INTERFACE_H
#define _CLIENT_INTERFACE_H


#include <its++.h>
#include <engine++.h>
#include <list>
#include <map>
#include <mab_cmn.h>

#define MAP_MSG_QUEUE 65506

typedef struct __clientRInfo
{
    ITS_UINT clientID;
    ROUTING_CRITERIA     routing_criteria;
    union
    {
        MABCL_TCAP    tcap;
        MABCL_ISUP    isup;
    }
    u;
}ClientRoutingInfo;


class ClientHandler
{
public:
    typedef std::map<ITS_UINT, ITS_UINT> ClientIDMap;

    static ClientHandler* GetClientHandler();
    ~ClientHandler();
    int IsClientAllowed (ClientRoutingInfo* msg);
    int Register(TPOOL_THREAD *thr, ITS_EVENT *evt);
    int DeRegister(TPOOL_THREAD *thr, ITS_EVENT *evt);
    int FindBestTCAPClient(MABCL_TCAP* tc);
    int FindBestISUPClient(MABCL_ISUP* ic);
    int FindBestMTP3Client(MABCL_ISUP* ic);
    int SendMsg(MABCL_MESSAGE* msg);

    int CleanUP(TPOOL_THREAD *thr);
private:
    ClientHandler();

    its::Mutex* rinfoMutex_;
    std::list<ClientRoutingInfo*> routInfo_;

    ClientIDMap clIdMap_;
    its::Mutex* cidmapMutex_;

    static ClientHandler* s_clientHandler;
};

#endif

