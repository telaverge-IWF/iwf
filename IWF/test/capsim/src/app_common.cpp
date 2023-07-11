/*********************************-*-C-*-************************************
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
 *
 * LOG: $Log: app_common.cpp,v $
 * LOG: Revision 1.1.2.1.14.1.2.1  2014/12/04 05:09:24  jkchaitanya
 * LOG: changes for increment imsi to a limit mentioned as per repeatImsi count mentioned in runfile
 * LOG:
 * LOG: Revision 1.1.2.1.8.1  2014/12/04 04:54:17  jkchaitanya
 * LOG: changes for supporing imcrement imsi for load setup in MapS6a
 * LOG:
 * LOG: Revision 1.1.2.1.14.1  2014/09/22 04:58:54  jkchaitanya
 * LOG: changes for enhancement bugs 5045, 5053
 * LOG:
 * LOG: Revision 1.1.2.1  2013/08/21 12:14:16  jkchaitanya
 * LOG: sub directories in capsim
 * LOG:
 * LOG: Revision 1.1.1.1.2.3  2013/06/14 08:39:33  jsarvesh
 * LOG: Added the PurgeMSArg option for Load
 * LOG:
 * LOG: Revision 1.1.1.1.2.2  2013/06/10 07:09:12  jsarvesh
 * LOG: enhanced for Load Run from MAP-Tool
 * LOG:
 * LOG: Revision 1.1.1.1.2.1  2013/02/22 19:59:13  lakshman
 * LOG: add gtt test info.
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/28 13:45:14  lakshman
 * LOG: checkin first version of MAP test along with CAP.
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_common.cpp,v 1.1.2.1.14.1.2.1 2014/12/04 05:09:24 jkchaitanya Exp $"


#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <engine++.h>
#include <its_route.h>
#include <its_sctp.h>
#include <sys/timeb.h>

#include <app_const.h>
#include <app_msgs.h>
#include <app_trace.h>
#include <app_stats.h>
#include <app_timer.h>
#include <app_cmn.h>

#if defined (Q)
#include <quantify.h>
#endif

using namespace std;
using namespace its;

extern TcapStats      stats;
extern TransportState transStateInfo;
struct timeb sendComplete, recvComplete;

extern ITS_UINT dPC;
extern ITS_UINT oPC;
extern ITS_UINT sSN;
extern ITS_UINT oSN;

#define OCTS_185_LEN 184 // sizeof(itstest::octs185)/sizeof(ITS_OCTET)
ITS_CTXT did = 0;

void PrintOctets(ITS_OCTET *, int);
int GetLoadReqChoice();

extern "C" void PrintToFile(FILE*, const char*);

TCAPMsgs::TCAPMsgs() 
{
   lockFile = new Mutex(0);

   if(lockFile == NULL)
   {
       APP_TRACE_ERROR(("Failed to allocate memory for locking a file"));
   }

   output = new ofstream("./Result.dat");
}

TCAPMsgs::~TCAPMsgs() 
{
   delete lockFile;

   delete output;
}

void
TCAPMsgs::SendMsgs(ITS_HANDLE hdl, ITS_INT choice)
{
    APP_TRACE_DEBUG(("TCAPMsgs::SendMsgs"));

    if ( SEND_VALID_CHOICE(choice))
    {
        switch (choice)
        {
            case SEND_UNI:
                APP_TRACE_DEBUG(("TCAPMsgs::SEND_UNI:"));
                InteractiveSendUniDlg(hdl);
                break;

            case SEND_BEGIN:
                APP_TRACE_DEBUG(("TCAPMsgs::SEND_BEGIN:"));
                InteractiveSendBeginDlg(hdl);
                break;

            case SEND_END:
                APP_TRACE_DEBUG(("TCAPMsgs::SEND_END:"));
                InteractiveSendEnd(hdl);
                break;

            case SEND_CONTINUE:
                APP_TRACE_DEBUG(("TCAPMsgs::SEND_CONTINUE:"));
                InteractiveSendContinue(hdl);
                break;

            case SEND_ABORT:
                APP_TRACE_DEBUG(("TCAPMsgs::SEND_ABORT:"));
                InteractiveSendAbort(hdl);
                break;


            case SEND_PRE_END:
                InteractiveSendPreArrangedEnd(hdl);
                break;

            case SEND_LOOP:
#if defined (Q)
    if ( quantify_is_running())
    {
        quantify_clear_data();
        quantify_start_recording_data();
    }
#endif
                GenerateLoad(hdl);
#if defined (Q)
    if ( quantify_is_running())
    {
        quantify_stop_recording_data();
    }
#endif
            break;

            case DUMP_RT:
                TCAPUtils::DumpRoutingTable();
                break;

            default:
                break;

        }
    }
}

int GetLoadReqChoice()
{
    int choice = 0;
    int op = -1;

    cout << "Enter the operation you want to send" << endl;
    cout << "====================================\n" << endl;
    cout << MAP_V13_UPDATE_GPRS_LOC << ".MapV13 UpdateGprsLocation" << endl;
    cout << MAP_V13_PURGE_MS_ARG << ".MapV13 PurgeMSArg" << endl;
    cout << MAP_V13_SEND_AUTH_INFO_ARG << ".MapV13 SendAuthenticationInfoArg" << endl;
    cout << MAP_V13_SAI_ARG_AND_UGL_ARG << ".MapV13 SAIArg-UGLArg\n" << endl;
    cout << "Choice : ";
    cin >> choice;
    cout << endl;


    if (choice >= MAP_V13_UPDATE_GPRS_LOC && choice <= MAP_V13_READY_FOR_SM_ARG)
    {
        return choice;
    }

    printf ("Enter the proper option............\n\n");
    return op;
}

void
TCAPMsgs::GenerateLoad(ITS_HANDLE handle)
{
   int msgs = 0;
   int burstSize = 20;
   int slpTime = 0;
   tcapTimer tt;
   clock_t activityTime;
   int opCode= -1;

   /* Send only when the transport state is up */
