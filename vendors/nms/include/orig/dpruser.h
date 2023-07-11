/******************************************************************************
*
*       dpruser.h - USER ACCESSABLE Dual Port Ram definitions file
*
*       DD-MMM-YY    Who                   Description                   Tag
*       =========  =======  ==========================================  ======
*       24-FEB-95  AJM      Add DPR 'C' Interface Prototypes            <C1.14>
*       02-Nov-95  jmd      Reserve DPR channels for MVIP & SS7         <d1.90>
*
*-----------------------------------------------------------------------------
* REV   DATE           WHO       $Log: dpruser.h,v $
* REV   DATE           WHO       Revision 9.1  2005/03/23 12:55:43  cvsadmin
* REV   DATE           WHO       Begin PR6.5
* REV   DATE           WHO
* REV   DATE           WHO       Revision 8.2  2005/03/21 13:55:04  cvsadmin
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
* REV   DATE           WHO       Revision 5.1  2001/08/16 20:46:34  mmiers
* REV   DATE           WHO       Start PR6.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 4.1  2001/05/04 16:22:07  mmiers
* REV   DATE           WHO       Start PR5.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 3.1  2000/08/16 00:10:41  mmiers
* REV   DATE           WHO
* REV   DATE           WHO       Begin round 4.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 2.0  1999/12/03 23:33:01  mmiers
* REV   DATE           WHO
* REV   DATE           WHO       Begin third iteration.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1  1998/01/15 01:38:57  rsonak
* REV   DATE           WHO       *** empty log message ***
* REV   DATE           WHO $NoKeywords: $
* 
* 1     3/10/97 3:24p Adam
* Release 6.5 Beta to NMS Natick
* 
* 4     1/22/97 12:11p Steve
* Added port assignments for SS7 protocols
*
* 3     12/13/96 10:26a Jeffr
* Added DPR Request/Response Msg layer
*
* 2     11/19/96 12:58p Jeffr
* Added Virtual Port Driver Dual Port Ram channel
 *
 * 1     9/12/96 5:14p Adam
 * Initial Recovery Checkin
*
* 6     8/28/96 2:27p Maf
* Added the __STDC__ ifdef bracket around the prototypes at the end of
* the file. In SCO UNIX the kernel is build with a non-ansi compiler and
* the prototypes will cause the kernel build to fail if the file is
* included in a driver.
*
* 5     8/21/96 3:15p Steve
*
* 4     5/16/96 1:57p Jeffr
* Added RAW Dual Port Ram Logger to INF
*
* 3     4/08/96 2:42p Jeffd
* Add 2 DPR channel assignments for T1 control and status channels.
*
* 2     2/15/96 8:51a Jeffr
* Added Source Safe log header
*-----------------------------------------------------------------------------
******************************************************************************/
#ifndef _DPRUSER_H_
#define _DPRUSER_H_

/* ----- Dual Port RAM ports */
#define PT_RMTDPR  31       /* Remote DPR control port id            <D1> */
#define PT_SS7     15       /* SS7 API port                          <D1.90> */
#define PT_VPD     13       /* Virtual Port Driver */
#define PT_INF     12       /* INF raw alarm port id */
#define PT_T1E1S   11       /* T1/E1 Status port                     <D1.xx> */
#define PT_T1E1C   10       /* T1/E1 Control port                    <D1.xx> */
#define PT_MVIP     9       /* MVIP Control port                     <D1.90> */
#define PT_DEBUG    8       /* debug port id                         <D0> */
#define PT_LOADER   7       /* task loader port id                   <D0> */
#define PT_CONSOLE  6       /* console port id */
#define PT_NETMNGR  5       /* network manager id */
#define PT_X25      4       /* X25 transmission over packet driver */
#define PT_FILEMNGR 3       /* file manager id */
#define PT_HIP      2       /* Host IP port id */
#define PT_NBX      1       /* NetBios to X25 id */
#define PT_MTP      0x15
#define PT_ISUP     0x14
#define PT_SCCP     0x1e

/* ----- Dual Port RAM port types (high byte of channel on dpr_crea) */
#define DPRT_NORM       0   /* normal channel type (true DPR channel) */
#define DPRT_PSEUDOHOST 1   /* simulating host side of DPRAM for given channel */

