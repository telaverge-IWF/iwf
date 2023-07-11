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
 * LOG: Revision 1.1.2.5.2.3.10.1  2014/09/22 04:58:54  jkchaitanya
 * LOG: changes for enhancement bugs 5045, 5053
 * LOG:
 * LOG: Revision 1.1.2.5.2.3  2013/12/27 13:53:04  jkchaitanya
 * LOG: changes for the bug 2301
 * LOG:
 * LOG: Revision 1.1.2.5.2.2  2013/12/24 06:52:45  jkchaitanya
 * LOG: changes for the bug 2660
 * LOG:
 * LOG: Revision 1.1.2.5.2.1  2013/12/06 13:20:43  jsarvesh
 * LOG: changes to handle reject component
 * LOG:
 * LOG: Revision 1.1.2.5  2013/09/27 06:00:12  jkchaitanya
 * LOG: changes in conditions to send cap response if MSC SSN is 146
 * LOG:
 * LOG: Revision 1.1.2.4  2013/08/30 07:13:32  jkchaitanya
 * LOG: changes for AddressIndicator for bug 1165 in capsim directory
 * LOG:
 * LOG: Revision 1.1.2.3  2013/08/29 08:46:44  jkchaitanya
 * LOG: changes after merging sarvesh changes for dividing SendMapResponse and SendCapResponse from map to capsim directory
 * LOG:
 * LOG: Revision 1.1.2.2  2013/08/28 11:33:03  jkchaitanya
 * LOG: changes for sms callflows in capsim for automation
 * LOG:
 * LOG: Revision 1.1.2.1  2013/08/21 12:14:16  jkchaitanya
 * LOG: sub directories in capsim
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
#ident "$Id: app_itu_msgs.cpp,v 1.1.2.5.2.3.10.1 2014/09/22 04:58:54 jkchaitanya Exp $"

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
extern TransportState transStateInfo;
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
ITS_CTXT did = 0;

ITS_UINT dPC=0;
ITS_UINT oPC=0;
ITS_UINT sSN=149;
ITS_UINT oSN=6;
//ITS_UINT sSN=6;
//ITS_UINT oSN=149;

string gRecvImsi;
static bool gInitGlobals = false;
static ITUTcapMsgs * ituTcapMsgs = NULL;
int GetReqChoice();
ITS_ULONG GetMapOpCodeForChoice(ITS_INT choice);
int InvokeID = 60;
ITS_BOOLEAN  LastCptRcvd = ITS_FALSE;
bool IsReleaseIfdurationExceededisSet = false;
int NumOfERBandACHinTc_Cont = 0;
bool sendERBandACRinTcEnd = false;
extern void BuildImsiList();
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
#if 0
    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];
#endif
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
                if((sSN == 149 && oSN == 6) || (sSN == 6 && oSN == 149))
                {    
                    SendMAPResponse(its_dlg, &its_cpt, work);
                }    
                else if((sSN == 146 && oSN == 149) || (sSN == 146 && oSN == 146))
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
            if(its_dlg && cpt_type_recvd != TCAP_L_CANCEL_TYPE && cpt_type_recvd != TCAP_L_REJECT_TYPE && LastCptRcvd)
            {
                delete its_dlg;
                its_dlg = NULL;
                LastCptRcvd = ITS_FALSE;
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

                    if((sSN == 149 && oSN == 6) || (sSN == 6 && oSN == 149))
                    {
                        SendMAPResponse(its_dlg, &its_cpt, work);
                    }
                    else if((sSN == 146 && oSN == 149) || (sSN == 146 && oSN == 146))
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

static void SetReceivedImsi(const map_v13::IMSI &usrid)
{
    const std::vector<byte> &array = usrid.GetArray();
    char *fromdg = 0;

    TCAPUtils::ConvertOctsToString(&fromdg, (ITS_OCTET *)&array[0], (int)array.size(), true);
    gRecvImsi = fromdg;
    free(fromdg);
    fromdg = 0;
}

int ITUTcapMsgs::SendMAPResponse(TCAP_Dialogue* dlg, 
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

   APP_TRACE_DEBUG(("Inside SendMAPResponse() function."));

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
               }
               else if (op == map_common::OP_sendAuthenticationInfo)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::SendAuthenticationInfoArg saiarg;
                   Octets octs(param);
                   saiarg.Decode(octs);
                   saiarg.Print(cout);
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
               else if (op == map_common::OP_insertSubscriberData)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::InsertSubscriberDataArg isda;
                   Octets octs(param);
                   isda.Decode(octs);
                   isda.Print(cout);
               }
               else if (op == map_common::OP_deleteSubscriberData)
               {    
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::DeleteSubscriberDataArg dsda;
                   Octets octs(param);
                   dsda.Decode(octs);
                   dsda.Print(cout);
               }
               else if (op == map_common::OP_cancelLocation)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::CancelLocationArg cla;
                   Octets octs(param);
                   cla.Decode(octs);
                   cla.Print(cout);
               }
               else if (op == map_common::OP_provideSubscriberInfo)
               {    
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::ProvideSubscriberInfoArg psia;
                   Octets octs(param);
                   psia.Decode(octs);
                   psia.Print(cout);
               }    
               else if (op == map_common::OP_reset)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::ResetArg rsa;
                   Octets octs(param);
                   rsa.Decode(octs);
                   rsa.Print(cout);
               }
               
           }
           break;

           case TCPPT_TC_RESULT_L:
           case TCPPT_TC_RESULT_NL:
           {
               TCAP_Result *resl = dynamic_cast<TCAP_Result *>(*cpt);
               resl->GetOperation(op); 

               //(*cpt)->Print(cout);
               if (op == map_common::OP_insertSubscriberData)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::InsertSubscriberDataRes isres;
                   Octets octs(param);
                   isres.Decode(octs);
                   isres.Print(cout);
               }
               else if (op == map_common::OP_deleteSubscriberData)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::DeleteSubscriberDataRes dsres;
                   Octets octs(param);
                   dsres.Decode(octs);
                   dsres.Print(cout);
               }
               else if (op == map_common::OP_cancelLocation)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::CancelLocationRes clRes;
                   Octets octs(param);
                   clRes.Decode(octs);
                   clRes.Print(cout);
               }
               else if (op == map_common::OP_updateGprsLocation)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::UpdateGprsLocationRes uglres;
                   Octets octs(param);
//                   uglres.Decode(octs);
//                   uglres.Print(cout);
               } 
               else if (op == map_common::OP_sendAuthenticationInfo)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::SendAuthenticationInfoRes saires;
                   Octets octs(param);
//                   saires.Decode(octs);
//                   saires.Print(cout);
               }
               else if (op == map_common::OP_purgeMS)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::PurgeMS_Res pmsres;
                   Octets octs(param);
