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
 * LOG: Revision 1.1.2.1  2014/07/29 09:49:58  jkchaitanya
 * LOG: added a new directory cap_sample useful for load testing
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27  2013/10/03 12:34:37  jkchaitanya
 * LOG: changes for displaying 146 as MSC SSN
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.26  2013/09/27 05:58:36  jkchaitanya
 * LOG: changes in conditions to send cap response if MSC SSN is 146
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.25  2013/09/03 12:55:52  jkchaitanya
 * LOG: changes for the bug 2164 removed unwanted flag in json
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.24  2013/09/02 06:07:00  jkchaitanya
 * LOG: changes for the bug 2145
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.23  2013/08/30 07:10:48  jkchaitanya
 * LOG: changes for AddressIndicator for bug 1165
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.22  2013/08/29 10:52:34  jkchaitanya
 * LOG: changes for bug 2085
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.21  2013/08/29 06:06:59  jsarvesh
 * LOG: Changes done for Conflicts in OpCodes and encoding of PDN_GW_Update
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.20  2013/08/20 08:43:34  jkchaitanya
 * LOG: changes for the bug 2061
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.19  2013/08/13 09:18:33  jkchaitanya
 * LOG: changes for the issue mentioned in the bug 1986(ERB in Tc_Cont and ACR in Tc_End)
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.18  2013/08/12 15:35:14  jkchaitanya
 * LOG: changes to enhance cap tool for bug 1896
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.17  2013/08/12 04:47:27  jkchaitanya
 * LOG: changes to remove warning
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.16  2013/08/12 04:38:17  jkchaitanya
 * LOG: changes for missing code in CVS for bug 2022
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.15  2013/08/06 13:35:57  jkchaitanya
 * LOG: changes are done to move set sleep time changes to default case place if continue comes to simulate ASR case
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.14  2013/08/02 06:51:36  jkchaitanya
 * LOG: changes for tool enhancements
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.13  2013/07/31 08:42:47  jkchaitanya
 * LOG: changes for the bug 1964
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.12  2013/07/30 11:48:47  jkchaitanya
 * LOG: changes to change the Exit option value in switch case
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.11  2013/07/30 05:03:52  jkchaitanya
 * LOG: changes to handle Release for SMS
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.10  2013/07/30 04:46:55  jkchaitanya
 * LOG: changes to ahndle RRB and Continue for SMS
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.9  2013/07/29 12:27:45  jkchaitanya
 * LOG: changes for sms support messages in cap tool and asn
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.8  2013/07/23 09:11:05  jkchaitanya
 * LOG: change in the application context for cap messages
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.7  2013/07/23 05:41:16  jkchaitanya
 * LOG: changes for the tool bug 1896
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.6  2013/07/22 09:45:08  jkchaitanya
 * LOG: changes for the bug 1902 printing SSN values for MSC and SCP
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.5  2013/07/18 08:36:48  jkchaitanya
 * LOG: changes to restrict ERB and ACR in case os Ro-ACR
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.4  2013/07/17 03:49:52  jkchaitanya
 * LOG: changes done for not sending ERB and ACR in TcCont for ASR case is reverted back, which is not required
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.3  2013/07/16 07:06:15  jkchaitanya
 * LOG: changes for review comments and release call decode
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.2  2013/07/12 06:47:08  jkchaitanya
 * LOG: changes in map tool to enhance cap supported changes for some cases like ASR and RAR testing
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.1  2013/07/09 11:27:21  jkchaitanya
 * LOG: changes for cap tool enhancement
 * LOG:
 * LOG: Revision 1.1.1.1.2.29  2013/06/14 08:39:33  jsarvesh
 * LOG: Added the PurgeMSArg option for Load
 * LOG:
 * LOG: Revision 1.1.1.1.2.28  2013/06/10 07:09:12  jsarvesh
 * LOG: enhanced for Load Run from MAP-Tool
 * LOG:
 * LOG: Revision 1.1.1.1.2.27  2013/06/03 10:17:05  jsarvesh
 * LOG: Changes done for setting application context for sending UGLRes and not to send ResetArg and Ready_For_SMArg as TCAP_Begin
 * LOG:
 * LOG: Revision 1.1.1.1.2.26  2013/06/03 07:33:51  jkchaitanya
 * LOG: changes for the bugs 1652,1655,1657
 * LOG:
 * LOG: Revision 1.1.1.1.2.25  2013/05/29 07:43:37  jsarvesh
 * LOG: Added Logs For SSN Number And Hardcoding GTT Route To 1 As Not Supported Now
 * LOG:
 * LOG: Revision 1.1.1.1.2.24  2013/05/29 04:28:47  jvikram
 * LOG: changed the log for reset
 * LOG:
 * LOG: Revision 1.1.1.1.2.23  2013/05/28 15:21:55  jsarvesh
 * LOG: Taking Input for OSSN and DSSN
 * LOG:
 * LOG: Revision 1.1.1.1.2.22  2013/05/24 13:31:53  millayaraja
 * LOG: Added Activate and Deactivate Trace Mode mapping
 * LOG:
 * LOG: Revision 1.1.1.1.2.21  2013/05/23 12:28:00  jkchaitanya
 * LOG: changes for the bug fixes for 1579,1581,1587,1588,1591,1592 and IDR-to-InsertSubDataArg changes
 * LOG:
 * LOG: Revision 1.1.1.1.2.20  2013/05/22 15:24:47  jsarvesh
 * LOG: IWF Phase-II Changes
 * LOG:
 * LOG: Revision 1.1.1.1.2.19  2013/05/21 11:17:28  jsarvesh
 * LOG: enhancement for MAP-DIAMETER translator Phase-II
 * LOG:
 * LOG: Revision 1.1.1.1.2.18  2013/05/02 04:33:23  jsarvesh
 * LOG: IWFPhaseII Changes for UGL, SAI and PurgeMS
 * LOG:
 * LOG: Revision 1.1.1.1.2.17  2013/04/05 05:30:00  jsarvesh
 * LOG: changed for simulator crash if no reponse is received from iwf
 * LOG:
 * LOG: Revision 1.1.1.1.2.16  2013/04/02 11:25:09  jsarvesh
 * LOG: added application context for srever initiated messages
 * LOG:
 * LOG: Revision 1.1.1.1.2.15  2013/03/21 04:53:33  jsarvesh
 * LOG: change in sendauthnticationinfo error code
 * LOG:
 * LOG: Revision 1.1.1.1.2.14  2013/03/15 07:39:51  jsarvesh
 * LOG: enhancement for map simulator added Activate tracemode reset arg deactivate trace mode
 * LOG:
 * LOG: Revision 1.1.1.1.2.13  2013/03/08 05:11:23  jsarvesh
 * LOG: implementation for map message through json
 * LOG:
 * LOG: Revision 1.1.1.1.2.12  2013/03/08 04:19:34  jsarvesh
 * LOG: implementation for map message through json
 * LOG:
 * LOG: Revision 1.1.1.1.2.11  2013/03/05 18:42:42  brajappa
 * LOG: BugId: 1165 - setting the network Indicator for CPA
 * LOG:
 * LOG: Revision 1.1.1.1.2.10  2013/02/22 19:59:13  lakshman
 * LOG: add gtt test info.
 * LOG:
 * LOG: Revision 1.1.1.1.2.9  2013/02/15 15:50:26  jvikas
 * LOG: PUR/PurgeMS related code changes.
 * LOG:
 * LOG: Revision 1.1.1.1.2.8  2013/02/15 12:46:28  brajappa
 * LOG: Sending and receiving Cancel Location Arg
 * LOG:
 * LOG: Revision 1.1.1.1.2.7  2013/02/14 09:55:16  brajappa
 * LOG: ISD sending withing UGLA is handled through command line, handling readyForSM
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
#ident "$Id: app_itu_msgs.cpp,v 1.1.2.1 2014/07/29 09:49:58 jkchaitanya Exp $"

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
#include <string.h>

