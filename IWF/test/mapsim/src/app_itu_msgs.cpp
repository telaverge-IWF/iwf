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
 * LOG: $Log: app_itu_msgs.cpp,v $
 * LOG: Revision 1.1.2.3  2013/03/18 09:45:51  jvikas
 * LOG: mapsim changes.
 * LOG:
 * LOG: Revision 1.1.2.2  2013/02/13 11:43:57  jvikas
 * LOG: MAP Simulator Enhancement
 * LOG:
 * LOG: Revision 1.1.2.1  2013/02/12 14:09:19  jvikas
 * LOG: Map Simulator Changes for IWF
 * LOG:
 * LOG: Revision 1.1.1.1.2.6  2013/01/31 19:31:28  arnabd
 * LOG: Handling of SendAuthenticationInfoArg
 * LOG:
 * LOG: Revision 1.1.1.1.2.5  2013/01/24 15:10:12  lakshman
 * LOG: tart testing delete subscriber data....
 * LOG:
 * LOG: Revision 1.1.1.1.2.4  2013/01/23 21:04:37  lakshman
 * LOG: verified provideSubscriberArg and tcap error scenarios.
 * LOG:
 * LOG: Revision 1.1.1.1.2.3  2013/01/17 23:49:15  lakshman
 * LOG: Update DeleteSubscriberdata and TCAP error handling function with few tests.
 * LOG:
 * LOG: Revision 1.1.1.1.2.2  2013/01/15 21:21:30  lakshman
 * LOG: get Delete subscriber and Insert subscriber conversions in cvs.
 * LOG:
 * LOG: Revision 1.1.1.1.2.1  2013/01/15 16:06:31  arnabd
 * LOG: Proper handling of ULR --- UpdateGprsLocationArg --- UpdateGprsLocationRes --- ULA scenario
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.2.8  2013/01/05 20:18:40  lakshman
 * LOG: add updatelocarg decode func
 * LOG:
 * LOG: Revision 1.1.2.7  2013/01/05 20:06:02  lakshman
 * LOG: update to manage invoke ids and dump insertSubRes
 * LOG:
 * LOG: Revision 1.1.2.6  2013/01/05 17:39:56  lakshman
 * LOG: increase the probability on tcap-end.
 * LOG:
 * LOG: Revision 1.1.2.5  2013/01/05 15:52:06  lakshman
 * LOG: send both cpts
 * LOG:
 * LOG: Revision 1.1.2.4  2013/01/05 15:26:30  lakshman
 * LOG: checkin updategrps loc res msg
 * LOG:
 * LOG: Revision 1.1.2.3  2013/01/03 21:22:27  lakshman
 * LOG: update address info
 * LOG:
 * LOG: Revision 1.1.2.2  2013/01/03 02:44:43  lakshman
 * LOG: update tcap tests - add gprs and randomize responses.
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/28 13:45:14  lakshman
 * LOG: checkin first version of MAP test along with CAP.
 * LOG:
 * LOG: Revision 1.3  2011/04/18 15:24:17  nvijikumar
 * LOG: More UT updates
 * LOG:
 * LOG: Revision 1.2  2011/04/15 11:35:46  nvijikumar
 * LOG: UT Updates
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_itu_msgs.cpp,v 1.1.2.3 2013/03/18 09:45:51 jvikas Exp $"

#undef TTC
#undef PRC
#undef CCITT
#undef ANSI
#define CCITT

#if defined (CCITT)

#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <engine++.h>
#include <its_route.h>
#include <its_sctp.h>
#include <sys/timeb.h>

#include <map>

#include <app_cmn.h>
#include <app_const.h>
#include <app_msgs.h>
#include <app_trace.h>
#include <app_stats.h>
#include <app_timer.h>
#include <map_v13_update_location_res.h>

#if defined (Q)
#include <quantify.h>
#endif

ITS_OCTET AC_NAMEIDP[] = {0x04,0x00,0x00,0x01,0x00,0x32,0x01}; 
//ITS_OCTET AC_NAMEIDP[] = {0x04,0x00,0x00,0x01,0x00,0x14,0x03,0x04};

using namespace std;
using namespace its;
using namespace map_v13;


static void SetGlobalTitleAddr(its::SCCP_Address&);

extern TcapStats      stats;
extern TransportState transStateInfo;
void  EncodeMsg(AsnObject* p, Octets** octets);
extern ApplicationStats appStats;

#if defined(USE_ANSI_SCCP)

#undef CCITT
#define ANSI
#include <ansi/sccp.h>
    its::SCCP_CalledPartyAddr_ANSI    cdp_itu;
    its::SCCP_CallingPartyAddr_ANSI   cpa_itu;
#if defined(DUAL_TCAP)
#define ISS7_Stack ISS7_CCITT_Stack
#else
#define ISS7_Stack ISS7_ANSI_Stack
#endif
#undef ANSI
#define CCITT

#elif defined(USE_TTC_SCCP)

#undef CCITT
#define TTC
#include <japan/sccp.h>
    its::SCCP_CalledPartyAddr_TTC     cdp_itu;
    its::SCCP_CallingPartyAddr_TTC    cpa_itu;
#define ISS7_Stack ISS7_TTC_Stack
#undef TTC
#define CCITT

#elif defined(USE_PRC_SCCP)

#undef CCITT
#define PRC
#include <china/sccp.h>
    SCCP_CalledPartyAddr_PRC     cdp_itu;
    SCCP_CallingPartyAddr_PRC    cpa_itu;
#define ISS7_Stack ISS7_PRC_Stack
#undef PRC
#define CCITT

#else
#include <itu/sccp.h>
    its::SCCP_CalledPartyAddr_CCITT   cdp_itu;
    its::SCCP_CallingPartyAddr_CCITT  cpa_itu;
#define ISS7_Stack ISS7_CCITT_Stack
#endif

#define TCAP_L_CANCEL_TYPE   TCPPT_TC_L_CANCEL
#define TCAP_END_TYPE        TCPPT_TC_END
#define TCAP_BEGIN_TYPE      TCPPT_TC_BEGIN
#define TCAP_CONTINUE_TYPE   TCPPT_TC_CONTINUE
#define TCAP_P_ABORT_TYPE    TCPPT_TC_P_ABORT
#define TCAP_U_ABORT_TYPE    TCPPT_TC_U_ABORT
#define TCAP_ERROR_TYPE      TCPPT_TC_U_ERROR
#define TCAP_R_REJECT_TYPE   TCPPT_TC_R_REJECT
#define TCAP_U_REJECT_TYPE   TCPPT_TC_U_REJECT
#define TCAP_L_REJECT_TYPE   TCPPT_TC_L_REJECT

#define OCTS_185_LEN 184 // sizeof(itstest::octs185)/sizeof(ITS_OCTET)
ITS_CTXT did = 0;

ITS_UINT dPC=0;
ITS_UINT oPC=0;
ITS_UINT sSN=149;
ITS_UINT oSN=6;

string gRecvImsi;
static bool gInitGlobals = false;
static ITUTcapMsgs * ituTcapMsgs = NULL;
int GetReqChoice();
ITS_ULONG GetMapOpCodeForChoice(ITS_INT choice);
void UpdateStats(TCAP_Component* its_cpt);
void UpdateReqStats(ITS_LONG op);
void UpdateRespStats(ITS_LONG op);

extern void BuildImsiList();
//AsnObject* BuildCapMsg(int opCode);

void
ITUTcapMsgs::InitExternals()
{
    if (!gInitGlobals)
    {
        BuildImsiList();
        gInitGlobals = true;
    }
}

ITUTcapMsgs *
ITUTcapMsgs::GetItuInstance()
{
    if(ituTcapMsgs == NULL)
    {
        ituTcapMsgs = new ITUTcapMsgs;
    }
    return ituTcapMsgs;
}

