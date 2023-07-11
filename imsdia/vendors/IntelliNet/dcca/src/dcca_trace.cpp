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
 * LOG: $Log: dcca_trace.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.5  2006/11/24 16:36:30  hbhatnagar
 * LOG: Made changes for SessionId as Key and corresponding changes
 * LOG:
 * LOG: Revision 2.4  2006/11/14 14:34:26  nvijikumar
 * LOG: Common disTrace for DCCA and Stack.
 * LOG:
 * LOG: Revision 2.3  2006/11/14 10:23:05  hbhatnagar
 * LOG: shifted the namespace here from corresponding .h file
 * LOG:
 * LOG: Revision 2.2  2006/11/13 06:48:17  hbhatnagar
 * LOG: Proper indentation and cleanup
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:56  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/25 08:45:51  nvijikumar
 * LOG: Converted file from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:35:01  nvijikumar
 * LOG: Made the trace object as singleton (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_trace.cpp,v 3.1 2008/03/31 10:33:31 nvijikumar Exp $
 *
 ****************************************************************************/

/**
 * Includes
 */
#include <dcca_trace.h>

/**
 * Namespace
 */
#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

/**
 * Global to this file
 */
static ITS_INT isEnabled  = 0;
static ITS_INT isDisabled = 0;
static its::ITS_Mutex guard(0);
static DCCATrace *dccaTrace = NULL;

/****************************************************************************
 *
 *  Purpose                : Singleton
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : DCCATrace*
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
DCCATrace* 
DCCATrace::GetDCCATrace()
{

    ITS_ASSERT(guard.Acquire() == ITS_SUCCESS);
    
    if (dccaTrace == NULL)
    {
        dccaTrace = new DCCATrace();
    }
    
    guard.Release();

    return dccaTrace;
}

/****************************************************************************
 *
 *  Purpose                : Constructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
DCCATrace::DCCATrace()
{
    dccaDebugTrace    = new its::TraceLevel(DCCA_DEBUG, TRACE_TO_DISPLAY);        
    dccaErrorTrace    = new its::TraceLevel(DCCA_ERROR, TRACE_TO_DISPLAY);
    dccaWarningTrace  = new its::TraceLevel(DCCA_WARNING, TRACE_TO_DISPLAY);
    dccaCriticalTrace = new its::TraceLevel(DCCA_CRITICAL, TRACE_TO_DISPLAY);
}

/****************************************************************************
 *
 *  Purpose                : Destructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
DCCATrace::~DCCATrace()
{
    delete dccaDebugTrace;
    delete dccaErrorTrace;
    delete dccaWarningTrace;
    delete dccaCriticalTrace;

    dccaDebugTrace    = NULL;
    dccaErrorTrace    = NULL;
    dccaWarningTrace  = NULL;
    dccaCriticalTrace = NULL;
}

/****************************************************************************
 *
 *  Purpose                : To enable trace
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
void
DCCATrace::DCCAEnableTrace()
{   
    if(isEnabled)
    {
        return;
    }

    TraceSubSystem::GetTrace().AddLevel(DCCA_DEBUG, dccaDebugTrace);           
    TraceSubSystem::GetTrace().AddLevel(DCCA_ERROR, dccaErrorTrace);
    TraceSubSystem::GetTrace().AddLevel(DCCA_WARNING, dccaWarningTrace);
    TraceSubSystem::GetTrace().AddLevel(DCCA_CRITICAL, dccaCriticalTrace);
        
    ITS_TraceSubSystem::GetTrace().GetLevel(DCCA_ERROR)->Enable();    
    ITS_TraceSubSystem::GetTrace().GetLevel(DCCA_DEBUG)->Enable();
    ITS_TraceSubSystem::GetTrace().GetLevel(DCCA_WARNING)->Enable();
    ITS_TraceSubSystem::GetTrace().GetLevel(DCCA_CRITICAL)->Enable();

    isEnabled  = 1;
    isDisabled = 0;
}

/****************************************************************************
 *
 *  Purpose                : To disable trace
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
void
DCCATrace::DCCADisableTrace()
{        
    if(isDisabled)
    {
        return;
    }
    if (ITS_TraceSubSystem::GetTrace().GetLevel(DCCA_ERROR))
    {
        ITS_TraceSubSystem::GetTrace().GetLevel(DCCA_ERROR)->Disable();    
        TraceSubSystem::GetTrace().RemLevel(DCCA_ERROR);
    }
    if (ITS_TraceSubSystem::GetTrace().GetLevel(DCCA_DEBUG))
    {
        ITS_TraceSubSystem::GetTrace().GetLevel(DCCA_DEBUG)->Disable();
        TraceSubSystem::GetTrace().RemLevel(DCCA_DEBUG);    
    }
    if (ITS_TraceSubSystem::GetTrace().GetLevel(DCCA_WARNING))
    {
        ITS_TraceSubSystem::GetTrace().GetLevel(DCCA_WARNING)->Disable();
        TraceSubSystem::GetTrace().RemLevel(DCCA_WARNING);
    }
    if (ITS_TraceSubSystem::GetTrace().GetLevel(DCCA_CRITICAL))
    {
        ITS_TraceSubSystem::GetTrace().GetLevel(DCCA_CRITICAL)->Disable();
        TraceSubSystem::GetTrace().RemLevel(DCCA_CRITICAL);
    }
    
    isEnabled  = 0;
    isDisabled = 1;
}
