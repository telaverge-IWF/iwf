/******************************************************************************
 *                                                                            *
 *  Copyright 2001 - 2002 IntelliNet Technologies, Inc. All Rights Reserved.  *
 *             Manufactured in the United States of America.                  *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.         *
 *                                                                            *
 *   This product and related documentation is protected by copyright and     *
 *   distributed under licenses restricting its use, copying, distribution    *
 *   and decompilation.  No part of this product or related documentation     *
 *   may be reproduced in any form by any means without prior written         *
 *   authorization of IntelliNet Technologies and its licensors, if any.      *
 *                                                                            *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the        *
 *   government is subject to restrictions as set forth in subparagraph       *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software         *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                          *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 ******************************************************************************
 *
 * LOG: $Log: its_dsm_posix.h,v $
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.1  2003/09/23 19:59:25  mmiers
 * LOG: New implementation for POSIX shared memory (more later).
 * LOG: Bug fix for index ranges in stub.
 * LOG:
 *
 *****************************************************************************/

#if !defined(_ITS_DSM_POSIX_H_)
#define _ITS_DSM_POSIX_H_

#include <its.h>
#include <its_dsm.h>

#ident "$Id: its_dsm_posix.h,v 9.1 2005/03/23 12:52:47 cvsadmin Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/******************************************************************************
 ******************************************************************************
 **
 ** DSM POSIX implementation class declaration.
 **
 */

DSMDLLAPI extern ITS_Class itsDSM_PosixImplClass;

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_DSM_POSIX_H_ */


