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
 *  ID: $Id: itu-isup_99.c,v 1.3 2008/07/18 05:50:28 ssingh Exp $
 *  
 *  LOG: $Log: itu-isup_99.c,v $
 *  LOG: Revision 1.3  2008/07/18 05:50:28  ssingh
 *  LOG: SDS ID:: ID :: D0240 Warning removal for Solaris Compilation
 *  LOG:
 *  LOG: Revision 1.2  2006/01/09 06:44:52  omayor
 *  LOG: Added support for ITU ISUP 99.(skatta)
 *  LOG:
 *  
 *****************************************************************************/

#include <its.h>

#undef CCITT
#undef ANSI
#define CCITT

#include <itu/isup_99.h>

#include "itu-isup_99_intern.h"


/*
 * Include the 99 message descriptors here 
 */

/*
 * ADDRESS COMPLETE (ACM)
 */
static ITS_OCTET    acmMArgs[] =
{
    ISUP_PRM_BKWD_CALL_INDICATORS
};

static ITS_OCTET    acmOArgs[] =
{
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_CALL_DIVERSION_INFO,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_REDIRECTION_NUM_RESTRICT,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_TX_MEDIUM_USED,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CAUSE_INDICATORS,
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,

    /* ITU97 Specific */
    ISUP_PRM_CONF_TREAT_INDICATORS,
    ISUP_PRM_UID_ACTION_INDICATORS,

    /* ITU99 Specific */
    ISUP_PRM_APPLLICATION_TRANSPORT,
    ISUP_PRM_CCNR_POSSIBLE_IND,
    ISUP_PRM_HTR_INFORMATION,
    ISUP_PRM_PIVOT_ROUTING_BKWD_INFO,
    ISUP_PRM_REDIRECT_STATUS

};

SS7DLLAPI ISUP_MSG_DESC ITU_99_ISUP_ACM_Desc =
{
    ITS_TRUE, /* has EOP */
    acmMArgs, /* Mandatory Fixed */
    sizeof(acmMArgs),
    NULL,     /* Mandatory Variable */
    0,
    acmOArgs, /* Optional */
    sizeof(acmOArgs)
};


/*
 * ANSWER (ANM)
 */
static ITS_OCTET anmOArgs[] =
{
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_CONNECTED_NUM,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_TX_MEDIUM_USED,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_REDIRECTION_NUM_RESTRICT,
    ISUP_PRM_GENERIC_NUM,
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_BKWD_CALL_INDICATORS,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,

    /* ITU97 Specific */
    ISUP_PRM_BACKWARD_GVNS,
    ISUP_PRM_DISPLAY_INFORMATION,

    /* ITU99 Specific */
    ISUP_PRM_CONF_TREAT_INDICATORS,
    ISUP_PRM_APPLLICATION_TRANSPORT,
    ISUP_PRM_PIVOT_ROUTING_BKWD_INFO,
    ISUP_PRM_REDIRECT_STATUS

};

SS7DLLAPI ISUP_MSG_DESC ITU_99_ISUP_ANM_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    anmOArgs, sizeof(anmOArgs)
};


/*
 * CALL PROGRESS (CPG)
 */
static ITS_OCTET cpgMArgs[] =
{
    ISUP_PRM_EVENT_INFO
};

static ITS_OCTET cpgOArgs[] =
{
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_BKWD_CALL_INDICATORS,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CAUSE_INDICATORS,
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_TX_MEDIUM_USED,
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_CALL_DIVERSION_INFO,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_REDIRECTION_NUM_RESTRICT,

    /* ITU97 Specific */
    ISUP_PRM_CALL_TRANSFER_NUMBER,
    ISUP_PRM_CONNECTED_NUM,
    ISUP_PRM_BACKWARD_GVNS,
    ISUP_PRM_GENERIC_NUM,
    ISUP_PRM_CONF_TREAT_INDICATORS,
    ISUP_PRM_UID_ACTION_INDICATORS,

    /* ITU99 Specific */
    ISUP_PRM_APPLLICATION_TRANSPORT,
    ISUP_PRM_CCNR_POSSIBLE_IND,
    ISUP_PRM_PIVOT_ROUTING_BKWD_INFO,
    ISUP_PRM_REDIRECT_STATUS

};

SS7DLLAPI ISUP_MSG_DESC   ITU_99_ISUP_CPG_Desc =
{
    ITS_TRUE,
    cpgMArgs, sizeof(cpgMArgs),
    NULL, 0,
    cpgOArgs, sizeof(cpgOArgs),
};


/*
 * CONNECT (CON)
 */
static ITS_OCTET    conMArgs[] =
{
    ISUP_PRM_BKWD_CALL_INDICATORS
};

