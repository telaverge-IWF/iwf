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
 * ID: $Id: ids_msghandler.cpp,v 3.31.6.4.6.1.4.1.22.1 2020/02/14 11:36:10 jkchaitanya Exp $
 * LOG: $Log: ids_msghandler.cpp,v $
 * LOG: Revision 3.31.6.4.6.1.4.1.22.1  2020/02/14 11:36:10  jkchaitanya
 * LOG: TCP Timeout fix ported from DRE
 * LOG:
 * LOG: Revision 3.31.6.4.6.1.4.1  2013/07/31 07:20:15  vsarath
 * LOG: Fix for coverity warnings
 * LOG:
 * LOG: Revision 3.31.6.4.6.1  2013/02/27 08:49:06  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.31.6.4  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.31.30.2  2012/11/20 10:16:59  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.31.30.1  2012/11/06 09:46:18  millayaraja
 * LOG: merge from B-DRE-0212-00 branch
 * LOG:
 * LOG: Revision 3.31.6.1  2012/11/05 12:10:37  pramana
 * LOG: Fix for coverity issue 10568
 * LOG:
 * LOG: Revision 3.31.24.1  2012/11/05 10:17:41  ncshivakumar
 * LOG: iCoverity Fixes
 * LOG:
 * LOG: Revision 3.31  2010/09/22 05:27:27  nvijikumar
 * LOG: GlobalUniqueAddr based routing/distribution support
 * LOG:
 * LOG: Revision 3.30  2010/08/19 11:23:06  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 3.29  2009/08/24 11:43:15  rajeshak
 * LOG: Fix for Issue 2317(ACTIVE COLD REDUNDANCY::IDC not able to send
 * LOG: messages to ACTIVE server)
 * LOG:
 * LOG: Revision 3.28  2009/07/13 05:57:27  rajeshak
 * LOG: Reverting back session table changes.
 * LOG:
 * LOG: Revision 3.27  2009/06/29 14:40:25  rajeshak
 * LOG: 1. Changes done for performance enhancement (splitting the session table).
 * LOG: 2. Moved GetSessionId Function to DiaUtils.
 * LOG:
 * LOG: Revision 3.26  2009/04/10 06:39:24  sureshj
 * LOG: Removed compilation flag HMI_ENABLE, added dynamic configuration.
 * LOG:
 * LOG: Revision 3.25  2009/04/07 14:02:20  sureshj
 * LOG:  Changes for HMI and Overload Control added.
 * LOG:
 * LOG: Revision 3.24  2009/03/19 12:46:57  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.23  2009/03/19 08:10:18  nvijikumar
 * LOG: Reverting back HMI changes (App hangs and drop in TPS)
 * LOG:
 * LOG: Revision 3.22  2009/03/16 11:46:53  sureshj
 * LOG: FeatureId: HMI Enhancement for monitoring raw threads.
 * LOG: Description: Threads added to HMI for monitoring hung thread.
 * LOG:
 * LOG: Revision 3.21  2009/03/03 11:10:47  rajeshak
 * LOG: Klockwork reported issue fix
 * LOG:
 * LOG: Revision 3.20  2009/03/03 10:32:42  nvijikumar
 * LOG: 1. Moved incoming msg decode to stack downstream thread scope
 * LOG: 2. Using PutEventReference for better performance
 * LOG:
 * LOG: Revision 3.19  2009/02/19 09:37:39  nvijikumar
 * LOG: Setting ptr to delete the encoded buffer of BaseCommand
 * LOG:
 * LOG: Revision 3.18  2009/02/12 04:11:36  nvijikumar
 * LOG: Changed signature for ProcessDiaStackMsg and ProcessAppMsg
 * LOG:  - Changed C++ ITS Event to C EVENT
 * LOG:
 * LOG: Revision 3.17  2009/01/07 07:19:42  nvijikumar
 * LOG: Print TPS if MOTO_PERF_PRINT defined exists
 * LOG:
 * LOG: Revision 3.16  2008/12/22 12:36:45  rajeshak
 * LOG: IssueID:1360
 * LOG: FeatureID:none
 * LOG: Description: Fix for Memory Leak.
 * LOG: (in error scenario encoded buffer was not getting deleted)
 * LOG:
 * LOG: Revision 3.15  2008/12/13 01:34:31  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.14  2008/11/28 13:50:17  ssaxena
 * LOG: Issue ID: 1327
 * LOG: Feature ID: None
 * LOG: Description: Discarding the Message if the Node is Backup.
 * LOG:
 * LOG: Revision 3.13  2008/11/19 11:38:34  ssaxena
 * LOG: Fix for Issue:: 1223 ( Unable to recognize any indication sent by IDS)
 * LOG:
 * LOG: Revision 3.12  2008/11/13 06:15:56  nvijikumar
 * LOG: IssueID:None
 * LOG: FeatureID:None
 * LOG: Description:E-Bit requirement is no longer valid, reverting back
 * LOG:             Changes
 * LOG:
 * LOG: Revision 3.11  2008/11/10 14:41:17  ssaxena
 * LOG: Multicasting the E-Bit set Answer to all clients registered with same
 * LOG: Application ID. Motorola specific feature as a part of 3.1.1 release.
 * LOG:
 * LOG: Revision 3.10  2008/11/06 07:17:27  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Incorporating Yogesh's Comment renaming StackTunning
 * LOG:              with QueueMgmt
 * LOG:
 * LOG: Revision 3.9  2008/10/31 05:35:24  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID: none
 * LOG: Description: 1. Introducing additional TQs and Threads for better
 * LOG:                 Performance on PP50 and initial stack tunning
 * LOG:              2. Unwanted code cleanup
 * LOG:
 * LOG: Revision 3.8  2008/09/08 11:33:31  ssaxena
 * LOG: Handled the Redundancy events using new source in Execute(). Also added
 * LOG: additional checks to verify that instance is Active before sending Ind.
 * LOG:
 * LOG: Revision 3.7  2008/08/25 05:54:09  ssaxena
 * LOG: Changes handle Failover/Failback indications
 * LOG:
 * LOG: Revision 3.6  2008/08/06 15:44:56  ssaxena
 * LOG: Fixed memory leak by moving the code in the ProcessDiaStackMsg().
 * LOG:
 * LOG: Revision 3.5  2008/07/23 14:11:24  ssaxena
 * LOG: Added Disconect Cause in Disconect indication
 * LOG:
 * LOG: Revision 3.4  2008/07/08 09:28:59  ssaxena
 * LOG: Change in ProcessDiaStackMsg for broadcasting disconnect indication
 * LOG: to all clients and for other indications without clientID are sent
 * LOG: to the appropriate clientID found using appID.
 * LOG:
 * LOG: Revision 3.3  2008/04/21 11:52:56  hbhatnagar
 * LOG: partial fix for the issue 846 in whizible where the indication sent to
 * LOG: IDC does not have proper client id. Getting client ID for indication
 * LOG: and sending it.
 * LOG:
 * LOG: Revision 3.2  2008/04/16 13:03:20  hbhatnagar
 * LOG: Fix for issue 785 in whizible. Sending error response properly with
 * LOG: ProxyInfoAVP
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.23  2008/03/27 11:21:05  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.21.2.1  2007/05/25 12:33:22  hbhatnagar
 * LOG: made changes in SendErrToPeer for not sending error response in case of answer
 * LOG:
 * LOG: Revision 2.21  2007/02/26 09:35:53  nvijikumar
 * LOG:  Fix for error response with appropriate appId.
 * LOG:
 * LOG: Revision 2.20  2007/01/22 12:27:33  kamakshilk
 * LOG: Minor change in check for Indication
 * LOG:
 * LOG: Revision 2.19  2007/01/04 11:29:55  nvijikumar
 * LOG: Accounting Statemachine changes.
 * LOG:
 * LOG: Revision 2.18  2006/12/12 14:14:45  kamakshilk
 * LOG: To sent peer based messages to all clients
 * LOG:
 * LOG: Revision 2.17  2006/12/11 04:50:00  kamakshilk
 * LOG: Added check if timeout Indications contain clientId
 * LOG:
 * LOG: Revision 2.16  2006/11/30 05:31:44  kamakshilk
 * LOG: Length correction for Indications sent to client
 * LOG:
 * LOG: Revision 2.15  2006/11/24 15:42:58  kamakshilk
 * LOG: Changes for redundancy support
 * LOG:
 * LOG: Revision 2.14  2006/11/24 05:43:31  kamakshilk
 * LOG: Null terminated session Id received for ReleaseSession
 * LOG:
 * LOG: Revision 2.13  2006/11/17 06:33:08  kamakshilk
 * LOG: SendNotification when dframe send fails
 * LOG:
 * LOG: Revision 2.12  2006/11/17 06:02:46  kamakshilk
 * LOG: diaFrame->ReleaseSession added
 * LOG:
 * LOG: Revision 2.11  2006/11/14 08:59:31  kamakshilk
 * LOG: New architecture. Session looks up removed. Round robin added
 * LOG:
 * LOG: Revision 2.10  2006/11/08 14:57:35  kamakshilk
 * LOG: Corrected sIdx value required for DCCA
 * LOG:
 * LOG: Revision 2.9  2006/11/08 08:30:45  kamakshilk
 * LOG: rxAddr changed to ULONG from UINT
 * LOG:
 * LOG: Revision 2.8  2006/11/08 06:12:41  kamakshilk
 * LOG: Changes for 64-bit support. ITS_ULONG changed to ITS_UINT
 * LOG:
 * LOG: Revision 2.7  2006/10/31 10:05:32  kamakshilk
 * LOG: IDSCL_Print function added
 * LOG:
 * LOG: Revision 2.6  2006/10/29 06:16:47  kamakshilk
 * LOG: Handle and route indications to client
 * LOG:
 * LOG: Revision 2.5  2006/10/26 05:52:13  kamakshilk
 * LOG: Routing request on sesIdx for entries found in SessionTable
 * LOG:
 * LOG: Revision 2.4  2006/10/24 11:40:34  kamakshilk
 * LOG: Added clntSesInfo==NULL check for answers
 * LOG:
 * LOG: Revision 2.3  2006/10/17 18:28:26  yranade
 * LOG: Update to use setSessionIndex.
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:17:44  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.13  2006/09/06 11:22:00  kamakshilk
 * LOG: Fix for bug Id 3615,4287. Added the IntToData and DataToInt APIs for encode and decode
 * LOG:
 * LOG: Revision 1.12  2006/08/08 04:44:06  kamakshilk
 * LOG: Fix for Bug Ids 4111,4112 and 4118
 * LOG:
 * LOG: Revision 1.11  2006/06/29 08:11:37  kamakshilk
 * LOG: Insertion of Session Index in sTable when request received from Peer
 * LOG:
 * LOG: Revision 1.10  2006/06/26 09:31:11  adutta
 * LOG: Fix of issue# 3615
 * LOG:
 * LOG: Revision 1.9  2006/06/16 12:05:16  kamakshilk
 * LOG: Fix for STR/STA sending for closed session
 * LOG:
 * LOG: Revision 1.8  2006/06/14 09:35:57  kamakshilk
 * LOG: Enhancements for sending Application Id to the client
 * LOG:
 * LOG: Revision 1.7  2006/05/23 06:18:35  adutta
 * LOG: Clearing session record on STA/Abort
 * LOG:
 * LOG: Revision 1.6  2006/05/19 12:17:57  adutta
 * LOG: Fixed issue#3799
 * LOG:
 * LOG: Revision 1.5  2006/04/06 07:45:57  adutta
 * LOG: Replacement of Ses-Id/Idx and related changes
 * LOG:
 * LOG: Revision 1.4  2006/03/14 06:40:39  adutta
 * LOG: Incorporated dframe changes
 * LOG:
 * LOG: Revision 1.3  2006/03/13 05:17:05  adutta
 * LOG: Check event message types from stack
 * LOG:
 * LOG: Revision 1.2  2006/03/06 13:16:21  adutta
 * LOG: Impl. APP_SRC
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:47:51  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/
#ident "$Id: ids_msghandler.cpp,v 3.31.6.4.6.1.4.1.22.1 2020/02/14 11:36:10 jkchaitanya Exp $"

