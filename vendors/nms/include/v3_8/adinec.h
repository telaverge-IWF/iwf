/******************************************************************************
*                                  ADINEC.H
*
*  This is the C language header file defining the CT Access parameters of 
*  Natural MicroSystems NEC protocol. 
*
*  #include in any application program that needs to perform CT Access
*  parameter functions involving the NEC0 TCP parameters.
*
*  Copyright (c)2001 Natural MicroSystems Corporation. All rights reserved.
*****************************************************************************/

#ifndef ADINECPARM_DEFINED           
#define ADINECPARM_DEFINED           

#include "ctadef.h"

#ifdef __cplusplus                   
extern "C"                           
{                                    
#endif  


#define    ADI_NEC_PARMID    0x10029

typedef struct                    /* passed with adiStartProtocol("NEC#")    */
{
    DWORD size;                   /*    */
    WORD optionflags;             /*  0 optional TCP behavior */

/*  Note:  These ring times are for ring pattern asserted on the signaling bits */

    WORD TmMinRingOn;             /*  1 user side min side ring on */
    WORD TmMaxRingOn;             /*  2 user side max side ring on */
    WORD TmMaxRingOff;            /*  3 user side max ring off */

    WORD TmRingOn;                /*  4 network emulation - ring on time */
    WORD TmRingOff;               /*  5 network emulation - ring off time */
    WORD MaxRings;                /*  6 network emulation - number rings before timeout */

    WORD TmBitQualification;      /*  7 bit qualification time */
    WORD NmRingsSeizure;          /*  8 user side - number rings before INCOMING CALL event */
    WORD debugmask;               /*  9 DEBUG MASK */
    WORD TmWaitForRelease;        /* 10 time to wait for remote to acknowledge disconnect */
    WORD BusyFreqLo;              /* 11 low freq for busy tone */
    WORD BusyFreqHi;              /* 12 high freq for busy tone */
    WORD TmBusyOn;                /* 13 on time for busy tone */
    WORD TmBusyOff;               /* 14 off time for busy tone */
    WORD AmpCPTones;              /* 15 amplitude for call progress tones */
    WORD signalingflags;          /* 16 bit parameter flags */
    WORD TmWaitAnswer;            /* 17 timeout for host to respond to INCOMING_CALL event */
/*  
 *  Transfer string parameters -- three words, two bytes per word
 *
 *  Default:  xferstring = !; (flash hook, wait for dial tone)
 */
	char xferstring[6];           /* 18 - 20 */

/*  Transfer back dial string.  Default:  connstring = ! (flash hook) */

	char connstring[6];           /* 21 - 23 */

	WORD TmQDISCONNECT;           /* 24 disconnect qualification time */
    WORD TmPredial;               /* 25 pre-dial delay before transfer */
    WORD TmPreDigitDelay;         /* 26 pre-dial delay for normal dialing */
    WORD Tm1stDigit;              /* 27 network side - inbound timer for 1st digit */
    WORD TmDigitOn;               /* 28 network side - stuck digit timeout */
    WORD TmInterDigit;            /* 29 network side - inter-digit timeout */
    WORD NmDigits;                /* 30 network side - expected number of digits */
    WORD TmWaitDialTone;          /* 31 timeout waiting for dialtone */
    WORD TmDTMF_ON;               /* 32 user side -- DTMF on time */
    WORD TmDTMF_OFF;              /* 33 user side -- DTMF off time */
    WORD RingFreqLo;              /* 34 network side - low audible ring frequency */
    WORD RingFreqHi;              /* 35 network side - high audible ring frequency */
    WORD TmARingOn;               /* 36 network side - audible ring on time */
    WORD TmARingOff;              /* 37 network side - audible ring off time */
    WORD Spare0;                  /* 38 spare parameter */
    WORD resourcegettimes;        /* 39 time to wait to get resources        */

} ADI_NEC_PARMS;

#ifdef __cplusplus                   
}
#endif  

#endif

