//////////////////////////////////-*-h-*-/////////////////////////////////////
//                                                                          //
//     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    //
//             Manufactured in the United States of America.                //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                          //
//   This product and related documentation is protected by copyright and   //
//   distributed under licenses restricting its use, copying, distribution  //
//   and decompilation.  No part of this product or related documentation   //
//   may be reproduced in any form by any means without prior written       //
//   authorization of IntelliNet Technologies and its licensors, if any.    //
//                                                                          //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      //
//   government is subject to restrictions as set forth in subparagraph     //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software       //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// CONTRACT: INTERNAL                                                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//
//   ID: $Id: codec_trace.h,v 1.1.2.6 2010/04/29 13:02:11 pvenkatarao Exp $
//
//   LOG: $Log: codec_trace.h,v $
//   LOG: Revision 1.1.2.6  2010/04/29 13:02:11  pvenkatarao
//   LOG: Added code to make LCS Codec traces on/off based on env LCS_CODEC_TRACE=ON/OFF
//   LOG:
//   LOG: Revision 1.1.2.5  2010/04/15 09:37:57  ssingh
//   LOG: compilation error removed
//   LOG:
//   LOG: Revision 1.1.2.4  2010/03/31 05:47:14  rajeshak
//   LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//   LOG:
//   LOG: Revision 1.1.2.3  2010/03/23 04:57:09  nvijikumar
//   LOG: Removed PRT header, print header implementation need to be moved to .c
//   LOG:
//   LOG: Revision 1.1.2.2  2010/03/19 11:41:02  rajeshak
//   LOG: Removing IntelliSS7 dependency from Codec
//   LOG:
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _CODEC_TRACE_H
#define _CODEC_TRACE_H

#include <stdio.h>
#include <pthread.h>

typedef unsigned int     ITS_BOOLEAN;
typedef unsigned char    ITS_OCTET;
typedef unsigned short   ITS_USHORT;
typedef unsigned int     ITS_UINT;
typedef unsigned long    ITS_ULONG;
typedef char             ITS_CHAR;
typedef short            ITS_SHORT;
typedef int              ITS_INT;
typedef long             ITS_LONG;


#define CODEC_SUCCESS   (0U)
/*
 * yes/no, true/false
 */
#define ITS_NO        (0U)
#define ITS_YES       (~ITS_NO)
#define ITS_FALSE     ITS_NO
#define ITS_TRUE      ITS_YES

#ifdef CODEC_TRACE_ON
#define CODEC_TRACE_CRITICAL(x) \
     printf("FATAL: File: %s Line: %d ",__FILE__, __LINE__); \
     printf x; printf("\n"); fflush(stdout);
#else
#define CODEC_TRACE_CRITICAL(x)
#endif

#ifdef CODEC_TRACE_ON
#define CODEC_TRACE_ERROR(x) \
     printf("ERROR   : File: %s Line: %d ",__FILE__, __LINE__); \
     printf x; printf("\n"); fflush(stdout);
#else
#define CODEC_TRACE_ERROR(x)
#endif

#ifdef CODEC_TRACE_ON
#define CODEC_TRACE_WARNING(x) \
     printf("MINOR   : File: %s Line: %d ",__FILE__, __LINE__); \
     printf x; printf("\n"); fflush(stdout);
#else
#define CODEC_TRACE_WARNING(x)
#endif

#ifdef CODEC_TRACE_ON
    #ifdef DEBUG
    #define CODEC_TRACE_DEBUG(x) \
         printf("DEBUG   : File: %s Line: %d ",__FILE__, __LINE__); \
         printf x; printf("\n"); fflush(stdout);
    #else
    #define CODEC_TRACE_DEBUG(x)
    #endif
#else
#define CODEC_TRACE_DEBUG(x)
#endif


#endif
