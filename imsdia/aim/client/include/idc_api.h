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
 * ID: $Id: idc_api.h,v 3.6 2010/09/22 05:22:54 nvijikumar Exp $
 *
 * LOG: $Log: idc_api.h,v $
 * LOG: Revision 3.6  2010/09/22 05:22:54  nvijikumar
 * LOG: GlobalUniqueAddr based routing/distribution support
 * LOG:
 * LOG: Revision 3.5  2009/07/13 11:54:39  rajeshak
 * LOG: Option to set TCP keepalive timers.
 * LOG:
 * LOG: Revision 3.4  2009/03/25 04:04:05  nvijikumar
 * LOG: Provided API to bind local IP and Port
 * LOG:
 * LOG: Revision 3.3  2009/03/03 13:32:59  sureshj
 * LOG: Introduced API to set IDC Reconnect interval timer.
 * LOG:
 * LOG: Revision 3.2  2008/11/06 07:19:00  nvijikumar
 * LOG: UDP Transport support between IDS and IDC
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:00  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.14  2008/03/27 11:18:28  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.8.4.3  2007/10/03 16:47:35  hbhatnagar
 * LOG: Rolling back changes done for RegisterWith() API and providing the
 * LOG: same functionality in Register() API by adding IDS_UINT conType as
 * LOG: default argument with value 0.(After discussion with Yogesh)
 * LOG:
 * LOG: Revision 2.8.4.2  2007/10/01 19:30:47  hbhatnagar
 * LOG: Changed the signature of IDSCL_Register to accomodate Reregistration
 * LOG: added RegisterWith() API for Bridgewater multiple registration enhancement.
 * LOG:
 * LOG: Revision 2.8.4.1  2007/03/15 18:17:24  hbhatnagar
 * LOG: added the defalut file name for dictionary parser functions
 * LOG:
 * LOG: Revision 2.8  2007/01/29 08:03:10  kamakshilk
 * LOG: idc_trace.h added
 * LOG:
 * LOG: Revision 2.7  2006/12/14 13:43:04  kamakshilk
 * LOG: Fix for bug ID 5054. IsRegisteredWith, IsConnectionUp APIs added
 * LOG:
 * LOG: Revision 2.6  2006/11/24 15:15:54  kamakshilk
 * LOG: CloseCon API added instead of CloseConnection
 * LOG:
 * LOG: Revision 2.5  2006/11/17 06:08:55  kamakshilk
 * LOG: ReleaseSession and DccaEnabled APIs added
 * LOG:
 * LOG: Revision 2.4  2006/11/16 12:42:54  kamakshilk
 * LOG: InitDiaDictParser API added
 * LOG:
 * LOG: Revision 2.3  2006/11/14 09:02:46  kamakshilk
 * LOG: Flag to indicate first Req of a session
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:22:01  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.9  2006/07/25 13:34:56  sumag
 * LOG: Updates to support Java.
 * LOG:
 * LOG: Revision 1.8  2006/06/14 14:56:59  kamakshilk
 * LOG: Enhancement to the C++ Send API. For Base Protocol Messages, sIdx and AppId
 * LOG: need not be set, as they should be 0.
 * LOG:
 * LOG: Revision 1.7  2006/05/30 09:37:50  yranade
 * LOG: Changes to compile with CC compiler on solaris 10.
 * LOG:
 * LOG: Revision 1.6  2006/04/13 11:06:07  nvijikumar
 * LOG: modified variable declaration (yogesh)
 * LOG:
 * LOG: Revision 1.5  2006/04/07 13:56:39  adutta
 * LOG: Documentation using doxygen
 * LOG:
 * LOG: Revision 1.4  2006/04/06 08:01:42  adutta
 * LOG: Ses-Id related changes
 * LOG:
 * LOG: Revision 1.3  2006/03/14 06:39:35  adutta
 * LOG: Codec changes
 * LOG:
 * LOG: Revision 1.2  2006/03/13 05:22:07  adutta
 * LOG: Impl. changes for diameter encode/decode
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:11:15  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/
#ident "$Id: idc_api.h,v 3.6 2010/09/22 05:22:54 nvijikumar Exp $"

#ifndef _IDS_API_H
#define _IDS_API_H


#include <string>

