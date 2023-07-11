/****************************************************************************
*
* FILE: isdntype.h
*
* DESCRIPTION: Resolves the differences between NMS types and Omnitel
*
*
*  Copyright (c) 1994-97  Natural MicroSystems Corp.  All rights reserved
*
****************************************************************************/

/*[]---------------------------------------------------[]*/
/*|                                                     |*/
/*| OMNITEL-BRICKS -                                    |*/
/*|                                                     |*/
/*|                                                     |*/
/*| Copyright (c) 1992 by OMNITEL SA                    |*/
/*| All Rights Reserved.                                |*/
/*|                                                     |*/
/*[]---------------------------------------------------[]*/



#ifndef ISDNTYPE_H
#define ISDNTYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NMSTYPES_INCLUDED
  #include "nmstypes.h"
#endif


/* ------------------------------------------------------------------------ */
/* -------------------------- Omnitel Native Data Types ------------------- */
/* ------------------------------------------------------------------------ */
typedef BYTE uchar;
typedef BYTE nai_t;
typedef BYTE sapi_t;
typedef BYTE ent_id_t;
typedef BYTE add_t;
typedef BYTE ces_t;
typedef BYTE code_t;
typedef DWORD timer_val_t;
typedef BYTE priority_t;


/* ------------------------------------------------------------------------ */
/* -------------------------- Data Alignment Issues ----------------------- */
/* ------------------------------------------------------------------------ */

#define  ALIGNMENT    8



            /* Round */

#define Round2(val)             ((val) + 1  & ~1)
#define Round4(val)             ((val) + 3  & ~3)
#define Round8(val)             ((val) + 7  & ~7)
#define Round16(val)            ((val) + 15 & ~15)



            /* Rounded 'sizeof' */

#define Rnd_sizeof(type)        (Round (sizeof (type)))

            /* Padding for structure and data alignment */

#if ALIGNMENT == 1
#   define Bound

#else

#   define Bound                unsigned :0;
#endif

#if ALIGNMENT == 1
#   define Round(x)             (x)
#endif

#if ALIGNMENT == 2
#   define Round(x)             Round2 (x)
#endif

#if ALIGNMENT == 4
#   define Round(x)             Round4 (x)
#endif

#if ALIGNMENT == 8
#   define Round(x)             Round8 (x)
#endif

#define Rnd_sizeof(type)        (Round (sizeof (type)))

#define Min(a, b)            ((a) < (b) ? (a) : (b))
#define Max(a, b)            ((a) > (b) ? (a) : (b))

/*--------------------------------------------------------------------------*/
/*--------------------------- CC Defines -----------------------------------*/
/*--------------------------------------------------------------------------*/

#define CC_MX_SERVICES               21     /* maximum number of services */
#define CC_PAR_PCS_USER_INFO        ON
#define CC_SPF_FAC                  ON
#define CC_SUPP_SERVICES            OFF
#define CC_ADDRESS_FILTERING        OFF
#define CC_CALLED_SUB_ADD           ON
#define CC_CALLING_SUB_ADD          ON
#define CC_UUI                      ON
#define CC_OVERLAP_RECEIVING        ON
#define CC_RESTART_PROCEDURE        ON
#define CC_SUSPEND_RESUME           ON
#define CC_V120_CODING              OFF
#define CC_USE_ACU_SET_MODE_RQ_CO   OFF
#define CC_PAR_CHARGING_INFO        ON
#define CC_PAR_DISPLAY_IE           ON
#define CC_PAR_DATE_TIME            ON
#define CC_PAR_PCS_USER_INFO        ON
#define CC_PAR_KEYPAD_IE            ON
#define CC_PAR_MULTIPLE_CALLING_NB  ON
#define CC_PAR_REDIR_NB             ON


/*--------------------------------------------------------------------------*/
/*--------------------------- Buffer Defines -------------------------------*/
/*--------------------------------------------------------------------------*/

#define ISDN_BUFFER_DATA_LGTH        750




/*--------------------------------------------------------------------------*/
/*--------------------------- Generic Return Codes -------------------------*/
/*--------------------------------------------------------------------------*/
#define OFF                                     (0)
#define ON                                      (!OFF)


/* ------------------------------------------------------------------------ */
/* -------------------------- Timer Values -------------------------------- */
/* ------------------------------------------------------------------------ */


#define MILLISECOND         (timer_val_t)1            /* UNIT = Millisecond */
#define SECOND              (1000*MILLISECOND)


