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
 * ID: $Id: ids_clientinterface.cpp,v 3.22.6.4.6.3 2013/04/01 05:35:36 vsarath Exp $
 *
 * LOG: $Log: ids_clientinterface.cpp,v $
 * LOG: Revision 3.22.6.4.6.3  2013/04/01 05:35:36  vsarath
 * LOG: Fix for Coverity warnings
 * LOG:
 * LOG: Revision 3.22.6.4.6.2  2013/03/12 04:45:02  vsarath
 * LOG: Fix for coverity issue
 * LOG:
 * LOG: Revision 3.22.6.4.6.1  2013/02/27 08:49:06  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.22.6.4  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.22.30.2  2012/11/20 10:16:59  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.22.30.1  2012/11/06 09:44:15  millayaraja
 * LOG: merge from B-DRE-0212-00 branch
 * LOG:
 * LOG: Revision 3.22.6.1  2012/11/05 12:09:00  pramana
 * LOG: Fix for coverity issue 10563
 * LOG:
 * LOG: Revision 3.22.24.1  2012/11/05 10:17:41  ncshivakumar
 * LOG: iCoverity Fixes
 * LOG:
 * LOG: Revision 3.22.6.2  2012/11/06 16:31:20  pramana
 * LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
 * LOG:
 * LOG: Revision 3.22.34.1  2012/11/06 10:06:11  cprem
 * LOG: Merged from 00 branch for 0212-06 release
 * LOG:
 * LOG: Revision 3.22.6.1  2012/11/05 12:09:00  pramana
 * LOG: Fix for coverity issue 10563
 * LOG:
 * LOG: Revision 3.22.24.1  2012/11/05 10:17:41  ncshivakumar
 * LOG: iCoverity Fixes
 * LOG:
 * LOG: Revision 3.22  2010/09/22 05:26:37  nvijikumar
 * LOG: GlobalUniqueAddr based routing/distribution support
 * LOG:
 * LOG: Revision 3.21  2009/08/24 11:43:15  rajeshak
 * LOG: Fix for Issue 2317(ACTIVE COLD REDUNDANCY::IDC not able to send
 * LOG: messages to ACTIVE server)
 * LOG:
 * LOG: Revision 3.20  2009/06/18 11:42:01  sureshj
 * LOG: Fix for helpdesk issue Id 2172 IDS caught core handler caught signal 11.
 * LOG:
 * LOG: Revision 3.19  2009/03/19 16:37:06  ssaxena
 * LOG: Made changes in the debug traces for redirect application Id
 * LOG:
 * LOG: Revision 3.18  2009/03/19 12:45:22  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.17  2009/03/03 11:10:47  rajeshak
 * LOG: Klockwork reported issue fix
 * LOG:
 * LOG: Revision 3.16  2009/02/19 08:35:22  nvijikumar
 * LOG: Dispatch dedicated Sender thread and queue only if _IDS_SENDER_THR defined
 * LOG:
 * LOG: Revision 3.15  2009/02/19 05:47:28  nvijikumar
 * LOG: Changes to write event directly to the socket instead of putting into
 * LOG: Sender threads, Still SenderThread exits only for transport Reg / Deg .
 * LOG: Going forward Sender thread can be avoided completely
 * LOG:
 * LOG: Revision 3.14  2009/01/04 06:25:45  nvijikumar
 * LOG: 1. Platform transport replaced with new TCP transport to handle IDC traffic
 * LOG:    To limit number of threads with multiple connections
 * LOG: 2. Having seperate API to handle UDP De-Registration message
 * LOG:
 * LOG: Revision 3.13  2009/01/01 05:44:17  nvijikumar
 * LOG: Fix for Issue Id: 1411
 * LOG: Alarm when failed to route message to IDC
 * LOG:
 * LOG: Revision 3.12  2008/12/23 09:35:16  nvijikumar
 * LOG: Alarm 15052 support
 * LOG: 15052: Transport connection success with client application
 * LOG:
 * LOG: Revision 3.11  2008/12/17 07:08:26  nvijikumar
 * LOG: Changes to fix endiannes issue with UDP Read/Write
 * LOG: Issue Id: 1338
 * LOG:
 * LOG: Revision 3.10  2008/12/13 01:28:31  rajeshak
 * LOG: Send ServerUp Indication to IDC only if connections exists
 * LOG:
 * LOG: Revision 3.9  2008/12/12 17:04:05  nvijikumar
 * LOG: Support to raise ALARMS
 * LOG:
 * LOG: Revision 3.8  2008/11/18 14:46:14  gdalawai
 * LOG: Fix for whizible ID:1279
 * LOG: IDS is not sending any error response if Client ID already registered (UDP)
 * LOG:
 * LOG: Revision 3.7  2008/11/18 04:37:56  nvijikumar
 * LOG: IssueID:1263
 * LOG: FeatureID:UDP transport support
 * LOG: Description: Failed to register over UDP - Fix
 * LOG:
 * LOG: Revision 3.6  2008/11/11 10:53:17  snandihalli
 * LOG: Fix for IssueID : 6420,6421
 * LOG:
 * LOG: Revision 3.5  2008/11/06 07:15:33  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: 3.1.1 release feature
 * LOG: Description: UDP Transport support between IDS and IDC
 * LOG:
 * LOG: Revision 3.4  2008/10/31 05:35:24  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID: none
 * LOG: Description: 1. Introducing additional TQs and Threads for better
 * LOG:                 Performance on PP50 and initial stack tunning
 * LOG:              2. Unwanted code cleanup
 * LOG:
 * LOG: Revision 3.3  2008/10/28 12:02:52  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.2  2008/09/08 12:10:56  ssaxena
 * LOG: Replaced the raw value to TypeToText for ConnectionType
 * LOG:
 * LOG: Revision 3.1.2.1  2008/10/07 07:24:07  nvijikumar
 * LOG: Memory leak fix for error scenario
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.11  2008/03/27 11:21:05  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.8.8.3  2007/04/04 06:07:23  nvijikumar
 * LOG: Validate IDC register request as per appId and AppId Type.
 * LOG:
 * LOG: Revision 2.8.8.2  2007/04/03 09:50:01  nvijikumar
 * LOG: Explicit dframe register is not required when IDS get required from IDC.
 * LOG: XML entries are already registered when application initialized.
 * LOG:
 * LOG: Revision 2.8.8.1  2007/03/13 05:12:29  hbhatnagar
 * LOG: Allow multiple registration from same client
 * LOG:
 * LOG: Revision 2.8  2006/11/24 15:42:58  kamakshilk
 * LOG: Changes for redundancy support
 * LOG:
 * LOG: Revision 2.7  2006/11/17 06:01:30  kamakshilk
 * LOG: DccaEnable byte added in RegAck msg
 * LOG:
 * LOG: Revision 2.6  2006/11/14 07:11:19  kamakshilk
 * LOG: Trace changed
 * LOG:
 * LOG: Revision 2.5  2006/11/08 06:12:40  kamakshilk
 * LOG: Changes for 64-bit support. ITS_ULONG changed to ITS_UINT
 * LOG:
 * LOG: Revision 2.4  2006/11/07 11:53:01  kamakshilk
 * LOG: Added ValidateAppId method
 * LOG:
 * LOG: Revision 2.3  2006/10/31 10:05:32  kamakshilk
 * LOG: IDSCL_Print function added
 * LOG:
 * LOG: Revision 2.2  2006/10/26 05:43:34  kamakshilk
 * LOG: Added ReleaseClientHandler() method
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.6  2006/06/14 09:30:50  kamakshilk
 * LOG: Register only when AppId != 0 received from client.
 * LOG:
 * LOG: Revision 1.5  2006/04/26 10:07:38  adutta
 * LOG: Fixed issues#3607/3608
 * LOG:
 * LOG: Revision 1.4  2006/04/06 07:43:58  adutta
 * LOG: Return from reg. function corrected
 * LOG:
 * LOG: Revision 1.3  2006/03/06 13:15:29  adutta
 * LOG: Registration in IsClientAllowed()
 * LOG:
 * LOG: Revision 1.2  2006/03/03 13:24:47  adutta
 * LOG: Registration with stack after reg req. from client
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:47:51  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/
#ident "$Id: ids_clientinterface.cpp,v 3.22.6.4.6.3 2013/04/01 05:35:36 vsarath Exp $"
#ident "$Id: ids_clientinterface.cpp,v 3.22.6.4.6.3 2013/04/01 05:35:36 vsarath Exp $"



