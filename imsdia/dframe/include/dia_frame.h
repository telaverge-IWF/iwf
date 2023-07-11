/**************************-*-Dia-*-*************************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 *  
 *  ID: $Id: dia_frame.h,v 3.2.28.1.2.6.6.3.4.1.14.1 2014/10/27 08:28:37 pramana Exp $
 *  
 *  LOG: $Log: dia_frame.h,v $
 *  LOG: Revision 3.2.28.1.2.6.6.3.4.1.14.1  2014/10/27 08:28:37  pramana
 *  LOG: changes for HA HotStandBy
 *  LOG:
 *  LOG: Revision 3.2.28.1.2.6.6.3.4.1  2014/01/06 09:22:26  cprem
 *  LOG: Changes in diameter stack to support session replication. Review request 1611.
 *  LOG:
 *  LOG: Revision 3.2.28.1.2.6.6.3  2013/04/08 07:48:42  cprem
 *  LOG: Added a new method for initialization if DiaFrame.
 *  LOG:
 *  LOG: Revision 3.2.28.1.2.6.6.2  2013/04/07 03:57:30  cprem
 *  LOG: Changes made to fix HA bugs. Review Request 784
 *  LOG:
 *  LOG: Revision 3.2.28.1.2.6.6.1  2013/03/22 06:33:33  pramana
 *  LOG: Changes for HA feature
 *  LOG:
 *  LOG: Revision 3.2.28.1.2.6  2012/11/20 17:39:44  pramana
 *  LOG: Merged from CMAPI branch for 212-07 release
 *  LOG:
 *  LOG: Revision 3.2.28.1.2.2.12.2  2012/11/20 10:22:46  rgovardhan
 *  LOG: merge from 00 Nov20Rel
 *  LOG:
 *  LOG: Revision 3.2.28.1.2.4  2012/11/06 16:31:20  pramana
 *  LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
 *  LOG:
 *  LOG: Revision 3.2.28.1.2.2.16.1  2012/11/06 10:06:16  cprem
 *  LOG: Merged from 00 branch for 0212-06 release
 *  LOG:
 *  LOG: Revision 3.2.28.1.2.3  2012/11/05 11:52:37  jvikas
 *  LOG: Changed the macro DIA_BASE_CMD into DiaMsgFlow
 *  LOG:
 *  LOG: Revision 3.2.28.1.2.2  2012/10/01 09:01:00  rsanjay
 *  LOG:  opendiameter code removal changes:bugzilla-id 300
 *  LOG:
 *  LOG: Revision 3.2.28.1.2.1  2012/09/06 11:30:45  jvikas
 *  LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 *  LOG:
 *  LOG: Revision 3.2.28.1.4.1  2012/08/21 06:16:25  jvikas
 *  LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 *  LOG:
 *  LOG: Revision 3.2.28.1  2012/03/07 13:23:08  brajappa
 *  LOG: Changes made for the DRE demo
 *  LOG:
 *  LOG: Revision 3.2  2008/04/01 15:54:52  hbhatnagar
 *  LOG: Changes for Proxy and Relay support (3.0 release) - (Viji, Hemant)
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:25  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.7  2007/01/12 13:48:57  nvijikumar
 *  LOG: Provided API to get session Id or Peer info incase of indications.
 *  LOG:
 *  LOG: Revision 2.6  2006/11/14 10:27:28  nvijikumar
 *  LOG: Provided API to check whether DCCA feature is enabled.
 *  LOG:
 *  LOG: Revision 2.5  2006/10/30 21:40:53  yranade
 *  LOG: Provide ReleaseSession API.
 *  LOG:
 *  LOG: Revision 2.4  2006/10/24 14:33:31  yranade
 *  LOG: Add a Deprecated statement, for SetConfigFile API.
 *  LOG:
 *  LOG: Revision 2.3  2006/10/24 14:26:30  yranade
 *  LOG: RegisterApplication now takes AppId type.
 *  LOG: Reorganize Initialization a bit
 *  LOG:
 *  LOG: Revision 2.2  2006/10/05 12:11:07  yranade
 *  LOG: Updates for ITS-Diameter.
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.8  2006/04/13 18:06:54  yranade
 *  LOG: Warning removal.
 *  LOG:
 *  LOG: Revision 1.7  2006/04/07 11:37:24  yranade
 *  LOG: DoxyGen Compatible Code Comments.
 *  LOG:
 *  LOG: Revision 1.6  2006/03/20 06:23:17  yranade
 *  LOG: Added AllocateSessionIndex API. This "must" be used by Applications
 *  LOG: to "initiate" requests.
 *  LOG:
 *  LOG: Revision 1.5  2006/03/15 09:56:05  yranade
 *  LOG: 1. Split OD Specifics and move them to vendors
 *  LOG: 2. Support Diameter Client Capability
 *  LOG: 3. Code Reorganization
 *  LOG:
 *  LOG: Revision 1.4  2006/03/13 16:38:13  yranade
 *  LOG: Added GetMessageType.
 *  LOG:
 *  LOG: Revision 1.3  2006/03/13 16:29:42  yranade
 *  LOG: Added DiaMsg class abstraction primarily for inbound messages.
 *  LOG:
 *  LOG: Revision 1.2  2006/03/09 11:47:32  tpanda
 *  LOG: Encode/Decode feature provided by wei's api replaced our encode/decode 
 *  LOG: function.Hence dia_codec.* files are redundant
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 13:08:15  tpanda
 *  LOG: Building IMS Diameter Infrastructure
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_frame.h,v 3.2.28.1.2.6.6.3.4.1.14.1 2014/10/27 08:28:37 pramana Exp $"

#ifndef _DIAMETER_FRAMEWORK_H
#define _DIAMETER_FRAMEWORK_H

#include <its++.h>
#include <diameter/Implementation.h>
#include <diameter/Command.h>
#include <dia_cmn.h>
#include <dia_msg_flow.h>
#include <dia_stack.h>
#include <dia_session_table.h>

typedef enum
{
    DIA_AUTHORIZATION_APP = 0,
    DIA_ACCOUNTING_APP
}
DIA_APPLICATION_TYPE;


/** Structure:
 *      DIA_MSG
 *      
 *  Purpose:
 *      DIA_MSG structure is used to represent an inbound message 
 *      from the Diameter Stack. 
 * 
 *  Variables:
 *   \n ITS_OCTET   msgType.
 *   \n ITS_OCTET   indication
 *   \n ITS_UINT    sessionIndex
 *   \n diameter::CommandImpl* cImpl
 **/
