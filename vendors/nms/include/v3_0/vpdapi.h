/*****************************************************************************
* File:    vpdapi.h
*
* Prototypes for Virtual Port Driver API routines.
*
*-----------------------------------------------------------------------------
* REV   DATE           WHO       $Log: vpdapi.h,v $
* REV   DATE           WHO       Revision 9.1  2005/03/23 12:55:51  cvsadmin
* REV   DATE           WHO       Begin PR6.5
* REV   DATE           WHO
* REV   DATE           WHO       Revision 8.2  2005/03/21 13:55:15  cvsadmin
* REV   DATE           WHO       PR6.4.2 Source Propagated to Current
* REV   DATE           WHO
* REV   DATE           WHO       Revision 7.1  2002/08/26 22:10:52  mmiers
* REV   DATE           WHO       Begin PR6.2
* REV   DATE           WHO
* REV   DATE           WHO       Revision 6.1  2002/02/28 16:14:54  mmiers
* REV   DATE           WHO       Begin PR7.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1  2001/09/05 20:35:47  mmiers
* REV   DATE           WHO       Consolidate the NMS libraries.  Only the root library so far.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 5.1  2001/08/16 20:46:40  mmiers
* REV   DATE           WHO       Start PR6.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 4.1  2001/05/04 16:22:07  mmiers
* REV   DATE           WHO       Start PR5.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 3.1  2000/08/16 00:11:31  mmiers
* REV   DATE           WHO
* REV   DATE           WHO       Begin round 4.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.4  2000/06/09 22:02:35  randresol
* REV   DATE           WHO       Adding file to current tree
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1.2.1  2000/05/16 21:17:29  randresol
* REV   DATE           WHO       Add include files for SS7 Version 3 software for TX3220
* REV   DATE           WHO
* 
* 6     5/27/99 12:38p Jrego
* Migrating to new Core Group source control system
* 
* 5     10/22/97 1:40p Vince
* Duplicated the function prototypes. Protected the parallel set with
* preprocessor directives, and moved the _export directive (macro) to an
* acceptable location for the Watcom compiler.
* 
* 4     9/10/97 3:52p Adam
* Fix export problems
*
* 3     5/16/97 1:54p Vince
* Changed export method to use macro TXVPDFUNC to provide compiler
* _export directives in DLL source.
*
* 2     1/28/97 5:19p Jeffr
* Added support for data transfer API
*
* 1     1/02/97 10:25a Jeffr
* Initial Checkin
*-----------------------------------------------------------------------------
******************************************************************************/

/**************************************************************************
 **
 **			   PROPRIETARY NOTICE
 **
 **        Copyright (c) 1996
 **      By Natural MicroSystems.
 **
 **
 **  The following is licensed program material and is considered
 **  proprietary and confidential.  No part of this program may be
 **  reproduced or used in any form or by any means without the express
 **  written permission of Natural MicroSystems.
 **
 *************************************************************************/
#ifndef _VPDAPI_H_
#define _VPDAPI_H_

#include "vpdtype.h"

#ifdef TXXPORT
#undef   TXXPORT
#endif

#ifdef WIN32      /* 32 bit Windows OS */

#ifdef _TX_VPD_SOURCE_
    /* VPD API source definition */

#define     TXXPORT     __declspec( dllexport )
#define     TXVPDFUNC   WINAPI
#else
    /* VPD API caller's definition */
#define     TXXPORT
#define     TXVPDFUNC   WINAPI
#endif  /* _TX_VPD_SOURCE_ */

#elif __OS2__      /*IBM OS/2*/

#ifdef _TX_VPD_SOURCE_
    /* VPD API source definition */
#define     TXXPORT     _export
#define     TXVPDFUNC   _System
#else
    /* VPD API caller's definition */
#define     TXXPORT
#define     TXVPDFUNC   _System
#endif

#else  /* all other OS statically linked */
#define     TXXPORT
#define     TXVPDFUNC
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------
 * TxVpd CPI-Interface Functions
 *---------------------------------------------------------------------------*/
