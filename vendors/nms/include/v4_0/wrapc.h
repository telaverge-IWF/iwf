/**************************************************************************
** wrapc.h
**
**     This file defines the common structures and definitions to support the
**     wrapper funtionality for tasks (i.e. tup and btnup)
**
**   Revision History:
**
*-----------------------------------------------------------------------------
*-----------------------------------------------------------------------------
**************************************************************************
**************************************************************************/

/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1997                           **
**                    By Natural MicroSystems, Inc.                     **
**                                                                      **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of Natural MicroSystems, Inc.                    **
**                                                                      **
*************************************************************************/
#ifndef WRAPC_H_
#define WRAPC_H_

/*
#ifdef __HIGHC__
#pragma Push_align_members(1)
#endif
*/

#ifndef TUP_TASK
#ifdef UNIX
#pragma pack(1)
#endif
#endif

#ifndef _XCODE_

typedef U8 Ent;                   /* entity */
typedef U8 Inst;                  /* instance */
typedef U8 Region;                /* region */
typedef U8 Pool;                  /* pool */
typedef U8 Selector;              /* selector */
#ifndef TUP_DEMO
typedef U8 Event;                 /* event */
#endif
typedef U16 ProcId;               /* processor id */
typedef U8 Route;                 /* route */
typedef U8 Prior;                 /* priority */
typedef Prior Priority;           /* priority */
typedef U8 QueueId;

#endif

#ifndef TUP_TASK
typedef struct _entityId           /* entity id */
{
   U8 ent;                       /* entity */
   U8 inst;                      /* instance */
   U8 spare1;                    /* Spare for alignment */
   U8 spare2;                    /* Spare for alignment */
} EntityId;

typedef struct _elmntId            /* element id */
{
   S16   elmnt;                   /* element */
   S16   elmntInst1;              /* element instance 1 */
   S16   elmntInst2;              /* element instance 2 */
   S16   elmntInst3;              /* element instance 3 */
} ElmntId;

#define MAX_BUF_SIZE    1400

typedef struct chn                /* chain */
{
    void   *flink;              /* forward link - must be 1st in struct */
    void   *blink;              /* backward link - must be 2nd in struct */
    void   *owner;              /* Queue that this element belongs to */
    void   *frameptr;           /* pointer back to start of owning frame */
    U8      buftype;            /* type of buffer this is */
    U8      spare1;             /* for alignment */
    U16     bufLen;             /* for alignment */
} Chn;

typedef Chn Chain;                /* chain */

#if 0
struct ss_buffer                                /* NMS's definition of ss_buffer */
{
    Chain   bufferHdr;          /* buffer type, linkages: must be first in buffer */
    S16     start;
    S16     end;
    unsigned char buffer[MAX_BUF_SIZE];
};

typedef struct ss_buffer Buffer;
#endif

#ifndef TUP_DEMO

typedef struct pst                /* parameters for SPstTsk */
{
   ProcId dstProcId;              /* destination processor id (U16) */
   ProcId srcProcId;              /* source processor id      (U16) */

   Ent dstEnt;                    /* destination entity       (U8)  */
   Inst dstInst;                  /* destination instance     (U8)  */
   Ent srcEnt;                    /* source entity            (U8)  */
   Inst srcInst;                  /* source instance          (U8)  */

   Prior prior;                   /* priority                 (U8)  */
   Route route;                   /* route                    (U8)  */
   Event event;                   /* event                    (U8)  */
   Region region;                 /* region                   (U8)  */

   Pool pool;                     /* pool                     (U8)  */
   Selector selector;             /* selector                 (U8)  */
   U16 spare1;                    /* spare 1                  (U16) */
} Pst;
#endif
#define MAX_QUEUE_THRESHOLDS 8
#define MAX_POOL_THRESHOLDS     MAX_QUEUE_THRESHOLDS

struct threshtbl
{
    struct
    {
        S16     onset;
        S16     abatement;
    } threshold[MAX_QUEUE_THRESHOLDS];
};

typedef struct threshtbl QTABLE;

#endif

#ifdef TUP_TASK

#define S7LM_ENT    0x0E                /* The SS7 Layer Manager                    */
#define S7MM_ENT    0x0F                /* SS7 Monitor Management                   */
#define S7MD_ENT    0x13                /* SS7 Monitor Data                         */
#define ISUP_ENT    0x14                /* ISDN User Part Protocol Handler          */
#define MTP3_ENT    0x15                /* Message Transfer Part Layer 3            */
#define MTP2_ENT    0x16                /* Message Transfer Part Layer 2            */
#define TCAP_ENT    0x17                /* Transaction Capabilities Application Part*/
#define IUP_ENT     0x18                /* IUP */
#define TXMON_ENT   0x19                /* TX Monitor task on board                 */
#define SCCPMGR_ENT 0x1B                /* SCCP Manager entity ID on host side      */
#define NUP_ENT     0x1B                /* BT Network User Part Protocol Handler    */
#define MTP1_ENT    0x1C                /* Message Transfer Part Layer 1            */
#define TUP_ENT     0x1D                /* Telephone User Part Prorocol Handler     */
#define SCCP_ENT    0x1E                /* SCCP Protocol Handler                    */
#define ISUPCFG_ENT 0x33                /* ISUP Configuration utility (host only) - changed value to avoid MTPMGR conflict */
#define ISUPMGR_ENT 0x32                /* ISUP Manager utility (host only)         */
#define MONMGR_ENT  0x5e
#define MON_ENT     0x5f                /* SS7 Monitoring task */

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

#endif

typedef struct _mgmtHeader       /* header */
{
   U16 msgLen;                  /* message length   - optional */
   U8 msgType;                  /* message type     - mandatory */
   U8 version;                  /* version          - optional */
   U16 seqNmb;                  /* sequence number  - optional */
   U16 spare1;                  /* Spare for alignment */
   EntityId entId;              /* entity id        - mandatory */
   ElmntId elmId;               /* element id       - mandatory */
} MgmtHeader;


#ifndef TUP_DEMO

#endif

#ifndef TUP_TASK


typedef S16 QLen;                 /* queue length */
#endif

#define ST_MAX_CONG_LVLS  4


#ifndef TUP_TASK
#ifdef UNIX
#pragma pack()
#endif
#endif

/*
#ifdef __HIGHC__
#pragma Pop_align_members
#endif
*/

#endif