int 
ITUTcapMsgs::HandleMessage(engine::Worker *work, its::ITS_Event& evt)
{
    TCAP_Dialogue*  its_dlg = NULL; /* Receive dialogue*/
    TCAP_Component* its_cpt = NULL; /* Receive component*/

    ITS_USHORT   cpt_type_recvd = 0x00;
    ITS_USHORT   dlg_type_recvd = 0x00;
    ITS_BOOLEAN  last_cpt_recvd = ITS_FALSE;

    switch (TCAP_MSG_TYPE(&evt.GetEvent()))
    {
        case ITS_TCAP_CPT:
            its_dlg = reinterpret_cast<TCAP_Dialogue *>(work->GetUserData());

            TCAP_Component::Receive(ISS7_Stack, evt, its_dlg, &its_cpt);

            APP_TRACE_DEBUG(("Received: Component Type %02x",
                                         its_cpt->GetComponentType()));

            cpt_type_recvd = its_cpt->GetComponentType();
            APP_TRACE_DEBUG(("Received: InvokeId %02x, InvokeType %02x",
                                    its_cpt->GetInvokeID(), cpt_type_recvd));

            //stats.UpdateRecvStats(its_cpt->GetComponentType());
            UpdateStats(its_cpt);

            PrintComponentType(cpt_type_recvd);

            if(cpt_type_recvd == TCAP_L_CANCEL_TYPE)
            {
            }
            else
            {
                /*
                 * replys to multiple components is a problem here
                 * somehow we need to track received cpt types, operation
                 * and invoke ids
                 */
                 if(its_cpt->GetLast()) /*Last component received*/
                 {
                     last_cpt_recvd = ITS_TRUE; /*we got all cpts*/
                 }
            }

            APP_TRACE_DEBUG(("Last CPT received? = %d", last_cpt_recvd));

            if(cpt_type_recvd != TCAP_L_CANCEL_TYPE ||
                          last_cpt_recvd)
            {
                SendResponses(its_dlg, &its_cpt, work);
                last_cpt_recvd = ITS_FALSE;
            }

            if(its_cpt)
            {
                delete its_cpt;
                its_cpt = NULL;
            }

            if(its_dlg)
            {
                delete its_dlg;
                its_dlg = NULL;
            }

            break;

        case ITS_TCAP_DLG:
        {
                ITS_OCTET flags = 0x00;
                ITS_OCTET slsKey = 0x00;
                ITS_OCTET priority = 0x00;
                ITS_OCTET acName[100];
                ITS_OCTET networkInd = 0x00;
                int acNameLen = 0;
                ITS_OCTET userInfo[100];
                int userInfoLen = 0;

                TCAP_Dialogue::Receive(ISS7_Stack, evt, &its_dlg);

                APP_TRACE_DEBUG(("Received: Dialogue Type %02x: Dialogue ID %02x",
                                         its_dlg->GetDialogueType(),
                                         its_dlg->GetDialogueID()));

                dlg_type_recvd = its_dlg->GetDialogueType();
                PrintDialogueType(dlg_type_recvd);

                stats.UpdateRecvStats(dlg_type_recvd);

                APP_TRACE_DEBUG(("Received: dialogueID = %02x, DialogueType = %02x",
                                      its_dlg->GetDialogueID(), dlg_type_recvd));

                its_dlg->GetQualityOfService(flags, slsKey, priority, networkInd);

                if (flags)
                {
                    APP_TRACE_DEBUG((" =====> Prot Version: %02x \n", flags));
                }
                its_dlg->GetApplicationContext(acName, acNameLen);

                if (acNameLen)
                {
                    int i;

                    APP_TRACE_DEBUG((" =====> AC NAME : \n"));

                    for (i = 0; i < acNameLen; i++)
                    {
                        printf("%02x ", acName[i]);
                    }

                    printf("\n");
                }

                its_dlg->GetUserInfo(userInfo, userInfoLen);

                if (userInfoLen)
                {
                    int i;

                    APP_TRACE_DEBUG((" =====> USER INFO : \n"));

                    for (i = 0; i < userInfoLen; i++)
                    {
                        printf("%02x ", userInfo[i]);
                        if (i%15 == 0)
                        printf("\n");
                    }

                    printf("\n");
                }
                if (its_dlg->IsComponentPresent())
                {
                    APP_TRACE_DEBUG(("**** TEST: DLG has COMPONENT ****\n"));
                    work->SetUserData(its_dlg);
                }
                else
                {
                    APP_TRACE_DEBUG(("**** TEST: DLG has NO COMPONENT ****\n"));

                    its_cpt = NULL;

                    SendResponses(its_dlg, &its_cpt, work);

                    delete its_dlg;
                }

                break;
         }
         default:
                APP_TRACE_ERROR(("Received neither Dlg not CPT."));
                break;
    }

    return ITS_SUCCESS;
}

static void SetReceivedImsi(const map_v13::IMSI &usrid)
{
    const std::vector<byte> &array = usrid.GetArray();
    char *fromdg = 0;

    TCAPUtils::ConvertOctsToString(&fromdg, (ITS_OCTET *)&array[0], (int)array.size(), true);
    gRecvImsi = fromdg;
    free(fromdg);
    fromdg = 0;
}

int ITUTcapMsgs::SendResponses(TCAP_Dialogue* dlg, 
                               TCAP_Component** cpt,
                               engine::Worker* work)
{
   int ret = 0;
   
   ITS_USHORT dlg_type = 0x00;
   ITS_USHORT cpt_type = 0x00;
   ITS_USHORT dlg_id;
   ITS_USHORT ivk_id;

   if(dlg != NULL)
   {
      dlg_type = dlg->GetDialogueType();
      dlg_id   = dlg->GetDialogueID();
   }

   if(*cpt != NULL)
   {
      cpt_type = (*cpt)->GetComponentType();
      ivk_id   = (*cpt)->GetInvokeID();
   }

   APP_TRACE_DEBUG(("Inside SendResponses() function."));

   ITS_LONG op ;

   try
   {
       switch ((*cpt)->GetComponentType())
       {
           case TCPPT_TC_INVOKE:
           {
               TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *>(*cpt);
               ivk->GetOperation(op);
               
               if (op == map_common::OP_updateGprsLocation)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::UpdateGprsLocationArg uglarg;
                   Octets octs(param);
                   uglarg.Decode(octs);
                   uglarg.Print(cout);

                   const map_v13::IMSI &usrid = uglarg.GetImsi();
                   SetReceivedImsi(usrid);

                   /*Display Message Details*/
                   std::stringstream ostr;
                   ostr.str( std::string());
                   ostr.clear();

                   ostr << uglarg.GetImsi();
                   appStats.last_processed_msgs[appStats.recent_msg_idx] = "[FROM IWF]-->RECEIVED UGL Arg with [IMSI]:";
                   appStats.last_processed_msgs[appStats.recent_msg_idx] += ostr.str();

                   ostr.str( std::string());
                   ostr.clear();
                   ostr << uglarg.GetSgsn_Number();
                   appStats.last_processed_msgs[appStats.recent_msg_idx+1] = "(M) [SGSN_Number]:";
                   appStats.last_processed_msgs[appStats.recent_msg_idx+1] += ostr.str();

                   ostr.str( std::string() );
                   ostr.clear();
                   ostr << uglarg.GetSgsn_Address();
                   appStats.last_processed_msgs[appStats.recent_msg_idx+2] = "(M) [SGSN_Address]:";
                   appStats.last_processed_msgs[appStats.recent_msg_idx+2] += ostr.str();
               }
               
               if (op == map_common::OP_sendAuthenticationInfo)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::SendAuthenticationInfoArg saiarg;
                   Octets octs(param);
                   saiarg.Decode(octs);
                   saiarg.Print(cout);

                   /*Display Message Details*/
                   std::stringstream ostr;

                   ostr << saiarg.GetImsi();
                   appStats.last_processed_msgs[appStats.recent_msg_idx +6] = "[FROM IWF]-->RECEIVED SAI Arg with [IMSI]:";
                   appStats.last_processed_msgs[appStats.recent_msg_idx +6] += ostr.str();
               }
               else if (op == map_common::OP_purgeMS)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::PurgeMS_Arg pumsarg;
                   Octets octs(param);
                   pumsarg.Decode(octs);
                   pumsarg.Print(cout);
               }
               else if (op == map_common::OP_readyForSM)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::ReadyForSM_Arg rfsa;
                   Octets octs(param);
                   rfsa.Decode(octs);
                   rfsa.Print(cout);
               }
           }
           break;

           case TCPPT_TC_RESULT_L:
           case TCPPT_TC_RESULT_NL:
           {
               TCAP_Result *resl = dynamic_cast<TCAP_Result *>(*cpt);
               resl->GetOperation(op); 

               (*cpt)->Print(cout);
               if (op == map_common::OP_insertSubscriberData)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::InsertSubscriberDataRes isres;
                   Octets octs(param);
                   isres.Decode(octs);
                   isres.Print(cout);
                   UpdateStats(*cpt);

                    /*Display Message Details*/
                   //InsertSubscriberDataRes *isdres = static_cast<InsertSubscriberDataRes *> (resl);
                   //std::stringstream ostr;
                   //ostr << isdres->GetImsi();
                   appStats.last_processed_msgs[appStats.recent_msg_idx+4] = "[FROM IWF]-->RECEIVED ISD Response for ISD Arg";
                   //appStats.last_processed_msgs[appStats.recent_msg_idx+4] += ostr.str();

               }
               else if (op == map_common::OP_cancelLocation)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::CancelLocationRes clRes;
                   Octets octs(param);
                   clRes.Decode(octs);
                   clRes.Print(cout);
                   UpdateStats(*cpt);

                   /*Display Message Details*/
                   appStats.last_processed_msgs[appStats.recent_msg_idx+10] = "[FROM IWF]-->RECEIVED Cancel Location Response";
               }
           }
           break;

           default:
           break;
       }
   }
   catch (AsnDecodeError &exc)
   {
       cout << exc.GetDescription() << endl;
   }
   SendMAPResponse(dlg, *cpt);

   return ret;
}