#ifdef __OS2__
short TXXPORT TXVPDFUNC TxVpdOpen     ( unsigned char board, TX_HANDLE *handle );
short TXXPORT TXVPDFUNC TxVpdClose    ( TX_HANDLE handle );
short TXXPORT TXVPDFUNC TxVpdControl  ( unsigned char msgtrc );

short TXXPORT TXVPDFUNC TxVpdMvipCfg  ( TX_HANDLE handle, unsigned short main_mode, unsigned short sec8k_mode,
                                        unsigned short network );
short TXXPORT TXVPDFUNC TxVpdT1E1Cfg  ( TX_HANDLE handle, unsigned char network, unsigned char framemode,
                                        unsigned char encoding, unsigned char linebldout,
                                        unsigned char robbedbit, unsigned char loopmaster );
short TXXPORT TXVPDFUNC TxVpdDefine   ( TX_HANDLE handle, TXVPD_RES *res );
short TXXPORT TXVPDFUNC TxVpdDestroy  ( TX_HANDLE handle, unsigned short resource );
short TXXPORT TXVPDFUNC TxVpdConfig   ( TX_HANDLE handle, unsigned short resource, TXVPD_CFG *cfg );
short TXXPORT TXVPDFUNC TxVpdVport    ( TX_HANDLE handle, unsigned short resource, unsigned short vport_num,
                                        TXVPD_ADDR *addr );

short TXXPORT TXVPDFUNC TxVpdAttach   ( TX_HANDLE handle, unsigned short vport_num,
                                        void *userkey, TXVPD_DPR_REQ *dprreq );
short TXXPORT TXVPDFUNC TxVpdEnable   ( TX_HANDLE handle,
                                        void *userkey, unsigned long cpkey, TXVPD_DPR_REQ *dprreq );
short TXXPORT TXVPDFUNC TxVpdDisable  ( TX_HANDLE handle,
                                        void *userkey, unsigned long cpkey, TXVPD_DPR_REQ *dprreq );
short TXXPORT TXVPDFUNC TxVpdDetach   ( TX_HANDLE handle,
                                        void *userkey, unsigned long cpkey, TXVPD_DPR_REQ *dprreq );
short TXXPORT TXVPDFUNC TxVpdTx       ( TX_HANDLE handle, unsigned short datalen,
                                        void *userkey, unsigned long cpkey, TXVPD_DPR_REQ *dprreq );

short TXXPORT TXVPDFUNC TxVpdLastRsp  ( TXVPD_DPR_RSP *lastrsp );
char * TXXPORT TXVPDFUNC TxVpdErrorStr ( short vpderror );

/*---------------------------------------------------------------------------
 * TxVpd Packet Fill Functions
 *---------------------------------------------------------------------------*/
short TXXPORT TXVPDFUNC TxVpdReqInit  ( TX_HANDLE handle, TXVPD_DPR_REQ *vpdreq, unsigned char msgnum );

short TXXPORT TXVPDFUNC TxVpdResDflt  ( TXVPD_RES *res );
short TXXPORT TXVPDFUNC TxVpdResDef   ( TXVPD_RES *res, unsigned short resource,
                                        unsigned char hw_type, unsigned char hw_num, unsigned char protocol );
short TXXPORT TXVPDFUNC TxVpdResTdm   ( TXVPD_RES *res,
                                        unsigned char stream, unsigned char channel, unsigned char count );

short TXXPORT TXVPDFUNC TxVpdCfgDflt  ( TXVPD_CFG *cfg, unsigned long rxfrm );
short TXXPORT TXVPDFUNC TxVpdCfgHdlc  ( TXVPD_CFG *cfg,
                                        unsigned short logparms, unsigned long intclkbr );

short TXXPORT TXVPDFUNC TxVpdAddrDef  ( TXVPD_ADDR *addr, unsigned char priority, unsigned char flags,
                                        unsigned char num_addrs,
                                        unsigned long addr1, unsigned long addr2,
                                        unsigned long addr3, unsigned long addr4 );

#else /* !OS2 */

