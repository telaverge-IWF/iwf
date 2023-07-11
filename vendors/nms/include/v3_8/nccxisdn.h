/***************************************************************************
*                                  NCCXISDN.H
*
*  Structures definition for AG ISDN Layer 4
*
*  Copyright (c)1998 Natural MicroSystems Corporation. All rights reserved.
****************************************************************************/

#ifndef NCCXISDN_INCLUDED
#define NCCXISDN_INCLUDED

#include "nccadi.h"

#define NCC_ADI_ISDN_PARMID 0x1c011d

/* ISDN protocol event values */
#define ISDN_PROGRESS         0x9F0E0000 /* ISDN Progress event value      */
#define ISDN_CALL_MESSAGE_SENT 0x9F200000 /* ISDN-specific event value     */

#define NCC_ISDN_MAX_UUI        131

/* EXT_STATUS_INFO mask */
#define NCC_X_STATUS_INFO_UUI           0x01 /* UUI field has changed      */
#define NCC_X_STATUS_INFO_PROGRESSDESCR 0x02 /* Progress descriptor field
                                                has changed                */
#define NCC_X_STATUS_INFO_CHARGE        0x04 /* Charging Information 
                                                has been received          */


/*------ ISDN PARMS -------------------------------------------------------*/
/* Supplementary services calling number extensions:                       */
typedef struct
{
    DWORD size;
    WORD plan;
    WORD type;
    WORD screen;
    WORD presentation;    

} CALLINGNUM;

/* Supplementary services redirecting number extensions:                   */
typedef struct
{
    DWORD size;
    char digits[33];
    char pad[3];
    WORD plan;
    WORD type;
    WORD screen;
    WORD presentation;
    WORD reason;
    WORD pad1;

} REDIRECTINGNUM;

/* Supplementary services called number extensions:                        */
typedef struct
{
    DWORD size;
    WORD plan;
    WORD type;

} CALLEDNUM;

/* Supplementary services place call extensions:                           */
typedef struct
{
    DWORD size;                         /* size of this structure                       */
    char  uui[NCC_ISDN_MAX_UUI + 1];    /* UUI                                          */   
    CALLEDNUM      callednumber;        /* called number substructure                   */  
    CALLINGNUM     callingnumber;       /* calling number substructure                  */
    REDIRECTINGNUM redirectingnumber;   /* redirecting number substructure              */  
    WORD  service;                      /* service                                      */ 
    WORD  nsf_present;                  /* nsf usage flag                               */
    WORD  nsf_service_feature;          /* service or fiture is set in the coding field */
    WORD  nsf_facility_coding;          /* nsf coding                                   */ 

} PLACECALL_EXT;

/* Supplementary services answer call extensions:                     */
typedef struct
{
    DWORD size;                             /* size of this structure */
    char uui [NCC_ISDN_MAX_UUI + 1];        /* UUI                    */

} ANSWERCALL_EXT;

/* Supplementary services accept call extensions:                     */
typedef struct
{
    DWORD size;                             /* size of this structure */
    char  uui [NCC_ISDN_MAX_UUI + 1];       /* UUI                    */  
    WORD  cause;                            /* cause value            */
    WORD  progressdescription;              /* progress description   */

} ACCEPTCALL_EXT;

/* Supplementary services disconnect call extensions:                       */
typedef struct
{
    DWORD size;                             /* size of this structure       */
    char  uui [NCC_ISDN_MAX_UUI + 1];       /* UUI                          */
    WORD  cause;                            /* disconnect cause (NCC value) */
    WORD  pad;

} DISCONNECTCALL_EXT;

typedef struct
{
    DWORD size;                             /* size of this structure       */    
    char  uui [NCC_ISDN_MAX_UUI + 1];       /* UUI                          */
    WORD  cause;                            /* disconnect cause (NCC value) */
    WORD  pad;

} REJECTCALL_EXT;