typedef struct
{
    ITS_OCTET   msgType;
    ITS_OCTET   indication;
    ITS_UINT    sessionIndex;
    //diameter::Command *cmd;
    DIA_BASE_CMD *cmd;
}
DIA_MSG;
/* forward declaration */
class DiaFrame;

/** Interface:
 *      DiaMsg 
 *      
 *  Purpose:
 *      DiaMsg class is used to represent an inbound message 
 *      from the Diameter Stack. 
 **/
class DiaMsg
{
public:
    friend class DiaFrame;
    /********************************************************************/
    /* Purpose:
    *      Class Constructor
    *
    *  Input Parameters:
    *      The CommandImpl Command to build the Message from
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
    *      This is not exposed to DoxyGen
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/  
    //DiaMsg(diameter::Command *command);
    DiaMsg(DIA_BASE_CMD *command);
    
    /********************************************************************/
    /* Purpose:
    *      Class Constructor
    *
    *  Input Parameters:
    *      ITS_HDR: Header structure to build the message from
    *      DIA_MSG: DIA_MSG structure to build the message from.
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
    *      This is not exposed to DoxyGen.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/     
    DiaMsg(ITS_HDR& _hdr, DIA_MSG& _diaMsg);

    /********************************************************************/
    /* Purpose:
    *      Class Destructor
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
    *      This is not exposed to DoxyGen.
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    ~DiaMsg();
    
    /********************************************************************/
    /** Purpose:
    *      API to retrieve the Application Id in the Msg
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
    *      The Application Id in the Msg
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/    
    ITS_UINT GetApplicationId() const;

    /********************************************************************/
    /** Purpose:
    *       API to retrieve the CommandImpl Object
    *
    *  Input Parameters:
    *       None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Pointer to the CommandImpl Object
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/ 
    const diameter::CommandImpl* GetCommandImpl();
    /********************************************************************/
    /** Purpose:
    *       API to retrieve the CommandImpl Object
    *
    *  Input Parameters:
    *       None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Pointer to the CommandImpl Object
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    const diameter::Command* GetCommand();
    const DIA_BASE_CMD* GetMsgFlow();

    /********************************************************************/
    /** Purpose:
    *       API to retrieve the MessageType of the Msg
    *
    *  Input Parameters:
    *       None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      The Type of the Message
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/ 
    ITS_OCTET GetMessageType() const;

    /********************************************************************/
    /** Purpose:
    *       API to check whether the message is an indication
    *
    *  Input Parameters:
    *       None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      A boolean value which is true in case of an indication
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/ 
    bool IsIndication() const;

    /********************************************************************/
    /** Purpose:
    *       API to retrieve the Type of Indication
    *
    *  Input Parameters:
    *       None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      The type of indication
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    ITS_OCTET GetIndication() const;

    /********************************************************************/
    /** Purpose:
    *       API to retrieve the SessionIndex of the Msg
    *
    *  Input Parameters:
    *       None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      The Unique session index that this message is part of.
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    ITS_UINT GetSessionIndex() const;

    /********************************************************************/
    /* Purpose:
    *       API to retrieve the Header associated with the Msg
    *
    *  Input Parameters:
    *       None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      The type of indication
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    const ITS_HDR& GetHeader() const;

    /********************************************************************/
    /* Purpose:
    *       API to retrieve the Data associated with the indication.
    *  Example:
    *       Returns Session Id for Session related indications.
    *       Returns FQDN for peer related indications.
    *
    *  Input Parameters:
    *       None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Session Id for Session related indications.
    *      FQDN for peer related indications.
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    const char* GetIndicationData();

private:
    ITS_HDR hdr;
    DIA_MSG diaMsg;
  
    /* Used for Transport disconnect indication to App */
    const char* indicationData;

};

