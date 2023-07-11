/*********************************-*-H-*-**********************************
 *                                                                          *
 *             Copyright 2011 IntelliNet Technologies, Inc.                 *
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
 *
 *  ID: $Id: ssg_defines.h,v 1.1.1.1.2.2 2013/03/15 21:22:45 brajappa Exp $
 *
 *  LOG: $Log: ssg_defines.h,v $
 *  LOG: Revision 1.1.1.1.2.2  2013/03/15 21:22:45  brajappa
 *  LOG: SCCP CCITT support for IWF
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1  2013/02/22 19:26:20  lakshman
 *  LOG: Added GT configuration and encoding GT address based on config.
 *  LOG:
 *  LOG: Revision 1.1.1.1  2013/01/09 16:41:38  brajappa
 *  LOG: Initial import
 *  LOG:
 *  LOG: Revision 1.2.2.3  2013/01/03 21:07:17  lakshman
 *  LOG: update SS7_Stack macros in common area
 *  LOG:
 *  LOG: Revision 1.2.2.2  2013/01/03 19:44:55  brajappa
 *  LOG: Changes for compilation errors
 *  LOG:
 *  LOG: Revision 1.2.2.1  2012/12/22 18:07:23  lakshman
 *  LOG: update transport framework changes and have few stubs ready for later
 *  LOG: additions.
 *  LOG:
 *  LOG: Revision 1.2  2011/04/15 11:34:58  nvijikumar
 *  LOG: UT Updates
 *  LOG:
 *  LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 *  LOG: Initial Draft for SSG
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/

#if !defined(SSG_DEFINES_H)
#define SSG_DEFINES_H

#include <its++.h>
#include <engine++.h>
#include <map>

#if defined(ITS_STD_NAMESPACE)
using namespace its;
using namespace std;
#endif

#define SCMG_SS_ALLOWED         1
#define MAX_WORKERS_PER_MODULE  10
#define MAX_COL_LEN             256

#define SSG_DIA_TQ_NAME         "SsgDiaHandlerTQ"
#define SSG_ITU_TCAP_TQ_NAME    "SsgItuTcapHandlerTQ"
#define SSG_ANSI_TCAP_TQ_NAME   "SsgAnsiTcapHandlerTQ"
#define SSG_SOAP_TQ_NAME        "SsgSoapHandlerTQ"
#define SSG_PROT_CONV_TQ_NAME   "SsgProtConvHandlerTQ"

#define SSG_APP_SRC               (0xFAA1U)
#define SSG_ITU_TCAP_HLDR_SRC     (0xFAA2U)
#define SSG_ANSI_TCAP_HLDR_SRC    (0xFAA3U)
#define SSG_DIA_HLDR_SRC          (0xFAA4U)
#define SSG_PROT_CONV_HLDR_SRC    (0xFAA5U)
#define SSG_SOAP_HLDR_SRC         (0xFAA6U)

#define SSG_DIA_TQ_INST           (0xFAB1U)
#define SSG_ITU_TCAP_TQ_INST      (0xFAB2U)
#define SSG_ANSI_TCAP_TQ_INST     (0xFAB3U)
#define SSG_SOAP_TQ_INST          (0xFAB4U)
#define SSG_PROT_CONV_TQ_INST     (0xFAB5U)


#define SSG_DEFAULT_SSN         149 /*SGSN SSN */

/* TCAP Errors */
#define TCAP_RC_SUCCESS         0
#define TCAP_ABORT_TRANSACTION  550
#define TCAP_ROUTING_FAILURE    551
#define TCAP_TIMEOUT            552
#define TCAP_REJECT_RESPONSE    553
#define TCAP_ERROR_RESPONSE     554
#define TCAP_DECODE_FAILURE     555
#define TCAP_ENCODE_FAILURE     556
#define TCAP_NO_COMPONENTS 	557
#define TCAP_UNKNOWN_COMPONENT 	558
#define TCAP_INVALID_PARAMETER 	559

#if defined(USE_ANSI_SCCP)
#  undef CCITT
#  define ANSI
#  include <ansi/sccp.h>
#  if defined(DUAL_TCAP)
#    define ISS7_Stack ISS7_CCITT_Stack
#  else
#    define ISS7_Stack ISS7_ANSI_Stack
#  endif
#  undef ANSI
#  define CCITT
#elif defined(USE_CCITT_SCCP)
#  include <itu/sccp.h>
#  define ISS7_Stack ISS7_CCITT_Stack
#endif


#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#define ANSI_SCCP_GTI_001               0x01
#define ANSI_SCCP_GTI_002               0x02

#define ITU_SCCP_GTI_001                0x01
#define ITU_SCCP_GTI_002                0x02
#define ITU_SCCP_GTI_003                0x03
#define ITU_SCCP_GTI_004                0x04

