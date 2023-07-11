/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: sample_base.java,v $
 * LOG: Revision 3.1  2008/03/31 10:33:23  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/05/23 05:55:02  sumag
 * LOG: This is version 1.0 of the tcpip based java diameter client and the test
 * LOG: java server.
 * LOG: The client and server applications in app directory are operational
 * LOG: javafiles directory files - to be completed
 * LOG:
 ****************************************************************************/
//#ident "$Id: sample_base.java,v 3.1 2008/03/31 10:33:23 nvijikumar Exp $"

//package .;

import java.lang.Thread;
import java.net.*;
import com.intellinet.diameter.*;
import diameter.base.*;

class sample_base
{
    int sIdxBase=0;
    String sessIdStringBase;

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
    int BaseMessage(Command impl/*, unsigned int &sIdxBase*/)
    {
        try
        {
            // Process the command based on the command codes
            switch(impl.getCommandCode())
            {
                case 274:
                    if(impl.isRequest())
                    {
                        AbortSessionRequest asreq = new AbortSessionRequest(impl);
                        System.out.println("\nAbort Session Request Received" + asreq + "\n");
                        System.out.println("Abort Session Answer sent by the stack\n");
                        SendAbortSessionAnswer(impl);
                    }
                    else
                    {
                        AbortSessionAnswer asans = new AbortSessionAnswer(impl);
                        System.out.println("\nAbort Session Answer Received" + asans + "\n");
                    }
                    break;
                case 271:
                    if(impl.isRequest())
                    {
                        AccountingRequest areq = new AccountingRequest(impl);
                        System.out.println("\nAccounting Request Received" + areq + "\n");
                        System.out.println("Accounting Answer sent by the stack\n");
                        SendAccountingAnswer(impl);
                    }
                    else
                    {
                        AccountingAnswer aans = new AccountingAnswer(impl);
                        System.out.println("\nAccounting Answer Received" + aans + "\n");
                    }
                    break;
                 case 257:
                    if(impl.isRequest())
                    {
                        CapabilitiesExchangeRequest cereq = new CapabilitiesExchangeRequest(impl);
                        System.out.println("\nCapabilities Exchange Request Received" + cereq + "\n");
                        System.out.println("Capabilities Exchange Answer sent by the stack\n");
                        SendCapabilitiesExchangeAnswer(impl);
                    }
                    else
                    {
                        CapabilitiesExchangeAnswer ceans = new CapabilitiesExchangeAnswer(impl);
                        System.out.println("\nCapabilities Exchange Answer Received" + ceans + "\n");
                    }
                    break;
                 case 280:
                    if(impl.isRequest())
                    {
                        DeviceWatchdogRequest dwreq = new DeviceWatchdogRequest(impl);
                        System.out.println("\nDevice Watchdog Request Received" + dwreq + "\n");
                        System.out.println("Device Watchdog Answer sent by the stack\n");
                        SendDeviceWatchdogAnswer(impl);
                    }
                    else
                    {
                        DeviceWatchdogAnswer dwans = new DeviceWatchdogAnswer(impl);
                        System.out.println("\nAbort Session Answer Received" + dwans + "\n");
                    }
                    break;
                 case 282:
                    if(impl.isRequest())
                    {
                        DisconnectPeerRequest dpreq = new DisconnectPeerRequest(impl);
                        System.out.println("\nDisconnect Peer Request Received" + dpreq + "\n");
                        System.out.println("Disconnect Peer Answer sent by the stack\n");
                        SendDisconnectPeerAnswer(impl);
                    }
                    else
                    {
                        DisconnectPeerAnswer dpans = new DisconnectPeerAnswer(impl);
                        System.out.println("\nDisconnect Peer Answer Received" + dpans + "\n");
                    }
                    break;
                 case 258:
                    if(impl.isRequest())
                    {
                        ReAuthRequest rreq = new ReAuthRequest(impl);
                        System.out.println("\nReAuth Request Received" + rreq + "\n");
                        System.out.println("ReAuth Answer sent by the stack\n");
                        SendReAuthAnswer(impl);
                    }
                    else
                    {
                        ReAuthAnswer rans = new ReAuthAnswer(impl);
                        System.out.println("\nReAuth Answer Received" + rans + "\n");
                    }
                    break;
                 case 275:
                    if(impl.isRequest())
                    {
                        SessionTerminationRequest streq = new SessionTerminationRequest(impl);
                        System.out.println("\nSession Termination Request Received" + streq + "\n");
                        System.out.println("Session Termination Answer sent by the stack\n");
                        SendSessionTerminationAnswer(impl);
                    }
                    else
                    {
                        SessionTerminationAnswer stans = new SessionTerminationAnswer(impl);
                        System.out.println("\nSession Termination Answer Received" + stans + "\n");
                    }
                    break;
                default:
                     System.out.println("Unknown Base Protocol Message Received\n");
                     break;         
            }//end switch
        }//try
        catch(NoSuchAttributeException e)
        {
            System.out.println("Exception Caught: " + e);
        }//catch
        catch(WrongCommandTypeException e)
        {
            System.out.println("Exception Caught: " + e);
        }//catch
        catch(UnknownTypeException e)
        {
            System.out.println("Exception Caught: " + e);
        }//catch
        catch (CodecException e)
        {
            System.out.println("Exception Caught: " + e);
        }
        catch (Exception e)
        {
            System.out.println("Unknown Exception Caught");
        }

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

    public static int BaseMenu()
    {

        boolean k=true;

        while(k)
        {
            int input = 0;
            do
            {
                System.out.println("Enter choice number of the base protocol command to be sent\n");
                System.out.println(" (1). Accounting Request Command\n");
                System.out.println(" (2). Capability Exchange Request Command\n");
                System.out.println(" (3). Device Watchdog Request Command\n");
                System.out.println(" (4). Disconnect Peer Request Command\n");
                System.out.println(" (5). ReAuth Request Command\n");
                System.out.println(" (6). Session Termination Request Command\n");
                System.out.println(" (7). Abort Session Request Command\n");
                System.out.println(" (99). Previous Menu\n");
 
                input = System.in.read();          

            }while((input < 1 || input > 7) && input != 99);

            switch(input)
            {
                case 1:
                    SendAccountingRequest();
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
                    k=false;
                    break;
                default:
                    System.out.println("\nPlease Enter a correct choice");
                    break;
            }//end switch
        }//end while
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

    int SendAccountingRequest()
    {
        diameter.base.AbortSessionRequest asreq = new diameter.base.AbortSessionRequest(false,false);
                                                                                                       
        String sessionIdvalue = "sessionId String";
        asreq.setSessionId(new SessionId(sessionIdvalue));
                                                                                                       
        String originHostvalue = "originHost String";
        asreq.setOriginHost(new OriginHost(originHostvalue));
                                                                                                       
        String originRealmvalue = "originRealm String";
        asreq.setOriginRealm(new OriginRealm(originRealmvalue));
                                                                                                       
        String destRealmvalue = "destRealm String";
        asreq.setDestinationRealm(new DestinationRealm(destRealmvalue));
                                                                                                       
        String destHostvalue = "destHost String";
        asreq.setDestinationHost(new DestinationHost(destHostvalue));

        asreq.setAuthApplicationId(new AuthApplicationId(0));

        String userName = "userName";
        asreq.setUserName(new UserName(userName));

        asreq.setOriginStateId(new OriginStateId(0));

        ProxyInfo proxyInfo1, proxyInfo2;
        ProxyHost proxyHost1 = new ProxyHost("proxyHost1.abc.com");
        ProxyHost proxyHost2 = new ProxyHost("proxyHost2.abc.com");
        ProxyState proxyState1 = new ProxyState("state1");
        ProxyState proxyState2 = new ProxyState("state2");
        proxyInfo1.setProxyHost(proxyHost1);
        proxyInfo2.setProxyHost(proxyHost2);
        proxyInfo1.setProxyState(proxyState1);
        proxyInfo2.setProxyState(proxyState2);
        asreq.addProxyInfo(proxyInfo1);
        asreq.addProxyInfo(proxyInfo2);

        RouteRecord routeRecord1 = new RouteRecord("routeRecord1");
        RouteRecord routeRecord2 = new RouteRecord("routeRecord2");
        asreq.addRouteRecord(routeRecord1);
        asreq.addRouteRecord(routeRecord2);

        // add more AVP as ANY values

        System.out.println(asreq);
                                                                                                       
        //Embed C++ method call SendToStack(&asreq);
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
 ****************************************************************************/
int SendCapabilitiesExchangeRequest()
{
        diameter.base.CapabilitiesExchangeRequest cereq = new diameter.base.CapabilitiesExchangeRequest(false,false);
                                                                                                       
        String originHostvalue = "originHost String";
        cereq.setOriginHost(new OriginHost(originHostvalue));
                                                                                                       
                                                                                                       
        String originRealmvalue = "originRealm String";
        cereq.setOriginRealm(new OriginRealm(originRealmvalue));
                                                                                                       
        Family family = new Family(1);
        String addressString = "address";
        Address address = new Address(family,addressString);
        cereq.addHostIPAddress(new HostIPAddress(address));
                                                                                                       
        cereq.setVendorId(new VendorId(1));
                                                                                                       
        String productNameString = "Intellinet Diameter";
        cereq.setProductName(new ProductName(productNameString));
                                                                                                       
        cereq.setOriginStateId(new OriginStateId(0));
        cereq.addSupportedVendorId(new SupportedVendorId(1));
        cereq.addAuthApplicationId(new AuthApplicationId(0));
        cereq.addInbandSecurityId(new InbandSecurityId(1));
        cereq.addAcctApplicationId(new AcctApplicationId(1));
                                                                                                       
        VendorSpecificApplicationId vsid;
        VendorId vendorId;
        vsid.addVendorId(vendorId);
        AuthApplicationId authApplicationId;
        vsid.setAuthApplicationId(authApplicationId);
        AcctApplicationId acctApplicationId;
        vsid.setAcctApplicationId(acctApplicationId);
        cereq.addVendorSpecificApplicationId(vsid);
                                                                                                       
        cereq.setFirmwareRevision(new FirmwareRevision(1));
                                                                                                       
        // add more AVP as ANY values
                                                                                                       
        System.out.println(cereq);
                                                                                                       
                                                                                                       
        //Embed C++ method call SendToStack(&cereq);

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
        diameter.base.DeviceWatchdogRequest dwreq = new diameter.base.DeviceWatchdogRequest(false,false);
                                                                                                       
        String originHostvalue = "originHost String";
        dwreq.setOriginHost(new OriginHost(originHostvalue));
                                                                                                       
                                                                                                       
        String originRealmvalue = "originRealm String";
        dwreq.setOriginRealm(new OriginRealm(originRealmvalue));
                                                                                                       
        dwreq.setOriginStateId(new OriginStateId(1));
                                                                                                       
        System.out.println(dwreq);
                                                                                                       
        //Embed C++ method call SendToStack(&dwreq);

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
        diameter.base.DisconnectPeerRequest dpreq = new diameter.base.DisconnectPeerRequest(false,false);
                                                                                                       
        String originHostvalue = "originHost String";
        dpreq.setOriginHost(new OriginHost(originHostvalue));
                                                                                                                                                                                                               
        String originRealmvalue = "originRealm String";
        dpreq.setOriginRealm(new OriginRealm(originRealmvalue));
                                                                                                       
        dpreq.setDisconnectCause(new DisconnectCause(DisconnectCause.REBOOTING));
                                                                                                       
        System.out.println(dpreq);
                                                                                                       
                                                                                                       
        //Embed C++ method call SendToStack(&dpreq);

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
        diameter.base.ReAuthRequest rareq = new diameter.base.ReAuthRequest(false,false);
                                                                                                       
        String sessionIdvalue = "sessionId String";
        rareq.setSessionId(new SessionId(sessionIdvalue));
                                                                                                       
        String originHostvalue = "originHost String";
        rareq.setOriginHost(new OriginHost(originHostvalue));
                                                                                                       
                                                                                                       
        String originRealmvalue = "originRealm String";
        rareq.setOriginRealm(new OriginRealm(originRealmvalue));
                                                                                                       
        String destRealmvalue = "destRealm String";
        rareq.setDestinationRealm(new DestinationRealm(destRealmvalue));
                                                                                                       
                                                                                                       
        String destHostvalue = "destHost String";
        rareq.setDestinationHost(new DestinationHost(destHostvalue));
                                                                                                       
        rareq.setAuthApplicationId(new AuthApplicationId(1));
        rareq.setReAuthRequestType(new ReAuthRequestType(ReAuthRequestType.AUTHORIZE_ONLY));
                                                                                                       
        String userName = "userName";
        rareq.setUserName(new UserName(userName));
                                                                                                       
        rareq.setOriginStateId(new OriginStateId(1));
                                                                                                       
        ProxyInfo proxyInfo1, proxyInfo2;
        ProxyHost proxyHost1 = new ProxyHost("proxyHost1.abc.com");
        ProxyHost proxyHost2 = new ProxyHost("proxyHost2.abc.com");
        ProxyState proxyState1 = new ProxyState("state1");
        ProxyState proxyState2 = new ProxyState("state2");
        proxyInfo1.setProxyHost(proxyHost1);
        proxyInfo2.setProxyHost(proxyHost2);
        proxyInfo1.setProxyState(proxyState1);
        proxyInfo2.setProxyState(proxyState2);
        rareq.addProxyInfo(proxyInfo1);
        rareq.addProxyInfo(proxyInfo2);
                                                                                                       
        RouteRecord routeRecord1 = new RouteRecord("routeRecord1");
        RouteRecord routeRecord2 = new RouteRecord("routeRecord2");
        rareq.addRouteRecord(routeRecord1);
        rareq.addRouteRecord(routeRecord2);
                                                                                                       
        rareq.setEventTimestamp(new EventTimestamp(1));
        rareq.setCCSubSessionId(new CCSubSessionId(1));
        rareq.setGSUPoolIdentifier(new GSUPoolIdentifier(1));
        rareq.setServiceIdentifier(new ServiceIdentifier("UTF8StringData"));
        rareq.setRatingGroup(new RatingGroup(1));
                                                                                                       
        // add more AVP as ANY values
                                                                                                       
        System.out.println(rareq);
                                                                                                       
        //Embed C++ method call SendToStack(&rareq);

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
int SendSessionTerminationRequest()
{
        diameter.base.SessionTerminationRequest streq = new diameter.base.SessionTerminationRequest(false,false);
                                                                                                       
        String sessionIdvalue = "sessionId String";
        streq.setSessionId(new SessionId(sessionIdvalue));
                                                                                                       
                                                                                                       
        String originHostvalue = "originHost String";
        streq.setOriginHost(new OriginHost(originHostvalue));
                                                                                                       
                                                                                                       
        String originRealmvalue = "originRealm String";
        streq.setOriginRealm(new OriginRealm(originRealmvalue));
                                                                                                       
                                                                                                       
        String destRealmvalue = "destRealm String";
        streq.setDestinationRealm(new DestinationRealm(destRealmvalue));
                                                                                                       
        streq.setAuthApplicationId(new AuthApplicationId(0));
        streq.setTerminationCause(new TerminationCause(TerminationCause.DIAMETER_LOGOUT));
                                                                                                       
        String userName = "userName";
        streq.setUserName(new UserName(userName));
                                                                                                       
        String destHostvalue = "destHost String";
        streq.setDestinationHost(new DestinationHost(destHostvalue));
                                                                                                       
        String classString = "classString";
        streq.addClass(new Class(classString));
                                                                                                       
        streq.setOriginStateId(new OriginStateId(1));
                                                                                                       
        ProxyInfo proxyInfo1, proxyInfo2;
        ProxyHost proxyHost1 = new ProxyHost("proxyHost1.abc.com");
        ProxyHost proxyHost2 = new ProxyHost("proxyHost2.abc.com");
        ProxyState proxyState1 = new ProxyState("state1");
        ProxyState proxyState2 = new ProxyState("state2");
        proxyInfo1.setProxyHost(proxyHost1);
        proxyInfo2.setProxyHost(proxyHost2);
        proxyInfo1.setProxyState(proxyState1);
        proxyInfo2.setProxyState(proxyState2);
        streq.addProxyInfo(proxyInfo1);
        streq.addProxyInfo(proxyInfo2);
                                                                                                       
        RouteRecord routeRecord1 = new RouteRecord("routeRecord1");
        RouteRecord routeRecord2 = new RouteRecord("routeRecord2");
        streq.addRouteRecord(routeRecord1);
        streq.addRouteRecord(routeRecord2);
                                                                                                       
        // add more AVP as ANY values
                                                                                                       
        System.out.println(streq);
                                                                                                       
        //Embed C++ method call SendToStack(&streq);
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
        diameter.base.AbortSessionRequest asreq = new diameter.base.AbortSessionRequest(false,false);
                                                                                                       
        String sessionIdvalue = "sessionId String";
        asreq.setSessionId(new SessionId(sessionIdvalue));
                                                                                                       
        String originHostvalue = "originHost String";
        asreq.setOriginHost(new OriginHost(originHostvalue));
                                                                                                       
        String originRealmvalue = "originRealm String";
        asreq.setOriginRealm(new OriginRealm(originRealmvalue));
                                                                                                       
        String destRealmvalue = "destRealm String";
        asreq.setDestinationRealm(new DestinationRealm(destRealmvalue));
                                                                                                       
        String destHostvalue = "destHost String";
        asreq.setDestinationHost(new DestinationHost(destHostvalue));
                                                                                                       
        asreq.setAuthApplicationId(new AuthApplicationId(0));
                                                                                                       
        String userName = "userName";
        asreq.setUserName(new UserName(userName));
                                                                                                       
        asreq.setOriginStateId(new OriginStateId(0));
                                                                                                       
        ProxyInfo proxyInfo1, proxyInfo2;
        ProxyHost proxyHost1 = new ProxyHost("proxyHost1.abc.com");
        ProxyHost proxyHost2 = new ProxyHost("proxyHost2.abc.com");
        ProxyState proxyState1 = new ProxyState("state1");
        ProxyState proxyState2 = new ProxyState("state2");
        proxyInfo1.setProxyHost(proxyHost1);
        proxyInfo2.setProxyHost(proxyHost2);
        proxyInfo1.setProxyState(proxyState1);
        proxyInfo2.setProxyState(proxyState2);
        asreq.addProxyInfo(proxyInfo1);
        asreq.addProxyInfo(proxyInfo2);
                                                                                                       
        RouteRecord routeRecord1 = new RouteRecord("routeRecord1");
        RouteRecord routeRecord2 = new RouteRecord("routeRecord2");
        asreq.addRouteRecord(routeRecord1);
        asreq.addRouteRecord(routeRecord2);
                                                                                                       
        // add more AVP as ANY values
                                                                                                       
        System.out.println(asreq);
                                                                                                       
        //Embed C++ method call SendToStack(&asreq);

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
int SendAbortSessionAnswer(Command impl1)
{
        diameter.base.AbortSessionAnswer asans = new diameter.base.AbortSessionAnswer(false,false);
   
        diameter.base.AbortSessionRequest asreq = new diameter.base.AbortSessionRequest(impl1);
                                                                                                       
        String sessionIdvalue = "sessionId String";
        asans.setSessionId(new SessionId(sessionIdvalue));

        asans.setResultCode(new ResultCode(1000));

        String originHostvalue = "originHost String";
        asans.setOriginHost(new OriginHost(originHostvalue));

        String originRealmvalue = "originRealm String";
        asans.setOriginRealm(new OriginRealm(originRealmvalue));

        String userName = "userName";
        asans.setUserName(new UserName(userName));

        asans.setOriginStateId(new OriginStateId(0));
                                                                                                       
        String errorMessagevalue = "ErrorMessage";
        asans.setErrorMessage(new ErrorMessage(errorMessagevalue));
                                                                                                       
        String errorReportingvalue = "ErrorReporting";
        asans.setErrorReportingHost(new ErrorReportingHost(errorReportinvalue));
                                                                                                       
        FailedAVP failedAvp1;
        asans.addFailedAVP(failedAvp1);
                                                                                                       
        URI uri1i = new URI("domainName",URI.AAA,3880,URI.TCP,URI.DIAMETER);
        asans.addRedirectHost(uri1);
                                                                                                       
        RedirectHostUsage rhu = new RedirectHostUsage(RedirectHostUsage.ALL_SESSION);
        asans.setRedirectHostUsage(rhu);
                                                                                                       
        asans.setRedirectMaxCacheTime(new RedirectMaxCacheTime(500));
                                                                                                       
        ProxyInfo proxyInfo1, proxyInfo2;
        ProxyHost proxyHost1 = new ProxyHost("proxyHost1.abc.com");
        ProxyHost proxyHost2 = new ProxyHost("proxyHost2.abc.com");
        ProxyState proxyState1 = new ProxyState("state1");
        ProxyState proxyState2 = new ProxyState("state2");
        proxyInfo1.setProxyHost(proxyHost1);
        proxyInfo2.setProxyHost(proxyHost2);
        proxyInfo1.setProxyState(proxyState1);
        proxyInfo2.setProxyState(proxyState2);
        asans.addProxyInfo(proxyInfo1);
        asans.addProxyInfo(proxyInfo2);
                                                                                                       
        // add more AVP as ANY values
                                                                                                       
        System.out.println(asans);
                                                                                                       
        // Embed C++ method call SendToStack(&asans) or apiBase.Send(asans,sIdxBase,BASE_INTERFACE_APP_ID);

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
 ****************************************************************************/
int SendCapabilitiesExchangeAnswer(Command impl1)
{
        diameter.base.CapabilitiesExchangeAnswer ceans = new diameter.base.CapabilitiesExchangeAnswer(false,false);
                                                                                                       
        ceans.setResultCode(new ResultCode(1000));
                                                                                                       
        String originHostvalue = "originHost String";
        ceans.setOriginHost(new OriginHost(originHostvalue));
                                                                                                       
        String originRealmvalue = "originRealm String";
        ceans.setOriginRealm(new OriginRealm(originRealmvalue));
                                                                                                       
        Family family = new Family(1);
        String addressString = "address";
        Address address = new address(family,addressString);
        ceans.addHostIPAddress(new HostIPAddress(address));
                                                                                                       
        ceans.setVendorId(new VendorId(1));
                                                                                                       
        String productNameString = "Intellinet Diameter";
        ceans.setProductName(new ProductName(productNameString));
                                                                                                       
        ceans.setOriginStateId(new OriginStateId(1));
                                                                                                       
        String errorMessagevalue = "ErrorMessage";
        ceans.setErrorMessage(new ErrorMessage(errorMessagevalue));
                                                                                                       
        FailedAVP failedAvp1;
        ceans.addFailedAVP(failedAvp1);
                                                                                                       
        ceans.addSupportedVendorId(new SupportedVendorId(1));
        ceans.addAuthApplicationId(new AuthApplicationId(0));
        ceans.addInbandSecurityId(new InbandSecurityId(1));
        ceans.addAcctApplicationId(new AcctApplicationId(3));
                                                                                                       
        VendorSpecificApplicationId vsid;
        VendorId vendorId;
        vsid.addVendorId(vendorId);
        AuthApplicationId authApplicationId;
        vsid.setAuthApplicationId(authApplicationId);
        AcctApplicationId acctApplicationId;
        vsid.setAcctApplicationId(acctApplicationId);
        ceans.addVendorSpecificApplicationId(vsid);
                                                                                                       
        ceans.setFirmwareRevision(new FirmwareRevision(1));
                                                                                                       
        // add more AVP as ANY values
                                                                                                       
        System.out.println(ceans);
                                                                                                       
        // Embed C++ method call SendToStack(&ceans); 
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
int SendDeviceWatchdogAnswer(Command impl1)
{
        diameter.base.DeviceWatchdogAnswer dwans = new diameter.base.DeviceWatchdogAnswer(false,false);

        diameter.base.DeviceWatchdogRequest dwreq = new diameter.base.DeviceWatchdogRequest(impl1);
                                                                                                       
        dwans.setResultCode(new ResultCode(1000));
                                                                                                       
        String originHostvalue = "originHost String";
        dwans.setOriginHost(new OriginHost(originHostvalue));
                                                                                                       
                                                                                                       
        String originRealmvalue = "originRealm String";
        dwans.setOriginRealm(new OriginRealm(originRealmvalue));
                                                                                                       
        String errorMessagevalue = "ErrorMessage";
        dwans.setErrorMessage(new ErrorMessage(errorMessagevalue));
                                                                                                       
        FailedAVP failedAVP;
        dwans.addFailedAVP(failedAVP);
                                                                                                       
        dwans.setOriginStateId(new OriginStateId(1));
                                                                                                       
        System.out.println(dwans);
                                                                                                       
        // Embed C++ method call SendToStack(&dwans)

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
int SendDisconnectPeerAnswer(Command impl1)
{
        diameter.base.DisconnectPeerAnswer dpans = new diameter.base.DisconnectPeerAnswer(false,false);

        diameter.base.DisconnectPeerRequest dpreq = new diameter.base.DisconnectPeerRequest(impl1);
                                                                                                       
        dpans.setResultCode(new ResultCode(1));
                                                                                                       
        String originHostvalue = "originHost String";
        dpans.setOriginHost(new OriginHost(originHostvalue));
                                                                                                       
        String originRealmvalue = "originRealm String";
        dpans.setOriginRealm(new OriginRealm(originRealmvalue));
                                                                                                       
        String errorMessageString = "errorMessage";
        dpans.setErrorMessage(errorMessageString);
                                                                                                       
        FailedAVP failedAVP;
        dpans.addFailedAVP(failedAVP);
                                                                                                       
        System.out.println(dpans);
                                                                                                       
        // Embed C++ method call SendToStack(&dpans);
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
int SendReAuthAnswer(Command impl1)
{
        diameter.base.ReAuthAnswer raans = new diameter.base.ReAuthAnswer(false,false);
  
        diameter.base.ReAuthRequest rareq = new diameter.base.ReAuthRequest(impl1);

        String sessionIdvalue = "sessionId String";
        raans.setSessionId(new SessionId(sessionIdvalue));                                                                                                        
        raans.setResultCode(new ResultCode(1000));
                                                                                                       
        String originHostvalue = "originHost String";
        raans.setOriginHost(new OriginHost(originHostvalue));

        String originRealmvalue = "originRealm String";
        raans.setOriginRealm(new OriginRealm(originRealmvalue));
                                                                                                       
        String userName = "userName";
        raans.setUserName(new UserName(userName));
                                                                                                       
        raans.setOriginStateId(new OriginStateId(1));
                                                                                                       
        String errorMessagevalue = "ErrorMessage";
        raans.setErrorMessage(new ErrorMessage(errorMessagevalue));
                                                                                                       
        String errorReportingvalue = "ErrorReporting";
        raans.setErrorReportingHost(new ErrorReportingHost(errorReportinvalue));
                                                                                                       
        FailedAVP failedAVP;
        raans.addFailedAVP(failedAVP);
                                                                                                       
        URI uri1 = new URI("domainName",URI.AAA,3880,URI.TCP,URI.DIAMETER);
        raans.addRedirectHost(new RedirectHost(uri1));
                                                                                                       
        RedirectHostUsage rhu = new RedirectHostUsage(RedirectHostUsage.ALL_SESSION);
        raans.setRedirectHostUsage(rhu);
                                                                                                       
        raans.setRedirectMaxCacheTime(new RedirectMaxCacheTime(500));
                                                                                                       
        ProxyInfo proxyInfo1, proxyInfo2;
        ProxyHost proxyHost1 = new ProxyHost("proxyHost1.abc.com");
        ProxyHost proxyHost2 = new ProxyHost("proxyHost2.abc.com");
	ProxyState proxyState1 = ProxyState("state1");
        ProxyState proxyState2 = new ProxyState("state2");
        proxyInfo1.setProxyHost(proxyHost1);
        proxyInfo2.setProxyHost(proxyHost2);
        proxyInfo1.setProxyState(proxyState1);
        proxyInfo2.setProxyState(proxyState2);
        raans.addProxyInfo(proxyInfo1);
        raans.addProxyInfo(proxyInfo2);
                                                                                                       
        // add more AVP as ANY values
                                                                                                       
        System.out.println(raans);
                                                                                                       
        // Embed C++ method call SendToStack(&raans)

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
int SendSessionTerminationAnswer(Command impl1)
{
        diameter.base.SessionTerminationAnswer stans = new diameter.base.SessionTerminationAnswer(false,false);

        diameter.base.SessionTerminationRequest streq = new diameter.base.SessionTerminationRequest(impl1);
                                                                                                       
        String sessionIdvalue = "sessionId String";
        stans.setSessionId(new SessionId(sessionIdvalue));
                                                                                                       
        stans.setResultCode(new ResultCode(1000));
                                                                                                       
        String originHostvalue = "originHost String";
        stans.setOriginHost(new OriginHost(originHostvalue));
                                                                                                       
        String originRealmvalue = "originRealm String";
        stans.setOriginRealm(new OriginRealm(originRealmvalue));
                                                                                                       
        String userName = "userName";
        stans.setUserName(new UserName(userName));
                                                                                                       
        String classString = "classString";
        stans.addClass(new Class(classString));
                                                                                                       
        String errorMessagevalue = "ErrorMessage";
        stans.setErrorMessage(new ErrorMessage(errorMessagevalue));
                                                                                                       
        String errorReportingvalue = "ErrorReporting";
        stans.setErrorReportingHost(new ErrorReportingHost(errorReportinvalue));
                                                                                                       
        FailedAVP failedAVP;
        stans.addFailedAVP(failedAVP);

        stans.setOriginStateId(new OriginStateId(1));
                                                                                                       
        URI uri1 = new URI("domainName",URI.AAA,3880,URI.TCP,URI.DIAMETER);
        stans.addRedirectHost(new RedirectHost(uri1));
                                                                                                       
        RedirectHostUsage rhu = new RedirectHostUsage(RedirectHostUsage.ALL_SESSION);
        stans.setRedirectHostUsage(rhu);
                                                                                                       
        stans.setRedirectMaxCacheTime(new RedirectMaxCacheTime(500));
                                                                                                       
        ProxyInfo proxyInfo1, proxyInfo2;
        ProxyHost proxyHost1 = new ProxyHost("proxyHost1.abc.com");
        ProxyHost proxyHost2 = new ProxyHost("proxyHost2.abc.com");
        ProxyState proxyState1 = new ProxyState("state1");
        ProxyState proxyState2 = new ProxyState("state2");
        proxyInfo1.setProxyHost(proxyHost1);
        proxyInfo2.setProxyHost(proxyHost2);
        proxyInfo1.setProxyState(proxyState1);
        proxyInfo2.setProxyState(proxyState2);
        stans.addProxyInfo(proxyInfo1);
        stans.addProxyInfo(proxyInfo2);
                                                                                                       
        // add more AVP as ANY values
                                                                                                       
        System.out.println(stans);
                                                                                                       
        // Embed C++ method call SendToStack(&stans)
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
int SendAccountingAnswer(Command impl1)
{
        diameter.base.AccountingAnswer aans = new diameter.base.AccountingAnswer(false,false);

        diameter.base.AccountingRequest areq = new diameter.base.AccountingRequest(impl1);
                                                                                                       
        String sessionIdvalue = "sessionId String";
        aans.setSessionId(new SessionId(sessionIdvalue));                                                                                                        
        aans.setResultCode(new ResultCode(1000));
                                                                                                       
        String originHostvalue = "originHost String";
        aans.setOriginHost(new OriginHost(originHostvalue));
                                                                                                       
        String originRealmvalue = "originRealm String";
        aans.setOriginRealm(new OriginRealm(originRealmvalue));
                                                                                                       
        aans.setAccountingRecordType(new AccountingRecordType(AccountingRecordType.EVENT_RECORD));
        aans.setAccountingRecordNumber(new AccountingRecordNumber(1));
        aans.setAcctApplicationId(new AcctApplicationId(1));
                                                                                                       
        VendorSpecificApplicationId vsid;
        VendorId vendorId;
        vsid.addVendorId(vendorId);
        AuthApplicationId authApplicationId;
        vsid.setAuthApplicationId(authApplicationId);
        AcctApplicationId acctApplicationId;
        vsid.setAcctApplicationId(acctApplicationId);
        aans.setVendorSpecificApplicationId(new VendorSpecificApplicationId(vsid));
                                                                                                       
        String userName = "userName";
        aans.setUserName(new UserName(userName));
                                                                                                       
        aans.setAccountingSubSessionId(new AccountingSubSessionId(1));
        aans.setAcctSessionId(new AcctSessionId("12345678"));
        aans.setAcctMultiSessionId(new AcctMultiSessionId("12345678"));
                                                                                                       
        String errorReportingvalue = "ErrorReporting";
        aans.setErrorReportingHost(new ErrorReportingHost(errorReportinvalue));
                                                                                                       
        aans.setAcctInterimInterval(new AcctInterimInterval(1));
        aans.setAccountingRealtimeRequired(new AccountingRealtimeRequired(AccountingRealtimeRequired.DELIVER_AND_GRANT));
                                                                                                       
        aans.setOriginStateId(new OriginStateId(0));
                                                                                                       
        aans.setEventTimestamp(new EventTimestamp(1));
                                                                                                       
        ProxyInfo proxyInfo1, proxyInfo2;
        ProxyHost proxyHost1 = new ProxyHost("proxyHost1.abc.com");
        ProxyHost proxyHost2 = new ProxyHost("proxyHost2.abc.com");
        ProxyState proxyState1 = new ProxyState("state1");
        ProxyState proxyState2 = new ProxyState("state2");
        proxyInfo1.setProxyHost(proxyHost1);
        proxyInfo2.setProxyHost(proxyHost2);
        proxyInfo1.setProxyState(proxyState1);
        proxyInfo2.setProxyState(proxyState2);
        aans.addProxyInfo(proxyInfo1);
        aans.addProxyInfo(proxyInfo2);
                                                                                                       
        // add more AVP as ANY values
                                                                                                       
        System.out.println(aans);
                                                                                                       
        // Embed C++ method call SendToStack(&answer)

    }
}
