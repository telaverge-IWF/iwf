/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2011 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 *
 * ID: $Id: ssg_callbacks.cpp,v 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.16 2023/05/05 09:34:13 jkchaitanya Exp $
 *
 *  LOG: $Log: ssg_callbacks.cpp,v $
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.16  2023/05/05 09:34:13  jkchaitanya
 *  LOG: Added multithread support
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.15  2020/04/20 08:45:34  jkchaitanya
 *  LOG: tcmalloc optimization added for IWF performance
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.14  2015/06/01 10:01:39  jkchaitanya
 *  LOG: changes to append 91 for SGSN Number
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.13  2015/04/21 14:38:04  jkchaitanya
 *  LOG: changes for restart crash
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.12  2015/04/21 09:13:53  jkchaitanya
 *  LOG: changes for not to reverse the vector while mapping diameter avp for SAIResp
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.11  2015/04/09 10:19:53  jkchaitanya
 *  LOG: changes for bug 5166 and critical stats implementation in IWF
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.10  2015/04/06 06:07:16  jkchaitanya
 *  LOG: Changes done for queueing implementation
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.9  2015/03/20 09:54:10  jkchaitanya
 *  LOG: changes for bug fixes and Couchbase issues in HA
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.8  2015/03/17 06:09:07  jkchaitanya
 *  LOG: changes for audit thread implementation, fix for returning readyforsm response and customer ticket 797
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.7  2015/03/05 06:40:46  jkchaitanya
 *  LOG: Changes done for having a periodic bulk fetch in the standby node, so that the Couchbase outage will not impact the service
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.6  2015/02/10 06:58:20  jkchaitanya
 *  LOG: changes for bug fixes done on top of 4.1.0-00 release
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.5  2015/01/30 12:52:46  mhimanshu
 *  LOG: Support for CSV format of CDR-log generation
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.4  2015/01/22 15:07:35  jkchaitanya
 *  LOG: changes for aspid issue faced in the HP site
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.3  2014/12/16 08:49:56  jkchaitanya
 *  LOG: changes for IWF crash observed at restart time
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.2  2014/12/04 11:59:16  pramana
 *  LOG: Added subscriber context replication support
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.1  2014/11/21 06:37:47  jkchaitanya
 *  LOG: changes for IPSP configurations
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3  2014/11/17 05:08:40  jkchaitanya
 *  LOG: changes for HA Bug Fixes
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.2  2014/11/04 09:11:56  jkchaitanya
 *  LOG: changes for HA bug fixes
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.1  2014/10/27 08:30:34  millayaraja
 *  LOG: changes for HA HotStandBy and selection criteria enhancements
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2  2014/08/22 11:16:18  millayaraja
 *  LOG: added check in postFunc() to indicate the PostNextEvnt() not to process any message once PostFunc() is called
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.1  2014/07/29 12:24:16  jsarvesh
 *  LOG: corrected the spelling of caught
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.4  2014/06/13 06:29:47  jkchaitanya
 *  LOG: reverted back the Leak fix for answer message without sessionID
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.3  2014/06/11 09:04:36  millayaraja
 *  LOG: fixed memory leak for Answer message without sessionId
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.2  2014/05/27 05:20:07  jkchaitanya
 *  LOG: Review request 2299
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5.4.1  2014/05/06 13:11:02  jkchaitanya
 *  LOG: changes for ccfh feature
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.5  2014/02/27 12:53:28  millayaraja
 *  LOG: updated to send ReleaseSMS for timeout scenario
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.4  2014/02/26 07:41:36  millayaraja
 *  LOG: Changes made to move from Diameter::Command to DIA_BASE_CMD(DiaMsgFlow) in IWF Application
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.3  2014/02/13 14:11:38  jkchaitanya
 *  LOG:  changes for avp mappings for TSL
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.2  2014/02/12 10:58:49  jkchaitanya
 *  LOG: changes for TSL
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6.2.1  2014/02/07 08:13:34  jkchaitanya
 *  LOG: changes for porting bug fixes from 02 Productization
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.7  2014/02/07 06:01:56  jsarvesh
 *  LOG: Changes done for GT configuration and removed the rollback of AssociationSet in case of failure
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.6  2014/01/07 10:43:34  jkchaitanya
 *  LOG: updated to send ReleaseCallArgs when unable to deliver Diameter Msgs
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.5  2014/01/06 06:12:27  millayaraja
 *  LOG: upated to handle loopback error message from diameter Stack
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.4  2013/12/31 04:40:41  millayaraja
 *  LOG: merged code from B-IWF-0100-01 to B-IWF-0100-02 with GTT support
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.3  2013/12/12 11:51:29  jsarvesh
 *  LOG: Changes done to send ASPINACTIVE and ASPDOWN when IWF comes down
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.2  2013/12/10 13:34:00  millayaraja
 *  LOG: updated productization code for eAccelero Logging
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3.2.1  2013/12/03 09:46:00 millayaraja
 *  LOG: initial code checkin for IWF productization
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.3  2013/10/04 13:43:07  millayaraja
 *  LOG: changes for RHEL machine dependent compilation flags and dependencies in IWF code
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.2  2013/08/01 05:51:05  millayaraja
 *  LOG: updated to handle the indication from stack
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11.2.1  2013/07/15 05:41:06  jsarvesh
 *  LOG: IWF-Phase-III Code CAP-Ro Implementation
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.11  2013/05/29 11:25:52  jvikram
 *  LOG: RSR to resetArg changes
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.10  2013/05/22 15:21:21  jsarvesh
 *  LOG: IWF Phase-II Changes
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.9  2013/05/20 09:01:50  jvikram
 *  LOG: Corrected Coverity Issues
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.8  2013/04/22 05:47:52  jsarvesh
 *  LOG: reverting coverity fix as causing crash in IWF
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.7  2013/04/18 05:41:22  jvikas
 *  LOG: Fixes for High Impact Coverity Issues
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.6  2013/03/15 21:22:45  brajappa
 *  LOG: SCCP CCITT support for IWF
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.5  2013/02/12 13:07:31  brajappa
 *  LOG: Removing the DCCA application registration for now
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.4  2013/01/23 21:04:37  lakshman
 *  LOG: verified provideSubscriberArg and tcap error scenarios.
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3  2013/01/15 21:21:30  lakshman
 *  LOG: get Delete subscriber and Insert subscriber conversions in cvs.
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.2  2013/01/15 16:00:42  arnabd
 *  LOG: IWF State Machine Changes & Enhancements
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1  2013/01/11 22:22:58  brajappa
 *  LOG: IWF config reading using json and Abstract base Translator addition
 *  LOG:
 *  LOG: Revision 1.1.1.1  2013/01/09 16:41:36  brajappa
 *  LOG: Initial import
 *  LOG:
 *  LOG: Revision 1.2.2.5  2013/01/03 22:34:36  arnabd
 *  LOG: Transaction Manager destruction
 *  LOG:
 *  LOG: Revision 1.2.2.4  2013/01/03 21:19:57  lakshman
 *  LOG: add changes relevant for the first round of integration
 *  LOG:
 *  LOG: Revision 1.2.2.3  2013/01/03 13:10:28  lakshman
 *  LOG: checkin V13 changes and update callbacks with transaction_manager api
 *  LOG:
 *  LOG: Revision 1.2.2.2  2012/12/26 19:07:43  lakshman
 *  LOG: create itutcap module object.
 *  LOG:
 *  LOG: Revision 1.2.2.1  2012/12/22 18:07:23  lakshman
 *  LOG: update transport framework changes and have few stubs ready for later
 *  LOG: additions.
 *  LOG:
 *  LOG: Revision 1.2  2011/04/15 11:34:07  nvijikumar
 *  LOG: UT Updates
 *  LOG:
 *  LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 *  LOG: Initial Draft for SSG
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: ssg_callbacks.cpp,v 1.1.1.1.2.11.2.3.2.6.2.5.4.4.2.2.2.3.2.16 2023/05/05 09:34:13 jkchaitanya Exp $"

