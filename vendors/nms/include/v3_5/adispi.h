/*****************************************************************************
*                                  ADIDEF.H
*
*  This is the include file for the AG Driver Interface (ADI) API.
*
*  This file is organized as:
*
*    . INCLUDES
*    . COMMON DEFINES AND STRUCTURES
*    . PLAY AND RECORD
*    . DTMF COLLECTION
*    . TONE AND DTMF GENERATION
*    . ENERGY AND TONE DETECTION
*    . CALL CONTROL
*    . NULL CALL-CONTROL ("NOCC"; LOW-LEVEL)
*    . GLOBAL PARAMETER MANAGEMENT
*    . MISCELLANEOUS FUNCTIONS
*    . MISCELLANEOUS STRUCTURES
*    . SUPERVISORY FUNCTIONS
*    . TCP PARAMETERS
*    . ADI EVENTS
*    . ADI ERRORS
*
*  Copyright (c)1994-98 Natural MicroSystems Corporation. All rights reserved.
*****************************************************************************/

#ifndef ADIDEF_INCLUDED
#define ADIDEF_INCLUDED 1

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NMSTYPES_INCLUDED
#include "nmstypes.h"
#endif

#ifndef CTAERR_INCLUDED
#include "ctaerr.h"
#endif

#ifndef CTADEF_INCLUDED
#include "ctadef.h"
#endif

#define ADI_SVCID  0x0001
#define ADI_BASEID 0x00010000L  /* base number for defining other keys */

#define ADI_SVCCOMPATLEVEL   1
#define ADIAPI_COMPATLEVEL   ADI_SVCCOMPATLEVEL

/*====== COMMON DEFINES AND STRUCTURES =====================================*/

/*------ 'Special Board Values' --------------------------------------------*/
#define ADI_AG_SUPERVISOR   ((DWORD)-1)
#define ADI_AG_DRIVER_ONLY  ((DWORD)-2)

/*------ 'Port Modes' ------------------------------------------------------*/
#define ADI_VOICE_INPUT     0x01
#define ADI_VOICE_OUTPUT    0x02
#define ADI_SIGNAL_INPUT    0x04
#define ADI_SIGNAL_OUTPUT   0x08
#define ADI_VOICE_DUPLEX    (ADI_VOICE_INPUT  + ADI_VOICE_OUTPUT)
#define ADI_SIGNAL_DUPLEX   (ADI_SIGNAL_INPUT + ADI_SIGNAL_OUTPUT)
#define ADI_FULL_DUPLEX     (ADI_VOICE_DUPLEX + ADI_SIGNAL_DUPLEX)


/*------ 'Signalling Bit' Mask Bits ----------------------------------------*/
#define ADI_A_BIT           0x08
#define ADI_B_BIT           0x04
#define ADI_C_BIT           0x02
#define ADI_D_BIT           0x01


/*------ 'reason' field for ADIEVN_xxx_DONE events : -----------------------*/

/* SPECIFIC REASONS ONLY - see ctaerr.h for generic reasons                 */
#define ADI_REASON_BAD_STOP_BIT    0x00011001 /* Bad stop bit in FSK recv     */
#define ADI_REASON_DROP_IN_DATA    0x00011002 /* Drop in data during FSK recv */
#define ADI_REASON_BAD_PARITY      0x00011003 /* Bad parity bit in FSK recv   */
#define ADI_REASON_BAD_CRC         0x00011004 /* Bad crc in FSK recv          */
#define ADI_REASON_BAD_CHECKSUM    0x00011005 /* Bad checksum in FSK recv     */


/*------- DTMF digits for bit masks ----------------------------------------*/
#define ADI_DIGIT_0     0x0001
#define ADI_DIGIT_1     0x0002
#define ADI_DIGIT_2     0x0004
#define ADI_DIGIT_3     0x0008
#define ADI_DIGIT_4     0x0010
#define ADI_DIGIT_5     0x0020
#define ADI_DIGIT_6     0x0040
#define ADI_DIGIT_7     0x0080
#define ADI_DIGIT_8     0x0100
#define ADI_DIGIT_9     0x0200
#define ADI_DIGIT_STAR  0x0400
#define ADI_DIGIT_POUND 0x0800
#define ADI_DIGIT_A     0x1000
#define ADI_DIGIT_B     0x2000
#define ADI_DIGIT_C     0x4000
#define ADI_DIGIT_D     0x8000
#define ADI_DIGIT_ANY   0xFFFF
#define ADI_DIGIT_0_9   0x03FF
#define ADI_DIGIT_A_D   0xF000


/*====== PLAY AND RECORD ===================================================*/

/*------ ADI_PLAY_/RECORD_PARMS 'DTMFabort' MASK: --------------------------*/
/* Both play and record include a feature to abort when a DTMF is detected.
 * The 'DTMFabort' parameter in their respective PARM structures is a mask
 * which allows you to control which DTMFs abort play or record.
 *  bit: FEDCBA9876543210 (lsb)
 *  TT:  #*DCBA9876543210
 *
 *  To abort only on DTMF '7' the value would be:
 *  bit: FEDCBA9876543210 (lsb)
 *       0000000010000000        = 0x00800
 *
 *  To abort on all DTMFs (the default), 0xffff is used.
 */

/*------ PLAY and RECORD functions 'encoding' argument: --------------------*/
/*
 * The encoding argument is used by ADI to run the proper DSP function on
 * the board.  The following encoding values require the '.dsp' file noted.
 * 'xxxxx'.dsp files output Mu-law to the line, while 'xxxxx_A.dsp' files
 * output A-law to the line.  Therefore the encoding only describes the
 * type of data received from record or provided for play.
 */

/* Dsp file VOICE(_A).DSP or VOICE.M54 */
#define ADI_ENCODE_NMS_16     1 /* NMS ADPCM 16kbs   (20ms frames  42 bytes) */
#define ADI_ENCODE_NMS_24     2 /* NMS ADPCM 24kbs   (20ms frames  62 bytes) */
#define ADI_ENCODE_NMS_32     3 /* NMS ADPCM 32kbs   (20ms frames  82 bytes) */
#define ADI_ENCODE_NMS_64     4 /* framed PCM 64kbs  (20ms frames 162 bytes) */

/* No DSP */
#define ADI_ENCODE_RAW        7 /* line code 64kbs   (10ms blocks  80 bytes) */

/* Dsp file RVOICE(_A).DSP or RVOICE.M54 */
#define ADI_ENCODE_MULAW     10 /* mu-law 64kbs      (10ms blocks  80 bytes) */
#define ADI_ENCODE_ALAW      11 /* A-law  64kbs      (10ms blocks  80 bytes) */
#define ADI_ENCODE_PCM8M16   13 /* PCM 8k mono 16 bit (10ms blks, 160 bytes) */

/* Dsp files OKIPLY(_A).DSP and OKIREC(_A).DSP), or OKI.M54 */
#define ADI_ENCODE_OKI_24    14 /* OKI ADPCM 24kbs   (10ms blocks  30 bytes) */
#define ADI_ENCODE_OKI_32    15 /* OKI ADPCM 32kbs   (10ms blocks  40 bytes) */

/* Dsp files WAVPLY(_A).DSP and WAVREC(_A).DSP), or WAVE.M54 */
#define ADI_ENCODE_PCM11M8   16 /* PCM 11khz  8 bit  (10ms blocks 110 bytes) */
#define ADI_ENCODE_PCM11M16  17 /* PCM 11khz 16 bit  (10ms blocks 220 bytes) */

/* Dsp files G726P(_A).DSP and G726R(_A).DSP), or G726.M54 */
#define ADI_ENCODE_G726      20 /* G726 ADPCM 32kbs  ( 2ms blocks   8 bytes) */

/* QX2000 G.726 - note that block size on the QX2000 is runtime dependent) */
#define ADI_ENCODE_G726_16   18 /* G726 ADPCM 16kbs  (  2 byte /ms         ) */
#define ADI_ENCODE_G726_24   19 /* G726 ADPCM 24kbs  (  3 bytes/ms         ) */
#define ADI_ENCODE_G726_32   20 /* G726 ADPCM 32kbs  (  4 bytes/ms         ) */
#define ADI_ENCODE_G726_40   21 /* G726 ADPCM 40kbs  (  5 bytes/ms         ) */

/* Dsp files IMAPLY(_A).DSP and IMAREC(_A).DSP), or IMA.M54 */
#define ADI_ENCODE_IMA_24    22 /* IMA ADPCM 24kbs   (10ms blocks  30 bytes) */
#define ADI_ENCODE_IMA_32    23 /* IMA ADPCM 32kbs   (10ms blocks  40 bytes) */

#define ADI_ENCODE_VOX_32    25 /* Special ADPCM 32kbs for QX boards (4 bytes/ms) */


DWORD NMSAPI adiGetEncodingInfo(  /* Returns information about a voice code */
    CTAHD          ctahd,         /*   context handle                       */
    unsigned       encoding,      /*   ADI_ENCODE_xxx (see above)           */
    unsigned      *framesize,     /*   Returned frame size                  */
    unsigned      *datarate,      /*   Returned avg bytes/sec               */
    unsigned      *maxbufsize);   /*   Returned Maximum buffer size         */

/*---------------- PLAY functions, parameters and structures  ---------*/

#define ADI_PLAY_LAST_BUFFER  1

typedef struct
{                                 /* parameters related to adiStartPlaying: */
    DWORD size ;                  /*   size of this structure               */
    DWORD DTMFabort;              /*   abort on DTMF; see descripton above  */
    INT32 gain;                   /*   playing gain in dB                   */
    DWORD speed;                  /*   initial speed in percent             */
    DWORD maxspeed;               /*   maximum play speed in percent        */
} ADI_PLAY_PARMS;

/*
 *  ADI_PLAY_ACCESS - pointer to function for application play callback.
 *       Used for adiStartPlaying().
 */

typedef int (NMSSTDCALLPTR ADI_PLAY_ACCESS)
    (
    void           *userarg,      /* user-defined access argument           */
    void           *buffer,       /* ADI supplied buffer                    */
    unsigned        bufsize,      /* size of ADI buffer                     */
    unsigned       *datasize      /* amount of user data put in *buffer     */
    );

DWORD NMSAPI adiStartPlaying(     /* Plays calling back for buffers         */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         encoding,      /*   encoding types (see above)           */
  ADI_PLAY_ACCESS  access,        /*   user callback access routine.        */
  void            *userarg,       /*   passed to access() "as is"           */
  ADI_PLAY_PARMS  *parms );       /*   pointers to play parameters          */

DWORD NMSAPI adiPlayFromMemory(   /* Plays directly from memory             */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         encoding,      /*   encoding types (see above)           */
  void            *buffer,        /*   pointer to buffer area with data     */
  unsigned         bufsiz,        /*   size of the buffer in bytes          */
  ADI_PLAY_PARMS  *parms );       /*   play parameters                      */

