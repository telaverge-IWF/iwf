/*****************************************************************************
*                                  ADISPI.H
*
*  This is the include file for the AG Driver Interface (ADI) SPI.
*
*
*  This file is organized as:
*
*    . ADISPI_COMPATLEVEL declaration
*    . PLAY AND RECORD SPIs
*    . DTMF COLLECTION SPIs
*    . TONE AND DTMF GENERATION SPIs
*    . ENERGY AND TONE DETECTION SPIs
*    . CALL CONTROL SPIs
*    . NULL CALL-CONTROL ("NOCC"; LOW-LEVEL) SPIs
*    . MISCELLANEOUS FUNCTIONS SPIs
*    . SUPERVISORY FUNCTIONS SPIs
*
*  Copyright (c)1994-98 Natural MicroSystems Corporation. All rights reserved.
*****************************************************************************/

#ifndef ADISPI_INCLUDED
#define ADISPI_INCLUDED 1

#ifdef __cplusplus
extern "C" {
#endif

   #include "adidef.h"

/*-----------------------------------------------------------------------------
  ADI SPI Compatibility Level Id
    - This id is used to determine runtime compatibility between the
      installed ADI service and clients of the ADI service. Clients can
      be another CT Access Service  (which access ADI functionality
      via the ADI SPI).
    - Clients check this id value via CTAREQSVC_INFO structure passed 
      with dispRegisterService in its service implementation of
      xxxDefineService binding function.
    - SPI compatiblity level value should be incremented when the associated 
      source module changes in a non-backwards compatible way. Refer to the CT 
      Access Service Writer's Manual for more info.
  ---------------------------------------------------------------------------*/
#define ADISPI_COMPATLEVEL                  1

/*-----------------------------------------------------------------------------
  Associated ADI Service SPI function prototypes.
    - For each API call, there is an associated SPI call which performs
      argument marshalling and invokes dispSendCommand() for processing.
    - Note that the only difference between the API signature and the SPI
      signature is the extra "source" argument.
    - Also note that if another service needed to call a TIK Service function,
      it would call the SPI function - NOT THE API FUNCTION!
  ---------------------------------------------------------------------------*/

/*====== PLAY AND RECORD ===================================================*/


/*-------------------------- Encoding SPI function  -------------------*/
DWORD NMSAPI adiSpiGetEncodingInfo  (
    CTAHD          ctahd,         /*   port handle                          */
    unsigned       encoding,      /*   ADI_ENCODE_xxx (see above)           */
    unsigned      *framesize,     /*   Returned frame size                  */
    unsigned      *datarate,      /*   Returned avg bytes/sec               */
    unsigned      *maxbufsize,    /*   Returned mMaximum buffer size        */
    WORD           source         /* calling application/service source id  */
                                    );

/*-------------------------- Play SPI function  -----------------------*/
DWORD NMSAPI adiSpiStartPlaying (
    CTAHD            ctahd,
    unsigned         encoding,  /* encoding types                           */
    ADI_PLAY_ACCESS  access,    /* access routine                           */
    void            *accarg,    /* passed to access() as is.                */
    ADI_PLAY_PARMS  *parms,     /* pointers to play parameters              */
    WORD             source     /* calling application/service source id    */
                                );

DWORD NMSAPI adiSpiPlayFromMemory (
    CTAHD           ctahd,
    unsigned        encoding,    /* encoding types                           */
    void           *buffer,      /* pointer to buffer area with data         */
    unsigned        bufsiz,      /* size of the buffer in bytes              */
    ADI_PLAY_PARMS *parms,       /* play parameters                          */
    WORD            source       /* calling application/service source id    */
                               );

DWORD NMSAPI adiSpiPlayAsync (
    CTAHD           ctahd,
    unsigned        encoding,    /* encoding types                           */
    void           *buffer,      /* pointer to buffer area with data         */
    unsigned        bufsiz,      /* size of the buffer in bytes              */
    unsigned        flags,       /* LAST_BUFFER_SUBMITTED                    */
    ADI_PLAY_PARMS *parms,       /* play parameters                          */
    WORD            source       /* calling application/service source id    */
                             );

DWORD NMSAPI adiSpiSubmitPlayBuffer (
    CTAHD          ctahd,
    void          *buffer,      /* pointer to buffer area with data         */
    unsigned       bufsiz,      /* size of the buffer in bytes              */
    unsigned       flags,       /* LAST_BUFFER_SUBMITTED                    */
    WORD           source       /* calling application/service source id    */
                                    );

DWORD NMSAPI adiSpiModifyPlayGain (
    CTAHD          ctahd,
    int            gain,     /* New gain (db)                            */
    WORD           source    /* calling application/service source id    */
                                  );

DWORD NMSAPI adiSpiModifyPlaySpeed  (
    CTAHD          ctahd,
    unsigned       speed,    /* New speed (percent)                      */
    WORD           source    /* calling application/service source id    */
                                    );

DWORD NMSAPI adiSpiGetPlayStatus (
    CTAHD            ctahd,     /* handle as obtained from adiOpenPort()    */
    ADI_PLAY_STATUS *ps,        /* passed pointer to returned status info   */
    unsigned         size,      /* passed byte size of above                */
    WORD             source     /* calling application/service source id    */
                                 );

DWORD NMSAPI adiSpiStopPlaying (
    CTAHD  ctahd,               /* handle as obtained from adiOpenPort()    */
    WORD   source               /* calling application/service source id    */
                               );

/*-------------------------- Record SPI function  ---------------------*/
DWORD NMSAPI adiSpiStartRecording   (
    CTAHD             ctahd,
    unsigned          encoding,  /* encoding type                            */
    unsigned          maxmsec,   /* max recoding time in msec; 0=unlimited   */
    ADI_RECORD_ACCESS access,    /* access routine                           */
    void             *accarg,    /* passed to access() as is.                */
    ADI_RECORD_PARMS *parms,     /* pointers to record parameters            */
    WORD              source     /* calling application/service source id  */
                                    );

DWORD NMSAPI adiSpiRecordToMemory   (
    CTAHD             ctahd,
    unsigned          encoding,  /* encoding types                           */
    void             *buffer,    /* pointer to buffer area with data         */
    unsigned          bufsiz,    /* size of the buffer in bytes              */
    ADI_RECORD_PARMS *parms,     /* record parameters                        */
    WORD              source     /* calling application/service source id    */
                                    );

DWORD NMSAPI adiSpiRecordAsync   (
    CTAHD             ctahd,
    unsigned          encoding,  /* encoding type                            */
    unsigned          maxmsec,   /* max recoding time in msec; 0=unlimited   */
    void             *buf1,      /* pointer to buffer area with data         */
    unsigned          bufsiz,    /* size of the buffer in bytes              */
    ADI_RECORD_PARMS *parms,     /* pointers to record parameters            */
    WORD              source     /* calling application/service source id    */
                                 );

DWORD NMSAPI adiSpiSubmitRecordBuffer  (
    CTAHD          ctahd,
    void          *buffer,      /* pointer to buffer area with data         */
    unsigned       bufsiz,      /* size of the buffer in bytes              */
    WORD           source       /* calling application/service source id    */
                                       );

DWORD NMSAPI adiSpiGetRecordStatus  (
    CTAHD              ctahd,
    ADI_RECORD_STATUS *ps,       /* passed pointer to returned status info   */
    unsigned           size,     /* passed byte size of above                */
    WORD              source     /* calling application/service source id    */
                                    );

DWORD NMSAPI adiSpiStopRecording (
    CTAHD ctahd,                  /* handle as obtained from adiOpenPort()    */
    WORD  source                  /* calling application/service source id    */
                                 );


/*====== DTMF COLLECTION ===================================================*/
DWORD NMSAPI adiSpiGetDigit   (
    CTAHD    ctahd,
    char    *digit,             /* pointer to returned character            */
    WORD     source             /* calling application/service source id    */
                              );

DWORD NMSAPI adiSpiPeekDigit  (
    CTAHD    ctahd,
    char    *digit,             /* pointer to returned character            */
    WORD     source             /* calling application/service source id    */
                              );

DWORD NMSAPI adiSpiFlushDigitQueue  (
     CTAHD ctahd,
     WORD  source                 /* calling application/service source id    */
                                    );

DWORD NMSAPI adiSpiCollectDigits (
    CTAHD              ctahd,
    char              *buffer,   /* user supplied buffer of digits           */
    unsigned           howmany,  /* how many digits to collect               */
    ADI_COLLECT_PARMS *parms,    /* parameters used for digits collection    */
    WORD               source    /* calling application/service source id    */
                                 );

DWORD NMSAPI adiSpiStopCollection   (
    CTAHD ctahd,
    WORD  source                 /* calling application/service source id    */
                                    );

/*====== TONE AND DTMF GENERATION ==========================================*/

DWORD NMSAPI adiSpiStartTones (
    CTAHD          ctahd,
    unsigned       tonecount,    /* number of tones to be played             */
    ADI_TONE_PARMS tones[],      /* pointers to tone specifications          */
    WORD           source        /* calling application/service source id    */
                              );

DWORD NMSAPI adiSpiStartDTMF  (
    CTAHD           ctahd,
    char           *digits,      /* string of digits to be played            */
    ADI_DTMF_PARMS *parms,       /* pointer to DTMF parameters               */
    WORD            source       /* calling application/service source id    */
                              );

DWORD NMSAPI adiSpiStopTones  (
    CTAHD ctahd,
    WORD  source                 /* calling application/service source id  */
                              );

/*====== MF DETECTION =======================================================*/

DWORD NMSAPI adiSpiStartMFDetector  (
    CTAHD           ctahd,
    unsigned        mftype,       /*   used-specified MF type (ADI_MF_xxx_  */
    WORD            source        /* calling application/service source id  */
                                    );

DWORD NMSAPI adiSpiStopMFDetector   (
    CTAHD ctahd,
    WORD  source                  /* calling application/service source id  */
                                    );

/*====== ENERGY AND TONE DETECTION =========================================*/

DWORD NMSAPI adiSpiStartEnergyDetector (
    CTAHD             ctahd,
    unsigned          energyqual,  /*   qualification time for energy        */
    unsigned          silencequal, /*   qualification time for silence       */
    ADI_ENERGY_PARMS *parms,       /*   pointer to energy parameters         */
    WORD              source       /* calling application/service source id  */
                                       );

DWORD NMSAPI adiSpiStopEnergyDetector  (
    CTAHD ctahd,
    WORD              source       /* calling application/service source id  */
                                       );

DWORD NMSAPI adiSpiStartToneDetector   (
    CTAHD           ctahd,
    unsigned        toneid,       /*   used-specified tone id (index)       */
    unsigned        frequency1,   /*   frequency to detect                  */
    unsigned        bandwidth1,   /*   bandwidth                            */
    unsigned        frequency2,   /*   2nd frequency to detect (dualtones)  */
    unsigned        bandwidth2,   /*   2nd bandwidth                        */
    ADI_TONEDETECT_PARMS *parms,  /*   pointer to audio parameters          */
    WORD  source                  /* calling application/service source id  */
                                       );

DWORD NMSAPI adiSpiStopToneDetector (
    CTAHD    ctahd,
    unsigned toneid,
    WORD  source                  /* calling application/service source id  */
                                    );

/*====== CALL CONTROL ======================================================*/

DWORD NMSAPI adiSpiStartProtocol (
    CTAHD             ctahd,
    char             *tcpname,   /* name of TCP already loaded on the board  */
    void             *tcpparms,  /* TCP specific parameters                  */
    ADI_START_PARMS  *selparm,   /* Start parameters or NULL for defaults    */
    WORD              source     /* calling application/service source id    */
                                 );

DWORD NMSAPI adiSpiStopProtocol  (
    CTAHD ctahd,
    WORD  source                /* calling application/service source id    */
                                 );

DWORD NMSAPI adiSpiSetBilling (
    CTAHD            ctahd,
    unsigned         rate,
    WORD  source                /* calling application/service source id    */
                              );

DWORD NMSAPI adiSpiAcceptCall (
    CTAHD            ctahd,
    unsigned         mode,     /* what to play while accepting              */
    void            *reserved, /* for future use                            */
    WORD             source    /* calling application/service source id     */
                              );

DWORD NMSAPI adiSpiAnswerCall (
    CTAHD            ctahd,
    unsigned         nrings,    /* number of rings before answering         */
    WORD             source     /* calling application/service source id    */
                              );

DWORD NMSAPI adiSpiRejectCall (
    CTAHD  ctahd,
    int    reason,
    WORD   source               /* calling application/service source id    */
                              );

DWORD NMSAPI adiSpiReleaseCall   (
    CTAHD    ctahd,
    WORD     source             /* calling application/service source id    */
                                 );

DWORD NMSAPI adiSpiBlockCalls
    (
    CTAHD  ctahd,
    WORD   source               /* calling application/service source id    */
    );

DWORD NMSAPI adiSpiUnBlockCalls
    (
    CTAHD  ctahd,
    WORD   source               /* calling application/service source id    */
    );

DWORD NMSAPI adiSpiAcceptIncomingAddress
    ( 
    CTAHD  ctahd,
    WORD   source               /* calling application/service source id    */
    );

DWORD NMSAPI adiSpiPlaceCall  (
    CTAHD                ctahd,
    char                *digitstr,   /* extended digit string                */
    ADI_PLACECALL_PARMS *parms,      /* place call param or NULL for defaults*/
    WORD                 source   /* calling application/service source id    */
                              );

DWORD NMSAPI adiSpiTransferCall  (
    CTAHD                ctahd,
    char                *digitstr,
    unsigned             method,
    ADI_PLACECALL_PARMS *parms,
    WORD                 source  /* calling application/service source id    */
                                 );

DWORD NMSAPI adiSpiPlaceSecondCall  (
    CTAHD               ctahd,
    char                *digitstr,
    ADI_PLACECALL_PARMS *parms,
    WORD                 source  /* calling application/service source id    */
                                    );

DWORD NMSAPI adiSpiReleaseSecondCall   (
    CTAHD ctahd,
    WORD  source                 /* calling application/service source id    */
                                       );

DWORD NMSAPI adiSpiGetCallStatus (
    CTAHD            ctahd,
    ADI_CALL_STATUS *ci,        /* pointer to call info structure           */
    unsigned         cisize,    /* size of the above structure              */
    WORD             source     /* calling application/service source id    */
                                 );

DWORD NMSAPI adiSpiSetExtendedArgs
    (
    CTAHD            ctahd,     /* handle as obtained from adiOpenPort()    */
    void            *p,         /* pointer to suitable mem area             */
    unsigned         size,      /* passed byte size of above                */
    WORD             source     /* calling application/service source id    */
    );

/*====== NULL CALL-CONTROL ("NOCC",LOW-LEVEL) ==============================*/

DWORD NMSAPI adiSpiStartSignalDetector (
    CTAHD    ctahd,
    unsigned initial,           /* initial state                            */
    unsigned mask,              /* mask                                     */
    unsigned timeon,            /* deglitching on                           */
    unsigned timeoff,           /* deglitching off                          */
    WORD     source             /* calling application/service source id    */
                                       );

DWORD NMSAPI adiSpiStopSignalDetector  (
    CTAHD ctahd,
    WORD  source                /* calling application/service source id    */
                                       );

DWORD NMSAPI adiSpiQuerySignalState (
    CTAHD ctahd,
    WORD  source                /* calling application/service source id    */
                                    );

DWORD NMSAPI adiSpiStartDTMFDetector   (
    CTAHD                 ctahd,
    ADI_DTMFDETECT_PARMS *parms, /* DTMF detection parameters                */
    WORD                  source /* calling application/service source id    */
                                       );

DWORD NMSAPI adiSpiStopDTMFDetector (
    CTAHD ctahd,
    WORD  source                 /* calling application/service source id    */
                                    );

DWORD NMSAPI adiSpiStartPulse (
    CTAHD    ctahd,
    unsigned signal,            /* signaling bits                           */
    unsigned timeon,            /* duration ON                              */
    unsigned timeoff,           /* duration OFF                             */
    WORD     source             /* calling application/service source id    */
                              );

DWORD NMSAPI adiSpiAssertSignal  (
    CTAHD    ctahd,
    unsigned pattern,           /* what to send                             */
    WORD     source             /* calling application/service source id    */
                                 );

DWORD NMSAPI adiSpiStartTimer (
    CTAHD    ctahd,
    unsigned timeout,           /* msec                                     */
    unsigned count,             /* iterations                               */
    WORD     source             /* calling application/service source id    */
                              );

DWORD NMSAPI adiSpiStopTimer  (
   CTAHD ctahd,
   WORD  source                 /* calling application/service source id    */
                              );

DWORD NMSAPI adiSpiStartDial  (
    CTAHD           ctahd,
    char           *digits,      /* string of digits to be played            */
    ADI_DIAL_PARMS *parms,
    WORD            source       /* calling application/service source id    */
                              );

DWORD NMSAPI adiSpiStopDial   (
    CTAHD ctahd,
    WORD  source                 /* calling application/service source id    */
                              );

DWORD NMSAPI adiSpiStartCallProgress   (
    CTAHD               ctahd,
    ADI_CALLPROG_PARMS *parms,   /*   parameters                           */
    WORD                source   /* calling application/service source id  */
                                       );

DWORD NMSAPI adiSpiStopCallProgress (
    CTAHD ctahd,
    WORD  source                 /* calling application/service source id  */
                                    );

/*--------------- FSK ------------------------------------------------------*/
DWORD NMSAPI adiSpiStartSendingFSK  (
    CTAHD           ctahd,        /* Port/context handle                    */
    void           *buffer,       /* Address of buffer of bytes to send     */
    unsigned        bufsiz,       /* Buffer size                            */
    ADI_FSKSEND_PARMS *parms,     /* FSK Send Parameters                    */
    WORD               source     /* calling application/service source id  */
                                    );

DWORD NMSAPI adiSpiStartReceivingFSK   (
    CTAHD                 ctahd,  /* Port/context handle                    */
    void                 *buffer, /* Address of buffer of bytes to send     */
    unsigned              bufsiz, /* Buffer size                            */
    ADI_FSKRECEIVE_PARMS *parms,  /* FSK Receive Parameters                 */
    WORD                  source  /* calling application/service source id  */
                                       );

DWORD NMSAPI adiSpiStopSendingFSK   (
    CTAHD ctahd,
    WORD  source                  /* calling application/service source id  */
                                    );

DWORD NMSAPI adiSpiStopReceivingFSK (
    CTAHD ctahd,
    WORD  source                  /* calling application/service source id  */
                                    );

/*====== MISCELLANEOUS FUNCTIONS ===========================================*/

DWORD NMSAPI adiSpiGetContextInfo   (
    CTAHD             ctahd,    /* NULL is ok if port has not been opened?  */
    ADI_CONTEXT_INFO *data,     /* pointer to call info structure           */
    unsigned          size,     /* size of the above structure              */
    WORD              source    /* calling application/service source id    */
                                    );

DWORD NMSAPI adiSpiSetTCPTrace   (
    CTAHD    ctahd,
    unsigned value,             /* trace value                              */
    WORD     source             /* calling application/service source id    */
                                 );


DWORD NMSAPI adiSpiGetBoardSlots (
    CTAHD        ctahd,     /* CTA context handle                       */
    unsigned     board,     /* AG board number                          */
    unsigned     mode,      /* ADI_VOICE_DUPLEX, ADI_FULL_DUPLEX        */
    unsigned     maxslot,   /* Maximum number of entries in array       */
    ADI_TIMESLOT *slotlist, /* Returned array of timeslots              */
    unsigned     *numslots, /* returned number of entries               */
    WORD          source    /* calling application/service source id    */
                                 );

DWORD NMSAPI adiSpiGetBoardInfo  (
    CTAHD           ctahd,       /* CTA context handle                       */
    unsigned        board,       /* AG board number                          */
    unsigned        size,        /* Size of caller's structure; ret size in  */
    ADI_BOARD_INFO *boardinfo,   /*  the returned structure.                 */
    WORD            source       /* calling application/service source id    */
                                 );

DWORD NMSAPI adiSpiGetEEPromData (
    CTAHD            ctahd,       /* CTA context handle                       */
    unsigned         board,       /* AG board number                          */
    unsigned         size,        /* Size of caller's structure; ret size in  */
    ADI_EEPROM_DATA *eepromdata,  /* the returned structure.                  */
    WORD             source       /* calling application/service source id    */
                                 );

DWORD NMSAPI adiSpiGetTimeStamp  (
    CTAHD          ctahd,     /* CTA context handle                         */
    DWORD          msgtime,   /* Event time stamp                           */
    unsigned long *timesec,   /* Returned seconds                           */
    unsigned      *timems,    /* Returned milliseconds                      */
    WORD           source     /* calling application/service source id      */
                                 );

DWORD NMSAPI adiSpiSetBoardClock (
    CTAHD         ctahd,        /* NULL is ok if port has not been opened?  */
                                /* NO IT IS NOT IF THIS IS THE ADI SERVICE
                                   OF CT ACCESS ???                         */
    unsigned      board,        /* device or queue id                       */
    unsigned long time,         /* Host time (typically seconds since 1970) */
    WORD          source        /* calling application/service source id    */
                                 );

#ifdef __cplusplus
}
#endif
#endif
/*=============================== [eof] ====================================*/