typedef struct                              /* passed with nccStartProtocol("ISDN")    */
{
    DWORD size;                             /*  size of this structure.                */
    WORD exclusive;                         /*  exclusive or prefered                  */
                                            /*     0 = non-exclusive                   */
                                            /*     1 = exclusive                       */
    WORD direction;                         /*  inbound, outbound or both              */
                                            /*     0 = both                            */
                                            /*     1 = inbound                         */
                                            /*     2 = outbound                        */
    WORD networkstream;                     /*  network stream (dflt: infer from DSP)  */
    WORD networkslot;                       /*  network time slot (dflt:infer from DSP)*/
    WORD defaulttone;                       /*  default tone to play on reject         */
                                            /*     0 = reorder (fast busy)             */
                                            /*     1 = ringing                         */
                                            /*     2 = busy                            */
    WORD startCP;                           /*  start call progress from the TCP       */
                                            /*  when a PROGRESS or a CONNECT message   */
                                            /*  is received                            */
    WORD flags;                             /*  miscellaneous flags                    */
#define PROCEEDING_MASK         0x0001  /* Send proceeding message on incoming call */

#define PROGRESS_MASK_ANSWER    0x0010  /* Send progress message on nccAnswerCall   */
#define ALERTING_MASK_ANSWER    0x0020  /* Send alert message on nccAnswerCall      */
#define PROCEEDING_MASK_ANSWER  0x0040  /* Send proceeding message on nccAnswerCall */

#define PROGRESS_MASK_ACCEPT    0x0100  /* Send progress message on nccAcceptCall   */
#define ALERTING_MASK_ACCEPT    0x0200  /* Send alert message on nccAcceptCall      */
#define PROCEEDING_MASK_ACCEPT  0x0400  /* Send proceeding message on nccAcceptCall */

#define PROGRESS_MASK_REJECT    0x1000  /* Send progress message on nccRejectCall   */
#define ALERTING_MASK_REJECT    0x2000  /* Send alert message on nccRejectCall      */
#define PROCEEDING_MASK_REJECT  0x4000  /* Send proceeding message on nccRejectCall */

    WORD blockrejectmode;                   /*  how to reject calls when the channel   */
                                            /*  is blocked with BLOCK_REJECTALL mode:  */
                                            /*  0 = reject immediate                   */
                                            /*  1 = play busy tone                     */ 
    WORD blockwaittime;                     /*  time to wait for block confirmation    */
#define ISDN_BLOCK_REJ_FORCE_IMMEDIATE 0 /* reject immediate          */
#define ISDN_BLOCK_REJ_MAKEBUSY        1 /* play busy tone            */ 

    WORD ISDNeventmask;                     /*  informational isdn event mask          */        
#define ISDN_REPORT_PROGRESS    0x0001  /* report received ISDN_PROGRESS       */

} START_EXT;

/* Supplementary services send digits extensions:                           */
typedef struct
{
    DWORD size;                             /* size of this structure       */
    CALLEDNUM      callednumber;            /* called number substructure   */  

} SENDDIGITS_EXT;


typedef struct                    /* Generic ISDN category */
{
    DWORD size;                   /*  Size of this structure.              */
    ACCEPTCALL_EXT                  isdn_accept;
    ANSWERCALL_EXT                  isdn_answer;
    DISCONNECTCALL_EXT              isdn_disconnect;
    PLACECALL_EXT                   isdn_place;
    REJECTCALL_EXT                  isdn_reject;
    START_EXT                       isdn_start;
    SENDDIGITS_EXT                  isdn_senddigits;
} NCC_ADI_ISDN_PARMS;

typedef struct
{                                 /* used by adiGetCallStatus()             */
    DWORD size ;                  /* size returned by adiGetCallStatus()    */
    INT32 reason;                 /* reason of going back to IDLE state     */
    DWORD stream;                 /* mvip stream number                     */
    DWORD timeslot;               /* mvip timeslot                          */

    WORD  callreference;          /* Q.931 call reference                   */
    WORD  pad;

    DWORD chargingvalue;          /* charging value                         */
    char  chargingmulti;          /* charging multiplier                    */
    char  chargingtype;           /* charging type                          */
    char  chargingperiod;         /* charging period                        */

    char  callednumplan;          /* Q.931 numbering plan ID if supported   */
    char  callednumtype;          /* Q.931 number type if supported         */
    char  callingnumplan;         /* Q.931 numbering plan ID if supported   */
    char  callingnumtype;         /* number type if supported               */
    char  callingpres;            /* caller ID presentation indicator       */
    char  callingscreen;          /* Q.931 ANI screening indicator          */

    char  progressdescr;          /* progress descriptor                    */

    char  releasecause;           /* cause for call release                 */

    char  redirectingaddr[33];    /* redirecting number info    */
    char  redirectingplan;        /* Q.931 numbering plan ID if supported   */
    char  redirectingtype;        /* Q.931 number type if supported         */
    char  redirectingpres;        /* redirecting number pres. indicator     */
    char  redirectingscreen;      /* Q.931 redirecting number screen ind.   */
    char  redirectingreason;      /* reason for redirection                 */

    char  originalcalledaddr[33]; /* original called number                 */
    char  origcalledplan;         /* Q.931 numbering plan ID if supported   */
    char  origcalledtype;         /* Q.931 number type if supported         */
    char  origcalledpres;         /* original called number pres. indicator */
    char  origcalledscreen;       /* Q.931 redirecting number screen ind.   */
    char  origcalledreason;       /* Q.931 reason for redirection           */
    
    char  UUI[NCC_ISDN_MAX_UUI + 1]; /*   user to user information          */    

    char  origlineinfo;           /* originating line information           */    



} NCC_ISDN_EXT_CALL_STATUS;


/* Structures and macros to send specific isdn messages to the board        */

