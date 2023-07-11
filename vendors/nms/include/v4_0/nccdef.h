/*****************************************************************************
  NAME:  nccdef.h

  PURPOSE:

      This file contains macros and function prototypes that define the API
      for the NCC service.
  ****************************************************************************/


#ifndef NCCDEF_INCLUDED
#define NCCDEF_INCLUDED

/* Standard CT Access include files. */
#include "nmstypes.h"
#include "ctadef.h"
#include "nccstart.h"

/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif


/*-----------------------------------------------------------------------------
  NCC Service ID.
    - These id's are allocated by NMS Developer Support.
    - Also defined in the nccparm.h file that is generated from the
      parameter file (for example, nccparm.pf) via pf2src.
  ---------------------------------------------------------------------------*/
#define NCC_SVCID                0x1C


/*-----------------------------------------------------------------------------
  NCC Version Ids
    - These id's are used to identify the revision level of this service.
  ---------------------------------------------------------------------------*/
#define NCC_MAJORREV             1
#define NCC_MINORREV             0


/*-----------------------------------------------------------------------------
  NCC API Compatibility Level Id
    - This id is used to determine runtime compatibility between the
      installed NCC service and clients of the NCC service. Clients can
      be a CT Access application which accesses NCC functionality
      via the NCC API.
    - Clients(CT Access applications) #include this file into their code and
      insert "hard coded" values for each NCC compatability level into their
      client code.
    - The API_COMPATLEVEL is used by CT Access application developers who
      want to check the "hard coded" value in their application against the
      "hard coded" value in the installed NCC service (as determined
      via ctaGetServiceVersion() will be available in CT Access Version 2.1).
    - API compatibility level value should be incremented when the associated
      source module changes in a non-backwards compatible way. Refer to the CT
      Access Service Writer's Manual for more info.
  ---------------------------------------------------------------------------*/
#define NCCAPI_COMPATLEVEL       1


/*-----------------------------------------------------------------------------
  NCC Event Codes.
    - These codes are constructed using the NCC_SVCID, the  CT Access
      CTA_CODE_EVENT typecode, and a sequence number. The formula is
        EVENTCODE = ((NCC_SVCID<<16) | (CTA_CODE_EVENT | SEQUENCE))
    - If an event declaration is a done event 0x100 must also be ORed into
      event code.
        EVENTCODE = ((TIK_SVCID<<16) | (CTA_CODE_EVENT | 0x100 | SEQUENCE)
    - Note that the NCC Service also generates CT Access events as well;
      therefore this is not an exhaustive list of all, NCC generated,
      event codes.
  ---------------------------------------------------------------------------*/

#define NCCEVN_PROTOCOL_ERROR               0x001C2000
#define NCCEVN_ACCEPTING_CALL               0x001C2001
#define NCCEVN_ANSWERING_CALL               0x001C2002
#define NCCEVN_BILLING_INDICATION           0x001C2003
#define NCCEVN_BILLING_SET                  0x001C2004
#define NCCEVN_CALLS_BLOCKED                0x001C2005
#define NCCEVN_CALLS_UNBLOCKED              0x001C2006
#define NCCEVN_CALL_CONNECTED               0x001C2007
#define NCCEVN_CALL_DISCONNECTED            0x001C2008
#define NCCEVN_CALL_HELD                    0x001C2009
#define NCCEVN_PROTOCOL_EVENT               0x001C200A
#define NCCEVN_CALL_PROCEEDING              0x001C200B
#define NCCEVN_CALL_STATUS_UPDATE           0x001C200C
#define NCCEVN_HOLD_REJECTED                0x001C200D
#define NCCEVN_INCOMING_CALL                0x001C200E
#define NCCEVN_LINE_IN_SERVICE              0x001C200F
#define NCCEVN_LINE_OUT_OF_SERVICE          0x001C2010
#define NCCEVN_REMOTE_ALERTING              0x001C2011
#define NCCEVN_REMOTE_ANSWERED              0x001C2012
#define NCCEVN_PLACING_CALL                 0x001C2013
#define NCCEVN_REJECTING_CALL               0x001C2014
#define NCCEVN_CALL_RELEASED                0x001C2015
#define NCCEVN_CALL_RETRIEVED               0x001C2016
#define NCCEVN_RETRIEVE_REJECTED            0x001C2017
#define NCCEVN_SEIZURE_DETECTED             0x001C2018
#define NCCEVN_START_PROTOCOL_DONE          0x001C2119
#define NCCEVN_STOP_PROTOCOL_DONE           0x001C211A
#define NCCEVN_CAPABILITY_UPDATE            0x001C201B
#define NCCEVN_EXTENDED_CALL_STATUS_UPDATE  0x001C201C
#define NCCEVN_RECEIVED_DIGIT               0x001C201D
#define NCCEVN_READY_FOR_MEDIA              0x001C201E
#define NCCEVN_NOT_READY_FOR_MEDIA          0x001C201F
#define NCCEVN_BLOCK_FAILED                 0x001C2020
#define NCCEVN_UNBLOCK_FAILED               0x001C2021
#define NCCEVN_CALLID_AVAILABLE             0x001C2022
#define NCCEVN_HOLD_INDICATION              0x001C2023
#define NCCEVN_REGISTER_USER                0x001C2024
#define NCCEVN_PRACK_INDICATION             0x001C2025
#define NCCEVN_PRACK_CONFIRMATION           0x001C2026
#define NCCEVN_SUBSCRIBE                    0x001C2027
#define NCCEVN_NOTIFY                       0x001C2028
/* Number of standard NCC events. Update if more added. */
#define NCCEVN_QTY                    ((0xff & NCCEVN_NOTIFY)+1)


