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
 * LOG: Revision 7.1  2002/08/26 22:09:55  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:07  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/05/16 20:10:53  mmiers
 * LOG: Locating bottlenecks.
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
 * LOG: Revision 1.2  2000/07/20 18:48:41  mmiers
 * LOG: Set the fields with the mutex held.
 * LOG:
 * LOG: Revision 1.1  2000/01/27 00:05:09  mmiers
 * LOG:
 * LOG: Make core lib smarter
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:16:30  mmiers
 * LOG: Sanitize the build environment a bit.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:53  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.8  1999/11/12 16:17:07  mmiers
 * LOG:
 * LOG:
 * LOG: Solaris fixes.
 * LOG:
 * LOG: Revision 1.7  1999/11/10 16:35:35  mmiers
 * LOG:
 * LOG:
 * LOG: Recursive mutexes for solaris.
 * LOG:
 * LOG: Revision 1.5  1998/09/30 19:09:11  jrao
 * LOG: Mutex implementations MUST NOT include trace, or recursion problems
 * LOG: will result.
 * LOG:
 * LOG: Revision 1.4  1998/06/01 16:35:34  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.3  1998/05/27 22:08:07  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.2  1998/03/12 03:50:57  mmiers
 * LOG: More corrections for the TCAP impl.  Make sure the LIST_Entry is appropriate
 * LOG: for the list type.
 * LOG:
 * LOG: Revision 1.1  1998/03/12 00:26:01  mmiers
 * LOG: Get them to build on solaris.
 * LOG:
 * LOG: Revision 1.1  1998/03/11 23:07:11  mmiers
 * LOG: Add some new files for lists, mutex protected lists, and semaphore gated
 * LOG: mutex protected lists.
 * LOG:
 * LOG: Revision 1.5  1998/02/04 18:51:03  ite
 * LOG: Debug for TCAP test applications
 * LOG:
 * LOG: Revision 1.4  1998/02/03 02:11:25  ite
 * LOG: Debug of NMS baseline.
 * LOG:
 * LOG: Revision 1.3  1998/01/28 02:01:50  rsonak
 * LOG: Forgot to complete ANSI build (Mitch).  Cleanup to reflect this.
 * LOG:
 * LOG: Revision 1.2  1998/01/27 23:34:05  mmiers
 * LOG: Finish up the port.
 * LOG:
 * LOG: Revision 1.1  1998/01/27 15:41:42  mmiers
 * LOG: NMS baseline for ITS
 * LOG:
 * LOG: Revision 1.2  1998/01/26 04:42:28  mmiers
 * LOG: Basic cleanup for NMS usage.  Need to add queue handling for correctness.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <its.h>
#include <its_types.h>
#include <its_mutex.h>

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
    if (m == NULL)
    {
        return (ITS_ENOMUTEX);
    }
    
    if (mutex_init(&m->mutex, USYNC_THREAD, NULL) != 0)
    {
        return (ITS_ENOMUTEX);
    }

    if (cond_init(&m->sleepQueue, USYNC_THREAD, NULL) != 0)
    {
        mutex_destroy(&m->mutex);
    }

    m->depthCount = initState;
    m->owner = 0;
    
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
    if (m == NULL)
    {
        return;
    }
    
    mutex_destroy(&m->mutex);
    cond_destroy(&m->sleepQueue);
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
    if (mutex_lock(&m->mutex) != 0)
    {
        return (ITS_EBADMUTEX);
    }
    
    /*
     * implicitly, I mean the following, but short circuit
     * of the first condition implies the real syntax
     * if (m->depthCount == 0 ||
     *     (m->depthCount != 0 && m->owner == thr_self())
     */
    if (m->depthCount == 0 ||
        m->owner == thr_self())
    {
        m->depthCount++;
        m->owner = thr_self();
        
        if (mutex_unlock(&m->mutex) != 0)
        {
            return (ITS_EBADMUTEX);
        }
        
        return (ITS_SUCCESS);
    }

    if (mutex_unlock(&m->mutex) != 0)
    {
        return (ITS_EBADMUTEX);
    }
    
    return (ITS_EWOULDBLOCK);
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
    if (mutex_lock(&m->mutex) != 0)
    {
        return (ITS_EBADMUTEX);
    }

    /*
     * make sure we are the owner, otherwise block.
     *
     * implicitly, I mean the following, but short circuit
     * of the first condition implies the real syntax
     * if (m->depthCount == 0 ||
     *     (m->depthCount != 0 && m->owner == thr_self())
     */
    if (m->depthCount == 0 ||
        m->owner == thr_self())
    {
        m->depthCount++;
        m->owner = thr_self();
        
        mutex_unlock(&m->mutex);
        
        return (ITS_SUCCESS);
    }
    
    /*
     * ok, it really is locked.  Wait for unlock.
     */
    while (m->depthCount != 0)
    {
        if (cond_wait(&m->sleepQueue, &m->mutex) != 0)
        {
            mutex_unlock(&m->mutex);
            
            return (ITS_EBADMUTEX);
        }
    }
    
    m->depthCount++;
    m->owner = thr_self();
    
    if (mutex_unlock(&m->mutex) != 0)
    {
        return (ITS_EBADMUTEX);
    }
    
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
    if (mutex_lock(&m->mutex) != 0)
    {
        return (ITS_EBADMUTEX);
    }
    
    if (m->depthCount == 0 ||
        m->owner != thr_self())
    {
        mutex_unlock(&m->mutex);
        
        return (ITS_EBADMUTEX);
    }
    
    m->depthCount--;
    
    if (m->depthCount == 0)
    {
        m->owner = 0;

        if (cond_signal(&m->sleepQueue) != 0)
        {
            mutex_unlock(&m->mutex);
            
            return (ITS_EBADMUTEX);
        }
    }
    
    if (mutex_unlock(&m->mutex) != 0)
    {
        return (ITS_EBADMUTEX);
    }

    return (ITS_SUCCESS);
}

#if defined(MUTEX_TEST)

#include <stdio.h>

int
main(int argc, char **argv)
{
    ITS_MUTEX m;
    
    printf("%d\n", MUTEX_CreateMutex(&m, 0));
    
    printf("Acquire\n");
    
    printf("first: %d\n", MUTEX_AcquireMutex(&m));
    
    printf("second: %d\n", MUTEX_AcquireMutex(&m));
    
    printf("releasing\n");
    
    printf("first: %d\n", MUTEX_ReleaseMutex(&m));
    
    printf("second: %d\n", MUTEX_ReleaseMutex(&m));
    
    return (0);
}

#endif