#include <iostream>

#ifdef ITU
#undef ITU
#endif

#ifndef CCITT
#define CCITT
#endif

#include <its++.h>
#include <its_timers.h>
#include <its_ual.h>
#include <engine++.h>
#include <mtp3_intern.h>

#include <ss7_mgmt.h>

#include <dia_trace.h>
#include <dia_config.h>
#include <dia_frame.h>

#include <dia_module.h>

#include <ssg_defines.h>
#include <ssg_trace.h>
#include <ssg_configuration.h>

//#include <ssg_dia_module.h>
//#include <ssg_itu_tcap_module.h>
//#include <ssg_prot_conv_module.h>

#include <ssg_utils.h>
#include <ssg_dbc.h>

//#include <ssg_mgmt_tables.h>

#include <iwf_transaction_manager.h>
#include <ual_config_mgnt.h>

#include "iwf_config.h"
#include "iwf_prot_s6a_map.h"
#include "iwf_prot_map_s6a.h"
#include "iwf_prot_cap_ro_transatel.h"
#include "iwf_prot_cap_ro.h"
#include "iwf_prot_default_translator.h"
#include "iwf.h"
#include "iwf_prot_utils.h"
#include "iwf_timer_defines.h"
#include "ThreadManager.h"
#if defined(ITS_STD_NAMESPACE)
#ifdef GCC_LESS_THAN_4_3
//using namespace std::tr1;
using namespace std;
#else
using namespace std;
#endif
using namespace its;
using namespace engine;
#endif

extern "C" int DetermineStartOctetNumForGttAddrDgts(ITS_OCTET addrInd,
                                                ITS_OCTET *gttInfo,
                                                std::string gttAddrDgtsNew);

extern "C" int SetGlobalTitleAddress(ITS_OCTET *gttInfo, ITS_OCTET *gTi);

extern "C" void UalTransCallback(ITS_POINTER object,
                                 ITS_POINTER userData,
                                 ITS_POINTER callData);
#ifndef USE_ANSI_SCCP
#if 0
extern "C" void SSG_GTT_Callback_ITU(ITS_POINTER object, ITS_POINTER userData,
                     ITS_POINTER callData);
#endif
#if 1
extern "C" void IWF_GTT_Callback_ITU(ITS_POINTER object, ITS_POINTER userData,
                     ITS_POINTER callData);

extern "C" void IWF_SCTP_Callback_ITU(ITS_POINTER object, ITS_POINTER userData,
                     ITS_POINTER callData);

extern "C" void IWF_SCTP_ASPIdRegistration_Callback(ITS_POINTER object, ITS_POINTER userData,
                     ITS_POINTER callData);

#endif
#endif

bool gisShutdownInProgress = false;

bool isASPUp;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
extern "C" ITS_USHORT
SSGCB_ApplicationSelector(ITS_HDR *hdr, ITS_EVENT *event)
{
    ScopedLogger socpedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG(" SSGCB_ApplicationSelector: Src = 0x%0x", event->src);

    // TODO: Application Transports can be randomized if need be.
    return ITS_DEFAULT_USER_SRC;
}

