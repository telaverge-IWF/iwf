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
 * ID: $Id: ids_callbacks.cpp,v 3.25.42.1 2013/02/27 08:49:06 jvikram Exp $
 *
 * LOG: $Log: ids_callbacks.cpp,v $
 * LOG: Revision 3.25.42.1  2013/02/27 08:49:06  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.25  2010/09/20 06:01:14  nvijikumar
 * LOG: MsgHandler constructor moved after diastack initialization
 * LOG:
 * LOG: Revision 3.24  2010/08/19 11:23:06  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 3.23  2010/07/07 08:29:49  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 3.22  2009/09/07 05:08:21  rajeshak
 * LOG: Changes for HMI Heartbeat Callback
 * LOG:
 * LOG: Revision 3.21  2009/08/28 12:28:45  rajeshak
 * LOG: Fix for Issue 2330 (IDS sends Heartbeat to IDC after double the time
 * LOG: configured in XML)
 * LOG: Changed the Previous heartbeat Implementation
 * LOG:
 * LOG: Revision 3.20  2009/08/25 10:16:32  rajeshak
 * LOG: Fix for Issue:2322 (IDS unable to send Heartbeat Message to DMC client)
 * LOG: Passing TrHandle properly.
 * LOG:
 * LOG: Revision 3.19  2009/08/24 11:43:15  rajeshak
 * LOG: Fix for Issue 2317(ACTIVE COLD REDUNDANCY::IDC not able to send
 * LOG: messages to ACTIVE server)
 * LOG:
 * LOG: Revision 3.18  2009/06/29 14:38:19  rajeshak
 * LOG: HMI Changes to improve the performance.
 * LOG:
 * LOG: Revision 3.17  2009/04/10 07:10:48  sureshj
 * LOG: Compilation flag HMI_ENABLE removed.
 * LOG:
 * LOG: Revision 3.16  2009/04/09 12:42:14  nvijikumar
 * LOG: HeartBeat support for MML API Interface
 * LOG:
 * LOG: Revision 3.15  2009/04/07 14:23:42  sureshj
 * LOG: HMI and Overload callbacks registering added.
 * LOG:
 * LOG: Revision 3.14  2009/03/19 12:45:22  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.13  2009/03/19 08:12:53  nvijikumar
 * LOG: Reverting back HMI changes (App hangs and drop in TPS)
 * LOG: HMI changes are planed to provide after 4.0
 * LOG:
 * LOG: Revision 3.12  2009/03/18 13:08:12  rajeshak
 * LOG: Added new Callback for getting IDC connection info.
 * LOG:
 * LOG: Revision 3.11  2009/03/16 11:53:06  sureshj
 * LOG: FeatureId: HMI enhancement for monitoring raw threads.
 * LOG: Description: Register HMI callbacks.
 * LOG:
 * LOG: Revision 3.10  2009/03/10 03:45:40  nvijikumar
 * LOG: Exit application if IDC transport initialization fails
 * LOG:
 * LOG: Revision 3.9  2009/03/03 10:36:29  nvijikumar
 * LOG: Cleanup:: Removed ITS_CLASS_EXTENSION for itsSOCKTRAN_DynamicServerClassRec
 * LOG: as we no more uses this transport for IDC communication
 * LOG:
 * LOG: Revision 3.8  2009/02/12 04:16:58  nvijikumar
 * LOG: 1. Provided Callback function to Stack for message processing at IDS
 * LOG: 2. Not dispatching dedicated threads for message processing at IDS
 * LOG: 3. Cleanup
 * LOG:
 * LOG: Revision 3.7  2009/01/04 06:23:54  nvijikumar
 * LOG: Platform transport replaced with new TCP transport to handle IDC traffic
 * LOG: To limit number of threads with multiple connections
 * LOG:
 * LOG: Revision 3.6  2008/12/17 07:03:13  nvijikumar
 * LOG: Typo in the trace
 * LOG:
 * LOG: Revision 3.5  2008/12/10 11:31:34  nvijikumar
 * LOG: Having new flag to check Scenario type Distributed / Static
 * LOG:
 * LOG: Revision 3.4  2008/11/06 07:07:50  nvijikumar
 * LOG: ssueID: none
 * LOG: FeatureID: 3.1.1 release feature
 * LOG: Description: UDP Transport support between IDS and IDC
 * LOG:
 * LOG: Revision 3.3  2008/10/31 05:35:24  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID: none
 * LOG: Description: 1. Introducing additional TQs and Threads for better
 * LOG:                 Performance on PP50 and initial stack tunning
 * LOG:              2. Unwanted code cleanup
 * LOG:
 * LOG: Revision 3.2  2008/10/28 12:02:52  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.1.2.3  2008/10/07 07:34:48  nvijikumar
 * LOG: RePlace Timestamps with counts to detect transport failure
 * LOG:
 * LOG: Revision 3.1.2.2  2008/09/16 10:43:34  nvijikumar
 * LOG: Removed unwanted free from WriteEvent
 * LOG:
 * LOG: Revision 3.1.2.1  2008/09/16 09:34:29  nvijikumar
 * LOG: Provided Wrapper for Read and Write to avoid number of reads and writes
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.9  2008/03/27 11:21:05  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.7.2.1  2007/03/30 12:57:36  nvijikumar
 * LOG: Dont Register Base AppId explicitly Bridgewater requirement.
 * LOG:
 * LOG: Revision 2.7  2007/02/27 13:07:05  nvijikumar
 * LOG: Terminate transport before cleaning up the IDS stuff.
 * LOG:
 * LOG: Revision 2.6  2007/02/19 05:03:43  kamakshilk
 * LOG: Fix for IDS ctrl+C crash
 * LOG:
 * LOG: Revision 2.5  2006/11/29 04:16:18  kamakshilk
 * LOG: Fix for bug ID 4963
 * LOG:
 * LOG: Revision 2.4  2006/11/14 07:06:41  kamakshilk
 * LOG: New architecture. Session table removed
 * LOG:
 * LOG: Revision 2.3  2006/10/29 05:27:05  kamakshilk
 * LOG: Added conTable,routeTable and sTable cleanups
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:17:44  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.9  2006/06/14 09:28:42  kamakshilk
 * LOG: Self-register for AppId 0
 * LOG:
 * LOG: Revision 1.8  2006/06/07 07:32:24  yranade
 * LOG: Enable OD Specific Tracing
 * LOG:
 * LOG: Revision 1.7  2006/05/30 09:37:51  yranade
 * LOG: Changes to compile with CC compiler on solaris 10.
 * LOG:
 * LOG: Revision 1.6  2006/04/27 15:59:05  yranade
 * LOG: Updates to reflect changes in Diameter tracing.
 * LOG:
 * LOG: Revision 1.5  2006/04/06 07:42:55  adutta
 * LOG: Removed hex dump trace
 * LOG:
 * LOG: Revision 1.4  2006/03/13 05:17:44  adutta
 * LOG: Check IDS_APPDATA_SRC
 * LOG:
 * LOG: Revision 1.3  2006/03/06 13:12:20  adutta
 * LOG: Trace change
 * LOG:
 * LOG: Revision 1.2  2006/03/03 13:24:47  adutta
 * LOG: Registration with stack after reg req. from client
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:47:51  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/
#ident "$Id: ids_callbacks.cpp,v 3.25.42.1 2013/02/27 08:49:06 jvikram Exp $"

