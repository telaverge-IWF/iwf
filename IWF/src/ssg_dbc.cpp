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
 *  ID: $Id: ssg_dbc.cpp,v 1.1.1.1.2.1.2.1.2.1.4.1.4.1.2.2 2015/01/13 07:02:00 mhimanshu Exp $
 *
 *  LOG: $Log: ssg_dbc.cpp,v $
 *  LOG: Revision 1.1.1.1.2.1.2.1.2.1.4.1.4.1.2.2  2015/01/13 07:02:00  mhimanshu
 *  LOG: Fix for Bug 5921 and resetDiaIntStats command implementaion at MML.
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1.2.1.2.1.4.1.4.1.2.1  2014/12/03 09:26:18  mhimanshu
 *  LOG: stats implementation at MML - diaS6aStats and activeSubscribers
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1.2.1.2.1.4.1.4.1  2014/09/16 09:54:32  jsarvesh
 *  LOG: Changes done for Peer wise Statistics enhancement
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1.2.1.2.1.4.1  2014/06/25 04:36:18  jkchaitanya
 *  LOG: changes for warnings removal in IWF application code
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1.2.1.2.1  2013/12/31 04:40:41  millayaraja
 *  LOG: merged code from B-IWF-0100-01 to B-IWF-0100-02 with GTT support
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1.2.1  2013/10/04 13:43:07  millayaraja
 *  LOG: changes for RHEL machine dependent compilation flags and dependencies in IWF code
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1  2013/06/19 12:39:42  jsarvesh
 *  LOG: MML implementation for IWF Statistics
 *  LOG:
 *  LOG: Revision 1.1.1.1  2013/01/09 16:41:36  brajappa
 *  LOG: Initial import
 *  LOG:
 *  LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 *  LOG: Initial Draft for SSG
 *  LOG:
 *  LOG:
 ****************************************************************************/
#ident "$Id: ssg_dbc.cpp,v 1.1.1.1.2.1.2.1.2.1.4.1.4.1.2.2 2015/01/13 07:02:00 mhimanshu Exp $"

#include <its++.h>
#include <engine++.h>
#include <its_route.h>
#include <its_thread_pool.h>
#include <its_support_exception.h>

#include <string>
#include <dia_stats.h>
#include <dia_mgmt.h>
#include <dia_frame.h>

#include <dia_trace.h>
#include <dcca_api.h>

#include <ssg_dbc.h>
#include <ssg_defines.h>
#include <ssg_statistics.h>
#include "PluginObj.h"
#include <DiameterDictionary.h>
#include <DictionaryTable.h>
#include "DiameterDictionaryStats.h"
#include "iwf.h"
//#include <ssg_transaction_table.h>

#if defined(ITS_STD_NAMESPACE)
#ifdef GCC_LESS_THAN_4_3
//using namespace std::tr1;
using namespace std;
#else
using namespace std;
#endif
using namespace its;
using namespace engine;
using namespace diameter;
#endif
extern void PrintMAPStatistics(std::ostream&);

#define MAX_CMD_LINE_LEN 1000
#define MAX_MML_CMD_LEN 20
#define MAX_PC_PROT_LEN 150

extern SsgStackStatistics mapStats;

/*.implementation:
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
 *  ---------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *****************************************************************************/
    void
