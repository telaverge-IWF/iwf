/*****************************************************************************
 *                                  VCEDEF.H
 *
 *  This is the include file for the Voice Integration Manager (VCE) API.
 *
 * Copyright (c)1996 Natural MicroSystems Corporation. All rights reserved.
 *****************************************************************************/

#ifndef VCEDEF_INCLUDED
#define VCEDEF_INCLUDED 1

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NMSTYPES_INCLUDED
#include "nmstypes.h"
#endif

#ifndef CTADEF_INCLUDED
#include "ctadef.h"
#endif

#ifdef ADIEXT
#undef ADIEXT
#endif

/*-----------------------------------------------------------------------------
  VCE Version Ids  
  - These id's are used to identify the revision level of this service. 
  ---------------------------------------------------------------------------*/
#define VCE_MAJORREV                        1
#define VCE_MINORREV                        0


/*-----------------------------------------------------------------------------
  VCE API Compatibility Level Id
  - This id is used to determine runtime compatibility between the
  installed VCE service and clients of the VCE service. Clients can
  be a CT Access application which accesses VCE functionality
  via the VCE API.
  - Clients(CT Access application) #include this file into their code and, 
  therefore, insert "hard coded" values for each VCE compat level
  into their client code.
  - The API_COMPATLEVEL is used by CT Access application developers who
  want to check the "hard coded" value in their application against the
  "hard coded" value in the installed VCE service (as determined
  via ctaGetServiceVersion() will be available in CT Access Version 2.1).
  - API compatibility level value should be incremented when the associated
  source module changes in a non-backwards compatible way. Refer to the CT 
  Access Service Writer's Manual for more info.
  ---------------------------------------------------------------------------*/
#define VCEAPI_COMPATLEVEL                  0


/*====== COMMON DEFINES AND STRUCTURES =====================================*/

#define VCE_SVCID 3

typedef DWORD VCEHD;
typedef DWORD VCEPROMPTHD ;

typedef struct
{
    VCEHD    vh ;
    unsigned message;
} VCE_MESSAGE ;


typedef struct
{
    DWORD offset ;
    DWORD bytes  ;
} VCE_SEGMENT ;


typedef struct           /* Describes an open voice file or memory object */
{
    DWORD    size ;      /* Size of this structure                     */
    DWORD    filetype ;  /* file type; 0 if memory                     */
    DWORD    openmode ;  /* VCE_PLAY_ONLY or VCE_PLAY_RECORD           */
    DWORD    encoding ;  /* Voice encoding of all message in the file  */
    CTAHD    ctahd ;     /* Context in which the object was opened     */
} VCE_OPEN_INFO ;


typedef struct
{
    DWORD  size ;           /* size of this struct              */
    DWORD  numcurrent;      /* size of current list              */
    DWORD  position ;       /* current position (ms)            */
    DWORD  reasondone;
    DWORD  auxerror ;
    DWORD  function;        /* active function                  */
    DWORD  underruns;
    DWORD  currentgain ;
    DWORD  currentspeed ;
    DWORD  encoding;
    DWORD  framesize;
    DWORD  frametime;
} VCE_CONTEXT_INFO ;


#pragma pack(2)
/****************************************************************************/
/* VOX Voice file header structure.                                         */

typedef struct
{
    WORD  vtype;       /* encoding                                    */
    WORD  totlidx;     /* total # of indices in file                  */
    WORD  usedidx;     /* total # of indices in use                   */
    WORD  actvidx;     /* # of active indices (excluding erased)      */
    WORD  freeidx;     /* # of free indices for future assignment     */
    WORD  highmsg;     /* highest msg # used                          */
    DWORD totlbyt;     /* total # of bytes                            */
    DWORD totlfrm;     /* total # of frames                           */
    char  unused[12];  /* reserved                                    */
}
#ifdef SOLARIS_SPARC
__attribute__((packed))
#endif
VOXHDR;

/*****************************************************************************
  VOX Index structure.  A pool of 'totlidx' indices reside in the file
  immediately after the header.  One index is needed for each separate piece
  of recorded speech in the file.  First are 'actvidx' indices describing
  the segments of speech currently belonging to messages.  They are sorted
  by message number.  Within a message number they are arranged in the order
  they are played.  Next are 'usedidx-actvidx' indices which point to segments
  which used to belong to a message, but have been erased.  These are in order
  of their position in the file. These pieces get reused on subsequent records.
  Finally 'freeidx' indices are unused and available for assignment.
 */

typedef struct
{
    WORD   msgno;             /* Integer message number of segment           */
    /*  High bit (0x8000) indicates message text   */
    DWORD  strtbyte;          /* Starting byte position in file              */
    DWORD  nframes;           /* Number of frames in segment                 */
}
#ifdef SOLARIS_SPARC
__attribute__((packed))
#endif
VOXIDX;

