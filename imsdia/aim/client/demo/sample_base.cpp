/*********************************-*-C-*-************************************
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
 * LOG: Revision 3.3  2009/07/24 09:35:14  rajeshak
 * LOG: Demo Application changed to include new Custom AVP in DWR message.
 * LOG:
 * LOG: Revision 3.2  2008/04/16 11:53:14  avinashks
 * LOG: Changes done for Accounting Application to support agents.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:00  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.7  2007/01/04 11:43:25  nvijikumar
 * LOG: Changes to send defferent types of Accounting Req.
 * LOG:
 * LOG: Revision 2.6  2006/10/31 16:30:23  kamakshilk
 * LOG: Accounting answer build changed. Added Acct-App-Id AVP
 * LOG:
 * LOG: Revision 2.5  2006/10/31 16:26:51  kamakshilk
 * LOG: Accounting Request build changed. Added Acct-App-Id AVP
 * LOG:
 * LOG: Revision 2.4  2006/10/27 07:39:46  kamakshilk
 * LOG: Print statement corrected
 * LOG:
 * LOG: Revision 2.3  2006/10/26 05:40:43  kamakshilk
 * LOG: Added DisplayBaseMenuToApp() in the menu.
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:23:57  kamakshilk
 * LOG: Changes to work with ITS-Diameter APIs
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:38  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.7  2006/08/23 12:19:05  kamakshilk
 * LOG: Corrected AuthApplicationId value for CER,CEA and RAR to 0
 * LOG:
 * LOG: Revision 1.6  2006/06/15 11:01:14  kamakshilk
 * LOG: Creating ACR instance from incoming request impl in SendAccountingAnswer function
 * LOG:
 * LOG: Revision 1.5  2006/06/14 14:58:53  kamakshilk
 * LOG: For Base Protocol Messages, sIdx need not be set in the Send API.
 * LOG:
 * LOG: Revision 1.4  2006/06/05 12:11:55  yranade
 * LOG: Updates to compile with CC Compiler
 * LOG:
 * LOG: Revision 1.3  2006/05/22 10:38:46  nvijikumar
 * LOG: putting sane values.
 * LOG:
 * LOG: Revision 1.2  2006/04/28 07:03:22  nvijikumar
 * LOG: Code Enhancement (Documentation).
 * LOG:
 * LOG: Revision 1.1  2006/04/13 11:08:06  nvijikumar
 * LOG: Baseline demo programs
 * LOG:
 * LOG:
 * ID: $Id: sample_base.cpp,v 3.3 2009/07/24 09:35:14 rajeshak Exp $
 ****************************************************************************/

#include <diameter/base/ReAuth.h>
#include <diameter/base/AbortSession.h>
#include <diameter/base/SessionTermination.h>
#include <diameter/base/Accounting.h>
#include <diameter/base/CapabilitiesExchange.h>
#include <diameter/base/DeviceWatchdog.h>
#include <diameter/base/DisconnectPeer.h>
#include <diameter/base/BaseGenericCommand.h>

#include <app.h>
#include <idc_api.h>

using namespace std;
using namespace diameter;
using namespace diameter::base;

unsigned int sIdxBase = 0;
string sessIdStringBase;
IDSCLApi apiBase;
int AccountingRequestMenu();

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
                cout << "Proxiable Message"<<endl;
                ProxyInfo pinfo;

                ProxyHost phost(oriHost);
                pinfo.setProxyHost(phost);

                ProxyState pstate("state0");
                pinfo.setProxyState(pstate);

                gCmd->getContainer().add(pinfo.name(),pinfo,false);
                cout << "Sending Message"<<endl;
                if ((ret = apiBase.Send(*gCmd, gCmd->getSessionIndex(),
                                BASE_INTERFACE_APP_ID)) != ITS_SUCCESS)
                {
                    APP_TRACE_ERROR(("SendDiaAppMsg Failure"));
                }
                return ret;
            }
            else
            {
                cout<<endl<<"Message is NOT Proxiable..."<<endl;
            }
        }
    }
    else
    {
        pinfo_avp_count = gCmd->countProxyInfo();
        cout<<endl<<"Processing Answer"<<endl;

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
                    cout<<endl<<"Message is Proxiable..."<<endl;
                    if ((pinf->removeAVP(pinf->getProxyHost())) == ITS_SUCCESS)
                    {
                        cout<<endl<<"Proxy-Host AVP removed successfully"<<endl;
                    }
                    else
                    {
                        cout<<endl<<"Unable to remove Proxy-Host AVP"<<endl;
                    }
                    if ((pinf->removeAVP(pinf->getProxyState())) == ITS_SUCCESS)
                    {
                        cout<<endl<<"Proxy-State AVP removed successfully"<<endl;
                    }
                    else
                    {
                        cout<<endl<<"Unable to remove Proxy-State AVP"<<endl;
                    }
                    if (((Command*)gCmd)->removeAVP(*pinf) == ITS_SUCCESS)
                    {
                        cout<<endl<<"Proxy-Info AVP removed successfully"<<endl;
                    }
                    else
                    {
                        cout<<endl<<"Unable to remove Proxy-Info AVP"<<endl;
                    }

                    if ((ret = apiBase.Send(*gCmd, gCmd->getSessionIndex(),
                                  BASE_INTERFACE_APP_ID)) != ITS_SUCCESS)
                    {
                       cout<<endl<<"SendDiaAppMsg Failure"<<endl;
                    }
                    return ret;
                }
                else
                {
                   cout<<endl<<"Message is NOT Proxiable..."<<endl;
                }
            }
        }
    }
    return ret;
}


