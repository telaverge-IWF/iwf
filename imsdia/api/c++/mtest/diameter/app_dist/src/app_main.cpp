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
 * ID: $Id: app_main.cpp,v 3.9.46.1.4.1 2013/07/31 07:29:26 vsarath Exp $
 *
 * LOG: $Log: app_main.cpp,v $
 * LOG: Revision 3.9.46.1.4.1  2013/07/31 07:29:26  vsarath
 * LOG: Fix for coverity warnings
 * LOG:
 * LOG: Revision 3.9.46.1  2013/02/27 08:49:06  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.9  2010/09/22 05:36:49  vkumara
 * LOG: GlobalUniqueAddr base routing support
 * LOG:
 * LOG: Revision 3.8  2010/07/07 08:28:22  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 3.7  2009/03/19 16:33:49  ssaxena
 * LOG: Made Changes for the Redirect Application Identifier.
 * LOG:
 * LOG: Revision 3.6  2008/12/29 10:54:31  ssaxena
 * LOG: Merge the changes from aim/client/demo/app_main.cpp
 * LOG:
 * LOG: Revision 3.5  2008/12/26 06:53:55  sureshj
 * LOG: Fix for the issue 1395. Decoding indications from IDS.
 * LOG:
 * LOG: Revision 3.4  2008/04/24 11:36:37  avinashks
 * LOG: Fix for Whizible Issue id: 890
 * LOG: Changes done to print error response which comes with Error.
 * LOG:
 * LOG: Revision 3.3  2008/04/22 11:49:10  avinashks
 * LOG: Fix for Whizible Issue id: 890
 * LOG: Changes done to print Error Response properly on IDC.
 * LOG:
 * LOG: Revision 3.2  2008/04/16 11:05:55  avinashks
 * LOG: Changes done for Application to support agents.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:06  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.6  2008/03/27 11:31:37  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 1.3.4.2  2007/04/16 08:50:07  rrath
 * LOG: Changes to Print Session-Id and Indication
 * LOG:
 * LOG: Revision 1.3.4.1  2007/04/04 06:18:09  nvijikumar
 * LOG: Get appIdType from user.
 * LOG:
 * LOG: Revision 1.3  2007/01/19 14:45:49  kamakshilk
 * LOG: Fix for Memory leak
 * LOG:
 * LOG: Revision 1.2  2006/12/22 13:38:20  nvijikumar
 * LOG: Get Backup server IP and port number from Run script.
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:09:04  kamakshilk
 * LOG: Common Files required for distributed set up
 * LOG:
 * LOG: Revision 1.5  2006/11/17 07:07:26  kamakshilk
 * LOG: ReleaseSesion Added
 * LOG:
 * LOG: Revision 1.4  2006/11/16 13:44:56  kamakshilk
 * LOG: InitDiaDictParser() API added
 * LOG:
 * LOG: Revision 1.3  2006/11/14 09:47:53  kamakshilk
 * LOG: Handle error response and notification
 * LOG:
 * LOG: Revision 1.2  2006/11/07 13:12:37  kamakshilk
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
#include <diameter/base/BaseGenericCommand.h>

#include <diameter/base/NONPROXYABLEERROR.h>
#include <diameter/base/PROXYABLEERROR.h>
                                                                                
using namespace diameter;
using namespace diameter::base;

/* gloabal variables */
static char hostIpAddress[20];
static int serverPort;
static char bkhostIpAddress[20];
static int bkserverPort;

IDS_CONNECTION_TYPE conType;
IDS_TRANS_TYPE transType;
static char connectType[20];
static char transportType[20];

unsigned int sendAppId     = 10000;
unsigned int sendAppIdType = 0;
unsigned int receivedAppId = 10000;
unsigned int regAppId      = 0;

char subsProfile[2000]; 
ITS_BOOLEAN isConnected = ITS_FALSE ,isTrying = ITS_FALSE;
ITS_BOOLEAN isConnectedBk = ITS_FALSE ,isTryingBk = ITS_FALSE;
ITS_BOOLEAN ifRedundancy = ITS_FALSE;