#if 0
   while(!transStateInfo.GetNumOfUPTransports())
   {
       APP_TRACE_DEBUG(("Transport state is down"));
       TIMERS_Sleep(1);
   }
#endif

   while(1)
   {
         cout << endl << " Enter Number of Messages to Send "
              << endl;

         cin >> msgs;

         cout << endl << " Enter Burst Size " << endl;
         cin >> burstSize;

         cout << endl  << " Enter Sleep Time between bursts (milli-secs)" << endl;

         cin >> slpTime;

         /*itstest::msgCount = msgs;*/

         //time(&itstest::startTime);
         //tt.StartTimer();

         opCode = GetLoadReqChoice();

         if( opCode == -1 || opCode == MAP_V13_RESET_ARG || opCode == MAP_V13_READY_FOR_SM_ARG)
         {
             cout << "Invalid Choice..!! Cannnot Send ResetArg/ReadyForSMArg as TC_Begin ..!!" << endl;
             cout << "Try Sending ResetArg/Ready_For_SMArg as : \"TC_Uni.\" ..!!" << endl;
             return;
         }
         SAIArg = BuildSendAuthenticationInfoArg();
         UGLArg = BuildUpdateGPRSLocV13();
         PURGEArg = BuildPurgeMSArg();
         uint64_t startimsi = imsiforload;
         /* For sending n number of messages we are running in infinite while inside which 
          * we are building specific message and sending a burst of messages after that waiting 
          * for a sleep(MicroSeconds) and sending next burst*/
         for ( int i=0; i<msgs; i++)
         {
             if(i%repeatImsiLimit == 0)
             {
                imsiforload = startimsi;
             }
             //Increment imsi for each call
             IncrementImsi(opCode); 
            
             if(opCode == MAP_V13_SAI_ARG_AND_UGL_ARG)
             {
                 //Send Both SAI Arg and UGL Arg one after other
                 SendBeginDlg(handle, TRANSPORT_INSTANCE(handle), ITS_FALSE, MAP_V13_SEND_AUTH_INFO_ARG);
                 SendBeginDlg(handle, TRANSPORT_INSTANCE(handle), ITS_FALSE, MAP_V13_UPDATE_GPRS_LOC);
             }
             else
             {
                SendBeginDlg(handle, TRANSPORT_INSTANCE(handle), ITS_FALSE, opCode);
             }

             if ( i % burstSize == 0)
             {
                 TIMERS_USleep(slpTime * 1000);
                 //tt.StopTimer();
                 //activityTime = tt.GetTotalTime();
                 //cout << " Total time for this activity: " << activityTime << endl;
                 //cout << " In seconds: " << (double)activityTime/CLOCKS_PER_SEC << endl;
                 //TIMERS_USleep((slpTime - activityTime) * 1000);
                 //tt.StartTimer();
             }
         }
         ftime(&sendComplete);
   }
}