#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <diameter/base/Accounting.h>

#include <its++.h>

#include <itsdiameter.h>
#include <dia_frame.h>
#include <dia_config.h>
#include <dia_defines.h>
#include <dia_trace.h>
#include <dia_utils.h>

#include <ids_msghandler.h>
#include <ids_routedb.h>

IDS_ROUTING_SCHEME routeScheme = IDS_ROUND_ROBIN;

extern RouteTable routeTable;

using namespace diameter;
using namespace diameter::base;

extern MsgHandler* msgHandler;
ITSDiaConfig *cfgn = &itsDiaConfig;

AppToStackMsgHandler::AppToStackMsgHandler()
{
    DIA_TRACE_DEBUG(("AppToStackMsgHandler: AppToStackMsgHandler"));

    keepGoing = ITS_TRUE;

    msgQ_ = new its::TaskQueueTransport (
                  "MSG Queue", IDS_APP_TO_STACK_MSG_QUEUE, ITS_TRANSPORT_TQUEUE);

    ITS_THROW_ASSERT (msgQ_ != NULL);
    TRANSPORT_IS_ACTIVE(msgQ_->GetTC()) = ITS_TRUE;
}
AppToStackMsgHandler::~AppToStackMsgHandler()
{
    TRANSPORT_Control* tc;

    DIA_TRACE_DEBUG(("AppToStackMsgHandler: ~AppToStackMsgHandler"));

    keepGoing = ITS_FALSE;

    tc = (TRANSPORT_Control*)msgQ_->GetTC();
    if (tc)
    {
        tc->transport.exitNow = ITS_TRUE;
    }
    TRANSPORT_IS_ACTIVE(tc) = ITS_FALSE;
    delete msgQ_;

    DIA_TRACE_DEBUG(("~AppToStackMsgHandler: Exit"));
}
int
AppToStackMsgHandler::GetQCount()
{
    int count = 0;

    if (msgQ_ != NULL)
    {
        const TRANSPORT_Control *tc = msgQ_->GetTC();
        TQUEUETRAN_Manager *tqM = (TQUEUETRAN_Manager *)tc;
        EMLIST_Manager *lm = TQUEUETRAN_EMLIST(tqM);
        count = LIST_COUNT((LIST_Manager *)(lm));
    }

    return count;
}
void
AppToStackMsgHandler::Execute()
{
    ITS_INT ret = ITS_SUCCESS;
    its::Event evt;
    ITSDiaConfig *cfg = &itsDiaConfig;

    DIA_TRACE_DEBUG(("MsgHandler: Execute"));
   
    ITS_INT thrID = THREAD_GetCurrentThreadID();
    HMI_AddToMonList(&monList, "AppToStackMsgHandler", (ITS_THREAD*)thrID);    
    while (keepGoing)
    {
        ret = msgQ_->GetNextEvent(evt);
        
        if(cfg->IsHMIEnabled())
        {
             //HMI_ResetHMIUpCount(&monList, (ITS_THREAD*)thrID);
        }

        if (ret != ITS_SUCCESS)
        {
            continue;
        }

        switch (evt.GetSource())
        {
            case ITS_APP_SRC:
            case IDS_APPDATA_SRC:
                msgHandler->ProcessAppMsg(&evt.GetEvent());
                break;
            case IDS_APP_TO_STACK_MSG_QUEUE:
                keepGoing = ITS_FALSE;
                break;
            default:
                DIA_TRACE_DEBUG(("AppToStackMsgHandler: Invalid message type"));
                break;
        }
    }
    HMI_RemoveFromMonList(&monList, (ITS_THREAD*)thrID);
}

