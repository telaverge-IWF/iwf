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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * ID: $Id: DIAMon_trace.cpp,v 3.1 2008/03/31 10:33:28 nvijikumar Exp $
 *
 * LOG: $Log: DIAMon_trace.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:28  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/03/07 15:49:40  yranade
 * LOG: Initial Version of Monitor Utility. Please refer README for details.
 * LOG:
 ****************************************************************************/
#ident "$Id: DIAMon_trace.cpp,v 3.1 2008/03/31 10:33:28 nvijikumar Exp $"

#include <DIAMon_trace.h>

#if defined(ITS_NAMESPACE)
using namespace its;
using namespace std;
#endif

//DIA_Monitor traces
ITS_TraceLevel adpMonTraceDEBUG(DIAMON_DEBUG, TRACE_TO_DISPLAY|TRACE_TO_SYSLOG);
ITS_TraceLevel adpMonTraceWARNING(DIAMON_WARNING, TRACE_TO_DISPLAY|TRACE_TO_SYSLOG);
ITS_TraceLevel adpMonTraceERROR(DIAMON_ERROR, TRACE_TO_DISPLAY|TRACE_TO_SYSLOG);
ITS_TraceLevel adpMonTraceCRITICAL(DIAMON_CRITICAL, TRACE_TO_DISPLAY|TRACE_TO_SYSLOG);

void
EnableDIAMONTracing()
{
    TraceSubSystem::GetTrace().SetSubSystemName("DiaMon");

    EnableDIAMONDebugTracing();
    EnableDIAMONErrorTracing();
    EnableDIAMONWarningTracing();
    EnableDIAMONCriticalTracing();
    
}

void
EnableDIAMONDebugTracing()
{
    // Add the trace levels to the subsystem.
    TraceSubSystem::
        GetTrace().AddLevel(DIAMON_DEBUG, &adpMonTraceDEBUG);

    ITS_TraceSubSystem::GetTrace().GetLevel(DIAMON_CRITICAL)->Enable();
}

void 
EnableDIAMONErrorTracing()
{
    // Add the trace levels to the subsystem.
    TraceSubSystem::
       GetTrace().AddLevel(DIAMON_ERROR, &adpMonTraceERROR);

    ITS_TraceSubSystem::GetTrace().GetLevel(DIAMON_ERROR)->Enable();
}

void 
EnableDIAMONWarningTracing()
{
    // Add the trace levels to the subsystem.
    TraceSubSystem::
        GetTrace().AddLevel(DIAMON_WARNING, &adpMonTraceWARNING);

    ITS_TraceSubSystem::GetTrace().GetLevel(DIAMON_WARNING)->Enable();
}

void 
EnableDIAMONCriticalTracing()
{
    // Add the trace levels to the subsystem.
    TraceSubSystem::
        GetTrace().AddLevel(DIAMON_CRITICAL, &adpMonTraceCRITICAL);

    ITS_TraceSubSystem::GetTrace().GetLevel(DIAMON_CRITICAL)->Enable();
}
