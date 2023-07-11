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
 * ID: $Id: ids_heartbeat.cpp,v 3.23 2010/08/19 11:23:06 nvijikumar Exp $
 *
 * LOG: $Log: ids_heartbeat.cpp,v $
 * LOG: Revision 3.23  2010/08/19 11:23:06  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 3.22  2009/11/12 12:11:20  sureshj
 * LOG: IDS-IDC HeartBeat unneccessary log commented.
 * LOG: Motorola ticket 2265.
 * LOG:
 * LOG: Revision 3.21  2009/09/09 07:23:50  rajeshak
 * LOG: Added HMI Reset code.
 * LOG:
 * LOG: Revision 3.20  2009/09/08 09:57:43  rajeshak
 * LOG: Fix for Issue 2350(IDC Heartbeat getting delayed with HMI timer values)
 * LOG: Calling sleep instead of HmiSleep.
 * LOG:
 * LOG: Revision 3.19  2009/08/28 12:28:45  rajeshak
 * LOG: Fix for Issue 2330 (IDS sends Heartbeat to IDC after double the time
 * LOG: configured in XML)
 * LOG: Changed the Previous heartbeat Implementation
 * LOG:
 * LOG: Revision 3.18  2009/08/25 10:16:32  rajeshak
 * LOG: Fix for Issue:2322 (IDS unable to send Heartbeat Message to DMC client)
 * LOG: Passing TrHandle properly.
 * LOG:
 * LOG: Revision 3.17  2009/06/29 14:38:19  rajeshak
 * LOG: HMI Changes to improve the performance.
 * LOG:
 * LOG: Revision 3.16  2009/06/18 11:42:58  sureshj
 * LOG: Fix for helpdesk issue Id 2172 IDS caught core handler caught signal 11.
 * LOG:
 * LOG: Revision 3.15  2009/05/08 11:18:39  rajeshak
 * LOG: Changes for MML cmd to set/get Heartbeat interval.
 * LOG:
 * LOG: Revision 3.14  2009/04/10 07:13:51  sureshj
 * LOG:  sleep in heartbeat thread removed.
 * LOG:
 * LOG: Revision 3.13  2009/04/10 07:12:28  sureshj
 * LOG: Compilation flag HMI_ENABLE removed added dynamic configuration.
 * LOG:
 * LOG: Revision 3.12  2009/04/09 12:39:40  nvijikumar
 * LOG: HeartBeat support for MML API Interface
 * LOG:
 * LOG: Revision 3.11  2009/04/07 14:10:17  sureshj
 * LOG: HMI monitoring enabled for heartbeat thread .
 * LOG:
 * LOG: Revision 3.10  2009/03/19 08:14:38  nvijikumar
 * LOG: Reverting back HMI changes (App hangs and drop in TPS)
 * LOG: HMI changes are planed to provide after 4.0
 * LOG:
 * LOG: Revision 3.9  2009/03/16 11:51:46  sureshj
 * LOG: FeatureId: HMI enhancement for monitoring raw threads.
 * LOG: Description: Diameter threads added to HMI monitoring for hung threads.
 * LOG:
 * LOG: Revision 3.8  2009/03/07 08:46:06  nvijikumar
 * LOG: Fix for Issue Id: 1732 (Failed to send heartbeat message)
 * LOG:
 * LOG: Revision 3.7  2009/03/03 11:10:47  rajeshak
 * LOG: Klockwork reported issue fix
 * LOG:
 * LOG: Revision 3.6  2009/01/04 09:33:52  nvijikumar
 * LOG: disconnect based on socket lastUpdate
 * LOG:
 * LOG: Revision 3.5  2009/01/04 06:27:03  nvijikumar
 * LOG: Platform transport replaced with new TCP transport to handle IDC traffic
 * LOG: To limit number of threads with multiple connectio
 * LOG:
 * LOG: Revision 3.4  2008/11/18 04:40:16  nvijikumar
 * LOG: IssueID:1263
 * LOG: FeatureID:UDP transport support
 * LOG: Description: Failed to register/de-register over UDP - Fix
 * LOG:
 * LOG: Revision 3.3  2008/11/06 07:03:17  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: 3.1.1 release feature
 * LOG: Description: UDP Transport support between IDS and IDC
 * LOG:
 * LOG: Revision 3.2  2008/10/28 12:02:52  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.1.2.1  2008/10/07 07:19:01  nvijikumar
 * LOG: RePlace Timestamps with counts to detect transport failure
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.6  2007/02/19 04:52:48  kamakshilk
 * LOG: hdHandler set to NULL in the destructor
 * LOG:
 * LOG: Revision 2.5  2006/11/14 07:16:44  kamakshilk
 * LOG: Release mutex when no clients found
 * LOG:
 * LOG: Revision 2.4  2006/11/08 06:12:40  kamakshilk
 * LOG: Changes for 64-bit support. ITS_ULONG changed to ITS_UINT
 * LOG:
 * LOG: Revision 2.3  2006/10/31 10:05:32  kamakshilk
 * LOG: IDSCL_Print function added
 * LOG:
 * LOG: Revision 2.2  2006/10/26 05:48:32  kamakshilk
 * LOG: Free all the allocated memory in destructor
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.3  2006/05/30 09:37:51  yranade
 * LOG: Changes to compile with CC compiler on solaris 10.
 * LOG:
 * LOG: Revision 1.2  2006/04/17 10:27:39  adutta
 * LOG: Heartbeat timer/re-try from xml
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:47:51  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/
#ident "$Id: ids_heartbeat.cpp,v 3.23 2010/08/19 11:23:06 nvijikumar Exp $"