void
ITUTcapMsgs::InteractiveSendPreArrangedEnd(ITS_HANDLE hdl)
{
   int ret = 0;
   ITS_USHORT dlgid;

   TCAP_End end;
   cout << endl <<"Enter Dialog ID:";
   cin >> dlgid;

   end.SetDialogueID(dlgid);

   end.SetPreArrangedEnd(true);

   ret = TCAP_Dialogue::Send(ISS7_Stack, &end);

   if(ret == ITS_SUCCESS)
   {
       stats.UpdateSendStats(end.GetDialogueType(), true);
       APP_TRACE_DEBUG(("Send prearranged end success:\n"));
   }

  return;
}

void ITUTcapMsgs::PrintComponentType(ITS_USHORT compType)
{
   switch (compType)
   {
      case TCPPT_TC_INVOKE:
            APP_TRACE_DEBUG(("**** TEST: Received INVOKE CPT **** \n"));
            break;
      case TCPPT_TC_RESULT_L:
            APP_TRACE_DEBUG(("**** TEST: Received RESULT LAST CPT **** \n"));
            break;
      case TCPPT_TC_RESULT_NL:
            APP_TRACE_DEBUG(("**** TEST: Received RESULT_NL CPT **** \n"));
            break;
      case TCAP_L_CANCEL_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received LOCAL CANCEL CPT **** \n"));
            break;
      case TCAP_ERROR_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received ERROR CPT **** \n"));
            break;
      case TCAP_R_REJECT_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received R_REJECT CPT **** \n"));
            break;
      case TCAP_U_REJECT_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received U_REJECT CPT **** \n"));
            break;
      case TCAP_L_REJECT_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received L_REJECT CPT **** \n"));
            break;
       default:
            break;

   }

}

void ITUTcapMsgs::PrintDialogueType(ITS_USHORT compType)
{
   switch (compType)
   {
       case TCAP_END_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received END DLG ****\n"));
            break;
       case TCAP_BEGIN_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received BEGIN DLG ****\n"));
            break;
       case TCAP_CONTINUE_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received CONTINUE DLG ****\n"));
            break;
       case TCAP_P_ABORT_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received P_ABORT DLG ****\n"));
            break;
       case TCAP_U_ABORT_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received U_ABORT DLG ****\n"));
            break;
       default:
            break;
   }
}
static void
SetGlobalTitleAddr(its::SCCP_Address& address)
{
   ITS_OCTET  octs[15];
   ITS_OCTET  gtt_arr[15];

   ITS_BOOLEAN eFlag = ITS_FALSE;

   int gtt_len = 0;
   int gtt_type = SCCP_CPA_GTTI_TNE;

   gtt_arr[0] = 0x00; /* GTT TT */
   gtt_arr[1] = 0x10; /* GTT NP */

   memset(octs, 0, 15);

   if(address.GetID() == SCCP_PRM_CALLED_PARTY_ADDR)
   {
       itstest::dE164 = const_cast<char *>("9876543210"); /*Temp for GTT Test - Ahil */
       printf("*****DESTGTT VALUE IS:%s\n",itstest::dE164);

       TCAPUtils::ConvertStringToOctets(octs, itstest::dE164, gtt_len, eFlag);
   }
   else if(address.GetID() == SCCP_PRM_CALLING_PARTY_ADDR)
   {
       itstest::oE164 = const_cast<char *>("1234567890"); /*Temp for GTT Test - Ahil */
       printf("*****ORIGGTT VALUE IS:%s\n",itstest::oE164);

       TCAPUtils::ConvertStringToOctets(octs, itstest::oE164, gtt_len, eFlag);
   }
   else
   {
       APP_TRACE_ERROR(("SetGlobalTitleAddr: Invalid Address "));
   }


   if(eFlag)
   {
       gtt_arr[1] |= 0x02; /* GTT ES is even */
                           /* else it is odd(by default) */
   }
   else
   {
       gtt_arr[1] |= 0x01;
   }

   memcpy(&gtt_arr[2], &octs[0], gtt_len);

   /*gtt type, bytes, length */
   address.SetGlobalTitle(gtt_type, gtt_arr, gtt_len + 2);

}
/*static ITS_UINT dPC=0;
static ITS_UINT oPC=0;
static ITS_UINT sSN=149;
static ITS_UINT oSN=6;*/

void 
ITUTcapMsgs::SetSCCPAddress()
{
   bool networkInd = false;
   printf("=====$ ITUITcapMsgs::SetSCCPAddress $====\n");

   char buf[256];
   int routtype_fromuser=0;
   //int routtype_fromuser=1;

   cout <<endl <<"=== >Enter OPC:";
   cin >> oPC;
   cpa_itu.SetPointCode(oPC);
   //cpa_itu.SetPointCode(4114);

   cout <<endl <<"=== >Enter DPC:";
   cin >> dPC;
   cdp_itu.SetPointCode(dPC);
   
   //cdp_itu.SetPointCode(2057);

   //cout <<endl <<"=== >Enter Destination SSN:";
   //cin >> sSN;
   cdp_itu.SetSSN(sSN);
   cpa_itu.SetSSN(oSN);

   if(itstest::apc == 0)
   {
       /* User did not set the adjacent pc so assume 
        * our adjacent is destination pc 
        */
       //itstest::apc = itstest::dpc;
   }

   printf("\n=== > IF you want GTT enter \"0\" Else Press \"1\"\n");
   cin >> routtype_fromuser;
   if (!routtype_fromuser)
   {
       itstest::routeType=0; /*Temp for GTT Test - Ahil */
       printf("ROUTETYPE==%d\n",itstest::routeType);
   }

   cdp_itu.SetRouteByPCSSN(itstest::routeType);

   cout <<endl <<"=== >SetInternationalRouting 0/1:\n";
   cin >> networkInd;

   cdp_itu.SetInternationalRouting(networkInd);
   cpa_itu.SetInternationalRouting(networkInd);

   if(!itstest::routeType)
   {
       SetGlobalTitleAddr(cdp_itu);
   }

   //APP_TRACE_DEBUG(("OPC = %d DPC = %d ", itstest::opc, itstest::dpc));

   APP_TRACE_DEBUG((buf, "OE164 = %s DE164 = %s ", itstest::oE164, itstest::dE164));

   cpa_itu.SetRouteByPCSSN(itstest::routeType);

   cpa_itu.SetInternationalRouting(networkInd);

   if(!itstest::routeType)
   {
       SetGlobalTitleAddr(cpa_itu);
   }
}

void
ITUTcapMsgs::InteractiveSendAbort(ITS_HANDLE hdl)
{
    ITS_INT ret;
    TCAP_Dialogue* dlg;
    TCAP_Component* cpt;
    TCAP_Abort     abortDlg;
    ITS_USHORT localDid;
    ITS_OCTET abrtInfo[3] = {0xd8,0x01,0x01};
    ITS_UINT abrtReason;

    cout << "\n======> Enter did : <======\n";
    cin >> localDid;

    abortDlg.SetDialogueID(localDid);


    abortDlg.SetApplicationContext(itstest::AC_NAME, 7);
    cout << "\n======> Enter Abort Reason (Cause) : <======\n";
    cin >> abrtReason;
    abortDlg.SetAbortReason(abrtReason);

    dlg = &abortDlg;

    cout << "**** Sending on DID " << localDid << endl;

    ret = TCAP_Dialogue::Send(ISS7_Stack, dlg);

    if(ret != ITS_SUCCESS)
    {
         cout << "====>TCAP_TEST: Failed to send Dialogue< =====" << endl;
    }
    else
    {
         cout << "==>TCAP_TEST: Dialogue send succes PTYPE ="
              << dlg->GetDialogueType() << endl;
    }

}

