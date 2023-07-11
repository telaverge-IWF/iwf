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
 * ID: $Id: app_main.cpp,v 3.1 2008/03/31 10:33:03 nvijikumar Exp $
 *
 * LOG: $Log: app_main.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:03  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.5  2006/11/17 07:38:58  kamakshilk
 * LOG: Registere API and Release indication added
 * LOG:
 * LOG: Revision 1.4  2006/11/16 14:00:00  kamakshilk
 * LOG: InitDiaDictParser() API added
 * LOG:
 * LOG: Revision 1.3  2006/11/14 09:48:40  kamakshilk
 * LOG: Handle error response and notification
 * LOG:
 * LOG: Revision 1.2  2006/11/07 13:29:52  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 2.4  2006/10/26 05:38:13  kamakshilk
 * LOG: Fix for issue ID 4615. Menu changes
 * LOG:
 * LOG: Revision 2.3  2006/10/17 12:09:07  kamakshilk
 * LOG: Added Routing based on AppId in IDC header
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:23:57  kamakshilk
 * LOG: Changes to work with ITS-Diameter APIs
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:38  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.10  2006/08/25 09:34:28  kamakshilk
 * LOG: Fix for Bug Id 4249
 * LOG:
 * LOG: Revision 1.9  2006/08/24 11:53:40  kamakshilk
 * LOG: Fix for Bug Ids 4113,4245 and 4246
 * LOG:
 * LOG: Revision 1.8  2006/08/09 08:29:52  kamakshilk
 * LOG: Reading Subscriber Profile Info from xml file
 * LOG:
 * LOG: Revision 1.7  2006/06/09 13:46:50  kamakshilk
 * LOG: RfRo support
 * LOG:
 * LOG: Revision 1.6  2006/06/05 12:11:54  yranade
 * LOG: Updates to compile with CC Compiler
 * LOG:
 * LOG: Revision 1.5  2006/05/23 06:21:19  adutta
 * LOG: Modified to handle indication with message
 * LOG:
 * LOG: Revision 1.4  2006/04/28 07:01:02  nvijikumar
 * LOG: Code Enhancement (Documentation).
 * LOG:
 * LOG: Revision 1.3  2006/04/25 12:35:02  nvijikumar
 * LOG: De-Register switch case added
 * LOG:
 * LOG: Revision 1.2  2006/04/25 10:33:29  nvijikumar
 * LOG: Fix for core dump (indication) and some enhancements
 * LOG:
 * LOG: Revision 1.1  2006/04/13 11:08:06  nvijikumar
 * LOG: Baseline demo programs
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

#include <app.h>
#include <idc_api.h>

#include <diameter/base/NONPROXYABLEERROR.h>
#include <diameter/base/PROXYABLEERROR.h>
                                                                                
using namespace diameter;
using namespace diameter::base;

/* gloabal variables */
static char hostIpAddress[20];
static int serverPort;
IDS_CONNECTION_TYPE conType;
static char connectType[20];

unsigned int SendAppId = 10000;
unsigned int ReceiveAppId = 10000;

char subsProfile[2000]; 
ITS_BOOLEAN isConnected = ITS_FALSE ,isTrying = ITS_FALSE;

