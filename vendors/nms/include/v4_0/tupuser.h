/**************************************************************************
** tupuser.h
**
**     This file defines the interface between the host api and TXn000 task
**
**   Revision History:
**
*-----------------------------------------------------------------------------
* REV   DATE           WHO       $Log: tupuser.h,v $
* REV   DATE           WHO       Revision 1.1.2.1  2010/04/15 05:12:32  ssingh
* REV   DATE           WHO       added NMS 4K support includes for vendor abstraction layer.
* REV   DATE           WHO $NoKeywords: $
*
* 5     8/24/98 2:20p Marcn
* Added pragmas for Solaris structure packing
*
* 4     5/28/98 5:17p Dan
* Enhancement: Support for new TUPQuietReset call
*
* 3     6/06/97 9:39a Dan
* Enhancement:  Added event code for clearing statistics
*
* 2     6/06/97 9:15a Steve
* Enhancement: Added support for group status request
*
* 1     6/03/97 1:24p Steve
* Release A.0.0 initial check in
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
#ifndef TUPUSER_H_
#define TUPUSER_H_

/* Turn on structure packing for UNIX */
#ifndef TUP_TASK
#ifdef UNIX
#pragma pack(1)
#endif
#endif


/*------------------
  Event definitions
 ------------------*/

/* Events used by Management API */
#define EVT_SETCFG              1           /* Set configuration */
#define EVT_GETCFG              2           /* Get configuration */
#define EVT_RESET               3           /* Reset */
#define EVT_STATS               4           /* Get statistics */
#define EVT_STATUS              5           /* Get status */
#define EVT_TRACE               6           /* Trace */
#define EVT_BILLING             7           /* Billing */
#define EVT_MBLOCK              8           /* Maintenance Block */
#define EVT_SBLOCK              9           /* Software Block */
#define EVT_HBLOCK             10           /* Hardware Block */
#define EVT_MUNBLOCK           11           /* Maintenance Unblock */
#define EVT_SUNBLOCK           12           /* Software Unblock */
#define EVT_HUNBLOCK           13           /* Hardware Unblock */
#define EVT_DELETE             14           /* Delete */
#define EVT_ALARM              15           /* Alarm */
#define EVT_STATS_CLEAR        16           /* Get statistics, then clear the stats */
#define EVT_QUIET_RESET        17           /* clear the circuits to IDLE state */


/* Events used by Application API */
#define EVT_BIND               21           /* Bind request */
#define EVT_CONREQ             22           /* Connect request */
#define EVT_CONRSP             23           /* Connect response */
#define EVT_CONSTSREQ          24           /* Connect status request */
#define EVT_RELREQ             25           /* Release request */
#define EVT_RELRSP             26           /* Release response */
#define EVT_CTRLREQ            27           /* Control request */

/*-------------------
  Entity definitions
 -------------------*/
#define ENT_STGEN               1           /* general */
#define ENT_STNSAP              3           /* network SAP */
#define ENT_STUSAP                4           /* user SAP */
#define ENT_STROUT             10           /* route */
#define ENT_STENT              25           /* entity */
#define ENT_STDELROUT          30           /* delete route */
#define ENT_STISAP             34           /* tup SAP */
#define ENT_STCIRC             35           /* tup circuit */
#define ENT_STGRP              36           /* tup group */

/* Trace flags */
#define AENA             1           /* enable */
#define ADISIMM          2           /* disable - immediately */

/* IDs for SDU, MDU and PDU */
#define SDUID_      0x21534455      /* !SDU */
#define MDUID_      0x214d4455      /* !MDU */
#define PDUID_      0x21504455      /* !PDU */
#define MAX_LSI_TRC   280           /* Maximum length for tracing */

typedef struct _tupHdrM
{
  #ifdef TUP_TASK
    Chain         chain;
  #else
    DPRH    dpr;
  #endif
    U16     start;
    U16     end;
    U8 event;
    U8 spare1;                          /* Spare for alignment */
    U8 spare2;                          /* Spare for alignment */
    U8 spare3;                          /* Spare for alignment */
    U32     id;
  #ifndef SDUID_
  #define SDUID_      0x21534455      /* !SDU */
  #endif

  #ifndef MDUID_
  #define MDUID_      0x214d4455      /* !MDU */
  #endif

  #ifndef PDUID_
  #define PDUID_      0x21504455      /* !PDU */
  #endif
    S16     ccode;
    S16     fill1;                      /* Spare for alignment */
    U32     rvalu;
}TupHdrM;

