/***************************************************************************\
*
* FILENAME:     isdnparm.h
*
* DESCRIPTION:  ISDN Interface file
*
* Copyright 1996-97 by Natural Microsystems.  All rights reserved.
*
\***************************************************************************/

#ifndef ISDNPARM_H
#define ISDNPARM_H  1

#ifdef __cplusplus
extern "C" {
#endif

#include "isdntype.h"

/* -------------------------------------------------------------------------- */
/* -------------------------- System Limits  -------------------------------- */
/* -------------------------------------------------------------------------- */

#define MAX_ISDN_SUBMITTED_BUFFERS  15
#define MAX_ISDN_BUFFER_SIZE        ISDN_BUFFER_DATA_LGTH
#define MAX_ISDN_HDLC_CHANNELS      2
#define MAX_NAI_QUAD                4         /* 1 Valid network interface */
#define MAX_NAI_DUAL                2         /* 1 Valid network interface */
#define MAX_NAI_AG                  1         /* 1 Valid network interface */

#define ISDN_USERID_ASYNC          0xFFFFFFFF

#ifndef CC_QSIG_MX_ADDR_SIZE
#   define CC_QSIG_MX_ADDR_SIZE    5
#endif

#define NFAS_GROUP_NIL 0xFF

/* -------------------------------------------------------------------------- */
/* -------------------------- Supported Protocol ---------------------------- */
/* -------------------------------------------------------------------------- */

#define ISDN_PROTOCOL_LAPD    4        /* Raw LAP-D protocol */
#define ISDN_PROTOCOL_Q931CC  5        /* ISDN call control */
#define ISDN_PROTOCOL_CHANNELIZED 6    /* Channelized ISDN */


/* -------------------------------------------------------------------------- */
/* -------------------------- Message Information Structure ----------------- */
/* -------------------------------------------------------------------------- */
/*#pragma pack(4)*/
typedef struct ISDN_MESSAGE
{
    nai_t nai;         /* Network access interface index */
    ent_id_t from_ent; /* Message source */
    ent_id_t to_ent;   /* Message destination */
    sapi_t to_sapi;    /* Destination Service Access Point */
    union {
    add_t conn_id; /* Connection identifier for ACU layer */
    add_t crv;     /* Call Reference value for NS layer (not exposed)  */
    add_t ces;     /* Connection Endpoint suffix (DL later upper half) */
    add_t tei;     /* Terminal Endpoint identifier (not exposed) */
    add_t chani;   /* Physical layer channel identifier (not exposed) */
    } add;
    code_t code;     /* Primitive code unique only between two entities */
    WORD inf0;       /* Information location 0 */
    WORD inf1;       /* Information location 1 */
    WORD inf2;       /* Information location 2 */
    WORD inf3;       /* Information location 3 */
    WORD inf4;       /* Information location 4 */
    WORD data_size;  /* Size of data to follow */

    WORD nfas_group; /* NFAS group number if duplicate NAI values       */
    DWORD userid;
} ISDN_MESSAGE;
/*#pragma pack()*/



typedef struct ISDN_PACKET
{
    ISDN_MESSAGE message;     /* ISDN message ideftification information */
    BYTE data[4];             /* Data included in packet >=0 */
} ISDN_PACKET;


/* ------------------------------------------------------------------------- */
/* -------------------------- Physical Layer Data Rates -------------------- */
/* ------------------------------------------------------------------------- */
#define ISDN_RATE_64K   0     /* 64 kbps rate */
#define ISDN_RATE_56K   1     /* 56 kbps rate */


/* ------------------------------------------------------------------------- */
/* -------------------------- Network Operators ---------------------------- */
/* ------------------------------------------------------------------------- */

#define ISDN_OPERATOR_FT_VN6 3        /* France Telecom VN6 */
#define ISDN_OPERATOR_ATT_4ESS  24    /* AT&T 4ESS */
#define ISDN_OPERATOR_NT_DMS 8        /* Northern Telecom DMS100 */
#define ISDN_OPERATOR_NTT 9           /* Nippon Telegraph Telephone */
#define ISDN_OPERATOR_ETSI 11         /* European ETSI Technical Comittee */
#define ISDN_OPERATOR_AUSTEL_1 15     /* Australian Telecom 1 */
#define ISDN_OPERATOR_ECMA_QSIG 16    /* ECMA 143 QSIG */
#define ISDN_OPERATOR_HK_TEL 17       /* Hong Kong Telephone */
#define ISDN_OPERATOR_NI2 20          /* US National ISDN 2 */
#define ISDN_OPERATOR_ATT_5E10 23     /* ARINC CTU to Bearer Systems (BS) -
                                            ARINC 746 attachment 11 */
#define ISDN_OPERATOR_ATT_5E9 ISDN_OPERATOR_ATT_5E10
#define ISDN_OPERATOR_KOREAN_OP 25   /* Korean Operator */
#define ISDN_OPERATOR_TAIWAN_OP 50   /* Taiwanese Operator */


/* ------------------------------------------------------------------------- */
/* -------------------------- Network Country Codes ------------------------ */
/* ------------------------------------------------------------------------- */

 #define COUNTRY_AUS        61
 #define COUNTRY_BEL        32
 #define COUNTRY_EUR        1000
 #define COUNTRY_FRA        33
 #define COUNTRY_GER        49
 #define COUNTRY_HONG_KONG  852
 #define COUNTRY_JPN        81
 #define COUNTRY_KOREA      82
 #define COUNTRY_SINGAPORE  65
 #define COUNTRY_SWE        46
 #define COUNTRY_CHINA      86
 #define COUNTRY_TAIWAN     886
 #define COUNTRY_GBR        44
 #define COUNTRY_USA        1


/* ------------------------------------------------------------------------- */
/* -------------------------- Network Signaling Timers --------------------- */
/* ------------------------------------------------------------------------- */

typedef enum TIMERS_AT4         /* Not used */
{
    AT4_T300=0,
    AT4_T303=1,
    AT4_T305=2,
    AT4_T306=3,
    AT4_T308=4,
    AT4_T310=5,
    AT4_T313=6,
    AT4_T309=7,
    AT4_T_LAST            /* Place holder-- don't use */
} TIMERS_AT4;

typedef enum TIMERS_AT5         /* Not used */
{
    AT5_T300=0,
    AT5_T302=1,
    AT5_T303=2,
    AT5_T305=3,
    AT5_T308=4,
    AT5_T310=5,
    AT5_T309=6,
    AT5_T_LAST
} TIMERS_AT5;

typedef enum TIMERS_AT9
{
    AT9_T300=0,
    AT9_T301=1,
    AT9_T302=2,
    AT9_T303=3,
    AT9_T305=4,
    AT9_T306=5,
    AT9_T308=6,
    AT9_T310=7,
    AT9_T313=8,
    AT9_T309=9,
    AT9_T_LAST
} TIMERS_AT9;

typedef enum TIMERS_DMS
{
    DMS_T300=0,
    DMS_T301=1,
    DMS_T303=2,
    DMS_T305=3,
    DMS_T308=4,
    DMS_T310=5,
    DMS_T312=6,
    DMS_T313=7,
    DMS_T322=8,
    DMS_T309=9,
    DMS_T_LAST
} TIMERS_DMS;

typedef enum TIMERS_E10
{
    E10_T300=0,
    E10_T303=1,
    E10_T305=2,
    E10_T306=3,
    E10_T308=4,
    E10_T310=5,
    E10_T313=6,
    E10_T309=7,
    E10_T_LAST
} TIMERS_E10;

typedef enum TIMERS_KOR     /* timers for Korea and taiwan */
{
    KOR_T300=0,
    KOR_T301=1,
    KOR_T302=2,
    KOR_T303=3,
    KOR_T304=4,
    KOR_T305=5,
    KOR_T306=6,
    KOR_T307=7,
    KOR_T308=8,
    KOR_T310=9,
    KOR_T312=10,
    KOR_T313=11,
    KOR_T318=12,
    KOR_T319=13,
    KOR_T320=14,
    KOR_T321=15,
    KOR_T322=16,
    KOR_T309=17,
    KOR_T_HOLD=18,
    KOR_T_RET=19,
    KOR_T_LAST
} TIMERS_KOR;

typedef enum TIMERS_NI1         /* Not used */
{
    NI1_T300=0,
    NI1_T301=1,
    NI1_T303=2,
    NI1_T305=3,
    NI1_T308=4,
    NI1_T310=5,
    NI1_T312=6,
    NI1_T313=7,
    NI1_T322=8,
    NI1_T309=9,
    NI1_T_LAST
} TIMERS_NI1;

typedef enum TIMERS_NI2     
{
    NI2_T300=0,
    NI2_T301=1,
    NI2_T302=2,
    NI2_T303=3,
    NI2_T305=4,
    NI2_T306=5,
    NI2_T308=6,
    NI2_T310=7,
    NI2_T313=8,
    NI2_T309=9,
    NI2_T_LAST
} TIMERS_NI2;

typedef enum TIMERS_AU1
{
    AU1_T300=0,
    AU1_T302=1,
    AU1_T303=2,
    AU1_T304=3,
    AU1_T305=4,
    AU1_T306=5,
    AU1_T308=6,
    AU1_T310=7,
    AU1_T312=8,
    AU1_T313=9,
    AU1_T322=10,
    AU1_T309=11,
    AU1_T_LAST
} TIMERS_AU1;

typedef enum TIMERS_HKT
{
    HKT_T300=0,
    HKT_T301=1,
    HKT_T302=2,
    HKT_T303=3,
    HKT_T304=4,
    HKT_T305=5,
    HKT_T306=6,
    HKT_T307=7,
    HKT_T308=8,
    HKT_T310=9,
    HKT_T312=10,
    HKT_T313=11,
    HKT_T318=12,
    HKT_T319=13,
    HKT_T320=14,
    HKT_T321=15,
    HKT_T322=16,
    HKT_T309=17,
    HKT_T_LAST
} TIMERS_HKT;

typedef enum TIMERS_KDD         /* Not used */
{
    KDD_T300=0,
    KDD_T303=1,
    KDD_T305=2,
    KDD_T308=3,
    KDD_T310=4,
    KDD_T313=5,
    KDD_T322=6,
    KDD_T309=7,
    KDD_T_LAST
} TIMERS_KDD;

typedef enum TIMERS_NTT
{
    NTT_T300=0,
    NTT_T301=1,
    NTT_T303=2,
    NTT_T305=3,
    NTT_T306=4,
    NTT_T307=5,
    NTT_T308=6,
    NTT_T310=7,
    NTT_T312=8,
    NTT_T313=9,
    NTT_T318=10,
    NTT_T319=11,
    NTT_T322=12,
    NTT_T3JA=13,
    NTT_T309=14,
    NTT_T_LAST
} TIMERS_NTT;

typedef enum TIMERS_BT2         /* Not used */
{
    BT2_T300=0,
    BT2_T301=1,
    BT2_T302=2,
    BT2_T303=3,
    BT2_T304=4,
    BT2_T305=5,
    BT2_T306=6,
    BT2_T307=7,
    BT2_T308=8,
    BT2_T310=9,
    BT2_T312=10,
    BT2_T313=11,
    BT2_T318=12,
    BT2_T319=13,
    BT2_T320=14,
    BT2_T30Y=15,
    BT2_T309=16,
    BT2_T_LAST
} TIMERS_BT2;

typedef enum TIMERS_BV1         /* Not used */
{
    BV1_T300=0,
    BV1_T303=1,
    BV1_T305=2,
    BV1_T307=3,
    BV1_T308=4,
    BV1_T310=5,
    BV1_T312=6,
    BV1_T313=7,
    BV1_T318=8,
    BV1_T319=9,
    BV1_T3CW=10,
    BV1_T_LAST
} TIMERS_BV1;

typedef enum TIMERS_ETS
{
    ETS_T300=0,
    ETS_T301=1,
    ETS_T302=2,
    ETS_T303=3,
    ETS_T304=4,
    ETS_T305=5,
    ETS_T306=6,
    ETS_T307=7,
    ETS_T308=8,
    ETS_T310=9,
    ETS_T312=10,
    ETS_T313=11,
    ETS_T318=12,
    ETS_T319=13,
    ETS_T320=14,
    ETS_T321=15,
    ETS_T322=16,
    ETS_T309=17,
    ETS_T_LAST
} TIMERS_ETS;

typedef enum TIMERS_QSI
{
    QSI_T300=0,
    QSI_T301=1,
    QSI_T302=2,
    QSI_T303=3,
    QSI_T304=4,
    QSI_T305=5,
    QSI_T308=6,
    QSI_T310=7,
    QSI_T313=8,
    QSI_T322=9,
    QSI_T309=10,
    QSI_T_LAST
} TIMERS_QSI;

typedef enum TIMERS_SWD         /* Not used */
{
    SWD_T300=0,
    SWD_T302=1,
    SWD_T303=2,
    SWD_T304=3,
    SWD_T305=4,
    SWD_T306=5,
    SWD_T308=6,
    SWD_T310=7,
    SWD_T313=8,
    SWD_T320=9,
    SWD_T391=10,
    SWD_T397=11,
    SWD_T_LAST
} TIMERS_SWD;

typedef enum TIMERS_TR6         /* Not used */
{
    TR6_T300=0,
    TR6_T302=1,
    TR6_T303=2,
    TR6_T304=3,
    TR6_T305=4,
    TR6_T307=5,
    TR6_T308=6,
    TR6_T310=7,
    TR6_T313=8,
    TR6_T318=9,
    TR6_T319=10,
    TR6_T3D2=11,
    TR6_T3AA=12,
    TR6_T3AB=13,
    TR6_T3AC=14,
    TR6_T3AD=15,
    TR6_T3AG=16,
    TR6_T_LAST
} TIMERS_TR6;

typedef enum TIMERS_VN2         /* Not used */
{
    VN2_T300=0,
    VN2_T302=1,
    VN2_T303=2,
    VN2_T304=3,
    VN2_T305=4,
    VN2_T307=5,
    VN2_T308=6,
    VN2_T310=7,
    VN2_T313=8,
    VN2_T318=9,
    VN2_T319=10,
    VN2_T399=11,
    VN2_T309=12,
    VN2_T_LAST
} TIMERS_VN2;

typedef enum TIMERS_VN3         /* Not used */
{
    VN3_T300=0,
    VN3_T302=1,
    VN3_T303=2,
    VN3_T304=3,
    VN3_T305=4,
    VN3_T307=5,
    VN3_T308=6,
    VN3_T310=7,
    VN3_T313=8,
    VN3_T318=9,
    VN3_T319=10,
    VN3_T322=11,
    VN3_T399=12,
    VN3_T309=13,
    VN3_T_LAST
} TIMERS_VN3;

typedef enum TIMERS_VN6
{
    VN6_T300=0,
    VN6_T301=1,
    VN6_T302=2,
    VN6_T303=3,
    VN6_T304=4,
    VN6_T305=5,
    VN6_T306=6,
    VN6_T307=7,
    VN6_T308=8,
    VN6_T310=9,
    VN6_T312=10,
    VN6_T313=11,
    VN6_T318=12,
    VN6_T319=13,
    VN6_T320=14,
    VN6_T321=15,
    VN6_T322=16,
    VN6_T399=17,
    VN6_T309=18,
    VN6_T_LAST
} TIMERS_VN6;


/* ------------------------------------------------------------------------- */
/* -------------------------- Equipment Types ------------------------------ */
/* ------------------------------------------------------------------------- */
#define EQUIPMENT_TE   1               /* Terminal Equipment (TE1, TE2) */
#define EQUIPMENT_DTE EQUIPMENT_TE     /* Data Terminal Equipment */
#define EQUIPMENT_NT   2               /* Network Termination (NT1, NT2) */
#define EQUIPMENT_DCE EQUIPMENT_NT     /* Data Circuit Terminating equipment */

/* ------------------------------------------------------------------------- */
/* -------------------------- LAPD Parms ----------------------------------- */
/* ------------------------------------------------------------------------- */

typedef struct ISDN_PROTOCOL_PARMS_LAPD
{
    DWORD size;                /* Size of this structure */

    timer_val_t  t101;
    timer_val_t  t102;
    timer_val_t  t198;         /* Observation period for Frame error count  */

    WORD rate;                 /* Data rate */

    WORD max_FEC_errors;       /* Maximum number of FEC during t198 */

    /*
    ** When to assign/remove a TEI
    */
    WORD tei_time_assignment;     /* TEI time assignment at : CONFIGURATION,
                                     NA ACTIVATION or USAGE time (isdndl.h) */
    WORD tei_time_removal;        /* TEI time removal at    : NA DEACTIVATION,
                                         POWER DOWN (dlint.h) */
    BYTE tei[3];                  /* tei values:
                                     0     :      broadcast
                                     1-63  :      Non automatic TEI assignment
                                     127   :      Automatic TEI assignment */
    BYTE bpad[1];                 /* for 8 bytes alignement */
                                  /* size is now 32 bytes */

    WORD nfas_group;              /* NFAS group number if duplicate NAI values */
    BYTE bpad1[2];                /* for 8 bytes alignement */
                                  /* size is now 32 bytes */

} ISDN_PROTOCOL_PARMS_LAPD;


/* ------------------------------------------------------------------------- */
/* -------------------------- Call Control Parms --------------------------- */
/* ------------------------------------------------------------------------- */

/*****************************************************************************
        Incoming calls behaviour:
        This configuration field is a 16-bits field (0-15):

        - bit #0 is reserved for compatibilty with former 'auto_answer' field
          values (ON/OFF).

        - CC_SEND_ALERT_IN bit: (bit #1)
            automatic sending of ACU_ALERT_IN after ACU_CONN_IN:
            if this bit is set, then the stack generates an ACU_ALERT_IN
            after having sent an ACU_CONN_IN. This message is used to keep
            compatibility with DTE_INT entity.

        - CC_SEND_CALL_PROC_RQ bit: (bit #2)
            automatic sending of a CALL PROCEEDING on incoming calls:
            if this bit is set, then the stack sends a CALL PROCEEDING on
            an incoming call. Otherwise, the application will have to send
            ACU_CALL_PROC_RQ for this (this message is optional anyway).

        - CC_DATA_ALERT_RQ bit: (bit #3)
            automatic sending of an ALERTING on not TELEPHONY incoming calls:
            if this bit is set, then the stack sends an ALERTING on a
            NOT TELEPHONY incoming call.

        - CC_VOICE_ALERT_RQ bit: (bit #4)
            automatic sending of an ALERTING on TELEPHONY incoming calls:
            if this bit is set, then the stack sends an ALERTING on a TELEPHONY
            incoming call.

        - CC_DATA_CONN_RS bit: (bit #5)
            automatic answering on NOT TELEPHONY incoming calls:
            if this bit is set, then the stack sends an CONNECT on
            NOT TELEPHONY incoming calls.

        - CC_VOICE_CONN_RS bit: (bit #6)
            automatic answering on TELEPHONY incoming calls:
            if this bit is set, then the stack sends an CONNECT on
            TELEPHONY incoming calls.

        - CC_TRANSPARENT_OVERLAP_RCV bit: (bit #7)
            transparent processing of overlap receiving mode:
            if this bit is set, then the stack sends an ACU_CONN_IN to the user
            even if the number is not full (i.e. the 'Sending Complete' IE
            is not present); and the stack sends the additional incoming digits
            into ACU_DIGIT_IN messages.
            If this bit is not set, then the stack waits for at least
            'nb_digits_to_route' digits (see the configuration structure) to
            come in before sending an ACU_CONN_IN message to the user.
            The additional digits coming into INFORMATION messages are ignored.

        - CC_TRUNCATE_NB bit: (bit #8)
            meaningful only in buffered Overlap Receiving mode.
            If this bit is set, then the called number is truncated to the
            number of digits specified by the 'nb_digits_to_route'
            configuration field.

        - CC_CALLED_NB_ABSENT_MATCH bit: (bit #9)
            If this bit is set, then a received incoming call with no called
            number will match a list with a programmed address.
            If this bit is not set, then a received incoming call with no
            called number will not match a list with a programmed address.

        - CC_CALL_WAITING bit: (bit #10)
            If this bit is set, then the stack will support the 'Call-Waiting'
            Supplementary Service: a incoming call received with a channel-id
            indicating 'No-channel' will be accepted by the stack
            If this bit is not set, then the stack will reject these calls
            with the appropriate cause value (#34 in most cases).


        - CC_DISABLE_SUPPLEMENTARY_SERVICES bit: (bit #12)
            If this bit is set, then the stack will not attempt to decode the
            IEs associated with supplementary services (Facility and Notify)
            and take appropriate actions.
            If this bit is not set, then the stack will process the IEs
            associated with supplementary services

        - CC_SET_CHAN_ID bit: (bit #13)
            if this bit is set, then CC force the Channel Id Information
            Element to be present in the first message in response to a SETUP
            even if the specs do not consider that mandatory

        - CC_BEHAVIOUR_NIL bit: (bit #15)
            if this bit is set, then the stack acts as if none of the previous
            bits where set.

        The default value if this field is set to 0 (=OFF) is:
        CC_VOICE_ALERT_RQ | CC_DATA_ALERT_RQ if partner_equipment = EQUIPMENT_NT
        
        CC_SEND_CALL_PROC_RQ if partner_equipment = EQUIPMENT_TE
*/

#define CC_SEND_ALERT_IN            0x0002  /* bit #1 */
#define CC_SEND_CALL_PROC_RQ        0x0004  /* bit #2 */
#define CC_DATA_ALERT_RQ            0x0008  /* bit #3 */
#define CC_VOICE_ALERT_RQ           0x0010  /* bit #4 */
#define CC_DATA_CONN_RS             0x0020  /* bit #5 */
#define CC_VOICE_CONN_RS            0x0040  /* bit #6 */
#define CC_TRANSPARENT_OVERLAP_RCV  0x0080  /* bit #7 */
#define CC_TRUNCATE_NB              0x0100  /* bit #8 */
#define CC_CALLED_NB_ABSENT_MATCH   0x0200  /* bit #9 */
#define CC_CALL_WAITING             0x0400  /* bit #10 */
#define CC_DISABLE_SUPPLEMENTARY_SERVICES   0x1000  /* bit #12 */
#define CC_SET_CHAN_ID              0x2000  /* bit #13 */

#define CC_BEHAVIOUR_NIL            0x8000  /* bit #15: reserved for 'NIL' value */


/*****************************************************************************
        Outgoing calls behaviour:
        This configuration field is a 16-bits field (0-15):

        - bit #0 is reserved for compatibility with former field values (ON/OFF).

        - CC_USER_SENDING_COMPLETE bit: (bit #1)
            automatic generation of 'Sending-complete' information element
            in ACU_CONN_RQ:
            if this bit is set, then the stack does not generate automatically
            the 'Sending-complete' information element: the user application
            must request it in the ACU_CONN_RQ primitive. Otherwise, the stack
            will generate it automatically in the ACU_CONN_RQ only.
            This bit does not affect the ACU_DIGIT_RQ primitive (the user
            application must specify explicitly the
            'Acu_digit_rq_sending_complete' field value).

        - CC_SEND_CONN_CO_ON_PROGRESS bit: (bit #2)
            if this bit is set, then the stack sends ACU_CONN_CO when it receives
            a PROGRESS message for a VOICE call;

        - CC_SEND_DIGIT_CO_ON_PROGRESS bit: (bit #3)
            if this bit is set, then the stack sends ACU_DIGIT_CO before
            ACU_CALL_PROC_IN when it receives a CALL PROCEEDING without having
            received a SETUP ACK before, otherwise it only sends
            ACU_CALL_PROC_IN (default behaviour).

        - CC_USE_MU_LAW bit: (bit #4)
            !!! For KOREAN operator only !!!
            - bit set:     the stack sends G711-Mu-Law in outgoing voice calls
            - bit cleared: the stack sends G711-A-Law  in outgoing voice calls.

        - CC_USE_A_LAW bit: (bit #5)
            !!! For Taiwanese operator only !!!
            - bit set:     the stack sends G711-A-Law in outgoing voice calls
            - bit cleared: the stack sends G711-Mu-Law  in outgoing voice calls.

        - CC_BEHAVIOUR_NIL bit: (bit #15)
            if this bit is set, then the stack acts as if none of the previous
            bits where set.

        The default value if this field is set to 0 (=OFF) is:
        CC_BEHAVIOUR_NIL

    */

#define CC_USER_SENDING_COMPLETE        0x0002  /* bit #1 */
#define CC_SEND_CONN_CO_ON_PROGRESS     0x0004  /* bit #2 */
#define CC_SEND_DIGIT_CO_ON_PROGRESS    0x0008  /* bit #3 */
#define CC_USE_MU_LAW                   0x0010  /* bit #4 */
#define CC_USE_A_LAW                    0x0020  /* bit #5 */


/* ------------------------------------------------------------------------- */
/* -------------------------- Network Signaling Parms ---------------------- */
/* ------------------------------------------------------------------------- */

/*****************************************************************************

         NS behaviour : this configuration field is a bit field :

            - NS_NO_STATUS_ON_UNKNOWN_IE bit:
                no sending of STATUS message upon receipt of an unknown IE :
                if this bit is set, then the stack does not generate a STATUS message after
                having received a message containing 1 or more unknown/unrecognized IE(s).
                This bit applies only for network variants for which the sending of STATUS
                in this case is optional (where recommendation says "a STATUS MAY be returned").

            - NS_NO_STATUS_ON_INV_OP_IE bit:
                no sending of STATUS message upon receipt of an optional IE with invalid content :
                if this bit is set, then the stack does not generate a STATUS message after
                having received a message containing 1 or more optional IE(s) with invalid content.
                This bit applies only for network variants for which the sending of STATUS
                in this case is optional (where recommendation says "a STATUS MAY be returned").

            - NS_ACCEPT_UNKNOWN_FAC_IE bit:
                unknown/unrecognized Facility IE accepted : if this bit is set, then the stack
                does not reject a received message containing a Facility IE that it does
                not recognize and acts as if the FIE was correct.

            - NS_IE_RELAY_BEHAVIOUR bit:
                the stack behaves as a relay regarding the Information Elements (the Layer 3
                procedures are still in use) : user may send IEs transparently to the
                line, possibly including unknown or unexpected IEs.

            - NS_SEND_USER_CONNECT_ACK bit :
                only applicable when configuration is ETS, EUROPE, TE-side,outgoing call.
                If this bit is set, then NS will send a CONNECT_ACK message only if NS
                receive a CONNECT message.

            - NS_EXPLICIT_INTERFACE_ID :
                If this bit is set, outbound messages (SETUP, PROCEEDING, RESTART, SERVICE etc.)
                will have explicitely coded interface id value (in the channel ID IE).
                This bit could be used for NFAS configured american variants only.

            - NS_PRESERVE_EXT_BIT_IN_CHAN_ID :
                only applicable when configuration is DMS, USA, incoming call.
                If this bit is set, channel id's octets 3.3 's extension bit inside
                the PROCEEDING or ALERT messages as an answer to a SETUP message
                is set to the value that was sent in a SETUP message.

            - NS_DISABLE_RESTART bit:
                if this bit is set the stack will disable the RESTART procedure. In particular
                a RESTART message will not be sent as a result of an isdnStopProtocol() call

            - NS_BEHAVIOUR_NIL : if this bit is set, then NS acts as if none of the previous
                bits where set.

            The default value if this field is set to 0 (=OFF) is :
            NS_IE_RELAY_BEHAVIOUR
        
        */

#define NS_NO_STATUS_ON_UNKNOWN_IE          0x0001
#define NS_NO_STATUS_ON_INV_OP_IE           0x0002
#define NS_ACCEPT_UNKNOWN_FAC_IE            0x0004
#define NS_IE_RELAY_BEHAVIOUR               0x0010
#define NS_SEND_USER_CONNECT_ACK            0x0100
#define NS_EXPLICIT_INTERFACE_ID            0x0200
#define NS_PRESERVE_EXT_BIT_IN_CHAN_ID      0x0400
#define NS_DISABLE_RESTART                  0x1000

#define NS_BEHAVIOUR_NIL                    0x0080


/* ------------------------------------------------------------------------- */
/* -------------------------- Automatic Call Unit Parms -------------------- */
/* ------------------------------------------------------------------------- */

/*****************************************************************************

        ACU behaviour : this configuration field is a bit field :

            - ACU_SEND_Q931_BUFFER bit:
                if this bit is set the stack will send up to the application
                the whole Q.931 message along with the ACU primitive

            - ACU_SEND_D_CHANNEL_STATUS_CHANGE bit:
                if this bit is set the stack will send up to the application
                an ACU_D_CHANNEL_STATUS_IN whenever the status of the D channel
                changes from ON to OFF and vice versa

            - ACU_SEND_UNKNOWN_FACILITY bit:
                if this bit is set the stack will send up to the application
                an ACU_FACILITY_IN message containing the whole Q.931 buffer
                with the unknown Facility IE. Setting this flag automaticly
                enables the NS_ACCEPT_UNKNOWN_FAC_IE behaviour bit.

            - ACU_BEHAVIOUR_NIL : this is the default value corresponding to
                the former behaviour of ACU entity when this field was not in
                configuration.
        */

#define ACU_SEND_Q931_BUFFER                0x01
#define ACU_SEND_D_CHANNEL_STATUS_CHANGE    0x02
#define ACU_SEND_UNKNOWN_FACILITY           0x04

#define ACU_BEHAVIOUR_NIL                   0x00


typedef struct ISDN_PROTOCOL_PARMS_Q931CC
{
    DWORD size;                /* Size of the structure */
    /*
    ** Nai when interfacing the physical layer
    ** should be the same as the 'nai'
    */

    WORD rate;                 /* Data rate */
    WORD t309;              /* T309 in use flag */

    union                   /* Timer values, use 0 for defaults */
    {
    timer_val_t at5[AT5_T_LAST];
    timer_val_t at9[AT9_T_LAST];
    timer_val_t dms[DMS_T_LAST];
    timer_val_t ni1[NI1_T_LAST];
    timer_val_t ni2[NI2_T_LAST];
    timer_val_t au1[AU1_T_LAST];
    timer_val_t hkt[HKT_T_LAST];
    timer_val_t ntt[NTT_T_LAST];
    timer_val_t bt2[BT2_T_LAST];
    timer_val_t bv1[BV1_T_LAST];
    timer_val_t ets[ETS_T_LAST];
    timer_val_t qsi[QSI_T_LAST];
    timer_val_t swd[SWD_T_LAST];
    timer_val_t tr6[TR6_T_LAST];
    timer_val_t vn2[VN2_T_LAST];
    timer_val_t vn3[VN3_T_LAST];
    timer_val_t vn6[VN6_T_LAST];
    timer_val_t foo[24]; /* 24 is more then the rest, will align the union on an 8 byte boundary. */
    } timers;


    /*
    ** Available services
    */
    BYTE services_list[CC_MX_SERVICES+1];
    BYTE bpad[2];       /* padding for 8 bytes alignement */            

    timer_val_t  t101;
    timer_val_t  t102;
    timer_val_t  t198;         /* Observation period for Frame error count  */

    WORD max_FEC_errors;       /* Maximum number of FEC during t198 */

    /*
    ** When to assign/remove a TEI
    */
    WORD tei_time_assignment;     /* TEI time assignment at : CONFIGURATION,
                                     NA ACTIVATION or USAGE time (isdndl.h) */
    WORD tei_time_removal;        /* TEI time removal at    : NA DEACTIVATION,
                                         POWER DOWN (isdndl.h) */
    WORD wpad[3];                 /* padding for 8 bytes alignement */          

    BYTE tei[3];                  /* tei values:
                                     0     :      broadcast
                                     1-63  :      Non automatic TEI assignment
                                     127   :      Automatic TEI assignment */
    BYTE digitstoroute;              /* Number of digits needed to route when
                                            using overlap receiving */

    BYTE bpad1[4];                  /* padding for 8 bytes alignement */            
    /*
    ** Call control behaviour
    */
    WORD in_calls_behaviour;         /* Incoming calls behaviour */
    WORD out_calls_behaviour;        /* Outgoing calls behaviour */
    /*
    ** network signaling behaviour
    */
    WORD ns_behaviour;              
    /*
    ** automatic call unit behaviour
    */
    WORD acu_behaviour;             
    BYTE           qsig_source_party_nb_type;  /* Used for network node addressing in SS */
    BYTE           qsig_source_type_of_nb;     /* Used for network node addressing in SS */
    BYTE           qsig_source_addr[CC_QSIG_MX_ADDR_SIZE+1];

    BYTE            aoc_s_presubscribed; /*On/Off, ON inidates na presubscribes to service */
    BYTE            aoc_d_presubscribed; /*On/Off, ON inidates na presubscribes to service */
    BYTE            aoc_e_presubscribed; /*On/Off, ON inidates na presubscribes to service */

    BYTE bpad2[1];      /* padding for 8 bytes alignement */
    WORD nfas_group;    /* NFAS group number if duplicate NAI values */

    BYTE bpad3[2];      /* padding for 8 bytes alignement */            

    WORD rfu1;          /* reserved for future use  MUST BE 0*/
    WORD rfu2;          /* reserved for future use  MUST BE 0*/
    WORD w2pad[2];      /* padding for 8 bytes alignement */            

} ISDN_PROTOCOL_PARMS_Q931CC;


/*-------------------------------------------------------------------------*/
/*------------------------- Channelized Parms -----------------------------*/
/*-------------------------------------------------------------------------*/
typedef ISDN_PROTOCOL_PARMS_Q931CC  ISDN_PROTOCOL_PARMS_CHANNELIZED;


#ifdef __cplusplus
}
#endif

#endif