DWORD NMSAPI adiPlayAsync(        /* Application submits buffers            */
  CTAHD            ctahd,         /* context handle                         */
  unsigned         encoding,      /* encoding types                         */
  void            *buffer,        /* pointer to buffer area with data       */
  unsigned         bufsiz,        /* size of the buffer in bytes            */
  unsigned         flags,         /* ADI_PLAY_LAST_BUFFER                   */
  ADI_PLAY_PARMS  *parms );       /* play parameters                        */

#define ADI_PLAY_STARTED     1    /* bit in ADIEVN_PLAY_BUFFER_REQ value    */
                                  /*  that indicates first request          */
#define ADI_PLAY_UNDERRUN    2    /* bit in ADIEVN_PLAY_BUFFER_REQ value    */
                                  /*  that indicates an underrun occurred   */

DWORD NMSAPI adiSubmitPlayBuffer( /* Application continues playing          */
  CTAHD            ctahd,         /* context handle                         */
  void            *buffer,        /* pointer to buffer area with data       */
  unsigned         bufsiz,        /* size of the buffer in bytes            */
  unsigned         flags );       /* ADI_PLAY_LAST_BUFFER                   */

DWORD NMSAPI adiModifyPlayGain (
    CTAHD          ctahd,
    int            volume );      /* New amplitude (dbm)                    */

DWORD NMSAPI adiModifyPlaySpeed (
    CTAHD          ctahd,
    unsigned       speed  );      /* New speed (percent)                    */

typedef struct
{
    DWORD size;                   /* returned size (GetPlayStatus())        */
    DWORD reason;                 /* reason last play ended                 */
    DWORD buffercount;            /* counter of buffers submitted           */
    DWORD framecount;             /* number of frames submitted             */
    DWORD totalbytes;             /* total bytes submitted                  */
    void *buffer;                 /* last buffer pointer SUBMITTED          */
    DWORD bytecount;              /* size of last buffer submitted          */
    DWORD bytesplayed;            /* total bytes actually played            */
    DWORD timestarted;            /* actual time started (ms units)         */
    DWORD underrun;               /* counts out-of-frame events             */
} ADI_PLAY_STATUS;

DWORD NMSAPI adiGetPlayStatus(    /* Returns status info about playing      */
  CTAHD            ctahd,         /*   context handle                       */
  ADI_PLAY_STATUS *status,        /*   passed ptr to returned status info   */
  unsigned         size );        /*   passed byte size of above            */

DWORD NMSAPI adiStopPlaying(      /* Terminates playing                     */
  CTAHD            ctahd );       /*   context handle                       */


/*--------------  RECORD API functions, parameters and structures  ---------*/

typedef struct
{
    DWORD size ;                  /*   size of this structure               */
    DWORD DTMFabort;              /* abort on DTMF; see descripton above    */
    INT32 gain;                   /* recording gain in dB                   */
                                  /*-[SLC parms (used if silence det)]------*/
    DWORD novoicetime;            /*   length of initial silence to stop    */
                                  /*     recording (ms); use 0 to deactivate*/
                                  /*     initial silence detection.         */
    DWORD silencetime;            /*   length of silence to stop recording  */
                                  /*     after voice has been detected (ms);*/
                                  /*     use 0 to deactivate.               */
    INT32 silenceampl;            /*   qualif level for silence (dBm)       */
    DWORD silencedeglitch;        /*   deglitch while qualifying silence(ms)*/
                                  /*-[Beep for record]----------------------*/
    DWORD beepfreq;               /*   beep frequency (Hz)                  */
    INT32 beepampl;               /*   beep amplitude (dBm)                 */
    DWORD beeptime;               /*   beep time (ms) 0=no beep             */
                                  /*--[AGC parms]---------------------------*/
    DWORD AGCenable;              /*   enable AGC; use 1 to activate        */
    INT32 AGCtargetampl;          /*   target AGC level (dBm)               */
    INT32 AGCsilenceampl;         /*   silence level (dBm)                  */
    DWORD AGCattacktime;          /*   attack time (ms)                     */
    DWORD AGCdecaytime;           /*   decay time (ms)                      */
} ADI_RECORD_PARMS;

/*
 *  ADI_RECORD_ACCESS - pointer to function for application record callback,
 *      for adiStartRecording() only.
 */

typedef int (NMSSTDCALLPTR ADI_RECORD_ACCESS)
    (
    void           *userarg,      /* user-defined access argument           */
    void           *buffer,       /* ADI supplied buffer                    */
    unsigned        bufsize       /* size of ADI buffer                     */
    );

#define ADI_RECORD_FOREVER   0

DWORD NMSAPI adiStartRecording(   /* Records calling back for buffers       */
  CTAHD             ctahd,        /*   context handle                       */
  unsigned          encoding,     /*   encoding types (see above)           */
  unsigned          maxtime,      /*   max record time in msec (0=no max)   */
  ADI_RECORD_ACCESS access,       /*   access routine                       */
  void             *userarg,      /*   passed to access() "as is"           */
  ADI_RECORD_PARMS *parms );      /*   pointers to play parameters          */

DWORD NMSAPI adiRecordToMemory(   /* Records directly into a memory buffer  */
  CTAHD             ctahd,        /*   context handle                       */
  unsigned          encoding,     /*   encoding types (see above)           */
  void             *buffer,       /*   pointer to buffer area with data     */
  unsigned          bufsiz,       /*   size of the buffer in bytes          */
  ADI_RECORD_PARMS *parms );      /*   record parameters                    */

DWORD NMSAPI adiRecordAsync(      /* Records directly into a memory buffer  */
  CTAHD             ctahd,        /*   context handle                       */
  unsigned          encoding,     /*   encoding types (see above)           */
  unsigned          maxmsec,      /* max recoding time in msec; 0=unlimited */
  void             *buffer1,      /*   pointer to 1st target buffer         */
  unsigned          bufsiz,       /*   size of the buffer in bytes          */
  ADI_RECORD_PARMS *parms );      /*   record parameters                    */

#define ADI_RECORD_BUFFER_REQ  1  /* bit in ADIEVN_RECORD_BUFFER_FULL value */
                                  /*  that indicates another buffer needed  */
#define ADI_RECORD_UNDERRUN    2  /* bit in ADIEVN_RECORD_BUFFER_FULL value */
                                  /*  that indicates an underrun occurred   */


DWORD NMSAPI adiSubmitRecordBuffer( /* Records directly into a memory buffer*/
  CTAHD            ctahd,         /*   context handle                       */
  void            *buffer,        /*   pointer to buffer area with data     */
  unsigned         bufsiz) ;      /*   size of the buffer in bytes          */

typedef struct
{                                 /* parameters related to RECORD functions:*/
    DWORD size ;                  /* returned size (GetRecordStatus())      */
    DWORD reason;                 /*   reason last record ended             */
    DWORD buffercount;            /*   counter of buffers submitted         */
    DWORD framecount;             /*   number of frames submitted           */
    DWORD totalbytes;             /*   total bytes submitted                */
    void *buffer;                 /*   last buffer pointer SUBMITTED.       */
    DWORD bytecount;              /*   number of bytes into this buffer     */
    DWORD bytesrecorded;          /*   total bytes actually recorded.       */
    DWORD timestarted;            /*   actual time started (ms units)       */
    DWORD underrun ;              /*   counts underrun events           */
} ADI_RECORD_STATUS;

DWORD NMSAPI adiGetRecordStatus(  /* Returns status info about recording    */
  CTAHD             ctahd,        /*   context handle                       */
  ADI_RECORD_STATUS *status,      /*   passed ptr to returned status info   */
  unsigned          size );       /*   passed byte size of above            */

DWORD NMSAPI adiStopRecording(    /* Terminates recording                   */
  CTAHD            ctahd );       /*   context handle                       */


/*====== DTMF COLLECTION ===================================================*/

DWORD NMSAPI adiGetDigit(         /* Retrieves a digit from the digit queue */
  CTAHD            ctahd,         /*   context handle                       */
  char            *digit );       /*   pointer to returned character        */

DWORD NMSAPI adiPeekDigit(        /* Retrieves first digit from the digit   */
                                  /* queue without removing it.             */
  CTAHD            ctahd,         /*   context handle                       */
  char            *digit );       /*   pointer to returned character        */

DWORD NMSAPI adiFlushDigitQueue(  /* Clears (flushes) the digit-queue       */
  CTAHD            ctahd );       /*   context handle                       */

typedef struct
{
    DWORD size ;                  /*   size of this structure               */
    DWORD firsttimeout;           /*   timeout waiting for the first digit; */
                                  /*     use 0 to wait forever.             */
    DWORD intertimeout;           /*   timeout waiting for the next digit;  */
                                  /*     use 0 to wait forever.             */
    DWORD waitendtone ;           /*   if non-zero, collection does not end */
                                  /*     until the end of the final dtmf    */
    DWORD validDTMFs ;            /*   mask of acceptable DTMFs; use 0 or   */
                                  /*     ADI_DIGIT_ANY to accept all.       */
    DWORD terminators;            /*   mask of terminating DTMFs; use 0     */
                                  /*     to indicate no terminators.        */
} ADI_COLLECT_PARMS;

DWORD NMSAPI adiCollectDigits(    /* Collects digits from the digit-queue   */
  CTAHD            ctahd,         /*   context handle                       */
  char            *buffer,        /*   user supplied buffer of digits       */
  unsigned         howmany,       /*   how many digits to collect           */
  ADI_COLLECT_PARMS *parms );     /*   parameters used for digits collection*/

DWORD NMSAPI adiStopCollection(   /* Terminates collection of digits        */
  CTAHD            ctahd );       /*   context handle                       */

/*====== TONE AND DTMF GENERATION ==========================================*/

typedef struct
{                                 /* parameters for tone generation:        */
    DWORD size ;                  /*   size of this structure               */
    DWORD freq1;                  /*   first frequency (Hz)                 */
    INT32 ampl1;                  /*   level of first tone (dBm)            */
    DWORD freq2;                  /*   second frequency (Hz)                */
    INT32 ampl2;                  /*   level of second tone (dBm)           */
    DWORD ontime;                 /*   on duration of DTMF tone (ms)        */
    DWORD offtime;                /*   off duration of DTMF tone (ms)       */
    INT32 iterations;             /*   times to repeat above; -1 = forever  */
                                  /*    last timeoff is trimmed if repeat>1 */
} ADI_TONE_PARMS;

DWORD NMSAPI adiStartTones(       /* Starts playing single or dual tones    */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         tonecount,     /*   number of tones to be played.        */
  ADI_TONE_PARMS   tone[] );      /*   pointers to tone specifications      */

