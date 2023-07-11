/******************************************************************************
 * File name:   osdep.h
 * Description:
 *
 * ****************************************************************************/
#ifndef __OSDEP_H__
#define __OSDEP_H__

enum AppErrorCodes {
   RET_FAILED  = 0,
   RET_SUCCESS = 1
};

#include "txnuser.h"

#ifdef WIN32 /******************************************************** WIN32 */
/*
 * Include files.
 */
#include <windows.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <process.h>
#include <time.h>

/*
*** Some definitions:
 */
#define CBFN  CALLBACK

/*
*** Errors:
 */
#define osGetLastError() \
   GetLastError()

#define ERR_MSGSIZE  WSAEMSGSIZE

/*
*** Threads:
 */
/* #define TPtrThrFunc  PTHREAD_START_ROUTINE */ /*for CreateThread*/
#define TPtrThrFunc  void(*)(void*) /*for _beginthread*/
#define TThrStkSize  DWORD
#define TPtrThrArg   LPVOID
#define TThrFlags    DWORD
#define TThrId       DWORD

#define THREAD_CREATE(ThrStkSz, pThrFunc, pThrArg, ThrFlags, pThrId) \
   (((*pThrId = _beginthread(pThrFunc, ThrStkSz, pThrArg)) != -1) ? RET_SUCCESS:RET_FAILED)
   /* CreateThread(NULL, ThrStkSz, pThrFunc, pThrArg, ThrFlags, pThrId)
    *  - there are problems with C RT lib (memory leaks when ExitThread is called)
    */

#define THREAD_EXIT() \
   _endthread()
   /* ExitThread(0) */

#define THREAD_DESTROY(ThrId,Ret) \
   ((CloseHandle((HANDLE)ThrId) != 0) ? RET_SUCCESS:RET_FAILED)

/*
*** Mutexes:
 */
#define TMutex   HANDLE

#define MUTEX_CREATE(MtxObj) \
   (((MtxObj = CreateMutex(NULL, FALSE, NULL)) != 0) ? RET_SUCCESS:RET_FAILED)

#define MUTEX_LOCK(MtxObj) \
   ((WaitForSingleObject(&MtxObj,INFINITE) != WAIT_FAILED) ? RET_SUCCESS:RET_FAILED)

#define MUTEX_UNLOCK(MtxObj) \
   ((ReleaseMutex(&MtxObj) != 0) ? RET_SUCCESS:RET_FAILED)

#define MUTEX_DESTROY(MtxObj) \
   ((CloseHandle(&MtxObj) != 0) ? RET_SUCCESS:RET_FAILED)

/*
*** Semaphores:
 */
#define TSema    HANDLE
#define TSemaCnt S32

#define SEMA_CREATE(SemaObj,Cnt) \
   (((SemaObj = CreateSemaphore(NULL, Cnt, Cnt, NULL)) != 0) ? RET_SUCCESS:RET_FAILED)

#define SEMA_WAIT(SemaObj) \
   ((WaitForSingleObject(SemaObj,INFINITE) != WAIT_FAILED) ? RET_SUCCESS:RET_FAILED)

#define SEMA_POST(SemaObj) \
   ((ReleaseSemaphore(SemaObj) != 0) ? RET_SUCCESS:RET_FAILED)

#define SEMA_DESTROY(SemaObj) \
   ((CloseHandle(SemaObj) != 0) ? RET_SUCCESS:RET_FAILED)

/*
*** Timers:
 */
#define TMR_ONESHOT   0
#define TMR_INFTIME   INFINITE
#define TMTimerId     DWORD
#define TTimerId      HANDLE
#define TTimHandler   PTIMERAPCROUTINE

#define TIMER_CREATE(TimId) \
   (((TimId = CreateWaitableTimer(NULL,FALSE,NULL)) != 0) ? RET_SUCCESS:RET_FAILED)

#define TIMER_INIT(TimId,TimHandler) \
   ((TRUE) ? RET_SUCCESS:RET_FAILED)