/*impnementation:static
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
MsgHandler::MsgHandler()
{
    DIA_TRACE_DEBUG(("MsgHandler: MsgHandler"));
    keepGoing = ITS_TRUE;

    msgQ_ = new its::TaskQueueTransport (
                  "MSG Queue", IDS_MSG_QUEUE, ITS_TRANSPORT_TQUEUE);

    ITS_THROW_ASSERT (msgQ_ != NULL);
    TRANSPORT_IS_ACTIVE(msgQ_->GetTC()) = ITS_TRUE;
    cHandler_ = ClientHandler::GetClientHandler();

    DiaConfig *cfg = DiaConfig::GetDiaConfig();
                                                                                
    char *routingScheme = cfg->GetRouteScheme();
    if ( (routingScheme != NULL) && !strcmp(routingScheme, "roundrobin"))
    {
        routeScheme = IDS_ROUND_ROBIN;
    }
    else if ( (routingScheme != NULL) && !strcmp(routingScheme, "broadcast"))
    {
        routeScheme = IDS_BROADCAST;
    }
    else if ( (routingScheme != NULL) && !strcmp(routingScheme, "globaluniqueaddr"))
    {
        routeScheme = IDS_GLOBAL_UNIQ_ADDR;
    }

    didcidMutex_ = NULL;
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
MsgHandler::~MsgHandler()
{
    TRANSPORT_Control* tc;
 
    DIA_TRACE_DEBUG(("MsgHandler: ~MsgHandler"));

    keepGoing = ITS_FALSE;

    tc = (TRANSPORT_Control*)msgQ_->GetTC();
    if (tc)
    {
        tc->transport.exitNow = ITS_TRUE;
    }
    TRANSPORT_IS_ACTIVE(tc) = ITS_FALSE;
    delete msgQ_;
   
    if (cHandler_)
    {
        cHandler_->ReleaseClientHandler();
        cHandler_ = NULL;
    }

    DIA_TRACE_DEBUG(("~MsgHandler: Exit"));
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
MsgHandler::GetSessionString(ITS_OCTET* data, std::string &str)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_UINT avpCode = 0;
    ITS_UINT len = 0;
    ITS_CHAR buff[IDS_MAX_BUF_SIZE];

    DIA_TRACE_DEBUG(("MsgHandler::GetSessionString"));

    memset(buff, 0, sizeof(buff));

    // Session-Id AVP code
    avpCode |= data[IDS_DIA_SES_AVP_POS];
    avpCode |= data[IDS_DIA_SES_AVP_POS - 1] << 8;

    DIA_TRACE_DEBUG(("GetSessionString: AVP Code %d", avpCode));

    // Verify Session-Id AVP code from dump
    if (avpCode != 263)
    {
        DIA_TRACE_DEBUG(("GetSessionString: Session AVP not found"));

        //str = buff;
        str = "";

        return (ITS_ENOTFOUND);
    }

    // Session-Id AVP length
    ITS_UINT lpos = IDS_DIA_SES_AVP_POS + 4;
    len |= data[lpos];
    len |= data[lpos - 1] << 8;
    len |= data[lpos - 2] << 16;

    // "V" flag is set
    if (data[IDS_DIA_SES_AVP_POS+5] & 0x80U)
    {
         len = len - (sizeof(ITS_UINT)*3);
         memcpy(buff, &data[IDS_DIA_SES_AVP_POS+1], len);
    }
    else
    {
         len = len - (sizeof(ITS_UINT)*2);
         memcpy(buff, &data[IDS_DIA_SES_AVP_POS+5], len);
    }

    buff[len] = '\0';
    str = buff;

    DIA_TRACE_DEBUG(("GetSessionString: Session string <%s> <%d>",
                                         str.c_str(), str.size()));

    return ITS_SUCCESS;
}

int
MsgHandler::GetQCount()
{
    int count = 0;

    if (msgQ_ != NULL)
    {
        const TRANSPORT_Control *tc = msgQ_->GetTC();
        TQUEUETRAN_Manager *tqM = (TQUEUETRAN_Manager *)tc;
        EMLIST_Manager *lm = TQUEUETRAN_EMLIST(tqM);
        count = LIST_COUNT((LIST_Manager *)(lm));
    }

    return count;
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
MsgHandler::Execute()
{
    ITS_INT ret = ITS_SUCCESS;
    its::Event evt;
     ITSDiaConfig *cfg = &itsDiaConfig;   
 
    DIA_TRACE_DEBUG(("MsgHandler: Execute"));
    
    ITS_INT thrID = THREAD_GetCurrentThreadID();
    HMI_AddToMonList(&monList, "MsgHandler", (ITS_THREAD*)thrID);
    while (keepGoing)
    {
        ret = msgQ_->GetNextEvent(evt);
       
        if(cfg->IsHMIEnabled())
        {
             //HMI_ResetHMIUpCount(&monList, (ITS_THREAD*)thrID);
        }
 
        if (ret != ITS_SUCCESS)
        {
            continue;
        }

        switch (evt.GetSource())
        {
            case ITS_DIA_SRC:
                ProcessDiaStackMsg(&evt.GetEvent());
                break;
            case ITS_APP_SRC:
            case IDS_APPDATA_SRC:
                ProcessAppMsg(&evt.GetEvent());
                break;
            case IDS_MSG_QUEUE:
                keepGoing = ITS_FALSE;
                break;
            case ITS_RED_MODULE_SRC:
            /**
             * If any redundancy event is directly received 
             * from Redundancy module,ignore them.
             */
                break;
            /**
             * Added a new source for the redundancy
             * events from the Diameter stack to App.
             */
            case DIA_REDUNDANCY_SRC:
            {
                /**
                 * Added a check so that Connection up 
                 * indication is sent only from the Active
                 * Instance of the two IDS.
                 */
                ITS_NODE_STATE node;
                ITS_GetNodeState(&node);
                if(node == ITS_STATE_PRIMARY)
                {
                    cHandler_->SendServerUpInd();
                }
                break;
            }
            default:
                DIA_TRACE_DEBUG(("MsgHandler: Invalid message type"));
                break;
        }
    }
    HMI_RemoveFromMonList(&monList, (ITS_THREAD*)thrID);
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
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi      09-06-06    Enhancement     ClientID added to the  
 *                                             GenericSessionInfo structure.
 *   Kamakshi      08-08-06    Bug Id 4111,    Session table Key changed to 
 *                              4112, 4118     8 bytes.
 *   Kamakshi      08-08-06    Enhancement     Clearing sessionDB removed. 
 *   Kamakshi      06-09-06    Bug Id 3615,    Added DataToInt() for decoding
                                     4287      clientId,clIdx values.
 *   Kamakshi      14-11-06    Enhancement     1.Session lookup removed.
 *                                             2.Send notification to client.
 *
 ****************************************************************************/