//                   pmsres.Decode(octs);
//                   pmsres.Print(cout);
               } 
               else if (op == map_common::OP_provideSubscriberInfo)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::ProvideSubscriberInfoRes psires;
                   Octets octs(param);
                   psires.Decode(octs);
                   psires.Print(cout);
               }
               else if (op == map_common::OP_deactivateTraceMode)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::DeactivateTraceModeRes dtmr;
                   Octets octs(param);
                   dtmr.Decode(octs);
                   dtmr.Print(cout);
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
   SendResponses(dlg, *cpt);

   return ret;
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
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   cap_v3::RequestReportBCSMEventArg rrb;
                   Octets octs(param);
                   rrb.Decode(octs);
                   rrb.Print(cout);
               }
               else if (op == cap::OP_applyCharging)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   cap_v3::ApplyChargingArg ach;
                   Octets octs(param);
                   ach.Decode(octs);
                   ach.Print(cout);
                   cap_v3::AChBillingChargingCharacteristics acc = ach.GetAChBillingChargingCharacteristics();
                   const std::vector<byte>& vec = acc.GetArray();
                   Octets camelach(vec,vec.size());
                   CAMEL_AChBillingChargingCharacteristics camelACH;
                   camelACH.Decode(camelach);
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
                    //NOTE: Nothing to do as this is just an indication from IWF to continue
               }
               else if (op == cap::OP_releaseCall)
               {
                    //NOTE: Nothing to do as this is just a release call
                    std::vector<byte> param;
                    ivk->GetParameter(param);
                    Octets octs(param);
                    cap_v3::Cause cau;
                    cau.Decode(octs);
                    cau.Print(cout);
                    string val = MAPUtils::VectorToString(cau.GetArray());
                    if(strcmp(val.c_str(),"BS"))
                    {
                        APP_TRACE_DEBUG(("Release Cause Matches with IWF value"));
                    }
               }
               else if (op == cap::OP_requestReportSMSEvent)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   cap_v3::RequestReportSMSEventArg rrsms;
                   Octets octs(param);
                   rrsms.Decode(octs);
                   rrsms.Print(cout);
               }
               else if (op == cap::OP_continueSMS)
               {
                   //NOTE: Nothing to do as this is just an indication from IWF to continue
               }
               else if (op == cap::OP_releaseSMS)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   cap_v3::ReleaseSMSArg rsmsa;
                   Octets octs(param);
                   rsmsa.Decode(octs);
                   rsmsa.Print(cout);
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

           case TCPPT_TC_L_REJECT:
           {
                TCAP_Reject *rejc = dynamic_cast<TCAP_Reject *>(*cpt);
                ITS_OCTET family, code;
                rejc->GetProblem(family, code);
                cout  << "Problem Type: " << (int)family << endl;
                cout  << "Problem Code: " << (int)code << endl;
                APP_TRACE_DEBUG(("Reject Component Received"));
                (*cpt)->Print(cout);
                //NOTE: Reject Component is received, MSC neednot send any response so just return the function.
                return ret;
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
    bool isNull;

    char buf[256];
    Json::Value l_jsonRootconf1 = parseCapConfig();

    c_jsonRoot = &l_jsonRootconf1;
    c_jsonRoot1 = &(*c_jsonRoot)["cap_v3"];

    Json::Value* cfg2 = &(*c_jsonRoot1)["cap_tool_configuration"];

    isNull = (*cfg2)["OPC"]["Value"].isNull();
    if(!isNull)
    {
        oPC = (*cfg2)["OPC"]["Value"].asInt();
    }
    else
    {
        oPC = 4114;
    }
    cpa_itu.SetPointCode(oPC);

    isNull = (*cfg2)["DPC"]["Value"].isNull();
    if(!isNull)
    {
        dPC = (*cfg2)["DPC"]["Value"].asInt();
    }
    else
    {
        dPC = 2057;
    }
    cdp_itu.SetPointCode(dPC);

    isNull = (*cfg2)["Destination_SSN"]["Value"].isNull();
    if(!isNull)
    {
        sSN = (*cfg2)["Destination_SSN"]["Value"].asInt();
    }
    else
    {
        sSN = 146;
    }
    cdp_itu.SetSSN(sSN);

    isNull = (*cfg2)["Source_SSN"]["Value"].isNull();
    if(!isNull)
    {
        oSN = (*cfg2)["Source_SSN"]["Value"].asInt();
    }
    else
    {
        oSN = 8;
    }
    cpa_itu.SetSSN(oSN);

    if(itstest::apc == 0) {
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

    isNull = (*cfg2)["InternationalRouting"]["Value"].isNull();
    if(!isNull)
    {
        networkInd = (*cfg2)["InternationalRouting"]["Value"].asInt();
    }
    else
    {
        networkInd = 0;
    }

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
    if (opcode >= MAP_V13_UPDATE_GPRS_LOC) {
        // Set Application Context for MAP
        return BuildMapMsg((MAP_OPCODE)opcode);
    }
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

         if(opCode != MAP_V13_RESET_ARG && opCode != MAP_V13_READY_FOR_SM_ARG)
         {
             cout << "Invalid Choice..!! Send either ResetArg or Ready_For_SMArg" << endl;
             return;
         }

         Octets *encOctets;
         AsnObject *obj = BuildProtocolMsg(opCode);

         if (opCode >= MAP_V13_UPDATE_GPRS_LOC)
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

        if(opCode == map_common::OP_reset)
         {
             std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::resetContext_v2);
             uniDlg.SetApplicationContext(&acEnc[0], acEnc.size());
         }
         else if(opCode == map_common::OP_readyForSM)
         {
             std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::mwdMngtContext_v3);
             uniDlg.SetApplicationContext(&acEnc[0], acEnc.size());
         }


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
    int op = -1;
    
    if(optionfromserver > 0 && optionfromserver <= 12)
    {
        //NOTE: For Voice CallFlows
        return OP_initialDP;
    }
    else if(optionfromserver > 12 && optionfromserver <=15)
    {
        //NOTE: For SMS CallFlows
        return OP_initialDPSMS;
    }
    else
    {
        return op;
    }
}

