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
 * LOG: $Log: its_thread.c,v $
 * LOG: Revision 9.1.136.1  2011/04/13 07:36:19  nvijikumar
 * LOG: Merging diamter branch changes
 * LOG:
 * LOG: Revision 1.2  2008/08/29 13:00:27  vnarang
 * LOG: On the basis Thread Type DETACHED threads are created
 * LOG:
 * LOG: Revision 1.1.1.1  2008/08/07 13:50:15  vnarang
 * LOG: Light wieght IntelliSS7 ( AcceleroCore)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:43  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:13  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.14.1.6.1  2005/01/05 07:21:28  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.2.14.1  2004/09/29 09:56:14  asingh
 * LOG: Changes for linux ES 30 operating system; compilation issue.
 * LOG:
 * LOG: Revision 7.2  2002/10/01 15:06:29  mmiers
 * LOG: Add API for yielding CPU
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.7  2001/12/12 20:40:18  hdivoux
 * LOG: Added function to get thread ID of calling thread.
 * LOG:
 * LOG: Revision 5.6  2001/11/09 16:39:20  mmiers
 * LOG: More mempool work.
 * LOG:
 * LOG: Revision 5.5  2001/11/09 00:27:28  mmiers
 * LOG: Allocate mempool at thread startup.
 * LOG:
 * LOG: Revision 5.4  2001/11/08 22:30:45  mmiers
 * LOG: local storage API needs to be visible to external users.
 * LOG:
 * LOG: Revision 5.3  2001/11/08 21:20:03  mmiers
 * LOG: Get the signature right.
 * LOG:
 * LOG: Revision 5.2  2001/11/08 20:47:38  mmiers
 * LOG: A better performing mem pool implementation.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:14  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.8  2001/04/25 00:39:54  mmiers
 * LOG: Fix up termination semantics on Linux.
 * LOG:
 * LOG: Revision 3.7  2001/04/05 17:45:42  mmiers
 * LOG: Proper class hierarchy for threads.
 * LOG:
 * LOG: Revision 3.6  2001/04/05 16:52:16  mmiers
 * LOG: Proper class hierarchy for thread.
 * LOG:
 * LOG: Revision 3.5  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:58  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:03  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.5  2000/08/10 01:42:55  mmiers
 * LOG: Block SIGCHLD too.
 * LOG:
 * LOG: Revision 1.4  2000/05/03 21:07:18  mmiers
 * LOG:
 * LOG:
 * LOG: Start adding support for reader/writer locks.
 * LOG: Add SOCK_GetPeerName().
 * LOG:
 * LOG: Revision 1.3  2000/04/25 23:30:03  mmiers
 * LOG:
 * LOG:
 * LOG: Platform cleanup.
 * LOG:
 * LOG: Revision 1.2  2000/04/25 23:03:32  mmiers
 * LOG:
 * LOG:
 * LOG: Update C service test.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:16:29  mmiers
 * LOG: Sanitize the build environment a bit.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:15  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.13  1999/11/22 19:23:33  mmiers
 * LOG:
 * LOG:
 * LOG: Cleanup from Linux build.  Removed nested comment in iniparse,
 * LOG: cleaned up decls in gdi_trans.
 * LOG:
 * LOG: Revision 1.12  1999/10/11 16:07:45  mmiers
 * LOG:
 * LOG:
 * LOG: Correct mask initialization in sigaction struct.
 * LOG:
 * LOG: Revision 1.11  1999/10/07 22:28:01  labuser
 * LOG:
 * LOG:
 * LOG: Find the termination problem with Brite applications.  Due to
 * LOG: not so great signal handling and resource leak.
 * LOG:
 * LOG: Revision 1.10  1999/08/23 01:12:09  mmiers
 * LOG:
 * LOG:
 * LOG: Add signal mask handling correctly.
 * LOG:
 * LOG: Revision 1.9  1999/08/22 22:27:58  labuser
 * LOG:
 * LOG:
 * LOG: Modernize thread handling on these.
 * LOG:
 * LOG: Revision 1.8  1998/11/19 02:18:29  mmiers
 * LOG: Straighten out a few potential bugs.
 * LOG:
 * LOG: Revision 1.7  1998/11/09 23:17:12  mmiers
 * LOG: Avoid race conditions on suspended thread creation.
 * LOG:
 * LOG: Revision 1.6  1998/10/01 01:32:08  mmiers
 * LOG: Linux is identical to digital.
 * LOG:
 * LOG: Revision 1.1  1998/10/01 00:01:56  mmiers
 * LOG: Port to digital unix
 * LOG:
 * LOG: Revision 1.3  1998/09/30 20:33:30  jrao
 * LOG: Fix a number of release bugs with pthread_cond_t(s).
 * LOG:
 * LOG: Revision 1.4  1998/09/23 23:13:01  jrao
 * LOG: Finish adding trace.
 * LOG:
 * LOG: Revision 1.3  1998/09/23 19:37:51  jrao
 * LOG: HPUX support fixes.
 * LOG:
 * LOG: Revision 1.2  1998/09/22 22:36:34  jrao
 * LOG: Hacks for POSIX threads (Suspend()/Resume()).  An attempt to allow the
 * LOG: user to start suspended threads.
 * LOG:
 * LOG: Revision 1.1  1998/09/22 16:01:35  jrao
 * LOG: Port to HPUX.  Some work still needs to be done with threading -- using
 * LOG: condition variables to support Suspend()/Resume().
 * LOG:
 * LOG: Revision 1.1  1998/06/20 03:50:38  mmiers
 * LOG: Add Linux as a target.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <its.h>
