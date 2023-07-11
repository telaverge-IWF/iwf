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
 * ID: $Id: ids_msghandler.h,v 3.13 2010/08/19 11:23:06 nvijikumar Exp $ 
 *
 * LOG: $Log: ids_msghandler.h,v $
 * LOG: Revision 3.13  2010/08/19 11:23:06  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 3.12  2009/08/28 12:28:45  rajeshak
 * LOG: Fix for Issue 2330 (IDS sends Heartbeat to IDC after double the time
 * LOG: configured in XML)
 * LOG: Changed the Previous heartbeat Implementation
 * LOG:
 * LOG: Revision 3.11  2009/08/25 10:16:32  rajeshak
 * LOG: Fix for Issue:2322 (IDS unable to send Heartbeat Message to DMC client)
 * LOG: Passing TrHandle properly.
 * LOG:
 * LOG: Revision 3.10  2009/08/24 11:43:15  rajeshak
 * LOG: Fix for Issue 2317(ACTIVE COLD REDUNDANCY::IDC not able to send
 * LOG: messages to ACTIVE server)
 * LOG:
 * LOG: Revision 3.9  2009/07/13 05:57:27  rajeshak
 * LOG: Reverting back session table changes.
 * LOG:
 * LOG: Revision 3.8  2009/06/29 14:35:43  rajeshak
 * LOG: Moved GetSessionId Function to DiaUtils.
 * LOG:
 * LOG: Revision 3.7  2009/04/09 12:37:19  nvijikumar
 * LOG: HeartBeat support for MML API Interface
 * LOG:
 * LOG: Revision 3.6  2009/03/07 09:40:32  nvijikumar
 * LOG: Fix for Issue Id 1732
 * LOG:
 * LOG: Revision 3.5  2009/02/12 04:08:15  nvijikumar
 * LOG: Changed signature for ProcessDiaStackMsg and ProcessAppMsg
 * LOG:  - Changed C++ ITS Event to C EVENT
 * LOG:
 * LOG: Revision 3.4  2008/12/13 01:40:13  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.3  2008/11/06 06:59:56  nvijikumar
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
 * LOG: Revision 2.5  2006/12/12 14:09:44  kamakshilk
 * LOG: To sent peer based messages to all clients
 * LOG:
 * LOG: Revision 2.4  2006/11/17 05:53:51  kamakshilk
 * LOG: SendNotify signature changed
 * LOG:
 * LOG: Revision 2.3  2006/11/14 07:04:05  kamakshilk
 * LOG: New Architecture. No database maintained at IDS
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:16:31  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.7  2006/08/08 04:42:52  kamakshilk
 * LOG: Fix for Bug Ids 4111, 4112 and 4118
 * LOG:
 * LOG: Revision 1.6  2006/06/14 09:23:33  kamakshilk
 * LOG: Enhancements for sending Application Id to the client.
 * LOG:
 * LOG: Revision 1.5  2006/05/23 06:18:59  adutta
 * LOG: Clearing session record on STA/Abort
 * LOG:
 * LOG: Revision 1.4  2006/04/17 10:28:06  adutta
 * LOG: Heartbeat timer/re-try from xml
 * LOG:
 * LOG: Revision 1.3  2006/04/06 07:52:28  adutta
 * LOG: Replacement of Ses-Id/Idx and related changes
 * LOG:
 * LOG: Revision 1.2  2006/03/14 06:41:05  adutta
 * LOG: Incorporated dframe changes
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:48:31  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/
#ident "$Id: ids_msghandler.h,v 3.13 2010/08/19 11:23:06 nvijikumar Exp $"

#ifndef _IDS_CLIENT_IFACE_H_
#define _IDS_CLIENT_IFACE_H_

#include <map>
#include <ids_clientinterface.h>

#include <dia_cmn.h>
#include <its_dia_config.h>
#include <itsdiameter.h>
#include <dia_err.h>

#include <diameter/base/NONPROXYABLEERROR.h>
#include <diameter/base/PROXYABLEERROR.h>

extern IDS_ROUTING_SCHEME routeScheme;

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
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi      08-08-06   Bug Ids 4111,    ClearSessionDB signature changed 
 *                               4112,4118     to accept 8 byte keys. 
 *   Kamakshi      14-11-06   Enhancement      ClearSessionDB, BuildSessionAVP, 
 *                                             methods removed.
 *                                             New methods SendErrToPeer,
 *                                             SendNotifyToApp added.
 *
 *****************************************************************************/
class MsgHandler: public its::WorkItem
{
public:
    MsgHandler();
    ~MsgHandler();

    virtual void Execute ();