/*.implementation:static
 ****************************************************************************
 *  Purpose: Handles the Error Commands received from the stack.
 *
 *  Input Parameters:
 *      const char** args: Arguments.
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
int HandleErrorResponse(const diameter::CommandImpl *impl)
{
    printf(("Error Answers Received"));
    if(impl->isProxyable())
    {
       PROXYABLEERROR err(*impl);
       cout<<endl<<err<<endl;
    }
    else
    {
       NONPROXYABLEERROR err(*impl);
       cout<<endl<<err<<endl;
    }
                                                                                
    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Method is used to print the Parameters, those are taken at
 *           Run time.
 *
 *  Input Parameters:
 *      const char** args: Arguments.
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
void Usage(const char** args)
{
    printf("Usage: %s ", args[0]);
    printf("interactive\n");
    printf("Usage: %s ", args[0]);
    printf("-oh <value> | ");
    printf("-or <value> | ");
    printf("-dh <value> | ");
    printf("-dr <value>| ");
    printf("-sp <value>| ");
    printf("-srvip <value>| ");
    printf("-contype <value>| ");
    printf("\n");
    exit(0);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Method is used to parse the parameters according to the 
 *      pre-string given. Set those valuse to the global variables.
 *
 *  Input Parameters:
 *      int argc: Number of arguments.
 *      const char** args: Arguments.
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
void parseArguments(int argc, const char** args)
{
    int i = 1;
    int flag = 1;
    int ret = 0;

    if (argc == 1)
    {
        Usage(args);
    }

    for(; i < argc && flag; i++)
    {
        if(strcmp(args[i], "-oh") == 0)
        {
           SetOriginHost(args[++i]);
           printf("OH = %s\n", args[i]);
        }
        else if(strcmp(args[i], "-or") == 0)
        {
           SetOriginRealm(args[++i]);
           printf("OriginRealm = %s\n", args[i]);
        }
        else if(strcmp(args[i], "-dh") == 0)
        {
           SetDestinationHost(args[++i]);
           printf("DH = %s\n", args[i]);
        }
        else if(strcmp(args[i], "-dr") == 0)
        {
           SetDestinationRealm(args[++i]);
           printf("DR = %s\n", args[i]);
        }
        else if(strcmp(args[i], "-sp") == 0)
        {
           serverPort=atoi(args[++i]);
           printf("SP = %s\n",args[i]);
        }
       else if(strcmp(args[i], "-srvip") == 0)
       {
          strcpy(hostIpAddress,args[++i]);
          printf("IDS Server = %s\n",args[i]);
       }
       else if(strcmp(args[i], "-contype") == 0)
       {
          strcpy(connectType,args[++i]);
          if(strcmp(connectType,"primary") == 0)
          {
              conType=IDS_PRIMARY_CONNECTION;
              printf("Connection Type: IDS_PRIMARY_CONNECTION\n");
          }
          else if(strcmp(connectType,"backup") == 0)
          {
              conType=IDS_BACKUP_CONNECTION;
              printf("Connection Type: IDS_BACKUP_CONNECTION\n");
          }
          else
          {
              printf(" invalid connection type\n");
          }
       }
       else
       {
          Usage(args);
       }
    }
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: Thread Function that handles messages received from the
 *      stack.
 *
 *  Input Parameters:
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
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    24-08-06   Bug # 4245,4246    Flag set/rest after receiving 
 *                                             regAck and deregAck.
 *
 ****************************************************************************/
