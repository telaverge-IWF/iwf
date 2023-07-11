/* **********************************************************************
*                                                                       *
* Copyright (c) 1996 Natural MicroSystems Corp.  All rights reserved.   *
* Generated by User Definable Parameter  ( Version 1.0 )                *
* exported udpGenerateParameterSourceFiles() function.                  *
*                                                                       *
* ********************************************************************* */
                                     
                                     
#ifndef ADISS5PARM_DEFINED           
#define ADISS5PARM_DEFINED           
                                     
#include "ctadef.h"                  
                                     
#ifdef __cplusplus                   
extern "C"                           
{                                    
#endif                               

#define    ADI_SS5_PARMID    0x10025 
                                     
typedef struct                       
{                                    
    DWORD    size;                   
    WORD    numdigits;               /* the expected number of digits         */
    WORD    optionflags;             /* user preferences                      */
    WORD    debugmask;               /* TCP debug options                     */
    WORD    intersignaltime;         /* min time between signaling tones in   */
                                     /* the same direction                    */
    WORD    longqualtime;            /* qualification time for almost all     */
                                     /* signaling tones                       */
    WORD    shortqualtime;           /* qualification time for seizure /      */
                                     /* proceed to send                       */
    WORD    connectqualtime;         /* qualification time during connect     */
                                     /* (longer to avoid talkoff)             */
    WORD    glarewaittime;           /* time to wait for seizure to go away   */
                                     /* on glare                              */
    WORD    signalcompelledtime;     /* first compelled signal max duration   */
    WORD    ackcompelledtime;        /* acknowledgement signal max duration   */
    WORD    compelledtoneslevel;     /* amplitude of compelled signals        */
    WORD    waitforPCtime;           /* time for the TCP to wait for the host */
                                     /* to answer or reject the call          */
    WORD    ringfreq1;               /* first frequency of ring tone          */
    WORD    ringfreq2;               /* second frequency of ring tone         */
    WORD    ringontime;              /* ring tone on time                     */
    WORD    ringofftime1;            /* first or only ring tone off time      */
    WORD    ringofftime2;            /* second ring tone off time if the ring */
                                     /* tone is a compound one                */
    WORD    busyfreq1;               /* first frequency of busy tone          */
    WORD    busyfreq2;               /* second frequency of busy tone         */
    WORD    busyontime;              /* busy tone on time                     */
    WORD    busyofftime;             /* busy tone off time                    */
    WORD    fastbusyontime;          /* fast busy (reorder) tone on time      */
    WORD    fastbusyofftime;         /* fast busy (reorder) tone off time     */
    WORD    CPtoneslevel;            /* amplitude of call progress tones      */
    WORD    waitKPtime;              /* inbound timer to wait for the KP      */
                                     /* digit                                 */
    WORD    waitdigittime;           /* inbound timer to wait for each        */
                                     /* subsequent digit                      */
    WORD    outdialdelay;            /* outbound delay between seizing the    */
                                     /* line and starting KP                  */
    WORD    KPandSTontime;           /* KP and ST tones on time               */
    WORD    MFtoneontime;            /* other dialed digits on time           */
    WORD    MFtoneofftime;           /* silence between dialed digits         */
    WORD    MFtoneslevel;            /* amplitude of call progress tones      */
    WORD    outboundguardtime;       /* pause between outbound calls          */
    WORD    alarmsqualtime;          /* qual time for alarms on: 400 ms       */
                                     /* qual time for alarms off: 500 ms      */
}    ADI_SS5_PARMS;                  
                                     
extern const CTAPARM_DESC * const _adiParmDescTable[];
                                     
                                     
#ifdef __cplusplus                   
}                                    
#endif                               
                                     
#endif                               