typedef struct _tupHdrS
{
  #ifdef TUP_TASK
    Chain         chain;
  #else
    DPRH    dpr;
  #endif
    U16     start;
    U16     end;
    U8      event;
    U8      spare1;
    U8      spare2;
    U8      spare3;
    U32     id;
  #ifndef SDUID_
  #define SDUID_      0x21534455      /* !SDU */
  #endif

  #ifndef MDUID_
  #define MDUID_      0x214d4455      /* !MDU */
  #endif

  #ifndef PDUID_
  #define PDUID_      0x21504455      /* !PDU */
  #endif
    S16     ccode;
    S16     fill1;
    U32     rvalu;
} TupHdr;

typedef struct _TUPCntrl
{
    DateTime dt;           /* date and time */
    U8 action;             /* action */
    U8 subAction;          /* sub action */
    U8 spare1;             /* spare for alignment */
    U8 spare2;             /* spare for alignment */
    U32 cirId;            /* circuit id code */
} TUPCntrl;               /* control */

typedef struct _TUPTrc
{
    DateTime dt;
    U16 evnt;
    U8 sapType;
    U8 fill;                            /* Spare for alignment */
    U32 dpc;
    S16 length;
    S16 fill1;                          /* Spare for alignment */
    U8 evntParm[MAX_LSI_TRC];
} TUPTrc;                    /* trace */



#ifdef TUPMGMT_INC

/* Management Data Unit structure */
typedef struct _tupMdu
{
/*    TupHdr  hdr;*/
    U16     sapId;
    U16     groupId;
    U32     circId;
    U16     circCnt;
    U8      evntType;
    U8      entType;
    U32   cccode;
    union
    {
        TUPGenParms     genCfg;
        TUPUSapCfg      usapCfg;
        TUPNSapCfg      nsapCfg;
        TUPCircCfg      circCfg;
        TUPGrpCfg       grpCfg;
        TUPRouteCfg     routeCfg;
        TUPUSapStats    usapStats;
        TUPNSapStats    nsapStats;
        TUPCircStats    circStats;
        TUPGrpStats     grpStats;
        TUPCircStatus   circStatus;
        TUPGrpStatus    grpStatus;
    } data;
} TupMduo;

/*New Management Data Unit structure which contains 20 bytes of chain structure*/
typedef struct _tupMdum
{
  TupHdrM hdr;
  U16     sapId;
  U16     groupId;
  U32     circId;
  U16     circCnt;
  U8      evntType;
  U8      entType;
  union
  {
    TUPGenParms     genCfg;
    TUPUSapCfg      usapCfg;
    TUPNSapCfg      nsapCfg;
    TUPCircCfg      circCfg;
    TUPGrpCfg       grpCfg;
    TUPRouteCfg     routeCfg;
    TUPUSapStats    usapStats;
    TUPNSapStats    nsapStats;
    TUPCircStats    circStats;
    TUPGrpStats     grpStats;
    TUPCircStatus   circStatus;
    TUPGrpStatus    grpStatus;
    TUPCntrl       cntrl;
    TUPTrc         trc;
  } data;
} TupMdum;
typedef struct _tupMdum TupMdu;
typedef struct _tupMdum TupMdux;


#endif

#ifdef TUPAPI_INC

/* Service Data Unit structure */
typedef struct _tupSdu
{
    TupHdr  hdr;
    U16     spId;
    U16     suId;
    U32     spInstId;
    U32     suInstId;
    U32     circId;
    U8      evntType;
    U8      subType;
    U16     spare2;
    union
    {
        TupConEvnt      conEvnt;
        TupConRspEvnt   conRspEvnt;
        TupCnStEvnt     conStEvnt;
        TupRelEvnt      relEvnt;
        TupStaEvnt      staEvnt;
    } data;
    TupErrInfo          errInfo;
} TupSdu;
#endif

#ifndef TUP_TASK
#ifdef UNIX
#pragma pack()
#endif
#endif

#endif
