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
 * LOG: $Log: dcca_trace.h,v $
 * LOG: Revision 3.1.110.1  2014/08/26 10:24:47  pramana
 * LOG: Logging related refinements
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2006/11/24 16:28:04  hbhatnagar
 * LOG: made changes for the key as Session Index and proper indentation done
 * LOG:
 * LOG: Revision 2.2  2006/11/14 10:18:04  hbhatnagar
 * LOG: shifted the namespace to .cpp
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:55  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/25 08:28:09  nvijikumar
 * LOG: Converted the files from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:19:50  nvijikumar
 * LOG: Made the dcca trace object as singleton (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_trace.h,v 3.1.110.1 2014/08/26 10:24:47 pramana Exp $
 *
 ****************************************************************************/

#ifndef DCCA_TRACE_H
#define DCCA_TRACE_H

/**
 * Includes
 */
#include <its++.h>
#include <its_trace.h>

/**
 * Defines
 */
#define DCCA_DEBUG    "Dcca-Debug" 
#define DCCA_ERROR    "Dcca-Error" 
#define DCCA_WARNING  "Dcca-Warning" 
#define DCCA_CRITICAL "Dcca-Critical" 

/**
 * Macros
 */
#if 0
#define DCCA_TRACE_DEBUG(x)    ITS_TRACE(DCCA_DEBUG, x)
#define DCCA_TRACE_ERROR(x)    ITS_TRACE(DCCA_ERROR, x)
#define DCCA_TRACE_WARNING(x)  ITS_TRACE(DCCA_WARNING, x)
#define DCCA_TRACE_CRITICAL(x) ITS_TRACE(DCCA_CRITICAL, x)
#else
#define DCCA_TRACE_DEBUG(x)    DT_DBG(x)
#define DCCA_TRACE_ERROR(x)    DT_ERR(x)
#define DCCA_TRACE_WARNING(x)  DT_WRN(x)
#define DCCA_TRACE_CRITICAL(x) DT_CRT(x)
#endif

/****************************************************************************
 *
 *  Interface: DCCATrace Class
 *      
 *  Purpose  : To implement DCCA trace
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *
 ****************************************************************************/
class DCCATrace
{
public:
    /**
     * Singleton
     */
    static DCCATrace* GetDCCATrace();        
    /**
     * Destructor
     */
    ~DCCATrace();        
    /**
     * To enable trace
     */
    void DCCAEnableTrace();
    /**
     * To disable trace
     */
    void DCCADisableTrace();

 private:
    /**
     * Constructor
     */
    DCCATrace();
    /**
     * Trace objects
     */            
    its::TraceLevel *dccaDebugTrace;        
    its::TraceLevel *dccaErrorTrace;
    its::TraceLevel *dccaWarningTrace;
    its::TraceLevel *dccaCriticalTrace;
};

#endif
