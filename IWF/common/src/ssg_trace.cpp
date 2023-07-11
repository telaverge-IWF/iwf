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
 *  ID: $Id: ssg_trace.cpp,v 1.1.1.1 2013/01/09 16:41:38 brajappa Exp $
 *  LOG: $Log: ssg_trace.cpp,v $
 *  LOG: Revision 1.1.1.1  2013/01/09 16:41:38  brajappa
 *  LOG: Initial import
 *  LOG:
 *  LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 *  LOG: Initial Draft for SSG
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: ssg_trace.cpp,v 1.1.1.1 2013/01/09 16:41:38 brajappa Exp $"

#include <engine++.h>
#include <ssg_trace.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

its::ITS_Mutex SsgTrace::guard(0);
static SsgTrace *hipTrace = NULL;

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
SsgTrace* 
SsgTrace::GetSsgTrace()
{
    
    /* If object does not exist, cteate one
    */ 
    if (hipTrace == NULL)
    {
        /* Acquire the mutex before creating the object
        */ 
        ITS_ASSERT(SsgTrace::guard.Acquire() == ITS_SUCCESS);

        hipTrace = new SsgTrace;

        //SsgTrace::Create();
        /* Release the mutex
        */
        SsgTrace::guard.Release();
    }

    return hipTrace;
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
SsgTrace::Create()
{
    // Add the trace levels to the subsystem.
    TraceSubSystem::GetTrace().SetSubSystemName("SSG");
    TraceSubSystem:: GetTrace().AddLevel(SSG_DEBUG, AppDebugTrace);
    TraceSubSystem:: GetTrace().AddLevel(SSG_WARNING, AppWarningTrace);
    TraceSubSystem:: GetTrace().AddLevel(SSG_ERROR, AppErrorTrace);
    TraceSubSystem:: GetTrace().AddLevel(SSG_CRITICAL, AppCriticalTrace);
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
SsgTrace::Enable()
{
    //
    //  Turn on SSG's trace levels (based on IntelliSS7 trace
    //  mechanism).
    TraceSubSystem::GetTrace().GetLevel(SSG_CRITICAL)->Enable();
    TraceSubSystem::GetTrace().GetLevel(SSG_ERROR)->Enable();
    TraceSubSystem::GetTrace().GetLevel(SSG_WARNING)->Enable();
    TraceSubSystem::GetTrace().GetLevel(SSG_DEBUG)->Enable();


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
void 
SsgTrace::Enable(char *level)
{   
    if (ITS_TraceSubSystem::GetTrace().GetLevel(level))
    {
        ITS_TraceSubSystem::GetTrace().GetLevel(level)->Enable();
        isEnabled = true;

        if (strcmp(level, SSG_DEBUG) == 0)
        {
            isDebugEnabled    = true;
        }
        else if (strcmp(level, SSG_CRITICAL) == 0)
        {
            isCriticalEnabled = true;
        }
        else if (strcmp(level, SSG_WARNING) == 0)
        {
            isWarnEnabled     = true;
        }
        else if (strcmp(level, SSG_ERROR) == 0)
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
SsgTrace::Disable(char *level)
{
    if (ITS_TraceSubSystem::GetTrace().GetLevel(level))
    {
        ITS_TraceSubSystem::GetTrace().GetLevel(level)->Disable();

        if (strcmp(level, SSG_DEBUG) == 0)
        {
            isDebugEnabled    = false;
        }
        else if (strcmp(level, SSG_CRITICAL) == 0)
        {
            isCriticalEnabled = false;
        }
        else if (strcmp(level, SSG_WARNING) == 0)
        {
            isWarnEnabled     = false;
        }
        else if (strcmp(level, SSG_ERROR) == 0)
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
SsgTrace::Disable()
{
    //
    //  Turn off SSG's trace levels (based on IntelliSS7 trace
    //  mechanism).
    //

    ITS_TraceSubSystem::GetTrace().GetLevel(SSG_CRITICAL)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(SSG_ERROR)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(SSG_WARNING)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(SSG_DEBUG)->Disable();
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
SsgTrace::Delete()
{
    // Remove the trace levels to the subsystem.
    TraceSubSystem::
        GetTrace().RemLevel(SSG_DEBUG);
    TraceSubSystem::
        GetTrace().RemLevel(SSG_WARNING);
    TraceSubSystem::
        GetTrace().RemLevel(SSG_ERROR);
    TraceSubSystem::
        GetTrace().RemLevel(SSG_CRITICAL);
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
SsgTrace::Display(std::ostream& os) const
{
    os << "    Ssg Debug Trace:        ";

    if (isDebugEnabled)
    {
        os << "Enabled " << endl;
    }
    else
    {
        os << "Disabled " << endl;
    }

    os << "    Ssg Stack Error Trace:        ";
    if (isErrorEnabled)
    {
        os << "Enabled " << endl;
    }
    else
    {
        os << "Disabled " << endl;
    }
    os << "    Ssg Stack Warning Trace:      ";
    if (isWarnEnabled)
    {
        os << "Enabled " << endl;
    }
    else
    {
        os << "Disabled " << endl;
    }
    os << "    Ssg Stack Critical Trace:     ";
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
SsgTrace::IsEnabled() const
{
    return isEnabled;
}

bool
SsgTrace::IsEnabled(char* level) const
{
    if (ITS_TraceSubSystem::GetTrace().GetLevel(level))
    {
        return ITS_TraceSubSystem::GetTrace().GetLevel(level)->IsEnabled();
    }
    return false;
}

bool
SsgTrace::IsDebugEnabled() const
{
    return isDebugEnabled;
}

bool
SsgTrace::IsWarningEnabled() const
{
    return isWarnEnabled;
}

bool
SsgTrace::IsCriticalEnabled() const
{
    return isCriticalEnabled;
}

bool
SsgTrace::IsErrorEnabled() const
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
operator<<(std::ostream& os, const SsgTrace& dt)
{
    dt.Display(os);
    return os;
}


