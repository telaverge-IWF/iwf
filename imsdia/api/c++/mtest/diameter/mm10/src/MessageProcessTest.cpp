/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: MessageProcessTest.cpp,v $
 * LOG: Revision 1.1  2011/06/14 05:29:42  vkumara
 * LOG: Baseline for Mm10 interface.
 * LOG:
 * LOG:
 * ID: $Id: MessageProcessTest.cpp,v 1.1 2011/06/14 05:29:42 vkumara Exp $
 ****************************************************************************/
#ident "$Id: MessageProcessTest.cpp,v 1.1 2011/06/14 05:29:42 vkumara Exp $"

#include <app.h>
#include <mm10_defines.h>
#include <mm10_stats.h>
#include <diameter/mm10/MessageProcess.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::mm10;

string sessIdString;
ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the  Mm10MessageProcessRequest to the
 *      diameter stack. Create the  Mm10MessageProcessRequest object,
 *      populate the AVPs and send the message to the stack.
 *
 *  Input Parameters:
 *      User choice.
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
int SendMm10MessageProcessRequest()
{
    // [1]. Create an instance of Mm10MessageProcessRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::mm10::MessageProcessRequest  mpReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
  AllocateSession(MM10_INTERFACE_APP_ID, sIdx, sessIdString);
  mpReq.setSessionId(diameter::base::SessionId(sessIdString));

  mpReq.setSessionIndex(sIdx);

   // [2.1.2.x] Required AVPs

    // [2.1.2.1.1]Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as possible.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.1.2.2]Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    AuthSessionState authSessionState(AuthSessionState::NO_STATE_MAINTAINED);
    mpReq.setAuthSessionState(authSessionState);



    // [2.1.2.1.2] Populate required parameter "Vendor-Id".
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
    // [2.1.2.1.3] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(MM10_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.1.2.1.4] Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.Exactly one of the Auth-Application-Id AVP and Acct-
    // Application-Id may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);
    //[2.1.2.1] Set the  Vendor-Specific-Application-Id AVP.
    mpReq.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // [2.1.2.3] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    mpReq.setOriginHost(originHost);

    // [2.1.2.4] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    mpReq.setOriginRealm(originRealm);

    // [2.1.2.5] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    mpReq.setDestinationRealm(destinationRealm);

    // [2.2.1] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    mpReq.setDestinationHost(destinationHost);


    // [2.2.10] Populate optional parameter "Event-Timestamp".
    // Set the Event-Timestamp AVP.
    // The data type of Event-Timestamp is Time.
    // This AVP is used to record the time that the reported event occurred, in
    // seconds since January 1, 1900 00:00 UTC.
    // The AVP Code of Event-Timestamp is 55.

   mpReq.setEventTimestamp(EventTimestamp(999));

   TriggerEvent triggerEvent(TriggerEvent::MM1_Message_Submission_Profile_based);
   mpReq.setTriggerEvent(triggerEvent);
   
   OriginatingInterface  originatingInterface(OriginatingInterface::MM1);
   mpReq.setOriginatingInterface(originatingInterface);

   ServedUserIdentity  servedUserIdentity;
   VASPID   vASPID("A100B");
   servedUserIdentity.setVASPID(vASPID);
   mpReq.addExtra(servedUserIdentity);

   InitialRecipientAddress iRecAddr;
   SequenceNumber sNum(1234);
   iRecAddr.setSequenceNumber(sNum);
   RecipientAddress rAddr("172.16.3.80");
   iRecAddr.setRecipientAddress(rAddr);
   mpReq.addExtra(iRecAddr);


    if (appMode == UNIT_TEST)
    cout<<mpReq;

    // Send object to stack.
    SendDiaAppMsg(mpReq, sIdx);

    Mm10Stats::GetMm10Stats()->UpdateSendStats(mpReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the  MessageProcess Request
 *      made by the diameter stack. Create the MessageProcessAnswer
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
int SendMm10MessageProcessAnswer(const CommandImpl * impl)
{
    // 1. Create an instance of MessageProcessAnswer class
    // The Multimedia-Auth-Answer command is sent by a server
    // in response to the Multimedia-Auth-Request command with
    // Command-Code = 303 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::mm10::MessageProcessAnswer  mpAns;

    // Create an instance of MultimediaAuthRequest class to get host and
    // session details
    MessageProcessRequest mpreq(*impl);

    // Get AVP values from requested message
    const SessionId &sid1 = mpreq.getSessionId();
    const OriginHost &oh1 = mpreq.getOriginHost();
    const OriginRealm &or1 = mpreq.getOriginRealm();
    const DestinationHost &dh1 = mpreq.getDestinationHost();
    const DestinationRealm &dr1 = mpreq.getDestinationRealm();
    const VendorSpecificApplicationId &vsAppId = 
                       mpreq.getVendorSpecificApplicationId();

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an MessageProcessAnswer command and
    // pass them by value to the corresponding data members set
    // methods of the MessageProcessAnswer object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    mpAns.setSessionId(sid1);

    mpAns.setSessionIndex(mpreq.getSessionIndex());

    // [2.1.2.x] Required AVPs

    // [2.1.2.1.1]Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as possibl
    //[2.1.2.1] Set the  Vendor-Specific-Application-Id AVP.
    mpAns.setVendorSpecificApplicationId(vsAppId);

    // [2.1.2.2]Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    AuthSessionState authSessionState(AuthSessionState::NO_STATE_MAINTAINED);
    mpAns.setAuthSessionState(authSessionState);

    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    mpAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    mpAns.setOriginRealm(originRealm);


    if (appMode == UNIT_TEST)
    cout<<mpAns;

    // Send Object to stack.
   SendDiaAppMsg(mpAns, sIdx);

    // Update stats.
    Mm10Stats::GetMm10Stats()->UpdateSendStats(mpAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}


