/*****************************************************************************
******************************************************************************
**
**   ss7type.h
**
**      Constants, Structures, and Function prototype necessary for utilization
**      of SS7 APIs and utilities.
**
*****************************************************************************/

/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1996                           **
**                          by TEKnique, Inc.                           **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of TEKnique, Inc.                                **
**                                                                      **
*************************************************************************/
#ifndef _SS7TYPE_H_
#define _SS7TYPE_H_

#include "txcpi.h"

#define S7LM_ENT    0x0E                /* The SS7 Layer Manager                    */
#define SCCP_ENT    0x1E                /* SCCP Protocol Handler                    */
#define ISUP_ENT    0x14                /* ISDN User Part Protocol Handler          */
#define MTP3_ENT    0x15                /* Message Transfer Part Layer 3            */
#define MTP2_ENT    0x16                /* Message Transfer Part Layer 2            */
#define MTP1_ENT    0x1C                /* Message Transfer Part Layer 1            */
#define TUP_ENT     0x1D                /* Telephone User Part Prorocol Handler     */
#define TCAP_ENT    0x17                /* Transaction Capabilities Application Part*/
#define IUP_ENT     0x18                /* InterConnect User Part                   */
#define TXMON_ENT   0x19                /* TX Monitor task on board                 */
#define S7MM_ENT    0x0F                /* SS7 Monitor Management                   */
#define S7MD_ENT    0x13                /* SS7 Monitor Data                         */

/* Data Types */

typedef unsigned char  Bool;        /* Boolean value                    */
typedef char           S8;          /* unsigned 8-bit quantity          */
typedef unsigned char  U8;          /* unsigned 8-bit quantity          */
typedef unsigned short U16;         /* unsigned 16-bit quantity         */
typedef short          S16;         /* signed 16-bit quantity           */
typedef unsigned long  U32;         /* unsigned 32-bit quantity         */
typedef long           S32;         /* signed 32-bit quantity           */
typedef void Void;                /* void */

/* Define abstract data types for:
 * 1. file descriptors, or handles, used to do I/O with TXn0000
 * 2. handles to "sychronization objects", which may or may not
 *    be the same as the file descriptor/handle, which can be
 *    useful/required on some host OS's deal with asynchonous
 *    events (e.g., incoming messages) multiple TxN000 and/or
 *    other devices.
 */

/* basic file descriptor/handle definition - note that the actual
 * definition for these for each supported operating system is
 * in the <txcpi.h> file.
 */
#ifdef TX_HANDLE
typedef TX_HANDLE       OS_FD;
#define OS_NULL_FD      CPI_INVALID_HANDLE
#else
typedef S32                     OS_FD;
#define OS_NULL_FD      -1
#endif

/* synchronization handle definition - note that the actual
 * definition for these for each supported operating system is
 * in the <txcpi.h> file.
 */
#ifdef CPI_WAIT_TYPE
typedef CPI_WAIT_TYPE   OS_HSYNC;
#define OS_NULL_HSYNC   CPI_INVALID_WAIT_HANDLE
#else
typedef OS_FD                   OS_HSYNC;
#define OS_NULL_HSYNC   OS_NULL_FD
#endif

/* point code lengths (in bits) for ANSI and ITU-T protocols */
#define PCLEN_ITU   0                   /* 14 bit point code */
#define PCLEN_ANSI  1                   /* 24 bit point code */
#define PCLEN_JAPAN 2                   /* Japanese variants - 16-bit point code */
#define PCLEN_DEFAULT   255             /* reserved for internal use */

/* Point code display formats */
#define SS7_PCDISP_DFLT 0           /* default: "8.8.8" for 24 bit PCs, hex for others */
#define SS7_PCDISP_INTL 1           /* International: "3.8.3" for 14 bit PCs, hex for others */
#define SS7_PCDISP_JNTT 2           /* Japan(NTT): "5.4.7" <Mcode>.<Scode>.<Ucode> for 16 bit PCs */

#ifdef __sun
#pragma pack(1)
#endif

/* common structures */
typedef struct _TimerCfg {
    U8  enable;                 /* 0 = disabled, 1 = enabled */
    U8 spare1;                          /* alignment */
    U16 value;                  /* timeout in tenths of seconds */
} TimerCfg;

typedef struct _PDesc           /* process descriptor */
{
   U16 dstProcId;               /* destination processor id  */
   U16 srcProcId;               /* source processor id       */
   U8 dstEnt;                   /* destination entity        */
   U8 dstInst;                  /* destination instance      */
   U8 srcEnt;                   /* source entity             */
   U8 srcInst;                  /* source instance           */
   U8 prior;                    /* priority                  */
   U8 route;                    /* route                     */
   U8 event;                    /* event                     */
   U8 region;                   /* region                    */
   U8 pool;                     /* pool                      */
   U8 selector;                 /* selector                  */
   U16 spare1;                  /* spare 1                   */
} PDesc;

typedef struct _MemoryId        /* memory */
{
   U8 region;                   /* region */
   U8 pool;                     /* pool */
   U16 spare;                   /* spare for alignment */
} MemoryId;


typedef struct _DateTime           /* date and time */
{
   U8 month;                      /* month */
   U8 day;                        /* day */
   U8 year;                       /* year - since 1900 (eg. 2000 = 100) */
   U8 hour;                       /* hour - 24 hour clock */
   U8 min;                        /* minute */
   U8 sec;                        /* second */
   U8 tenths;                     /* tenths of second */
   U8 fill;

} DateTime;

/* duration structure */

typedef struct _Duration           /* duration */
{
   U8 days;                       /* days */
   U8 hours;                      /* hours */
   U8 mins;                       /* minutes */
   U8 secs;                       /* seconds */
   U8 tenths;                     /* tenths of seconds */
   U8 fill;

} Duration;

#ifdef __sun
#pragma pack()
#endif

#endif                          /* _SS7TYPE_H_ */
