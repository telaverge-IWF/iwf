/****************************************************************************
 *                                                                          *
 *     Copyright 2012 Diametriq, LLC All Rights Reserved.                   *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.       *
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
 ****************************************************************************/

#ifndef ITS_DRE_EXIT_ERROR_CODES_H
#define ITS_DRE_EXIT_ERROR_CODES_H


//License viloation errors
#define ITS_LICENSE_INVALID_HOST_ID 101
#define ITS_LICENSE_FILE_OPENING_ERROR  102
#define ITS_LICENSE_MALFORMED_LICENSE_DATA 103
#define ITS_LICENSE_INVALID_DATA 104
#define ITS_LICENSE_WRITING_ERROR 105
#define ITS_LICENSE_CORRUPTED_MUTEX 106
#define ITS_LICENSE_VERSION_MISMATCH 107
#define ITS_LICENSE_EXPIRED 108
#define ITS_LICENSE_CLOCK_REVERSED 110
#define ITS_LICENSE_DURATION_EXCEEDED 111
#define ITS_LICENSE_CAPABILITY_VIOLATION 112

#define ITS_DRE_CONFIG_FETCH_ERROR 113
#define ITS_DRE_CONFIG_FILE_ERROR 114
#define ITS_PROCESS_UNSTABLE_ERROR 115

//Replication failure errors
#define ITS_DRE_REPLICATION_INIT_FAILURE 130
#endif /* ITS_DRE_EXIT_ERROR_CODES_H */
