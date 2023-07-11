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
 * LOG: $Log: client.java,v $
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
//#ident "$Id: client.java,v 3.1 2008/03/31 10:33:23 nvijikumar Exp $"

package app;

import java.net.*;
import java.util.*;
import java.io.*;

import com.intellinet.*;
import com.intellinet.diameter.*;
import diameter.base.*;

/**
 * Class   : diameterclientsocket
 * 
 * Purpose : This class contains the tcpip client socket implementation
 *
 */

class diameterclientsocket {

    public diameterclientsocket(String[] args)
    {
        createClient();
    }

/**
 *
 * Method      : createSessionTerminationRequest
 *
 * Input       : None
 *
 * Return Type : diameter.base.SessionTerminationRequest
 *
 */
    private diameter.base.SessionTerminationRequest createSessionTerminationRequest()
    {
            diameter.base.SessionTerminationRequest str = new diameter.base.SessionTerminationRequest(false,false);
            OriginHost oh = new OriginHost("oh");
            System.out.println(oh.toString());
            str.setOriginHost(oh);
            OriginRealm or = new OriginRealm("or");
            System.out.println(or);
            str.setOriginRealm(or);
            SessionId sessionId = new SessionId("sessionId");
            System.out.println(sessionId);
            str.setSessionId(sessionId);
            str.setDestinationRealm(new DestinationRealm("dr"));
            str.setAuthApplicationId(new AuthApplicationId(1));
            //str.setTerminationCause(new TerminationCause(TerminationCause.DIAMETER_LOGOUT));
            str.addClass(new diameter.base.Class("classString"));
            str.setOriginStateId(new OriginStateId(1));

            ProxyInfo proxyInfo1 = new ProxyInfo();
            ProxyInfo proxyInfo2 = new ProxyInfo();
            ProxyHost proxyHost1 = new ProxyHost("proxyHost1.abc.com");
            ProxyHost proxyHost2 = new ProxyHost("proxyHost2.abc.com");
            ProxyState proxyState1 = new ProxyState("state1");
            ProxyState proxyState2 = new ProxyState("state2");
            proxyInfo1.setProxyHost(proxyHost1);
            proxyInfo2.setProxyHost(proxyHost2);
            proxyInfo1.setProxyState(proxyState1);
            proxyInfo2.setProxyState(proxyState2);
            str.addProxyInfo(proxyInfo1);
            str.addProxyInfo(proxyInfo2);

            RouteRecord routeRecord1 = new RouteRecord("routeRecord1");
            RouteRecord routeRecord2 = new RouteRecord("routeRecord2");
            str.addRouteRecord(routeRecord1);
            str.addRouteRecord(routeRecord2);
          
//            System.out.println(str);
            return str;
    }

/**
 *
 * Method    : createClient
 *
 * Purpose   : This method creates a client socket, messages and send 
 *             the messages to a tcpip peer. 
 *             
 */
    void createClient()
    {
        try
        {
            // Create a client socket connecting the localhost
            // to the named host and port
            Socket clientSocket = new Socket("localhost",8001);
            System.out.println(clientSocket);

            // Obtain the OutputStream associated with the invoking socket            
            OutputStream outStream = clientSocket.getOutputStream();
            PrintStream printStream = new PrintStream(outStream);

            // Obtain the InputStream associated with the invoking socket
            InputStream inputStream = clientSocket.getInputStream();
            DataInputStream dataInputStream = new DataInputStream(inputStream);
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(dataInputStream));            

            // Buffered Input - Keyboard
            DataInputStream dataInputStream1 = new DataInputStream(System.in);
            BufferedReader bufferedReader1 = new BufferedReader(new InputStreamReader(dataInputStream1));

            String s1 = new String();

            while(true)
            {
                System.out.println("Select the message to be sent or else disconnect");
                System.out.println("\n1)CapabilitiesExchangeRequest\n2)ReAuthRequest\n");
                System.out.println("3)AccountingRequest\n4)DeviceWatchdogRequest\n");
                System.out.println("5)AbortSessionRequest\n6)DisconnectPeerRequest\n");
                System.out.println("7)SessionTerminationRequest\n99)To disconnect\n");

                int choice = Integer.parseInt(bufferedReader1.readLine());

                switch(choice)
                {
                   case 1: diameter.base.CapabilitiesExchangeRequest cer;//TBC

                   case 2: diameter.base.ReAuthRequest rar;//TBC

                   case 3: diameter.base.AccountingRequest ar;//TBC

                   case 4: diameter.base.DeviceWatchdogRequest dwr;//TBC

                   case 5: diameter.base.AbortSessionRequest asr;//TBC

                   case 6: diameter.base.DisconnectPeerRequest dpr;//TBC

                   case 7: diameter.base.SessionTerminationRequest 
                                       str = createSessionTerminationRequest();
                            s1 = str.toString();
                            // Send the message to the peer
                            printStream.println(s1);
                            break;
                    default:       
                            printStream.println("Client is disconnecting");
                            // close the InputStream and the OutputStream
                            outStream.close();
                            inputStream.close();
                            //End the client application
                            System.exit(0);
                            
                }
            }//while
        }
        catch(java.net.UnknownHostException e)
        {
            System.out.println(e);
        }
        catch(java.io.IOException e)
        {
            System.out.println(e);
        }
        catch(java.lang.NumberFormatException e)
        {
            System.out.println(e);
        }
        catch(java.lang.Exception e)
        {
            System.out.println(e);
        }

    }
}

/**
*
* Class    : client
* 
* Purpose  : This class contains the main method and acts as the entry point
*            for the client application
*
*/
public class client
{
    public static void main(String[] args)
    {
        // Create a diameter client socket
        diameterclientsocket cs = new diameterclientsocket(args);
    }
}