ITS_ULONG GetMapOpCodeForChoice(ITS_INT choice)
{
    switch (choice)
    {
        case MAP_V13_UPDATE_GPRS_LOC:
            return map_common::OP_updateGprsLocation;

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

        case MAP_V13_TRACE_ACTIVATE_MODE_ARG:
            return map_common::OP_activateTraceMode;

        case MAP_V13_TRACE_DEACTIVATE_MODE_ARG:
            return map_common::OP_deactivateTraceMode;

        case MAP_V13_RESET_ARG:
            return map_common::OP_reset;

        case MAP_V13_PURGE_MS_ARG:
            return map_common::OP_purgeMS;

        case MAP_V13_SEND_AUTH_INFO_ARG:
            return map_common::OP_sendAuthenticationInfo;

        case MAP_V13_READY_FOR_SM_ARG:
            return map_common::OP_readyForSM;

        default:
            break;
    }
    return 0;
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
    bool isNull;
    Json::Value l_jsonRootconf3 = parseCapConfig();

    c_jsonRoot = &l_jsonRootconf3;
    c_jsonRoot1 = &(*c_jsonRoot)["cap_v3"];

    Json::Value* cfg3 = &(*c_jsonRoot1)["cap_tool_configuration"];

    TCAP_Begin     beginDlg;
    begin = &beginDlg;
    TCAP_AllocateDialogueId(ISS7_Stack, &did);

    begin->SetDialogueID(did);
    begin->SetOrigAddr(cpa_itu);
    begin->SetOPC(oPC);
    begin->Print(cout);
    cdp_itu.SetRouteByPCSSN(itstest::routeType);


    begin->SetDestAddr(cdp_itu);
    begin->SetDPC(dPC);
    begin->Print(cout);
    isNull = (*cfg3)["SCCP_PROTOCOL_CLASS"]["Value"].isNull();
    if(!isNull)
    {
        pcls = (*cfg3)["SCCP_PROTOCOL_CLASS"]["Value"].asInt();
    }
    else
    {
        pcls = 1;
    }
    if(pcls!=1)
      pcls=0;

    ITS_UINT compdialogSelection=0;
    isNull = (*cfg3)["component_and_DialogSelection"]["Value"].isNull();
    if(!isNull)
    {
        compdialogSelection = (*cfg3)["component_and_DialogSelection"]["Value"].asInt();
    }
    else
    {
        compdialogSelection = 1;
    }

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

    isNull = (*cfg3)["UserInfo"]["Value"].isNull();
    if(!isNull)
    {
        hasUserInfo = (*cfg3)["UserInfo"]["Value"].asInt();
    }
    else
    {
        hasUserInfo = 1;
    }

    if (hasUserInfo)
    {
         begin->SetUserInfo(itstest::USER_INFO, 25);
    }

    dlg = begin;

    isNull = (*cfg3)["Num_Of_Invokes"]["Value"].isNull();
    if(!isNull)
    {
        invokeCount = (*cfg3)["Num_Of_Invokes"]["Value"].asInt(); 
    }
    else
    {
        invokeCount = 1;
    }
    for (int i = 1; i <= invokeCount; i++)
    {

        TCAP_Invoke    invoke;
        isNull = (*cfg3)["Invoke_Id"]["Value"].isNull();
        if(!isNull)
        {
            invoke.SetInvokeID((*cfg3)["Invoke_Id"]["Value"].asInt());
        }
        else
        {
            invoke.SetInvokeID(1);
        }
        isNull = (*cfg3)["Operation_Class"]["Value"].isNull();
        if(!isNull)
        {
            invoke.SetClass((*cfg3)["Operation_Class"]["Value"].asInt());
        }
        else
        {
            invoke.SetClass(3);
        }
        int opCode= -1;
        opCode = GetReqChoice();

        if( opCode == -1 || opCode == MAP_V13_RESET_ARG || opCode == MAP_V13_READY_FOR_SM_ARG)
        {
            cout << "Invalid Choice..!! Cannnot Send ResetArg/ReadyForSMArg as TC_Begin ..!!" << endl;
            cout << "Try Sending ResetArg/Ready_For_SMArg as : \"TC_Uni.\" ..!!" << endl;
            return;
        }
        Octets *encOctets;
        AsnObject *obj = BuildProtocolMsg(opCode);
        if (opCode >= MAP_V13_UPDATE_GPRS_LOC)
        {
            opCode = GetMapOpCodeForChoice(opCode);
        }

        if(opCode == map_common::OP_updateGprsLocation)
        {
            std::vector<byte> acenc = map_common::EncodeApplicationContext(map_common::gprsLocationUpdateContext_v3);
            begin->SetApplicationContext(&acenc[0], acenc.size());
        }
        else if (opCode == map_common::OP_provideSubscriberInfo)
        {
            std::vector<byte> acenc = map_common::EncodeApplicationContext(map_common::subscriberInfoEnquiryContext_v3);
            begin->SetApplicationContext(&acenc[0], acenc.size());
        }
        else if (opCode == map_common::OP_insertSubscriberData || opCode == map_common::OP_deleteSubscriberData)
        {
            std::vector<byte> acenc = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
            begin->SetApplicationContext(&acenc[0], acenc.size());
        }
        else if(opCode == map_common::OP_activateTraceMode || opCode == map_common::OP_deactivateTraceMode)
        {
            std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::tracingContext_v3);
            begin->SetApplicationContext(&acEnc[0], acEnc.size());
        }
        else if(opCode == map_common::OP_cancelLocation)
        {
            std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::locationCancellationContext_v3);
            begin->SetApplicationContext(&acEnc[0], acEnc.size());
        }
        else if(opCode == map_common::OP_reset)
        {
            std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::resetContext_v2);
            begin->SetApplicationContext(&acEnc[0], acEnc.size());
        }
        else if(opCode == map_common::OP_purgeMS)
        {
            std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::msPurgingContext_v3);
            begin->SetApplicationContext(&acEnc[0], acEnc.size());
        }
        else if(opCode == map_common::OP_sendAuthenticationInfo)
        {
            std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::infoRetrievalContext_v3);
            begin->SetApplicationContext(&acEnc[0], acEnc.size());
        }
        else if(opCode == map_common::OP_readyForSM)
        {
            std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::mwdMngtContext_v3);
            begin->SetApplicationContext(&acEnc[0], acEnc.size());
        }
        else if(opCode == cap::OP_initialDP || opCode == cap::OP_eventReportBCSM || opCode == cap::OP_applyChargingReport)
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

