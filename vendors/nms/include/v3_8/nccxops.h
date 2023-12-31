/* **********************************************************************
*                                                                       *
* Copyright (c) 1996 Natural MicroSystems Corp.  All rights reserved.   *
* Generated by User Definable Parameter  ( Version 1.0 )                *
* exported udpGenerateParameterSourceFiles() function.                  *
*                                                                       *
* ********************************************************************* */
                                     
                                     
#ifndef NCCXOPSPARM_DEFINED          
#define NCCXOPSPARM_DEFINED          
                                     
#include "ctadef.h"                  
                                     
#ifdef __cplusplus                   
extern "C"                           
{                                    
#endif                               
                                     
                                     
#define    NCC_ADI_OPS_PARMID    0x1C0118
                                     
typedef struct                       
{                                    
    DWORD    size;                   
    WORD    nodialtonebehavior;      /* 0 behavior if no dialtone             */
                                     /*   0=abandon; 1=proceed                */
    WORD    transfersupport;         /* 1 support transfer commands           */
    WORD    CIDsupport;              /* 2 enable analog caller ID             */
    WORD    cleardowntone;           /* 3 choice of tones to play as cleardown*/
                                     /*   tone:                               */
                                     /*   0=don't play cleardown tone         */
                                     /*   1=play dialtone                     */
                                     /*   2=play busy tone                    */
                                     /*   3=play fast busy tone               */
    WORD    networkside;             /* 4 emulate network                     */
    WORD    hangupsignal;            /* 5 signaling flags:                    */
                                     /*   0xa -hangup supervision on the A bit*/
                                     /*   0xb -hangup supervision on the B bit*/
    WORD    trunktype;               /* 6 defines the physical link,          */
                                     /*   0=T1 TRUNK                          */
                                     /*   1=E1 TRUNK                          */
    WORD    signalingtype;           /* 7 the type of signaling               */
                                     /*   0=FX SIGNALING                      */
                                     /*   1=SA SIGNALING                      */
    WORD    bitqualtime;             /* 8 A or B bit must be ON/OFF of this   */
                                     /*   duration to be qualified so.        */
    WORD    minringontime;           /* 9 minimum incoming ring               */
    WORD    maxringontime;           /*10 maximum incoming ring               */
    WORD    maxringofftime;          /*11 maximum silence between rings       */
    WORD    ringstoincoming;         /*12 when to send INCOMING_CALL          */
    WORD    dialtonewaittime;        /*13 Time to wait for dialtone (if 0,    */
                                     /*   don't wait for dialtone but dial    */
                                     /*   immediately)                        */
    WORD    dialtonemintime;         /*14 minimum generic dial tone required  */
    WORD    releaseguardtime;        /*15 time to wait between outbound calls */
    WORD    CIDtype;                 /*16 type of caller ID protocol          */
                                     /*   0: BELL: USA Hong Kong              */
                                     /*   1: NTT: JAPAN                       */
                                     /*   2: ETSI (V.23)                      */
    WORD    CIDmaxwaittime;          /*17 maximum time to wait for CID        */
    WORD    CIDmaxalerttime;         /*18 max alert signal in a CID protocols */
    WORD    CIDminmarktime;          /*19 the CID minimum mark time           */
    char    xferstring[6];           /*20, default xfer string, = "!;"        */
    char    connstring[6];           /*23, default reconnect string, = "!"    */
    WORD    waitdialnodialtone;      /*26 Time to wait to dial if no dialtone */
                                     /*   detection is required               */
    WORD    connectbacktime;         /*27 Time to wait after sending a        */
                                     /*   transfer back hookflash if the PBX  */
                                     /*   was playing busy                    */
    WORD    ringsignalontime;        /*28 nominal ring-on time                */
    WORD    ringsignalofftime;       /*29 nominal silence between rings       */
    WORD    numdigits;               /*30 expected number of digits           */
    WORD    alarmsonqualtime;        /*31 qual time for alarms on             */
    WORD    alarmsoffqualtime;       /*32 qual time for alarms off            */
    WORD    cleardownflag;           /*33 turn on cleardown detection         */
                                     /*   0=off                               */
                                     /*   1=on                                */

}    NCC_ADI_OPS_PARMS;              
                                     
extern const CTAPARM_DESC * const _nccParmDescTable[];
                                     
                                     
#ifdef __cplusplus                   
}                                    
#endif                               
                                     
#endif                               

