/*****************************************************************************
* File:    vpdtype.h
*
* Data type declarations and constant values for Virtual Port Driver API.
*
* NOTE: Structures and Literals defined in this file must remain in sync
*       with those defined in
*-----------------------------------------------------------------------------
* REV   DATE           WHO       $Log: vpdtype.h,v $
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
* REV   DATE           WHO       Revision 1.4  2000/06/09 22:02:36  randresol
* REV   DATE           WHO       Adding file to current tree
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1.2.1  2000/05/16 21:17:30  randresol
* REV   DATE           WHO       Add include files for SS7 Version 3 software for TX3220
* REV   DATE           WHO
* 
* 6     5/26/99 10:07a Jrego
* Migrating to new Core Group source control system
* 
* 5     2/17/99 12:00p Jeffr
* Mailbox auto-address enhancement & OVERWRITE fix (per Adam)
*
* 4     4/24/98 11:38a Adam
* Resync and save on network drive
*
* 3     1/28/97 5:19p Jeffr
* Added support for data transfer API
*
* 2     1/16/97 10:42a Adam
* Start Adding VPORT API all the way out to the PC
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
#ifndef _VPDTYPE_H_
#define _VPDTYPE_H_

/*---------------------------------------------------------------------------
 * TxVpd Literals
 *---------------------------------------------------------------------------*/
#define TXVPD_DPRCHAN   13          /* Dual Port Ram channel number for VPD access */

#define TXVPD_MAXDEMUX  4           /* maximum number of demux addresses for single vport */
#define TXVPD_DEMUXALL  0xFFFFFFFFL /* demux_addr when attaching for ALL addrs */

/* ----- TxVpd Message Trace Levels (passed to TXn000 for on-board message tracing as well) */
#define TXVPD_MSGTRC_CP 1           /* CP tracing of messages (see CPCON> LOG command) */

/* ----- TxVpd Error Codes */
#define TXVPD_ERRCODE_BASE  (CPI_ERRCODE_BASE+0x100)
#define TXVPD_RSPLEN        (TXVPD_ERRCODE_BASE+0)  /* response length invalid for request */
#define TXVPD_RSPWRONG      (TXVPD_ERRCODE_BASE+1)  /* pkt rcvd as rsp not what was expected */
#define TXVPD_NOLASTRSP     (TXVPD_ERRCODE_BASE+2)  /* there is no last response to return */
#define TXVPD_INVALREQ      (TXVPD_ERRCODE_BASE+3)  /* request type indicated is invalid */
#define TXVPD_ERRCODE_MAX   (TXVPD_ERRCODE_BASE+3)

/*---------------------------------------------------------------------------
 * TxVpd Structures
 *---------------------------------------------------------------------------*/

/* ----- TxVpd MVIP Configuration */
typedef struct _txvpd_mvipcfg
{
  unsigned short main_mode;
  unsigned short sec8k_mode;
  unsigned short network;
} TXVPD_MVIPCFG;

/* ----- TxVpd T1/E1 Configuration */
typedef struct _txvpd_t1e1cfg
{
  unsigned char  network;               /* indicator of which T1/E1 is being config'd */
  unsigned char  framemode;
  unsigned char  encoding;
  unsigned char  linebldout;
  unsigned char  robbedbit;
  unsigned char  loopmaster;
} TXVPD_T1E1CFG;

