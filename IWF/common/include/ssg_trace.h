/*********************************-*--H--*-**********************************
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
 * LOG: $Log: ssg_trace.h,v $
 * LOG: Revision 1.1.1.1.2.1  2013/05/20 08:56:40  jvikram
 * LOG: Corrected Coverity Issues
 * LOG:
 * LOG: Revision 1.2  2013/05/20 04:42:59  jenkins
 * LOG: Fix for coverity warnings
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:38  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.1.1.2.1  2013/01/08 22:20:13  brajappa
 * LOG: Using stringstream instead of deprecated strstream
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 *
 * ID: $Id: ssg_trace.h,v 1.1.1.1.2.1 2013/05/20 08:56:40 jvikram Exp $
 ****************************************************************************/
#ident "$Id: ssg_trace.h,v 1.1.1.1.2.1 2013/05/20 08:56:40 jvikram Exp $"

#ifndef SSG_TRACE_H
#define SSG_TRACE_H

#include <sstream>
#include <its++.h>
#include <its_trace.h>

extern bool isDebugEnabled;
extern bool isCriticalEnabled;
extern bool isErrorEnabled;
extern bool isWarnEnabled;

/*
 * Define macros for trace variables.
 */

 
#define SSG_DEBUG          ITS_DEBUG_STRING
#define SSG_ERROR          ITS_ERROR_STRING
#define SSG_WARNING        ITS_WARNING_STRING
#define SSG_CRITICAL       ITS_CRITICAL_STRING

#define SSG_TRACE_DEBUG(x)             \
    if (isDebugEnabled)                 \
    {                                   \
        ITS_TRACE(SSG_DEBUG, x)        \
    }

#define SSG_TRACE_CRITICAL(x)          \
    if (isCriticalEnabled)              \
    {                                   \
        ITS_TRACE(SSG_CRITICAL, x)     \
    }

#define SSG_TRACE_ERROR(x)             \
    if (isErrorEnabled)                 \
    {                                   \
        ITS_TRACE(SSG_ERROR, x)        \
    }

#define SSG_TRACE_WARNING(x)           \
    if (isWarnEnabled)                  \
    {                                   \
        ITS_TRACE(SSG_WARNING, x)      \
    }

/** Interface:
 *      SsgTrace
 *      
 *  Purpose:
 *      SsgTrace class maintains all Ssgmeter stack tracing
 *
 **/
class SsgTrace
{
public:
    /********************************************************************/
    /** Purpose:
    *      Static Function to get the SsgTrace instance.
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
    *      Pointer to the singleton SsgTrace object.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    static SsgTrace* GetSsgTrace();

    /********************************************************************/
    /** Purpose:
    *      Function to Enable Trace on a per level basis.
    *
    *  Input Parameters:
    *      char *level: The Level to Enable.
    *      4 Levels SSG_DEBUG, SSG_ERROR, SSG_WARNING, SSG_CRITICAL
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      None.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    void Enable(char *level);

    /********************************************************************/
    /** Purpose:
    *      Function to Disable Trace on a per level basis.
    *
    *  Input Parameters:
    *      char *level: The Level to Disable.
    *      4 Levels SSG_DEBUG, SSG_ERROR, SSG_WARNING, SSG_CRITICAL
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      None.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    void Disable(char *level);

    /********************************************************************/
    /** Purpose:
    *      Function to Enable All Level Traces.
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
    *      None.
    *
    *  Notes:
    *      4 Levels SSG_DEBUG, SSG_ERROR, SSG_WARNING, SSG_CRITICAL
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    void Enable();

    /********************************************************************/
    /** Purpose:
    *      Function to Disable All Level Traces.
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
    *      None.
    *
    *  Notes:
    *      4 Levels SSG_DEBUG, SSG_ERROR, SSG_WARNING, SSG_CRITICAL
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    void Disable();

    void Delete();

    /********************************************************************/
    /** Purpose:
    *      Function to Display All Level Traces.
    *
    *  Input Parameters:
    *      std::ostream& os: The ostream object to display traces to.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      None.
    *
    *  Notes:
    *      4 Levels SSG_DEBUG, SSG_ERROR, SSG_WARNING, SSG_CRITICAL
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    void Display(std::ostream& os) const;

    /********************************************************************/
    /** Purpose:
    *      Function to Check whether All traces are enabled.
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
    *      true : if 4 levels are enabled
    *      false: if disabled
    *
    *  Notes:
    *      4 Levels SSG_DEBUG, SSG_ERROR, SSG_WARNING, SSG_CRITICAL
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    bool IsEnabled() const;
    bool IsDebugEnabled() const;
    bool IsCriticalEnabled() const;
    bool IsWarningEnabled() const;
    bool IsErrorEnabled() const;

    /********************************************************************/
    /** Purpose:
    *      Function to Check whether individual trace level is enabled.
    *
    *  Input Parameters:
    *      char* level.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      true : if level is enabled
    *      false: if disabled
    *
    *  Notes:
    *      4 Levels SSG_DEBUG, SSG_ERROR, SSG_WARNING, SSG_CRITICAL
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    bool IsEnabled(char* level) const;

    static void Create();

    static void Create(char *level, int mask);


private:
    static its::ITS_Mutex guard;

    SsgTrace()
    {
        isEnabled = false;
    };

    SsgTrace(const SsgTrace&){};

    bool isEnabled;

};
std::
ostream& operator<< (std::ostream& os, const SsgTrace& dt);

#define SSG_TRACE() SsgTrace::GetSsgTrace()

#define ST_DBG SSG_TRACE_DEBUG
#define ST_CRT SSG_TRACE_CRITICAL
#define ST_WRN SSG_TRACE_WARNING
#define ST_ERR SSG_TRACE_ERROR

#endif