#include <dia_trace.h>
#include <dia_frame.h>

#include <its_dia_config.h>

#include <ids_clientinterface.h>
#include <ids_msghandler.h>
#include <ids_conndb.h>
#include <ids_routedb.h>
#include <ids_idcManager.h>

#include <its_redundancy.h>

extern IDSAPP_DLLAPI int
IDSCL_Decode(IDS_MESSAGE *msg, ITS_EVENT *event);

extern IDSAPP_DLLAPI int
IDSCL_Encode(IDS_MESSAGE *msg, ITS_EVENT *event);

int HandleUdpRegMsg(IDS_DEST_INFO &dInfo);
int SendMsgToDest(IDS_DEST_INFO *info, ITS_EVENT *evt);

ClientHandler* ClientHandler::s_clientHandler = NULL;
ConnectionTable conTable;
RouteTable routeTable;

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
ClientHandler* 
ClientHandler::GetClientHandler()
{
    DIA_TRACE_DEBUG(("ClientHandler: GetClientHandler"));

    if (s_clientHandler == NULL)
    {
        s_clientHandler = new ClientHandler;
    }

    return (s_clientHandler);
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
IDS_CONNECTION_TYPE
ClientHandler::GetConnectionType()
{
    ITS_NODE_STATE node;
    ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);

    DIA_TRACE_DEBUG(("ClientHandler: GetConnectionType"));

    if (redunClass == NULL)
    {
        DIA_TRACE_WARNING(("GetConnectionType: No redundancy"));

        return (IDS_PRIMARY_CONNECTION);
    }

    ITS_GetNodeState(&node);

    if (node == ITS_STATE_PRIMARY)
    {
        DIA_TRACE_DEBUG(("GetConnectionType: Node primary"));

        return (IDS_PRIMARY_CONNECTION);
    }
    else
    {
        DIA_TRACE_DEBUG(("GetConnectionType: Node secondary"));

        return (IDS_BACKUP_CONNECTION);
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
ClientHandler::ClientHandler():
tType(IDS_TCP),
udpHandle(NULL)
{
    DIA_TRACE_DEBUG(("ClientHandler: ClientHandler"));
    //Initializing Uninitialized pointer vlaue
    servAddr = NULL;
    servPort = 0;
    servUdpPort = 0;
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
ClientHandler::~ClientHandler()
{
    DIA_TRACE_DEBUG(("ClientHandler::~ClientHandler"));
   
    if (servAddr)
    {
        free(servAddr);
        servAddr = NULL;
    }
    servPort = 0;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Releases the static s_clientHandler pointer
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
 *  Return Value: None
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
void ClientHandler::ReleaseClientHandler()
{
    DIA_TRACE_DEBUG(("ClientHandler::ReleaseClientHandler"));

    if (s_clientHandler)
    {
        delete s_clientHandler;
        s_clientHandler = NULL;
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
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------- *   Name          Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Kamakshi      09-06-06   Enhancement      Register only when AppId is 
 *                                             non-zero (not base protocol). 
 *   Kamakshi      07-11-06   Enhancement      Validate AppId. 
 *   Kamakshi      12-04-07   BridgeWater      Duplicate client check removed.
 *                                             AppId reregister check added. 
 *
 ****************************************************************************/
ITS_INT
ClientHandler::IsClientAllowed(IDS_MESSAGE* msg)
{
    ITS_INT ret = ITS_SUCCESS;

    DIA_TRACE_DEBUG(("ClientHandler: IsClientAllowed"));

    // TO DO: Needs to validate with the XML appId entries
    switch(msg->u.regInfo.routing_criteria)
    {
       case IDS_APP_IDENTIFIER:
           DIA_TRACE_DEBUG(("IsClientAllowed : Criteria AppId <%u>", 
                                               msg->u.regInfo.appIdentifier ));
           DIA_TRACE_DEBUG(("IsClientAllowed : Criteria AppIdType <%u>", 
                                               msg->u.regInfo.appIdType ));
           ret = ITS_SUCCESS;
       break;

       default:
           ret = IDS_ROUTING_CRITERIA_INVALID;
       break;
    }

    /* Check if same client has registered with the same AppId */
    if (routeTable.RetrieveWithAppId(msg->clientID,
                         msg->u.regInfo.appIdentifier))
    {
        DIA_TRACE_ERROR(("IsClientAllowed: Application Registered already"));

        ret = IDS_APP_ID_REGISTERED_ALREADY;

        return ret;
    }

    if (msg->u.regInfo.appIdentifier != 0)
    {
         ret = ValidateAppId(msg->u.regInfo.appIdentifier, 
                             msg->u.regInfo.appIdType);
         if (ret != ITS_SUCCESS)
         {
             DIA_TRACE_ERROR(("IsClientAllowed: Unsupported App Id <%d> ",
                               msg->u.regInfo.appIdentifier));
             return ret;
         }
#if 0
         DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
         ret = diaFrame->RegisterApplication(msg->u.regInfo.appIdentifier,
                                             msg->u.regInfo.appIdType);

         if (ret != ITS_SUCCESS)
         {
             DIA_TRACE_ERROR(("Register: Fail to register with stack %d", ret));
         }
         else
         {
             DIA_TRACE_DEBUG(("*** Register: register with stack %d ***",
                                                 msg->u.regInfo.appIdentifier));
         }
#endif
    }

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Checks if the AppId is supported by the stack. 
 *
 *  Input Parameters:
 *      App Id.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value: ITS_SUCCESS or IDS_UNSUPPORTED_APP_ID
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 ****************************************************************************/
ITS_INT
ClientHandler::ValidateAppId(ITS_UINT& appId, ITS_UINT& appIdType)
{
    int i =0;
    DIA_CER *cer;
    cer = itsDiaConfig.GetLocalCER();

    if (appIdType == DIA_AUTHORIZATION)
    {
        for (int i=0; i<cer->countAuthApplicationId();i++)
        {
            if (appId == cer->getAuthApplicationId(i).value())
            {
                return ITS_SUCCESS;
            }
        }
    }
    else if (appIdType == DIA_ACCOUNTING)
    {
        for (int i=0; i<cer->countAcctApplicationId();i++)
        {
            if (appId == cer->getAcctApplicationId(i).value())
            {
                return ITS_SUCCESS;
            }
        }
    }
    
    /*
     * If not found check from vendorSpecific Id.
     */
    for (int i=0; i<cer->countVendorSpecificApplicationId();i++)
    {
        const diameter::base::VendorSpecificApplicationId 
                      &vendSpecificId = cer->getVendorSpecificApplicationId(i);
        if (appIdType == DIA_AUTHORIZATION)
        {
            if(vendSpecificId.containsAuthApplicationId() &&
               (appId == vendSpecificId.getAuthApplicationId().value()))
            {
                return ITS_SUCCESS;
            }
        }
        else if (appIdType == DIA_ACCOUNTING)
        {
            if(vendSpecificId.containsAcctApplicationId() &&
               (appId == vendSpecificId.getAcctApplicationId().value()))
            {
                return ITS_SUCCESS;
            }
        }
    }
#if 0
    for (
         i = 0;
         i < cer->countAuthApplicationId() ||
         i < cer->countAcctApplicationId() ||
         i < cer->countVendorSpecificApplicationId();
         i++)
    {
        if (i < cer->countAuthApplicationId() &&
           (appId == cer->getAuthApplicationId(i).value()) )
        {
            return ITS_SUCCESS;
        }
        else if(i < cer->countAcctApplicationId() &&
               (appId == cer->getAcctApplicationId(i).value()) )
        {
            return ITS_SUCCESS;
        }
    }
#endif 
    return IDS_UNSUPPORTED_APP_ID;
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
 *  --------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  --------------------------------------------------------------------------
 *   Kamakshi    24-11-06     Enhancement     Make new events when Multicast 
 *
 ****************************************************************************/
ITS_INT
ClientHandler::SendServerUpInd()
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_UINT count = 0;
    IDS_TRANS_INFO* clist = NULL;
    ITS_EVENT evt = {0,0,NULL}, evtUdp = {0,0,NULL};
    IDS_MESSAGE status, statusUdp;

    DIA_TRACE_DEBUG(("ClientHandler: SendServerUpInd"));

    clist = conTable.GetAllValues(&count);
    if (!count)
    {
        DIA_TRACE_DEBUG(("ClientHandler: No Client is connected"));
        if (clist != NULL)
        {
           free(clist);
           clist = NULL;
        }
        return !ITS_SUCCESS;
    }

    memset(&status, 0, sizeof(IDS_MESSAGE));
    memset(&statusUdp, 0, sizeof(IDS_MESSAGE));

    status.msg_type = SERVER_STATUS_MSG;
    status.u.servInfo.port = servPort;
    strncpy(status.u.servInfo.ipAddr, servAddr, 15); //Correcting Calling Risky Function
    status.u.servInfo.conType = GetConnectionType(); 

    if (IDSCL_Encode(&status, &evt) != ITS_SUCCESS)
    {
        //fix resource leak issue 
        //For memory leak.need free clist
        free(clist);
        clist = NULL;
        return !ITS_SUCCESS;
    }

    statusUdp.msg_type = SERVER_STATUS_MSG;
    statusUdp.u.servInfo.port = servUdpPort;
    strcpy(statusUdp.u.servInfo.ipAddr, servAddr);
    statusUdp.u.servInfo.conType = GetConnectionType();

    if (IDSCL_Encode(&statusUdp, &evtUdp) != ITS_SUCCESS)
    {
        //fix for the resource leak issue
        //For memory leak.need free clist
        free(clist);
        clist = NULL;
        return !ITS_SUCCESS;
    }

    DIA_TRACE_DEBUG(("\nMessage to client event len:%d\n",evt.len));
    IDSCL_Print(evt.data, evt.len);

#if 0
    clist = conTable.GetAllValues(&count);

    if (!count)
    {
        return (ITS_ENOTFOUND);
    }
#endif

    if (count == 1)
    {
        if ((&clist[0])->type == IDS_UDP)
        {
            SendMsgToDest(&((&clist[0])->u.udpInfo), &evtUdp);
        }
        else
        {
#if 0
            evt.src = (&clist[0])->u.tcpInfo;
            TRANSPORT_PutEvent(IDS_APP_TO_STACK_MSG_QUEUE, &evt);
#endif
            SendToIDC(&clist[0], &status);
        }
    }
    else
    {
        ITS_EVENT newevt;
        newevt.src = ITS_APP_SRC;
        for (ITS_INT i = 0; i < count; i++)
        {
            if ((&clist[i])->type == IDS_UDP)
            {
                newevt.len = evtUdp.len;
                newevt.data = (ITS_OCTET*)calloc(1, evtUdp.len);
                memcpy(newevt.data, evtUdp.data, evtUdp.len);
                SendMsgToDest(&((&clist[i])->u.udpInfo), &newevt);
            }
            else
            {
#if 0
                newevt.len = evt.len;
                newevt.data = (ITS_OCTET*)calloc(1, evt.len);
                memcpy(newevt.data, evt.data, evt.len);
                newevt.src = (&clist[i])->u.tcpInfo;
                TRANSPORT_PutEvent(IDS_APP_TO_STACK_MSG_QUEUE, &newevt);
#endif
                SendToIDC(&clist[i], &status);
            }
        }
#if 0
        free(evt.data);
        evt.len = 0;
        free(evtUdp.data);
        evtUdp.len = 0;
#endif
    }
    if (evt.data != NULL)
    {
        free(evt.data);
        evt.data = NULL;
        evt.len = 0;
    }

    if (evtUdp.data != NULL)
    {
        free(evtUdp.data);
        evtUdp.data = NULL;
        evtUdp.len = 0;
    }
    free(clist);

    DIA_TRACE_DEBUG(("SendServerUpInd: Server ip %s port %d type %d",
                                                   status.u.servInfo.ipAddr,
                                                   status.u.servInfo.port,
                                                   status.u.servInfo.conType));

    return (ret);
}

ITS_INT
ClientHandler::SendToIDC(IDS_TRANS_INFO* inst, IDS_MESSAGE* msg)
{
    ITS_EVENT evt = {0,0,NULL};
    ITS_INT ret = ITS_SUCCESS;

    if (IDSCL_Encode(msg, &evt) != ITS_SUCCESS)
    {
        return !ITS_SUCCESS;
    }
#if _IDS_SENDER_THR
    evt.src = inst->u.tcpInfo;
    ret = TRANSPORT_PutEvent(IDS_TCP_SEND_MSG_QUEUE, &evt);
#else
    evt.src = ITS_APP_SRC;
    ret = WriteEvent(inst, &evt);
#endif
    if (ret != ITS_SUCCESS)
    {
        DIA_TRACE_CRITICAL(("WriteEvent: Failed to client "));
    }
    ITS_EVENT_TERM(&evt);
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
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    12-04-07   BridgeWater Issue  Detect Duplicate client entry
 *                                             using transport Instance.
 *
 ****************************************************************************/
ITS_INT
ClientHandler::Register(ITS_INT sockId, ITS_EVENT *evt)
{
    IDS_MESSAGE msg;
    IDS_MESSAGE rackMsg;
    IDS_TRANS_INFO tableInfo;

    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    ITS_CHAR isDccaEnb = diaFrame->IsDccaEnabled();

    DIA_TRACE_DEBUG(("ClientHandler: Register"));

    rackMsg.msg_type = REGISTER_ACK_MSG;
    strncpy(rackMsg.u.regAck.ipAddr, servAddr, 15); //Correcting Calling Risky Function
    rackMsg.u.regAck.port = servPort;
    rackMsg.u.regAck.conType = GetConnectionType();
    rackMsg.u.regAck.isDccaEnbl = isDccaEnb;
    
    if (IDSCL_Decode(&msg, evt) != ITS_SUCCESS)
    {
        rackMsg.clientID = msg.clientID;
        rackMsg.u.regAck.result = FAILURE;
        rackMsg.u.regAck.errorCode = IDS_REGISTRATION_DECODE_FAIL;
        rackMsg.u.regAck.routing_criteria = IDS_APP_IDENTIFIER;

        DIA_Alarm(15050, __FILE__, __LINE__, "ClientId=%d:EC=%d", 
                  msg.clientID,rackMsg.u.regAck.errorCode);

        ITS_EVENT evt;
        if (IDSCL_Encode(&rackMsg, &evt) != ITS_SUCCESS)
        {
            return !(ITS_SUCCESS);
        }
#if _IDS_SENDER_THR
        evt.src = sockId;
        TRANSPORT_PutEvent(IDS_TCP_SEND_MSG_QUEUE, &evt);
#else
        evt.src = ITS_APP_SRC;
        if(WriteEvent(sockId, &evt) != ITS_SUCCESS)
        {   
            DIA_TRACE_CRITICAL(("SendMsg: Failed to client <%u>",msg.clientID));
        }
        ITS_EVENT_TERM(&evt);
#endif

    }

    ITS_UINT clientid = msg.clientID;

    /* Check for Duplicate client entry using transport Instance.
       Check if client (trasnport instance) is trying to register
       with the clientId already registered. */
    ITS_UINT tmpInst = sockId;
    IDS_TRANS_INFO* trnsInst = conTable.RetrieveEntry(clientid);
    if ((trnsInst != NULL) && (tmpInst != trnsInst->u.tcpInfo))
    {
        rackMsg.clientID = clientid;
        rackMsg.u.regAck.result = FAILURE;
        rackMsg.u.regAck.errorCode = IDS_CLIENT_DUPLICATE_ENTRY;
        rackMsg.u.regAck.routing_criteria = msg.u.regInfo.routing_criteria;

        ITS_EVENT evtRsp = {0,0,NULL};
        if (IDSCL_Encode(&rackMsg, &evtRsp) != ITS_SUCCESS)
        {
            return !(ITS_SUCCESS);
        }
#if _IDS_SENDER_THR
        evtRsp.src = sockId;
        TRANSPORT_PutEvent(IDS_TCP_SEND_MSG_QUEUE, &evtRsp);
#else
        evtRsp.src = ITS_APP_SRC;
        if(WriteEvent(sockId, &evtRsp) != ITS_SUCCESS)
        {
            DIA_TRACE_CRITICAL(("SendMsg: Failed to client <%u>", clientid));
        }
        ITS_EVENT_TERM(&evtRsp);
#endif

        DIA_Alarm(15050, __FILE__, __LINE__, "ClientId =%d: EC =%d", 
                  clientid, rackMsg.u.regAck.errorCode);
        return !(ITS_SUCCESS);
    }

    ITS_INT ret = IsClientAllowed(&msg);

    if (ret == ITS_SUCCESS)
    {
        ClientRoutingInfo* info = 
            (ClientRoutingInfo*) calloc(1, sizeof(ClientRoutingInfo));
        if (info == NULL)
        {
            throw "Error: memory allocation failed";
        }

        info->clientID = clientid;
        info->regInfo = msg.u.regInfo;
        tableInfo.type = IDS_TCP;
        tableInfo.u.tcpInfo = sockId;
       
        // Populate the list of route info 
        routeTable.InsertEntry(info);

        // Insert the clientID v/s socket instance in hash map
        // insert only if early not inserted
        if (trnsInst == NULL)
        {
            conTable.InsertEntry(clientid, &tableInfo );
        }

        DIA_TRACE_DEBUG(("Register: client id v/s socket instance <%d> <%d>", 
                                             clientid, sockId));

        rackMsg.clientID = clientid;
        rackMsg.u.regAck.result = SUCCESS;
        rackMsg.u.regAck.errorCode = 0;
        rackMsg.u.regAck.routing_criteria = msg.u.regInfo.routing_criteria;
    
        DIA_TRACE_DEBUG(("Register: Ack from server ip %s port %d type %d",
                                      rackMsg.u.regAck.ipAddr, 
                                      rackMsg.u.regAck.port,
                                      rackMsg.u.regAck.conType));

        DIA_Alarm(15052, __FILE__, __LINE__, "ClientId=%d:AppId=%d:IP=%s",
                  clientid,msg.u.regInfo.appIdentifier,rackMsg.u.regAck.ipAddr); 
        free (info);
        info = NULL;

        return SendMsg(&rackMsg);
    }
    else
    {
        rackMsg.clientID = clientid;
        /* If appId is already registered, return a success */
        rackMsg.u.regAck.result = (ret == IDS_APP_ID_REGISTERED_ALREADY) ?
            SUCCESS : FAILURE;
        rackMsg.u.regAck.errorCode = ret;
        rackMsg.u.regAck.routing_criteria = msg.u.regInfo.routing_criteria;

        DIA_Alarm(15050, __FILE__, __LINE__, "ClientId =%d: EC=%d", 
                  clientid, rackMsg.u.regAck.errorCode);

        ITS_EVENT evt = {0,0,NULL};
        if (IDSCL_Encode(&rackMsg, &evt) != ITS_SUCCESS)
        {
            return !(ITS_SUCCESS);
        }
#if _IDS_SENDER_THR
        evt.src = sockId;
 
        TRANSPORT_PutEvent(IDS_TCP_SEND_MSG_QUEUE, &evt);
#else
        evt.src = ITS_APP_SRC;
        if(WriteEvent(sockId, &evt) != ITS_SUCCESS)
        {
            DIA_TRACE_CRITICAL(("SendMsg: Failed to client <%u>", clientid));
        }
        ITS_EVENT_TERM(&evt);
#endif

        return !(ITS_SUCCESS);
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
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    12-04-07   BridgeWater Issue  Detect Duplicate client entry
 *                                             using transport Instance.
 *
 ****************************************************************************/
    ITS_INT
ClientHandler::RegisterUdp(TPOOL_THREAD *thr, ITS_EVENT *evt)
{
    engine::Worker* worker = (engine::Worker*)thr;
    IDS_MESSAGE msg;
    IDS_MESSAGE rackMsg;

    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    ITS_CHAR isDccaEnb = diaFrame->IsDccaEnabled();
    IDS_DEST_INFO dInfo;
    IDS_TRANS_INFO tableInfo;

    DIA_TRACE_DEBUG((" ClientHandler: Register UDP Port %d", servUdpPort));

    rackMsg.msg_type = REGISTER_ACK_MSG;
    strncpy(rackMsg.u.regAck.ipAddr, servAddr, 15); //calling risky function with fixed length of ipAddr as 15
    rackMsg.u.regAck.port = servUdpPort;
    rackMsg.u.regAck.conType = GetConnectionType();
    rackMsg.u.regAck.isDccaEnbl = isDccaEnb;

    HandleUdpRegMsg(dInfo);

    if (IDSCL_Decode(&msg, evt) != ITS_SUCCESS)
    {
        rackMsg.clientID = msg.clientID;
        rackMsg.u.regAck.result = FAILURE;
        rackMsg.u.regAck.errorCode = IDS_REGISTRATION_DECODE_FAIL;
        rackMsg.u.regAck.routing_criteria = IDS_APP_IDENTIFIER;

        DIA_Alarm(15050, __FILE__, __LINE__, "ClientId =%d : EC=%d", 
                  msg.clientID, rackMsg.u.regAck.errorCode);

        ITS_EVENT evt = {0,0,NULL};
        if (IDSCL_Encode(&rackMsg, &evt) != ITS_SUCCESS)
        {
            return !(ITS_SUCCESS);
        }
        SendMsgToDest(&dInfo, &evt);

    }

    ITS_UINT clientid = msg.clientID;

    /* Check for Duplicate client entry using transport Instance.
       Check if client (trasnport instance) is trying to register
       with the clientId already registered. */
    ITS_UINT tmpInst = worker->GetInstance();
    IDS_TRANS_INFO *  trnsInst = conTable.RetrieveEntry(clientid);
    if ((trnsInst != NULL) && 
        ((strcmp(trnsInst->u.udpInfo.ipAddr, dInfo.ipAddr)!=0) ||
         (trnsInst->u.udpInfo.port != dInfo.port)))
    {
        rackMsg.clientID = clientid;
        rackMsg.u.regAck.result = FAILURE;
        rackMsg.u.regAck.errorCode = IDS_CLIENT_DUPLICATE_ENTRY;
        rackMsg.u.regAck.routing_criteria = msg.u.regInfo.routing_criteria;

        DIA_Alarm(15050, __FILE__, __LINE__, "ClientId =%d:EC=%d", 
                  clientid, rackMsg.u.regAck.errorCode);

        ITS_EVENT evtRsp = {0,0,NULL};
        if (IDSCL_Encode(&rackMsg, &evtRsp) != ITS_SUCCESS)
        {
            return !(ITS_SUCCESS);
        }

        SendMsgToDest(&dInfo, &evtRsp);

        return !(ITS_SUCCESS);
    }

    ITS_INT ret = IsClientAllowed(&msg);

    if (ret == ITS_SUCCESS)
    {
        ClientRoutingInfo* info =
            (ClientRoutingInfo*) calloc(1, sizeof(ClientRoutingInfo));
        if (info == NULL)
        {
            throw "Error: memory allocation failed";
        }

        info->clientID = clientid;
        info->regInfo = msg.u.regInfo;
        tableInfo.type = IDS_UDP;
        tableInfo.u.udpInfo = dInfo;

        // Populate the list of route info
        routeTable.InsertEntry(info);

        // Insert the clientID v/s socket instance in hash map
        // insert only if early not inserted
        if (trnsInst == NULL)
        {
            conTable.InsertEntry(clientid, &tableInfo);
        }

        HeartBeatHandler* hb = HeartBeatHandler::GetHeartBeatHandler();

        DIA_TRACE_DEBUG(("Insert Value",clientid));
        hb->GetUdpTable().InsertEntry(clientid);

        DIA_TRACE_DEBUG(("Register: client id v/s socket instance <%d> <%d>",
                    clientid, worker->GetInstance()));

        rackMsg.clientID = clientid;
        rackMsg.u.regAck.result = SUCCESS;
        rackMsg.u.regAck.errorCode = 0;
        rackMsg.u.regAck.routing_criteria = msg.u.regInfo.routing_criteria;

        DIA_TRACE_DEBUG(("Register: Ack from server ip %s port %d type %d",
                    rackMsg.u.regAck.ipAddr,
                    rackMsg.u.regAck.port,
                    rackMsg.u.regAck.conType));

        DIA_Alarm(15052, __FILE__, __LINE__, "ClientId=%d:AppId=%d:IP=%s",
                  clientid,msg.u.regInfo.appIdentifier,rackMsg.u.regAck.ipAddr); 
        free (info);
        info = NULL;
        return SendMsg(&rackMsg);
    }
    else
    {
        rackMsg.clientID = clientid;
        /* If appId is already registered, return a success */
        rackMsg.u.regAck.result = (ret == IDS_APP_ID_REGISTERED_ALREADY) ?
            SUCCESS : FAILURE;
        rackMsg.u.regAck.errorCode = ret;
        rackMsg.u.regAck.routing_criteria = msg.u.regInfo.routing_criteria;

        DIA_Alarm(15050, __FILE__, __LINE__, "ClientId =%d:EC=%d", 
                  clientid, rackMsg.u.regAck.errorCode);

        //Parse Warning - Hides existing parameter evt
        ITS_EVENT levt = {0,0,NULL};
        if (IDSCL_Encode(&rackMsg, &levt) != ITS_SUCCESS)
        {
            return !(ITS_SUCCESS);
        }

        SendMsgToDest(&dInfo, &levt);

        return !(ITS_SUCCESS);
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
ITS_INT
ClientHandler::DeRegister(ITS_INT sockId, ITS_EVENT *evt)
{
    ITS_EVENT ev = {0,0,NULL};
    IDS_MESSAGE msg;
    IDS_MESSAGE dackMsg;
    ITS_UINT clientid = 0;
    IDS_TRANS_INFO * info = NULL;

    DIA_TRACE_DEBUG(("ClientHandler: DeRegister"));

    dackMsg.msg_type = DERGISTER_ACK_MSG;

    if (IDSCL_Decode(&msg, evt) != ITS_SUCCESS)
    {
        dackMsg.u.deregAck.result = 1;
        dackMsg.u.deregAck.errorCode = 1;
        dackMsg.clientID = msg.clientID;
        dackMsg.u.deregAck.routing_criteria = IDS_APP_IDENTIFIER;

        SendMsg(&dackMsg);

        return !(ITS_SUCCESS);
    }
    else
    {
        dackMsg.clientID = msg.clientID;
        dackMsg.u.deregAck.result = 0;
        dackMsg.u.deregAck.errorCode = 0;
        dackMsg.u.deregAck.routing_criteria = msg.u.regInfo.routing_criteria;
    }

    clientid = msg.clientID;

     info = conTable.RetrieveEntry(clientid);

    // In event of duplicate de-registration
    if (info == NULL )
    {
        DIA_TRACE_WARNING(("DeRegister: Client <%d> already de-registered", 
                                                              clientid ));

        dackMsg.u.deregAck.result = 1;
        dackMsg.u.deregAck.errorCode = IDS_NOT_REGISTERED;
        dackMsg.clientID = clientid;
        dackMsg.u.deregAck.routing_criteria = msg.u.regInfo.routing_criteria;

        if (IDSCL_Encode(&dackMsg, &ev) != ITS_SUCCESS)
        {
            return !ITS_SUCCESS;
        }
  
        if (sockId)
        {
#if _IDS_SENDER_THR
            ev.src = sockId;
            TRANSPORT_PutEvent(IDS_TCP_SEND_MSG_QUEUE, &ev);
#else
            ev.src = ITS_APP_SRC;
            if(WriteEvent(sockId, &ev) != ITS_SUCCESS)
            {   
                DIA_TRACE_CRITICAL(("SendMsg: Failed to client <%u>",clientid));
            }
            ITS_EVENT_TERM(&ev);
#endif

        }
        return !(ITS_SUCCESS);
    } 

    SendMsg(&dackMsg);

    conTable.RemoveEntry(clientid);

    routeTable.RemoveEntry(clientid);

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
ITS_INT
ClientHandler::DeRegisterUdp(TPOOL_THREAD *thr, ITS_EVENT *evt)
{
    ITS_EVENT ev = {0,0,NULL};
    IDS_MESSAGE msg;
    IDS_MESSAGE dackMsg;
    ITS_UINT clientid = 0;
    IDS_TRANS_INFO * info = NULL;

    DIA_TRACE_DEBUG(("ClientHandler: DeRegisterUdp"));
    dackMsg.msg_type = DERGISTER_ACK_MSG;

    if (IDSCL_Decode(&msg, evt) != ITS_SUCCESS)
    {
        dackMsg.u.deregAck.result = 1;
        dackMsg.u.deregAck.errorCode = 1;
        dackMsg.clientID = msg.clientID;
        dackMsg.u.deregAck.routing_criteria = IDS_APP_IDENTIFIER;

        SendMsg(&dackMsg);

        return !(ITS_SUCCESS);
    }
    else
    {
        dackMsg.clientID = msg.clientID;
        dackMsg.u.deregAck.result = 0;
        dackMsg.u.deregAck.errorCode = 0;
        dackMsg.u.deregAck.routing_criteria = msg.u.regInfo.routing_criteria;
    }
    clientid = msg.clientID;

     info = conTable.RetrieveEntry(clientid);

    // In event of duplicate de-registration
    if (info == NULL )
    {
        DIA_TRACE_WARNING(("DeRegister: Client <%d> already de-registered",
                                                              clientid ));

        dackMsg.u.deregAck.result = 1;
        dackMsg.u.deregAck.errorCode = IDS_NOT_REGISTERED;
        dackMsg.clientID = clientid;
        dackMsg.u.deregAck.routing_criteria = msg.u.regInfo.routing_criteria;

        if (IDSCL_Encode(&dackMsg, &ev) != ITS_SUCCESS)
        {
            return !ITS_SUCCESS;
        }

        IDS_DEST_INFO dInfo;
        HandleUdpRegMsg(dInfo);
        SendMsgToDest(&dInfo, &ev);

        return !(ITS_SUCCESS);
    }

    SendMsg(&dackMsg);
    conTable.RemoveEntry(clientid);

    routeTable.RemoveEntry(clientid);

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
ClientList*
ClientHandler::FindBestClient(ITS_UINT appId, ITS_INT* count)
{
    ITS_UINT cid = 0;
    ITS_INT index = 0;
    ClientList* clist = NULL;

    DIA_TRACE_DEBUG(("ClientHandler: FindBestClient"));

    index = routeTable.GetSize();
    if (!index)
    {
        DIA_TRACE_ERROR(("FindBestClient: No client registered"));

        return (clist);
    } 

    clist = (ClientList*) calloc(1, sizeof(ClientList));
    if (clist)
    {
        clist->clientID = (ITS_UINT*)calloc(index, sizeof(ITS_UINT));

        if (clist->clientID)
        {
            index = routeTable.FindBestMatch(appId, clist->clientID);
        }
    }

    *count = index;

    if (!index)
    {
        free(clist->clientID);
        free(clist);

        clist = NULL;
    } 

    return (clist);
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
ITS_INT
ClientHandler::SendMsg(IDS_MESSAGE* msg)
{
    IDS_TRANS_INFO* inst = 0;
    ITS_EVENT evt = {0,0,NULL};
    ITS_INT ret = ITS_SUCCESS;

    DIA_TRACE_DEBUG(("ClientHandler: SendMsg"));

    inst = conTable.RetrieveEntry(msg->clientID);
    
    if (inst != NULL)
    {
        if (IDSCL_Encode(msg, &evt) != ITS_SUCCESS)
        {
            return !ITS_SUCCESS;
        }
        DIA_TRACE_DEBUG(("\nMessage to client event len:%d\n",evt.len));

        IDSCL_Print(evt.data, evt.len);
        
        if(inst->type == IDS_UDP)
        {
            if (SendMsgToDest(&inst->u.udpInfo, &evt) != ITS_SUCCESS)
            {
                DIA_Alarm(15103, __FILE__, __LINE__, "ClientId = %d",
                          msg->clientID);
                return !(ITS_SUCCESS);
            }
        }
        else
        {
#if _IDS_SENDER_THR
            evt.src = inst->u.tcpInfo;
            ret = TRANSPORT_PutEvent(IDS_TCP_SEND_MSG_QUEUE, &evt);
#else
            evt.src = ITS_APP_SRC;
            ret = WriteEvent(inst, &evt);
#endif      

            if (ret != ITS_SUCCESS)
            {
                if (evt.data)
                {
                    free(evt.data);
                    evt.data = NULL;
                }
                DIA_Alarm(15103, __FILE__, __LINE__,"ClientId = %d:TransId =%d",
                          msg->clientID, inst->u.tcpInfo);
                return !(ITS_SUCCESS);
            }
        }
    }
    else
    {
        DIA_TRACE_CRITICAL(("SendMsg: Failed to dispatch to client <%u>",
                             msg->clientID));

        DIA_Alarm(15103, __FILE__, __LINE__, "ClientId =%d",msg->clientID);

        return !(ITS_SUCCESS);
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
ITS_INT
ClientHandler::CleanUP(ITS_INT sockid)
{
    ITS_UINT clientID = 0;
    IDS_TRANS_INFO  info;

    DIA_TRACE_DEBUG(("ClientHandler: CleanUP"));

    info.type = IDS_TCP;
    info.u.tcpInfo = sockid;

    clientID = conTable.GetKeyFromValue(&info);


    DIA_TRACE_DEBUG(("CleanUP: Removing client id v/s socket instance "
                                      "<%d> <%d>", clientID, sockid));

    DIA_Alarm(15051, __FILE__, __LINE__, "ClientId = %d",clientID);
    if (clientID)
    {
        conTable.RemoveEntry(clientID);
        routeTable.RemoveEntry(clientID);
    }
           
    (HeartBeatHandler::GetHeartBeatHandler())->RemoveHandle(sockid);
    return (ITS_SUCCESS);
}

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
int SendUdpMsg(ITS_UINT &clientID, ITS_EVENT *evt)
{
    int nrite;
    static ITS_USHORT tmp, tmp1;
    struct sockaddr_in to;
    IDS_TRANS_INFO *info = NULL;

    DIA_TRACE_DEBUG(("SendUdpMsg"));

    info = conTable.RetrieveEntry(clientID);
    ITS_HANDLE udpHandle = ClientHandler::GetClientHandler()->GetUdpHandle(); 

    if (udpHandle == NULL)
    {
        DIA_TRACE_CRITICAL(("HandleUdpRegMsg No Transport Handle1"));
        return !ITS_SUCCESS;
    }


    DIA_TRACE_DEBUG(("SendUdpMsg %d", clientID));
    if (info)
    {

        DIA_TRACE_DEBUG(("SendUdpMsg we Find the data"));
        DIA_TRACE_WARNING(("SendUdpMsg::$$ClientId:IP:Port:: %d:%s:%d$$",
                    clientID, info->u.udpInfo.ipAddr, info->u.udpInfo.port));
        to.sin_family = AF_INET;
        to.sin_addr.s_addr = inet_addr(info->u.udpInfo.ipAddr);
        to.sin_port = htons(info->u.udpInfo.port);
    }
    else
    {
        DIA_TRACE_DEBUG(("SORRY SendUdpMsg"));
        DIA_TRACE_ERROR(("Entry not found"));
        free(evt->data);
        return !ITS_SUCCESS;
    }

    /* Write the source */
    tmp = SOCK_HToNS(evt->src);

    nrite = SOCK_Send(SOCKTRAN_SOURCE(udpHandle), (char *)&tmp, 
                     sizeof(ITS_USHORT), &to, sizeof(to));

    if (nrite != sizeof(ITS_USHORT))
    {
        free(evt->data);
        return (ITS_ESENDFAIL);
    }

    /* Write the len */
    tmp1 = SOCK_HToNS(evt->len);

    nrite = SOCK_Send(SOCKTRAN_SOURCE(udpHandle), (char *)&tmp1,
                                    sizeof(ITS_USHORT), &to, sizeof(to));

    if (nrite != sizeof(ITS_USHORT))
    {
        free(evt->data);
        return (ITS_ESENDFAIL);
    }

    nrite = SOCK_Send(SOCKTRAN_SOURCE(udpHandle), (char *)evt->data, evt->len,
            &to, sizeof(to));

    if (nrite == evt->len)
    {
        free(evt->data);
        return (ITS_SUCCESS);
    }
    free(evt->data);
    return (ITS_ESENDFAIL);
}

int SendMsgToDest(IDS_DEST_INFO *info, ITS_EVENT *evt)
{
    int nrite;
    struct sockaddr_in to;
    static ITS_USHORT tmp, tmp1;

    ITS_HANDLE udpHandle = ClientHandler::GetClientHandler()->GetUdpHandle();
    if (udpHandle != NULL)
    {
        DIA_TRACE_DEBUG(("SendMsgToDest::$$Remote IP %s PORT %d$$",
                    info->ipAddr, info->port));
        to.sin_family = AF_INET;
        to.sin_addr.s_addr = inet_addr(info->ipAddr);
        to.sin_port = htons(info->port);
    }
    else
    {
        DIA_TRACE_CRITICAL(("HandleUdpRegMsg No Transport Handle"));
        free(evt->data);
        //Suspect Double Free
        evt->data = NULL;
        return !ITS_SUCCESS;
    }

    /* Write the source */
    tmp = SOCK_HToNS(evt->src);

    nrite = SOCK_Send(SOCKTRAN_SOURCE(udpHandle), (char *)&tmp, 
                                    sizeof(ITS_USHORT), &to, sizeof(to));

    if (nrite != sizeof(ITS_USHORT))
    {
        free(evt->data);
        //Suspect Double Free
        evt->data = NULL;
        return (ITS_ESENDFAIL);
    }

    /* Write the length */
    tmp1 = SOCK_HToNS(evt->len);

    nrite = SOCK_Send(SOCKTRAN_SOURCE(udpHandle), (char *)&tmp1, 
                                    sizeof(ITS_USHORT), &to, sizeof(to));

    if (nrite != sizeof(ITS_USHORT))
    {
        free(evt->data);
        //Suspect Double Free
        evt->data = NULL;
        return (ITS_ESENDFAIL);
    }

    nrite = SOCK_Send(SOCKTRAN_SOURCE(udpHandle), (char *)evt->data, evt->len,
            &to, sizeof(to));

    if (nrite == evt->len)
    {
        free(evt->data);
        //Suspect Double Free
        evt->data = NULL;
        return (ITS_SUCCESS);
    }
    free(evt->data);
    //Suspect Double Free
    evt->data = NULL;
    return (ITS_ESENDFAIL);
}

int HandleUdpRegMsg(IDS_DEST_INFO &dInfo)
{
    ITS_CHAR addr[16];
    ITS_INT port;
    struct sockaddr_in *sockAddr;

    addr[0]= 0;

    memset(&dInfo,0,sizeof(IDS_DEST_INFO));

    DIA_TRACE_DEBUG(("HandleUdpRegMsg"));

    ITS_HANDLE udpHandle = ClientHandler::GetClientHandler()->GetUdpHandle();

    if (udpHandle == NULL)
    {
        DIA_TRACE_CRITICAL(("HandleUdpRegMsg No Transport Handle1"));
        return !ITS_SUCCESS;
    }
    sockAddr = (struct sockaddr_in *)SOCKTRAN_CONNECT(udpHandle)->addr;

    SOCK_IPv4AddrToName(addr, SOCK_NToHL(sockAddr->sin_addr.s_addr));
    port = SOCK_NToHS(sockAddr->sin_port);

    memcpy(dInfo.ipAddr, addr, strlen(addr));
    dInfo.port = port;
    DIA_TRACE_WARNING(("HandleUdpRegMsg::$$Remote IP %s PORT %d$$",
                dInfo.ipAddr, dInfo.port));

    return ITS_SUCCESS;
}

ITS_INT
ClientHandler::ProcessGlobalUniqAddrMsg(ITS_EVENT* evt)
{
    ITS_INT ret = ITS_SUCCESS;
    IDS_MESSAGE msg;
    IDS_MESSAGE rackMsg;
    IDS_TRANS_INFO tableInfo;
    ITS_INT clientId = 0, i = 0;
    ClientRoutingInfo* clientInfo = NULL;

    DIA_TRACE_DEBUG(("ClientHandler: ProcessGlobalUniqAddrMsg"));

    //Initializing Uninitialized Scalar Variable
    memset(&rackMsg, 0, sizeof (IDS_MESSAGE));
    memset(&msg, 0, sizeof (IDS_MESSAGE));

    rackMsg.msg_type = GLOBAL_UNIQ_ADDR_ACK_MSG;

    IDSCL_Print(evt->data, evt->len);
    if (IDSCL_Decode(&msg, evt) == ITS_SUCCESS)
    {
        rackMsg.u.guaAck.action = msg.u.guaInfo.action;
        rackMsg.clientID = msg.clientID;
        rackMsg.u.guaAck.result = FAILURE;

        clientId = msg.clientID;
        ITS_INT ipAddr = htonl(inet_addr(msg.u.guaInfo.ipAddr));
        DIA_TRACE_DEBUG((" Global Uniq Addr = 0x4x\n", ipAddr));

        routeTable.Lock();

        clientInfo = routeTable.RetrieveEntry(clientId);
        if (clientInfo == NULL)
        {
            DIA_TRACE_ERROR(("ClientHandler::Client <%d> not found", clientId));
            goto __ERROR_;
        }
        if (msg.u.guaInfo.action == IDS_GUA_ADD)
        {
            /* Update Global Uniq Address */ 
            for(i=0; i<IDS_GUA_LIST_SIZE; i++)
            {
                if(clientInfo->guaList[i] == NULL)
                {
                    break;
                }
            }
            if (i<IDS_GUA_LIST_SIZE)
            {
                IDS_GUA_ENTRY *guaEntry = 
                             (IDS_GUA_ENTRY*)calloc(1, sizeof(IDS_GUA_ENTRY));

                //guaEntry->appId = clientInfo->regInfo.appIdentifier;
                guaEntry->startIp = ipAddr;
                guaEntry->endIp = ipAddr+msg.u.guaInfo.count; 

                clientInfo->guaList[i] = guaEntry;
                clientInfo->guaEntryCount++;
                rackMsg.u.guaAck.result = SUCCESS;
            }
        }
        else if (rackMsg.u.guaInfo.action == IDS_GUA_DEL)
        {
            for(int i=0; i<IDS_GUA_LIST_SIZE; i++)
            {
                if(clientInfo->guaList[i] != NULL)
                {
                    IDS_GUA_ENTRY *ent = clientInfo->guaList[i];
                    if (ent->startIp == ipAddr)
                    {
                       clientInfo->guaList[i] = NULL;
                       free(ent);
                       clientInfo->guaEntryCount--;
                       rackMsg.u.guaAck.result = SUCCESS;
                       break;
                    }
                }
            }
            
        }
        else
        {
            DIA_TRACE_ERROR(("ClientHandler::Invalid msg action"));
            rackMsg.u.guaAck.result = FAILURE;
        }
    }
    else
    {
        DIA_TRACE_ERROR(("ClientHandler:: Decode failed"));
        rackMsg.u.guaAck.result = FAILURE;
    }

__ERROR_:
    routeTable.Unlock();
    return SendMsg(&rackMsg);
}
