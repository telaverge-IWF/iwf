/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: GSMSMS.h,v 9.1 2005/03/23 12:51:24 cvsadmin Exp $
 *
 * LOG: $Log: GSMSMS.h,v $
 * LOG: Revision 9.1  2005/03/23 12:51:24  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:24  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:45  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:17  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:02  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:56:35  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/04/03 21:23:02  mmiers
 * LOG:
 * LOG:
 * LOG: Finish the prototypes.
 * LOG:
 * LOG: Revision 2.1  2000/03/27 15:25:06  mmiers
 * LOG:
 * LOG:
 * LOG: Add the SMS stuff.
 * LOG:
 *
 ****************************************************************************/

#if !defined(GSMSMS_H)
#define GSMSMS_H

#if !defined(TANDEM)

#include <its.h>

#else /* TANDEM */

#include <itsh>

#endif /* TANDEM */

/*
 * 3.38 definitions and functions
 */

/************************************************************
 * SMS data coding scheme.  The upper four bits represent the
 * coding type.
 */
#define GSM_SMS_CODING_MASK                     0xF0U

#define GSM_SMS_GEN_CODING                      0x00U
/* meaning of bits 4 and 5 */
# define GSM_SMS_GC_COMPRESSED                  0x20U
# define GSM_SMS_GC_HAS_CLASS                   0x10U

/* meaning of bits 2 and 3, if bit 4 is set */
# define GSM_SMS_GC_CLASS_0                     0x00U
# define GSM_SMS_GC_CLASS_1                     0x01U
# define GSM_SMS_GC_CLASS_2                     0x02U
# define GSM_SMS_GC_CLASS_3                     0x03U

/* meaning of bits 0 and 1 */
# define GSM_SMS_GC_ALPHABET_DEF                0x00U
# define GSM_SMS_GC_ALPHABET_8BIT               0x04U
# define GSM_SMS_GC_ALPHABET_UCS2               0x08U
# define GSM_SMS_GC_ALPHABET_RSRVD              0x0CU

/* message waiting coding types */
#define GSM_SMS_MWIG_DISCARD_CODING             0xC0U
#define GSM_SMS_MWIG_STORE_CODING_ALPHABET_DEF  0xD0U
#define GSM_SMS_MWIG_STORE_CODING_ALPHABET_UCS2 0xE0U
/* this next bit cleared means SET_IND_INACTIVE */
# define GSM_SMS_MWIG_SET_IND_ACTIVE            0x08U
# define GSM_SMS_MWIG_VM_WAITING                0x00U
# define GSM_SMS_MWIG_FAX_WAITING               0x01U
# define GSM_SMS_MWIG_EMAIL_WAITING             0x02U
# define GSM_SMS_MWIG_OTHER_WAITING             0x03U

/* data coding type */
#define GSM_SMS_DATA_CODING                     0xF0U
/* meaning of bit 2.  Clear implies default alphabet */
# define GSM_SMS_DC_ALPHABET_8BIT               0x04U

/* meaning of bits 0 and 1 */
#define GSM_SMS_DC_CLASS_0                      0x00U
#define GSM_SMS_DC_CLASS_1                      0x01U
#define GSM_SMS_DC_CLASS_2                      0x02U
#define GSM_SMS_DC_CLASS_3                      0x03U

/***********************************************************
 * Cell broadcast data coding scheme.
 */
#define GSM_CB_CODING_MASK                      0xF0U

