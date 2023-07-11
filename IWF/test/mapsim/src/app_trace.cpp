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
 * LOG: $Log: app_trace.cpp,v $
 * LOG: Revision 1.1.2.1  2013/02/12 14:09:19  jvikas
 * LOG: Map Simulator Changes for IWF
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
 *
 ****************************************************************************/
#ident "$Id: app_trace.cpp,v 1.1.2.1 2013/02/12 14:09:19 jvikas Exp $"

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
void EnableAppTracing()
{
    TraceSubSystem::GetTrace().SetSubSystemName("SampleApp");

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

