/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: ACTest.cpp,v $
 * LOG: Revision 1.2  2011/04/25 05:26:45  nvijikumar
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1  2011/03/10 09:27:34  vkumara
 * LOG: Sample Demo for Gy Interface
 * LOG:
 * LOG:
 *
 * ID: $Id: ACTest.cpp,v 1.2 2011/04/25 05:26:45 nvijikumar Exp $
 ****************************************************************************/
#include <app.h>
#include <gy_defines.h>
#include <gy_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::gy;

extern string sessIdString;
extern ITS_UINT sIdx;

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the RA raReq to the
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
int SendGyACRequest(int reqType, const diameter::CommandImpl* impl)
{
    // [1] Create AccountingRequest object.
    // parameter error - whether this command carries an error indicator
    // parameter retrans - whether this is a retransmission

    ACRequest acr(false, false);
    string sessIdString;
    static int num = 0;

    // [2] Insert data in the created AccountingRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed paramete "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    if (reqType == START || reqType == EVENT)
    {
        num =0;
        AllocateSession(GY_INTERFACE_APP_ID,sIdx,sessIdString);
        acr.setSessionId(SessionId(sessIdString));
    }
    else
    {
        //for unit test provide the values of Session Id and Index
        cout << endl << "Please Enter the SessionId:" <<endl;
        cin >> sessIdString ;
        acr.setSessionId(SessionId(sessIdString));
    }


    // Is is an proprietary API used in Accounting State Machine
    // It can be set with the basis of Application database.
    // Application can have its own logic to set or reset this API.
    // If this AVP is not exist by default value is taken as "true".
    //acr.setStorageSpaceAvailable(true);

    // Is is an proprietary API used in Accounting State Machine
    // It can be set with the basis of Application database.
    // Application can have its own logic to set or reset this API.
    // If this AVP is not set by default value is taken as "false".
    //acr.setLastRecordInStorage(false);

    // [2.1.2] Populate required Mandatories.
    // [2.1.2.1] Populate required paramete "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost origh(GetOriginHost());
    acr.setOriginHost(origh);

    // [2.1.2.2] Populate required paramete "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
    acr.setOriginRealm(origr);

    // [2.1.2.3] Populate required paramete "Destination-Realm".
    // Set the Destination-Realm AVP.
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    DestinationRealm desr(GetDestinationRealm());
    acr.setDestinationRealm(desr);

    // [2.1.2.4] Populate required paramete "Accounting-Record-Type".
    // Set the Accounting-Record-Type AVP.
    // The data type of Accounting-Record-Type is Enumerated.
    // This Avp contains the type of accounting record being sent.
    // The following values are currently defined
    // EVENT_RECORD                    1
    // START_RECORD                    2
    // The AVP Code of Accounting-Record-Type is 480.
    switch (reqType)
    {
    case START:
    case START_AUTHSESS:
    {
        AccountingRecordType accr(AccountingRecordType::START_RECORD);
        acr.setAccountingRecordType(accr);
        break;
    }
    case INTERIM:
    {
        AccountingRecordType accr(AccountingRecordType::INTERIM_RECORD);
        acr.setAccountingRecordType(accr);
        break;
    }
    case STOP:
    {
        AccountingRecordType accr(AccountingRecordType::STOP_RECORD);
        acr.setAccountingRecordType(accr);
        break;
    }
    default:
        AccountingRecordType accr(AccountingRecordType::EVENT_RECORD);
        acr.setAccountingRecordType(accr);
    }

    // [2.1.2.5] Populate required paramete "Accounting-Record-Number".
    // Set the Accounting-Record-Number AVP.
    // The data type of Accounting-Record-Number is Unsigned32.
    // This AVP identifies this record within one session.
    // The AVP Code of Accounting-Record-Number is 485.
    // 0 for records of type EVENT_RECORD and START_RECORD
    // 1 for the first INTERIM_RECORD, 2 for the second, and so on
    AccountingRecordNumber accRec(0u);
    acr.setAccountingRecordNumber(accRec);

    // [2.2] Populate Optionals
    // [2.2.1] Populate optional parameter "Acct-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AcctApplicationId accId(3);
    acr.setAcctApplicationId(accId);

    // [2.2.2] Insert Vendor-Specific-Application-Id Data.
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP is used to advertise support of a vendor-specific Diameter
    // Application.
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Vendor-Specific-Application-Id is 260.
    VendorSpecificApplicationId venSAId;

    // [2.2.2.1] Populate optional parameter "Vendor-Id".
    // Set the Vendor-ID AVP.
    // The data type of Vendor-ID is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may be
    // sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates that
    // this field is ignored.
    // The AVP Code of Vendor-ID is 266.
    VendorId venId(VENDOR_ID);
    venSAId.addVendorId(venId);

    // [2.2.2.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId authId(GY_INTERFACE_APP_ID);
    venSAId.setAuthApplicationId(authId);

    // acr.setVendorSpecificApplicationId(venSAId);

    // [2.2.3]Populate optional parameter "User-Name"
    // Set the User-Name AVP.
    // The data type of User-Name is UTF8String.
    // This AVP contains the User-Name.
    // The AVP Code of User-Name is 1.
    UserName userName("sip:good.customer@3gppnetwork.com");
    acr.setUserName(userName);


    cout<<"Send ACR "<< acr<<endl;
    SendDiaAppMsg(acr, sIdx);
    GyStats::GetGyStats()->UpdateSendStats(acr.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;

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
int SendGyACAnswer(const CommandImpl *impl)
{
    ACAnswer aca(false, false);

    ACRequest com_req(*impl);

    const SessionId& sid1 = com_req.getSessionId();
    const OriginHost& oh1 = com_req.getOriginHost();
    const OriginRealm& or1 = com_req.getOriginRealm();
    const AccountingRecordType& recordType = com_req.getAccountingRecordType();

    // [2] Insert data in the created SessionTerminationRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed paramete "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    aca.setSessionId(sid1);

    // [2.2.2] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    ResultCode rc(2001u);
    aca.setResultCode(rc);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost origh(GetOriginHost());
    aca.setOriginHost(origh);

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
    aca.setOriginRealm(origr);

    // [2.2.5] Populate required paramete "Accounting-Record-Type".
    // Set the Accounting-Record-Type AVP.
    // The data type of Accounting-Record-Type is Enumerated.
    // This Avp contains the type of accounting record being sent.
    // The following values are currently defined
    // EVENT_RECORD                    1
    // START_RECORD                    2
    // The AVP Code of Accounting-Record-Type is 480.
    aca.setAccountingRecordType(recordType);

    // [2.1.6] Populate required paramete "Accounting-Record-Number".
    // Set the Accounting-Record-Number AVP.
    // The data type of Accounting-Record-Number is Unsigned32.
    // This AVP identifies this record within one session.
    // The AVP Code of Accounting-Record-Number is 485.
    AccountingRecordNumber arn(0u);
    aca.setAccountingRecordNumber(arn);

    // [2.2.7] Populate optional parameter "Acct-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AcctApplicationId accid(3);
    aca.setAcctApplicationId(accid);

    // This AVP contains the User-Name.
    // The AVP Code of User-Name is 1.
    UserName un("sip:good.customer@india.internal.net");
    aca.setUserName(un);

    cout<<"Send ACA " << aca <<endl;
    SendDiaAppMsg(aca, sIdx);
    GyStats::GetGyStats()->UpdateSendStats(aca.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS; 

}