/*  implementation: public
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
int BaseMessage(const diameter::CommandImpl *impl, unsigned int &sIdxbase)
{
    sIdxBase=sIdxbase;
    Command *cmd = NULL;
    int ret;

    cout<<endl<<"Base Diameter Messages Received"<<endl;

    const char *oriHost = GetOriginHost();
    const char *oriRealm = GetOriginRealm();

    try
    {
        // Process the commands based on the command code.
        switch (impl->getCommandCode())
        {
        case 274: 
            if(impl->isRequest())
            {
                AbortSessionRequest asreq(*impl);
                cout << endl <<"Abort Session Request Received" << endl;
                cmd = (Command*)&asreq;
                if ((ret = ProcessIfProxy(cmd)) == ITS_SUCCESS)
                {
                    cout<<asreq;
                }
                else
                {
                    cout << "Abort-Session-Request" << asreq << endl;
                    cout << endl <<"Abort Session Answer Sent by the Stack" << endl;
                    SendAbortSessionAnswer(impl);
                    ret = ITS_SUCCESS;
                }

            }
            else
            {
                AbortSessionAnswer asans(*impl);
                cout << endl << "Abort Session Answer Received" << endl;
                cmd = (Command*)&asans;
                if ((ret = ProcessIfProxy(cmd)) == ITS_SUCCESS)
                {
                    cout<<asans;
                    ret = ITS_SUCCESS;
                }
                else
                {
                    cout << "Abort-Session-Answer" << asans << endl;
                    ret = ITS_SUCCESS;
                }
            }
            break;

        case 271:
            if(impl->isRequest())
            {
                AccountingRequest areq(*impl);
                cout << endl <<"Accounting Request Received" << endl;
                cmd = (Command*)&areq;
                if ((ret = ProcessIfProxy(cmd)) == ITS_SUCCESS)
                {
                    cout<<areq;
                }
                else
                {
                    cout << "Accounting-Request" << areq << endl;
                    cout << endl <<"Accounting Answer Sent by the Stack" << endl;
                    SendAccountingAnswer(impl);
                    return ITS_SUCCESS;
                }
            }
            else
            {
                AccountingAnswer aans(*impl);
                cout << endl << "Accounting Answer Received" << endl;
                cmd = (Command*)&aans;
                if ((ret = ProcessIfProxy(cmd)) == ITS_SUCCESS)
                {
                    cout<<aans;
                    return ITS_SUCCESS;
                }
                else
                {
                    cout << "Accounting-Answer" << aans << endl;
                    return ITS_SUCCESS;
                }
            }
            break;

        case 257:
            if(impl->isRequest())
            {
                CapabilitiesExchangeRequest cereq(*impl);
                cout << endl << "Capabilties Exchange Request "
                     << "Received" << cereq << endl;
                cout << endl << "Capabilties Exchange Answer "
                     << "Sent by the Stack" << endl;
                     //SendCapabilitiesExchangeAnswer(impl);
            }
            else
            {
                CapabilitiesExchangeAnswer ceans(*impl);
                cout << endl << "Capabilties Exchange Answer "
                     << "Received" << ceans << endl;
            }
            break;

        case 280:
            if(impl->isRequest())
            {
                DeviceWatchdogRequest dwreq(*impl);
                cout << endl << "Device Watch Dog Request "
                     << "Received" << dwreq << endl;
                cout << endl << "Device Watch Dog Answer Sent "
                     << "by the Stack" << endl << endl;
                //SendDeviceWatchdogAnswer(impl);
            }
            else
            {
                DeviceWatchdogAnswer dwans(*impl);
                cout << endl <<"Device Watch Dog Answer "
                     << "Received" << dwans << endl;
            }
            break;

        case 282:
            if(impl->isRequest())
            {
                DisconnectPeerRequest dpreq(*impl);
                cout << endl << "Disconnect Peer Request "
                     << "Received" << dpreq << endl;
                cout << endl << "Disconnect Peer Answer "
                     << "Sent by the Stack" << endl << endl;
                //SendDisconnectPeerAnswer(impl);
            }
            else
            {
                DisconnectPeerAnswer dpans(*impl);
                cout << endl <<"Disconnect Peer Answer Received"
                     << dpans << endl;
            }
            break;

        case 258:
            if(impl->isRequest())
            {
                ReAuthRequest rreq(*impl);
                cout << endl <<"ReAuth Request Received"
                     << rreq << endl;
                cout << endl << endl << "Sending ReAuth Answer" << endl;
                SendReAuthAnswer(impl);
            }
            else
            {
                ReAuthAnswer rans(*impl);
                cout << endl << "ReAuth Answer Received" << rans 
                     << endl;
            }
            break;

        case 275:
            if(impl->isRequest())
            {
                SessionTerminationRequest streq(*impl);
                cout << endl << "Session Termination Request Received"
                     << endl << streq << endl;
                cout << endl <<"Session Termination Answer Sent by the "
                     << "Stack" << endl;
                //Let the stack send Session Termination Answer,
                //since session state is controlled by the stack.
                SendSessionTerminationAnswer(impl);
            }
            else
            {
                SessionTerminationAnswer stans(*impl);
                cout << endl << "Session Termination Answer Received"
                     << stans << endl;
            }
            break;

        default:
            cout<<"Unknown Base Protocol Message Received"<<endl;
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
 *      Base protocol interface.
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
BaseMenu()
{
    int k=1;
    while(k)
    {
        string input;
        int ret;
        do
        {
            cout << endl << "Enter choice no for the given following base"
                 << "messages" << endl << endl;
            cout << endl << " (1) . Accounting Req Command" << endl;
            cout << endl << " (2) . Capability Exchange Req Command" << endl;
            cout << endl << " (3) . Device Watchdog Req Command" << endl;
            cout << endl << " (4) . Disconnect Peer Req Command" << endl;
            cout << endl << " (5) . ReAuth Req Command" << endl;
            cout << endl << " (6) . Session Termination Req Command" << endl;
            cout << endl << " (7) . Abort Session Req Command" << endl;
            cout << endl << "(99) . To Previous Menu" << endl;

            cin >>input;
            ret = atoi(input.c_str());

        } while ((ret < 1 || ret > 7) && ret!=99);

        switch(ret)
        {
        case 1:
            AccountingRequestMenu();
            break;
        case 2:
            SendCapabilitiesExchangeRequest();
            break;
        case 3:
            SendDeviceWatchdogRequest();
            break;
        case 4:
            SendDisconnectPeerRequest();
            break;
        case 5:
            SendReAuthRequest();
            break;
        case 6:
            SendSessionTerminationRequest();
            break;
        case 7:
            SendAbortSessionRequest();
            break;
        case 99:
            k=0;
            break;
        default:
            cout << endl << "please enter the correct choice";
            break;
        }
    }
    return 0;
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

    int k=1;
    while(k)
    {
        do
        {
            cout << "Enter your choice to send the following base Messages"
             << endl << endl;
            cout << " (1) . RAR - ReAuth Req Command" << endl;
            cout << " (2) . STR - Session Termination Req Command" << endl;
            cout << " (3) . ASR - Abort Session Req Command" << endl;
            cout << " (4) . ACR - Accounting Req Command" << endl;
            cout << "(99) . To Previous Menu" << endl;

            cin >> input;
            ret = atoi(input.c_str());

        } while ((ret < 1 || ret > 4) && ret!=99);

        switch(ret)
        {
        case 1:
            return SendReAuthRequest();
        case 2:
            return SendSessionTerminationRequest();
        case 3:
            return SendAbortSessionRequest();
        case 4:
            return AccountingRequestMenu();
        case 99:
            k = 0;
        default:
            cout << endl << "please enter the correct choice";
            break;
        }
    }
    return 0;
}

int
AccountingRequestMenu()
{
    string input;
    int ret = 0;
    do
    {
        cout << "Enter your choice to send the following Accounting Messages"
             << endl << endl;
        cout << endl << " (1) . Accounting START Request"   << endl;
        cout << endl << " (2) . Accounting INTERIM Request" << endl;
        cout << endl << " (3) . Accounting STOP Request"    << endl;
        cout << endl << " (4) . Accounting EVENT Request"   << endl;
        cout << endl << " (5) . Accounting START Request on Auth session"<<endl;
        cout << endl << " (6) . Accounting EVENT Request on Auth session"<<endl;
        cout << endl << "(99) . Exit" << endl;

        cin >> input;
        ret = atoi(input.c_str());

    } while ((ret < 1 || ret > 6) && ret!=99);

    switch(ret)
    {
    case 1:
        return SendAccountingRequest(START);
    case 2:
        return SendAccountingRequest(INTERIM);
    case 3:
        return SendAccountingRequest(STOP);
    case 4:
        return SendAccountingRequest(EVENT);
    case 5:
        return SendAccountingRequest(START_AUTHSESS);
    case 6:
        return SendAccountingRequest(EVENT_AUTHSESS);
    case 99:
            exit(1);
    default:
        cout << endl << "Invalid choice";
        break;
    }
    return 0;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Accounting request to the
 *      diameter stack. Create the Accounting Request object,
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
int SendAccountingRequest(int reqType, const diameter::CommandImpl* impl) 
{

    // [1] Create AccountingRequest object.

    AccountingRequest acr(false, false);

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
        apiBase.AllocateSessionIndex(10000, sIdxBase, sessIdStringBase);
        printf("\tSession Index: %d\n", sIdxBase);
        acr.setSessionId(SessionId(sessIdStringBase)); 
    }
    else
    {
        //for unit test provide the values of Session Id and Index
        cout << endl << "Please Enter the SessionId:" <<endl;
        cin >> sessIdStringBase ;
        acr.setSessionId(SessionId(sessIdStringBase));

        cout << "Please enter Session Index" << endl;
        string sId;
        cin >> sId;
        sIdxBase = atoi(sId.c_str());
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
    // acr.setLastRecordInStorage(false);

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
    VendorId venId(0u);
    venSAId.addVendorId(venId);

    // [2.2.2.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AcctApplicationId acctId(3u);
    venSAId.setAcctApplicationId(acctId);

    acr.setVendorSpecificApplicationId(venSAId);

    // [2.2.3]Populate optional parameter "User-Name"
    // Set the User-Name AVP.
    // The data type of User-Name is UTF8String.
    // This AVP contains the User-Name.
    // The AVP Code of User-Name is 1.
    UserName userName("sip:good.customer@3gppnetwork.com");
    acr.setUserName(userName);

    // [2.2.4]Populate optional parameter "Accounting-Sub-Session-Id".
    // Set the Accounting-Sub-Session-Id AVP.
    // The data type of Accounting-Sub-Session-Id is Unsigned64.
    // This AVP contains the accounting sub-session identifier.
    // The AVP Code of Accounting-Sub-Session-Id is 287.
    AccountingSubSessionId assid(2u);
    acr.setAccountingSubSessionId(assid);

    // [2.2.5]Populate optional parameter "Acct-Session-Id".
    // Set the Acct-Session-Id AVP.
    // The data type of Acct-Session-Id is OctetString.
    // This AVP is only used when RADIUS/Diameter translation occurs.
    // The AVP Code of Acct-Session-Id is 44.
    AcctSessionId asid("ACCT-00343");
    acr.setAcctSessionId(asid);

    // [2.2.6]Populate optional parameter "Acct-Multi-Session-Id".
    // Set the Acct-Multi-Session-Id AVP.
    // The data type of Acct-Multi-Session-Id is UTF8String.
    // The Acct-Multi-Session-Id AVP is used to link together multiple related
    // accounting sessions, where each session would have a unique Session-Id,
    // but the same Acct-Multi-Session-Id AVP.
    // The AVP Code of Acct-Multi-Session-Id is 50.
    AcctMultiSessionId amsid("ACCT-MULTI-35334");
    acr.setAcctMultiSessionId(amsid);

    // [2.2.7]Populate optional parameter "Acct-Interim-Interval".
    // Set the Acct-Interim-Interval AVP.
    // The data type of Acct-Interim-Interval is Unsigned32.
    // The client uses information in this AVP to decide how and when to produce
    // accounting records
    // The AVP Code of Acct-Interim-Interval is 85.
    AcctInterimInterval aii(200);
    acr.setAcctInterimInterval(aii);

    // [2.2.8]Populate optional parameter "Accounting-Realtime-Required"
    // Set the Accounting-Realtime-Required AVP.
    // The data type of Accounting-Realtime-Required is Enumerated.
    // The client uses information in this AVP to decide what to do if the
    // sending of accounting records to the accounting server has been
    // temporarily prevented .
    // The following values are supported
    // DELIVER_AND_GRANT                           1
    // GRANT_AND_STORE                             2
    // GRANT_AND_LOSE                              3
    // The AVP Code of Accounting-Realtime-Required is 483.
    AccountingRealtimeRequired arr(AccountingRealtimeRequired::GRANT_AND_LOSE);
    acr.setAccountingRealtimeRequired(arr);

    // [2.2.9] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state, 
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId origs(45);
    acr.setOriginStateId(origs);

    // [2.2.10] Populate optional parameter "Event-Timestamp".
    // Set the Event-Timestamp AVP.
    // The data type of Event-Timestamp is Time.
    // This AVP is used to record the time that the reported event occurred, in
    // seconds since January 1, 1900 00:00 UTC.
    // The AVP Code of Event-Timestamp is 55.
    // acr.setEventTimestamp(EventTimestamp(999));
    // [2.2.11] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.

    //ProxyInfo pi1;

    // [2.2.11.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info AVP.
    // The AVP Code of Proxy-Info is 280.

    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.11.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as opaque
    //  data
    // The AVP Code of Proxy-State is 33.
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    // Stack sets this AVP.
    // Application should not set this AVP
    // acr.addProxyInfo(pi1);

    // [2.2.12] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the message.
    // The AVP Code of Route-Record is 282.
    //RouteRecord rrec("abcdef");

    // Stack sets this AVP.
    // Application should not set this AVP
    // acr.addRouteRecord(rrec);

    // [3] Use appropriate application specific logic to Send object

    std::cout << acr << std::endl;

    apiBase.Send(acr, sIdxBase, BASE_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Capability exchange request to the
 *      diameter stack. Create the Capability exchnage Request
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
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi      23-08-06    Bug Id 4238     AuthAppId for CER changed to 0.
 *
 ****************************************************************************/