static ITS_OCTET    conOArgs[] =
{
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,
    ISUP_PRM_CONNECTED_NUM,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_TX_MEDIUM_USED,
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    /* ISUP_PRM_REDIRECTION_NUM, - only in ITU93 */
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_GENERIC_NUM,
    ISUP_PRM_REDIRECTION_NUM_RESTRICT,

    /* ITU97 Specific */
    ISUP_PRM_BACKWARD_GVNS,
    ISUP_PRM_CONF_TREAT_INDICATORS,

    /* ITU99 Specific */
    ISUP_PRM_APPLLICATION_TRANSPORT,
    ISUP_PRM_HTR_INFORMATION,
    ISUP_PRM_PIVOT_ROUTING_BKWD_INFO,
    ISUP_PRM_REDIRECT_STATUS

};

SS7DLLAPI ISUP_MSG_DESC   ITU_99_ISUP_CON_Desc =
{
    ITS_TRUE,
    conMArgs, sizeof(conMArgs),
    NULL, 0,
    conOArgs, sizeof(conOArgs)
};


/*
 * INITIAL ADDRESS (IAM)
 */
static ITS_OCTET iamMArgs[] =
{
    ISUP_PRM_NATURE_CONN_INDICATORS,
    ISUP_PRM_FWD_CALL_INDICATORS,
    ISUP_PRM_CALLING_PARTY_CATEGORY,
    ISUP_PRM_TX_MEDIUM_REQMNT
};
static ITS_OCTET iamVArgs[] =
{
    ISUP_PRM_CALLED_PARTY_NUM
};
static ITS_OCTET iamOArgs[] =
{
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CALLING_PARTY_NUM,
    ISUP_PRM_CONNECTION_REQ,
    ISUP_PRM_GENERIC_DIGITS,
    ISUP_PRM_REDIRECTING_NUM,
    ISUP_PRM_REDIRECTION_INFO,
    ISUP_PRM_ORIG_CALLED_NUM,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_TRANSIT_NTWK_SELECT,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_SERVICE_INFO,
    ISUP_PRM_OPT_FWD_CALL_INDICATORS,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_CLOSED_USR_GRP_INTRLCK_CODE,
    ISUP_PRM_USER_SERVICE_INFO_PRIME,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_GENERIC_NUM,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_GENERIC_REF,
    ISUP_PRM_MLPP_PRECEDENCE,
    ISUP_PRM_TX_MEDIUM_REQMNT_PRIME,
    ISUP_PRM_LOCATION_NUM,

    /* ITU97 Specific */
    ISUP_PRM_USER_TELESERVICE_INFO,
    ISUP_PRM_FORWARD_GVNS,
    ISUP_PRM_CCSS,
    ISUP_PRM_NETWORK_MANAGEMENT_CONTROLS,
    ISUP_PRM_CIRCUIT_ASSIGNMENT_MAP,
    ISUP_PRM_CORRELATION_ID,
    ISUP_PRM_CALL_DIV_TREAT_INDICATORS,
    ISUP_PRM_CALLED_IN_NUMBER,
    ISUP_PRM_CALL_OFF_TREAT_INDICATORS,
    ISUP_PRM_CONF_TREAT_INDICATORS,
    ISUP_PRM_SCF_ID,
    ISUP_PRM_UID_CAPABILITY_INDICATORS,
    ISUP_PRM_HOP_COUNTER,
    ISUP_PRM_COLLECT_CALL_REQUEST,

    /* ITU99 Specific */
    ISUP_PRM_APPLLICATION_TRANSPORT,
    ISUP_PRM_PIVOT_CAPABILITY,
    ISUP_PRM_CALLED_DIR_NUM,
    ISUP_PRM_ORIGINAL_CALLED_IN_NUM,
    ISUP_PRM_CALLING_GEODETIC_LOCATION,
    ISUP_PRM_NETWORK_ROUTING_NUM,
    ISUP_PRM_QUERY_ON_RELEASE_CAPABILITY,
    ISUP_PRM_PIVOT_COUNTER,
    ISUP_PRM_PIVOT_ROUTING_FRWD_INFO,
    ISUP_PRM_REDIRECT_CAPABILITY,
    ISUP_PRM_REDIRECT_COUNTER,
    ISUP_PRM_REDIRECT_STATUS,
    ISUP_PRM_REDIRECT_FRWD_INFO,
    ISUP_PRM_NUM_PORTABILTY_FRWD_INFO
   
};

