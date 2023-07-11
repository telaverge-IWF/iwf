/*********************************-*-CDIA-*-**********************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
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
 *  ID: $Id: dia_trace.cpp,v 3.3.64.1 2013/02/27 08:49:06 jvikram Exp $
 *  LOG: $Log: dia_trace.cpp,v $
 *  LOG: Revision 3.3.64.1  2013/02/27 08:49:06  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 3.3  2008/12/10 11:00:01  nvijikumar
 *  LOG: Use local flag to check TraceLevel ON/OFF
 *  LOG:
 *  LOG: Revision 3.2  2008/10/28 12:00:22  nvijikumar
 *  LOG: IssueID: none
 *  LOG: FeatureID: none
 *  LOG: Description: Porting Performance changes from 3.0 branch
 *  LOG:
 *  LOG: Revision 3.1.2.2  2008/10/06 09:43:44  nvijikumar
 *  LOG: Fix for tracing issue
 *  LOG:
 *  LOG: Revision 3.1.2.1  2008/09/16 09:37:46  nvijikumar
 *  LOG: Local flags are used to check trace level enabled or not
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:22  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.3  2006/10/05 11:54:19  yranade
 *  LOG: Updates.
 *  LOG:
 *  LOG: Revision 2.2  2006/09/13 10:08:51  yranade
 *  LOG: ITS-Diameter specific updates.
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.6  2006/06/21 10:41:27  nvijikumar
 *  LOG: Modification for Copyright info.
 *  LOG:
 *  LOG: Revision 1.5  2006/05/04 20:44:44  yranade
 *  LOG: IsEnabled on a per level basis.
 *  LOG:
 *  LOG: Revision 1.4  2006/05/04 20:27:23  yranade
 *  LOG: API to check whether traces are enabled.
 *  LOG:
 *  LOG: Revision 1.3  2006/04/28 18:22:34  yranade
 *  LOG: Update some errorneous comments.
 *  LOG:
 *  LOG: Revision 1.2  2006/04/27 15:57:41  yranade
 *  LOG: Converted to a Trace Class.
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 13:03:08  tpanda
 *  LOG: Building IMS Infrastructure
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_trace.cpp,v 3.3.64.1 2013/02/27 08:49:06 jvikram Exp $"

#include <dia_trace.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

its::TraceLevel    *diaDebugTrace = NULL;
its::TraceLevel    *diaErrorTrace = NULL;
its::TraceLevel    *diaCriticalTrace = NULL;
its::TraceLevel    *diaWarningTrace = NULL;

its::ITS_Mutex DiaTrace::guard(0);
static DiaTrace *diaTrace = NULL;

/* Global Variables */
bool isDebugEnabled    = false;
bool isCriticalEnabled = false;
bool isErrorEnabled    = false;
bool isWarnEnabled     = false;

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
DiaTrace* 
DiaTrace::GetDiaTrace()
{
    
    /* If object does not exist, cteate one
    */ 
    if (diaTrace == NULL)
    {
        /* Acquire the mutex before creating the object
        */ 
        ITS_ASSERT(DiaTrace::guard.Acquire() == ITS_SUCCESS);

        diaTrace = new DiaTrace;

        //DiaTrace::Create();
        /* Release the mutex
        */
        DiaTrace::guard.Release();
    }

    return diaTrace;
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
void
DiaTrace::Create()
{
    if (diaDebugTrace    == NULL &&
        diaWarningTrace  == NULL &&
        diaErrorTrace    == NULL &&
        diaCriticalTrace == NULL)
    {
        diaDebugTrace =
                 new its::TraceLevel(DIA_DEBUG, TRACE_TO_DISPLAY);
        diaWarningTrace =
                 new its::TraceLevel(DIA_WARNING, TRACE_TO_DISPLAY);
        diaErrorTrace =
                new its::TraceLevel(DIA_ERROR, TRACE_TO_DISPLAY);
        diaCriticalTrace =
                 new its::TraceLevel(DIA_CRITICAL, TRACE_TO_DISPLAY);

        // Add the trace levels to the subsystem.
        TraceSubSystem::
            GetTrace().AddLevel(DIA_DEBUG, diaDebugTrace);
        TraceSubSystem::
            GetTrace().AddLevel(DIA_WARNING, diaWarningTrace);
        TraceSubSystem::
            GetTrace().AddLevel(DIA_ERROR, diaErrorTrace);
        TraceSubSystem::
            GetTrace().AddLevel(DIA_CRITICAL, diaCriticalTrace);
    }
}

//Warning fix - deprecated conversion from string constant to char*
void
DiaTrace::Create(const char *level, int mask)
{
    if (diaDebugTrace == NULL && ((strcmp(level, DIA_DEBUG) == 0)))
    {
        diaDebugTrace =
                     new its::TraceLevel(level, mask);

        TraceSubSystem::
            GetTrace().AddLevel(level, diaDebugTrace);
    }

    else if (diaWarningTrace == NULL && ((strcmp(level, DIA_WARNING) == 0)))
    {
        diaWarningTrace =
                     new its::TraceLevel(level, mask);

        TraceSubSystem::
            GetTrace().AddLevel(level, diaWarningTrace);
    }
    else if (diaErrorTrace == NULL && ((strcmp(level, DIA_ERROR) == 0)))
    {
        diaErrorTrace =
                     new its::TraceLevel(level, mask);

        TraceSubSystem::
            GetTrace().AddLevel(level, diaErrorTrace);
    }
    else if (diaCriticalTrace == NULL && ((strcmp(level, DIA_CRITICAL) == 0)))
    {
        diaCriticalTrace =
                     new its::TraceLevel(level, mask);

        TraceSubSystem::
            GetTrace().AddLevel(level, diaCriticalTrace);
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
 ****************************************************************************/
void 
DiaTrace::Enable()
{
    //
    //  Turn on DIA's trace levels (based on IntelliSS7 trace
    //  mechanism).
    //
    TraceSubSystem::GetTrace().GetLevel(DIA_CRITICAL)->Enable();
    TraceSubSystem::GetTrace().GetLevel(DIA_ERROR)->Enable();
    TraceSubSystem::GetTrace().GetLevel(DIA_WARNING)->Enable();
    TraceSubSystem::GetTrace().GetLevel(DIA_DEBUG)->Enable();

    isEnabled = true;
    isDebugEnabled    = true;
    isCriticalEnabled = true;
    isErrorEnabled    = true;
    isWarnEnabled     = true;

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
//Warning fix - deprecated conversion from string constant to char*
void 
DiaTrace::Enable(const char *level)
{   
    if (ITS_TraceSubSystem::GetTrace().GetLevel(level))
    {
        ITS_TraceSubSystem::GetTrace().GetLevel(level)->Enable();
        isEnabled = true;

        if (strcmp(level, DIA_DEBUG) == 0)
        {
            isDebugEnabled    = true;
        }
        else if (strcmp(level, DIA_CRITICAL) == 0)
        {
            isCriticalEnabled = true;
        }
        else if (strcmp(level, DIA_WARNING) == 0)
        {
            isWarnEnabled     = true;
        }
        else if (strcmp(level, DIA_ERROR) == 0)
        {
            isErrorEnabled    = true;
        }
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
 ****************************************************************************/
void 
DiaTrace::Disable(const char *level)
{
    if (ITS_TraceSubSystem::GetTrace().GetLevel(level))
    {
        ITS_TraceSubSystem::GetTrace().GetLevel(level)->Disable();

        if (strcmp(level, DIA_DEBUG) == 0)
        {
            isDebugEnabled    = false;
        }
        else if (strcmp(level, DIA_CRITICAL) == 0)
        {
            isCriticalEnabled = false;
        }
        else if (strcmp(level, DIA_WARNING) == 0)
        {
            isWarnEnabled     = false;
        }
        else if (strcmp(level, DIA_ERROR) == 0)
        {
            isErrorEnabled    = false;
        }
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
 ****************************************************************************/
void 
DiaTrace::Disable()
{
    //
    //  Turn off DIA's trace levels (based on IntelliSS7 trace
    //  mechanism).
    //

    ITS_TraceSubSystem::GetTrace().GetLevel(DIA_CRITICAL)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(DIA_ERROR)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(DIA_WARNING)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(DIA_DEBUG)->Disable();
    isEnabled         = false;
    isDebugEnabled    = false;
    isCriticalEnabled = false;
    isErrorEnabled    = false;
    isWarnEnabled     = false;

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
void 
DiaTrace::Delete()
{
    // Remove the trace levels to the subsystem.
    TraceSubSystem::
        GetTrace().RemLevel(DIA_DEBUG);
    TraceSubSystem::
        GetTrace().RemLevel(DIA_WARNING);
    TraceSubSystem::
        GetTrace().RemLevel(DIA_ERROR);
    TraceSubSystem::
        GetTrace().RemLevel(DIA_CRITICAL);

    delete diaDebugTrace;
    delete diaErrorTrace;
    delete diaCriticalTrace;
    delete diaWarningTrace;
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
void
DiaTrace::Display(std::ostream& os) const
{
#if 0
    bool isDebugEnabled =
       ITS_TraceSubSystem::GetTrace().GetLevel(DIA_DEBUG)->IsEnabled();
    bool isCriticalEnabled = 
       ITS_TraceSubSystem::GetTrace().GetLevel(DIA_CRITICAL)->IsEnabled();
    bool isErrorEnabled = 
       ITS_TraceSubSystem::GetTrace().GetLevel(DIA_ERROR)->IsEnabled();
    bool isWarnEnabled =
       ITS_TraceSubSystem::GetTrace().GetLevel(DIA_WARNING)->IsEnabled();
#endif

    os << "    Diameter Debug Trace:        ";

    if (isDebugEnabled)
    {
        os << "Enabled " << endl;
    }
    else
    {
        os << "Disabled " << endl;
    }

    os << "    Diameter Error Trace:        ";
    if (isErrorEnabled)
    {
        os << "Enabled " << endl;
    }
    else
    {
        os << "Disabled " << endl;
    }
    os << "    Diameter Warning Trace:      ";
    if (isWarnEnabled)
    {
        os << "Enabled " << endl;
    }
    else
    {
        os << "Disabled " << endl;
    }
    os << "    Diameter Critical Trace:     ";
    if (isCriticalEnabled)
    {
        os << "Enabled " << endl;
    }
    else
    {
        os << "Disabled " << endl;
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
 ****************************************************************************/
bool
DiaTrace::IsEnabled() const
{
    return isEnabled;
}

bool
DiaTrace::IsEnabled(const char* level) const
{
    if (ITS_TraceSubSystem::GetTrace().GetLevel(level))
    {
        return ITS_TraceSubSystem::GetTrace().GetLevel(level)->IsEnabled();
    }
    return false;
}

bool
DiaTrace::IsDebugEnabled() const
{
    return isDebugEnabled;
}

bool
DiaTrace::IsWarningEnabled() const
{
    return isWarnEnabled;
}

bool
DiaTrace::IsCriticalEnabled() const
{
    return isCriticalEnabled;
}

bool
DiaTrace::IsErrorEnabled() const
{
    return isErrorEnabled;
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
std::ostream&
operator<<(std::ostream& os, const DiaTrace& dt)
{
    dt.Display(os);
    return os;
}


