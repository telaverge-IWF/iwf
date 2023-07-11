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
 * ID: $Id: idc_client.cpp,v 3.23.46.3.4.1 2013/07/31 07:19:52 vsarath Exp $
 *
 * LOG: $Log: idc_client.cpp,v $
 * LOG: Revision 3.23.46.3.4.1  2013/07/31 07:19:52  vsarath
 * LOG: Fix for coverity warnings
 * LOG:
 * LOG: Revision 3.23.46.3  2013/04/01 05:14:35  vsarath
 * LOG: Fix for Coverity warnings
 * LOG:
 * LOG: Revision 3.23.46.2  2013/03/12 04:44:32  vsarath
 * LOG: Fix for coverity issue
 * LOG:
 * LOG: Revision 3.23.46.1  2013/02/27 08:49:06  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.23  2010/12/27 16:04:22  nvijikumar
 * LOG: Compilation issue on MVL
 * LOG:
 * LOG: Revision 3.22  2010/09/22 05:22:21  nvijikumar
 * LOG: GlobalUniqueAddr based routing/distribution support
 * LOG:
 * LOG: Revision 3.21  2010/07/07 08:30:30  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 3.20  2010/04/29 06:44:49  nvijikumar
 * LOG: Fix for compilation issue on Sun CC - version 12
 * LOG:
 * LOG: Revision 3.19  2009/12/18 08:36:17  sureshj
 * LOG: return statement added to setsocketbindinfo() in success case.
 * LOG:
 * LOG: Revision 3.18  2009/12/11 08:19:23  sureshj
 * LOG: New API call to skip LICENSE_load when DISABLE_LICENSING flag
 * LOG: defined. Motorola helpdesk ticket 2286.
 * LOG:
 * LOG: Revision 3.17  2009/11/26 08:34:45  sureshj
 * LOG: delete [] enBuf replaced with free() call. Motorola helpdesk
 * LOG: ticket 2277.
 * LOG:
 * LOG: Revision 3.16  2009/07/13 11:54:39  rajeshak
 * LOG: Option to set TCP keepalive timers.
 * LOG:
 * LOG: Revision 3.15  2009/06/04 03:47:47  rajeshak
 * LOG: Memory leak fix in case of overload.
 * LOG:
 * LOG: Revision 3.14  2009/04/14 09:16:30  sureshj
 * LOG: OverLoad & overload abated callbacks added.
 * LOG:
 * LOG: Revision 3.13  2009/04/07 14:34:56  sureshj
 * LOG: Overload Handling is added to control Traffic when overload
 * LOG: indication is received from IDS.
 * LOG:
 * LOG: Revision 3.12  2009/03/25 04:02:10  nvijikumar
 * LOG: Provided API to bind local IP and Port
 * LOG:
 * LOG: Revision 3.11  2009/03/19 12:33:13  rajeshak
 * LOG: Klockwork Issue Fix.
 * LOG:
 * LOG: Revision 3.10  2009/03/03 13:29:09  sureshj
 * LOG: Introduced API to set IDC Reconnect interval timer.
 * LOG:
 * LOG: Revision 3.9  2008/12/31 13:25:05  nvijikumar
 * LOG: Mutex is required only for TCP transport
 * LOG:
 * LOG: Revision 3.8  2008/12/17 08:52:13  nvijikumar
 * LOG: Changes to fix endiannes issue with UDP Read/Write
 * LOG: Issue Id: 1338
 * LOG:
 * LOG: Revision 3.7  2008/12/06 12:50:21  nvijikumar
 * LOG: Connection Disconnect Callback support
 * LOG:
 * LOG: Revision 3.6  2008/12/05 04:59:15  nvijikumar
 * LOG: 1. Return proper errCode if failed to send Message
 * LOG: 2. NULL check for destination Host/Realm in AllocateSessionIdex()
 * LOG:
 * LOG: Revision 3.5  2008/11/28 13:30:23  ssaxena
 * LOG: Issue ID: 1323
 * LOG: Feature ID: None
 * LOG: Description: Properly Unsetting the flags for Primay and Secondary
 * LOG:              Connection when one of them is active.
 * LOG:
 * LOG: Revision 3.4  2008/11/06 07:22:50  nvijikumar
 * LOG: UDP Transport support between IDS and IDC
 * LOG:
 * LOG: Revision 3.3  2008/10/28 12:03:32  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.1.2.2  2008/09/16 11:27:41  nvijikumar
 * LOG: Incorporated Yogesh's comments
 * LOG: 1. Clear Reg info if failed to send
 * LOG:
 * LOG: Revision 3.1.2.1  2008/09/16 09:53:29  nvijikumar
 * LOG: 1. Introduced New Thread and Queue for handling outgoing messages
 * LOG: 2. Updated for ReadEvent and WriteEvent to avoid multiple times
 * LOG:    Read/Write Calls
 * LOG:
  * LOG: Revision 3.2  2008/07/07 12:15:01  sureshj
  * LOG:      Debug trace for IDS_CALLBACK_INFO CallBack not configured added.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:03  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.30  2008/03/27 11:18:29  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.18.2.9  2007/10/03 16:37:24  hbhatnagar
 * LOG: Adding the check so that connection type should be one of
 * LOG: Primary or Server or Both.
 * LOG:
 * LOG: Revision 2.18.2.8  2007/10/01 19:35:50  hbhatnagar
 * LOG: Changed the signature of IDSCL_Register to accomodate the re-registration,
 * LOG: removed the Re-reg info, Invocation of  the callback in Primary and backup
 * LOG: Thread and removed the Re-Registraion for first AppId
 * LOG:
 * LOG: Revision 2.18.2.7  2007/05/30 07:17:58  nvijikumar
 * LOG: If Server connection is down, wait for some time before try to reconnect.
 * LOG: Fix for Bug Id: 5917, 5905
 * LOG:
 * LOG: Revision 2.18.2.6  2007/05/30 04:20:27  nvijikumar
 * LOG: Fix for Bug Id 5906 Provided proper Traces.
 * LOG:
 * LOG: Revision 2.18.2.5  2007/05/25 11:04:26  sumag
 * LOG: Clear the Registration info while deregistering
 * LOG: from a IDS is that not up
 * LOG:
 * LOG: Revision 2.18.2.4  2007/03/16 06:31:48  hbhatnagar
 * LOG: JAVA changes reverted back(Viji)
 * LOG:
 * LOG: Revision 2.18.2.3  2007/03/15 18:20:24  hbhatnagar
 * LOG: changed the signature for IDSCL_InitDiaDictParser and DiaDictParserInitialize and added check for Duplicate entries
 * LOG:
 * LOG: Revision 2.18.2.2  2007/03/13 05:14:03  hbhatnagar
 * LOG: Allow multiple registration from same client
 * LOG:
 * LOG: Revision 2.19  2007/03/07 14:14:30  sumag
 * LOG: Baselined Java modifications / Additions for ITS Diameter.
 * LOG:
 * LOG: Revision 2.18  2007/02/19 04:49:32  kamakshilk
 * LOG: Fix for Bridgewater issue
 * LOG:
 * LOG: Revision 2.17  2007/01/29 08:04:55  kamakshilk
 * LOG: Check for primary port added
 * LOG:
 * LOG: Revision 2.16  2007/01/19 13:01:49  kamakshilk
 * LOG: Memory leaks fixed
 * LOG:
 * LOG: Revision 2.15  2007/01/04 11:31:17  nvijikumar
 * LOG: Accounting Statemachine changes.
 * LOG:
 * LOG: Revision 2.14  2006/12/14 13:41:44  kamakshilk
 * LOG: Fix for bug ID 5054. IsRegisteredWith, IsConnectionUp APIs added.
 * LOG:
 * LOG: Revision 2.13  2006/12/12 14:15:26  kamakshilk
 * LOG: Fix for bug If 5049
 * LOG:
 * LOG: Revision 2.12  2006/11/24 15:21:53  kamakshilk
 * LOG: regStatus flag reset in CloseCon API
 * LOG:
 * LOG: Revision 2.11  2006/11/24 05:46:25  kamakshilk
 * LOG: Null character appended fro ReleaseSession event
 * LOG:
 * LOG: Revision 2.10  2006/11/17 06:12:19  kamakshilk
 * LOG: ReleaseSession API and DccaEnable Added
 * LOG:
 * LOG: Revision 2.9  2006/11/16 12:42:54  kamakshilk
 * LOG: InitDiaDictParser API added
 * LOG:
 * LOG: Revision 2.8  2006/11/15 13:17:48  kamakshilk
 * LOG: IDS_INSERT_APPID removed in Send
 * LOG:
 * LOG: Revision 2.7  2006/11/14 09:11:22  kamakshilk
 * LOG: SessionId to contain clientId and client session Index
 * LOG:
 * LOG: Revision 2.6  2006/11/08 06:15:46  kamakshilk
 * LOG: Changes for 64-bit support.ITS_ULONG changed to ITS_UINT
 * LOG:
 * LOG: Revision 2.5  2006/10/31 10:01:43  kamakshilk
 * LOG: IDSCL_Print function added
 * LOG:
 * LOG: Revision 2.4  2006/10/29 06:50:22  kamakshilk
 * LOG: Added print to display the received n sent buffers
 * LOG:
 * LOG: Revision 2.3  2006/10/24 11:48:37  kamakshilk
 * LOG: Added check on sessIdx, not to exceed DIA_DIR_BIT
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:22:50  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.13  2006/09/06 11:23:17  kamakshilk
 * LOG: Fix for bug Ids 3615,4287. Added IntToData and DataToInt APIs for encode and decode.
 * LOG:
 * LOG: Revision 1.12  2006/09/01 16:34:13  yranade
 * LOG: Finalize licensing.
 * LOG:
 * LOG: Revision 1.11  2006/09/01 15:59:41  yranade
 * LOG: Add License Capability.
 * LOG:
 * LOG: Revision 1.10  2006/07/25 13:42:08  sumag
 * LOG: Updates for Java.
 * LOG:
 * LOG: Revision 1.9  2006/05/30 09:37:50  yranade
 * LOG: Changes to compile with CC compiler on solaris 10.
 * LOG:
 * LOG: Revision 1.8  2006/04/26 10:19:11  adutta
 * LOG: Fixed issues# 3603/3607
 * LOG:
 * LOG: Revision 1.7  2006/04/25 15:59:42  yranade
 * LOG: Fix Compilation problem.
 * LOG:
 * LOG: Revision 1.6  2006/04/17 06:01:04  nvijikumar
 * LOG: Dump trace added in Reg.
 * LOG:
 * LOG: Revision 1.5  2006/04/13 11:05:12  nvijikumar
 * LOG: static variable problem (yogesh)
 * LOG:
 * LOG: Revision 1.4  2006/04/06 07:59:23  adutta
 * LOG: Ses-Id related changes/API added
 * LOG:
 * LOG: Revision 1.3  2006/03/14 06:39:18  adutta
 * LOG: Codec changes
 * LOG:
 * LOG: Revision 1.2  2006/03/13 05:20:53  adutta
 * LOG: Impl. changes for diameter encode/decode
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:12:34  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/
#ident "$Id: idc_client.cpp,v 3.23.46.3.4.1 2013/07/31 07:19:52 vsarath Exp $"

#include <diameter/base/Accounting.h>
#include <sys/time.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <its.h>
#include <its++.h>
#include <its_types.h>
#include <its_license.h>
#include <engine++.h>
#include <its_license.h>

#include <netinet/tcp.h>

#include <arpa/inet.h>
#include <errno.h>

#if defined(IPPROTO_SCTP)
#undef IPPROTO_SCTP
#endif

#include <idc_client.h>
#include <idc_trace.h>

#include <dia_defines.h>
#include <dia_dict_parse.h>

#include <idc_api.h>

using namespace diameter;

//static char* sync_data = "ISS7SSI";
static std::string sync_data = "ISS7SSI";
static ITS_INT   sd_len = 7;
ITS_BOOLEAN ovrLoadF = ITS_FALSE;
static ITS_BOOLEAN isTCPKeepAliveSet = ITS_FALSE;

ITS_MUTEX hashLock;
ITS_MUTEX regLock;

IDSCL_DLLAPI IDS_CONNECTION IDS_Connection;
IDSCL_DLLAPI ITS_HANDLE ISS7_Stack = (ITS_HANDLE)&IDS_Connection;

IDS_UINT IDS_ClientID = 0;

IDS_BOOLEAN IDSCLApi::bInitialize = IDS_FALSE;
IDS_HANDLE IDSCLApi::handle = NULL;

IDSCL_DLLAPI IDS_HOSTINFO IDS_HostInfo;

/*
 * Close the connection, for the UDP user
 */
static IDS_INT
EndPointOpen(IDS_CONNECTION_INFO *info);

/*
 * Write the event to UDP Server
 */

static IDS_INT
UdpSend(IDS_CONNECTION_INFO *info, ITS_EVENT *evt);

/*
 * Recv the event from UDP Server
 */
static IDS_INT
UdpRecv(IDS_CONNECTION_INFO *info, ITS_EVENT *evt); 

ITS_THREAD sendThreadInfo;
IDSCL_DLLAPI ITS_INT
IDSCL_GetNextOutGoingEvent(ITS_HANDLE handle, ITS_EVENT *evt);
ITS_BOOLEAN isSThreadRunning = ITS_FALSE;
IDS_INT sockConInterval = SOC_CONNECT_INTERVAL;

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *      
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *    
 *  Notes:
 * 
 *  See Also:
 * 
 *************************************************************************/
