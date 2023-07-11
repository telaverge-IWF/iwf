/*********************************************************
*
* tx_core.h - This header file is for applications that use
*       the core.obj for controlling applications using the 
*       CPI library.  There is a version of the core for each
*       Operating System. 
*
*
**********************************************************/
#ifndef _TX_CORE_H
#define _TX_CORE_H

#if defined(WIN32) || defined (__OS2__)

#define FILE_READ                   "rb"
#define FILE_WRITE                  "wb"
#define FILE_UPDATE                 "wb+"

#define TX_CORE_ERROR               0
#define TX_CORE_SUCCESS             1
#define TX_CORE_EXIT_POLL_LOOP      2
#define TX_CORE_TIMEOUT             3
#define TX_CORE_EEXIST              -1
#define TX_CORE_ENOMEM              -1

/* these values are unused by NT/OS2 and can be changed */

#define TX_CORE_INPUT               0x01
#define TX_CORE_PRI                 0x02
#define TX_CORE_OUT                 0x04
#define TX_CORE_RDNORM              0x08
#define TX_CORE_WRNORM              0x10
#define TX_CORE_RDBAND              0x20
#define TX_CORE_WRBAND              0x40

#ifdef WIN32      /* 32 bit Windows OS */
#define TX_CORE_UNUSED              CPI_INVALID_HANDLE
#define TX_CORE_INFINITE            INFINITE 
#define TX_CORE_CR_POS              1
#endif

#ifdef __OS2__      /* IBM OS/2 */
#define TX_CORE_UNUSED              CPI_INVALID_HANDLE
#define TX_CORE_INFINITE            0xFFFFFFFF
#define TX_CORE_CR_POS              1
#endif

#endif /* WIN32 or OS2 */

#ifdef UNIX

#include <poll.h>
#ifndef BOOL
#define BOOL                        short
#endif
#ifndef TRUE
#define TRUE                        1
#endif
#ifndef FALSE
#define FALSE                       0
#endif

#define FILE_READ                   "r"
#define FILE_WRITE                  "w"
#define FILE_UPDATE                 "w+"

#define TX_CORE_SUCCESS             0
#define TX_CORE_ERROR               (-1)
#define TX_CORE_EXIT_POLL_LOOP      (-2)
#define TX_CORE_TIMEOUT             (-3)
#define TX_CORE_EEXIST              (-4)
#define TX_CORE_ENOMEM              (-5)

#define TX_CORE_UNUSED              CPI_INVALID_HANDLE
#define TX_CORE_INFINITE            (-1) 

/* These are used by UNIX and must remain untouched */
/* the values depend on the poll.h header file      */

#define TX_CORE_INPUT               POLLIN
#define TX_CORE_PRI                 POLLPRI
#define TX_CORE_OUT                 POLLOUT

#if defined(_SVID3)
#define TX_CORE_RDNORM              POLLRDNORM
#define TX_CORE_WRNORM              POLLWRNORM
#define TX_CORE_RDBAND              POLLRDBAND
#define TX_CORE_WRBAND              POLLWRBAND
#endif /* defined(_SVID3) */

#define TX_CORE_CR_POS		2

#endif /* UNIX */

short tx_core_set_poll(CPI_WAIT_TYPE fd, short events);
short tx_core_install_handler(CPI_WAIT_TYPE fd, TX_HANDLE handle, short (*handler)(TX_HANDLE fd, short events));
short tx_core_init();
long tx_core_poll_loop(long wait_time);
char *tx_core_gets(char *input, short len);
BOOL tx_core_kbhit();
BOOL tx_core_process_events(short event, short events);

#endif /* _TX_CORE_H */
