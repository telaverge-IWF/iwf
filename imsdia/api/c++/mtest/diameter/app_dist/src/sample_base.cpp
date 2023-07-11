/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *    This product and related documentation is protected by copyright and  *
 *    distributed under licenses restricting its use, copying, distribution *
 *    and decompilation.  No part of this product or related documentation  *
 *    may be reproduced in any form by any means without prior written      *
 *    authorization of IntelliNet Technologies and its licensors, if any.   *
 *                                                                          *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     *
 *    government is subject to restrictions as set forth in subparagraph    *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software      *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                       *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: sample_base.cpp,v $
 * LOG: Revision 3.4  2008/04/16 11:05:55  avinashks
 * LOG: Changes done for Application to support agents.
 * LOG:
 * LOG: Revision 3.3  2008/04/08 19:14:06  avinashks
 * LOG: Added ProxyInfo AVPs from request to answer while sending answer.
 * LOG: Also properly handled the return values.
 * LOG:
 * LOG: Revision 3.2  2008/04/07 09:42:26  avinashks
 * LOG: Changes made for Implementation of Proxy client.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:06  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:09:04  kamakshilk
 * LOG: Common Files required for distributed set up
 * LOG:
 * LOG:
 *
 * ID: $Id: sample_base.cpp,v 3.4 2008/04/16 11:05:55 avinashks Exp $
 ****************************************************************************/
#ident "$Id: sample_base.cpp,v 3.4 2008/04/16 11:05:55 avinashks Exp $"

#include <dia_defines.h>

#include <diameter/base/ReAuth.h>
#include <diameter/base/AbortSession.h>
#include <diameter/base/SessionTermination.h>
#include <diameter/base/Accounting.h>
#include <diameter/base/CapabilitiesExchange.h>
#include <diameter/base/DeviceWatchdog.h>
#include <diameter/base/DisconnectPeer.h>
#include <diameter/base/BaseGenericCommand.h>

#include <app.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;

extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function Processes the Proxiable messages.
 *
 *  Input Parameters:
 *      BaseGenericCommand
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success returns ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
ProcessIfProxy(diameter::Command *cmd)
{
    ITS_INT pinfo_avp_count=0, avpCount;
    ProxyInfo *pinf=NULL;
    ITS_INT ret = (!ITS_SUCCESS);

    const char *oriHost = GetOriginHost();
    const char *oriRealm = GetOriginRealm();
    
    diameter::base::BaseGenericCommand *gCmd = 
                                (diameter::base::BaseGenericCommand *) cmd;

    if(gCmd->isRequest())
    {
        if(!strcmp(gCmd->getDestinationRealm()->value().c_str(), oriRealm))
        {
            return ret;
        }
        else
        {
            if(gCmd->isProxyable())
            {
                ProxyInfo pinfo;

                ProxyHost phost(oriHost);
                pinfo.setProxyHost(phost);

                ProxyState pstate("state0");
                pinfo.setProxyState(pstate);

                gCmd->getContainer().add(pinfo.name(),pinfo,false);
                if ((ret = SendDiaAppMsg(*gCmd, gCmd->getSessionIndex())) 
                                                          != ITS_SUCCESS)
                {
                    APP_TRACE_ERROR(("SendDiaAppMsg Failure"));
                }  
                return ret;
            }
            else
            {
                APP_TRACE_DEBUG(("Message is NOT Proxiable..."));
            }
        }
    }
    else
    {
        pinfo_avp_count = gCmd->countProxyInfo();

        for(avpCount=0; avpCount < pinfo_avp_count; avpCount++)
        {
            if(!strcmp(oriHost,
                       gCmd->getProxyInfo(avpCount)->getProxyHost(). \
                       value().c_str()))
            {
                const ProxyInfo *pinfo1 = gCmd->getProxyInfo(avpCount);
                pinf = (ProxyInfo*) pinfo1;
                if(gCmd->isProxyable())
                {
                    APP_TRACE_DEBUG(("Message is Proxiable..."));
                    if ((pinf->removeAVP(pinf->getProxyHost())) == ITS_SUCCESS)
                    {
                        APP_TRACE_DEBUG(("Proxy-Host AVP removed successfully"));
                    }
                    else
                    {
                        APP_TRACE_ERROR(("Unable to remove Proxy-Host AVP"));
                    }
                    if ((pinf->removeAVP(pinf->getProxyState())) == ITS_SUCCESS)
                    {
                        APP_TRACE_DEBUG(("Proxy-State AVP removed successfully"));
                    }
                    else
                    {
                        APP_TRACE_ERROR(("Unable to remove Proxy-State AVP"));
                    }
                    if (((Command*)gCmd)->removeAVP(*pinf) == ITS_SUCCESS)
                    {
                        APP_TRACE_DEBUG(("Proxy-Info AVP removed successfully"));
                    }
                    else
                    {
                        APP_TRACE_ERROR(("Unable to remove Proxy-Info AVP"));
                    }

                    if ((ret = SendDiaAppMsg(*gCmd, gCmd->getSessionIndex())) != ITS_SUCCESS)
                    {
                        APP_TRACE_ERROR(("SendDiaAppMsg Failure"));
                    }  
                    return ret;
                }
                else
                {
                   APP_TRACE_DEBUG(("Message is NOT Proxiable..."));
                }
            } 
        }
    }
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function processes the message received from the base
 *      diameter stack. It identifies the commands and processes that command.
 *
 *  Input Parameters:
 *     ITS_Event& ev: Event Received from the Queue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success returns ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int HandleBaseMessages(const diameter::CommandImpl *impl,
                                   unsigned int &sIdxBase)
{
    ITS_BOOLEAN isProxy;
    ITS_INT ret = !(ITS_SUCCESS);
    ITS_INT count=0;
    sIdx = sIdxBase;
    Command *cmd = NULL;

    APP_TRACE_DEBUG(("Base Diameter Messages Received"));

    const char *oriHost = GetOriginHost();
    const char *oriRealm = GetOriginRealm();
   
    // Process the commands based on the command code.
    switch (impl->getCommandCode())
    {
    case BASE_RA_MSG_CMD_CODE:
        if (impl->isRequest())
        {
            APP_TRACE_DEBUG(("Processing Request..."));
            ReAuthRequest rreq(*impl);
            cmd = (Command*)&rreq;
            if ((ret = ProcessIfProxy(cmd)) == ITS_SUCCESS)
            {
                if (appMode == UNIT_TEST)
                    cout<<rreq;
            }
            else 
            {
                if (appMode == UNIT_TEST)
                    cout << "Re-Auth-Request" << rreq << endl;
                SendReAuthAnswer(impl);
                ret = ITS_SUCCESS; 
            }
        }
        else
        {
            APP_TRACE_DEBUG(("Processing Answer..."));

            ReAuthAnswer rans(*impl);
            cmd = (Command*)&rans;
            if ((ret = ProcessIfProxy(cmd)) == ITS_SUCCESS)
            {
                if (appMode == UNIT_TEST)
                    cout<<rans;
                ret = ITS_SUCCESS;   
            }
            else
            {
                if (appMode == UNIT_TEST)
                    cout << "Re-Auth-Answer" << rans << endl;
                ret = ITS_SUCCESS;
            }
        }
        break;
    case BASE_AS_MSG_CMD_CODE: 
        if (impl->isRequest())
        {
            APP_TRACE_DEBUG(("Processing Request..."));
            AbortSessionRequest asreq(*impl);
            cmd = (Command*)&asreq;
            if ((ret = ProcessIfProxy(cmd)) == ITS_SUCCESS)
            {
                if (appMode == UNIT_TEST)
                    cout<<asreq;
            }
            else 
            {
                if (appMode == UNIT_TEST)
                   cout << "Abort-Session-Request" << asreq << endl;
                SendAbortSessionAnswer(impl);
                ret = ITS_SUCCESS; 
            }
        }
        else
        {
            APP_TRACE_DEBUG(("Processing Answer..."));

            AbortSessionAnswer asans(*impl);
            cmd = (Command*)&asans;
            if ((ret = ProcessIfProxy(cmd)) == ITS_SUCCESS)
            {
                if (appMode == UNIT_TEST)
                    cout<<asans;
                ret = ITS_SUCCESS; 
            }
            else
            {
                if (appMode == UNIT_TEST)
                    cout << "Abort-Session-Answer" << asans << endl;
                ret = ITS_SUCCESS;
            }
        }
        break;

    case BASE_ST_MSG_CMD_CODE:
        if (impl->isRequest())
        {
            APP_TRACE_DEBUG(("Processing Request..."));
            SessionTerminationRequest streq(*impl);  
            cmd = (Command*)&streq;
            if ((ret = ProcessIfProxy(cmd)) == ITS_SUCCESS)
            {
                if (appMode == UNIT_TEST)
                    cout<<streq;
            }
            else 
            {
                if (appMode == UNIT_TEST)
                    cout << "Session-Termination-Request" << streq << endl;
                SendSessionTerminationAnswer(impl);
                ret = ITS_SUCCESS; 
            }
        }
        else
        {
            APP_TRACE_DEBUG(("Processing Answer..."));

            SessionTerminationAnswer stans(*impl);
            cmd = (Command*)&stans;
            if ((ret = ProcessIfProxy(cmd)) == ITS_SUCCESS)
            {
                     if (appMode == UNIT_TEST)
                         cout<<stans;
                     ret = ITS_SUCCESS; 
            }
            else
            {
                if (appMode == UNIT_TEST)
                    cout << "Session-Termination-Answer" << stans << endl;
                ret = ITS_SUCCESS;
            }
        }
        break;

    case BASE_CE_MSG_CMD_CODE:
        if(impl->isRequest())
        {
            CapabilitiesExchangeRequest cereq(*impl);
            if (appMode == UNIT_TEST)
                cout << endl << "Capabilties Exchange Request Received "
                     << cereq << endl;
        }
        else
        {
            CapabilitiesExchangeAnswer ceans(*impl);
            if (appMode == UNIT_TEST)
                cout << endl << "Capabilties Exchange Answer Received"
                     << ceans << endl;
        }
        break;
    case BASE_DW_MSG_CMD_CODE:
        if(impl->isRequest())
        {
            DeviceWatchdogRequest dwreq(*impl);
            if (appMode == UNIT_TEST)
                cout << endl << "Device Watch Dog Request Received"
                     << dwreq << endl;
        }
        else
        {
            DeviceWatchdogAnswer dwans(*impl);
            if (appMode == UNIT_TEST)
                cout << endl <<"Device Watch Dog Answer Received"
                     << dwans << endl;
        }
        break;
    case BASE_DP_MSG_CMD_CODE:
        if(impl->isRequest())
        {
            DisconnectPeerRequest dpreq(*impl);
            if (appMode == UNIT_TEST)
                cout << endl << "Disconnect Peer Request Received"
                     << dpreq << endl;
        }
        else
        {
            DisconnectPeerAnswer dpans(*impl);
            if (appMode == UNIT_TEST)
                cout << endl <<"Disconnect Peer Answer Received"
                     << dpans << endl;
        }
        break;
    case BASE_ACCT_MSG_CMD_CODE:
        if(impl->isRequest())
        {
            AccountingRequest areq(*impl);
            if (appMode == UNIT_TEST)
                cout << endl << "Accounting Request Received"
                     << areq << endl;
        }
        else
        {
            AccountingAnswer aans(*impl);
            if (appMode == UNIT_TEST)
                cout << endl << "Accounting Answer Received"
                     << aans << endl;
        }
        break;
    default:
        APP_TRACE_WARNING(("Unknown Base Protocol Message Received"));
        break;
    }

    return ret;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function displays the menu options for the
 *      Base protocol interface used by the Other Applications.
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
 *      Returns the option selected.
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
DisplayBaseMenuToApp()
{
    string input;
    int ret = 0;

    do
    {
        cout << endl << "Enter your choice to send the following base Messages"
             << endl << endl;
        cout << endl << " (1) . RAR - ReAuth Req Command" << endl;
        cout << endl << " (2) . STR - Session Termination Req Command" << endl;
        cout << endl << " (3) . ASR - Abort Session Req Command" << endl;
        cout << endl << "(99) . Back" << endl;

        cin >> input;
        ret = atoi(input.c_str());

    } while ((ret < 1 || ret > 3) && ret!=99);

    switch(ret)
    {
        case 1:
            return SendReAuthRequest();
        case 2:
            return SendSessionTerminationRequest();
        case 3:
            return SendAbortSessionRequest();
        case 99:
            return 0;
        default:
            cout << endl << "please enter the correct choice";
            break;
    }
    return 0;

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the ReAuthentication request to the
 *      diameter stack. Create the ReAuthRequest object,
 *      populate the AVPs and send the message to the stack.
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
int SendReAuthRequest() 
{
    // [1] Create ReAuthRequest object.
    // Optional param error - whether this command carries an error indicator.
    // optional param retrans - whether this is a retransmission.
    ReAuthRequest rar(false, false);

    // [2] Insert data in the created ReAuthRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed paramete "Session-Id".
    cout << "Please Enter Session ID for ReAuth" << endl;
    string sessId;
    cin >> sessId;
    rar.setSessionId(SessionId(sessId));

    // [2.1.2] Populate required Mandatories.
    // [2.1.2.1] Populate required paramete "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost origh(GetOriginHost());
    rar.setOriginHost(origh);

    // [2.1.2.2] Populate required paramete "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
    rar.setOriginRealm(origr);

    // [2.1.2.3] Populate required paramete "Destination-Realm".
    // Set the Destination-Realm AVP.
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    DestinationRealm desr(GetDestinationRealm());
    rar.setDestinationRealm(desr);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost desh(GetDestinationHost());
    rar.setDestinationHost(desh);

    // [2.1.2.5] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId authId(0u);//Base protocol
    rar.setAuthApplicationId(authId);

    // [2.1.2.6] Populate required parameter "Re-Auth-Request-Type".
    // Set the Re-Auth-Request-Type AVP.
    // The data type of Re-Auth-Request-Type is Enumerated.
    // This AVP is used to inform the client of the action expected upon
    // expiration of the Authorization-Lifetime.
    // The AVP Code of Re-Auth-Request-Type is 285.
    ReAuthRequestType rear1(ReAuthRequestType::AUTHORIZE_ONLY);
    rar.setReAuthRequestType(rear1);

    // [2.2] Populate Optionals
    // [2.2.1] Populate Optional paramete "User-Name".
    // Set the User-Name AVP.
    // The data type of User-Name is UTF8String.
    // This AVP contains the User-Name.
    // The AVP Code of User-Name is 1.
    UserName uname1("sip:adam.smith@india.internal.net");
    rar.setUserName(uname1);

    // [2.2.2] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId origsid(41);
    rar.setOriginStateId(origsid);

    // [2.2.3] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo pi1;

    // [2.2.3.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info AVP.
    // The AVP Code of Proxy-Info is 280.
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.3.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as opaque
    //  data
    // The AVP Code of Proxy-State is 33.
    // Stack sets this AVP.
    // Application should not set this AVP
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);
    //rar.addProxyInfo(pi1);

    // [2.2.4] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the message.
    // The AVP Code of Route-Record is 282.

    //RouteRecord rrec("jerry");
    // rar.addRouteRecord(rrec);

    if (appMode == UNIT_TEST)
        cout << rar << endl;

    SendDiaAppMsg(rar, sIdx);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Session termination request to the
 *      diameter stack. Create the SessionTerminationRequest
 *      object, populate the AVPs and send the message to the stack.
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
int SendSessionTerminationRequest(const SessionId *sesId) 
{
   // [1] Create SessionTerminationRequest object.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    SessionTerminationRequest str(false, false);

    // [2] Insert data in the created SessionTerminationRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed paramete "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
//    if (appMode == LOAD_TEST)
    {
//        str.setSessionId(*sesId);
    }
//    else
    {
        cout<<"Please Enter Session Id to Terminate"<<endl;
        string sessId;
        cin>>sessId;
        str.setSessionId(SessionId(sessId));
    }


    // [2.1.2] Populate required Mandatories.
    // [2.1.2.1] Populate required paramete "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost origh(GetOriginHost());
    str.setOriginHost(origh);

    // [2.1.2.2] Populate required paramete "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
    str.setOriginRealm(origr);

    // [2.1.2.3] Populate required paramete "Destination-Realm".
    // Set the Destination-Realm AVP.
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    DestinationRealm desr(GetDestinationRealm());
    str.setDestinationRealm(desr);

    // [2.1.2.4] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId authid((Unsigned32)0);
    str.setAuthApplicationId(authid);

    // [2.1.2.5] Populate required parameter "Termination-Cause".
    // Set the Termination-Cause AVP.
    // The data type of Termination-Cause is Enumerated.
    // This AVP  is used to indicate the reason why a session was terminated on
    // the access device.
    // The following values are defined:
    // DIAMETER_LOGOUT                   1
    // DIAMETER_SERVICE_NOT_PROVIDED     2
    // DIAMETER_BAD_ANSWER               3
    // DIAMETER_ADMINISTRATIVE           4
    // DIAMETER_LINK_BROKEN              5
    // DIAMETER_AUTH_EXPIRED             6
    // DIAMETER_USER_MOVED               7
    // DIAMETER_SESSION_TIMEOUT          8
    // The AVP Code of Termination-Cause is 295.
    TerminationCause termc(TerminationCause::DIAMETER_BAD_ANSWER);
    str.setTerminationCause(termc);

    // [2.2] Populate Optionals
    // [2.2.1] Populate Optional paramete "User-Name".
    // Set the User-Name AVP.
    // The data type of User-Name is UTF8String.
    // This AVP contains the User-Name.
    // The AVP Code of User-Name is 1.
    UserName un("sip:john.smith@india.internal.net");
    str.setUserName(un);

    // [2.2.2] Populate optional paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost desh(GetDestinationHost());
    str.setDestinationHost(desh);

    // [2.2.3] Populate optional parameter "Class".
    // Set the Class AVP.
    // The data type of Class is OctetString.
    //This AVP is used to by Diameter servers to return state information to the
    // access device.
    // The AVP Code of Class is 25.
    Class class1("business");
    str.addClass(class1);
    Class class2("residential");
    str.addClass(class2);

    // [2.2.4] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId origsid(41);
    str.setOriginStateId(origsid);

    // [2.2.5] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo pi1;

    // [2.2.5.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info AVP.
    // The AVP Code of Proxy-Info is 280.
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.5.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as opaque
    //  data
    // The AVP Code of Proxy-State is 33.
    // Stack sets this AVP.
    // Application should not set this AVP
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    // [2.2.6] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the message.
    // The AVP Code of Route-Record is 282.
    // Stack sets this AVP.
    // Application should not set this AVP
    //RouteRecord rrec("jerry");
    //str.addRouteRecord(rrec);

    // [3] Use appropriate application specific logic to Send object

    if (appMode == UNIT_TEST)
        cout << str << endl;

    SendDiaAppMsg(str, sIdx);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Abort session request to the
 *      diameter stack. Create the AbortSessionRequest
 *      object, populate the AVPs and send the message to the stack.
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
int SendAbortSessionRequest() 
{
    // [1] Create AbortSessionRequest object.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    AbortSessionRequest asr(false, false);

    // [2] Insert data in the created object
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed paramete "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    cout << "Please Enter Session ID" << endl;
    string sessId;
    cin >> sessId;
    asr.setSessionId(SessionId(sessId)); 

    // [2.1.2] Populate required Mandatories.
    // [2.1.2.1] Populate required paramete "Origin-Host".
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost orig(GetOriginHost());
    asr.setOriginHost(orig);

    // [2.1.2.2] Populate required paramete "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
    asr.setOriginRealm(origr);

    // [2.1.2.3] Populate required paramete "Destination-Realm".
    // Set the Destination-Realm AVP.
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    DestinationRealm destr(GetDestinationRealm());
    asr.setDestinationRealm(destr);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost desth(GetDestinationHost());
    asr.setDestinationHost(desth);

    // [2.1.2.5] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId authid((Unsigned32)0);
    asr.setAuthApplicationId(authid);

    // [2.2] Populate Optionals
    // [2.2.1] Populate Optional paramete "User-Name".
    // Set the User-Name AVP.
    // The data type of User-Name is UTF8String.
    // This AVP contains the User-Name.
    // The AVP Code of User-Name is 1.
    UserName userName("sip:john.smith@india.internal.net");
    asr.setUserName(userName);

    // [2.2.2] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId org(41);
    asr.setOriginStateId(org);

    // [2.2.3] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo pi1;

    // [2.2.3.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info AVP.
    // The AVP Code of Proxy-Info is 280.
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.3.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as opaque
    //  data
    // The AVP Code of Proxy-State is 33.
    // Stack sets this AVP.
    // Application should not set this AVP
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);
    //asr.addProxyInfo(pi1);

    // [2.2.4] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the message.
    // The AVP Code of Route-Record is 282.
    // Stack sets this AVP.
    // Application should not set this AVP
    //RouteRecord rrec("jerry");
    //asr.addRouteRecord(rrec);

    // [3] Use appropriate application specific logic to Send object

    if (appMode == UNIT_TEST)
        cout << asr << endl;

    SendDiaAppMsg(asr, sIdx); 

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the Abort session request
 *      made by the diameter stack. Create the AbortSessionAnswer
 *      object, populate the AVPs and send the message to the stack.
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
int SendAbortSessionAnswer(const CommandImpl* impl1)
{
    // [1] Create AbortSessionAnswer object.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    AbortSessionAnswer asa(false, false);

    AbortSessionRequest com_req(*impl1);

    // [2] Insert data in the created object
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed paramete "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId &sid1 = com_req.getSessionId();
    asa.setSessionId(sid1);

    // [2.2.2] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    // -  1xxx (Informational)
    //   -  2xxx (Success)
    //   -  3xxx (Protocol Errors)
    //   -  4xxx (Transient Failures)
    //   -  5xxx (Permanent Failure)
    ResultCode resCode(2001u);
    asa.setResultCode(resCode);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    const DestinationHost &dh1 = com_req.getDestinationHost();
    OriginHost orig(dh1.value());
    asa.setOriginHost(orig);

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    const DestinationRealm &dr1 = com_req.getDestinationRealm();
    OriginRealm origr(dr1.value());
    asa.setOriginRealm(origr);

    // [2.2.3] Populate Optional paramete "User-Name".
    // Set the User-Name AVP.
    // The data type of User-Name is UTF8String.
    // This AVP contains the User-Name.
    // The AVP Code of User-Name is 1.
    UserName userName("sip:john.smith@india.internal.net");
    asa.setUserName(userName);

    // [2.2.4] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever
    // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId org(41);
    asa.setOriginStateId(org);

    // [2.2.5] Populate optional parameter "Error-Message".
    // Set the Error-Message AVP.
    // The data type of Error-Message is UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message.
    // The AVP Code of Error-Message is 281.
    // ErrorMessage err("Authentication error");
    // asa.setErrorMessage(err);

    // [2.2.6] Populate optional parameter "Error-Reporting-Host".
    // Set the Error-Reporting-Host AVP.
    // The data type of Error-Reporting-Host is DiameterIdentity.
    // This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP to a value other than 2001
    // (Success), only if the host setting the Result-Code is different from
    // the one encoded in the Origin-Host AVP.  This AVP is intended to be
    // used for troubleshooting purposes, and MUST be set when the Result-
    // Code AVP indicates a failure.
    // The AVP Code of Error-Reporting-Host is 294.
    //ErrorReportingHost errh("dia.xyz.com");
    //asa.setErrorReportingHost(errh);

    //FailedAVP fh1;
    //asa.addFailedAVP(fh1);

    // [2.2.7] Populate optional parameter "Redirect-Host".
    // Set the Redirect-Host AVP.
    // The data type of Redirect-Host is DiamURI.
    //
    // The AVP Code of Redirect-Host is 292.
    // Application should not set this AVP.
    // Stack sets this AVP.
    //URI uri1("SecondaryEventCollectionFunction.com", URI::AAA,
    //        3880, URI::TCP, URI::DIAMETER);
    //RedirectHost rh(uri1);
    //asa.addRedirectHost(rh);

    // [2.2.8] Populate optional parameter "Redirect-Host-Usage".
    // Set the Redirect-Host-Usage AVP.
    // The data type of Redirect-Host-Usage is Enumerated.
    // This AVP MAY be present in answer messages whose 'E' bit is set and
    // the Result-Code AVP is set to DIAMETER_REDIRECT_INDICATION.
    // The AVP Code of Redirect-Host-Usage is 261.
    // Application should not set this AVP.
    // Stack sets this AVP.
    //RedirectHostUsage rhu(RedirectHostUsage::ALL_SESSION);
    //asa.setRedirectHostUsage(rhu);

    // [2.2.9] Populate optional parameter "Redirect-Max-Cache-Time".
    // Set the Redirect-Max-Cache-Time AVP.
    // The data type of Redirect-Max-Cache-Time is Unsigned32.
    // This AVP MUST be present in answer messages whose 'E' bit is set, the
    // Result-Code AVP is set to DIAMETER_REDIRECT_INDICATION and the
    // Redirect-Host-Usage AVP set to a non-zero value.
    // The AVP Code of Redirect-Max-Cache-Time is 262.
    // Application should not set this AVP.
    // Stack sets this AVP.
    //RedirectMaxCacheTime rmct(500);
    //asa.setRedirectMaxCacheTime(rmct);

    // [2.2.10] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo pi1;

    // [2.2.10.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info 
    // AVP.
    // The AVP Code of Proxy-Info is 280.
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.10.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as opaque
    //  data
    // The AVP Code of Proxy-State is 33.
    // Stack sets this AVP.
    // Application should not set this AVP
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    //asa.addProxyInfo(pi1);

    int pinfo_count = com_req.countProxyInfo();
    for(int i=0; i<pinfo_count; i++)
    {
        ProxyInfo pinfo;
        ProxyHost phost(com_req.getProxyInfo(i).getProxyHost());
        pinfo.setProxyHost(phost);

        ProxyState pstate(com_req.getProxyInfo(i).getProxyState());
        pinfo.setProxyState(pstate);

        asa.addProxyInfo(pinfo);
    }


    // [3] Use appropriate application specific logic to Send object

    if (appMode == UNIT_TEST)
        cout << asa << endl;

    SendDiaAppMsg(asa, sIdx);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the ReAuth request made
*       by the diameter stack. Create the ReAuthAnswer
 *      object, populate the AVPs and send the message to the stack.
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
int SendReAuthAnswer(const CommandImpl *impl1)
{
    // [1] Create ReAuthAnswer object.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    ReAuthAnswer raa(false, false);

    ReAuthRequest com_req(*impl1);

    const OriginHost& oh1 = com_req.getOriginHost();
    const DestinationHost& dh1 = com_req.getDestinationHost();
    const OriginRealm& or1 = com_req.getOriginRealm();
    const DestinationRealm& dr1 = com_req.getDestinationRealm();

    // [2] Insert data in the created object
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed paramete "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId& sid1 = com_req.getSessionId();
    raa.setSessionId(sid1);

    // [2.2.2] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    ResultCode rc(2001u);
    raa.setResultCode(rc);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost origh(dh1.value());
    raa.setOriginHost(origh);

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(dr1.value());
    raa.setOriginRealm(origr);

    // [2.2.5] Populate Optional paramete "User-Name".
    // Set the User-Name AVP.
    // The data type of User-Name is UTF8String.
    // This AVP contains the User-Name.
    // The AVP Code of User-Name is 1.
    UserName uname1("sip:adam.smith@india.internal.net");
    raa.setUserName(uname1);

    // [2.2.6] Populate required parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // is a monotonically increasing value that is advanced whenever a 
    // Diameter entity restarts with loss of previous state, for example
    // upon reboot. Origin-State-Id MAY be included in any Diameter message,
    // including CER.
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId origsid(41);
    raa.setOriginStateId(origsid);

    // [2.2.7] Populate optional parameter "Error-Message".
    // Set the Error-Message AVP.
    // The data type of Error-Message is UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message.
    // The AVP Code of Error-Message is 281.
    // ErrorMessage erm("Server problem");
    // raa.setErrorMessage(erm);

    // [2.2.8] Populate optional parameter "Error-Reporting-Host".
    // Set the Error-Reporting-Host AVP.
    // The data type of Error-Reporting-Host is DiameterIdentity.
    // This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP to a value other than 2001
    // (Success), only if the host setting the Result-Code is different from
    // the one encoded in the Origin-Host AVP.  This AVP is intended to be
    // used for troubleshooting purposes, and MUST be set when the Result-
    // Code AVP indicates a failure.
    // The AVP Code of Error-Reporting-Host is 294.
    // ErrorReportingHost erh("xyz.dia.com");
    // raa.setErrorReportingHost(erh);

    // FailedAVP fh1;
    // raa.addFailedAVP(fh1);

    // [2.2.9] Populate optional parameter "Redirect-Host".
    // Set the Redirect-Host AVP.
    // The data type of Redirect-Host is DiamURI.
    // The AVP Code of Redirect-Host is 292.
    //URI uri1("SecondaryEventCollectionFunction.com", URI::AAA,
    //        3880, URI::TCP, URI::DIAMETER);
    //RedirectHost rh(uri1);
 
    // Application should not set this AVP.
    // Stack sets this AVP.
    // raa.addRedirectHost(rh);

    // [2.2.10] Populate optional parameter "Redirect-Host-Usage".
    // Set the Redirect-Host-Usage AVP.
    // The data type of Redirect-Host-Usage is Enumerated.
    // This AVP MAY be present in answer messages whose 'E' bit is set and
    // the Result-Code AVP is set to DIAMETER_REDIRECT_INDICATION.
    // The AVP Code of Redirect-Host-Usage is 261.
    // Application should not set this AVP.
    // Stack sets this AVP.
    //RedirectHostUsage rhu(RedirectHostUsage::ALL_SESSION);
    //raa.setRedirectHostUsage(rhu);

    // [2.2.11] Populate optional parameter "Redirect-Max-Cache-Time".
    // Set the Redirect-Max-Cache-Time AVP.
    // The data type of Redirect-Max-Cache-Time is Unsigned32.
    // This AVP MUST be present in answer messages whose 'E' bit is set, the
    // Result-Code AVP is set to DIAMETER_REDIRECT_INDICATION and the
    // Redirect-Host-Usage AVP set to a non-zero value.
    // The AVP Code of Redirect-Max-Cache-Time is 262.
    // Application should not set this AVP.
    // Stack sets this AVP.
    //RedirectMaxCacheTime rmct(500);
    //raa.setRedirectMaxCacheTime(rmct);

    // [2.2.12] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo pi1;

    // [2.2.12.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info 
    // AVP.
    // The AVP Code of Proxy-Info is 280.
    //ProxyHost ph1("india.internal.net");
    //pi1.setProxyHost(ph1);

    // [2.2.12.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as opaque
    //  data
    // The AVP Code of Proxy-State is 33.
    // Stack sets this AVP.
    // Application should not set this AVP
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    // raa.addProxyInfo(pi1);

    // [3] Use appropriate application specific logic to Send object

    int pinfo_count = com_req.countProxyInfo();
    for(int i=0; i<pinfo_count; i++)
    {
        ProxyInfo pinfo;
        ProxyHost phost(com_req.getProxyInfo(i).getProxyHost());
        pinfo.setProxyHost(phost);

        ProxyState pstate(com_req.getProxyInfo(i).getProxyState());
        pinfo.setProxyState(pstate);

        raa.addProxyInfo(pinfo);
    }


    if (appMode == UNIT_TEST)
        cout << raa << endl;

    SendDiaAppMsg(raa, sIdx);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the session termination
 *      request made by the stack. Create the
 *      SessionTerminationAnswer object, populate the AVPs and send 
 *      the message to the stack.
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
int SendSessionTerminationAnswer(const CommandImpl *impl1)
{
    // [1] Create SessionTerminationAnswer object.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    SessionTerminationAnswer sta(false, false);

    SessionTerminationRequest com_req(*impl1);

    const OriginHost& oh1 = com_req.getOriginHost();
    const OriginRealm& or1 = com_req.getOriginRealm();
    const DestinationRealm& dr1 = com_req.getDestinationRealm();

    // [2] Insert data in the created SessionTerminationRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed paramete "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId& sid1 = com_req.getSessionId();
    sta.setSessionId(sid1);

    // [2.2.2] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    ResultCode rc(2001u);
    sta.setResultCode(rc);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost origh(GetOriginHost());
    sta.setOriginHost(origh);

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(dr1.value());
    sta.setOriginRealm(origr);

    // [2.2.5] Populate Optional paramete "User-Name".
    // Set the User-Name AVP.
    // The data type of User-Name is UTF8String.
    // This AVP contains the User-Name.
    // The AVP Code of User-Name is 1.
    UserName un("sip:john.smith@3gppnetwork.com");
    sta.setUserName(un);

    // [2.2.6] Populate optional parameter "Class".
    // Set the Class AVP.
    // The data type of Class is OctetString.
    //This AVP is used to by Diameter servers to return state information to the
    // access device.
    // The AVP Code of Class is 25.
    Class class1("business");
    sta.addClass(class1);

    // [2.2.7] Populate optional parameter "Error-Message".
    // Set the Error-Message AVP.
    // The data type of Error-Message is UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message.
    // The AVP Code of Error-Message is 281.
    // ErrorMessage erm("Server problem");
    // sta.setErrorMessage(erm);

    // [2.2.8] Populate optional parameter "Error-Reporting-Host".
    // Set the Error-Reporting-Host AVP.
    // The data type of Error-Reporting-Host is DiameterIdentity.
    // This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP to a value other than 2001
    // (Success), only if the host setting the Result-Code is different from
    // the one encoded in the Origin-Host AVP.  This AVP is intended to be
    // used for troubleshooting purposes, and MUST be set when the Result-
    // Code AVP indicates a failure.
    // The AVP Code of Error-Reporting-Host is 294.
    // ErrorReportingHost erh("xyz.dia.com");
    // sta.setErrorReportingHost(erh);

    // FailedAVP fh1;
    // sta.addFailedAVP(fh1);

    // [2.2.9] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId origsid(41);
    sta.setOriginStateId(origsid);

    // [2.2.10] Populate optional parameter "Redirect-Host".
    // Set the Redirect-Host AVP.
    // The data type of Redirect-Host is DiamURI.
    // The AVP Code of Redirect-Host is 292.
    // Application should not set this AVP.
    // Stack sets this AVP.
    //URI uri1("SecondaryEventCollectionFunction.com", URI::AAA,
    //        3880, URI::TCP, URI::DIAMETER);
    //RedirectHost rh(uri1);
    //sta.addRedirectHost(rh);

    // [2.2.11] Populate optional parameter "Redirect-Host-Usage".
    // Set the Redirect-Host-Usage AVP.
    // The data type of Redirect-Host-Usage is Enumerated.
    // This AVP MAY be present in answer messages whose 'E' bit is set and
    // the Result-Code AVP is set to DIAMETER_REDIRECT_INDICATION.
    // The AVP Code of Redirect-Host-Usage is 261.
    // Application should not set this AVP.
    // Stack sets this AVP.
    //RedirectHostUsage rhu(RedirectHostUsage::ALL_SESSION);
    // sta.setRedirectHostUsage(rhu);

    // [2.2.12] Populate optional parameter "Redirect-Max-Cache-Time".
    // Set the Redirect-Max-Cache-Time AVP.
    // The data type of Redirect-Max-Cache-Time is Unsigned32.
    // This AVP MUST be present in answer messages whose 'E' bit is set, the
    // Result-Code AVP is set to DIAMETER_REDIRECT_INDICATION and the
    // Redirect-Host-Usage AVP set to a non-zero value.
    // The AVP Code of Redirect-Max-Cache-Time is 262.
    // Application should not set this AVP.
    // Stack sets this AVP.
    //RedirectMaxCacheTime rmct(500);
    //sta.setRedirectMaxCacheTime(rmct);

    // [2.2.13] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo pi1;

    // [2.2.13.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info 
    // AVP.
    // The AVP Code of Proxy-Info is 280.
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.13.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as
    // opaque data
    // The AVP Code of Proxy-State is 33.
    // Stack sets this AVP.
    // Application should not set this AVP
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);
    // sta.addProxyInfo(pi1);

    int pinfo_count = com_req.countProxyInfo();
    for(int i=0; i<pinfo_count; i++)
    {   
        ProxyInfo pinfo;
        ProxyHost phost(com_req.getProxyInfo(i).getProxyHost());
        pinfo.setProxyHost(phost);
        
        ProxyState pstate(com_req.getProxyInfo(i).getProxyState());
        pinfo.setProxyState(pstate);
        
        sta.addProxyInfo(pinfo);
    }


    // [3] Use appropriate application specific logic to Send object

    if (appMode == UNIT_TEST) 
        cout << sta << endl;

    SendDiaAppMsg(sta, sIdx);

    return (ITS_SUCCESS);
}