/*-----------------------------------------------------------------------------
  NCC Value Codes.
    - These value codes further qualify the events named above.
    - The word afer "NCC_" in the value name corresponds to the event that
      the value is associated with. For example, NCC_REJECT_HOST_TIMEOUT
      relates the the NCCEVN_REJECTING_CALL event.
    - Some of these value codes, such as NCC_ACCEPT_PLAY RING,
      NCC_ACCEPT_PLAY_SILENT and NCC_ACCEPT_USER_AUDIO, are also arguments
      to NCC functions. For example, the three value codes stated above
      are also arguments to the nccAcceptCall function.
    - These value code should all be unique with regard to one another.
    - No value code should be the same number as CTAERR_INVALID_ARGUMENT.
  ---------------------------------------------------------------------------*/

/* ---------------------------------------- */
/* NCCEVN_ACCEPTING_CALL values             */
/* ---------------------------------------- */
                              /* play a ring */
#define NCC_ACCEPT_PLAY_RING                      (0x0001)
                              /* play nothing */
#define NCC_ACCEPT_PLAY_SILENT                    (0x0002)
                              /* let user supply audio to play */
                              /* stops when call is answered   */
#define NCC_ACCEPT_USER_AUDIO                     (0x0003)
                              /* let user supply audio to play  */
                              /* continues into connected state */
#define NCC_ACCEPT_USER_AUDIO_INTO_CONNECT        (0x0004)

/* ---------------------------------------- */
/* NCCEVN_BILLING_SET values                */
/* ---------------------------------------- */
                              /* normal charged call */
#define NCC_BILLINGSET_DEFAULT                    (0xffff)
                              /* call is free */
#define NCC_BILLINGSET_FREE                       (0x0000)
                              /* call is charged, with called party control */
#define NCC_BILLINGSET_CHARGE_CPC                 (0x0008)
                              /* send a metering pulse */
#define NCC_BILLINGSET_SEND_PULSE                 (0x0009)

/* ---------------------------------------- */
/* NCCEVN_BLOCK_FAILED values               */
/* ---------------------------------------- */
                               /* block command timeout */
#define NCC_BLOCK_TIMEOUT                         (0x000A)
                               /* block command out of sequence */
#define NCC_BLOCK_OUT_OF_SEQUENCE                 (0x000B)
                               /* block command not supported */
#define NCC_BLOCK_CAPABILITY_ERROR                (0x000C)

/* ---------------------------------------- */
/* NCCEVN_CALLS_BLOCKED values              */
/* ---------------------------------------- */
                              /* don't answer subsequent calls */
#define NCC_BLOCK_REJECTALL                       (0x0010)
                              /* put the line out of service */
#define NCC_BLOCK_OUT_OF_SERVICE                  (0x0011)

/* ---------------------------------------- */
/* NCCEVN_CALL_CONNECTED values             */
/* ---------------------------------------- */
                              /* call answered via nccAnswerCall */
#define NCC_CON_ANSWERED                          (0x0020)
                              /* out-bound CED detected */
#define NCC_CON_CED                               (0x0021)
                              /* out-bound cp dialtone (may be DISA) */
#define NCC_CON_DIALTONE_DETECTED                 (0x0022)
                              /* don't run call-progress */
#define NCC_CON_PROCEEDING                        (0x0023)
                              /* out-bound ring detected */
#define NCC_CON_RING_BEGIN                        (0x0024)
                              /* out-bound ring stop(soft speaker) */
#define NCC_CON_RING_QUIT                         (0x0025)
                              /* connect by out-of-band signal */