void
ITUTcapMsgs::InteractiveSendUniDlg(ITS_HANDLE hdl)
{
    ITS_INT ret;
    TCAP_Dialogue* dlg;
    TCAP_Component* cpt;
    TCAP_Unidirectional uniDlg;
    int hasAC = 0;
    int hasProtVer = 0;
    int hasUserInfo = 0;
    bool hasInvoke = false;
    int  invokeCount =  1;
    hasInvoke = true;
    TCAP_AllocateDialogueId(ISS7_Stack, &did);

    printf("\n ******** Allocated DID %d *******\n", did);
    uniDlg.SetDialogueID(did);
    uniDlg.SetOrigAddr(cpa_itu);
    //uniDlg.SetOPC(itstest::opc);
    uniDlg.SetOPC(oPC);
    uniDlg.SetDestAddr(cdp_itu);
    //uniDlg.SetDPC(itstest::apc);
    uniDlg.SetDPC(dPC);

    cout << "=====> Enter 1 for Prot Version <=====\n";
    cin >> hasProtVer;

    if (hasProtVer)
    {
         uniDlg.SetQualityOfService(QOSI_PROT_VER, 0, 0);
    }

    cout << "=====> Enter 1 for AC Name <=====\n";
    cin >> hasAC;

    if (hasAC)
    {
         uniDlg.SetApplicationContext(itstest::AC_NAME, 7);
    }

    cout << "=====> Enter 1 for UserInfo <=====\n";
    cin >> hasUserInfo;

    if (hasUserInfo)
    {
         uniDlg.SetUserInfo(itstest::USER_INFO, 25);
    }

    dlg = &uniDlg;

    cout << "======> \n";
    cout << "======> How many invokes? <======\n";
    cin >> invokeCount;

    for (int i = 1; i <= invokeCount; i++)
    {
         TCAP_Invoke    invoke;
         int invokeId;
         int opClass;

         cout << "========> \n";
         cout << "========> Enter Invoke Id: <======== \n";
         cin >> invokeId;

         invoke.SetInvokeID(invokeId);

         cout << "==========> \n";
         cout << "==========> Enter Operation Class (1, 2, 3 or 4): <======== \n";
         cin >> opClass;

         invoke.SetOperation(2);
         invoke.SetClass(opClass);
         invoke.SetParameter(itstest::LocationArg, LOC_ARG_LEN);

         invoke.SetTimeOut(350);

         cpt = &invoke;

         ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);
         if(ret == ITS_SUCCESS)
         {
              cout << "\n **** TEST: TCAP Send component successful *****" << endl;
         }
         else
         {
              cout << "\n **** TEST: Component send failed ****" << endl;
         }
    }
    cout << "**** Sending on DID " << did << endl;

    ret = TCAP_Dialogue::Send(ISS7_Stack, dlg);

    if(ret != ITS_SUCCESS)
    {
         cout << "====>Failed to send Dialogue<====" << endl;
    }
    else
    {
         cout << "TCAP_TEST: Dialogue send succes PTYPE ="
              << dlg->GetDialogueType() << endl;
    }



}

int
GetReqChoice()
{
    int choice = 0;
    int op = -1;
    printf("Enter the choice ");
    do
    {
        printf("Enter the operation you want to send\n");
        printf("\t6.Exit\n");
        printf("\t1.Initial DP\n");
        printf("\t2.Event Report BCSM\n");
        printf("\t3.Apply Charging Report\n");
        printf("\t4.Release Call\n");
        printf("\t5.Activity Test\n");
        printf("\t%d.MapV3 UpdateLocation\n", MAP_V13_UPDATE_LOC);
        printf("\t%d.MapV3 UpdateLocation Res\n", MAP_V13_UPDATE_LOC_RES);
        printf("\t%d.MapV3 InsertSubscriberData\n", MAP_V13_INSERT_SUB_DATA);
        printf("\t%d.MapV13 ProvideSubscriberInfoArg\n", MAP_V13_PROVIDE_SUB_INFO);
        printf("\t%d.MapV13 DeleteSubscriberDataArg\n", MAP_V13_DELETE_SUB_DATA);
        printf("\t%d.MapV13 Cancel Location Arg\n", MAP_V13_CANCEL_LOCATION);
        printf("\t%d.MapV13 Purge MS Res\n", MAP_V13_PURGEMS_RES);

        printf("Choice : ");
        scanf("%d",&choice);

        switch (choice)
        {
            /*case 1:
                return OP_initialDP;

            case 2:
                return OP_eventReportBCSM;

            case 3:
                return OP_applyChargingReport;

            case 4:
                return OP_releaseCall;

            case 5:
                return OP_activityTest;*/

            default:
            {
               if (choice >= MAP_V13_UPDATE_LOC && choice <= MAP_V13_PURGEMS_RES)
               {
                   return choice;
               }
               printf ("Enter the proper option............\n\n");
            }
        }
    }while (1);

    return op;
}

ITS_ULONG GetMapOpCodeForChoice(ITS_INT choice)
{
    switch (choice)
    {
        case MAP_V13_UPDATE_LOC:
            return map_common::OP_updateLocation;

        case MAP_V13_UPDATE_LOC_RES:
            return map_common::OP_updateLocation;

        case MAP_V13_INSERT_SUB_DATA:
            return map_common::OP_insertSubscriberData;

        case MAP_V13_PROVIDE_SUB_INFO:
            return map_common::OP_provideSubscriberInfo;

        case MAP_V13_DELETE_SUB_DATA:
            return map_common::OP_deleteSubscriberData;

        case MAP_V13_CANCEL_LOCATION:
            return map_common::OP_cancelLocation;

        default:
            break;
    }
    return 0;
}

/*With component passed, based on the OP update the statistics accordingly */
void UpdateStats(TCAP_Component* its_cpt)
{
    ITS_LONG op;
    switch (its_cpt->GetComponentType())
    {
        case TCPPT_TC_INVOKE:
            {
                TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *>(its_cpt);
                ivk->GetOperation(op);

                if (op == map_common::OP_updateGprsLocation)
                {
                    appStats.u.hlrmap.ulr.m_in++;
                    /*TCAP_Invoke   ugl;
                    IMSI &imsi =  
                    int recent_msg_idx = appStats.recent_msg_idx++ % 10;
                    appStats.last_processed_msgs[recent_msg_idx] = "Received UGL Request with IMSI: ";
                    appStats.last_processed_msgs[recent_msg_idx] += udReq.getUserName().value();
                    appStats.recent_msg_idx = recent_msg_idx+1;*/
                }
                else if (op == map_common::OP_sendAuthenticationInfo)
                {
                    appStats.u.hlrmap.air.m_in++;
                }
                else if (op == map_common::OP_insertSubscriberData)
                {
                    appStats.u.hlrmap.idr.m_in++;
                }
                else if (op == map_common::OP_cancelLocation)
                {
                    appStats.u.hlrmap.clr.m_in++;
                }
            }
            break;

        case TCPPT_TC_RESULT_L:
        case TCPPT_TC_RESULT_NL:
            {
                TCAP_Result *resl = dynamic_cast<TCAP_Result *>(its_cpt);
                resl->GetOperation(op); 

                its_cpt->Print(cout);
                if (op == map_common::OP_updateGprsLocation)
                {
                    appStats.u.hlrmap.ula.m_in++;
                }
                else if (op == map_common::OP_insertSubscriberData)
                {
                    appStats.u.hlrmap.ida.m_in++;
                }
                else if (op == map_common::OP_sendAuthenticationInfo)
                {
                    appStats.u.hlrmap.aia.m_in++;
                }
                else if (op == map_common::OP_cancelLocation)
                {
                    appStats.u.hlrmap.cla.m_in++;
                }
            }
            break;

        default:
            break;
    }

    return;
}

void UpdateReqStats(ITS_LONG op)
{
    if (op == map_common::OP_updateGprsLocation)
    {
        appStats.u.hlrmap.ulr.m_in++;
        //int recent_msg_idx = appStats.recent_msg_idx++ % 10;
        //appStats.last_processed_msgs[recent_msg_idx] = "Received UpdateGPRS Location Request with IMSI: ";
        //appStats.last_processed_msgs[recent_msg_idx] += udReq.getUserName().value();
        //appStats.recent_msg_idx = recent_msg_idx+1; 
        //appStats.u.hlrmap.ula.m_out++;
    }
    else if (op == map_common::OP_sendAuthenticationInfo)
    {
        appStats.u.hlrmap.air.m_in++;
    }
    else if (op == map_common::OP_insertSubscriberData)
    {
        appStats.u.hlrmap.idr.m_in++;
    }
    return;
}