extern "C" int
SSGPreFunc()
{
    ScopedLogger socpedLogger(IwfController::Instance().GetLogger());

    DLOG_DEBUG("--Enter SSGPreFunc--");
    int ret = ITS_SUCCESS;
    // Check if all the env var are set -Arun, Bug #1050

    SSG_TRACE()->Create();
    SSG_TRACE()->Enable();


    GetSsgConfiguration();

    DLOG_DEBUG("In Pre-Func");

    DLOG_DEBUG("Waiting for status update request from avamgr for CMGR initialization....");
    int status = IwfController::WaitForUpdateFromAvaMgr();
    if(status == RECEIVED_UPDATE)
    {
        DLOG_DEBUG("IWF get a received update request from avamgr..hence proceeding with initialization");
    }
    else
    {
        DLOG_DEBUG("IWF didnt get the status update request from avamgr");
        return ITS_EINVALIDERR;
    }

    /* This code is being moved to the ssg.cpp file
    // IWF objects initialization
    char *iwfJson = getenv("IWF_CONFIG_FILE");
    if (iwfJson == NULL)
    {
        iwfJson = (char*)IWF_CONFIG_DEFAULT_FILE;
    }
    IwfController::Create(iwfJson);
    */

    ret = IwfController::Instance().Config().ParseConfig();
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    DLOG_DEBUG("IWF Config parse success!");
    // Register the available protocol translators here
    IwfController::Instance().RegisterTranslator(DEF_TRANSLATOR_STR,
                                    new DefaultHandler());
    IwfController::Instance().RegisterTranslator(S6A_TO_MAP_STR,
                                    new S6aToMAPHandler());
    IwfController::Instance().RegisterTranslator(MAP_TO_S6A_STR,
                                    new MAPToS6aHandler());
    IwfController::Instance().RegisterTranslator(CAP_TO_RO_STR,
                                    new CAPToRoHandler());
	IwfController::Instance().RegisterTranslator(CAP_TO_RO_STR_TSL,
                                    new TransatelCAPToRoHandler());

    ret = IwfController::Instance().Config().ParseTranslatorConfig();
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    DLOG_DEBUG("IWF Translator Config parse success!");

    //This code is moved to IwfController::InitDiameterStack()
    /*
    DiaConfig *cfg = DiaConfig::GetDiaConfig();
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();

    if (diaFrame)
    {
        if (cfg)
        {
            diaFrame->RegisterApplication(BASE_INTERFACE_APP_ID);
            diaFrame->Initialize();
        }
    }
    */

    IwfHssToSgsnCache::getInstance()->initialize(IwfController::Instance().Config().RoutingRules().getE164StartNumber(),
                                                 IwfController::Instance().Config().RoutingRules().getE164EndNumber());
    cout << "SSGPreFunc: Dispatching WorkerPools" << endl;
    DLOG_DEBUG("SSGPreFunc: Dispatching WorkerPools");
    // Start WorkerPools...let engine do the thread management.
    ThreadPoolEntry thr;
    engine::Worker *eng;

    workerPool->GetFirstAvailThread(thr);
    eng = reinterpret_cast<engine::Worker *>(thr.GetThread());
    workerPool->DispatchOnThread(thr,
                                 DISP_Dispatch_USER_CPP,
                                 (void *)eng->GetCallbackStruct());

#ifndef USE_ANSI_SCCP
    if (CALLBACK_AddCallback(__UAL_SCTPMgntCallBack,
                             IWF_SCTP_Callback_ITU, NULL) != ITS_SUCCESS)
    {
        DLOG_ERROR("Error adding SCCP GTT Callback...");
        ITS_GlobalStop();
        exit(0);
    }
    if(CALLBACK_AddCallback(UAL_ASP_ManagementCallbacks,
                            IWF_SCTP_ASPIdRegistration_Callback, NULL) != ITS_SUCCESS)
    {
        DLOG_ERROR("Error adding SCCP GTT Callback...");
        ITS_GlobalStop();
        exit(0);
    }
#endif
    ITS_SetNodeState(ITS_STATE_BACKUP);
    //If we are active initialize the stack with the transports initialized

    DiaConfig *cfg = DiaConfig::GetDiaConfig();
    /*
     * Access the diameter stack HANDLE
     * via the DiaFrame Singleton Object Pointer
     */
    DiaTrace::GetDiaTrace()->Disable(DIA_DEBUG);
    DiaFrame *diaFrame = DiaFrame::InitDiaFrame();

    if(MESS_ISActiveInst(IwfController::Instance().m_iwfMeSS.MeSSObj().Self().instance))
    {
        if( IwfController::Instance().InitDiameterStack(true) != ITS_SUCCESS )
        {
            cout << "IwfController InitDiaStack failed, Check the Diameter local configuration and restart IWF" <<endl;
            DLOG_DEBUG("IwfController InitDiaStack failed, Check the Diameter local configuration and restart IWF");
        }

        if( IwfController::Instance().InitSigTranStack(true) != ITS_SUCCESS )
        {
            cout << "IwfController InitSigTranStack failed, Check the Sigtran Local configurtioan and restart IWF" << endl;
            DLOG_DEBUG("IwfController InitSigTranStack failed, Check the Sigtran Local configurtioan and restart IWF");
        }
    }
    else// if (!itsDiaConfig.IsInterWorkingMode())
    {
        if( IwfController::Instance().InitDiameterStack(false) != ITS_SUCCESS )
        {
            cout << "IwfController InitDiaStack failed, Check the Diameter local configuration and restart IWF" <<endl;
            DLOG_DEBUG("IwfController InitDiaStack failed, Check the Diameter local configuration and restart IWF");
        }

        if( IwfController::Instance().InitSigTranStack(true) != ITS_SUCCESS )
        {
            cout << "IwfController InitSigTranStack failed, Chekc the Sigtran Local configurtioan and restart IWF" << endl;
            DLOG_DEBUG("IwfController InitSigTranStack failed, Chekc the Sigtran Local configurtioan and restart IWF");
        }
    }

#ifndef USE_ANSI_SCCP
#if 0
    if (CALLBACK_AddCallback(SCCP_CCITT_GlobalTitleTranslator,
                             SSG_GTT_Callback_ITU, NULL) != ITS_SUCCESS)
    {
        DLOG_ERROR("Error adding SCCP GTT Callback...");
        ITS_GlobalStop();
        exit(0);
    }
#endif
#if 1
    if (CALLBACK_AddCallback(SCCP_CCITT_GlobalTitleTranslator,
                             IWF_GTT_Callback_ITU, NULL) != ITS_SUCCESS)
    {
        DLOG_ERROR("Error adding SCCP GTT Callback...");
        ITS_GlobalStop();
        exit(0);
    }


    DLOG_DEBUG("Self SCCP address: Use configured value: %d",
            IwfController::Instance().Config().LocalConfig().SelfSccpAddress().IsUseFromConfig());

    DLOG_DEBUG("Self SCCP address: GT address digits: %s",
            IwfController::Instance().Config().LocalConfig().SelfSccpAddress().GtDigits().c_str());

    DLOG_DEBUG("Remote SCCP address: Use configured value: %d",
            IwfController::Instance().Config().LocalConfig().RemoteSccpAddress().IsUseFromConfig());

    DLOG_DEBUG("Remote SCCP address: GT address digits: %s",
            IwfController::Instance().Config().LocalConfig().RemoteSccpAddress().GtDigits().c_str());

#endif
#endif
    if(IwfController::Instance().Config().LocalConfig().IsClearSessionContextSet())
    {
        TransactionManager::Instance()->RestartSubscrAuditTimer();
    }

    //if (!itsDiaConfig.IsInterWorkingMode())
    //{
        /*Send update to Avamgr that IWF component is initialized. this has to be
         * done after all Diameter stack, Sigtran stack and IWF applicaion's config
         * fetch was successfully initialized */
        IwfController::Instance().UpdateIWFStatus(COMPONENT_STATUS_INITIALIZED);
    //}

    DLOG_DEBUG("--Exit SSGPreFunc--");

    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
extern "C" void
SSGPostFunc()
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("SSG Post Func Called...Exiting");

    gisShutdownInProgress = true;

    SendASPInactiveAndASPDown();

    //NOTE: To fix restart crash TransactionManager::Destroy() is commented
    //TransactionManager::Destroy();

    /*
     * Terminate the diameter stack
     */
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    if (diaFrame)
    {
        diaFrame->Terminate();
    }

    //NOTE: To fix restart crash _exit is moved before IwfController Destroy
    usleep(500000);
    _exit(0);

    /* Terminate the Transport Controller thread */
    iwf::IWFTransportController::SetExit(true);
    iwf::IWFTransportController::SetTransportStatus(IWF_DEACTIVATE_TRANSPORTS);

    IwfController::Destroy();

    ITS_GlobalStop();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  Notes: This function get's called after Initializing WorkerPool's
 *         Transport.
 *  See Also:
 *
 *  Revision History:
 *  ------------------------------------------------------------------------
 *  Name     Date         Reference      Description
 *  ------------------------------------------------------------------------
 ****************************************************************************/
extern "C" int
WPTQ_PostInitialize(ThreadPoolThread *thr, ITS_HANDLE hd)
{
    // Any objects to be initialized or instance id assignments to
    // to handlers.
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("WPTQ_PostInitialize:");
    cout << "WPTQ_PostInitialize:" << endl;
    return ITS_SUCCESS;
}
extern "C" void
WPTQ_PostTerminate(ThreadPoolThread *thr)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_CRITICAL("WPTQ_PostTerminate: Application Thread Exited Loop.");
}

