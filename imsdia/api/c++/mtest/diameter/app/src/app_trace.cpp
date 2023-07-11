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
 * LOG: $Log: app_trace.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:06  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/07/24 14:29:23  nvijikumar
 * LOG: Baseline common application for all interfaces.
 * LOG:
 * LOG:
 *
 * ID: $Id: app_trace.cpp,v 3.1 2008/03/31 10:33:06 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: app_trace.cpp,v 3.1 2008/03/31 10:33:06 nvijikumar Exp $"

#include <engine++.h>
#include <app_trace.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

/* implementation:public
 ****************************************************************************
 *  Purpose: This function enable the Application level traces
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
void EnableAPPTracing()
{
    TraceSubSystem::GetTrace().SetSubSystemName("DiaApp");

    // Add the trace levels to the subsystem.
    TraceSubSystem::
        GetTrace().AddLevel(APP_DEBUG, AppDebugTrace);
    TraceSubSystem::
        GetTrace().AddLevel(APP_WARNING, AppWarningTrace);
    TraceSubSystem::
        GetTrace().AddLevel(APP_ERROR, AppErrorTrace);
    TraceSubSystem::
        GetTrace().AddLevel(APP_CRITICAL, AppCriticalTrace);

    //
    //  Turn on APP's trace levels (based on IntelliSS7 trace
    //  mechanism).
    //
    TraceSubSystem::GetTrace().GetLevel(APP_CRITICAL)->Enable();
    TraceSubSystem::GetTrace().GetLevel(APP_ERROR)->Enable();
    TraceSubSystem::GetTrace().GetLevel(APP_WARNING)->Enable();
    TraceSubSystem::GetTrace().GetLevel(APP_DEBUG)->Enable();
}

/* implementation:public
 ****************************************************************************
 *  Purpose: This function disables the Application Traces
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
void DisableAPPTracing()
{
    //
    //  Turn off APP's trace levels (based on IntelliSS7 trace
    //  mechanism).
    //

    ITS_TraceSubSystem::GetTrace().GetLevel(APP_CRITICAL)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(APP_ERROR)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(APP_WARNING)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(APP_DEBUG)->Disable();

}

