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
 *
 * LOG: $Log: idc_trace.cpp,v $
 * LOG: Revision 3.1.70.1  2013/02/27 08:49:06  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:03  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2007/01/19 13:00:18  kamakshilk
 * LOG: CreateTracing and DeleteTracing APIs added
 * LOG:
 * LOG: Revision 2.3  2007/01/11 06:21:45  kamakshilk
 * LOG: TraceEnabled flag set to false in DisableTrace
 * LOG:
 * LOG: Revision 2.2  2006/10/31 10:01:43  kamakshilk
 * LOG: IDSCL_Print function added
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:12:34  adutta
 * LOG: First cut
 * LOG:
 *
 * ID: $Id: idc_trace.cpp,v 3.1.70.1 2013/02/27 08:49:06 jvikram Exp $
 ****************************************************************************/
#ident "$Id: idc_trace.cpp,v 3.1.70.1 2013/02/27 08:49:06 jvikram Exp $"


#include <engine++.h>

#include <idc_trace.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

bool idcTraceEnabled = false;

its::TraceLevel *AimDebugTrace = NULL;
its::TraceLevel *AimErrorTrace = NULL;
its::TraceLevel *AimWarningTrace = NULL;
its::TraceLevel *AimCriticalTrace = NULL;

extern "C"
{

/*.implementation:static
 ****************************************************************************
 *  Purpose: This creates the trace level.
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
void
IDSCL_CreateTracing()
{
    if (AimDebugTrace ==NULL &&
        AimWarningTrace == NULL &&
        AimErrorTrace == NULL &&
        AimCriticalTrace == NULL )
    {
        AimDebugTrace = 
                 new its::TraceLevel(IDS_DEBUG, TRACE_TO_DISPLAY);
        AimWarningTrace = 
                 new its::TraceLevel(IDS_WARNING, TRACE_TO_DISPLAY);
        AimErrorTrace = 
                 new its::TraceLevel(IDS_ERROR, TRACE_TO_DISPLAY);
        AimCriticalTrace = 
                 new its::TraceLevel(IDS_CRITICAL, TRACE_TO_DISPLAY);

        // Add the trace levels to the subsystem.
        TraceSubSystem::
            GetTrace().AddLevel(IDS_DEBUG, AimDebugTrace);
    
        TraceSubSystem::
            GetTrace().AddLevel(IDS_WARNING, AimWarningTrace);
    
        TraceSubSystem::
            GetTrace().AddLevel(IDS_ERROR, AimErrorTrace);

        TraceSubSystem::
            GetTrace().AddLevel(IDS_CRITICAL, AimCriticalTrace);
    }

}

/*.implementation:static
 ****************************************************************************
 *  Purpose: This deletes the trace levels created.
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
void
IDSCL_DeleteTracing()
{
    if (AimDebugTrace != NULL &&
        AimWarningTrace != NULL &&
        AimErrorTrace != NULL &&
        AimCriticalTrace != NULL )
    {
        // Remove the trace levels to the subsystem.
        TraceSubSystem::
            GetTrace().RemLevel(IDS_CRITICAL);
        TraceSubSystem::
            GetTrace().RemLevel(IDS_ERROR);
        TraceSubSystem::
            GetTrace().RemLevel(IDS_WARNING);
        TraceSubSystem::
            GetTrace().RemLevel(IDS_DEBUG);

        delete AimCriticalTrace;
        delete AimErrorTrace;
        delete AimWarningTrace;
        delete AimDebugTrace;

        AimDebugTrace = NULL;
        AimErrorTrace = NULL;
        AimWarningTrace = NULL;
        AimCriticalTrace = NULL;
    }
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
 *  ---------------------------------------------------------------------------
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    19-01-07   Enhancement   Creation of debug levels removed. 
 *
 ****************************************************************************/
void
IDSCL_EnableTracing()
{
    //
    //  Turn on IDS's trace levels (based on IntelliSS7 trace
    //  mechanism).
    //
    ITS_TraceSubSystem::GetTrace().GetLevel(IDS_CRITICAL)->Enable();
    ITS_TraceSubSystem::GetTrace().GetLevel(IDS_ERROR)->Enable();
    ITS_TraceSubSystem::GetTrace().GetLevel(IDS_WARNING)->Enable();
    ITS_TraceSubSystem::GetTrace().GetLevel(IDS_DEBUG)->Enable();

    idcTraceEnabled = true;
}

bool
IDSCL_IsTraceEnabled()
{
    return idcTraceEnabled;
}

bool
IDSCL_IsEnabled(const char *level)
{
   return ITS_TraceSubSystem::GetTrace().GetLevel(level)->IsEnabled();
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
 *  ---------------------------------------------------------------------------
 *   Name          Date      Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    19-01-07   Enhancement   Deletion of debug levels removed. 
 *
 ****************************************************************************/
void
IDSCL_DisableTracing()
{
    //
    //  Turn off IDS's trace levels (based on IntelliSS7 trace
    //  mechanism).
    //
    ITS_TraceSubSystem::GetTrace().GetLevel(IDS_CRITICAL)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(IDS_ERROR)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(IDS_WARNING)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(IDS_DEBUG)->Disable();

    idcTraceEnabled = false;
}

}