#define VCEVOX_MAX_MESSAGE  0x7fff

#define VCEVOX_DFLTIDX      250  /* Default number of indices in created file */

#pragma pack()


/* Values for 'function' field in status */
#define VCE_PLAY   1
#define VCE_RECORD 2


/* Special message values */
#define VCE_UNDEFINED_MESSAGE 0xffffffff
#define VCE_ALL_MESSAGES      0xfffffffe


/* Special parameter value */
#define VCE_CURRENT_VALUE 0x80000000


/* Miscellaneous constants */
#define VCE_FILETYPE_AUTO 0
#define VCE_FILETYPE_VOX  1
#define VCE_FILETYPE_WAVE 2
#define VCE_FILETYPE_FLAT 3

#define VCE_PLAY_ONLY      257
#define VCE_PLAY_RECORD    258

#define VCE_NO_TIME_LIMIT 0xffffffff

#define VCE_SEEK_SET    0
#define VCE_SEEK_CUR    1
#define VCE_SEEK_END    2

#define VCE_INSERT       1
#define VCE_OVERWRITE    2


/* ADI Encodings are re-defined here for convenience */
#define VCE_ENCODE_NMS_16    1   /* ADI_ENCODE_NMS_16   */
#define VCE_ENCODE_NMS_24    2   /* ADI_ENCODE_NMS_24   */
#define VCE_ENCODE_NMS_32    3   /* ADI_ENCODE_NMS_32   */
#define VCE_ENCODE_NMS_64    4   /* ADI_ENCODE_NMS_64   */

#define VCE_ENCODE_MULAW    10   /* ADI_ENCODE_MULAW    */
#define VCE_ENCODE_ALAW     11   /* ADI_ENCODE_ALAW     */
#define VCE_ENCODE_PCM8M16  13   /* ADI_ENCODE_PCM8M16  */

#define VCE_ENCODE_OKI_24   14   /* ADI_ENCODE_OKI_24   */
#define VCE_ENCODE_OKI_32   15   /* ADI_ENCODE_OKI_32   */

#define VCE_ENCODE_PCM11M8  16   /* ADI_ENCODE_PCM11M8  */
#define VCE_ENCODE_PCM11M16 17   /* ADI_ENCODE_PCM11M16 */

#define VCE_ENCODE_G726     20   /* ADI_ENCODE_G726     */

#define VCE_ENCODE_IMA_24   22   /* ADI_ENCODE_IMA_24   */
#define VCE_ENCODE_IMA_32   23   /* ADI_ENCODE_IMA_32   */

/*------- DTMF digits for bit masks ----------------------------------------*/
#define VCE_DIGIT_0     0x0001
#define VCE_DIGIT_1     0x0002
#define VCE_DIGIT_2     0x0004
#define VCE_DIGIT_3     0x0008
#define VCE_DIGIT_4     0x0010
#define VCE_DIGIT_5     0x0020
#define VCE_DIGIT_6     0x0040
#define VCE_DIGIT_7     0x0080
#define VCE_DIGIT_8     0x0100
#define VCE_DIGIT_9     0x0200
#define VCE_DIGIT_STAR  0x0400
#define VCE_DIGIT_POUND 0x0800
#define VCE_DIGIT_A     0x1000
#define VCE_DIGIT_B     0x2000
#define VCE_DIGIT_C     0x4000
#define VCE_DIGIT_D     0x8000
#define VCE_DIGIT_ANY   0xFFFF
#define VCE_DIGIT_0_9   0x03FF
#define VCE_DIGIT_A_D   0xF000

#ifdef SCO
#define max(a, b)  (((a) > (b)) ? (a) : (b))
#define min(a, b)  (((a) < (b)) ? (a) : (b))
#endif


/*====== Function Prototypes ============================================*/

/*-----------------------------------------------------------------------------
  Open/Create/Close
  -----------------------------------------------------------------------------*/

DWORD NMSAPI vceOpenFile (CTAHD ctahd,  const char *filename, unsigned filetype,
                          unsigned openmode, unsigned encoding, VCEHD *vh);
DWORD NMSAPI vceCreateFile(CTAHD ctahd, const char *filename, unsigned filetype,
                           unsigned encoding, const void *fileinfo, VCEHD *vh);

/* File info for creating VOX file */
typedef struct
{
    DWORD size ;       /* size of this structure   */
    DWORD maxindex ;   /* max indices (default 48) */
} VCE_CREATE_VOX ;

DWORD NMSAPI vceOpenMemory (CTAHD ctahd, BYTE *address, unsigned bytes,
                            unsigned encoding, VCEHD *vh);