#include <dia_defines.h>
#include <diameter/Command.h>

#include <idc_common.h>
#include <idc_errors.h>
#include <idc_trace.h>

#if defined(WIN32)
#if defined(IDSCL_IMPLEMENTATION)
#define IDSCL_DLLAPI __declspec(dllexport)
#else
#define IDSCL_DLLAPI __declspec(dllimport)
#endif
#else
#define IDSCL_DLLAPI
#endif

/*
 * initialization function
 */
IDSCL_DLLAPI IDS_INT
IDSCL_Initialize(const IDS_CHAR *host, IDS_INT port, 
                           IDS_TRANS_TYPE tType = IDS_TCP);

/*
 * Registration of CallBack function
 */
IDSCL_DLLAPI IDS_INT
IDSCL_RegisterCallBack(IDS_CALLBACK func);

/*
 * Registration function
 * (1-10-07) Added IDS_CONNECTION_TYPE as default argument 
 * for Re-Registering purpose. 
 */
IDSCL_DLLAPI IDS_INT
IDSCL_Register(IDS_HANDLE handle, IDS_MESSAGE *ctxt, IDS_UINT conType=0);

/*
 * Deregister function
 */
IDSCL_DLLAPI IDS_INT
IDSCL_Deregister(IDS_HANDLE handle, IDS_MESSAGE *ctxt);

/* 
 * Send the event to the server
 */
IDSCL_DLLAPI IDS_INT
IDSCL_Send(IDS_HANDLE handle, diameter::Command& mesg, IDS_UINT sesId, 
           IDS_UINT appId, IDS_BOOLEAN newRequest=IDS_FALSE);

/*
 * Receive function
 */
IDSCL_DLLAPI IDS_INT
IDSCL_Receive(IDS_HANDLE handle, IDS_MESSAGE *evt);

/*
 * Receive function
 */
IDSCL_DLLAPI IDS_INT
IDSCL_Receive(IDS_HANDLE handle, IDS_MESSAGE_BUFF *evt);

/*
 * Do the clean up during Terminate
 */
IDSCL_DLLAPI void
IDSCL_Terminate();

/*
 * Pre initialization function
 */
IDSCL_DLLAPI IDS_INT
IDSCL_PreInitialize(IDS_HANDLE *handle);

IDSCL_DLLAPI IDS_HANDLE
IDSCL_GetHandle();

/*
 * Close the connection, for the user
 */
IDSCL_DLLAPI ITS_INT
IDSCL_CloseCon(ITS_HANDLE handle , IDS_CONNECTION_TYPE type);


/* This function checks whether one of the connections is up 
   and if client is registered with that server. */
IDSCL_DLLAPI IDS_INT
IDSCL_IsRegistered(IDS_HANDLE handle);

/* Switch on tracing */
IDSCL_DLLAPI
void IDSCL_EnableTracing();

/* Switch off tracing */
IDSCL_DLLAPI
void IDSCL_DisableTracing();

/* Generate session string */
IDSCL_DLLAPI
IDS_INT IDSCL_AllocateSessionIndex(IDS_UINT appId, IDS_UINT& sessId, 
                                         IDS_CHAR* sessIdStringa);
                                  
/* Sets origin host and realm */
IDSCL_DLLAPI
void IDSCL_SetHostInfo(const IDS_CHAR* orgHost, const IDS_CHAR* orgRealm);

void
IDSCL_InitDiaDictParser(const char* filename);

/* This function checks whether the DCCA Feature is enabled at the 
   Distributed Server. Returns true or false */
IDSCL_DLLAPI IDS_INT
IDSCL_IsDccaEnabled(IDS_HANDLE handle);

IDSCL_DLLAPI IDS_INT
IDSCL_ReleaseSession(ITS_HANDLE handle, std::string& sesStr, IDS_UINT sesIdx=0);

/* This function checks whether one of the connections is up */
IDSCL_DLLAPI ITS_BOOLEAN
IDSCL_IsConnectionUp(ITS_HANDLE handle, IDS_CONNECTION_TYPE type);

/* This function checks whether one of the connections is up 
   and if client is registered with that server. */
IDSCL_DLLAPI IDS_INT
IDSCL_IsRegisteredWith(IDS_HANDLE handle, IDS_CONNECTION_TYPE type);

