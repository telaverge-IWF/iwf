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
 * LOG: $Log: its_condvar.c,v $
 * LOG: Revision 9.1  2005/03/23 12:53:45  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:13  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:14  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/05/16 20:10:53  mmiers
 * LOG: Locating bottlenecks.
 * LOG:
 * LOG: Revision 4.2  2001/05/16 01:19:15  mmiers
 * LOG: When cond_timedwait returns on timeout, the mutex *is* held.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.12  2001/04/05 17:45:42  mmiers
 * LOG: Proper class hierarchy for threads.
 * LOG:
 * LOG: Revision 3.11  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.10  2001/02/20 18:57:38  mmiers
 * LOG: Assert removal
 * LOG:
 * LOG: Revision 3.9  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.8  2001/02/05 22:11:59  hxing
 * LOG: Remove dead code.
 * LOG:
 * LOG: Revision 3.7  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.6  2001/01/31 00:32:58  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.5  2000/12/20 22:12:35  mmiers
 * LOG: Still condvar problems on Solaris
 * LOG:
 * LOG: Revision 3.4  2000/09/18 17:29:56  mmiers
 * LOG: Fix case where cond_wait() returns, but we don't hold
 * LOG: the mutex.
 * LOG:
 * LOG: Revision 3.3  2000/08/31 22:57:24  mmiers
 * LOG: Fix a typo, condition variable locking for Solaris.
 * LOG:
 * LOG: Revision 3.2  2000/08/16 22:31:17  labuser
 * LOG: A few snafus with solaris's lack of recursive mutexes.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:03  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.4  2000/08/09 01:13:45  mmiers
 * LOG: Platform corrections.
 * LOG:
 * LOG: Revision 1.3  2000/08/09 00:08:28  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 1.2  2000/04/25 23:03:32  mmiers
 * LOG:
 * LOG:
 * LOG: Update C service test.
 * LOG:
 * LOG: Revision 1.1  2000/04/25 14:52:55  mmiers
 * LOG:
 * LOG:
 * LOG: Add condition variable type.  Also remove race from thread
 * LOG: pool where allocated but not started thread could miss pool
 * LOG: destruction [Ricardo].
 * LOG:
 * LOG: Revision 1.1  2000/04/24 22:24:51  mmiers
 * LOG:
 * LOG:
 * LOG: Add condvar type.
 * LOG:
 *
 ****************************************************************************/

#include <sys/time.h>
#include <errno.h>

#include <its.h>
#include <its_condvar.h>
#include <its_trace.h>
#include <its_assertion.h>

#ident "$Id: its_condvar.c,v 9.1 2005/03/23 12:53:45 cvsadmin Exp $"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
 ****************************************************************************/
ITSDLLAPI int
CONDVAR_Create(ITS_CONDVAR *cv)
{
    if (cond_init(cv, USYNC_THREAD, NULL) != 0)
    {
        ITS_TRACE_ERROR(("CONDVAR_Create: can't init condvar\n"));

        return (ITS_EBADCONDVAR);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
 ****************************************************************************/
ITSDLLAPI void
CONDVAR_Delete(ITS_CONDVAR *cv)
{
    cond_destroy(cv);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
 ****************************************************************************/
ITSDLLAPI int
CONDVAR_Wait(ITS_CONDVAR *cv, ITS_MUTEX *m)
{
    int ret;

    /* Solaris needs a little help, it's mutex isn't recursive so it
     * needs a condvar itself. */

    /* we hold the mutex, but we don't hold the lock.  Make sure
     * to get it before changing depth */
    if (mutex_lock(&m->mutex) != 0)
    {
        return (ITS_EBADMUTEX);
    }

    ITS_C_ASSERT(m->owner == thr_self());
    m->depthCount--;
    ITS_C_ASSERT(m->depthCount == 0);

    cond_signal(&m->sleepQueue);

    ret = cond_wait(cv, &m->mutex);

    /*
     * we *might* not own the mutex at this point (although we should).
     * check and see if we got signalled out of order. NOTE: Solaris does
     * guarantee that we _do_ own the lock, regardless of whether the
     * wait succeeded or not.
     */
    if (m->depthCount != 0)
    {
        ITS_C_ASSERT(m->owner != thr_self());

        while (m->depthCount != 0)
        {
            if (cond_wait(&m->sleepQueue, &m->mutex) != 0)
            {
                mutex_unlock(&m->mutex);

                return (ITS_EBADMUTEX);
            }
        }
    }

    ITS_C_ASSERT(m->depthCount == 0);

    m->depthCount++;
    m->owner = thr_self();

    /* tricky part here.  We own the mutex, but we don't need to hold
     * the lock on it. */
    mutex_unlock(&m->mutex);   

    if (ret != 0)
    {
        return (ITS_EBADCONDVAR);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
 ****************************************************************************/
ITSDLLAPI int
CONDVAR_WaitWithTimeOut(ITS_CONDVAR *cv, ITS_MUTEX *m, ITS_UINT millisecs)
{
    timestruc_t totime;
    struct timeval abstime;
    int ret;

    if (millisecs == ITS_INFINITE_WAIT)
    {
        return CONDVAR_Wait(cv, m);
    }

    gettimeofday(&abstime, NULL);

    abstime.tv_sec += millisecs / 1000;
    abstime.tv_usec += (millisecs % 1000) * 1000;
    if (abstime.tv_usec > 1000000)
    {
        abstime.tv_usec -= 1000000;
        abstime.tv_sec++;
    }

    totime.tv_sec = abstime.tv_sec;
    totime.tv_nsec = abstime.tv_usec * 1000;

    /* Solaris needs a little help, it's mutex isn't recursive so it
     * needs a condvar itself. */

    /* we hold the mutex, but we don't hold the lock.  Make sure
     * to get it before changing depth */
    if (mutex_lock(&m->mutex) != 0)
    {
        return (ITS_EBADMUTEX);
    }

    ITS_C_ASSERT(m->owner == thr_self());
    m->depthCount--;
    ITS_C_ASSERT(m->depthCount == 0);

    cond_signal(&m->sleepQueue);

    ret = cond_timedwait(cv, &m->mutex, &totime);

    /*
     * we *might* not own the mutex at this point (although we should).
     * check and see if we got signalled out of order. NOTE: Solaris does
     * guarantee that we _do_ own the lock, regardless of whether the
     * wait succeeded or not.
     */
    if (m->depthCount != 0)
    {
        ITS_C_ASSERT(m->owner != thr_self());

        while (m->depthCount != 0)
        {
            if (cond_wait(&m->sleepQueue, &m->mutex) != 0)
            {
                mutex_unlock(&m->mutex);

                return (ITS_EBADMUTEX);
            }
        }
    }

    ITS_C_ASSERT(m->depthCount == 0);

    m->depthCount++;
    m->owner = thr_self();

    /* tricky part here.  We own the mutex, but we don't need to hold
     * the lock on it. */
    mutex_unlock(&m->mutex);   

    if (ret == ETIME || ret == EINTR)
    {
        return (ITS_ETIMEOUT);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
 ****************************************************************************/
ITSDLLAPI int
CONDVAR_Signal(ITS_CONDVAR *cv)
{
    cond_signal(cv);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
 ****************************************************************************/
ITSDLLAPI int
CONDVAR_Broadcast(ITS_CONDVAR *cv)
{
    cond_broadcast(cv);

    return (ITS_SUCCESS);
}