/* ----- TxVpd Demultiplex Address(es) Specification */
typedef struct _txvpd_addr
{
  unsigned char  flags;                 /* Flags byte */
#define TXVPA_OVERWRITE   (1<<0)        /* If set, overwrite TX Address with RX Addr[0] */
#define TXVPA_SOCKETADDR  (1<<1)        /* If set, addr array changes meaning */
#define TXVPA_AUTOADDR    (1<<2)        /* If set, and num_addr=0, automaticaly
                                           generate a demux address value     */
#define TXVPA_OW_LOCPORT  (1<<3)        /* If set, overwrite Local Port # (Prot Specific) */
#define TXVPA_OW_LOCDEV   (1<<4)        /* If set, overwrite Local Device # (Prot Specific) */
#define TXVPA_OW_REMPORT  (1<<5)        /* If set, overwrite Remote Port # (Prot Specific) */
#define TXVPA_OW_REMDEV   (1<<6)        /* If set, overwrite Remove Port # (Prot Specific) */
  unsigned char  priority;              /* Priority of RX Demuxing */
  unsigned char  num_addrs;             /* number of addrs associated with virtual port */
  unsigned char  avail;                 /* Long align */
  unsigned long  addr[TXVPD_MAXDEMUX];  /* demux address set */
} TXVPD_ADDR;

/* ----- TxVpd Additional Resource Configuration [by TDM connection type] */
typedef struct txvpd_tdmconn
{
  unsigned char stream;               /* TDM stream */
  unsigned char channel;              /* TDM time slot */
  unsigned char count;                /* number of channels in a hyper-channel */
  unsigned char avail;
} TXVPD_TDMCONN;

/* ----- TxVpd Resource Definition */
typedef struct _txvpd_res
{
  unsigned short resource;        /* resource number */
  unsigned char  hw_type;         /* type of physical hardware resource applies to */
#define TXVPD_HWDPR   1
#define TXVPD_HWSCC   2
#define TXVPD_HWETH   3
#define TXVPD_HWATM   4

  unsigned char  hw_num;          /* hardware number (e.g. SCC number) */
  unsigned char  flags;
#define TXVPD_RES_SHARED  (1<<0)  /* set = resource may be shared (address demultiplexing) */

  unsigned char  avail;
  unsigned char  protocol;        /* Lev1 protocol that will be used on this resource */
#define TXVPD_PROT_NONDEF 0
#define TXVPD_PROT_ETH    1
#define TXVPD_PROT_ASY    2
#define TXVPD_PROT_HDLC   3
#define TXVPD_PROT_SS7    4
#define TXVPD_PROT_NSNR   5

  unsigned char  connection;      /* type of connection that protocol will be used over */
#define TXVPD_C_HBUS      1       /* Host Bus Interface */
#define TXVPD_C_SERIAL    2       /* Serial Communications Controller */
#define TXVPD_C_ETH       3       /* Ethernet Network Interface Controller */
#define TXVPD_C_TDM       4       /* MVIP/T1/E1 TDM Controller */
#define TXVPD_C_EEPROM    5       /* EEPROM Controller */

  union                           /* type determined by if_type of TxVpdDefine */
  {
    TXVPD_TDMCONN   tdm;          /* TDM additional configuration */
  } conn;
} TXVPD_RES;

/* ----- TxVpd Protocol Configuration */

/*-------------
 * HDLC Config
 *-------------*/
typedef struct _vpdhdlc_cfg
{
   unsigned short  logparms;     /* logical (bit) parameters */
#define TXVPD_HDLC_IDLEFL_  (1<<13) /* bit set = idle in flags if set */
#define TXVPD_HDLC_ITXCLK_  (1<<12) /* bit set = internal transmit clock if set */
#define TXVPD_HDLC_NRZI_    (1<<10) /* bit set = NRZI option if set */
#define TXVPD_HDLC_MOD_     (1<<9)  /* bit set = incoming ring modem if set */
#define TXVPD_HDLC_V24_     (1<<8)  /* bit set = V24 leased line if set */
#define TXVPD_HDLC_HALF_    (1<<7)  /* bit set = SDLC half-duplex protocol if set */

   unsigned long   intclkbr;     /* internal clock baud rate */
} TXVPD_HDLC_CFG;

typedef struct _txvpd_cfg
{
  unsigned long  rxfrm;           /* RX frame size */
  union                           /* type determined by if_type of TxVpdDefine */
  {
    TXVPD_HDLC_CFG   hdlc;           /* HDLC protocol configuration */
  } prot;
} TXVPD_CFG;