typedef struct 
{
    WORD message_id;                          /* message id                 */
        #define NCC_ISDN_TBCT               1 /* Two B-Channel Transfer     */
        #define NCC_ISDN_D_CHANNEL_ID_RQ    2 /* D-Channel Identifier Request */
        #define NCC_ISDN_TRANSPARENT_BUFFER 3 /* Transparent buffer         */
    
    WORD message_type;                         /* message type              */
        #define NCC_ISDN_RETURN_REJECT      2  /* REJECT COMPONENT          */
        #define NCC_ISDN_RETURN_RESULT      3  /* RESULT COMPONENT          */
        #define NCC_ISDN_RETURN_ERROR       4  /* ERROR  COMPONENT          */
} NCC_ISDN_SEND_CALL_MESSAGE;

/* Structures NCC_ISDN_XXX_INVOKE are used to send to the board with 
   nccSendCallMessage(). 
   Structures NCC_ISDN_XXX_RETURN_ZZZ come from the board inside event with
   ID set to NCCEVN_PROTOCOL_EVENT and the value set to ISDN_CALL_MESSAGE_SENT
 */


/* D-Channel Identifier Structure */

typedef struct
{
    unsigned char value[4];         /* D-Channel Identifier value */
    unsigned char length;           /* length of D-Channel Identifier value */
    unsigned char pad[3];
} D_CHANNEL_ID;

/* Structures associated with NCC_ISDN_TBCT */

typedef struct
{
    NCC_ISDN_SEND_CALL_MESSAGE hdr;
    WORD    callreference;          /* Call Reference of the second call    */
    WORD    pad;
    D_CHANNEL_ID  dCID;             /* D-Channel Identifier, optional       */
} NCC_ISDN_TBCT_INVOKE;

typedef struct
{
    NCC_ISDN_SEND_CALL_MESSAGE hdr;
    unsigned char cause;
        #define NCC_ISDN_REJECT_UNSPECIFIED            1
        #define NCC_ISDN_REJECT_DUPLICATE_INVOCE       8   
        #define NCC_ISDN_REJECT_UNRECOGNIZED_OP        9
        #define NCC_ISDN_REJECT_RESOURCE_LIMITATION    10
    unsigned char pad[7];
} NCC_ISDN_TBCT_RETURN_REJECT;

typedef struct
{
    NCC_ISDN_SEND_CALL_MESSAGE hdr;
} NCC_ISDN_TBCT_RETURN_RESULT;

typedef struct
{
    NCC_ISDN_SEND_CALL_MESSAGE hdr;
    WORD error;
        #define NCC_ISDN_ERROR_NOT_SUBSCRIBED         0 
        #define NCC_ISDN_ERROR_NOT_AVAILABLE          3
        #define NCC_ISDN_ERROR_INVALID_CALL_STATE     7
        #define NCC_ISDN_ERROR_INTERAC_NOT_ALLOWED    10
        #define NCC_ISDN_ERROR_NOT_ALLOWED            32
        #define NCC_ISDN_ERROR_LINK_ID_NOT_ASSIGNED   61
        #define NCC_ISDN_ERROR_DCHAN_ID_NOT_ASSIGNED  254
        #define NCC_ISDN_ERROR_UNSPECIFIED            255
} NCC_ISDN_TBCT_RETURN_ERROR;


/* Structures associated with NCC_ISDN_D_CHANNEL_ID_RQ */

typedef struct
{
    NCC_ISDN_SEND_CALL_MESSAGE hdr;
} NCC_ISDN_D_CHANNEL_ID_RQ_INVOKE;

typedef struct 
{
    NCC_ISDN_SEND_CALL_MESSAGE hdr;
    D_CHANNEL_ID dCID;                /* D-Channel Identifier */
} NCC_ISDN_D_CHANNEL_ID_RQ_RETURN_RESULT;

typedef struct 
{
    NCC_ISDN_SEND_CALL_MESSAGE hdr;
    WORD error;
        #define NCC_ISDN_ERROR_DCHAN_ID_NOT_AVAILABLE 3
    WORD pad;
} NCC_ISDN_D_CHANNEL_ID_RQ_RETURN_ERROR;


/* Structures associated with NCC_ISDN_TRANSPARENT_BUFFER */

typedef struct
{
    NCC_ISDN_SEND_CALL_MESSAGE hdr;
    unsigned char   isdn_message;           /* isdn message                 */
        #define NCC_ISDN_FACILITY        1
    unsigned char   size;                   /* size of the buffer           */
    char            buffer[1];              /* buffer, attached to the msg  */
} NCC_ISDN_TRANSPARENT_BUFFER_INVOKE;

typedef NCC_ISDN_TRANSPARENT_BUFFER_INVOKE NCC_ISDN_TRANSPARENT_BUFFER_RETURN_RESULT;


#endif /* NCCXISDN_INCLUDED */