typedef struct
{                                 /* parameters for DTMF generation:        */
    DWORD size ;                  /*   size of this structure               */
    INT32 ampl1;                  /*   level of first tone (dBm)            */
    INT32 ampl2;                  /*   level of second tone (dBm)           */
    DWORD ontime;                 /*   on duration of DTMF tone (ms)        */
    DWORD offtime;                /*   off duration of DTMF tone (ms)       */
    DWORD shortpause;             /*   duration of ',' (ms)                 */
    DWORD longpause;              /*   duration of '.' (ms)                 */
} ADI_DTMF_PARMS;

DWORD NMSAPI adiStartDTMF(        /* Starts playing DTMF strings            */
  CTAHD            ctahd,         /*   context handle                       */
  char            *digits,        /*   string of digits to be played        */
  ADI_DTMF_PARMS  *parms );       /*   pointer to DTMF parameters           */

DWORD NMSAPI adiStopTones(        /* Stops playing tones, beeps and DTMFs   */
  CTAHD            ctahd );       /*   context handle                       */

/*====== MF DETECTION =======================================================*/

#define ADI_MF_US             0
#define ADI_MF_CCITT_FORWARD  1
#define ADI_MF_CCITT_BACKWARD 2

DWORD NMSAPI adiStartMFDetector(  /* Starts detecting specified MFs         */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         mftype );      /*   type of MF to detect (ADI_MF_xxx)    */

DWORD NMSAPI adiStopMFDetector(   /* Turn off MF detector                   */
  CTAHD            ctahd );       /*   context handle                       */

/*====== ENERGY AND TONE DETECTION =========================================*/

typedef struct
{                                 /* parameters for energy detection:       */
    DWORD size ;                  /*   size of this structure               */
    INT32 thresholdampl;          /*   silence level (dBm)                  */
    DWORD deglitch;               /*   ms deglitch during transitions       */
    DWORD autostop;               /*   on detection, 1=autostop 0=don't     */
} ADI_ENERGY_PARMS;

DWORD NMSAPI adiStartEnergyDetector(
                                  /* Starts running the energy detector     */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         energyqual,    /*   qualification time for energy        */
  unsigned         silencequal,   /*   qualification time for silence       */
  ADI_ENERGY_PARMS *parms );      /*   pointer to energy parameters         */

DWORD NMSAPI adiStopEnergyDetector(
                                  /* Stops energy detection                 */
  CTAHD            ctahd );       /*   context handle                       */

typedef struct
{                                 /* parameters for precise tone detection: */
    DWORD size ;                  /*   size of this structure               */
    INT32 qualampl;               /*   broadband qual level (in dBm)        */
    DWORD qualtime;               /*   qualification time (in ms)           */
    DWORD reflevel;               /*   qual thresh,output of filter (IDUs)  */
    DWORD reserved;               /*   reserved, must be 0                  */
} ADI_TONEDETECT_PARMS;

#define ADI_MAX_TONE_DETECTORS 3

DWORD NMSAPI adiStartToneDetector(
                                  /* Starts running a tone detector         */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         toneid,        /*   id of tone to start detecting  (1-3) */
  unsigned         freq1,         /*   frequency to detect                  */
  unsigned         bandw1,        /*   bandwidth for frequency detection    */
  unsigned         freq2,         /*   2nd frequency to detect (dualtones)  */
  unsigned         bandw2,        /*   2nd bandwidth                        */
  ADI_TONEDETECT_PARMS *parms );  /*   pointer to tone detection parameters */

DWORD NMSAPI adiStopToneDetector( /* Stops tone detection                   */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         toneid );      /*   id of tone to stop detecting         */

/*====== CALL CONTROL ======================================================*/

/*------ DIAL PARAMETERS ---------------------------------------------------*/
                                  /* used during adiStartProtocol() and     */
typedef struct                    /*  passed with adiStartDial():           */
{
    DWORD size ;            /*   size of this structure                     */
    DWORD method;           /* default dialing method: 0=DTMF, 1=pulse, 2=MF*/
    DWORD breaktime;        /* duration of pulse digit break (ms)           */
    DWORD maketime;         /* duration of pulse digit make (ms)            */
    DWORD interpulse;       /* interdigit delay between pulsed digits (ms)  */
    DWORD flashtime;        /* duration of the flash-hook (ms)              */
    DWORD shortpause;       /* duration of the comma in dialing string (ms) */
    DWORD longpause;        /* duration of the dot in dialing string (ms)   */
    INT32 dtmfampl1;        /* first dtmf amplitude (dBm)                   */
    INT32 dtmfampl2;        /* second dtmf amplitude (dBm)                  */
    DWORD dtmfontime;       /* ON duration of DTMFs (ms)                    */
    DWORD dtmfofftime;      /* OFF duration of DTMFs (ms)                   */
    DWORD dialtonewait;     /* max time to wait for dialtone (ms) on ';'    */

                            /*-- Dial tone detection parameters           --*/
    DWORD tonefreq1;        /*   frequency to detect                        */
    DWORD tonebandw1;       /*   bandwidth                                  */
    DWORD tonefreq2;        /*   2nd frequency to detect (dualtone)         */
    DWORD tonebandw2;       /*   2nd bandwidth                              */
    INT32 tonequalampl;     /*   broadband qual level (in dBm)              */
    DWORD tonequaltime;     /*   qualification time (in ms)                 */
    DWORD tonereflevel;     /*   qual thresh,output of filter (IDUs)        */
    DWORD reserved;         /*   reserved, must be 0                        */
    DWORD tonetotaltime;    /*   total time for dial tone with interruptions*/
} ADI_DIAL_PARMS;

/*------ CALLPROGRESS DETECTOR PARAMETERS ----------------------------------*/

typedef struct                    /* passed to adiCallProgress or by        */
{                                 /* adiPlaceCall in ADI_PLACECALL_PARMS.   */
    DWORD size ;        /* Size of this structure                           */
    DWORD timeout;      /* If no tone/voice detected, done via timeout (ms).*/

    DWORD busycount;    /* Number of busy cycles until report and quit;     */
                        /*  busycount ignored if precise busy detected.     */

    DWORD ringcount;    /* Number of ring cycles until report and quit.     */

                        /* Durations to distinguish between network tones:  */
    DWORD maxreorder;   /*  Separates reorder (fast busy) from busy (ms).   */
    DWORD maxbusy;      /*  Separates busy from ring cycle (ms).            */
    DWORD maxring;      /*  Separates ring from dial tones (ms).            */

    DWORD maxringperiod;/* Maximum ring period before CP_RING_QUIT (ms).    */

    DWORD voicemedium;  /* Time after VOICE BEGIN until VOICE MEDIUM (ms).  */
    DWORD voicelong;    /* Time after VOICE BEGIN until VOICE LONG (ms).    */
    DWORD voicextended; /* Time after VOICE BEGIN until VOICE EXTENDED (ms).*/
    DWORD silencetime;  /* Silence period after voice til VOICE END (ms).   */

    DWORD precqualtime; /* Precise tone qualification time (ms).            */
    DWORD precmask;     /* Precise tone mask.                               */
                        #define ADI_CPMSK_PRECISE_CED  0x0001
                        #define ADI_CPMSK_PRECISE_SIT  0x0002
                        #define ADI_CPMSK_PRECISE_BUSY 0x0004

    DWORD stopmask;     /* mask to auto-stop adiCallProgress:               */
                        #define ADI_CPSTOP_ON_RINGTONE     0x01
                        #define ADI_CPSTOP_ON_RINGQUIT     0x02
                        #define ADI_CPSTOP_ON_VOICE_BEGIN  0x04
                        #define ADI_CPSTOP_ON_VOICE_MEDIUM 0x08
                        #define ADI_CPSTOP_ON_VOICE_LONG   0x10
                        #define ADI_CPSTOP_ON_VOICE_EXTD   0x20
                        #define ADI_CPSTOP_ON_VOICE_END    0x40

                        /* additional stopmask bit to modify behavior */
                        #define ADI_CP_REPORT_ALL_RINGS  0x4000
                                                 /* send ADIEVN_CP_RINGTONE */
                                                 /* for each ring cycle */

                                 /*   generic voice-tone detection params.  */
    INT32 silencelevel;          /* Reference level below which is "silence"*/
                                 /*   (in dBm)                              */
    DWORD voicetoneratio;        /* voice vs. tone ratio (IDUs)             */
    DWORD qualtonetime1;         /* Qualify time 1 for the TONE state (ms); */
    DWORD qualtonetime2;         /* Qualify time 2 for the TONE state (ms); */
    DWORD qualvoicetime1;        /* Qualify time 1 for the VOICE state (ms);*/
    DWORD qualvoicetime2;        /* Qualify time 2 for the VOICE state (ms);*/
    DWORD leakagetime;           /* Leaky integrator time constant (in ms)  */
    DWORD noiselevel;            /* Level window for QT2 state (in IDUs)    */
} ADI_CALLPROG_PARMS;


/*------ CALL CONTROL PARAMETERS -------------------------------------------*/

typedef struct                    /* used during adiStartProtocol(),        */
{                                 /* call control parameters:               */
    DWORD size ;                  /*   size of this structure               */
    DWORD eventmask;              /*   report low-level call-control events:*/
          #define ADI_CC_REPTSEIZURE    0x0001 /* ADIEVN_SEIZURE_DETECTED   */
          #define ADI_CC_REPTPROCEEDING 0x0002 /* ADIEVN_PROCEEDING         */
          #define ADI_CC_REPTALERTING   0x0004 /* ADIEVN_REMOTE_ALERTING    */
          #define ADI_CC_REPTANSWERED   0x0008 /* ADIEVN_REMOTE_ANSWERED    */
          #define ADI_CC_REPTDIGITS     0x0010 /* ADIEVN_INCOMING_DIGIT     */
          #define ADI_CC_REPTBILLING    0x0020 /* ADIEVN_BILLING_PULSE      */
          #define ADI_CC_REPTSTATUSINFO 0x0040 /* ADIEVN_INCOMING_STATUSINFO*/

    DWORD mediamask;              /*   functions to run during conversation:*/
          #define ADI_CC_RESVDTMF       0x0001 /* reserve dtmf detection    */
          #define ADI_CC_RESVSILENCE    0x0002 /* reserve silence detector  */
          #define ADI_CC_RESVCLRDWN     0x0004 /* reserve clear-down det.   */
          #define ADI_CC_AUTODTMF       0x0008 /* start DTMF detection      */
          #define ADI_CC_AUTOECHO       0x0010 /* start echo canceller      */
          #define ADI_CC_ALLMEDIA (ADI_CC_RESVDTMF|ADI_CC_RESVSILENCE|\
                             ADI_CC_RESVCLRDWN|ADI_CC_AUTODTMF|ADI_CC_AUTOECHO)
          #define ADI_CC_ACCEPTDTMF     0x0100 /* dtmf detection in accept  */

    DWORD blockmode;              /*   method of blocking:                  */
          #define ADI_CC_BLOCK_REJECTALL 0  /* don't answer subsequent calls*/
          #define ADI_CC_BLOCK_MAKEBUSY  1  /* assert reverse make busy     */
          #define ADI_CC_BLOCK_OOS       2  /* tell switch to block calls   */
    DWORD debugmask;              /*   protocol debug (low-level events):   */
          #define ADI_CC_DBGDIGITS     0x0001 /* report all digits received */
          #define ADI_CC_DBGRINGS      0x0002 /* report all ring begin/ends */
          #define ADI_CC_DBGRINGTONE   0x0004 /* report all ringtone events */
          #define ADI_CC_DBGCID        0x0008 /* report all CID errors      */
} ADI_CALLCTL_PARMS;