SS7DLLAPI ISUP_MSG_DESC   ITU_99_ISUP_IAM_Desc =
{
    ITS_TRUE,
    iamMArgs, sizeof(iamMArgs),
    iamVArgs, sizeof(iamVArgs),
    iamOArgs, sizeof(iamOArgs)
};


/*
 * RELEASE (REL)
 */
static ITS_OCTET relVArgs[] =
{
    ISUP_PRM_CAUSE_INDICATORS
};
static ITS_OCTET relOArgs[] =
{
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_REDIRECTION_INFO,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_SIGNALLING_POINT_CODE,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_AUTO_CONGEST_LEVEL,

    /* ITU97 Specific */
    ISUP_PRM_DISPLAY_INFORMATION,
    ISUP_PRM_REMOTE_OPS,

    /* ITU99 Specific */
    ISUP_PRM_HTR_INFORMATION,
    ISUP_PRM_REDIRECT_COUNTER,
    ISUP_PRM_REDIRECT_BKWD_INFO
};

SS7DLLAPI ISUP_MSG_DESC   ITU_99_ISUP_REL_Desc =
{
    ITS_TRUE,
    NULL, 0,
    relVArgs, sizeof(relVArgs),
    relOArgs, sizeof(relOArgs)
};


/*
 * FACILITY (FAC)
 */
static ITS_OCTET facOArgs[] =
{
    ISUP_PRM_MSG_COMPAT_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_SERVICE_ACTIVATION,

    /* ITU97 Specific */
    ISUP_PRM_CALL_TRANSFER_NUMBER,
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_GENERIC_NOTIFICATION,

    /* ITU99 Specific */
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_PIVOT_ROUTING_IND,
    ISUP_PRM_PIVOT_STATUS,
    ISUP_PRM_PIVOT_COUNTER,
    ISUP_PRM_PIVOT_ROUTING_BKWD_INFO,
    ISUP_PRM_REDIRECT_STATUS
};

SS7DLLAPI ISUP_MSG_DESC   ITU_99_ISUP_FAC_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    facOArgs, sizeof(facOArgs)
};


/*
 * FACILITY ACCEPTED (FAA)
 */
/*
static ITS_OCTET faaMArgs[] =
{
    ISUP_PRM_FACILITY_INDICATOR
};
static ITS_OCTET faaOArgs[] =
{
    ISUP_PRM_CALL_REF,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_USER_TO_USER_INDICATORS,
};
*/
/*
SS7DLLAPI ISUP_MSG_DESC   ITU_UK_ISUP_FAA_Desc =
{
    ITS_TRUE,
    faaMArgs, sizeof(faaMArgs),
    NULL, 0,
    faaOArgs, sizeof(faaOArgs)
};

*/

/*
 * APPLICATION TRANSPORT (APM)
 */
static ITS_OCTET apmOArgs[] =
{
    /* ITU99 Specific */
    ISUP_PRM_MSG_COMPAT_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_APPLLICATION_TRANSPORT
};

SS7DLLAPI ISUP_MSG_DESC   ITU_99_ISUP_APM_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    apmOArgs, sizeof(apmOArgs)
};


/*
 * PRE-RELEASE INFO (PRI)
 */
static ITS_OCTET priOArgs[] =
{
    /* ITU99 Specific */
    ISUP_PRM_MSG_COMPAT_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_OPT_FWD_CALL_INDICATORS,
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,
    ISUP_PRM_APPLLICATION_TRANSPORT
};

SS7DLLAPI ISUP_MSG_DESC   ITU_99_ISUP_PRI_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    priOArgs, sizeof(priOArgs)
};


/*
 * SUBSEQUENT DIRECTORY (SDM)
 */
static ITS_OCTET sdmOArgs[] =
{
    /* ITU99 Specific */
    ISUP_PRM_SUBSEQUENT_NUM,
    ISUP_PRM_MSG_COMPAT_INFO
};

SS7DLLAPI ISUP_MSG_DESC   ITU_99_ISUP_SDM_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    sdmOArgs, sizeof(sdmOArgs)
};

