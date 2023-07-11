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
 * ID: $Id: idc_errors.h,v 3.1 2008/03/31 10:33:00 nvijikumar Exp $
 *
 * LOG: $Log: idc_errors.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:00  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2008/03/27 11:18:28  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.1.10.1  2007/03/15 18:15:00  hbhatnagar
 * LOG: removed the unecessary macros and cleanup
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.4  2006/04/26 10:10:07  adutta
 * LOG: New registration error messages added
 * LOG:
 * LOG: Revision 1.3  2006/04/06 08:03:54  adutta
 * LOG: Reg/D-reg errors re-defined
 * LOG:
 * LOG: Revision 1.2  2006/03/14 06:39:35  adutta
 * LOG: Codec changes
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:11:15  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/
#ident "$Id: idc_errors.h,v 3.1 2008/03/31 10:33:00 nvijikumar Exp $"

#ifndef IDS_ERROR_H
#define IDS_ERROR_H 

#if defined(WIN32)
 #if defined(IDSCL_IMPLEMENTATION)
    #define MULAPP_DLLAPI __declspec(dllexport)
 #else
    #define MULAPP_DLLAPI __declspec(dllimport)
 #endif
#else
  #define MULAPP_DLLAPI
#endif


/*
 * error codes
 */
#define IDS_ENOMEM                     -1
#define IDS_ERCVFAIL                   -6
#define IDS_ESENDFAIL                  -9
#define IDS_ENOMUTEX                   -24
#define IDS_EBADMUTEX                  -25
#define IDS_ENOSOCKET                  -36
#define IDS_EINVALIDARGS               -39
#define IDS_ECONNECTFAIL               -42
#define IDS_EINUSE                     -55
#define IDS_ENULLPTR                   -61
#define IDS_ETIMEOUT                   -71
#define IDS_EMISSINGMANDPRM            -116

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


/* always last */
#define IDS_EINVALIDERR                -128
#define IDS_MAX_ERROR                  (-(IDS_EINVALIDERR))


#endif

