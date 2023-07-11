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
 * ID: $Id: ids_clientinterface.h,v 3.7 2010/09/22 05:23:49 nvijikumar Exp $
 *
 * LOG: $Log: ids_clientinterface.h,v $
 * LOG: Revision 3.7  2010/09/22 05:23:49  nvijikumar
 * LOG: GlobalUniqueAddr based routing/distribution support
 * LOG:
 * LOG: Revision 3.6  2009/08/24 11:43:15  rajeshak
 * LOG: Fix for Issue 2317(ACTIVE COLD REDUNDANCY::IDC not able to send
 * LOG: messages to ACTIVE server)
 * LOG:
 * LOG: Revision 3.5  2009/02/19 05:34:57  nvijikumar
 * LOG: New API exposed to ClientHandler for writing an event.
 * LOG:
 * LOG: Revision 3.4  2009/01/04 06:36:06  nvijikumar
 * LOG: Platform transport replaced with new TCP transport to handle IDC traffic
 * LOG: To limit number of threads with multiple connections
 * LOG:
 * LOG: Revision 3.3  2008/11/06 06:55:44  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: 3.1.1 release feature
 * LOG: Description: UDP Transport support between IDS and IDC
 * LOG:
 * LOG: Revision 3.2  2008/10/31 05:32:03  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID: none
 * LOG: Description: 1. Introducing additional TQs and Threads for better
 * LOG:                 Performance on PP50 and initial stack tunning
 * LOG:              2. Unwanted code cleanup
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.5  2008/03/27 11:21:05  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.3.8.1  2007/04/04 06:10:31  nvijikumar
 * LOG: Validate IDC register as per appId and appIdType.
 * LOG:
 * LOG: Revision 2.3  2006/11/07 11:51:37  kamakshilk
 * LOG: Added ValidateAppId method
 * LOG:
 * LOG: Revision 2.2  2006/10/26 04:39:09  kamakshilk
 * LOG: ReleaseClientHandler() method added
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:48:31  adutta
 * LOG: First cut
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: ids_clientinterface.h,v 3.7 2010/09/22 05:23:49 nvijikumar Exp $"

#ifndef _CLIENT_INTERFACE_H
#define _CLIENT_INTERFACE_H


#include <its++.h>
#include <engine++.h>

#include <ids_common.h>
#include <ids_idcManager.h>

/*.Interface: ClientHandler  
 *****************************************************************************
 *  Interface:
 *      ClientHandler Class
 *      
 *  Purpose:
 *      Implement the client handler Functionality
 *****************************************************************************/
class ClientHandler: public IdcReadWriteUtils
{
public:

    ~ClientHandler();

    static ClientHandler* GetClientHandler();

    ITS_INT IsClientAllowed (IDS_MESSAGE* msg);
    ITS_INT Register(ITS_INT sockId, ITS_EVENT *evt);
    ITS_INT RegisterUdp(TPOOL_THREAD *thr, ITS_EVENT *evt);

    ITS_INT DeRegister(ITS_INT sockId, ITS_EVENT *evt);
    ITS_INT DeRegisterUdp(TPOOL_THREAD *thr, ITS_EVENT *evt);

    ITS_INT ProcessGlobalUniqAddrMsg(ITS_EVENT *evt);

    ClientList* FindBestClient(ITS_UINT appId, ITS_INT* count);
    ITS_INT SendMsg(IDS_MESSAGE* msg);

    ITS_INT CleanUP(int sockId);

    ITS_INT SendServerUpInd();

    ITS_INT SendToIDC(IDS_TRANS_INFO* inst, IDS_MESSAGE* msg);

    IDS_CONNECTION_TYPE GetConnectionType();

    void SetServerPort(ITS_UINT p)
    {
        servPort = p; 
    }

    ITS_UINT GetServerPort()
    {
        return (servPort); 
    }

    void SetServerIPAddr(ITS_CHAR* addr)
    {
        servAddr = strdup(addr);
    }

    ITS_CHAR* GetServerIPAddr()
    {
        return (servAddr);
    }

    void SetTransType(IDS_TRANS_TYPE transType)
    {
        tType = transType;
    }

    IDS_TRANS_TYPE GetTransType()
    {
        return tType;
    }

    void SetServerUdpPort(ITS_UINT p)
    {
        servUdpPort = p;
    }

    ITS_HANDLE GetUdpHandle()
    { 
        return udpHandle;
    }
    void SetUdpHandle(ITS_HANDLE h)
    {
        udpHandle = h;
    }

    static void ReleaseClientHandler();

    ITS_INT ValidateAppId(ITS_UINT& appId, ITS_UINT& appIdType);

private:
    ClientHandler();

    static ClientHandler* s_clientHandler;
    ITS_CHAR* servAddr;
    ITS_UINT servPort;
    ITS_UINT servUdpPort;
    IDS_TRANS_TYPE tType;
    ITS_HANDLE udpHandle;
};

#endif

