/* **********************************************************************
*                                                                       *
* Copyright (c) 1996 Natural MicroSystems Corp.  All rights reserved.   *
* Generated by User Definable Parameter  ( Version 1.0 )                *
* exported udpGenerateParameterSourceFiles() function.                  *
*                                                                       *
* ********************************************************************* */
                                     
                                     
#ifndef NCCXWNKPARM_DEFINED          
#define NCCXWNKPARM_DEFINED          
                                     
#include "ctadef.h"                  
                                     
#ifdef __cplusplus                   
extern "C"                           
{                                    
#endif                               
                                     
                                     
#define    NCC_SVCID    0x1C         
                                     
#define    NCC_ADI_WNK_PARMID    0x1C011C
                                     
typedef struct                       
{                                    
    DWORD    size;                   
    WORD    numdigits;               /* 0 expected number of digits           */
    WORD    variabledigits;          /* 1 set to 0x1 to allow for reception   */
                                     /*   of variable number of digits        */
    WORD    idlebits;                /* 2 idle code mode:                     */
                                     /*   pulse on busy: 0, pulse on idle: 1  */
    WORD    trunkdirection;          /* 3 0=two way, 1=IN, 2=OUT              */
    WORD    playcleardown;           /* 4 play cleardown tone if 1            */
    WORD    defaultrejecttone;       /* 5 default tone if PC does not         */
                                     /* respond:                              */
                                     /*  1=CAS_REJECT_PLAY_RINGTONE           */
                                     /*  2=CAS_REJECT_PLAY_BUSY               */
                                     /*  3=CAS_REJECT_PLAY_REORDER            */
    WORD    transfersupport;         /* 6 set to 1 to enable transfer         */
    WORD    qualtime;                /* 7 bit qualification time              */
    WORD    compelledKP;             /* 8 set to 1 in Taiwan                  */
    WORD    immediatestart;          /* 9 set to 1 not to look for wink       */
    WORD    signalingmethod;         /*10 sets register signaling type:       */
                                     /*   0=DTMF, 1=MF, 2=decadic             */
    WORD    receiveKPST;             /*11 set to 0 not to look for KP and ST  */
    WORD    noSTreceptionOK;         /*12 set to 1 if it's OK not get ST      */
    WORD    sendKPST;                /*13 set to 0 not to send KP and ST      */
    WORD    anibeforedid;            /*14 set to 1 if ANI come first          */
    WORD    anididtone;              /*15 tone that specifies a separator     */
                                     /*   between DIDs and ANIs.              */
                                     /*   set to 0x2a for '*'                 */
    WORD    endofdigitstone;         /*16 tone that specifies the end of      */
                                     /*   digits. 'F' is the default.         */
    WORD    winktime;                /*17 wink duration                       */
    WORD    prewinktime;             /*18 time from seizure to wink           */
    WORD    wait1stdigittime;        /*19 max wait for first digit            */
    WORD    waitfordigitstime;       /*20 max wait for following digits       */
    WORD    winkwaittime;            /*21 max wait for wink                   */
    WORD    minwinktime;             /*22 min wink duration                   */
    WORD    maxwinktime;             /*23 max wink duration                   */
    WORD    predialtime;             /*24 delay to dial after wink            */
    WORD    mfkpsttimeon;            /*25 ON time for KP and ST               */
    WORD    mfkpsttimeoff;           /*26 OFF time for KP and ST              */
    WORD    mfkpstampl;              /*27 level of KP and ST                  */
    WORD    releaseguardtime;        /*28 release guard duration              */
    WORD    alarmsonqualtime;        /*29 qual time for alarms on             */
    WORD    alarmsoffqualtime;       /*30 qual time for alarms off            */
    WORD    assumenewdigittime;      /*31 set to the MF dialing period if     */
                                     /*   silence is too short to detect      */
    WORD    connectbacktime;         /*32 Time to wait after sending a        */
                                     /*   transfer back hookflash if the PBX  */
                                     /*   was playing busy                    */
    char    xferstring[6];           /*33 default xfer string, = "!;"         */
    char    connstring[6];           /*34 default reconnect string, = "!"     */
    WORD    BCD_BitFlag;             /*35 if set to 1, BCD=101                */
                                     /*   otherwise, BCD follows A bit        */
    WORD    KP_Reset;                /*36 KP resets the digit string          */
    WORD    Pass_KP_ST;              /*37 pass KP and ST in digit string      */
}    NCC_ADI_WNK_PARMS;              
                                     
extern const CTAPARM_DESC * const _nccParmDescTable[];
                                     
                                     
#ifdef __cplusplus                   
}                                    
#endif                               
                                     
#endif                               

