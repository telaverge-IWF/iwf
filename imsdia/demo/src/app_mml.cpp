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
 * LOG: $Log: app_mml.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:23  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.8  2006/06/21 09:57:29  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.7  2006/05/11 13:36:47  rrath
 * LOG: Added output information in MML console.
 * LOG:
 * LOG: Revision 1.6  2006/05/04 20:48:17  yranade
 * LOG: Added commands to enable/disable all traces.
 * LOG:
 * LOG: Revision 1.5  2006/04/28 18:23:58  yranade
 * LOG: Changes for accelero based OD tracing.
 * LOG:
 * LOG: Revision 1.4  2006/04/27 16:04:57  yranade
 * LOG: Added Commands to Enable/Disable Diameter Traces.
 * LOG:
 * LOG: Revision 1.3  2006/04/25 14:07:30  adsouza
 * LOG: 1. Code Enhancements (Added Comments, Flowerboxes)
 * LOG: 2. Method to Inject Hex Dumps
 * LOG:
 * LOG: Revision 1.2  2006/04/22 00:06:20  ahanda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1  2006/04/17 16:07:29  yranade
 * LOG: MML Server Support.
 * LOG:
 *
 * ID: $Id: app_mml.cpp,v 3.1 2008/03/31 10:33:23 nvijikumar Exp $
 ****************************************************************************/

#include <dia_trace.h>

#include <app.h>
#include <app_mml.h>
#include <app_stats.h>
#include <app_trace.h>

/* Conflict Resolution on Linux
*/

#if defined(IPPROTO_SCTP)
#undef IPPROTO_SCTP
#endif

#include <dia_frame.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
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

        /*
         * Set the traffic generator function
         */
        //TrafficGeneratorFunc = SendReAuthRequest;
        TrafficGeneratorFunc = SendProfileUpdateRequest;
        // TrafficGeneratorFunc = SendMultimediaAuthRequest;
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
        ODiaTrace::GetODiaTrace()->Enable();

	oss <<"*****All the traces are enabled*****" << endl;
    }
    else if (Cmd("disTrace", "Disable All Traces"))
    {
        DisableAPPTracing();
        DiaTrace::GetDiaTrace()->Disable();
        ODiaTrace::GetODiaTrace()->Disable();

	oss <<"*****All the traces are disabled*****" << endl;
    }
    else if (Cmd("tps", "TPS"))
    {
        APPStats::GetAPPStats()->CalcTPS(oss);
    }
    else if (Cmd("enDiaTrace", "Enable All Dia Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable();
        ODiaTrace::GetODiaTrace()->Enable();

	oss <<"*******All Diameter Traces are enabled*******" << endl; 
    }
    else if (Cmd("disDiaTrace", "Disable All Dia Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable();
        ODiaTrace::GetODiaTrace()->Disable();

	oss <<"*******All Diameter Traces are disabled*******" << endl;
    }
    else if (Cmd("enDiaDebTrace", "Enable Dia Debug Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_DEBUG);
        ODiaTrace::GetODiaTrace()->Enable(ODIA_DEBUG);
	
	oss <<"*******Diameter Debug Traces are enabled*******" << endl;
    }
    else if (Cmd("enDiaErrTrace", "Enable Dia Error Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_ERROR);
        ODiaTrace::GetODiaTrace()->Enable(ODIA_ERROR);

	oss <<"*******Diameter Error Traces are enabled*******" << endl;
    }
    else if (Cmd("enDiaWarnTrace", "Enable Dia Warning Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_WARNING);
        ODiaTrace::GetODiaTrace()->Enable(ODIA_WARNING);
	
	oss <<"*******Diameter Warning Traces are enabled*******" << endl;
    }
    else if (Cmd("enDiaCritTrace", "Enable Dia Critical Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_CRITICAL);
        ODiaTrace::GetODiaTrace()->Enable(ODIA_CRITICAL);

	oss <<"*******Diameter Critical Traces are enabled*******" << endl;
    }
    else if (Cmd("disDiaDebTrace", "Disable Dia Debug Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable(DIA_DEBUG);
        ODiaTrace::GetODiaTrace()->Disable(ODIA_DEBUG);

	oss <<"*******Diameter Debug Traces are disabled*******" << endl;
    }
    else if (Cmd("disDiaErrTrace", "Disable Dia Error Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable(DIA_ERROR);
        ODiaTrace::GetODiaTrace()->Disable(ODIA_ERROR);

	oss <<"*******Diameter Error Traces are disabled*******" << endl;
    }
    else if (Cmd("disDiaCritTrace", "Disable Dia Critical Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable(DIA_CRITICAL);
        ODiaTrace::GetODiaTrace()->Disable(ODIA_CRITICAL);

	oss <<"*******Diameter Critical Traces are disabled*******" << endl;
    }
    else if (Cmd("disDiaWarnTrace", "Disable Dia Warning Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable(DIA_WARNING);
        ODiaTrace::GetODiaTrace()->Disable(ODIA_WARNING);

	oss <<"*******Diameter Warning Traces are disabled*******" << endl;
    }
    else if (Cmd("DisplayDiaTrace", "Display Dia Tracing Info"))
    {
        DiaTrace::GetDiaTrace()->Display(oss);
        ODiaTrace::GetODiaTrace()->Display(oss);
    }
    else if (Cmd("di", "Hex Dump Injector", "TransportInstance"))
    {
        ITS_UINT inst;
        commandLine >> dummy >> inst;
        InjectDump(inst);
    }
}
