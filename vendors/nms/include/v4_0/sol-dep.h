/*****************************************************************************
 * File:       sol-dep.h
 * Objective:
 *****************************************************************************/

#ifndef _SOL_DEP_H_
#define _SOL_DEP_H_

#include "txnuser.h"

#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <thread.h>
#include <pthread.h>
#include <synch.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

/******* */
typedef void *		LPTHREAD_START_ROUTINE;

typedef  unsigned int   SOCKET;
#define  INVALID_SOCKET   (SOCKET)(-1)
#define  SOCKET_ERROR     (-1)
#define  LPVOID           void *
#ifndef  INADDR_NONE
#define  INADDR_NONE      ((U32)-1)
#endif
#define  LPSOCKADDR       struct sockaddr *
#define  WSAEMSGSIZE      (ENOBUFS || ENOSR || ENOMEM)
#define  NO_ERROR	  0
#define  HOSTBUFFERLENGTH 1024

typedef mutex_t CRITICAL_SECTION;

/******* Forward function declarations */

int GetLastError();
U32  _beginthread( void *(*start_addr)(void*), unsigned stack_size, void *arglist);
void  _endthread(void);
void InitializeCriticalSection(CRITICAL_SECTION *pCriticalSection);
void EnterCriticalSection(CRITICAL_SECTION *pCriticalSection);
void LeaveCriticalSection(CRITICAL_SECTION *pCriticalSection);
int _kbhit(void);
int _getch(void);
void _strtime(char *LocTime);

#endif /* _SOL_DEP_H_ */