/*This function sets new Connection retry timer value */
IDSCL_DLLAPI void
IDSCL_SetIDCconInterval(ITS_INT val);

/*
 * Set Local socket info
 */
IDSCL_DLLAPI IDS_INT
IDSCL_SetSockBindInfo(const IDS_CHAR *host, IDS_INT actPort, IDS_INT bkpPort);

/* Set TCP KeepAlive Timers
 */
IDSCL_DLLAPI IDS_INT 
IDSCL_SetTcpKeepAliveTimer(IDS_TCP_TIMER* timerVal);

/** Interface:
 *      IDSCLApi 
 *      
 *  Purpose:
 *
 *      IDSCLApi class is used for\n
 *      a. Initialize client library\n
 *      b. Connect to the server\n
 *      c. Register/De-register\n
 *      d. Exchange messages\n
 **/
class IDSCLApi
{
public:
    /********************************************************************/
    /** Purpose:
    *      Class Constructor\n
    *      Initializes the client library.
    *
    *  Input Parameters:
    *      None
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
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/  
    IDSCLApi()
    {
        if (!IsPreInitialize())
        {
            PreInitialize();
        }
        newMessage = IDS_FALSE;
    }

    /********************************************************************/
    /** Purpose:
    *      Connects with the server.
    *
    *  Input Parameters:
    *      IDS_CHAR* host ip address
    *      IDS_INT   port number
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
    *      None.
    *   
    *  See Also:
    *      In case of redundancy, call this function twice to connect\n
    *      with the redundant server.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    IDS_INT 
    Initialize(const IDS_CHAR *host, IDS_INT port, 
                             IDS_TRANS_TYPE tType = IDS_TCP)
    {
        return (IDSCL_Initialize(host, port, tType));
    }


    /********************************************************************/
    /** Purpose:
    *      Registers the client application with the server.
    *
    *  Input Parameters:
    *      ctxt of type IDS_MESSAGE*  Carries the registration information.
    *      conType of type IDS_UINT  carries which server to send
    *      registration message.
    *      conType = 0 as default argument( Register with Both servers ) 
    *                1 or IDS_PRIMARY_CONNECTION( Register with Primary server)
    *                2 or IDS_BACKUP_CONNECTION( Register with Backup server)
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      IDS_EMISSINGMANDPRM.\n
    *      IDS_SUCCESS.
    *   
    *  Notes:
    *      While Re-Registering this API can be used by providing corresponding
    *      Connection as ConnectionType. 
    *   
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *********************************************************************/
    IDS_INT
    Register(IDS_MESSAGE *ctxt, IDS_UINT conType=0)
    {
        return (IDSCL_Register(handle, ctxt, conType));
    }