#include <map>

#include <app_cmn.h>
#include <app_const.h>
#include <app_msgs.h>
#include <app_trace.h>
#include <app_stats.h>
#include <app_timer.h>

#include "app_cap_msgs.cpp"
#if defined (Q)
#include <quantify.h>
#endif

ITS_OCTET AC_NAMEIDP[] = {0x04,0x00,0x00,0x01,0x00,0x32,0x01}; 
//ITS_OCTET AC_NAMEIDP[] = {0x04,0x00,0x00,0x01,0x00,0x14,0x03,0x04};

using namespace std;
using namespace its;

static void SetGlobalTitleAddr(its::SCCP_Address&);

extern TcapStats      stats;
void  EncodeMsg(AsnObject* p, Octets** octets);

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
#define TCAP_UNI_TYPE        TCPPT_TC_UNI
#define TCAP_CONTINUE_TYPE   TCPPT_TC_CONTINUE
#define TCAP_P_ABORT_TYPE    TCPPT_TC_P_ABORT
#define TCAP_U_ABORT_TYPE    TCPPT_TC_U_ABORT
#define TCAP_ERROR_TYPE      TCPPT_TC_U_ERROR
#define TCAP_R_REJECT_TYPE   TCPPT_TC_R_REJECT
#define TCAP_U_REJECT_TYPE   TCPPT_TC_U_REJECT
#define TCAP_L_REJECT_TYPE   TCPPT_TC_L_REJECT

#define OCTS_185_LEN 184 // sizeof(itstest::octs185)/sizeof(ITS_OCTET)
#define CallingLegIdStr "01"
#define CalledLegIdStr "02"
#define TCAP_error_RetVal  30
#define Release_NormalCalClear 31
#define Release_UserBusy 32
#define Release_NoAns 33
#define OPERATOR_DETERMINED_BARRING 0x08

ITS_CTXT did = 0;

ITS_UINT dPC=0;
ITS_UINT oPC=0;
ITS_UINT sSN=149;
ITS_UINT oSN=6;



static ITUTcapMsgs * ituTcapMsgs = NULL;
static ITS_OCTET invokeId = 127;

int GetReqChoice();
//ITS_ULONG GetMapOpCodeForChoice(ITS_INT choice);
int InvokeID = 60;
ITS_BOOLEAN  LastCptRcvd = ITS_FALSE;
bool IsReleaseIfdurationExceededisSet = false;
int NumOfERBandACHinTc_Cont = 0;
bool sendERBandACRinTcEnd = false;
int prevCptInvoke = -1;

std::map<ITS_CTXT, ITS_OCTET> gInvokeList;

int CapVersion = cap::CAPV2_VERSION;
cap_v3::CalledPartyNumber RecvCdPtyNo;

void
ITUTcapMsgs::InitExternals()
{

}

ITUTcapMsgs * ITUTcapMsgs::GetItuInstance()
{
    if(ituTcapMsgs == NULL)
    {
        ituTcapMsgs = new ITUTcapMsgs;
    }
    return ituTcapMsgs;
}