#define TIMER_SETTIME(TimId,IPeriod,DueTime,TimHandler,pArg) \
{ \
   LARGE_INTEGER  liDueTime; \
   liDueTime.HighPart = -1; \
   liDueTime.LowPart = (DWORD)((-DueTime) * 10000); \
   ((SetWaitableTimer(TimId, &liDueTime, IPeriod, TimHandler, pArg, FALSE) != 0) ? RET_SUCCESS:RET_FAILED); \
}

#define TIMER_CANCEL(TimId) \
   ((CancelWaitableTimer(TimId) != 0) ? RET_SUCCESS:RET_FAILED)

#define TIMER_DESTROY(TimId) \
   ((CloseHandle(TimId) != 0) ? RET_SUCCESS:RET_FAILED)

#define TIMER_HANDLER_DECL(FuncName) \
   void CALLBACK FuncName(void *pArg, U32 TimLoVal, U32 TimHiVal)

/*
*** Network:
 */
#define TSocket      SOCKET
#define TSockAddrIn  struct sockaddr_in
#define TSockAddr    struct sockaddr
#define THostent     struct hostent

#define osGetHostByName(pNodeName, pHostent) \
   (((pHostent = gethostbyname(pNodeName)) != NULL) ? RET_SUCCESS:RET_FAILED)

#define SOCKET_OPEN(Domain,Type,Protocol,Socket) \
   (((Socket = socket(Domain,Type,Protocol)) != INVALID_SOCKET) ? RET_SUCCESS:RET_FAILED)

#define SOCKET_BIND(Socket,pName,pNameLen) \
   ((bind(Socket,pName,pNameLen) != SOCKET_ERROR) ? RET_SUCCESS:RET_FAILED)

#define SOCKET_CLOSE(SockObj) \
   ((closesocket(SockObj) != 0) ? RET_SUCCESS:RET_FAILED)

#define SOCKET_RECVFROM(Socket,pBuf,Len,Flags,pFrom,pFromLen,RecvLen) \
   (((RecvLen = recvfrom(Socket,pBuf,Len,Flags,pFrom,pFromLen)) != SOCKET_ERROR) ? RET_SUCCESS:RET_FAILED)

#define SOCKET_SENDTO(Socket,pMsg,Len,Flags,pTo,pToLen) \
   ((sendto(Socket,pMsg,Len,Flags,pTo,pToLen) != SOCKET_ERROR) ? RET_SUCCESS:RET_FAILED)

/*
*** Files:
 */
#define TFile    FILE

/*
*** System calls:
 */
#define PAUSE(msec) \
   SleepEx(msec,TRUE)

#define OBJECT_WAIT(ObjId,TimeOut) \
   WaitForSingleObjectEx(ObjId,TimeOut,TRUE)

#endif /* WIN32 */

/* TRP change from SOLARIS to UNIX for Unixware support */
#ifdef UNIX /**************************************************** SOLARIS */
/*
 * Include files.
 */
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#ifdef LINUX
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#else
#include <thread.h>
#include <synch.h>
#endif
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


/*
*** Some definitions:
 */
#define CBFN

/*
*** Errors:
 */
#define osGetLastError() \
   errno

#define ERR_MSGSIZE   (ENOBUFS || ENOSR || ENOMEM)

/*
*** Threads:
 */
#define TPtrThrFunc  void*(*)(void*)
#define TThrStkSize  size_t
#define TPtrThrArg   void*
#define TThrFlags    S32
#ifdef LINUX
#define TThrId       pthread_t
#else
#define TThrId       thread_t
#endif

#ifndef LINUX
#define THREAD_CREATE(ThrStkSz, pThrFunc, pThrArg, ThrFlags, pThrId) \
   ((thr_create(NULL, ThrStkSz, pThrFunc, pThrArg, ThrFlags | THR_DETACHED, pThrId) == 0) ? RET_SUCCESS:RET_FAILED)