#define SCCP_GTT_TT_NAT_ROAMING_SERVICE 0x03
#define SCCP_GTT_NP_ISDN_E164           0x01
#define SCCP_GTT_ES_BCD_ODD             0x01
#define SCCP_GTT_ES_BCD_EVEN            0x02
#define SCCP_GTT_ES_NATIONAL_SPECIFIC   0x03 //ITU

#define ITU_SCCP_NAI_SUBSCRIBER         0x01
#define ITU_SCCP_NAI_NSN                0x03
#define ITU_SCCP_NAI_INTERNATIONAL      0x04

#define ITU_SCCP_ENABLE_ODD_IND        ((uint8_t)(1<<7))

typedef enum ss7_prot_ver_id
{
    ITU_CAP_VERSION_1 = 1,
    ITU_CAP_VERSION_2 = 2,
    ITU_CAP_VERSION_3 = 3,
    ITU_MAP_VERSION_1 = 4,
    ITU_MAP_VERSION_2 = 5,
    ITU_MAP_VERSION_3 = 6,
    SS7_PROT_VERSION_INVALID = 15
}SS7_PROT_VER_ID;

#define MAX_CAP_VERSION   3
#define MIN_CAP_VERSION   1

/* Diamere Specific */
#define BASE_INTERFACE_APP_ID    0
#define DCCA_INTERFACE_APP_ID    4
#define VENDOR_ID                10415

/** 
 * Standard CommandCode's defined by IANA
 * For Base Interface
 **/
#define BASE_ACCT_MSG_CMD_CODE    271
#define BASE_CE_MSG_CMD_CODE      257
#define BASE_DWD_MSG_CMD_CODE     280
#define BASE_DP_MSG_CMD_CODE      282
#define BASE_RA_MSG_CMD_CODE      258
#define BASE_STR_MSG_CMD_CODE     275
#define BASE_AS_MSG_CMD_CODE      274

/** 
 * Standard CommandCode's defined by IANA
 * For RfRo Interface
 **/
#define RFRO_CC_MSG_CMD_CODE        272


/* 
 *     octet 1 bits 4321    Mobile Country Code 1st digit
 *             bits 8765    Mobile Country Code 2nd digit
 *     octet 2 bits 4321    Mobile Country Code 3rd digit
 *             bits 8765    Mobile Network Code 3rd digit
 *             or filler (1111) for 2 digit MNCs 
 *     octet 3 bits 4321    Mobile Network Code 1st digit 
 *             bits 8765    Mobile Network Code 2nd digit 
 */

#define GET_CGI_MCC(array,MCC)   \
(       \
   MCC  =((((array[0] & 0x0F) << 4) | ((array[0] & 0xF0)>> 4) )<< 4 )\
                |( array[1] & 0x0F) \
)

#define GET_CGI_MNC(array,MNC)   \
(       \
   MNC  =((array[1] & 0xF0) != 0xF0 )? \
                ((( array[1]  & 0xF0) >> 4) << 8 )\
                |(((array[2] & 0x0F)<< 4) | ( (array[2] & 0xF0)>>4)): \
                ((array[2] & 0x0F) | (array[2] & 0xF0)) \
)

// Function template to convert arrays to vectors.
template <typename T> inline std::vector<T> 
ArrayToVector(T array[],size_t size)
{ 
    return std::vector<T>(array, array + size); 
}

/*
 * Macro to get the size (count of items) of a fixed array.
 */
#define FixedArraySize(array)       \
    (sizeof(array) / sizeof(array[0]))

/*
 * Macro to convert fixed arrays (of bytes) to vectors.
 */
#define FixedByteArrayToVector(array)   \
    (vector<byte>(array, array + FixedArraySize(array)))

#define FixedLenByteArrayToVector(array, len)   \
    (vector<byte>(array, array + len))


typedef enum _ssg_prot_version
{
    SSG_UNKNOWN_VERSION = 0,
    /* CAMEL Specific */
    SSG_CAP_V1,
    SSG_CAP_V2,
    SSG_CAP_V3,
    SSG_CAP_V4,
    /* Diameter Specific */
    SSG_DIA_V1,
    /* INAP Specific */
    SSG_INAP_CS1,
    SSG_INAP_CS2,
    /* MAP Specific */
    SSG_MAP_V1,
    SSG_MAP_V2,
    SSG_MAP_V13,
    /* WIN Specific */
    SSG_WIN_VERSION,
}SSG_PROT_VERSION;

typedef enum _ssg_msgType
{
    SSG_PROT_UNKNOWN = 0,
    SSG_PROT_CAP,
    SSG_PROT_DIA,
    SSG_PROT_INAP,
    SSG_PROT_MAP,
    SSG_PROT_WIN,
}SSG_PROT_TYPE;

#endif 