void
ProcessHeartBeat(ITS_HANDLE* hdl)
{
    ITS_EVENT ev;
    ITS_INT i = 0;
    ITS_INT index = 0;

    IDS_TRACE_DEBUG(("ProcessHeartBeat"));

    ITS_EVENT_INIT(&ev, ITS_APP_SRC, sizeof(ITS_UINT) + sizeof(ITS_OCTET));

    for (i = 0; i < sizeof(ITS_UINT); i++)
    {
        ev.data[i] = 0xFF;
    }

    ev.data[i] = HEARTBEAT_MSG;

    IDS_TRACE_DEBUG(("\nProcessHeartBeat:: Sending HB ack to server....\n"));    
    IDSCL_Print(ev.data, ev.len);

    IDSCL_WriteEvent(hdl, &ev);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *       
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *     
 *  Notes:
 *  
 *  See Also:
 *  
 *************************************************************************/
ITS_INT
ProcessRegAckAndStatus(ITS_EVENT evt)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_UINT port  = 0;
    ITS_CHAR ipAddr[IDSCL_IP_ADDR_LEN] = {'\0'};
    IDS_CONNECTION_TYPE conType;
    IDS_MESSAGE msg;

    IDS_TRACE_DEBUG(("ProcessRegAckAndStatus"));

    memset(&msg, 0, sizeof(IDS_MESSAGE));
    ret = IDSCL_Decode(&msg, &evt);

    if (msg.msg_type == REGISTER_ACK_MSG)
    {
        conType = msg.u.regAck.conType;
        port = msg.u.regAck.port;
        //Correcting Calling risky function
        strncpy(ipAddr, msg.u.regAck.ipAddr,IDSCL_IP_ADDR_LEN-1);
        IDS_Connection.isDccaEnabled = (IDS_BOOLEAN)msg.u.regAck.isDccaEnabled;
        if (msg.u.regAck.errorCode == IDS_CLIENT_DUPLICATE_ENTRY)
            IDS_Connection.clid = 0;
    }
    else
    {
        conType = msg.u.servInfo.conType;
        port = msg.u.servInfo.port;
        strncpy(ipAddr, msg.u.servInfo.ipAddr, IDSCL_IP_ADDR_LEN - 1);
    }


    IDS_TRACE_DEBUG(("ProcessRegAckAndStatus: Server ip %s port %d type %d", 
                                      ipAddr, port, conType));

    if (conType != IDS_PRIMARY_CONNECTION)
    {
        return (ret);
    }

    if ((port == IDS_Connection.primaryInfo.port)
       && (strcmp(ipAddr, IDS_Connection.primaryInfo.ipAddr) == 0))
    {
         IDS_TRACE_DEBUG(("ProcessRegAckAndStatus: Primary connection "
                                                              "taking over "));

         IDS_Connection.primaryInfo.isPrimary = ITS_TRUE;

         /**
          * Partial Fix for whizible issue 1323. Unsetting the Secondary Connection Flag.
          */  
         IDS_Connection.backupInfo.isPrimary = ITS_FALSE;
    }
    else  if ((port == IDS_Connection.backupInfo.port)
       && (strcmp(ipAddr, IDS_Connection.backupInfo.ipAddr) == 0))
    {
         IDS_TRACE_DEBUG(("ProcessRegAckAndStatus: Secondary connection "
                                                             "taking over "));

         IDS_Connection.backupInfo.isPrimary = ITS_TRUE;

         /**
          * Partial Fix for whizible issue 1323. Unsetting the Primary Connection Flag.
          */  
         IDS_Connection.primaryInfo.isPrimary = ITS_FALSE;
    }

    return (ret);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method is used when we are inserting the connection info 
 *      in to the hash table with glgid as the key.
 *
 *  Input Parameters:
 *      dlgid- key. cInfo- connection info.
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *
 *  See Also:
 *
 *************************************************************************/
ITS_INT 
IDSCL_AddAppIdentifierEntry(ITS_OCTET ptype, 
                            ITS_UINT appId ,
                            ITS_USHORT cInfo)
{
    ITS_USHORT *connInfo = NULL;
    ITS_INT ret = ITS_SUCCESS;

    return (ret);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This function is called to set TCP KeepAlive Timers table
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *
 *  See Also:
 *
 *************************************************************************/
IDSCL_DLLAPI IDS_INT
IDSCL_SetTcpKeepAliveTimer(IDS_TCP_TIMER* val)
{
    IDS_Connection.tcpTimer.keepAliveCnt = val->keepAliveCnt;
    IDS_Connection.tcpTimer.keepAliveIdle = val->keepAliveIdle;
    IDS_Connection.tcpTimer.keepAliveIntvl = val->keepAliveIntvl;

    isTCPKeepAliveSet = ITS_TRUE;
    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This function is called when hash table 
 *      entries is to be updated to the connection given in the "in" param.
 *      in  0 - for primary connection 1 - backup connection.
 *  Input Parameters:
 *      
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *
 *  See Also:
 *
 *************************************************************************/

IDSCL_DLLAPI ITS_INT 
IDSCL_UpdateEntryProc(ITS_INT context, ITS_POINTER data,
                               void *in, void *out)
{
    ITS_OCTET *tmp = (ITS_OCTET *)in;

    *data = *tmp;

    return (ITS_SUCCESS);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This function is called when hash table
 *      entries is to be deleted.  
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *
 *  See Also:
 *
 *************************************************************************/
IDSCL_DLLAPI ITS_INT 
IDSCL_DeleteEntryProc(ITS_INT context, ITS_POINTER data,
                               void *in, void *out)
{
    return (ITS_SUCCESS);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This function is wrapper function for update hash function.
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *
 *  See Also:
 *
 *************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_UpdateHashEntry(ITS_OCTET type)
{

    IDS_TRACE_DEBUG(("IDSCL_UpdateHashEntry"));

    return (ITS_SUCCESS);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This function is wrapper function for delete hash function.
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *
 *  See Also:
 *
 *************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_DeleteHashEntry()
{
    IDS_TRACE_DEBUG(("IDSCL_DeleteHashEntry"));

    return (ITS_SUCCESS);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method sends the event to server 
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      evt - event to be send
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *  This method decides on which connection it should put the event,
 *  it always try to send on the primary connection in case of failure
 *  of primary connection only it sends on backup connection alternatively.  
 *  See Also:
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT 
IDSCL_SendEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    IDS_CONNECTION *conn = NULL; 
    ITS_INT ret = 0, index = 0; 
    ITS_USHORT *connInfo = NULL;
    ITS_BOOLEAN flag = ITS_TRUE;
    ITS_USHORT ptype;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_DIAMETER))
    {
        return ITS_ENOLICENSE;
    }

    IDS_TRACE_DEBUG(("IDSCL_SendEvent"));

    if (handle == NULL)
    {
        IDS_TRACE_ERROR(("IDSCL_SendEvent: Socket handle null"));

        return (IDS_EINVALIDARGS);
    }

    IDS_TRACE_DEBUG(("\nIDSCL_SendEvent:: Sending event to server. Len %d\n",
                     evt->len));
    IDSCL_Print(evt->data, evt->len);
       
    conn = (IDS_CONNECTION*)handle;

    if(conn->backupInfo.isPrimary == ITS_TRUE)
    {
        flag = ITS_FALSE;
    }
    else if((conn->primaryInfo.isPrimary == ITS_FALSE) &&
                (conn->backupInfo.isPrimary == ITS_FALSE))
    {
        IDS_TRACE_CRITICAL(("IDSCL_SendEvent: All connection down"));

        return (ITS_ENOSOCKET);
    }
    else
    {
        flag = ITS_TRUE;
    }

    if (flag)
    {
        if (conn->primaryInfo.regStatus == SUCCESS)
        {
            ret = IDSCL_WriteEvent(&conn->primaryInfo, evt);
        }
        else
        {
            IDS_TRACE_CRITICAL(("IDSCL_SendEvent: Client not registered"));

            ret = IDS_NOT_REGISTERED;
        }
    }
    else
    {
        if (conn->backupInfo.regStatus == SUCCESS)
        {
            ret = IDSCL_WriteEvent(&conn->backupInfo, evt);
        }
        else
        {
            IDS_TRACE_CRITICAL(("IDSCL_SendEvent: Client not registered"));

            ret = IDS_NOT_REGISTERED;
        }
    }

    return (ret);
}


/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method sends the event to server
 *
 *  Input Parameters:
 *      evt - event to be send
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *  See Also:
 *
 * Revision History:
 * ----------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 * ----------------------------------------------------------------------------
 *   Kamakshi    06-09-06    Bug #3615,4287     Added IntToData() for encoding
                                                IDS_ClientID,sId
 *   Kamakshi    14-11-06    Enhancement        Msg Type to indicate first Req
                                                in a session. 
 *   Kamakshi    15-11-06    Enhancement        IDS_INSERT_APPID removed. 
 *   Kamakshi    19-02-07    Bridgewater        Return statement added. 
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_Send(ITS_HANDLE handle, diameter::Command& mesg, ITS_UINT sId, 
           ITS_UINT appId, IDS_BOOLEAN newRequest)
{
    ITS_EVENT evt;
    ITS_INT ret = !ITS_SUCCESS;
    ITS_UINT index = 0;
    ITS_UINT idcHdrLen = sizeof(ITS_UINT) + 
                         sizeof(ITS_UINT) +
                         sizeof(ITS_OCTET) + 1;
    // IDC hdr = ClientID (4 octets) + SesIdx (4 octets) + MsgType(1 octet)
    ITS_INT enLen = 0;
    ITS_OCTET *enBuf = NULL;
    ITS_OCTET accRecInfo = 0x00;
    IDS_TRACE_DEBUG(("IDSCL_Send"));

    /* Encoded message */
    try
    {
       mesg.encode(enBuf,enLen);
       ret = ITS_SUCCESS;
    }
    catch (NoSuchAttributeException& e)
    {
        IDS_TRACE_DEBUG(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
    }
    catch (WrongCommandTypeException& e)
    {
        IDS_TRACE_DEBUG(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
    }
    catch (UnknownTypeException& e)
    {
        IDS_TRACE_DEBUG(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
    }
    catch (CodecException& e)
    {
        IDS_TRACE_DEBUG(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
    }
    catch (...)
    {
        IDS_TRACE_DEBUG(("Unknown Exception Caught"));
    }

    if (ret != ITS_SUCCESS || enBuf == NULL || enLen == 0)
    {
        IDS_TRACE_ERROR(("IDSCL_Send: Diameter encode fail"));
        //Fixing Resource Leak
        if (enBuf != NULL)
            free((char*)enBuf);
        return (IDS_ESENDFAIL);
    }

    ITS_EVENT_INIT(&evt, IDS_APPDATA_SRC, enLen+idcHdrLen);

    /* Pre-fix client ID */
    IDSCL_IntToData((evt.data), IDS_ClientID, sizeof(ITS_UINT));
    index = sizeof(ITS_UINT);

    /* Pre-fix session index before encoded dia data */
    IDSCL_IntToData((&evt.data[index]), sId, sizeof(ITS_UINT));
    index += sizeof(ITS_UINT);

    /* Set Accounting record information if ACR */
    if (mesg.isRequest() && (mesg.getCommandCode() == 271))
    {
        diameter::base::AccountingRequest &acr = 
                                     (diameter::base::AccountingRequest &)mesg;
        if (acr.IsStorageSpaceAvailable())
        {
            /* Set IsStorageSpaceAvailable flag */
            accRecInfo |= 0x01;
        }
        if (acr.IsLastRecordInStorage())
        {
            /* Set IsLastRecordInStorage flag */
            accRecInfo |= 0x02;
        }
    }

    /* Pre-fix Accounting Record Information required only for ACR */
    IDSCL_IntToData((&evt.data[index]), accRecInfo, sizeof(ITS_OCTET));
    index += sizeof(ITS_OCTET);

    if (mesg.isRequest())
    {
        /* Add the message type */
        if (newRequest)
            evt.data[index++] = IDS_DIA_MSG_TYPE_NEW_REQ;
        else
            evt.data[index++] = ITS_DIA_MSG_TYPE_DATA_REQ;
    }
    else
    {
        /* Add the message type */
        evt.data[index++] = ITS_DIA_MSG_TYPE_DATA_ANS;
    }

    memcpy(evt.data+index,enBuf,enLen);
    free((char*)enBuf);

    if (appId != mesg.getApplicationId())
    {
        IDS_TRACE_WARNING(
            ("IDSCL_Send: Send AppId <%u> doesnt match Command AppId <%u>",
                              appId, mesg.getApplicationId()));
    }

    //ret = IDSCL_SendEvent(handle, &evt);
    /* Put into Queue, another thread takes care writing to socket */
    if(!ovrLoadF)
    {
        ret = IDSCL_PutEventOnTaskQue(&IDS_Connection.outBoundTaskTrans,
                                                 &evt);
    }
    else
    {
        /* delete the buffer in case of overload */
        if (evt.data)
        {
            ITS_Free(evt.data);
            evt.data = NULL;
        }
    }
    if (ret != ITS_SUCCESS)
    {
        IDS_TRACE_ERROR(("IDSCL_Send:  PutEvent fail"));
    }

    return ret;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method write the data to socket
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      evt - event to be send
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *   
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    19-01-07   Enhancement   Freeing evt after write. 
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_WriteEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    ITS_INT nrite;
    ITS_USHORT tmp =0;
    ITS_OCTET evtInfo[2*sizeof(ITS_USHORT)]  ={ 0 };
    IDS_CONNECTION_INFO *conInfo = NULL; 

    IDS_TRACE_DEBUG(("IDSCL_WriteEvent"));

    if (handle == NULL)
    {
        IDS_TRACE_ERROR(("IDSCL_WriteEvent: Handle null"));

        /* Free the event*/
        if (evt->data)
        {
            free(evt->data);
            evt->data = NULL;
        }

        return (IDS_EINVALIDARGS);
    }

    conInfo = (IDS_CONNECTION_INFO*)handle;

    if (!conInfo->isUp)
    {
        IDS_TRACE_ERROR(("IDSCL_WriteEvent: Connection down"));

        /* Free the event*/
        if (evt->data)
        {
            free(evt->data);
            evt->data = NULL;
        }

        return (IDS_ESENDFAIL);
    }

    if (conInfo->transType == IDS_UDP)
    {
        /* UDP transport */
        return UdpSend(conInfo, evt);
    }

    MUTEX_AcquireMutex(&conInfo->writeLock);

    /* TCP Starts here */
#if IDS_PATTERN
    nrite = SOCK_Write(conInfo->sockInfo, (char*)sync_data.c_str(), sd_len); 
    if (nrite != sd_len)
    {
        MUTEX_ReleaseMutex(&conInfo->writeLock);
        IDS_TRACE_ERROR(("IDSCL_WriteEvent: Send fail"));

        /* Free the event*/
        if (evt->data)
        {
            free(evt->data);
            evt->data = NULL;
        }
        // Clear the Registration info while deregistering
        //from a IDS is that not up
        {
             IDS_Connection.primaryInfo.regStatus = NOTREGISTERED;
             /* Reset the values */
             if (!IDS_Connection.backupInfo.isUp)
             {
                  IDS_Connection.clid = 0;
                  IDS_Connection.regInfoLen = 0;
                  if (IDS_Connection.reRegInfo != NULL)
                  {
                       free(IDS_Connection.reRegInfo);
                            IDS_Connection.reRegInfo = NULL;
                  }
             }
        }

        return (IDS_ESENDFAIL);
    }

    tmp = SOCK_HToNS(evt->src);

    nrite = SOCK_Write(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT)); 
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->writeLock);
        IDS_TRACE_ERROR(("IDSCL_WriteEvent: Send fail"));

        /* Free the event*/
        if (evt->data)
        {
            free(evt->data);
            evt->data = NULL;
        }

        return (IDS_ESENDFAIL);
    }

    tmp = SOCK_HToNS(evt->len);

    nrite = SOCK_Write(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT)); 
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->writeLock);
        IDS_TRACE_ERROR(("IDSCL_WriteEvent: Send fail"));

        /* Free the event*/
        if (evt->data)
        {
            free(evt->data);
            evt->data = NULL;
        }

        return (IDS_ESENDFAIL);
    }
#else
   /* First 2 bytes contains evt->src) */
    tmp = SOCK_HToNS(evt->src);
    memcpy(&evtInfo[0], &tmp, sizeof(ITS_USHORT));

    /* Next 2 bytes contains evt->len) */
    tmp = SOCK_HToNS(evt->len);
    memcpy(&evtInfo[2], &tmp, sizeof(ITS_USHORT));

    nrite = SOCK_Write(conInfo->sockInfo, (char *)evtInfo, sizeof(ITS_UINT));
    if (nrite != sizeof(ITS_UINT))
    {
        MUTEX_ReleaseMutex(&conInfo->writeLock);
        IDS_TRACE_ERROR(("IDSCL_WriteEvent: Send fail"));

        /* Free the event*/
        if (evt->data)
        {
            free(evt->data);
            evt->data = NULL;
        }

        // Clear the Registration info while deregistering
        //from a IDS is that not up
        {
             IDS_Connection.primaryInfo.regStatus = NOTREGISTERED;
             /* Reset the values */
             if (!IDS_Connection.backupInfo.isUp)
             {
                  IDS_Connection.clid = 0;
                  IDS_Connection.regInfoLen = 0;
                  if (IDS_Connection.reRegInfo != NULL)
                  {
                       free(IDS_Connection.reRegInfo);
                            IDS_Connection.reRegInfo = NULL;
                  }
             }
        }

        return (IDS_ESENDFAIL);
    }
#endif

    /* Write the data */
    if (evt->len)
    {
        nrite = SOCK_Write(conInfo->sockInfo, (char *)evt->data, evt->len);

        if (nrite != (ITS_INT)evt->len)
        {
            MUTEX_ReleaseMutex(&conInfo->writeLock);
            IDS_TRACE_ERROR(("IDSCL_WriteEvent: Send fail"));

            /* Free the event*/
            if (evt->data)
            {
                free(evt->data);
                evt->data = NULL;
            }

            return (IDS_ESENDFAIL);
        }
    }
   
    /* Free the event*/
    if (evt->data)
    {
        free(evt->data);
        evt->data = NULL;
    }

    MUTEX_ReleaseMutex(&conInfo->writeLock);

    return (ITS_SUCCESS);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method gives the info whether either of the socket is up.
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 * 
 *  See Also:
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_IsRegistered(ITS_HANDLE handle)
{
   IDS_CONNECTION *conInfo = NULL;

   IDS_TRACE_DEBUG(("IDSCL_IsRegistered"));
     
   conInfo = (IDS_CONNECTION *)handle;

   if(conInfo->primaryInfo.isUp) 
   {
       switch(conInfo->primaryInfo.regStatus)
       {
           case SUCCESS:
                return ITS_SUCCESS;
           break;
           case FAILURE:
           case NOTREGISTERED:
           default:
               return !ITS_SUCCESS;
           break;
       }  
   }
   else
   {
       if(conInfo->backupInfo.isUp)
       {
           switch(conInfo->backupInfo.regStatus)
           {
               case SUCCESS:
                  return ITS_SUCCESS;
               break;
               case FAILURE:
               case NOTREGISTERED:
               default:
                   return !ITS_SUCCESS;
               break;
           }
       }
   } 
  
   return (!ITS_SUCCESS);
} 

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method Reads the data from server
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      evt    -  event 
 *
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *      evt - type ITS_EVENT *.
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 * 
 *  See Also:
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT 
IDSCL_ReadEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    ITS_INT nread = 0, ret =0;
    char buf;
    ITS_USHORT tmp =0;
    ITS_OCTET evtInfo[2*sizeof(ITS_USHORT)] ={0};
    ITS_BOOLEAN firstTime = ITS_TRUE;
    unsigned i, dosCount;
    IDS_CONNECTION_INFO *conInfo = NULL; 

    IDS_TRACE_DEBUG(("IDSCL_ReadEvent"));

    if (evt == NULL)
    {
        return (IDS_EINVALIDARGS);
    }

    conInfo = (IDS_CONNECTION_INFO*)handle;
    if (conInfo == NULL)
    {
        return (IDS_ERCVFAIL);
    }


    if (conInfo->transType == IDS_UDP)
    {
        /* UDP transport */
        return UdpRecv(conInfo, evt); 
    }

    MUTEX_AcquireMutex(&conInfo->readLock);

#if IDS_PATTERN
    /* synchronize the stream */
    for (i = 0, dosCount = 0;
         i < (unsigned)sd_len && dosCount < ITS_MAX_EVENT_SIZE;
         i++, dosCount++)
    {
        /*
         * this should be the blocking point
         */
        if (firstTime)
        {
            ITS_SockPollInfo info;

repeat:
            memset(&info, 0, sizeof(info));

            info.lookFor = SOCK_POLL_READ;
            info.sinfo = conInfo->sockInfo;

            ret = SOCK_Poll(&info, 1,
                            HMI_GetTimeOutInterval() * 1000);
            if (ret < ITS_SUCCESS)
            {
                MUTEX_ReleaseMutex(&conInfo->readLock);

                return (IDS_ERCVFAIL);
            }

            if (ret == 0)
            {
                if (conInfo->isUp == ITS_FALSE)
                {
                    MUTEX_ReleaseMutex(&conInfo->readLock);

                    return IDS_ENOSOCKET;
                }
                goto repeat;
            }

            firstTime = ITS_FALSE;
        }

        ret = SOCK_Read(conInfo->sockInfo, &buf, sizeof(char));

        if (ret != sizeof(char))
        {
            MUTEX_ReleaseMutex(&conInfo->readLock);

            return (IDS_ERCVFAIL);
        }

        if (buf != sync_data[i])
        {
            i = ~0U;
            continue;
        }
    }

    /* Here we are so successfully received ISS7SSI*/ 

    /* read the source */
    nread = SOCK_Read(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);

        return (IDS_ERCVFAIL);
    }

    evt->src = SOCK_NToHS(tmp);

    /* read the length */
    nread = SOCK_Read(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);

        return (IDS_ERCVFAIL);
    }

    evt->len = SOCK_NToHS(tmp);
#else
    /* read the source */
    nread = SOCK_Read(conInfo->sockInfo, (char *)evtInfo, sizeof(ITS_UINT));
    if (nread != sizeof(ITS_UINT))
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);

        return (IDS_ERCVFAIL);
    }

    /* First 2 bytes contains evt->src) */
    memcpy(&tmp, &evtInfo[0], sizeof(ITS_USHORT));
    evt->src  = SOCK_NToHS(tmp);

    /* Next 2 bytes contains evt->len) */
    memcpy(&tmp, &evtInfo[2], sizeof(ITS_USHORT));
    evt->len  = SOCK_NToHS(tmp);