TXXPORT short TXVPDFUNC TxVpdOpen     ( unsigned char board, TX_HANDLE *handle );
TXXPORT short TXVPDFUNC TxVpdClose    ( TX_HANDLE handle );
TXXPORT short TXVPDFUNC TxVpdControl  ( unsigned char msgtrc );

TXXPORT short TXVPDFUNC TxVpdMvipCfg  ( TX_HANDLE handle, unsigned short main_mode, unsigned short sec8k_mode,
                                        unsigned short network );
TXXPORT short TXVPDFUNC TxVpdT1E1Cfg  ( TX_HANDLE handle, unsigned char network, unsigned char framemode,
                                        unsigned char encoding, unsigned char linebldout,
                                        unsigned char robbedbit, unsigned char loopmaster );
TXXPORT short TXVPDFUNC TxVpdDefine   ( TX_HANDLE handle, TXVPD_RES *res );
TXXPORT short TXVPDFUNC TxVpdDestroy  ( TX_HANDLE handle, unsigned short resource );
TXXPORT short TXVPDFUNC TxVpdConfig   ( TX_HANDLE handle, unsigned short resource, TXVPD_CFG *cfg );
TXXPORT short TXVPDFUNC TxVpdVport    ( TX_HANDLE handle, unsigned short resource, unsigned short vport_num,
                                        TXVPD_ADDR *addr );

TXXPORT short TXVPDFUNC TxVpdAttach   ( TX_HANDLE handle, unsigned short vport_num,
                                        void *userkey, TXVPD_DPR_REQ *dprreq );
TXXPORT short TXVPDFUNC TxVpdEnable   ( TX_HANDLE handle,
                                        void *userkey, unsigned long cpkey, TXVPD_DPR_REQ *dprreq );
TXXPORT short TXVPDFUNC TxVpdDisable  ( TX_HANDLE handle,
                                        void *userkey, unsigned long cpkey, TXVPD_DPR_REQ *dprreq );
TXXPORT short TXVPDFUNC TxVpdDetach   ( TX_HANDLE handle,
                                        void *userkey, unsigned long cpkey, TXVPD_DPR_REQ *dprreq );
TXXPORT short TXVPDFUNC TxVpdTx       ( TX_HANDLE handle, unsigned short datalen,
                                        void *userkey, unsigned long cpkey, TXVPD_DPR_REQ *dprreq );

TXXPORT short TXVPDFUNC TxVpdLastRsp  ( TXVPD_DPR_RSP *lastrsp );
TXXPORT char * TXVPDFUNC TxVpdErrorStr ( short vpderror );

/*---------------------------------------------------------------------------
 * TxVpd Packet Fill Functions
 *---------------------------------------------------------------------------*/
TXXPORT short TXVPDFUNC TxVpdReqInit  ( TX_HANDLE handle, TXVPD_DPR_REQ *vpdreq, unsigned char msgnum );

TXXPORT short TXVPDFUNC TxVpdResDflt  ( TXVPD_RES *res );
TXXPORT short TXVPDFUNC TxVpdResDef   ( TXVPD_RES *res, unsigned short resource,
                                        unsigned char hw_type, unsigned char hw_num, unsigned char protocol );
TXXPORT short TXVPDFUNC TxVpdResTdm   ( TXVPD_RES *res,
                                        unsigned char stream, unsigned char channel, unsigned char count );

TXXPORT short TXVPDFUNC TxVpdCfgDflt  ( TXVPD_CFG *cfg, unsigned long rxfrm );
TXXPORT short TXVPDFUNC TxVpdCfgHdlc  ( TXVPD_CFG *cfg,
                                        unsigned short logparms, unsigned long intclkbr );

TXXPORT short TXVPDFUNC TxVpdAddrDef  ( TXVPD_ADDR *addr, unsigned char priority, unsigned char flags,
                                        unsigned char num_addrs,
                                        unsigned long addr1, unsigned long addr2,
                                        unsigned long addr3, unsigned long addr4 );
#endif

#ifdef __cplusplus
}
#endif

#endif