/* default alphabet */
#define GSM_CB_CODING_ALPHABET_DEFAULT          0x00U
# define GSM_CB_ADEF_GERMAN                     0x00U
# define GSM_CB_ADEF_ENGLISH                    0x01U
# define GSM_CB_ADEF_ITALIAN                    0x02U
# define GSM_CB_ADEF_FRENCH                     0x03U
# define GSM_CB_ADEF_SPANISH                    0x04U
# define GSM_CB_ADEF_DUTCH                      0x05U
# define GSM_CB_ADEF_SWEDISH                    0x06U
# define GSM_CB_ADEF_DANISH                     0x07U
# define GSM_CB_ADEF_PORTUGUESE                 0x08U
# define GSM_CB_ADEF_FINNISH                    0x09U
# define GSM_CB_ADEF_NORWEGIAN                  0x0AU
# define GSM_CB_ADEF_GREEK                      0x0BU
# define GSM_CB_ADEF_TURKISH                    0x0CU
# define GSM_CB_ADEF_HUNGARIAN                  0x0DU
# define GSM_CB_ADEF_POLISH                     0x0EU
# define GSM_CB_ADEF_UNSPECIFIED                0x0FU

/* message start is alphabet */
#define GSM_CB_CODING_ALPHABET_IN_MSG           0x10U
# define GSM_CB_AIM_ALPHABET_DEFAULT            0x00U
# define GSM_CB_AIM_ALPHABET_UCS2               0x01U

/* Czech */
#define GSM_CB_CODING_ALPHABET_DEFAULT_2        0x20U
# define GSM_CB_ADEF2_CZECH                     0x00U

/* General Data Coding */
#define GSM_CB_CODING_GENERAL                   0xC0U

/* Meaning of bits 4 and 5 */
# define GSM_CB_GC_COMPRESSED                   0x20U
# define GSM_CB_GC_HAS_CLASS                    0x10U

/* meaning of bits 0 and 1, if bit 4 is set */
# define GSM_CB_GC_CLASS_0                      0x00U
# define GSM_CB_GC_CLASS_1                      0x01U
# define GSM_CB_GC_CLASS_2                      0x02U
# define GSM_CB_GC_CLASS_3                      0x03U

/* meaning of bits 0 and 1 */
# define GSM_CB_GC_ALPHABET_DEF                 0x00U
# define GSM_CB_GC_ALPHABET_8BIT                0x04U
# define GSM_CB_GC_ALPHABET_UCS2                0x08U
# define GSM_CB_GC_ALPHABET_RSRVD               0x0CU

/* data coding type */
#define GSM_CB_DATA_CODING                      0xF0U
/* meaning of bit 2.  Clear implies default alphabet */
# define GSM_CB_DC_ALPHABET_8BIT                0x04U

/* meaning of bits 0 and 1 */
#define GSM_CB_DC_CLASS_0                       0x00U
#define GSM_CB_DC_CLASS_1                       0x01U
#define GSM_CB_DC_CLASS_2                       0x02U
#define GSM_CB_DC_CLASS_3                       0x03U

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * nastiness needed for 7 bit packing.  No bit goes unused.
 * The array should be memset to zero before being used.
 */
void GSM_SMSCB_7BitSet(ITS_OCTET *array, ITS_USHORT offset,
                       ITS_OCTET value);

ITS_OCTET GSM_SMSCB_7BitGet(ITS_OCTET *array, ITS_USHORT offset);

#if defined(__cplusplus)
}
#endif

/*
 * 3.40 definitions and API.
 */

/***************************************************************
 * Relay Layer primitives
 */
#define GSM_SMRL_RP_MO_DATA         1
#define GSM_SMRL_RP_MT_DATA         2
#define GSM_SMRL_RP_ACK             3
#define GSM_SMRL_RP_ERROR           4
#define GSM_SMRL_RP_ALERT_SC        5
#define GSM_SMRL_RP_SM_MEM_AVAIL    6

#define GSM_SMRL_RP_TO_MS           0
#define GSM_SMRL_RP_TO_SC           1

/***************************************************************
 * First octet
 */

/*
 * Bits 0 and 1 of all PDUs.
 */
#define GSM_SMS_TP_MTI_MASK                     0x03U
# define GSM_SMS_TP_MTI_DELIVER_TO_MS           0x00U
# define GSM_SMS_TP_MTI_DELIVER_REPORT_TO_SC    0x00U
# define GSM_SMS_TP_MTI_STATUS_REPORT_TO_MS     0x02U
# define GSM_SMS_TP_MTI_COMMAND_TO_SC           0x02U
# define GSM_SMS_TP_MTI_SUBMIT_TO_SC            0x01U
# define GSM_SMS_TP_MTI_SUBMIT_REPORT_TO_MS     0x01U