IDSCLApi smplApi;

ApplicationMode appMode = UNIT_TEST ;
LoadGenFunc TrafficGeneratorFunc = NULL;

extern int DisplayAppMenu();
extern int HandleDiaAppMsg(const diameter::CommandImpl *impl,
                                             unsigned int &sIdx);
 
/**
 * Global Vector object to hold the Registration Information with IDS_MESSAGE.
 */
 vector<IDS_MESSAGE> regVect;
 int  StoreRegInfo(IDS_MESSAGE* msg);
 void ReleaseRegInfo();
 IDS_MESSAGE* RetrieveRegInfo(ITS_UINT appId);
 IDS_MESSAGE* GetFirstRegInfo();
 static ITS_BOOLEAN clFlag = IDS_FALSE;

#define DISC_CAUSE_TYPE_TO_TEXT(x) \
    ((x== DisconnectCause::REBOOTING)  ? "REBOOTING"   :\
    ((x== DisconnectCause::BUSY)       ? "BUSY"        :\
    ((x== DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU)  ? \
          "DO_NOT_WANT_TO_TALK_TO_YOU" :\
          "INVALID")))
 
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
    ITS_INT pinfo_avp_count=0, avpCount;
    ProxyInfo *pinf=NULL;
    ITS_INT ret = (!ITS_SUCCESS);

    const char *oriHost = GetOriginHost();

    printf(("Error Answers Received"));

    if(impl->isProxyable())
    {
        PROXYABLEERROR err(*impl);
        Command *cmd = (Command *) &err;
        diameter::base::BaseGenericCommand *gCmd =
                                (diameter::base::BaseGenericCommand *) cmd;
        pinfo_avp_count = gCmd->countProxyInfo();

        for(avpCount=0; avpCount < pinfo_avp_count; avpCount++)
        {
            if(!strcmp(oriHost,
                       gCmd->getProxyInfo(avpCount)->getProxyHost(). \
                       value().c_str()))
            {
                const ProxyInfo *pinfo1 = gCmd->getProxyInfo(avpCount);
                pinf = (ProxyInfo*) pinfo1;

                if ((pinf->removeAVP(pinf->getProxyHost())) == ITS_SUCCESS)
                {
                    APP_TRACE_DEBUG(("Proxy-Host AVP removed successfully"));
                }
                else
                {
                    APP_TRACE_ERROR(("Unable to remove Proxy-Host AVP"));
                }
                if ((pinf->removeAVP(pinf->getProxyState())) == ITS_SUCCESS)
                {
                    APP_TRACE_DEBUG(("Proxy-State AVP removed successfully"));
                }
                else
                {
                    APP_TRACE_ERROR(("Unable to remove Proxy-State AVP"));
                }
                if (((Command*)gCmd)->removeAVP(*pinf) == ITS_SUCCESS)
                {
                    APP_TRACE_DEBUG(("Proxy-Info AVP removed successfully"));
                }
                else
                {
                    APP_TRACE_ERROR(("Unable to remove Proxy-Info AVP"));
                }

                if ((ret = SendDiaAppMsg(*gCmd, gCmd->getSessionIndex())) != ITS_SUCCESS)
                {
                    APP_TRACE_ERROR(("SendDiaAppMsg Failure"));
                }
                return ret;
            }
        }

        if(pinfo_avp_count == 0)
        {
            cout<<endl<<err<<endl;
            return ITS_SUCCESS;
        }
        else if(avpCount >= pinfo_avp_count)
        {
            cout<<endl<<"Error in Message"<<endl;
            cout<<endl<<err<<endl;
            return (!ITS_SUCCESS);
        }
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
    printf("-bksp <value>| ");
    printf("-bksrvip <value>| ");
    printf("-contype <value>| ");
    printf("-transtype <value>| ");
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
       else if(strcmp(args[i], "-bksp") == 0)
       {
           bkserverPort=atoi(args[++i]);
           printf("Backup SP = %s\n",args[i]);
       }
       else if(strcmp(args[i], "-bksrvip") == 0)
       {
          strcpy(bkhostIpAddress,args[++i]);
          ifRedundancy = ITS_TRUE;
          printf("Backup-IDS Server = %s\n",args[i]);
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
       else if(strcmp(args[i], "-transtype") == 0)
       {
          strcpy(transportType,args[++i]);
          if(strcmp(transportType,"udp") == 0)
          {
              transType=IDS_UDP;
              printf("Connection Type: UDP\n");
          }
          else
          {
              transType=IDS_TCP;
              printf("Connection Type: TCP\n");
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
extern "C"
void* Recieve(void* args)
{
    printf("In Recieve thread\n");

    IDS_MESSAGE ev;
    bool message;
    IDSCLApi smplApi;

    while(1)
    { 
        // fills the memory area and point that memory with variable ev
        memset(&ev, 0, sizeof(IDS_MESSAGE));
        smplApi.ReceiveEvent(&ev);

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
                unsigned int receiveSesIdx = ev.u.diaInfo.sessionIndex;

                // If message is not NULL process the messages based on
                // Application ID.
                if(impl)
                {
                    receivedAppId=ev.u.diaInfo.appIdentifier;

                    printf("\tApplication Id <%u>\n", receivedAppId);

                    if(receivedAppId == BASE_INTERFACE_APP_ID)
                    {
                        HandleBaseMessages(impl,receiveSesIdx); 
                    }  
                    if (receivedAppId == regAppId )
                    {
                        HandleDiaAppMsg(impl, receiveSesIdx);
                    }
                    delete ev.u.diaInfo.cImpl;
                    ev.u.diaInfo.cImpl = NULL;
                }
            }
            else
            {
                printf("Indication type: <%d> for session index <%u>\n", 
                        ev.u.diaInfo.indication, ev.u.diaInfo.sessionIndex);

                switch(ev.u.diaInfo.indication)
                {
                    case DISCONECT_IND_FROM_STACK:
                        {
                          ITS_OCTET *diaInfoData = (ITS_OCTET*)ev.u.diaInfo.data;
 
                          ITS_OCTET peerHost[64];
                          memset(peerHost, 0, sizeof(peerHost)/sizeof
                                                         (ITS_OCTET));
                          ITS_OCTET ab=0; 
                          while(*diaInfoData != '.')
                          {
                            peerHost[ab++]= *(diaInfoData++);
                          } 
                          peerHost[ab]='\0';
                          printf("Peer Host            : %s\n", peerHost);
                          diaInfoData++;
 
                          ITS_OCTET peerRelam[64];
                          memset(peerRelam, 0, sizeof(peerRelam)/sizeof
                                                           (ITS_OCTET));
                          ITS_OCTET bc=0; 
                          while(*diaInfoData != ';')
                          {
                            peerRelam[bc++]= *(diaInfoData++);
                          } 
                          peerRelam[bc]='\0';
                          printf("Peer Relam           : %s\n", peerRelam);
                          diaInfoData++;
 
                          ITS_USHORT disCause = 0;
                          disCause = atoi((const char*)(diaInfoData));
                          printf("Disconnect Cause     : %s\n",
                                  DISC_CAUSE_TYPE_TO_TEXT(disCause));
                          printf("Disconnect Indication from stack\n");
                        }
                        break;
                    case TIME_OUT_IND_FROM_STACK:
                        {
                          printf("Session Id : %s\n", ev.u.diaInfo.data);
                          printf("Session Timeout Indication from stack\n");
                        }
                        break;
                    case AUTH_LIFE_TIME_OUT_IND_FROM_STACK:
                        {
                          printf("Session Id : %s\n", ev.u.diaInfo.data);
                          printf("Authorization-Lifetime Timeout Indication" \
                                 "from stack\n");
                        }
                        break;
                    case AUTH_GRACE_TIME_OUT_IND_FROM_STACK:
                        {
                          printf("Session Id : %s\n", ev.u.diaInfo.data);
                          printf(" Auth-Grace-Period Timeout Indication from" \
                                 "stack\n");
                        }
                        break;
                    case CORRUPTED_MSG_IND_FROM_STACK:
                        {
                          printf("Session Id : %s\n", ev.u.diaInfo.data);
                          printf("Corrupted message Indication from stack\n");
                        }
                        break;
                    case ACCT_INTERIM_TIME_OUT_IND_FROM_STACK:
                        {
                          printf("Session Id : %s\n", ev.u.diaInfo.data);
                          printf("Accounting Interim Timeout Indication" \
                                 "from stack\n");
                        }
                        break;
                    case FAILOVER_IND_FROM_STACK:
                        {
                          ITS_OCTET *diaInfoData = (ITS_OCTET*)ev.u.diaInfo.data;
 
                          ITS_OCTET peerHost[64];
                          memset(peerHost, 0, sizeof(peerHost)/sizeof
                                                         (ITS_OCTET));
                          ITS_OCTET ab=0;
                          while(*diaInfoData != '.')
                          {
                            peerHost[ab++]= *(diaInfoData++);
                          }
                          peerHost[ab]='\0';
                          printf("Peer Host            : %s\n", peerHost);
                          diaInfoData++;
 
                          ITS_OCTET peerRelam[64];
                          memset(peerRelam, 0, sizeof(peerRelam)/sizeof
                                                           (ITS_OCTET));
                          ITS_OCTET bc=0;
                          while(*diaInfoData != ';')
                          {
                            peerRelam[bc++]= *(diaInfoData++);
                          }
                          peerRelam[bc]='\0';
                          printf("Peer Relam           : %s\n", peerRelam);
                          diaInfoData++;
 
                          ITS_OCTET altPeerHost[64];
                          memset(altPeerHost, 0, sizeof(altPeerHost)/sizeof
                                                               (ITS_OCTET));
                          ITS_OCTET cd=0;
                          while(*diaInfoData != '.')
                          {
                            altPeerHost[cd++]= *(diaInfoData++);
                          }
                          altPeerHost[cd]='\0';
                          printf("Altenate Peer Host   : %s\n", altPeerHost);
                          diaInfoData++;
 
                          ITS_OCTET altPeerRelam[64];
                          memset(altPeerRelam, 0, sizeof(altPeerRelam)/sizeof
                                                                 (ITS_OCTET));
                          ITS_OCTET de=0;
                          while(*diaInfoData != '\0')
                          {
                            altPeerRelam[de++]= *(diaInfoData++);
                          }
                          altPeerRelam[de]='\0';
                          printf("Alternate Peer Relam : %s\n", altPeerRelam);
                          printf("FAILOVER Indication from stack\n");
                        }
 
                        break;
                    case FAILBACK_IND_FROM_STACK:
                        {
                          ITS_OCTET *diaInfoData = (ITS_OCTET*)ev.u.diaInfo.data;
 
                          ITS_OCTET peerHost[64];
                          memset(peerHost, 0, sizeof(peerHost)/sizeof
                                                         (ITS_OCTET));
                          ITS_OCTET ab=0;
                          while(*diaInfoData != '.')
                          {
                            peerHost[ab++]= *(diaInfoData++);
                          }
                          peerHost[ab]='\0';
                          printf("Peer Host            : %s\n", peerHost);
                          diaInfoData++;
 
                          ITS_OCTET peerRelam[64];
                          memset(peerRelam, 0, sizeof(peerRelam)/sizeof
                                                           (ITS_OCTET));
                          ITS_OCTET bc=0;
                          while(*diaInfoData != ';')
                          {
                            peerRelam[bc++]= *(diaInfoData++);
                          }
                          peerRelam[bc]='\0';
                          printf("Peer Relam           : %s\n", peerRelam);
                          diaInfoData++;
 
                          ITS_OCTET altPeerHost[64];
                          memset(altPeerHost, 0, sizeof(altPeerHost)/sizeof
                                                               (ITS_OCTET));
                          ITS_OCTET cd=0;
                          while(*diaInfoData != '.')
                          {
                            altPeerHost[cd++]= *(diaInfoData++);
                          }
                          altPeerHost[cd]='\0';
                          printf("Altenate Peer Host   : %s\n", altPeerHost);
                          diaInfoData++;
 
                          ITS_OCTET altPeerRelam[64];
                          memset(altPeerRelam, 0, sizeof(altPeerRelam)/sizeof
                                                                 (ITS_OCTET));
                          ITS_OCTET de=0;
                          while(*diaInfoData != '\0')
                          {
                            altPeerRelam[de++]= *(diaInfoData++);
                          }
                          altPeerRelam[de]='\0';
                          printf("Alternate Peer Relam : %s\n", altPeerRelam);
                          printf("FAILBACK Indication from stack\n");
                        }
                        break;
                }

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
            printf("Notification from Server for\n");
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
        if (ev.msg_type == GLOBAL_UNIQ_ADDR_ACK_MSG)
        {
            printf("Global Unique Addr Ack\n");
            if (ev.u.guaAck.action == IDS_GUA_ADD)
            {
                printf("Global Unique Addr Msg Action: Add\n");
            }
            else
            {
                printf("Global Unique Addr Msg Action: Del\n");
            }
            if (ev.u.guaAck.result == SUCCESS)
            {
                printf("Global Unique Addr Success\n");
            }
            else
            {
                printf("Global Unique Addr Failure\n");
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
extern "C"
void* ConnectToServer(void *args)
{
   ITS_INT retVal = ITS_SUCCESS;

   isTrying = ITS_TRUE;

   // Initializes the connectivity with the IDS Server
   retVal = smplApi.Initialize(hostIpAddress,serverPort);
   if (retVal == ITS_SUCCESS)
       isConnected = ITS_TRUE;

   isTrying = ITS_FALSE;

   pthread_exit(NULL);
 
   return NULL;
}

extern "C"
void* ConnectToBkServer(void *args)
{
   ITS_INT retVal = ITS_SUCCESS;

   isTryingBk = ITS_TRUE;

   // Initializes the connectivity with the IDS Server
   // Connect to backup
   retVal = smplApi.Initialize(bkhostIpAddress,bkserverPort);
   if (retVal == ITS_SUCCESS)
       isConnectedBk = ITS_TRUE;

   isTryingBk = ITS_FALSE;

   pthread_exit(NULL);
 
   return NULL;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility function to store the Registration Information.
 * 
 *  Input Parameters:
 *      takes IDS_MESSAGE* pointer as input.
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 * 
 *  Return Value:
 *      returns IDS_SUCCESS on successful storage and !IDS_SUCCESS on failure.
 *  Notes: 
 * 
 *  See Also:
 ****************************************************************************/
int 
StoreRegInfo(IDS_MESSAGE* msg)
{ 
    if (msg)
    {
        vector<IDS_MESSAGE>::iterator ii;
        for (ii =regVect.begin(); ii!=regVect.end() ; ii++)
        {
            if ((*ii).u.regInfo.appIdentifier == msg->u.regInfo.appIdentifier)
            {
                cout<<endl<<"AppId Already Exists"<<endl;
                return(!IDS_SUCCESS);
            }
        }
       regVect.push_back(*msg);
 
       return IDS_SUCCESS;
    }
    return(!IDS_SUCCESS);
}
 
/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility function to delete the complete elements in vector.
 *      used when the Deregistration is successful.
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ReleaseRegInfo()
{
    IDS_MESSAGE msg;
    vector<IDS_MESSAGE>::iterator ii;
    regVect.clear();
}
 
 
/*  implementation: public
****************************************************************************
*  Purpose:
 *      Utility function to retrieve an element from the vector for a
 *      particular Application-Id.
 *
 *  Input Parameters:
 *     Application Id which is unsigned int other than zero.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      returns the address of the element in the vector which contains the
 *      appId.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
IDS_MESSAGE*
RetrieveRegInfo(ITS_UINT appId)
{
    if (appId)
    {
        vector<IDS_MESSAGE>::iterator ii;
        for (ii =regVect.begin(); ii!=regVect.end() ; ii++)
        {
            if ((*ii).u.regInfo.appIdentifier == appId)
            {
                return(&(*ii));
            }
        }
    }
    cout<<endl<<"AppId is not Registered"<<endl;
    return NULL;
}
/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility function to get the first element in the vector.
 *
 *  Input Parameters:
 *      None.
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns the address of the first element in the vector if size is
 *      is not zero. In case of empty Vector returns NULL.
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
IDS_MESSAGE*
GetFirstRegInfo()
{
    vector<IDS_MESSAGE>::iterator ii;
    if (regVect.size()>0)
    {
        return (&(regVect[1]));
    }
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
extern "C"
void* PrintMenu(void* args)
{
   int input = 0;
   int choice = 0;
   IDS_MESSAGE reg;
   pthread_t threadConnect;
   pthread_t threadConnectBk;
   string  inStr;
   int len = 0;
   int idx = 0;

   //Coverity Issue Fix - 12421 - Uninitialized Scalar Variable
   memset(&reg, 0, sizeof (IDS_MESSAGE));
   smplApi.SetHostInfo(GetOriginHost(),GetOriginRealm());

   while (1)
   {
       printf("\n############## Choice ###########\n");

       printf("1.Connect\n");
       printf("2.Register\n");
       printf("3.DeRegister\n");
       printf("4.Send\n");
       printf("5.Send Globally Unique Ip Address \n");
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
               if (ifRedundancy)
               {
	               if (!isConnectedBk && !isTryingBk)
	               {
	                   // Create a thread to Connect to the backup server
	                   pthread_create(&threadConnectBk,NULL,ConnectToBkServer,NULL);
	               }
               }
               else if ( (!ifRedundancy && isConnected) ||
                         (ifRedundancy && (isConnected || isConnectedBk)))
 
               {
                   printf("Already Connected to the Server \n");
               }
           break;

           case 2:

               //if (!isConnected)
               if ((!ifRedundancy && !isConnected) ||
                  ((ifRedundancy && !isConnected && !isConnectedBk)))
               {
                   printf("Not Connected to Server \n");
                   break;
               }
               else if ( (ifRedundancy &&
                          (
                           (smplApi.IsConnectionUp(IDS_PRIMARY_CONNECTION) &&
                            smplApi.IsConnectionUp(IDS_BACKUP_CONNECTION) &&
                            !smplApi.IsRegisteredWith(IDS_PRIMARY_CONNECTION)&&
                            !smplApi.IsRegisteredWith(IDS_BACKUP_CONNECTION)
                           ) ||
                           (smplApi.IsConnectionUp(IDS_PRIMARY_CONNECTION) &&
                            !smplApi.IsConnectionUp(IDS_BACKUP_CONNECTION) &&
                            !smplApi.IsRegisteredWith(IDS_PRIMARY_CONNECTION)
                           )||
                           (smplApi.IsConnectionUp(IDS_BACKUP_CONNECTION) &&
                            !smplApi.IsConnectionUp(IDS_PRIMARY_CONNECTION) &&
                            !smplApi.IsRegisteredWith(IDS_BACKUP_CONNECTION)
                           )
                          )
                         ) ||
                         (!ifRedundancy && !smplApi.IsRegistered()) )
               {
                  if (!clFlag)
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
                   clFlag = ITS_TRUE;
                  }

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

                   sendAppId = strtoul(inStr.c_str(), NULL, 0); //Return Unsigned long.
 
                   /*
                    * Pass type of Application Id with registration.
                    */
                   printf("\nApplication ID Type\n");
                   printf("0 - Auth AppId \n1 - Acct AppId\n");
                   cin >> inStr;
                   len = inStr.length();
                   idx = 0;
                   while(idx != len)
                   {
                       if (!isdigit(inStr.c_str()[idx]))
                       {
                            printf("Please enter only numeric 0 or 1 \n");
                            inStr = "";
                            break;
                       }
                       idx++;
                   }
                   if (inStr == "")
                       break;
                   sendAppIdType = atoi(inStr.c_str());

                   reg.u.regInfo.appIdentifier = sendAppId;
                   reg.u.regInfo.connectionType = conType;
                   reg.u.regInfo.appIdType      = sendAppIdType;

                   // Registers the Client w.r.t Client ID and 
                   // Application ID.
                   if (StoreRegInfo(&reg) == IDS_SUCCESS)
                   {
                       smplApi.Register(&reg);
                   }
               }
               else if (ifRedundancy)
               {
                   if (smplApi.IsConnectionUp(IDS_PRIMARY_CONNECTION))
                   {
                   if (!smplApi.IsRegisteredWith(IDS_PRIMARY_CONNECTION))
                   {
                       // Registers the Client with Primary
                       smplApi.Register(&reg);
                   }
                   else
                   {
                       printf("Registered already: ClientId [%d], AppId [%d]\n"
                               ,reg.clientID, reg.u.regInfo.appIdentifier);
                   }
                   }
                   if (smplApi.IsConnectionUp(IDS_BACKUP_CONNECTION))
                   {
                   if (!smplApi.IsRegisteredWith(IDS_BACKUP_CONNECTION))
                   {
                       // Registers the Client with Backup
                       smplApi.Register(&reg);
                   }
                   else
                   {
                       printf("Registered already: ClientId [%d], AppId [%d]\n"
                               ,reg.clientID, reg.u.regInfo.appIdentifier);
                   }
                   }
               }
               else
               {
                   printf("Registered already : ClientId [%d], AppId [%d] \n",
                       reg.clientID, reg.u.regInfo.appIdentifier);
               }
           break;

           case 3:

               if ((!ifRedundancy && smplApi.IsRegistered()) ||
                    (ifRedundancy && 
                      ((smplApi.IsRegisteredWith(IDS_PRIMARY_CONNECTION) ||
                        smplApi.IsRegisteredWith(IDS_BACKUP_CONNECTION)))))
               {
                   IDS_MESSAGE *msg = GetFirstRegInfo();
                   reg.clientID= msg->clientID;
                   reg.msg_type = DEREGISTER_MSG; 

                   // De-Register the Registered Client 
                   ReleaseRegInfo();
                   smplApi.DeRegister(&reg);
               }
               else
               {
                   printf("Client not Registered \n");
               }
            break;

           case 4:
      
               if ((!ifRedundancy && smplApi.IsRegistered()) ||
                    (ifRedundancy && 
                      ((smplApi.IsRegisteredWith(IDS_PRIMARY_CONNECTION) ||
                        smplApi.IsRegisteredWith(IDS_BACKUP_CONNECTION)))))
               {
               // Display the Menu to send the message to stack based on the
               // Registered Application ID. 
                   if(sendAppId == regAppId)
                   {
                       DisplayAppMenu();
                   }
                   else
                   {
                       printf("Not Registered for AppId <%d>\n",regAppId);
                   }
               }
               else
               {
                   printf("Client not Registered \n");
               }
           break;
           case 5:
           {
               if ((!ifRedundancy && smplApi.IsRegistered()) ||
                    (ifRedundancy &&
                      ((smplApi.IsRegisteredWith(IDS_PRIMARY_CONNECTION) ||
                        smplApi.IsRegisteredWith(IDS_BACKUP_CONNECTION)))))
               {
                   ITS_UINT action =0;
                   IDS_MESSAGE *msg = GetFirstRegInfo();
                   IDS_MESSAGE dMsg;
                   dMsg.clientID= msg->clientID;
                   dMsg.msg_type = GLOBAL_UNIQ_ADDR_MSG;

                   cout <<"Please enter GUA Action 0 - Add, 1 -Del\n";
                   cin>>action;
                   if (action == IDS_GUA_DEL)
                   {
                       dMsg.u.guaInfo.action = IDS_GUA_DEL;
                   }
                   else
                   {
                       dMsg.u.guaInfo.action = IDS_GUA_ADD;
                   }

                   cout <<"Please enter Initial IP addr\n";
                   cin>>dMsg.u.guaInfo.ipAddr;

                   cout <<"Please enter Number IP Addr from Initial\n";
                   cin>>dMsg.u.guaInfo.count;

                   // Global Unique Addr Range to Server
                   smplApi.SendGlobalUniqAddrMsg(&dMsg);

               }
               else
               {
                   printf("Client not Registered \n");
               }
               break;
           }

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
    fclose(fp);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: ReRegister function registers the application Id
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
void
ReRegister(IDS_CALLBACK_INFO idsCbInfo)
{
    IDSCLApi api;
    IDS_MESSAGE reg;   // The  registration info saved sent first time
    printf("Re-Register \n");
 
   /**
    * Checking if primary connection is up
    */
   if ( idsCbInfo.ids_stat.conType == IDS_PRIMARY_CONNECTION &&
        idsCbInfo.isConUp == IDS_TRUE )
   {
       cout<<"Primary Connection is up"<<endl;
   }
   /**
    * Checking if backup connection is up
    */
   else if (idsCbInfo.ids_stat.conType == IDS_BACKUP_CONNECTION &&
         idsCbInfo.isConUp == IDS_TRUE)
   {
       cout<<"Backup Connection is up"<<endl;
 
   }
 
 /**
 * Please do the Re-Registration processing here.
 */
 
    vector<IDS_MESSAGE>::iterator it;
     for (it = regVect.begin(); it!= regVect.end() ; it++)
    {
        cout<<endl<<"Sending Re-Registration Message for Client-Id:"<<
            (*it).clientID<<" and AppId:"<<(*it).u.regInfo.appIdentifier<<
            endl;
        api.Register(&(*it), idsCbInfo.ids_stat.conType);
    }
 
}
 
/* CallBackFunc function */
void
CallBackFunc(IDS_CALLBACK_INFO idsCbInfo)
{
    cout <<"CallBackFunc invoked"<<endl;
 
    if (idsCbInfo.type == IDS_CONNECT)
    {
        ReRegister(idsCbInfo);
    }
    else if(idsCbInfo.type == IDS_DISCONNECT)
    {
       /**
        * Checking if primary connection is up
        */
       if ( idsCbInfo.ids_stat.conType == IDS_PRIMARY_CONNECTION &&
            idsCbInfo.isConUp == IDS_FALSE )
       {
           cout<<"Primary Connection is down"<<endl;
       }
       /**
        * Checking if backup connection is up
        */
       else if (idsCbInfo.ids_stat.conType == IDS_BACKUP_CONNECTION &&
             idsCbInfo.isConUp == IDS_FALSE)
       {
           cout<<"Backup Connection is down"<<endl;
 
       }
 
    }
    else
    {
        cout<<"Unknown Callback Type \n";
    }
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
int AppMain(int argc, const char** argv)
{
    parseArguments(argc, argv);
    pthread_t thread, threadPrint;
    int ret =0;

    IDSCLApi smplApi;
    // Re-Register call back
    smplApi.RegisterCallback(CallBackFunc);
    smplApi.InitDiaDictParser();

    //Read in Subscriber profile for HSS simulation
    ReadInSubsProfile();

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

    return 0;    
}

void
AppInitialize(ITS_UINT appId)
{
    int ret;
                                                                                
    printf("In AppInitialize\n");
                                                                                
    regAppId = appId;
                                                                                
    printf("Returning from  AppInitialize\n");

    return;
}

