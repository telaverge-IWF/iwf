/* **********************************************************************
*                                                                       *
* Copyright (c) 1996-2002 NMS Communications.  All rights reserved.     *
* Generated by User Definable Parameter  ( Version 1.0 )                *
* exported udpGenerateParameterSourceFiles() function.                  *
*                                                                       *
* ********************************************************************* */
                                     
                                     
#ifndef NCCXSTAPARM_DEFINED          
#define NCCXSTAPARM_DEFINED          
                                     
#include "ctadef.h"                  
                                     
#ifdef __cplusplus                   
extern "C"                           
{                                    
#endif                               
                                     
                                     
#define    NCC_ADI_STA_PARMID    0x1C011B
                                     
typedef struct                       
{                                    
    DWORD   size;                   
    WORD    numdigits;               /* 0 expected number of digits           */
    WORD    wait1stdigittime;        /* 1 waiting until first digit comes     */
    WORD    waitfordigitstime;       /* 2 waiting until N-th digit comes      */
    WORD    defaultrejecttone;       /* 3 default tone if PC doesn't respond  */
                                     /*   1 = ringing                         */
                                     /*   2 = busy                            */
                                     /*   3 = reorder (fast busy)             */
    WORD    releasecallbehavior;     /* 4 behav. upon release from Connected  */
                                     /*   0 = do nothing                      */
                                     /*   1 = deny battery for loopdroptime   */
                                     /*   2 = play dialtone                   */
                                     /*   3 = play busy                       */
                                     /*   4 = play reorder                    */
    WORD    playdialtone;            /* 5 Behaviour for playing dt on inbound */
                                     /*   0 = don't play dialtone             */
                                     /*   1 = play dialtone                   */
    WORD    blockplayreorder;        /* 6 0 = Play reorder when blocking      */
                                     /*   1 = remove battery when blocking    */
    WORD    maxringseconds;          /* 7 the maximum time to wait for the    */
                                     /*   remote to answer, in seconds        */
    WORD    loopdroptime;            /* 8 drop loop current after release     */
    WORD    cidsupport;              /* 9 type of CID to be generated         */
                                     /*   low nibble:  0 = disabled           */
                                     /*                1 = Bellcore           */
                                     /*                3 = ETSI               */
                                     /*   high nibble:                        */
                                     /*     0 = Normal Ring Alerting Signal   */
                                     /*     1 = Ring Pulse Alerting Signal    */
                                     /*     2 = Dual Tone Alerting Signal     */
    WORD    qualaddron;              /*10 qual dur. ON during addressing      */
    WORD    qualaddroff;             /*11 qual dur. OFF during addressing     */
    WORD    qualdisconnect;          /*12 qual dur. of disconnect             */
    WORD    qualpermsignal;          /*13 qual dur. of permanent signal       */
    WORD    outring1ontime;          /*14 ontime for the 1st ring cycle       */
    WORD    outring1offtime;         /*15 offtime for the 1st ring cycle      */
    WORD    outring2ontime;          /*16 ontime for the 2nd ring cycle       */
    WORD    outring2offtime;         /*17 offtime for the 2nd ring cycle      */
    WORD    maxflashtime;            /*18 Maximum flash-hook duration         */
                                     /* Note the interaction with             */
                                     /* qualdisconnect, that in this case     */
                                     /* represents the MINIMUM time.          */
    WORD    linetype;                /*19 0 = analog                          */
                                     /*   2 = digital OPS FX                  */
                                     /*   3 = digital OPS SA                  */
    WORD    CDsignalbits;            /*20 if linetype is digital trunk, then  */
                                     /*   0 = CD bits = AB bits (normal T1)   */
                                     /*   1 = CD bits = 01      (normal E1)   */
                                     /*   2 = CD bits = 10                    */
                                     /*   3 = CD bits = 11                    */
}    NCC_ADI_STA_PARMS;              
                                     
extern const CTAPARM_DESC * const _nccParmDescTable[];
                                     
                                     
#ifdef __cplusplus                   
}                                    
#endif                               
                                     
#endif                               

