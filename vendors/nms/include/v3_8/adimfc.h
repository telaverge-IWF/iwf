/* **********************************************************************
*                                                                       *
* Copyright (c) 1996 Natural MicroSystems Corp.  All rights reserved.   *
* Generated by User Definable Parameter  ( Version 1.0 )                *
* exported udpGenerateParameterSourceFiles() function.                  *
*                                                                       *
* ********************************************************************* */
                                     
                                     
#ifndef ADIMFCPARM_DEFINED           
#define ADIMFCPARM_DEFINED           
                                     
#include "ctadef.h"                  
                                     
#ifdef __cplusplus                   
extern "C"                           
{                                    
#endif                               

#define    ADI_MFC_PARMID    0x1001F 
                                     
typedef struct                       
{                                    
    DWORD    size;                   
    WORD    DIDnumber;               /* 0 the expected number of DID          */
    WORD    ANInumber;               /* 1 the expected number of ANI          */
    WORD    DIDBeforeANI;            /* 2 DID to request before ANI           */
    WORD    optionflags;             /* 3 user preferences                    */
    WORD    debugmask;               /* 4 TCP debug options                   */
    WORD    compelledtimers;         /* 5 all compelled timers (s)            */
    WORD    releaseguardtime;        /* 6 release guard timer                 */
    WORD    inboundqualtimers;       /* 7 in qfy times, packed                */
    WORD    outboundqualtimers;      /* 8 qfy time during sz ack              */
    WORD    seizureacktime;          /* 9 outbound sz ack timer               */
    WORD    answertime;              /*10 outbound answer timer               */
    WORD    inboundreleasetime;      /*11 inbound length of pulse             */
    WORD    tonesgroupA;             /*12 backward Group A tones              */
    WORD    tonesgroupB;             /*13 backward Group B tones              */
    WORD    tonesendofinfo;          /*14 tones for end of info               */
    WORD    tonesanswer;             /*15 answer tones                        */
    WORD    tonesmiscellaneous;      /*16 various tones                       */
    WORD    tonesrepeatrequest;      /*17 outbound repeat tones               */
    WORD    tonesgroupC;             /*18 outbound repeat tones               */
    WORD    ringfreq1;               /*19 low frequency of ring               */
    WORD    ringfreq2;               /*20 hi frequency of ring                */
    WORD    ringontime;              /*21 ring-on time                        */
    WORD    ringofftime1;            /*22 1st ring-off time                   */
    WORD    ringofftime2;            /*23 2nd ring-off time, if!=0            */
    WORD    busyfreq1;               /*24 low frequency of busy               */
    WORD    busyfreq2;               /*25 hi frequency of busy                */
    WORD    busyontime;              /*26 busy-on time                        */
    WORD    busyofftime;             /*27 busy-off time                       */
    WORD    CPtonelevel;             /*28 amplitude of ring, busy             */
    WORD    compelledtonelevel;      /*29 amplitude of cmpl tones             */
    WORD    signalingflags;          /*30 flags governing the prot            */
                                     /*   signaling behavior                  */
    WORD    validDIDmask;            /*31 16 tones; 1=valid, 0=not            */
    WORD    validANImask;            /*32 16 tones; 1=valid, 0=not            */
    WORD    validcategorymask;       /*33 16 tones; 1=valid, 0=not            */
    WORD    validgroupIImask;        /*34 16 tones; 1=valid, 0=not            */
    WORD    catnoANImask;            /*35 16 tones; 1=valid, 0=not            */
    WORD    tonesinternational;      /*36 ANIs meaning no more ANIs           */
    WORD    reanswerdelay;           /*37 time before reanswer                */
    WORD    reanswerpulsetime;       /*38 length of reanswer pulse            */
    WORD    alarmsqualtime;          /*39 qual time for alarms on: 400 ms     */
                                     /*   qual time for alarms off: 500 ms    */
}    ADI_MFC_PARMS;                  
                                     
extern const CTAPARM_DESC * const _adiParmDescTable[];
                                     
                                     
#ifdef __cplusplus                   
}                                    
#endif                               
                                     
#endif                               
