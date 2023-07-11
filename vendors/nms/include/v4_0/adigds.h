/* **********************************************************************
*                                                                       *
* Copyright (c) 1996-2002 NMS Communications.  All rights reserved.     *
* Generated by User Definable Parameter  ( Version 1.0 )                *
* exported udpGenerateParameterSourceFiles() function.                  *
*                                                                       *
* ********************************************************************* */
                                     
                                     
#ifndef ADIGDSPARM_DEFINED           
#define ADIGDSPARM_DEFINED           
                                     
#include "ctadef.h"                  
                                     
#ifdef __cplusplus                   
extern "C"                           
{                                    
#endif                               
                                     
                                     
#define    ADI_GDS_PARMID    0x10027 
                                     
typedef struct                       
{                                    
    DWORD    size;                   
    WORD    optionflags;             /* 0 flags for the user to set for       */
                                     /*   optional TCP behavior               */
                                     /*   0x1  disconnect if no dialtone      */
                                     /*   0x2  continue dialing if no dialtone*/
                                     /*   0x4  don't accept transfer commands */
                                     /*   0x8  enable analog caller ID        */
                                     /*   0x30 choice of tones to play as     */
                                     /*        cleardown tone, if network:    */
                                     /*        0x00: nothing                  */
                                     /*        0x10: dialtone (default)       */
                                     /*        0x20: busy                     */
                                     /*        0x30: reorder                  */
                                     /*   0x8000 emulate the switch           */
                                     /*          (for testing)                */
    WORD    signalingflags;          /* 1 signaling flags:                    */
                                     /*   0x1 hangup supervision on the A bit */
                                     /*   0x2 hangup supervision on the B bit */
    WORD    trunktype;               /* 2 Where the least significant hexade  */
                                     /*   marks the physical link, the next   */
                                     /*   the type of signaling (FX, SA, ...) */
                                     /*   T1_TRUNK       0x00                 */
                                     /*   E1_TRUNK       0x01                 */
                                     /*   FX_SIGNALING   0x00                 */
                                     /*   SA_SIGNALING   0x10                 */
    WORD    bitqualtime;             /* 3 A or B bit must be ON/OFF of this   */
                                     /*   duration to be qualified so.        */
    WORD    minringontime;           /* 4 minimum incoming ring               */
    WORD    maxringontime;           /* 5 maximum incoming ring               */
    WORD    maxringofftime;          /* 6 maximum silence between rings       */
    WORD    numrings;                /* 7 when to send INCOMING_CALL          */
    WORD    dialtonewaittime;        /* 8 Time to wait for dialtone (if 0,    */
                                     /*   don't wait for dialtone but dial    */
                                     /*   immediately)                        */
    WORD    dialtonemintime;         /* 9 minimum generic dial tone required  */
    WORD    releaseguardtime;        /*10 time to wait between outbound calls */
    WORD    CIDtype;                 /*11 type of caller ID protocol          */
                                     /*   0: BELL: USA Hong Kong              */
                                     /*   1: NTT: JAPAN                       */
                                     /*   2: ETSI (V.23)                      */
    WORD    CIDmaxwaittime;          /*12 maximum time to wait for CID        */
    WORD    CIDmaxalerttime;         /*13 max alert signal in a CID protocols */
    WORD    CIDminmarktime;          /*14 the CID minimum mark time           */
    char    xferstring[6];           /*15 default xfer string, = "!;"         */
    char    connstring[6];           /*18 default reconnect string, = "!"     */
    WORD    waitdialnodialtone;      /*21 Time to wait to dial if no dialtone */
                                     /*   detection is required               */
    WORD    connectbacktime;         /*22 Time to wait after sending a        */
                                     /*   transfer back hookflash if the PBX  */
                                     /*   was playing busy                    */
    WORD    ringsignalontime;        /*23 nominal ring-on time                */
    WORD    ringsignalofftime;       /*24 nominal silence between rings       */
    WORD    dialtonefreq1;           /*25 1st dial tone frequency             */
    WORD    dialtonefreq2;           /*26 2nd dial tone frequency             */
    WORD    ringfreq1;               /*27 1st ring tone frequency             */
    WORD    ringfreq2;               /*28 2nd ring tone frequency             */
    WORD    ringontime;              /*29 time on while playing ring          */
    WORD    ringofftime1;            /*30 1st silent time while playing ring  */
    WORD    ringofftime2;            /*31 2nd silent time while playing ring  */
    WORD    busyfreq1;               /*32 1st busy tone frequency             */
    WORD    busyfreq2;               /*33 2nd busy tone frequency             */
    WORD    busyontime;              /*34 time on while playing busy          */
    WORD    busyofftime;             /*35 1st silent time while playing busy  */
    WORD    toneslevel;              /*36 CP tones level                      */
    WORD    numdigits;               /*37 expected number of digits           */
    WORD    alarmsqualtime;          /*38 qual time for alarms on             */
                                     /*   qual time for alarms off            */
}    ADI_GDS_PARMS;                  
                                     
extern const CTAPARM_DESC * const _adiParmDescTable[];
                                     
                                     
#ifdef __cplusplus                   
}                                    
#endif                               
                                     
#endif                               