/*------ DTMF DETECTOR PARAMETERS ------------------------------------------*/

typedef struct                    /* used during adiStartProtocol() and     */
{                                 /*  passed with adiStartDTMFDetect():     */
    DWORD  size ;                 /*   size of this structure               */
    DWORD  columnfour;            /* 1=detect DTMFs A,B,C,D; 0=don't        */
    INT32  onqualampl;            /* min input lev to qual tone (dBm)       */
    DWORD  onthreshold;           /* talkoff vs.cut-thru quallev (IDUs)     */
    DWORD  onqualtime;            /* qualify time of DTMF (ms)              */
    INT32  offqualampl;           /* min input lev of valid DTMF (dBm)      */
    DWORD  offthreshold;          /* hysteresis:talkoff vs.cutthru (IDUs)   */
    DWORD  offqualtime;           /* disqualify time for tone (ms)          */
} ADI_DTMFDETECT_PARMS;

/*------ START-PROTOCOL CLEARDOWN DETECTOR PARAMETERS ----------------------*/

typedef struct
{                                 /* passed with adiStartProtocol()         */
    DWORD    size ;               /*   size of this structure               */
    DWORD    freq1;               /*   frequency to detect                  */
    DWORD    bandw1;              /*   bandwidth                            */
    DWORD    freq2;               /*   2nd frequency to detect (dualtone)   */
    DWORD    bandw2;              /*   2nd bandwidth                        */
    INT32    qualampl;            /*   broadband qual level (in dBm)        */
    DWORD    qualtime;            /*   qualification time (in ms)           */
    DWORD    reflevel;            /*   qual thresh,output of filter (IDUs)  */
    DWORD    reserved;            /*   reserved, must be 0                  */
    DWORD    tonecount;           /*   # of tones, or 0 for continuous tones*/
    DWORD    minontime;           /*   shortest allowable tone              */
    DWORD    maxontime;           /*   longest allowable tone               */
    DWORD    minofftime;          /*   shortest silence between tones       */
    DWORD    maxofftime;          /*   longest silence between tones        */
} ADI_CLEARDOWN_PARMS;

/*------ START-PROTOCOL ECHO CANCELLER PARAMETERS --------------------------*/
                                  /* Values for 'mode' parameter            */
#define ADI_ECHOCANCEL_DEFAULT 1  /*   Choose best length and adapt time    */
                                  /*    based on current board type.        */
#define ADI_ECHOCANCEL_CUSTOM  2  /*   Use specified len and adapttime.     */
                                  /*    defaults are 0, no echo cancel      */
typedef struct
{                                 /* parameters for echo cancelling:        */
    DWORD  size ;                 /*   size of this structure               */
    DWORD  mode ;                 /*   1- board default  2- custom          */
    DWORD  filterlength ;         /*   filter length (msec)                 */
    DWORD  adapttime ;            /*   filter adaptation time (msec)        */
    DWORD  predelay ;             /*   offset of input sample (msec)        */
    INT32  gain ;                 /*   receive gain (db)                    */
} ADI_ECHOCANCEL_PARMS ;

/*------ START-PROTOCOL PARAMETERS -----------------------------------------*/

typedef struct
{                                  /* passed with adiStartProtocol()        */
    DWORD                size ;    /*   size of this structure              */
    ADI_CALLCTL_PARMS    callctl;  /*   call control parameters             */
    ADI_DIAL_PARMS       dial;     /*   dial control parameters             */
    ADI_DTMFDETECT_PARMS dtmfdet;  /*   DTMF detection parameters           */
    ADI_CLEARDOWN_PARMS  cleardown;/*   clear-down detection parameters     */
    ADI_ECHOCANCEL_PARMS echocancel;/*  echo canceller parameters           */
} ADI_START_PARMS;

/*------ CALL CONTROL FUNCTIONS --------------------------------------------*/
DWORD NMSAPI adiStartProtocol(    /* Loads and Starts a TCP                 */
  CTAHD            ctahd,         /*   context handle                       */
  char            *tcpname,       /*   TCP to run (must be avail on board)  */
  void            *tcpparms,      /*   TCP specific parameters or NULL      */
  ADI_START_PARMS *parms );       /*   start params or NULL for defaults    */

DWORD NMSAPI adiStopProtocol(     /* Stops running previously started TCP   */
  CTAHD            ctahd );       /*   context handle                       */

                                  /* options for adiSetBilling(), also      */
                                  /* returned with BILLING_SET event:       */
#define ADI_BILLINGRATE_FREE    0 /* call is free                           */
#define ADI_BILLINGRATE_DEFAULT 0xFFFF /* default is that call is billed,   */
                                       /* and the network sets the rate     */
DWORD NMSAPI adiSetBilling(       /* Set billing mode of an incoming call   */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         rate);         /*   the requested rate                   */

#define ADI_ACCEPT_PLAY_RING    1 /* play ring while accepting a call       */
#define ADI_ACCEPT_QUIET        2 /* play silence while accepting a call    */
#define ADI_ACCEPT_USER_AUDIO   3 /* user provides audio while accepting    */
DWORD NMSAPI adiAcceptCall(       /* Accept an incoming call                */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         mode,          /*   what to play during accept           */
  void            *reserved );    /*   reserved for future use              */

DWORD NMSAPI adiAnswerCall(       /* Answers an incoming call               */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         ringcount );   /*   number of rings before answering     */

                                  /*  options for adiRejectCall(), also     */
                                  /*   returned with REJECTING_CALL event:  */
#define ADI_REJ_PLAY_REORDER    1 /*  reject inbound with reorder (if able) */
#define ADI_REJ_PLAY_BUSY       2 /*  reject inbound with busy    (if able) */
#define ADI_REJ_PLAY_RINGTONE   3 /*  reject inbound with ringtone(if able) */
#define ADI_REJ_USER_AUDIO      4 /*  reject inbound w/user audio (if able) */
                                  /*  only returned w/ REJECTING_CALL event:*/
#define ADI_REJ_HOST_TIMEOUT    5 /*  rejecting inbound with default tone   */
                                  /*   because PC didn't respond in time    */
#define ADI_REJ_FORCE_IMMEDIATE 6 /*  reject by forcing call termination    */

DWORD NMSAPI adiRejectCall(       /* Rejects an incoming call               */
  CTAHD            ctahd,         /*   context handle                       */
  int              method );      /*   method of rejecting the call         */
                                  /*   (for loop-start,always play ringtone)*/

DWORD NMSAPI adiReleaseCall(      /* Releases a call (hangs-up)             */
  CTAHD            ctahd );       /*   context handle                       */

DWORD NMSAPI adiBlockCalls(       /* Blocks subsequent calls                */
  CTAHD            ctahd );       /*   context handle                       */

DWORD NMSAPI adiUnBlockCalls(     /* UnBlocks subsequent calls              */
  CTAHD            ctahd );       /*   context handle                       */

DWORD NMSAPI adiAcceptIncomingAddress( /* Tell TCP to complete call setup   */
  CTAHD            ctahd );       /*   context handle                       */

typedef struct
{                                 /* Passed with adiPlaceCall,              */
                                  /* adiTransferCall, adiPlaceSecondCall    */
    DWORD               size ;    /*   size of this structure               */
    DWORD connectmask;            /*   events that transition to connected: */
          #define ADI_CON_ON_SIGNAL         0x0001 /* out-of-band signal    */
          #define ADI_CON_ON_VOICE_BEGIN    0x0002 /* on the begin of voice */
          #define ADI_CON_ON_VOICE_MEDIUM   0x0004 /* on cp voice medium    */
          #define ADI_CON_ON_VOICE_LONG     0x0008 /* on cp voice long      */
          #define ADI_CON_ON_VOICE_EXTENDED 0x0010 /* on cp voice extended  */
          #define ADI_CON_ON_VOICE_END      0x0020 /* on cp voice end       */
          #define ADI_CON_ON_RING_QUIT      0x0080 /* on cp ringquit        */
          #define ADI_CON_ON_CED            0x0100 /* on cp CED detect      */
          #define ADI_CON_ON_DIALTONE       0x0200 /* on cp dialtone        */
          #define ADI_CON_ON_SIT            0x0400 /* on cp SIT detect      */
          #define ADI_CON_ON_RING_BEGIN     0x0800 /* on cp ring begin      */
          #define ADI_CON_ON_PROCEEDING     0x8000 /* don't run cp          */

          #define ADI_CON_ON_ANSWER\
                  (ADI_CON_ON_SIGNAL|ADI_CON_ON_VOICE_BEGIN|ADI_CON_ON_CED)

    DWORD disconnectmask;         /* events that transition to disconnected:*/
          #define ADI_DIS_ON_VOICE_BEGIN    0x0002 /* on the begin of voice */
          #define ADI_DIS_ON_VOICE_MEDIUM   0x0004 /* on cp voice medium    */
          #define ADI_DIS_ON_VOICE_LONG     0x0008 /* on cp voice long      */
          #define ADI_DIS_ON_VOICE_EXTENDED 0x0010 /* on cp voice extended  */
          #define ADI_DIS_ON_VOICE_END      0x0020 /* on cp voice ended     */
          #define ADI_DIS_ON_TIMEOUT        0x0040 /* on cp timeout         */
          #define ADI_DIS_ON_RING_QUIT      0x0080 /* on cp ringquit        */
          #define ADI_DIS_ON_CED            0x0100 /* on callprog CED detect*/
          #define ADI_DIS_ON_RING_BEGIN     0x0800 /* on cp ring begin      */
                                  /* and default disconnect on dialtone and */
                                  /* SIT, and always disconnect on reorder, */
                                  /* busy, no answer and no wink.           */

    ADI_CALLPROG_PARMS  callprog; /*   call progress parameters             */
} ADI_PLACECALL_PARMS;

DWORD NMSAPI adiPlaceCall(        /* Places a call                          */
  CTAHD                ctahd,     /*   context handle                       */
  char                *digitstr,  /*   extended digit string                */
  ADI_PLACECALL_PARMS *parms );   /*   place call param or NULL for defaults*/

#define ADI_XFER_PROCEEDING  1    /*  options for                           */
#define ADI_XFER_ALERTING    2    /*  adiTransferCall()                     */
#define ADI_XFER_CONNECTED   3    /*                                        */