    void ProcessRedundancyMsg(ITS_EVENT* evt);
    ITS_INT ProcessAppMsg(ITS_EVENT* evt);
    ITS_INT ProcessDiaStackMsg(ITS_EVENT* evt);

    void SendErrToPeer(diameter::BaseCommand *inMsg, ITS_UINT rCode);
    void SendNotifyToApp(ITS_OCTET* evtData, IDS_APP_IND_TYPE indType, 
                           std::string &sessStr);
    void SendPeerBasedMsgToApp(diameter::BaseCommand *rxCmd, ITS_OCTET *evtData);

    int GetQCount();

protected:
    ITS_INT GetSessionString(ITS_OCTET* data, std::string &str);

private:
    IDS_REGISTER* GetRouteInfo(const ITS_UINT appId);

private:
    ClientHandler* cHandler_;
    its::TaskQueueTransport* msgQ_;
    its::Mutex* didcidMutex_;

    ITS_BOOLEAN keepGoing;
};

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
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *
 *****************************************************************************/
class AppToStackMsgHandler: public its::WorkItem
{
public:
    AppToStackMsgHandler();
    ~AppToStackMsgHandler();

    virtual void Execute ();

    int GetQCount();

private:
    its::TaskQueueTransport* msgQ_;

    ITS_BOOLEAN keepGoing;
};

/*
 *****************************************************************************
 *  Interface:
 *      UdpHeartBeatHandler
 *
 *  Purpose:
 *      Exchange heart beat messages with distributed clients.
 *
 *  Usage:
 *****************************************************************************/
class UdpHeartBeatTable
{
public:
    UdpHeartBeatTable();
    ~UdpHeartBeatTable();
    void InsertEntry(ITS_UINT clientId);
    void RemoveEntry(ITS_UINT clientId);
    UDP_HB_INFO* RetrieveEntry(ITS_UINT  key);
    UDP_HB_INFO** GetAllValues(ITS_UINT * key);
private:
    typedef std::map<ITS_UINT, UDP_HB_INFO *> UdpHbTable;
    UdpHbTable UdpHbMap;
    its::Mutex* hdMutex_;
};

/*
 *****************************************************************************
 *  Interface:
 *      HeartBeatHandler
 *
 *  Purpose:
 *      Exchange heart beat messages with distributed clients.
 *
 *  Usage:
 *****************************************************************************/
class HeartBeatHandler: public its::WorkItem, public IdcReadWriteUtils
{
public:
    ~HeartBeatHandler();

    static HeartBeatHandler* GetHeartBeatHandler();
    void InsertHandle(ITS_UINT inst, ITS_HANDLE hdl);
    void RemoveHandle(ITS_UINT inst);
    void SendHeartBeat(ITS_UINT inst);
    void SendHeartBeatToDest(ITS_UINT clientId);
    void Disconnect(ITS_HANDLE hdl, ITS_UINT inst);
    UdpHeartBeatTable& GetUdpTable()
    {
        return udpHb;
    } 
    void SetDmsSockInfo(ITS_USHORT trId, ITS_HANDLE sockHandle)
    {
        dmsSock.handle     = (TCP_SOCK_INFO *)malloc(sizeof(TCP_SOCK_INFO));
        TCP_SOCK_INFO *hdl = (TCP_SOCK_INFO *)dmsSock.handle;
        hdl->socket        = SOCKTRAN_SOURCE(sockHandle)->socket;
        hdl->trId          = trId;
        //hdl->lastUpdated   = 0;
        hdl->tries         = 0;
        hdl->count         = 0;
    }
    void UnsetDmsSockInfo()
    {
        if(dmsSock.handle != NULL)
        {
            free(dmsSock.handle);
            dmsSock.handle = NULL;
            dmsSock.tries  = 0;
        }
    }
    void ResetDmsSockLastUpdate()
    {
        if(dmsSock.handle != NULL)
        {
            TCP_SOCK_INFO *hdl = (TCP_SOCK_INFO *)dmsSock.handle;
            hdl->count = 0;
            hdl->tries = 0;
        }

        dmsSock.tries  = 0;
    }
    void Stop()
    {
        keepGoing = ITS_FALSE;
    }

    virtual void Execute();
    typedef std::map<ITS_UINT, IDS_SOCK_INFO*> HandleMap;
private:
    HeartBeatHandler();
    ClientHandler* cHandler_;
    static HeartBeatHandler* _hbHandler;
    HandleMap hdMap_;
    its::Mutex* hdMutex_;
    ITS_BOOLEAN keepGoing;

    ITS_UINT hbInterval;
    ITS_UINT hbRetry;
    UdpHeartBeatTable udpHb;
    IDS_SOCK_INFO dmsSock;
};

#endif