ITS_INT
MsgHandler::ProcessAppMsg(ITS_EVENT* evt)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET mType = 0;
    ITS_USHORT index = 0;
    ITS_UINT clientId = 0;
    ITS_UINT appId = 0;
    ITS_UINT clIdx = 0;
    ITS_UINT sIdx = 0;
    ITS_USHORT evtLen = evt->len;
    ITS_OCTET* evtData = (ITS_OCTET*)evt->data;
    ITS_USHORT offset = 0;

    DIA_TRACE_DEBUG(("MsgHandler: ProcessAppMsg"));

    if (evt->src == IDS_APPDATA_SRC)
    {
        DiaFrame *diaFrame = DiaFrame::GetDiaFrame();

        /* Get the client ID */
        clientId = IDSCL_DataToInt(evtData+index, sizeof(ITS_UINT));
        index += sizeof(ITS_UINT);

        DIA_TRACE_DEBUG(("\n\nMessage from distributed client %d: len=%d\n",
                                                   clientId, evtLen));
        IDSCL_Print(evtData, evtLen);

        if (!clientId)
        {
            DIA_TRACE_DEBUG(("ProcessAppMsg: Invalid ClientID <%u>", clientId));
            return !ITS_SUCCESS;
        }

        /* Get client Session Index */
        /* sessIndx not used */
        //clIdx = IDSCL_DataToInt(evtData+index, sizeof(ITS_UINT));
        index += sizeof(ITS_UINT);

        /* Get  Accounting record information if ACR */
        //accRecInfo = IDSCL_DataToInt(evtData+index, sizeof(ITS_OCTET));
        index += sizeof(ITS_OCTET);

        /* Get Diameter message type */
        mType = evtData[index];
        index++;

        offset = 10; /*2*sizeof(ITS_UINT) + 2*sizeof(ITS_OCTET) */

        if (mType == IDS_DIA_MSG_TYPE_SES_RLS)
        {
            ITS_CHAR *buff = (ITS_CHAR*)&evtData[index];
            std::string sesStr = buff;
            ret = diaFrame->ReleaseSession(sesStr);

            /* Send a Notification to client if the release was 
               success or failure */
            if (ret == ITS_SUCCESS)
            {
                SendNotifyToApp(evtData, IDS_RELEASE_SESS_SUCCESS_IND ,sesStr);
            }
            else
            {
                SendNotifyToApp(evtData, IDS_RELEASE_SESS_FAIL_IND , sesStr);
            }

            return ret; 
        }
        try
        {
#if 0
            //DIA_GEN_CMD *cmd = new DIA_GEN_CMD(evtData+offset, evtLen-offset);
            BaseCommand *cmd = new BaseCommand(evtData+offset, evtLen-offset);

            if (cmd == NULL)
            {
                std::string clstr = "";
                GetSessionString(evtData+offset, clstr);

                SendNotifyToApp(evtData, IDS_SENDTO_STACK_FAIL_IND, clstr);
                return !ITS_SUCCESS;
            }
            
            cmd->setSessionIndex(sIdx);
            cmd->setClientId(clientId);
          
            if (cmd->isRequest() && (cmd->getCommandCode() == 271))
            {
                //diameter::base::AccountingRequest *acr =
                //                     (diameter::base::AccountingRequest *)cmd;

                bool storageSpaceFlag = true;
                bool lastRecFlag = false;
                /* Get last bit i.e storageSpaceFlag */
                storageSpaceFlag = (accRecInfo & 0x01);
                /* Get last but one bit i.e lastRecFlag */
                lastRecFlag = ((accRecInfo & 0x02) >> 1);

                /* Set respective flags */
                cmd->setStorageSpaceAvailable(storageSpaceFlag);
                cmd->setLastRecordInStorage(lastRecFlag);
            }

            /**
             * Partial Fix for the issue 1327. 
             * Send message to Stack only if the node is active 
             * else Discard the message.
             */
            ITSDiaConfig* cfg = ITSDiaConfig::GetITSDiaConfig();
            ITS_NODE_STATE state;
            if (cfg->IsRedundancyEnabled() &&
                (ITS_GetNodeState(&state) == ITS_SUCCESS) &&
                state != ITS_STATE_PRIMARY)
            {
                DT_ERR(("ProcessAppMsg::Node is Backup: Message can't be"\
                        "delivered to peer. Discarding Message..."));
                if (cmd != NULL)
                {
                    delete cmd;
                    cmd = NULL;
                }
                return !ITS_SUCCESS;
            }

            /*
             * Handover for stack processing
             */
            ITS_USHORT dest = DIASTACK_TQ_INST;
            if (itsDiaConfig.IsQueueMgmtEnabled())
            {
                dest = DIASTACK_SENDER_TQ_INST;
            }

            /*
             *Set Buffer in the message and set evt->data to NULL
             * to avoid multple deletes
             */
            cmd->setPtrToFreeBuf((void *)evt->data);
            evt->data = NULL;

            ITS_OCTET data[sizeof(ITS_ULONG)];
            memcpy(&data[0], &cmd, sizeof(ITS_ULONG));
            its::Event ev(DIA_APP_INST, sizeof(ITS_ULONG), data);
            ret = its::Transport::PutEvent(dest, ev);
#endif
            /*
             * Handover for stack processing
             */
            ITS_USHORT dest = DIASTACK_TQ_INST;
            if (itsDiaConfig.IsQueueMgmtEnabled())
            {
                dest = DIASTACK_SENDER_TQ_INST;
            }

            evt->src = DIA_IDS_APP_INST;
            ret = DiaUtils::PutEventReference(dest, evt);
  
            /* Send Notification to the client indicating 
               the failure to deliver the message to stack */
            if (ret != ITS_SUCCESS)
            {
                std::string clstr = "";
                GetSessionString(evtData+offset, clstr);

                SendNotifyToApp(evtData, IDS_SENDTO_STACK_FAIL_IND, clstr); 
#if 0
                if (cmd != NULL)
                {
                    delete cmd;
                    cmd = NULL;
                }
#endif

            }
        }
        catch(...)
        {
            DIA_TRACE_DEBUG(("ProcessAppMsg: Encode error"));

            /* Send Notification to the client indicating 
               the failure to deliver the message to stack */
            std::string clstr = "";
            GetSessionString(evtData+offset, clstr);

            SendNotifyToApp(evtData, IDS_MSG_ENCODE_FAIL_IND , clstr);

        }

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
IDS_REGISTER*
MsgHandler::GetRouteInfo(const ITS_UINT appId)
{
    ITS_INT index ;
    IDS_REGISTER* tc = NULL;

    DIA_TRACE_DEBUG(("MsgHandler: GetRouteInfo"));

    tc = (IDS_REGISTER*)calloc(1, sizeof(IDS_REGISTER));
    if (tc == NULL)
    {
        throw "Error: memory allocation failed";
    }

    tc->appIdentifier = appId;
    
    DIA_TRACE_DEBUG(("GetRouteInfo: AppId <%d>", tc->appIdentifier));

    return (tc);
}

void
MsgHandler::ProcessRedundancyMsg(ITS_EVENT* evt)
{
    ITS_NODE_STATE node;
    ITS_GetNodeState(&node);
    if(node == ITS_STATE_PRIMARY)
    {
        cHandler_->SendServerUpInd();
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
 *   Kamakshi      09-06-06   Enhancement    Route answers on SessionIdx 
 *   Abhijit       14-06-06   Enhancement    Send AppId to client 
 *   Kamakshi      08-08-06   Bug Id 4111,   Session table Key changed to 
 *                             4112, 4118    8 bytes. 
 *   Kamakshi      08-08-06   Enhancement    Clearing peer initiated session.
 *   Kamakshi      06-09-06   Bug Id 3615,   Added IntToData() for encoding
                                     4287    clntSesIdx,appId values.
 *   Kamakshi      26-10-06   Enhancement    Route request on SessionIdx for
                                             entries found in SessionTable.
 *   Kamakshi      29-10-06   Enhancement    Handle & Route Indication to clnt.
 *   Kamakshi      08-11-06   Enhancement    rxAddr changed fom UINT to ULONG 
                                             for 64-bit compatibility.
 *   Kamakshi      14-11-06   Enhancement    1.Round robin routing added.
 *                                           2.Session lookup removed.
 *                                           3.Send Error msg to peer.
 *                                           4.Changed to ProcessDiaStackMsg.
 *
 ****************************************************************************/
ITS_INT 
MsgHandler::ProcessDiaStackMsg(ITS_EVENT* evt)
{
    ITS_INT ret  = ITS_SUCCESS;
    ITS_INT index = 0;
    ITS_UINT sIdx = 0;
    IDS_MESSAGE msg;
    ITS_OCTET* txBuff = NULL;
    ITS_UINT appId = 0;
    ITS_BOOLEAN isRequest = ITS_FALSE;
    ITS_UINT clntId = 0;
    ITS_UINT Code = 0;
    ITS_INT evtLen = evt->len;
    ITS_OCTET *evtData = (ITS_OCTET*)evt->data;
    ITS_INT enLen = 0;
    ITS_ULONG rxAddr = 0;
    BaseCommand *rxCmd = NULL;
    ITS_OCTET *enBuf = NULL;
    ITS_UINT* clist = NULL;
    ITS_UINT count  = 0;
    ITS_OCTET indication = 0; 
    DIA_TRACE_DEBUG(("MsgHandler: ProcessDiaStackMsg Msglen = %d", evtLen));

    memset(&msg, 0, sizeof(IDS_MESSAGE));

    IDSCL_Print(evtData, evtLen);

    /* Get Session Index */
    /* SessIndx Not used */
     //sIdx = IDSCL_DataToInt(evtData+1);
    /* Get App Id */
    appId = IDSCL_DataToInt(evtData+5);

    /* Routing Indications (timeout indications) to the Client. 
       The last four bytes are the Client Id. */
    if (evtData[0] == ITS_DIA_MSG_TYPE_IND)
    {
        /** 
         * Memory leak Fix (Start). 
         * Moved code inside the IND TYPE 
         */
        ITS_UINT indLen = evtLen - sizeof(ITS_UINT);
        /* Retrieve ClientID from the last four bytes */
 
        clntId = IDSCL_DataToInt(evtData+indLen);

        msg.msg_type = DIAMETER_MSG;
        msg.u.diaInfo.len = evtLen-IDS_DIA_MSG_POS;
        msg.u.diaInfo.data = evtData+IDS_DIA_MSG_POS;
        msg.u.diaInfo.msgType = evtData[0];
        msg.u.diaInfo.sessIdx = sIdx;
        msg.u.diaInfo.appId   = appId;

        /* Memory leak Fix (End).*/

        /* Get the Indication from Event */   
        indication = evtData[IDS_DIA_MSG_POS];
        DIA_TRACE_DEBUG(("ProcessDiaStackMsg: Received Indication <%d>",
                                                evtData[IDS_DIA_MSG_POS]));
 
        /* Check if ClientID is present in the Indication */
        ITS_CHAR *sessBuff = (ITS_CHAR*)&evtData[IDS_DIA_MSG_POS+1];
        //std::string sesStr = sessBuff;
        if ((evtLen <= (IDS_DIA_MSG_POS + 1 + strlen(sessBuff)+1))  ||
            (indication == INVALID_AVP_LEN_ERR_IND_FROM_STACK))
        {

            /* Check indication is disconnect then Broadcast the indication
             * to all clients. 
             */ 
           if (indication == DISCONECT_IND_FROM_STACK ||
               indication == FAILOVER_IND_FROM_STACK ||
               indication == FAILBACK_IND_FROM_STACK ||
               indication == OVERLOAD_IND_FROM_STACK || 
               indication == OVLD_ABATED_IND_FROM_STACK ||
	       indication == PEER_CONG_START_IND_FROM_STACK ||
	       indication == PEER_CONG_ABATE_IND_FROM_STACK ||
               ((indication == TIME_OUT_IND_FROM_STACK) &&
               (clntId != 0)) ||
               ((indication == AUTH_LIFE_TIME_OUT_IND_FROM_STACK) &&
               (clntId != 0)))
           {
                /* Re-intialize right length */
                msg.u.diaInfo.len = evtLen;

                if (indication == TIME_OUT_IND_FROM_STACK ||
                    indication == AUTH_LIFE_TIME_OUT_IND_FROM_STACK)
                {
                    clist = routeTable.GetAllEntries(appId, count);
                }
                else
                {
                    /* Route message to all the client , irrespective
                     of the AppId they have registered with */
                    clist = routeTable.GetAllEntries(count);
                }

                DIA_TRACE_DEBUG(("ProcessDiaStackMsg:Sending Indication to" \
                               "  %d clients", count));
 
                if (count)
                {
                  for (ITS_INT i = 0; i < count; i++)
                  {
                    msg.clientID = clist[i];
                    ret = cHandler_->SendMsg(&msg);
                    if (ret != ITS_SUCCESS)
                    {
                        ret = (ITS_ENOTFOUND);
                        free(clist);
                        clist = NULL;
                        if (txBuff != NULL)
                        {
                            delete []txBuff;
                            txBuff = NULL;
                        }
                        return ret;
                    }
                  }
 
                  free(clist);
                  clist = NULL;
                  if (txBuff != NULL)
                  {
                      delete []txBuff;
                      txBuff = NULL;
                  }
                  return ret;               
                }
                /**
                 * Added error scenario.
                 */
                else
                {
                    DT_ERR(("No Client(s) to send the Indication."));

                    //Fixing Resource leak
                    if (clist != NULL)
                    {
                       free(clist);
                       clist = NULL;
                    }
                    if (txBuff != NULL)
                    { 
                        delete []txBuff;
                        txBuff = NULL;
                    }
                    ret = (ITS_ENOTFOUND);
                    return ret;
                }
           }
            /**
             * If indication is other than DISCONECT_IND_FROM_STACK then 
             * find appropriate clientId from AppId and send the indication  
             * to the same. If client ID is not found return error.
             */
          else
          {
            if (routeTable.GetSize() == 0)
            {
               DIA_TRACE_ERROR(("ProcessDiaStackMsg: No clients"));
               ret = ITS_ENOTFOUND;
            }
            else if (!(clntId = routeTable.FindBestMatch(appId)))
            {
               DIA_TRACE_DEBUG(("ProcessDiaStackMsg:No matching clients"));
               ret = ITS_ENOTFOUND;
            }
            else
            {
               DIA_TRACE_DEBUG(("ProcessDiaStackMsg:Sending Ind to client %d",
                                      clntId));
 
               msg.clientID = clntId;
               ret = cHandler_->SendMsg(&msg);
            }
           
            if (txBuff != NULL)
            { 
               delete []txBuff;
                txBuff = NULL;
            }
            return ret;  
          }
         
        }

        /** 
         * Here means the Client id in the indication is present.
         * Copy the clientId from Indication to msg. 
         */
        DIA_TRACE_DEBUG(("ProcessDiaStackMsg:Sending Ind to client %d",
                          clntId));
        msg.clientID = clntId;

        ret = cHandler_->SendMsg(&msg);
        if (txBuff != NULL)
        {
            delete []txBuff;
            txBuff = NULL;
        }
        return ret;
    }

    /* If MsgType is DATA or IND_WITH_DATA,
       Get the address of diameter::command object from the event */
    memcpy(&rxAddr, evtData+IDS_DIA_MSG_POS, sizeof(ITS_ULONG));
    rxCmd = (BaseCommand*)rxAddr;

    if (!rxCmd)
    {
        DIA_TRACE_ERROR(("ProcessDiaStackMsg: No Diameter Message"));

        return (ITS_ENOTFOUND); 
    }

    isRequest = rxCmd->isRequest();

    /* Get Command Code */
    Code = rxCmd->getCommandCode();

    /* ITS_DIA_MSG_TYPE_IND_WITH_DATA is received in case of error responses.
       The last four bytes are the Client Id. */
    if (evtData[0] == ITS_DIA_MSG_TYPE_IND_WITH_DATA)
    {
        if (evtLen == (IDS_DIA_MSG_POS + sizeof(ITS_ULONG)))
        {
            DIA_TRACE_DEBUG(("ProcessDiaStackMsg: No ClientID."));
            clntId = 0;
        }
        else
        {
            clntId = IDSCL_DataToInt(evtData+evtLen-sizeof(ITS_UINT));
        }

        /* Stack gives this event when the Peer has 
           established or disconnected a connection */
        if (Code == DIA_MSG_CE || Code == DIA_MSG_DP) 
        {
            /* Send the Peer status message to all the clients */
            SendPeerBasedMsgToApp(rxCmd, evtData);

            delete rxCmd;
            rxCmd = NULL;

            return ITS_SUCCESS;
        }
    }
    else
    {
        /* For Event Type ITS_DIA_MSG_TYPE_IND, the client Id is 
           retrieved from the BaseGenericCommand Object */
        clntId = rxCmd->getClientId();
    }
 
    /* Encode the Command */
    //CommandImplDerived& ImplDer = (CommandImplDerived&)rxCmd->getImpl();
    enBuf = (ITS_OCTET*)rxCmd->getEncodedBuf();
    if (enBuf != NULL)
    {
       enLen  = rxCmd->getEncodedBufLen();
       ret = ITS_SUCCESS;
    }
    else
    {
        ret = !ITS_SUCCESS;
        DIA_TRACE_DEBUG(("Error: Invalid Encoded buffer"));
    }

    if (ret != ITS_SUCCESS || enBuf == NULL || enLen == 0)
    {
        DIA_TRACE_ERROR(("ProcessDiaStackMsg:: Diameter encode fail"));
                                                                                
        /* Form a error message to be sent to the peer */
        SendErrToPeer(rxCmd, ITS_DIA_UNABLE_TO_DELIVER);

        delete rxCmd;
        rxCmd = NULL;

        return (ITS_ENOTFOUND);
    }
#if 0
    txBuff = new ITS_OCTET[IDS_DIA_MSG_POS+enLen];

    /* Copy MsgType */
    txBuff[0] = evtData[0];  

    IDSCL_IntToData(txBuff+1,sIdx);
    
    /* Copy Application Id */
    IDSCL_IntToData(txBuff+5,appId);

    /* Copy Diameter message */
    memcpy(txBuff+IDS_DIA_MSG_POS,enBuf,enLen);
    delete [] enBuf;
#endif

    msg.u.diaInfo.msgType = evtData[0];
    msg.u.diaInfo.sessIdx = sIdx;
    msg.u.diaInfo.appId   = appId;

    if (!isRequest)
    {
        msg.msg_type = DIAMETER_MSG;
        msg.u.diaInfo.len = enLen;
        msg.u.diaInfo.data = enBuf;
        /* Route Answer to Client */
                                                                                
        DIA_TRACE_DEBUG(("ProcessDiaStackMsg:Sending Ans to client %d",
                          clntId));
            
        msg.clientID = clntId;
        ret = cHandler_->SendMsg(&msg);

#if MOTO_PERF_PRINT
        static int numAnsSent;
        numAnsSent++;
        time_t t1,temp, tx;
        static time_t preTime;
        struct tm tbuf;
        char buff[80];
        int tps =0;

        if (numAnsSent == 1)
        {
            time(&preTime);
        }
        if((numAnsSent % 200000) == 0)
        {
            time(&t1);
            if (t1 != preTime)
            {
                tps = 200000/(t1-preTime);
                time(&tx);
                localtime_r(&tx, &tbuf);
                strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
                std::cout <<"Previus Ans received at ----->" << buff << std::endl;
                printf("TPS(Ans per sec): %d Total Ans From Peer =%d\n", tps, numAnsSent);
                preTime = t1;
                fflush(stdout);
            }
        }
#endif

    } 
    else
    {
        /* Route Request to Client */

        msg.msg_type = DIAMETER_MSG;
        msg.u.diaInfo.len = enLen;
        msg.u.diaInfo.data = enBuf;

        /* Client ID present for the session,
           route the request to this client. */
        if (clntId)
        {
            DIA_TRACE_DEBUG(("ProcessDiaStackMsg:Sending Req to client %d",
                              clntId));

            msg.clientID = clntId;
            ret = cHandler_->SendMsg(&msg);
        }
        /* If client Id is zero, Search for the best client based on AppId */
        /* If routing chosen is Round Robin, route messages to one of many
           clients matching the routing criteria */
        else if (routeScheme == IDS_ROUND_ROBIN)
        {
            if (routeTable.GetSize() == 0)
            {
                DIA_TRACE_ERROR(("ProcessDiaStackMsg: No clients"));
                ret = ITS_ENOTFOUND;
            }
            else if (!(clntId = routeTable.FindBestMatch(appId)))
            {
                DIA_TRACE_DEBUG(("ProcessDiaStackMsg:No matching clients"));
                ret = ITS_ENOTFOUND;
            }
            else
            {
                DIA_TRACE_DEBUG(("ProcessDiaStackMsg:Sending Req to client %d",
                                  clntId));

                msg.clientID = clntId;
                ret = cHandler_->SendMsg(&msg);
            }
        }
        /* If routing chosen is based on Global Uniq Addr */
        else if (routeScheme == IDS_GLOBAL_UNIQ_ADDR)
        {
            if (rxCmd->containsGlobalUniqAddr())
            {
                unsigned char *ipAddr = rxCmd->getGlobalUniqAddr();

                DIA_TRACE_DEBUG(("GlobalUniqIpAddr = %s",ipAddr));

                if (routeTable.GetSize() == 0)
                {
                    DIA_TRACE_ERROR(("ProcessDiaStackMsg: No clients"));
                    ret = ITS_ENOTFOUND;
                }
                else if (!(clntId = routeTable.FindBestMatch(ipAddr, appId)))
                {
                    DIA_TRACE_DEBUG(("ProcessDiaStackMsg:No matching clients"));
                    ret = ITS_ENOTFOUND;
                }
                else
                {
                  DIA_TRACE_DEBUG(("ProcessDiaStackMsg:SendingReq to client %d",
                                  clntId));

                    msg.clientID = clntId;
                    ret = cHandler_->SendMsg(&msg);
                }
            }
            else
            {
                DIA_TRACE_ERROR(("Dropping GlobalUniq Address missing in msg"));
                ret = ITS_ENOTFOUND;
            }
        }
        /* If client Id is zero and Routing scheme is Broad cast, then route 
           the command to all clients with the matching routing criteria */
        else
        {
            ClientList* client = NULL;
            client = cHandler_->FindBestClient(appId, &index);

            if (!client)
            {
                DIA_TRACE_ERROR(("MsgHandler: Route not found"));

                if (txBuff)
                {
                    delete []txBuff;
                    txBuff = NULL;
                }

                /* Form a error message to be sent to the peer */
                SendErrToPeer(rxCmd, ITS_DIA_UNABLE_TO_DELIVER);

                if (rxCmd)
                {
                    delete rxCmd;
                    rxCmd = NULL;
                }

                return (ITS_ENOTFOUND);
            }

            DIA_TRACE_DEBUG(("ProcessDiaStackMsg:Sending Req to %d clients"
                             , index));

            /* broadcast */
            for (int k=0; k < index; k++)
            {
                msg.clientID = client->clientID[k];
                ret = cHandler_->SendMsg(&msg);
            }

            free(client->clientID);
            free(client);

            client = NULL;
        }

    } // Route Req to client

    if (txBuff)
    {
        delete []txBuff;
        txBuff = NULL;
    }

    if (ret != ITS_SUCCESS)
    {
        /* Form a error message to be sent to the peer */
        SendErrToPeer(rxCmd, ITS_DIA_UNABLE_TO_DELIVER);
    }

    if (rxCmd)
    {
        delete rxCmd;
        rxCmd = NULL;
    }
  
    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Forms Error message to the peer (sent through stack) when 
 *           message delivery to client fails.
 *
 *  Input Parameters:
 *      Command and the result code to be sent.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 *  Revision History:
 *
 ****************************************************************************/
void
MsgHandler::SendErrToPeer(diameter::BaseCommand *inMsg, ITS_UINT rCode)
{
    //ITS_INT ret = ITS_SUCCESS;
    ITS_INT pinfo_count = 0;

    /* if STA, then do not send to Stack. Stack would've cleaned up 
       the context  */
    if (!inMsg->isRequest())
    {
        return;
    }
 
    DIA_TRACE_DEBUG(("MsgHandler: SendErrToPeer"));

    DIA_CER *lcer = itsDiaConfig.GetLocalCER();
                                                                                
    DIA_HDR &hdr = (DIA_HDR&)inMsg->getHeader();

    PROXYABLEERROR pErr(true, false, inMsg->getCommandCode());
    NONPROXYABLEERROR nErr(true, false, inMsg->getCommandCode());
    DIA_GEN_CMD *cmd;
    if (inMsg->isProxyable())
    {
        if (inMsg->getSessionId())
        {
            SessionId sid(inMsg->getSessionId()->value());
            pErr.setSessionId(sid);
        }
        
        pErr.setOriginHost(lcer->getOriginHost());
        pErr.setOriginRealm(lcer->getOriginRealm());
        pErr.setResultCode(ResultCode(rCode));

        /**
         * Adding the Proxy-Info AVP in error response
         * from message. Fix for issue 785 in whizible
         */
        pinfo_count = inMsg->countProxyInfo();
        for(int i=0; i<pinfo_count; i++)
        {
            //const ProxyInfo *pInfo = (inMsg->getProxyInfo(i));
            PROXY_INFO* pInfo = (inMsg->getProxyInfo(i));

            /**
             * While adding ProxyInfo AVPs Check for whether
             * added locally in request. If yes omit in Error
             * response.
             */
            if (!strcmp(pInfo->getProxyHost()->value().c_str(),
                lcer->getOriginHost().value().c_str()))
            {
                continue;
            }

            ProxyInfo proxyInfo;
            ProxyHost phost(pInfo->getProxyHost()->value().c_str());
            proxyInfo.setProxyHost(phost);

            ProxyState pstate(pInfo->getProxyState()->value().c_str());
            proxyInfo.setProxyState(pstate);

            /**
             * changing the API from setProxyInfo to addProxyInfo
             * according to  changes done in abnf
             */
            pErr.addProxyInfo(proxyInfo);
        }

        cmd = (DIA_GEN_CMD *)&pErr;
    }
    else
    {
        if (inMsg->getSessionId())
        {
            SessionId sid(inMsg->getSessionId()->value());
            nErr.setSessionId(sid);
        }
        nErr.setOriginHost(lcer->getOriginHost());
        nErr.setOriginRealm(lcer->getOriginRealm());
        nErr.setResultCode(ResultCode(rCode));
        cmd = (DIA_GEN_CMD *)&nErr;
    }

    /* Fix for error response with appropriate appId while InterOP with Aricent */
    ((DIA_HDR&)cmd->getHeader()).appId   = hdr.appId;
    ((DIA_HDR&)cmd->getHeader()).flags.p = hdr.flags.p;
    ((DIA_HDR&)cmd->getHeader()).hh = hdr.hh;
    ((DIA_HDR&)cmd->getHeader()).ee = hdr.ee;

    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    cmd->setSessionIndex(inMsg->getSessionIndex());
    cmd->setClientId(inMsg->getClientId());

    diaFrame->Send(cmd);
    return;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Sends Notifications to the clients in case of a failure to 
 *           deliver the message to the stack.
 *
 *  Input Parameters:
 *      event and the type of indication to be sent.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 *  Revision History:
 *
 ****************************************************************************/
void  
MsgHandler::SendNotifyToApp(ITS_OCTET* evtData, IDS_APP_IND_TYPE indType , 
                             std::string &sessStr)
{
    IDS_MESSAGE msg;
    ITS_UINT clientId = 0;
    ITS_UINT clIdx = 0;
    ITS_UINT index = 0;
    ITS_UINT offset = 2*sizeof(ITS_UINT) + sizeof(ITS_OCTET);
    ITS_UINT sesLen = 0;
    ITS_UINT ret = ITS_SUCCESS;
    ClientRoutingInfo* clientInfo = NULL;

    DIA_TRACE_DEBUG(("MsgHandler: SendNotifyToApp"));

    /* Get the client ID */
    clientId = IDSCL_DataToInt(evtData+index, sizeof(ITS_UINT));
    index += sizeof(ITS_UINT);

    /* Get client Session Index */
    clIdx = IDSCL_DataToInt(evtData+index, sizeof(ITS_UINT));
    index += sizeof(ITS_UINT);

    /* Send notification to Client */
    msg.msg_type = DIASERVER_NOTIFY_MSG; 
    msg.clientID = clientId; 

    clientInfo = routeTable.RetrieveEntry(clientId);
    if (clientInfo == NULL)
    {
        DIA_TRACE_ERROR(("SendNotifyToApp: Client <%d> not found", clientId));
        return;
    }

    sesLen = sessStr.size();
    msg.u.notifyInfo.indType = indType; 
    msg.u.notifyInfo.sessionIndex = clIdx; 
    msg.u.notifyInfo.appId = clientInfo->regInfo.appIdentifier; 
    msg.u.notifyInfo.length = sizeof(ITS_OCTET) + 2*sizeof(ITS_UINT)
                              + sesLen; 
    msg.u.notifyInfo.data = (ITS_OCTET*)sessStr.c_str();

    ret = cHandler_->SendMsg(&msg);

}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Sends Peer based messages CER/CEA and DPR/DPA to the clients
 *            irrespective of the APPID they are registered with
 *
 *  Input Parameters:
 *      GenericCommand and event received
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 *  Revision History:
 *
 ****************************************************************************/
void MsgHandler::SendPeerBasedMsgToApp(diameter::BaseCommand* rxCmd, ITS_OCTET *evtData)
{
    ITS_INT ret  = ITS_SUCCESS;
    ITS_INT enLen = 0;
    ITS_OCTET *enBuf = NULL;
    ITS_OCTET* txBuff = NULL;
    IDS_MESSAGE msg;
    ITS_UINT count = 0;
    ITS_UINT* clist = NULL;

    DIA_TRACE_DEBUG(("MsgHandler::SendPeerBasedMsgToApp"));
    enBuf = (ITS_OCTET*)rxCmd->getEncodedBuf();
    enLen = rxCmd->getEncodedBufLen();

    if (ret != ITS_SUCCESS || enBuf == NULL || enLen == 0)
    {
        DIA_TRACE_ERROR(("SendPeerBasedMsgToApp:: Diameter encode fail"));
                                                                                
        return;
    }
#if 0
    txBuff = new ITS_OCTET[IDS_DIA_MSG_POS+enLen];

    /* Copy MsgType, sIdx and appId */
    memcpy(txBuff, evtData, IDS_DIA_MSG_POS);  

    /* Copy Diameter message */
    memcpy(txBuff+IDS_DIA_MSG_POS,enBuf,enLen);
    delete [] enBuf;
#endif
    /* Route Answer to Client */

    msg.u.diaInfo.msgType = evtData[0];
    msg.u.diaInfo.sessIdx = 0;
    msg.u.diaInfo.appId   = 0;

    msg.msg_type = DIAMETER_MSG;
    msg.u.diaInfo.len = enLen;
    msg.u.diaInfo.data = enBuf;


   /* Route message to all the client , irrespective 
      of the AppId they have registered with */
    clist = routeTable.GetAllEntries(count);

    if (count)
    {
        for (ITS_INT i = 0; i < count; i++)
        {
            msg.clientID = clist[i];
            ret = cHandler_->SendMsg(&msg);
        }
         //fix for coverity CID 10568
         free(clist);
         clist = NULL;
    }

    if (txBuff != NULL)
    {
        delete []txBuff;
        txBuff = NULL;
    }

    //Fixing Resource Leak
    if (clist != NULL)
    {
       free(clist);
       clist = NULL;
    }
    return;
}