void UpdateRespStats(ITS_LONG op)
{
    if (op == map_common::OP_updateGprsLocation)
    {
        appStats.u.hlrmap.ula.m_in++;
        //int recent_msg_idx = appStats.recent_msg_idx++ % 10;
        //appStats.last_processed_msgs[recent_msg_idx] = "Received UpdateGPRS Location Request with IMSI: ";
        //appStats.last_processed_msgs[recent_msg_idx] += udReq.getUserName().value();
        //appStats.recent_msg_idx = recent_msg_idx+1; 
        //appStats.u.hlrmap.ula.m_out++;
    }
    else if (op == map_common::OP_sendAuthenticationInfo)
    {
        appStats.u.hlrmap.aia.m_in++;
    }
    else if (op == map_common::OP_insertSubscriberData)
    {
        appStats.u.hlrmap.ida.m_in++;
    }
    return;
}

void
CharToDigits(char  *d,char tmpBuff[], ITS_INT& len)
{

    ITS_UINT imsiLen = strlen((const char*)tmpBuff);
    ITS_INT  nIdx    = 0;
    ITS_UINT oIdx    = 0;

    cout<<"LEN ---->"<<imsiLen<<endl;
    while(oIdx <= imsiLen)
    {
        d[nIdx] = tmpBuff[oIdx];
        oIdx++;
        d[nIdx] |= (oIdx == 0) ?  0xF0 : ((tmpBuff[oIdx] << 4) & 0xF0);
        oIdx++;
        nIdx++;
        cout<<"INT VALEUE"<<nIdx<<"OIDX--->"<<oIdx<<endl;
    }
    len = nIdx;
}

/*AsnObject* BuildCapMsg(int opCode)
{
  AsnObject *obj= NULL;
  byte calledPartyArray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
  byte callingPartyArray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
  char  imsi_temp[16] = "123456789123456";
  ITS_OCTET imsi[8];

  switch(opCode)
  {
     case OP_initialDP:
     {
        cap_v3::InitialDPArg *idp = new cap_v3::InitialDPArg;

        int skey = 1000;
        ServiceKey* serviceKey = new ServiceKey(skey);
        idp->SetServiceKey(serviceKey);

        /* Set the Called Party No* /
        CalledPartyNumber* cdp =
               new CalledPartyNumber(FixedByteArrayToVector(calledPartyArray));
        idp->SetCalledPartyNumber(cdp);
        /* Set the Calling Party No* /
        CallingPartyNumber* clp =
              new CallingPartyNumber(FixedByteArrayToVector(callingPartyArray));
        idp->SetCallingPartyNumber(clp);
        
        /* IMSI * /
        for(int i=0;i<15;i++)
        {
           imsi_temp[i] = imsi_temp[i] - '0';
        }
        char bcd[20];
        int len = 0;
        CharToDigits(bcd, imsi_temp, len);
        cout <<"\n IMSI Lenght = " << len;
        for(int i=0;i<len;i++)
        {
          imsi[i]= bcd[i];
        }
        IMSI *iMSI = new IMSI(FixedByteArrayToVector(imsi));
        idp->SetIMSI(iMSI);
        obj = idp;
        break;
     }
     case OP_eventReportBCSM:
     {
        EventReportBCSMArg *erb = new EventReportBCSMArg;
        EventTypeBCSM *evType =new 
                        EventTypeBCSM(EventTypeBCSM::EVENT_TYPE_BCSM_OANSWER);

        erb->SetEventTypeBCSM(evType);

        EventSpecificInformationBCSM *evSpecInfo= new 
                                                  EventSpecificInformationBCSM;

        CalledPartyNumber* cdp =
               new CalledPartyNumber(FixedByteArrayToVector(calledPartyArray));

        EventSpecificInformationBCSM::OAnswerSpecificInfo *oAnswer = 
                      new EventSpecificInformationBCSM::OAnswerSpecificInfo;
        oAnswer->SetDestinationAddress(cdp);
        evSpecInfo->SetChoiceOAnswerSpecificInfo(oAnswer);

        erb->SetEventSpecificInformationBCSM(evSpecInfo);
        obj = erb;
 
        break;
     }
     case OP_applyChargingReport:
     {
        byte CallResult[12] = 
                        {0x01,0x02,0x03,0x04,0x05,0x6,0x7,0x8,0x9,0xa,0xb,0xc};

        ApplyChargingReportArg *acr = new 
                     ApplyChargingReportArg(FixedByteArrayToVector(CallResult));
        obj = acr;

        break;
     }
     case OP_releaseCall:
     {
        break;
     }
     case OP_requestReportBCSMEvent:
     {
        break;
     }
     case OP_applyCharging:
     {
        break;
     }
     case OP_activityTest:
     {
        break;
     }
     default:
     {
        cout << "--------------------------------------------------" << endl;
        cout << "Worng choice" << endl;
     }

  }
  return obj;

}*/

AsnObject* BuildProtocolMsg(int opcode)
{
    if (opcode >= MAP_V13_UPDATE_LOC) {
        // Set Application Context for MAP
        return BuildMapMsg((MAP_OPCODE)opcode);
    }
    //return BuildCapMsg(opcode);
    return NULL;
}


void
ITUTcapMsgs::InteractiveSendBeginDlg(ITS_HANDLE hdl)
{
    ITS_INT ret;
    TCAP_Dialogue* dlg;
    TCAP_Component* cpt;
    TCAP_Begin* begin;
    int hasAC = 0;
    int hasProtVer = 0;
    int hasUserInfo = 0;
    bool hasInvoke = false;
    int  invokeCount =  1;
    int val = 0;
    TCAP_Begin Qwp;
    int pcls=0;


    TCAP_Begin     beginDlg;
    begin = &beginDlg;
    printf("\n ******** Allocated DID: %d *******\n", did);
    TCAP_AllocateDialogueId(ISS7_Stack, &did);
    printf("\n ******** Allocated DID: %d *******\n", did);

    begin->SetDialogueID(did);
    begin->SetOrigAddr(cpa_itu);
    begin->SetOPC(oPC);
    //begin->SetOPC(topc);
    begin->Print(cout);
    //begin->SetOPC(itstest::opc);
   //cdp_itu.SetPointCode(itstest::dpc);
   //cdp_itu.SetSSN(itstest::dssn);
   cdp_itu.SetRouteByPCSSN(itstest::routeType);


    begin->SetDestAddr(cdp_itu);
    begin->SetDPC(dPC);
    //begin->SetDPC(tdpc);
    begin->Print(cout);
    //begin->SetDPC(dPC);

    /*cout << "=====> Enter 1 for SCCP PROTOCOL CLASS 1 Else \"0\" is set <=====\n";
    cin >> pcls;
    if(pcls!=1)
      pcls=0;*/

    //ITS_UINT compdialogSelection=0;
    ITS_UINT compdialogSelection=1;
    /*cout <<"==== > Enter \"1\" for component & Dialog Selection: ";
    cin >> compdialogSelection;*/

    if(compdialogSelection)
    {

    hasInvoke = true;

    hasProtVer = 1;

    if (hasProtVer & pcls)
    {
         begin->SetQualityOfService(QOSI_SEQ_CTRL | QOSI_PROT_VER, 0, 0);
    }
    else if (hasProtVer)
         begin->SetQualityOfService(QOSI_PROT_VER, 0, 0);


    std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::networkLocUpContext_v3);
    begin->SetApplicationContext(&acEnc[0], acEnc.size());

    /*cout << "=====> Enter 1 for UserInfo <=====\n";
    cin >> hasUserInfo;*/
    hasUserInfo = 1;

    if (hasUserInfo)
    {
         begin->SetUserInfo(itstest::USER_INFO, 25);
    }

    dlg = begin;

    /*cout << "======> \n";
    cout << "======> How many invokes? <======\n";
    cin >> invokeCount;*/
    for (int i = 1; i <= invokeCount; i++)
    {

         TCAP_Invoke    invoke;
         int invokeId;
         int opClass;

         /*cout << "========> \n";
         cout << "========> Enter Invoke Id: <======== \n";
         cin >> invokeId;*/
         invokeId = 1;

         invoke.SetInvokeID(invokeId);

         /*cout << "==========> \n";
         cout << "==========> Enter Operation Class (1, 2, 3 or 4): <======== \n";
         cin >> opClass;*/
         opClass = 3;

         invoke.SetClass(opClass);
         int opCode= -1;
         /*opCode = GetReqChoice();*/
         opCode = 100;
         if( opCode == -1)
         {
                return;
         }
         Octets *encOctets;
         AsnObject *obj = BuildProtocolMsg(opCode);
         if (opCode >= MAP_V13_UPDATE_LOC)
         {
             opCode = GetMapOpCodeForChoice(opCode);
         }

         invoke.SetOperation(opCode);
         EncodeMsg(obj, &encOctets);

         if (obj == NULL)
         {
            cout << "\n **** Object is Null ****" << endl;
         }
         cout << obj;

         invoke.SetParameter(encOctets->GetArray());
         invoke.SetTimeOut(30);

         cpt = &invoke;

         ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);

         if(ret == ITS_SUCCESS)
         {
              cout << "\n **** TEST: TCAP Send component successful *****" << endl;
              //int op;
              //invoke.GetOperation(op);
              UpdateStats(cpt);
              if(opCode == map_common::OP_cancelLocation)
              {
                  std::stringstream ostr;
                  CancelLocationArg *clrarg = static_cast<CancelLocationArg *> (obj); 
                  ostr << clrarg->GetCancellationType();
                  appStats.last_processed_msgs[appStats.recent_msg_idx+9] = "[TO IWF]-->SENT MAP CLR with [Identity]";
                  appStats.last_processed_msgs[appStats.recent_msg_idx+9] += ostr.str();
              }
         }
         else
         {
              cout << "\n **** TEST: Component send failed ****" << endl;
         }
    }

    }
    else
    {
        dlg = begin;
    }
    cout << "**** Sending on DID : " << did << endl;
    dlg->Print(cout);

    ret = TCAP_Dialogue::Send(ISS7_Stack, dlg);

    if(ret != ITS_SUCCESS)
    {
         cout << "**** Failed to send Dialogue ****" << endl;
    }
    else
    {
         cout << "TCAP_TEST: Dialogue send succes PTYPE ="
              << dlg->GetDialogueType() << endl;
    }
}

