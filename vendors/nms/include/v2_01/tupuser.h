/**************************************************************************
** tupuser.h
**
**     This file defines the interface between the host api and TXn000 task
**
**   Revision History:
**
*-----------------------------------------------------------------------------
* REV   DATE           WHO       $Log: tupuser.h,v $
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

/* Turn on structure packing for Solaris */
#ifdef __sun
#pragma pack(1)
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
#define ENT_STUSAP              4           /* user SAP */
#define ENT_STROUT             10           /* route */
#define ENT_STENT              25           /* entity */
#define ENT_STDELROUT          30           /* delete route */
#define ENT_STISAP             34           /* tup SAP */
#define ENT_STCIRC             35           /* tup circuit */
#define ENT_STGRP              36           /* tup group */

typedef struct _tupHdr
{
    DPRH    dpr;
    U16     start;
    U16     end;
    U32     id;
#define SDUID_      0x21534455      /* !SDU */
#define MDUID_      0x214d4455      /* !MDU */
#define PDUID_      0x21504455      /* !PDU */
    void   *flink;
    void   *blink;
    S16     ccode;
    U32     rvalu;
} TupHdr;

#ifdef TUPMGMT_INC

/* Management Data Unit structure */
typedef struct _tupMdu
{
    TupHdr  hdr;
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
    } data;
} TupMdu;

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

#ifdef __sun
#pragma pack()
#endif

#endif