#endif

    evt->data = (ITS_OCTET *)malloc(evt->len);
    if (evt->data == NULL)
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);

        return (IDS_ENOMEM);
    }

    /* read the data */
    if (evt->len)
    {
        nread = SOCK_Read(conInfo->sockInfo, (char *)evt->data, evt->len);

        if (nread != evt->len)
        {
            free(evt->data);
            evt->data = NULL;

            MUTEX_ReleaseMutex(&conInfo->readLock);

            return (IDS_ERCVFAIL);
        }
    }
    MUTEX_ReleaseMutex(&conInfo->readLock);

    return (ITS_SUCCESS);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method handles the cleint specific events
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT 
IDSCL_HandleClientEvent(ITS_EVENT *evt)
{
    IDS_TRACE_DEBUG(("---Unexpected client msg received from server"));

    return ITS_SUCCESS;
}


/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method connects to the server.
 *      socket
 *
 *  Input Parameters:
 *      info  -   of type IDS_CONNECTION_INFO
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *      This function doesn't return until it connects to the server.
 *
 *  See Also:
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT 
IDSCL_Connect(IDS_CONNECTION_INFO *info, IDS_TCP_TIMER* timerVal)
{
    ITS_INT ret =0;
    ITS_INT repeat_count = 1;
    int    dummy = 1;                    /* for socket option */
    ITS_SocketInfo *sInfo;
    struct linger      linger;           /* for set linger */

    IDS_TRACE_DEBUG(("IDSCL_Connect"));
    /* 
     * Create UDP Socket
     */
    if (info->transType == IDS_UDP)
    {
        /* UDP transport */
        return EndPointOpen(info);
    }

    while(1)
    {
        if (info->isClose == ITS_TRUE)
        {
            return (IDS_ECONNECTFAIL); 
        }

        ret = SOCK_ClientOpen(&info->sockInfo,
                              INET_DOMAIN,
                              info->ipAddr,
                              info->port);
        if (ret != ITS_SUCCESS)
        {
            IDS_TRACE_CRITICAL(("IDSCL_Connect: Create client failed"));

            return (ret);
        }

        if (info->lSockBindInfo.isSet == ITS_TRUE)
        {
            int aSize;
            struct sockaddr_in sin;
            // Initializing Uninitialized Scalar Variable sin_zero of sin
            memset(&sin, 0, sizeof(sockaddr_in));
            IDS_TRACE_DEBUG(("Bind IP=%s Port=%d",info->lSockBindInfo.ipAddr, 
                              info->lSockBindInfo.port));
            /* Buil sock addr */
            sin.sin_family      = AF_INET;
            sin.sin_addr.s_addr = inet_addr(info->lSockBindInfo.ipAddr);
            sin.sin_port        = htons(info->lSockBindInfo.port);
            aSize = sizeof(struct sockaddr_in);
            if(bind(info->sockInfo->socket,(sockaddr *)&sin,
                                        (socklen_t)aSize) < 0)
            {
                IDS_TRACE_ERROR(("SockBind failed IP =%s errno = %d\n",
                                    info->lSockBindInfo.ipAddr, errno));
                return !ITS_SUCCESS;
            }
        }

        /* KEEPALIVE */
#if defined(linux)
        if (isTCPKeepAliveSet == ITS_TRUE)
        {
            int optval = 1;
            socklen_t optlen = sizeof(optval);
            if(setsockopt(info->sockInfo->socket, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) 
            {
                IDS_TRACE_ERROR(("Error :setsockopt() SO_KEEPALIVE \n"));
            }

            optval = timerVal->keepAliveCnt;
            if(setsockopt(info->sockInfo->socket, SOL_TCP, TCP_KEEPCNT, &optval, optlen) < 0) 
            {
                IDS_TRACE_ERROR(("Error :setsockopt() TCP_KEEPCNT \n"));
            }
        
            optval = timerVal->keepAliveIdle;
            if(setsockopt(info->sockInfo->socket, SOL_TCP, TCP_KEEPIDLE, &optval, optlen) < 0)    
            {
                IDS_TRACE_ERROR(("Error :setsockopt() TCP_KEEPIDLE \n"));
            }

            optval = timerVal->keepAliveIntvl;
            if(setsockopt(info->sockInfo->socket, SOL_TCP, TCP_KEEPINTVL, &optval, optlen) < 0)
            {
                IDS_TRACE_ERROR(("Error :setsockopt() TCP_KEEPINTVL \n"));
            }
        }
#endif

        ret = SOCK_ClientConnect(info->sockInfo);
        if (ret != ITS_SUCCESS)
        {
            IDS_TRACE_WARNING(("IDSCL_Connect: Connect failed....re-trying "
                               "ip addr %s and port %d",
                               info->ipAddr, info->port));

            SOCK_Close(info->sockInfo);

            info->sockInfo = NULL;
#ifdef WIN32
            Sleep(sockConInterval);
#else
            sleep(sockConInterval);
#endif
            repeat_count++;
        }
        else
        {   
            info->isUp = ITS_TRUE;

            IDS_TRACE_DEBUG(("IDSCL_Connect:: Connected to server\n"));

            break;
        }
    }

    return (ret);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method puts the event on to the task que.
 *
 *  Input Parameters:
 *      taskTran  -   of type IDSCL_CONNECTION
 *      evt   -   of type ITS_EVENT
 *      
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT 
IDSCL_PutEventOnTaskQue(IDS_TRANS_QUE *taskTran, ITS_EVENT *evt)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT index = 0;

    IDS_TRACE_DEBUG(("IDSCL_PutEventOnTaskQue"));
    
    if (EMLIST_Lock(taskTran->taskQue) != ITS_SUCCESS)
    {
        return (IDS_EBADMUTEX);
    }
    
    ret = EMLIST_PutEvent(taskTran->taskQue,(ITS_CHAR*)evt,sizeof(ITS_EVENT));

    ++taskTran->noCurrEnts;

    EMLIST_Unlock(taskTran->taskQue);
    
    return (ret);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method retrieves the event from the task que.
 *
 *  Input Parameters:
 *      taskTran  -   of type IDSCL_CONNECTION
 *      
 *  Output Parameters:
 *      evt   -   of type ITS_EVENT
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    19-01-07   Enhancement   Freeing data in case of error. 
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT 
IDSCL_GetEventFromTaskQue(IDS_TRANS_QUE *taskTran, ITS_EVENT *evt)
{
    ITS_INT len = 0, ret;
    void *data = 0;

repeat:

    if ((ret = EMLIST_GetNextEventWithTimeOut(taskTran->taskQue,
                       &data, &len,
                       HMI_GetTimeOutInterval())) != ITS_SUCCESS)
    {
        if (ret == IDS_ETIMEOUT)
        {
            goto repeat;
        }

        if (data != NULL)
        {
            ITS_Free(data);
        }
        return (ret);
    }

    memcpy(evt, data, len);
 
    if (EMLIST_Lock(taskTran->taskQue) != ITS_SUCCESS)
    {
        ITS_Free(data);
        return (IDS_EBADMUTEX);
    }

    --taskTran->noCurrEnts;

    EMLIST_Unlock(taskTran->taskQue);

    ITS_Free(data);

    return (ret);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method closes the socket connection with server based on 
 *      the Connection type.
 *      This is for the user to close connection with one server and 
 *      establish conn with new, or may be swap the connection ie primary to 
 *      backup or vice-versa.
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      type - IDS_CONNECTION_TYPE 1 - primary  2- Backup.
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    24-11-06   Enhancement   regStatus set to NOTREGISTERED. 
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_CloseCon(ITS_HANDLE handle , IDS_CONNECTION_TYPE type)
{
    IDS_CONNECTION *conn = NULL;

    IDS_TRACE_DEBUG(("IDSCL_CloseCon"));

    if (handle == NULL)
    {
        return IDS_EINVALIDARGS;
    }

    conn = (IDS_CONNECTION*)handle;

    if(type == IDS_PRIMARY_CONNECTION)
    {
        if (conn->primaryInfo.isUp)
        {
            /* acquire lock */
            MUTEX_AcquireMutex(&regLock);
            SOCK_Close(conn->primaryInfo.sockInfo);
            conn->primaryInfo.sockInfo = NULL;
            conn->primaryInfo.isClose = ITS_TRUE;
            THREAD_DeleteThread(&conn->primaryInfo.thrInfo.info);
            IDSCL_CloseConnection(IDS_PRIMARY_CONNECTION);
            conn->primaryInfo.regStatus = NOTREGISTERED;
            /* release lock */
            MUTEX_ReleaseMutex(&regLock);
        }
    }
    else 
    {
        if (conn->backupInfo.isUp)
        {
            /* acquire lock */
            MUTEX_AcquireMutex(&regLock);
            SOCK_Close(conn->backupInfo.sockInfo);
            conn->backupInfo.sockInfo = NULL;
            conn->backupInfo.isClose = ITS_TRUE;
            // Fixing Free of Address-of-Expression
            //THREAD_DeleteThread(&conn->backupInfo.thrInfo.info);
            IDSCL_CloseConnection(IDS_BACKUP_CONNECTION);
            conn->backupInfo.regStatus = NOTREGISTERED;
            /* release lock */
            MUTEX_ReleaseMutex(&regLock);
        }
    }

    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method is thread function for primary connection.
 *
 *  Input Parameters:
 *      void  *  -   not used 
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
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    19-01-07   Enhancement  free() added before continue statement
 *   Kamakshi    12-03-07   Enhancement  Values reset after deregAck received.
 *
 ****************************************************************************/
#ifdef WIN32
static unsigned __stdcall 
#else
static void *
#endif
PrimaryThreadFunction(void *v)
{
    ITS_EVENT evt;
    ITS_EVENT reRegevt;
    ITS_INT ret = 0, i = 0;
    IDS_MESSAGE msg;

    IDS_TRACE_DEBUG(("PrimaryThreadFunction"));

    memset(&evt, 0, sizeof(ITS_EVENT));

    while(IDS_Connection.primaryInfo.thrInfo.isRunning)
    {
        ret = IDSCL_ReadEvent(&IDS_Connection.primaryInfo, &evt);
        if (ret == ITS_SUCCESS)
        {
            IDS_TRACE_DEBUG(("\nMessage from server event len:%d\n",evt.len));
            IDSCL_Print(evt.data, evt.len);
            
            if (evt.src == ITS_APP_SRC)
            {
                if (evt.data[sizeof(ITS_UINT)] == REGISTER_ACK_MSG) 
                {
                    IDS_TRACE_DEBUG(("PThreadFunction: REGISTER_ACK_MSG"));

                    ProcessRegAckAndStatus(evt);
    
                    if (IDS_Connection.primaryInfo.regStatus != SUCCESS)
                    {
                        IDS_Connection.primaryInfo.regStatus =
                                (IDS_REG_STATUS)evt.data[sizeof(ITS_UINT)+
                                        sizeof(ITS_OCTET) + sizeof(ITS_OCTET)];
                    }
                }
                else if (evt.data[sizeof(ITS_UINT)] == SERVER_STATUS_MSG)
                {
                    IDS_TRACE_DEBUG(("PThreadFunction: SERVER_STATUS_MSG"));

                    ProcessRegAckAndStatus(evt);

                    /* Free the event */
                    free(evt.data);
                    evt.data = NULL;

                    continue;
                }
                else if (evt.data[sizeof(ITS_UINT)] == DEREGISTER_ACK_MSG)
                {
                    IDS_TRACE_DEBUG(("PThreadFunction: DEREGISTER_ACK_MSG"));

                    ret = evt.data[sizeof(ITS_UINT)+
                                        sizeof(ITS_OCTET) + sizeof(ITS_OCTET)];
                    if (ret == SUCCESS)
                    {
                        IDS_Connection.primaryInfo.regStatus = NOTREGISTERED;
                        /* Reset the values */
                        if (!IDS_Connection.backupInfo.isUp)
                        {
                            IDS_Connection.clid = 0;
                            IDS_Connection.regInfoLen = 0;
                            if (IDS_Connection.reRegInfo != NULL)
                            {
                                free(IDS_Connection.reRegInfo);
                                IDS_Connection.reRegInfo = NULL;
                            }
                        }
                    }
                }
                else if (evt.data[sizeof(ITS_UINT)] == HEARTBEAT_MSG)
                {
                    ProcessHeartBeat((ITS_HANDLE*)&IDS_Connection.primaryInfo);

                    /* Free the event */
                    free(evt.data);
                    evt.data = NULL;

                    continue;
                }

                ret = IDSCL_PutEventOnTaskQue(&IDS_Connection.taskTrans,
                                                 &evt);

                if (ret != ITS_SUCCESS)
                {
                    IDS_TRACE_ERROR(("PrimaryThreadFunction: PutEvent fail"));
                }
            }
        }
        else if (ret == IDS_ENOSOCKET)
        {
            continue;
        }    
        else if (ret == IDS_ERCVFAIL)
        {
            IDS_TRACE_ERROR(("PrimaryThreadFunction:Primary connection down"));

            SOCK_Close(IDS_Connection.primaryInfo.sockInfo);

            IDS_Connection.primaryInfo.sockInfo = NULL;
            IDS_Connection.primaryInfo.isPrimary = ITS_FALSE;
   
            /* Invoke CallBack */
            IDS_CALLBACK_INFO idsCbInfo;
            idsCbInfo.type = IDS_DISCONNECT;
            idsCbInfo.ids_stat.port = IDS_Connection.primaryInfo.port;
            memcpy(idsCbInfo.ids_stat.ipAddr,IDS_Connection.primaryInfo.ipAddr,
                   sizeof(IDSCL_IP_ADDR_LEN));
            idsCbInfo.ids_stat.conType = IDS_PRIMARY_CONNECTION;
            idsCbInfo.isConUp = IDS_FALSE;
            idsCbInfo.regStatus = NOTREGISTERED;
            idsCbInfo.isPrimary = IDS_Connection.primaryInfo.isPrimary;
            /* invoking the callback with primary info*/
            if (IDS_Connection.func)
            {
                IDS_Connection.func(idsCbInfo);
            }
            else
            {
                IDS_TRACE_DEBUG(("\nCallback is not configured \n"));
            }

           /* If Server connection is down wait for some time 
              before try to re-connect */
#ifdef WIN32
            Sleep(SOC_CONNECT_INTERVAL);
#else
            sleep(SOC_CONNECT_INTERVAL);
#endif

            /* Try to reconnect */
            ret = IDSCL_Connect(&IDS_Connection.primaryInfo, &IDS_Connection.tcpTimer);
            if (ret != ITS_SUCCESS)
            {
                if (ret == IDS_ECONNECTFAIL)
                {
                    continue;
                }

                IDS_TRACE_CRITICAL(("PrimaryThreadFunction: Thread exit %d", 
                                                                       ret));

                IDS_Connection.primaryInfo.thrInfo.isRunning = ITS_FALSE;
            }
            else
            {
                IDS_TRACE_DEBUG(("PrimThreadFunction: Connection re-estd."));

                /* Extra check for non redundant */
                if(IDS_Connection.backupInfo.isUp == ITS_FALSE)
                {
                    IDS_Connection.primaryInfo.isPrimary = ITS_TRUE;
                }

                /**
                 * storing the callback information in variable and passing it
                 * in callback function. This callback is used to notify the 
                 * application that the Primary connection with IDS is up.
                 */
                IDS_CALLBACK_INFO idsCbInfo;
                idsCbInfo.type = IDS_CONNECT;
                idsCbInfo.ids_stat.port = IDS_Connection.primaryInfo.port;
                memcpy(idsCbInfo.ids_stat.ipAddr,IDS_Connection.primaryInfo.ipAddr,
                       sizeof(IDSCL_IP_ADDR_LEN));                       
                idsCbInfo.ids_stat.conType = IDS_PRIMARY_CONNECTION; 
                idsCbInfo.isConUp = IDS_TRUE;
                idsCbInfo.regStatus = NOTREGISTERED;
                idsCbInfo.isPrimary = IDS_Connection.primaryInfo.isPrimary;
                /* invoking the callback with primary info*/
                if (IDS_Connection.func)
                {
                    idsCbInfo.isConClose = false;
                    IDS_Connection.func(idsCbInfo);
                }
                else
                {
                    IDS_TRACE_DEBUG(("\nCallback is not configured \n"));
                } 
               continue;
            }
        } 
    }

    MUTEX_AcquireMutex(&regLock);

    if(IDS_Connection.primaryInfo.sockInfo)
    {
        SOCK_Close(IDS_Connection.primaryInfo.sockInfo);
        IDS_Connection.primaryInfo.sockInfo = NULL;
    }

    IDSCL_CloseConnection(IDS_PRIMARY_CONNECTION); 

    MUTEX_ReleaseMutex(&regLock);

    //Fixing  Free of address-of-expression  
    //THREAD_DeleteThread(&IDS_Connection.primaryInfo.thrInfo.info);

    return NULL;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method is thread function for backup connection.
 *
 *  Input Parameters:
 *      void  *  -   not used 
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
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    19-01-07   Enhancement  free() added before continue statement
 *   Kamakshi    12-03-07   Enhancement  Values reset after deregAck received.
 *
 ****************************************************************************/
#ifdef WIN32
unsigned __stdcall 
#else
static void *
#endif
BackupThreadFunction(void *v)
{
    ITS_EVENT evt;
    ITS_EVENT reRegevt;
    ITS_INT ret =0, i = 0;
   
    IDS_TRACE_DEBUG(("BackupThreadFunction"));
 
    memset(&evt, 0, sizeof(ITS_EVENT));

    while(IDS_Connection.backupInfo.thrInfo.isRunning)
    {
        ret = IDSCL_ReadEvent(&IDS_Connection.backupInfo, &evt);
        if (ret == ITS_SUCCESS)
        {

            IDS_TRACE_DEBUG(("\nMessage from server event len:%d\n",evt.len));
            IDSCL_Print(evt.data, evt.len);

            if (evt.src == ITS_APP_SRC)
            {
                if (evt.data[sizeof(ITS_UINT)] == REGISTER_ACK_MSG)
                {
                    IDS_TRACE_DEBUG(("BThreadFunction: REGISTER_ACK_MSG"));

                    ProcessRegAckAndStatus(evt);
                    if (IDS_Connection.backupInfo.regStatus != SUCCESS)
                    {
                        IDS_Connection.backupInfo.regStatus =
                                (IDS_REG_STATUS)evt.data[sizeof(ITS_UINT)+
                                        sizeof(ITS_OCTET) + sizeof(ITS_OCTET)];
                    }
                    
                }
                else if (evt.data[sizeof(ITS_UINT)] == SERVER_STATUS_MSG)
                {
                    IDS_TRACE_DEBUG(("BThreadFunction: SERVER_STATUS_MSG"));

                    ProcessRegAckAndStatus(evt);

                    /* Free the event */
                    free(evt.data);
                    evt.data = NULL;

                    continue;
                }
                else if (evt.data[sizeof(ITS_UINT)] == DEREGISTER_ACK_MSG)
                {
                    IDS_TRACE_DEBUG(("BThreadFunction: DEREGISTER_ACK_MSG"));
       
                    ret = evt.data[sizeof(ITS_UINT)+
                                        sizeof(ITS_OCTET) + sizeof(ITS_OCTET)];

                    if (ret == SUCCESS)
                    {
                        IDS_Connection.backupInfo.regStatus = NOTREGISTERED;
                        /* Reset the values */
                        if (!IDS_Connection.primaryInfo.isUp)
                        {
                            IDS_Connection.clid = 0;
                            IDS_Connection.regInfoLen = 0;
                            if (IDS_Connection.reRegInfo != NULL)
                            {
                                free(IDS_Connection.reRegInfo);
                                IDS_Connection.reRegInfo = NULL;
                            }
                        }
                    }
                }
                else if (evt.data[sizeof(ITS_UINT)] == HEARTBEAT_MSG)
                {
                    ProcessHeartBeat((ITS_HANDLE*)&IDS_Connection.backupInfo);

                    /* Free the event */
                    free(evt.data);
                    evt.data = NULL;

                    continue;
                }

                ret = IDSCL_PutEventOnTaskQue(&IDS_Connection.taskTrans,
                                                 &evt);

                if (ret != ITS_SUCCESS)
                {
                     IDS_TRACE_ERROR(("BackupThreadFunction: PutEvent fail"));
                }
            }
        }
        else if (ret == IDS_ENOSOCKET)
        {
            continue;
        }
        else if (ret == IDS_ERCVFAIL)
        {
            IDS_TRACE_ERROR(("BackupThreadFunction: Backup connection down"));
            
            SOCK_Close(IDS_Connection.backupInfo.sockInfo);
            IDS_Connection.backupInfo.sockInfo = NULL;
            IDS_Connection.backupInfo.isPrimary = ITS_FALSE;

            /* Invoke CallBack */
            IDS_CALLBACK_INFO idsCbInfo;
            idsCbInfo.type = IDS_DISCONNECT;
            idsCbInfo.ids_stat.port = IDS_Connection.primaryInfo.port;
            memcpy(idsCbInfo.ids_stat.ipAddr,IDS_Connection.backupInfo.ipAddr,
                   sizeof(IDSCL_IP_ADDR_LEN));
            idsCbInfo.ids_stat.conType = IDS_BACKUP_CONNECTION;
            idsCbInfo.isConUp = IDS_FALSE;
            idsCbInfo.regStatus = NOTREGISTERED;
            idsCbInfo.isPrimary = IDS_Connection.backupInfo.isPrimary;
            /* invoking the callback with primary info*/
            if (IDS_Connection.func)
            {
                IDS_Connection.func(idsCbInfo);
            }
            else
            {
                IDS_TRACE_DEBUG(("\nCallback is not configured \n"));
            }

            ret = IDSCL_Connect(&IDS_Connection.backupInfo, &IDS_Connection.tcpTimer);
            if (ret != ITS_SUCCESS)
            {
                if (ret == IDS_ECONNECTFAIL)
                {
                    continue;
                }

                IDS_TRACE_CRITICAL(("BackupThreadFunction: Thread exit %d",
                                                                       ret));
                IDS_Connection.backupInfo.thrInfo.isRunning = ITS_FALSE;
            }
            else
            {
                IDS_TRACE_DEBUG(("BackupThreadFunction: Connection re-estd."));

                /* Extra check for non redundant */
                if(IDS_Connection.primaryInfo.isUp == ITS_FALSE)
                {
                    IDS_Connection.backupInfo.isPrimary = ITS_TRUE;
                }

                /**
                 * storing the callback information in variable and passing it
                 * in callback function. This callback is used to notify the
                 * application that the Backup connection with IDS is up.
                 */
                IDS_CALLBACK_INFO idsCbInfo;
                idsCbInfo.ids_stat.port = IDS_Connection.backupInfo.port;
                memcpy(idsCbInfo.ids_stat.ipAddr,IDS_Connection.backupInfo.ipAddr,
                       sizeof(IDSCL_IP_ADDR_LEN));
                idsCbInfo.ids_stat.conType = IDS_BACKUP_CONNECTION;
                idsCbInfo.isConUp = IDS_TRUE;
                idsCbInfo.regStatus = NOTREGISTERED;
                idsCbInfo.isPrimary = IDS_Connection.backupInfo.isPrimary;

                /* invoking the callback with backup info*/
                if (IDS_Connection.func)
                {
                    idsCbInfo.isConClose = false;
                    IDS_Connection.func(idsCbInfo);
                }

                continue;
            }
        } 
    }

    MUTEX_AcquireMutex(&regLock);

    if(IDS_Connection.backupInfo.sockInfo)
    {
        SOCK_Close(IDS_Connection.backupInfo.sockInfo);
        IDS_Connection.backupInfo.sockInfo = NULL;
    }

    IDSCL_CloseConnection(IDS_BACKUP_CONNECTION);

    MUTEX_ReleaseMutex(&regLock);

    //Fixing Free of address-of-expression
    //THREAD_DeleteThread(&IDS_Connection.backupInfo.thrInfo.info);

    return NULL;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method is thread function for primary connection.
 *
 *  Input Parameters:
 *      void  *  -   not used
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
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 ****************************************************************************/
#ifdef WIN32
static unsigned __stdcall
#else
static void *
#endif
SenderThread(void *v)
{
    ITS_EVENT evt;
    ITS_INT ret = 0;

    IDS_TRACE_DEBUG(("SenderThread"));

    memset(&evt, 0, sizeof(ITS_EVENT));
    while(IDS_Connection.primaryInfo.thrInfo.isRunning ||
          IDS_Connection.backupInfo.thrInfo.isRunning)
    {
        ret = IDSCL_GetNextOutGoingEvent(ISS7_Stack, &evt);
        if (ret == ITS_SUCCESS)
        {
             /* Convert received event */
             ret = IDSCL_SendEvent(ISS7_Stack, &evt);
        }
    }

    //Fixing Freeing global variable which is not pointer 
    //THREAD_DeleteThread(&sendThreadInfo);

    isSThreadRunning = ITS_FALSE;
 
    return NULL;

}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method pre intializes 
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs int if ITS_SUCCESS 
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    19-01-07   Enhancement   CreateTracing() called before Enable 
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_PreInitialize(ITS_HANDLE *handle)
{
    ITS_INT ret = ITS_SUCCESS;

    LICENSE_LoadIfEnabled();

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_DIAMETER))
    {
        return ITS_ENOLICENSE;
    }

    IDSCL_CreateTracing();
    IDSCL_EnableTracing();

    IDS_TRACE_DEBUG(("IDSCL_PreInitialize"));

    /*primary initialization*/
    IDS_Connection.primaryInfo.thrInfo.func = (ITS_THREAD_FUNC)PrimaryThreadFunction;
    IDS_Connection.primaryInfo.thrInfo.isRunning = ITS_FALSE;
    IDS_Connection.primaryInfo.isUp = ITS_FALSE;
    IDS_Connection.primaryInfo.isInitialized = ITS_FALSE;
    IDS_Connection.primaryInfo.isClose = ITS_FALSE;
    IDS_Connection.primaryInfo.sockInfo = NULL;
    IDS_Connection.primaryInfo.isPrimary = ITS_FALSE;
    IDS_Connection.primaryInfo.regStatus = NOTREGISTERED;
    IDS_Connection.primaryInfo.transType = IDS_TCP;

    if (MUTEX_CreateMutex(&IDS_Connection.primaryInfo.readLock, 0) 
                                                            != ITS_SUCCESS)
    {
        IDS_TRACE_CRITICAL(("Failed to create mutex"));

        return (IDS_ENOMUTEX);
    }

    if (MUTEX_CreateMutex(&IDS_Connection.primaryInfo.writeLock, 0) 
                                                             != ITS_SUCCESS)
    {
        IDS_TRACE_CRITICAL(("Failed to create mutex"));

        return  (IDS_ENOMUTEX);
    }

    if (MUTEX_CreateMutex(&hashLock, 0) != ITS_SUCCESS)
    {
        IDS_TRACE_CRITICAL(("Failed to create mutex"));

        return (IDS_ENOMUTEX);
    }

    if (MUTEX_CreateMutex(&regLock, 0) != ITS_SUCCESS)
    {
        IDS_TRACE_CRITICAL(("Failed to create mutex"));

        return (IDS_ENOMUTEX);
    }

    /*Back up initialization*/
    IDS_Connection.backupInfo.thrInfo.func = (ITS_THREAD_FUNC)BackupThreadFunction;
    IDS_Connection.backupInfo.thrInfo.isRunning = ITS_FALSE;
    IDS_Connection.backupInfo.isUp = ITS_FALSE;
    IDS_Connection.backupInfo.isInitialized = ITS_FALSE;
    IDS_Connection.backupInfo.isClose = ITS_FALSE;
    IDS_Connection.backupInfo.sockInfo = NULL;
    IDS_Connection.backupInfo.isPrimary = ITS_FALSE;
    IDS_Connection.backupInfo.regStatus = NOTREGISTERED;
    IDS_Connection.backupInfo.transType = IDS_TCP;

    if (MUTEX_CreateMutex(&IDS_Connection.backupInfo.readLock, 0) 
                                                         != ITS_SUCCESS)
    {
        IDS_TRACE_CRITICAL(("Failed to create mutex"));

        return (IDS_ENOMUTEX);
    }

    if (MUTEX_CreateMutex(&IDS_Connection.backupInfo.writeLock, 0) 
                                                         != ITS_SUCCESS)
    {
        IDS_TRACE_CRITICAL(("Failed to create mutex"));

        return (IDS_ENOMUTEX);
    }

    /* Create Task Que for client */
    IDS_Connection.taskTrans.taskQue = EMLIST_Create();
 
    /* Create Task Que for Sender thread */
    IDS_Connection.outBoundTaskTrans.taskQue = EMLIST_Create();

    IDS_Connection.clid = 0;
    IDS_Connection.reRegInfo = NULL;
    IDS_Connection.regInfoLen = 0;

    *handle = IDSCL_GetHandle();

    return (ret);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method creates a client stream socket and connects to the server
 *      socket
 *
 *  Input Parameters:
 *      host  - host machine IP address.
 *      port  - port number of the server
 *      type - IDS_CONNECTION_TYPE 0- primary 1-Backup.
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns int. 
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    12-12-06   Bug Id 5049   Allow initilization with backup when 
 *                                        primary is not up(trying to connect). 
 *   Kamakshi    29-01-07   Bug           Check primary srv port along with IP 
 *   Kamakshi    19-02-07   Enhancement   Trace added for Initialize failure. 
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_Initialize(const char *host, ITS_INT port, IDS_TRANS_TYPE tType)
{
    ITS_INT ret = ITS_SUCCESS;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_DIAMETER))
    {
        return ITS_ENOLICENSE;
    }

    IDS_TRACE_DEBUG(("IDSCL_Initialize"));

    if (host == NULL)
    {
        IDS_TRACE_ERROR(("IDSCL_Initialize: No host configured"));

        return (IDS_EINVALIDARGS);
    }

    if ((IDS_Connection.primaryInfo.isInitialized != ITS_TRUE) &&
        (strcmp(IDS_Connection.primaryInfo.ipAddr, "\0") == 0 ||
         (strcmp(IDS_Connection.primaryInfo.ipAddr, host) == 0 && 
          IDS_Connection.primaryInfo.port == port) ) )
    {
        memcpy(&IDS_Connection.primaryInfo.ipAddr, host, strlen(host));

        IDS_Connection.primaryInfo.port = port;
        IDS_Connection.primaryInfo.isClose = ITS_FALSE;
        IDS_Connection.primaryInfo.transType = tType;

        ret = IDSCL_Connect(&IDS_Connection.primaryInfo, &IDS_Connection.tcpTimer);
        if (ret == ITS_SUCCESS)
        {
            IDS_TRACE_DEBUG(("IDSCL_Initialize: Connection confirmed"));
        }
        else if (ret == IDS_ENOSOCKET)
        {
            IDS_TRACE_ERROR(("IDSCL_Initialize: Attempt to connect failed"));
            IDS_TRACE_ERROR(("Server IP Addr %s and Port %d\n",
                    IDS_Connection.primaryInfo.ipAddr,
                    IDS_Connection.primaryInfo.port));

            IDSCL_CloseConnection(IDS_PRIMARY_CONNECTION);

            return (ret);
        }
        else
        {
            IDS_TRACE_CRITICAL(("IDSCL_Initialize: Failed to initialize primary connection !!"));
            IDS_TRACE_ERROR(("Server IP Addr '%s' and Port '%d'\n",
                    IDS_Connection.primaryInfo.ipAddr,
                    IDS_Connection.primaryInfo.port));

            return (ret);
        }

        IDS_Connection.primaryInfo.isUp = ITS_TRUE;
        IDS_Connection.primaryInfo.thrInfo.isRunning = ITS_TRUE;

        THREAD_CreateThread(&IDS_Connection.primaryInfo.thrInfo.info,
                            0,
                            IDS_Connection.primaryInfo.thrInfo.func,
                            NULL,
                            ITS_TRUE);

        IDS_Connection.primaryInfo.isInitialized = ITS_TRUE;
    }
    else
    {
        if (IDS_Connection.backupInfo.isInitialized == ITS_TRUE)
        {
            IDS_TRACE_ERROR(("IDSCL_Initialize: Backup already connected")); 

            return (IDS_EINUSE);
        }

        if (IDS_Connection.primaryInfo.port == port
            && strcmp(IDS_Connection.primaryInfo.ipAddr, host) == 0)
        {
            IDS_TRACE_ERROR(("IDSCL_Initialize: Duplicate server"));

            return (IDS_EINUSE);
        }
 
        memcpy(&IDS_Connection.backupInfo.ipAddr, host, strlen(host));

        IDS_Connection.backupInfo.port = port;
        IDS_Connection.backupInfo.isClose = ITS_FALSE;
        IDS_Connection.backupInfo.transType = tType;

        ret = IDSCL_Connect(&IDS_Connection.backupInfo, &IDS_Connection.tcpTimer);
        if (ret == ITS_SUCCESS)
        {
            IDS_TRACE_DEBUG(("IDSCL_Initialize: Connection confirmed"));
        }
        else if (ret == IDS_ENOSOCKET)
        {
            IDS_TRACE_ERROR(("IDSCL_Initialize: Attempt to connect failed"));
            IDS_TRACE_ERROR(("Server IP Addr %s and Port %d\n",
                    IDS_Connection.backupInfo.ipAddr,
                    IDS_Connection.backupInfo.port));

            IDSCL_CloseConnection(IDS_BACKUP_CONNECTION);

            return (ret);
        }
        else
        {
            IDS_TRACE_CRITICAL(("IDSCL_Initialize: Failed to initialize backup  connection !!"));
            if (strcmp(IDS_Connection.backupInfo.ipAddr, "\0") != 0)
            {
                IDS_TRACE_ERROR(("Server IP Addr '%s' and Port '%d'\n",
                    IDS_Connection.backupInfo.ipAddr,
                    IDS_Connection.backupInfo.port));
            }

            return (ret);
        }

        if (IDS_Connection.backupInfo.sockInfo == NULL)
        {
            return (IDS_ENOSOCKET);
        }

        IDS_Connection.backupInfo.isUp = ITS_TRUE;
        IDS_Connection.backupInfo.thrInfo.isRunning = ITS_TRUE;
        THREAD_CreateThread(&IDS_Connection.backupInfo.thrInfo.info,
                            0,
                            IDS_Connection.backupInfo.thrInfo.func,
                            NULL,
                            ITS_TRUE);
        IDS_Connection.backupInfo.isInitialized = ITS_TRUE;

    }
    /* Dispatch thread which handles out going messages */
    if (!isSThreadRunning)
    {
        THREAD_CreateThread(&sendThreadInfo,
                        0,
                        (ITS_THREAD_FUNC)SenderThread,
                        NULL,
                        ITS_TRUE);
        isSThreadRunning = ITS_TRUE;
    }
    return (ITS_SUCCESS);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method do the clean up job
 *
 *  Input Parameters:
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
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    19-01-07   Enhancement   Disable and Delete Trace APIs added
 *
 ****************************************************************************/
IDSCL_DLLAPI void
IDSCL_Terminate()
{
    IDS_TRACE_DEBUG(("IDSCL_Terminate"));

    IDS_Connection.primaryInfo.thrInfo.isRunning = ITS_FALSE;
    IDS_Connection.backupInfo.thrInfo.isRunning = ITS_FALSE;
    isSThreadRunning = ITS_FALSE;

    MUTEX_DeleteMutex(&IDS_Connection.primaryInfo.readLock); 
    MUTEX_DeleteMutex(&IDS_Connection.primaryInfo.writeLock); 
    
    MUTEX_DeleteMutex(&IDS_Connection.backupInfo.readLock); 
    MUTEX_DeleteMutex(&IDS_Connection.backupInfo.writeLock); 

    EMLIST_Delete(IDS_Connection.taskTrans.taskQue);

    if (IDS_Connection.primaryInfo.sockInfo)
    {
        IDSCL_CloseConnection(IDS_PRIMARY_CONNECTION);
    }

    if (IDS_Connection.backupInfo.sockInfo)
    {
        IDSCL_CloseConnection(IDS_BACKUP_CONNECTION);
    }
   
    if (IDS_HostInfo.originHost)
    {
       free(IDS_HostInfo.originHost);
       IDS_HostInfo.originHost = NULL;
    }
    if (IDS_HostInfo.originRealm)
    {
       free(IDS_HostInfo.originRealm);
       IDS_HostInfo.originRealm = NULL;
    }

    IDSCL_DisableTracing();
    IDSCL_DeleteTracing();
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method registers the routing info with server.
 *      socket
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      msg - IDS_MESSAGE structure pointer which contains 
 *                          Deregistration information.
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    24-11-06   Enhancement   Reassigning regInfo->conType,removed. 
 *   Kamakshi    14-12-06   Enhancement   Register only if not registered. 
 *   Kamakshi    19-01-07   Enhancement   free primevt & bckevt during error. 
 *   Kamakshi    12-03-07   BridgeWater   Allow multiple Register from client.
 *                                        ClientId validated using the handle.
 *   Hemant      01-10-07   Bridgewater   Added IDS_UINT as default
 *                                        argument Sending the Registration 
 *                                        Message to Pri(1)/Bkup(2)/Both(0).
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_Register(ITS_HANDLE handle, IDS_MESSAGE *msg, IDS_UINT conType)
{
    ITS_EVENT primevt;
    ITS_EVENT bckevt;
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT index = 0;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_DIAMETER))
    {
        return ITS_ENOLICENSE;
    }

    IDS_TRACE_DEBUG(("IDSCL_Register"));

    if (!msg->u.regInfo.connectionType)
    {
        return (IDS_EMISSINGMANDPRM);
    }

    if (msg->clientID <= 0)
    {
        IDS_TRACE_ERROR(("IDSCL_Register: Not a valid client ID"));

        return (IDS_EMISSINGMANDPRM);
    }

    /* validate the clientId with that in the handle */
    IDS_CONNECTION *tmpConInfo = (IDS_CONNECTION*)handle;
    if ((tmpConInfo->clid != 0) && (tmpConInfo->clid != msg->clientID))
    {
        IDS_TRACE_ERROR(("IDSCL_Register: client ID cannot be changed"));

        return (IDS_EMISSINGMANDPRM);
    }

    IDS_ClientID = msg->clientID;

    /* validate the msg */
    if ((ret = IDSCL_ValidateContext(&msg->u.regInfo)) != ITS_SUCCESS)
    {
        IDS_TRACE_ERROR(("IDSCL_Register: Registration invalid"));

        return (ret);
    }

    /**
     * Check to validate that the connection type is one of the following 
     * Both (0 - by default), Primary(1), Secondary(2) else indicate error.
     */
    if (!(conType == 0 || 
          conType == IDS_PRIMARY_CONNECTION ||
          conType == IDS_BACKUP_CONNECTION))
    {
        IDS_TRACE_ERROR(("IDSCL_Register: Invalid Connection Type")); 
        return (!ITS_SUCCESS);
    } 
 
    /**
     * Check to validate if  primary connection or both 
     * send the event. 
     */
    if (conType == 0 || conType == IDS_PRIMARY_CONNECTION)
    { 
        if (IDS_Connection.primaryInfo.isUp == ITS_TRUE)
        {
            /* form a register event and send to server*/
            ITS_EVENT_INIT(&primevt, ITS_APP_SRC, sizeof(IDS_MESSAGE));
        
            if(IDSCL_Encode(msg, &primevt)!= ITS_SUCCESS)
            {
                ITS_EVENT_TERM(&primevt);
                return (!ITS_SUCCESS);
            }

            IDS_TRACE_DEBUG(("\nRegistration message to primary server...\n")); 
            IDSCL_Print(primevt.data, primevt.len);

            ret = IDSCL_WriteEvent((ITS_HANDLE*)&IDS_Connection.primaryInfo, 
                                                               &primevt);
        }
        else
        {
            IDS_TRACE_ERROR(("IDSCL_Register: No primary connection"));

            ret = !ITS_SUCCESS;
        }
    }
 
    /**
     * Check to validate if  backup connection or both 
     * send the event. 
     */
    if (conType == 0 || conType == IDS_BACKUP_CONNECTION)
    { 
        if (IDS_Connection.backupInfo.sockInfo != NULL)
        {
            if (IDS_Connection.backupInfo.isUp == ITS_TRUE)
            {
                /* form a register event and send to server*/
                ITS_EVENT_INIT(&bckevt, ITS_APP_SRC, (sizeof(IDS_MESSAGE)));

                if(IDSCL_Encode(msg, &bckevt)!= ITS_SUCCESS)
                {
                    ITS_EVENT_TERM(&bckevt);
                    return (!ITS_SUCCESS);
                }

                IDS_TRACE_DEBUG(("\nRegistration message to backup server...\n"));
                IDSCL_Print(bckevt.data, bckevt.len);

                ret = IDSCL_WriteEvent((ITS_HANDLE*)&IDS_Connection.backupInfo,
                                                                &bckevt);
            }
            else
            {
                ret = !ITS_SUCCESS;
            }
        }
        else
        {
            IDS_TRACE_ERROR(("IDSCL_Register: No backup connection"));
        }
    }

    IDS_Connection.clid = msg->clientID; 

    return (ret);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method deregerters the routing info with the server
 *      socket
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      msg - IDS_MESSAGE structure pointer which contains 
 *                          Deregistration information.
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    12-03-07   Enhancement   ClientId taken from the handle. 
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_Deregister(ITS_HANDLE handle, IDS_MESSAGE *msg)
{
    ITS_EVENT evt;
    ITS_INT index = 0;
        
    IDS_TRACE_DEBUG(("IDSCL_Deregister"));                                                                        
    IDS_CONNECTION *tmpConInfo = (IDS_CONNECTION*)handle;
    msg->clientID = tmpConInfo->clid;

    /* form a Deregister event and send to server for primary conn */

    if (IDS_Connection.primaryInfo.isUp)
    {
        ITS_EVENT_INIT(&evt, ITS_APP_SRC, sizeof(IDS_MESSAGE));

        if(IDSCL_Encode(msg, &evt) == ITS_SUCCESS)
        { 
            IDSCL_WriteEvent((ITS_HANDLE*)&IDS_Connection.primaryInfo,
                                                               &evt);
        }
    }

    /* form a Deregister event and send to server for backup conn */

    if (IDS_Connection.backupInfo.isUp)
    {
        ITS_EVENT_INIT(&evt, ITS_APP_SRC, sizeof(IDS_MESSAGE));

        if(IDSCL_Encode(msg, &evt) == ITS_SUCCESS)
        {
            IDSCL_WriteEvent((ITS_HANDLE*)&IDS_Connection.backupInfo,
                           &evt);
        }
    }

    MUTEX_AcquireMutex(&regLock);

    if (IDS_Connection.regInfoLen)
    {
        IDS_Connection.regInfoLen = 0;
    }

    if(IDS_Connection.reRegInfo != NULL)
    {
        free(IDS_Connection.reRegInfo);
        IDS_Connection.reRegInfo = NULL; 
    }

    MUTEX_ReleaseMutex(&regLock);

    return (ITS_SUCCESS);
}


/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method retrives new event comming from server
 *
 *  Input Parameters:
 *      handle  - ITS_HANDLE  
 *      evt    - ITS_EVENT * 
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS if succeeds else returns ITS_ERCVFAIL
 *
 *  Notes:
 *      It retrun ITS_ERCVFAIL if it lost connection with server
 *      in that case user supposed to re Initialize the connection
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    19-01-07   Enhancement    evt used instead of clevt variable
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_GetNextEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    ITS_INT ret = ITS_SUCCESS;
    IDS_CONNECTION *conn = (IDS_CONNECTION*)handle;
    ITS_EVENT clevt;

    if (conn == NULL)
    {
        IDS_TRACE_ERROR(("IDSCL_GetNextEvent: Handle is null")); 

        return (IDS_EINVALIDARGS);
    }

    ret = IDSCL_GetEventFromTaskQue(&conn->taskTrans, evt);
    if (ret != ITS_SUCCESS)
    {
        IDS_TRACE_ERROR(("IDSCL_GetNextEvent:Get event failed %d\n",ret));

        return (ret);
    }

    return (ITS_SUCCESS);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method retrives new event comming from application
 *
 *  Input Parameters:
 *      handle  - ITS_HANDLE
 *      evt    - ITS_EVENT *
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS if succeeds else returns ITS_ERCVFAIL
 *
 *  Notes:
 *      It retrun ITS_ERCVFAIL if it lost connection with server
 *      in that case user supposed to re Initialize the connection
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_GetNextOutGoingEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    ITS_INT ret = ITS_SUCCESS;
    IDS_CONNECTION *conn = (IDS_CONNECTION*)handle;

    if (conn == NULL)
    {
        IDS_TRACE_ERROR(("IDSCL_GetNextOutGoingEvent: Handle is null"));

        return (IDS_EINVALIDARGS);
    }

    ret = IDSCL_GetEventFromTaskQue(&conn->outBoundTaskTrans, evt);
    if (ret != ITS_SUCCESS)
    {
      IDS_TRACE_ERROR(("IDSCL_GetNextOutGoingEvent:Get event failed %d\n",ret));

        return (ret);
    }

    return (ITS_SUCCESS);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method retrives new event comming from server
 *
 *  Input Parameters:
 *      handle  - ITS_HANDLE
 *      evt    - ITS_EVENT *
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS if succeeds else returns ITS_ERCVFAIL
 *
 *  Notes:
 *      It retrun ITS_ERCVFAIL if it lost connection with server
 *      in that case user supposed to re Initialize the connection
 *  See Also:
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_Receive(ITS_HANDLE handle, IDS_MESSAGE *msg)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_EVENT ev;
    IDS_CALLBACK_INFO idsCbInfo;

    IDS_TRACE_DEBUG(("IDSCL_Receive"));

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_DIAMETER))
    {
        return ITS_ENOLICENSE;
    }

    ret = IDSCL_GetNextEvent(handle, &ev);
    if (ret == ITS_SUCCESS)
    {
        ret = IDSCL_Decode(msg, &ev);
    }

    if (msg->u.diaInfo.indication == OVERLOAD_IND_FROM_STACK)
    {
        ovrLoadF = ITS_TRUE;
        idsCbInfo.type = IDS_OVERLOAD;
          
    }
    if(msg->u.diaInfo.indication == OVLD_ABATED_IND_FROM_STACK)
    {
        ovrLoadF = ITS_FALSE;
        idsCbInfo.type = IDS_OVERLOAD_ABATED; 
    }

    if(msg->u.diaInfo.indication == OVERLOAD_IND_FROM_STACK ||
       msg->u.diaInfo.indication == OVLD_ABATED_IND_FROM_STACK)
    {  
        /* invoking the callback with overload info*/
        if(IDS_Connection.primaryInfo.isPrimary)
        { 
             idsCbInfo.isPrimary = IDS_Connection.primaryInfo.isPrimary; 
             idsCbInfo.ids_stat.port = IDS_Connection.primaryInfo.port;
             memcpy(idsCbInfo.ids_stat.ipAddr,IDS_Connection.primaryInfo.ipAddr,
                          sizeof(IDSCL_IP_ADDR_LEN));
             idsCbInfo.ids_stat.conType = IDS_PRIMARY_CONNECTION;
             idsCbInfo.isConUp = IDS_TRUE;
             idsCbInfo.regStatus = SUCCESS;
        }
        else
        {
             idsCbInfo.ids_stat.port = IDS_Connection.backupInfo.port;
             memcpy(idsCbInfo.ids_stat.ipAddr,IDS_Connection.backupInfo.ipAddr,
                                            sizeof(IDSCL_IP_ADDR_LEN));
             idsCbInfo.ids_stat.conType = IDS_BACKUP_CONNECTION;
             idsCbInfo.isConUp = IDS_TRUE;
             idsCbInfo.regStatus = SUCCESS;
             idsCbInfo.isPrimary = IDS_Connection.backupInfo.isPrimary;
        }

        if (IDS_Connection.func)
        {
            idsCbInfo.isConClose = false;
            IDS_Connection.func(idsCbInfo);
        }
        else
        {
            IDS_TRACE_DEBUG(("\nCallback is not configured \n"));
        }
    }
    if (ev.data)
    {
        free(ev.data);
        ev.data = NULL;
    }

    return (ret);
}

/*implemt: public
 ****************************************************************************
 *  Purpose: Reset the flag values, required to close the connection.
 *
 *  Input Parameters:
 *      type IDS_CONNECTION_TYPE 0-Primary 1- Backup.
 *      
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_CloseConnection(IDS_CONNECTION_TYPE type)
{
    IDS_TRACE_DEBUG(("IDSCL_CloseConnection"));

    if (type == IDS_PRIMARY_CONNECTION)
    {
        IDS_Connection.primaryInfo.isUp = ITS_FALSE;
        IDS_Connection.primaryInfo.isInitialized = ITS_FALSE;
        IDS_Connection.primaryInfo.thrInfo.isRunning = ITS_FALSE;
    }
    else if (type == IDS_BACKUP_CONNECTION)
    {
        IDS_Connection.backupInfo.isUp = ITS_FALSE;
        IDS_Connection.backupInfo.isInitialized = ITS_FALSE;
        IDS_Connection.backupInfo.thrInfo.isRunning = ITS_FALSE;
    }
    else
    {
        IDS_TRACE_ERROR(("IDSCL_CloseConnection:Invalid connection type %d", 
                                                                      type));
        return (!ITS_SUCCESS);
    }

    return (ITS_SUCCESS);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method validates whether the context infomation provided 
 *      is correct or not depending on the routing criteria.
 *
 *  Input Parameters:
 *      reginfo - pointer to the register info structure.
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_INT
IDSCL_ValidateContext(IDS_REGISTER *reginfo)
{
    ITS_INT ret = ITS_EINVCHOICE;

    IDS_TRACE_DEBUG(("IDSCL_ValidateContext"));

    switch(reginfo->routing_criteria)
    {
        case IDS_APP_IDENTIFIER:
            ret = ITS_SUCCESS;
        break;
    }
 
    return (ret);
} 
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method returns the ISS7_Stack
 *  Input Parameters:
 *      None.
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_HANDLE
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_HANDLE
IDSCL_GetHandle()
{
    IDS_TRACE_DEBUG(("IDSCL_GetHandle"));

    return (ISS7_Stack); 
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method fills the registration info.
 *  Input Parameters:
 *      reginfo - pointer to the register info structure.
 *      event - pointer to the input event.
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_ReceiveRegisterIndication(ITS_HANDLE handle, 
                                ITS_EVENT  *event,
                                IDS_REGISTER_ACK *regInfo)
{
    ITS_INT   ret = ITS_SUCCESS;
    ITS_OCTET offset = sizeof(ITS_UINT) + sizeof(ITS_OCTET);

    IDS_TRACE_DEBUG(("IDSCL_ReceiveRegisterIndication"));
 
    memcpy(regInfo, &event->data[offset], sizeof(IDS_REGISTER_ACK)); 

    return (ret);
} 

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method fills the deregistration return info.
 *  Input Parameters:
 *      reginfo - pointer to the register info structure.
 *      event - pointer to the input event.
 *
 *  Input Parameters:
 *      reginfo - pointer to the deregister info structure.
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_ReceiveDeRegisterIndication(ITS_HANDLE handle, 
                                  ITS_EVENT  *event,
                                  IDS_DEREGISTER_ACK *regInfo)
{

    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET offset = sizeof(ITS_UINT) + sizeof(ITS_OCTET);

    IDS_TRACE_DEBUG(("IDSCL_ReceiveDeRegisterIndication"));

    memcpy(regInfo, &event->data[offset], sizeof(IDS_DEREGISTER_ACK)); 

    return ret;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_RegisterCallBack(IDS_CALLBACK func)
{
    ITS_INT ret = ITS_SUCCESS;
 
    IDS_TRACE_DEBUG(("IDSCL_RegisterCallBack"));

    IDS_Connection.func = func;

    return ret;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *       
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *    
 *  Notes:
 * 
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    14-11-06   Enhancement    SessionId str to contain clientId
 *                                         and client session Index. 
 *   Kamakshi    17-11-06   Enhancement    getpid and tv_usec added to SesId
 * 
 *************************************************************************/
IDS_INT 
IDSCL_AllocateSessionIndex(ITS_UINT appId, ITS_UINT& sessId, 
                     IDS_CHAR* sessIdString)
{

    static ITS_UINT sessIdx = 0;
    static ITS_UINT cnt = getpid();

    IDS_TRACE_DEBUG(("AllocateSessionIndex"));
        
    MUTEX_AcquireMutex(&regLock);

    /* Allocation of Session index */        
    sessIdx++;
    if (!sessIdx)
    {
        sessIdx++;
    }
    else if (sessIdx >= DIA_DIR_BIT)
    {
        sessIdx = 1;
    }
    sessId = sessIdx;

    cnt++;
    if (cnt > 65000)
    {
        cnt = 1;
    }

    timeval tv;
    gettimeofday(&tv, NULL);
    
    if ((IDS_HostInfo.originHost == NULL)||
        (IDS_HostInfo.originRealm == NULL))
    {
         IDS_TRACE_CRITICAL(("OriginHost||OriginRealm is NULL \n"));
         return !ITS_SUCCESS;
    }

    std::string orgnHost;
    orgnHost = (const char *)IDS_HostInfo.originHost;
    if(orgnHost.find('.') == -1)
    {
        sprintf(sessIdString, "%s.%s;%ld;%ld;%u:%u",
                          IDS_HostInfo.originHost, IDS_HostInfo.originRealm, 
                          tv.tv_sec, (cnt + tv.tv_usec), 
                          IDS_ClientID, sessId);
    }
    else
    {
        sprintf(sessIdString, "%s;%ld;%ld;%u:%u",
                          IDS_HostInfo.originHost, 
                          tv.tv_sec, (cnt + tv.tv_usec),
                          IDS_ClientID, sessId);
    }

    IDS_TRACE_DEBUG(("AllocateSessionIndex: SessionId Generated = %s", 
                                                     sessIdString));

    MUTEX_ReleaseMutex(&regLock);

    return (ITS_SUCCESS);
}

/*implemt: public
 ****************************************************************************
 *  Purpose: Sets the Origin Host and Origin Realm
 *
 *  Input Parameters: char buffers
 *
 *  Output Parameters:
 *      None.
 *       
 *  Return Value:
 *      None
 *    
 *  Notes:
 * 
 *  See Also:
 * 
 *************************************************************************/
void
IDSCL_SetHostInfo(const IDS_CHAR *orgH, const IDS_CHAR *orgR)
{
    IDS_HostInfo.originHost = (ITS_OCTET*)strdup(orgH);
    IDS_HostInfo.originRealm = (ITS_OCTET*)strdup(orgR);
}

/*implemt: public
 ****************************************************************************
 *  Purpose: Initializez the ITS_Diameter dictionary for extensible AVPs
 *
 *  Input Parameters: 
 *
 *  Output Parameters:
 *      None.
 *       
 *  Return Value:
 *      None
 *    
 *  Notes:
 * 
 *  See Also:
 * 
 *************************************************************************/
void
IDSCL_InitDiaDictParser(const char* filename)
{
    DiaDictParserInitialize(filename);
}

/*implemt: public
 ****************************************************************************
 *  Purpose: This function checks whether the DCCA Feature is enabled at the 
 *           Distributed Server. 
 *
 *  Input Parameters: IDS_HANDLE 
 *
 *  Output Parameters:
 *      None.
 *       
 *  Return Value:
 *      true or false
 *    
 *  Notes:
 * 
 *  See Also:
 * 
 *************************************************************************/
IDSCL_DLLAPI IDS_INT
IDSCL_IsDccaEnabled(IDS_HANDLE handle)
{
    IDS_CONNECTION *conInfo = NULL;
                                                                                
    IDS_TRACE_DEBUG(("IDSCL_IsDccaEnabled"));
                                                                                
    conInfo = (IDS_CONNECTION *)handle;

    return conInfo->isDccaEnabled;
}

/*implemt: public
 ****************************************************************************
 *  Purpose: This function forms the ReleaseSession event and sends to the 
 *           Distributed Server. 
 *
 *  Input Parameters: IDS_HANDLE, session Id and index
 *
 *  Output Parameters:
 *      None.
 *       
 *  Return Value:
 *      success or failure
 *    
 *  Notes:
 * 
 *  See Also:
 * 
 *************************************************************************/
IDSCL_DLLAPI IDS_INT
IDSCL_ReleaseSession(ITS_HANDLE handle, std::string& sesStr, IDS_UINT sesIdx)
{
    IDS_INT ret = IDS_SUCCESS;
    ITS_EVENT rlsevt;
    ITS_UINT index =0;
    ITS_OCTET accRecInfo = 0;

    IDS_TRACE_DEBUG(("IDSCL_ReleaseSession"));

    ITS_UINT evtLen = 2*sizeof(ITS_UINT) + 2*sizeof(ITS_OCTET) + 
                         sesStr.size()+1;

    /* form a release session message */
    ITS_EVENT_INIT(&rlsevt, IDS_APPDATA_SRC, evtLen);

    /* Pre-fix client ID */
    IDSCL_IntToData((rlsevt.data), IDS_ClientID, sizeof(ITS_UINT));
    index = sizeof(ITS_UINT);

    /* Pre-fix session index before encoded data */
    IDSCL_IntToData((&rlsevt.data[index]), sesIdx, sizeof(ITS_UINT));
    index += sizeof(ITS_UINT);

    /* Pre-fix Accounting Record Information required only for ACR */
    IDSCL_IntToData((&rlsevt.data[index]), accRecInfo, sizeof(ITS_OCTET));
    index += sizeof(ITS_OCTET);

    /* Copy the Message Type */
    rlsevt.data[index++] = IDS_DIA_MSG_TYPE_SES_RLS;
 
    /* Copy the Session Id string */
    memcpy(&rlsevt.data[index], (char*)sesStr.c_str(), sesStr.size());
    index += sesStr.size();
    
    /* Append a NULL Character */
    rlsevt.data[index] = '\0';

    //ret = IDSCL_SendEvent(handle, &rlsevt);
    ret = IDSCL_PutEventOnTaskQue(&IDS_Connection.outBoundTaskTrans,
                                                 &rlsevt);

    if (ret != ITS_SUCCESS)
    {
        IDS_TRACE_ERROR(("PrimaryThreadFunction: PutEvent fail"));
    }


    return ret;
}

/*implemt: public
 ****************************************************************************
 *  Purpose: This function checks whether the connection specified
 *           (primary or backup) is Up.
 *
 *  Input Parameters: IDS_HANDLE, IDS_CONNECTION_TYPE 
 *
 *  Output Parameters:
 *      None.
 *       
 *  Return Value:
 *      true or false
 *    
 *  Notes:
 * 
 *  See Also:
 * 
 *************************************************************************/
IDSCL_DLLAPI IDS_BOOLEAN
IDSCL_IsConnectionUp(ITS_HANDLE handle, IDS_CONNECTION_TYPE type)
{
    IDS_CONNECTION *conInfo = NULL;
                                                                                
    IDS_TRACE_DEBUG(("IDSCL_IsConnectionUp"));
                                                                                
    conInfo = (IDS_CONNECTION *)handle;
                                                                                
    if(type == IDS_PRIMARY_CONNECTION)
    {
        return conInfo->primaryInfo.isUp;
    }
    else if (type == IDS_BACKUP_CONNECTION)
    {
        return conInfo->backupInfo.isUp;
    }
    else
    {
        return IDS_FALSE;
    }
}

/*implemt: public
 ****************************************************************************
 *  Purpose: This function checks whether the Client is registered 
 *           with the connection specified.
 *
 *  Input Parameters: IDS_HANDLE, IDS_CONNECTION_TYPE 
 *
 *  Output Parameters:
 *      None.
 *       
 *  Return Value:
 *      true or false
 *    
 *  Notes:
 * 
 *  See Also:
 * 
 *************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_IsRegisteredWith(ITS_HANDLE handle, IDS_CONNECTION_TYPE type)
{
   IDS_CONNECTION *conInfo = NULL;

   IDS_TRACE_DEBUG(("IDSCL_IsRegisteredWith"));
     
   conInfo = (IDS_CONNECTION *)handle;

   if ((type == IDS_PRIMARY_CONNECTION) && (conInfo->primaryInfo.isUp)) 
   {
       switch(conInfo->primaryInfo.regStatus)
       {
           case SUCCESS:
                return ITS_SUCCESS;
           break;
           case FAILURE:
           case NOTREGISTERED:
           default:
               return !ITS_SUCCESS;
           break;
       }  
   }
   else if ((type == IDS_BACKUP_CONNECTION) && (conInfo->backupInfo.isUp))
   {
       switch(conInfo->backupInfo.regStatus)
       {
           case SUCCESS:
              return ITS_SUCCESS;
           break;
           case FAILURE:
           case NOTREGISTERED:
           default:
               return !ITS_SUCCESS;
           break;
       }
   }
  
   return (!ITS_SUCCESS);
} 

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method creates UDP socket
 *
 *  Input Parameters:
 *      info  -   of type IDS_CONNECTION_INFO
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
static IDS_INT
EndPointOpen(IDS_CONNECTION_INFO *info)
{
    int    dummy = 1;                    /* for socket option */

    ITS_SocketInfo *sInfo;
    struct linger      linger;           /* for set linger */

    /* Set up our addr info accounting */
    if ((sInfo=(ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    /* get the address */
    if (SOCK_CreateAddr(INET_DOMAIN, info->ipAddr, info->port,
                    &sInfo->addr, &sInfo->asize) != ITS_SUCCESS)
    {
        free(sInfo);

        return (ITS_EBADHOST);
    }

    if ((sInfo->socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        free(sInfo->addr);
        free(sInfo);

        return (ITS_ENOSOCKET);
    }

    /* Set linger on, to 0 time */
    linger.l_onoff = 1;
    linger.l_linger = 0;
    // Checking Unchecked return value 
    if (setsockopt(sInfo->socket, SOL_SOCKET, SO_LINGER,
               (char *)&linger, sizeof(struct linger)) < 0)
    {
        IDS_TRACE_CRITICAL(("setsockopt failed for SO_LINGER with error: %d", errno));
    }

    /* Save off addr info in our own dataspace */
    sInfo->type = SPROT_TYPE_UDP;
    sInfo->af = AF_INET;
    info->sockInfo = sInfo;

    /* Set reuseaddr socket option */
    if((setsockopt(sInfo->socket, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int))) < 0 )
    {
        IDS_TRACE_CRITICAL(("setsockopt failed for SO_LINGER with error: %d", errno));
        return (!ITS_SUCCESS);
    }

    return (ITS_SUCCESS);

}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method sends event to specified destination
 *
 *  Input Parameters:
 *      info  -   of type IDS_CONNECTION_INFO
 *      evt   -  ITS_EVENT
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
static IDS_INT
UdpSend(IDS_CONNECTION_INFO *conInfo, ITS_EVENT *evt)
{
    ITS_UINT nrite;
    static ITS_USHORT tmp, tmp1;

    /* Write source */
    tmp = SOCK_HToNS(evt->src);

    nrite = SOCK_Send(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT),
                conInfo->sockInfo->addr, conInfo->sockInfo->asize);

    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->writeLock);
        return (IDS_ESENDFAIL);
    }

    /* Write len */
    tmp1 = SOCK_HToNS(evt->len);

    nrite = SOCK_Send(conInfo->sockInfo, (char *)&tmp1, sizeof(ITS_USHORT),
                conInfo->sockInfo->addr, conInfo->sockInfo->asize);

    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->writeLock);
        return (IDS_ESENDFAIL);
    }

    /* Write data */
    nrite = SOCK_Send(conInfo->sockInfo, (char *)evt->data, evt->len,
                conInfo->sockInfo->addr, conInfo->sockInfo->asize);

    MUTEX_ReleaseMutex(&conInfo->writeLock);

    if (nrite == evt->len)
    {
        return (ITS_SUCCESS);
    }

    return (IDS_ESENDFAIL);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method receives data from UDP socket
 *
 *  Input Parameters:
 *      info  -   of type IDS_CONNECTION_INFO
 *      evt   -   ITS_EVENT
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
static IDS_INT
UdpRecv(IDS_CONNECTION_INFO *conInfo, ITS_EVENT *evt)
{
    int ret;
    ITS_SockPollInfo info;
    static ITS_USHORT tmp, tmp1;
repeatudp:
    memset(&info, 0, sizeof(info));

    info.lookFor = SOCK_POLL_READ;
    info.sinfo = conInfo->sockInfo;

    ret = SOCK_Poll(&info, 1,
                HMI_GetTimeOutInterval() * USEC_PER_MILLISEC);

    if (ret < ITS_SUCCESS)
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);
        return (IDS_ERCVFAIL);
    }

    if (ret == 0)
    {
        if (conInfo->isUp == ITS_FALSE)
        {
            MUTEX_ReleaseMutex(&conInfo->readLock);

            return IDS_ENOSOCKET;
        }
        goto repeatudp;
    }

    /* read Event src */

    ret = SOCK_Recv(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT),
                    conInfo->sockInfo->addr, &conInfo->sockInfo->asize);

    if (ret != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);
        return (IDS_ERCVFAIL);
    }

    /* read Event len */
    evt->src = SOCK_NToHS(tmp);

    ret = SOCK_Recv(conInfo->sockInfo, (char *)&tmp1, sizeof(ITS_USHORT),
                    conInfo->sockInfo->addr, &conInfo->sockInfo->asize);

    if (ret != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);
        return (IDS_ERCVFAIL);
    }

    evt->len = SOCK_NToHS(tmp1);

    /* read data len */
    evt->data = (ITS_OCTET *)malloc(evt->len);

    if (evt->data == NULL)
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);
        return (ITS_ENOMEM);
    }

    /* read data */
    ret = SOCK_Recv(conInfo->sockInfo, (char *)evt->data, evt->len,
                    conInfo->sockInfo->addr, &conInfo->sockInfo->asize);

    MUTEX_ReleaseMutex(&conInfo->readLock);

    if (ret == evt->len)
    {
        return (ITS_SUCCESS);
    }
    else
    {
        return (IDS_ERCVFAIL);
    }
}