/* ------------------------------------------------------------------------ */
/* -------------------------- Confirm Stucture ---------------------------- */
/* ------------------------------------------------------------------------ */
struct confirm {
    uchar   return_code;            /* return code : OK or NOK */
    uchar   cause;                  /* cause Id if NOK */
    uchar   diagnostic;             /* diagnostic if NOK */
	uchar   pad[5];					/* pad for 8 bytes alignement */
};



struct sm_report    {
	ent_id_t        entity_origination; /* entity ID where the report has been detected */
	uchar           report_type;        /* Type of report message */
	uchar   pad[6];					    /* pad for 8 bytes alignement */
};

struct sm_info {
    ent_id_t        entity_origination; /* entity ID where the information has been built */
    uchar           info_type;          /* Type of information confirm message */
	uchar   pad[6];					    /* pad for 8 bytes alignement */
};


/* ------------------------------------------------------------------------ */
/* -------------------------- DL Parameters ------------------------------- */
/* ------------------------------------------------------------------------ */
#define DL_CONFIG_MX_SAP    4
#define DL_CONFIG_MX_NA     2


/* ------------------------------------------------------------------------ */
/* -------------------------- Bit macros -- ------------------------------- */
/* ------------------------------------------------------------------------ */
#define G_1(b1) (uchar)b1

#define G_2(b2,b1) (uchar)((b2<<1)+b1)

#define G_3(b3,b2,b1) (uchar)((((b3<<1)+b2)<<1)+b1)

#define G_4(b4,b3,b2,b1) (uchar)((((((b4<<1)+b3)<<1)+b2)<<1)+b1)

#define G_5(b5,b4,b3,b2,b1) (uchar)((((((((b5<<1)+b4)<<1)+b3)<<1)+b2)<<1)+b1)

#define G_6(b6,b5,b4,b3,b2,b1) (uchar)((((((((((b6<<1)+b5)<<1)+b4)<<1)+b3)<<1)+b2)\
                               <<1)+b1)

#define G_7(b7,b6,b5,b4,b3,b2,b1) (uchar)((((((((((((b7<<1)+b6)<<1)+b5)<<1)+b4)\
                                  <<1)+b3)<<1)+b2)<<1)+b1)

#define G_8(b8,b7,b6,b5,b4,b3,b2,b1) (uchar)((((((((((((((b8<<1)+b7)<<1)+b6)<<1)\
                                     +b5)<<1)+b4)<<1)+b3)<<1)+b2)<<1)+b1)


/*--------------------------------------------------------------------------*/

                /*-=-=-=-=-=-=-=-=-=-=-=-*/
                /*                       */
                /*  ENTITY  IDENTIFIERS  */
                /*                       */
                /*-=-=-=-=-=-=-=-=-=-=-=-*/

#define ENTITY_ID_MIN           '0'             /* min entity ID */
#define ENTITY_ID_MAX           'z'             /* max entity ID */
#define ENT_NIL                 'n'             /* entity NIL */

#define ENT_SM                  'z'             /* System Management */
#define ENT_TI                  'T'             /* TImer process pseudo-entity */

#define ENT_APPLI               'A'             /* application entity */
#define ENT_IMGT                '$'             /* Service Management entity */

#define ENT_FS                  'L'             /* File server entity */
#define ENT_FT                  'N'             /* File transfer */

#define ENT_DTE_INT             'i'             /* DTE interface entity */
#define ENT_DTE_SCC_IT          ENT_PH_IT       /* DTE serial controller interface interrupt */
#define ENT_DTE_INT_IT          ENT_PH_IT

#define ENT_ECL                 ':'             /* Equipment Control Link entity */
#define ENT_MPH_S               ';'             /* Shared Memory Interface driver management entity */
#define ENT_AT_ECL              '_'             /* AT-ECL entity (between DTE-INT and ECL entities) */

#define ENT_ECI                 '`'             /* Eicon Interface entity (OMNABIOS) */

#define ENT_STS                 '0'             /* STS entity id */

#define ENT_DL_R                'g'             /* Data link relay */
#define ENT_MDL                 'm'             /* Data Link layer Management entity */
#define ENT_DL                  'l'             /* Data Link generic entity */
#define ENT_DL_D                'd'             /* " LAPD " Data Link entity */
#define ENT_DL_B                'b'             /* " LAPB " Data Link entity */
#define ENT_DL_F                ']'             /* Data Link LAPF entity */
#define ENT_DL_M                'v'             /* Data Link LAPM entity */
#define ENT_MNP4                '4'             /* MNP 4 processing entity */
#define ENT_V120                '2'             /* V120 LAP entity */
#define ENT_DL_V120             ENT_V120        /* V.120 Data Link entity */
#define ENT_DL_4K               'k'             /* LAP4K Data Link entity */