/* ----- DPR Packet Header Structure   <D0> */
typedef struct __dprh
{
  unsigned char  srcch;     /* Source channel number */
  unsigned char  srcbd;     /* Source board number (0 = PC) */
  unsigned char  dstch;     /* Destination channel number */
  unsigned char  dstbd;     /* Destination board # (0 = PC) */
  unsigned short len;       /* Len of message body (incl hdr) */
#define DPH_F_MORE   (1<<7) /* INTERNAL more flag (high bit of 1st byte) */

} DPRH;
#define dprhsize (sizeof(DPRH))

/* ----- Request/Response extensions to Dual Port Ram header */
typedef struct __dprmsghdr
{
  unsigned char   msgdir;
#define DPRMSG_TOCP    '>'        /* message being passed from HOST to TXn000 CP */
#define DPRMSG_TOHOST  '<'        /* message being passed from TXn000 CP to HOST */

  unsigned char   msgtype;
#define DPRMSG_COMMAND 'C'        /* command request */
#define DPRMSG_RESULT  'R'        /* result (response to command request) */
#define DPRMSG_NOTIF   'N'        /* notification */
#define DPRMSG_ACK     'A'        /* acknowledgement (response to notification) */

  unsigned char   msgnum;         /* message number (specific to application interface) */
  unsigned char   msgtrc;         /* trace level    (specific to application interface) */
  unsigned long   msgid;          /* unique id of COMMAND|NOTIF [returned in RESULT|ACK] */
  unsigned long   msgkey;         /* key assoc'd w/ COMMAND|NOTIF [returned in RESULT|ACK] */
  unsigned long   future;         /* area reserved for future extension of TX MSG control */
} DPRMSGHDR;

typedef struct __dprreqhdr
{
  DPRH            hdr;            /* Dual Port Ram header */
  DPRMSGHDR       msg;            /* Message header */
} DPRREQHDR;

typedef struct __dprrsphdr
{
  DPRH            hdr;            /* Dual Port Ram header */
  DPRMSGHDR       msg;            /* Message header */
  short           status;         /* Status of response */
  short           future;         /* area reserved for future extension of TX responses */
} DPRRSPHDR;

/* ----- Info buffer returned */
typedef struct __dpiinfo
{
  unsigned long dpirxnomem;     /* rx frames dropped because no memory */
  unsigned long dpirxgiant;     /* rx frames dropped because too big */
  unsigned long dpirxqerr;      /* rx frames dropped because queue error */
  unsigned long dpirxderr;      /* deallocation errors */
  unsigned long dpitxfail;      /* failure reported from DPRsend        <D0> */
  unsigned long dpitxbadcp;     /* destined for invalid CP number       <D0> */
  unsigned long dpitxqerr;      /* error while handling TX queue        <D0> */
  unsigned long dpirxsucc;      /* frames received successfully         <D0> */
  unsigned long dpitxsucc;      /* frames transmitted successfully      <D0> */

} DPIINFO;
#define dpisize (sizeof(DPIINFO))

#define DPROK_      0   /* success */
#define DPROVRF_    1   /* overflow error */
#define DPRLEN_     2   /* length error */
#define DPRCHAN_    3   /* invalid channel specified */

/*-----------------------------------------------------------------------------
// Add Dual Port Ram 'C' Prototypes				<C1.14>
//---------------------------------------------------------------------------*/
#ifdef __STDC__
short dpr_crea( void *userkey, void *libctx, unsigned short channel,void **dprkey);
short dpr_dest( void *dprkey, void *userkey, void *libctx);
short dpr_rxon( void *dprkey, void *userkey, void *rxnotf);
short dpr_rxoff( void *dprkey, void *userkey, void *offnotf);
short dpr_tx( void *dprkey, void *userkey, void *libctx, void *pkt, void *txnotf);
short dpr_info( void *dprkey, void *userkey, void **dprpb);

/* void	<rxnotf>( void *dprkey, void *userkey, void *pkt, unsigned short len,
 		  short ccode ); */
/* void  <offnotf>( void *dprkey, void *userkey, short ccode ); */
/* void	<txnotf>( void *dprkey, void *userkey, void *pkt, short ccode ); */
#endif /* __STDC__ */

#endif
