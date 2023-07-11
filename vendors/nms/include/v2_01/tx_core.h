/*****************************************************************************
******************************************************************************
**
**   tx_core.h
** This header file is for applications that use the core.obj for controlling
** applications using the CPI library.  There is a version of the core for each
** Operating System. 
**
**   Revision History:
*-----------------------------------------------------------------------------
* REV   DATE           WHO       $Log: tx_core.h,v $
* REV   DATE           WHO       Revision 9.1  2005/03/23 12:55:47  cvsadmin
* REV   DATE           WHO       Begin PR6.5
* REV   DATE           WHO
* REV   DATE           WHO       Revision 8.2  2005/03/21 13:55:08  cvsadmin
* REV   DATE           WHO       PR6.4.2 Source Propagated to Current
* REV   DATE           WHO
* REV   DATE           WHO       Revision 7.1  2002/08/26 22:10:51  mmiers
* REV   DATE           WHO       Begin PR6.2
* REV   DATE           WHO
* REV   DATE           WHO       Revision 6.1  2002/02/28 16:14:54  mmiers
* REV   DATE           WHO       Begin PR7.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1  2001/09/05 20:35:47  mmiers
* REV   DATE           WHO       Consolidate the NMS libraries.  Only the root library so far.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 5.1  2001/08/16 20:46:36  mmiers
* REV   DATE           WHO       Start PR6.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 4.1  2001/05/04 16:22:07  mmiers
* REV   DATE           WHO       Start PR5.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 3.1  2000/08/16 00:11:07  mmiers
* REV   DATE           WHO
* REV   DATE           WHO       Begin round 4.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1  2000/06/21 19:19:42  hxing
* REV   DATE           WHO       Add NMS vendor lib for version 2.01
* REV   DATE           WHO $NoKeywords: $
* 
* 7     2/06/98 1:14p Vince
* Slight reformat - easier to read now.
* Added typedef for handler prototype.
* Added SourceSafe header.
* 
*-----------------------------------------------------------------------------
******************************************************************************
*****************************************************************************/
/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1998                           **
**                    by Natural MicroSystems, Inc.                     **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of Natural MicroSystems, Inc.                    **
**                                                                      **
*************************************************************************/
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

typedef short
(*TX_HANDLER)(
  TX_HANDLE fd,
  short events);

short
tx_core_set_poll(
  CPI_WAIT_TYPE fd,
  short events);

short
tx_core_install_handler(
  CPI_WAIT_TYPE fd,
  TX_HANDLE handle,
  TX_HANDLER handler);
 
short
tx_core_init(
  void);

long
tx_core_poll_loop(
  long wait_time);

char*
tx_core_gets(
  char* input,
  short len);

BOOL
tx_core_kbhit(
  void);

BOOL
tx_core_process_events(
  short event,
  short events);

#endif /* _TX_CORE_H */