#else
#define THREAD_CREATE(ThrStkSz, pThrFunc, pThrArg, ThrFlags, pThrId) \
   ((pthread_create(pThrId, NULL, pThrFunc, pThrArg) == 0) ? RET_SUCCESS:RET_FAILED)
#endif

#ifndef LINUX
#define THREAD_EXIT() \
   thr_exit(NULL)
#else
#define THREAD_EXIT() \
   pthread_exit(NULL)
#endif

#ifndef LINUX
#define THREAD_DESTROY(ThrId) \
   ((thr_kill(ThrId, SIGKILL) == 0) ? RET_SUCCESS:RET_FAILED)
#else
#define THREAD_DESTROY(ThrId) \
   ((pthread_kill(ThrId, SIGKILL) == 0) ? RET_SUCCESS:RET_FAILED)
#endif

/* *** Mutexes:*/
#ifndef LINUX
#define TMutex   mutex_t

#define MUTEX_CREATE(MtxObj) \
   ((mutex_init(&MtxObj,0,NULL) == 0) ? RET_SUCCESS:RET_FAILED)

#define MUTEX_LOCK(MtxObj) \
   ((mutex_lock(&MtxObj) == 0) ? RET_SUCCESS:RET_FAILED)

#define MUTEX_UNLOCK(MtxObj) \
   ((mutex_unlock(&MtxObj) == 0) ? RET_SUCCESS:RET_FAILED)

#define MUTEX_DESTROY(MtxObj) \
   ((mutex_destroy(&MtxObj) == 0) ? RET_SUCCESS:RET_FAILED)
#else /* LINUX */
#define TMutex   pthread_mutex_t

#define MUTEX_CREATE(MtxObj) \
   ((pthread_mutex_init(&MtxObj,0) == 0) ? RET_SUCCESS:RET_FAILED)

#define MUTEX_LOCK(MtxObj) \
   ((pthread_mutex_lock(&MtxObj) == 0) ? RET_SUCCESS:RET_FAILED)

#define MUTEX_UNLOCK(MtxObj) \
   ((pthread_mutex_unlock(&MtxObj) == 0) ? RET_SUCCESS:RET_FAILED)

#define MUTEX_DESTROY(MtxObj) \
   ((pthread_mutex_destroy(&MtxObj) == 0) ? RET_SUCCESS:RET_FAILED)
#endif
/*
*** Semaphores:
 */
#ifndef LINUX
#define TSema    sema_t
#define TSemaCnt int

#define SEMA_CREATE(SemaObj,Cnt) \
   ((sema_init(&SemaObj, Cnt, USYNC_PROCESS, NULL) == 0) ? RET_SUCCESS:RET_FAILED)

#define SEMA_WAIT(SemaObj) \
   ((sema_wait(&SemaObj) == 0) ? RET_SUCCESS:RET_FAILED)

#define SEMA_POST(SemaObj) \
   ((sema_post(&SemaObj) == 0) ? RET_SUCCESS:RET_FAILED)

#define SEMA_DESTROY(SemaObj) \
   ((sema_destroy(&SemaObj) == 0) ? RET_SUCCESS:RET_FAILED)
#else   /* LINUX */
#define TSema    sem_t
#define TSemaCnt int

#define SEMA_CREATE(SemaObj,Cnt) \
   ((sem_init(&SemaObj, Cnt, USYNC_PROCESS, NULL) == 0) ? RET_SUCCESS:RET_FAILED)

#define SEMA_WAIT(SemaObj) \
   ((sem_wait(&SemaObj) == 0) ? RET_SUCCESS:RET_FAILED)

#define SEMA_POST(SemaObj) \
   ((sem_post(&SemaObj) == 0) ? RET_SUCCESS:RET_FAILED)

#define SEMA_DESTROY(SemaObj) \
   ((sem_destroy(&SemaObj) == 0) ? RET_SUCCESS:RET_FAILED)