extern "C" int
WPTQ_PostNextEvent(ThreadPoolThread *thr, its::Event &event)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("--Entry WPTQ_PostNextEvent--");
    ThreadManager::GetInstance()->MapEventToThread(event);
    DLOG_DEBUG("--Exit WPTQ_PostNextEvent--");
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  Revision History:
 *  ------------------------------------------------------------------------
 *  Name     Date         Reference      Description
 *  ------------------------------------------------------------------------
 ****************************************************************************/
#ifndef USE_ANSI_SCCP
#if 0
extern "C" void
SSG_GTT_Callback_ITU(ITS_POINTER object, ITS_POINTER userData,
                      ITS_POINTER callData)
{

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    SCCP_CALLBACK_DATA *cd = (SCCP_CALLBACK_DATA *)callData;

    DLOG_DEBUG("SSG_GTT_Callback_ITU:\n");

    if (!cd)
    {
        DLOG_ERROR("SSG_GTT_Callback: No CallData...\n");
        return;
    }

    ITS_INT opc = 0, dpc = 0;
    ITS_INT mapPc = 0;

    SCCP_ADDR* cgp = NULL;
    SCCP_ADDR* cdp = NULL;

    ITS_OCTET addrIndCalling = 0;
    ITS_UINT  pcCl = 0;
    ITS_OCTET ssnCl = 0;
    ITS_OCTET gttInfoCalling[SCCP_MAX_ADDR_LEN];
    ITS_USHORT gttLenCalling = 0;

    ITS_OCTET addrIndCalled = 0;
    ITS_UINT  pcCd = 0;
    ITS_OCTET ssnCd = 0;
    ITS_OCTET gttInfoCalled[SCCP_MAX_ADDR_LEN];
    ITS_USHORT gttLenCalled = 0;

    opc = MTP3_RL_GET_OPC_VALUE_CCITT(((MTP3_HEADER *)cd->mtp3)->label);
    dpc = MTP3_RL_GET_DPC_VALUE_CCITT(((MTP3_HEADER *)cd->mtp3)->label);

    DLOG_DEBUG("SSG_GTT_Callback: MTP3_RL OPC = 0x%02x\n", opc);
    DLOG_DEBUG("SSG_GTT_Callback: MTP3_RL DPC = 0x%02x\n", dpc);

    if (dpc == GetSsgConfiguration().GetGsmSsgPC())
    {
        mapPc = GetSsgConfiguration().GetGsmSsgPC();
    }

    for (int i=0; i < cd->ieCount; i++)
    {
        if (cd->ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            cdp = &(cd->ies[i].param_data.calledPartyAddr);
        }
        else if (cd->ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            cgp = &(cd->ies[i].param_data.callingPartyAddr);
        }
    }

    //Decode Calling Party Address
    if (SCCP_DecodeAddr_CCITT(cgp,
                              &addrIndCalling,
                              &pcCl,
                              &ssnCl,
                              gttInfoCalling, &gttLenCalling) != ITS_SUCCESS)
    {
        DLOG_ERROR("Couldn't decode CgPa\n");
        cd->transSuccess = ITS_FALSE;
        return;
    }

    //Decode Called Party Address
    if (SCCP_DecodeAddr_CCITT(cdp,
                              &addrIndCalled,
                              &pcCd,
                              &ssnCd,
                              gttInfoCalled, &gttLenCalled) != ITS_SUCCESS)
    {
        DLOG_ERROR("Couldn't decode CdPa\n");
        cd->transSuccess = ITS_FALSE;
        return;
    }

    //Modify Called Party Address to PC/SSN Based with our (SSG) PC/SSN
    ITS_OCTET addrInd = SCCP_CPA_HAS_SSN_CCITT   |
                        SCCP_CPA_HAS_PC_CCITT    |
                        SCCP_CPA_ROUTE_SSN;

    if (SCCP_EncodeAddr_CCITT(cd->translation,
                              addrInd,
                              mapPc,
                              ssnCd = GetSsgConfiguration().GetGsmSsgSSN(),
                              NULL, 0) != ITS_SUCCESS)
    {
        DLOG_ERROR("Encode Failure\n");
        cd->transSuccess = ITS_FALSE;
        return;
    }

    cd->dpc = dpc;
    cd->transSuccess = ITS_TRUE;

    DLOG_DEBUG("SSG_GTT_Callback: Modified CdPa: addrInd: 0x%02x, "
                     "pc: 0x%02x, ssn: 0x%02x\n", addrInd, mapPc, ssnCd);

    //Now Check if we need to Modify CgPa
    DLOG_DEBUG("CgPa Addr Ind : 0x%02x\n", addrIndCalling);

    if (((addrIndCalling & SCCP_CPA_GTTI_ALL) == SCCP_CPA_GTTI_ALL) ||
    ((addrIndCalling & SCCP_CPA_GTTI_TNE_CCITT) == SCCP_CPA_GTTI_TNE_CCITT) ||
    ((addrIndCalling & SCCP_CPA_GTTI_TRANS_CCITT) == SCCP_CPA_GTTI_TRANS_CCITT))
    {
        if (addrIndCalling & SCCP_CPA_HAS_PC_CCITT)
        {
            DLOG_DEBUG("SSG_GTT_Callback: CgPa Has PC = 0x%02x\n", pcCl);

            if (addrIndCalling & SCCP_CPA_HAS_SSN_CCITT)
            {
                DLOG_DEBUG("SSG_GTT_Callback: CgPa Has SSN = 0x%02x\n",
                                                                        ssnCl);
            }
            else
            {
                DLOG_DEBUG("SSG_GTT_Callback: CgPa Has No SSN\n");
                //Default Set it to HLR's SSN
                ssnCl = 5;
            }

            //CgPa although GTT Based has PC,
            //Change routing to be based on PC/SSN. Using the
            //retrieved PC/SSN
            if (SCCP_EncodeAddr_CCITT(cgp,
                                      addrInd,
                                      pcCl,
                                      ssnCl,
                                      NULL, 0) != ITS_SUCCESS)
            {
                DLOG_ERROR("Calling Party Encode Failure\n");

                return;
            }

            DLOG_DEBUG("SSG_GTT_Callback: Modified CgPa: addrInd: "
                             "0x%02x, pc: 0x%02x, ssn: 0x%02x\n",
                             addrInd, pcCl, ssnCl);
        }
    }

    //If MTP3 RL OPC and CgPa PC don't match,
    //change the OPC in the MTP3 RL to this OPC
    if (pcCl && opc != (int)pcCl)
    {
        DLOG_DEBUG("SSG_GTT_Callback: MTP3 OPC & CgPa PC different.. "
                         "Use CgPa PC\n");

        MTP3_RL_SET_OPC_VALUE_CCITT(((MTP3_HEADER *)cd->mtp3)->label, pcCl);

        DLOG_DEBUG("SSG_GTT_Callback: Modified OPC 0x%02x in RL\n", pcCl);
    }

    return;
}
#endif
#endif
/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  Revision History:
 *  ------------------------------------------------------------------------
 *  Name     Date         Reference      Description
 *  ------------------------------------------------------------------------
 ****************************************************************************/
