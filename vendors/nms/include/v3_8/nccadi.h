/*****************************************************************************
  NAME:  nccadi.h
  
  PURPOSE:

      This is a common include file for all CAS protocols for the NCC service.
****************************************************************************/

#ifndef NCCADI_INCLUDED
#define NCCADI_INCLUDED 

/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif

/* Meanings for ncc.x.adi_start.mediamask bits -----                        */
#define NCC_RESERVE_DTMF       0x0001 /* reserve dtmf detection             */
#define NCC_RESERVE_SILENCE    0x0002 /* reserve silence detector           */
#define NCC_RESERVE_CLEARDOWN  0x0004 /* reserve clear-down det.            */
#define NCC_AUTO_DTMF          0x0008 /* start DTMF detection               */
#define NCC_AUTO_ECHO          0x0010 /* start echo canceller               */
#define NCC_ALL_MEDIA (NCC_RESV_DTMF|NCC_RESV_SILENCE|\
                       NCC_RESV_CLEARDOWN|NCC_AUTO_DTMF|NCC_AUTO_ECHO)
#define NCC_ACCEPT_DTMF        0x0100 /* dtmf detection in accept           */

    
/* Meanings for ncc.x.adi_placecall.connectmask bits -----                  */
/* events that transition to connected:                                     */
#define NCC_CON_ON_SIGNAL         0x0001 /* out-of-band signal              */
#define NCC_CON_ON_VOICE_BEGIN    0x0002 /* on the begin of voice           */
#define NCC_CON_ON_VOICE_MEDIUM   0x0004 /* on cp voice medium              */
#define NCC_CON_ON_VOICE_LONG     0x0008 /* on cp voice long                */
#define NCC_CON_ON_VOICE_EXTENDED 0x0010 /* on cp voice extended            */
#define NCC_CON_ON_VOICE_END      0x0020 /* on cp voice end                 */
#define NCC_CON_ON_RING_QUIT      0x0080 /* on cp ringquit                  */
#define NCC_CON_ON_CED            0x0100 /* on cp CED detect                */
#define NCC_CON_ON_DIALTONE       0x0200 /* on cp dialtone                  */
#define NCC_CON_ON_SIT            0x0400 /* on cp SIT detect                */
#define NCC_CON_ON_RING_BEGIN     0x0800 /* on cp ring begin                */
#define NCC_CON_ON_PROCEEDING     0x8000 /* don't run cp                    */

#define NCC_CON_ON_ANSWER\
        (NCC_CON_ON_SIGNAL|NCC_CON_ON_VOICE_BEGIN|NCC_CON_ON_CED)

/* Meanings for ncc.x.adi_placecall.disconnectmask bits -----               */
/* events that transition to disconnected:                                  */
#define NCC_DIS_ON_VOICE_BEGIN    0x0002 /* on the begin of voice           */
#define NCC_DIS_ON_VOICE_MEDIUM   0x0004 /* on cp voice medium              */
#define NCC_DIS_ON_VOICE_LONG     0x0008 /* on cp voice long                */
#define NCC_DIS_ON_VOICE_EXTENDED 0x0010 /* on cp voice extended            */
#define NCC_DIS_ON_VOICE_END      0x0020 /* on cp voice ended               */
#define NCC_DIS_ON_TIMEOUT        0x0040 /* on cp timeout                   */
#define NCC_DIS_ON_RING_QUIT      0x0080 /* on cp ringquit                  */
#define NCC_DIS_ON_CED            0x0100 /* on callprog CED detect          */
#define NCC_DIS_ON_RING_BEGIN     0x0800 /* on cp ring begin                */
                                         /* and default disconnect on       */
                                         /* dialtone and SIT, and always    */
                                         /* disconnect on reorder, busy, no */
                                         /* answer and no wink.             */

/* Meanings for ncc.x.adi_placecall.callprog.precmask bits -----            */
/* Precise tone mask.                                                       */
#define NCC_CPMSK_PRECISE_CED  0x0001
#define NCC_CPMSK_PRECISE_SIT  0x0002
#define NCC_CPMSK_PRECISE_BUSY 0x0004

/* Meanings for ncc.x.adi_placecall.callprog.stopmask bits -----            */
/* mask to auto-stop adiCallProgress:                                       */
#define NCC_CPSTOP_ON_RINGTONE     0x01
#define NCC_CPSTOP_ON_RINGQUIT     0x02
#define NCC_CPSTOP_ON_VOICE_BEGIN  0x04
#define NCC_CPSTOP_ON_VOICE_MEDIUM 0x08
#define NCC_CPSTOP_ON_VOICE_LONG   0x10
#define NCC_CPSTOP_ON_VOICE_EXTD   0x20
#define NCC_CPSTOP_ON_VOICE_END    0x40
/* additional stopmask bit to modify behavior */
#define NCC_CP_REPORT_ALL_RINGS  0x4000 /* send ADIEVN_CP_RINGTONE          */
                                        /* for each ring cycle              */

/* Meanings for ncc.x.adi_start.echocancel.mode -----                       */
/* Values for 'mode' parameter                                              */
#define NCC_ECHOCANCEL_DEFAULT 1  /*   Choose best length and adapt time    */
                                  /*    based on current board type.        */
#define NCC_ECHOCANCEL_CUSTOM  2  /*   Use specified len and adapttime.     */
                                  /*    defaults are 0, no echo cancel      */
#ifdef __cplusplus
}
#endif


#endif /* NCCADI_INCLUDED */