DWORD NMSAPI adiTransferCall(     /* Places a call                          */
  CTAHD                ctahd,     /*   context handle                       */
  char                *digitstr,  /*   extended digit string                */
  unsigned             xferwhen,  /*   when to complete the transfer        */
  ADI_PLACECALL_PARMS *parms );   /*   place call param or NULL for defaults*/

DWORD NMSAPI adiPlaceSecondCall(  /* Places a call                          */
  CTAHD                ctahd,     /*   context handle                       */
  char                *digitstr,  /*   extended digit string                */
  ADI_PLACECALL_PARMS *parms );   /*   place call param or NULL for defaults*/

DWORD NMSAPI adiReleaseSecondCall(
                                  /* Releases a second call                 */
  CTAHD            ctahd );       /*   context handle                       */

/* Values for pending command in ADI_CALL_STATUS */
#define ADI_PENDCMD_PLACE_CALL      1
#define ADI_PENDCMD_ANSWER_CALL     2
#define ADI_PENDCMD_REJECT_CALL     3
#define ADI_PENDCMD_RELEASE_CALL    4
#define ADI_PENDCMD_TRANSFER_CALL   5
#define ADI_PENDCMD_PLACE_SECOND    6
#define ADI_PENDCMD_RELEASE_SECOND  7
#define ADI_PENDCMD_ACCEPT_CALL     8

#define ADI_MAX_DIGITS 31
#define ADI_MAX_CNAME  31
typedef struct
{                                 /* used by adiGetCallStatus()             */
    DWORD size ;                  /* size returned by adiGetCallStatus()    */
    DWORD state;                  /* call states (ADI_CC_STATE_xxx below)   */
    INT32 reason;                 /* reason of going back to IDLE state     */
    char  calledaddr [ADI_MAX_DIGITS+1]; /* DNIS info  (null term string)   */
    char  callingaddr[ADI_MAX_DIGITS+1]; /* ANI info (null term string)     */
    char  callingname[ADI_MAX_CNAME+1];  /* Calling party name              */
    DWORD pendingcommand ;        /* current unack'ed command (see above)   */
    char  usercategory;           /* the type of the calling party          */
    char  tollcategory;           /* (generally the same as usercategory)   */
    BYTE  stream;                 /* MVIP address of B channel              */
    BYTE  timeslot;               /* MVIP address of B channel              */

    WORD  billingrate;            /* billing rate of call                   */

    char  callednumplan;          /* Q.931 numbering plan ID if supported   */
    char  callednumtype;          /* Q.931 number type if supported         */
    char  callingnumplan;         /* Q.931 numbering plan ID if supported   */
    char  callingnumtype;         /* number type if supported               */
    char  callingpres;            /* caller ID presentation indicator       */
    char  callingscreen;          /* Q.931 ANI screening indicator          */
    char  progressdescr;          /* progress descriptor                    */
    char  releasecause;           /* cause for call release                 */

    char  redirectingaddr[ADI_MAX_DIGITS+1];  /* redirecting number info    */
    char  redirectingplan;        /* Q.931 numbering plan ID if supported   */
    char  redirectingtype;        /* Q.931 number type if supported         */
    char  redirectingpres;        /* redirecting number pres. indicator     */
    char  redirectingscreen;      /* Q.931 redirecting number screen ind.   */
    char  redirectingreason;      /* reason for redirection                 */

    char  originalcalledaddr [ADI_MAX_DIGITS+1]; /* original called number  */
    char  origcalledplan;         /* Q.931 numbering plan ID if supported   */
    char  origcalledtype;         /* Q.931 number type if supported         */
    char  origcalledpres;         /* original called number pres. indicator */
    char  origcalledscreen;       /* Q.931 redirecting number screen ind.   */
    char  origcalledreason;       /* Q.931 reason for redirection           */

    char  UUI[132];               /*   user to user information             */

} ADI_CALL_STATUS;


DWORD NMSAPI adiGetCallStatus(    /* Returns call state info                */
  CTAHD            ctahd,         /*   context handle                       */
  ADI_CALL_STATUS *status,        /*   pointer to call info structure       */
  unsigned         size );        /*   size of the above structure          */

/*--------------------------------------------------------------------------*/
/* values associated with the event ADIEVN_STATUSINFO_UPDATE, signaling a   */
/* asynchronous change in the ADI_CALL_STATUS structure                     */
/*--------------------------------------------------------------------------*/
#define CALL_STATUS_CALLINGADDR 1
#define CALL_STATUS_BILLINGRATE 2
#define CALL_STATUS_UUI         3

DWORD NMSAPI adiSetExtendedArgs(  /* Set supplementary services arguments   */
  CTAHD            ctahd,         /*   context handle                       */
  void            *p,             /*   pointer to suitable structure        */
  unsigned         size);         /*   size of the above  structure         */

/*-------------------- Values for call control events ----------------------*/

/*------ Reason for connect ADIEVN_CALL_CONNECTED, CALL2_CONNECTED----------*/

#define ADI_CON_ANSWERED           0  /*                                    */
#define ADI_CON_SIGNAL             1  /*                                    */
#define ADI_CON_VOICE_BEGIN        2  /* out-bound voice detected           */
#define ADI_CON_VOICE_MEDIUM       3  /* out-bound voice medium             */
#define ADI_CON_VOICE_LONG         4  /* out-bound voice long               */
#define ADI_CON_VOICE_EXTENDED     5  /* out-bound voice extended           */
#define ADI_CON_VOICE_END          6  /* out-bound voice ended              */
#define ADI_CON_TIMEOUT            7  /* out-bound timeout (hi & dry?)      */
#define ADI_CON_RING_QUIT          8  /* out-bound ring stop(soft speaker)  */
#define ADI_CON_CED                9  /* out-bound CED detected             */
#define ADI_CON_DIALTONE_DETECTED 10  /* out-bound cp dialtone (may be DISA)*/
#define ADI_CON_SIT_DETECTED      11  /* out-bound SIT detected             */
#define ADI_CON_RING_BEGIN        12  /* out-bound ring detected            */
#define ADI_CON_PROCEEDING        20  /* don't run call-progress            */


/*------ Reason for disconnect ADIEVN_DISCONNECTED -------------------------*/

#define ADI_DIS_REJECT_REQUESTED   1  /* Call disconnected via adiRejectCall*/

#define ADI_DIS_SIGNAL             2  /* Out-of-band remote disconnect      */
#define ADI_DIS_CLEARDOWN_TONE     3  /* In-band remote disconnect          */
#define ADI_DIS_RING_STUCK         4  /* Incoming ring stuck to long        */
#define ADI_DIS_HOST_TIMEOUT       5  /* Host did not respond in time       */
#define ADI_DIS_REMOTE_ABANDONED   6  /* Loop-start inbound stopped ringing */

#define ADI_DIS_TRANSFER           7  /* Transfer completed                 */

#define ADI_DIS_DIAL_FAILURE       8  /* Dial had a failure                 */
#define ADI_DIS_NO_WINK            9  /* No wink when dialing out           */
#define ADI_DIS_NO_DIALTONE       10  /* No dialtone to dialing out (LPS)   */

#define ADI_DIS_REMOTE_NOANSWER   11  /* 'Place call' got no answer         */
#define ADI_DIS_BUSY_DETECTED     12  /* 'Place call' got busy tone         */
#define ADI_DIS_REORDER_DETECTED  13  /* 'Place call' got reorder tone      */
#define ADI_DIS_DIALTONE_DETECTED 14  /* 'Place call' got dialtone after dial*/
#define ADI_DIS_SIT_DETECTED      15  /* 'Place call' got SIT tone          */
#define ADI_DIS_VOICE_BEGIN       16  /* 'Place call' got voice detected    */
#define ADI_DIS_VOICE_MEDIUM      17  /* 'Place call' got voice medium      */
#define ADI_DIS_VOICE_LONG        18  /* 'Place call' got voice long        */
#define ADI_DIS_VOICE_EXTENDED    19  /* 'Place call' got voice extended    */
#define ADI_DIS_VOICE_END         20  /* 'Place call' got voice ended       */
#define ADI_DIS_TIMEOUT           21  /* 'Place call' got timeout(hi & dry?)*/
#define ADI_DIS_RING_QUIT         22  /* 'Place call' got ringstop(soft spkr)*/
#define ADI_DIS_CED               23  /* 'Place call' got CED detected      */
#define ADI_DIS_NO_LOOP_CURRENT   24  /* No loop current to dial out (LPS)  */
#define ADI_DIS_NO_CS_RESOURCE    25  /* No CS resource to place call       */
#define ADI_DIS_RING_BEGIN        26  /* 'Place call' got ring begin        */
                                      /* 990715 CAT New DIS values with NCC */
#define ADI_DIS_GLARE             27  /* call disconnected because of glare */
#define ADI_DIS_SIGNAL_UNASSIGNED_NUMBER \
                                  28  /* called number is not allocated     */
#define ADI_DIS_SIGNAL_UNKNOWN    29  /* disconnected via unknown signal    */
#define ADI_DIS_PROTOCOL_ERROR    30  /* protocol error had occured         */
#define ADI_DIS_FRAMING_ALARM     31  /* aglc reported alarm                */


/*------ Remote Answered ADIEVN_REMOTE_ANSWERED ----------------------------*/

#define ADI_ANSW_SIGNAL            1  /*    due to out-of-band signalling   */
#define ADI_ANSW_VOICE             2  /*    due to voice detection          */
#define ADI_ANSW_MODEM             3  /*    due to modem detection          */

/*------ Out-of-Service  ADIEVN_OUT_OF_SERVICE -----------------------------*/

#define ADI_CC_OOS_REMOTE_BLOCK    1 /* Remote end is blocking calls        */
#define ADI_CC_OOS_NO_DIGITS       2 /* DID Timed out waiting for 1st digit */
#define ADI_CC_OOS_DIGIT_TIMEOUT   3 /* DID,Timed out waiting for digits    */
#define ADI_CC_OOS_WINK_STUCK      4 /* OGT,Wink is too long                */
#define ADI_CC_OOS_PERM_SIGNAL     5 /* Timed out waiting for remote end    */
#define ADI_CC_OOS_NO_LOOP_CURRENT 6 /* No loop current to place calls      */
#define ADI_CC_OOS_LINE_FAULT      7 /* Line not in correct state           */

/*------ Protocol error ADIEVN_PROTOCOL_ERROR ------------------------------*/

/* 990715 (from hostif.tcs) The ERR_* constant values must follow the SEQ_* 
*  values sequentially, due to an overlap of their use in qualifying a single 
*  event in NCC.
*
*  The following 9 definitions have been re-numbered from 1-9 to 4-11; defines
*  12 and 13 are new. 
*/ 
#define ADI_CC_ERR_FALSE_SEIZURE    4 /* DID:Seized, then gone before digits*/
                                      /* LPS:Ring stopped b4 inc-call event */