/*
 * bit 2 of SMS-DELIVER and SMS-STATUS-REPORT
 */
#define GSM_SMS_TP_MMS_MASK                     0x04U
# define GSM_SMS_TP_MMS_NO_MORE_MESSAGES        0x04U

/*
 * bits 3 and 4 of SMS-SUBMIT
 */
#define GSM_SMS_TP_VPF_MASK                     0x18U
# define GSM_SMS_TP_VPF_NOT_PRESENT             0x00U
# define GSM_SMS_TP_VPF_RELATIVE                0x10U
# define GSM_SMS_TP_VPF_ENHANCED                0x08U
# define GSM_SMS_TP_VPF_ABSOLUTE                0x18U

/*
 * bit 5 of SMS-DELIVER
 */
#define GSM_SMS_TP_SRI_MASK                     0x20U
# define GSM_SMS_TP_SRI_RETURN_REPORT           0x20U

/*
 * bit 5 of SMS-SUBMIT
 */
#define GSM_SMS_TP_SRR_MASK                     0x20U
# define GSM_SMS_TP_SRR_REQUEST_REPORT          0x20U

/*
 * bit 6 of SMS-SUBMIT, SMS-SUBMIT-REPORT, SMS-DELIVER,
 * SMS-DELIVER-REPORT, SMS-STATUS-REPORT, and SMS-COMMAND.
 */
#define GSM_SMS_TP_UDHI_MASK                    0x40U
# define GSM_SMS_TP_UDHI_HEADER_INCLUDED        0x40U

/*
 * bit 7 of SMS-DELIVER and SMS-SUBMIT
 */
#define GSM_SMS_TP_RP_MASK                      0x80U
# define GSM_SMS_TP_RP_REPLY_PATH_SET           0x80U

/**********************************************************
 * Other fields
 */
typedef struct
{
    ITS_OCTET    addr_len;
    ITS_OCTET    type_plan;
    ITS_OCTET    address[12];
}
GSM_ADDRESS;

/*
 * Time stamp
 */
typedef struct
{
    ITS_OCTET    year;
    ITS_OCTET    month;
    ITS_OCTET    day;
    ITS_OCTET    hour;
    ITS_OCTET    minute;
    ITS_OCTET    second;
    ITS_OCTET    timeZone;
}
GSM_TIME_STAMP;

/*
 * OR one the following TYPE and PLAN defines together to make a
 * type_plan.
 */
#define GSM_NUMBER_TYPE_UNKNOWN                 0x80U
#define GSM_NUMBER_TYPE_INTERNATIONAL           0x90U
#define GSM_NUMBER_TYPE_NATIONAL                0xA0U
#define GSM_NUMBER_TYPE_NETWORK_SPECIFIC        0xB0U
#define GSM_NUMBER_TYPE_SUBSCRIBER_NUMBER       0xC0U
#define GSM_NUMBER_TYPE_ALPHANUMERIC            0xD0U
#define GSM_NUMBER_TYPE_ABBREVIATED             0xE0U
#define GSM_NUMBER_TYPE_RESERVED                0xF0U

#define GSM_NUMBER_PLAN_UNKNOWN                 0x00U
#define GSM_NUMBER_PLAN_ISDN                    0x01U
#define GSM_NUMBER_PLAN_DATA                    0x03U
#define GSM_NUMBER_PLAN_TELEX                   0x04U
#define GSM_NUMBER_PLAN_NATIONAL                0x08U
#define GSM_NUMBER_PLAN_PRIVATE                 0x09U
#define GSM_NUMBER_PLAN_ERMES                   0x0AU
#define GSM_NUMBER_PLAN_RESERVED                0x0FU