void
ITUTcapMsgs::SendBeginDlg(ITS_HANDLE hdl, int inst, ITS_BOOLEAN addR, int opCode)
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


   //APP_TRACE_DEBUG(("Send: DialogueId = %02x , DialogueType = %02x", dlgid, 
   //        begin.GetDialogueType()));

   ivk.SetInvokeID(GetInvokeID());
   ivk.SetTimeOut(timeout);

   ivk.SetClass(3);

   Octets *encOctets;
   AsnObject *obj = NULL;
   if(opCode == MAP_V13_SEND_AUTH_INFO_ARG)
       obj = SAIArg;
   else if(opCode == MAP_V13_UPDATE_GPRS_LOC)
       obj = UGLArg;
   else if(opCode == MAP_V13_PURGE_MS_ARG)
       obj = PURGEArg;
   
   //AsnObject *obj = BuildProtocolMsg(opCode);
   EncodeMsg(obj, &encOctets);

   if (obj == NULL)
   {
       cout << "\n **** Object is Null ****" << endl;
   }
   //cout << obj;

   if (opCode >= MAP_V13_UPDATE_GPRS_LOC)
   {
       opCode = GetMapOpCodeForChoice(opCode);
   }

   ivk.SetOperation(opCode);
 
   //APP_TRACE_DEBUG(("Invokeid = %02x", ivk.GetInvokeID()));

   //srand(time(NULL));

    ivk.SetParameter(encOctets->GetArray());
    
    if(opCode == map_common::OP_updateGprsLocation)
    {
        std::vector<byte> acenc = map_common::EncodeApplicationContext(map_common::gprsLocationUpdateContext_v3);
        begin.SetApplicationContext(&acenc[0], acenc.size());
    }
    else if (opCode == map_common::OP_provideSubscriberInfo)
    {
        std::vector<byte> acenc = map_common::EncodeApplicationContext(map_common::subscriberInfoEnquiryContext_v3);
        begin.SetApplicationContext(&acenc[0], acenc.size());
    }
    else if (opCode == map_common::OP_insertSubscriberData || opCode == map_common::OP_deleteSubscriberData)
    {
        std::vector<byte> acenc = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
        begin.SetApplicationContext(&acenc[0], acenc.size());
    }
    else if(opCode == map_common::OP_activateTraceMode || opCode == map_common::OP_deactivateTraceMode)
    {
        std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::tracingContext_v3);
        begin.SetApplicationContext(&acEnc[0], acEnc.size());
    }
    else if(opCode == map_common::OP_cancelLocation)
    {
        std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::locationCancellationContext_v3);
        begin.SetApplicationContext(&acEnc[0], acEnc.size());
    }
    else if(opCode == map_common::OP_reset)
    {
        std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::resetContext_v2);
        begin.SetApplicationContext(&acEnc[0], acEnc.size());
    }
    else if(opCode == map_common::OP_purgeMS)
    {
        std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::msPurgingContext_v3);
        begin.SetApplicationContext(&acEnc[0], acEnc.size());
    }
    else if(opCode == map_common::OP_sendAuthenticationInfo)
    {
        std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::infoRetrievalContext_v3);
        begin.SetApplicationContext(&acEnc[0], acEnc.size());
    }
    else if(opCode == map_common::OP_readyForSM)
    {
        std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::mwdMngtContext_v3);
        begin.SetApplicationContext(&acEnc[0], acEnc.size());
    }
    else if(opCode == cap::OP_initialDP || opCode == cap::OP_eventReportBCSM || opCode == cap::OP_applyChargingReport)
    {
        std::vector<byte> acenc = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
        begin.SetApplicationContext(&acenc[0], acenc.size());
    }
    else if(opCode == cap::OP_eventReportSMS || opCode == cap::OP_initialDPSMS)
    {
        std::vector<byte> acenc = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
        begin.SetApplicationContext(&acenc[0], acenc.size());
    }

    ret = TCAP_Component::Send(ISS7_Stack, &begin, &ivk);

    if(ret == ITS_SUCCESS)
    {
        ret = TCAP_Dialogue::Send(ISS7_Stack, &begin);
        if(ret == ITS_SUCCESS)
        {
            stats.UpdateSendStats(begin.GetDialogueType());
            stats.UpdateSendStats(ivk.GetComponentType());
#if 0
            APP_TRACE_DEBUG(("Send Dialogue Type = %02x Dlgid = %d", 
                        begin.GetDialogueType(), dlgid));
            APP_TRACE_DEBUG(("TCAP Cpt and DlgType Send success."));
#endif
        }
    }

    if(encOctets != NULL)
    {
        delete encOctets;
        encOctets = NULL;
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

void ITUTcapMsgs::BuildTCAPErrorCpt(TCAP_Dialogue *dlg, ITS_OCTET invokeId, TCAP_Error **tcapErr,  ITS_OCTET errVal)
{

    APP_TRACE_DEBUG(("Inside ITUTcapMsgs::BuildTCAPErrorCpt"));
    Octets *enc2 = 0;
    bool isNull;
    bool isAVPEnabled;
    TCAP_Error *terr = new TCAP_Error();


    terr->SetInvokeID(invokeId);

    terr->SetError(errVal);

    switch(errVal)
    {
        case map_common::ERR_unknownSubscriber:
            {
                Json::Value* cfg = &(*m_jsonRoot1)["UnknownSubscriberParam"];
                map_v13::UnknownSubscriberParam *unkwnSubs = new map_v13::UnknownSubscriberParam();
                isNull = (*cfg)["UnknownSubscriberDiagnostic"]["Value"].isNull();
                isAVPEnabled = (*cfg)["UnknownSubscriberDiagnostic"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::UnknownSubscriberDiagnostic unknsubdia((*cfg)["UnknownSubscriberDiagnostic"]["Value"].asInt());
                    unkwnSubs->SetUnknownSubscriberDiagnostic(unknsubdia);
                }
                EncodeMsg(unkwnSubs, &enc2);
                terr->SetParameter(enc2->GetArray());
                break;
            }
        case map_common::ERR_roamingNotAllowed:
            {
                Json::Value* cfg = &(*m_jsonRoot1)["RoamingNotAllowedParam"];
                map_v13::RoamingNotAllowedParam *roamNot = new map_v13::RoamingNotAllowedParam();
                isNull = (*cfg)["RoamingNotAllowedCause"]["Value"].isNull();
                if(!isNull)
                {
                    map_v13::RoamingNotAllowedCause rnac((*cfg)["RoamingNotAllowedCause"]["Value"].asInt());
                    roamNot->SetRoamingNotAllowedCause(rnac);
                }

                isNull = (*cfg)["AdditionalRoamingNotAllowedCause"]["Value"].isNull();
                isAVPEnabled = (*cfg)["AdditionalRoamingNotAllowedCause"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::AdditionalRoamingNotAllowedCause arnac((*cfg)["AdditionalRoamingNotAllowedCause"]["Value"].asInt());
                    roamNot->SetAdditionalRoamingNotAllowedCause(arnac);
                }
                EncodeMsg(roamNot, &enc2);
                terr->SetParameter(enc2->GetArray());
                break;
            }
        case map_common::ERR_dataMissing:
            {
                map_v13::DataMissingParam *datamiss = new map_v13::DataMissingParam();
                EncodeMsg(datamiss, &enc2);
                terr->SetParameter(enc2->GetArray());
            }
        case map_common::ERR_unexpectedDataValue:
            {
                Json::Value* cfg = &(*m_jsonRoot1)["UnexpectedDataParam"];
                map_v13::UnexpectedDataParam *udp = new map_v13::UnexpectedDataParam();

                isAVPEnabled = (*cfg)["unexpectedSubscriber"]["Enabled"].asBool();
                isNull = (*cfg)["unexpectedSubscriber"]["Enabled"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::UnexpectedDataParam::UnexpectedSubscriber us;
                    udp->SetUnexpectedSubscriber(us);
                }
                EncodeMsg(udp, &enc2);
                terr->SetParameter(enc2->GetArray());
            }
        case map_common::ERR_facilityNotSupported:
            {
                Json::Value* cfg = &(*m_jsonRoot1)["FacilityNotSupParam"];
                map_v13::FacilityNotSupParam *fns = new map_v13::FacilityNotSupParam();

                isAVPEnabled = (*cfg)["shapeOfLocationEstimateNotSupported"]["Enabled"].asBool();
                isNull = (*cfg)["shapeOfLocationEstimateNotSupported"]["Enabled"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::FacilityNotSupParam::ShapeOfLocationEstimateNotSupported solens;
                    fns->SetShapeOfLocationEstimateNotSupported(solens);
                }
                isAVPEnabled = (*cfg)["neededLcsCapabilityNotSupportedInServingNode"]["Enabled"].asBool();
                isNull = (*cfg)["neededLcsCapabilityNotSupportedInServingNode"]["Enabled"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::FacilityNotSupParam::NeededLcsCapabilityNotSupportedInServingNode nlc;
                    fns->SetNeededLcsCapabilityNotSupportedInServingNode(nlc);
                }
                EncodeMsg(fns, &enc2);
                terr->SetParameter(enc2->GetArray());
            }
        case map_common::ERR_systemFailure:
            {
                Json::Value* cfg = &(*m_jsonRoot1)["SystemFailureParam"];
                map_v13::SystemFailureParam *sfp = new map_v13::SystemFailureParam();

                isAVPEnabled = (*cfg)["NetworkResource"]["Enabled"].asBool();
                isNull = (*cfg)["NetworkResource"]["Value"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::SystemFailureParam::NetworkResource nr((*cfg)["NetworkResource"]["Value"].asInt());
                    sfp->SetChoiceNetworkResource(nr);
                }
                isAVPEnabled = (*cfg)["ExtensibleSystemFailureParam"]["Enabled"].asBool();
                isNull = (*cfg)["ExtensibleSystemFailureParam"]["Enabled"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::SystemFailureParam::ExtensibleSystemFailureParam esfp;
                    isAVPEnabled = (*cfg)["ExtensibleSystemFailureParam"]["NetworkResource"]["Enabled"].asBool();
                    isNull = (*cfg)["ExtensibleSystemFailureParam"]["NetworkResource"]["Value"].isNull();
                    if((!isNull) && isAVPEnabled)
                    {
                        map_v13::SystemFailureParam::ExtensibleSystemFailureParam::NetworkResource nr((*cfg)["ExtensibleSystemFailureParam"]["NetworkResource"]["Value"].asInt());
                        esfp.SetNetworkResource(nr);
                    }
                    isAVPEnabled = (*cfg)["ExtensibleSystemFailureParam"]["AdditionalNetworkResource"]["Enabled"].asBool();
                    isNull = (*cfg)["ExtensibleSystemFailureParam"]["AdditionalNetworkResource"]["Value"].isNull();
                    if((!isNull) && isAVPEnabled)
                    {
                        map_v13::SystemFailureParam::ExtensibleSystemFailureParam::AdditionalNetworkResource anr((*cfg)["ExtensibleSystemFailureParam"]["AdditionalNetworkResource"]["Value"].asInt());
                        esfp.SetAdditionalNetworkResource(anr);
                    }
                    isAVPEnabled = (*cfg)["ExtensibleSystemFailureParam"]["FailureCauseParam"]["Enabled"].asBool();
                    isNull = (*cfg)["ExtensibleSystemFailureParam"]["FailureCauseParam"]["Value"].isNull();
                    if((!isNull) && isAVPEnabled)
                    {
                        map_v13::SystemFailureParam::ExtensibleSystemFailureParam::FailureCauseParam fcp((*cfg)["ExtensibleSystemFailureParam"]["FailureCauseParam"]["Value"].asInt());
                        esfp.SetFailureCauseParam(fcp);
                    }
                    sfp->SetChoiceExtensibleSystemFailureParam(esfp);
                }
                EncodeMsg(sfp, &enc2);
                terr->SetParameter(enc2->GetArray());
            }
        case map_common::ERR_illegalSubscriber:
            {
                map_v13::IllegalSubscriberParam *isp = new map_v13::IllegalSubscriberParam();
                EncodeMsg(isp, &enc2);
                terr->SetParameter(enc2->GetArray());
            }
        case map_common::ERR_illegalEquipment:
            {
                map_v13::IllegalEquipmentParam *iep = new map_v13::IllegalEquipmentParam();
                EncodeMsg(iep, &enc2);
                terr->SetParameter(enc2->GetArray());
            }
        case map_common::ERR_absentSubscriber:
            {
                Json::Value* cfg = &(*m_jsonRoot1)["AbsentSubscriberParam"];
                map_v13::AbsentSubscriberParam *asp = new map_v13::AbsentSubscriberParam();

                isAVPEnabled = (*cfg)["AbsentSubscriberReason"]["Enabled"].asBool();
                isNull = (*cfg)["AbsentSubscriberReason"]["Value"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::AbsentSubscriberParam::AbsentSubscriberReason asr((*cfg)["AbsentSubscriberReason"]["Value"].asInt());
                    asp->SetAbsentSubscriberReason(asr);
                }
                EncodeMsg(asp, &enc2);
                terr->SetParameter(enc2->GetArray());
            }
        case map_common::ERR_unidentifiedSubscriber:
            {
                map_v13::UnidentifiedSubParam *usp = new map_v13::UnidentifiedSubParam();
                EncodeMsg(usp, &enc2);
                terr->SetParameter(enc2->GetArray());
            }
    }
            

    *tcapErr = terr;

}
int prevCptInvoke = -1;

std::map<ITS_CTXT, ITS_OCTET> gInvokeList;

int ITUTcapMsgs::SendResponses(TCAP_Dialogue *dlg,
                                 TCAP_Component *cpt)
{
    TCAP_Continue tc_cont;
    TCAP_End      tc_end;
    TCAP_Invoke   isdr;
    TCAP_Invoke   erbr;
    TCAP_Result   ugla;
    TCAP_Result   saia;
    TCAP_Result   rfsr;
    TCAP_Result   puMsa;
    TCAP_Unidirectional tc_uni;
    bool isNull;
    int errVal = 0;
    TCAP_Error *tcapErr = NULL;

    //APP_TRACE_DEBUG(("Inside ITUTcapMsgs::SendCAPResponse"));
    ITS_ByteArray app_ctxt = map_common::EncodeApplicationContext(map_common::networkLocUpContext_v3);
    tc_end.SetApplicationContext(app_ctxt);
    tc_cont.SetApplicationContext(app_ctxt);

    srand(time(0));
    //int num = rand() % 17;

    if (dlg->GetDialogueType() == TCPPT_TC_BEGIN && cpt->GetComponentType() == TCPPT_TC_INVOKE) 
    {
        TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *> (cpt);
        ITS_LONG op;
        ivk->GetOperation(op);

        if (op == map_common::OP_sendAuthenticationInfo) 
        {
            Json::Value* cfg = &(*m_jsonRoot1)["SendAuthenticationInfoErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                if(errVal > 0 && errVal <= 72)
                {
                    app_ctxt = map_common::EncodeApplicationContext(map_common::infoRetrievalContext_v3);
                    tc_end.SetApplicationContext(app_ctxt);

                    BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                    tc_end.SetDialogueID(dlg->GetDialogueID());

                    if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                    {
                        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                        {
                            APP_TRACE_DEBUG(("Sent SendAuthenticationInfoError v3"));
                        }
                    }
                }
                else
                {
                    APP_TRACE_ERROR(("Invalid Error Value %c", errVal));
                }
            }
            else
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
                    }
                }

                delete enc2;
                delete tempSaia;
                enc2 = 0;
                tempSaia = 0;
            }
        }
        else if (op == map_common::OP_purgeMS) 
        {
            Json::Value* cfg = &(*m_jsonRoot1)["PurgeMSErr_Res"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                app_ctxt = map_common::EncodeApplicationContext(map_common::msPurgingContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent iPurgeMs_Err v3"));
                    }
                }
            }
            else
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
        }

        else if (op == map_common::OP_updateGprsLocation && 
                itstest::noISD)
        {
            Json::Value* cfg = &(*m_jsonRoot1)["UpdateGprsLocationErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent UpdateGprsLocationRes v3"));
                    }
                }
            }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::gprsLocationUpdateContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

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
                    }
                }

                delete enc2;
                delete tempUgla;
                enc2 = 0;
                tempUgla = 0;

                gRecvImsi.clear();
            }
        }
        else if (op == map_common::OP_updateGprsLocation && 
                !itstest::noISD)
        {
            Json::Value* cfg = &(*m_jsonRoot1)["UpdateGprsLocationErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent UpdateGprsLocationRes v3"));
                    }
                }
            }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempIsdr = BuildMapMsg(MAP_V13_INSERT_SUB_DATA);
                Octets *enc1 = 0;

                EncodeMsg(tempIsdr, &enc1);
                ITS_UINT pointCode = 0; 
                bool isNational = false;
                ITS_OCTET ssn = 0;
                TCAP_Begin *begin = (TCAP_Begin*)dlg;
                begin->GetOrigAddr(isNational, pointCode, ssn);
                isdr.SetParameter(enc1->GetArray());
                isdr.SetClass(1);
                isdr.SetInvokeID(10);
                isdr.SetOperation(map_common::OP_insertSubscriberData);

                tc_cont.SetDialogueID(dlg->GetDialogueID());
                tc_cont.SetOrigAddr(isNational, oPC, oSN);

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

                delete enc1;
                delete tempIsdr;
                enc1 = 0;
                tempIsdr = 0;            
            }
        }
        else if (op == map_common::OP_readyForSM)
        {
            Json::Value* cfg = &(*m_jsonRoot1)["ReadyForSMErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);
                
                app_ctxt = map_common::EncodeApplicationContext(map_common::mwdMngtContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent ReadyForSMErrRes v3"));
                    }
                }
            }
            else
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
        else if (op == map_common::OP_insertSubscriberData)
        {   
            Json::Value* cfg = &(*m_jsonRoot1)["InsertSubscriberDataErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);
                
                app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent InsertSubscriberDataRes v3"));
                    }
                }
            }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempRfsr = BuildMapMsg(MAP_V13_INSERT_SUB_DATA_RES);
                Octets *enc2 = 0;

                rfsr.SetInvokeID(cpt->GetInvokeID());

                EncodeMsg(tempRfsr, &enc2);

                rfsr.SetParameter(enc2->GetArray());
                rfsr.SetOperation(map_common::OP_insertSubscriberData);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent InsertSubscriberDataRes v3"));
                    }
                }

                delete enc2;
                delete tempRfsr;
                enc2 = 0;
                tempRfsr = 0;
            }
        }
        else if (op == map_common::OP_deleteSubscriberData)
        {
            Json::Value* cfg = &(*m_jsonRoot1)["DeleteSubscriberDataErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent DeleteSubscriberDataRes v3"));
                    }
                }
            }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempRfsr = BuildMapMsg(MAP_V13_DELETE_SUB_DATA_RES);
                Octets *enc2 = 0;

                rfsr.SetInvokeID(cpt->GetInvokeID());

                EncodeMsg(tempRfsr, &enc2);

                rfsr.SetParameter(enc2->GetArray());
                rfsr.SetOperation(map_common::OP_deleteSubscriberData);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS)
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS)
                    {
                        APP_TRACE_DEBUG(("Sent DeleteSubscriberDataRes v3"));
                    }
                }

                delete enc2;
                delete tempRfsr;
                enc2 = 0;
                tempRfsr = 0;
            }
        }
        else if (op == map_common::OP_cancelLocation)
        {   
            Json::Value* cfg = &(*m_jsonRoot1)["CancelLocationErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                app_ctxt = map_common::EncodeApplicationContext(map_common::locationCancellationContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent CancelLocationRes v3"));
                    }
                }
            }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::locationCancellationContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempRfsr = BuildMapMsg(MAP_V13_CANCEL_LOCATION_RES);
                Octets *enc2 = 0;

                rfsr.SetInvokeID(cpt->GetInvokeID());

                EncodeMsg(tempRfsr, &enc2);

                rfsr.SetParameter(enc2->GetArray());
                rfsr.SetOperation(map_common::OP_cancelLocation);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent CancelLocationRes v3"));
                    }
                }

                delete enc2;
                delete tempRfsr;
                enc2 = 0;
                tempRfsr = 0;
            }
        }
        else if (op == map_common::OP_provideSubscriberInfo)
        {
            Json::Value* cfg = &(*m_jsonRoot1)["ProvideSubscriberInfoErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberInfoEnquiryContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent ProvideSubscriberInfoRes v3"));
                    }
                }
            }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberInfoEnquiryContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempRfsr = BuildMapMsg(MAP_V13_PROVIDE_SUB_INFO_RES);
                Octets *enc2 = 0;

                rfsr.SetInvokeID(cpt->GetInvokeID());

                EncodeMsg(tempRfsr, &enc2);

                rfsr.SetParameter(enc2->GetArray());
                rfsr.SetOperation(map_common::OP_provideSubscriberInfo);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS)
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS)
                    {
                        APP_TRACE_DEBUG(("Sent ProvideSubscriberInfoRes v3"));
                    }
                }

                delete enc2;
                delete tempRfsr;
                enc2 = 0;
                tempRfsr = 0;
            }
        }
        else if (op == map_common::OP_deactivateTraceMode)
        {
            app_ctxt = map_common::EncodeApplicationContext(map_common::tracingContext_v3);
            tc_end.SetApplicationContext(app_ctxt);

            AsnObject *tempRfsr = BuildMapMsg(MAP_V13_TRACE_DEACTIVATE_MODE_RES);
            Octets *enc2 = 0;

            rfsr.SetInvokeID(cpt->GetInvokeID());

            EncodeMsg(tempRfsr, &enc2);

            rfsr.SetParameter(enc2->GetArray());
            rfsr.SetOperation(map_common::OP_deactivateTraceMode);

            tc_end.SetDialogueID(dlg->GetDialogueID());

            if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS)
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS)
                {
                    APP_TRACE_DEBUG(("Sent DeactivateTraceModeRes v3"));
                }
            }

            delete enc2;
            delete tempRfsr;
            enc2 = 0;
            tempRfsr = 0;
        }
        else if (op == map_common::OP_activateTraceMode)
        {
            app_ctxt = map_common::EncodeApplicationContext(map_common::tracingContext_v3);
            tc_end.SetApplicationContext(app_ctxt);

            AsnObject *tempRfsr = BuildMapMsg(MAP_V13_TRACE_ACTIVATE_MODE_RES);
            Octets *enc2 = 0;

            rfsr.SetInvokeID(cpt->GetInvokeID());

            EncodeMsg(tempRfsr, &enc2);

            rfsr.SetParameter(enc2->GetArray());
            rfsr.SetOperation(map_common::OP_activateTraceMode);

            tc_end.SetDialogueID(dlg->GetDialogueID());

            if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS)
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS)
                {
                    APP_TRACE_DEBUG(("Sent ActivateTraceModeRes v3"));
                }
            }

            delete enc2;
            delete tempRfsr;
            enc2 = 0;
            tempRfsr = 0;
        }

    }
    else if (dlg->GetDialogueType() == TCPPT_TC_UNI && cpt->GetComponentType() == TCPPT_TC_INVOKE)
    {
        TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *> (cpt);
        ITS_LONG op;
        ivk->GetOperation(op);
        if(op == map_common::OP_reset)
        {
            APP_TRACE_DEBUG(("Received Reset Arg.. Consume It..!!"));
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
                }
            }

            delete enc2;
            delete tempUgla;
            enc2 = 0;
            tempUgla = 0;
        }
        else if(op == cap::OP_releaseCall)
        {
            APP_TRACE_DEBUG(("Nothing To do for after receiving Release Call"));
        }
 
    }
    else if (dlg->GetDialogueType() == TCPPT_TC_CONTINUE && cpt->GetComponentType() == TCPPT_TC_INVOKE)
    {
        TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *> (cpt);
        ITS_LONG op;
        ivk->GetOperation(op);

        if (op == map_common::OP_insertSubscriberData)
        {
            app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
            tc_cont.SetApplicationContext(app_ctxt);

            AsnObject *tempRfsr = BuildMapMsg(MAP_V13_INSERT_SUB_DATA_RES);
            Octets *enc2 = 0;

            rfsr.SetInvokeID(cpt->GetInvokeID());

            EncodeMsg(tempRfsr, &enc2);

            rfsr.SetParameter(enc2->GetArray());
            rfsr.SetOperation(map_common::OP_insertSubscriberData);

            tc_cont.SetOrigAddr(false, oPC, oSN);
            tc_cont.SetDialogueID(dlg->GetDialogueID());

            if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &rfsr) == ITS_SUCCESS) 
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) == ITS_SUCCESS) 
                {
                    APP_TRACE_DEBUG(("Sent InsertSubscriberDataRes v3"));
                }
            }

            delete enc2;
            delete tempRfsr;
            enc2 = 0;
            tempRfsr = 0;
        }
        else if(op == cap::OP_requestReportSMSEvent)
        {
            APP_TRACE_DEBUG(("Request Report SMS Event received in Tc_Cont"));
        }
        else if(op == cap::OP_continueSMS)
        {
            APP_TRACE_DEBUG(("Continue SMS Event received in Tc_Cont"));
            SendEventReportSMSArginTcEnd(dlg); 
        }
        else if(op == cap::OP_requestReportBCSMEvent)
        {
            APP_TRACE_DEBUG(("Nothing To do for after receiving RRB"));         
        }
        else if(op == cap::OP_releaseCall)
        {
            //NOTE: For call flow 6, 9 
            APP_TRACE_DEBUG(("Release Call Recieved in Tc_Cont"));
            SendEventReportBCSMArgInTcCont(dlg,true);
            SendApplyChargingReportInTcEnd(dlg);
        }
        else if(op == cap::OP_applyCharging && LastCptRcvd)
        {
            try {
                SendResponseForUpdateCase(dlg);
            }
            catch(...)
            {    
                APP_TRACE_DEBUG((" Encode Failed "));
            }
        }
        else if(op == cap::OP_continue)
        {
            try {
                SendResponseForInitialCase(dlg);
            }
            catch(...)
            {    
                APP_TRACE_DEBUG((" Encode Failed "));
            }
        }
    }
    else if (dlg->GetDialogueType() == TCPPT_TC_END && cpt->GetComponentType() == TCPPT_TC_INVOKE)
    {
        TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *> (cpt);
        ITS_LONG op;
        ivk->GetOperation(op);
        if(op == cap::OP_releaseCall)
        {
            APP_TRACE_DEBUG(("Release Call Recieved in Tc_End, no need to send response"));
        }
        else if(op == cap::OP_releaseSMS)
        {
            APP_TRACE_DEBUG(("Release SMS Recieved in Tc_End, no need to send response"));
        }
    }
       return 0;
}