int
TCAPMsgs::GetInvokeID() const
{
#if 0
   static int ivkid = 1;
   int ret;

   ret = (ivkid++) % 221;
#endif
   int ret = 1;

   return ret;
} 

void
TCAPMsgs::DeleteApplicationRoute(ITS_USHORT instance, ITS_USHORT dlgid)
{
   ITS_HDR hdr;
   int ret = 0;

   hdr.type = ITS_TCAP;
   hdr.context.dialogue_id = dlgid;

   ret = ROUTE_DeleteApplication(instance, &hdr);


   if(ret != ITS_SUCCESS)
   {
       APP_TRACE_ERROR(("Unable to delete route for dlgid = %d ",dlgid));
   }

   APP_TRACE_DEBUG(("Deleted application route on instance %d, %02x", 
                    instance, hdr.context.dialogue_id));

   return;
}

void TCAPMsgs::Lock()
{
   if(lockFile->Acquire() != ITS_SUCCESS)
   {
       APP_TRACE_ERROR(("Lock: Failed to acquire mutex:"));
   }

   return;
}

void TCAPMsgs::UnLock()
{
   if(lockFile->Release() != ITS_SUCCESS)
   {
       APP_TRACE_ERROR(("UnLock: Failed to release mutex:"));
   }

   return;
}

int
TCAPUtils::GetVariantType()
{
    string input;
    int index = 2;
#if 0 
    do
    {
        cout << "Please enter Variant type \n";
        cout << "ANSI -> 1 \n";
        cout << "ITU  -> 2 \n";
        cin >> input;
        index = atoi(input.c_str());
    } while ((index < 1 || index > 2));
#endif
    return index;
}

void
TCAPUtils::ConvertStringToOctets(ITS_OCTET* octs, std::string& str,
                                int& gtt_len, ITS_BOOLEAN& eFlag)
{
   int arr_len;

   if(str.length() % 2 == 0)
   {
      eFlag = ITS_TRUE;
   }

   str = (str.length() %2 == 1) ? str + '0' : str;

   arr_len = str.length() / 2;
   int j = 0;

   for(int i = 0; j < arr_len; i += 2, j++)
   {
      octs[j] = str.at(i + 1) - '0';
      octs[j] <<= 4;
      octs[j] |= str.at(i) - '0';
   }

   gtt_len = j;

   for(int i = 0; i < gtt_len; i++)
   {
       printf("%02x ", octs[i]);
   }

   return;
}

void
TCAPUtils::ConvertStringToOctets(ITS_OCTET* octs, char* str,
                                int& gtt_len, ITS_BOOLEAN& eFlag)
{
   int  arr_len;
   char *temp1, *temp2;

   temp1 = (char*)malloc(sizeof(char));
   temp2 = (char*)malloc(sizeof(char));

   if(strlen(str) % 2 == 0)
   {
      eFlag = ITS_TRUE;
   }
   arr_len = (strlen(str) %2 == 1) ? strlen(str) + 1: strlen(str);
   int j = 0;

   for(int i = 0; i < arr_len; j++, i+=2)
   {
      *temp1 = *(str++);
      if(strlen(str) != 0)
      {
         *temp2 = *(str++);

         *(octs + j) = atoi(temp2);
         *(octs + j) <<= 4;
      }
      else
      {
         *(octs +j) = 0x00;
      }

      *(octs + j) |= atoi(temp1);
   }

   free(temp1);
   free(temp2);

   gtt_len = j;

   return;
}