/*
 * TP-PID
 */
#define GSM_SMS_TP_PID_PAYLOAD_MASK             0xC0U
# define GSM_SMS_TP_PID_PAYLOAD_SET_1           0x00U
# define GSM_SMS_TP_PID_PAYLOAD_SET_2           0x40U
# define GSM_SMS_TP_PID_RESERVED                0x80U
# define GSM_SPS_TP_PID_SC_SPECIFIC             0xC0U

#define GSM_SMS_TP_PID_TELEMATIC_INTERWORKING   0x20U

#define GSM_SMS_TP_PID_PAYLOAD_SET_1_MASK       0x1FU

# define GSM_SMS_TP_PID_PS1_IMPLICIT            0x00U
# define GSM_SMS_TP_PID_PS1_TELEX               0x01U
# define GSM_SMS_TP_PID_PS1_GROUP3_FAX          0x02U
# define GSM_SMS_TP_PID_PS1_GROUP4_FAX          0x03U
# define GSM_SMS_TP_PID_PS1_VOICE               0x04U
# define GSM_SMS_TP_PID_PS1_ERMES               0x05U
# define GSM_SMS_TP_PID_PS1_PAGING              0x06U
# define GSM_SMS_TP_PID_PS1_VIDEOTEX            0x07U
# define GSM_SMS_TP_PID_PS1_TELETEX_ANON        0x08U
# define GSM_SMS_TP_PID_PS1_TELETEX_PSPDN       0x09U
# define GSM_SMS_TP_PID_PS1_TELETEX_CSPDN       0x0AU
# define GSM_SMS_TP_PID_PS1_TELETEX_PSTN        0x0BU
# define GSM_SMS_TP_PID_PS1_TELETEX_ISDN        0x0CU
# define GSM_SMS_TP_PID_PS1_UCI                 0x0DU
# define GSM_SMS_TP_PID_PS1_RESERVE_1           0x0EU
# define GSM_SMS_TP_PID_PS1_RESERVE_2           0x0FU
# define GSM_SMS_TP_PID_PS1_MSG_HANDLER         0x10U
# define GSM_SMS_TP_PID_PS1_X400                0x11U
# define GSM_SMS_TP_PID_PS1_EMAIL               0x12U
# define GSM_SMS_TP_PID_PS1_RESERVE_3           0x13U
# define GSM_SMS_TP_PID_PS1_RESERVE_4           0x14U
# define GSM_SMS_TP_PID_PS1_RESERVE_5           0x15U
# define GSM_SMS_TP_PID_PS1_RESERVE_6           0x16U
# define GSM_SMS_TP_PID_PS1_RESERVE_7           0x17U
# define GSM_SMS_TP_PID_PS1_SC_PRIVATE_1        0x18U
# define GSM_SMS_TP_PID_PS1_SC_PRIVATE_2        0x19U
# define GSM_SMS_TP_PID_PS1_SC_PRIVATE_3        0x1AU
# define GSM_SMS_TP_PID_PS1_SC_PRIVATE_4        0x1BU
# define GSM_SMS_TP_PID_PS1_SC_PRIVATE_5        0x1CU
# define GSM_SMS_TP_PID_PS1_SC_PRIVATE_6        0x1DU
# define GSM_SMS_TP_PID_PS1_SC_PRIVATE_7        0x1EU
# define GSM_SMS_TP_PID_PS1_MS                  0x1FU

#define GSM_SMS_TP_PID_PAYLOAD_SET_2_MASK       0x3FU

