/******************************************************************************
*                                  NCCXNEC.H
*
*
*
*  Copyright (c)2001 Natural MicroSystems Corporation. All rights reserved.
*****************************************************************************/

#ifndef NCCNECPARM_DEFINED           
#define NCCNECPARM_DEFINED           

#include "ctadef.h"

#ifdef __cplusplus                   
extern "C"                           
{                                    
#endif  


#define    NCC_SVCID         0x1C 
#define    NCC_ADI_NEC_PARMID    0x1C011F

typedef struct                    /* passed with nccStartProtocol("NEC#")    */
{
    DWORD size;                   /*    */
    WORD trunkdirection;          /*  0 inbound, outbound, two-way */
    WORD playcleardown;           /*  1 cleardown during disconnect -- boolean */
    WORD networkside;             /*  2 act as network (PBX) */
    WORD nowaitfordialtone;       /*  3 wait for dialtone before dialing */
    WORD abortnodialtone;         /*  4 abort if dialtone is not detected */

/*  Note:  These ring times are for ring pattern asserted on the signaling bits */

    WORD TmMinRingOn;             /*  5 user side min side ring on */
    WORD TmMaxRingOn;             /*  6 user side max side ring on */
    WORD TmMaxRingOff;            /*  7 user side max ring off */

    WORD TmRingOn;                /*  8 network emulation - ring on time */
    WORD TmRingOff;               /*  9 network emulation - ring off time */
    WORD MaxRings;                /* 10 network emulation - number rings before timeout */

    WORD TmBitQualification;      /* 11 bit qualification time */
    WORD NmRingsSeizure;          /* 12 user side - number rings before INCOMING CALL event */
    WORD debugmask;               /* 13 protocol specific DEBUG MASK */
    WORD TmWaitForRelease;        /* 14 time to wait for remote to acknowledge disconnect */

    WORD BusyFreqLo;              /* 15 low freq of busy tone */
    WORD BusyFreqHi;              /* 16 high freq of busy tone */
    WORD TmBusyOn;                /* 17 on time (ms) busy tone */
    WORD TmBusyOff;               /* 18 off time (ms) busy tone */
    WORD AmpCPTones;              /* 19 amplitude (internal units) */

    WORD bmCDbit;                 /* 20 value of the CD bits (1 or 3) */
    WORD TmWaitAnswer;            /* 21 timeout for host to respond to INCOMING_CALL event */
/*  
 *  Transfer string parameters -- three words, two bytes per word
 *
 *  Default:  xferstring = !; (flash hook, wait for dial tone)
 */
	char xferstring[6];           /* 22 - 24 */

/*  Transfer back dial string.  Default:  connstring = ! (flash hook) */

	char connstring[6];           /* 25 - 27 */

	WORD TmQDISCONNECT;           /* 28 disconnect qualification time */
    WORD TmPredial;               /* 29 pre-dial delay before transfer */
    WORD TmPreDigitDelay;         /* 30 pre-dial delay for normal dialing */
    WORD Tm1stDigit;              /* 31 network side - inbound timer for 1st digit */
    WORD TmDigitOn;               /* 32 network side - stuck digit timeout */
    WORD TmInterDigit;            /* 33 network side - inter-digit timeout */
    WORD NmDigits;                /* 34 network side - expected number of digits */
    WORD TmWaitDialTone;          /* 35 timeout waiting for dialtone */

    WORD TmDTMF_ON;               /* 36 user side -- DTMF on time */
    WORD TmDTMF_OFF;              /* 37 user side -- DTMF off time */

    WORD FrRingL;                 /* 38 low freq of audible ring */
    WORD FrRingH;                 /* 39 high freq of audible ring */
    WORD TmARingOn;               /* 40 on time of audible ring */
    WORD TmARingOff;              /* 41 off time of audible ring */

    WORD resourcegettimes;        /* 42 time to wait to get resources        */

} NCC_ADI_NEC_PARMS;

extern const CTAPARM_DESC * const _nccParmDescTable[];


#ifdef __cplusplus                   
}
#endif  

#endif