void
TCAPUtils::ConvertOctsToString(char** str, ITS_OCTET* octs,
                              int len, ITS_BOOLEAN eFlag)
{
   *str = (char*)calloc(len * 2, sizeof(char));

   if(*str == NULL)
   {
      return;
   }

   for(int i = 0, j = 0; i < len; i++)
   {
       (*str)[j++] = (octs[i] & 0x0F) + '0';

       if(!eFlag && i == len-1)
       {
          /* odd number of digits present */
          break;
       }

       (*str)[j++] = ((octs[i] & 0xF0) >> 4) + '0';
   }

   return;
}

void
TCAPUtils::RegisterGTTCallback(ITS_POINTER object, ITS_POINTER userData,
                              ITS_POINTER callData)
{
   int   start = -1;
   char* str = NULL;
   int   ret;

   ITS_BOOLEAN eFlag = ITS_FALSE;

   SCCP_CALLBACK_DATA* gtt = (SCCP_CALLBACK_DATA*) callData;
   PrintOctets((ITS_OCTET *)callData, sizeof(SCCP_CALLBACK_DATA));
   /*ITS_OCTET  addrInd = SCCP_CPA_ROUTE_SSN | SCCP_CPA_HAS_PC |
    SCCP_CPA_HAS_SSN;*/
   /* Remove prefixes for gtt */
   if(gtt->gttLen > 0)
   {
       printf("GTT ADDRINDICATOR:%d\n",gtt->addrInd);//Temp, Remove later --Ahil
       if((gtt->addrInd & SCCP_CPA_GTTI_ALL) == SCCP_CPA_GTTI_ALL)
       {
           APP_TRACE_DEBUG(("Contains SCCP_CPA_GTTI_ALL"));
           eFlag = (gtt->gttInfo[1] & 0x01) == 0x01 ? ITS_FALSE : ITS_TRUE;
           start = 3; /* digits strat from octet 3 */
       }
       else if((gtt->addrInd & SCCP_CPA_GTTI_TNE) ==
               SCCP_CPA_GTTI_TNE)
       {
           APP_TRACE_DEBUG(("Contains SCCP_CPA_GTTI_TNE"));
           //eFlag = (gtt->gttInfo[1] & 0x01) == 0x01 ? ITS_FALSE : ITS_TRUE;
           start = 2;
       }
       else if((gtt->addrInd & SCCP_CPA_GTTI_TRANS) ==
               SCCP_CPA_GTTI_TRANS)
       {
           APP_TRACE_WARNING(("May contain NP and ES in this type"));
           start = 1;
       }
       else if(gtt->addrInd & SCCP_CPA_GTTI_NATURE == SCCP_CPA_GTTI_NATURE)
       {
           APP_TRACE_DEBUG(("Contains SCCP_CPA_GTTI_NATURE"));
           eFlag = (gtt->gttInfo[0] & 0x80) ? ITS_FALSE : ITS_TRUE;

           start = 1; /* digits start from 2nd octet */
       }
       else
       {
           APP_TRACE_ERROR(("Address indicator for GTT doesn't match"));
       }
   }

   if(start != -1)
   {
      TCAPUtils::ConvertOctsToString(&str, &gtt->gttInfo[start], (gtt->gttLen), eFlag);

   }
   if(str != NULL)
   {
       APP_TRACE_WARNING(("GTT Successful"));
       gtt->addrInd = gtt->addrInd | 
                          (SCCP_CPA_ROUTE_SSN | SCCP_CPA_HAS_PC | SCCP_CPA_HAS_SSN);
       gtt->dpc = oPC;
       gtt->ssn = oSN;
       ret = SCCP_EncodeAddr(gtt->translation, gtt->addrInd, gtt->dpc,
                                  gtt->ssn, gtt->gttInfo, gtt->gttLen);

       if(ret == ITS_SUCCESS)
       {
           gtt->transSuccess = ITS_TRUE;
           cout << "******HELLO I DID GTT, NO PROBLEM WITH ME *******"<<endl;
       }
   }
   else
   {
       APP_TRACE_ERROR(("GlobalTitleTranslation Failed:"));
       gtt->transSuccess = ITS_FALSE;
   }
       
    return;
}


