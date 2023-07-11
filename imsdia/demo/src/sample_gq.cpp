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
 * LOG: $Log: sample_gq.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:24  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.21  2006/06/30 14:20:03  nvijikumar
 * LOG: Small changes for menu exit function.
 * LOG:
 * LOG: Revision 1.20  2006/06/30 10:28:13  nvijikumar
 * LOG: Changes for Exit function.
 * LOG:
 * LOG: Revision 1.19  2006/06/07 11:07:54  tpanda
 * LOG: Handling of error responses
 * LOG:
 * LOG: Revision 1.18  2006/06/02 11:52:44  tpanda
 * LOG: STR/ASR session issue fix
 * LOG:
 * LOG: Revision 1.17  2006/06/02 09:21:34  yranade
 * LOG: Minor update
 * LOG:
 * LOG: Revision 1.16  2006/05/26 14:10:59  yranade
 * LOG: Support for CC Compiler.
 * LOG:
 * LOG: Revision 1.15  2006/05/24 04:50:52  nvijikumar
 * LOG: defines for Commandcodes and correcting the code comments.
 * LOG:
 * LOG: Revision 1.14  2006/05/08 16:46:07  yranade
 * LOG: Minor updates to menu.
 * LOG:
 * LOG: Revision 1.13  2006/05/08 10:04:16  nvijikumar
 * LOG: Changes according to Tushar's input(Proxy,RouteRcord,Originstate,..etc).
 * LOG:
 * LOG: Revision 1.12  2006/04/25 15:31:37  nvijikumar
 * LOG: Code Enhancements, Documentation.
 * LOG:
 * LOG: 
 *
 * ID: $Id: sample_gq.cpp,v 3.1 2008/03/31 10:33:24 nvijikumar Exp $
 ****************************************************************************/
#include <dia_defines.h>
#include <dia_frame.h>
#include <app_trace.h>

#include <diameter/gqgqprime/AA.h>
#include <diameter/gqgqprime/AS.h>
#include <diameter/gqgqprime/RA.h>
#include <diameter/gqgqprime/ST.h>

#include <app.h>
#include <app_defines.h>
#include <app_stats.h>

using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::gqgqprime;

// Function prototype to handle GqGq prime Messages
int HandleGqDiaMessage(its::ITS_Event& ev);