void
ITUTcapMsgs::InteractiveSendEnd(ITS_HANDLE hdl)
{
    ITS_INT ret;
    TCAP_Dialogue* dlg;
    TCAP_Component* cpt;
    TCAP_End       endDlg;
    int numResult = 0, outcome = 0;
    int invokeId;
    ITS_USHORT localDid;
    ITS_UINT rejectType;
    ITS_UINT rejectCode;
    ITS_BOOLEAN hasProtVer=0;
    ITS_BOOLEAN hasAC= 0 ;
    ITS_BOOLEAN hasUserInfo = 0;


    cout << "======> \n";
    cout << "======> Enter did : <======\n";
    cin >> localDid;
    endDlg.SetDialogueID(localDid);
    dlg = &endDlg;

    ITS_UINT compdialogSelection=0;
    cout <<"==== > Enter \"1\" for component & Dialog Selection: ";
    cin >> compdialogSelection;

    if(compdialogSelection)
    {
        cout << "======> \n";
        cout << "======> OutCome of transaction (1-success, 0-failure) <======\n";
        cin >> outcome;

        if (outcome)
        {
            cout << "=====> Enter 1 for Prot Version <=====\n";
            cin >> hasProtVer;
            if (hasProtVer)
                dlg->SetQualityOfService(QOSI_PROT_VER, 0, 0);
            cout << "=====> Enter 1 for AC Name <=====\n";
            cin >> hasAC;

            if (hasAC)
            {
                int no_AC=0;
                cout << "====> LENGTH OF AC NAME:" << endl;
                cin >>no_AC;
                dlg->SetApplicationContext(itstest::AC_NAME, no_AC);
            }

            cout << "=====> Enter 1 for UserInfo <=====\n";
            cin >> hasUserInfo;

            if (hasUserInfo)
            {
                dlg->SetUserInfo(itstest::USER_INFO, 25);
            }

            ITS_OCTET testByte[1];

            cout << "========> \n";
            cout << "========>How many Return Results? <========\n";
            cin >> numResult;
            for (int i = 1; i <= numResult; i++)
            {
                TCAP_Result    result;

                int resNL=0;
                cout <<"=== > If you want RETURN RESULT NOT LAST press \"0\":  ";
                cin >> resNL;
                if(!resNL)
                    result  = TCAP_Result(false);
                else
                    result  = TCAP_Result(true);

                cout << "==========> \n";
                cout << "==========> Enter Invoke Id: <==========\n";
                cin >> invokeId;

                result.SetInvokeID(invokeId);

                result.SetOperation(2);
                result.SetParameter(itstest::LocationArg, LOC_ARG_LEN);

                cpt = &result;

                ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);

                if(ret == ITS_SUCCESS)
                {
                     cout << "\n **** TEST: TCAP_Comp RESULT send successful ****" << endl;
                }
                else
                {
                     cout << "\n **** TEST: TCAP_Comp RESULT failed to send. ****" << endl;
                }
           }
       }
       else
       {
           TCAP_Cancel cancel;
           cout << "==========> Enter Invoke Id: <==========\n";
            cin >> invokeId;
            cancel.SetInvokeID(invokeId);
            cpt = &cancel;

            ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);

            APP_TRACE_DEBUG(("ComponentType = %02x", cpt->GetComponentType()));

            if(ret == ITS_SUCCESS)
            {
                cout << "\n **** TEST: TCAP_Comp send successful ****" << endl;
            }
            else
            {
                cout << "\n **** TEST: TCAP_Comp ERROR failed to send: "  <<ret << endl;
            }
        }
    }

    cout << "**** Sending on DID " << localDid << endl;

    ret = TCAP_Dialogue::Send(ISS7_Stack, dlg);

    if(ret != ITS_SUCCESS)
    {
        cout << "Failed to send Dialogue" << endl;
    }
    else
    {
        cout << "TCAP_TEST: Dialogue send succes PTYPE ="
             << dlg->GetDialogueType() << endl;
    }
}

void
ITUTcapMsgs::InteractiveSendContinue(ITS_HANDLE hdl)
{
    ITS_UINT ret;
    int numResult = 0;
    int numInvoke = 0;
    int invokeId;
    int i = 0;
    TCAP_Dialogue* dlg;
    TCAP_Component* cpt;
    TCAP_Continue* cont;
    TCAP_Continue Cwp;
    ITS_UINT rejectCode;

    TCAP_Continue  continueDlg;
    cont = &continueDlg;

    ITS_USHORT localDid;

    cout << "======> \n";
    cout << "======> Enter did : <======\n";
    cin >> localDid;
    cont->SetDialogueID(localDid);
    cont->SetOPC(oPC);
    dlg = cont;
    ITS_UINT compdialogSelection=1;

    if(compdialogSelection)
    {
    int  noterror;
    cout <<endl<<"=====>Enter 1 for Return Result & Invoke Component selection \"0\" for Error Component"<<endl;
    cin >> noterror;

    if(noterror)
    {
        if (1)
        {
             dlg->SetQualityOfService(QOSI_PROT_VER, 0, 0);
        }
        int no_AC=8;
        dlg->SetApplicationContext(AC_NAMEIDP, no_AC);

        cout << "======> \n";
        cout << "======>How many Return Results? \n";
        cin >> numResult;


        for (i = 0; i < numResult; i++)
        {
            TCAP_Result    result;

            int resNL=0;
            cout <<"=== > If you want RETURN RESULT NOT LAST press 0: ";
            cin >> resNL;
            if(!resNL)
            {
                result  = TCAP_Result(false);
            }
            else
            {
                result  = TCAP_Result(true);
            }

            cout << "Enter Invoke Id: \n";
            cin >> invokeId;

            result.SetInvokeID(invokeId);
            result.SetOperation(2);
            result.SetParameter(itstest::LocationArg, LOC_ARG_LEN);

            cpt = &result;

            ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);

            if(ret == ITS_SUCCESS)
            {
                cout << "TCAP_Comp RESULT send success:" << endl;
            }
            else
            {
                cout << "TCAP_Comp RESULT failed to send.:" << endl;
            }
        }

        cout << "How many Invokes? \n";
        cin >> numInvoke ;
        for (i = 1; i <= numInvoke; i++)
        {
            TCAP_Invoke    invoke;
            int opClass;

            cout << "=== >Enter Invoke Id: \n";
            cin >> invokeId;

            invoke.SetInvokeID(invokeId);
            int opCode= -1;
            opCode = GetReqChoice();
               if( opCode == -1)
            {
                   return;
            }
            Octets *encOctets;
            AsnObject *obj = NULL; //Set to NULL to avoid CAP compilation issues.BuildCapMsg(opCode);
            invoke.SetOperation(opCode);
            EncodeMsg(obj, &encOctets);

            if (obj == NULL)
            {
               cout << "\n **** Object is Null ****" << endl;
            }
            cout << obj;

            invoke.SetParameter(encOctets->GetArray());
            invoke.SetClass(1);
            invoke.SetTimeOut(30);

            cpt = &invoke;

            ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);
            if(ret == ITS_SUCCESS)
            {
                cout << "TCAP Send component success" << endl;
            }
            else
            {
                cout << "Component send failed :" << endl;
            }
        }

    }
    else
    {

        int choice = 0;

        cout << "==========> \n";
        cout << "==========> Choose RetError (0), or Reject (1). <==========\n";
        cin >> choice;
        if (choice)
        {
             TCAP_Reject reject;
             cout << "==========> Enter Invoke Id: <==========\n";
             cin >> invokeId;

             reject.SetInvokeID(invokeId);
             reject.SetProblem(0x81U, 0x01U);

             cpt = &reject;
        }
        else
        {

             TCAP_Error error;

             cout << "==========> \n";
             cout << "==========> Enter Invoke Id: <==========\n";
             cin >> invokeId;

             error.SetInvokeID(invokeId);

             cout << "==========> \n";
             cout << "==========> Enter Error Code: <==========\n";
             cin >> rejectCode;

             error.SetError(rejectCode);
             cpt = &error;
        }
        ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);
        if(ret == ITS_SUCCESS)
        {
            cout << "TCAP Send Error component success" << endl;
        }
        else
        {
            cout << "Component send failed :" << endl;
        }
    }
    }

    cout << "**** Sending on DID " << localDid << endl;

    ret = TCAP_Dialogue::Send(ISS7_Stack, dlg);

    if(ret != ITS_SUCCESS)
    {
        cout << "Failed to send Dialogue" << endl;
    }
    else
    {
        cout << "TCAP_TEST: Dialogue send succes PTYPE ="
             << dlg->GetDialogueType() << endl;
    }
}