DWORD NMSAPI vceCreateMemory (CTAHD ctahd, unsigned bytes, unsigned encoding,
                              VCEHD *vh);
DWORD NMSAPI vceAssignHandle (CTAHD ctahd, int filedes, unsigned encoding,
                              VCEHD *vh);
DWORD NMSAPI vceDefineMessages (VCEHD vh, const VCE_SEGMENT segments[],
                                unsigned msgcount);
DWORD NMSAPI vceClose (VCEHD vh);

/*-----------------------------------------------------------------------------
  Playing and Rcording Functions
  -----------------------------------------------------------------------------*/

#define VCE_PLAY_PARMID 0x30001
typedef struct
{                                 /* parameters related to adiStartPlaying: */
    DWORD size ;                  /*   size of this structure               */
    DWORD DTMFabort;              /*   abort on DTMF; see descripton above  */
    INT32 gain;                   /*   playing gain in dB                   */
    DWORD speed;                  /*   initial speed in percent             */
    DWORD maxspeed;               /*   maximum play speed in percent        */
} VCE_PLAY_PARMS;


DWORD NMSAPI vcePlayMessage (VCEHD vh, unsigned message,
                             const VCE_PLAY_PARMS *parms);
DWORD NMSAPI vcePlay (CTAHD ctahd, unsigned maxtime,
                      const VCE_PLAY_PARMS *parms);
DWORD NMSAPI vcePlayList (VCEHD vh, const unsigned msglist[], unsigned count,
                          const VCE_PLAY_PARMS *parms);
DWORD NMSAPI vceSetPlayGain  (CTAHD ctahd, int dB);
DWORD NMSAPI vceSetPlaySpeed (CTAHD ctahd, unsigned speed) ;

#define VCE_RECORD_PARMID 0x30002
typedef struct
{                                 /* parameters related to adiStartPlaying: */
    DWORD size ;                  /*   size of this structure               */
    DWORD DTMFabort;              /*   abort on DTMF; see descripton above  */
    INT32 gain;                   /*   playing gain in dB                   */
    DWORD novoicetime;            /*   length of initial silence to stop    */
    /*     recording (ms); use 0 to deactivate*/
    /*     initial silence detection.         */
    DWORD silencetime;            /*   length of silence to stop recording  */
    /*     after voice has been detected (ms);*/
    /*     use 0 to deactivate.               */
    INT32 silenceampl;            /*   qualif level for silence (dBm)       */
    /*-[Beep for record]----------------------*/
    DWORD beepfreq;               /*   beep frequency (Hz)                  */
    INT32 beepampl;               /*   beep amplitude (dBm)                 */
    DWORD beeptime;               /*   beep time (ms) 0=no beep             */
    /*--[AGC parms]---------------------------*/
    DWORD AGCenable;              /*   enable AGC; use 1 to activate        */
} VCE_RECORD_PARMS;

DWORD NMSAPI vceRecordMessage (VCEHD vh, unsigned message, unsigned maxtime,
                               const VCE_RECORD_PARMS *parms);

DWORD NMSAPI vceRecord (CTAHD ctahd, unsigned maxtime, unsigned insertmode,
                        const VCE_RECORD_PARMS *parms);
DWORD NMSAPI vceStop  (CTAHD ctahd );


/* prototype for _vceParmDescTable[] - previously declared in vceparm.h */
extern const CTAPARM_DESC * const _vceParmDescTable[];


/*-----------------------------------------------------------------------------
  Query Functions
  -----------------------------------------------------------------------------*/
DWORD NMSAPI vceGetCurrentList (CTAHD ctahd, VCE_MESSAGE msglist[],
                                unsigned maxcount, unsigned *actualcount);
DWORD NMSAPI vceGetCurrentSize (CTAHD ctahd, unsigned *actualsize);

DWORD NMSAPI vceGetEncodingInfo  (CTAHD ctahd, unsigned encoding,
                                  unsigned *framesize, unsigned *frametime);

DWORD NMSAPI vceGetHighMessageNumber   (VCEHD vh, unsigned *highmsg) ;

DWORD NMSAPI vceGetMessageSize (VCEHD vh, unsigned message, unsigned *msgsize);

DWORD NMSAPI vceGetOpenInfo (VCEHD vh, VCE_OPEN_INFO *openinfo, unsigned size);

DWORD NMSAPI vceGetContextInfo (CTAHD ctahd, VCE_CONTEXT_INFO *contextinfo,
                                unsigned usersize);

DWORD NMSAPI vceGetUniqueMessageNumber (VCEHD vh, unsigned *message) ;


/*-----------------------------------------------------------------------------
  Edit Functions
  -----------------------------------------------------------------------------*/
