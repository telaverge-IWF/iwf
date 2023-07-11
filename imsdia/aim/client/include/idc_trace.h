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
 * LOG: $Log: idc_trace.h,v $
 * LOG: Revision 3.3.66.1  2013/02/27 08:49:06  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.3  2008/11/06 06:38:58  nvijikumar
 * LOG: Changes for solaris compilation problem
 * LOG:
 * LOG: Revision 3.2  2008/10/28 12:03:32  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:00  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2007/01/19 13:00:18  kamakshilk
 * LOG: CreateTracing and DeleteTracing APIs added
 * LOG:
 * LOG: Revision 2.2  2006/10/31 10:00:06  kamakshilk
 * LOG: IDSCL_Print function added
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:11:15  adutta
 * LOG: First cut
 * LOG:
 *
 * ID: $Id: idc_trace.h,v 3.3.66.1 2013/02/27 08:49:06 jvikram Exp $
 ****************************************************************************/
#ident "$Id: idc_trace.h,v 3.3.66.1 2013/02/27 08:49:06 jvikram Exp $"

#ifndef IDS_TRACE_H
#define IDS_TRACE_H

#include <its_trace.h>


/*
 * Define macros for trace variables.
 */

#define IDS_DEBUG          "DiaDbg" 
#define IDS_ERROR          "DiaErr" 
#define IDS_WARNING        "DiaWarn" 
#define IDS_CRITICAL       "DiaCrit" 


#define IDS_TRACE_DEBUG(x)           \
    if (IDSCL_IsTraceEnabled())      \
    {        		             \
        ITS_TRACE(IDS_DEBUG, x)      \
    }

#define IDS_TRACE_CRITICAL(x)        \
    if (IDSCL_IsTraceEnabled())      \
    {                                \
        ITS_TRACE(IDS_CRITICAL, x)   \
    }

#define IDS_TRACE_ERROR(x)           \
    if (IDSCL_IsTraceEnabled())      \
    {                                \
        ITS_TRACE(IDS_ERROR, x)      \
    }

#define IDS_TRACE_WARNING(x)         \
    if (IDSCL_IsTraceEnabled())      \
    {                                \
        ITS_TRACE(IDS_WARNING, x)    \
    }

extern "C"
{
void
IDSCL_EnableTracing();

bool
IDSCL_IsTraceEnabled();
                                                                                
//Warning fix - deprecated conversion from string constant to char*
bool
IDSCL_IsEnabled(const char *level);

void
IDSCL_DisableTracing();

void
IDSCL_CreateTracing();

void
IDSCL_DeleteTracing();

}

#endif
