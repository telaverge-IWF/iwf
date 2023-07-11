/****************************************************************************
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
 * ID: $Id: client.cpp,v 3.1 2008/03/31 10:33:03 nvijikumar Exp $
 *
 * LOG: $Log: client.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:03  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.4  2006/05/30 09:37:50  yranade
 * LOG: Changes to compile with CC compiler on solaris 10.
 * LOG:
 * LOG: Revision 1.3  2006/04/06 07:56:59  adutta
 * LOG: Test app modified to send multiple req/ans in same sess.
 * LOG:
 * LOG: Revision 1.2  2006/03/14 06:39:57  adutta
 * LOG: Added new apis
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:14:01  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


using namespace std;


#include <idc_api.h>

#include <diameter/base/ReAuth.h>
#include <diameter/base/AbortSession.h>
#include <diameter/base/SessionTermination.h>
#include <diameter/base/Accounting.h>
#include <diameter/base/CapabilitiesExchange.h>
#include <diameter/base/DeviceWatchdog.h>
#include <diameter/base/DisconnectPeer.h>

using namespace diameter;
using namespace base;



/* gloabal variables */

/* public variable */
static char* hostIpAddress;
static int serverPort;
char*  style;
unsigned int appId = 10000;

string sessIdString;
unsigned int sIdx = 0;

void
SendReAuthRequest(Command* ra)
{
   IDSCLApi api;
   static bool first = false;

// [1] Create ReAuthRequest object.

    ReAuthRequest rar(false, false);

// [2] Insert data in the created CapabilitiesExchangeRequest object.

// [2.1] Populate Mandatories.

// [2.1.1] Populate Fixed Mandatories.

// [2.1.1.1] Populate Fixed paramete "Session-Id".

   if (!first)
   {
   api.AllocateSessionIndex(10000, sIdx, sessIdString);
   printf("\tSession Index: %d\n", sIdx);
   first = true;
   }

   rar.setSessionId(SessionId(sessIdString));

// [2.1.2] Populate required Mandatories.

// [2.1.2.1] Populate required paramete "Origin-Host".
// Set the Origin-Host AVP.
// The data type of Origin-Host is DiameterIdentity
// This AVP identifies the endpoint that originated the Diameter message
// This AVP SHOULD be placed as close to the Diameter header
// The AVP Code of Origin-Host is 264.
    OriginHost origh("nemocl");
    rar.setOriginHost(origh);

// [2.1.2.2] Populate required paramete "Origin-Realm".
// Set the Origin-Realm AVP.
// The data type of Origin-Realm is DiameterIdentity.
// This AVP contains the Realm of the originator of any Diameter message.
// This AVP SHOULD be placed as close to the Diameter header.
// The AVP Code of Origin-Realm is 296.
   OriginRealm origr("india.internal.net");
    rar.setOriginRealm(origr);

// [2.1.2.3] Populate required paramete "Destination-Realm".
// Set the Destination-Realm AVP.
// The data type of Destination-Realm is DiameterIdentity.

// This AVP contains the Realm the message is to be routed to.
// This AVP SHOULD be placed as close to the Diameter header.
// The AVP Code of Destination-Realm is 283.
    DestinationRealm desr("india.internal.net");
    rar.setDestinationRealm(desr);

// [2.1.2.4] Populate required paramete "Destination-Host".
// Set the Destination-Host AVP.
// The data type of Destination-Host is DiameterIdentity
// This AVP identifies the endpoint where  the Diameter message is destinated
// This AVP SHOULD be placed as close to the Diameter header
// The AVP Code of Destination-Host is 293.
    DestinationHost desh("nemo");
    rar.setDestinationHost(desh);

// [2.1.2.5] Populate required parameter "Auth-Application-Id".
// Set the Auth-Application-Id AVP.
// The data type of Auth-Application-Id is Unsigned32.
// This AVP is used in order to advertise support of the Authentication and
// Authorization portion of an application
// The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId authid(258);
    rar.setAuthApplicationId(authid);

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

    UserName uname1("adam.smith");
    rar.setUserName(uname1);

// [2.2.2] Populate optional parameter "Origin-State-Id".
// Set the Origin-State-Id AVP.
// The data type of Origin-State-Id is Unsigned32.
// This is a monotonically increasing value that is advanced whenever a
// Diameter entity restarts with loss of previous state
// The AVP Code of Origin-State-Id is 278.
    OriginStateId origsid(1);
    rar.setOriginStateId(origsid);

// [2.2.3] Populate optional parameter "Proxy-Info".
// Set the Proxy-Info AVP.
// The data type of Proxy-Info is Grouped.
// This AVP gives information about proxy.
// The AVP Code of Proxy-Info is 284.

    ProxyInfo pi1;

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
    //    ProxyState ps1("state0");
    //pi1.setProxyState(ps1);
    //rar.addProxyInfo(pi1);

// [2.2.4] Populate optional parameter "Route-Record".
// Set the Route-Record AVP.
// The data type of Route-Record is DiameterIdentity.
// The identity added in this AVP MUST be the same as the one received in
// the Origin-Host of the Capabilities Exchange message.
// The AVP Code of Route-Record is 282.
    RouteRecord rrec("jerry.india.internal.net");
    rar.addRouteRecord(rrec);

// [3] Use appropriate application specific logic to Send object

// To stop here in  console application.

    std::cout << rar << std::endl;

    api.Send(rar, sIdx, appId);
}