/* Interface:
 *      Abstract DiaFramework Class. 
 *      
 *  Purpose:
 *      DiaFramework class provides abstraction services for an Application
 *      to Initialize, Terminate, Send and Receive with the Base Diameter
 *      Stack.
 *
 *  Note:
 *      Not exposed to DoxyGen
 *
 *  See Also:
 *      DiaFrame Class
 **/
class DiaFramework
{
public:
    virtual ~DiaFramework(){};

    /********************************************************************/
    /* Purpose:
    *      Pure Virtual Function Initialize a Diameter Stack. Derived
    *      Classes *must* implement this to provide needed functionality
    *      with 3'rd party diameter vendor.
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
    *      This is not exposed to DoxyGen
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    virtual int Initialize(bool isActive = false) = 0;

    /********************************************************************/
    /* Purpose:
    *      Pure Virtual Function Terminate a Diameter Stack. Derived
    *      Classes *must* implement this to provide needed functionality
    *      with 3'rd party diameter vendor.
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
    *      This is not exposed to DoxyGen
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    virtual int Terminate() = 0;
    
    /********************************************************************/
    /* Purpose:
    *      Pure Virtual Function Send a Command to a Diameter Stack. Derived
    *      Classes *must* implement this to provide needed functionality
    *      with 3'rd party diameter vendor.
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
    *      This is not exposed to DoxyGen
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    virtual int Send(const diameter::Command* msg) = 0;
    
    /********************************************************************/
    /* Purpose:
    *      Pure Virtual Function to convert an ITS_Event to a Command. 
    *      Derived Classes *must* implement this to provide needed 
    *      functionality with 3'rd party diameter vendor.
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
    *      This is not exposed to DoxyGen
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    virtual int Receive(its::Event& ev, DiaMsg** msg) = 0;

};

/** Interface:
 *      Singleton DiaFrame Class. Applications utlize the services
 *      provided by this class to communicate with the base diameter stack 
 *      
 *  Purpose:
 *      DiaFrame class provides abstraction services for an Application
 *      to Initialize, Terminate, Send and Receive with the Base Diameter
 *      Stack. 
 **/
class DiaFrame: public DiaFramework
{
public:
    /********************************************************************/
    /** Purpose:
    *      Static Function to get the DiaFrame instance. 
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
    *      Pointer to the singleton DiaFrame object.
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
    static DiaFrame *GetDiaFrame();
    static DiaFrame *InitDiaFrame();
    
    /********************************************************************/
    /** Purpose:
    *      Function to Initialize the Diameter Stack. 
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
    *      A return value of ITS_SUCCESS signifies successful stack 
    *      initialization.
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
    //int Initialize();

    int Initialize(bool isActive = true);

    /********************************************************************/
    /** Purpose:
     *      Function to Initiate the local and peer transport connections
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
     *      A return value of ITS_SUCCESS signifies successful transport 
     *      initialization.
     *
     *  Notes:
     *      This method is used in the HA context where the transports of ACTIVE node should
     *      be initialized.
     *
     *  See Also:
     *      None.
     *
     **/
    /* Revision History:
     *
     *********************************************************************/
    //int InitTransports();
    int GoActive();

