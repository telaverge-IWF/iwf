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
 * LOG: Revision 3.1.70.1.2.2  2013/05/22 09:59:50  ncshivakumar
 * LOG: Merged from 300 Branch
 * LOG:
 * LOG: Revision 3.1.70.1.2.1  2013/05/15 05:04:45  ncshivakumar
 * LOG: Fixed issue causing crash
 * LOG:
 * LOG: Revision 3.1.70.2  2013/04/25 06:56:47  millayaraja
 * LOG: modified for using CLOG for testapp logging
 * LOG:
 * LOG: Revision 3.1.70.1  2013/04/18 07:04:30  jvikram
 * LOG: Included changes relatd to log segregation.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:07  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 07:59:44  kamakshilk
 * LOG: Common files required for static setup
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/07/24 14:29:23  nvijikumar
 * LOG: Baseline common application for all interfaces.
 * LOG:
 * LOG:
 * ID: $Id: app_trace.cpp,v 3.1.70.1.2.2 2013/05/22 09:59:50 ncshivakumar Exp $
 ****************************************************************************/

#include <engine++.h>
#include <dia_defines.h>
#include <dia_trace.h>
#include <dia_frame.h>
#include <app_trace.h>

#ifdef FOR_DRE

#include <Component.h>
#include <ComponentDefines.h>
#include <MeSSComponent.h>
#include <Logger.h>

#endif

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
#ifdef FOR_DRE
eAccelero::MeSSComponent *gocMessComp = NULL;
#endif

void EnableAPPTracing()
{
#ifdef FOR_DRE
   gocMessComp = new eAccelero::MeSSComponent("TEST", eAccelero::COMP_TEST_APP);
   char *gargv[]={(char*)"dummy",(char*)"-l",(char*)"7",(char*)"-i",(char*)"0"};
   gocMessComp->Init(5, gargv);
   eAccelero::Logger ocLogger = gocMessComp->GetLogger();
   ocLogger.SetLevel(eAccelero::Logger::EACC_LOG_DEBUG);
#else

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
#endif
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

/* implementation:public
 ****************************************************************************
 *  Purpose:
 *      Enable Diameter Tracing Function
 *      Enables the DiaTrace Traces.
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
void EnableDiaTracing()
{
    /* Enable Tracing of the Diameter Stack
       There are 4 Levels of Tracing that are enabled, namely
       DEBUG, CRITICAL, ERROR, WARNING
    */

    DiaTrace::GetDiaTrace()->Enable();
}

/* implementation:public
 ****************************************************************************
 *  Purpose:
 *      Enable Diameter Warning Tracing Function
 *      Enables the DiaTrace Traces.
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
void EnableDiaWarnTracing()
{
    /* Enable Warning Tracing of the Diameter Stack
    */

    DiaTrace::GetDiaTrace()->Enable(DIA_WARNING);
}

/* implementation:public
 ****************************************************************************
 *  Purpose:
 *      Enable Diameter Critical Tracing Function
 *      Enables the DiaTrace Traces.
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
void EnableDiaCriticalTracing()
{
    /* Enable Critical Tracing of the Diameter Stack
    */

    DiaTrace::GetDiaTrace()->Enable(DIA_CRITICAL);
}

/* implementation:public
 ****************************************************************************
 *  Purpose:
 *      Enable Diameter Critical Tracing Function
 *      Enables the DiaTrace Traces.
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
void EnableDiaErrorTracing()
{
    /* Enable Error Tracing of the Diameter Stack
    */

    DiaTrace::GetDiaTrace()->Enable(DIA_ERROR);
}

/* implementation:public
 ****************************************************************************
 *  Purpose:
 *      Enable Diameter Debug Tracing Function
 *      Enables the DiaTrace Traces.
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
void EnableDiaDebugTracing()
{
    /* Enable Debug Tracing of the Diameter Stack
    */

    DiaTrace::GetDiaTrace()->Enable(DIA_DEBUG);
}

/* implementation:public
 ****************************************************************************
 *  Purpose:
 *      Disable Diameter Tracing Function
 *      Disables the DiaTrace Traces.
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
void DisableDiaTracing()
{
    /* Disable Tracing of the Diameter Stack
       There are 4 Levels of Tracing that are enabled, namely
       DEBUG, CRITICAL, ERROR, WARNING
    */

    DiaTrace::GetDiaTrace()->Disable();
}

/* implementation:public
 ****************************************************************************
 *  Purpose:
 *      Disable Diameter Warning Tracing Function
 *      Disables the DiaTrace Traces.
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
void DisableDiaWarnTracing()
{
    /* Disable Warning Tracing of the Diameter Stack
    */

    DiaTrace::GetDiaTrace()->Disable(DIA_WARNING);
}


/* implementation:public
 ****************************************************************************
 *  Purpose:
 *      Disable Diameter Error Tracing Function
 *      Disables the DiaTrace Traces.
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
void DisableDiaErrorTracing()
{
    /* Disable Error Tracing of the Diameter Stack.
    */

    DiaTrace::GetDiaTrace()->Disable(DIA_ERROR);
}

/* implementation:public
 ****************************************************************************
 *  Purpose:
 *      Disable Diameter Critical Tracing Function
 *      Disables the DiaTrace Traces.
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
void DisableDiaCriticalTracing()
{
    /* Disable Critical Tracing of the Diameter Stack.
    */

    DiaTrace::GetDiaTrace()->Disable(DIA_CRITICAL);
}

/* implementation:public
 ****************************************************************************
 *  Purpose:
 *      Disable Diameter Debug Tracing Function
 *      Disables the DiaTrace Traces.
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
void DisableDiaDebugTracing()
{
    /* Disable Debug Tracing of the Diameter Stack.
    */

    DiaTrace::GetDiaTrace()->Disable(DIA_DEBUG);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *
 *         Utility function to display the diameter Tracing
 *
 *  Input Parameters:
 *      const std::ostream & oss: Pointer to display the dia traces.
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
void DisplayDiaTracing(std::ostream& oss)
{
        DiaTrace::GetDiaTrace()->Display(oss);
}