void* Recieve(void* args)
{
    printf("In Recieve thread\n");

    IDSCLApi api;
    IDS_MESSAGE ev;
    bool message;

    while(1)
    { 
        // fills the memory area and point that memory with variable ev
        memset(&ev, 0, sizeof(IDS_MESSAGE));
        api.ReceiveEvent(&ev);

        message = false;

        printf("\n<---------- MessageType %d ------------------->\n",
                                                                ev.msg_type);
        
        // If received Message type is DIAMETER_MSG then go further
        if (ev.msg_type == DIAMETER_MSG)
        {
            switch(ev.u.diaInfo.msgType)
            {
                case ITS_DIA_MSG_TYPE_DATA:
                    message = true;
                    printf("\nReceived message from Stack\n");
                break;
                case ITS_DIA_MSG_TYPE_IND:
                    printf("\nReceived Indication from Stack\n");
                break;
                case ITS_DIA_MSG_TYPE_IND_WITH_DATA:
                    message = true;
                    printf("\nReceived Indication with message from Stack\n");
                break;
                default:
                    printf("\nReceived unknown indication from Stack\n");
                break;
            }

            // If not an indication, then it is a Command Message
            if (message)
            {        
                printf("\n<---------- Diameter message ------------------->\n");

                printf("\tDiameter session index <%d>\n",
                                                ev.u.diaInfo.sessionIndex);

                // Get the command instance from the message.
                const diameter::CommandImpl* impl = ev.u.diaInfo.cImpl;
                unsigned int RecivesIdx = ev.u.diaInfo.sessionIndex;

                // If message is not NULL process the messages based on
                // Application ID.
                if(impl)
                {
                    ReceiveAppId=ev.u.diaInfo.appIdentifier;

                    printf("\tApplication Id <%d>\n", ReceiveAppId);

                    if(impl->isError())
                    {
                       HandleErrorResponse(impl);
                       continue;
                    }

                    switch(ReceiveAppId)
                    {
                    case WX_INTERFACE_APP_ID:
                        WxMessage(impl,RecivesIdx);
                    break;
                    default:
                        printf("Invalid AppID\n");
                    break;
                    }
                }
            }
            else
            {
                printf("Indication type: <%d> for session index <%u>\n",
                        ev.u.diaInfo.indication, ev.u.diaInfo.sessionIndex);
            }
        }

        // If the message is acknowledge for Register
        // Display the result of the requested message
        // Display the Registered server IP and Port
        if (ev.msg_type == REGISTER_ACK_MSG)
        {
            printf("Registered result: %d\n", ev.u.regAck.result);
            printf("Registered error:  %d\n", ev.u.regAck.errorCode);
            printf("Registered with server ip:  %s\n", ev.u.regAck.ipAddr);
            printf("Registered with server port: %d\n", ev.u.regAck.port);
            if (ev.u.regAck.errorCode < 0)
            {
               printf("Client registration failed \n");
            }
        }

        // If the message is acknowledge for DeRegister
        // Display the result of the requested message
        if (ev.msg_type == DEREGISTER_ACK_MSG)
        {
            printf("Deregistered result: %d\n", ev.u.deregAck.result);
            printf("Deregistered error:  %d\n", ev.u.deregAck.errorCode);
            if (ev.u.deregAck.errorCode < 0)
            {
               printf("Client deregistration failed \n");
            }
        }
        // If the message a notification from Distributed Server
        if (ev.msg_type == DIASERVER_NOTIFY_MSG)
        {
            printf("Failure Notification from Server for\n");
            printf("Diameter Application Id <%u> session index <%u>\n",
                       ev.u.notifyInfo.appId, ev.u.notifyInfo.sessionIndex);
            if (ev.u.notifyInfo.data)
            {
                printf("Session Id : %s\n", ev.u.notifyInfo.data);
                free(ev.u.notifyInfo.data);
                ev.u.notifyInfo.data = NULL;
            }
            switch(ev.u.notifyInfo.indType)
            {
               case IDS_MSG_ENCODE_FAIL_IND:
                   printf("Failed to encode message\n");
                   break;
               case IDS_SENDTO_STACK_FAIL_IND:
                   printf("Failed to send message to Stack\n");
                   break;
               case IDS_RELEASE_SESS_FAIL_IND:
                   printf("Failed to release the diameter session\n");
                   break;
               case IDS_RELEASE_SESS_SUCCESS_IND:
                   printf("Diameter session released \n");
                   break;
            }
        }

    } 
    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Thread Method used to Connect to the Distributed Server 
 *
 *  Input Parameters:
 *      void* args: Arguments (if any).
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
void* ConnectToServer(void *args)
{
   IDSCLApi api;
   ITS_INT retVal = ITS_SUCCESS;

   isTrying = ITS_TRUE;

   // Initializes the connectivity with the IDS Server
   retVal = api.Initialize(hostIpAddress,serverPort);
   if (retVal == ITS_SUCCESS)
       isConnected = ITS_TRUE;

   isTrying = ITS_FALSE;

   pthread_exit(NULL);
 
   return NULL;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Thread Method used to to get the Menu options for connection,
 *      Register, De-Register and Send Messages.
 *
 *  Input Parameters:
 *      void* args: Arguments (if any).
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
 *   Kamakshi    24-08-06   Bug # 4113       Thread created for Connect.
 *   Kamakshi    24-08-06   Bug # 4245,4246  Flags checked before Register,
 *                                           Deregister and Send
 *   Kamakshi    25-08-06   Bug # 4249       ClientId and AppId value read 
 *                                           checked if numeric.
 *
 ****************************************************************************/
void* PrintMenu(void* args)
{
   int input = 0;
   int choice = 0;
   IDS_MESSAGE reg;
   IDSCLApi api;
   pthread_t threadConnect;
   string  inStr;
   int len = 0;
   int idx = 0;

   api.SetHostInfo(GetOriginHost(),GetOriginRealm());

   while (1)
   {
       printf("\n############## Choice ###########\n");

       printf("1.Connect\n");
       printf("2.Register\n");
       printf("3.DeRegister\n");
       printf("4.Send\n");
       printf("9.Terminate\n");

       printf("\n###############################\n");

       cin >> inStr;
       choice = atoi(inStr.c_str());

       switch(choice)
       {
           case 1:
               // Connect to the server , if client is not already connected
               // or if client is not already trying to connect.
               if (!isConnected && !isTrying)
               {
                   // Create a thread to Connect to the server 
                   pthread_create(&threadConnect, NULL, ConnectToServer, NULL);
               }
               else if (isConnected)
               {
                   printf("Already Connected to the Server \n");
               }
           break;

           case 2:

               if (!isConnected)
               {
                   printf("Not Connected to Server \n");
               }
               else if (!api.IsRegistered())
               {
                   printf("\nClient ID\n");
                   cin >> inStr;
                   len = inStr.length();
                   idx = 0;
                   while(idx != len)
                   {
                       if (!isdigit(inStr.c_str()[idx]))
                       {
                            printf("Please enter only numeric values \n");
                            inStr = "";
                            break;
                       }
                       idx++;
                   }
                   if (inStr == "")
                       break;
                   input = atoi(inStr.c_str());
                   reg.clientID = input;

                   reg.msg_type = REGISTER_MSG;

                   reg.u.regInfo.routing_criteria = IDS_APP_IDENTIFIER;
                   printf("\nApp ID\n");
                   cin >> inStr;
                   len = inStr.length();
                   idx = 0;
                   while(idx != len)
                   {
                       if (!isdigit(inStr.c_str()[idx]))
                       {
                            printf("Please enter only numeric values \n");
                            inStr = "";
                            break;
                       }
                       idx++;
                   }
                   if (inStr == "")
                       break;
                   SendAppId = atoi(inStr.c_str());

                   reg.u.regInfo.appIdentifier = SendAppId;
                   reg.u.regInfo.connectionType = conType;
                           
                   // Registers the Client w.r.t Client ID and 
                   // Application ID.
                   api.Register(&reg);
               }
               else
               {
                   printf("Registered already : ClientId [%d], AppId [%d] \n",
                       reg.clientID, reg.u.regInfo.appIdentifier);
               }
           break;

           case 3:

               if (api.IsRegistered())
               {
                   reg.msg_type = DEREGISTER_MSG; 

                   // De-Register the Registered Client 
                   api.DeRegister(&reg);
               }
               else
               {
                   printf("Client not Registered \n");
               }
            break;

           case 4:
      
               if (api.IsRegistered())
               {
               // Display the Menu to send the message to stack based on the
               // Registered Application ID. 
                   switch(SendAppId)
                   {
                       case WX_INTERFACE_APP_ID:
                           WxMenu();
                       break;
                       default:
                           printf("Please enter valid AppID\n");
                       break;
                   }
               }
               else
               {
                   printf("Client not Registered \n");
               }
           break;

           case 9:
               IDSCL_Terminate();
               exit(1);
           break;

           default:
               printf("Please enter valid input\n");
           break;
       }
   }
   return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: ReadInSubsProfile function reads the SubsProfile.xml file 
 *      and fills into a character array.
 *
 *  Input Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value: None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void ReadInSubsProfile()
{
    FILE *fp;
    int i=0;
                                                                                
    subsProfile[0] = '\0';
                                                                                
    if((fp = fopen("SubsProfile.xml","r")) != NULL)
    {
       while ((subsProfile[i] = fgetc(fp)) !=EOF)
       {
          i++;
       }
       subsProfile[i] = '\0';
    }
    else
    {
       strcpy(subsProfile,"Subscriber not provisioned");
    }
    //Printing User Data Read
    //printf("User Data Read %s", subsProfile);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose: Main function starts here, it creates two threads one for 
 *      Sending the messages and another one for Recieving.
 *
 *  Input Parameters:
 *      int argc: Number commandline arguments.
 *      const char** argv: commandline arguments.
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
int main(int argc, const char** argv)
{
    parseArguments(argc, argv);
    pthread_t thread, threadPrint;
    int ret =0;
    IDSCLApi api;

    api.InitDiaDictParser();

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