void ITUTcapMsgs::BuildAndSendERBandACRinTcEnd(TCAP_Dialogue *dlg)
{
    bool isNull;
    bool isAVPEnabled;
    bool isERBorACRSent = false;

    Json::Value l_jsonRootcap = parseCapConfig();

    Json::Value* m_jsonRoot3 = &l_jsonRootcap;
    Json::Value* m_jsonRoot4 = &(*m_jsonRoot3)["cap_v3"]["Send_Response_After_Receiving_Only_ACH"];

    Json::Value* cfg = &(*m_jsonRoot4)["Send_Only_ERB_in_TcEnd"];
    isNull = (*cfg)["Enabled"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        APP_TRACE_DEBUG((" Send ERB in TC_End "));
        SendEventReportBCSMArgInTcEnd(dlg);
        isERBorACRSent = true;
    }

    cfg = &(*m_jsonRoot4)["Send_Only_ERB_in_TcCont"];
    isNull = (*cfg)["Enabled"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        APP_TRACE_DEBUG((" Send ERB in TC_Cont "));
        SendEventReportBCSMArgInTcCont(dlg,true);
        isERBorACRSent = true;
    }

    cfg = &(*m_jsonRoot4)["Send_Only_ACR_in_TcEnd"];
    isNull = (*cfg)["Enabled"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        APP_TRACE_DEBUG((" Send ACR in TC_End "));
        SendApplyChargingReportInTcEnd(dlg);
        isERBorACRSent = true;
    }

    cfg = &(*m_jsonRoot4)["Send_Only_ACR_in_TcCont"];
    isNull = (*cfg)["Enabled"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        APP_TRACE_DEBUG((" Send ACR in TC_Cont "));
        SendApplyChargingReportArgInTcCont(dlg,true);
        isERBorACRSent = true;
    }
    
    if(!isERBorACRSent)
    {
        APP_TRACE_DEBUG((" Send ERB and ACR in TC_End "));
        SendERBandACRInTcEnd(dlg);
    }

}

