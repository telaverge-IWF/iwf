/******************************************************************************
*
*       tdmuser.h - TDM/MVIP LEVEL 1 DRIVER ACCESS DEFINITIONS
*
*       DD-MMM-YY    Who                   Description                   Tag
*       =========  =======  ==========================================  ======
*       13-Oct-95  adam     Created                                     <D1.79>
*
*-----------------------------------------------------------------------------
* REV   DATE           WHO       $Log: tdmuser.h,v $
* REV   DATE           WHO       Revision 9.1  2005/03/23 12:55:46  cvsadmin
* REV   DATE           WHO       Begin PR6.5
* REV   DATE           WHO
* REV   DATE           WHO       Revision 8.2  2005/03/21 13:55:06  cvsadmin
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
* REV   DATE           WHO       Revision 3.1  2000/08/16 00:10:48  mmiers
* REV   DATE           WHO
* REV   DATE           WHO       Begin round 4.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 2.0  1999/12/03 23:33:11  mmiers
* REV   DATE           WHO
* REV   DATE           WHO       Begin third iteration.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1  1998/01/15 01:39:03  rsonak
* REV   DATE           WHO       *** empty log message ***
* REV   DATE           WHO $NoKeywords: $
* 
* 1     3/10/97 3:24p Adam
* Release 6.5 Beta to NMS Natick
* 
* 2     9/23/96 9:04a Adam
* Fix spelling of debounce
 *
 * 1     9/12/96 5:14p Adam
 * Initial Recovery Checkin
*
* 6     7/24/96 11:54a Adam
* Modify tdmuser structures, and constants for new E1 parameters
*
* 5     5/10/96 10:17a Adam
* Modify T1E1STATUS block and include new t1e1_reg_stats functionallity.
*
* 4     4/08/96 2:13p Jeffd
* Remove constants needed by applications & APIs & move to .h files
* accessible to APIs (mviptype.h & t1e1type.h).
*
* 3     3/06/96 10:18a Adam
* Initial Addition of T1 Functionality for TX2000.
*
* 2     2/15/96 8:52a Jeffr
* Added Source Safe log header
*-----------------------------------------------------------------------------
******************************************************************************/
#ifndef _TDMUSER_H_
#define _TDMUSER_H_

/*******************************************************************************
* T1E1 Carrier Status Response
*******************************************************************************/
typedef struct _t1e1status {
   unsigned char  yellowalarm;
   unsigned char  bluealarm;
   unsigned char  syncstate;
   unsigned char  framemode;
   unsigned char  encoding;
   unsigned char  linebldout;
   unsigned char  debounce;
   unsigned char  loopmaster;
   unsigned char  robbedbit;
   unsigned char  loopback;
   unsigned short currsecs;
   unsigned short escount;
   unsigned short lescount;
   unsigned short bescount;
   unsigned short sescount;
   unsigned short uascount;
   unsigned short ccscount;
   unsigned short lofcount;
   unsigned long  pcvcnt;
   unsigned long  lcvcnt;
   unsigned long  slipcnt;
   unsigned long  ebitcnt;
   unsigned char  ts16aisalarm;
   unsigned char  ts16failalarm;
   unsigned char  distmfalarm;
   unsigned char  align;
} T1E1STATUS;


/*******************************************************************************
* T1 Status Registration and notification bits
*******************************************************************************/
#define  T1_LOOP_UP_DETECT    0x80000000  /* Loop Up Code Detected */
#define  T1_LOOP_DOWN_DETECT  0x40000000  /* Loop Down Code Detected */
#define  T1_LOSS_OF_TXCLK     0x20000000  /* Loss of Transmit Clock */
#define  T1_RX_SLIP           0x10000000  /* Receive Elastic Store Slip */
#define  T1_RXBLUE_ALARM      0x08000000  /* Receive Blue Alarm */
#define  T1_RXYELLOW_ALARM    0x04000000  /* Receive Yellow Alarm */
#define  T1_RX_CARRIERLOSS    0x02000000  /* Receive Carrier Loss */
#define  T1_RX_SYNCLOSS       0x01000000  /* Receive Loss of Sync */