/* ----- VPD Virtual Port Statistics */
typedef struct _txvpd_stats
{
  unsigned char   state;          /* current state of virtual port */
#define VPORT_FREE      0x00      /* Virtual port currently unused */
#define VPORT_DISABLED  0x01      /* virtual port currently disabled */
#define VPORT_IDLE      0x02      /* virtual port enabled; not currently transmitting */
#define VPORT_TXING     0x03      /* virtual port currently transmitting frame(s) */
#define VPORT_FULL      0x04      /* virtual port's transmit queue is full */
#define VPORT_DISABING  0x05      /* virtual port is disabling */
#define VPORT_STALLED   0x06      /* Stalled due to internal Error */

  unsigned char   avail;
  unsigned long   txframes;       /* number of frames transmitted successfully */
  unsigned long   txbytes;        /* number of bytes transmitted successfully */
  unsigned long   rxframes;       /* number of frames received successfully */
  unsigned long   rxbytes;        /* number of bytes received successfully */
  unsigned long   txfail;         /* number of transmit requests that have failed */
  unsigned long   rxfail;         /* number of interrupted receive frames */
  unsigned long   rxdrop;         /* Number of frames droped due to no match */
  short           last_error;     /* last error reported */
} TXVPD_STATS;


/*---------------------------------------------------------------------------
 * TxVpd Function parameter definitions (API params as structures)
 *---------------------------------------------------------------------------*/

/* ----- Define Resource (TxVpdDefine) */
typedef struct txvpd_p_define
{
  TXVPD_RES       vpdres;     /* Resource Definition */
} TXVPD_P_DEFINE;

/* ----- Destroy Resource (TxVpdDestroy) */
typedef struct txvpd_p_destroy
{
  unsigned short  vpdresnum;  /* Resource Number */
} TXVPD_P_DESTROY;

/* ----- Configure Resource (TxVpdConfig) */
typedef struct txvpd_p_config
{
  unsigned short  vpdresnum;  /* Resource Number */
  TXVPD_CFG       vpdcfg;     /* Protocol Configuration */
} TXVPD_P_CONFIG;

/* ----- Define Virtual Port (TxVpdVport) */
typedef struct txvpd_p_vport
{
  unsigned short  vpdresnum;  /* Resource Number */
  unsigned short  vpdvpnum;   /* Virtual Port Number */
  TXVPD_ADDR      vpdaddr;    /* Demultiplex Address(es) */
} TXVPD_P_VPORT;

/* ----- Attach to Virtual Port (TxVpdAttach) */
typedef struct txvpd_p_attach
{
  unsigned short  vpdvpnum;   /* Virtual Port Number */
  unsigned long   vpdatchkey; /* User's attach key */
} TXVPD_P_ATTACH;

/* ----- Virtual Port Identification structure */
/* Used for  requests:         DETACH, VPSTATS, CLRSTATS, ENABLE, DISABLE
 *          responses: ATTACH, DETACH,          CLRSTATS, ENABLE, DISABLE, TX */
typedef struct txvpd_p_vpid
{
  unsigned long   vpdatchkey; /* User's attach key */
  unsigned long   vpdcpctl;   /* CP's virtual port control key (from ATTACH rsp) */
} TXVPD_P_VPID;

/* ----- Register for Virtual Port Signal Changes (TxVpdRegsigs) */
typedef struct txvpd_p_regsigs
{
  TXVPD_P_VPID    vpdid;      /* virtual port identification */
  unsigned long   vpdsigmask; /* mask of signals to register for */
} TXVPD_P_REGSIGS;

#define MAXVPDDATA (MAXCPIDATA - (sizeof(TX_DPR_MSGHDR) + sizeof(TXVPD_P_VPID)))
/* ----- Transmit/Receive over Virtual Port (TxVpdTx | receive notif) */
typedef struct txvpd_p_data
{
  TXVPD_P_VPID    vpdid;      /* virtual port identification */
  unsigned char   vpddata[MAXVPDDATA];  /* data to be transmitted | data received */
} TXVPD_P_DATA;

