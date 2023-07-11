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
 * ID: $Id: DIAMon_trace.h,v 3.1 2008/03/31 10:33:28 nvijikumar Exp $
 *
 * LOG: $Log: DIAMon_trace.h,v $
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
#ident "$Id: DIAMon_trace.h,v 3.1 2008/03/31 10:33:28 nvijikumar Exp $"

//
// header for the DIAMON trace
//

#if !defined(_DIAMON_TRACE_H_)
#define _DIAMON_TRACE_H_

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif

#include <its++.h>
#include <its_trace.h>

using namespace its;


#define DIAMON_DEBUG          "DIAMON_DBG"
#define DIAMON_ERROR          "DIAMON_ERR"
#define DIAMON_WARNING        "DIAMON_WRN"
#define DIAMON_CRITICAL       "DIAMON_CRI"

extern its::ITS_TraceLevel adpMonTraceDEBUG;
extern its::ITS_TraceLevel adpMonTraceWARNING;
extern its::ITS_TraceLevel adpMonTraceERROR;
extern its::ITS_TraceLevel adpMonTraceCRITICAL;

//
// trap generation
//

#if defined(DO_SNMP)

#define SEND_ALARM DIA_EVENT_MGMT.SendEvent

#else

//#define SEND_ALARM (void)

#endif

// Traces for DIA_Monitor
#define DIAMON_TRACE_DEBUG(x)           \
        ITS_TRACE(DIAMON_DEBUG, x)

#define DIAMON_TRACE_ERROR(x)           \
        ITS_TRACE(DIAMON_ERROR,x)

#define DIAMON_TRACE_WARNING(x)         \
        ITS_TRACE(DIAMON_WARNING,x)

#define DIAMON_TRACE_CRITICAL(x)        \
        ITS_TRACE(DIAMON_CRITICAL,x)

void EnableDIAMONTracing();
void EnableDIAMONDebugTracing();
void EnableDIAMONErrorTracing();
void EnableDIAMONWarningTracing();
void EnableDIAMONCriticalTracing();


#endif    // !defined(_DIAMON_TRACE_H_)