#ifndef USE_ANSI_SCCP
#if 1
extern "C" void
IWF_GTT_Callback_ITU(ITS_POINTER object, ITS_POINTER userData,
                      ITS_POINTER callData)
{

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    SCCP_CALLBACK_DATA *cd = (SCCP_CALLBACK_DATA *)callData;

    DLOG_DEBUG("IWF_GTT_Callback_ITU:\n");

    if (!cd)
    {
        DLOG_ERROR("IWF_GTT_Callback: No CallData...\n");
        return;
    }

    ITS_INT opc = 0, dpc = 0;

    SCCP_ADDR* cgp = NULL;
    SCCP_ADDR* cdp = NULL;

    ITS_OCTET addrIndCalling = 0;
    ITS_UINT  pcCl = 0;
    ITS_OCTET ssnCl = 0;
    ITS_OCTET gttInfoCalling[SCCP_MAX_ADDR_LEN];
    ITS_USHORT gttLenCalling = 0;

    ITS_OCTET addrIndCalled = 0;
    ITS_UINT  pcCd = 0;
    ITS_OCTET ssnCd = 0;
    ITS_OCTET gttInfoCalled[SCCP_MAX_ADDR_LEN];
    ITS_USHORT gttLenCalled = 0;

    opc = MTP3_RL_GET_OPC_VALUE_CCITT(((MTP3_HEADER *)cd->mtp3)->label);
    dpc = MTP3_RL_GET_DPC_VALUE_CCITT(((MTP3_HEADER *)cd->mtp3)->label);

    DLOG_DEBUG("IWF_GTT_Callback: MTP3_RL OPC = 0x%02x\n", opc);
    DLOG_DEBUG("IWF_GTT_Callback: MTP3_RL DPC = 0x%02x\n", dpc);

    for (int i=0; i < cd->ieCount; i++)
    {
        if (cd->ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            cdp = &(cd->ies[i].param_data.calledPartyAddr);
        }
        else if (cd->ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            cgp = &(cd->ies[i].param_data.callingPartyAddr);
        }
    }

    //Decode Calling Party Address
    if (SCCP_DecodeAddr_CCITT(cgp,
                              &addrIndCalling,
                              &pcCl,
                              &ssnCl,
                              gttInfoCalling, &gttLenCalling) != ITS_SUCCESS)
    {
        DLOG_ERROR("Calling Party Decode Failure");
        cd->transSuccess = ITS_FALSE;
        return;
    }


    // The following if-block is executed only if the Remote SCCP address has to be used from configuration (iwf.json).
    // If IsUseFromConfig() is set to false, whatever is sent by the remote side, is used.
    // Currently, the configuration only supports GT address digits.
    if (IwfController::Instance().Config().LocalConfig().RemoteSccpAddress().IsUseFromConfig())
    {
        std::string remoteGtDigits = IwfController::Instance().Config().LocalConfig().RemoteSccpAddress().GtDigits();
        DLOG_DEBUG("Using Remote SCCP GT address digits from configuration: %s", remoteGtDigits.c_str());

        // The new GT address digits, length, and ES (for GTI 0011 or 0100) (for BCD O/E encoding) or O/E (for GTI 0001)
        // have to encoded in the GTT Calling Info
        int start = DetermineStartOctetNumForGttAddrDgts(addrIndCalling, gttInfoCalling, remoteGtDigits);
        memset(&gttInfoCalling[start], 0, (gttLenCalling - start));

        ITS_OCTET remoteGtDigitOctects[SCCP_MAX_ADDR_LEN];
        int lenRemoteGtDigits = IWFUtils::StringToTBCD(remoteGtDigits, remoteGtDigitOctects, SCCP_MAX_ADDR_LEN);

        memcpy(&gttInfoCalling[start], remoteGtDigitOctects, lenRemoteGtDigits);
        gttLenCalling = start + lenRemoteGtDigits;

        //Encode Calling Party Address
        if (SCCP_EncodeAddr_CCITT(cgp,
                                addrIndCalling,
                                pcCl,
                                ssnCl,
                                gttInfoCalling, gttLenCalling) != ITS_SUCCESS)
        {
            DLOG_ERROR("Calling Party Encode Failure");
            cd->transSuccess = ITS_FALSE;
            return;
        }
    }

    //Decode Called Party Address
    if (SCCP_DecodeAddr_CCITT(cdp,
                              &addrIndCalled,
                              &pcCd,
                              &ssnCd,
                              gttInfoCalled, &gttLenCalled) != ITS_SUCCESS)
    {
        DLOG_ERROR("Called Party Decode Failure");
        cd->transSuccess = ITS_FALSE;
        return;
    }

    // The following if-block is executed only if the Self SCCP address has to be used from configuration (iwf.json).
    // If IsUseFromConfig() is set to false, whatever is sent by the remote side, is used.
    // Currently, the configuration only supports GT address digits.
    if (IwfController::Instance().Config().LocalConfig().SelfSccpAddress().IsUseFromConfig())
    {
        ITS_OCTET gTi;
        if(!SetGlobalTitleAddress(gttInfoCalled, &gTi))
        {
            /* Setting the gTi Type over the incoming GTI bits */
            addrIndCalled = ((addrIndCalled & 0xc3) | gTi);
        }
        std::string selfGtDigits = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().GtDigits();
        DLOG_DEBUG("Using Self SCCP GT address digits from configuration: %s", selfGtDigits.c_str());

        // The new GT address digits, length, and ES (for GTI 0011 or 0100) (for BCD O/E encoding) or O/E (for GTI 0001)
        // have to encoded in the GTT Called Info
        int start = DetermineStartOctetNumForGttAddrDgts(addrIndCalled, gttInfoCalled, selfGtDigits);
        memset(&gttInfoCalled[start], 0, (gttLenCalled - start));

        ITS_OCTET selfGtDigitOctects[SCCP_MAX_ADDR_LEN];
        int lenSelfGtDigits = IWFUtils::StringToTBCD(selfGtDigits, selfGtDigitOctects, SCCP_MAX_ADDR_LEN);

        memcpy(&gttInfoCalled[start], selfGtDigitOctects, lenSelfGtDigits);
        gttLenCalled = start + lenSelfGtDigits;
    }

    //Encode Called Party Address
    if (SCCP_EncodeAddr_CCITT(cd->translation,
                              addrIndCalled,
                              pcCd,
                              ssnCd,
                              gttInfoCalled, gttLenCalled) != ITS_SUCCESS)
    {
        DLOG_ERROR("Called Party Encode Failure");
        cd->transSuccess = ITS_FALSE;
        return;
    }

    //If MTP3 RL OPC and CgPa PC don't match,
    //change the OPC in the MTP3 RL to this OPC
    if (pcCl && opc != (int)pcCl)
    {
        DLOG_DEBUG("IWF_GTT_Callback: MTP3 OPC & CgPa PC different.. "
                         "Use CgPa PC\n");

        MTP3_RL_SET_OPC_VALUE_CCITT(((MTP3_HEADER *)cd->mtp3)->label, pcCl);

        DLOG_DEBUG("IWF_GTT_Callback: Modified OPC 0x%02x in RL\n", pcCl);
    }


    //If MTP3 RL DPC and CdPa PC don't match,
    //change the DPC in the MTP3 RL to this DPC
    if (pcCd && dpc != (int)pcCd)
    {
        DLOG_DEBUG("IWF_GTT_Callback: MTP3 DPC & CdPa PC different.. "
                         "Use CdPa PC\n");

        MTP3_RL_SET_DPC_VALUE_CCITT(((MTP3_HEADER *)cd->mtp3)->label, pcCd);

        dpc = pcCd;

        DLOG_DEBUG("IWF_GTT_Callback: Modified DPC 0x%02x in RL\n", pcCd);
    }

    cd->dpc = dpc;
    cd->transSuccess = ITS_TRUE;

    return;
}


    extern "C" void