#include <math.h>
#include <iostream>
#include <string>

#include <dia_trace.h>
#include <dia_config.h>
#include <dia_frame.h>

#include <ids_clientinterface.h>
#include <ids_msghandler.h>
#include <ids_routedb.h>
#include <ids_conndb.h>
#include <ids_idcManager.h>
#include <its_dia_config.h>

#include <its_redundancy.h>

its::WorkItemPool    *AimWorkItemPool = NULL;
MsgHandler           *msgHandler      = NULL;
HeartBeatHandler     *hbHandler       = NULL;
AppToStackMsgHandler *appMsgHandler   = NULL;
IdcTransManager      *idcTransMgr     = NULL;

// This flag is added to avoid crash during ctrl+C.
// The connection from IDC is Accepted only when this flag is True. 
ITS_BOOLEAN isIdsInitialized = ITS_FALSE;

extern ConnectionTable conTable;
extern RouteTable routeTable;
extern int HandleUdpRegMsg(IDS_DEST_INFO &dInfo);
extern int ParseIdcTransInfo();
extern void OverLoadCallbackFunc(ITS_POINTER object,
                ITS_POINTER userData,
                ITS_POINTER callData);

extern void HMICallbackFunc(ITS_POINTER object,
                ITS_POINTER userData,
                ITS_POINTER callData);

