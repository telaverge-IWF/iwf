/*********************************-*-C-*-************************************
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
 * LOG: $Log: sample_sh.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:00  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.5  2006/10/29 07:30:45  kamakshilk
 * LOG: Re-Auth received handed to BaseMessage()
 * LOG:
 * LOG: Revision 2.4  2006/10/26 05:40:43  kamakshilk
 * LOG: Added DisplayBaseMenuToApp() in the menu.
 * LOG:
 * LOG: Revision 2.3  2006/10/24 11:45:50  kamakshilk
 * LOG: Fix for Bug ID 4588. Handle Base messages
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:23:57  kamakshilk
 * LOG: Changes to work with ITS-Diameter APIs
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:38  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.5  2006/08/09 08:33:05  kamakshilk
 * LOG: Subscriber Profile Info from xml file sent in PUR,PNR and UDA
 * LOG:
 * LOG: Revision 1.4  2006/06/05 12:11:55  yranade
 * LOG: Updates to compile with CC Compiler
 * LOG:
 * LOG: Revision 1.3  2006/05/22 10:42:13  nvijikumar
 * LOG: putting sane values.
 * LOG:
 * LOG: Revision 1.2  2006/04/28 07:06:48  nvijikumar
 * LOG: Code Enhancement (Documentation, exception handling).
 * LOG:
 * LOG: Revision 1.1  2006/04/13 11:08:06  nvijikumar
 * LOG: Baseline demo programs
 * LOG:
 * LOG:
 * ID: $Id: sample_sh.cpp,v 3.1 2008/03/31 10:33:00 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: sample_sh.cpp,v 3.1 2008/03/31 10:33:00 nvijikumar Exp $"

#include <diameter/sh/PushNotification.h>
#include <diameter/sh/SubscribeNotifications.h>
#include <diameter/sh/ProfileUpdate.h>
#include <diameter/sh/UserData.h>

#include <app.h>
#include <idc_api.h>

using namespace std;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::sh;
using namespace diameter::cxdx;

IDSCLApi apiSh;
static bool first = false;
unsigned int sIdxSh = 0;
string sessIdStringSh;

extern char subsProfile[2000];

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function handles the message received to the base
 *      diameter stack frm Sh App. This identifies the commands
 *      in the message and processes that command.
 *
 *  Input Parameters:
 *      ITS_Event& ev: ITS_Event
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
int ShMessage(const diameter::CommandImpl *impl, unsigned int &sIdxsh)
{
    sIdxSh=sIdxsh;
    try
    {
        switch (impl->getCommandCode())
        {
        case 306: 
            if(impl->isRequest())
            {
                UserDataRequest udreq(*impl);
                cout << "udreq" << udreq << endl;
                SendUserDataAnswer(impl);
            }
            else
            {
                UserDataAnswer udans(*impl);
                cout << "udans" << udans << endl;
            }
            break;

        case 307:
            if(impl->isRequest())
            { 
                ProfileUpdateRequest pureq(*impl);
                cout << "pureq" << pureq << endl;

                SendProfileUpdateAnswer(impl);

            }
            else
            {
                ProfileUpdateAnswer puans(*impl);
                cout << "puans" << puans << endl;
            }
            break;

        case 308: 
            if(impl->isRequest())
            {
                SubscribeNotificationsRequest snreq(*impl);
                cout << "snreq" << snreq << endl;

                SendSubscribeNotificationsAnswer(impl);
            }
            else
            {
                SubscribeNotificationsAnswer snans(*impl);
                cout << "snans" << snans << endl;
            }
            break;

        case 309:
            if(impl->isRequest())
            {
                PushNotificationRequest pnreq(*impl);
                cout << "pnreq" << pnreq << endl;
                SendPushNotificationAnswer(impl);
            }
            else
            {
                PushNotificationAnswer pnans(*impl);
                cout << "pnans" << pnans << endl;
            }
            break;

        case 274:
        case 275:
        case 258:
            BaseMessage(impl,sIdxsh);
            break;
     
        default:
            break;
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

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function displays the menu options for the
 *      Sh interface.
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
int ShMenu()
{
    string input;
    int ret = 0;
    int k=1;
    while(k)
    {
        do
        {
            cout << endl << "Select Sh Command"<<endl<<endl;
            cout <<"1: PUR - Profile Update Request"<<endl;
            cout <<"2: PNR - Push Notification Request"<<endl;
            cout <<"3: SNR - Subscriber Notification Request"<<endl;
            cout <<"4: UDR - User Data Request"<<endl;
            cout <<"5: To Send Base protocol Messages"<<endl;
            cout <<"99: To previous Menu"<<endl;

            cin >> input;
            ret = atoi(input.c_str());
        } while ((ret < 1 || ret > 5) && ret!=99);

        switch(ret)
        {
        case 1:
            SendProfileUpdateRequest(); break;
        case 2:
            SendPushNotificationRequest(); break;
        case 3:
            SendSubscribeNotificationsRequest(); break;
        case 4:
            SendUserDataRequest(); break;
        case 5:
            DisplayBaseMenuToApp(); break;
        case 99:
            k=0; break;
        default:
            cout << endl << "please enter the correct choice";
            break;
        }
    }
    return 0;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Profile update request to the
 *      diameter stack. This creates the ProfileUpdateRequest object,
 *      populate the AVPs and sends the message to the stack.
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
int SendProfileUpdateRequest()
{
    // [1] Create ProfileUpdateRequest object.
    ProfileUpdateRequest pur(false,false);

    // [2] Insert data in the created ProfileUpdateRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    apiSh.AllocateSessionIndex(10000, sIdxSh, sessIdStringSh);
    printf("\tSession Index: %d\n", sIdxSh);
    pur.setSessionId(SessionId(sessIdStringSh));

    // [2.2] Populate required Mandatories.
    // [2.2.1] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.1.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(10415u);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // [2.2.1.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication
    // and Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId authApplicationId(SH_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.2.1.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    pur.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // [2.2.2] Populate required parameter "Auth-Session-State".
    // Set the Auth-Session-State AVP.
    // The data type of Vendor-Specific-Application-Id is Enumerated.
    // This AVP specifies whether state is maintained for a particular session
    // The AVP Code of Auth-Session-State is 277.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    pur.setAuthSessionState(authSessionState);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost originHost(GetOriginHost());
    pur.setOriginHost(originHost);

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm originRealm(GetOriginRealm());
    pur.setOriginRealm(originRealm);

    // [2.2.5] Populate required parameter "Destination-Realm".
    // Set the Destination-Realm AVP.
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    DestinationRealm destinationRealm(GetDestinationRealm());
    pur.setDestinationRealm(destinationRealm);

    // [2.2.6] Populate required parameter "User-Identity".
    // Set the User-Identity AVP.
    // The data type of Destination-Realm is Grouped.
    // This AVP contains either Public Identity or an MSISDN AVP.
    // The AVP Code of User-Identity is 700.
    UserIdentity userIdentity;

    // [2.2.6.1] Populate required parameter "Public-Identity".
    // Set the Public-Identity AVP.
    // The data type of Public-Identity is UTF8String.
    // This AVP contains the public identity of a user in the IMS
    // The AVP Code of Public-Identity is 601.
    PublicIdentity  publicIdentity("sip:user@3gppnetwork.com");
    userIdentity.setPublicIdentity(publicIdentity);

    // [2.2.6.2] Populate required parameter "MSISDN".
    // Set the MSISDN AVP.
    // The data type of MSISDN is OctetString.
    // This AVP contains an MSISDN, in international number format as 
    // described in ITU-T Rec E.164, encoded as a TBCD-string, i.e. 
    // digits from 0 through 9 are encoded 0000 to 1001; 1111 is used
    // as a filler when there is an odd number of digits; bits 8 to 5 
    // of octet n encode digit 2n; bits 4 to 1 of octet n encode digit
    // 2(n-1)+1.
    // The AVP Code of MSISDN is 701.
    MSISDN msisdn("3217260686");
    userIdentity.setMSISDN(msisdn);

    pur.setUserIdentity(userIdentity);

    // [2.2.7] Populate required parameter "Data-Reference".
    // Set the Data-Reference AVP.
    // The data type of Data-Reference is Enumerated.
    // This AVP indicates the type of the requested user data 
    // in the operation UDR and SNR.
    // The AVP Code of Data-Reference is 703.
    DataReference dataReference(DataReference::RepositoryData);
    pur.setDataReference(dataReference);

    // [2.2.8] Populate required parameter "User-Data".
    // Set the User-Data AVP.
    // The data type of User-Data is OctateString.
    // This AVP contains the user data requested in the PUR and SNR 
    // operations and the data to be modified in the UPR operation
    // The AVP Code of User-data is 702.
    ShUserData userData(subsProfile);
    pur.setShUserData(userData);

    // [2.2.9] Populate optional parameter "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of User-Data is DiameterIdentity.
    // This AVP contains the Host the message is to be routed to.
    // The absence of the Destination-Host AVP will cause a message to be
    // sent to any Diameter server supporting the application within the
    // realm specified in Destination-Realm AVP.
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    pur.setDestinationHost(destinationHost);

    // [2.2.10] Populate optional parameter "Supported-Features".
    // Set the Supported-Features AVP.
    // The data type of User-Data is Grouped.
    // If this AVP is present it may inform the destination host about
    // the features that the origin host supports.
    // The AVP Code of Supported-Features is 628.
    SupportedFeatures supportedFeatures;

    // [2.2.10.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId1(10415u);
    supportedFeatures.setVendorId(vendorId1);

    // [2.2.10.2] Populate required parameter "Feature-List-ID".
    // Set the Feature-List-ID AVP.
    // The data type of Feature-List-ID is Unsigned32.
    // This AVP contains the identity of a feature list
    // The AVP Code of Feature-List-ID is 629.
    FeatureListID featureListID(1u);
    supportedFeatures.setFeatureListID(featureListID);

    // [2.2.10.3] Populate required parameter "Feature-List".
    // Set the Feature-List AVP.
    // The data type of Feature-List is Unsigned32.
    // This AVP contains a bit mask indicating the supported features
    // of an application.
    // The AVP Code of Feature-List is 630.
    FeatureList featureList(1u); 
    supportedFeatures.setFeatureList(featureList);

    pur.addSupportedFeatures(supportedFeatures);

    // [2.2.11] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo proxyInfo1, proxyInfo2;

    // [2.2.11.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info 
    // AVP.
    // The AVP Code of Proxy-Info is 280.
    // ProxyHost proxyHost1("proxyHost1"), proxyHost2("proxyHost1");
    // proxyInfo1.setProxyHost(proxyHost1);
    // proxyInfo2.setProxyHost(proxyHost2);

    // [2.2.11.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as
    // opaque data
    // The AVP Code of Proxy-State is 33.
    // ProxyState proxyState1("proxyState1"), proxyState2("proxyState2");
    // proxyInfo1.setProxyState(proxyState1);
    // proxyInfo2.setProxyState(proxyState2);
    // Stack sets this AVP.
    // Application should not set this AVP
    // pur.addProxyInfo(proxyInfo1);
    // pur.addProxyInfo(proxyInfo2);

    // [2.2.12] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the message.
    // The AVP Code of Route-Record is 282.
    // RouteRecord routeRecord1("nemo"),routeRecord2("nemocl");

    // Stack sets this AVP.
    // Application should not set this AVP
    // pur.addRouteRecord(routeRecord1);
    // pur.addRouteRecord(routeRecord2);

    // [3] Use appropriate application specific logic to Send object
    cout << pur;

    apiSh.Send(pur, sIdxSh, SH_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to Profile update request 
 *      sent by the application. This creates the ProfileUpdateAnswer
 *      object, populate the AVPs and sends the message to the app.
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
int SendProfileUpdateAnswer(const diameter::CommandImpl* impl) {

    ProfileUpdateRequest pureq(*impl);

    // [1] Create ProfileUpdateAnswer object.
    ProfileUpdateAnswer pua(false,false);

    // [2] Insert data in the created ProfileUpdateAnswer object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed paramete "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId& sid = pureq.getSessionId();
    pua.setSessionId(sid);

    //const VendorSpecificApplicationId& vsaid = 
    //    pureq.getVendorSpecificApplicationId();
    //SupportedFeatures sf;// = pureq.getSupportedFeatures(1);
    //ProxyInfo pInfo1;// = pureq.getProxyInfo(1);
    //ProxyInfo pInfo2;// = pureq.getProxyInfo(2);

    // [2.2] Populate required Mandatories.
    // [2.2.1] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    //VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.1.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
       //VendorId vendorId(10415u);
       //vendorSpecificApplicationId1.addVendorId(vendorId);

    // [2.2.1.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication
    // and Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
        //AuthApplicationId authApplicationId(SH_INTERFACE_APP_ID);
        //vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.2.1.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

      //pua.setVendorSpecificApplicationId(vendorSpecificApplicationId1);
    pua.setVendorSpecificApplicationId(pureq.getVendorSpecificApplicationId());

    // [2.2.2] Populate required parameter "Auth-Session-State".
    // Set the Auth-Session-State AVP.
    // The data type of Vendor-Specific-Application-Id is Enumerated.
    // This AVP specifies whether state is maintained for a particular session
    // The AVP Code of Auth-Session-State is 277.
    const AuthSessionState& asessionstate = pureq.getAuthSessionState();
    pua.setAuthSessionState(asessionstate);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    const OriginHost& oh = pureq.getOriginHost();
    pua.setOriginHost(oh);

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    const OriginRealm& orm = pureq.getOriginRealm();
    pua.setOriginRealm(orm);

    // [2.2.5] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    ResultCode resultCode(2001u);
    pua.setResultCode(resultCode);

    // [2.2.6] Populate required parameter "Experimental-Result".
    // Set the Experimental-Result AVP.
    // The data type of Experimental-Result is Grouped.
    // This AVP indicates whether a particular vendor-specific request 
    // was completed successfully or whether an error occurred.
    // The AVP Code of Experimental-Result is 297.
    // ResultCode AVP is already been set, it is not required to set.
    //ExperimentalResult experimentalResult;

    // [2.2.6.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    //VendorId vendorId1(10415u);
    //experimentalResult.setVendorId(vendorId1);

    // [2.2.6.2] Populate required parameter "Experimental-Result-Code".
    // Set the Experimental-Result-Code AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP contains a vendor-assigned value representing the result of
    // processing the request.
    // The AVP Code of Experimental-Result-Code is 298.
    //ExperimentalResultCode experimentalResultCode(2000u);
    //experimentalResult.setExperimentalResultCode(experimentalResultCode);

    //pua.setExperimentalResult(experimentalResult);

    // [2.2.7] Populate optional parameter "Supported-Features".
    // Set the Supported-Features AVP.
    // The data type of User-Data is Grouped.
    // If this AVP is present it may inform the destination host about
    // the features that the origin host supports.
    // The AVP Code of Supported-Features is 628.
    SupportedFeatures supportedFeatures;

    // [2.2.7.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId2(10415u);
    supportedFeatures.setVendorId(vendorId2);

    // [2.2.7.2] Populate required parameter "Feature-List-ID".
    // Set the Feature-List-ID AVP.
    // The data type of Feature-List-ID is Unsigned32.
    // This AVP contains the identity of a feature list
    // The AVP Code of Feature-List-ID is 629.
    FeatureListID featureListID(1u);
    supportedFeatures.setFeatureListID(featureListID);

    // [2.2.7.3] Populate required parameter "Feature-List".
    // Set the Feature-List AVP.
    // The data type of Feature-List is Unsigned32.
    // This AVP contains a bit mask indicating the supported features
    // of an application.
    // The AVP Code of Feature-List is 630.
    FeatureList featureList(1u);
    supportedFeatures.setFeatureList(featureList);

    pua.addSupportedFeatures(supportedFeatures);

    //ErrorMessage errMsg("failed");
    //FailedAVP failedAVP;
    //failedAVP.addExtra(errMsg);
    //pua.addFailedAVP(failedAVP);
    //open type AVP. any AVP can be passed

    // [2.2.8] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo  proxyInfo1;
    //ProxyInfo  proxyInfo2;

    // [2.2.8.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info 
    // AVP.
    // The AVP Code of Proxy-Info is 280.
    //ProxyHost proxyHost1("proxyHost1");
    //ProxyHost proxyHost2("proxyHost1");

    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // [2.2.8.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as opaque
    //  data
    // The AVP Code of Proxy-State is 33.
    //ProxyState proxyState1("proxyState1");
    //ProxyState proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // Stack sets this AVP.
    // Application should not set this AVP
    //pua.addProxyInfo(proxyInfo1);
    //pua.addProxyInfo(proxyInfo2);

    // [2.2.9] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the  message.
    // The AVP Code of Route-Record is 282.
    // Stack sets this AVP.
    // Application should not set this AVP
    // int cntRouteRcd = pureq.countRouteRecord();
    // if(cntRouteRcd)
    // {
    //     const RouteRecord& rr1 = pureq.getRouteRecord(0);
    //     const RouteRecord& rr2 = pureq.getRouteRecord(1);
    //     pua.addRouteRecord(rr1);
    //     pua.addRouteRecord(rr2);
    // }

    // [3] Use appropriate application specific logic to Send object
    cout << endl << pua;
    apiSh.Send(pua, sIdxSh, SH_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Push notification request to the 
 *      diameter stack. This creates the PushNotificationRequest
 *      object, populate the AVPs and sends the message to the stack.
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
int SendPushNotificationRequest()
{
    // [1] Create PushNotificationRequest object.
    PushNotificationRequest pnr(false,false);

    // [2] Insert data in the created PushNotificationRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    apiSh.AllocateSessionIndex(10000, sIdxSh, sessIdStringSh);
    printf("\tSession Index: %d\n", sIdxSh);
    pnr.setSessionId(SessionId(sessIdStringSh));

    // [2.2] Populate required Mandatories.
    // [2.2.1] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.1.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may be
    // sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates that
    // this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(10415u);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // [2.2.1.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId authApplicationId(SH_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.2.1.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);
    pnr.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // [2.2.2] Populate required parameter "Auth-Session-State".
    // Set the Auth-Session-State AVP.
    // The data type of Vendor-Specific-Application-Id is Enumerated.
    // This AVP specifies whether state is maintained for a particular session
    // The AVP Code of Auth-Session-State is 277.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    pnr.setAuthSessionState(authSessionState);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost originHost(GetOriginHost());
    pnr.setOriginHost(originHost);

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm originRealm(GetOriginRealm());
    pnr.setOriginRealm(originRealm);

    // [2.2.5] Populate required parameter "Destination-Realm".
    // Set the Destination-Realm AVP.
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    DestinationRealm destinationRealm(GetDestinationRealm());
    pnr.setDestinationRealm(destinationRealm);

    // [2.2.6] Populate required parameter "User-Identity".
    // Set the User-Identity AVP.
    // The data type of Destination-Realm is Grouped.
    // This AVP contains either Public Identity or an MSISDN AVP.
    // The AVP Code of User-Identity is 700.
    UserIdentity userIdentity;

    // [2.2.6.1] Populate required parameter "Public-Identity".
    // Set the Public-Identity AVP.
    // The data type of Public-Identity is UTF8String.
    // This AVP contains the public identity of a user in the IMS
    // The AVP Code of Public-Identity is 601.
    PublicIdentity publicIdentity("sip:user@3gppnetwork.com");
    userIdentity.setPublicIdentity(publicIdentity);

    // [2.2.6.2] Populate required parameter "MSISDN".
    // Set the MSISDN AVP.
    // The data type of MSISDN is OctetString.
    // This AVP contains an MSISDN, in international number format as 
    // described in ITU-T Rec E.164, encoded as a TBCD-string, i.e. 
    // digits from 0 through 9 are encoded 0000 to 1001; 1111 is used
    // as a filler when there is an odd number of digits; bits 8 to 5 
    // of octet n encode digit 2n; bits 4 to 1 of octet n encode digit
    // 2(n-1)+1.
    // The AVP Code of MSISDN is 701.
    MSISDN msisdn("3217260686");
    userIdentity.setMSISDN(msisdn);

    pnr.setUserIdentity(userIdentity);

    // [2.2.7] Populate required parameter "User-Data".
    // Set the User-Data AVP.ProfileUpdateAnswer
    // The data type of User-Data is OctateString.
    // This AVP contains the user data requested in the PUR and SNR 
    // operations and the data to be modified in the UPR operation
    // The AVP Code of User-data is 702.
    ShUserData userData(subsProfile);
    pnr.setShUserData(userData);

    // [2.2.8] Populate optional parameter "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of User-Data is DiameterIdentity.
    // This AVP contains the Host the message is to be routed to.
    // The absence of the Destination-Host AVP will cause a message to be
    // sent to any Diameter server supporting the application within the
    // realm specified in Destination-Realm AVP.
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    pnr.setDestinationHost(destinationHost);

    // [2.2.9] Populate optional parameter "Supported-Features".
    // Set the Supported-Features AVP.
    // The data type of User-Data is Grouped.
    // If this AVP is present it may inform the destination host about
    // the features that the origin host supports.
    // The AVP Code of Supported-Features is 628.
    SupportedFeatures supportedFeatures;

    // [2.2.9.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId1(10415u);
    supportedFeatures.setVendorId(vendorId1);

    // [2.2.9.2] Populate required parameter "Feature-List-ID".
    // Set the Feature-List-ID AVP.
    // The data type of Feature-List-ID is Unsigned32.
    // This AVP contains the identity of a feature list
    // The AVP Code of Feature-List-ID is 629.
    FeatureListID featureListID(1u);
    supportedFeatures.setFeatureListID(featureListID);

    // [2.2.9.3] Populate required parameter "Feature-List".
    // Set the Feature-List AVP.
    // The data type of Feature-List is Unsigned32.
    // This AVP contains a bit mask indicating the supported features
    // of an application.
    // The AVP Code of Feature-List is 630.
    FeatureList featureList(1u);
    supportedFeatures.setFeatureList(featureList);

    pnr.addSupportedFeatures(supportedFeatures);

    // [2.2.10] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // [2.2.10.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info 
    // AVP.
    // The AVP Code of Proxy-Info is 280.
    //ProxyHost proxyHost1("proxyHost1"), proxyHost2("proxyHost1");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // [2.2.10.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as opaque
    //  data
    // The AVP Code of Proxy-State is 33.
    //ProxyState proxyState1("proxyState1"), proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // Stack sets this AVP.
    // Application should not set this AVP
    //pnr.addProxyInfo(proxyInfo1);
    //pnr.addProxyInfo(proxyInfo2);

    // [2.2.11] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the  message.
    // The AVP Code of Route-Record is 282.
    //RouteRecord routeRecord1("routeRecord1"),routeRecord2("routeRecord2");
    // Stack sets this AVP.
    // Application should not set this AVP
    // pnr.addRouteRecord(routeRecord1);
    // pnr.addRouteRecord(routeRecord2);

    // [3] Use appropriate application specific logic to Send object

    cout << pnr;
    apiSh.Send(pnr, sIdxSh, SH_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the Push notification
 *      request sent by the Application. This creates the
 *      PushNotificationAnswer object, populate the AVPs and sends
 *      the message to the app.
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
int SendPushNotificationAnswer(const diameter::CommandImpl* impl)
{
    // [1] Create PushNotificationAnswer object.
    PushNotificationAnswer pna(false,false);

    PushNotificationRequest pnreq(*impl);

    //const VendorSpecificApplicationId & vsid = 
    //      pnreq.getVendorSpecificApplicationId();
    //const SupportedFeatures & sf = pnreq.getSupportedFeatures(1);
    //const ProxyInfo & pi1 = pnreq.getProxyInfo(1);
    //const ProxyInfo & pi2 = pnreq.getProxyInfo(2);

    // [2] Insert data in the created PushNotificationAnswer object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed paramete "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId& sid = pnreq.getSessionId();
    pna.setSessionId(sid);

    // [2.2] Populate required Mandatories.
    // [2.2.1] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.1.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    vendorSpecificApplicationId1.addVendorId(VendorId(10415u));

    // [2.2.1.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication
    // and Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    vendorSpecificApplicationId1.
        setAuthApplicationId(AuthApplicationId(SH_INTERFACE_APP_ID));

    // [2.2.1.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    // vendorSpecificApplicationId1.setAcctApplicationId(AcctApplicationId(2));
    pna.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // [2.2.2] Populate required parameter "Auth-Session-State".
    // Set the Auth-Session-State AVP.
    // The data type of Vendor-Specific-Application-Id is Enumerated.
    // This AVP specifies whether state is maintained for a particular session
    // The AVP Code of Auth-Session-State is 277.
    const AuthSessionState& authSessSt = pnreq.getAuthSessionState();
    pna.setAuthSessionState(authSessSt);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    const OriginHost& oh = pnreq.getOriginHost();
    pna.setOriginHost(oh);

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    const OriginRealm& orm = pnreq.getOriginRealm();
    pna.setOriginRealm(orm);

    // [2.2.5] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    pna.setResultCode(ResultCode(2001u));

    // [2.2.6] Populate required parameter "Experimental-Result".
    // Set the Experimental-Result AVP.
    // The data type of Experimental-Result is Grouped.
    // This AVP indicates whether a particular vendor-specific request 
    // was completed successfully or whether an error occurred.
    // The AVP Code of Experimental-Result is 297.
    // ResultCode AVP is already been set, both should not be set.
    //ExperimentalResult experimentalResult;

    // [2.2.6.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and
    // indicates that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    //experimentalResult.setVendorId(VendorId(10415u));

    // [2.2.6.2] Populate required parameter "Experimental-Result-Code".
    // Set the Experimental-Result-Code AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP contains a vendor-assigned value representing the result of
    // processing the request.
    // The AVP Code of Experimental-Result-Code is 298.
    //ExperimentalResultCode experimentalResultCode(2001u);
    //experimentalResult.setExperimentalResultCode(experimentalResultCode);

    //pna.setExperimentalResult(experimentalResult);

    // [2.2.7] Populate optional parameter "Supported-Features".
    // Set the Supported-Features AVP.
    // The data type of User-Data is Grouped.
    // If this AVP is present it may inform the destination host about
    // the features that the origin host supports.
    // The AVP Code of Supported-Features is 628.
    SupportedFeatures supportedFeatures;

    // [2.2.7.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    supportedFeatures.setVendorId(VendorId(10415u));

    // [2.2.7.2] Populate required parameter "Feature-List-ID".
    // Set the Feature-List-ID AVP.
    // The data type of Feature-List-ID is Unsigned32.
    // This AVP contains the identity of a feature list
    // The AVP Code of Feature-List-ID is 629.
    supportedFeatures.setFeatureListID(FeatureListID(1u));

    // [2.2.7.3] Populate required parameter "Feature-List".
    // Set the Feature-List AVP.
    // The data type of Feature-List is Unsigned32.
    // This AVP contains a bit mask indicating the supported features
    // of an application.
    // The AVP Code of Feature-List is 630.
    supportedFeatures.setFeatureList(FeatureList(1u));
    pna.addSupportedFeatures(supportedFeatures);

    // [2.2.8] Populate required parameter "Failed-AVP".
    // Set the Failed-AVP AVP.
    // The data type of Feature-List is Grouped.
    // This AVP provides debugging information in cases where a request is
    // rejected or not fully processed due to erroneous information in a
    // specific AVP. The value of the Result-Code AVP will provide 
    // information on the reason for the Failed-AVP AVP.
    // The AVP Code of Feature-List is 297.
    // FailedAVP failedAVP;
    // pna.addFailedAVP(failedAVP);

    // [2.2.9] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo proxyInfo1;
    //ProxyInfo proxyInfo2;

    // [2.2.9.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info 
    // AVP.
    // The AVP Code of Proxy-Info is 280.
    //proxyInfo1.setProxyHost(ProxyHost("proxyHost1"));
    //proxyInfo2.setProxyHost(ProxyHost("proxyHost2"));

    // [2.2.9.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated
    // as opaque data
    // The AVP Code of Proxy-State is 33.
    //proxyInfo1.setProxyState(ProxyState("proxyState1"));
    //proxyInfo2.setProxyState(ProxyState("proxyState2"));

    // Stack sets this AVP.
    // Application should not set this AVP
    // pna.addProxyInfo(proxyInfo1);
    // pna.addProxyInfo(proxyInfo2);

    // [2.2.10] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the  message.
    // The AVP Code of Route-Record is 282.
    for(int i =0; i < pnreq.countRouteRecord(); i++)
    {
      const RouteRecord & rRec = pnreq.getRouteRecord(i);
    // Stack sets this AVP.
    // Application should not set this AVP
    // pna.addRouteRecord(rRec);
    }

    // [3] Use appropriate application specific logic to Send object

    cout << pna;
    apiSh.Send(pna, sIdxSh, SH_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Subscriber notification
 *      request to the stack. This creates the
 *      SubscribeNotificationsRequest object, populate the AVPs and sends
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
int SendSubscribeNotificationsRequest()
{
    // [1] Create SubscribeNotificationsRequest object.
    SubscribeNotificationsRequest snr(false,false);

    // [2] Insert data in the created SubscribeNotificationsRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    apiSh.AllocateSessionIndex(10000, sIdxSh, sessIdStringSh);
    printf("\tSession Index: %d\n", sIdxSh);
    snr.setSessionId(SessionId(sessIdStringSh));

    // [2.2] Populate required Mandatories.
    // [2.2.1] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.1.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    vendorSpecificApplicationId1.addVendorId(VendorId(10415u));

    // [2.2.1.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication
    // and Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    vendorSpecificApplicationId1.
        setAuthApplicationId(AuthApplicationId(SH_INTERFACE_APP_ID));

    // [2.2.1.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    // vendorSpecificApplicationId1.setAcctApplicationId(AcctApplicationId(2));
    snr.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // [2.2.2] Populate required parameter "Auth-Session-State".
    // Set the Auth-Session-State AVP.
    // The data type of Vendor-Specific-Application-Id is Enumerated.
    // This AVP specifies whether state is maintained for a particular session
    // The AVP Code of Auth-Session-State is 277.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    snr.setAuthSessionState(authSessionState);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    snr.setOriginHost(OriginHost(GetOriginHost()));

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    snr.setOriginRealm(OriginRealm(GetOriginRealm()));

    // [2.2.5] Populate required parameter "Destination-Realm".
    // Set the Destination-Realm AVP.
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    snr.setDestinationRealm(DestinationRealm(GetDestinationRealm()));

    // [2.2.6] Populate required parameter "User-Identity".
    // Set the User-Identity AVP.
    // The data type of Destination-Realm is Grouped.
    // This AVP contains either Public Identity or an MSISDN AVP.
    // The AVP Code of User-Identity is 700.
    UserIdentity userIdentity;

    // [2.2.6.1] Populate required parameter "Public-Identity".
    // Set the Public-Identity AVP.
    // The data type of Public-Identity is UTF8String.
    // This AVP contains the public identity of a user in the IMS
    // The AVP Code of Public-Identity is 601.
    userIdentity.setPublicIdentity(PublicIdentity("sip:user@3gppnetwork.com"));

    // [2.2.6.2] Populate required parameter "MSISDN".
    // Set the MSISDN AVP.
    // The data type of MSISDN is OctetString.
    // This AVP contains an MSISDN, in international number format as 
    // described in ITU-T Rec E.164, encoded as a TBCD-string, i.e. 
    // digits from 0 through 9 are encoded 0000 to 1001; 1111 is used
    // as a filler when there is an odd number of digits; bits 8 to 5 
    // of octet n encode digit 2n; bits 4 to 1 of octet n encode digit
    // 2(n-1)+1.
    // The AVP Code of MSISDN is 701.
    userIdentity.setMSISDN(MSISDN("3217260686"));
    snr.setUserIdentity(userIdentity);

    // [2.2.7] Populate required parameter "Subs-Req-Type".
    // Set the Subs-Req-Type AVP.
    // The data type of Subs-Req-Type is Enumerated.
    // This AVP indicates the type of the subscription-to-notifications
    // request. The following values are defined:
    // 1) Subscribe
    // 2) Unsubscribe
    // The AVP Code of Subs-Req-Type is 705.
    snr.setSubsReqType(SubsReqType(SubsReqType::Subscribe));

    // [2.2.8] Populate required parameter "Data-Reference".
    // Set the Data-Reference AVP.
    // The data type of Data-Reference is Enumerated.
    // This AVP indicates the type of the requested user data 
    // in the operation UDR and SNR.
    // The AVP Code of Data-Reference is 703.
    snr.setDataReference(DataReference(DataReference::RepositoryData));

    // [2.2.9] Populate optional parameter "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of User-Data is DiameterIdentity.
    // This AVP contains the Host the message is to be routed to.
    // The absence of the Destination-Host AVP will cause a message to be
    // sent to any Diameter server supporting the application within the
    // realm specified in Destination-Realm AVP.
    // The AVP Code of Destination-Host is 293.
    snr.setDestinationHost(DestinationHost(GetDestinationHost()));

    // [2.2.10] Populate optional parameter "Supported-Features".
    // Set the Supported-Features AVP.
    // The data type of User-Data is Grouped.
    // If this AVP is present it may inform the destination host about
    // the features that the origin host supports.
    // The AVP Code of Supported-Features is 628.
    SupportedFeatures supportedFeatures;

    // [2.2.10.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    supportedFeatures.setVendorId(VendorId(10415u));

    // [2.2.10.2] Populate required parameter "Feature-List-ID".
    // Set the Feature-List-ID AVP.
    // The data type of Feature-List-ID is Unsigned32.
    // This AVP contains the identity of a feature list
    // The AVP Code of Feature-List-ID is 629.
    supportedFeatures.setFeatureListID(FeatureListID(1u));

    // [2.2.10.3] Populate required parameter "Feature-List".
    // Set the Feature-List AVP.
    // The data type of Feature-List is Unsigned32.
    // This AVP contains a bit mask indicating the supported features
    // of an application.
    // The AVP Code of Feature-List is 630.
    supportedFeatures.setFeatureList(FeatureList(1u));

    snr.addSupportedFeatures(supportedFeatures);

    // [2.2.11] Populate required parameter "Service-Indication".
    // Set the Service-Indication AVP.
    // The data type of Service-Indication is OctateString.
    // If this AVP contains the Service Indication that identifies
    // a service in an AS.
    // The AVP Code of Service-Indication is 704.
    snr.setServiceIndication(ServiceIndication("Video Sharing"));

    // [2.2.12] Populate required parameter "Server-Name".
    // Set the Server-Name AVP.
    // The data type of Server-Name is UTF8String.
    // If this AVP contains a SIP-URL (as defined in IETF RFC 3261 and IETF
    // RFC 2396), used to identify a SIP server (e.g. S-CSCF name).
    // The AVP Code of Server-Name is 602.
    snr.setServerName(ServerName("sip:cscf@3gppnetwork.com"));

    // [2.2.13] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // [2.2.13.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info 
    // AVP.
    // The AVP Code of Proxy-Info is 280.
    //proxyInfo1.setProxyHost(ProxyHost("proxyHost1"));
    //proxyInfo2.setProxyHost(ProxyHost("proxyHost2"));

    // [2.2.13.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated
    // as opaque data
    // The AVP Code of Proxy-State is 33.
    //proxyInfo1.setProxyState(ProxyState("proxyState1"));
    //proxyInfo2.setProxyState(ProxyState("proxyState2"));

    // Stack sets this AVP.
    // Application should not set this AVP
    // snr.addProxyInfo(proxyInfo1);
    // snr.addProxyInfo(proxyInfo2);

    // [2.2.14] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the  message.
    // The AVP Code of Route-Record is 282.
    //RouteRecord routeRecord1("routeRecord1"),routeRecord2("routeRecord2");

    // Stack sets this AVP.
    // Application should not set this AVP
    // snr.addRouteRecord(routeRecord1);
    // snr.addRouteRecord(routeRecord2);

    // [3] Use appropriate application specific logic to Send object

    cout << snr;
    apiSh.Send(snr, sIdxSh, SH_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to Subscriber notification
 *      request made by the application. This creates the
 *      SubscribeNotificationsAnswer object, populate the AVPs and sends
 *      the message to the application.
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
int SendSubscribeNotificationsAnswer(const diameter::CommandImpl* impl)
{
    // [1] Create SubscribeNotificationsAnswer object.
    SubscribeNotificationsAnswer sna(false,false);

    SubscribeNotificationsRequest snreq(*impl);

    const AuthSessionState& authSessSt = snreq.getAuthSessionState();
    //const VendorSpecificApplicationId & vsid = snreq.
    //    getVendorSpecificApplicationId();
    //const SupportedFeatures& sf = snreq.getSupportedFeatures(1);
    //const ProxyInfo &proxyInfo11 = snreq.getProxyInfo(1);
    //const ProxyInfo& proxyInfo12 = snreq.getProxyInfo(2);

    // [2] Insert data in the created SubscribeNotificationsAnswer object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId& sid = snreq.getSessionId();
    sna.setSessionId(sid);

    // [2.2] Populate required Mandatories.
    // [2.2.1] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.1.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    vendorSpecificApplicationId1.addVendorId(VendorId(10415u));

    // [2.2.1.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication
    // and Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    vendorSpecificApplicationId1.
        setAuthApplicationId(AuthApplicationId(SH_INTERFACE_APP_ID));

    // [2.2.1.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    // vendorSpecificApplicationId1.setAcctApplicationId(AcctApplicationId(2));
    sna.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // [2.2.2] Populate required parameter "Auth-Session-State".
    // Set the Auth-Session-State AVP.
    // The data type of Vendor-Specific-Application-Id is Enumerated.
    // This AVP specifies whether state is maintained for a particular session
    // The AVP Code of Auth-Session-State is 277.
    sna.setAuthSessionState(authSessSt);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    const OriginHost& oh = snreq.getOriginHost();
    sna.setOriginHost(oh);

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    const OriginRealm& orealm = snreq.getOriginRealm();
    sna.setOriginRealm(orealm);

    // [2.2.5] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    sna.setResultCode(ResultCode(2001u));

    // [2.2.6] Populate required parameter "Experimental-Result".
    // Set the Experimental-Result AVP.
    // The data type of Experimental-Result is Grouped.
    // This AVP indicates whether a particular vendor-specific request 
    // was completed successfully or whether an error occurred.
    // The AVP Code of Experimental-Result is 297.
    // ResultCode and ExperimentalResult both shouldnot be set.
    //ExperimentalResult experimentalResult;

    // [2.2.6.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    //experimentalResult.setVendorId(VendorId(10415u));

    // [2.2.6.2] Populate required parameter "Experimental-Result-Code".
    // Set the Experimental-Result-Code AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP contains a vendor-assigned value representing the result of
    // processing the request.
    // The AVP Code of Experimental-Result-Code is 298.
    //ExperimentalResultCode experimentalResultCode(100u);
    //experimentalResult.setExperimentalResultCode(experimentalResultCode);

    //sna.setExperimentalResult(experimentalResult);

    // [2.2.7] Populate optional parameter "Supported-Features".
    // Set the Supported-Features AVP.
    // The data type of User-Data is Grouped.
    // If this AVP is present it may inform the destination host about
    // the features that the origin host supports.
    // The AVP Code of Supported-Features is 628.
    SupportedFeatures supportedFeatures;

    // [2.2.7.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    supportedFeatures.setVendorId(VendorId(10415u));

    // [2.2.7.2] Populate required parameter "Feature-List-ID".
    // Set the Feature-List-ID AVP.
    // The data type of Feature-List-ID is Unsigned32.
    // This AVP contains the identity of a feature list
    // The AVP Code of Feature-List-ID is 629.
    supportedFeatures.setFeatureListID(FeatureListID(1u));

    // [2.2.7.3] Populate required parameter "Feature-List".
    // Set the Feature-List AVP.
    // The data type of Feature-List is Unsigned32.
    // This AVP contains a bit mask indicating the supported features
    // of an application.
    // The AVP Code of Feature-List is 630.
    supportedFeatures.setFeatureList(FeatureList(1u));
    sna.addSupportedFeatures(supportedFeatures);

    // [2.2.8] Populate required parameter "Failed-AVP".
    // Set the Failed-AVP AVP.
    // The data type of Feature-List is Grouped.
    // This AVP provides debugging information in cases where a request is
    // rejected or not fully processed due to erroneous information in a
    // specific AVP. The value of the Result-Code AVP will provide 
    // information on the reason for the Failed-AVP AVP.
    // The AVP Code of Feature-List is 297.
    // FailedAVP failedAVP;
    // sna.addFailedAVP(failedAVP);

    // [2.2.9] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo proxyInfo1;
    //ProxyInfo proxyInfo2;

    // [2.2.9.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info 
    // AVP.
    // The AVP Code of Proxy-Info is 280.
    //proxyInfo1.setProxyHost(ProxyHost("proxyHost1"));
    //proxyInfo2.setProxyHost(ProxyHost("proxyHost2"));

    // [2.2.9.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as
    // opaque data
    // The AVP Code of Proxy-State is 33.
    //proxyInfo1.setProxyState(ProxyState("proxyState1"));
    //proxyInfo2.setProxyState(ProxyState("proxyState2"));

    // Stack sets this AVP.
    // Application should not set this AVP
    // sna.addProxyInfo(proxyInfo1);
    // sna.addProxyInfo(proxyInfo2);

    // [2.2.10] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the  message.
    // The AVP Code of Route-Record is 282.
    for(int i =0; i < snreq.countRouteRecord(); i++)
    {
       const RouteRecord & rRec = snreq.getRouteRecord(i);

       // Stack sets this AVP.
      // Application should not set this AVP
      // sna.addRouteRecord(rRec);
    }

    // [3] Use appropriate application specific logic to Send object

    cout << sna;
    apiSh.Send(sna, sIdxSh, SH_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the User data request to the stack.
 *      This creates the UserDataRequest object, populate the AVPs
 *      and sends the message to the application.
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
int SendUserDataRequest()
{
    // [1] Create UserDataRequest object.
    UserDataRequest udr(false,false);

    // [2] Insert data in the created UserDataRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    apiSh.AllocateSessionIndex(10000, sIdxSh, sessIdStringSh);
    printf("\tSession Index: %d\n", sIdxSh);
    udr.setSessionId(SessionId(sessIdStringSh));

    // [2.2] Populate required Mandatories.
    // [2.2.1] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.1.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    vendorSpecificApplicationId1.addVendorId(VendorId(10415u));

    // [2.2.1.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication
    // and Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    vendorSpecificApplicationId1.
        setAuthApplicationId(AuthApplicationId(SH_INTERFACE_APP_ID));

    // Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    vendorSpecificApplicationId1.setAcctApplicationId(AcctApplicationId(2));
    udr.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // [2.2.2] Populate required parameter "Auth-Session-State".
    // Set the Auth-Session-State AVP.
    // The data type of Vendor-Specific-Application-Id is Enumerated.
    // This AVP specifies whether state is maintained for a particular session
    // The AVP Code of Auth-Session-State is 277.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    udr.setAuthSessionState(authSessionState);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    udr.setOriginHost(OriginHost(GetOriginHost()));

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    udr.setOriginRealm(OriginRealm(GetOriginRealm()));

    // [2.2.5] Populate required parameter "Destination-Realm".
    // Set the Destination-Realm AVP.
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    udr.setDestinationRealm(DestinationRealm(GetDestinationRealm()));

    // [2.2.6] Populate required parameter "User-Identity".
    // Set the User-Identity AVP.
    // The data type of Destination-Realm is Grouped.
    // This AVP contains either Public Identity or an MSISDN AVP.
    // The AVP Code of User-Identity is 700.
    UserIdentity userIdentity;

    // [2.2.6.1] Populate required parameter "Public-Identity".
    // Set the Public-Identity AVP.
    // The data type of Public-Identity is UTF8String.
    // This AVP contains the public identity of a user in the IMS
    // The AVP Code of Public-Identity is 601.
    userIdentity.setPublicIdentity(PublicIdentity("sip:user@3gppnetwork.com"));

    // [2.2.6.2] Populate required parameter "MSISDN".
    // Set the MSISDN AVP.
    // The data type of MSISDN is OctetString.
    // This AVP contains an MSISDN, in international number format as 
    // described in ITU-T Rec E.164, encoded as a TBCD-string, i.e. 
    // digits from 0 through 9 are encoded 0000 to 1001; 1111 is used
    // as a filler when there is an odd number of digits; bits 8 to 5 
    // of octet n encode digit 2n; bits 4 to 1 of octet n encode digit
    // 2(n-1)+1.
    // The AVP Code of MSISDN is 701.
    userIdentity.setMSISDN(MSISDN("3217260686"));
    udr.setUserIdentity(userIdentity);

    // [2.2.7] Populate required parameter "Data-Reference".
    // Set the Data-Reference AVP.
    // The data type of Data-Reference is Enumerated.
    // This AVP indicates the type of the requested user data 
    // in the operation UDR and SNR.
    // The AVP Code of Data-Reference is 703.
    udr.setDataReference(DataReference(DataReference::Value(0)));

    // [2.2.8] Populate optional parameter "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of User-Data is DiameterIdentity.
    // This AVP contains the Host the message is to be routed to.
    // The absence of the Destination-Host AVP will cause a message to be
    // sent to any Diameter server supporting the application within the
    // realm specified in Destination-Realm AVP.
    // The AVP Code of Destination-Host is 293.
    udr.setDestinationHost(DestinationHost(GetDestinationHost()));

    // [2.2.9] Populate optional parameter "Supported-Features".
    // Set the Supported-Features AVP.
    // The data type of User-Data is Grouped.
    // If this AVP is present it may inform the destination host about
    // the features that the origin host supports.
    // The AVP Code of Supported-Features is 628.
    SupportedFeatures supportedFeatures;

    // [2.2.9.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    supportedFeatures.setVendorId(VendorId(10415u));

    // [2.2.9.2] Populate required parameter "Feature-List-ID".
    // Set the Feature-List-ID AVP.
    // The data type of Feature-List-ID is Unsigned32.
    // This AVP contains the identity of a feature list
    // The AVP Code of Feature-List-ID is 629.
    supportedFeatures.setFeatureListID(FeatureListID(1u));

    // [2.2.9.3] Populate required parameter "Feature-List".
    // Set the Feature-List AVP.
    // The data type of Feature-List is Unsigned32.
    // This AVP contains a bit mask indicating the supported features
    // of an application.
    // The AVP Code of Feature-List is 630.
    supportedFeatures.setFeatureList(FeatureList(1u));
    udr.addSupportedFeatures(supportedFeatures);

    // [2.2.10] Populate required parameter "Server-Name".
    // Set the Server-Name AVP.
    // The data type of Server-Name is UTF8String.
    // If this AVP contains a SIP-URL (as defined in IETF RFC 3261 and IETF
    // RFC 2396), used to identify a SIP server (e.g. S-CSCF name).
    // The AVP Code of Server-Name is 602.
    udr.setServerName(ServerName("sip:cscf@3gppnetwork.com"));

    // [2.2.11] Populate required parameter "Service-Indication".
    // Set the Service-Indication AVP.
    // The data type of Service-Indication is OctateString.
    // If this AVP contains the Service Indication that identifies
    // a service in an AS.
    // The AVP Code of Service-Indication is 704.
    udr.setServiceIndication(ServiceIndication("Video Sharing"));

    // [2.2.12] Populate required parameter "Identity-Set".
    // Set the Identity-Set AVP.
    // The data type of Identity-Set is Enumerated.
    // If this AVP indicates the requested set of IMS Public Identities.
    // The following values are defined:
    // ALL_IDENTITIES (0)
    // REGISTERED_IDENTITIES (1)
    // IMPLICIT_IDENTITIES (2)
    // The AVP Code of Identity-Set is 708.
    udr.setIdentitySet(IdentitySet(IdentitySet::ALL_IDENTITIES));

    // [2.2.13] Populate required parameter "Requested-Domain".
    // Set the Requested-Domain AVP.
    // The data type of Requested-Domain is Enumerated.
    // If this AVP indicates the access domain for which certain data 
    // (e.g. user state) are requested. The following values are defined:
    // CS-Domain (0) -> The requested data apply to the CS domain.
    // PS-Domain (1) -> The requested data apply to the PS domain.
    // The AVP Code of Requested-Domain is 706.
    udr.setRequestedDomain(RequestedDomain(RequestedDomain::Value(0)));

    // [2.2.14] Populate required parameter "Current-Location".
    // Set the Current-Location AVP.
    // The data type of Current-Location is Enumerated.
    // If this AVP indicates whether an active location retrieval has 
    // to be initiated or not:
    // DoNotNeedInitiateActiveLocationRetrieval (0)
    // InitiateActiveLocationRetrieval (1)
    // The AVP Code of Current-Location is 707.
    udr.setCurrentLocation(CurrentLocation(CurrentLocation::
                          DoNotNeedInitiateActiveLocationRetrieval));

    // [2.2.15] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // [2.2.15.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info 
    // AVP.
    // The AVP Code of Proxy-Info is 280.
    //proxyInfo1.setProxyHost(ProxyHost("nemo"));
    //proxyInfo2.setProxyHost(ProxyHost("nemo"));

    // [2.2.15.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated
    // as opaque data
    // The AVP Code of Proxy-State is 33.
    //proxyInfo1.setProxyState(ProxyState("proxyState1"));
    //proxyInfo2.setProxyState(ProxyState("proxyState2"));

    // Stack sets this AVP.
    // Application should not set this AVP
    // udr.addProxyInfo(proxyInfo1);
    // udr.addProxyInfo(proxyInfo2);

    // [2.2.16] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the  message.
    // The AVP Code of Route-Record is 282.
    //RouteRecord routeRecord1("nemocl"), routeRecord2("jerry");

    // Stack sets this AVP.
    // Application should not set this AVP
    // udr.addRouteRecord(routeRecord1);
    // udr.addRouteRecord(routeRecord2);

    // [3] Use appropriate application specific logic to Send object

    cout << udr;
    apiSh.Send(udr, sIdxSh, SH_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the User data request
 *      made by the application. This creates the UserDataAnswer
 *     object, populate the AVPs and sends the message to the application.
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
int SendUserDataAnswer(const diameter::CommandImpl* impl)
{
    // [1] Create UserDataAnswer object.
    UserDataAnswer uda(false,false);

    UserDataRequest udreq(*impl);

    //for (int i = 0; i < udreq.countRouteRecord(); i++)
    //{
    //    const RouteRecord& rr = udreq.getRouteRecord(i);
    //}

    // [2] Insert data in the created UserDataAnswer object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId& sid = udreq.getSessionId();
    uda.setSessionId(sid);

    // [2.2] Populate required Mandatories.
    // [2.2.1] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.1.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    vendorSpecificApplicationId1.addVendorId(VendorId(10415u));

    // [2.2.1.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication
    // and Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    vendorSpecificApplicationId1.
        setAuthApplicationId(AuthApplicationId(SH_INTERFACE_APP_ID));

    // [2.2.1.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    // vendorSpecificApplicationId1.setAcctApplicationId(AcctApplicationId(2));
    uda.setVendorSpecificApplicationId( vendorSpecificApplicationId1);

    // [2.2.2] Populate required parameter "Auth-Session-State".
    // Set the Auth-Session-State AVP.
    // The data type of Vendor-Specific-Application-Id is Enumerated.
    // This AVP specifies whether state is maintained for a particular session
    // The AVP Code of Auth-Session-State is 277.
    const AuthSessionState& asessionstate = udreq.getAuthSessionState();
    uda.setAuthSessionState(asessionstate);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    const OriginHost& oh = udreq.getOriginHost();
    uda.setOriginHost(oh);

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    const OriginRealm& orm = udreq.getOriginRealm();
    uda.setOriginRealm(orm);

    // [2.2.5] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    uda.setResultCode(ResultCode(2001u));

    // [2.2.6] Populate required parameter "Experimental-Result".
    // Set the Experimental-Result AVP.
    // The data type of Experimental-Result is Grouped.
    // This AVP indicates whether a particular vendor-specific request 
    // was completed successfully or whether an error occurred.
    // The AVP Code of Experimental-Result is 297.
    // ResultCode AVP is already been set, it is not required to set.
    //ExperimentalResult experimentalResult;

    // [2.2.6.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    //experimentalResult.setVendorId(VendorId(10415u));

    // [2.2.6.2] Populate required parameter "Experimental-Result-Code".
    // Set the Experimental-Result-Code AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP contains a vendor-assigned value representing the result of
    // processing the request.
    // The AVP Code of Experimental-Result-Code is 298.
    //ExperimentalResultCode experimentalResultCode(2001u);
    //experimentalResult.setExperimentalResultCode(experimentalResultCode);

    //uda.setExperimentalResult(experimentalResult);

    // [2.2.8] Populate required parameter "User-Data".
    // Set the User-Data AVP.
    // The data type of User-Data is OctateString.
    // This AVP contains the user data requested in the PUR and SNR 
    // operations and the data to be modified in the UPR operation
    // The AVP Code of User-data is 702.
    ShUserData userData(subsProfile);
    uda.setShUserData(userData);

    //SupportedFeatures supportedFeatures;

    //supportedFeatures.setVendorId(VendorId(10415u));
    //supportedFeatures.setFeatureListID(FeatureListID(1u));
    //supportedFeatures.setFeatureList(FeatureList(1u));
    //uda.addSupportedFeatures(sf);

    //FailedAVP failedAVP;
    //uda.addFailedAVP(failedAVP);

    //ProxyInfo proxyInfo1,proxyInfo2;
    //proxyInfo1.setProxyHost(ProxyHost("proxyHost1"));
    //proxyInfo2.setProxyHost(ProxyHost("proxyHost2"));
    //proxyInfo1.setProxyState(ProxyState("proxyState1"));
    //proxyInfo2.setProxyState(ProxyState("proxyState2"));
    //uda.addProxyInfo(pInfo1);
    //uda.addProxyInfo(pInfo2);

    // Stack sets this AVP.
    // Application should not set this AVP
    //uda.addRouteRecord(rr1);
    //uda.addRouteRecord(rr2);

    // [3] Use appropriate application specific logic to Send object

    cout << uda;
    apiSh.Send(uda, sIdxSh, SH_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