IWF_SCTP_ASPIdRegistration_Callback(ITS_POINTER object, ITS_POINTER userData,
        ITS_POINTER callData)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IWF_SCTP_ASPIdRegistration_Callback : entry");
    int ret = ITS_SUCCESS;
    SCTP_API_MSG_HDR* msg = (SCTP_API_MSG_HDR*)callData;
    struct sockaddr_in remoteAddr;
    struct AspIdRoutingKeyConfigData aspIdRkInfo;

    if(UAL_GL_ITW_MODE != UAL_ITW_SG && UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE))
    {
        memcpy(&remoteAddr, msg->name, msg->nameLen);
        memset(&aspIdRkInfo, 0, sizeof aspIdRkInfo);
        aspIdRkInfo.port = ntohs(remoteAddr.sin_port);
        strcpy(aspIdRkInfo.remoteIp, inet_ntoa(remoteAddr.sin_addr));

        if(IwfController::Instance().Config().LocalConfig().GetRoutingKeyInfofromMap(aspIdRkInfo.remoteIp,
                    aspIdRkInfo.port, aspIdRkInfo.routingKey, aspIdRkInfo.homeIp))
        {
            DLOG_DEBUG("Successfully found the RoutingKey info for transport %s - %d",aspIdRkInfo.remoteIp, aspIdRkInfo.port);
        }
        else
        {
            DLOG_ERROR("Not able to find the RoutingKey info for transport %s - %d",aspIdRkInfo.remoteIp, aspIdRkInfo.port);
        }

        if(aspIdRkInfo.routingKey)
        {
            CreateApplicationServerProcess(aspIdRkInfo.routingKey, ++localaspId, aspIdRkInfo.homeIp);
        }
    }
    DLOG_DEBUG("IWF_SCTP_ASPIdRegistration_Callback: exit");
}

    extern "C" void