#define ADI_CC_ERR_EXTRA_DIGITS     5 /* DID:More digits rec'd than expected*/
#define ADI_CC_ERR_PREMATURE_ANSWER 6 /* OGT:Answer before all digits given */
#define ADI_CC_ERR_DIGIT_TIMEOUT    7 /* timeout in digit reception         */
#define ADI_CC_ERR_INVALID_DIGIT    8 /* invalid compelled digit received   */
#define ADI_CC_ERR_BAD_DIALSTRING   9 /* invalid formatting of dial string  */
#define ADI_CC_ERR_NO_CS_RESOURCE  10 /* call setup resource unavailable    */
#define ADI_CC_ERR_NOT_SUPPORTED   11 /* generic: last command unsupported  */
#define ADI_CC_ERR_BAD_SEQUENCE    12 /* protocol-specific bad state for cmd*/
#define ADI_CC_ERR_TIMEOUT         13 /* protocol-specific timeout          */


/*------ Sequence error ADIEVN_SEQUENCE_ERROR ------------------------------*/

#define ADI_SEQ_ERR_WRONG_STATE     1 /* command was issued in wrong state  */
#define ADI_SEQ_ERR_NOT_SUPPORTED   2 /* unsupported function requested     */
#define ADI_SEQ_ERR_CALLS_BLOCKED   3 /* command in blocking state          */

/*------ Diagnostic/debug ADIEVN_PROTOCOL_EVENT ----------------------------*/
                                           /*------ 'ADI_CC_DBGRINGS' ------*/
#define  ADI_CCDBG_RING_BEGIN  0x001       /* leading edge                  */
#define  ADI_CCDBG_RING_OK     0x011       /* qualified as a good ring      */
#define  ADI_CCDBG_RING_END    0x002       /* ring end after qualified      */
#define  ADI_CCDBG_RING_FALSE  0x000       /* disqualified                  */
                                           /*----- 'ADI_CC_DBGRINGTONE' ----*/
#define  ADI_CCDBG_RINGTONE    0x101       /* ring tone during placecall    */
                                           /*  size contains ringcnt        */
                                           /*------ 'ADI_CC_DBGDIGITS' -----*/
                                           /*  size contains digit          */
#define  ADI_CCDBG_DTMF        0x201       /* DTMF digit                    */
#define  ADI_CCDBG_MF          0x202       /* MF digit                      */
#define  ADI_CCDBG_R2FORWARD   0x203       /* MFC-R2 FWD                    */
#define  ADI_CCDBG_R2BACKWARD  0x204       /* MFC-R2 BACK                   */
#define  ADI_CCDBG_PULSE_DIGIT 0x205       /* pulse digit                   */
                                           /*------ 'ADI_CC_DBGDIGITS' -----*/
                                           /*  size contains actual error   */
#define  ADI_CCDBG_CID_ERROR   0x301       /* CID line error:               */
                                           /*    ADI_REASON_BAD_STOP_BIT    */
                                           /*    ADI_REASON_DROP_IN_DATA    */
                                           /* ADI_REASON_BAD_PARITY         */
                                           /* ADI_REASON_BAD_CRC            */
                                           /* ADI_REASON_BAD_CHECKSUM       */


/*------ CALL (and TCP) STATES -----------------------------------------------*/
/* Note that state transitions occur on EVENTS only, not on commands          */

                                       /* expected events | valid commands   */
                                       /* ----------------|-------------------*/
#define ADI_CC_STATE_STOPPED         0 /* only PROTOCOL_STARTED if not NOCC   */
                                       /*                 :                   */
#define ADI_CC_STATE_IDLE            1 /*  _INCOMING_CALL :                   */
                                       /*  _PLACING       : adiPlaceCall      */
                                       /*  _CALLS_BLOCKED : adiBlockCalls(1)  */
                                       /*                 : adiReleaseCall(4) */
                                       /*  _OUT_OF_SERVICE:                   */
                                       /*                 :                   */
#define ADI_CC_STATE_INCOMING_CALL   2 /*  _ANSWERING     : adiAnswerCall     */
                                       /*  _REJECTING     : adiRejectCall     */
                                       /*  _DISCONNECTED  :                   */
                                       /*                 :                   */
#define ADI_CC_STATE_ANSWERING_CALL  3 /*  _CONNECTED     : adiAnswerCall     */
                                       /*  _DISCONNECTED  :                   */
                                       /*  _RELEASED      : adiReleaseCall    */
                                       /*                 :                   */
#define ADI_CC_STATE_PLACING_CALL    4 /*  _CONNECTED     :                   */
                                       /*  _DISCONNECTED  :                   */
                                       /*  _RELEASED      : adiReleaseCall    */
                                       /*                 :                   */
#define ADI_CC_STATE_DISCONNECTED    5 /*  _RELEASED      : adiReleaseCall    */
                                       /*                 :                   */
#define ADI_CC_STATE_BLOCKING        6 /*  _UNBLOCKED     : adiUnblockCalls(2)*/
                                       /*                 :                   */
#define ADI_CC_STATE_CONNECTED       7 /*  _RELEASED      : adiReleaseCall    */
                                       /*  _DISCONNECTED  : adiTransferCall(3)*/
                                       /*  _PLACING_2     : adiPlaceSecondCall*/
                                       /*  _2_DISCONNECTED: adiReleaseSecond  */
                                       /*                 :                   */
#define ADI_CC_STATE_REJECTING_CALL  8 /*  _DISCONNECTED  : none              */
                                       /*                 :                   */
#define ADI_CC_STATE_OUT_OF_SERVICE  9 /*  _IN_SERVICE    : none              */
                                       /*                 :                   */
#define ADI_CC_STATE_PLACING_CALL2  10 /*  _RELEASED      : adiReleaseCall    */
                                       /*  _2_DISCONNECTED: adiReleaseSecond  */
                                       /*                 :                   */
#define ADI_CC_STATE_CONNECTED2     11 /*  _RELEASED      : adiReleaseCall    */
                                       /*  _2_DISCONNECTED: adiReleaseSecond  */
                                       /*                 :                   */

                                       /* (1) can always call block calls,    */
                                       /*     which tells the protocol to     */
                                       /*     block calls next time it goes   */
                                       /*     to idle.                        */
                                       /* (2) can always call unblock calls,  */
                                       /*     which clears the block calls    */
                                       /*     flag, and if currently blocking,*/
                                       /*     returns to idle.                */
                                       /* (3) the following are PBX extensions*/
                                       /*     to standard call control:       */
                                       /*      adiTransferCall,               */
                                       /*      adiPlaceSecondCall             */
                                       /*      adiReleaseSecondCall           */
                                       /* (4) Release in IDLE state can be    */
                                       /*     used to cancel a PlaceCall.     */
                                       /*                 :                   */
#define ADI_CC_STATE_ACCEPTING_CALL 12 /*  _CONNECTED     : adiAnswerCall     */
                                       /*  _DISCONNECTED  : none              */
                                       /*  _RELEASED      : adiReleaseCall    */


/*====== NULL CALL-CONTROL ("NOCC",LOW-LEVEL) ==============================*/


DWORD NMSAPI adiStartSignalDetector(
                                  /* Starts A/B signal detector             */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         initial,       /*   initial state (see 'signalling bits')*/
  unsigned         mask,          /*   mask  (see 'signalling bits')        */
  unsigned         timeon,        /*   deglitching on                       */
  unsigned         timeoff );     /*   deglitching off                      */

/*------ ADIEVN_SIGNALBIT_CHANGED value field -------------------------------*/
#define ADI_A_BIT_HI         0xA1
#define ADI_B_BIT_HI         0xB1
#define ADI_C_BIT_HI         0xC1
#define ADI_D_BIT_HI         0xD1
#define ADI_A_BIT_LO         0xA0
#define ADI_B_BIT_LO         0xB0
#define ADI_C_BIT_LO         0xC0
#define ADI_D_BIT_LO         0xD0

DWORD NMSAPI adiStopSignalDetector(
                                  /* Stops A/B signal detector              */
  CTAHD            ctahd );       /*   context handle                       */

DWORD NMSAPI adiQuerySignalState( /* Queries the state of the A/B sig det.  */
  CTAHD            ctahd );       /*   context handle                       */

DWORD NMSAPI adiStartDTMFDetector(
                                  /* Turn on DTMF detection                 */
  CTAHD            ctahd,         /*   context handle                       */
  ADI_DTMFDETECT_PARMS *parms );  /*   DTMF detection parameters            */

DWORD NMSAPI adiStopDTMFDetector( /* Turn off DTMF detection                */
  CTAHD            ctahd );       /*   context handle                       */

DWORD NMSAPI adiStartPulse(       /* Starts a precise pulse                 */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         signal,        /*   signaling bits                       */
  unsigned         timeon,        /*   duration ON                          */
  unsigned         timeoff );     /*   duration OFF                         */

DWORD NMSAPI adiAssertSignal(     /* Sends an A/B signalling pattern        */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         pattern );     /*   mask to send (see 'signalling bits') */

DWORD NMSAPI adiStartTimer(       /* Start a timer                          */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         timeout,       /*   msec                                 */
  unsigned         count );       /*   iterations (number of ticks)         */

DWORD NMSAPI adiStopTimer(        /* Stop the timer                         */
  CTAHD            ctahd );       /*   context handle                       */

DWORD NMSAPI adiStartDial(        /* Starts dialing                         */
  CTAHD            ctahd,         /*   context handle                       */
  char            *digits,        /*   string of digits to be played        */
  ADI_DIAL_PARMS   *parms );      /*   dial parameters                      */

DWORD NMSAPI adiStopDial(         /* Stops dialing                          */
  CTAHD            ctahd );       /*   context handle                       */

DWORD NMSAPI adiStartCallProgress(
                                  /* Starts call progress                   */
  CTAHD               ctahd,      /*   context handle                       */
  ADI_CALLPROG_PARMS  *parms );   /*   parameters                           */

DWORD NMSAPI adiStopCallProgress( /* Stop call progress.                    */
  CTAHD            ctahd );       /*   context handle                       */

/*--------------- FSK ------------------------------------------------------*/

typedef struct
{
    DWORD size;             /* Size of this structure                       */
    DWORD noseizureflag;    /* No channel seizure when set                  */
    INT32 level;            /* Transmit output scaling (dBm)                */
    DWORD seizetime;        /* Length of channel seisure in (ms)            */
    DWORD marktime;         /* Length of the initial mark signal in (ms)    */
    DWORD baudrate;         /* Baud rate                                    */
} ADI_FSKSEND_PARMS;


typedef struct
{
    DWORD size;             /* Size of this structure                       */
    INT32 minlevel;         /* Required minimum receive modem signal level  */
    DWORD minmark;          /* Minimum required initial mark and seizure    */
    DWORD droptime;         /* Minimum dropout to silence before a packet   */
                            /* considered terminated (ms)                   */
    DWORD baudrate;         /* Baud rate                                    */
} ADI_FSKRECEIVE_PARMS;