#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <engine++.h>

#include <dia_trace.h>
#include <ids_msghandler.h>
#include <dia_defines.h>
#include <dia_utils.h>

#include <dia_config.h>
#include <ids_conndb.h>
#include <ids_routedb.h>

HeartBeatHandler* HeartBeatHandler::_hbHandler = NULL;
extern int SendUdpMsg(ITS_UINT &clientID, ITS_EVENT *evt);
extern ConnectionTable conTable;
extern RouteTable routeTable;


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
HeartBeatHandler::Disconnect(ITS_HANDLE hdl, ITS_UINT sockId)
{   
    DIA_TRACE_ERROR(("HeartBeatHandler: Disconnect"));
#if 0
    if (MUTEX_AcquireMutex(&SOCKTRAN_WMUTEX(hdl)) == ITS_SUCCESS)
    {
        if (SOCKTRAN_IS_VALID(hdl) == ITS_TRUE)
        {
           close (SOCKTRAN_SOURCE(hdl)->socket);
        }
        MUTEX_ReleaseMutex(&SOCKTRAN_WMUTEX(hdl));
    }
#endif 
#if defined(linux) && !defined(USE_SELECT)
    ClientHandler::GetClientHandler()->CleanUP(sockId);
#endif
    close(sockId);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
HeartBeatHandler::SendHeartBeat(ITS_UINT inst)
{
    ITS_EVENT ev;
    ITS_INT i;

    DIA_TRACE_DEBUG(("HeartBeatHandler:SendHeartBeat to " 
                                 " Transport Instance: %d", inst));

    ITS_EVENT_INIT(&ev, ITS_APP_SRC, sizeof(ITS_UINT) + sizeof(ITS_OCTET));

    for (i = 0; i < sizeof(ITS_UINT); i++)
    {
        ev.data[i] = 0xFF;
    }

    ev.data[i] = HEARTBEAT_MSG;

    DIA_TRACE_DEBUG(("\nMessage to client event len:%d\n",ev.len));
    IDSCL_Print(ev.data, ev.len);

#if _IDS_SENDER_THR
    ev.src = inst;
    TRANSPORT_PutEvent(IDS_TCP_SEND_MSG_QUEUE, &ev);
#else
    if(WriteEvent(inst, &ev) != ITS_SUCCESS)
    {
        DIA_TRACE_CRITICAL(("SendHeartBeat:: failed socket <%u>",inst));
    }
    ITS_EVENT_TERM(&ev);
#endif

}

void SendHeartBeatToDms(ITS_USHORT inst)
{
    ITS_EVENT ev;
    ITS_INT i;

    DIA_TRACE_DEBUG(("HeartBeatHandler: SendHeartBeat to DMC instance = %d", inst));

    ITS_EVENT_INIT(&ev, ITS_APP_SRC, sizeof(ITS_UINT) + sizeof(ITS_OCTET));

    for (i = 0; i < sizeof(ITS_UINT); i++)
    {
        ev.data[i] = 0xFF;
    }

    ev.data[0] = HEARTBEAT_MSG;

    TRANSPORT_PutEvent(inst, &ev);

    ITS_EVENT_TERM(&ev);
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
HeartBeatHandler::HeartBeatHandler()
{   
    DIA_TRACE_DEBUG(("HeartBeatHandler: HeartBeatHandler"));

    hdMutex_ = new its::Mutex(0);
    keepGoing = ITS_TRUE;
    cHandler_ = ClientHandler::GetClientHandler();

    DiaConfig *cfg = DiaConfig::GetDiaConfig();

    hbInterval = cfg->GetHeartBeatInterval();
    hbRetry = cfg->GetHeartBeatRetry();

    if (!hbInterval)
    {
        hbInterval = MAX_HB_PERIOD;
        cfg->SetHeartBeatInterval(MAX_HB_PERIOD);
    }

    if (!hbRetry)
    {
        hbRetry = MAX_HB_TRIES;
        cfg->SetHeartBeatRetry(MAX_HB_TRIES);
    }

    DIA_TRACE_DEBUG(("HeartBeatHandler: Heart beat interval %d", hbInterval));
    DIA_TRACE_DEBUG(("HeartBeatRetry: Heart beat retry %d", hbRetry));

    dmsSock.handle = NULL;
    dmsSock.tries  = 0;

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
HeartBeatHandler*
HeartBeatHandler::GetHeartBeatHandler()
{
    //DIA_TRACE_DEBUG(("HeartBeatHandler: GetHeartBeatHandler"));

    if (_hbHandler == NULL)
    {
        _hbHandler = new HeartBeatHandler;
    }
    return (_hbHandler);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
HeartBeatHandler::~HeartBeatHandler()
{
    DIA_TRACE_DEBUG(("HeartBeatHandler: ~HeartBeatHandler"));

    HandleMap::iterator biter = hdMap_.begin();
    HandleMap::iterator eiter = hdMap_.end();
    IDS_SOCK_INFO* info = NULL;

    while (biter != eiter)
    {
        // Get socket handle 
        info = biter->second; 
        // Disconnect 
        Disconnect(info->handle, biter->first);
#if !defined(linux) || defined(USE_SELECT)
        /* Already removed incase of epoll */
        RemoveHandle(biter->first);
#endif
        biter++;
    }
    keepGoing = ITS_FALSE;
    delete hdMutex_;

    hbInterval = 0;
    hbRetry = 0;

    _hbHandler = NULL;
 
    UnsetDmsSockInfo(); 

    DIA_TRACE_DEBUG(("HeartBeatHandler: Exit"));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 *  
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date       Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    11-11-06    Enhancement   Release Mutex when no clients found.
 *
 ****************************************************************************/
void 
HeartBeatHandler::Execute()
{
    ITS_TIME prevTime;
    ITS_TIME currTime;
    IDS_SOCK_INFO* info = NULL;
    SOCKTRAN_Manager *ft = NULL;
    UDP_HB_INFO** cliList;
    UDP_HB_INFO* client;
    ITS_UINT     cliCount ;
    ITS_INT thrID;
    ITSDiaConfig *cfg = &itsDiaConfig;
    DiaConfig *diaCfg = DiaConfig::GetDiaConfig();
    HMIThread_Info* hmiInfo = NULL;
  
    DIA_TRACE_DEBUG(("HeartBeatHandler: Execute"));
    thrID = THREAD_GetCurrentThreadID(); 
    hmiInfo = HMI_AddToMonList(&monList, "HeartBeatHandler", (ITS_THREAD*)thrID);
    while (keepGoing)
    {
        hbInterval = diaCfg->GetHeartBeatInterval();
 
        hbRetry = diaCfg->GetHeartBeatRetry();
 
        // Sleep till HeartBeat period
        //DiaUtils::HmiSleep(hmiInfo, hbInterval);
        /* Putting a sleep of 1 sec */
        TIMERS_Sleep(1);

        if(cfg->IsHMIEnabled())
        {
            HMI_ResetCounter(hmiInfo);
        }

        /* 
         * TCP Connections
         */
        hdMutex_->Acquire();

        HandleMap::iterator biter = hdMap_.begin();
        HandleMap::iterator eiter = hdMap_.end();
        while (biter != eiter)
        {
            // Get socket handle 
            info = biter->second; 
            //ITS_USHORT lastUpdate = 0;
            TCP_SOCK_INFO *tcpSock=NULL;

            if(info !=NULL)
            {
                tcpSock = (TCP_SOCK_INFO *)info->handle;

                if (tcpSock)
                {
                    TCP_SOCK_INCR_COUNTER(tcpSock);

                    if (TCP_SOCK_COUNTER(tcpSock) >= hbInterval)
                    {
                        DIA_TRACE_DEBUG(("TCP Execute: HeartBeat period expired"));
                        TCP_SOCK_RST_COUNTER(tcpSock);
                        TCP_SOCK_INCR_TRIES(tcpSock);

                        if (TCP_SOCK_TRIES(tcpSock) <= hbRetry)
                        {
                            SendHeartBeat(biter->first);
                        }
                        else
                        {
                            // Disconnect 
                            TCP_SOCK_RST_TRIES(tcpSock);
                            Disconnect(info->handle, biter->first);
                        }
                    }
                }
                else
                {
                    // CleanUP
                    DIA_TRACE_CRITICAL(("Invalid socket handler "));
                }

                biter++;
            }
           else
           {
                DIA_TRACE_DEBUG(("Info is NULL!! "));
           }
          
        }
        hdMutex_->Release();
        /*  End TCP Connections */

        /*
         * UDP Connections
         */
        cliCount = 0;
        cliList = GetUdpTable().GetAllValues(&cliCount);
        while (cliCount)
        {
            client = cliList[cliCount - 1];

            client->count += 1; 

            if (client->count >= hbInterval)
            {
                DIA_TRACE_DEBUG(("UDP Execute: HeartBeat period expired"));
                client->count = 0; 
                client->tries += 1;

                if (client->tries <= hbRetry)
                {
		    SendHeartBeatToDest(client->clientId);
                }
                else
                {
                    DIA_TRACE_ERROR(("CleanUP for Client %d\n",
                                             client->clientId));
                    conTable.RemoveEntry(client->clientId);
                    routeTable.RemoveEntry(client->clientId);
                    GetUdpTable().RemoveEntry(client->clientId);
                }
            }

            cliCount--;
        }
        free(cliList);
        cliList = NULL;
        /*  End UDp Connections */
      
        /* DMS HB Handling */
        if (dmsSock.handle != NULL)
        {
            TCP_SOCK_INFO *hdl = (TCP_SOCK_INFO *)dmsSock.handle;

            TCP_SOCK_INCR_COUNTER(hdl);

            if (TCP_SOCK_COUNTER(hdl) >= hbInterval)
            {
                DIA_TRACE_DEBUG(("DMS Execute: HeartBeat period expired"));
                TCP_SOCK_RST_COUNTER(hdl);

                /* for dms-dmc heartbeat we use this tries */
                dmsSock.tries += 1;
                if (dmsSock.tries <= hbRetry)
                {
                    SendHeartBeatToDms(hdl->trId);
                }
                else
                {
                    // Disconnect
                    dmsSock.tries = 0;
                    DIA_TRACE_ERROR(("CleanUP for Socket %d\n",
                                             hdl->socket));
                    close(hdl->socket);
                    UnsetDmsSockInfo(); 
                }
            }
        }
    }
    HMI_RemoveFromMonList(&monList, (ITS_THREAD*)thrID);   
    delete this;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
HeartBeatHandler::InsertHandle(ITS_UINT inst, ITS_HANDLE hdl)
{
    IDS_SOCK_INFO* info = NULL;

    DIA_TRACE_DEBUG(("HeartBeatHandler: InsertHandle"));

    info = (IDS_SOCK_INFO*)calloc(1, sizeof(IDS_SOCK_INFO));
    if (info == NULL)
    {
        throw "Error: memory allocation failed";
    }
  
    info->handle = hdl;

    hdMutex_->Acquire();

    hdMap_.insert(HandleMap::value_type(inst, info));

    DIA_TRACE_DEBUG(("InsertHandle: Socket instance <%d>", inst));

    hdMutex_->Release();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
HeartBeatHandler::RemoveHandle(ITS_UINT inst)
{

    DIA_TRACE_DEBUG(("HeartBeatHandler: RemoveHandle"));

    hdMutex_->Acquire();

    HandleMap::iterator iter = hdMap_.find(inst);

    if (iter->second)
    { 
        free(iter->second);
        if (hdMap_.erase(inst))
        {
             DIA_TRACE_DEBUG(("RemoveHandle: Socket instance <%d>", inst));
        }
    }

    hdMutex_->Release();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
HeartBeatHandler::SendHeartBeatToDest(ITS_UINT clientId)
{
    ITS_EVENT ev;
    ITS_INT i;

    DIA_TRACE_DEBUG(("HeartBeatHandler: SendHeartBeatToDest"));

    ITS_EVENT_INIT(&ev, ITS_APP_SRC, sizeof(ITS_UINT) + sizeof(ITS_OCTET));

    for (i = 0; i < sizeof(ITS_UINT); i++)
    {
        ev.data[i] = 0xFF;
    }

    ev.data[i] = HEARTBEAT_MSG;

    DIA_TRACE_DEBUG(("\nMessage to client event len:%d\n",ev.len));
    IDSCL_Print(ev.data, ev.len);

    SendUdpMsg(clientId, &ev);
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
UdpHeartBeatTable::UdpHeartBeatTable()
{
    hdMutex_ = new its::Mutex(0);
}
UdpHeartBeatTable::~UdpHeartBeatTable()
{
    delete hdMutex_;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
UdpHeartBeatTable::InsertEntry(ITS_UINT clientId)
{

    UDP_HB_INFO *  info;
    DIA_TRACE_DEBUG(("UdpHeartBeatTable: InsertHandle"));

    info = (UDP_HB_INFO * ) malloc(sizeof(UDP_HB_INFO ));
    if (info == NULL)
    {
        //alloc failed throw exception();
        throw "Error: memory allocation failed";
    }
    info->clientId = clientId;
    info->tries = 0;
    //info->lastUpdated = 0;
    info->count = 0;

    hdMutex_->Acquire();
    UdpHbMap.insert(UdpHbTable::value_type(clientId, info));
    hdMutex_->Release();
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
UdpHeartBeatTable::RemoveEntry(ITS_UINT inst)
{
    DIA_TRACE_DEBUG(("UdpHeartBeatTable: RemoveHandle"));

    hdMutex_->Acquire();

    UdpHbTable::iterator iter = UdpHbMap.find(inst);

    if (iter->second)
    {
        free(iter->second);
        if (UdpHbMap.erase(inst))
        {
            DIA_TRACE_DEBUG(("RemoveHandle: Socket instance <%d>", inst));
        }
    }
    hdMutex_->Release();
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
UDP_HB_INFO**
UdpHeartBeatTable::GetAllValues(ITS_UINT* count)
{
    ITS_INT index = 0;
    UDP_HB_INFO **dInfo= NULL;

    //DIA_TRACE_DEBUG(("ConnectionTable: GetAllValues"));

    hdMutex_->Acquire();
    UdpHbTable::const_iterator iter = UdpHbMap.begin();
    *count = UdpHbMap.size();

    if (*count)
    {
        dInfo= (UDP_HB_INFO**) calloc(*count, sizeof(UDP_HB_INFO*));
        if (dInfo == NULL)
        {
            throw "Error: memory allocation failed"; 
        }        

        for (index = 0; index < *count; index++)
        {
            //memcpy(&dInfo[index], ((*iter).second), sizeof(UDP_HB_INFO));
            dInfo[index] = iter->second;
            iter++;
        }
    }

    hdMutex_->Release();
    return (dInfo);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      Not thread safe. To be used in conjunction with Lock() and Unlock().
 *
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date       Reference               Description
 *  ---------------------------------------------------------------------------
 *
 ****************************************************************************/
UDP_HB_INFO *
UdpHeartBeatTable::RetrieveEntry(ITS_UINT key)
{
    UDP_HB_INFO *entry = NULL;

    DIA_TRACE_DEBUG(("UdpHeartBeatTable: RetrieveEntry"));

    hdMutex_->Acquire();
    UdpHbTable::iterator iter = UdpHbMap.find(key);

    if (iter != UdpHbMap.end())
    {
        entry = ((*iter).second);
    }
    else
    {
        hdMutex_->Release();
        return NULL;
    }
    hdMutex_->Release();
    return (entry);
}