IWF_SCTP_Callback_ITU(ITS_POINTER object, ITS_POINTER userData,
        ITS_POINTER callData)
{

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IWF_SCTP_Callback_ITU : entry");
    int ret = ITS_SUCCESS;
    CLOG_DEBUG("GetBulkFetchSuccess %d",IwfController::Instance().GetIsBulkFetchSuccess());

    if ((eAccelero::MESS_ISActiveInst(MeSS::MeSSObj().Self().instance)))
    {
        if(IwfController::Instance().GetIsBulkFetchSuccess())
        {
            StoreASPActiveConfigData *storeASPActiveData = (StoreASPActiveConfigData *)callData;

            ret = UAL_SendASP_ACTIVE(storeASPActiveData->rKey, storeASPActiveData->rKeyLen,storeASPActiveData->aspRec,
                    storeASPActiveData->mode, storeASPActiveData->flag);
            if (ret != ITS_SUCCESS)
            {
                DLOG_ERROR("IWF_SCTP_Callback_ITU : Could not send "
                        "ASP Active, code %d.\n", ret);

                return;
            }
            DLOG_DEBUG("Successfully sent ASP Active Message");
        }
        else
        {
            DLOG_ERROR("Bulk Fetch not happened... Hence not triggering ASP Active");
        }
    }
    else
    {
        if (IwfController::Instance().Config().LocalConfig().IsSendASPActiveFromStandBySet())
        {
            StoreASPActiveConfigData *storeASPActiveData = (StoreASPActiveConfigData *)callData;

            ret = UAL_SendASP_ACTIVE(storeASPActiveData->rKey, storeASPActiveData->rKeyLen,storeASPActiveData->aspRec,
                    storeASPActiveData->mode, storeASPActiveData->flag);
            if (ret != ITS_SUCCESS)
            {
                DLOG_ERROR("IWF_SCTP_Callback_ITU : Could not send "
                        "ASP Active, code %d.\n", ret);

                return;
            }
            DLOG_DEBUG("Successfully sent ASP Active Message");
        }
        else
        {
            DLOG_DEBUG("IWF_SCTP_Callback_ITU: Configuration Option to send ASPActive is not Enabled, no ASP Active is sent");
        }
    }
    DLOG_DEBUG("IWF_SCTP_Callback_ITU : exit");
    isASPUp = true;
}
#endif
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
ITS_INT CnvPCtoStr(std::string str, std::string& opBuf)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    char *pcStr = (char *)str.c_str() ;
    ITS_UINT val = 0;
    ITS_UINT output = 0;
    char tempbuf[20] ;

    switch(*pcStr)
    {
       case 'P' :
       case 'p' :
       {
           pcStr++;
           if (*pcStr == 'C' || *pcStr == 'c')
           {
              pcStr++;
              while (pcStr)
              {
                  if (*pcStr >= '0' && *pcStr <= '9')
                  {
                      val = (val * 10) + (*pcStr - '0');

                      if(val >255)
                      {
                         output = 0 ;
                         break ;
                      }
                  }
                  else if (*pcStr == '-')
                  {
                      output = (output << 8) | val;
                      val = 0;
                  }
                  else
                  {
                      break;
                  }
                  pcStr++;
              }
           }
           else
           {
               DLOG_ERROR("INVALID PC FORMAT");
               return !ITS_SUCCESS ;
           }
           if ( *pcStr == '\0')
           {
               output = (output << 8) | val;
           }
           snprintf(tempbuf, 20, "%d", output);
           opBuf = tempbuf ;

           break ;
       }
       case 'e' :
       case 'E' :
       {
           pcStr++;
           opBuf = pcStr ;
           break ;
       }
       default :
       {
           return ITS_ENOTFOUND ;
       }
    }
    return ITS_SUCCESS;
}