/** 
 This method sets IDC connection retry interval timer.  
 */   
IDSCL_DLLAPI void 
IDSCL_SetIDCconInterval(ITS_INT val)
{
  sockConInterval = val;
} 

IDSCL_DLLAPI IDS_INT
IDSCL_SetSockBindInfo(const IDS_CHAR *host, IDS_INT actPort, IDS_INT bkpPort)
{
    int ret = ITS_SUCCESS;
 
    if(host == NULL)
    {
        return !ITS_SUCCESS;
    }

    /* Set Sock info for active */
    IDS_Connection.primaryInfo.lSockBindInfo.isSet  = ITS_TRUE;
    IDS_Connection.primaryInfo.lSockBindInfo.port   = actPort;
    //Correcting Calling risky function
    strncpy(IDS_Connection.primaryInfo.lSockBindInfo.ipAddr, host, IDSCL_IP_ADDR_LEN-1);

    /* Set Sock info for backup */
    IDS_Connection.backupInfo.lSockBindInfo.isSet  = ITS_TRUE;
    IDS_Connection.backupInfo.lSockBindInfo.isSet  = ITS_TRUE;
    IDS_Connection.backupInfo.lSockBindInfo.port   = actPort;
    //Correcting Calling risky function
    strncpy(IDS_Connection.backupInfo.lSockBindInfo.ipAddr, host, IDSCL_IP_ADDR_LEN-1);
    return ret;
}