extern void HMIHeartbeatCBFunc(ITS_POINTER object,
                ITS_POINTER userData,
                ITS_POINTER callData);

/* DMS HearBeat Handling Callbacks */
extern DMS_CALLBACK hbRegister;
extern DIA_CALLBACK hbDeRegister;
extern DIA_CALLBACK hbResetLastUpdate;

extern"C"
{

/*
 *  Callback Function called by Stack to process message at IDS
 */
void ProcessStackMsgCB(ITS_EVENT *evt)
{
   msgHandler->ProcessDiaStackMsg(evt); 
}

void ProcessRedundancyMsgCB(ITS_EVENT* evt)
{
    msgHandler->ProcessRedundancyMsg(evt);
}

void SetDmsSockInfo(void *arg1, void *arg2)
{
   if ((arg1 == NULL) || (arg2 == NULL))
   {
       return;
   }
   ITS_USHORT *fd = (ITS_USHORT *)arg1;
   HeartBeatHandler::GetHeartBeatHandler()->SetDmsSockInfo(*fd, arg2);
}

void UnsetDmsSockInfo(void *arg)
{
   HeartBeatHandler::GetHeartBeatHandler()->UnsetDmsSockInfo();
}

void ResetDmsSockLastUpdate(void *arg)
{
    HeartBeatHandler::GetHeartBeatHandler()->ResetDmsSockLastUpdate();
}  

int ProcessStackCmdCB(int cmd, void* inParam, void* outParam)
{
    int ret = !ITS_SUCCESS;

    switch(cmd)
    {
        case GET_IDC_CONN_TABLE_SZ:
        {
            int* count = (int*)outParam;
            if (count != NULL)
            {
                *count = conTable.GetCount();
            }
            else
            {
                ret = !ITS_SUCCESS;
            }
            break;
        }
        case GET_IDC_CONN_INFO:
        {
            int* key = (int*) inParam;
            IDC_CONN_STATUS_INFO* pConnInfo =
                           (IDC_CONN_STATUS_INFO*)outParam;

            if ((key != NULL) && (pConnInfo != NULL))
            {
#if 0 
                IDS_TRANS_INFO* trInfo = conTable.RetrieveEntry(*key);
                if (trInfo != NULL)
                {
                    pConnInfo->estbTime = trInfo->estbTime;
                    pConnInfo->type     = trInfo->type;
                }
#endif
                ClientRoutingInfo* rInfo = routeTable.RetrieveEntry(*key);
                if (rInfo != NULL)
                {
                    pConnInfo->appIdentifier = rInfo->regInfo.appIdentifier;
                    pConnInfo->appIdType = rInfo->regInfo.appIdType;

                    ret = ITS_SUCCESS;
                }
            }
            break;
        }
        default:
        {
            ret = !ITS_SUCCESS;
            break;
        }
    } 

    return ret;
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
IDSAPP_DLLAPI ITS_USHORT 
RouteAllToApp(ITS_HDR* h, ITS_EVENT* ev)
{
    DIA_TRACE_DEBUG(("IDS Received Event\n "));
  
    return (IDS_MSG_QUEUE);
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
IDSAPP_DLLAPI ITS_USHORT 
RouteNoneToApp(ITS_HDR* h, ITS_EVENT* ev)
{
    if (ev->src == ITS_MAB_SRC)
    {
       return (IDS_MSG_QUEUE);
    }
    else
    { 
       return (ITS_NO_SRC);
    }
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
IDSAPP_DLLAPI ITS_USHORT 
RouteOddToApp(ITS_HDR* hdr, ITS_EVENT* event)
{
   return (ITS_NO_SRC);
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
IDSAPP_DLLAPI ITS_USHORT 
RouteEvenToApp(ITS_HDR* hdr, ITS_EVENT* event)
{
   return (ITS_NO_SRC);
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
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi      09-06-06    Enhancement    Self Register for AppID 0.
 *   Kamakshi      19-02-07    Bug 5251       isIdsInitialized set to TRUE.
 *   sureshj       09-03-09    Enhancement    Register HMI callbacks
 ****************************************************************************/
IDSAPP_DLLAPI void
IDSPreFunc()
{
    DIA_TRACE_DEBUG(("IDSPreFunc"));
    AimWorkItemPool = new its::WorkItemPool(IDS_WORKITEM_QUEUE,
                                        IDS_NUM_OF_THREADS, 0);

  
    /* This instance is not needed as there is no dedicated Queue and thread
     * exists at IDS layer
     */
    //appMsgHandler = new AppToStackMsgHandler;

    hbHandler = HeartBeatHandler::GetHeartBeatHandler();

    /* This instance is not needed as there is no dedicated Queue and thread
     * exists at IDS layer
     */
    //AimWorkItemPool->AddWorkItem(msgHandler);
    //AimWorkItemPool->AddWorkItem(appMsgHandler);

    DiaConfig *cfg = DiaConfig::GetDiaConfig();
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();

    if (diaFrame)
    {
        if (cfg)
        {
            diaFrame->SetConfigFile(cfg->GetConfigFile());
            diaFrame->Initialize();
        }
    }
    /* XML Elements are parsed only after DiaStack Initialize */
    msgHandler = new MsgHandler;

    /* Setting Distributed Scenario falg ON */
    ITSDiaConfig *dCfg = NULL;
    dCfg = &itsDiaConfig;
    if (cfg != NULL)
    {
        dCfg->SetDistScenarioFlag();
        dCfg->RegisterIDSMsgProcessingCB((void *)ProcessStackMsgCB);
        dCfg->RegisterIDSRedundancyCB((void *)ProcessRedundancyMsgCB);
    }

    /* setting Callbackfunction for IDS Cmd Processing */
    dCfg->RegisterIDSCmdProcessingCB((void*)ProcessStackCmdCB);

    /* New Transport Changes */
    if (ParseIdcTransInfo() != ITS_SUCCESS)
    {
        DIA_TRACE_CRITICAL(("IDSPreFunc: Failed to parse IDC Trans info"));
        return;
    }
    /* Create IdcTransManager transport*/
    idcTransMgr = IdcTransManager::GetIdcTransManager();
    if ((idcTransMgr == NULL) || (idcTransMgr->StartMgr() != ITS_SUCCESS))
    {
        DIA_TRACE_CRITICAL(("IDSPreFunc: CreateTrans failied"));
        exit(1);
        return;
    }
    /* register for HMI and Overload callbacks */
    if (CALLBACK_AddCallback(Overload_Callbacks, (ITS_CALLBACK)OverLoadCallbackFunc, NULL)
                            != ITS_SUCCESS)
    {
        DIA_TRACE_DEBUG((" Unable to Register OverloadCallbacks \n"));
    }
    else
    {
         DIA_TRACE_DEBUG((" Successfully registered Overloadcallback\n"));
    }
    if (CALLBACK_AddCallback(HMI_Callbacks, (ITS_CALLBACK)HMICallbackFunc, NULL) != ITS_SUCCESS)
    {
        DIA_TRACE_DEBUG((" Unable to Register HMICallbacks \n"));
    }
    else
    {
         DIA_TRACE_DEBUG((" Successfully registred HMI callback\n"));
    }

    if (CALLBACK_AddCallback(HMI_HeartbeatCallbacks, (ITS_CALLBACK)HMIHeartbeatCBFunc, NULL)
                                                             != ITS_SUCCESS)
    {
        DIA_TRACE_DEBUG((" Unable to Register HMI Heartbeat Callback\n"));
    }
    else
    {
        DIA_TRACE_DEBUG((" Successfully registred HMI Heartbeat Callback\n"));
    }

    AimWorkItemPool->AddWorkItem(hbHandler);

    hbRegister        = (DMS_CALLBACK)SetDmsSockInfo;
    hbDeRegister      = (DIA_CALLBACK)UnsetDmsSockInfo; 
    hbResetLastUpdate = (DIA_CALLBACK)ResetDmsSockLastUpdate;

    isIdsInitialized = ITS_TRUE;
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
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi      19-02-07    Bug 5251       isIdsInitialized set to FALSE.
 *
 ****************************************************************************/
IDSAPP_DLLAPI void
IDSPostFunc()
{
    DIA_TRACE_DEBUG(("IDSPostFunc"));

    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    if (diaFrame)
    {
        diaFrame->Terminate();
    }

    if (idcTransMgr)
    {
        /** Stopping the idcAcceptor & idcReader Thread.
         ** Obj gets deleted on thead exit
         **/
        idcTransMgr->Stop();
    }

    if (msgHandler)
    {
        delete msgHandler;
        msgHandler = NULL;
    }

    if (appMsgHandler)
    {
        delete appMsgHandler;
        appMsgHandler = NULL;
    }

    if (hbHandler)
    { 
        /** Stopping the HB Thread. hbHandler Obj is deleted on thead exit **/
        hbHandler->Stop();
#if 0
        delete hbHandler;
        hbHandler = NULL;
#endif
    }

    isIdsInitialized = ITS_FALSE;

    delete AimWorkItemPool;

    routeTable.RemoveAllEntries();
    conTable.RemoveAllEntries();

    ITS_GlobalStop();

    _exit(0);
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
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi      19-02-07    Bug 5251       isIdsInitialized flag checked.
 *
 ****************************************************************************/
IDSAPP_DLLAPI ITS_INT
IDS_OnAccept(TPOOL_THREAD *thrd1, TPOOL_THREAD *thrd2)
{
    DIA_TRACE_DEBUG(("IDS_OnAccept"));

    if (isIdsInitialized)
        return (ITS_SUCCESS);
    else
        return (!ITS_SUCCESS);
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
IDSAPP_DLLAPI ITS_INT 
IDS_NextEventFailed(TPOOL_THREAD *thr, ITS_INT pReturn)
{
    DIA_TRACE_DEBUG(("IDS_NextEventFailed"));

    return (!ITS_SUCCESS);
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
IDSAPP_DLLAPI ITS_INT
IDS_UdpPostInit(TPOOL_THREAD* thr, ITS_HANDLE h)
{
    ITS_CHAR* addr;
    ITS_UINT port;
    SOCKTRAN_Manager* m;
    HeartBeatHandler* hb = NULL;

    DIA_TRACE_DEBUG(("IDS_UdpPostInit"));

    if (thr == NULL || h == NULL)
    {
        DIA_TRACE_CRITICAL(("IDS_PostInit: Failed to Initialize Socketi \
                             check ServerIP & Port"));
        exit(1);
    }

    if (h != NULL)
    {
        m = (SOCKTRAN_Manager*)h;
        addr = m->socket.host_or_path;
        port =  m->socket.port;

        (ClientHandler::GetClientHandler())->SetUdpHandle(h);
        (ClientHandler::GetClientHandler())->SetServerIPAddr(addr);
        (ClientHandler::GetClientHandler())->SetServerUdpPort(port);

        return (ITS_SUCCESS);
    }

    return (ITS_SUCCESS);

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
IDSAPP_DLLAPI ITS_INT
IDS_PostNextUdpEvent(TPOOL_THREAD *thr, ITS_EVENT *event)
{
    its::Event* ev = (its::Event*)event;
    HeartBeatHandler* hb = NULL;
    ITS_EVENT* evt = &ev->GetEvent();
    IDS_TRANS_INFO dInfo;
    ITS_UINT clientId;
    UDP_HB_INFO * info;

    DIA_TRACE_DEBUG(("IDS_Post UDP NextEvent"));

    //Initializing Uninitialized Scalar Variable
    memset(&dInfo, 0, sizeof (IDS_TRANS_INFO));
    if (evt->src != IDS_APPDATA_SRC)
    {

        if ((evt->len > IDS_MIN_MSG_SIZE) && (evt->data[IDS_MSG_TYPE_POS]
                    == REGISTER_MSG))
        {
            DIA_TRACE_DEBUG(("IDS_PostNextEvent: Register from client"));
            (ClientHandler::GetClientHandler())->RegisterUdp(thr, evt);

        }
        else if ((evt->len > IDS_MIN_MSG_SIZE) && (evt->data[IDS_MSG_TYPE_POS]
                    == DEREGISTER_MSG))
        {
            DIA_TRACE_DEBUG(("IDS_PostNextEvent: De-Register from client"));
            (ClientHandler::GetClientHandler())->DeRegisterUdp(thr, evt);

        }
        else
        {
            DIA_TRACE_DEBUG(("IDS_PostUDP NextEvent: Dia-Message from client"));
            HandleUdpRegMsg(dInfo.u.udpInfo);
            clientId = conTable.GetKeyFromValue(&dInfo);
            hb = HeartBeatHandler::GetHeartBeatHandler();
            if(clientId && hb)
            {
                info = hb->GetUdpTable().RetrieveEntry(clientId);
                //info->lastUpdated = 0;
                info->tries       = 0;
                info->count       = 0;
            }
        }
    }
    else
    {

        DIA_TRACE_DEBUG((" IDS_PostUDP NextEvent: Diameter-Message "));
        HandleUdpRegMsg(dInfo.u.udpInfo);
        clientId = conTable.GetKeyFromValue(&dInfo);
        hb = HeartBeatHandler::GetHeartBeatHandler();

        if(clientId && hb)
        {
            info = hb->GetUdpTable().RetrieveEntry(clientId);
            //info->lastUpdated = 0;
            info->count       = 0;
            info->tries       = 0;
        }
        if (msgHandler->ProcessAppMsg(evt) != ITS_SUCCESS)
        {
            DT_ERR((" Failed to process Message from IDC"));
        }
        ITS_EVENT_TERM(evt);
    }

    return (ITS_SUCCESS);
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
IDSAPP_DLLAPI void
IDS_MembershipChangeCb(ITS_POINTER object,
                       ITS_POINTER userData, 
                       ITS_POINTER callData)
{
    static ITS_INT first = 1;

    DSM_MembershipChangeCbData*
        membershipChangeCbData =
        (DSM_MembershipChangeCbData*)callData;
    
    ITS_USHORT concernedNodeId = membershipChangeCbData->memberNodeId;
    
    if (membershipChangeCbData->membershipChangeType == 
                                             DSM_FT_GROUP_MEMBER_LEAVE)
    {
        DIA_TRACE_WARNING(("IDS_MembershipChangeCb: Member leave nodeid = %d",
                                                              concernedNodeId));

       (ClientHandler::GetClientHandler())->SendServerUpInd();
       
        ROUTE_SetApplicationSelector(RouteAllToApp);
    }
    else if (membershipChangeCbData->membershipChangeType ==
                                                  DSM_FT_GROUP_MEMBER_JOIN)
    {
        
        DIA_TRACE_DEBUG(("IDS_MembershipChangeCb: Member join nodeid = %d",
                                                   concernedNodeId));

        ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);

        if (redunClass == NULL)
        { 
            DIA_TRACE_DEBUG(("IDS_MembershipChangeCb: redunClass NULL"));

            return;
        }

        if (!first && REDUNDANCY_CONFIGURED_TYPE(redunClass) == 
                                                        ITS_ACTIVE_ACTIVE)
        {
            DIA_TRACE_DEBUG(("IDS_MembershipChangeCb: acitve-active"));

            if (DSM_GetNodeId() == 1)
            {
                ROUTE_SetApplicationSelector(RouteOddToApp);
            }
            else
            {
                ROUTE_SetApplicationSelector(RouteEvenToApp);
            }
        }
        else
        {
            first = 0;
        }
    }
    else if (membershipChangeCbData->membershipChangeType ==
                                                   DSM_FT_GROUP_MEMBER_ALIVE)
    {
        
        DIA_TRACE_DEBUG(("IDS_MembershipChangeCb: Member alive = %d",
                                                   concernedNodeId));
    }
}

}