int SetGlobalTitleAddress(ITS_OCTET *gttInfo, ITS_OCTET *gTi)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    ITS_OCTET l_addInd = 0;
    ITS_OCTET l_tranType = 0;
    ITS_OCTET l_encScheme = 0;
    ITS_OCTET l_numPlan = 0;
    memset(&gttInfo[0], 0, 3);
    /* Storing the GT Type */
    *gTi = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().GTI();
    switch(*gTi)
    {
        case ITU_SCCP_GTI_001:
            {
                l_addInd = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().AddressIndicator();
                /* Encoding the Nature Of Address Indicator for GT Type 1 */
                gttInfo[0] = (l_addInd & 0x7f);
                break;
            }
        case ITU_SCCP_GTI_002:
            {
                l_tranType = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().TranslationType();
                /* Encoding the Translation Type for GT Type 1 */
                gttInfo[0] = l_tranType;
                break;
            }
        case ITU_SCCP_GTI_003:
            {
                l_tranType = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().TranslationType();
                l_numPlan = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().NumberingPlan();
                l_encScheme = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().EncodingScheme();

                /* Encoding the Translation Type in first Octet
                 * Encoding the Numbering Plan in Higher Nibble of Second Octet
                 * and Encoding Scheme in lower nibble */

                gttInfo[0] = l_tranType;
                gttInfo[1] = (l_numPlan & 0xf) << 4;
                gttInfo[1] |= (l_encScheme & 0xf);

                break;
            }
        case ITU_SCCP_GTI_004:
            {
                l_tranType = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().TranslationType();
                l_numPlan = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().NumberingPlan();
                l_encScheme = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().EncodingScheme();
                l_addInd = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().AddressIndicator();

                /* Encoding the Translation Type in first Octet
                 * Encoding the Numbering Plan in Higher Nibble of Second Octet
                 * and Encoding Scheme in lower nibble
                 * Encoding Nature of Address Indicator in third Octet*/

                gttInfo[0] = l_tranType;
                gttInfo[1] = (l_numPlan & 0x0f) << 4;
                gttInfo[1] |= (l_encScheme & 0xf);
                gttInfo[2] = (l_addInd & 0x7f);
                break;
            }
        default:
            {
                DLOG_ERROR("Unknown GTI received");
                return !ITS_SUCCESS;
            }
    }
    /* Shifting thr gTi bits by 2 so that it will be in sync with the position
     * of the incoming Address Indicator bits */

    *gTi = (*gTi << 2);
    return ITS_SUCCESS;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Determine the start octet number for the GT address digits.
 *
 *      Depending on the GTI (Global Title Indicator), encode the ES
 *      (Encoding Scheme) (for GTO 0011 and 0100) or O/E indicator
 *      (GTI 0001) appropriately.
 *
 *  Input Parameters:
 *      addrInd         - GT (Global Title) address indicator.
 *      gttAddrDgtsNew  - New GT address digits.
 *
 *  Input/Output Parameters:
 *      gttInfo - GT information.
 *
 *  Output Parameters:
 *      Start octet number for the GT address digits.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int DetermineStartOctetNumForGttAddrDgts(ITS_OCTET addrInd, ITS_OCTET *gttInfo, std::string gttAddrDgtsNew)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int start = -1;

    ITS_BOOLEAN eFlagNew = ITS_FALSE;

    if (gttAddrDgtsNew.length() % 2 == 0)
    {
        eFlagNew = ITS_TRUE;
    }

    if ((addrInd & SCCP_CPA_GTTI_ALL) == SCCP_CPA_GTTI_ALL)
    {
        DLOG_DEBUG("Received GTT address indicator is SCCP_CPA_GTTI_ALL");

        if ((gttInfo && (gttInfo[1] & 0x01)) || (gttInfo && (gttInfo[1] & 0x02)))
        {
            if (eFlagNew)
            {
                gttInfo[1] &= (~0x01);  //unset bit 1, just in case the number of address digits was Odd before
                gttInfo[1] |= 0x02;     //set bit 2
            }
            else
            {
                gttInfo[1] &= (~0x02);  //unset bit 2, just in case the number of address digits was Even before
                gttInfo[1] |= 0x01;     //set bit 1
            }
        }

        start = 3;
    }
    else if ((addrInd & SCCP_CPA_GTTI_TNE) == SCCP_CPA_GTTI_TNE)
    {
        DLOG_DEBUG("Received GTT address indicator is SCCP_CPA_GTTI_TNE");

        if ((gttInfo && (gttInfo[1] & 0x01)) || (gttInfo && (gttInfo[1] & 0x02)))
        {
            if (eFlagNew)
            {
                gttInfo[1] &= (~0x01);  //unset bit 1
                gttInfo[1] |= 0x02;     //set bit 2
            }
            else
            {
                gttInfo[1] &= (~0x02);  //unset bit 2
                gttInfo[1] |= 0x01;     //set bit 1
            }
        }

        start = 2;
    }
    else if ((addrInd & SCCP_CPA_GTTI_TRANS) == SCCP_CPA_GTTI_TRANS)
    {
        DLOG_DEBUG("Received GTT address indicator is SCCP_CPA_GTTI_TRANS");

        start = 1;
    }
    else if ((addrInd & SCCP_CPA_GTTI_NATURE) == SCCP_CPA_GTTI_NATURE)
    {
        DLOG_DEBUG("Received GTT address indicator is SCCP_CPA_GTTI_NATURE");

        if (gttInfo)
        {
            if (eFlagNew)
            {
                gttInfo[0] |= 0x00;
            }
            else
            {
                gttInfo[0] |= 0x80;
            }
        }

        start = 1;
    }
    else
    {
        DLOG_ERROR("Received GTT address indicator is INVALID!!!");
    }

    return start;
}

void UalTransCallback(ITS_POINTER object,
                      ITS_POINTER userData,
                      ITS_POINTER callData)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    switch (UAL_CB_CTXT_TYPE(callData))
    {
        case UAL_CB_ASP_CTXT:
            // can be used to create application alarms.
            switch (UAL_CB_CTXT_ASP_STATE(callData))
            {
                case UAL_ASP_UP:
                    DLOG_DEBUG("ASP-UP Indication is received");
                    break;

                case UAL_ASP_ACTIVE:
                    DLOG_DEBUG("ASP-ACTIVE Indication is received");
                    break;

                case UAL_ASP_INACTIVE:
                case UAL_ASP_DOWN:
                    DLOG_DEBUG("ASP-INACTIVE/DOWN Indication is received");
                    break;

                case UAL_ASP_CANT_START:
                    DLOG_DEBUG("ASP Can't Start Indication is received");
                    break;

                default:
                    DLOG_DEBUG("ASP Invalid Indication is received");
                    break;
            }
            break;

        // Application can just rely on AS states. If AS is not active
        // then mostly far end is going to drop the messages.
        case UAL_CB_AS_CTXT:
            switch (UAL_CB_CTXT_AS_STATE(callData))
            {
                case UAL_AS_DOWN:
                    DLOG_DEBUG("AS-DOWN Indication is received");
                    break;

                case UAL_AS_ACTIVE:
                    DLOG_DEBUG("AS-ACTIVE Indication is received");
                    break;

                case UAL_AS_INACTIVE:
                    DLOG_DEBUG("AS-INACTIVE Indication is received");
                    break;

                default:
                    DLOG_DEBUG("AS Invalid Indication is received");
                    break;
            }
            break;

        default:
            break;
    }
}