#endif
/*
*** Timers:
 */
#define _POSIX_PER_PROCESS_TIMER_SOURCE
#define TMR_ONESHOT   0
#define TMR_INFTIME   INFTIM
#ifdef __sun
#define TMTimerId     timer_t
#define TTimerId      timer_t
#elif defined(UNIXWARE) || defined (LINUX)
#define TMTimerId     struct itimerval *
#define TTimerId      struct itimerval *
#endif

/*???#define TTimHandler   void (*)(void*,unsigned long,unsigned long)*/

#define TIMER_CREATE(TimId) \
   ((timer_create(CLOCK_REALTIME,NULL,&TimId) == 0) ? RET_SUCCESS:RET_FAILED)

#define TIMER_INIT(TimId,TimHandler) \
   ((sigset(SIGALRM,TimHandler) == 0) ? RET_SUCCESS:RET_FAILED)

#define TIMER_SETTIME(TimId,IPeriod,DueTime,TimHandler,pArg) \
{ \
   struct itimerspec value; \
   value.it_value.tv_sec = DueTime/1000; \
   value.it_value.tv_nsec = (DueTime%1000)*1000000; \
   value.it_interval.tv_sec = IPeriod/1000; \
   value.it_interval.tv_nsec = (IPeriod%1000)*1000000; \
   ((timer_settime(TimId,TIMER_RELTIME,&value,NULL) == 0) ? RET_SUCCESS:RET_FAILED); \
}

#define TIMER_CANCEL(TimId) \
{ \
   struct itimerspec value = {0}; \
   ((timer_settime(TimId,TIMER_RELTIME,&value,NULL) == 0) ? RET_SUCCESS:RET_FAILED); \
}

#define TIMER_DESTROY(TimId) \
   ((timer_delete(TimId) == 0) ? RET_SUCCESS:RET_FAILED)

#define TIMER_HANDLER_DECL(FuncName) \
   void FuncName(int Arg)

/*
*** Network:
 */
#ifndef INADDR_NONE
#define INADDR_NONE      ((U32)-1)
#endif

#define TSocket      int
#define TSockAddrIn  struct sockaddr_in
#define TSockAddr    struct sockaddr
#define THostent     struct hostent

/*Note: MT unsafe. Only one thread in the app can use this function.*/
#define osGetHostByName(pNodeName, pHostent) \
   (((pHostent = gethostbyname(pNodeName)) != NULL) ? RET_SUCCESS:RET_FAILED)

#define SOCKET_OPEN(Domain,Type,Protocol,Socket) \
   (((Socket = socket(Domain,Type,Protocol)) != -1) ? RET_SUCCESS:RET_FAILED)

#define SOCKET_BIND(Socket,pName,pNameLen) \
   ((bind(Socket,pName,pNameLen) != -1) ? RET_SUCCESS:RET_FAILED)

#define SOCKET_CLOSE(SockObj) \
   ((shutdown(SockObj,2) == 0) ? RET_SUCCESS:RET_FAILED)

#define SOCKET_RECVFROM(Socket,pBuf,Len,Flags,pFrom,pFromLen,RecvLen) \
   (((RecvLen = recvfrom(Socket,pBuf,Len,Flags,pFrom,pFromLen)) != -1) ? RET_SUCCESS:RET_FAILED)

#define SOCKET_SENDTO(Socket,pMsg,Len,Flags,pTo,pToLen) \
   ((sendto(Socket,pMsg,Len,Flags,pTo,pToLen) != -1) ? RET_SUCCESS:RET_FAILED)

/*
*** Files:
 */
#define TFile    FILE

/*
*** System calls:
 */
#define PAUSE(msec) \
   poll(NULL,0,msec)

#define OBJECT_WAIT(ObjId,TimeOut) \
   poll(ObjId,0,TimeOut)

#endif /************************************************************ SOLARIS */

#endif  /* __OSDEP_H__ */