    /********************************************************************/
    /** Purpose:
    *      De-Registers the client application with the server
    *
    *  Input Parameters:
    *      IDS_MESSAGE  Carries the De-registration information
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      IDS_EMISSINGMANDPRM.\n
    *      IDS_SUCCESS.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    IDS_INT
    DeRegister(IDS_MESSAGE *ctxt)
    {
        return (IDSCL_Deregister(handle, ctxt));
    }

    /********************************************************************/
    /** Purpose:
    *      To set the Tcp KeepAlive Values
    *
    *  Input Parameters:
    *      IDS_TCP_TIMERS  Carries Timer information.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      IDS_SUCCESS.
    *
    *  Notes:
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    IDS_INT
    SetTcpKeepAliveTimers(IDS_TCP_TIMER* timerVal)
    {
        return IDSCL_SetTcpKeepAliveTimer(timerVal);
    }

    /********************************************************************/
    /** Purpose:
    *      Receives event from server
    *
    *  Input Parameters:
    *      IDS_MESSAGE  Carries the server information.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      IDS_SUCCESS.\n
    *      Error codes.
    *
    *  Notes:
    *      Blocking call.
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    IDS_INT
    ReceiveEvent(IDS_MESSAGE *msg)
    {
        IDS_INT ret = IDS_SUCCESS;

        if (msg == NULL)
        {
            return (IDS_ENULLPTR);
        }

        ret = IDSCL_Receive(handle, msg);

        return (ret);
    }


    IDS_INT
    ReceiveEvent(IDS_MESSAGE_BUFF *msg)
    {
        IDS_INT ret = IDS_SUCCESS;

        if (msg == NULL)
        {
            return (IDS_ENULLPTR);
        }

        ret = IDSCL_Receive(handle, msg);

        return (ret);
    }


    /********************************************************************/
    /** Purpose:
    *      Sends event (diameter message) to server
    *
    *  Input Parameters:
    *      Command  Object of command code\n
    *      sId      Session index\n
    *      appId    Application ID
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      IDS_EINVALIDARGS.\n
    *      IDS_SUCCESS.
    *
    *  Notes:
    *      In case of sending Base Protocol Messages, make sure that 
    *      sId == 0, and appId == 0 
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    IDS_INT
    Send(diameter::Command& mesg, IDS_UINT sId = 0, IDS_UINT appId = 0)
    {
        if (newMessage)    
        {
            newMessage = IDS_FALSE;
            return (IDSCL_Send(handle, mesg, sId, appId, IDS_TRUE));
        }
        else
            return (IDSCL_Send(handle, mesg, sId, appId));
    }

    /********************************************************************/
    /** Purpose:
    *      Checks if the client is registered to server. 
    *      Return true, even if client is registered with one of the 
    *      two servers primary or backup.
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
    *      IDS_TRUE.\n
    *      IDS_FALSE.
    *
    *  Notes:
    *      If already registered with Primary, then doesnot check
    *      if registered with backup .
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    IDS_BOOLEAN
    IsRegistered()
    {
        if (IDSCL_IsRegistered(handle) == ITS_SUCCESS)
        {
            return (IDS_TRUE);
        }
    
        return (IDS_FALSE);
    }

    /********************************************************************/
    /** Purpose:
    *      Closes the connection towards server 
    *
    *  Input Parameters:
    *      IDS_CONNECTION_TYPE      Connection type (Primary/backup)
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      IDS_EINVALIDARGS\n.
    *      IDS_SUCCESS.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    IDS_INT
    CloseConnection(IDS_CONNECTION_TYPE type)
    {
        return (IDSCL_CloseCon(handle, type));
    }

    /********************************************************************/
    /** Purpose:
    *      Enables client library tracing.
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
    *      None.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    void
    EnableTracing()
    {
        IDSCL_EnableTracing();
    }

    /********************************************************************/
    /** Purpose:
    *      Disables client library tracing.
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
    *      None.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    void    
    DisableTracing()
    {
        IDSCL_DisableTracing();
    }

    /********************************************************************/
    /** Purpose:
    *      Terminates the client connection (primary and backup) and 
    *      threads.
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
    *      None.
    *
    *  Notes:
    *      This *can* be called by the application *only* during 
    *      gracefull exit .
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    void Terminate()
    {
        IDSCL_Terminate();
    }

    /********************************************************************/
    /** Purpose:
    *      Enables user application to register function to get network
    *      event notification.
    *
    *  Input Parameters:
    *      IDS_CALLBACK Callback function of the application.
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
    *      The uses function will be invoked if the IP connection 
    *      breaks or makes.
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    void
    RegisterCallback(IDS_CALLBACK f)
    {
        IDSCL_RegisterCallBack(f);
    }

    /********************************************************************/
    /** Purpose:
    *      Allocates Session Index and Session string.
    *
    *  Input Parameters:
    *      IDS_UINT Application ID.
    *
    *  Input/Output Parameters:
    *      None.
    *  
    *  Output Parameters:
    *      IDS_UINT  Session Index.\n
    *      string    Session string.\n
    *
    *  Return Value:
    *      IDS_SUCCESS.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    IDS_INT
    AllocateSessionIndex(IDS_UINT appId, IDS_UINT& sessId,
                                        std::string& sessIdString)
    {
        IDS_INT ret;
        IDS_CHAR buff[255];

        ret = IDSCL_AllocateSessionIndex(appId, sessId, buff);

        sessIdString = buff;

        newMessage = IDS_TRUE;
       
        return ret;
    }

    /********************************************************************/
    /** Purpose:
    *      This function sets the origin Host and Realm for the client.
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
    *      None.
    *
    *  Notes:
    *      The Origin Host and Realm needs to be that of the Distributed 
    *      Server.
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    void 
    SetHostInfo(const IDS_CHAR *orgH, const IDS_CHAR* orgR)
    {
        IDSCL_SetHostInfo(orgH, orgR);
    }

    /********************************************************************/
    /** Purpose:
    *      This function initializes the dictionary file required for 
    *      extensibility (extra AVP addition)
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
    *      None.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    void 
    InitDiaDictParser(const char* filename="dictionary.xml")
    {
        IDSCL_InitDiaDictParser(filename);
    }

    /********************************************************************/
    /** Purpose:
    *      Checks if the DCCA feature is enabled at the server.
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
    *      IDS_TRUE.\n
    *      IDS_FALSE.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    IDS_BOOLEAN
    IsDccaEnabled()
    {
        return IDSCL_IsDccaEnabled(handle);
    }

    /********************************************************************/
    /** Purpose:
    *      Sends a release session Event to the Server asking to 
    *      realese the diameter session at the stack.
    *
    *  Input Parameters:
    *      std::string& sesStr, IDS_UINT sessIdx.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      ITS_SUCCESS or FAILURE.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    IDS_INT
    ReleaseSession(std::string& sesStr, IDS_UINT sessIdx=0)
    {
        return IDSCL_ReleaseSession(handle, sesStr, sessIdx);
    }

    /********************************************************************/
    /** Purpose:
    *      Checks if the registered with the server(PRIMARY or BACKUP) 
    *
    *  Input Parameters:
    *      IDS_CONNECTION_TYPE.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      IDS_TRUE.\n
    *      IDS_FALSE.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    IDS_BOOLEAN
    IsRegisteredWith(IDS_CONNECTION_TYPE type)
    {
        if (IDSCL_IsRegisteredWith(handle, type) == ITS_SUCCESS)
        {
            return (IDS_TRUE);
        }
    
        return (IDS_FALSE);
    }

    /********************************************************************/
    /** Purpose:
    *      Checks if the Connection to the server(PRIMARY or BACKUP) is Up
    *
    *  Input Parameters:
    *      IDS_CONNECTION_TYPE.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      IDS_TRUE.\n
    *      IDS_FALSE.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/
    IDS_BOOLEAN
    IsConnectionUp(IDS_CONNECTION_TYPE type)
    {
        return (IDSCL_IsConnectionUp(handle, type));
    }

 /********************************************************************/
    /** Purpose:
    *      sets new connection Retry timer value. 
    *  Input Parameters:
    *      timer value 
    *  Input/Output Parameters:
    *      None.
    *  Output Parameters:
    *      None.
    *  Return Value:
    *     None. 
    *  Notes:
    *      None.
    *  See Also:
    *      None.
    **/
    /* Revision History:
    *
    *********************************************************************/