# define GSM_SMS_TP_PID_PS2_SHORT_MSG_TYPE_0    0x00U
# define GSM_SMS_TP_PID_PS2_SHORT_MSG_TYPE_1    0x01U
# define GSM_SMS_TP_PID_PS2_SHORT_MSG_TYPE_2    0x02U
# define GSM_SMS_TP_PID_PS2_SHORT_MSG_TYPE_3    0x03U
# define GSM_SMS_TP_PID_PS2_SHORT_MSG_TYPE_4    0x04U
# define GSM_SMS_TP_PID_PS2_SHORT_MSG_TYPE_5    0x05U
# define GSM_SMS_TP_PID_PS2_SHORT_MSG_TYPE_6    0x06U
# define GSM_SMS_TP_PID_PS2_SHORT_MSG_TYPE_7    0x07U
# define GSM_SMS_TP_PID_PS2_RETURN_CALL         0x1FU
# define GSM_SMS_TP_PID_PS2_ME_DATA_DOWNLOAD    0x3DU
# define GSM_SMS_TP_PID_PS2_ME_DEPERSON         0x3EU
# define GSM_SMS_TP_PID_PS2_SIM_DATA_DOWNLOAD   0x3FU

/*
 * Validity period values
 */
#define GSM_SMS_TP_VP_EXT_BIT                   0x80U
#define GSM_SMS_TP_VP_SINGLE_SHOT               0x40U
#define GSM_SMS_TP_VP_NONE                      0x00U
#define GSM_SPS_TP_VP_RELATIVE                  0x01U
#define GSM_SMS_TP_VP_RELATIVE_INT              0x02U
#define GSM_SMS_TP_VP_RELATIVE_SEMI             0x03U

/*
 * Status values
 */
#define GSM_SMS_TP_ST_MASK                      0x7FU
/* message transaction completed */
# define GSM_SMS_TP_ST_RCV_BY_SME               0x00U
# define GSM_SMS_TP_ST_FWD_BY_SC_UNCONFIRMED    0x01U
# define GSM_SMS_TP_ST_REPLACED                 0x02U
/* temp error, SC still trying to transfer */
# define GSM_SMS_TP_ST_TER_CONGESTION           0x20U
# define GSM_SMS_TP_ST_TER_SME_BUSY             0x21U
# define GSM_SMS_TP_ST_TER_SME_NO_REPONSE       0x22U
# define GSM_SMS_TP_ST_TER_SERVICE_REJECTED     0x23U
# define GSM_SMS_TP_ST_TER_QOS_UNAVAILABLE      0x24U
# define GSM_SMS_TP_ST_TER_ERROR_IN_SME         0x25U
/* perm error, SC not making transfer attempts */
# define GSM_SMS_TP_ST_PENR_RPC_ERROR           0x40U
# define GSM_SMS_TP_ST_PENR_INCOMPAT_DEST       0x41U
# define GSM_SMS_TP_ST_PENR_CONN_REJ_BY_SME     0x42U
# define GSM_SMS_TP_ST_PENR_NOT_OBTAINABLE      0x43U
# define GSM_SMS_TP_ST_PENR_QOS_UNAVAILABLE     0x44U
# define GSM_SMS_TP_ST_PENR_NO_INTERWORKING     0x45U
# define GSM_SMS_TP_ST_PENR_SM_VALIDITY_EXPIRED 0x46U
# define GSM_SMS_TP_ST_PENR_SM_DEL_BY_ORIG_SME  0x47U
# define GSM_SMS_TP_ST_PENR_SM_DEL_BY_SME_ADMIN 0x48U
# define GSM_SMS_TP_ST_PENR_SM_DOES_NOT_EXIST   0x49U
/* temp error, SC not making transfer attempts */
# define GSM_SMS_TP_ST_TENR_CONGESTION          0x60U
# define GSM_SMS_TP_ST_TENR_SME_BUSY            0x61U
# define GSM_SMS_TP_ST_TENR_SME_NO_RESPONSE     0x62U
# define GSM_SMS_TP_ST_TENR_SERVICE_REJECTED    0x63U
# define GSM_SMS_TP_ST_TENR_QOS_UNAVAILABLE     0x64U
# define GSM_SMS_TP_ST_TENR_ERROR_IN_SME        0x65U

/*
 * Command type
 */
