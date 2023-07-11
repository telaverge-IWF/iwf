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
 * LOG: $Log: app_dbc.cpp,v $
 * LOG: Revision 1.1.4.2  2013/12/06 09:46:09  jkchaitanya
 * LOG: PerfSim is taken from B-IWF-0100-01 branch
 * LOG:
 * LOG: Revision 1.1.2.1  2013/11/15 11:03:56  jsarvesh
 * LOG: IWF Performance for CAP-Ro
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
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_dbc.cpp,v 1.1.4.2 2013/12/06 09:46:09 jkchaitanya Exp $"


#include <its++.h>
#include <its_route.h>
#include <its_thread_pool.h>
#include <its_support_exception.h>

#include <app_dbc.h>

#undef ITS_TRACE_H
#undef USE_CPLUSPLUS
#include <its_trace.h>
#include<itu/sccp.h>
#include<itu/mtp3.h>
#include<app_stats.h>

using namespace std;
using namespace its;

extern TcapStats stats;

void
TCAPDbcServer::DoCommand(istream& commandLine)
{
    string dummy;

    if (Cmd("asr", "Add SS7 route", "<(int) POINT-CODE>"))
    {        
        int pc;        
        commandLine >> dummy >> pc;

        if (commandLine.fail())
        {
            oss << "Invalid Route "<< endl;
            return;
        }
    }        
    else if (Cmd("rsr", "Remove SS7 route", "<(int) POINT-CODE>"))
    {        
        int pc;        

        commandLine >> dummy >> pc;

        if (commandLine.fail())
        {
            oss << "Invalid Route "<< endl;
            return;
        }
    }        
    //IntelliSS7 tracing
    else if (Cmd("ITSWarTrace", "IntelliSS7 Warning Trace", "<on, off>"))
    {        
        string onOff;

        commandLine >> dummy >> onOff;

        if (onOff == "on")
        {
            TRACE_TurnWarningTraceOnOff(ITS_TRUE);
        }
        else if (onOff == "off")
        {
            TRACE_TurnWarningTraceOnOff(ITS_FALSE);
        }            
    }
    else if (Cmd("ITSDbTrace", "IntelliSS7 Debug Trace", "<on, off>"))
    {   
        string onOff;

        commandLine >> dummy >> onOff;

        if (onOff == "on")
        {
            TRACE_TurnDebugTraceOnOff(ITS_TRUE);
        }
        else if (onOff == "off")
        {
            TRACE_TurnDebugTraceOnOff(ITS_FALSE);
        }                                
    }        
    else if (Cmd("ITSErrTrace", "IntelliSS7 Error Trace", "<on, off>"))
    {    
        string onOff;

        commandLine >> dummy >> onOff;

        if (onOff == "on")
        {
            TRACE_TurnErrorTraceOnOff(ITS_TRUE);
        }
        else if (onOff == "off")
        {
            TRACE_TurnErrorTraceOnOff(ITS_FALSE);
        }                                 
    }        
    else if (Cmd("ITSCrTrace", "IntelliSS7 Critical Trace", "<on, off>"))
    {        
        string onOff;

        commandLine >> dummy >> onOff;

        if (onOff == "on")
        {
            TRACE_TurnCriticalTraceOnOff(ITS_TRUE);
        }
        else if (onOff == "off")
        {
            TRACE_TurnCriticalTraceOnOff(ITS_FALSE);
        }                              
    }               
    else if (Cmd("irt", "IntelliSS7 routes", ""))
    {
        char* strDump = NULL;
        const char* cmdLine = NULL;

        int res;// = ROUTE_DumpSS7ToIdHashtable(&strDump, cmdLine);

        if (res != ITS_SUCCESS)
        {
            oss << "Unable to proceed - dump fatal error." << endl;            
        }

        oss << strDump;
        oss << endl;        

        if (strDump)
        {
           free(strDump);
        }
    }
    else if (Cmd("ils", "IntelliSS7 linksets", ""))
    {
        char* strDump = NULL;

        int res;// = LINKSET_DumpLinkSetHashtable(&strDump);

        if (res != ITS_SUCCESS)
        {
            oss << "Unables to dump linkset." << endl;
        }

        oss << strDump;
        oss << endl;

        if (strDump)
        {
            free(strDump);
        }
    }
    else if (Cmd("stats", "Statistics", "<>", "<>"))
    {
        stats.PrintTCAPStats(oss);
    }

}