#define ENT_DC                  'V'             /* Data compression entity */

#define ENT_CC                  'C'             /* Call Control entity */
#define ENT_CCR                 ENT_CC          /* Call Control Relay entity */
#define ENT_CCE                 '['             /* Extended Call Control entity (Nx64K calls) */
#define ENT_CF                  's'             /* Control Functions entity */

#define ENT_MNS                 'M'             /* NS layer Management entity */
#define ENT_NS                  'S'             /* network signalling entity */
#define ENT_L3                  '3'             /* layer 3 generic entity */

#define ENT_FM                  'f'             /* FAXMOD entity */
#define ENT_MFM                 'F'             /* FAXMOD management entity */
#define ENT_T30                 'e'             /* T30 entity */
#define ENT_MT30                'E'             /* T30 management entity */

#define ENT_PH_R                'R'             /* PH relay */
#define ENT_MPH                 'P'             /* physical layer management */
#define ENT_MPH_D               'W'             /* physical layer management D channel */
#define ENT_MPH_B               'Q'             /* physical layer management B channel */
#define ENT_MPH_IT              ENT_PH_IT       /* physical layer management interrupt */
#define ENT_PH                  'p'             /* physical generic entity */
#define ENT_PH_IT               'q'             /* physical IT */

#define ENT_PH_D                'D'             /* physical D channel entity */
#define ENT_PH_D_IT             'r'             /* physical D channel interruption */

#define ENT_PH_B                'c'             /* physical B channel entity */
#define ENT_PH_B_IT             ENT_PH_IT       /* physical B channel interruption */
#define ENT_MPH_B_IT            ENT_PH_IT       /* physical B channel interruption */

#define ENT_PH_GSTN             'G'             /* physical GSTN entity */
#define ENT_PH_GSTN_IT          ENT_PH_IT       /* physical GSTN interruption */

#define ENT_PH_MODEM            'H'             /* physical modem entity */
#define ENT_PH_MODEM_IT         ENT_PH_IT       /* physical modem interruption */

#define ENT_PAD                 'a'             /* packet assembler deassembler */
#define ENT_T                   't'             /* OSI transport entity */
#define ENT_MX25                'X'             /* X25 layer management entity */
#define ENT_X25                 'x'             /* X.25-PLP entity */
#define ENT_X213                'o'             /* X.213 entity */
#define ENT_MX213               'O'             /* X.213 layer management entity */

#define ENT_ACU                 'u'             /* ACU entity */
#define ENT_BL                  'B'             /* Black List entity */

#define ENT_IP                  'I'             /* ISO IP entity */
#define ENT_ES                  'J'             /* ISO ES-IS entity */
#define ENT_IS                  'K'             /* ISO IS-IS entity */
#define ENT_MIP                 'j'             /* ISO CLNP Management entity */

#define ENT_ACC                 '9'             /* ATM Call Control entity */
#define ENT_ANS                 'Y'             /* ATM network signalling entity */
#define ENT_MANS                'w'             /* ATM network signalling Management entity */
#define ENT_AAL                 'y'             /* ATM Adaptation Layer entity */
#define ENT_MAAL                'h'             /* ATM Adaptation Layer Management entity */
#define ENT_AALCP               'U'             /* ATM Adaptation Layer Common Part entity */
#define ENT_AALCP_IT            ENT_PH_IT       /* ATM Adaptation Layer Common Part Interrupt entity */
#define ENT_MAALCP              '5'             /* ATM Adaptation Layer Common Part Management entity */
#define ENT_MAALCP_IT           ENT_PH_IT       /* ATM Adaptation Layer Common Part Management Interrupt entity */

#define ENT_SMI                 '6'             /* Shared Memory Interface entity */
#define ENT_SMI_IT              ENT_PH_IT       /* Shared Memory Interface Interrupt part pseudo-entity */

#define ENT_PH_S                ENT_SMI         /* Shared Memory Interface entity */
#define ENT_PH_S_IT             ENT_SMI_IT      /* Shared Memory Interface Interrupt part pseudo-entity */

#define ENT_API                 '1'             /* API entity */

#define ENT_IB                  '7'             /* ISDN BIOS entity */
#define ENT_IBI                 '8'             /* ISDN BIOS interface entity */

#define ENT_EF                  'Z'             /* ETSI EuroFile service entity */
#define ENT_AT_V25              '@'             /* conversion V25 <--> "AT" */

#define ENT_AG                  '?'             /* AG runtime interface entity (NMS only) */

#ifdef __cplusplus
}
#endif

#endif