void ITUTcapMsgs::BuildAndSendERBandACRinTcCont(TCAP_Dialogue *dlg,bool receivedonlyACH)
{
    bool isNull;
    bool isAVPEnabled;
    bool isERBorACRSent = false;

    Json::Value l_jsonRootcap = parseCapConfig();

    Json::Value* m_jsonRoot3 = &l_jsonRootcap;
    Json::Value* m_jsonRoot4 = NULL;

    if(receivedonlyACH)
        m_jsonRoot4 = &(*m_jsonRoot3)["cap_v3"]["Send_Response_After_Receiving_Only_ACH"];
    else
        m_jsonRoot4 = &(*m_jsonRoot3)["cap_v3"]["Send_Multiple_CAP_ERB_ACR"];

    Json::Value* cfg = &(*m_jsonRoot4)["Send_Only_ERB_in_TcEnd"];
    isNull = (*cfg)["Enabled"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        APP_TRACE_DEBUG((" Send ERB in TC_End "));
        SendEventReportBCSMArgInTcEnd(dlg);
        isERBorACRSent = true;
    }

    cfg = &(*m_jsonRoot4)["Send_Only_ERB_in_TcCont"];
    isNull = (*cfg)["Enabled"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        APP_TRACE_DEBUG((" Send ERB in TC_Cont "));
        SendEventReportBCSMArgInTcCont(dlg);
        isERBorACRSent = true;
    }

    cfg = &(*m_jsonRoot4)["Send_Only_ACR_in_TcEnd"];
    isNull = (*cfg)["Enabled"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        APP_TRACE_DEBUG((" Send ACR in TC_End "));
        SendApplyChargingReportInTcEnd(dlg);
        isERBorACRSent = true;
    }

    cfg = &(*m_jsonRoot4)["Send_Only_ACR_in_TcCont"];
    isNull = (*cfg)["Enabled"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        APP_TRACE_DEBUG((" Send ACR in TC_Cont "));
        SendApplyChargingReportArgInTcCont(dlg);
        isERBorACRSent = true;
    }

    if(!isERBorACRSent)
    {
        APP_TRACE_DEBUG((" Send ERB in TC_Cont "));
        SendEventReportBCSMArgInTcCont(dlg);
        APP_TRACE_DEBUG((" Send ACR in TC_Cont "));
        SendApplyChargingReportArgInTcCont(dlg);
    }
}