void* Recieve(void* args)
{
    printf("In Recieve thread\n");

    IDSCLApi api;
    IDS_MESSAGE ev;

    while(1)
    { 
        memset(&ev, 0, sizeof(IDS_MESSAGE));
        api.ReceiveEvent(&ev);


        if (ev.msg_type == DIAMETER_MSG)
        {
                printf("\n<---------- Diameter message ------------------->\n");

               
                printf("\tDiameter session index <%d>\n", 
                                                ev.u.diaInfo.sessionIndex);

            
                diameter::CommandImpl* impl = ev.u.diaInfo.cImpl;
                if (impl && impl->isRequest())
                {
                    if (impl->getCommandCode() == 258)
                    {
                        printf("\n<--------------------------------------->\n");
                        ReAuthRequest rreq(*impl);
                        cout << "rreq" << rreq << endl;
                        printf("\n<--------------------------------------->\n");

                        const SessionId& sid = rreq.getSessionId();
                        const OriginHost& oh = rreq.getOriginHost();
                        const DestinationHost& dh = rreq.getDestinationHost();

                        sIdx = ev.u.diaInfo.sessionIndex;
                        appId = impl->getApplicationId();

                        // Send Answer
                        ReAuthAnswer rra;
                        rra.setSessionId(sid);
                        rra.setOriginHost(OriginHost(dh.value()));
                        ResultCode rcode(1u);
                        rra.setResultCode(rcode); 

                        api.Send(rra, sIdx, appId);
                    }
                }
                else
                {
                    if (impl && impl->getCommandCode() == 258)
                    {  
                        printf("\n<--------------------------------------->\n");
                        ReAuthAnswer rra(*impl);
                        cout << "\trra" << rra << endl;
                        printf("\n<--------------------------------------->\n");
                   }
               } 

               if (ev.u.diaInfo.msgType == ITS_DIA_MSG_TYPE_IND)
               {
                   printf("\n<--------Diameter indication -------------->\n\n");

                   printf( "\tIndication type: ", ev.u.diaInfo.indication);
               }
               printf("\n\n");
        }
      

        if (ev.msg_type == REGISTER_ACK_MSG)
        {
            printf("\n<--------------------------------------------->\n");
            printf("\tRegister Ack Message at the applicaiton\n");
            printf("\tRegister Ack result %d\n", ev.u.regAck.result);
            printf("\tRegister Ack error %d\n", ev.u.regAck.errorCode);
            printf("\tRegistered server i/p %s\n", ev.u.regAck.ipAddr);
            printf("\tRegistered server i/p port %d\n", ev.u.regAck.port);
            printf("\n<--------------------------------------------->\n");
        }

    } 
    return (NULL);
}
    
void* PrintMenu(void* args)
{
   int input = 0;
   int choice = 0;
   unsigned char buffer[256];
   IDS_CONNECTION_TYPE conType;
   IDS_MESSAGE reg;
   IDSCLApi api;


   while (1)
   {
       printf("\n############## Choice ###########\n");

       printf("1.Connect\n");
       printf("2.Register\n");
       printf("3.Send\n");
       printf("0.Terminate\n");

       printf("\n###############################\n");

       scanf("%d", &input);

       switch(input)
       {
           case 1:
               conType = IDS_PRIMARY_CONNECTION;
               api.Initialize("172.16.3.1", 9999);
           break;

           case 2:
               printf("\nClient ID\n");
               scanf("%d", &input);
               reg.clientID = input;

               reg.msg_type = REGISTER_MSG;

               reg.u.regInfo.routing_criteria = IDS_APP_IDENTIFIER;
               printf("\nApp ID\n");
               scanf("%d", &appId);
               reg.u.regInfo.appIdentifier = appId;

               reg.u.regInfo.connectionType = IDS_PRIMARY_CONNECTION;

               api.Register(&reg);

           break;

           case 3:
               Command* com ;
               SendReAuthRequest(com);

           break;

           case 0:
               exit(1);
           break;

       }

   }
   return (NULL);
}


int main()
{
    pthread_t thread, threadPrint;
    int ret =0;
    IDSCLApi api;


    /* Specify absolute path if not in the pwd */
    api.SetDictionaryFile("dictionary");


    printf("\n\t *******************************************\n");
    printf("\t *****  IntelliNet Technologies, Inc.    *****\n");
    printf("\t *****  IntelliNet Diameter Client Test  *****\n");
    printf("\t *******************************************\n\n\n");


    /* Receive thread */
    pthread_create(&thread, NULL, Recieve, NULL);

    /* Send thread */
    pthread_create(&threadPrint, NULL, PrintMenu, NULL);

    /* Suspend the main */
    pthread_join(thread, NULL);
    
}