#define NCC_CON_SIGNAL                            (0x0026)
                              /* out-bound SIT detected */
#define NCC_CON_SIT_DETECTED                      (0x0027)
                              /* out-bound timeout (hi & dry?) */
#define NCC_CON_TIMEOUT                           (0x0028)
                              /* out-bound voice detected */
#define NCC_CON_VOICE_BEGIN                       (0x0029)
                              /* out-bound voice ended */
#define NCC_CON_VOICE_END                         (0x002A)
                              /* out-bound voice extended */
#define NCC_CON_VOICE_EXTENDED                    (0x002B)
                              /* out-bound voice long */
#define NCC_CON_VOICE_LONG                        (0x002C)
                              /* out-bound voice medium */
#define NCC_CON_VOICE_MEDIUM                      (0x002D)
#define NCC_CON_TDD_DETECTED                      (0x002E)

/* ---------------------------------------- */
/* NCCEVN_CALL_DISCONNECTED values          */
/* ---------------------------------------- */
                              /* 'Place call' got busy tone */
#define NCC_DIS_BUSY                              (0x0040)
                              /* 'Place call' got CED detected */
#define NCC_DIS_CED                               (0x0041)
                              /* In-band remote disconnect */
#define NCC_DIS_CLEARDOWN_TONE                    (0x0042)
                              /* 'Place call' got reorder tone */
#define NCC_DIS_REORDER                           (0x0043)
                              /* Dial had a failure */
#define NCC_DIS_DIAL_FAILURE                      (0x0044)
                              /* 'Place call' got dialtone after dial */
#define NCC_DIS_DIALTONE                          (0x0045)
                              /* glare detected */
#define NCC_DIS_GLARE                             (0x0046)
                              /* Host did not respond in time */
#define NCC_DIS_HOST_TIMEOUT                      (0x0047)
                              /* Fault while setting up incoming call */
#define NCC_DIS_INCOMING_FAULT                    (0x0048)
                              /* Outbound call initiation not acknowledged */
#define NCC_DIS_NO_ACKNOWLEDGEMENT                (0x0049)
                              /* No CS resource to place call */
#define NCC_DIS_NO_CS_RESOURCE                    (0x004A)
                              /* No dialtone to dialing out (LPS) */
#define NCC_DIS_NO_DIALTONE                       (0x004B)
                              /* No loop current to dial out (LPS) */
#define NCC_DIS_NO_LOOP_CURRENT                   (0x004C)
                              /* Call disconnected via nccRejectCall */
#define NCC_DIS_REJECT_REQUESTED                  (0x004D)
                              /* Loop-start inbound stopped ringing */
#define NCC_DIS_REMOTE_ABANDONED                  (0x004E)
                              /* 'Place call' got no answer */
#define NCC_DIS_REMOTE_NOANSWER                   (0x004F)
                              /* 'Place call' got ring begin */
#define NCC_DIS_RING_BEGIN                        (0x0050)
                              /* 'Place call' got ringstop(soft spkr) */
#define NCC_DIS_RING_QUIT                         (0x0051)
                              /* Normal out-of-band remote disconnect. */
#define NCC_DIS_SIGNAL                            (0x0052)
                              /* the called number is not allocated */
#define NCC_DIS_UNASSIGNED_NUMBER                 (0x0053)
                              /* an unspecified disconnect signal or message */
#define NCC_DIS_SIGNAL_UNKNOWN                    (0x0054)
                              /* 'Place call' got SIT tone */
#define NCC_DIS_SIT_DETECTED                      (0x0055)
                              /* Place call' got timeout (left high & dry) */
#define NCC_DIS_TIMEOUT                           (0x0056)
                              /* Transfer completed */
#define NCC_DIS_TRANSFER                          (0x0057)
                              /* 'Place call' got voice detected */
#define NCC_DIS_VOICE_BEGIN                       (0x0058)
                              /* 'Place call' got voice ended */
#define NCC_DIS_VOICE_END                         (0x0059)
                              /* 'Place call' got voice extended */
#define NCC_DIS_VOICE_EXTENDED                    (0x005A)
                              /* 'Place call' got voice long */
#define NCC_DIS_VOICE_LONG                        (0x005B)
                              /* 'Place call' got voice medium */
#define NCC_DIS_VOICE_MEDIUM                      (0x005C)
                              /* Disconnected on protocol error */
#define NCC_DIS_PROTOCOL_ERROR                    (0x005D)
                              /* 'Place call' got network congestion */
#define NCC_DIS_CONGESTION                        (0x005E)
                              /* 'Place call' got network reject msg */
#define NCC_DIS_REJECTED                          (0x005F)
                              /* call preempted - trunk reused */