#define  T1_FRAME_ALIGN       0x00008000  /* Change of Frame Alignment */
#define  T1_8ZERO_DETECT      0x00004000  /* Eight Zero Detect */
#define  T1_16ZERO_DETECT     0x00002000  /* Sixteen Zero Detect */
#define  T1_RXESTORE_FULL     0x00001000  /* Receive Elastic Store Full */
#define  T1_RXESTORE_EMPTY    0x00000800  /* Receive Elastic Store Empty */
#define  T1_SEVERLY_ERROR_F   0x00000400  /* Severely Errored Framing Event */
#define  T1_B8ZS_CODE_WORD    0x00000200  /* B8ZS Code Word Detcect */
#define  T1_FRAME_BIT_ERR     0x00000100  /* Frame Bit Error */

#define  T1_TXESTORE_FULL     0x00000020  /* Transmit Elastic Store Full */
#define  T1_TXESTORE_EMPTY    0x00000010  /* Transmit Elastci Store Empty */
#define  T1_TXSLIP            0x00000008  /* Transmit Elastic Store Slip */
#define  T1_JITTER_TRIP       0x00000004  /* Jitter Attenuator Limit Trip */
#define  T1_RXPDV             0x00000002  /* Receive Pulse Density Violation */
#define  T1_TXPDV             0x00000001  /* Transmit Pulse Density Violation */

/*******************************************************************************
* E1 Status Registration and notification bits
*******************************************************************************/
#define  E1_RX_SIGNAL_ONES    0x80000000  /* Rx Signaling all Ones Detected */
#define  E1_RX_DISTANT_MFALM  0x40000000  /* Rx Distant MF Alarm Detected */
#define  E1_RX_SIGNAL_ZEROS   0x20000000  /* Rx Signaling all Zeros Detected */
#define  E1_SLIP              0x10000000  /* Elastic Store Slip */
#define  E1_RX_UNFRAMED_ONES  0x08000000  /* Rx Unframed all Ones Detected */
#define  E1_RX_REMOTE_ALM     0x04000000  /* Rx Remote Alarm */
#define  E1_RX_CARRIERLOSS    0x02000000  /* Receive Carrier Loss */
#define  E1_RX_SYNCLOSS       0x01000000  /* Receive Loss of Sync */

#define  E1_JITTER_TRIP       0x00002000  /* Jitter Limit Trip */
#define  E1_ESTORE_FULL       0x00001000  /* Elastic Store Full */
#define  E1_ESTORE_EMPTY      0x00000800  /* Elastic Store Empty */
#define  E1_FAS_RESYNC        0x00000200  /* FAS Resync Criteria Met */
#define  E1_CAS_RESYNC        0x00000100  /* CAS Resync Criteria Met */

/*******************************************************************************
* T1/E1 Channel masks for channel status and Robbed bit registration
* and notification routines
*******************************************************************************/
#define T1_CHAN_1    0x00000001     /* Channel 1 */
#define T1_CHAN_2    0x00000002     /* Channel 2 */
#define T1_CHAN_3    0x00000004     /* Channel 3 */
#define T1_CHAN_4    0x00000008     /* Channel 4 */
#define T1_CHAN_5    0x00000010     /* Channel 5 */
#define T1_CHAN_6    0x00000020     /* Channel 6 */
#define T1_CHAN_7    0x00000040     /* Channel 7 */
#define T1_CHAN_8    0x00000080     /* Channel 8 */
#define T1_CHAN_9    0x00000100     /* Channel 9 */
#define T1_CHAN_10   0x00000200     /* Channel 10 */
#define T1_CHAN_11   0x00000400     /* Channel 11 */
#define T1_CHAN_12   0x00000800     /* Channel 12 */
#define T1_CHAN_13   0x00001000     /* Channel 13 */
#define T1_CHAN_14   0x00002000     /* Channel 14 */
#define T1_CHAN_15   0x00004000     /* Channel 15 */
#define T1_CHAN_16   0x00008000     /* Channel 16 */
#define T1_CHAN_17   0x00010000     /* Channel 17 */
#define T1_CHAN_18   0x00020000     /* Channel 18 */
#define T1_CHAN_19   0x00040000     /* Channel 19 */
#define T1_CHAN_20   0x00080000     /* Channel 20 */
#define T1_CHAN_21   0x00100000     /* Channel 21 */
#define T1_CHAN_22   0x00200000     /* Channel 22 */
#define T1_CHAN_23   0x00400000     /* Channel 23 */
#define T1_CHAN_24   0x00800000     /* Channel 24 */