void
ITUTcapMsgs::SendBeginDlg(ITS_HANDLE hdl, int inst, ITS_BOOLEAN addR)
{
   int         ret = 0;
   ITS_CTXT    dlgid;
   TCAP_Begin  begin;
   TCAP_Invoke ivk;
   ITS_HDR     hdr;
   ITS_UINT    timeout = 100;


   TCAP_AllocateDialogueId(ISS7_Stack, &dlgid);

   hdr.type = ITS_TCAP;
   hdr.context.dialogue_id = dlgid;

   begin.SetDialogueID(dlgid);
   begin.SetOrigAddr(cpa_itu);
   begin.SetOPC(oPC);

   begin.SetDestAddr(cdp_itu);
   begin.SetDPC(dPC); 

   APP_TRACE_DEBUG(("Send: DialogueId = %02x , DialogueType = %02x", dlgid, 
           begin.GetDialogueType()));

   ivk.SetInvokeID(GetInvokeID());
   ivk.SetTimeOut(timeout);

   ivk.SetClass(2);
   ivk.SetOperation(2);
 
   APP_TRACE_DEBUG(("Invokeid = %02x", ivk.GetInvokeID()));

   srand(time(NULL));

   if(0) //(rand() % 11) <= 5)
   {
       ivk.SetParameter(itstest::octs185, OCTS_185_LEN);
   }
   else
   {
       ivk.SetParameter(itstest::LocationArg, LOC_ARG_LEN);
   }

   ret = TCAP_Component::Send(ISS7_Stack, &begin, &ivk);

   if(ret == ITS_SUCCESS)
   {
       ret = TCAP_Dialogue::Send(ISS7_Stack, &begin);
       if(ret == ITS_SUCCESS)
       {
           stats.UpdateSendStats(begin.GetDialogueType());
           stats.UpdateSendStats(ivk.GetComponentType());

           APP_TRACE_DEBUG(("Send Dialogue Type = %02x Dlgid = %d", 
                          begin.GetDialogueType(), dlgid));
           APP_TRACE_DEBUG(("TCAP Cpt and DlgType Send success."));
       }
   }

   return;
}

void
ITUTcapMsgs::SendPreArrangedEnd(ITS_HANDLE hdl, ITS_USHORT dlgid)
{
   int ret = 0;

   TCAP_End end;

   end.SetDialogueID(dlgid);

   end.SetPreArrangedEnd(true);

   APP_TRACE_DEBUG(("SendPreArrangedEnd: DialogueId = %02x , DialogueType = %02x", dlgid, 
           end.GetDialogueType()));

   ret = TCAP_Dialogue::Send(ISS7_Stack, &end);

   if(ret == ITS_SUCCESS)
   {
       stats.UpdateSendStats(end.GetDialogueType(), true);
       APP_TRACE_DEBUG(("Send prearranged end success:\n"));
   }

  return;
}

int prevCptInvoke = -1;

std::map<ITS_CTXT, ITS_OCTET> gInvokeList;