IDSCL_DLLAPI ITS_INT
IDSCL_SendGlobalUniqAddrMsg(ITS_HANDLE handle, IDS_MESSAGE *msg)
{
    ITS_EVENT evt;
    ITS_INT index = 0, ret = ITS_SUCCESS;
    ITS_BOOLEAN flag = ITS_TRUE;
    IDS_CONNECTION *conn = NULL;

    IDS_TRACE_DEBUG(("IDSCL_SendGlobalUniqAddrMsg"));                                                                        

    conn = (IDS_CONNECTION*)handle;
    msg->clientID = conn->clid;

    if(conn->backupInfo.isPrimary == ITS_TRUE)
    {
        flag = ITS_FALSE;
    }
    else if((conn->primaryInfo.isPrimary == ITS_FALSE) &&
                (conn->backupInfo.isPrimary == ITS_FALSE))
    {
        IDS_TRACE_CRITICAL(("IDSCL_SendEvent: All connection down"));

        return (ITS_ENOSOCKET);
    }
    else
    {
        flag = ITS_TRUE;
    }

    if (flag)
    {
        if (conn->primaryInfo.regStatus == SUCCESS)
        {
            ITS_EVENT_INIT(&evt, ITS_APP_SRC, sizeof(IDS_MESSAGE));

            if(IDSCL_Encode(msg, &evt) == ITS_SUCCESS)
            { 
                IDSCL_WriteEvent((ITS_HANDLE*)&IDS_Connection.primaryInfo,
                                                               &evt);
            }
        }
        else
        {
            IDS_TRACE_CRITICAL(("IDSCL_SendEvent: Client not registered"));

            ret = IDS_NOT_REGISTERED;
        }
    }
    else
    {
        if (conn->backupInfo.regStatus == SUCCESS)
        {
            ITS_EVENT_INIT(&evt, ITS_APP_SRC, sizeof(IDS_MESSAGE));

            if(IDSCL_Encode(msg, &evt) == ITS_SUCCESS)
            {
                IDSCL_WriteEvent((ITS_HANDLE*)&IDS_Connection.backupInfo,
                           &evt);
            }
        }
        else
        {
            IDS_TRACE_CRITICAL(("IDSCL_SendEvent: Client not registered"));
            ret = IDS_NOT_REGISTERED;
        }
    }

    return (ret);
}


