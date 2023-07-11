/*********************************-*-DIA-*-**********************************
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
 * LOG: $Log: app_trace.h,v $
 * LOG: Revision 1.1.2.1  2013/02/12 14:11:30  jvikas
 * LOG: Map Simulator Changes for IWF
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/31 14:52:10  lakshman
 * LOG: add includes.
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_trace.h,v 1.1.2.1 2013/02/12 14:11:30 jvikas Exp $"

#ifndef SAMPLE_APP_TRACE_H
#define SAMPLE_APP_TRACE_H

#include <its++.h>
#include <its_trace.h>

/*
 * Define macros for trace variables. Based on Accelero Tracing Mechanism
 */

#define APP_DEBUG          ITS_DEBUG_STRING 
#define APP_ERROR          ITS_ERROR_STRING 
#define APP_WARNING        ITS_WARNING_STRING 
#define APP_CRITICAL       ITS_CRITICAL_STRING 

/* Macro to log/display the DEBUG trace messages
*/
#define APP_TRACE_DEBUG(x) \
              ITS_TRACE(APP_DEBUG, x)

/* Macro to log/display the CRITICAL error messages
*/
#define APP_TRACE_CRITICAL(x) \
              ITS_TRACE(APP_CRITICAL, x)

/* Macro to log/display the error messages
*/
#define APP_TRACE_ERROR(x) \
              ITS_TRACE(APP_ERROR, x)

/* Macro to log/display the WARNING messages
*/
#define APP_TRACE_WARNING(x) \
              ITS_TRACE(APP_WARNING, x)

void EnableAppTracing();

void DisableAPPTracing();

#endif