#define GSM_SMS_TP_CT_ENQUIRE_PREVIOUS_MSG      0x00U
#define GSM_SMS_TP_CT_CANCEL_STATUS_REPORT_PREV 0x01U
#define GSM_SMS_TP_CT_DELETE_PREVIOUS_MSG       0x02U
#define GSM_SMS_TP_CT_ENABLE_STATUS_REPORT_PREV 0x03U

/*
 * Failure causes
 */
/* PID errors */
#define GSM_SMS_TP_FCS_PID_TELEMATIC_UNSUPP     0x80U
#define GSM_SMS_TP_FCS_PID_SM_TYPE_0_UNSUPP     0x81U
#define GSM_SMS_TP_FCS_PID_CANT_REPLACE_SM      0x82U
#define GSM_SMS_TP_FCS_PID_UNSPECIFIED          0x8FU
/* DCS errors */
#define GSM_SMS_TP_FCS_DCS_UNSUPPORTED          0x90U
#define GSM_SMS_TP_FCS_DCS_MSG_CLASS_UNSUPP     0x91U
#define GSM_SMS_TP_FCS_DCS_UNSPECIFIED          0x9FU
/* CT errors */
#define GSM_SMS_TP_FCS_CT_CANNOT_ACTION         0xA0U
#define GSM_SMS_TP_FCS_CT_UNSUPPORTED           0xA1U
#define GSM_SMS_TP_FCS_CT_UNSPECIFIED           0xAFU
/* TPDU errors */
#define GSM_SMS_TP_FCS_TPDU_UNSUPPORTED         0x80U
/* General */
#define GSM_SMS_TP_FCS_GEN_SC_BUSY              0xC0U
#define GSM_SMS_TP_FCS_GEN_NO_SC_SUBSCRIPTION   0xC1U
#define GSM_SMS_TP_FCS_GEN_SC_SYSTEM_FAILED     0xC2U
#define GSM_SMS_TP_FCS_GEN_INVALID_SME_ADDR     0xC3U
#define GSM_SMS_TP_FCS_GEN_DEST_SME_BARRED      0xC4U
#define GSM_SMS_TP_FCS_GEN_DUPLICATE_SM         0xC5U
#define GSM_SMS_TP_FCS_GEN_VPF_UNSUPP           0xC6U
#define GSM_SMS_TP_FCS_GEN_VP_UNSUPP            0xC7U
#define GSM_SMS_TP_FCS_GEN_SIM_STORE_FULL       0xD0U
#define GSM_SMS_TP_FCS_GEN_SIM_CANT_STORE       0xD1U
#define GSM_SMS_TP_FCS_GEN_MS_ERROR             0xD2U
#define GSM_SMS_TP_FCS_GEN_MEMORY_EXHAUSTED     0xD3U
#define GSM_SMS_TP_FCS_GEN_SIM_TOOLKIT_BUSY     0xD4U
#define GSM_SMS_TP_FCS_GEN_SIM_DOWNLOAD_ERROR   0xD5U
#define GSM_SMS_TP_FCS_GEN_UNSPECIFIED          0xFFU

/*
 * User data IEIs
 */
#define GSM_SMS_TP_UD_IEI_CONCAT_SMS            0x00U
#define GSM_SMS_TP_UD_IEI_SPECIAL_SMS_MI        0x01U
#define GSM_SMS_TP_UD_IEI_RESERVE_1             0x02U
#define GSM_SMS_TP_UD_IEI_VALUE_UNUSED          0x03U
#define GSM_SMS_TP_UD_IEI_8BIT_ADDR             0x04U
#define GSM_SMS_TP_UD_IEI_16BIT_ADDR            0x05U
#define GSM_SMS_TP_UD_IEI_SMSC_CTRL_PARAMS      0x06U
#define GSM_SMS_TP_UD_IEI_UDH_SRC_INDICATOR     0x07U

/*
 * Parameter indicator
 */
#define GSM_SMS_TP_PI_TP_PID_BIT                0x01U
#define GSM_SMS_TP_PI_TP_DCS_BIT                0x02U
#define GSM_SMS_TP_PI_TP_UDL_BIT                0x03U

