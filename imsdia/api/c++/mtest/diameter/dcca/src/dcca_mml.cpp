/*********************************-*-C-*-************************************
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 * LOG: $Log: dcca_mml.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:08  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.2  2006/11/24 20:13:08  hbhatnagar
 * LOG: Made changes as per the new application and interface independent Dcca
 * LOG: Module and cleanup
 * LOG:
 * LOG: Revision 2.1  2006/10/25 10:48:57  hbhatnagar
 * LOG: Integration with ITS_Diameter
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/27 09:40:51  hbhatnagar
 * LOG: Fix for Bug ID: 4383 and cleaning (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:37:17  nvijikumar
 * LOG: DCCA mtest First Cut (badri)
 * LOG:
 * LOG: Revision 1.1  2006/07/25 04:56:35  kamakshilk
 * LOG: Baseline demo application for Tx Interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: dcca_mml.cpp,v 3.1 2008/03/31 10:33:08 nvijikumar Exp $
 ****************************************************************************/

#include <dia_trace.h>

#include <app.h>
#include <dcca_mml.h>
#include <dcca_stats.h>
#include <dcca_defines.h>
#include <app_trace.h>
#include <app_diatrace.h>
#include <dcca_api.h>

/* Conflict Resolution on Linux
*/

#if defined(IPPROTO_SCTP)
#undef IPPROTO_SCTP
#endif

#include <dia_frame.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
#endif

LoadGenFunc TrafficGeneratorFunc = NULL;

/*  implementation: public
****************************************************************************
*  Purpose:
*      All Commands that need to be displayed to the MMLConsole need to be
*      Defined Here.This function also processes the commands received by the
*      from the User Driven MML Console.
*
*  Input Parameters:
*      istream& commandLine: User Input from MML Console.
*
*  Input/Output Parameters:
*      None.
*
*  Output Parameters:
*      None.
*
*  Return Value:
*      None
*
*  Notes:
*
*  See Also:
****************************************************************************/
void
APPMMLServer::DoCommand(istream& commandLine)
{
    string dummy;

    /*
     * Command to print the statistics
     */
    if (Cmd("stats", "Show Statistics"))
    {
        APPStats::GetAPPStats()->Print(oss);
    }
    /*
     * Command to clear the statistics
     */
    else if (Cmd("clear", "Clear Statistics"))
    {
        APPStats::GetAPPStats()->ResetAll();
	oss <<"*****Cleared Statistics *****" << endl;
    }
    /* 
     * Command to start the traffic during load testing
     */
    else if (Cmd("start-traffic", "Start Traffic", "duration, burstSize,\
                  sleepBetweenBurst"))
    {
        time_t    tx;
        struct tm tbuf, *temp;
        char buff[80];

        APPStats::GetAPPStats()->ResetAll();

        /*
         * Set the duration, burst size and the sleep time
         */
        commandLine >> dummy >> APPStats::duration >> APPStats::burstSize 
                    >> APPStats::slpTime;

        /*
         * Store the start time
         */
        ftime(&APPStats::starter);
        time(&APPStats::startTime);

        APPStats::sendTraffic = ITS_TRUE;
        APPStats::firstTime = ITS_TRUE;
        time(&tx);
        temp =  localtime_r(&tx, &tbuf);
        strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
        oss <<"Test Started at ----->" << buff << endl;

    }

    /* 
     * Command to stop the traffic
     */
    else if (Cmd("stop-traffic", "Stop Traffic"))
    {
        APPStats::sendTraffic = ITS_FALSE;
        ftime(&APPStats::sendComplete);
	oss <<"***** Traffic Generation Stopped *****" << endl;
    }
    /* 
     * Command to display the TPS
     */
    else if (Cmd("enTrace", "Enable All Traces"))
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
    }
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
    else if (Cmd("di", "Hex Dump Injector", "TransportInstance"))
    {
        ITS_UINT inst;
        commandLine >> dummy >> inst;
        InjectDump(inst);
    }
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
}