#include <its_types.h>
#include <its_thread.h>
#include <its_trace.h>
#include <its_condvar.h>
#include <its_mem_pool.h>

#ident "$Id: its_thread.c,v 9.1.136.1 2011/04/13 07:36:19 nvijikumar Exp $"

/*
 * context for thread local storage.
 */
static pthread_key_t    ctxt;

/*
 * register for this so that we (a) don't restart interrupted syscalls,
 * and (b) don't take the default behavior of crapping out.
 */
static void
sigusr1(int signal)
{
}

/*
 * POSIX_START:
 *
 * A way to create POSIX threads in the suspended mode.
 */
static THREAD_RET_TYPE
startSuspended(void *arg)
{
    ITS_THREAD* curThread = (ITS_THREAD *)arg;
    sigset_t newset;
    struct sigaction action;
    MEMPOOL_Manager *m;
    THREAD_RET_TYPE ret;

    /*
     * this is a little weird, I know.  Keep this in mind:
     * 1) A thread can't preempt itself.
     * 2) No other thread can see this store.
     */
    if ((m = MEMPOOL_CreateHeapPool(MEMPOOL_POWERS_DEFAULT)) == NULL)
    {
        ITS_TRACE_CRITICAL(("StartSuspended: MEMPOOL_CreateHeapPool failed\n"));
        abort();
    }

    if (THREAD_SetLocalStorage(m) != ITS_SUCCESS)
    {
        MEMPOOL_DestroyPool(m);
        ITS_TRACE_CRITICAL(("StartSuspended: THREAD_SetLocalStorage failed\n"));
        abort();
    }

    action.sa_handler = sigusr1;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &action, NULL);

    sigemptyset(&newset);
    sigaddset(&newset, SIGINT);
    sigaddset(&newset, SIGTERM);
    sigaddset(&newset, SIGSTOP);
    sigaddset(&newset, SIGCONT);
    sigaddset(&newset, SIGHUP);
    sigaddset(&newset, SIGKILL);
    sigaddset(&newset, SIGCHLD);

    pthread_sigmask(SIG_BLOCK, &newset, NULL);

    if (MUTEX_AcquireMutex(&curThread->thread.condMutex) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("THREAD_(startSuspended): can't acquire mutex\n"));
 
        THREAD_ThreadExit(NULL);
    }
 
    while (!curThread->thread.runnable)
    {
        if (CONDVAR_Wait(&curThread->thread.sleepQueue,
                         &curThread->thread.condMutex) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("THREAD_(startSuspended): can't wait cond\n"));
 
            THREAD_ThreadExit(NULL);
        }
    }
 
    MUTEX_ReleaseMutex(&curThread->thread.condMutex);

    ret = (*curThread->thread.threadFunc)(curThread->thread.threadArg);

    if ((m = (MEMPOOL_Manager *)THREAD_GetLocalStorage()) != NULL)
    {
        MEMPOOL_DestroyPool(m);

        THREAD_SetLocalStorage(NULL);
    }

    return (ret);
}