#define NCC_DIS_PREEMPTED_REUSE                   (0x0060)
                              /* call preempted - trunk not reused */
#define NCC_DIS_PREEMPTED_IDLE                    (0x0061)
 
/* ---------------------------------------- */ 
/* NCCEVN_CALL_RELEASED values              */ 
/* ---------------------------------------- */ 
                              /* Outbound call released because of glare. */
#define NCC_RELEASED_GLARE                        (0x0070)
                              /* Outbound call release becuase of an error */
#define NCC_RELEASED_ERROR                        (0x0071)

/* ------------------------------------------ */
/* NCCEVN_CALL_STATUS_UPDATE values (BIT MAP) */
/* ------------------------------------------ */

#define NCC_CALL_STATUS_CALLINGADDR     (0x0080)    /* calling number (ANI) updated */

/* --------------------------------------------------- */
/* NCCEVN_EXTENDED_CALL_STATUS_UPDATE values (BIT MAP) */
/* --------------------------------------------------- */

#define NCC_X_STATUS_INFO_UUI           (0x0001)    /* UUI field has changed        */
#define NCC_X_STATUS_INFO_PROGRESSDESCR (0x0002)    /* Progress descriptor field    */
                                                    /* has changed                  */
#define NCC_X_STATUS_INFO_CHARGE        (0x0004)    /* Charging Information         */
                                                    /* has been received            */
#define NCC_X_STATUS_INFO_CONN_NAME     (0x0008)    /* connected name received      */
#define NCC_X_STATUS_INFO_CAUSE         (0x0010)    /* releasecause has been        */
                                                    /* updated prior to clearing    */
#define NCC_X_STATUS_INFO_CONN_NUMBER   (0x0020)    /* connected number received    */
#define NCC_X_STATUS_INFO_REDIRECTING   (0x0040)    /* redirecting number received  */
#define NCC_X_STATUS_INFO_REDIRECTION   (0x0080)    /* redirection number received  */
#define NCC_X_STATUS_INFO_KEYPAD        (0x0100)    /* keypad in origcallednumber   */
#define NCC_X_STATUS_INFO_CALL_RELEASED (0x0200)    /* disconnected call has been   */
                                                    /* released by the network      */

#define NCC_EXTENDED_CALL_STATUS_CATEGORY (0x00E0)  /* For R15 CAS only, this value */
                                                    /* means CATEGORY was updated   */

/* ---------------------------------------- */
/* NCCEVN_LINE_OUT_OF_SERVICE values        */
/* ---------------------------------------- */
                              /* DID,Timed out waiting for digits */
#define NCC_OUT_OF_SERVICE_DIGIT_TIMEOUT          (0x0090)
                              /* No loop current to place calls */
#define NCC_OUT_OF_SERVICE_NO_LOOP_CURRENT        (0x0091)
                              /* Timed out waiting for remote end */
#define NCC_OUT_OF_SERVICE_PERM_SIGNAL            (0x0092)
                              /* Remote end is blocking calls */
#define NCC_OUT_OF_SERVICE_REMOTE_BLOCK           (0x0093)
                              /* OGT,Wink is too long */
#define NCC_OUT_OF_SERVICE_WINK_STUCK             (0x0094)
                              /* No digits received after seizure. */
#define NCC_OUT_OF_SERVICE_NO_DIGITS              (0x0095)
                              /* Line in inappropriate state. */
#define NCC_OUT_OF_SERVICE_LINE_FAULT             (0x0096)

/* ---------------------------------------- */
/* NCCEVN_PROTOCOL_ERROR values             */
/* ---------------------------------------- */
                              /* Caller ID information was incorrect */
#define NCC_PROTERR_BAD_CALLERID                  (0x00A0)
                              /* generic: last command unsupported */
#define NCC_PROTERR_CAPABILITY_ERROR              (0x00A1)
                              /* timeout in digit reception */
#define NCC_PROTERR_DIGIT_TIMEOUT                 (0x00A2)
                              /* DID:More digits rec'd than expected */
#define NCC_PROTERR_EXTRA_DIGITS                  (0x00A3)
                              /* invalid compelled digit received */
#define NCC_PROTERR_INVALID_DIGIT                 (0x00A4)
                              /* call setup resource unavailable */
#define NCC_PROTERR_NO_CS_RESOURCE                (0x00A5)
                              /* OGT:Answer before all digits given */
#define NCC_PROTERR_PREMATURE_ANSWER              (0x00A6)
                              /* a timeout has occurred */
#define NCC_PROTERR_TIMEOUT                       (0x00A7)
                              /* command made when call/line in wrong state */
