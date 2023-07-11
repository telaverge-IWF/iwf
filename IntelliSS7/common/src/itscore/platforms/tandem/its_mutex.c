/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: its_mutex.c,v $
 * LOG: Revision 9.1  2005/03/23 12:53:30  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:51  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 20:20:29  mmiers
 * LOG: Add BC IDE file, add mutex API.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:55  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:07  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/03/09 16:08:26  mmiers
 * LOG: Add DLL modifier.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:39  mmiers
 * LOG: Convert rcsid to ident
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:10  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.2  2000/03/18 21:03:51  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 1.1  2000/03/01 15:44:16  mmiers
 * LOG:
 * LOG:
 * LOG: Add Tandem files.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <its.h>
#include <its_types.h>
#include <its_mutex.h>
#include <its_trace.h>

#ident "$Id: its_mutex.c,v 9.1 2005/03/23 12:53:30 cvsadmin Exp $"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function initializes a mutex to a known state (locked or
 *      unlocked).
 *
 *  Input Parameters:
 *      initState - the desired initial lock state of the mutex.  0 indicates
 *          the mutex should be created unlocked, non-zero indicates that the
 *          mutex should be created locked.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      m - the address of an ITS_MUTEX object
 *
 *  Return Value:
 *      If the mutex is successfully created, ITS_SUCCESS is returned.
 *      Any other error code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      MUTEX_DeleteMutex()
 ****************************************************************************/
ITSDLLAPI int
MUTEX_CreateMutex(ITS_MUTEX *m, int initState)
{
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method removes the mutex from the operating system's list of
 *      mutexes associated with this process.
 *
 *  Input Parameters:
 *      m - the address of the mutex to destroy
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
 *
 *  See Also:
 *      MUTEX_CreateMutex()
 ****************************************************************************/
ITSDLLAPI void
MUTEX_DeleteMutex(ITS_MUTEX *m)
{
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method tries to acquire the mutex without blocking the calling
 *      entity.
 *
 *  Input Parameters:
 *      m - the address of the mutex object to acquire
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the mutex was acquired (without blocking), ITS_SUCCESS is returned.
 *      Any other return value indicates that the mutex was not acquired,
 *          or that an IntelliSS7 error occurred.
 *
 *  Notes:
 *
 *  See Also:
 *      MUTEX_AcquireMutex()
 ****************************************************************************/
ITSDLLAPI int
MUTEX_TryAcquireMutex(ITS_MUTEX *m)
{
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function attempts to acquire the mutex.  If the mutex is
 *      currently locked, the calling entity will block until the mutex is
 *      unlocked.
 *
 *  Input Parameters:
 *      m - the address of the mutex to acquire
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the mutex was successfully acquired, ITS_SUCCESS is returned.
 *      Any other return value indicates that an IntelliSS7 error occurred.
 *
 *  Notes:
 *
 *  See Also:
 *      MUTEX_ReleaseMutex()
 ****************************************************************************/
ITSDLLAPI int
MUTEX_AcquireMutex(ITS_MUTEX *m)
{
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method unlocks an already acquired mutex.  If the mutex was not
 *      locked when this function was invoked, the results are undefined.
 *
 *  Input Parameters:
 *      m - the address of the mutex to release.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the mutex was successfully unlocked, ITS_SUCCESS is returned.
 *      Any other return value indicates an error unlocking the mutex.
 *
 *  Notes:
 *
 *  See Also:
 *      MUTEX_AcquireMutex()
 ****************************************************************************/
ITSDLLAPI int
MUTEX_ReleaseMutex(ITS_MUTEX *m)
{
    return (ITS_SUCCESS);
}
