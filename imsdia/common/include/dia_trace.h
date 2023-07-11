/*********************************-*-CPP-*-**********************************
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
 * LOG: $Log: dia_trace.h,v $
 * LOG: Revision 3.3.64.2  2013/02/27 08:49:06  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.3.64.1  2013/02/01 11:34:15  pramana
 * LOG: Merged from branch 0212 to 0300.
 * LOG:
 * LOG: Revision 3.3.24.2  2013/01/18 11:21:52  millayaraja
 * LOG: updated for stack syslog
 * LOG:
 * LOG: Revision 3.3  2008/12/10 11:01:42  nvijikumar
 * LOG: Use local flag to check TraceLevel ON/OFF
 * LOG:
 * LOG: Revision 3.2  2008/10/28 12:00:22  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.1.2.1  2008/09/16 09:36:39  nvijikumar
 * LOG: Local flags are used to check trace level enabled or not
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:22  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2006/09/14 12:45:52  yranade
 * LOG: Check Global Enable flag before tracing.
 * LOG:
 * LOG: Revision 2.2  2006/09/13 10:08:51  yranade
 * LOG: ITS-Diameter specific updates.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.4  2006/05/04 20:44:44  yranade
 * LOG: IsEnabled on a per level basis.
 * LOG:
 * LOG: Revision 1.3  2006/05/04 20:27:23  yranade
 * LOG: API to check whether traces are enabled.
 * LOG:
 * LOG: Revision 1.2  2006/04/27 15:57:41  yranade
 * LOG: Converted to a Trace Class.
 * LOG:
 * LOG: Revision 1.1  2006/03/02 13:03:08  tpanda
 * LOG: Building IMS Infrastructure
 * LOG:
 *
 * ID: $Id: dia_trace.h,v 3.3.64.2 2013/02/27 08:49:06 jvikram Exp $
 ****************************************************************************/
#ident "$Id: dia_trace.h,v 3.3.64.2 2013/02/27 08:49:06 jvikram Exp $"

#ifndef DIA_TRACE_H
#define DIA_TRACE_H

#include <strstream>
#include <its++.h>
#include <its_trace.h>

extern its::TraceLevel    *diaDebugTrace;
extern its::TraceLevel    *diaErrorTrace;
extern its::TraceLevel    *diaCriticalTrace;
extern its::TraceLevel    *diaWarningTrace;

extern bool isDebugEnabled;
extern bool isCriticalEnabled;
extern bool isErrorEnabled;
extern bool isWarnEnabled;

/*
 * Define macros for trace variables.
 */

#define DIA_DEBUG          "DIA_DEBUG" 
#define DIA_ERROR          "DIA_ERROR" 
#define DIA_WARNING        "DIA_WARN" 
#define DIA_CRITICAL       "DIA_CRIT" 

#define DIA_TRACE_DEBUG(x)               \
    if (isDebugEnabled)                  \
    {                                    \
        ITS_TRACE(DIA_DEBUG, x)          \
    }

#define DIA_TRACE_CRITICAL(x)            \
    if (isCriticalEnabled)               \
    {                                    \
        ITS_TRACE(DIA_CRITICAL, x)       \
    }

#define DIA_TRACE_ERROR(x)               \
    if (isErrorEnabled)                  \
    {                                    \
        ITS_TRACE(DIA_ERROR, x)          \
    }

#define DIA_TRACE_WARNING(x)             \
    if (isWarnEnabled)                   \
    {                                    \
        ITS_TRACE(DIA_WARNING, x)        \
    }

/** Interface:
 *      DiaTrace
 *      
 *  Purpose:
 *      DiaTrace class maintains all Diameter stack tracing
 *
 **/
class DiaTrace
{
public:
    /********************************************************************/
    /** Purpose:
    *      Static Function to get the DiaTrace instance.
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
    *      Pointer to the singleton DiaTrace object.
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
    static DiaTrace* GetDiaTrace();

    /********************************************************************/
    /** Purpose:
    *      Function to Enable Trace on a per level basis.
    *
    *  Input Parameters:
    *      char *level: The Level to Enable.
    *      4 Levels DIA_DEBUG, DIA_ERROR, DIA_WARNING, DIA_CRITICAL
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
    //Warning fix - deprecated conversion from string constant to char*
    void Enable(const char *level);

    /********************************************************************/
    /** Purpose:
    *      Function to Disable Trace on a per level basis.
    *
    *  Input Parameters:
    *      char *level: The Level to Disable.
    *      4 Levels DIA_DEBUG, DIA_ERROR, DIA_WARNING, DIA_CRITICAL
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
    void Disable(const char *level);

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
    *      4 Levels DIA_DEBUG, DIA_ERROR, DIA_WARNING, DIA_CRITICAL
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
    *      4 Levels DIA_DEBUG, DIA_ERROR, DIA_WARNING, DIA_CRITICAL
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
    *      4 Levels DIA_DEBUG, DIA_ERROR, DIA_WARNING, DIA_CRITICAL
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
    *      4 Levels DIA_DEBUG, DIA_ERROR, DIA_WARNING, DIA_CRITICAL
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
    *      4 Levels DIA_DEBUG, DIA_ERROR, DIA_WARNING, DIA_CRITICAL
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    //Warning fix - deprecated conversion from string constant to char*
    bool IsEnabled(const char* level) const;

    static void Create();

    //Warning fix - deprecated conversion from string constant to char*
    static void Create(const char *level, int mask);


private:
    static its::ITS_Mutex guard;

    //Initializing Uninitialized Scalar Field
    DiaTrace(){isEnabled = false;};

    DiaTrace(const DiaTrace&){};

    bool isEnabled;

};
std::
ostream& operator<< (std::ostream& os, const DiaTrace& dt);

#define DIA_TRACE() DiaTrace::GetDiaTrace()

#endif