#define NCC_PROTERR_COMMAND_OUT_OF_SEQUENCE       (0x00A8)
                              /* event received when call/line in wrong state*/
#define NCC_PROTERR_EVENT_OUT_OF_SEQUENCE         (0x00A9)
                              /* event received when seizure has been aborted*/
#define NCC_PROTERR_FALSE_SEIZURE                 (0x00AA)
                              /* two channel call transfer failed */
#define NCC_PROTERR_TCT_FAILED                    (0x00AB)

/* ---------------------------------------- */
/* NCCEVN_REJECTING_CALL values             */
/* ---------------------------------------- */
                              /* inbound call not acknowledged before timeout*/
#define NCC_REJECT_HOST_TIMEOUT                   (0x00B0)
                              /* reject inbound with busy    (if able) */
#define NCC_REJECT_PLAY_BUSY                      (0x00B1)
                              /* reject inbound with reorder (if able) */
#define NCC_REJECT_PLAY_REORDER                   (0x00B2)
                              /* reject inbound with ringtone(if able) */
#define NCC_REJECT_PLAY_RINGTONE                  (0x00B3)
                              /* reject inbound w/user audio (if able) */
#define NCC_REJECT_USER_AUDIO                     (0x00B4)

/* ---------------------------------------- */
/* NCCEVN_REMOTE_ANSWERED values            */
/* ---------------------------------------- */
                              /* due to modem detection */
#define NCC_ANSWER_MODEM                          (0x00C0)
                              /* due to out-of-band signalling */
#define NCC_ANSWER_SIGNAL                         (0x00C1)
                              /* due to voice detection */
#define NCC_ANSWER_VOICE                          (0x00C2)

/* ---------------------------------------- */
/* NCCEVN_UNBLOCK_FAILED values             */
/* ---------------------------------------- */
                               /* unblock command timeout */
#define NCC_UNBLOCK_TIMEOUT                       (0x00CA)
                               /* unblock command out of sequence */
#define NCC_UNBLOCK_OUT_OF_SEQUENCE               (0x000B)
                               /* unblock command not supported */
#define NCC_UNBLOCK_CAPABILITY_ERROR              (0x000C)

/* ---------------------------------------- */
/* NCCEVN_CALL_RETRIEVED values             */
/* ---------------------------------------- */
                              /* Automatic tranfer failed. */
#define NCC_RETRIEVED_AUTO_TRANSFER_FAILED        (0x00D0)

/* ---------------------------------------- */
/* NCCEVN_PROTOCOL_EVENT values             */
/* ---------------------------------------- */

#define NCC_PROTEVN_RING_BEGIN      (0x001) /* leading edge                 */
#define NCC_PROTEVN_RING_OK         (0x011) /* qualified as a good ring     */
#define NCC_PROTEVN_RING_END        (0x002) /* ring end after qualified     */
#define NCC_PROTEVN_RING_FALSE      (0x000) /* disqualified                 */
#define NCC_PROTEVN_RINGTONE        (0x101) /* ringtone tone qualified      */
#define NCC_PROTEVN_TONE_END        (0x110) /* tone end                     */
#define NCC_PROTEVN_TONE_BEGIN      (0x111) /* tone begin                   */
#define NCC_PROTEVN_DTMF            (0x201) /* DTMF digit received          */
#define NCC_PROTEVN_MF              (0x202) /* MF digit received            */
#define NCC_PROTEVN_R2FORWARD       (0x203) /* MFC-R2 FWD digit received    */
#define NCC_PROTEVN_R2BACKWARD      (0x204) /* MFC-R2 BACK digit received   */
#define NCC_PROTEVN_PULSE_DIGIT     (0x205) /* pulse digit received         */
#define NCC_PROTEVN_CID_ERROR       (0x301) /* CID experienced a line error */
#define NCC_PROTEVN_REANSWER        (0x400) /* re-answer signal             */
#define NCC_PROTEVN_CALL_TRACE      (0x401) /* malicious call trace invoked */
#define NCC_PROTEVN_TRUNK_OFFER     (0x403) /* trunk offer                  */
#define NCC_PROTEVN_CANCEL_OFFER    (0x404) /* cancel trunk offer           */
#define NCC_PROTEVN_RERING          (0x405) /* rering                       */

/*-----------------------------------------------------------------------------
  NCC Reason Codes.
    - NCC reason codes for events defined above.  These values are to be
      utilized in the "value" member of the event structure, so that an
      application can determine why an event occurred.

    - These codes are constructed using the NCC_SVCID, the CT Access
      CTA_CODE_REASON typecode, and a sequence number. The formula is
        REASONCODE = ((NCC_SVCID<<16) | (CTA_CODE_REASON | SEQUENCE))
  ---------------------------------------------------------------------------*/