DWORD NMSAPI adiStartSendingFSK   /* Send FSK data */
    (
    CTAHD           ctahd,        /* context handle                         */
    void           *buffer,       /* Address of buffer of bytes to send     */
    unsigned        bufsiz,       /* Buffer size                            */
    ADI_FSKSEND_PARMS *parms      /* FSK Send Parameters                    */
    );

DWORD NMSAPI adiStartReceivingFSK /* Receive FSK data                       */
    (
    CTAHD           ctahd,        /* context handle                         */
    void           *buffer,       /* Address of buffer of bytes to receive  */
    unsigned        bufsiz,       /* Buffer size                            */
    ADI_FSKRECEIVE_PARMS *parms   /* FSK Receive Parameters                 */
    );

DWORD NMSAPI adiStopSendingFSK    /* Stop Send FSK data                     */
    (
    CTAHD           ctahd         /* context handle                         */
    );

DWORD NMSAPI adiStopReceivingFSK  /* Stop Receiving FSK data                */
    (
    CTAHD           ctahd         /* context handle                         */
    );

/*====== GLOBAL PARAMETER MANAGEMENT =======================================*/

/*------ PARAMETER IDs ----------------------------------------------------*/

/* The following parameter IDs are provided for calling adiGetParms()
 * and correspond to ADI_xxx_PARMS structures:
 */
#define       ADI_PLAY_PARMID  (ADI_BASEID +  1)
#define     ADI_RECORD_PARMID  (ADI_BASEID +  2)
#define       ADI_TONE_PARMID  (ADI_BASEID +  3)
#define       ADI_DTMF_PARMID  (ADI_BASEID +  4)
#define    ADI_COLLECT_PARMID  (ADI_BASEID +  6)
#define ADI_DTMFDETECT_PARMID  (ADI_BASEID +  7)
#define ADI_TONEDETECT_PARMID  (ADI_BASEID +  8)
#define     ADI_ENERGY_PARMID  (ADI_BASEID +  9)
#define       ADI_DIAL_PARMID  (ADI_BASEID + 10)
#define   ADI_CALLPROG_PARMID  (ADI_BASEID + 11)
#define      ADI_START_PARMID  (ADI_BASEID + 12)
#define    ADI_FSKSEND_PARMID  (ADI_BASEID + 14)
#define ADI_FSKRECEIVE_PARMID  (ADI_BASEID + 15)
#define  ADI_PLACECALL_PARMID  (ADI_BASEID + 16)

/* Note: ADI_BASEID + 17, ADI_BASEID + 18 reserved for expansion */

#define       ADI_MIN_PARMID  (ADI_BASEID + 1)
#define       ADI_MAX_PARMID  (ADI_BASEID + 27)

typedef struct
{                                 /* Describes the fields in a structure:   */
    char  structname[40];         /*   name of the structure                */
    char  fieldname[40];          /*   name of the field                    */
    DWORD offset;                 /*   byte offset from the base            */
    DWORD size;                   /*   size of the field                    */
    DWORD format;                 /*   format type (see below)              */
    DWORD units;                  /*   units type (see below)               */
} ADI_PARM_INFO;

/* Definition of the 'format' field of ADI_PARM_INFO */
#define ADI_FMT_UNKNOWN     0
#define ADI_FMT_WORD        1
#define ADI_FMT_DWORD       2
#define ADI_FMT_INT16       3
#define ADI_FMT_INT32       4
#define ADI_FMT_STRING      5

/* Definition of the 'units' field of ADI_PARM_INFO */
#define ADI_UNITS_INTERNAL  0
#define ADI_UNITS_INTEGER   1
#define ADI_UNITS_COUNT     2
#define ADI_UNITS_MASK      3
#define ADI_UNITS_HZ        4
#define ADI_UNITS_MS        5
#define ADI_UNITS_DB        6
#define ADI_UNITS_DBM       7
#define ADI_UNITS_IDU       8
#define ADI_UNITS_STRING    9
#define ADI_UNITS_PERCENT  10


/*====== MISCELLANEOUS FUNCTIONS ===========================================*/

typedef struct
{                                 /* User accessible PORT INFO structure:   */
    DWORD   size;                 /*   returned size of this structure      */
    DWORD   queueid;              /*   queue id (a.k.a. devid in adi.lib)   */
    DWORD   userid;               /*   user supplied during 'adiOpenPort()' */
    INT32   agliberr;             /*   last error code after calling AGLIB  */
    DWORD   channel;              /*   AG Channel (driver port id)          */
    DWORD   board;                /*   AG Board                             */
    DWORD   stream;               /*   MVIP stream of this port             */
    DWORD   timeslot;             /*   MVIP slot of this port               */
    DWORD   mode;                 /*   MVIP mode of operation of this port  */
    DWORD   maxbufsize;           /*   maximum board buffer size            */
    char    tcpname[12];          /*   Current Protocol                     */
    DWORD   state;                /*   port state                           */
    DWORD   stream95;             /*   MVIP-95 base stream number           */
} ADI_CONTEXT_INFO;

/* Definition of the 'state' field of ADI_CONTEXT_INFO */
#define ADI_STATE_OPENING     0x0001 /*  In process of opening the port     */
#define ADI_STATE_OPENED      0x0002 /*  OPENPORT/CXT_DONE rxd with success */
#define ADI_STATE_OPENFAILED  0x0004 /*  OPENPORT/CXT_DONE rxd with fail    */
#define ADI_STATE_CLOSING     0x0008 /*  In process of closing              */
#define ADI_STATE_STARTING    0x0010 /*  In process of starting protocol    */
#define ADI_STATE_STARTED     0x0020 /*  STARTPROTOCOL_DONE with success    */
#define ADI_STATE_STOPPING    0x0040 /*  In process of stopping protocol    */
#define ADI_STATE_STARTFAILED 0x0080 /*  STARTPROTOCOL_DONE with error      */
#define ADI_STATE_DRIVERONLY  0x4000 /*  AG Driver query port/cxt           */
#define ADI_STATE_SUPERVISOR  0x8000 /*  AG supervisor port/cxt             */

DWORD NMSAPI adiGetContextInfo(   /* Returns information about the context  */
  CTAHD             ctahd,        /*   context handle                       */
  ADI_CONTEXT_INFO *data,         /*   pointer to context info structure    */
  unsigned          size );       /*   size of the above structure          */

DWORD NMSAPI adiSetTCPTrace(      /* Enables/Disable TCP tracing            */
  CTAHD            ctahd,         /*   context handle                       */
  unsigned         value );       /*   which function to call               */

typedef struct
{
    BYTE  stream ;
    BYTE  slot ;
} ADI_TIMESLOT ;

DWORD NMSAPI adiGetBoardSlots(    /* Returns configured timeslots on a board*/
    CTAHD          ctahd,         /* CT Access context handle               */
    unsigned       board,         /* AG board number                        */
    unsigned       mode,          /* ADI_VOICE_DUPLEX, ADI_FULL_DUPLEX      */
    unsigned       maxslot,       /* Maximum number of entries in array     */
    ADI_TIMESLOT  *slotlist,      /* Returned array of timeslots            */
    unsigned      *numslots );    /* returned number of entries             */

typedef struct
{
    DWORD size;                   /* Size of this structure                 */
    DWORD boardtype;              /* Physical board type ADI_BOARDTYPE_xxx  */
    DWORD serial;                 /* Serial number                          */
    DWORD ioaddr;                 /* Base IO address                        */
    DWORD intnum;                 /* Interrupt number                       */
    DWORD bufsize;                /* Buffer size                            */
    DWORD freemem;                /* Available memory                       */
    BYTE  daughterboardid[4] ;    /* Daughterboard IDs; 0 = none            */
    DWORD totalmips;              /* Total gross DSP MIPS                   */
    DWORD trunktype;              /* Trunk type ADI_TRUNKTYPE_xxx           */
    DWORD numtrunks;              /* Number of trunks                       */
} ADI_BOARD_INFO;

/* Boardtype values as reported in ADI_BOARD_INFO */
#define ADI_BOARDTYPE_UNKNOWN         0
#define ADI_BOARDTYPE_AG24            1
#define ADI_BOARDTYPE_AG24PLUS        2
#define ADI_BOARDTYPE_AG30            3
#define ADI_BOARDTYPE_AG48            4
#define ADI_BOARDTYPE_AG60            5
#define ADI_BOARDTYPE_AG8             6
#define ADI_BOARDTYPE_T1              7
#define ADI_BOARDTYPE_E1              8
#define ADI_BOARDTYPE_AG8_80          9
#define ADI_BOARDTYPE_QX2000         10
#define ADI_BOARDTYPE_AGQUADT1       11
#define ADI_BOARDTYPE_AGQUADE1       12
#define ADI_BOARDTYPE_AGDUALT1       13
#define ADI_BOARDTYPE_AGDUALE1       14
#define ADI_BOARDTYPE_QUADT1_CONNECT 15
#define ADI_BOARDTYPE_QUADE1_CONNECT 16
#define ADI_BOARDTYPE_CPCI_QUADT1    17
#define ADI_BOARDTYPE_CPCI_QUADE1    18
#define ADI_BOARDTYPE_AG2000         19     /* 8 port analog on PCI */
#define ADI_BOARDTYPE_AG4000_4T      20     /* AG4000 Quad T1 */
#define ADI_BOARDTYPE_AG4000_4E      21     /* AG4000 Quad E1 */
#define ADI_BOARDTYPE_AG4000_2T      22     /* AG4000 Dual T1 */
#define ADI_BOARDTYPE_AG4000_2E      23     /* AG4000 Dual E1 */
#define ADI_BOARDTYPE_AG4000_1T      24     /* AG4000 Single T1 */
#define ADI_BOARDTYPE_AG4000_1E      25     /* AG4000 Single E1 */
#define ADI_BOARDTYPE_AG4000C_4T     26     /* AG4000C Quad T1 */
#define ADI_BOARDTYPE_AG4000C_4E     27     /* AG4000C Quad E1 */
#define ADI_BOARDTYPE_AG4000C_2T     28     /* AG4000C Dual T1 */
#define ADI_BOARDTYPE_AG4000C_2E     29     /* AG4000C Dual E1 */

