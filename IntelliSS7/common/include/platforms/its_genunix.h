/****************************************************************************
 *                                                                          *
 * Copyright 1997-1999 IntelliNet Technologies, Inc. All Rights Reserved.   *
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
 * LOG: $Log: its_genunix.h,v $
 * LOG: Revision 9.1  2005/03/23 12:52:57  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:51:05  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:44  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/11/08 20:47:38  mmiers
 * LOG: A better performing mem pool implementation.
 * LOG:
 * LOG: Revision 5.2  2001/11/07 22:53:58  mmiers
 * LOG: Add IPC mutex.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:00  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:14  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.4  2001/04/05 16:52:16  mmiers
 * LOG: Proper class hierarchy for thread.
 * LOG:
 * LOG: Revision 3.3  2001/02/14 20:44:54  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.2  2001/02/08 22:43:05  mmiers
 * LOG: Add dynamic symbol resolution.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:55  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.4  2000/08/09 00:08:20  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 1.3  2000/04/25 23:30:01  mmiers
 * LOG:
 * LOG:
 * LOG: Platform cleanup.
 * LOG:
 * LOG: Revision 1.2  2000/04/24 22:20:04  mmiers
 * LOG:
 * LOG:
 * LOG: Add condition variable type.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 18:13:01  mmiers
 * LOG:
 * LOG: More platform cleanup.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_PLATFORM_H)
#define ITS_PLATFORM_H

#ident "$Id: its_genunix.h,v 9.1 2005/03/23 12:52:57 cvsadmin Exp $"

/*
 * FIFO type
 */
#include <sys/stat.h>
#include <its_spinlock.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * this platform does NOT support reentrant fifos.  Use GatedFifo instead
 */
typedef int       ITS_FIFO;

/*
 * mutex type (broken)
 */
typedef struct
{
    ITS_THREAD*     owner;
    ITS_ULONG       locked;
    LIST_Manager    list;
    ITS_SPINLOCK    list_lock;
}
ITS_MUTEX;

/*
 * IPC MUTEX
 */
typedef int       ITS_IPC_MUTEX;

/*
 * CONDVAR (broken)
 */
typedef int ITS_CONDVAR;

/*
 * SEMAPHORE
 */
typedef int       ITS_IPC_SEMAPHORE;

/*
 * SOCKET
 */
typedef int       ITS_SOCKET;

/*
 * THREAD
 */
typedef void *(*ITS_THREAD_FUNC)(void *);

typedef struct
{
    pthread_t              thread;
    int                    stackSize;
    ITS_BOOLEAN            runnable;
    ITS_BOOLEAN            constructed;
    ITS_THREAD_FUNC        threadFunc;
    void*                  threadArg;
    ITS_MUTEX              condMutex;
    ITS_CONDVAR            sleepQueue;
}
ITS_ThreadPart;

typedef struct
{
    ITS_CoreObjectPart     core;
    ITS_ThreadPart         thread;
}
ITS_THREAD;

#define THREAD_RET_TYPE void *
#define THREAD_NORMAL_EXIT                                              \
    do                                                                  \
    {                                                                   \
        MEMPOOL_Manager *m;                                             \
        if ((m = (MEMPOOL_Manager *)THREAD_GetLocalStorage()) != NULL)  \
        {                                                               \
            MEMPOOL_DestroyPool(m);                                     \
            THREAD_SetLocalStorage(NULL);                               \
        }                                                               \
        return (NULL);                                                  \
    }                                                                   \
    while (0)

/*
 * shared libs
 */
typedef void *      ITS_DLSYM_HANDLE;
typedef void *      ITS_DLSYM;

#if defined(__cplusplus)
}
#endif

#endif /* ITS_PLATFORM_H */