    void
    SetIDCconInterval(ITS_INT val)
    {
        IDSCL_SetIDCconInterval(val);
    }

    IDS_INT
    SetSockBindInfo(const IDS_CHAR *host, IDS_INT actPort, IDS_INT bkpPort)
    {
        return (IDSCL_SetSockBindInfo(host, actPort, bkpPort));
    }

    ITS_INT 
    SendGlobalUniqAddrMsg(IDS_MESSAGE *msg)
    {
        return (IDSCL_SendGlobalUniqAddrMsg(handle, msg));
    }
private:

    /********************************************************************/
    /* Purpose:
    *      Client library initialization.
    *
    *  Input Parameters:
    *      None
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
    *      None.
    *
    *  See Also:
    *      None.
    *
    */
    /* Revision History:
    *
    *********************************************************************/
    IDS_INT
    PreInitialize()
    {
        bInitialize = IDS_TRUE;

        return (IDSCL_PreInitialize(&handle));
    }

    /********************************************************************/
    /* Purpose:
    *      Checks if the client library has already been intialized.
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
    *      IDS_TRUE.\n
    *      IDS_FALSE.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    */
    /* Revision History:
    *
    *********************************************************************/
    static IDS_BOOLEAN
    IsPreInitialize()
    {
        return (bInitialize);
    }


private:
    static IDS_HANDLE handle;
    static IDS_BOOLEAN bInitialize;
    /* Flag, to indicate the first request of a session */
    IDS_BOOLEAN newMessage;  
};


#endif