int ITUTcapMsgs::SendEventReportSMSArginTcEnd(TCAP_Dialogue *dlg)
{
    TCAP_End tc_end;
    TCAP_Invoke erb;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
    tc_end.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = BuildEventReportSMSArg();
    Octets *enc2 = 0;
 
    EncodeMsg(tempRfsr, &enc2);
    erb.SetParameter(enc2->GetArray());
    erb.SetClass(1);
    erb.SetInvokeID(230);
    erb.SetOperation(cap::OP_eventReportSMS);

    tc_end.SetDialogueID(dlg->GetDialogueID());

    if (TCAP_Component::Send(ISS7_Stack, &tc_end, &erb) == ITS_SUCCESS)
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent EventReportSMSArg in Tc_End"));
        }
    }

    delete enc2;
    delete tempRfsr;
    enc2 = 0;
    tempRfsr = 0;

    return 0;
}

int ITUTcapMsgs::SendERBandACRInTcEnd(TCAP_Dialogue *dlg)
{
    TCAP_End tc_end;
    TCAP_Invoke erb;
    TCAP_Invoke acr;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    tc_end.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = BuildEventReportBCSMArginTcEnd();
    Octets *enc2 = 0;

    EncodeMsg(tempRfsr, &enc2);
    erb.SetParameter(enc2->GetArray());
    erb.SetClass(1);
    erb.SetInvokeID(++InvokeID);
    erb.SetOperation(cap::OP_eventReportBCSM);

    tc_end.SetDialogueID(dlg->GetDialogueID());


    AsnObject *tempRfsr2 = BuildApplyChargingReportinTcEnd();
    Octets *enc3 = 0;

    EncodeMsg(tempRfsr2, &enc3);
    acr.SetParameter(enc3->GetArray());
    acr.SetClass(1);
    acr.SetInvokeID(++InvokeID);
    acr.SetOperation(cap::OP_applyChargingReport);

    if (TCAP_Component::Send(ISS7_Stack, &tc_end, &erb) == ITS_SUCCESS) 
    {
        if (TCAP_Component::Send(ISS7_Stack, &tc_end, &acr) == ITS_SUCCESS)
        {
            if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
            {
                APP_TRACE_DEBUG(("Sent EventReportBCSMArg v3 & ApplyChargingReportArg v3 in a single dialogue"));
            }
        }
    }
    
    delete enc2;
    delete enc3;
    delete tempRfsr;
    delete tempRfsr2;
    enc2 = 0;
    enc3 = 0;
    tempRfsr = 0;
    tempRfsr2 = 0;

    return 0;
}

int ITUTcapMsgs::SendApplyChargingReportArgInTcCont(TCAP_Dialogue *dlg, bool sendACRinTcContAgain)
{
    TCAP_Continue tc_cont;
    TCAP_Invoke   acr;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    tc_cont.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = NULL;

    if(sendACRinTcContAgain)
        tempRfsr = BuildApplyChargingReportinTcContAgain();
    else
        tempRfsr = BuildApplyChargingReportinTcCont();

    Octets *enc = 0;

    EncodeMsg(tempRfsr, &enc);
    acr.SetParameter(enc->GetArray());
    acr.SetClass(1);
    acr.SetInvokeID(++InvokeID);
    acr.SetOperation(cap::OP_applyChargingReport);

    tc_cont.SetOrigAddr(false, oPC, oSN);
    tc_cont.SetDialogueID(dlg->GetDialogueID());

    if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &acr) == ITS_SUCCESS) 
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent ApplyChargingReportArg v3"));
        }
    }
    
    delete enc;
    enc = 0;
    delete tempRfsr;
    tempRfsr = 0;
    return 0;
}

