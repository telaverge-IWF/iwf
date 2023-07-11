/********************************-*-CPP-*-***********************************
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
 * LOG: $Log: RegistrationTerminationTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:03  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2006/11/07 13:29:52  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1  2006/10/03 09:21:28  rrath
 * LOG: Baseline distributed demo for new IMS Interfaces.
 * LOG:
 * LOG:
 * ID: $Id: RegistrationTerminationTest.cpp,v 3.1 2008/03/31 10:33:03 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: RegistrationTerminationTest.cpp,v 3.1 2008/03/31 10:33:03 nvijikumar Exp $"

#include <app.h>
#include <idc_api.h>

#include <wx_defines.h>
#include <diameter/wx/RegistrationTermination.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::wx;

unsigned int sIdxWxRt = 0;
string sessIdStringWxRt;
IDSCLApi apiWxRt;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the RegistrationTerminationRequestto the
 *      diameter stack. Create the RegistrationTerminationRequest object,
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
int SendWxRegistrationTerminationRequest() 
{
    // 1. Create an instance of RegistrationTerminationRequest class
    // The Registration-Termination-Request command is sent from a Diameter
    // multimedia client to a Diameter multimedia server in order to
    // saReq it to store the name of the server that is currently
    // serving the user.
    // Command-Code = 301 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    RegistrationTerminationRequest rtReq(false,false);

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an RegistrationTerminationRequest command and
    // pass them by value to the corresponding data members set
    // methods of the RegistrationTerminationRequest object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.

    apiWxRt.AllocateSessionIndex(10000, sIdxWxRt, sessIdStringWxRt);
    rtReq.setSessionId(diameter::base::SessionId(sessIdStringWxRt));

    // Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter
    // application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as
    // possible.
    VendorSpecificApplicationId        vendorSpecificApplicationId1;

    // [2.2.5] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // Set the Auth-Application-Id AVP.
    // [2.2] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(WX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.2] Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    //AcctApplicationId acctApplicationId(12);
    //vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    //[2.1] Set the  Vendor-Specific-Application-Id AVP.
    rtReq.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    // [2.1] Set the Auth-Session-State AVP.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    rtReq.setAuthSessionState(authSessionState);

    // [2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    rtReq.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    rtReq.setOriginRealm(originRealm);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    rtReq.setDestinationHost(destinationHost);

    // [2.1] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    rtReq.setDestinationRealm(destinationRealm);

    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    rtReq.setUserName(userName);

    // for a de-registration operation.
    // The AVP Code of Degistration-Reason AVP is 615.
    // The data type of User-Name AVP is Grouped.
    DeregistrationReason deregistrationReason;
                                                                                
    // [2.1] Set the Reason-Code AVP.
    // The Reason-Code AVP defines the reason for the network
    // initiated de-registration.
    // The AVP Code of Reason-Code AVP is 616 .
    // The data type of Reason-Code AVP is Enumerated{0,1,2,3}.
    ReasonCode reasonCode(ReasonCode::NEW_SERVER_ASSIGNED);
    deregistrationReason.setReasonCode(reasonCode);
                                                                                
    // [2.2] Set the Reason-Info AVP.
    // The Reason-Info AVP contains textual information to inform
    // the user about the reason for a de-registration
    // The AVP Code of Reason-Info AVP is 617.
    // The data type of Reason-Info AVP is UTF8String.
    ReasonInfo reasonInfo("1234567");
    deregistrationReason.setReasonInfo(reasonInfo);

    // [2.1] Set the De-Registration-Reason AVP.
    rtReq.setDeregistrationReason(deregistrationReason);


    //cout<<rtReq;
    //SendToStack(&rtReq);
    //WxStats::GetWxStats()->UpdateSendStats(rtReq.getCommandCode(), ITS_TRUE);

    std::cout << rtReq << std::endl;

    apiWxRt.Send(rtReq, sIdxWxRt, WX_INTERFACE_APP_ID);


    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the RegistrationTermination
 *      request made by the diameter stack. Create the 
 *      RegistrationTerminationAnswer object, populate the AVPs and send the 
 *      message to the stack. send message to Diameter Stack
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

int SendWxRegistrationTerminationAnswer(const CommandImpl * impl1) 
{
    // 1. Create an instance of RegistrationTerminationAnswer class
    // The Registration-Termination-Answer command is sent by a server
    // in response to the Registration-Termination-Request command with
    // Command-Code = 304 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    RegistrationTerminationAnswer rta(false, false);
                                                                                
   // Create an instance of RegistrationTerminationrequest class
    RegistrationTerminationRequest rreq(*impl1);
                                                                                
    // Get some AVP values from requested Message and set them to Answer
    const SessionId &sid1 = rreq.getSessionId();
    const OriginHost &oh1 = rreq.getOriginHost();
    const OriginRealm &or1 = rreq.getOriginRealm();
    const DestinationHost &dh1 = rreq.getDestinationHost();
    const DestinationRealm &dr1 = rreq.getDestinationRealm();

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an RegistrationTerminationAnswer command and
    // pass them by value to the corresponding data members set
    // methods of the RegistrationTerminationAnswer object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    rta.setSessionId(sid1);
                                                                                
    // Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter
    // application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as
    // possible.
    VendorSpecificApplicationId        vendorSpecificApplicationId1;

     // [2.2.5] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);
                                                                                
    // Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(WX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

     // Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);
                                                                                
    // [2.1.1] Set the  Vendor-Specific-Application-Id AVP.
    rta.setVendorSpecificApplicationId(vendorSpecificApplicationId1);
                                                                                
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    // [2.1.1] Set the Auth-Session-State AVP.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    rta.setAuthSessionState(authSessionState);
                                                                                
    // [2.1.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(dh1.value());
    rta.setOriginHost(originHost);
                                                                                
    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(dr1.value());
    rta.setOriginRealm(originRealm);
                                                                                
    // [2.2] Set the Result-Code AVP .
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
    ResultCode resultCode(2001u);
    rta.setResultCode(resultCode);
                                                                                
    // Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // already ResultCode is set, both should not be set
    //ExperimentalResult experimentalResult;
                                                                                
    // Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vendorId1(VENDOR_ID);
    //experimentalResult.setVendorId(vendorId1);
                                                                                
    // Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode experimentalResultCode(2001u);
    //experimentalResult.setExperimentalResultCode(experimentalResultCode);
    // [2.2] Set the Experimental-Result AVP.
    // rta.setExperimentalResult(experimentalResult);
                                                                                
    // Create the Failed-AVP AVP.
    // The Failed-AVP AVP provides debugging information in cases
    // where a request is rejected or not fully processed due to
    // erroneous information in a specific AVP.
    // The AVP Code of AVP is 279.
    // The data type of AVP is Grouped Type.
                                                                                
    // FailedAVP
    //    failedAVP;
    // [2.2] Set the Failed-AVP.
    // rta.addFailedAVP(failedAVP);
                                                                                
    // Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;
                                                                                
    // Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"),proxyHost2("proxyHost2");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);
                                                                                
    // Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // The data type of is OctetString.
    //ProxyState proxyState1("proxyState1"),proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);
                                                                                
    // [2.2] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // rta.addProxyInfo(proxyInfo1);
    // rta.addProxyInfo(proxyInfo2);
                                                                                
    // [2.2] Set the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord routeRecord1("routeRecord1"),
    //routeRecord2("routeRecord2");
                                                                                
    // Set Route Record
    // rta.addRouteRecord(routeRecord1);
    // rta.addRouteRecord(routeRecord2);
                                                                                
    // 3. Send the encoded RegistrationTerminationAnswer object to an output
    // stream
    // buffer(Note: For test purpose, the object is being sent to ios::cout
    // output buffer.
                                                                                
    //cout << rta;

    //SendToStack(&rta);
    //WxStats::GetWxStats()->UpdateSendStats(rta.getCommandCode(), ITS_FALSE);

    std::cout << rta << std::endl;

    apiWxRt.Send(rta, sIdxWxRt, WX_INTERFACE_APP_ID);
    return (ITS_SUCCESS);
}