SsgDbcServer::DoCommand(istream& commandLine)
{

    DiaMgmt *diaMgmt = DiaMgmt::GetDiaMgmt();
    string dummy;

    ITS_C_ASSERT(dbc != NULL);

    if (Cmd("disTraces", "Disable ALL MAP stack Tracing"))
    {
        engine::AppDebugTrace->Disable();
        engine::AppWarningTrace->Disable();
        engine::AppErrorTrace->Disable();
        engine::AppCriticalTrace->Disable();
    }
    else if (Cmd("enTraces", "Enable ALL MAP stack Tracing"))
    {
        engine::AppDebugTrace->Enable();
        engine::AppWarningTrace->Enable();
        engine::AppErrorTrace->Enable();
        engine::AppCriticalTrace->Enable();
    }
    else if (Cmd("enCriticalTraces", "Enable MAP stack Critical Traces"))
    {
        engine::AppCriticalTrace->Enable();
    }
    else if (Cmd("enErrorTraces", "Enable MAP stack Error Traces"))
    {
        engine::AppErrorTrace->Enable();
    }
    else if (Cmd("enWarningTraces", "Enable MAP stack Error Traces"))
    {
        engine::AppWarningTrace->Enable();
    }
    else if (Cmd("enDebugTraces", "Enable MAP stack Error Traces"))
    {
        engine::AppDebugTrace->Enable();
    }
    else if (Cmd("disCriticalTraces", "Disable MAP stack Critical Traces"))
    {
        engine::AppCriticalTrace->Disable();
    }
    else if (Cmd("disErrorTraces", "Disable MAP stack Error Traces"))
    {
        engine::AppErrorTrace->Disable();
    }
    else if (Cmd("disWarningTraces", "Disable MAP stack Warning Traces"))
    {
        engine::AppWarningTrace->Disable();
    }
    else if (Cmd("disDebugTraces", "Disable MAP stack Debug Traces"))
    {
        engine::AppDebugTrace->Disable();
    }
    else if (Cmd("stats", "Get  Gsm Ssg Statistics"))
    {
        mapStats.Print(oss);
    }
    else if (Cmd("resetStats", "Reset  Gsm Ssg Statistics"))
    {
        mapStats.ResetAll();
    }
    else if (Cmd("enStatistics", "Enable Dia Stack Statistics "))
    {
        diaMgmt->EnableStatistics();
    }
    else if (Cmd("disStatistics", "Disable Dia Stack Statistics "))
    {
        diaMgmt->DisableStatistics();
    }
    else if (Cmd("isStatsEnabled", "Is Dia Stack Statistics Enabled"))
    {
        if(diaMgmt->IsStatsEnabled())
        {
            oss<<" ********Statistics Enabled ********";
        }
        else
        {
            oss<<" ******** Statistics Disabled ********";
        }
    }
    else if (Cmd("getStackStats", "Display Dia Stack statistics"))
    {
        diaMgmt->GetDiaStackStats(oss);
    }
    else if (Cmd("getDiaSesionStats", "Display Dia Session command statistics"))
    {
        diaMgmt->GetDiaSessionStats(oss);
    }
    else if (Cmd("getDiaPeerStats", "Display DiaPeer based message statistics"))
    {
        diaMgmt->GetDiaPeerStats(oss);
    }
    else if (Cmd("getDiaMiscStats", "Display Miscellaneous Stats"))
    {
        diaMgmt->GetDiaMiscStats(oss);
    }
    else if (Cmd("resetStackStats", "Reset Dia statistics Info"))
    {
        diaMgmt->ResetStackStats();
    }
    else if (Cmd("printPeerTable","Prints Peer Table "))
    {
        diaMgmt->PrintPeerTable(oss);
        diaMgmt->PrintPeerTable(cout);
    }
    else if (Cmd("printRealmTable","Prints Realm Table "))
    {
        diaMgmt->PrintRealmTable(oss);
        diaMgmt->PrintRealmTable(cout);
    }
    else if (Cmd("qCount", "Prints Diameter Q Count "))
    {
        oss << "Diameter Stack Q Count = " << DiaStackClass::GetDiaStackQCount() << endl;
    }
    else if (Cmd("printSessionTable", "Prints Session Table "))
    {
        diaMgmt->PrintSessionTable(oss);
    }
    else if (Cmd("downStreamQCount", "Prints Diameter DownStream Q Count "))
    {
        ITS_INT count;
        if ((count = DiaStackClass::GetDiaStackSenderQCount()) >= 0)
        {
            oss << "Diameter Stack DownStream Q Count = "
                << count << endl;
        }
        else
        {
            oss << "Diameter Stack DownStream Q Not Initialized"
                << endl;
        }
    }
    else if (Cmd("stSize", "Prints Diameter Session Table Size "))
    {
        oss << "Diameter Session Table Size = "
            << diaMgmt->GetSessionTableSize() << endl;
    }

    /*else if (Cmd("enTrace", "Enable All Traces"))
      {
      EnableAPPTracing();
      DiaTrace::GetDiaTrace()->Enable();
      DCCAApi::EnableDccaTrace();
      oss <<"*****All the traces are enabled*****" << endl;
      }
      else if (Cmd("disTrace", "Disable All Traces"))
      {
      DisableAPPTracing();
      DiaTrace::GetDiaTrace()->Disable();
      DCCAApi::DisableDccaTrace();
      oss <<"*****All the traces are disabled*****" << endl;
      }
      else if (Cmd("tps", "TPS"))
      {
      APPStats::GetAPPStats()->CalcTPS(oss);
      }*/
    else if (Cmd("enDiaTrace", "Enable All Dia Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable();
        oss <<"*******All Diameter Traces are enabled*******" << endl;
    }
    else if (Cmd("disDiaTrace", "Disable All Dia Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable();
        oss <<"*******All Diameter Traces are disabled*******" << endl;
    }
    else if (Cmd("enDiaDebTrace", "Enable Dia Debug Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_DEBUG);
        oss <<"*******Diameter Debug Traces are enabled*******" << endl;
    }
    else if (Cmd("enDiaErrTrace", "Enable Dia Error Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_ERROR);
        oss <<"*******Diameter Error Traces are enabled*******" << endl;
    }
    else if (Cmd("enDiaWarnTrace", "Enable Dia Warning Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_WARNING);
        oss <<"*******Diameter Warning Traces are enabled*******" << endl;
    }
    else if (Cmd("enDiaCritTrace", "Enable Dia Critical Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_CRITICAL);
        oss <<"*******Diameter Critical Traces are enabled*******" << endl;
    }
    else if (Cmd("disDiaDebTrace", "Disable Dia Debug Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable(DIA_DEBUG);
        oss <<"*******Diameter Debug Traces are disabled*******" << endl;
    }
    else if (Cmd("disDiaErrTrace", "Disable Dia Error Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable(DIA_ERROR);
        oss <<"*******Diameter Error Traces are disabled*******" << endl;
    }
    else if (Cmd("disDiaCritTrace", "Disable Dia Critical Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable(DIA_CRITICAL);
        oss <<"*******Diameter Critical Traces are disabled*******" << endl;
    }
    else if (Cmd("disDiaWarnTrace", "Disable Dia Warning Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable(DIA_WARNING);
        oss <<"*******Diameter Warning Traces are disabled*******" << endl;
    }
    else if (Cmd("DisplayDiaTrace", "Display Dia Tracing Info"))
    {
        DiaTrace::GetDiaTrace()->Display(oss);
    }
    /*else if (Cmd("di", "Hex Dump Injector", "TransportInstance"))
      {
      ITS_UINT inst;
      commandLine >> dummy >> inst;
      InjectDump(inst);
      }*/
    else if (Cmd("PrintDccaStats", "Show DCCA Statistics"))
    {
        DCCAApi::PrintDccaStats(oss);
    }
    else if (Cmd("ClearDccaStats", "Clear DCCA Statistics"))
    {
        DCCAApi::ClearDccaStats();
        oss <<"********DCCA Statistics are cleared**********" << endl;
    }
    else if (Cmd("enDccaTrace", "Enable DCCA Traces"))
    {
        DCCAApi::EnableDccaTrace();
        oss <<"********DCCA Traces are Enabled**********" << endl;
    }
    else if (Cmd("disDccaTrace", "Disable DCCA Traces"))
    {
        DCCAApi::DisableDccaTrace();
        oss <<"********DCCA Traces are Disabled**********" << endl;
    }
    else if (Cmd("getTx", "Get the Tx Timer Value "))
    {
        ITS_UINT val = DCCAApi::GetTxTimer();
        oss << "***Tx Timer Present Value is:" << val<<"Seconds***" <<endl;
    }
    else if (Cmd("setTx", "Change the Tx Timer Value "))
    {
        ITS_UINT old = DCCAApi::GetTxTimer();
        std::string val   = "";
        std::string dummy = "";
        commandLine >> dummy >> val;
        ITS_UINT timerValue = (atoi(val.c_str()));
        DCCAApi::SetTxTimer(timerValue);
        oss << "***Tx Timer Value changed from:" << old
            << "Seconds To:" <<timerValue<<"Seconds.***" << endl;
    }
    else if (Cmd("getTcc", "Get the Tcc Timer Value "))
    {
        ITS_UINT val = DCCAApi::GetTccTimer();
        oss << "***Tcc Timer Present Value is:" << val<<"Seconds***" <<endl;
    }
    else if (Cmd("setTcc", "Change the Tcc Timer Value "))
    {
        ITS_UINT old = DCCAApi::GetTccTimer();
        std::string val   = "";
        std::string dummy = "";
        commandLine >> dummy >> val;
        ITS_UINT timerValue = (atoi(val.c_str()));
        DCCAApi::SetTccTimer(timerValue);
        oss << "***Tcc Timer Value changed from:" << old
            << "Seconds To:" <<timerValue<<"Seconds.***" << endl;
    }
    else if (Cmd("getRoStats", "Get the ROR10TSL Interface specific Stats"))
    {
        ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
        char tbuf[ITS_PATH_MAX];
        time_t local;

        time(&local);
#if defined (__SUNPRO_CC)
        ctime_r(&local, tbuf, ITS_PATH_MAX);
#else
        ctime_r(&local, tbuf);
#endif
        DiameterDictionaryRef dictRef;
        try
        {
            dictRef = DiaStackClass::GetDictionaryTable().fetchDictionaryObject((unsigned int)25); // Ro_r10_tsl
        }
        catch(eAccelero::PluginException &e)
        {
            DLOG_ERROR(" DictionaryID not found PluginException:: %s",e.what());
        }
        catch(...)
        {
            DLOG_ERROR(" General exception");
        }
        if(dictRef)
        {
            eAccelero::MsgStatsCounter collatedCounter;
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it = dictRef->DictStatsMap.begin();
            std::string dictionaryName = dictRef->getDictionaryName();

            oss << "------------------------------------------------------------------------------------"
                << endl;    oss << "-- Dia ROR10TSL Interface Stats -- at " << tbuf;
            oss << "------------------------------------------------------------------------------------"
                << endl;
            oss <<"    Message           : ReqIn   | ReqOut | AnsIn  | AnsOut |  Error  |  InvalidMsg  |"
                <<endl;
            oss << "------------------------------------------------------------------------------------"
                << endl;

            for( ; it != dictRef->DictStatsMap.end() ; it++)
            {
                unsigned int cmdCode = it->first;
                collatedCounter = collateMsgStatsCounter(it->second->MsgStats);
                switch(cmdCode)
                {
                    case 272:
                        {
                            oss << "    CCR/CCA           : "<<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetRxRspCount()<< "|"
                                <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"
                                <<setw(8)<<collateStats(it->second->ErrorStats)<<"|"
                                <<setw(8)<<collateStats(it->second->InvalidMsgs)<<"|"<<endl;
                            break;
                        }
                    case 258:
                        {
                            oss << "    Re-Auth           : "<<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetRxRspCount()<< "|"
                                <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"
                                <<setw(8)<<collateStats(it->second->ErrorStats)<<"|"
                                <<setw(8)<<collateStats(it->second->InvalidMsgs)<<"|"<<endl;
                        }
                }
            }
            oss << "------------------------------------------------------------------------------------"
                << endl;
        }
        else
        {
            oss << "No Peer is configured with Ro dictionary." << endl;
        }
    }
    else if(Cmd("resetDiaIntStats","To reset diameter interface statistics"))
    {
        {
            unsigned int dictId[] = {22,25}; // Ro_r10 and Ro_r10_tsl
            unsigned int commandCode[] = {272,258};
            for(int dictIndex = 0; dictIndex < sizeof(dictId)/sizeof(dictId[0]); dictIndex++)
            {
                for(int index = 0; index < sizeof(commandCode)/sizeof(commandCode[0]); index++)
                {
                    DIA_RESET_INTERFACE_TOTAL_MSGS(dictId[dictIndex],commandCode[index]);
                    DIA_RESET_INTERFACE_ERROR_MSG_COUNT(dictId[dictIndex],commandCode[index]);
                    DIA_RESETT_INTERFACE_INVALID_MSG_COUNT(dictId[dictIndex],commandCode[index]);
                }
            }
        }
        {
            unsigned int dictId[] = {6,7,18}; // S6a_r8, S6a_r10 and S6a_r11
            unsigned int commandCode[] = {316,317,318,319,320,321,322,323};
            for(int dictIndex = 0; dictIndex < sizeof(dictId)/sizeof(dictId[0]); dictIndex++)
            {
                for(int index = 0; index < sizeof(commandCode)/sizeof(commandCode[0]); index++)
                {
                    DIA_RESET_INTERFACE_TOTAL_MSGS(dictId[dictIndex],commandCode[index]);
                    DIA_RESET_INTERFACE_ERROR_MSG_COUNT(dictId[dictIndex],commandCode[index]);
                    DIA_RESETT_INTERFACE_INVALID_MSG_COUNT(dictId[dictIndex],commandCode[index]);
                }
            }
        }
        oss <<"********Reset of Diameter Interface Stats is done**********" << endl;
    }
    else if(Cmd("diaS6aStats","Get the S6a Interface specific Stats"))
    {
        ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
        char tbuf[ITS_PATH_MAX];
        time_t local;

        time(&local);
#if defined (__SUNPRO_CC)
        ctime_r(&local, tbuf, ITS_PATH_MAX);
#else
        ctime_r(&local, tbuf);
#endif
        DiameterDictionaryRef dictRef;
        try
        {
            dictRef = DiaStackClass::GetDictionaryTable().fetchDictionaryObject((unsigned int)7); // 7: S6a_r10
        }
        catch (eAccelero::PluginException &e)
        {
            DLOG_ERROR(" DictionaryID not found PluginException:: %s",e.what());
        }
        catch(...)
        {
            DLOG_ERROR(" General exception");
        }
        if(dictRef)
        {
            eAccelero::MsgStatsCounter collatedCounter;
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it = dictRef->DictStatsMap.begin();
            std::string dictionaryName = dictRef->getDictionaryName();

            oss << "-------------------------------------------------------------------------------------"
                << endl;    oss << "-- Dia S6a_r10 Interface Stats -- at " << tbuf;
            oss << "-------------------------------------------------------------------------------------"
                << endl;
            oss <<"    Message           : ReqIn   | ReqOut | AnsIn  | AnsOut |  Error |  InvalidMsg  |"
                <<endl;
            oss << "-------------------------------------------------------------------------------------"
                << endl;


            for( ; it != dictRef->DictStatsMap.end() ; it++)
            {
                unsigned int cmdCode = it->first;
                collatedCounter = collateMsgStatsCounter(it->second->MsgStats);
                switch(cmdCode)
                {
                    case 316:
                        {
                            oss << "    ULR/ULA           : "
                                <<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetRxRspCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"
                                <<setw(8)<<collateStats(it->second->ErrorStats)<<"|"
                                <<setw(14)<<collateStats(it->second->InvalidMsgs)<<"|"<<endl;
                            break;
                        }
                    case 317:
                        {
                            oss << "    CLR/CLA           : "
                                <<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetRxRspCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"
                                <<setw(8)<<collateStats(it->second->ErrorStats)<<"|"
                                <<setw(14)<<collateStats(it->second->InvalidMsgs)<<"|"<<endl;
                            break;
                        }
                    case 318:
                        {
                            oss << "    AIR/AIA           : "
                                <<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetRxRspCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"
                                <<setw(8)<<collateStats(it->second->ErrorStats)<<"|"
                                <<setw(14)<<collateStats(it->second->InvalidMsgs)<<"|"<<endl;
                            break;
                        }
                    case 319:
                        {
                            oss << "    IDR/IDA           : "
                                <<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetRxRspCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"
                                <<setw(8)<<collateStats(it->second->ErrorStats)<<"|"
                                <<setw(14)<<collateStats(it->second->InvalidMsgs)<<"|"<<endl;
                            break;
                        }
                    case 320:
                        {
                            oss << "    DSR/DSA           : "
                                <<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetRxRspCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"
                                <<setw(8)<<collateStats(it->second->ErrorStats)<<"|"
                                <<setw(14)<<collateStats(it->second->InvalidMsgs)<<"|"<<endl;
                            break;
                        }
                    case 321:
                        {
                            oss << "    PUR/PUA           : "
                                <<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetRxRspCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"
                                <<setw(8)<<collateStats(it->second->ErrorStats)<<"|"
                                <<setw(14)<<collateStats(it->second->InvalidMsgs)<<"|"<<endl;
                            break;
                        }
                    case 322:
                        {
                            oss << "    RSR/RSA           : "
                                <<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetRxRspCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"
                                <<setw(8)<<collateStats(it->second->ErrorStats)<<"|"
                                <<setw(14)<<collateStats(it->second->InvalidMsgs)<<"|"<<endl;
                            break;
                        }
                    case 323:
                        {
                            oss << "    NOR/NOA           : "
                                <<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
                                <<setw(8)<<collatedCounter.GetRxRspCount()<<"|"
                                <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"
                                <<setw(8)<<collateStats(it->second->ErrorStats)<<"|"
                                <<setw(14)<<collateStats(it->second->InvalidMsgs)<<"|"<<endl;
                            break;
                        }
                }
            }
            oss << "-------------------------------------------------------------------------------------"
                << endl;
        }
        else
        {
            oss << "No Peer is configured with S6a dictionary." << endl;
        }
    }
    else if (Cmd("EnInterfaceStats", "Enable specific Stats"))
    {
        DiaStackClass::EnableInterfaceStats(true);
        if(DiaStackClass::InterfaceStatsEnabled)
        {
            oss << "Interface Stats Enabled" << endl;
        }
        else
        {
            oss << "Interface Stats not Enabled..!!" << endl;
        }
    }
    else if (Cmd("DisInterfaceStats", "Disable specific Stats"))
    {
        DiaStackClass::EnableInterfaceStats(false);
        if(!DiaStackClass::InterfaceStatsEnabled)
        {
            oss << "Interface Stats Disabled" << endl;
        }
        else
        {
            oss << "Interface Stats not Disabled..!!" << endl;
        }
    }
    else if (Cmd("getPeerStats", "Get Peer Stats", "peerName realmName",
                "If no PeerName and RealmName passed, will dispaly all Peer Statistics"))
    {
        string peerName = "";
        string realmName = "";

        commandLine >> dummy >> peerName >> realmName;
        oss << "PeerName : " << peerName << endl;
        oss << "RealmName : " << realmName << endl;

        diaMgmt->PrintPeerStats(oss, peerName, realmName);
    }
    else if (Cmd("activeSubscribers", "Get Current active subscribers count"))
    {
        mapStats.PrintActiveSubscribers(oss);
    }
#if 0
    else if (Cmd("printTransTable", "Print Transaction Table"))
    {
        GET_TRANS_TBL()->Print(oss);
    }
#endif
}