/*
 * Max size of user data
 */
#define GSM_SMS_MAX_DATA            160

/*
 * the overall structure
 */
typedef struct
{
    ITS_OCTET    firstOctet;
    union
    {
        struct
        {
            GSM_ADDRESS       origAddr;                /* TP-OA */
            ITS_OCTET         protIdent;               /* TP-PID */
            ITS_OCTET         dataCodeScheme;          /* TP-DCS */
            GSM_TIME_STAMP    scTimestamp;             /* TP-SCTS */
            ITS_OCTET         userDataLen;             /* TP-UDL */
            ITS_OCTET         userData[GSM_SMS_MAX_DATA];
        }
        deliver;
        struct
        {
            ITS_OCTET         failCause;               /* TP-FCS.  Not included in RP-ACK */
            ITS_OCTET         paramInd;                /* TP-PI */
            ITS_OCTET         protIdent;               /* TP-PID */
            ITS_OCTET         dataCodeScheme;          /* TP-DCS */
            ITS_OCTET         userDataLen;             /* TP-UDL */
            ITS_OCTET         userData[GSM_SMS_MAX_DATA];
        }
        deliver_report;
        struct
        {
            ITS_OCTET         msgRef;                  /* TP-MR */
            GSM_ADDRESS       destAddr;                /* TP-DA */
            ITS_OCTET         protIdent;               /* TP-PID */
            ITS_OCTET         dataCodeScheme;          /* TP-DCS */
            GSM_TIME_STAMP    validPeriod;             /* TP-VP */
            ITS_OCTET         userDataLen;             /* TP-UDL */
            ITS_OCTET         userData[GSM_SMS_MAX_DATA];
        }
        submit;
        struct
        {
            ITS_OCTET         failCause;               /* TP-FCS.  Not included in RP-ACK */
            ITS_OCTET         paramInd;                /* TP-PI */
            GSM_TIME_STAMP    scTimestamp;             /* TP-SCTS */
            ITS_OCTET         protIdent;               /* TP-PID */
            ITS_OCTET         dataCodeScheme;          /* TP-DCS */
            ITS_OCTET         userDataLen;             /* TP-UDL */
            ITS_OCTET         userData[GSM_SMS_MAX_DATA];
        }
        submit_report;
        struct
        {
            ITS_OCTET         msgRef;                  /* TP-MR */
            GSM_ADDRESS       recipAddr;               /* TP-RA */
            GSM_TIME_STAMP    scTimestamp;             /* TP-SCTS */
            GSM_TIME_STAMP    dischargeTime;           /* TP-DT */
            ITS_OCTET         status;                  /* TP-ST */
            ITS_OCTET         paramInd;                /* TP-PI */
            ITS_OCTET         protIdent;               /* TP-PID */
            ITS_OCTET         dataCodeScheme;          /* TP-DCS */
            ITS_OCTET         userDataLen;             /* TP-UDL */
            ITS_OCTET         userData[GSM_SMS_MAX_DATA];
        }
        status_report;
        struct
        {
            ITS_OCTET         msgRef;                  /* TP-MR */
            ITS_OCTET         protIdent;               /* TP-PID */
            ITS_OCTET         cmdType;                 /* TP-CT */
            ITS_OCTET         msgNumber;               /* TP-MN */
            GSM_ADDRESS       destAddr;                /* TP-DA */
            ITS_OCTET         cmdDataLen;              /* TP-CDL */
            ITS_OCTET         cmdData[GSM_SMS_MAX_DATA];
        }
        command;
    }
    sms;
}
GSM_SMS_MSG;

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * API
 */
int GSM_SMS_EncodeMsg(int rpType, int dir,
                      GSM_SMS_MSG *msg,
                      char *buf, int *len);
int GSM_SMS_DecodeMsg(int rpType, int dir,
                      GSM_SMS_MSG *msg,
                      char *buf, int len);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* GSMSMS_H */