int ITUTcapMsgs::HandleMessage(engine::Worker *work, its::ITS_Event& evt)
{
    TCAP_Dialogue*  its_dlg = NULL; /* Receive dialogue*/
    TCAP_Component* its_cpt = NULL; /* Receive component*/

    ITS_USHORT   cpt_type_recvd = 0x00;
    ITS_USHORT   dlg_type_recvd = 0x00;

	#if 0 
    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];
	#endif 
    switch (TCAP_MSG_TYPE(&evt.GetEvent()))
    {
        case ITS_TCAP_CPT:
				{
            its_dlg = reinterpret_cast<TCAP_Dialogue *>(work->GetUserData());

            TCAP_Component::Receive(ISS7_Stack, evt, its_dlg, &its_cpt);

            APP_TRACE_DEBUG(("Received: Component Type %02x",
                        its_cpt->GetComponentType()));

            cpt_type_recvd = its_cpt->GetComponentType();
            APP_TRACE_DEBUG(("Received: InvokeId %02x, InvokeType %02x",
                        its_cpt->GetInvokeID(), cpt_type_recvd));

            stats.UpdateRecvStats(its_cpt->GetComponentType());

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
                    LastCptRcvd = ITS_TRUE; /*we got all cpts*/
                }
            }

            APP_TRACE_DEBUG(("Last CPT received? = %d", LastCptRcvd));

            if(cpt_type_recvd != TCAP_L_CANCEL_TYPE ||
                    LastCptRcvd )
            {
				if(sSN == 146 && oSN == 146)
                {
                    SendCAPResponse(its_dlg, &its_cpt, work);
                }
            }

            if(its_cpt)
            {
                delete its_cpt;
                its_cpt = NULL;
            }
            //NOTE: Delteting the dialogue after processing of the last component received in a single dialogue.
            if(its_dlg && cpt_type_recvd != TCAP_L_CANCEL_TYPE && LastCptRcvd)
            {
                delete its_dlg;
                its_dlg = NULL;
                LastCptRcvd = ITS_FALSE;
            }
            break;
        	}
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
                LastCptRcvd = ITS_FALSE;
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
					if(sSN == 146 && oSN == 146)
                    {
                        SendCAPResponse(its_dlg, &its_cpt, work);
                    }

                    delete its_dlg;
                    its_dlg = NULL;
                }

                break;
            }
        default:
            APP_TRACE_ERROR(("Received neither Dlg not CPT."));
            break;
    }

    return ITS_SUCCESS;
}
int ITUTcapMsgs::SendCAPResponse(TCAP_Dialogue* dlg, 
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
   else
   {
       APP_TRACE_ERROR(("Received Dlg without CPT."));
       return !ITS_SUCCESS;
   }


   APP_TRACE_DEBUG(("Inside SendCAPResponse() function."));

   ITS_LONG op ;

   try
   {
       switch ((*cpt)->GetComponentType())
       {
           case TCPPT_TC_INVOKE:
           {
               TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *>(*cpt);
               ivk->GetOperation(op);

               if (op == cap::OP_requestReportBCSMEvent)
               {
               	   APP_TRACE_DEBUG(("Received RRB."));
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   cap_v3::RequestReportBCSMEventArg rrb;
                   Octets octs(param);
                   rrb.Decode(octs);
				   if ( itstest::appMode == UNIT_TEST)
	                   rrb.Print(cout);
               }
               else if (op == cap::OP_applyCharging)
               {
               	   APP_TRACE_DEBUG(("Received AC."));               
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   cap_v3::ApplyChargingArg ach;
                   Octets octs(param);
                   ach.Decode(octs);
				   if ( itstest::appMode == UNIT_TEST)
	                   ach.Print(cout);
                   cap_v3::AChBillingChargingCharacteristics acc = ach.GetAChBillingChargingCharacteristics();
                   const std::vector<byte>& vec = acc.GetArray();
                   Octets camelach(vec,vec.size());
                   CAMEL_AChBillingChargingCharacteristics camelACH;
                   camelACH.Decode(camelach);
				   if ( itstest::appMode == UNIT_TEST)
				   		camelACH.Print(cout);
				   

                   if(camelACH.ChoiceTimeDurationCharging())
                   {
                        cap_v3::CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging tdc = camelACH.GetChoiceTimeDurationCharging();
                        if(tdc.GetReleaseIfdurationExceeded().GetValue() == true)
                        {
                           IsReleaseIfdurationExceededisSet = true; 
                        }
                   }
               }
               else if (op == cap::OP_continue)
               {
					APP_TRACE_DEBUG(("Received CONT."));
					
					std::vector<byte> param;
					ivk->GetParameter(param);
					cap_v3::ContinueWithArgumentArg contarg;
					Octets octs(param);
					contarg.Decode(octs);
					if ( itstest::appMode == UNIT_TEST)
						contarg.Print(cout);
                    //NOTE: Nothing to do as this is just an indication to continue
               }
               else if (op == cap::OP_releaseCall)
               {
                    //NOTE: Nothing to do as this is just a release call
                    APP_TRACE_DEBUG(("Received REL."));
                    std::vector<byte> param;
                    ivk->GetParameter(param);
                    Octets octs(param);
                    cap_v3::Cause cau;
                    cau.Decode(octs);
					if ( itstest::appMode == UNIT_TEST)
                    	cau.Print(cout);
                   
               }
               else if (op == cap::OP_requestReportSMSEvent)
               {
               	   APP_TRACE_DEBUG(("Received RRB SMSEvent."));
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   cap_v3::RequestReportSMSEventArg rrsms;
                   Octets octs(param);
                   rrsms.Decode(octs);
				   if ( itstest::appMode == UNIT_TEST)
                   	rrsms.Print(cout);
               }
               else if (op == cap::OP_continueSMS)
               {
               	   APP_TRACE_DEBUG(("Received CONT SMS."));
				   std::vector<byte> param;
                   ivk->GetParameter(param);
                   cap_v3::ContinueWithArgumentArg contsms;
                   Octets octs(param);
                   contsms.Decode(octs);
				   if ( itstest::appMode == UNIT_TEST)
                   	contsms.Print(cout);
                   //NOTE: Nothing to do as this is just an indication  to continue
               }
               else if (op == cap::OP_releaseSMS)
               {
               	   APP_TRACE_DEBUG(("Received REL SMS."));
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   cap_v3::ReleaseSMSArg rsmsa;
                   Octets octs(param);
                   rsmsa.Decode(octs);
				   if ( itstest::appMode == UNIT_TEST)
                   	rsmsa.Print(cout);
               }
			   else if(op == cap::OP_eventReportBCSM)
			   	{
			   	   APP_TRACE_DEBUG(("Received ERB."));
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   cap_v3::EventReportBCSMArg erb;
                   Octets octs(param);
                   erb.Decode(octs);
				   if ( itstest::appMode == UNIT_TEST)
                   	erb.Print(cout);
								   	
			   	}
			   else if( op == cap::OP_initialDP)
			   	{
			   	   APP_TRACE_DEBUG(("Received IDP."));
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   cap_v3::InitialDPArg idp;
                   Octets octs(param);
                   idp.Decode(octs);
				   if ( itstest::appMode == UNIT_TEST)
                   	idp.Print(cout);
			   	
			   	}
			   else if(op == cap::OP_applyChargingReport)
			   	{
			   	   APP_TRACE_DEBUG(("Received ACR."));
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   cap_v3::ApplyChargingReportArg acr;
                   Octets octs(param);
                   acr.Decode(octs);
				   if ( itstest::appMode == UNIT_TEST)
                   	acr.Print(cout);
			   	
			   	}
			   else if (op == cap::OP_initialDPSMS)
			   	{
			   	   APP_TRACE_DEBUG(("Received SMS idp."));
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   cap_v3::InitialDPSMSArg acr;
                   Octets octs(param);
                   acr.Decode(octs);
				   if ( itstest::appMode == UNIT_TEST)
                   	acr.Print(cout);
			   	
			   	}
			   	
               
           }
           break;

           case TCPPT_TC_RESULT_L:
           case TCPPT_TC_RESULT_NL:
           {
               TCAP_Result *resl = dynamic_cast<TCAP_Result *>(*cpt);
               resl->GetOperation(op); 

               (*cpt)->Print(cout);
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
   SendResponses(dlg, *cpt);

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
       case TCAP_UNI_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received UNI DLG ****\n"));
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

void 
ITUTcapMsgs::SetSCCPAddress()
{
   bool networkInd = false;
   printf("=====$ ITUITcapMsgs::SetSCCPAddress $====\n");

   char buf[256];
   //int routtype_fromuser=0;

   cout <<endl <<"=== >Enter OPC:";
   cin >> oPC;
   cpa_itu.SetPointCode(oPC);
   cout <<endl <<"=== >Enter DPC:";
   cin >> dPC;
   cdp_itu.SetPointCode(dPC);
   
   cout <<endl <<"=== >SSN for MSC/SCP = \"146\"";
   cout <<endl <<"=== >Enter Destination SSN:";
   cin >> sSN;
   cdp_itu.SetSSN(sSN);

   cout <<endl <<"=== >SSN for MSC/SCP = \"146\"";

   cout <<endl <<"=== >Enter Source SSN:";
   cin >> oSN;
   cpa_itu.SetSSN(oSN);

   if(itstest::apc == 0)
   {
       /* User did not set the adjacent pc so assume 
        * our adjacent is destination pc 
        */
       //itstest::apc = itstest::dpc;
   }

   /*printf("\n=== > IF you want GTT enter \"0\" Else Press \"1\"\n");
   cin >> routtype_fromuser;
   if (!routtype_fromuser)
   {
       itstest::routeType=0; / *Temp for GTT Test - Ahil * /
       printf("ROUTETYPE==%d\n",itstest::routeType);
   }*/

   itstest::routeType=1;
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
    //TCAP_Component* cpt;
    TCAP_Abort     abortDlg;
    ITS_USHORT localDid;
    //ITS_OCTET abrtInfo[3] = {0xd8,0x01,0x01};
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


AsnObject* BuildProtocolMsg(int opcode)
{
    
    return BuildCapMsg(opcode);
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

         invoke.SetClass(opClass);

         int opCode= -1;
         opCode = GetReqChoice();

         Octets *encOctets;
         AsnObject *obj = BuildProtocolMsg(opCode);
         invoke.SetOperation(opCode);

         EncodeMsg(obj, &encOctets);

         if (obj == NULL)
         {
            cout << "\n **** Object is Null ****" << endl;
         }
         cout << obj;

         //invoke.SetParameter(itstest::LocationArg, LOC_ARG_LEN);
         invoke.SetParameter(encOctets->GetArray());

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
        printf("\t8.Exit\n");
        printf("\t1.Initial DP\n");
        printf("\t2.Initial DP SMS\n");
#if 0
        printf("\t3.Event Report BCSM\n");
        printf("\t4.Apply Charging Report\n");
        printf("\t5.Release Call\n");
        printf("\t6.Activity Test\n");
        printf("\t7.Event Report SMS\n");

        printf("\t%d.MapV3 UpdateGprsLocation\n", MAP_V13_UPDATE_GPRS_LOC);
        printf("\t%d.MapV3 UpdateLocation\n", MAP_V13_UPDATE_LOC);
        printf("\t%d.MapV3 UpdateLocation Res\n", MAP_V13_UPDATE_LOC_RES);
        printf("\t%d.MapV3 InsertSubscriberData\n", MAP_V13_INSERT_SUB_DATA);
        printf("\t%d.MapV13 ProvideSubscriberInfoArg\n", MAP_V13_PROVIDE_SUB_INFO);
        printf("\t%d.MapV13 DeleteSubscriberDataArg\n", MAP_V13_DELETE_SUB_DATA);
        printf("\t%d.MapV13 Cancel Location Arg\n", MAP_V13_CANCEL_LOCATION);
        printf("\t%d.MapV13 Purge MS Res\n", MAP_V13_PURGEMS_RES);
        printf("\t%d.MapV13 TraceActivateModeArg\n", MAP_V13_TRACE_ACTIVATE_MODE_ARG);
        printf("\t%d.MapV13 TraceDeActivateModeArg\n", MAP_V13_TRACE_DEACTIVATE_MODE_ARG);
        printf("\t%d.MapV13 ResetArg\n", MAP_V13_RESET_ARG);
        printf("\t%d.MapV13 PurgeMSArg\n", MAP_V13_PURGE_MS_ARG);
        printf("\t%d.MapV13 SendAuthenticationInfoArg\n", MAP_V13_SEND_AUTH_INFO_ARG);
        printf("\t%d.MapV13 ReadyForSM_Arg\n", MAP_V13_READY_FOR_SM_ARG);
#endif		

        printf("Choice : ");
        scanf("%d",&choice);

        switch (choice)
        {
            case 1:
                return OP_initialDP;

            case 2:
                return OP_initialDPSMS;
#if 0
            case 3:
                return OP_eventReportBCSM;

            case 4:
                return OP_applyChargingReport;

            case 5:
                return OP_releaseCall;

            case 6:
                return OP_activityTest;
         
            case 7:
                return OP_eventReportSMS;
#endif       
            case 8:
                exit(0);

            default:
            {
			   #if 0
               if (choice >= MAP_V13_UPDATE_GPRS_LOC && choice <= MAP_V13_READY_FOR_SM_ARG)
               {
                   return choice;
               }
			   #endif
               printf ("Enter the proper option............\n\n");
            }
        }
    }while (1);

    return op;
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

void
ITUTcapMsgs::InteractiveSendBeginDlg(ITS_HANDLE hdl)
{
    ITS_INT ret;
    TCAP_Dialogue* dlg;
    TCAP_Component* cpt;
    TCAP_Begin* begin;
    //int hasAC = 0;
    int hasProtVer = 0;
    int hasUserInfo = 0;
    bool hasInvoke = false;
    int  invokeCount =  1;
    //int val = 0;
    TCAP_Begin Qwp;
    int pcls=0;

    //NOTE: making default value to 0 for Multiple Intermediate ERB and ACR 
    NumOfERBandACHinTc_Cont = 0;
    sendERBandACRinTcEnd = false;

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

    cout << "=====> Enter 1 for SCCP PROTOCOL CLASS 1 Else \"0\" is set <=====\n";
    cin >> pcls;
    if(pcls!=1)
      pcls=0;

    ITS_UINT compdialogSelection=0;
    cout <<"==== > Enter \"1\" for component & Dialog Selection: ";
    cin >> compdialogSelection;

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



    cout << "=====> Enter 1 for UserInfo <=====\n";
    cin >> hasUserInfo;

    if (hasUserInfo)
    {
         begin->SetUserInfo(itstest::USER_INFO, 25);
    }

    dlg = begin;

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

         invoke.SetClass(opClass);
         int opCode= -1;
         opCode = GetReqChoice();
         Octets *encOctets;
         AsnObject *obj = BuildProtocolMsg(opCode);
		 if(opCode == cap::OP_initialDP || opCode == cap::OP_eventReportBCSM || opCode == cap::OP_applyChargingReport)
         {
             std::vector<byte> acenc = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
             begin->SetApplicationContext(&acenc[0], acenc.size());
         }
         else if(opCode == cap::OP_eventReportSMS || opCode == cap::OP_initialDPSMS)
         {
             std::vector<byte> acenc = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
             begin->SetApplicationContext(&acenc[0], acenc.size());
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
    //ITS_UINT rejectType;
    //ITS_UINT rejectCode;
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

            //ITS_OCTET testByte[1];

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
            AsnObject *obj = BuildCapMsg(opCode);
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

void ITUTcapMsgs::SendBeginDlg(ITS_HANDLE hdl, int inst, ITS_BOOLEAN addR, int opCode)
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

   ivk.SetClass(3);

   Octets *encOctets;
   AsnObject *obj = BuildProtocolMsg(opCode);
   EncodeMsg(obj, &encOctets);

   if (obj == NULL)
   {
       cout << "\n **** Object is Null ****" << endl;
   }
   cout << obj;
  if (encOctets == NULL)
	  {
   cout << "\n **** Object is Null ****" << endl;
	  }
   if(opCode == cap::OP_initialDP || opCode == cap::OP_eventReportBCSM || opCode == cap::OP_applyChargingReport)
 	{
     std::vector<byte> acenc = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
     begin.SetApplicationContext(&acenc[0], acenc.size());
 	}
 	else if(opCode == cap::OP_eventReportSMS || opCode == cap::OP_initialDPSMS)
 	{
     std::vector<byte> acenc = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
     begin.SetApplicationContext(&acenc[0], acenc.size());
 	}
   ivk.SetOperation(opCode);
 
   APP_TRACE_DEBUG(("Invokeid = %02x", ivk.GetInvokeID()));

   srand(time(NULL));

   /*if(0) //(rand() % 11) <= 5)
   {
       ivk.SetParameter(itstest::octs185, OCTS_185_LEN);
   }
   else
   {
       ivk.SetParameter(itstest::LocationArg, LOC_ARG_LEN);
   }*/
   #if 0
   switch(opCode)
   {
        case map_common::OP_updateGprsLocation:
            {
                ivk.SetParameter(encOctets->GetArray());
                //ivk.SetParameter(itstest::LocationArg, LOC_ARG_LEN);
                break;
            }
        case map_common::OP_purgeMS:
            {   
                ivk.SetParameter(encOctets->GetArray());
                break;
            }
        case map_common::OP_sendAuthenticationInfo:
            {
                ivk.SetParameter(encOctets->GetArray());
                //ivk.SetParameter(itstest::AuthenticationArg, AUTH_ARG_LEN);
                break;
            }

   }
   #endif
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
int ITUTcapMsgs::SendResponses(TCAP_Dialogue *dlg,
                                 TCAP_Component *cpt)
{

    APP_TRACE_DEBUG(("Inside SendResponses() function."));
    TCAP_Continue tc_cont;
    TCAP_End      tc_end;
    TCAP_Invoke   isdr;
    TCAP_Invoke   erbr;
    TCAP_Result   ugla;
    TCAP_Result   saia;
    TCAP_Result   rfsr;
    TCAP_Result   puMsa;
    TCAP_Unidirectional tc_uni;

	
	cap::CAP_AC appCtxt;	
	ITS_ByteArray app_ctxt, buf;
	dlg->GetApplicationContext(buf);
	appCtxt = cap::DecodeApplicationContext(buf);
	switch(appCtxt)
	{

	case cap::CAPV1_gsmSSF_to_gsmSCF_AC :
			{
				app_ctxt = cap::EncodeApplicationContext(cap::CAPV1_gsmSSF_to_gsmSCF_AC);
				CapVersion = cap::CAPV1_VERSION;
			}
			break;
	case cap::CAPV2_gsmSSF_to_gsmSCF_AC :
			{
				app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
				CapVersion = cap::CAPV2_VERSION;
				
			}
			break;
	case cap::CAPV3_cap3_sms_AC :
			{
				app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
			}
			break;
			
	default : 
			{
				APP_TRACE_DEBUG(("SendResponses: Unknown CAP ApplicationContext : %d received in dlg",appCtxt)); 
				app_ctxt = cap::EncodeApplicationContext(cap::UNKNOWN);
			}
			break;
	}
	APP_TRACE_DEBUG(("SendResponses:: Received CAP AppContext : %d",appCtxt)); 
	APP_TRACE_DEBUG(("SendResponses:: Sending CAP AppContext : %d.",appCtxt)); 
	tc_end.SetApplicationContext(app_ctxt);
	tc_cont.SetApplicationContext(app_ctxt);

    
	
	APP_TRACE_DEBUG(("SendResponses: Recv DialogueId = %02x , Recv InvokeId = %02x", dlg->GetDialogueID(), 
			cpt->GetInvokeID()));
	invokeId = cpt->GetInvokeID();

    if (dlg->GetDialogueType() == TCPPT_TC_BEGIN && cpt->GetComponentType() == TCPPT_TC_INVOKE) 
    {
        TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *> (cpt);
        ITS_LONG op;
        ivk->GetOperation(op);
		switch(op)
		{
		case cap::OP_initialDP:
								{
									int ret = ValidateIDPArgs(cpt,CapVersion);
									if(ret != ITS_SUCCESS)
									{
										APP_TRACE_DEBUG(("SendingTCAPErrResp value %d.",ret)); 
										SendTCapErrResp(dlg,cpt,ret);	
										break;
									}
									if(cap::CAPV2_VERSION == CapVersion)
										SendRRBAchContinTcCont(dlg->GetDialogueID(),app_ctxt, false);			
									if(cap::CAPV1_VERSION == CapVersion)
									{
										std::vector<byte> param;
										ivk->GetParameter(param);
										cap_v3::InitialDPArg idp;
										Octets octs(param);
										idp.Decode(octs);
										RecvCdPtyNo = idp.GetCalledPartyNumber();
										SendRRBConnectInTcCont(dlg->GetDialogueID(),app_ctxt,RecvCdPtyNo);
									}
								}
								break;
		case cap::OP_initialDPSMS:	
								{
									
									int ret = ValidateIDPSMSArgs(cpt);
									if(ret != ITS_SUCCESS)
									{
										APP_TRACE_DEBUG(("SendingTCAPErrResp value %d.",ret));							
										SendTCapErrResp(dlg,cpt,ret);
										break;
									}
									else
										SendRRBAchContinTcCont(dlg->GetDialogueID(),app_ctxt,true); 		
								}
								break;
		default : 
				 break;
		}
    }
    else if (dlg->GetDialogueType() == TCPPT_TC_UNI && cpt->GetComponentType() == TCPPT_TC_INVOKE)
    {
        TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *> (cpt);
        ITS_LONG op;
        ivk->GetOperation(op);
    }
    else if (dlg->GetDialogueType() == TCPPT_TC_CONTINUE && cpt->GetComponentType() == TCPPT_TC_RESULT_L)
    {
        // We received a Continue; send an End

        TCAP_Result *res = dynamic_cast<TCAP_Result *> (cpt);
        ITS_LONG op;
        res->GetOperation(op);
		if(op == cap::OP_releaseCall)
        {
            APP_TRACE_DEBUG(("Nothing To do for after receiving Release Call"));
        }
 		
		APP_TRACE_DEBUG(("Received Op_code : %ld", op));
    }
	 
    else if (dlg->GetDialogueType() == TCPPT_TC_CONTINUE && cpt->GetComponentType() == TCPPT_TC_INVOKE)
    {
        TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *> (cpt);
        ITS_LONG op;
        ivk->GetOperation(op);
		switch(op)
		{
		case cap::OP_applyChargingReport:
										{
											APP_TRACE_DEBUG((" SendResponses:: ACR received in TC_Cont/INVOKE, Send ACh")); 			
											BuildACinTcCont(dlg->GetDialogueID(),cpt);
										}
			  							break;
		case cap::OP_eventReportBCSM:
									{
										cap_v3::EventReportBCSMArg erb;
										std::vector<byte> param;
										ivk->GetParameter(param);
										Octets octs(param);
										erb.Decode(octs);
										
										EventTypeBCSM erbType = erb.GetEventTypeBCSM();
										APP_TRACE_DEBUG(("EventType : %ld",erbType.GetValue()));				
										int ret = ValidateERBArgs(cpt);
										if(ITS_SUCCESS != ret)
										{
											SendRelease(ret,dlg->GetDialogueID());
											break;
										}
										if(CapVersion == cap::CAPV1_VERSION)
										{
											if(true == erbType.IsOAnswer())
											{
												APP_TRACE_DEBUG(("CAPV1 ERB received in TC_CONT/INVK, Consume wait for ERB O_Disconnect event."));
											}
											if(true == erbType.IsODisconnect())
											{
												APP_TRACE_DEBUG(("CAPV1 ERB(O_Disconnect) event received in TC_CONT/INVK, Send RELEASE"));
												ret = Release_NormalCalClear;
												SendRelease(ret,dlg->GetDialogueID());
											}
										}
									}
			 						break;
		default : 
				 break;
				
		}
    }
    else if (dlg->GetDialogueType() == TCPPT_TC_END && cpt->GetComponentType() == TCPPT_TC_INVOKE)
    {
        TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *> (cpt);
        ITS_LONG op;
		ITS_ByteArray buf;
        ivk->GetOperation(op);
		switch(op)
		{
		case cap::OP_releaseCall: 
								{
									APP_TRACE_DEBUG(("Release Call Recieved in Tc_End, no need to send response"));
								}
			 					break;
		case cap::OP_releaseSMS: 
								{
									APP_TRACE_DEBUG(("Release SMS Recieved in Tc_End, no need to send response"));
								}
			 					break;
		case cap::OP_eventReportBCSM: 
								{
									APP_TRACE_DEBUG(("ERB Recieved in Tc_End, consume, Wait for ACR[CallActive=False]"));
									cap_v3::EventReportBCSMArg erb;
									std::vector<byte> param;
									ivk->GetParameter(param);
									Octets octs(param);
									erb.Decode(octs);
								
									EventTypeBCSM erbType = erb.GetEventTypeBCSM();
									APP_TRACE_DEBUG(("EventType : %ld",erbType.GetValue())); 
									
								}
			 					break;
		case cap::OP_applyChargingReport: 
			{
				ivk->GetParameter(buf);
				CallResult cr;
				Octets octs(buf);
				cr.Decode(octs);
				CAMEL_CallResult camelcr;
				const std::vector<byte>& vec = cr.GetArray();
				Octets croctets(vec,vec.size());
				camelcr.Decode(croctets);
			
				if(camelcr.ChoiceTimeDurationChargingResult())						
				{
				  
					cap_v3::CAMEL_CallResult::TimeDurationChargingResult tdcr = camelcr.GetChoiceTimeDurationChargingResult();
					APP_TRACE_DEBUG(("Recv ACR in TC_End, CallActive set to %s",tdcr.GetCallActive().GetValue()?"true":"false"));
				}
			}
			break;
		case cap::OP_eventReportSMS:
				{
					cap_v3::EventReportSMSArg erbSMS;
					std::vector<byte> param;
					ivk->GetParameter(param);
					Octets octs(param);
					erbSMS.Decode(octs);
				
					EventTypeSMS erbType = erbSMS.GetEventTypeSMS();
					APP_TRACE_DEBUG(("SMSEventType : %ld",erbType.GetValue())); 
					
				}
			  	break;
		default : 
			 break;			 
		}

    }
       return 0;
}

void ITUTcapMsgs::BuildACinTcCont(ITS_CTXT dlgId, TCAP_Component *in_cpt)
{

ITS_LONG opCode = 0; 
ITS_ByteArray buf; 


ITS_USHORT cptType = in_cpt->GetComponentType();

int ret=0;
ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);


switch(cptType)

{

	case TCPPT_TC_INVOKE :
			{
	
		TCAP_Invoke *tcapIvk = static_cast<TCAP_Invoke*>(in_cpt);
		tcapIvk->GetOperation(opCode);
		tcapIvk->GetParameter(buf);
		switch(opCode)
		{
			case cap::OP_applyChargingReport:
				{
					CallResult cr;
					Octets octs(buf);
					cr.Decode(octs);
					CAMEL_CallResult camelcr;
					const std::vector<byte>& vec = cr.GetArray();
					Octets croctets(vec,vec.size());
                    camelcr.Decode(croctets);

					if(camelcr.ChoiceTimeDurationChargingResult())						
					{
					  
						cap_v3::CAMEL_CallResult::TimeDurationChargingResult tdcr = camelcr.GetChoiceTimeDurationChargingResult();
				        if(tdcr.GetCallActive().GetValue())
						{
							APP_TRACE_DEBUG(("BuildACinTcCont:: CallActive set to %s",tdcr.GetCallActive().GetValue()?"True":"False"));
							TCAP_Component *nwcpt  = NULL;
							BuildACH(nwcpt);
							nwcpt->SetInvokeID(++invokeId);
							TCAP_Continue tc_cont;
							tc_cont.SetApplicationContext(app_ctxt);
							tc_cont.SetDialogueID(dlgId);
							tc_cont.SetOrigAddr(false,oPC,oSN);
							if((ret = TCAP_Component::Send(ISS7_Stack, &tc_cont, nwcpt)) == ITS_SUCCESS) 
							{
								if((ret = TCAP_Dialogue::Send(ISS7_Stack, &tc_cont)) != ITS_SUCCESS) 
								{
									APP_TRACE_CRITICAL(("TransactionManager::sendTcapContinue TCAP Continue could not be sent"));
								} 
								else 
								{
									APP_TRACE_DEBUG(("TCAP Continue with dialogue id %d successfully sent",tc_cont.GetDialogueID()));
								}
						    }
							
							if (nwcpt != NULL)
							{
								delete nwcpt;
								nwcpt = NULL;
							}
			        	}
						else
						{
							APP_TRACE_DEBUG(("BuildACinTcCont:: CallActive set to %s",tdcr.GetCallActive().GetValue()?"TRUE":"FALSE"));
							TCAP_Component *newcmpt = NULL; 
							BuildRelease(newcmpt,NORMAL_CALL_CLEARING);
							newcmpt->SetInvokeID(++invokeId);
							TCAP_End tc_end;
							tc_end.SetApplicationContext(app_ctxt);
							tc_end.SetDialogueID(dlgId);
							if ((ret = TCAP_Component::Send(ISS7_Stack, &tc_end, newcmpt)) == ITS_SUCCESS) 
							{
								if ((ret = TCAP_Dialogue::Send(ISS7_Stack, &tc_end)) != ITS_SUCCESS) 
								{
									APP_TRACE_CRITICAL(("BuildACinTcCont:: TCAP End could not be sent"));
								} 
								else 
								{
										APP_TRACE_DEBUG(("TCAP End with dialogue id %d successfully sent", tc_end.GetDialogueID()));
								}
							}
							else
							{
								APP_TRACE_CRITICAL(("BuildACinTcCont:: TCAP Component could not be sent"));
							}
							if (newcmpt != NULL)
							{
								delete newcmpt;
								newcmpt = NULL;
							}
						}
					}				
					break;
				}
				
	
		}
			break ;
	}
	default : 
				break ;
				
  }


}

void ITUTcapMsgs::SendRRBAchContinTcCont(ITS_CTXT dlgId,ITS_ByteArray& app_ctxt, bool isSMSIdp)
{
	//If isSMSIdp is set then construct RRB/CONT and send TCAP response
	//otherwise build RRB/AC/CONT 
	

	TcapCptList out;
	bool buildFailed = false;
	TCAP_Component *cpt  = NULL;
	BuildRRB(cpt,isSMSIdp);


	if( cpt != NULL )
    {
        cpt->SetInvokeID(++invokeId);
        out.BuildTcapCptList(*cpt);
		APP_TRACE_DEBUG(("SendRRBAchContinTcCont:: RRB Built Successfully appended to the list"));
    }
    else
    {
        APP_TRACE_ERROR(("SendRRBAchContinTcCont:: Failed to build CAP RRB "));
        buildFailed = true;
    }
    if( cpt != NULL )
    {
        delete cpt;
        cpt = NULL;
    }

	if (false == isSMSIdp)
	{
	    APP_TRACE_DEBUG(("SendRRBAchContinTcCont:: Constructing [CAP:ApplyChargingArg]"));
	    BuildACH(cpt);
	    if( cpt != NULL )
	    {
	        cpt->SetInvokeID(++invokeId);
	        out.BuildTcapCptList(*cpt);
	        APP_TRACE_DEBUG(("SendRRBAchContinTcCont:: ACH Built Successfully appended to the list"));
	    }
	    else
	    {
	        APP_TRACE_ERROR(("Failed to build CAP ACH."));
	        buildFailed = true;
	    }
	    if( cpt != NULL )
	    {
	        delete cpt;
	        cpt = NULL;
	    }
	}
    APP_TRACE_DEBUG(("SendRRBAchContinTcCont:: Building [CAP:Continue]"));
    BuildContinue(cpt,isSMSIdp);
    if( cpt != NULL )
    {
        cpt->SetInvokeID(++invokeId);
        out.BuildTcapCptList(*cpt);
		APP_TRACE_DEBUG(("SendRRBAchContinTcCont:: CONT Built Successfully appended to the list"));
    }
    else
    {
        APP_TRACE_ERROR(("Faild to build CAP "));
        buildFailed = true;
    }
    if( cpt != NULL )
    {
        delete cpt;
        cpt = NULL;
    }
    if(true ==  buildFailed )
    {
        // incase if building of any one component failed,clean the out list
        out.ClearTcapCptList();
        buildFailed = false;
    }
	else
		SendMultiCmptInTcCont(out,dlgId,app_ctxt);
	
}

void ITUTcapMsgs::SendRRBConnectInTcCont(ITS_CTXT dlgId,ITS_ByteArray& app_ctxt,cap_v3::CalledPartyNumber& CdPtyNo)
{
	TcapCptList out;
	bool buildFailed = false;
	TCAP_Component *cpt  = NULL;
	BuildRRB(cpt,false);


	if( cpt != NULL )
    {
        cpt->SetInvokeID(++invokeId);
        out.BuildTcapCptList(*cpt);
		APP_TRACE_DEBUG(("SendRRBConnectInTcCont:: RRB Built Successfully appended to the list"));
    }
    else
    {
        APP_TRACE_ERROR(("SendRRBConnectInTcCont:: Failed to build CAP RRB "));
        buildFailed = true;
    }
    if( cpt != NULL )
    {
        delete cpt;
        cpt = NULL;
    }

	
    APP_TRACE_DEBUG(("SendRRBConnectInTcCont:: Constructing CONNECT"));
    BuildConnect(cpt,CdPtyNo);
    if( cpt != NULL )
    {
        cpt->SetInvokeID(++invokeId);
        out.BuildTcapCptList(*cpt);
        APP_TRACE_DEBUG(("SendRRBConnectInTcCont:: CONNECT built successfully appended to the list"));
    }
    else
    {
        APP_TRACE_ERROR(("Failed to build CAP CONNECT."));
        buildFailed = true;
    }
    if( cpt != NULL )
    {
        delete cpt;
        cpt = NULL;
    }
	
    if(true ==  buildFailed )
    {
        out.ClearTcapCptList();
        buildFailed = false;
    }
	else
		SendMultiCmptInTcCont(out,dlgId,app_ctxt);

		

}

void ITUTcapMsgs::SendMultiCmptInTcCont(TcapCptList& cmptLst, ITS_CTXT dlgId, ITS_ByteArray& app_ctxt)
{
	
	TCAP_Continue tc_cont;

	tc_cont.SetApplicationContext(app_ctxt);

	std::list <TCAP_Component> outTcapCpt = cmptLst.GetTcapCptList();
	cmptLst.ClearTcapCptList();

	tc_cont.SetDialogueID(dlgId);

	tc_cont.SetOrigAddr(false,oPC,oSN);

	bool send = true;
	int ret = 0;
	while(!outTcapCpt.empty())
	{
		TCAP_Component tcapCpt = outTcapCpt.front();
		if ((ret = TCAP_Component::Send(ISS7_Stack, &tc_cont, &tcapCpt)) != ITS_SUCCESS) 
		{
			send = false;
			break;
		}
		outTcapCpt.pop_front();
	}
	if(send)
	{
		APP_TRACE_DEBUG(("TCAP Continue with dialogue id %u successfully sent", tc_cont.GetDialogueID()));
		if ((ret = TCAP_Dialogue::Send(ISS7_Stack, &tc_cont)) != ITS_SUCCESS) 
		{
			APP_TRACE_CRITICAL(("SendMultiCmptInTcCont:: TCAP Continue could not be sent"));
		} 
		else 
		{
			APP_TRACE_DEBUG(("TCAP Continue with dialogue id %u successfully sent", tc_cont.GetDialogueID()));
		}
	} 
	else 
	{
		APP_TRACE_CRITICAL(("SendMultiCmptInTcCont:: Unable to send TCAP message."));
	}



}


int ITUTcapMsgs::ValidateIDPArgs(TCAP_Component *cpt, int& version)
{

int ret = 0;

TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *>(cpt);


APP_TRACE_DEBUG(("ValidateIDPArgs entry."));
std::vector<byte> param;
ivk->GetParameter(param);
cap_v3::InitialDPArg idp;
Octets octs(param);
idp.Decode(octs);

if(version >= cap::CAPV2_VERSION)
{
	if(false == idp.OptionCallReferenceNumber())
	{
		APP_TRACE_DEBUG(("Mandatory IE CallRefernceNumber not present in IDP"));
		return cap::ERR_missingParameter;
	}
	if(	false == idp.OptionTimeAndTimezone())
	{
		APP_TRACE_DEBUG(("Mandatory IE TimeAndTimezon not present in IDP"));
		return cap::ERR_missingParameter;

	}
}

if(!(idp.OptionCalledPartyNumber() && idp.OptionCallingPartyNumber()))
{
	APP_TRACE_DEBUG(("Invalid IDP received, both CallingPartyNumber & CalledPartyNumber are not present in IDP"));
	return cap::ERR_unexpectedParameter;
}
else
{
	if(false == idp.OptionCallingPartyNumber())	
	{
		APP_TRACE_DEBUG(("Mandatory IE CallingPartyNumber not present in IDP"));
		return cap::ERR_missingParameter;			
	}

	std::string oCallingPartyNumber;
    const std::vector<byte>& vec = idp.GetCallingPartyNumber().GetArray();
	
	CAPUtils::TBCDToString(&vec[0], vec.size(), oCallingPartyNumber);
	const int minCallingPartyNumberLength = 2;
	const int maxCallingPartyNumberLength = 10;	
#if 0
	if(oCallingPartyNumber.size() < minCallingPartyNumberLength || 
	   oCallingPartyNumber.size() > maxCallingPartyNumberLength)
		{
			APP_TRACE_DEBUG(("CallingPartyNumber value out of Range[2-10]"));
			return  cap::ERR_parameterOutOfRange;
		}
#endif
}

if(false == idp.OptionCallingPartysCategory())
{
	APP_TRACE_DEBUG(("Mandatory IE CallingPartysCategor not present in IDP"));
	return cap::ERR_missingParameter;			

}

if(	false == idp.OptionIMSI())
{
	APP_TRACE_DEBUG(("Mandatory IE IMSI not present in IDP"));
	return cap::ERR_missingParameter;

}
if(idp.OptionEventTypeBCSM())
{
	
	if(cap_v3::EventTypeBCSM::EVENT_TYPE_BCSM_COLLECTED_INFO == idp.GetEventTypeBCSM().GetValue())
	{
		APP_TRACE_DEBUG(("Received IDP-DP2 event"));
	}
	else if(cap_v3::EventTypeBCSM::EVENT_TYPE_BCSM_TERM_ATTEMPT_AUTHORIZED == (idp.GetEventTypeBCSM()).GetValue())
	{
		APP_TRACE_DEBUG(("Received IDP-DP12 event"));	
	}
	else
	{
		APP_TRACE_DEBUG(("Invalid DP event : %ld received in IDP, Neithe MO or MT call. ",(idp.GetEventTypeBCSM()).GetValue()));	
		return cap::ERR_unexpectedParameter;
	}
}
else 
{
	APP_TRACE_DEBUG(("Mandatory IE EventTypeBCSM not present in IDP"));
	return cap::ERR_missingParameter;

}

if(false == idp.OptionMscAddress())
{
	APP_TRACE_DEBUG(("Mandatory IE MscAddress not present in IDP"));
	return cap::ERR_missingParameter;
}

if(false == idp.OptionCalledPartyBCDNumber())
{
	APP_TRACE_DEBUG(("Mandatory IE CalledPartyBCDNumber not present in IDP"));
	return cap::ERR_missingParameter;
	
}


return ret;
}

int ITUTcapMsgs::ValidateERBArgs(TCAP_Component *cpt)
{

	TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *>(cpt);
	cap_v3::EventReportBCSMArg erb;
	std::vector<byte> param;
	ivk->GetParameter(param);
	Octets octs(param);
	erb.Decode(octs);

	cap_v3::EventTypeBCSM evtType = erb.GetEventTypeBCSM();
	string LegIdVal;
	if(true != erb.OptionLegID())
	{
		APP_TRACE_DEBUG(("ValidateERBArgs::Mandatory IE LegId not present in ERB"));
		return cap::ERR_missingParameter;
	}
		cap_v3::ReceivingSideID recvId = erb.GetLegID();
		if(false == recvId.ChoiceReceivingSideID())
		{
			APP_TRACE_DEBUG(("ValidateERBArgs::Mandatory IE ReceivingSide not present in ERB"));
			return cap::ERR_missingParameter;
		}
		cap_v3::LegType legType =  recvId.GetChoiceReceivingSideID();
		const std::vector<byte> legTypeval = legType.GetArray();
		CAPUtils::TBCDToString(&legTypeval[0],legTypeval.size(),LegIdVal,false,true);
		APP_TRACE_DEBUG(("ERB event %ld recv on legId %s",evtType.GetValue(),LegIdVal.c_str()));
		
		
	if(CapVersion == cap::CAPV2_VERSION)
	{
		if(evtType.IsOCalledPartyBusy())
		{
			APP_TRACE_DEBUG(("OCalledPartyBusy evnt : %ld recv on  legId %s, Sending RELEASE",evtType.GetValue(),LegIdVal.c_str()));	
			return Release_UserBusy;	
		}
	    if(evtType.IsONoAnswer())
		{
			APP_TRACE_DEBUG(("ONoAnswer event %ld recv on  legId %s, Sending RELEASE",evtType.GetValue(),LegIdVal.c_str()));	
			return Release_NoAns;	
		}
		if(evtType.IsOAbandon())
		{
			APP_TRACE_DEBUG(("ERB event %ld recv on  legId %s, Sending RELEASE",evtType.GetValue(),LegIdVal.c_str()));	
			return Release_NormalCalClear;
		}
		if(evtType.IsODisconnect())
		{
			if( 0 != strcmp(LegIdVal.c_str(),CallingLegIdStr))
			{
				APP_TRACE_DEBUG(("ERB event %ld recv on  legId %s, Sending TCapError",evtType.GetValue(),LegIdVal.c_str()));	
				return cap::ERR_unknownLegID;
			}
		}
		if(evtType.IsTAbandon() ||
		   evtType.IsTAnswer() ||
		   evtType.IsTBusy() ||
		   evtType.IsTDisconnect() ||
		   evtType.IsTNoAnswer())
		{
			APP_TRACE_DEBUG(("ERB event %ld recv on  Terminationg Events, Sending RELEASE",evtType.GetValue()));	
			return TCAP_error_RetVal;
		}
	}
	return ITS_SUCCESS;
}

int ITUTcapMsgs::ValidateIDPSMSArgs(TCAP_Component *cpt)
{

int ret = 0;

TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *>(cpt);


APP_TRACE_DEBUG(("ValidateIDPSMSArgs entry."));
std::vector<byte> param;
ivk->GetParameter(param);
cap_v3::InitialDPSMSArg idpSMS;
Octets octs(param);
idpSMS.Decode(octs);
idpSMS.Print(cout);

if(false == idpSMS.OptionCallingPartyNumber()) 
{
	APP_TRACE_DEBUG(("ValidateIDPSMSArgs::Mandatory IE CallingPartyNumber not present in IDPSMS"));
	return cap::ERR_missingParameter;			
}

if(	false == idpSMS.OptionIMSI())
{
	APP_TRACE_DEBUG(("ValidateIDPSMSArgs::Mandatory IE IMSI not present in IDP"));
	return cap::ERR_missingParameter;

}

if(	false == idpSMS.OptionTPShortMessageSubmissionSpecificInfo())
{
	APP_TRACE_DEBUG(("ValidateIDPSMSArgs::Mandatory IE TPShortMessageSubmissionSpecificInfo not present in IDP"));
	return cap::ERR_missingParameter;

}

if(	false == idpSMS.OptionTPProtocolIdentifier())
{
	APP_TRACE_DEBUG(("ValidateIDPSMSArgs::Mandatory IE TPProtocolIdentifier not present in IDP"));
	return cap::ERR_missingParameter;

}

if(idpSMS.OptionEventTypeSMS())
{
	if(cap_v3::EventTypeSMS::EVENT_TYPE_SMS_SMS_COLLECTED_INFO == idpSMS.GetEventTypeSMS().GetValue())
	{
		APP_TRACE_DEBUG(("Received IDP-SMS event"));
	}
	else
	{
		APP_TRACE_DEBUG(("Invalid SMS-DP event : %ld received in IDP, Sending REALEASE. ",(idpSMS.GetEventTypeSMS()).GetValue()));	
		return cap::ERR_unexpectedParameter;
	}
}
else 
{
	APP_TRACE_DEBUG(("Mandatory IE EventTypeSMS not present in IDP"));
	return cap::ERR_missingParameter;

}
if(	false == idpSMS.OptionTimeAndTimezone())
{
	APP_TRACE_DEBUG(("Mandatory IE TimeAndTimezon not present in IDP"));
	return cap::ERR_missingParameter;

}

if(false == idpSMS.OptionSMSCAddress())
{
	APP_TRACE_DEBUG(("Mandatory IE SMSCAddress not present in IDP"));
	return cap::ERR_missingParameter;
}

if(false == idpSMS.OptionMscAddress())
{
	APP_TRACE_DEBUG(("Mandatory IE MscAddress not present in IDP"));
	return cap::ERR_missingParameter;
}

if(false == idpSMS.OptionSmsReferenceNumber())
{
	APP_TRACE_DEBUG(("Mandatory IE SMSReferenceNumber not present in IDP"));
	return cap::ERR_missingParameter;
}

if(false == idpSMS.OptionDestinationSubscriberNumber())
{
	APP_TRACE_DEBUG(("Mandatory IE DestinationSubscriberNumber not present in IDP"));
	return cap::ERR_missingParameter;
}


return ret;
}

void ITUTcapMsgs::SendTCapErrResp(TCAP_Dialogue *dlg, TCAP_Component *cmpt, int& capErrVal)
{

TCAP_End *outTcapEndDlg = new TCAP_End();

TCAP_Error *terr = new TCAP_Error();
terr->SetInvokeID(cmpt->GetInvokeID());
terr->SetError((ITS_OCTET)capErrVal);

ITS_ByteArray buf;
dlg->GetApplicationContext(buf);
outTcapEndDlg->SetDialogueID(dlg->GetDialogueID());
outTcapEndDlg->SetApplicationContext(buf);

ITS_OCTET flags = 0x00;
ITS_OCTET slsK  = 0x00;
ITS_OCTET prio  = 0x00;
ITS_OCTET nind  = 0x00;

dlg->GetQualityOfService(flags,slsK,prio,nind);
outTcapEndDlg->SetQualityOfService(flags, slsK, prio, nind);
int ret;
if ((ret = TCAP_Component::Send(ISS7_Stack, (TCAP_Dialogue *)outTcapEndDlg, (TCAP_Component *)terr)) == ITS_SUCCESS) 
{
	if ((ret = TCAP_Dialogue::Send(ISS7_Stack, (TCAP_Dialogue *)outTcapEndDlg)) != ITS_SUCCESS) 
	{
		APP_TRACE_CRITICAL(("SendTcapErrResp TCAP Error Last sent successfully. But TCAP End could not be sent"));
	} 
	else
	{

	APP_TRACE_DEBUG(("TCAP End with dialogue id %d successfully sent", outTcapEndDlg->GetDialogueID()));
	}
} 
else
{
	APP_TRACE_CRITICAL(("SendTcapErrResp::SendTcapErrResp Unable to send TCAP message"));
}

if (terr != NULL) 
{
	delete terr;
	terr = NULL;
}

if (outTcapEndDlg != NULL)
{
	delete outTcapEndDlg;
	outTcapEndDlg = NULL;
}

	
}

void ITUTcapMsgs::SendRelease(int& relValue,ITS_CTXT dialogueID)
{
	switch(relValue)
	{
	 case cap::ERR_missingParameter : 
	 case TCAP_error_RetVal :	
	 case Release_NormalCalClear: 
							{
								TCAP_Component *newcmpt = NULL; 
								BuildRelease(newcmpt,NORMAL_CALL_CLEARING);
								newcmpt->SetInvokeID(++invokeId);
								SendTcEnd(newcmpt,dialogueID);
								break;
							}
							
	 case Release_UserBusy :
							 {
								 TCAP_Component *newcmpt = NULL; 
								 BuildRelease(newcmpt,USER_BUSY);
								 newcmpt->SetInvokeID(++invokeId);
								 SendTcEnd(newcmpt,dialogueID);
								 break;
							 }
	 case Release_NoAns :
						 {
							 TCAP_Component *newcmpt = NULL; 
							 BuildRelease(newcmpt,USER_NOANS);
							 newcmpt->SetInvokeID(++invokeId);
							 SendTcEnd(newcmpt,dialogueID);
							 break;
						 }
		
	 case cap::ERR_unknownLegID : 
							{
								TCAP_Component *newcmpt = NULL; 
								BuildRelease(newcmpt,NORMAL_UNSPECIFIED);
								newcmpt->SetInvokeID(++invokeId);
								SendTcEnd(newcmpt,dialogueID);
								break;
							}
	 default : 
			  {
				APP_TRACE_DEBUG((" SendResponses:: ERB received in TC_CONT/INVK, Consume wait for ACR."));	
				break;
			  }
	 
	}

}

void ITUTcapMsgs::SendTcEnd(TCAP_Component *&cpt, ITS_CTXT dialogueID)
{
	TCAP_End tc_end;
	ITS_ByteArray app_ctxt;
	int ret = ITS_SUCCESS;
	if(CapVersion == cap::CAPV1_VERSION)
		app_ctxt = cap::EncodeApplicationContext(cap::CAPV1_gsmSSF_to_gsmSCF_AC);
	else
		app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
	tc_end.SetApplicationContext(app_ctxt);
	tc_end.SetDialogueID(dialogueID);
	if ((ret = TCAP_Component::Send(ISS7_Stack, &tc_end, cpt)) == ITS_SUCCESS) 
	{
		if ((ret = TCAP_Dialogue::Send(ISS7_Stack, &tc_end)) != ITS_SUCCESS) 
		{
			APP_TRACE_CRITICAL(("SendResponses:: TCAP End could not be sent"));
		} 
		else 
		{
				APP_TRACE_DEBUG(("TCAP End with dialogue id %d successfully sent", tc_end.GetDialogueID()));
		}
	}
	else
	{
		APP_TRACE_CRITICAL(("SendResponses:: TCAP Component could not be sent"));
	}
	if (cpt != NULL)
	{
		delete cpt;
		cpt = NULL;
	}

}

//#include "app_map_msgs.cpp"

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
    //cout << endl;
    //cout << "--------------------------------------------------" << endl;
    //cout << "Printing ASN value before encoding..." << endl;

    if (p == NULL)
    {
        return;
    }

    //cout << endl << *p << endl;

    Octets* tmpOctets;

    try
    {
        tmpOctets = p->Encode();
    }
    catch (AsnEncodeError& exc)
    {
        //cout << endl;
        //cout << "--------------------------------------------------" << endl;
        //cout << "Exception during encoding phase..." << endl;
        //cout << exc.GetDescription() << endl;
        //cout << "Exit test..." << endl;
    }

    //cout << endl;
    //cout << "--------------------------------------------------" << endl;
    *octets = tmpOctets;
}


#endif