DWORD NMSAPI vceCopyMessage ( VCEHD srcvh, unsigned  srcmsg,
                              VCEHD destvh, unsigned  destmsg);
DWORD NMSAPI vceEraseMessage (VCEHD vh, unsigned  message);
DWORD NMSAPI vceErase (CTAHD ctahd, unsigned milliseconds, unsigned *actualms);
DWORD NMSAPI vceRead (CTAHD ctahd, BYTE *buffer, unsigned bytes,
                      unsigned *bytesread);
DWORD NMSAPI vceWrite (CTAHD ctahd, const BYTE *buffer, unsigned bytes,
                       unsigned insertmode, unsigned *byteswritten);
DWORD NMSAPI vceConvertMessage (VCEHD srcvh, unsigned  srcmsg,
                                VCEHD destvh, unsigned destmsg, int gain) ;

/*-----------------------------------------------------------------------------
  Message Text (Vox files only)
  -----------------------------------------------------------------------------*/
DWORD NMSAPI vceCopyMessageText (VCEHD srcvh, unsigned  srcmsg,
                                 VCEHD destvh, unsigned  destmsg);
DWORD NMSAPI vceReadMessageText (VCEHD vh, unsigned message, void *buffer,
                                 unsigned bytes, unsigned *bytesread);
DWORD NMSAPI vceWriteMessageText (VCEHD vh, unsigned message, void *buffer,
                                  unsigned bytes);


/*-----------------------------------------------------------------------------
  Position Functions
  -----------------------------------------------------------------------------*/
DWORD NMSAPI vceSetPosition (CTAHD ctahd, int msec, unsigned seekmode,
                             unsigned *actual);
DWORD NMSAPI vceSetCurrentMessage (VCEHD vh, unsigned message);
DWORD NMSAPI vceSetCurrentList (CTAHD ctahd, VCE_MESSAGE msglist[],
                                unsigned count);

/*-----------------------------------------------------------------------------
  WAVE Functions
  -----------------------------------------------------------------------------*/
typedef struct
{
    DWORD  size ;          /* Size of this structure plus format-specific data*/
    DWORD  format;         /* WAVE format type */
    DWORD  nchannels;      /* number of channels */
    DWORD  samplespersec;  /* sample rate */
    DWORD  datarate;       /* avg bytes per second */
    DWORD  blocksize;      /* block size of data */
    DWORD  bitspersample;  /* Number of bits per sample of mono  */
} VCE_WAVE_INFO ;

DWORD NMSAPI vceGetWaveInfo (CTAHD ctahd, unsigned encoding,
                             VCE_WAVE_INFO *waveinfo, unsigned size);
DWORD NMSAPI vceSetWaveInfo (CTAHD ctahd, unsigned encoding,
                             VCE_WAVE_INFO *info);


/*-----------------------------------------------------------------------------
  Prompt Functions
  -----------------------------------------------------------------------------*/
DWORD NMSAPI vceLoadPromptRules (CTAHD ctahd, char *name,
                                 VCEPROMPTHD *prompthandle );
DWORD NMSAPI vceBuildPromptList (VCEPROMPTHD prompthandle, unsigned method,
                                 char *text, unsigned list[],
                                 unsigned maxcount, unsigned *actualcount);
DWORD NMSAPI vceUnloadPromptRules( VCEPROMPTHD prompthandle );


/*-----------------------------------------------------------------------------
  Voice Message Service EVENTS
  -----------------------------------------------------------------------------*/
#define VCEEVN_PLAY_DONE            0x32101   /* value = reason, size = msec */
#define VCEEVN_RECORD_DONE          0x32102   /* value = reason, size = msec */

/*-----------------------------------------------------------------------------
  ERRORS
  -----------------------------------------------------------------------------*/
#define VCEERR_INVALID_MESSAGE      0x30000
#define VCEERR_NO_MESSAGE           0x30001
#define VCEERR_INVALID_OPERATION    0x30002
#define VCEERR_PLAY_ONLY            0x30003
#define VCEERR_NO_SPACE             0x30004
#define VCEERR_MIXED_ENCODING       0x30005
#define VCEERR_WRONG_FILE_TYPE      0x30006
#define VCEERR_WRONG_ENCODING       0x30007
#define VCEERR_OUT_OF_INDICES       0x30008
#define VCEERR_UNSUPPORTED_ENCODING 0x30009
#define VCEERR_BAD_PROMPT_COMMAND   0x3000A
#define VCEERR_PROMPT_BUILD_FAIL    0x3000B
#define VCEERR_CONVERSION_FAILED    0x3000C

#ifdef __cplusplus
}
#endif
#endif /* ifndef VCEDEF_INCLUDED  */


