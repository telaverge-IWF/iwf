/* **********************************************************************
*                                                                       *
* Copyright (c) 1996 Natural MicroSystems Corp.  All rights reserved.   *
* Generated by User Definable Parameter  ( Version 1.0 )                *
* exported udpGenerateParameterSourceFiles() function.                  *
*                                                                       *
* ********************************************************************* */
                                     
                                     
#ifndef ADIWNKPARM_DEFINED           
#define ADIWNKPARM_DEFINED           
                                     
#include "ctadef.h"                  
                                     
#ifdef __cplusplus                   
extern "C"                           
{                                    
#endif                               

#define    ADI_WNK_PARMID    0x10015 
                                     
typedef struct                       
{                                    
    DWORD    size;                   
    WORD    numdigits;               /* 0 expected number of digits           */
    WORD    optionflags;             /* 1 flags for the user to set for       */
                                     /*   optional TCP behavior               */
    WORD    debugmask;               /* 2 trace level specifications          */
    WORD    qualtime;                /* 3 A or B bit must be ON/OFF of this   */
                                     /*   duration to be qualified so.        */
    WORD    signalingflags;          /* 4 protocols signaling flags.          */
    WORD    separatordigits;         /* 5 '*' low byte, 'F' hi byte           */
    WORD    winktime;                /* 6 duration of the wink.               */
    WORD    waitforPCtime;           /* 7 waiting for the PC window.          */
    WORD    prewinktime;             /* 8 pre-wink delay                      */
    WORD    ringfreq1;               /* 9 1st frequency of ring tone in Hz    */
    WORD    ringfreq2;               /*10 2nd frequency of ring tone in Hz    */
    WORD    ringontime;              /*11 sec ring tone on time               */
    WORD    ringofftime1;            /*12 1st ring tone off time              */
    WORD    ringofftime2;            /*13 2nd ring tone off time              */
    WORD    busyfreq1;               /*14 1st freq of busy and reorder tones  */
    WORD    busyfreq2;               /*15 2nd freq of busy and reorder tones  */
    WORD    busyontime;              /*16 busy tone on time                   */
    WORD    busyofftime;             /*17 busy tone off time                  */
    WORD    reorderontime;           /*18 reorder tone on                     */
    WORD    reorderofftime;          /*19 reorder tone off                    */
    WORD    cptoneslevel;            /*20 ampl of busy and reorder tones      */
    WORD    ringtonelevel;           /*21 amplitude of ring tone (-16dBm)     */
    WORD    digitswaittime;          /*22 packed 2 timers - 1 bits each       */
                                     /*   Tm1stDigit (7000 ms) waiting for    */
                                     /*   first digit                         */
                                     /*   TmNthDigit (8000 ms) waiting for    */
                                     /*   Nth digit                           */
                                     /* |nth(*100)|1st(*100)|                 */
                                     /* |0101|0000|0100|0110|                 */
    WORD    winkwaittime;            /*23 maximum time to wait for the wink   */
                                     /*   set to 0 if wink is not expected    */
    WORD    minwinktime;             /*24 minimum duration of the wink        */
    WORD    maxwinktime;             /*25 maximum duration of the wink        */
    WORD    predialtime;             /*26 post wink delay                     */
    WORD    mfkpsttime;              /*27 packed 2 timers 1 bit, 80 ms each   */
                                     /*   duration of KP or ST tone on and off*/
                                     /*   |unsed    |off |on  |               */
                                     /*   |0000|0000|8000|8000|               */
    WORD    mfkpstampl;              /*28 amplitude of MF KP,ST               */
    WORD    releaseguardtime;        /*29 minimum duration after hangup before*/
                                     /*   allowed to place another call       */
    WORD    alarmsqualtime;          /*30 qual time for alarms on: 400 ms     */
                                     /*   qual time for alarms off: 500 ms    */
    WORD    assumenewdigittime;      /*31 time to assume that a new digit has */
                                     /*   been received if no event in        */
                                     /*   InFinishDTMF                        */
    WORD    connectbacktime;         /*32 Time to wait after sending a        */
                                     /*   transfer back hookflash if the PBX  */
                                     /*   was playing busy                    */
    char    xferstring[6];           /*33 default is ";!"                     */
    char    connstring[6];           /*36 default is "!"                      */
}    ADI_WNK_PARMS;                  
                                     
extern const CTAPARM_DESC * const _adiParmDescTable[];
                                     
                                     
#ifdef __cplusplus                   
}                                    
#endif                               
                                     
#endif                               
