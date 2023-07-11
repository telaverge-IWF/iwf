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
 * ID: $Id: ids_errors.h,v 3.1 2008/03/31 10:33:04 nvijikumar Exp $
 *
 * LOG: $Log: ids_errors.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2008/03/27 11:21:05  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.2.8.1  2007/03/13 05:09:58  hbhatnagar
 * LOG: IDS_APPID_REGISTERED_ALREADY added
 * LOG:
 * LOG: Revision 2.2  2006/11/07 11:50:24  kamakshilk
 * LOG: Added error code IDS_UNSUPPORTED_APP_ID
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.3  2006/04/26 10:09:31  adutta
 * LOG: New registration error messages added
 * LOG:
 * LOG: Revision 1.2  2006/04/06 07:49:59  adutta
 * LOG: Modified error codes
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:48:31  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/
#ident "$Id: ids_errors.h,v 3.1 2008/03/31 10:33:04 nvijikumar Exp $"

#ifndef IDS_ERROR_H
#define IDS_ERROR_H 

#include <its.h>
#include <its_types.h>

 
#if defined(WIN32)
 #if defined(MABCL_IMPLEMENTATION)
    #define MULAPP_DLLAPI __declspec(dllexport)
 #else
    #define MULAPP_DLLAPI __declspec(dllimport)
 #endif
#else
  #define MULAPP_DLLAPI
#endif


/* Registration Errors */
#define IDS_APP_ID_REGISTERED_ALREADY                 -120
#define IDS_UNSUPPORTED_APP_ID                        -121
#define IDS_CLIENT_DUPLICATE_ENTRY                    -122
#define IDS_ROUTING_CRITERIA_DUPLICATE_ENTRY          -123
#define IDS_ROUTING_CRITERIA_INVALID                  -124
#define IDS_NOT_REGISTERED                            -125

/* Decode Error */
#define IDS_REGISTRATION_DECODE_FAIL                  -126
#define IDS_DIAMETER_DECODE_FAIL                      -127


#endif