/*  implementation: public
 ****************************************************************************
 *  Purpose: Thread Function that handles messages received from the
 *      stack with AppId = 16777222
 *
 *  Input Parameters:
 *      ThreadPoolThread* thr: ThreadPoolThread
 *      void* arg: Arguments(if any)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern "C"
void GqThreadFunc(ThreadPoolThread* thr, void* arg)
{
    int ret;
    engine::Worker* work = (engine::Worker *)thr;

    ITS_HANDLE handle = NULL;

    ITS_USHORT inst = work->GetInstance();
    Event evt;

    while (!work->GetExit())
    {
        /*
         * Wait For Event from the event queue.
         * GetNextEvent is a BlockingCall that returns
         * when an Event is posted onto the associated worker
         * taskqueue
         */
        if (work->GetNextEvent(evt) == ITS_SUCCESS)
        {
            APP_TRACE_DEBUG(("Charging:Received an event on Instance %d",
                             inst));
            // If the event source is from the diameter stack,
            // handle that event. 
            switch (evt.GetSource())
            {
            case ITS_DIA_SRC:
                 APP_TRACE_DEBUG(("Received Event from ITS Diameter Stack "));
                 HandleGqDiaMessage(evt);
                 break;
            default:
                 APP_TRACE_ERROR(("Unknown Event Received"));
                 break;
            }
        }
    }
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function processes the message received from the
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
int HandleGqDiaMessage(ITS_Event& ev)
{
    /*
     * Access the diameter stack HANDLE
     * via the DiaFrame Singleton Object Pointer
     */
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
                                                                                
    if (diaFrame)
    {
        DiaMsg *dMsg;

        // Read the message in the event received
        if (diaFrame->Receive(ev, &dMsg) != ITS_SUCCESS)
        {
           APP_TRACE_ERROR(("Failed to Receive Diameter Message"));
           return -1;
        }

        // If the message is the indication from the stack, 
        // Handle the Indication. In this case, we simply update
        // the indication statistics.
        if (dMsg->IsIndication())
        {
            APP_TRACE_DEBUG(("Received Indication from Stack %d\n",
                            dMsg->GetIndication()));

            APP_TRACE_DEBUG(("Received Indication for AppId %d\n",
                            dMsg->GetApplicationId()));

            APPStats::GetAPPStats()->UpdateRecvIndications(
                                     dMsg->GetIndication());
        }
        // If not an indication, then it is a Command Message
        else
        {
            APP_TRACE_DEBUG(("dMsg->GetAppId = %d",
                dMsg->GetApplicationId()));

            APP_TRACE_DEBUG(("dMsg->GetSessionIndex = %d",
                dMsg->GetSessionIndex()));

            // Get the command instance from the message.
            const diameter::CommandImpl* impl = dMsg->GetCommandImpl();

            ITS_BOOLEAN isReq = impl->isRequest() ? ITS_TRUE:ITS_FALSE;

            // Update the receive statistics
            APPStats::GetAPPStats()->UpdateRecvStats(impl->getCommandCode(),
                                                           isReq);

            try
            {
                // Process the commands based on the command code.
                if(impl->isError())
                {
                   HandleErrorResponse(impl);
                }
                else
                {
                   switch (impl->getCommandCode())
                   {
                      case GQGQ_AA_MSG_CMD_CODE:
                           if(impl->isRequest())
                           {
                              AARequest aareq(*impl);
                              cout << "AARequest " << aareq << endl;
                              SendAAAnswer(impl);
                           }
                           else
                           {
                              AAAnswer aaans(*impl);
                              cout << "AAAnswer " << aaans << endl;
                           }
                           break;

                       case GQGQ_RA_MSG_CMD_CODE:
                           if(impl->isRequest())
                           {
                               RARequest rareq(*impl);
                               cout << "RARequest" << rareq << endl;
                               SendRAAnswer(impl);
                           }
                           else
                           {
                               RAAnswer raans(*impl);
                               cout << "RAAnswer" << raans << endl;
                           }
                           break;

                       case GQGQ_STR_MSG_CMD_CODE:
                           if(impl->isRequest())
                            {
                               STRequest streq(*impl);
                               cout << "STRequest" << streq << endl;

                        // SendSTAnswer(impl);
                            }
                            else
                            {
                               STAnswer stans(*impl);
                               cout << "STAnswer" << stans << endl;
                            }
                            break;

                        case GQGQ_AS_MSG_CMD_CODE:
                            if(impl->isRequest())
                            {
                               ASRequest asreq(*impl);
                               cout << "ASRequest" << asreq << endl;
                            }
                            else
                            {
                               ASAnswer asans(*impl);
                               cout << "ASAnswer" << asans << endl;
                            }
                            break;
                        default:
                           break;
                       }
                  }
            }
            catch (NoSuchAttributeException e)
            {
                APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                                 e.name(), e.what()));
            }
            catch (WrongCommandTypeException e)
            {
                APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                                 e.name(), e.what()));
            }
            catch (UnknownTypeException e)
            {
                APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                                 e.name(), e.what()));
            }
            catch (CodecException e)
            {
                APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                                 e.name(), e.what()));
            }
            catch (...)
            {
                APP_TRACE_ERROR(("Unknown Exception Caught"));
            }

        }
        if (dMsg)
            delete dMsg;
    }
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function displays the menu options for the
 *      Gqgq prime protocol interface.
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

                                                                                
int DisplayGqMenu()
{
    string input;
    int ret = 0;
    do
    {
        cout <<  endl << "Enter choice no for the given following GQGQ"
                      <<" messages"<<endl<<endl;
        cout << endl <<"(1) . AA Req Command"<<endl;
        cout << endl <<"(2) . RA Req Command"<<endl;
        cout << endl <<"(3) . ST Req Command"<<endl;
        cout << endl <<"(4) . AS Req Command"<<endl;
        cout << endl <<"(99) . Quit "<<endl;
                                                                                
        cin >> input;

        ret = atoi(input.c_str());

    } while ((ret < 1 || ret > 4) && ret!=99);

    return ret;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the request to the diameter
 *      stack based on the option selected in the menu.
 *
 *  Input Parameters:
 *      int input: User choice to send Request Message.
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
int SendGqMessage(int input)
{
    switch(input)
    {
        case 1:
            SendAARequest();
            break;
        case 2:
            SendRARequest();
            break;
        case 3:
            SendSTRequest();
            break;
        case 4:
            SendASRequest();
            break;
        case 99:
            {
                DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
                if (diaFrame)
                {
                    diaFrame->Terminate();
                }
                exit(EXIT_SUCCESS);
            }
        default:
            cout<<endl<<"please enter the correct choice";
            break;
    }
    return 0;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the AA request to the
 *      diameter stack. Creates the Accounting Request object,
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
int SendAARequest() 
{
    // [1]. Create an instance of AARequest class
    // The AA-Request command is sent by a Diameter
    // client to a Diameter Server in order to request deregistration
    // Command-Code = 265 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    AARequest request(false,false);

    // [2.1.1.1] Fixed AVP.
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    string sessIdString;
    ITS_UINT sIdx;
    if (diaFrame->AllocateSessionIndex(GQGQ_INTERFACE_APP_ID,
                                       sIdx, sessIdString)
                                       == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("Successful Session Allocation"));
        APP_TRACE_DEBUG(("SessionIdx = %d, SessionId = %s", sIdx,
                         sessIdString.c_str()));
    }
    else
    {
        APP_TRACE_ERROR(("Failure in Session Allocation"));
        return (ITS_ESENDFAIL);
    }

    // Fixed AVP 

    request.setSessionId(SessionId(sessIdString));

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authid(GQGQ_INTERFACE_APP_ID);
    request.setAuthApplicationId(authid);
    
    // [2.1.2.2] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(GetOriginHost());
    request.setOriginHost(origh);

    // [2.1.2.3] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(GetOriginRealm());
    request.setOriginRealm(origr);

    // [2.1.2.4] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm desr(GetDestinationRealm());
    request.setDestinationRealm(desr);

    // [2.2.x] Optional AVPS
    
    // [2.2.1.1] The Media-Component-Description AVP (AVP code 517) 
    // is of type Grouped, and it contains service information 
    // for a  single media component within an AF session. 
    // It may be based on the SDI exchanged between the AF and the AF client
    MediaComponentDescription m1;

    // [2.2.1.2] The Media-Component-Number AVP (AVP code 518) is of 
    // type Unsigned32, and it contains the ordinal number of 
    // the media component, assigned 
    MediaComponentNumber mcn(10);
    m1.setMediaComponentNumber(mcn);

    // [2.2.1.3] The Media-Sub-Component AVP (AVP code 519) 
    // is of type Grouped, and it contains the requested QoS 
    // and filters for the set of IP flows identified by their i
    // common Flow-Identifier. 
    MediaSubComponent ms1;

    // [2.2.1.4] The Flow-Number AVP (AVP code 509) is of type Unsigned32, 
    // and it contains the ordinal number of the IP flow(s),
    FlowNumber fn(10);
    ms1.setFlowNumber(fn);
  
    m1.addMediaSubComponent(ms1);
   
    // [2.2.1] set MediaComponentDescription to AA Request
    request.addMediaComponentDescription(m1);

    // [2.2.2.1] The Flows AVP (AVP code 510) is of type Grouped, 
    // and it indicates IP flows via their flow identifiers
    Flows f1;

    // [2.2.2.2] The Flow-Number AVP (AVP code 509) is of type Unsigned32,
    // and it contains the ordinal number of the IP flow(s),
    FlowNumber fn2(10);
    f1.addFlowNumber(fn2);

    //  [2.2.2.3] The Media-Component-Number AVP (AVP code 518) is of
    // type Unsigned32, and it contains the ordinal number of
    // the media component, assigned
    MediaComponentNumber mcn2(10);
    f1.setMediaComponentNumber(mcn2);

    // [2.2.2.4] The Flow-Grouping AVP (AVP code 508) is of type Grouped, 
    // and it indicates that no other IP Flows shall be transported together 
    // with the listed IP Flows in the same PDP context(s).
    FlowGrouping F1;
    F1.addFlows(f1);

    // [2.2.2] set FlowGrouping to AA Request object
    request.addFlowGrouping(F1);

    // [2.2.3.1] The AF-Charging-Identifier AVP (AVP code 505)
    //  is of type OctetString, contains the AF Charging Identifier 
    // that is sent by the AF.
    AFChargingIdentifier afcid("INT100");
    request.setAFChargingIdentifier(afcid);

    // [2.2.3.2] The SIP_Forking AVP (AVP code 523) is of type Enumerated, 
    // and describes if several SIP dialogues are related to one
    // SINGLE_DIALOGUE (default)
    // SEVERAL_DIALOGUES
    SIPForkingIndication sipin(SIPForkingIndication::SINGLE_DIALOGUE);
    request.setSIPForkingIndication(sipin);

    // [2.2.3] The Specific-Action AVP (AVP code 513) is of type Enumerated.
    // The following values are defined for this AVP
    // SERVICE_INFORMATION_REQUEST
    // CHARGING_CORRELATION_EXCHANGE
    // INDICATION_OF_LOSS_OF_BEARER
    // INDICATION_OF_RECOVERY_OF_BEARER
    // INDICATION_OF_RELEASE_OF_BEARER
    // INDICATION_OF_ESTABLISHMENT_OF_BEARER
    SpecificAction sp1(SpecificAction::INDICATION_OF_RELEASE_OF_BEARER);
    request.addSpecificAction(sp1);

    // [2.2.4] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName un("sip:Smith@3gppnetwork.com");
    request.setUserName(un);

    // [2.2.5.1] The V4-Transport-Address AVP (AVP code 454) 
    // is of type Grouped and contains a single IPv4 address and 
    // a single port number.
    V4TransportAddress addv4;

    // [2.2.5.2] The Framed-IP-Address AVP (AVP Code 8) [RADIUS] 
    // is of type OctetString and contains an IPv4 address
    FramedIPAddress faddr("10.1.1.1");
    addv4.setFramedIPAddress(faddr);

    // [2.2.5.3] The Port-Number AVP (AVP code 455) is of type 
    // Unsigned32 and contains the end point port number.
    PortNumber pno(1811);
    addv4.setPortNumber(pno);

    // [2.2.5.4] The V6-Transport-Address AVP (AVP code 453) 
    // is of type Grouped and contains a single IPv6 address 
    // and a single port number.
    V6TransportAddress addv6;


    // [2.2.5.4] The Framed-IPv6-Prefix AVP (AVP Code 97) is 
    // of type OctetString and contains the IPv6 prefix to be 
    // configured for the user
    FramedIPv6Prefix fpre("10.1.1.2");
    addv6.setFramedIPv6Prefix(fpre);

    // [2.2.5.5] The Port-Number AVP (AVP code 455) is of type 
    // Unsigned32 and contains the end point port number.
    PortNumber pno1(1812);
    addv6.setPortNumber(pno1);

    // [2.2.5.6] The Binding-Input-List AVP (AVP code 451) is 
    // of type Grouped and contains a list transport addresses 
    // for which a binding is requested.
    BindingInputList bil;
    bil.addV4TransportAddress(addv4);
    bil.addV6TransportAddress(addv6);

    // [2.2.5.7] The Binding-Information AVP (AVP code 450) is 
    // of type Grouped and is sent between the AF and the SPDF
    BindingInformation b1;
    b1.setBindingInputList(bil);

    // [2.2.5] set BindingInformation to AA Request object
    request.setBindingInformation(b1); 

    // [2.2.6] Reservation-Priority AVP (AVP code 458) is of type Enumerated. 
    // The following values are specified:
    // PRIORITY-ONE
    // PRIORITY-TWO
    // PRIORITY-THREE
    // PRIORITY-FOUR
    // PRIORITY-FIVE
    // PRIORITY-SIX
    // PRIORITY-SEVEN
    ReservationPriority rprty(ReservationPriority::PRIORITY_ONE);
    request.setReservationPriority(rprty);

    // [2.2.7.1] The Globally-Unique-Address AVP (AVP code 300) 
    // is of type Grouped
    GloballyUniqueAddress gua;

    // [2.2.7.2] The Framed-IP-Address AVP (AVP Code 8) [RADIUS] 
    // is of type OctetString and contains an IPv4 address
    FramedIPAddress fip("11.1.2.1");
    gua.setFramedIPAddress(fip);

    // [2.2.7.3] The Framed-IPv6-Prefix AVP (AVP Code 97) is 
    // of type OctetString and contains the IPv6 prefix
    FramedIPv6Prefix fpre1("x.y");
    gua.setFramedIPv6Prefix(fpre1);

    // [2.2.7.4] The Address-Realm AVP (AVP code 301) is of 
    // type Octet String
    AddressRealm addrr("dia.net");
    gua.setAddressRealm(addrr);

    // [2.2.7] set GloballyUniqueAddress to the AA Request Object
    request.setGloballyUniqueAddress(gua);

    // [2.2.8] The Authorization-Lifetime AVP (AVP Code 291) 
    // is of type Unsigned32
    AuthorizationLifetime authlt(24);
    request.setAuthorizationLifetime(authlt);

    // [2.2.9.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //diameter::base::ProxyInfo pi1;

    // [2.2.9.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.9.2] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    // [2.2.9] set the ProxyInfo AVP
    // Application should not set this AVP.
    // request.addProxyInfo(pi1);

    // [2.2.10] Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord rrec("nemo");
    // Application should not set this AVP.
    // request.addRouteRecord(rrec);

    cout<<request;

    SendToStack(&request);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the AA Answer to the
 *      diameter stack. Creates the AA Answer object,
 *      populate the AVPs and send the message to the stack.
 *
 *  Input Parameters:
 *      const diameter::CommandImpl *impl: Pointer to the received Request
 *      Command, for which the Answer is to be sent.
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
int SendAAAnswer(const CommandImpl *impl) 
{
    //[ 1] Create an instance of AAAnswer class
    // The AA-Answer command is sent by a Diameter
    // server to a Diameter client in order to request deregistration
    // Command-Code = 265 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::AAAnswer answer;

    // Create an instance of AARequest class 
    AARequest aar1(*impl);

    // Get the some AVP values and set them to Answer Message
    const SessionId& sid = aar1.getSessionId();
    const OriginHost& oh = aar1.getOriginHost();
    const OriginRealm& or1 = aar1.getOriginRealm();
    const DestinationRealm& dr = aar1.getDestinationRealm();
    const AuthApplicationId& aaid1 = aar1.getAuthApplicationId();
   
    // Fixed AVP

    // [2] Insert data in the created AAAnswer object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed paramete "Session-Id".
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    answer.setSessionId(sid);

    // Required AVPs

    // [2.1.2] Populate required Manatories.
    // [2.1.2.1] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    answer.setAuthApplicationId(aaid1);

    // [2.1.2.2] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(GetOriginHost());
    answer.setOriginHost(origh);


    // [2.1.2.3] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(dr.value());
    answer.setOriginRealm(origr);

    // Optional AVPS

    // [2.2] Populate Optionals
    // [2.2.1] Set the Result-Code AVP .
    // The Result-Code AVP indicates whether a particular request
    // was completed successfully or whether an error occurred
    // All Diameter answer messages must contain one Result-Code AVP
    // Diameter provides the following classes of error which
    // is represented by the Result-Code AVP:
    // 1xxx - Informational
    // 2xxx - Success
    // 3xxx - Protocol Errors
    // 4xxx - Transient Failures
    // 5xxx - Permanent Failure
    // The AVP Code of AVP is 268.
    // The data type of AVP is Unsigned32.
    ResultCode rc(2001u);
    answer.setResultCode(rc);

    // [2.2.2.1] Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // ResultCode AVP is already been set, we dont need to set this.
    //ExperimentalResult er1;

    // [2.2.2.2] Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vid(VENDOR_ID);
    //er1.setVendorId(vid);

    // [2.2.2.3] Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode erc(100);
    //er1.setExperimentalResultCode(erc);

    // [2.2.2]Set the ExperimentalResult AVP
    // answer.setExperimentalResult(er1);
   
    // [2.2.3.1] The V4-Transport-Address AVP (AVP code 454) 
    // is of type Grouped and contains a single IPv4 address 
    // and a single port number.
    V4TransportAddress addv4;

    // [2.2.3.2] The Framed-IP-Address AVP (AVP Code 8) [RADIUS] 
    // is of type OctetString and contains an IPv4 address
    FramedIPAddress fip1("10.1.1.1");
    addv4.setFramedIPAddress(fip1);

    // [2.2.3.3] The Port-Number AVP (AVP code 455) is of 
    // type Unsigned32 and contains the end point port number.
    PortNumber pn1(1811);
    addv4.setPortNumber(pn1);

    // [2.2.3.4] The V6-Transport-Address AVP (AVP code 453) 
    // is of type Grouped and contains a single IPv6 address 
    // and a single port number.
    V6TransportAddress addv6;

    // [2.2.3.5] The Framed-IPv6-Prefix AVP (AVP Code 97) 
    // is of type OctetString and contains the IPv6 prefix 
    // to be configured for the user
    FramedIPv6Prefix fpre("10.1.1.2");
    addv6.setFramedIPv6Prefix(fpre);

    // [2.2.3.6] The Port-Number AVP (AVP code 455) is of 
    // type Unsigned32 and contains the end point port number.
    PortNumber pno1(1824);
    addv6.setPortNumber(pno1);

    // [2.2.3.7] The Binding-Input-List AVP (AVP code 451) 
    // is of type Grouped and contains a list transport 
    // addresses for which a binding is requested.
    BindingInputList bil;
    bil.addV4TransportAddress(addv4);
    bil.addV6TransportAddress(addv6);

    // [2.2.3.8] The Binding-Information AVP (AVP code 450) is 
    // of type Grouped and is sent between the AF and the SPDF
    BindingInformation b1;
    b1.setBindingInputList(bil);

    // [2.2.3 ] set the BindingInformation AVP
    answer.setBindingInformation(b1); 

    // [2.2.4] Reservation-Priority AVP (AVP code 458) is of type Enumerated.
    // The following values are specified:
    // PRIORITY-ONE
    // PRIORITY-TWO
    // PRIORITY-THREE
    // PRIORITY-FOUR
    // PRIORITY-FIVE
    // PRIORITY-SIX
    // PRIORITY-SEVEN
    ReservationPriority v1(ReservationPriority::PRIORITY_ONE);
    answer.setReservationPriority(v1);

    // [2.2.5] The Authorization-Token AVP (AVP code 506) is of type 
    // OctetString, and contains the Authorization Token
    AuthorizationToken atoken("ABC");
    answer.setAuthorizationToken(atoken);

    // [2.2.6.1] The Access-Network-Charging-Identifier AVP 
    // (AVP code 502) is of type Grouped, and contains a 
    // charging identifier
    AccessNetworkChargingIdentifier ac1;

    //[2.2.6.2]The Access-Network-Charging-Identifier-Value 
    // AVP (AVP code 503) is of type OctetString, and contains 
    // a charging identifier
    AccessNetworkChargingIdentifierValue aciv("ABC");
    ac1.setAccessNetworkChargingIdentifierValue(aciv);

    // [2.2.6] set the AccessNetworkChargingIdentifier 
    // AVP to AAAnswer Message
    answer.addAccessNetworkChargingIdentifier(ac1);

    // [2.2.7.1] Address AVP for each potential IP address 
    // that MAY be locally used when transmitting Diameter messages.
    Address f1(Address::IPV4,"11.1.1.1");

    // [2.2.7] The Access-Network-Charging-Address AVP 
    // (AVP code 501) is of type Address, and it indicates 
    // the IP Address of the network entity within the access 
    // network performing charging
    AccessNetworkChargingAddress anc(f1);
    answer.setAccessNetworkChargingAddress(anc);


    // [2.2.8] The Error-Message AVP (AVP Code 281) is of type UTF8String.  
    // It MAY accompany a Result-Code AVP as a human readable error message
    // ErrorMessage err("Authentication error");
    // answer.setErrorMessage(err);

    // [2.2.9] The Error-Reporting-Host AVP (AVP Code 294) is of type
    // DiameterIdentity.  This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP
    // ErrorReportingHost errh("dia.xyz.com");
    // answer.setErrorReportingHost(errh);

    // [2.2.10] The Authorization-Lifetime AVP (AVP Code 291) 
    // is of type Unsigned32
    AuthorizationLifetime alt1(24);
    answer.setAuthorizationLifetime(alt1);

    // [2.2.11] The Auth-Grace-Period AVP (AVP Code 276) 
    // is of type Unsigned32 and contains the number of 
    // seconds the Diameter server to wait
    AuthGracePeriod authp(10);
    answer.setAuthGracePeriod(authp);

    // [2.2.12.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    // diameter::base::ProxyInfo pi2;

    // [2.2.12.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy2.abc.com");
    //pi2.setProxyHost(ph1);

    // [2.2.12.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi2.setProxyState(ps1);

    // [2.2.12] Set the ProxyInfo AVP to AAAnswer Message
    // Application should not set this AVP.
    // answer.addProxyInfo(pi2);

    cout<<answer;

    // Send AA Answer Message to stack
    SendToStack(&answer);

    return (ITS_SUCCESS);

}


/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the RA request to the
 *      diameter stack. Creates the RA Request object,
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
int SendRARequest() 
{
    // [1] Create an instance of AARequest class
    // The RA-Request command is sent by a Diameter
    // client to a Diameter Server in order to request deregistration
    // Command-Code = 258
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::RARequest request;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    string sessIdString;
    ITS_UINT sIdx;
    if (diaFrame->AllocateSessionIndex(GQGQ_INTERFACE_APP_ID,
                                       sIdx, sessIdString)
                                       == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("Successful Session Allocation"));
        APP_TRACE_DEBUG(("SessionIdx = %d, SessionId = %s", sIdx,
                         sessIdString.c_str()));
    }
    else
    {
        APP_TRACE_ERROR(("Failure in Session Allocation"));
        return (ITS_ESENDFAIL);
    }

    // Fixed AVP 

    request.setSessionId(SessionId(sessIdString));

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter  messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(GetOriginHost());
    request.setOriginHost(origh);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(GetOriginRealm());
    request.setOriginRealm(origr);

    // [2.1.2.3] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm desr(GetDestinationRealm());
    request.setDestinationRealm(desr);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost desh(GetDestinationHost());
    request.setDestinationHost(desh);

    // [2.1.2.5] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authid(GQGQ_INTERFACE_APP_ID);
    request.setAuthApplicationId(authid);

    // The Specific-Action AVP (AVP code 513) is of type Enumerated.
    // The following values are defined for this AVP
    // SERVICE_INFORMATION_REQUEST
    // CHARGING_CORRELATION_EXCHANGE
    // INDICATION_OF_LOSS_OF_BEARER
    // INDICATION_OF_RECOVERY_OF_BEARER
    // INDICATION_OF_RELEASE_OF_BEARER
    // INDICATION_OF_ESTABLISHMENT_OF_BEARER
    SpecificAction sp1(SpecificAction::INDICATION_OF_RELEASE_OF_BEARER);
    request.addSpecificAction(sp1);

    // [2.2.x] Optional AVPs

    // [2.2.1.1] The Access-Network-Charging-Identifier AVP 
    // (AVP code 502) is of type Grouped, and contains a 
    // charging identifier
    AccessNetworkChargingIdentifier ac1;

    // [2.2.1.2] The Access-Network-Charging-Identifier-Value 
    // AVP (AVP code 503) is of type OctetString, and contains 
    // a charging identifier
    AccessNetworkChargingIdentifierValue anciv("ABC");
    ac1.setAccessNetworkChargingIdentifierValue(anciv);

    // [2.2.1] set the AccessNetworkChargingIdentifier AVP 
    // to RA Request Message
    request.addAccessNetworkChargingIdentifier(ac1);

    // [2.2.2.1] Address AVP for each potential IP address that 
    // MAY be locally used when transmitting Diameter messages.
    Address f1(Address::IPV4,"11.1.1.2");

    // [2.2.2] The Access-Network-Charging-Address AVP (AVP code 501) is of
    // type Address, and it indicates the IP Address of the network
    // entity within the access network performing charging
    AccessNetworkChargingAddress anc(f1);
    request.setAccessNetworkChargingAddress(anc);

    // [2.2.3.1] The Flows AVP (AVP code 510) is of type Grouped, 
    // and it indicates IP flows via their flow identifiers
    Flows ff1;

    // [2.2.3.2] The Flow-Number AVP (AVP code 509) is of type Unsigned32,
    // and it contains the ordinal number of the IP flow(s),
    FlowNumber fn(10);
    ff1.addFlowNumber(fn);

    //  [2.2.3.3] The Media-Component-Number AVP (AVP code 518) is of
    // type Unsigned32, and it contains the ordinal number of
    // the media component, assigned
    MediaComponentNumber mcn(10);
    ff1.setMediaComponentNumber(mcn);

    // [2.2.3] Set the Flows AVP to RA Request Message
    request.addFlows(ff1);

    // [2.2.4] The Session-Abort-Cause AVP (AVP code 500) is of type 
    // Enumerated, and determines the cause of a session abort request.
    //  The following values are defined:
    // BEARER_RELEASED
    // INSUFFICIENT_SERVER_RESOURCES
    // INSUFFICIENT_BEARER_RESOURCES
    AbortCause v1(AbortCause::INSUFFICIENT_SERVER_RESOURCES);
    request.setAbortCause(v1);

    // [2.2.5] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId osid(40);
    request.setOriginStateId(osid);

    // [2.2.6.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //diameter::base::ProxyInfo pi1;

    // [2.2.6.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.6.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    // [2.2.6] set the ProxyInfo AVP to RA Request
    // Application should not set this AVP.
    // request.addProxyInfo(pi1);

    // [2.2.7] Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord rrec("nemo");
    // Application should not set this AVP.
    // request.addRouteRecord(rrec);

    cout<<request;
   
    // Send RA Request Message to Diameter stack 
    SendToStack(&request);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the RA Answer to the
 *      diameter stack. Creates the RA Answer object,
 *      populate the AVPs and send the message to the stack.
 *
 *  Input Parameters:
 *      const diameter::CommandImpl *impl: Pointer to the received Request
 *      Command, for which the Answer is to be sent.
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
int SendRAAnswer(const CommandImpl *impl) 
{
    // [1]. Create an instance of  RA Answer class
    // The RA-Answer command is sent by a Diameter
    // server to a Diameter client in order to request deregistration
    // Command-Code = 258 
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::RAAnswer answer;

    // Create an instance of  RA Request class 
    RARequest rar(*impl);

    // Get AVP values from Request and set them to Answer Message
    const SessionId& sid = rar.getSessionId();
    const OriginHost& oh = rar.getOriginHost();
    const OriginRealm& or1 = rar.getOriginRealm();
    const DestinationHost& dh = rar.getDestinationHost();
    const DestinationRealm& dr = rar.getDestinationRealm();
    const AuthApplicationId& aaid1 = rar.getAuthApplicationId();
    const OriginStateId& osid = rar.getOriginStateId();

    // [2.1.1.x] Fixed AVP

    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    answer.setSessionId(sid);

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(dh.value());
    answer.setOriginHost(origh);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(dr.value());
    answer.setOriginRealm(origr);

    // [2.2.x] Optional AVPs

    // [2.2.1] Set the Result-Code AVP .
    // The Result-Code AVP indicates whether a particular request
    // was completed successfully or whether an error occurred
    // All Diameter answer messages must contain one Result-Code AVP
    // Diameter provides the following classes of error which
    // is represented by the Result-Code AVP:
    // 1xxx - Informational
    // 2xxx - Success
    // 3xxx - Protocol Errors
    // 4xxx - Transient Failures
    // 5xxx - Permanent Failure
    // The AVP Code of AVP is 268.
    // The data type of AVP is Unsigned32.
    ResultCode rc(2001u);
    answer.setResultCode(rc);

    // [2.2.2.1] Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // ResultCode AVP is already been set.
    //ExperimentalResult er1;

    // [2.2.2.2] Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vid(VENDOR_ID);
    //er1.setVendorId(vid);

    // [2.2.2.3] Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode erc(2001);
    //er1.setExperimentalResultCode(erc);

    // [2.2.2] set ExperimentalResult AVP 
    // answer.setExperimentalResult(er1);

    // [2.2.3.1] The Media-Component-Description AVP (AVP code 517)
    // is of type Grouped, and it contains service information
    // for a  single media component within an AF session.
    // It may be based on the SDI exchanged between the AF and the AF client
    diameter::gqgqprime::MediaComponentDescription m1;

    // [2.2.3.2] The Media-Component-Number AVP (AVP code 518) is of
    // type Unsigned32, and it contains the ordinal number of
    // the media component, assigned
    MediaComponentNumber mcn(10);
    m1.setMediaComponentNumber(mcn);

    // [2.2.3.3] The Media-Sub-Component AVP (AVP code 519) is 
    // of type Grouped, and it contains the requested QoS and 
    // filters for the set of IP
    // flows identified by their common Flow-Identifier.
    MediaSubComponent ms1;

    // [2.2.3.4]The Flow-Number AVP (AVP code 509) is of type Unsigned32,
    // and it contains the ordinal number of the IP flow(s)
    FlowNumber fn(10);
    ms1.setFlowNumber(fn);
    m1.addMediaSubComponent(ms1);

    // [2.2.3] set MediaComponentDescription to AA Request
    answer.addMediaComponentDescription(m1);

    // [2.2.4.1]The Flows AVP (AVP code 510) is of type Grouped, 
    // and it indicates IP flows via their flow identifiers
    Flows f1;

    // [2.2.4.2] The Flow-Number AVP (AVP code 509) is of type 
    // Unsigned32, and it contains the ordinal number of the IP flow(s)
    FlowNumber fn2(10);
    f1.addFlowNumber(fn2);    

    // [2.2.4.3] The Media-Component-Number AVP (AVP code 518) is of
    // type Unsigned32, and it contains the ordinal number of
    // the media component, assigned
    MediaComponentNumber mcn1(10);
    f1.setMediaComponentNumber(mcn1);

    //  [2.2.4.4] The Flow-Grouping AVP (AVP code 508) is of 
    // type Grouped, and it indicates that no other IP Flows 
    // shall be transported together with the listed IP Flows 
    // in the same PDP context(s).
    FlowGrouping F1;
    F1.addFlows(f1);

    // [2.2.4] set the FlowGrouping AVP 
    answer.addFlowGrouping(F1);

    // [2.2.5] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    answer.setOriginStateId(osid);

    // [2.2.6] The Error-Message AVP (AVP Code 281) is of type UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message
    // ErrorMessage erm("server problem");
    // answer.setErrorMessage(erm);

    // [2.2.7] The Error-Reporting-Host AVP (AVP Code 294) is of type
    // DiameterIdentity.  This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP
    // ErrorReportingHost erh("abc.def.com");
    // answer.setErrorReportingHost(erh);

    // [2.2.8] Set Failed AVP
    // FailedAVP fa;
    // answer.addFailedAVP(fa);


    // [2.2.9.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //diameter::base::ProxyInfo pi2;

    // [2.2.9.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy1.abc.com");
    //pi2.setProxyHost(ph1);

    // [2.2.9.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi2.setProxyState(ps1);

    // [2.2.9] set the ProxyInfo AVP
    // Application should not set this AVP.
    // answer.addProxyInfo(pi2);

    cout<<answer;
 
    // Send RA Answer Message to Diameter stack
    SendToStack(&answer);

    return (ITS_SUCCESS);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Session termination request to the
 *      diameter stack. Creates the SessionTerminationRequest
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
int SendSTRequest() 
{
    // [1]. Create an instance of STRequest class
    // The ST-Request command is sent by a Diameter
    // client to a Diameter Server in order to request deregistration
    // Command-Code = 275 with 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::STRequest request(false,false);

    
    // [2.1.1.x] Fixed AVP 

    // [2.1.1.1] The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    // Provide Session Id to terminate
    cout<<"Please enter the Session ID to Terminate"<<endl;
    string sessIdString;
    cin>>sessIdString;
    request.setSessionId(SessionId(sessIdString));

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(GetOriginHost());
    request.setOriginHost(origh);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(GetOriginRealm());
    request.setOriginRealm(origr);

    // [2.1.2.3] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm desr(GetDestinationRealm());
    request.setDestinationRealm(desr);

    // [2.1.2.4] Populate required parameter "Termination-Cause".
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
    request.setTerminationCause(termc);

    // [2.1.2.5] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authid(GQGQ_INTERFACE_APP_ID);
    request.setAuthApplicationId(authid);

    // [2.2.x] Optional AVPs

    // [2.2.1] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost desh(GetDestinationHost());
    request.setDestinationHost(desh);

    // [2.2.2] The Class AVP (AVP Code 25) is of type OctetString and is used 
    // to be Diameter servers to return state information to the access device.
    Class class1("Business");
    request.addClass(class1);

    // [2.2.3] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId origsid(41);
    request.setOriginStateId(origsid);

    // [2.2.4] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //diameter::base::ProxyInfo pi1;

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
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    // [2.2.5] set the ProxyInfo AVP 
    // request.addProxyInfo(pi1);

    // [2.2.6] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the message.
    // The AVP Code of Route-Record is 282.
    //RouteRecord rrec("nemo");
    // Application should not set this AVP.
    // request.addRouteRecord(rrec);

    cout<<request;

    // Send STRequest Message to Diameter stack 
    SendToStack(&request);

    return (ITS_SUCCESS);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the session termination
 *      request made by the stack. Creates the SessionTerminationAnswer 
 *      object, populate the AVPs and send the message to the stack.
 *
 *  Input Parameters:
 *      const diameter::CommandImpl *impl: Pointer to the received Request
 *      Command, for which the Answer is to be sent.
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
int SendSTAnswer(const CommandImpl* impl) 
{
    // [1]. Create an instance of STAnswer class
    // The ST Answer command is sent by a Diameter
    // client to a Diameter Server in order to request deregistration
    // Command-Code = 275
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::STAnswer answer;

    // Create an instance of STRequest class
    STRequest str1(*impl);

    // Get the AVP values from Request and set them to Answer
    const SessionId& sid = str1.getSessionId();
    const OriginHost& oh = str1.getOriginHost();
    const OriginRealm& or1 = str1.getOriginRealm();
    const DestinationHost& dh = str1.getDestinationHost();
    const DestinationRealm& dr = str1.getDestinationRealm();
    const AuthApplicationId& aaid1 = str1.getAuthApplicationId();

    // [2.1.1.x] Fixed AVP 

    //[2.1.1.1] set the session Id that is taken from Request
    answer.setSessionId(sid);

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    // Vaule taken from the Requested Message
    OriginHost origh(dh.value());
    answer.setOriginHost(origh);

    // [2.1.2.2] The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    // Values taken from the Requested Message
    OriginRealm origr(dr.value());
    answer.setOriginRealm(origr);

    // [2.2.x] Optional AVPs

    // [2.2.1] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    ResultCode rc(2001u);
    answer.setResultCode(rc);

    // [2.2.2.1] Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // ResultCode AVP is already been set.
    //ExperimentalResult er1;

    // [2.2.2.2] Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vid(VENDOR_ID);
    //er1.setVendorId(vid);

    // [2.2.2.3] Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode erc(2001);
    //er1.setExperimentalResultCode(erc);

    // [2.2.2] set the ExperimentalResult AVP
    // answer.setExperimentalResult(er1);

    // [2.2.3] The Error-Message AVP (AVP Code 281) is of type UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message
    // ErrorMessage erm("Server problem");
    // answer.setErrorMessage(erm);

    // [2.2.4] The Error-Reporting-Host AVP (AVP Code 294) is of type
    // DiameterIdentity.  This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP
    // ErrorReportingHost erh("xyz.dia.com");
    // answer.setErrorReportingHost(erh);

    // [2.2.5] The Failed-AVP AVP (AVP Code 279) is of type Grouped and provides
    // debugging information in cases where a request is rejected or not
    // fully processed due to erroneous information in a specific AVP
    // FailedAVP fh1;
    // answer.addFailedAVP(fh1);


    // [2.2.6] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId osid(41);
    answer.setOriginStateId(osid);

    // [2.2.7.1]
    //URI uri1("SecondaryEventCollectionFunction.com", URI::AAA,
    //       3880, URI::TCP, URI::DIAMETER);

    // [2.2.7] Upon receiving Result-Code AVP is set to 
    // DIAMETER_REDIRECT_INDICATION Diameter node forwards the request 
    // directly to one of the hosts identified in these AVPs (AVP Code 292).
    // Application need not to set this.
    //RedirectHost rh(uri1);
    //answer.addRedirectHost(rh);

    // [2.2.8] The Redirect-Host-Usage AVP (AVP Code 261) is of type Enumerated.
    // This AVP MAY be present in answer messages whose 'E' bit is set and
    //  the Result-Code AVP is set to DIAMETER_REDIRECT_INDICATION.
    // The following values are supported.
    // DONT_CACHE             0
    // ALL_SESSION            1
    // ALL_REALM              2
    // REALM_AND_APPLICATION  3
    // ALL_APPLICATION        4
    // ALL_HOST               5
    // ALL_USER               6
    //RedirectHostUsage rhu(RedirectHostUsage::ALL_SESSION);
    //answer.setRedirectHostUsage(rhu);


    // [2.2.9] The Redirect-Max-Cache-Time AVP (AVP Code 262) is of type 
    // Unsigned32. This AVP contains the maximum number of seconds the peer 
    // and route table entries, created as a result of the Redirect-Host,
    // to cache
    //RedirectMaxCacheTime rmct(500);
    //answer.setRedirectMaxCacheTime(rmct);

    // [2.2.10.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //diameter::base::ProxyInfo pi1;

    // [2.2.10.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.10.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    //[2.2.10] set the ProxyInfo AVP
    // Application should not set this AVP.
    // answer.addProxyInfo(pi1);

    cout<<answer;

    // Send answer message to stack
    SendToStack(&answer);

    return (ITS_SUCCESS);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the AS request to the
 *      diameter stack. Creates the Accounting Request object,
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
int SendASRequest() 
{
    // [1]. Create an instance of ASRequest class
    // The AS-Request command is sent by a Diameter
    // Command-Code = 274
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::ASRequest request;

    // [2.1.1.x ]Fixed AVP 

    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    // Get the user input to Abort the session.
    string sessIdString;
    cout<<"Please Enter the Session ID to Abort \n";
    cin>>sessIdString;

    request.setSessionId(SessionId(sessIdString));

    // [2.1.2.x] Required AVPs 

    // [2.1.2.1.] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(GetOriginHost());
    request.setOriginHost(origh);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(GetOriginRealm());
    request.setOriginRealm(origr);

    // [2.1.2.3] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm desr(GetDestinationRealm());
    request.setDestinationRealm(desr);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost desh(GetDestinationHost());
    request.setDestinationHost(desh);

    // [2.2.1.5] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authid(GQGQ_INTERFACE_APP_ID);
    request.setAuthApplicationId(authid);

    // [2.2.1.6] The Session-Abort-Cause AVP (AVP code 500) is of type 
    // Enumerated,and determines the cause of a session abort request.
    //  The following values are defined:
    // BEARER_RELEASED
    // INSUFFICIENT_SERVER_RESOURCES
    // INSUFFICIENT_BEARER_RESOURCES
    AbortCause acause(AbortCause::INSUFFICIENT_SERVER_RESOURCES);
    request.setAbortCause(acause);

    // [2.2.x] Optional AVPs

    // [2.2.1] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId orgid(41);
    request.setOriginStateId(orgid);


    // [2.2.2.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //diameter::base::ProxyInfo pi1;

    // [2.2.2.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);        

    // [2.2.2.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    //[2.2.2] set ProxyInfo AVP
    // Application should not set this AVP.
    // request.addProxyInfo(pi1);

    // [2.2.3] Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the Capabilities
    // Exchange message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord rrec("nemo");
    // Application should not set this AVP.
    //request.addRouteRecord(rrec);

    cout<<request;

    // Send AS Request Message to Diameter stack.
    SendToStack(&request);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the AS Answer to the
 *      diameter stack. Creates the AS Answer object,
 *      populate the AVPs and send the message to the stack.
 *
 *  Input Parameters:
 *      const diameter::CommandImpl *impl: Pointer to the received Request
 *      Command, for which the Answer is to be sent.
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
int SendASAnswer(const CommandImpl *impl) 
{
    // [1]. Create an instance of  RA Answer class
    // The AS-Answer command is sent by a Diameter
    // server to a Diameter client in order to request deregistration
    // Command-Code = 274 
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::ASAnswer answer;

    // Create an instance of  AS Request class
    ASRequest asr(*impl);

    // Get the AVP values from AS Request Message
    const SessionId& sid = asr.getSessionId();
    const OriginHost& oh = asr.getOriginHost();
    const OriginRealm& or1 = asr.getOriginRealm();
    const DestinationHost& dh = asr.getDestinationHost();
    const DestinationRealm& dr = asr.getDestinationRealm();

    // [2.1.1.x] Fixed AVP

    // [2.1.1.1] The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    answer.setSessionId(sid);

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(dh.value());
    answer.setOriginHost(origh);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(dr.value());
    answer.setOriginRealm(origr);

    // [2.2.x]Optional AVPs


    // [2.2.1] Set the Result-Code AVP .
    // The Result-Code AVP indicates whether a particular request
    // was completed successfully or whether an error occurred
    // All Diameter answer messages must contain one Result-Code AVP
    // Diameter provides the following classes of error which
    // is represented by the Result-Code AVP:
    // 1xxx - Informational
    // 2xxx - Success
    // 3xxx - Protocol Errors
    // 4xxx - Transient Failures
    // 5xxx - Permanent Failure
    // The AVP Code of AVP is 268.
    // The data type of AVP is Unsigned32.
    ResultCode rc(2001u);
    answer.setResultCode(rc);

    // [2.2.2.1] Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // Already ResultCode AVP is been test.
    //ExperimentalResult er1;

    // [2.2.2.2] Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vid(VENDOR_ID);
    //er1.setVendorId(vid);

    // [2.2.2.3] Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode erc(2001);
    //er1.setExperimentalResultCode(erc);

    // [2.2.2] set ExperimentalResult AVP
    // answer.setExperimentalResult(er1);

    // [2.2.3] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId osid(41);
    answer.setOriginStateId(osid);

    // [2.2.4] The Error-Message AVP (AVP Code 281) is of type UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message
    // Result code is successfull
    //ErrorMessage erm("Error sdf");
    //answer.setErrorMessage(erm);

    // [2.2.5] The Error-Reporting-Host AVP (AVP Code 294) is of type
    // DiameterIdentity.  This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP
    //ErrorReportingHost erh("host1.xyz.com");
    //answer.setErrorReportingHost(erh);

    // [2.2.6] The Failed-AVP AVP (AVP Code 279) is of type Grouped and provides
    // debugging information in cases where a request is rejected or not
    // fully processed due to erroneous information in a specific AVP
    //FailedAVP fa;
    //answer.addFailedAVP(fa);

    // [2.2.7.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //diameter::base::ProxyInfo pi2;

    // [2.2.7.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy1.abc.com");
    //pi2.setProxyHost(ph1);

    // [2.2.7.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi2.setProxyState(ps1);

    // [2.2.7] set the ProxyInfo AVP.
    // answer.addProxyInfo(pi2);

   cout<<answer;

    // Send AS Answer to diameter stack w.r.t AS Request.
    SendToStack(&answer);

    return (ITS_SUCCESS);
}