int SendCapabilitiesExchangeRequest() 
{

    // [1] Create CapabilitiesExchangeRequest object.
    CapabilitiesExchangeRequest cer(false, false);

    // [2] Insert data in the created CapabilitiesExchangeRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.2] Populate required Mandatories.
    // [2.1.2.1] Populate required paramete "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost origh(GetOriginHost());
    cer.setOriginHost(origh);

    // [2.1.2.2] Populate required paramete "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
    cer.setOriginRealm(origr);

    // [2.1.2.3] Populate required paramete "Host-IP-Address".
    // Set the Host-IP-Address AVP.
    // The data type of Host-IP-Address is Address.
    // This AVP is used to inform a Diameter peer of the sender's IP address.
    // The AVP Code of Host-IP-Address is 257.
    Address addr(Address::IPV4, "192.168.2.1");
    HostIPAddress hostIp(addr);
    cer.addHostIPAddress(hostIp);

    // [2.1.2.4] Populate required paramete "Vendor-ID".
    // Set the Vendor-ID AVP.
    // The data type of Vendor-ID is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may be
    // sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates that
    // this field is ignored.
    // The AVP Code of Vendor-ID is 266.
    VendorId venId(10415);
    cer.setVendorId(venId);

    // [2.1.2.5] Populate required paramete "Product-Name".
    // Set the Product-Name AVP.
    // The data type of Product-Name is UTF8String.
    // This AVP contains the vendor assigned name for the product.
    // The Product-Name AVP SHOULD remain constant across firmware revisions for
    // the same product.
    // The AVP Code of Product-Name is 269.
    ProductName prodName("IntelliNet Diameter");
    cer.setProductName(prodName);

    // [2.2] Populate Optionals
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
    cer.setOriginStateId(orgid);

    // [2.2.2] Populate optional parameter "Supported-Vendor-Id".
    // Set the Supported-Vendor-Id AVP.
    // The data type of Supported-Vendor-Id isUnsigned32.
    // This AVP is used in order to inform the peer that the sender supports the
    // vendor-specific AVPs defined by the vendor identified in This AVP.
    // The AVP Code of Supported-Vendor-Id is 265.
    SupportedVendorId supVenId(10415);
    cer.addSupportedVendorId(supVenId);

    // [2.2.3] Populate optional parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId aaid((Unsigned32)0);
    cer.addAuthApplicationId(aaid);

    // [2.2.4] Populate optional parameter "Inband-Security-Id".
    // Set the Inband-Security-Id AVP.
    // The data type of Inband-Security-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Security portion of
    // the application.
    // Currently, the following values are supported:
    // NO_INBAND_SECURITY                0
    // TLS                               1
    // The AVP Code of Inband-Security-Id is 299.
    InbandSecurityId inbandSec(0u);
    cer.addInbandSecurityId(inbandSec);

    // [2.2.4] Populate optional parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting portion
    // of an application.
    // The AVP Code of Acct-Application-Id is 259.
    AcctApplicationId actId(3);
    cer.addAcctApplicationId(actId);

    // [2.2.5] Populate optional parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP is used to advertise support of a vendor-specific Diameter
    // Application
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Vendor-Specific-Application-Id is 260.
    VendorSpecificApplicationId venSpecAppId;

    // [2.2.5.1] Popolate optional parameter "Vendor-Id".
    // Set the Vendor-ID AVP.
    // The data type of Vendor-ID is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may be
    // sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates that
    // this field is ignored.
    // The AVP Code of Vendor-ID is 266.
    VendorId vendId(10415);
    venSpecAppId.addVendorId(vendId);

    // [2.2.5.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId aapId(16777216);
    venSpecAppId.setAuthApplicationId(aapId);

    // [2.2.5.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting portion
    // of an application.
    // The AVP Code of Acct-Application-Id is 259.
    // AcctApplicationId accid(3);
    // venSpecAppId.setAcctApplicationId(accid);

    cer.addVendorSpecificApplicationId(venSpecAppId);

    // [2.2.6] Populate optional parameter "Firmware-Revision".
    // Set the Firmware-Revision AVP.
    // The data type of Firmware-Revision is Unsigned32.
    //This Avp is used to inform a Diameter peer of the firmware revision of the
    // issuing device
    // The AVP Code of Firmware-Revision is 267.
    FirmwareRevision firmRev(1);
    cer.setFirmwareRevision(firmRev);

    // [3] Use appropriate application specific logic to Send object
    std::cout << cer << std::endl;

    apiBase.Send(cer, BASE_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Device Watch dog request to the
 *      diameter stack. Create the DeviceWatchdogRequest
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
int SendDeviceWatchdogRequest() 
{

    // [1] Create DeviceWatchdogRequest object.
    DeviceWatchdogRequest dwr(false, false);

    // [2] Insert data in the created DeviceWatchdogRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.2] Populate required Mandatories.
    // [2.1.2.1] Populate required paramete "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost origh(GetOriginHost());
    dwr.setOriginHost(origh);

    // [2.1.2.2] Populate required paramete "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
    dwr.setOriginRealm(origr);

    // [2.2] Populate Optionals
    // [2.2.1] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     
    // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId origsid(41);
    dwr.setOriginStateId(origsid);

    IDCIDSHeartbeat idcHb(100);
    dwr.setIDCIDSHeartbeat(idcHb);

    // [3] Use appropriate application specific logic to Send object
    std::cout << dwr << std::endl;

    apiBase.Send(dwr, BASE_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Peer disconnect request to the
 *      diameter stack. Create the DisconnectPeerRequest
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
int SendDisconnectPeerRequest() 
{

    // [1] Create Disconnect Peer Request object.
    DisconnectPeerRequest dpr(false, false);

    // [2] Insert data in the created DisconnectPeerRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.2] Populate required Mandatories.
    // [2.1.2.1] Populate required paramete "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost origh(GetOriginHost());
    dpr.setOriginHost(origh);

    // [2.1.2.2] Populate required paramete "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
    dpr.setOriginRealm(origr);

    // [2.1.2.3] Populate required parameter "Disconnect-Cause".
    // Set the Disconnect-Cause AVP.
    // The data type of Disconnect-Cause is Enumerated.
    // This AVP to inform the peer of the reason for its intention to shutdown
    // the transport connection.
    // The following values are supported:
    // REBOOTING                         0
    // BUSY                              1
    // DO_NOT_WANT_TO_TALK_TO_YOU        2
    // The AVP Code of Disconnect-Cause is 273.
    DisconnectCause discause(DisconnectCause::REBOOTING);
    dpr.setDisconnectCause(discause);

    // [2.2] Populate Optionals
    // [3] Use appropriate application specific logic to Send object
    std::cout << dpr << std::endl;

    apiBase.Send(dpr, BASE_INTERFACE_APP_ID);

    return (ITS_SUCCESS);

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
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi      23-08-06    Bug Id 4238     AuthAppId for RAR changed to 0.
 *
 ****************************************************************************/
int SendReAuthRequest() 
{
    // [1] Create ReAuthRequest object.
    ReAuthRequest rar(false, false);

    // [2] Insert data in the created ReAuthRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed paramete "Session-Id".
    cout<<"Please Enter Session Id to Re-Authorize"<<endl;
    string sessId;
    cin>>sessId;
    rar.setSessionId(SessionId(sessId));

    cout << "Please enter Session Index" << endl;
    string sId;
    cin >> sId;
    sIdxBase = atoi(sId.c_str()); 

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
    AuthApplicationId authId(0u);
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

    std::cout << rar << std::endl;

    apiBase.Send(rar, sIdxBase, BASE_INTERFACE_APP_ID);

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
int SendSessionTerminationRequest() {

    // [1] Create SessionTerminationRequest object.
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
    cout<<"Please Enter Session Id to Terminate"<<endl;
    string sessId;
    cin>>sessId;
    str.setSessionId(SessionId(sessId));

    cout << "Please enter Session Index" << endl;
    string sId;
    cin >> sId;
    sIdxBase = atoi(sId.c_str()); 

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

    std::cout << str << std::endl;

    apiBase.Send(str, sIdxBase, BASE_INTERFACE_APP_ID);

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
    cout << "Please Enter Session ID to Abort" << endl;
    string sessId;
    cin >> sessId;
    asr.setSessionId(SessionId(sessId)); 

    cout << "Please enter Session Index" << endl;
    string sId;
    cin >> sId;
    sIdxBase = atoi(sId.c_str()); 

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

    std::cout << asr << std::endl;

    apiBase.Send(asr, sIdxBase, BASE_INTERFACE_APP_ID);

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
    // [1] Create AbortSessionRequest object.
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
     OriginHost orig(GetOriginHost());
     asa.setOriginHost(orig);

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
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
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
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

    // [3] Use appropriate application specific logic to Send object

    std::cout << asa << std::endl;

    apiBase.Send(asa, sIdxBase, BASE_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the capability exchange
 *      request made by the diameter stack. Create the 
 *      CapabilitiesExchangeAnswer object, populate the AVPs and send 
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
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi      23-08-06    Bug Id 4238     AuthAppId for CEA changed to 0.
 *
 ****************************************************************************/
int SendCapabilitiesExchangeAnswer(const CommandImpl* impl1)
{
    // [1] Create CapabilitiesExchangeAnswer object.
    CapabilitiesExchangeAnswer cea(false, false);

    // [2] Insert data in the created object
    // [2.1] Populate Mandatories.
    // [2.2.1] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    ResultCode rc(2001u);
    cea.setResultCode(rc);

    // [2.2.2] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost origh(GetOriginHost());
    cea.setOriginHost(origh);

    // [2.2.3] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
    cea.setOriginRealm(origr);

    // [2.2.4] Populate required paramete "Host-IP-Address".
    // Set the Host-IP-Address AVP.
    // The data type of Host-IP-Address is Address.
    // This AVP is used to inform a Diameter peer of the sender's IP address.
    // The AVP Code of Host-IP-Address is 257.
    Address addr(Address::IPV4, "192.168.2.1");
    HostIPAddress hip(addr);
    cea.addHostIPAddress(hip);

    // [2.2.5] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vid(10415u);
    cea.setVendorId(vid);

    // [2.2.6] Populate required parameter "Product-Name".
    // Set the Product-Name AVP.
    // The data type of Product-Name is UTF8String.
    // This AVP contains the vendor assigned name for the product.  The
    // Product-Name AVP SHOULD remain constant across firmware revisions
    // for the same product.
    // The AVP Code of Product-Name is 269.
    ProductName prodName("IntelliNet Diameter");
    cea.setProductName(prodName);

    // [2.2.7] Populate required parameter "Origin-State-Id".
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
    OriginStateId orgid(41);
    cea.setOriginStateId(orgid);

    // [2.2.8] Populate optional parameter "Error-Message".
    // Set the Error-Message AVP.
    // The data type of Error-Message is UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message.
    // The AVP Code of Error-Message is 281.
    ErrorMessage erm("Server problem");
    // cea.setErrorMessage(erm);

    //FailedAVP fh1;
    //cea.addFailedAVP(fh1);

    // [2.2.9] Populate optional parameter "Supported-Vendor-Id".
    // Set the Supported-Vendor-Id AVP.
    // The data type of Supported-Vendor-Id is Unsigned32.
    // Contains the IANA "SMI Network Management Private Enterprise Codes"
    // [ASSIGNNO] value assigned to a vendor other than the device vendor.
    // This is used in the CER and CEA messages in order to inform the peer
    // that the sender supports (a subset of) the vendor-specific AVPs
    // defined by the vendor identified in this AVP.
    // The AVP Code of Supported-Vendor-Id is 265.
    SupportedVendorId svid(10415);
    cea.addSupportedVendorId(svid);

    // [2.2.10] Populate optional parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication
    // and Authorization portion of an application (see Section 2.4).  The
    // Auth-Application-Id MUST also be present in all Authentication and/or
    // Authorization messages that are defined in a separate Diameter
    // specification and have an Application ID assigned.
    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId aaid((Unsigned32)0);
    cea.addAuthApplicationId(aaid);

    // [2.2.11] Populate optional parameter "Inband-Security-Id".
    // Set the Inband-Security-Id AVP.
    // The data type of Inband-Security-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Security
    // portion of the application.
    // The AVP Code of Inband-Security-Id is 299.
    InbandSecurityId isid(0u);
    cea.addInbandSecurityId(isid);

    // [2.2.12] Populate optional parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP used in order to advertise support of the Accounting 
    // portion of an application (see Section 2.4).  The 
    // Acct-Application-Id MUST also be present in all Accounting messages.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id 
    // AVPs MAY be present.
    // The AVP Code of Acct-Application-Id is 259.
    AcctApplicationId actid(3u);
    cea.addAcctApplicationId(actid);

    // [2.2.13] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    VendorSpecificApplicationId venSpecAppId;

    // [2.2.13.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may be
    // sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates that
    // this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId venid(10415);
    venSpecAppId.addVendorId(venid);

    // [2.2.13.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId aapid(16777217);
    venSpecAppId.setAuthApplicationId(aapid);

    // [2.2.13.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    //AcctApplicationId accid(3);
    //venSpecAppId.setAcctApplicationId(accid);

    cea.addVendorSpecificApplicationId(venSpecAppId);

    // [2.2.14] Populate required parameter "Firmware-Revision".
    // Set the Firmware-Revision AVP.
    // The data type of Firmware-Revision is Unsigned32.
    // This AVP is used to inform a Diameter peer of the firmware
    // revision of the issuing device.
    // The AVP Code of Firmware-Revision is 267.
    FirmwareRevision frev(1);
    cea.setFirmwareRevision(frev);

    // [3] Use appropriate application specific logic to Send object

    std::cout << cea << std::endl;

    apiBase.Send(cea, sIdxBase, BASE_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the Device Watch dog
 *      request made by the diameter stack. Create the
 *      DeviceWatchdogAnswer object, populate the AVPs and send the
 *      message to the stack.
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
int SendDeviceWatchdogAnswer(const CommandImpl* impl1)
{
    // [1] Create DeviceWatchdogAnswer object.
    DeviceWatchdogAnswer dwa(false, false);

    DeviceWatchdogRequest com_req(*impl1);

    // [2] Insert data in the created object
    // [2.1] Populate Mandatories.
    // [2.2.1] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    ResultCode rc(2001u);
    dwa.setResultCode(rc);

    // [2.2.2] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost origh(GetOriginHost());
    dwa.setOriginHost(origh);

    // [2.2.3] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
    dwa.setOriginRealm(origr);

    // [2.2.4] Populate optional parameter "Error-Message".
    // Set the Error-Message AVP.
    // The data type of Error-Message is UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message.
    // The AVP Code of Error-Message is 281.
    // ErrorMessage erm("Server problem");
    // dwa.setErrorMessage(erm);

    // FailedAVP fh1;
    // dwa.addFailedAVP(fh1);

    // [2.2.4] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This AVP is a monotonically increasing value that is advanced 
    // whenever a Diameter entity restarts with loss of previous state,
    // for example upon reboot. Origin-State-Id MAY be included in any
    // Diameter message, including CER.
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     
    // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId origsid(41);
    dwa.setOriginStateId(origsid);

    // [3] Use appropriate application specific logic to Send object

    std::cout << dwa << std::endl;

    apiBase.Send(dwa, sIdxBase, BASE_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the Peer disconnect
 *      request made by the diameter stack. Create the
 *      DisconnectPeerAnswer object, populate the AVPs and send the
 *      message to the stack.
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
int SendDisconnectPeerAnswer(const CommandImpl *impl1)
{
    // [1] Create DisconnectPeer object.
    DisconnectPeerAnswer dpa(false, false);

    DisconnectPeerRequest com_req(*impl1);

    // [2] Insert data in the created object
    // [2.1] Populate Mandatories.
    // [2.2.1] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    ResultCode rc(20001u);
    dpa.setResultCode(rc);

    // [2.2.2] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost origh(GetOriginHost());
    dpa.setOriginHost(origh);

    // [2.2.3] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
    dpa.setOriginRealm(origr);

    // [2.2.4] Populate optional parameter "Error-Message".
    // Set the Error-Message AVP.
    // The data type of Error-Message is UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message.
    // The AVP Code of Error-Message is 281.
    // ErrorMessage erm("Server problem");
    // dpa.setErrorMessage(erm);

    // FailedAVP fh1;
    // dpa.addFailedAVP(fh1);

    // [3] Use appropriate application specific logic to Send object

    std::cout << dpa << std::endl;

    apiBase.Send(dpa, sIdxBase, BASE_INTERFACE_APP_ID);

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
    ReAuthAnswer raa(false, false);

    ReAuthRequest com_req(*impl1);

    const OriginHost& oh1 = com_req.getOriginHost();
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
    OriginHost origh(GetOriginHost());
    raa.setOriginHost(origh);

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
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

    std::cout << raa << std::endl;

    apiBase.Send(raa, sIdxBase, BASE_INTERFACE_APP_ID);

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
    OriginRealm origr(GetOriginRealm());
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

    // [3] Use appropriate application specific logic to Send object

    std::cout << sta << std::endl;
    apiBase.Send(sta, sIdxBase, BASE_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the Accounting
 *      request made by diameter stack. Create the AccountingAnswer
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
int SendAccountingAnswer(const CommandImpl *impl1)
{
    // [1] Create AccountingAnswer object.
    AccountingAnswer aca(false, false);

    AccountingRequest com_req(*impl1);

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

    // [2.2.8] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    VendorSpecificApplicationId vs1;

    // [2.2.8.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may be
    // sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates that
    // this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId venid(0u);
    vs1.addVendorId(venid);

    // [2.2.8.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AcctApplicationId aapid(3u);
    vs1.setAcctApplicationId(aapid);

    // [2.2.8.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    // AcctApplicationId accad(23);
    // vs1.setAcctApplicationId(accad);
    aca.setVendorSpecificApplicationId(vs1);

    // [2.2.9] Populate Optional paramete "User-Name".
    // Set the User-Name AVP.
    // The data type of User-Name is UTF8String.
    // This AVP contains the User-Name.
    // The AVP Code of User-Name is 1.
    UserName un("sip:good.customer@india.internal.net");
    aca.setUserName(un);

    // [2.2.10]Populate optional parameter "Accounting-Sub-Session-Id".
    // Set the Accounting-Sub-Session-Id AVP.
    // The data type of Accounting-Sub-Session-Id is Unsigned64.
    // This AVP contains the accounting sub-session identifier.
    // The AVP Code of Accounting-Sub-Session-Id is 287.
    AccountingSubSessionId assid(3u);
    aca.setAccountingSubSessionId(assid);

    // [2.2.11]Populate optional parameter "Acct-Session-Id".
    // Set the Acct-Session-Id AVP.
    // The data type of Acct-Session-Id is OctetString.
    // This AVP is only used when RADIUS/Diameter translation occurs.
    // The AVP Code of Acct-Session-Id is 44.
    AcctSessionId asid("ACCT-00343");
    aca.setAcctSessionId(asid);

    // [2.2.12]Populate optional parameter "Acct-Multi-Session-Id".
    // Set the Acct-Multi-Session-Id AVP.
    // The data type of Acct-Multi-Session-Id is UTF8String.
    // The Acct-Multi-Session-Id AVP is used to link together multiple related
    // accounting sessions, where each session would have a unique Session-Id,
    // but the same Acct-Multi-Session-Id AVP.
    // The AVP Code of Acct-Multi-Session-Id is 50.
    AcctMultiSessionId amsid("ACCT-MULTI-35334");
    aca.setAcctMultiSessionId(amsid);

    // [2.2.13]Populate optional parameter "Acct-Interim-Interval".
    // Set the Acct-Interim-Interval AVP.
    // The data type of Acct-Interim-Interval is Unsigned32.
    // The client uses information in this AVP to decide how and when to produce
    // accounting records
    // The AVP Code of Acct-Interim-Interval is 85.
    AcctInterimInterval accInter(20u);
    aca.setAcctInterimInterval(accInter);

    // [2.2.14]Populate optional parameter "Accounting-Realtime-Required"
    // Set the Accounting-Realtime-Required AVP.
    // The data type of Accounting-Realtime-Required is Enumerated.
    // The client uses information in this AVP to decide what to do if the
    // sending of accounting records to the accounting server has been
    // temporarily prevented .
    // The following values are supported
    // DELIVER_AND_GRANT                           1
    // GRANT_AND_STORE                             2
    // GRANT_AND_LOSE                              3
    // The AVP Code of Accounting-Realtime-Required is 483.
    AccountingRealtimeRequired arr(AccountingRealtimeRequired::GRANT_AND_STORE);
    aca.setAccountingRealtimeRequired(arr);

    // [2.2.15] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId origs(45);
    aca.setOriginStateId(origs);

    // [2.2.16] Populate optional parameter "Event-Timestamp".
    // Set the Event-Timestamp AVP.
    // The data type of Event-Timestamp is Time.
    // This AVP is used to record the time that the reported event occurred, in
    // seconds since January 1, 1900 00:00 UTC.
    // The AVP Code of Event-Timestamp is 55.
    aca.setEventTimestamp(EventTimestamp(2006u));

    // [2.2.17] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo pi1;

    // [2.2.17.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info AVP.
    // The AVP Code of Proxy-Info is 280.
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.17.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as opaque
    //  data
    // The AVP Code of Proxy-State is 33.
    // Stack sets this AVP.
    // Application should not set this AVP
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);
    //aca.addProxyInfo(pi1);

    int pinfo_count = com_req.countProxyInfo();
    for(int i=0; i<pinfo_count; i++)
    {
        ProxyInfo pinfo;
        ProxyHost phost(com_req.getProxyInfo(i).getProxyHost());
        pinfo.setProxyHost(phost);

        ProxyState pstate(com_req.getProxyInfo(i).getProxyState());
        pinfo.setProxyState(pstate);

        aca.addProxyInfo(pinfo);
    }

    // [3] Use appropriate application specific logic to Send object

    std::cout << aca << std::endl;

    apiBase.Send(aca, sIdxBase, BASE_INTERFACE_APP_ID);

    return (ITS_SUCCESS);
}