/* ---------------------------------------- */
/* NCCEVN_START_PROTOCOL_DONE reason codes  */
/* ---------------------------------------- */
                              /* due to lack of resources */
#define NCCREASON_OUT_OF_RESOURCES            (0x001C1001)
                              /* wrong API call used to start protocol */
#define NCCREASON_WRONG_CC_METHOD             (0x001C1002)


/*-----------------------------------------------------------------------------
  NCC Error codes.
    -   Error codes are the return values for API calls for error events
        peculiar to this service.  You may wish to check ctaerr.h to see if a
        generic CT Access error code is good enough to suite your debugging
        needs.
    - These codes are constructed using the NCC_SVCID, the CT Access
      CTA_CODE_ERROR typecode, and a sequence number. The formula is
         ERRORCODE = ((NCC_SVCID<<16) | (CTA_CODE_ERROR | SEQUENCE))
  ---------------------------------------------------------------------------*/
#define NCCERR_NOT_CAPABLE                    (0x001C0001)
#define NCCERR_INVALID_CALL_STATE             (0x001C0002)
#define NCCERR_ADDRESS_BLOCKED                (0x001C0003)
#define NCCERR_NO_CALLID                      (0x001C0004)

/**/
/*-----------------------------------------------------------------------------
  Exported API Data Structures & Types
  - Definition of data structures exposed via NCC API
  ---------------------------------------------------------------------------*/

/* Constants used in NCC -------------------- */
#define NCC_MAX_DIGITS                      (31)
#define NCC_MAX_CALLING_NAME                (63)
#define NCC_MAX_PROT_NAME                   (31)

/* NCC call handle -------------------------- */
typedef DWORD NCC_CALLHD;
#define NULL_NCC_CALLHD (0X0)

/* nccAutomaticTransfer transferwhen values - */
#define NCC_TRANSFER_PROCEEDING              (1)
#define NCC_TRANSFER_ALERTING                (2)
#define NCC_TRANSFER_CONNECTED               (3)

/* Call states ------------------------------ */
#define NCC_CALLSTATE_INVALID              (0x0)
#define NCC_CALLSTATE_SEIZURE              (0x1)
#define NCC_CALLSTATE_RECEIVING_DIGITS     (0x2)
#define NCC_CALLSTATE_INCOMING             (0x3)
#define NCC_CALLSTATE_ACCEPTING            (0x4)
#define NCC_CALLSTATE_ANSWERING            (0x5)
#define NCC_CALLSTATE_REJECTING            (0x6)
#define NCC_CALLSTATE_CONNECTED            (0x7)
#define NCC_CALLSTATE_DISCONNECTED         (0x8)
#define NCC_CALLSTATE_OUTBOUND_INITIATED   (0x9)
#define NCC_CALLSTATE_PLACING              (0xA)
#define NCC_CALLSTATE_PROCEEDING           (0xB)
#define NCC_CALLSTATE_CALL_ANSWERED        (0xC)
/* Number of NCC call states. Update if more added. */
#define NCC_CALLSTATE_QTY                  (NCC_CALLSTATE_CALL_ANSWERED+1)

/* Pending call commands -------------------- */
/* Pending command values for a call must NEVER
   have the 0x100 bit set. */
#define NCC_PENDINGCMD_ACCEPT_CALL        (0x01)
#define NCC_PENDINGCMD_ANSWER_CALL        (0x02)
#define NCC_PENDINGCMD_AUTOMATIC_TRANSFER (0x03)
#define NCC_PENDINGCMD_DISCONNECT_CALL    (0x04)
#define NCC_PENDINGCMD_HOLD_CALL          (0x05)
#define NCC_PENDINGCMD_PLACE_CALL         (0x06)
#define NCC_PENDINGCMD_REJECT_CALL        (0x07)
#define NCC_PENDINGCMD_RETRIEVE_CALL      (0x08)
#define NCC_PENDINGCMD_SET_BILLING        (0x09)
#define NCC_PENDINGCMD_TRANSFER_CALL      (0x0A)
#define NCC_PENDINGCMD_RELEASE_CALL       (0x0B)
#define NCC_PENDINGCMD_REGISTER_USER      (0x0C)
#define NCC_PENDINGCMD_ACKNOWLEDGE_CALL   (0x0D)

/* Direction of a call ---------------------- */
#define NCC_CALL_INBOUND                     (0)
#define NCC_CALL_OUTBOUND                    (1)

