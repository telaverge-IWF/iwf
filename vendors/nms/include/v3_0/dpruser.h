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
* REV   DATE           WHO       Revision 9.1  2005/03/23 12:55:50  cvsadmin
* REV   DATE           WHO       Begin PR6.5
* REV   DATE           WHO
* REV   DATE           WHO       Revision 8.2  2005/03/21 13:55:14  cvsadmin
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
* REV   DATE           WHO       Revision 5.1  2001/08/16 20:46:39  mmiers
* REV   DATE           WHO       Start PR6.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 4.1  2001/05/04 16:22:07  mmiers
* REV   DATE           WHO       Start PR5.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 3.1  2000/08/16 00:11:22  mmiers
* REV   DATE           WHO
* REV   DATE           WHO       Begin round 4.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.4  2000/06/09 22:02:25  randresol
* REV   DATE           WHO       Adding file to current tree
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1.2.1  2000/05/16 21:17:18  randresol
* REV   DATE           WHO       Add include files for SS7 Version 3 software for TX3220
* REV   DATE           WHO $NoKeywords: $
* 
* 11    5/26/99 10:07a Jrego
* Migrating to new Core Group source control system
* 
* 10    3/30/98 9:05a Maf
* Put in changes for Solaris port (mostly ifdefed with __sun)
* 
* 9     3/17/98 10:42a Jeffr
* Dual Port Ram level 1.5 now over Virtual Ports
*
* 8     10/17/97 10:23a Adam
* Merge from DEVTXN back into TXN
*
* 8     6/26/97 3:12p Adam
* H323 Development
*
* 7     6/26/97 2:52p Jeffr
* Moved common structure definitions to dpriface.h
*
* 6     6/26/97 1:19p Jeffr
* Changed message header structures to match TXCPI.H definitions
*
* 5     4/24/97 3:45p Dan
* TCAP and TUP
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

#include <dpriface.h>

/* ----- Dual Port RAM port types (high byte of channel on dpr_crea) */
#define DPRT_NORM       0   /* normal channel type (true DPR channel) */
#define DPRT_PSEUDOHOST 1   /* simulating host side of DPRAM for given channel */

#ifdef __sun
#pragma pack(1)
#endif	/* __sun */
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

#ifdef __sun
#pragma pack()
#endif	/* __sun */

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
short dpr_info( void *dprkey, void *userkey, void *dprpb);

/* void	<rxnotf>( void *dprkey, void *userkey, void *pkt, unsigned short len,
 		  short ccode ); */
/* void  <offnotf>( void *dprkey, void *userkey, short ccode ); */
/* void	<txnotf>( void *dprkey, void *userkey, void *pkt, short ccode ); */
#endif /* __STDC__ */

#endif