/* ----- MVIP Config (TxVpdMvipCfg) */
typedef struct txvpd_p_mvipcfg
{
  TXVPD_MVIPCFG   vpdmvip;    /* MVIP clock configuration */
} TXVPD_P_MVIPCFG;

/* ----- T1/E1 Config (TxVpdT1E1Cfg) */
typedef struct txvpd_p_t1e1cfg
{
  TXVPD_T1E1CFG   vpdt1e1;    /* T1/E1 configuration */
} TXVPD_P_T1E1CFG;

/* ----- General Response */
typedef struct txvpd_p_rsp
{
  unsigned long   future;     /* Reserved for future expansion */
} TXVPD_P_RSP;

/*---------------------------------------------------------------------------
 * TxVpd Dual Port Ram packet definitions
 *---------------------------------------------------------------------------*/

/* ----- DPR MSGHDR msgnum values */
#define TXVPD_DPR_DEFINE   0x01 /* TxVpdDefine   */
#define TXVPD_DPR_DESTROY  0x02 /* TxVpdDestroy  */
#define TXVPD_DPR_CONFIG   0x03 /* TxVpdConfig   */
#define TXVPD_DPR_VPORT    0x04 /* TxVpdVport    */
#define TXVPD_DPR_MVIPCFG  0x05 /* TxVpdMvipCfg  */
#define TXVPD_DPR_T1E1CFG  0x06 /* TxVpdT1E1Cfg  */
#define TXVPD_DPR_ATTACH   0x07 /* TxVpdAttach   */
#define TXVPD_DPR_DETACH   0x08 /* TxVpdDetach   */
#define TXVPD_DPR_REGSIGS  0x09 /* TxVpdRegsigs  */
#define TXVPD_DPR_VPSTATS  0x0A /* TxVpdVpstats  */
#define TXVPD_DPR_CLRSTATS 0x0B /* TxVpdClrstats */
#define TXVPD_DPR_ENABLE   0x0C /* TxVpdEnable   */
#define TXVPD_DPR_DISABLE  0x0D /* TxVpdDisable  */
#define TXVPD_DPR_TX       0x0E /* TxVpdTx       */
#define TXVPD_DPR_RX       0x0F /* receive notif */

typedef struct txvpd_dpr_data
{
  union
  {
    TXVPD_P_DEFINE  define;     /* TxVpdDefine  parameters */
    TXVPD_P_DESTROY destroy;    /* TxVpdDestroy parameters */
    TXVPD_P_CONFIG  config;     /* TxVpdConfig  parameters */
    TXVPD_P_VPORT   vport;      /* TxVpdVport   parameters */
    TXVPD_P_MVIPCFG mvip;       /* TxVpdMvipCfg parameters */
    TXVPD_P_T1E1CFG t1e1;       /* TxVpdT1E1Cfg parameters */
    TXVPD_P_ATTACH  attach;     /* TxVpdAttach  parameters */
    TXVPD_P_VPID    vpid;       /* standard attach-related request|response */
    TXVPD_P_REGSIGS regsigs;    /* TxVpdRegsigs parameters */
    TXVPD_P_DATA    data;       /* TxVpdTx (and RX notif) parameters */
    TXVPD_P_RSP     response;   /* general response to any request */
  } u;
} TXVPD_DPR_DATA;

typedef struct txvpd_dpr_req
{
  TX_DPR_REQHDR     req;        /* common request header */
  TXVPD_DPR_DATA    data;       /* request data */
} TXVPD_DPR_REQ;

typedef struct txvpd_dpr_rsp
{
  TX_DPR_RSPHDR     rsp;        /* common response header */
  TXVPD_DPR_DATA    data;       /* response data */
} TXVPD_DPR_RSP;

#endif