/*************************************************************************
 *
 *  Register SCTPTrans call back for TRANSPORT_SetState
 *
 ************************************************************************/

void
TCAPUtils::RegisterSCTPTransCallback(ITS_POINTER object, ITS_POINTER userData,
                                    ITS_POINTER callData)
{

    ITS_USHORT inst = ((TRANSPORT_Control *)object)->transport.instance;
    SCTP_API_MSG_HDR* msg = (SCTP_API_MSG_HDR *)callData;
    SCTP_API_CMSG*    cmsg = (SCTP_API_CMSG *)msg->control;

    switch(cmsg->hdr.type)
    {
        case SCTP_CM_ASSOC_CHG:
            switch (cmsg->data.assocChg.state)
            {
                case SCTP_AC_COMM_UP:
                case SCTP_AC_COMM_RESTART:
                   APP_TRACE_DEBUG(("SCTP Communication Up notification."));

                   break;

                case SCTP_AC_COMM_LOST:
                case SCTP_AC_COMM_ABORTED:
                case SCTP_AC_SHUTDOWN_DONE:
                   APP_TRACE_ERROR(("SCTP Lost Communication."));

                   break;

                default:
                   APP_TRACE_ERROR(("Unkwon SCTP notification received."));

                   break;
            }

            break;
         default:
            APP_TRACE_WARNING(("Not interested on the source %d",cmsg->hdr.type));
            break;
    }
    return;
}

/* Callback to register for MTP3 link up/Down notifications */
void
TCAPUtils::RegisterMTP3TransCallback(ITS_POINTER object, ITS_POINTER userData,
                                    ITS_POINTER callData)
{
#if defined(INTELLINET_MTP3) || defined (NMS_MTP3)
    ITS_USHORT inst = 0;
#else
    ITS_USHORT inst = ((TRANSPORT_Control *)object)->transport.instance;
#endif

    ITS_EVENT* mtp3Indi = (ITS_EVENT *)callData;

    switch(mtp3Indi->data[0])
    {
         case MTP3_MSG_RESUME:
             APP_TRACE_CRITICAL(("Received MTP3_MSG_RESUME on Instance %d", inst));

             break;

          case MTP3_MSG_PAUSE:
             APP_TRACE_CRITICAL(("Received MTP3_MSG_PAUSE on instance %d", inst));

             break;

           default:
              APP_TRACE_ERROR(("Unknown MTP3 notification got here on instance %d:", inst));
              break;
     }
     return;
}

void
TCAPUtils::DumpRoutingTable()
{
   char* routeString = NULL;
   const char* cmdLine = NULL;

   ROUTE_DumpSS7ToIdHashtable(&routeString, cmdLine);
   //ROUTE_DumpSS7ToIdHashtable(&routeString);

   printf("%s", routeString);

   free(routeString);
}

void PrintOctets(ITS_OCTET *data, int dlen)
{
    int i = 0;

    printf("-----------------------\n");
    //getchar();
    for (i = 0; i < dlen; i ++)
    {
        printf("%02x ", data[i]);
        if ( i % 15 == 0 && i != 0)
        {
             printf("\n");
        }
    }
    printf("\n----------------------\n");
}
/***** Added to find out XUDT Info --Ahil *****/

void
TCAPMsgs::Print(const char* fmtStr)
{
#if defined FILE_APP_TRACE
   Lock();

   /* PrintToFile(output, fmtStr);  */
   (*output) << fmtStr << endl;

   UnLock();
#endif

   return;
}


extern "C" void PrintToFile(FILE* fptr, const char* fmt)
{
   fprintf(fptr, fmt);

   return;
}