extern const char *
ISUP_GetFSMStateString(ITS_ISUP_STATE state);

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the class record
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name           Date           Reference              Description
 *  ---------------------------------------------------------------------------
 *   Ramesh KV   01-05-2005  AUD-ETS-SDS-01-v1.0.doc    Support for ITU 99. 
 * 
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{

    ITS_CLASS_SUPERCLASS(objClass) = isupITU97_Class;

    ISUP_DEBUG(("ClassInitialize: ITU_99...\n"));

    /* ITU 93 part */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[0] = NULL;
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[1] = &ISUP_IAM_Desc;     /* 0x01 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[2] = &ISUP_SAM_Desc;     /* 0x02 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[3] = &ISUP_INR_Desc;     /* 0x03 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[4] = &ISUP_INF_Desc;     /* 0x04 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[5] = &ISUP_COT_Desc;     /* 0x05 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[6] = &ISUP_ACM_Desc;     /* 0x06 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[7] = &ISUP_CON_Desc;     /* 0x07 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[8] = &ISUP_FOT_Desc;     /* 0x08 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[9] = &ISUP_ANM_Desc;     /* 0x09 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[10] = NULL;               /* 0x0A */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[11] = NULL;               /* 0x0B */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[12] = &ISUP_REL_Desc;     /* 0x0C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[13] = &ISUP_SUS_Desc;     /* 0x0D */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[14] = &ISUP_RES_Desc;     /* 0x0E */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[15] = NULL;               /* 0x0F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[16] = &ISUP_RLC_Desc;     /* 0x10 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[17] = &ISUP_CCR_Desc;     /* 0x11 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[18] = &ISUP_RSC_Desc;     /* 0x12 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[19] = &ISUP_BLO_Desc;     /* 0x13 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[20] = &ISUP_UBL_Desc;     /* 0x14 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[21] = &ISUP_BLA_Desc;     /* 0x15 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[22] = &ISUP_UBA_Desc;     /* 0x16 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[23] = &ISUP_GRS_Desc;     /* 0x17 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[24] = &ISUP_CGB_Desc;     /* 0x18 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[25] = &ISUP_CGU_Desc;     /* 0x19 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[26] = &ISUP_CGBA_Desc;    /* 0x1A */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[27] = &ISUP_CGUA_Desc;    /* 0x1B */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[28] = NULL;               /* 0x1C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[29] = NULL;               /* 0x1D */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[30] = NULL;               /* 0x1E */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[31] = &ISUP_FAR_Desc;     /* 0x1F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[32] = &ISUP_FAA_Desc;     /* 0x20 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[33] = &ISUP_FRJ_Desc;     /* 0x21 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[34] = NULL;               /* 0x22 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[35] = NULL;               /* 0x23 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[36] = &ISUP_LPA_Desc;     /* 0x24 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[37] = NULL;               /* 0x25 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[38] = NULL;               /* 0x26 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[39] = NULL;               /* 0x27 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[40] = &ISUP_PAM_Desc;     /* 0x28 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[41] = &ISUP_GRA_Desc;     /* 0x29 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[42] = &ISUP_CQM_Desc;     /* 0x2A */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[43] = &ISUP_CQR_Desc;     /* 0x2B */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[44] = &ISUP_CPG_Desc;     /* 0x2C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[45] = &ISUP_USR_Desc;     /* 0x2D */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[46] = &ISUP_UCIC_Desc;    /* 0x2E */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[47] = &ISUP_CFN_Desc;     /* 0x2F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[48] = &ISUP_OLM_Desc;     /* 0x30 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[49] = NULL;               /* 0x31 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[50] = &ISUP_NRM_Desc;     /* 0x32 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[51] = &ISUP_FAC_Desc;     /* 0x33 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[52] = &ISUP_UPT_Desc;     /* 0x34 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[53] = &ISUP_UPA_Desc;     /* 0x35 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[54] = &ISUP_IDR_Desc;     /* 0x36 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[55] = &ISUP_IRS_Desc;     /* 0x37 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[56] = &ISUP_SGM_Desc;     /* 0x38 */

    /* Begin - ITU 97 over-riding 93 part */

    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[6] = &ITU97_ISUP_ACM_Desc; /* 0x06 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[9] = &ITU97_ISUP_ANM_Desc; /* 0x09 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[44] = &ITU97_ISUP_CPG_Desc; /* 0x2C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[7] = &ITU97_ISUP_CON_Desc; /* 0x07 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[1] = &ITU97_ISUP_IAM_Desc; /* 0x01 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[12] = &ITU97_ISUP_REL_Desc; /* 0x0C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[50] = &ITU97_ISUP_NRM_Desc; /* 0x32 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[51] = &ITU97_ISUP_FAC_Desc; /* 0x33 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[54] = &ITU97_ISUP_IDR_Desc; /* 0x36 */

    /* End - ITU 97 over-riding 93 part */

    /* Additional Message in ITU97 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[64] = &ITU97_ISUP_LOP_Desc; /* 0x40 */

    /* Begin - ITU 99 over-riding 97-93 part */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[6] = &ITU_99_ISUP_ACM_Desc;   /* 0x06 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[9] = &ITU_99_ISUP_ANM_Desc;   /* 0x09 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[44] = &ITU_99_ISUP_CPG_Desc;  /* 0x2C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[7] = &ITU_99_ISUP_CON_Desc;   /* 0x07 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[1] = &ITU_99_ISUP_IAM_Desc;   /* 0x01 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[12] = &ITU_99_ISUP_REL_Desc;  /* 0x0C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[51] = &ITU_99_ISUP_FAC_Desc;  /* 0x33 */
  //  ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[32] = &ITU_99_ISUP_FAA_Desc;  /* 0x20 */

    /* End - ITU 99 over-riding 97-93 part */

    /* Additional Messages in ITU_99 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[65] = &ITU_99_ISUP_APM_Desc;  /* 0x41 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[66] = &ITU_99_ISUP_PRI_Desc;  /* 0x42 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[67] = &ITU_99_ISUP_SDM_Desc;  /* 0x43 */

    return (ITS_SUCCESS);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the class record
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name           Date             Reference             Description
 *  ----------------------------------------------------------------------------
 *  Ramesh KV   01-05-2005    AUD-ETS-SDS-01-v1.0.doc      Support for ITU 99. 
 *
 ****************************************************************************/
static void
ClassDestroy(ITS_Class objClass)
{
    ISUP_DEBUG(("(%s) ClassDestroy: ITU_99...\n",__FILE__));

    return;
}

/*.implementation:static
****************************************************************************
 *  Purpose:
 *      Destroy the class record.
 *
 *  Input Parameters:
 *      classRec - the class to destroy
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name           Date             Reference             Description
 *  ----------------------------------------------------------------------------
 *  Ramesh KV   01-05-2005    AUD-ETS-SDS-01-v1.0.doc      Support for ITU 99.
 *
 ****************************************************************************/
static void
ITU_ISUP_99_ClassPartDestroy(ITS_Class classRec)
{
    ISUP_DEBUG(("(%s) ITU_ISUP_99_ClassPartDestroy: ITU_99...\n",__FILE__));

    /*  Call HASH_DeleteTable for function pointers */
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to store the address of a message Handling
 *      function in the HashTable.
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *      msg - particular message to be handled.
 *      HashTable - placeholder for Message Handling function addresses
 *      State - state where the msg was received.
 *      func - function address to be inserted in the Table.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This function may be recursively called during initialization of the
 *      variant. For each msg-state combination which requires a variant
 *      specific handling, this function is called to store the address of
 *      the variant specific Message Handler function in the Hash Table.
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name           Date             Reference             Description
 *  ----------------------------------------------------------------------------
 *  Ramesh KV   01-05-2005    AUD-ETS-SDS-01-v1.0.doc      Support for ITU 99.
 *
 ****************************************************************************/
static int
ITU_ISUP_99_SetMsgProc(ITS_Class V_Class, HASH_Table MsgProcTable,
                       ITS_OCTET msgType, ITS_ISUP_STATE state,
                       __ISUP_MsgHandlerProc func)
{
    ISUP_DEBUG(("ITU_ISUP_99_SetMsgProc: mtype %d, state %d, func %x\n",
                                             msgType, state, func));

    return ISUP_SET_MSG_PROC(V_Class) ((ITS_Class)V_Class, MsgProcTable,
                                        msgType, state, func);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to set the address of a Timeout Handler function
 *      in the Hash Table.  
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *      HashTable - placeholder for Timeout Handling function addresses 
 *      Timer - particular timer which popped.
 *      State - state where the timeout indication was received.
 *      func - function address to be inserted in the Table. 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 * 
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This function is recursively called during initialization of the 
 *      variant. For each timer-state combination this function is called to 
 *      store the particular Timeout Handler function pointer in the Hash
 *      Table. 
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name           Date             Reference             Description
 *  ----------------------------------------------------------------------------
 *  Ramesh KV   01-05-2005    AUD-ETS-SDS-01-v1.0.doc      Support for ITU 99.
 *
 ****************************************************************************/
int
ITU_99_SetTimeoutProc(ITS_Class V_Class, HASH_Table TimeoutProcTable,
                      ITS_UINT tmr, ITS_ISUP_STATE state, 
                      __ISUP_TimeoutHandlerProc func)
{
    ISUP_DEBUG(("ITU_ISUP_99_SetTimeoutProc: tmr %d, state %d, func %x\n",
                                             tmr, state, func));

    return ISUP_SET_TIMEOUT_PROC(V_Class) ((ITS_Class)V_Class, TimeoutProcTable,
                                            tmr, state, func);

}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a pointer to a message handler procedure, 
 *      based on the msgType and state of the CIC. This is the main function
 *      for the ITU ISUP generic variant (ITU93) message handling procedures. 
 *
 *  Input Parameters:
 *      msgType: the type of message per ISUP.
 *      status: the state of the CIC, as defined in isup_intern.h.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Valid pointer to a function.
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name           Date             Reference             Description
 *  ----------------------------------------------------------------------------
 *  Ramesh KV   01-05-2005    AUD-ETS-SDS-01-v1.0.doc      Support for ITU 99.
 *
 ****************************************************************************/
__ISUP_MsgHandlerProc
__ISUP_GetMsgHandler_ITU_99(ITS_OCTET msgType, ITS_ISUP_STATE state)
{
    switch(state)
    {
    /*
     * This should be called only after verifying that the msgType is correct.
     */
    case IDLE:
        return __ISUP_GetMsgProc_Idle_ITU_99(msgType);
    /* IAM sent to network, waiting for ACM. */
    case WAIT_INCOMING_ACM:
        return __ISUP_GetMsgProc_WaitIncomingAcm_ITU_99(msgType);
    /* ACM sent to network, waiting for ANM. */
    case WAIT_INCOMING_ANM:
        return __ISUP_GetMsgProc_WaitIncomingAnm_ITU_99(msgType);
    /* ANM rcvd from network, call established. */
    case RCVD_INCOMING_ANM:
        return __ISUP_GetMsgProc_RcvdIncomingAnm_ITU_99(msgType);
    /* REL sent to network, waiting for RLC. */
    case WAIT_INCOMING_RLC:
        return __ISUP_GetMsgProc_WaitIncomingRlc_ITU_99(msgType);
    /* SUS rcvd from network, call suspended, waiting for RES. */
    case WAIT_INCOMING_RES:
        return __ISUP_GetMsgProc_WaitIncomingRes_ITU_99(msgType);
    /* IAM rcvd from network, waiting to send ACM. */
    case WAIT_OUTGOING_ACM:
        return __ISUP_GetMsgProc_WaitOutgoingAcm_ITU_99(msgType);
    /* ACM rcvd from network, waiting to send ANM. */
    case WAIT_OUTGOING_ANM:
        return  __ISUP_GetMsgProc_WaitOutgoingAnm_ITU_99(msgType);
    /* ANM sent to network, call established. */
    case SENT_OUTGOING_ANM:
        return  __ISUP_GetMsgProc_SentOutgoingAnm_ITU_99(msgType);
    /* REL rcvd from network, waiting to send RLC. */
    case WAIT_OUTGOING_RLC:
        return __ISUP_GetMsgProc_WaitOutgoingRlc_ITU_99(msgType);
    /* SUS sent to network, call suspended, waiting to send RES to network. */
    case WAIT_OUTGOING_RES:
        return  __ISUP_GetMsgProc_WaitOutgoingRes_ITU_99(msgType);
    /* Timeout/error, waiting to send REL to network. */
    case WAIT_OUTGOING_REL:
        return  __ISUP_GetMsgProc_WaitOutgoingRel_ITU_99(msgType);
    /* Timeout/error, waiting to send RSC to network. */
    case WAIT_OUTGOING_RSC:
        return __ISUP_GetMsgProc_WaitOutgoingRsc_ITU_99(msgType);
    case WAIT_OUTGOING_GRA:
        return __ISUP_GetMsgProc_WaitOutgoingGra_ITU_99(msgType);
    default:
        return NULL;
    }
}



/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to initialize the variant class-specific
 *      Message Handler function addresses.
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      Within this function, ONLY those addresses need to be inserted in
 *      Hash Table, which are either new or need to overwrite function
 *      addresses laid down by the base class.
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name           Date             Reference             Description
 *  ----------------------------------------------------------------------------
 *  Ramesh KV   01-05-2005    AUD-ETS-SDS-01-v1.0.doc      Support for ITU 99.
 *
 ****************************************************************************/
static int
ITU_ISUP_99_InitMsgProcs(ITS_Class classRec)
{
    ITS_USHORT state = 0;
    ITS_USHORT msg = 0;
    HASH_Table MsgProcTable = NULL;
    __ISUP_MsgHandlerProc func = NULL;

    ISUP_DEBUG(("(%s) ITU_ISUP_99_InitMsgProcs: ITU_99...\n",__FILE__));

    if ((MsgProcTable = ISUP_CLASS_HASH_MSG_PROCS(isupITU97_Class)) == NULL)
    {
        ISUP_DEBUG(("MsgProcTable access error: exiting"));
        return ITS_EINITFAIL;
    }

    for (state = 0; state < ISUP_NB_STATES; state++)
    {
        for (msg = 0; msg < ISUP_NB_MSGS; msg++)
        {
            func = __ISUP_GetMsgHandler_ITU_99((ITS_OCTET)msg, state);

            if (func)
            {
                if (ITU_ISUP_99_SetMsgProc(classRec, MsgProcTable,
                                           (ITS_OCTET)msg,
                                           state, func) != ITS_SUCCESS)
                {
                    ISUP_DEBUG(("\n could not add function entry in HASH_Table:"
                                " msg = %x, state = %x\n",
                                msg, state));

                    return ITS_ENOMEM;
                }
                else
                {
                    func = NULL;
                }
            }
        }
    }

    return ITS_SUCCESS;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the variant class-specific functionality.
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      If the variant class does not have any specific handling of the
 *      function, then it will use (inherit) the function definition in the
 *      generic variant class (ITU93). Note that this is because initialization
 *      of the ITU93 class (base class) has been already done before calling
 *      this function.
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name           Date             Reference             Description
 *  ----------------------------------------------------------------------------
 *  Ramesh KV   01-05-2005    AUD-ETS-SDS-01-v1.0.doc      Support for ITU 99.
 *
 ****************************************************************************/
static int
ITU_ISUP_99_ClassPartInitialize(ITS_Class classRec)
{
    ISUP_DEBUG(("ITU_ISUP_99_ClassPartInitialize: ITU_99...\n"));

    if (ITU_ISUP_99_InitMsgProcs(classRec) != ITS_SUCCESS)
    {
        return ITS_EINITFAIL;
    }

    return (ITS_SUCCESS);
}


/*
 * the Variant Info. record
 */
ISUP_VariantInfo isupITU_99_Info = 
{
    {
        /* Bitwise table for msgs. supported in the variant. */
        TABLE_MSG_SUPPORTED_ROW0_ITU_99,
        TABLE_MSG_SUPPORTED_ROW1_ITU_99,
        TABLE_MSG_SUPPORTED_ROW2_ITU_99,
        TABLE_MSG_SUPPORTED_ROW3_ITU93,
        TABLE_MSG_SUPPORTED_ROW4_ITU93,
        TABLE_MSG_SUPPORTED_ROWX_SET,
        TABLE_MSG_SUPPORTED_ROW1_ITU_99,
        TABLE_MSG_SUPPORTED_ROW7_ITU93,
        TABLE_MSG_SUPPORTED_ROW8_ITU_99
    },
    {
        /* Timers: CSC timers - default handling stack; others - default app. */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T1.  15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 180 },  /* Timer T2.  3 mins.              */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Timer T3.  2 mins.              */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T4.  5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T5.  5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T6.  per Q.118            */
        { ISUP_TMR_HNDL_STACK, 20  },  /* Timer T7.  20-30 sec.           */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Timer T8.  10-15 sec.           */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T9.  per Q.118            */
        { ISUP_TMR_HNDL_STACK, 4   },  /* Timer T10. 4-6 sec.             */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T11. 15-20 sec.           */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T12. 15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T13. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T14. 15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T15. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T16. 15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T17. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T18. 15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T19. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T20. 15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T21. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T22. 15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T23. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Timer T24. < 2 sec.             */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Timer T25. 1-10 s.              */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Timer T26. 1-3 mins.            */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Timer T27. 4 mins.              */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Timer T28. 10 sec.              */
        { ISUP_TMR_HNDL_STACK, 1   },  /* Timer T29. 300-600 ms. (FIXME)  */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer T30. 5-10 sec.            */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Timer T31. > 6 mins.            */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Timer T32. 3-5 sec.             */
        { ISUP_TMR_HNDL_STACK, 12  },  /* Timer T33. 12-15 sec.           */
        { ISUP_TMR_HNDL_STACK, 4   },  /* Timer T34. 2-4 sec.             */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T35. 15-20 sec.           */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Timer T36. 10-15 sec.           */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Timer T37. 2-4 sec.             */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Timer T38. per Q.118            */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T39. per Q.730            */
    },
    {
        NULL /* Array of msg. descriptors : updated within ClassInitialize() */
    },
    NULL,   /* Hash Table for message procs. : Table ptr. updated after init.*/
    NULL,   /* Hash Table for timeout procs. : Table ptr. updated after init.*/
    1,      /* First CIC in Ckgp. */
    ISUP_ITU_MAX_CICS_IN_GP,     /* Number of CICs in Circuit Group */
    0xFFU,  /* supportMsgCompInfo */
    0xFFU,  /* supportParamCompInfo */
    0x01U   /* exchangeType */
};



/*
 * the class record
 */
SS7DLLAPI ITU_ISUP_99_VARIANT_ClassRec isupITU_99_ClassRec =
{
    /* core part */
    {
        (ITS_Class)&isupITU97_ClassRec, /* superclass is ITU97 */
        sizeof(ISUP_VariantInfo),        /* sizeof instance  ??? */
        ITS_FALSE,                       /* not initted */
        0,                               /* initial refCount */
        ITU_ISUP_99_VARIANT_CLASS_NAME,  /* class name */
        ClassInitialize,                 /* class initialize ??? inherit */
        ClassDestroy,                    /* class destroy ??? inherit */
        ITU_ISUP_99_ClassPartInitialize, /* class initialize part */
        ITU_ISUP_99_ClassPartDestroy,    /* class destroy part */
        NULL,                            /* instantiate */
        NULL,                            /* destroy */
        ITS_INST_CLONE_INHERIT,          /* inherit clone */
        ITS_INST_PRINT_INHERIT,          /* inherit print */
        ITS_INST_SERIAL_INHERIT,         /* inherit serial */
        ITS_INST_EQUALS_INHERIT,         /* inherit equals */
        ITS_INST_HASH_INHERIT,           /* inherit hash */
        NULL                             /* no extension of interest */
    },
    /* VARIANT part */
    {
        &isupITU_99_Info,                 /* info */
        ISUP_DECODE_MSG_INHERIT,          /* inherit from base ISUP VARIANT */
        ISUP_ENCODE_MSG_INHERIT,          /* inherit from base ISUP VARIANT */
        ISUP_COMPUTE_MSIZE_INHERIT,       /* inherit from base ISUP VARIANT */
        ISUP_HANDLE_UNREC_MSG_INHERIT,    /* inherit from base ISUP VARIANT */
        ISUP_GET_MSG_PROC_INHERIT,        /* inherit from base ISUP VARIANT */
        ISUP_GET_TIMEOUT_PROC_INHERIT,    /* inherit from base ISUP VARIANT */

        /* Private Functions for Class Init. : Users stay out */

        ISUP_INIT_MSG_PROCS_INHERIT,      /* inherit from base ISUP VARIANT */
        ISUP_INIT_TIMEOUT_PROCS_INHERIT,  /* inherit from base ISUP VARIANT */
        ISUP_SET_MSG_PROC_INHERIT,        /* inherit from base ISUP VARIANT */
        ISUP_SET_TIMEOUT_PROC_INHERIT     /* inherit from base ISUP VARIANT */
    }
};

SS7DLLAPI ITS_Class isupITU_99_Class = (ITS_Class)&isupITU_99_ClassRec;

/*
 * Generic message and timer Handlers, for all states...
 */
                                                                                                                             
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an APM received in the RCVD_INCOMING_ANM state
 *      is done here. The message is forwarded to the application if received
 *      from the network, or vice versa.
 *      The APM message shall be sent immediately prior to the Release message
 *      ... the rest is application dependent.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name           Date             Reference             Description
 *  ----------------------------------------------------------------------------
 *  Ramesh KV   01-05-2005    AUD-ETS-SDS-01-v1.0.doc      Support for ITU 99.
 *
 ****************************************************************************/

void
__ISUP_Received_APM(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received APM in %s state from MTP3, pcic 0x%08x, vcic %d.\n",
                     ISUP_GetFSMStateString(cic_rec->fsm_state), cic_rec->pcic,
                     cic_rec->vcic));

        /* Send to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
    }
    else
    {
        ISUP_DEBUG(("Received APM in %s state from APP, pcic 0x%08x, vcic %d.\n",
                    ISUP_GetFSMStateString(cic_rec->fsm_state), cic_rec->pcic,
                    cic_rec->vcic));

        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
    }

    return;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an PRI received in the RCVD_INCOMING_ANM state
 *      is done here. The message is forwarded to the application if received
 *      from the network, or vice versa.
 *      The PRI message shall be sent immediately prior to the Release message
 *      ... the rest is application dependent. 
 *      
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
 *      
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name           Date             Reference             Description
 *  ----------------------------------------------------------------------------
 *  Ramesh KV   01-05-2005    AUD-ETS-SDS-01-v1.0.doc      Support for ITU 99.
 * 
 ****************************************************************************/
void
__ISUP_Received_PRI(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward PRI appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received PRI in %s from MTP3, pcic 0x%08x, vcic %d.\n",
                     ISUP_GetFSMStateString(cic_rec->fsm_state),
                     cic_rec->pcic, cic_rec->vcic));

        /* Send to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
    
    }
    else
    {   
        ISUP_DEBUG(("Received PRI in %s from APP, pcic 0x%08x, vcic %d.\n",
                     ISUP_GetFSMStateString(cic_rec->fsm_state),
                     cic_rec->pcic, cic_rec->vcic));
        
        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
    
    }
}