/* Call status structure -------------------- */
typedef struct
{
    DWORD          size;
    DWORD          state;
    char           calledaddr [NCC_MAX_DIGITS+1];
    char           callingaddr [NCC_MAX_DIGITS+1];
    char           callingname [NCC_MAX_CALLING_NAME+1];
    DWORD          pendingcmd;
    DWORD          held;
    DWORD          direction;
    CTAHD          linehd;
} NCC_CALL_STATUS;

/* Line states ------------------------------ */
#define NCC_LINESTATE_UNINITIALIZED        (0x0)
#define NCC_LINESTATE_IDLE                 (0x1)
#define NCC_LINESTATE_BLOCKING             (0x2)
#define NCC_LINESTATE_OUT_OF_SERVICE       (0x3)
#define NCC_LINESTATE_ACTIVE               (0x4)
/* Number of NCC line states. */
#define NCC_LINESTATE_QTY                  (NCC_LINESTATE_ACTIVE+1)
#define NCC_LINESTATE_INVALID              (0xffffffff)

/* Pending line commands -------------------- */
/* The 0x100 bit is set to indicate that this is
   a pending command for a line, not a call. */
#define NCC_PENDINGCMD_BLOCK_CALLS     (0x101)
#define NCC_PENDINGCMD_UNBLOCK_CALLS   (0x102)
#define NCC_PENDINGCMD_START_PROTOCOL  (0x103)
#define NCC_PENDINGCMD_STOP_PROTOCOL   (0x104)

/* Line status structure -------------------- */
typedef struct
{
    DWORD           size;
    DWORD           state;
    DWORD           pendingcmd;
    char            protocol [NCC_MAX_PROT_NAME+1];
    CTA_MVIP_ADDR   port;
    unsigned        numcallhd;
} NCC_LINE_STATUS;

/* Protocol capabilities structure ----------- */
typedef struct
{
    DWORD size;
    DWORD capabilitymask;
} NCC_PROT_CAP;

/* capabilitymask bit definition ------------- */
/* NOTE: All undefined bits in the capabilitymask definition are RESERVED  ---*/

/* The following capability indications allow the corresponding functions     */
#define NCC_CAP_ACCEPT_CALL                 (0x1) /* nccAcceptCall            */
#define NCC_CAP_SET_BILLING                 (0x2) /* nccSetBilling            */
#define NCC_CAP_OVERLAPPED_SENDING          (0x4) /* nccSendDigit             */
#define NCC_CAP_HOLD_RESPONSE               (0x8) /* nccHoldResponse          */

#define NCC_CAP_HOLD_CALL                  (0x10) /* nccHoldCall              */
#define NCC_CAP_SUPERVISED_TRANSFER        (0x20) /* nccTransferCall          */
#define NCC_CAP_AUTOMATIC_TRANSFER         (0x40) /* nccAutomaticTransfer     */
#define NCC_CAP_TWOCHANNEL_TRANSFER        (0x80) /* nccTransferCall          */

#define NCC_CAP_EXTENDED_CALL_STATUS      (0x100) /* nccGetExtendedCallStatus */
#define NCC_CAP_SEND_CALL_MESSAGE         (0x200) /* nccSendCallMessage       */
#define NCC_CAP_SEND_LINE_MESSAGE         (0x400) /* nccSendLineMessage       */

/* The following capability indications allow the corresponding functions
   in all callstates, if not set these functions may only be executed while
   the call is in NCC_CALLSTATE_CONNECTED                              */
#define NCC_CAP_HOLD_IN_ANY_STATE        (0x1000) /* nccHoldCall       */
#define NCC_CAP_DISCONNECT_IN_ANY_STATE  (0x2000) /* nccDisconnectCall */

/* The following capability indications signify support of the following feature: */
/* - the execution of adi media functions during call setup */
#define NCC_CAP_MEDIA_IN_SETUP          (0x10000)
/* - the availability of caller id information in the call status */
#define NCC_CAP_CALLER_ID               (0x20000)
#define NCC_CAP_REGISTER_USER           (0x40000)
#define NCC_CAP_ACKNOWLEDGE_CALL        (0x80000)

//  NOTE:  in nccsys.h, no call control capability is to be 0x100000
//
// #define NCC_CAP_NO_CALL_CONTROL      (0x100000)
//
#define NCC_CAP_PRACK_CAPABLE           (0x200000)
#define NCC_CAP_SUBSCRIBE_CAPABLE       (0x400000)