/*
 * start running.
 */
static THREAD_RET_TYPE
startNormal(void *arg)
{
    ITS_THREAD* curThread = (ITS_THREAD *)arg;
    sigset_t newset;
    struct sigaction action;
    MEMPOOL_Manager *m;
    THREAD_RET_TYPE ret;

    /*
     * this is a little weird, I know.  Keep this in mind:
     * 1) A thread can't preempt itself.
     * 2) No other thread can see this store.
     */
    if ((m = MEMPOOL_CreateHeapPool(MEMPOOL_POWERS_DEFAULT)) == NULL)
    {
        ITS_TRACE_CRITICAL(("StartNormal: MEMPOOL_CreateHeapPool failed\n"));
        abort();
    }

    if (THREAD_SetLocalStorage(m) != ITS_SUCCESS)
    {
        MEMPOOL_DestroyPool(m);
        ITS_TRACE_CRITICAL(("StartNormal: THREAD_SetLocalStorage failed\n"));
        abort();
    }

    action.sa_handler = sigusr1;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGUSR1, &action, NULL);

    sigemptyset(&newset);
    sigaddset(&newset, SIGINT);
    sigaddset(&newset, SIGTERM);
    sigaddset(&newset, SIGSTOP);
    sigaddset(&newset, SIGCONT);
    sigaddset(&newset, SIGHUP);
    sigaddset(&newset, SIGKILL);
    sigaddset(&newset, SIGCHLD);

    pthread_sigmask(SIG_BLOCK, &newset, NULL);

    ret = (*curThread->thread.threadFunc)(curThread->thread.threadArg);

    if ((m = (MEMPOOL_Manager *)THREAD_GetLocalStorage()) != NULL)
    {
        MEMPOOL_DestroyPool(m);

        THREAD_SetLocalStorage(NULL);
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function creates a thread.
 *
 ****************************************************************************/
static int
InitThread(ITS_Object obj, va_list args)
{
    ITS_THREAD *t = (ITS_THREAD *)obj;
    pthread_attr_t attr;
    int ret;
    int stackSize;
    ITS_THREAD_FUNC entryPoint;
    void *arg;
    ITS_BOOLEAN running;

    stackSize = va_arg(args, int);
    entryPoint = va_arg(args, ITS_THREAD_FUNC);
    arg = va_arg(args, void *);
    running = va_arg(args, ITS_BOOLEAN);

    ITS_TRACE_DEBUG(("THREAD_CreateThread:\n"));

    t->thread.threadFunc = entryPoint;
    t->thread.threadArg = arg;
    t->thread.runnable = running;
    t->thread.constructed = ITS_FALSE;
    t->thread.stackSize = stackSize;

    /* create the mutex */
    if (MUTEX_CreateMutex(&t->thread.condMutex, 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("THREAD_CreateThread: can't create cond mutex\n"));

        return (ITS_EBADMUTEX);
    }

    if (CONDVAR_Create(&t->thread.sleepQueue) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("THREAD_CreateThread: can't init condvar\n"));

        MUTEX_DeleteMutex(&t->thread.condMutex);

        return (ITS_EBADCONDVAR);
    }

    pthread_attr_init(&attr);
    if(t->thread.thrType == DETACHED)
    { 
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    }

    if (stackSize != 0)
    {
        pthread_attr_setstacksize(&attr, stackSize);
    }

    if (running)
    {
        if ((ret = pthread_create(&t->thread.thread, &attr,
                                  startNormal, (void *)t)) != 0)
        {
            ITS_TRACE_ERROR(("THREAD_CreateThread: can't create thread ret=%d\n", ret));


            CONDVAR_Delete(&t->thread.sleepQueue);

            MUTEX_DeleteMutex(&t->thread.condMutex);

            return (ITS_ENOTHREAD);
        }
    }
    else
    {
        if ((ret = pthread_create(&t->thread.thread, &attr,
                                  startSuspended, (void *)t)) != 0)
        {
            ITS_TRACE_ERROR(("THREAD_CreateThread: can't create thread ret=%d\n", ret));

            CONDVAR_Delete(&t->thread.sleepQueue);

            MUTEX_DeleteMutex(&t->thread.condMutex);

            return (ITS_ENOTHREAD);
        }
    }

    t->thread.constructed = ITS_TRUE;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function destroys a thread.
 *
 ****************************************************************************/
static void
DestroyThread(ITS_Object obj)
{
    ITS_THREAD *t = (ITS_THREAD *)obj;

    ITS_TRACE_DEBUG(("THREAD_DeleteThread:\n"));

    CONDVAR_Delete(&t->thread.sleepQueue);

    MUTEX_DeleteMutex(&t->thread.condMutex);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a key for thread local storage.
 *
 *  Input Parameters:
 *      objClass - the class to init.
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
static int
ClassInit(ITS_Class objClass)
{
    if (pthread_key_create(&ctxt, NULL) != 0)
    {
        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a key for thread local storage.
 *
 *  Input Parameters:
 *      objClass - the class to init.
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
static void
ClassTerm(ITS_Class objClass)
{
    pthread_key_delete(ctxt);
}

/*
 * thread class record
 */
ITSDLLAPI ITS_ClassRec itsTHREAD_ClassRec =
{
    {
        &itsCORE_ClassRec,
        sizeof(ITS_THREAD),
        ITS_FALSE,
        0,
        "THREAD Class",
        ClassInit,
        ClassTerm,
        ITS_CLASS_PART_NO_INIT,
        ITS_CLASS_PART_NO_DEST,
        InitThread,
        DestroyThread,
        ITS_INST_CLONE_INHERIT,
        ITS_INST_PRINT_INHERIT,
        ITS_INST_SERIAL_INHERIT,
        ITS_INST_EQUALS_INHERIT,
        ITS_INST_HASH_INHERIT,
        NULL
    }
};
ITSDLLAPI ITS_Class itsTHREAD_Class = &itsTHREAD_ClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function creates a thread.  The thread is created "running",
 *      and will begin executing the C function provided.
 *
 *  Input Parameters:
 *      stackSize - the initial stack size for the thread.
 *      entryPoint - a pointer to the function that the thread is to execute
 *      arg - the argument to the function that the thread is to execute
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      t - a pointer to the thread object to be initialized
 *
 *  Return Value:
 *      If the thread is created successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an error.
 *
 *  Notes:
 *      Passing a stackSize of 0 to this function is a hint to the operating
 *      system to use the default thread stack size.  Usually, passing 0
 *      is recommended, as the thread creation can be significantly faster
 *      when the default is used.
 *
 *  See Also:
 *      THREAD_DeleteThread()
 ****************************************************************************/
ITSDLLAPI int
THREAD_CreateThread(ITS_THREAD *t, int stackSize,
                    ITS_THREAD_FUNC entryPoint, void *arg,
                    ITS_BOOLEAN running)
{
    ITS_Object ret;

    ret = ITS_ConstructObjectIn(t, itsTHREAD_Class, stackSize,
                                 entryPoint, arg, running);

    if (ret != (ITS_Object)t)
    {
        return (ITS_EINVALIDARGS);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function frees any resources that should be released by a thread
 *      after it terminates.
 *
 *  Input Parameters:
 *      t - the thread to clean up after.
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
 *      This routine is a no-op for Solaris.
 *      This routine must NOT be called before the thread exits.
 *
 *  See Also:
 *      THREAD_CreateThread()
 ****************************************************************************/
ITSDLLAPI void
THREAD_DeleteThread(ITS_THREAD *t)
{
    ITS_DestructObject((ITS_Object)t);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function suspends a thread.  In practice, this means the thread
 *      will not be scheduled until it resumes.  The result of suspending a
 *      suspended thread is not defined.
 *
 *  Input Parameters:
 *      t - the thread to suspend
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the thread was suspended, ITS_SUCCESS is returned.
 *      Any other return value indicates an error.
 *
 *  Notes:
 *      A thread may call this for itself.
 *
 *  See Also:
 *      THREAD_ThreadResume()
 ****************************************************************************/
ITSDLLAPI int
THREAD_ThreadSuspend(ITS_THREAD *t)
{
    ITS_TRACE_DEBUG(("THREAD_ThreadSuspend:\n"));

    if (MUTEX_AcquireMutex(&t->thread.condMutex) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("THREAD_ThreadSuspend: can't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    t->thread.runnable = ITS_FALSE;

    while (!t->thread.runnable)
    {
        if (CONDVAR_Wait(&t->thread.sleepQueue,
                         &t->thread.condMutex) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("THREAD_ThreadSuspend: can't wait condition\n"));

            THREAD_ThreadExit(NULL);
        }
    }

    MUTEX_ReleaseMutex(&t->thread.condMutex);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function resumes a suspended thread.  In practice, this means
 *      the thread will be returned to the scheduler.  The result of
 *      resuming a running thread is undefined.
 *
 *  Input Parameters:
 *      t - the thread to resume
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the thread was successfully resumed, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntellISS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      THREAD_ThreadSuspend()
 ****************************************************************************/
ITSDLLAPI int
THREAD_ThreadResume(ITS_THREAD *t)
{
    ITS_TRACE_DEBUG(("THREAD_ThreadResume:\n"));

    if (MUTEX_AcquireMutex(&t->thread.condMutex) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("THREAD_ThreadResume: can't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    t->thread.runnable = ITS_TRUE;

    MUTEX_ReleaseMutex(&t->thread.condMutex);

    CONDVAR_Signal(&t->thread.sleepQueue);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function should be called for a thread that wants to safely
 *      exit (returning its resources to the process).
 *
 *  Input Parameters:
 *      status - a pointer value to return to the process.  If an entity
 *          is waiting on this thread, this is the value the entity
 *          will receive.
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
THREAD_ThreadExit(void *status)
{
    MEMPOOL_Manager *m;

    ITS_TRACE_DEBUG(("THREAD_ThreadExit:\n"));

    if ((m = (MEMPOOL_Manager *)THREAD_GetLocalStorage()) != NULL)
    {
        MEMPOOL_DestroyPool(m);

        THREAD_SetLocalStorage(NULL);
    }

    pthread_exit(status);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function can be used to kill a thread.  This function is included
 *      for completeness only and should NOT be used.  You have been warned.
 *
 *  Input Parameters:
 *      t - the thread to kill
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the thread was killed, ITS_SUCCESS is returned.
 *      Any other return value indicate an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
THREAD_KillThread(ITS_THREAD *t)
{
    ITS_TRACE_DEBUG(("THREAD_KillThread:\n"));

    if (pthread_cancel(t->thread.thread) != 0)
    {
        ITS_TRACE_ERROR(("THREAD_KillThread: can't cancel thread\n"));

        return (ITS_EBADTHREAD);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function can be used by the caller to wait for the return
 *      code of a spawned thread.
 *
 *  Input Parameters:
 *      t - the thread to wait for
 *      status - the address of a pointer where the return code should be
 *          placed
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the thread exists, and exited, ITS_SUCCESS is returned
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
THREAD_WaitForThread(ITS_THREAD *t, void **status)
{
    ITS_TRACE_DEBUG(("THREAD_WaitForThread:\n"));

    if (pthread_join(t->thread.thread, status) != 0)
    {
        ITS_TRACE_ERROR(("THREAD_KillThread: can't join thread\n"));

        return (ITS_EBADTHREAD);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function can be used by the caller to voluntarily yield the
 *      CPU.
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
 *      If the thread exists, and exited, ITS_SUCCESS is returned
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
THREAD_Yield(void)
{
    ITS_TRACE_DEBUG(("THREAD_Yield:\n"));

    pthread_yield();
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Fetch the local storage for this thread.
 *
 *  Input Parameters:
 *      thr - thread to fetch from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to the thread local storage, or NULL if it hasn't been
 *      set yet.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void *
THREAD_GetLocalStorage()
{
    return pthread_getspecific(ctxt);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the local storage for this thread.
 *
 *  Input Parameters:
 *      thr - thread to fetch from
 *      set - the value to set the local storage to.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
THREAD_SetLocalStorage(void *set)
{
    if (pthread_setspecific(ctxt, set) == 0)
    {
        return (ITS_SUCCESS);
    }

    return (ITS_ENOMEM);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Retrieve the thread identifier of the calling thread.
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
 *      ITS_UINT - thread identifier of the calling thread.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
THREAD_GetCurrentThreadID()
{
    return (ITS_UINT)pthread_self();
}

