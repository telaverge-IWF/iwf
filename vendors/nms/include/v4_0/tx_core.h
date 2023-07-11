/*****************************************************************************
 *
 * tx_core.h -
 * This header file is for applications that use the core.obj for controlling
 * applications using the CPI library.  There is a version of the core for each
 * Operating System.

 *****************************************************************************/

/*****************************************************************************
 *
 *                         PROPRIETARY NOTICE
 *
 *                      Copyright (c) 1988-2003
 *                       by NMS Communications.
 *
 *  The following is licensed program material and is considered
 *  proprietary and confidential.  No part of this program may be
 *  reproduced or used in any form or by any means without the express
 *  written permission of NMS Communications.
 *
 *****************************************************************************/

#ifndef _TX_CORE_H
#define _TX_CORE_H

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * PACKING: pack on 1-byte boundaries
 *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#ifdef UNIX
#pragma pack(1)
#endif
#ifdef __HIGHC__
#pragma Push_align_members(1)
#endif
#ifdef _WINNT
#pragma pack(1)
#endif


#if defined(WIN32) || defined (__OS2__)

#define FILE_READ                   "rb"    /* open existant file for reading */
#define FILE_CHANGE                 "rb+"   /* open existant file for reading and writing */
#define FILE_WRITE                  "wb"    /* create and open new file for writing */
#define FILE_UPDATE                 "wb+"   /* create and open new file for reading and writing */

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

#ifdef WIN32                        /* 32 bit Windows OS */
#define TX_CORE_UNUSED              CPI_INVALID_HANDLE
#define TX_CORE_INFINITE            INFINITE
#endif

#ifdef __OS2__                      /* IBM OS/2 */
#define TX_CORE_UNUSED              CPI_INVALID_HANDLE
#define TX_CORE_INFINITE            0xFFFFFFFF
#endif

#endif  /* WIN32 or OS2 */

#ifdef UNIX

#include <poll.h>
#ifndef BOOL
#define BOOL                        S16
#endif
#ifndef TRUE
#define TRUE                        1
#endif
#ifndef FALSE
#define FALSE                       0
#endif

#define FILE_READ                   "r" /* open existant file for reading */
#define FILE_CHANGE                 "r+"    /* open existant file for reading and writing */
#define FILE_WRITE                  "w" /* create and open new file for writing */
#define FILE_UPDATE                 "w+"    /* create and open new file for reading and writing */

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
#endif  /* defined(_SVID3) */

#endif  /* UNIX */

#define TX_CORE_CR_POS      1

typedef S16   (*TX_HANDLER) (TX_HANDLE fd, S16 events);

S16  tx_core_set_poll(CPI_WAIT_TYPE fd, S16 events);

S16  tx_core_install_handler(CPI_WAIT_TYPE fd,
                        TX_HANDLE handle, TX_HANDLER handler);

S16  tx_core_init(void);

S32  tx_core_poll_loop(S32 wait_time);

S8   *tx_core_gets(S8 *input, S16 len);

BOOL tx_core_kbhit(void);

BOOL tx_core_process_events(S16 event, S16 events);

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * PACKING: return to default
 *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#ifdef UNIX
#pragma pack()
#endif
#ifdef _WINNT
#pragma pack()
#endif
#ifdef __HIGHC__
#pragma Pop_align_members
#endif

#endif  /* _TX_CORE_H */