/* Trunktype values as reported in ADI_BOARD_INFO */
#define ADI_TRUNKTYPE_NONE            0     /* DSP-only board             */
#define ADI_TRUNKTYPE_T1              1     /* T1                         */
#define ADI_TRUNKTYPE_E1              2     /* E1                         */
#define ADI_TRUNKTYPE_LOOPSTART       3     /* Loop start                 */
#define ADI_TRUNKTYPE_GROUNDSTART     4     /* Ground start or LSGS combo */
#define ADI_TRUNKTYPE_DID             5     /* DID or DID/E&M combo       */
#define ADI_TRUNKTYPE_EM              6     /* E&M                        */
#define ADI_TRUNKTYPE_EM4W            7     /* 4-Wire E&M                 */
#define ADI_TRUNKTYPE_STATION         8     /* Station (battery feed)     */
#define ADI_TRUNKTYPE_MONITOR         9     /* Audio Monitor              */
#define ADI_TRUNKTYPE_UNKNOWN       255     /* Unknown type               */


DWORD NMSAPI adiGetBoardInfo (    /* Returns info about an AG board         */
    CTAHD           ctahd,        /* CT Access context handle               */
    unsigned        board,        /* AG board number                        */
    unsigned        size,         /* Size of caller's structure; ret size in*/
    ADI_BOARD_INFO *boardinfo );  /* the returned structure.                */

typedef struct
{
    DWORD size;                   /* Size of this structure                 */
    WORD  data[32];               /* EEprom data                            */
} ADI_EEPROM_DATA;

DWORD NMSAPI adiGetEEPromData(    /* Returns 'user' section of board EEProm */
    CTAHD           ctahd,        /* CT Access context handle               */
    unsigned        board,        /* AG board number                        */
    unsigned        size,         /* Size of caller's structure; ret size in*/
    ADI_EEPROM_DATA *eepromdata); /* the returned structure.                */

DWORD NMSAPI adiGetTimeStamp(
    CTAHD          ctahd,         /* CT Access context handle               */
    DWORD          msgtime,       /* Event time stamp                       */
    unsigned long *timesec,       /* Returned seconds                       */
    unsigned      *timems );      /* Returned milliseconds                  */



/*====== SUPERVISORY FUNCTIONS =============================================*/

DWORD NMSAPI adiSetBoardClock(
    CTAHD          ctahd,
    unsigned       board,        /* board number                            */
    unsigned long  time );       /* Host time (typically seconds since 1970)*/


/*====== ADI EVENTS ========================================================*/
                                           /* Call Control Events:            */
#define ADIEVN_INCOMING_CALL       0x12010 /*  incoming call ready to process */
#define ADIEVN_ANSWERING_CALL      0x12011 /*  application answering inbound  */
#define ADIEVN_REJECTING_CALL      0x12012 /*  application rejecting inbound  */
#define ADIEVN_SEIZURE_DETECTED    0x12013 /*  low-level:(in) seizure         */
#define ADIEVN_PLACING_CALL        0x12014 /*  acknowlege of place call cmd   */
#define ADIEVN_CALL_PROCEEDING     0x12015 /*  low-level:(out) dial done      */
#define ADIEVN_REMOTE_ALERTING     0x12016 /*  low-level:(out) ring detected  */
#define ADIEVN_REMOTE_ANSWERED     0x12017 /*  low-level:(out) answer detected*/
#define ADIEVN_CALL_CONNECTED      0x12018 /*  finished,timeout,ADIEVN_CP_ev  */
#define ADIEVN_CALL_DISCONNECTED   0x12019 /*  see ADI_DIS_ reasons           */
#define ADIEVN_CALL_RELEASED       0x1201A /*  acknowlege of release call cmd */
#define ADIEVN_INCOMING_DIGIT      0x1201B /*  low-level:(in) digit in value  */
#define ADIEVN_BILLING_PULSE       0x1201C /*  low-level: billing pulse recv'd*/
#define ADIEVN_ACCEPTING_CALL      0x1201D /*  application accepting inbound  */
#define ADIEVN_BILLING_SET         0x1201E /*  billing option set for answer  */
#define ADIEVN_STATUSINFO_UPDATE   0x1201F /*  async call status info arrived */

#define ADIEVN_OUT_OF_SERVICE      0x12020 /*  detected out-of-service        */
#define ADIEVN_IN_SERVICE          0x12021 /*  detected in service            */
#define ADIEVN_CALLS_BLOCKED       0x12022 /*  request to block now active    */
#define ADIEVN_CALLS_UNBLOCKED     0x12023 /*  request to unblock is complete */

#define ADIEVN_ISDN_PROGRESS       0x12024 /*  low-level: ISDN progress msg   */

                                           /* PBX extensions to call control: */
#define ADIEVN_PLACING_CALL2       0x12028 /*  placing 2nd all or transfer    */
#define ADIEVN_CALL2_CONNECTED     0x12029 /*  three-way connection made      */
#define ADIEVN_CALL2_DISCONNECTED  0x1202A /*  second call failed/aborted     */

                                           /* Warnings and diagnostics:       */
#define ADIEVN_SEQUENCE_ERROR      0x1202B /*  onboard rejected command       */
#define ADIEVN_PROTOCOL_EVENT      0x1202E /*  low-level:diagnostics events   */
#define ADIEVN_PROTOCOL_ERROR      0x1202F /*  warning/informational          */
/*----------------------------------------------------------------------------*/

                                           /* Play and Record Events:         */
#define ADIEVN_PLAY_BUFFER_REQ     0x12030
#define ADIEVN_RECORD_STARTED      0x12031
#define ADIEVN_RECORD_BUFFER_FULL  0x12032

                                           /* Digit Detection Events:         */
#define ADIEVN_DIGIT_BEGIN         0x12040
#define ADIEVN_DIGIT_END           0x12041
#define ADIEVN_MF_DIGIT_BEGIN      0x12048
#define ADIEVN_MF_DIGIT_END        0x12049

                                           /* Call-Progress Events:           */
#define ADIEVN_CP_VOICE            0x12050
#define  ADI_CP_VOICE_BEGIN    0x1         /* selective-terminate CP */
#define  ADI_CP_VOICE_MEDIUM   0x2         /* selective-terminate CP */
#define  ADI_CP_VOICE_LONG     0x3         /* selective-terminate CP */
#define  ADI_CP_VOICE_EXTENDED 0x4         /* selective-terminate CP */
#define  ADI_CP_VOICE_END      0xF         /* selective-terminate CP */
#define ADIEVN_CP_DIALTONE         0x12051 /* will auto-terminate CP */
#define ADIEVN_CP_BUSYTONE         0x12052 /* will auto-terminate CP */
#define ADIEVN_CP_REORDERTONE      0x12053 /* will auto-terminate CP */
#define ADIEVN_CP_RORDTONE         ADIEVN_CP_REORDERTONE /*backwards compat*/
#define ADIEVN_CP_RINGTONE         0x12054 /* selective-terminate CP */
#define ADIEVN_CP_NOANSWER         0x12055
#define ADIEVN_CP_RINGQUIT         0x12056 /* selective-terminate CP */
#define ADIEVN_CP_SIT              0x12057 /* will auto-terminate CP */
#define ADIEVN_CP_CED              0x12059

                                           /* Precise Tone Detection Events:  */
#define ADIEVN_TONE_1_BEGIN        0x12070
#define ADIEVN_TONE_1_END          0x12071
#define ADIEVN_TONE_2_BEGIN        0x12072
#define ADIEVN_TONE_2_END          0x12073
#define ADIEVN_TONE_3_BEGIN        0x12074
#define ADIEVN_TONE_3_END          0x12075

                                           /* Energy Detection Events:        */
#define ADIEVN_SILENCE_DETECTED    0x12080
#define ADIEVN_ENERGY_DETECTED     0x12081

                                           /* Timer Tick Event:               */
#define ADIEVN_TIMER_TICK          0x12090

                                           /* Out-of-Band Signaling Events:   */
#define ADIEVN_SIGNALBIT_CHANGED   0x120A0

                                           /* "Pass-Through" Raw Events:      */
#define ADIEVN_BOARD_EVENT         0x120EE
#define ADIEVN_BOARD_ERROR         0x120FF

                                           /* "Done" Events:                  */
#define ADIEVN_OPENPORT_DONE       0x12101
#define ADIEVN_CLOSEPORT_DONE      0x12102

#define ADIEVN_STARTPROTOCOL_DONE  0x12111
#define ADIEVN_STOPPROTOCOL_DONE   0x12112

#define ADIEVN_PLAY_DONE           0x12130
#define ADIEVN_RECORD_DONE         0x12131

#define ADIEVN_COLLECTION_DONE     0x12140
#define ADIEVN_DTMF_DETECT_DONE    0x12141
#define ADIEVN_MF_DETECT_DONE      0x12142

#define ADIEVN_CP_DONE             0x12150  /* finished,stopped,timeout       */

#define ADIEVN_TONE_1_DETECT_DONE  0x12170
#define ADIEVN_TONE_2_DETECT_DONE  0x12171
#define ADIEVN_TONE_3_DETECT_DONE  0x12172

#define ADIEVN_ENERGY_DETECT_DONE  0x12180

#define ADIEVN_TIMER_DONE          0x12190

#define ADIEVN_PULSE_DONE          0x121A0
#define ADIEVN_SIGNAL_DETECT_DONE  0x121A1
#define ADIEVN_QUERY_SIGNAL_DONE   0x121A2  /* finished,error; size=state */

#define ADIEVN_TONES_DONE          0x121B0
#define ADIEVN_DIAL_DONE           0x121C0

#define ADIEVN_FSK_RECEIVE_DONE    0x121E0
#define ADIEVN_FSK_SEND_DONE       0x121E1


/*====== ADI ERRORS ==========================================================*/

/* ADI-SPECIFIC ERRORS ONLY - see ctaerr.h for generic errors                 */

#define ADIERR_PLAYREC_ACCESS        0x10001 /* Play/record access routine ret*/

/* ADIERR_INVALID_QUEUEID is not used in CTaccess.
 * If you get this error, you're probably linked with adi.lib (libadi.so)
 * instead of adimgr.lib (libadimgr.so).
 */
#define ADIERR_INVALID_QUEUEID       0x10002 /* Bad queue/device id           */

#define ADIERR_UNKNOWN_BOARDTYPE     0x10003 /* AG board type not recognized  */
#define ADIERR_TOO_MANY_BUFFERS      0x10004 /* Async play/recd buff max limit*/
#define ADIERR_INVALID_CALL_STATE    0x10005 /* Invalid request for call state*/

#define ADIERR_CANNOT_CREATE_CHANNEL 0x10006 /* AG driver create channel fail */
#define ADIERR_NO_DSP_PORT           0x10007 /* No input/output for function  */
#define ADIERR_NO_DSP_RESOURCES      0x10008 /* No MIPs or place for function */
#define ADIERR_TOO_MANY_MANAGERS     0x10009 /* Exceeded board mgr limit      */
#define ADIERR_NOT_ENOUGH_RESOURCES  0x1000a /* Requested unavailable resource*/

#define ADIERR_EXTENSION_PARAMETER   0x1000b /* Failed to load extension      */
                                             /* parameter files.              */

/*==========================================================================*/

#ifdef __cplusplus
}
#endif
#endif
/*=============================== [eof] ====================================*/