/* Meanings for ncc.start.eventmask bits ----- */
#define NCC_REPORT_ALERTING         0x0004 /* NCCEVN_REMOTE_ALERTING    */
#define NCC_REPORT_ANSWERED         0x0008 /* NCCEVN_REMOTE_ANSWERED    */
#define NCC_REPORT_BILLING          0x0020 /* NCCEVN_BILLING_INDICATION */
#define NCC_REPORT_STATUSINFO       0x0040 /* NCCEVN_CALL_STATUS_UPDATE */
#define NCC_REPORT_ANSSUP           0x0080 /* NCCEVN_REMOTE_ANSWERED for Answer Supervision */
#define NCC_REPORT_HOLD_INDICATION  0x0100 /* NCCEVN_HOLD_INDICATION    */
#define NCC_REPORT_CALLID          0x10000 /* NCCEVN_CALLID_AVAILABLE   */

/**/
/*-----------------------------------------------------------------------------
  NCC Service API function prototypes.
  ---------------------------------------------------------------------------*/

DWORD NMSAPI nccAcceptCall(NCC_CALLHD callhd,
                           unsigned mode,
                           void* acceptparms);

DWORD NMSAPI nccAnswerCall(NCC_CALLHD callhd,
                           unsigned num_rings,
                           void* answerparms);

DWORD NMSAPI nccAutomaticTransfer(NCC_CALLHD callhd,
                                  char* digitstr,
                                  unsigned transferwhen,
                                  void* transferparms,
                                  void* mgrcallparms,
                                  void* protcallparms);

DWORD NMSAPI nccBlockCalls(CTAHD linehd, unsigned blockmode, void* blockparms);

DWORD NMSAPI nccDisconnectCall(NCC_CALLHD callhd, void* disconnectparms);

DWORD NMSAPI nccGetCallStatus(NCC_CALLHD callhd,
                              NCC_CALL_STATUS* callstatus,
                              unsigned size);

DWORD NMSAPI nccGetExtendedCallStatus(NCC_CALLHD callhd,
                                      void* extendedcallstatus,
                                      unsigned size);

DWORD NMSAPI nccGetLineStatus(CTAHD linehd,
                              NCC_LINE_STATUS* linestatus,
                              unsigned linestatussize,
                              NCC_CALLHD* callhd,
                              unsigned callhdsize);

DWORD NMSAPI nccHoldCall(NCC_CALLHD callhd, void* holdparms);

DWORD NMSAPI nccHoldResponse(NCC_CALLHD callhd, unsigned respondhow, void* holdresponseparms);

DWORD NMSAPI nccPlaceCall(CTAHD linehd,
                          char* calledaddr,
                          char* callingaddr,
                          void* mgrcallparms,
                          void* protcallparms,
                          NCC_CALLHD* callhd);

DWORD NMSAPI nccQueryCapability(CTAHD linehd,
                                NCC_PROT_CAP* protcap,
                                unsigned size);

DWORD NMSAPI nccRejectCall(NCC_CALLHD callhd,
                           unsigned method,
                           void* rejectparms);

DWORD NMSAPI nccReleaseCall(NCC_CALLHD callhd, void* releaseparms);

DWORD NMSAPI nccRetrieveCall(NCC_CALLHD callhd, void* retrieveparms);

DWORD NMSAPI nccSendCallMessage(NCC_CALLHD callhd,
                                void* message,
                                unsigned size);

DWORD NMSAPI nccSendDigits(NCC_CALLHD callhd,
                           char* digits,
                           void* senddigitparms);

DWORD NMSAPI nccSendLineMessage(CTAHD linehd, void* message, unsigned size);

DWORD NMSAPI nccSetBilling(NCC_CALLHD callhd,
                           unsigned rate,
                           void* billingparms);

DWORD NMSAPI nccStartProtocol(CTAHD linehd,
                              char* protname,
                              NCC_START_PARMS* startparms,
                              void* mgrstartparms,
                              void* protstartparms);

DWORD NMSAPI nccStopProtocol(CTAHD linehd,
                             void* stopparms);

DWORD NMSAPI nccTransferCall(NCC_CALLHD callhd1,
                             NCC_CALLHD callhd2,
                             void* transferparms);

DWORD NMSAPI nccUnblockCalls(CTAHD ctahd, void* unblockparms);

//  The following are SIP specific extensions to NCC

DWORD NMSAPI nccRegisterUser(CTAHD linehd, void* sipIEs);

DWORD NMSAPI nccAcknowledgeCall(NCC_CALLHD callhd, void* sipIEs);

DWORD NMSAPI nccSendPrack(NCC_CALLHD callhd, void* sipIEs);

DWORD NMSAPI nccSendPrackResponse(NCC_CALLHD callhd, void* sipIEs);

DWORD NMSAPI nccSubscribe(CTAHD linehd, void* sipIEs);

#ifdef __cplusplus
}
#endif


#endif /* NCCDEF_INCLUDED */