int ITUTcapMsgs::SendMAPResponse(TCAP_Dialogue *dlg,
                                 TCAP_Component *cpt)
{
    TCAP_Continue tc_cont;
    TCAP_End      tc_end;
    TCAP_Invoke   isdr;
    TCAP_Result   ugla;
    TCAP_Result   saia;
    TCAP_Result   rfsr;
    TCAP_Result   puMsa;

    ITS_ByteArray app_ctxt = map_common::EncodeApplicationContext(map_common::networkLocUpContext_v3);
    tc_end.SetApplicationContext(app_ctxt);
    tc_cont.SetApplicationContext(app_ctxt);
    
    srand(time(0));
    int num = rand() % 17;

    if (dlg->GetDialogueType() == TCPPT_TC_BEGIN && cpt->GetComponentType() == TCPPT_TC_INVOKE) 
    {
        TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *> (cpt);
        ITS_LONG op;
        ivk->GetOperation(op);

        if (op == map_common::OP_sendAuthenticationInfo) 
        {
            app_ctxt = map_common::EncodeApplicationContext(map_common::infoRetrievalContext_v3);
            tc_end.SetApplicationContext(app_ctxt);

            AsnObject *tempSaia = BuildMapMsg(MAP_V13_SEND_AUTHENTICATION_INFO_RES);
            Octets *enc2 = 0;

            saia.SetInvokeID(cpt->GetInvokeID());

            EncodeMsg(tempSaia, &enc2);

            saia.SetParameter(enc2->GetArray());
            saia.SetOperation(map_common::OP_sendAuthenticationInfo);

            tc_end.SetDialogueID(dlg->GetDialogueID());

            if (TCAP_Component::Send(ISS7_Stack, &tc_end, &saia) == ITS_SUCCESS) 
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                {
                    APP_TRACE_DEBUG(("Sent SendAuthenticationInfoRes v3"));
                    //UpdateRespStats(op);
                    UpdateStats(&saia);
                }
            }
            
            /*Display Message Details*/
            appStats.last_processed_msgs[appStats.recent_msg_idx + 8] = "[TO IWF}<--SENT SAI Response";

            delete enc2;
            delete tempSaia;
            enc2 = 0;
            tempSaia = 0;
        }
        else if (op == map_common::OP_purgeMS) 
        {
            app_ctxt = map_common::EncodeApplicationContext(map_common::msPurgingContext_v3);
            tc_end.SetApplicationContext(app_ctxt);

            AsnObject *temppuMsa = BuildMapMsg(MAP_V13_PURGEMS_RES);
            Octets *enc2 = 0;

            puMsa.SetInvokeID(cpt->GetInvokeID());

            EncodeMsg(temppuMsa, &enc2);

            puMsa.SetParameter(enc2->GetArray());
            puMsa.SetOperation(map_common::OP_purgeMS);

            tc_end.SetDialogueID(dlg->GetDialogueID());

            if (TCAP_Component::Send(ISS7_Stack, &tc_end, &puMsa) == ITS_SUCCESS) 
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                {
                    APP_TRACE_DEBUG(("Sent PurgeMs_Res v3"));
                }
            }

            delete enc2;
            delete temppuMsa;
            enc2 = 0;
            temppuMsa = 0;
        }


        else if (op == map_common::OP_updateGprsLocation && 
                itstest::noISD) /*num < 5*/ /* In randomization we send End after receiving Begin */
        {
            AsnObject *tempUgla = BuildMapMsg(MAP_V13_UPDATE_GPRS_LOC_RES);
            Octets *enc2 = 0;
            std::map<ITS_CTXT, ITS_OCTET>::iterator itr = gInvokeList.find(dlg->GetDialogueID());

            if (itr != gInvokeList.end()) 
            {
                ugla.SetInvokeID((*itr).second);
                gInvokeList.erase(itr);
            } 
            else 
            {
                ugla.SetInvokeID(cpt->GetInvokeID());
            }

            EncodeMsg(tempUgla, &enc2);

            ugla.SetParameter(enc2->GetArray());
            ugla.SetOperation(map_common::OP_updateGprsLocation);

            tc_end.SetDialogueID(dlg->GetDialogueID());

            if (TCAP_Component::Send(ISS7_Stack, &tc_end, &ugla) == ITS_SUCCESS) 
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                {
                    APP_TRACE_DEBUG(("Sent UpdateGprsLocationRes"));
                    //UpdateRespStats(op);
                    UpdateStats(&ugla);
                }
            }

            /*Display Message Details*/
            std::stringstream ostr;
            UpdateGprsLocationRes *uglres = static_cast<UpdateGprsLocationRes *> (tempUgla); 
            ostr << uglres->GetHlr_Number();
            appStats.last_processed_msgs[appStats.recent_msg_idx + 5] = "[TO IWF}<--SENT UGL Res with [HLR-Number]:";
            appStats.last_processed_msgs[appStats.recent_msg_idx+5] += ostr.str();

            delete enc2;
            delete tempUgla;
            enc2 = 0;
            tempUgla = 0; 

            gRecvImsi.clear();
        }
        else if (op == map_common::OP_updateGprsLocation && 
                !itstest::noISD) /*num >= 5 In randomization we exchange Continue */
        {
            AsnObject *tempIsdr = BuildMapMsg(MAP_V13_INSERT_SUB_DATA);
            Octets *enc1 = 0;

            EncodeMsg(tempIsdr, &enc1);

            isdr.SetParameter(enc1->GetArray());
            isdr.SetClass(1);
            isdr.SetInvokeID(10);
            isdr.SetOperation(map_common::OP_insertSubscriberData);

            tc_cont.SetDialogueID(dlg->GetDialogueID());
            tc_cont.SetOrigAddr(false, oPC, oSN);

            std::pair<ITS_CTXT, ITS_OCTET> idpair(dlg->GetDialogueID(), cpt->GetInvokeID());
            gInvokeList.insert(idpair);

            if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &isdr) != ITS_SUCCESS) 
            {
                cout << "Failed To Send Component 1" << endl;
            }
            if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) != ITS_SUCCESS) 
            {
                cout << "Failed To send Dialogue Continue" << endl;
            }
            else
            {
                UpdateStats(&isdr);
                /*Display Message Details*/
                std::stringstream ostr;
                InsertSubscriberDataArg *isdreq = static_cast<InsertSubscriberDataArg *> (tempIsdr);
                ostr << isdreq->GetImsi();
                appStats.last_processed_msgs[appStats.recent_msg_idx + 3] = "[TO IWF]<--SENT ISD Arg (Part of UGL) with [IMSI]:";
                appStats.last_processed_msgs[appStats.recent_msg_idx+3] += ostr.str();
            }
            
            delete enc1;
            delete tempIsdr;
            enc1 = 0;
            tempIsdr = 0;            
        }
        else if (op == map_common::OP_readyForSM)
        {
            app_ctxt = map_common::EncodeApplicationContext(map_common::mwdMngtContext_v3);
            tc_end.SetApplicationContext(app_ctxt);

            AsnObject *tempRfsr = BuildMapMsg(MAP_V13_READY_FOR_SM_RES);
            Octets *enc2 = 0;

            rfsr.SetInvokeID(cpt->GetInvokeID());

            EncodeMsg(tempRfsr, &enc2);

            rfsr.SetParameter(enc2->GetArray());
            rfsr.SetOperation(map_common::OP_readyForSM);

            tc_end.SetDialogueID(dlg->GetDialogueID());

            if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS) 
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                {
                    APP_TRACE_DEBUG(("Sent SendAuthenticationInfoRes v3"));
                }
            }

            delete enc2;
            delete tempRfsr;
            enc2 = 0;
            tempRfsr = 0;
        }
 
    }
    else if (dlg->GetDialogueType() == TCPPT_TC_CONTINUE && cpt->GetComponentType() == TCPPT_TC_RESULT_L)
    {
        // We received a Continue; send an End
        
        TCAP_Result *res = dynamic_cast<TCAP_Result *> (cpt);
        ITS_LONG op;
        res->GetOperation(op);
        
        if (op == map_common::OP_insertSubscriberData)
        {
            AsnObject *tempUgla = BuildMapMsg(MAP_V13_UPDATE_GPRS_LOC_RES);
            Octets *enc2 = 0;
            std::map<ITS_CTXT, ITS_OCTET>::iterator itr = gInvokeList.find(dlg->GetDialogueID());

            if (itr != gInvokeList.end()) 
            {
                ugla.SetInvokeID((*itr).second);
                gInvokeList.erase(itr);
            } else 
            {
                ugla.SetInvokeID(cpt->GetInvokeID());
            }

            EncodeMsg(tempUgla, &enc2);

            ugla.SetParameter(enc2->GetArray());
            ugla.SetOperation(map_common::OP_updateGprsLocation);

            tc_end.SetDialogueID(dlg->GetDialogueID());

            if (TCAP_Component::Send(ISS7_Stack, &tc_end, &ugla) == ITS_SUCCESS) 
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                {
                    APP_TRACE_DEBUG(("Sent UpdateGprsLocationRes"));
                    //UpdateRespStats(map_common::OP_updateGprsLocation);
                    UpdateStats(&ugla);
                }
            }
            
            std::stringstream ostr;
            UpdateGprsLocationRes *uglres = static_cast<UpdateGprsLocationRes *> (tempUgla); 
            ostr << uglres->GetHlr_Number();
            appStats.last_processed_msgs[appStats.recent_msg_idx + 7] = "[TO IWF]<-- SENT UGL Arg with [HLR-Number]:";
            appStats.last_processed_msgs[appStats.recent_msg_idx+7] += ostr.str();

            delete enc2;
            delete tempUgla;
            enc2 = 0;
            tempUgla = 0;
        }
    }
}

int
ITUTcapMsgs::SendResponse(ITS_HANDLE hdl, ITS_USHORT dlgid, ITS_INT ivkid)
{
   int            ret = 0;
   TCAP_Continue  cont;
   TCAP_End       end;
   TCAP_Invoke    ivk;
   TCAP_Result    resl;

   TCAP_Dialogue*  dlg = NULL;
   TCAP_Component* cpt = NULL;

   srand(time(NULL));

   APP_TRACE_DEBUG(("DialogueId = %d InvokeId = %d ",dlgid, ivkid));

   if(1) /*rand() % 17 <= 13)*/
   {
      ret = 1; /*Tell the application to call DeleteApplicationRoute */

      end.SetDialogueID(dlgid);

      resl.SetInvokeID(ivkid);
      resl.SetOperation(2); 
      resl.SetParameter(itstest::LocationArg, LOC_ARG_LEN);
  
      cpt = &resl;
      dlg = &end;
   }
   else
   {
      ret = 2;
      cont.SetDialogueID(dlgid);
      cont.SetOrigAddr(cpa_itu);
      //cont.SetOPC(itstest::opc);
      cont.SetOPC(oPC);

      ivk.SetInvokeID(GetInvokeID());
      ivk.SetTimeOut(10);
      ivk.SetClass(2);
      ivk.SetOperation(2);

      ivk.SetParameter(itstest::LocationArg, LOC_ARG_LEN);

      cpt = &ivk;
      dlg = &cont;
   }

   APP_TRACE_DEBUG(("SendResponse: DialogueId = %02x , DialogueType = %02x", dlgid, 
           dlg->GetDialogueType()));

   APP_TRACE_DEBUG(("SendResponse: InvokeId = %02x", cpt->GetInvokeID()));

   if(TCAP_Component::Send(ISS7_Stack, dlg, cpt) == ITS_SUCCESS)
   {
       if(TCAP_Dialogue::Send(ISS7_Stack, dlg) == ITS_SUCCESS)
       {
           stats.UpdateSendStats(dlg->GetDialogueType(), false);
           stats.UpdateSendStats(cpt->GetComponentType(), true);

           APP_TRACE_DEBUG(("DlgType = %02x  Dialogue ID = %02x ", 
                             dlg->GetDialogueType(), dlg->GetDialogueID()));
           APP_TRACE_DEBUG(("Dialogue/Component send Success:"));
       }
   }

   return ret;
}

#include "app_map_msgs.cpp"


/*****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      octets - used to store the encoded value of the inputted mesg .
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
void EncodeMsg(AsnObject* p, Octets** octets)
{
    cout << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Printing ASN value before encoding..." << endl;

    if (p == NULL)
    {
        return;
    }

    cout << endl << *p << endl;

    Octets* tmpOctets;

    try
    {
        tmpOctets = p->Encode();
    }
    catch (AsnEncodeError& exc)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Exception during encoding phase..." << endl;
        cout << exc.GetDescription() << endl;
        cout << "Exit test..." << endl;
    }

    cout << endl;
    cout << "--------------------------------------------------" << endl;
    *octets = tmpOctets;
}



#endif