int ITUTcapMsgs::SendApplyChargingReportInTcEnd(TCAP_Dialogue *dlg)
{
    TCAP_End tc_end;
    TCAP_Invoke acr;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    tc_end.SetApplicationContext(app_ctxt);

    tc_end.SetDialogueID(dlg->GetDialogueID());

    AsnObject *tempRfsr = BuildApplyChargingReportinTcEnd();
    Octets *enc = 0;

    EncodeMsg(tempRfsr, &enc);
    acr.SetParameter(enc->GetArray());
    acr.SetClass(1);
    acr.SetInvokeID(++InvokeID);
    acr.SetOperation(cap::OP_applyChargingReport);
    if (TCAP_Component::Send(ISS7_Stack, &tc_end, &acr) == ITS_SUCCESS)
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent ApplyChargingReportArg v3 in Tc_End"));
        }
    }

    delete enc;
    delete tempRfsr;
    enc = 0;
    tempRfsr = 0;
    
    return 0;
}

int ITUTcapMsgs::SendEventReportBCSMArgInTcEnd(TCAP_Dialogue *dlg)
{
    TCAP_End tc_end;
    TCAP_Invoke erb;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    tc_end.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = BuildEventReportBCSMArginTcEnd();
    Octets *enc2 = 0;

    EncodeMsg(tempRfsr, &enc2);
    erb.SetParameter(enc2->GetArray());
    erb.SetClass(1);
    erb.SetInvokeID(++InvokeID);

    erb.SetOperation(cap::OP_eventReportBCSM);

    tc_end.SetDialogueID(dlg->GetDialogueID());

    if (TCAP_Component::Send(ISS7_Stack, &tc_end, &erb) == ITS_SUCCESS) 
    {
            if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
            {
                APP_TRACE_DEBUG(("Sent EventReportBCSMArg v3"));
            }
    }
    
    delete enc2;
    delete tempRfsr;
    enc2 = 0;
    tempRfsr = 0;

    return 0;

}

int ITUTcapMsgs::SendEventReportBCSMArgInTcCont(TCAP_Dialogue *dlg,  bool sendERBinTcContAgain)
{
    TCAP_Continue tc_cont;
    TCAP_Invoke   erbr;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    tc_cont.SetApplicationContext(app_ctxt);
    AsnObject *tempRfsr = NULL;

    if(sendERBinTcContAgain)
        tempRfsr = BuildEventReportBCSMArginTcContAgain();
    else
        tempRfsr = BuildEventReportBCSMArginTcCont();

    Octets *enc = 0;

    EncodeMsg(tempRfsr, &enc);
    erbr.SetParameter(enc->GetArray());
    erbr.SetClass(1);
    erbr.SetInvokeID(++InvokeID);
    erbr.SetOperation(cap::OP_eventReportBCSM);

    tc_cont.SetOrigAddr(false, oPC, oSN);
    tc_cont.SetDialogueID(dlg->GetDialogueID());
    if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &erbr) == ITS_SUCCESS) 
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent EventReportBCSMArg v3"));
        }
    }

    delete enc;
    enc = 0;
    delete tempRfsr;
    tempRfsr = 0;

    return 0;
}

void ITUTcapMsgs::IncrementImsi(int opCode)
{
    uint8_t l_imsi[MAP_MAX_E164_SZ/2] = {0};
    char s_Imsi[256];
    sprintf(s_Imsi,"%lld",imsiforload++);
    string Imsi = (char *)s_Imsi;
    //cout << "Imsi in msg" << Imsi<<endl;
    if (Imsi.length() >= 15)
    {
        Imsi.erase(15, std::string::npos);
    }
    int len = MAPUtils::StringToTBCD(Imsi, l_imsi, MAP_MAX_E164_SZ);
    if (Imsi.length() % 2) 
    {    
        l_imsi[(Imsi.length() / 2)] |= 0xF0;
    }
    map_v13::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
    
    switch(opCode)
    {
        case  MAP_V13_UPDATE_GPRS_LOC:
            {
                map_v13::UpdateGprsLocationArg *gprsa = (map_v13::UpdateGprsLocationArg *) UGLArg;
                gprsa->SetImsi(imsi);
                break;
            }
        case MAP_V13_SEND_AUTH_INFO_ARG:
            {
                map_v13::SendAuthenticationInfoArg *saia = (map_v13::SendAuthenticationInfoArg *) SAIArg;
                saia->SetImsi(imsi);
                break;
            }
        case MAP_V13_PURGE_MS_ARG:
            {
                map_v13::PurgeMS_Arg *purge = (map_v13::PurgeMS_Arg *) PURGEArg;
                purge->SetImsi(imsi);
                break;
            }
        case MAP_V13_SAI_ARG_AND_UGL_ARG:
            {
                map_v13::UpdateGprsLocationArg *gprsa = (map_v13::UpdateGprsLocationArg *) UGLArg;
                gprsa->SetImsi(imsi);
                map_v13::SendAuthenticationInfoArg *saia = (map_v13::SendAuthenticationInfoArg *) SAIArg;
                saia->SetImsi(imsi);
                break;
            }
        default:
            {
                APP_TRACE_DEBUG(("Unknown OpCode %d",opCode));
                break;
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
int ITUTcapMsgs::SendResponseForUpdateCase(TCAP_Dialogue *dlg)
{
    switch(optionfromserver)
    {
        case 1:
            {
                //NOTE: O_Disconnet in ERB and CallActive false in ACR
                SendEventReportBCSMArgInTcCont(dlg,true);
                SendApplyChargingReportArgInTcCont(dlg,true);
                break;
            }
        case 4:
        case 7:
        case 8:
            {
                SendEventReportBCSMArgInTcCont(dlg,true);
                SendApplyChargingReportInTcEnd(dlg);
                break;
            }
        default:
            {
                APP_TRACE_DEBUG(("Error:Update Case - Unknown CallFlow Received"));
                return -1;
            }
    }
    return 0;
}
int ITUTcapMsgs::SendResponseForInitialCase(TCAP_Dialogue *dlg)
{
    switch(optionfromserver)
    {
        case 1:
        case 4:
        case 6:
        case 7:
        case 8:
        case 9:
        case 11:
            {
                //NOTE: O_Answer in ERB and CallActive true in ACR
                SendEventReportBCSMArgInTcCont(dlg);
                if(optionfromserver == 8)
                {
                    //NOTE: For callflow 8, to simulate RAR case after CalledParty Answer
                    //sleep till RAR call flow is done between OCS and IWF
                    APP_TRACE_DEBUG(("Sleep to simulate RAR case after CalledParty Answers"));
                    sleep(10);
                }
                SendApplyChargingReportArgInTcCont(dlg);
                break;
            }
        case 2:
        case 3:
            {
                //NOTE: For callflow 2 O_CalledPartyBusy, for callflow 3 O_NoAnswer is set in ERB
                SendEventReportBCSMArgInTcCont(dlg);
                break;
            }
        default:
            {
                APP_TRACE_DEBUG(("Error:Initial Case - Unknown CallFlow Received"));
                return -1;
            }
    }
    return 0;
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
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Exception during encoding phase..." << endl;
        cout << exc.GetDescription() << endl;
        cout << "Exit test..." << endl;
    }

    //cout << endl;
    //cout << "--------------------------------------------------" << endl;
    *octets = tmpOctets;
}



#endif