#define T1_RBIT_A    0x01         /* Robbed bit A */
#define T1_RBIT_B    0x02         /* Robbed bit B */
#define T1_RBIT_C    0x04         /* Robbed bit C */
#define T1_RBIT_D    0x08         /* Robbed bit D */

/* ===== FUNCTION PROTOTYPES ===== */

short mvip_query_switch ( unsigned short *domain,
                          unsigned short *routing,
                          unsigned short *blocking,
                          unsigned short *networks,
                          unsigned short *channels);

short mvip_config_clock ( unsigned short clockmode,
                          unsigned short sec8kmode,
                          unsigned short network );

short mvip_control_switch ( unsigned short operation );

short mvip_switch_status ( unsigned short *clockmode,
                           unsigned short *sec8kmode,
                           unsigned short *network,
                           unsigned short *swstatus );

short mvip_channel_connect ( unsigned short outstream,
                             unsigned short outslot,
                             unsigned short chanmode,
                             unsigned short srcstream,
                             unsigned short srcslot,
                             unsigned short pattern,
                             unsigned short duplex );

short mvip_channel_status ( unsigned short outstream,
                            unsigned short outslot,
                            unsigned short *chanmode,
                            unsigned short *srcstream,
                            unsigned short *srcslot,
                            unsigned short *pattern,
                            unsigned short *direction,
                            unsigned short *indirection,
                            unsigned char  *inputsample );


short t1e1_config_carrier ( unsigned char network,
                            unsigned char framemode,
                            unsigned char encoding,
                            unsigned char linebldout,
                            unsigned char robbedbit,
                            unsigned char loopmaster );

short t1e1_carrier_status ( unsigned char network,
                            T1E1STATUS *t1e1status,
                            unsigned char clrcount);

short t1e1_control_carrier ( unsigned char network,
                             unsigned char loopback,
                             unsigned char yelalarm,
                             unsigned char bluealarm,
                             unsigned char ts16aisalm,
                             unsigned char distmfalm );

short t1e1_condition_chan ( unsigned char network,
                            unsigned char channel,
                            unsigned char pattern,
                            unsigned char control );

short t1e1_config_chan ( unsigned char network,
                         unsigned char channel,
                         unsigned char transparent );

short  t1e1_channel_status ( unsigned char network,
                             unsigned long *transparent,
                             unsigned long *rxsignal,
                             unsigned long *txsignal );

short t1e1_reg_robbit ( unsigned char network,
                        unsigned long chanmask,
                        unsigned char abcdmask,
                        void *userkey,
                        void *rbit_notif);

/* Robbed bit Change Notification Prototype (user-defined function):
void <rbit_notif>( void *userkey,
                   unsigned long changemask,
                   unsigned long currabits,
                   unsigned long currbbits,
                   unsigned long currcbits,
                   unsigned long currdbits ); */

short t1e1_dereg_robbit ( unsigned char network,
                          void *userkey);

short t1e1_reg_status ( unsigned char network,
                        unsigned long notifmask,
                        void *userkey,
                        void *status_notif );

/* Status Change Notification Prototype (user-defined function):
void <status_notif>( void *userkey,
                     unsigned long changemask,
                     unsigned long currvalue ); */


short t1e1_dereg_status ( unsigned char network,
                          void *userkey);

short t1e1_reg_stats ( unsigned char network,
                       void *userkey,
                       T1E1STATUS *statbuff,
                       void *stats_notif );

/* Stats Change Notification Prototype (user-defined function):
void <stats_notif>( void *userkey,
                    T1E1STATUS *statbuff ); */

short t1e1_dereg_stats ( unsigned char network,
                         void *userkey);

#endif