    /********************************************************************/
    /** Purpose:
    *      Function to Terminate the Diameter Stack. 
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
    *      A return value of ITS_SUCCESS signifies successful stack 
    *      termination.
    *
    *  Notes:
    *      It is mandatory for the application to terminate the Diameter stack
    *      before application termination.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    int Terminate();

    /********************************************************************/
    /** Purpose:
    *      Function to Terminate the local and peer transport connections
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
    *      A return value of ITS_SUCCESS signifies successful transport 
    *      termination.
    *
    *  Notes:
    *      This method is used in the HA context where the transports of standby should
    *      be terminated.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    //int TermTransports();
    int GoStandby();

    /********************************************************************/
    /** Purpose:
    *      Function to Register an ApplicationId with the Stack.  
    *
    *  Input Parameters:
    *      ITS_UINT appId: The ApplicationId of the Diameter Application
    *      ITS_UINT appId: The Type of diameter application
    *                0 == AUTHORIZATION
    *                1 == ACCOUNTING 
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      A return value of ITS_SUCCESS signifies successful stack 
    *      initialization.
    *
    *  Notes:
    *      The Usage of this API is mandatory to initiate communication
    *      with the Diameter stack.
    *      This API should be called before initializing the stack.
    *      THe Applications Registered are exchanged in CER/CEA exchange.
    *
    *  See Also:
    *      struct DIA_APPLICATION_TYPE 
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    int RegisterApplication(ITS_UINT appId, ITS_UINT appType = 0);
    
    /********************************************************************/
    /** Purpose:
    *      Function to Allocate/Request a SessionId from the Stack.  
    *
    *  Input Parameters:
    *      ITS_UINT appId: The ApplicationId of the Diameter Application
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      ITS_UINT& sessId: An unique stack generated session index
    *       
    *      std::string& sessIdString: An unique stack generated sessionId String
    *
    *  Return Value:
    *      A return value of ITS_SUCCESS signifies successful Session 
    *      allocation.
    *
    *  Notes:
    *      The Usage of this API is mandatory to initiate requests from
    *      the application.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    int AllocateSessionIndex(ITS_UINT appId, ITS_UINT& sessId, 
                            std::string& sessIdString);

    int ReleaseSession(std::string sessIdString);

    bool IsDccaEnabled();
                            
    /********************************************************************/
    /** Purpose:
    *      Function to Send a Command to Stack.  
    *
    *  Input Parameters:
    *      const diameter::Command* msg: The Diameter Command to send
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      A return value of ITS_SUCCESS signifies successful sending
    *      of the Diameter Message to the Stack.
    *
    *  Notes:
    *      The Usage of this API is mandatory to send requests from
    *      the application.
    *
    *  See Also:
    *      AllocateSessionIndex()
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    int Send(const diameter::Command* msg);

    /********************************************************************/
    /* Purpose:
    *      Function to Send a Command to Stack on a SessionIndex
    *
    *  Input Parameters:
    *      const diameter::Command* msg: The Diameter Command to send
    *      ITS_UINT sessIndex: SessionIndex to send the message on.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      A return value of ITS_SUCCESS signifies successful sending
    *      of the Diameter Message to the Stack.
    *
    *  Notes:
    *      Deprecated: Not exposed in DoxyGen.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    int Send(const diameter::Command* msg, ITS_UINT sessIndex, 
             ITS_USHORT toPeer = 0xFF, ITS_UINT flags = 0);
    
    int Send(const diameter::DiaMsgFlow* msg, ITS_UINT sessIndex, ITS_USHORT toPeer, ITS_UINT flags);
    /********************************************************************/
    /** Purpose:
    *       Function to Receive Diameter Command from Stack. 
    *       An Application can pass the Event received from the queue, 
    *       to this function to retrieve the correct DiaMsg object. 
    *       The DiaMsg type can then be used to find whether it's data 
    *       received or whether it's an indication from the stack.
    *
    *  Input Parameters:
    *       its::Event& ev: Reference to the Event Received
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      DiaMsg** msg: The Received DiaMsg object pointer
    *
    *  Return Value:
    *      A return value of ITS_SUCCESS signifies successful receipt
    *      of the Diameter Message from the Stack.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      DiaMsg::IsIndication()
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    int Receive(its::Event& ev, DiaMsg** msg);
    
    /********************************************************************/
    /** Purpose:
    *      Function to Set the Diameter Stack Configuration File.
    *
    *  Input Parameters:
    *      char* cfgFile: The Diameter Configuration File Name.
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
    *      NOTE NOTE: DEPRECATED..and SHOULD NO LONGER BE USED.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    void SetConfigFile(char* cfgFile);

    /*
     * Replication Calback registrations.
     */
    int registerCreateSessionReplicationCbk(createSessionCbk );
    int registerUpdateSessionReplicationCbk(updateSessionCbk );
    int registerDeleteSessionReplicationCbk(deleteSessionCbk );
    int registerFetchSessionReplicaCbk(fetchSessionCbk );
    int enableReplication();
    int disableReplication();

    int ReCreateSessionEntry(string& sessionId, ITS_EVENT& event);

private:
    DiaFrame();                           /* Private Constructor */
    DiaFrame(const DiaFrame&);            /* Prevent Copy Constructor */    
    DiaFrame& operator=(const DiaFrame&); /* Prevent assignment */
    void Lock() const;
    void Unlock() const;
    DiaStackClass obj;
    ITS_BOOLEAN stackInitialized;
    char *configFile;
    static its::ITS_Mutex lock;
    static its::ITS_Mutex guard;
};


#endif

