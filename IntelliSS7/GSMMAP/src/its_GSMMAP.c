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
 * CONTRACT: IntelliSS7                                                     *
 *                                                                          *
 *     FILE: its_GSMMAP.c                                                   *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: its_GSMMAP.c,v 9.1 2005/03/23 12:51:26 cvsadmin Exp $
 *
 * LOG: $Log: its_GSMMAP.c,v $
 * LOG: Revision 9.1  2005/03/23 12:51:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:26  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:45  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:18  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:03  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:56:47  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.14  2000/04/27 16:42:52  npopov
 * LOG: Added all the values for regression testing.
 * LOG:
 * LOG: Revision 2.13  2000/04/26 18:12:04  npopov
 * LOG: Added more PDU values for regression testing.
 * LOG:
 * LOG: Revision 2.12  2000/04/25 17:05:34  npopov
 * LOG: Added more PDUs for regression testing and fixed some typos in function names.
 * LOG:
 * LOG: Revision 2.10  2000/04/20 16:10:58  npopov
 * LOG: More changes for regression testing.
 * LOG:
 * LOG: Revision 2.9  2000/04/19 15:32:18  npopov
 * LOG: Added new GSMMAP PDUs for regression testing.
 * LOG:
 * LOG: Revision 2.8  2000/04/18 15:32:50  npopov
 * LOG: Changes related to cross-encoding/decoding testing.
 * LOG:
 * LOG: Revision 2.7  2000/04/17 13:58:30  npopov
 * LOG: Changes related to cross-encoding/decoding regression testing.
 * LOG:
 * LOG: Revision 2.6  2000/04/14 17:03:45  mmiers
 * LOG:
 * LOG:
 * LOG: Fix merge problem.
 * LOG:
 * LOG: Revision 2.5  2000/04/13 21:28:20  mmiers
 * LOG:
 * LOG:
 * LOG: More changes from Saritel integration.
 * LOG:
 * LOG: Revision 2.4  2000/04/12 16:58:16  npopov
 * LOG: Fixed a problem with regression testing when decoding PurgeMS_Arg.
 * LOG:
 * LOG: Revision 2.3  2000/04/12 15:53:11  npopov
 * LOG: Changes related to regression testing
 * LOG:
 * LOG: Revision 2.2  2000/03/31 21:24:27  omayor
 * LOG: Added functions to encode/decode user_info, DialoguePDU
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:24  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:03  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.7  1999/03/15 17:31:55  mmiers
 * LOG:
 * LOG:
 * LOG: Add license checks in.
 * LOG:
 * LOG: Revision 1.6  1999/03/02 22:46:26  mmiers
 * LOG:
 * LOG:
 * LOG: Update for new TCAP.
 * LOG:
 * LOG: Revision 1.5.2.1  1999/03/02 22:27:04  mmiers
 * LOG:
 * LOG:
 * LOG: Update for prototypes.
 * LOG:
 * LOG: Revision 1.5  1998/10/23 21:25:07  jpakrasi
 * LOG: Rework error checks for decode functions.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 20:46:20  mmiers
 * LOG: Minor build tweak for UNIX.
 * LOG:
 * LOG: Revision 1.3  1998/10/21 20:38:17  mmiers
 * LOG: Remove generated files.
 * LOG:
 * LOG: Revision 1.2  1998/10/21 20:03:27  jpakrasi
 * LOG: Unit tested. Somewhat stable. Undergoing testing at Nokia.
 * LOG:
 * LOG: Revision 1.1  1998/08/26 14:55:30  jpakrasi
 * LOG: First time compile on NT.
 * LOG:
 *
 ****************************************************************************/

#if !defined(TANDEM)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <its.h>
#include <its_license.h>

#if defined(CCITT)
#include <itu/tcap.h>
#elif defined(ANSI)
#include <ansi/tcap.h>
#endif

#include <itu/GSMMAP.h>
#include <itu/GSMMAP-types.h>
#include <itu/its_GSMMAP.h>

#ifndef RENAME_API
#ifdef DEBUG
int gsm_debug = 1;
#else
int gsm_debug = 0;
#endif
#else
extern int gsm_debug;
#endif /* !RENAME_API */


#if defined(OSS_ENCODE) || defined(OSS_DECODE)
#include "gsmmapvn.h"
int getEncodedPDU(int pduNum, char **encodedPDU, int *encodedPDULength);
int getDecodedPDU(int pduNum, char *encodedPDU,
				int encodedPDULength, void **decodedPDU);
#ifdef RENAME_API
/*
 * Renaming the APIs is needed for running interoperability regression tests
 * with the following sequence of events in one executable: encoding with OSS-->
 * decoding with IntelliNet-->encoding with IntelliNet what was decoded-->
 * decoding with OSS.
 */
#include "itu/gsmmapcodetest.h"
#endif /* RENAME_API */
#endif /* OSS_ENCODE || OSS_DECODE */

#else /* TANDEM */

#include <stdioh>
#include <stdlibh>
#include <asserth>

#include <itsh>
#include <itslicen>

#if defined(CCITT)
#include <itutcap>
#elif defined(ANSI)
#include <ansitcap>
#endif

#include <GSMMAPh>
#include <itsGSMMA>
#include <GSMMAPty>

#endif /* TANDEM */

/*
 * OIDs for MAP
 */
/*
 * Location Update
 */
static unsigned int NetworkLocUpV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_NETWORK_LOC_UP,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPNetworkLocUpV2 =
{
    sizeof(NetworkLocUpV2Value) / sizeof(unsigned int),
    NetworkLocUpV2Value
};
static unsigned int NetworkLocUpV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_NETWORK_LOC_UP,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPNetworkLocUpV1 =
{
    sizeof(NetworkLocUpV1Value) / sizeof(unsigned int),
    NetworkLocUpV1Value
};
/***********/

/*
 * Location Cancel
 */
static unsigned int LocationCancelV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_LOCATION_CANCEL,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPLocationCancelV2 =
{
    sizeof(LocationCancelV2Value) / sizeof(unsigned int),
    LocationCancelV2Value
};
static unsigned int LocationCancelV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_LOCATION_CANCEL,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPLocationCancelV1 =
{
    sizeof(LocationCancelV1Value) / sizeof(unsigned int),
    LocationCancelV1Value
};
/***************/

/*
 * RoaminNumberEnquiry
 */
static unsigned int RoamingNbEnquiryV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_ROAMING_NB_INQ,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPRoamingNbEnquiryV2 =
{
    sizeof(RoamingNbEnquiryV2Value) / sizeof(unsigned int),
    RoamingNbEnquiryV2Value
};
static unsigned int RoamingNbEnquiryV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_ROAMING_NB_INQ,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPRoamingNbEnquiryV1 =
{
    sizeof(RoamingNbEnquiryV1Value) / sizeof(unsigned int),
    RoamingNbEnquiryV1Value
};
/***************/

/*
 * Location Info Retrieval
 */
static unsigned int LocationInfoRetrievalV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_LOCATION_INFO_RETRIEVAL,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPLocationInfoRetrievalV2 =
{
    sizeof(LocationInfoRetrievalV2Value) / sizeof(unsigned int),
    LocationInfoRetrievalV2Value
};
static unsigned int LocationInfoRetrievalV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_LOCATION_INFO_RETRIEVAL,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPLocationInfoRetrievalV1 =
{
    sizeof(LocationInfoRetrievalV1Value) / sizeof(unsigned int),
    LocationInfoRetrievalV1Value
};
/***************/

/*
 * Reset
 */
static unsigned int ResetContextV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_RESET,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPResetContextV2 =
{
    sizeof(ResetContextV2Value) / sizeof(unsigned int),
    ResetContextV2Value
};
static unsigned int ResetContextV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_RESET,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPResetContextV1 =
{
    sizeof(ResetContextV1Value) / sizeof(unsigned int),
    ResetContextV1Value
};
/***************/

/*
 * Handover Control
 */
static unsigned int HandoverControlV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_HANDOVER_CONTROL,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPHandoverControlV2 =
{
    sizeof(HandoverControlV2Value) / sizeof(unsigned int),
    HandoverControlV2Value
};
static unsigned int HandoverControlV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_HANDOVER_CONTROL,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPHandoverControlV1 =
{
    sizeof(HandoverControlV1Value) / sizeof(unsigned int),
    HandoverControlV1Value
};
/***************/

/*
 * Equipment Mngt
 */
static unsigned int EquipmentMngtV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_EQUIPMENT_MNGT,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPEquipmentMngtV2 =
{
    sizeof(EquipmentMngtV2Value) / sizeof(unsigned int),
    EquipmentMngtV2Value
};
static unsigned int EquipmentMngtV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_EQUIPMENT_MNGT,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPEquipmentMngtV1 =
{
    sizeof(EquipmentMngtV1Value) / sizeof(unsigned int),
    EquipmentMngtV1Value
};
/***************/

/*
 * INFO_RETRIEVAL
 */
static unsigned int InfoRetrievalV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_INFO_RETRIEVAL,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPInfoRetrievalV2 =
{
    sizeof(InfoRetrievalV2Value) / sizeof(unsigned int),
    InfoRetrievalV2Value
};
static unsigned int InfoRetrievalV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_INFO_RETRIEVAL,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPInfoRetrievalV1 =
{
    sizeof(InfoRetrievalV1Value) / sizeof(unsigned int),
    InfoRetrievalV1Value
};
/***************/

/*
 * VLR Info Retrieval
 */
static unsigned int VLRInfoRetrievalV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_LOCATION_INFO_RETRIEVAL,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPVLRInfoRetrievalV2 =
{
    sizeof(VLRInfoRetrievalV2Value) / sizeof(unsigned int),
    VLRInfoRetrievalV2Value
};
/***************/

/*
 * Subscriber Data Management
 */
static unsigned int SubscriberDataMngtV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_SUBSCRIBER_DATA_MNGT,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPSubscriberDataMngtV2 =
{
    sizeof(SubscriberDataMngtV2Value) / sizeof(unsigned int),
    SubscriberDataMngtV2Value
};
static unsigned int SubscriberDataMngtV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_SUBSCRIBER_DATA_MNGT,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPSubscriberDataMngtV1 =
{
    sizeof(SubscriberDataMngtV1Value) / sizeof(unsigned int),
    SubscriberDataMngtV1Value
};
/***************/

/*
 * Tracing Context
 */
static unsigned int TracingContextV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_TRACING_CONTEXT,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPTracingContextV2 =
{
    sizeof(TracingContextV2Value) / sizeof(unsigned int),
    TracingContextV2Value
};
static unsigned int TracingContextV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_TRACING_CONTEXT,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPTracingContextV1 =
{
    sizeof(TracingContextV1Value) / sizeof(unsigned int),
    TracingContextV1Value
};
/***************/

/*
 * Network Functional SS
 */
static unsigned int NetworkFunctionalSSV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_NETWORK_FUNCTIONAL_SS,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPNetworkFunctionalSSV2 =
{
    sizeof(NetworkFunctionalSSV2Value) / sizeof(unsigned int),
    NetworkFunctionalSSV2Value
};
static unsigned int NetworkFunctionalSSV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_NETWORK_FUNCTIONAL_SS,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPNetworkFunctionalSSV1 =
{
    sizeof(NetworkFunctionalSSV1Value) / sizeof(unsigned int),
    NetworkFunctionalSSV1Value
};
/***************/

/*
 * Network Unstructured SS
 */
static unsigned int NetworkUnstructuredSSV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_NETWORK_UNSTRUCTURED_SS,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPNetworkUnstructuredSSV2 =
{
    sizeof(NetworkUnstructuredSSV2Value) / sizeof(unsigned int),
    NetworkUnstructuredSSV2Value
};
/***************/

/*
 * Short Msg Gateway
 */
static unsigned int ShortMsgGatewayV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_SHORT_MSG_GATEWAY,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPShortMsgGatewayV2 =
{
    sizeof(ShortMsgGatewayV2Value) / sizeof(unsigned int),
    ShortMsgGatewayV2Value
};
static unsigned int ShortMsgGatewayV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_SHORT_MSG_GATEWAY,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPShortMsgGatewayV1 =
{
    sizeof(ShortMsgGatewayV1Value) / sizeof(unsigned int),
    ShortMsgGatewayV1Value
};
/***************/

/*
 * Short Msg MO Relay
 */
static unsigned int ShortMsgMORelayV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_SHORT_MSG_MO_RELAY,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPShortMsgMORelayV2 =
{
    sizeof(ShortMsgMORelayV2Value) / sizeof(unsigned int),
    ShortMsgMORelayV2Value
};
static unsigned int ShortMsgMORelayV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_SHORT_MSG_MO_RELAY,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPShortMsgMORelayV1 =
{
    sizeof(ShortMsgMORelayV1Value) / sizeof(unsigned int),
    ShortMsgMORelayV1Value
};
/***************/

/*
 * Short Msg Alert
 */
static unsigned int ShortMsgAlertV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_SHORT_MSG_ALERT,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPShortMsgAlertV2 =
{
    sizeof(ShortMsgAlertV2Value) / sizeof(unsigned int),
    ShortMsgAlertV2Value
};
static unsigned int ShortMsgAlertV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_SHORT_MSG_ALERT,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPShortMsgAlertV1 =
{
    sizeof(ShortMsgAlertV1Value) / sizeof(unsigned int),
    ShortMsgAlertV1Value
};
/***************/

/*
 * MWD Mngt
 */
static unsigned int MWDMngtV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_MWD_MNGT,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPMWDMngtV2 =
{
    sizeof(MWDMngtV2Value) / sizeof(unsigned int),
    MWDMngtV2Value
};
static unsigned int MWDMngtV1Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_MWD_MNGT,
    GSMMAP_OID_CPT_MAP_V1
};
OIDentifier GSMMAPMWDMngtV1 =
{
    sizeof(MWDMngtV1Value) / sizeof(unsigned int),
    MWDMngtV1Value
};
/***************/

/*
 * Short Msg MT
 */
static unsigned int ShortMsgMTV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_SHORT_MSG_MT,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPShortMsgMTV2 =
{
    sizeof(ShortMsgMTV2Value) / sizeof(unsigned int),
    ShortMsgMTV2Value
};
/***************/

/*
 * IMSI Retrieval
 */
static unsigned int IMSIRetrievalV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_SHORT_MSG_MT,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPIMSIRetrievalV2 =
{
    sizeof(IMSIRetrievalV2Value) / sizeof(unsigned int),
    IMSIRetrievalV2Value
};
/***************/

/*
 * MS Purging
 */
static unsigned int MSPurgingV2Value[] =
{
    GSMMAP_OID_CPT_CCITT,
    GSMMAP_OID_CPT_IDEN_ORG,
    GSMMAP_OID_CPT_ETSI,
    GSMMAP_OID_CPT_MOBILE_DOMAIN,
    GSMMAP_OID_CPT_GSM_NETWORK,
    GSMMAP_OID_CPT_AC_ID,
    GSMMAP_OID_CPT_SHORT_MSG_MT,
    GSMMAP_OID_CPT_MAP_V2
};
OIDentifier GSMMAPMSPurgingV2 =
{
    sizeof(MSPurgingV2Value) / sizeof(unsigned int),
    MSPurgingV2Value
};
/***************/

/*
 * GSM MAP Messages according to OPERATIONs (43 in all).
 */

/*** UpdateLocation OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Update Location invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_UpdateLocationArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeUpdateLocationArg();
 *
 ****************************************************************************/
int
GSMMAP_SendUpdateLocationArg( ITS_HANDLE handle, ITS_HDR *hdr,
                              TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(UpdateLocationArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_UpdateLocationArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_UpdateLocationArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_UpdateLocationArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_updateLocation;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_updateLocation;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_UpdateLocationArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Update Location invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_UpdateLocationArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_UpdateLocationArg(data);
 *
 *  See Also:
 *      GSMMAP_SendUpdateLocationArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeUpdateLocationArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err = 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(UpdateLocationArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_UpdateLocationArg(pe, 1, NULL, NULL,
                                        (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_UpdateLocationArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Update Location return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_UpdateLocationRes*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeUpdateLocationRes();
 *
 ****************************************************************************/
int
GSMMAP_SendUpdateLocationRes( ITS_HANDLE handle, ITS_HDR *hdr,
                              TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(UpdateLocationRes_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_UpdateLocationRes(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_UpdateLocationRes(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_UpdateLocationRes(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_updateLocation;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_UpdateLocationRes(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Update Location return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_UpdateLocationRes*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_UpdateLocationRes(data);
 *
 *  See Also:
 *      GSMMAP_SendUpdateLocationRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeUpdateLocationRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(UpdateLocationRes_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_UpdateLocationRes(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_UpdateLocationRes(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** CancelLocation OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Cancel Location invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_CancelLocationArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeCancelLocationArg();
 *
 ****************************************************************************/
int
GSMMAP_SendCancelLocationArg( ITS_HANDLE handle, ITS_HDR *hdr,
                              TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(CancelLocationArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_CancelLocationArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_CancelLocationArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_CancelLocationArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_cancelLocation;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_cancelLocation;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_CancelLocationArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Cancel Location invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_CancelLocationArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_CancelLocationArg(data);
 *
 *  See Also:
 *      GSMMAP_SendCancelLocationArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeCancelLocationArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }

#ifdef OSS_DECODE
    ret = getDecodedPDU(CancelLocationArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_CancelLocationArg(pe, 1, NULL, NULL,
                                        (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_CancelLocationArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** PurgeMS OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Purge MS invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PurgeMS__Arg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodePurgeMS_Arg();
 *
 ****************************************************************************/
int
GSMMAP_SendPurgeMS_Arg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                        void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(PurgeMS_Arg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_PurgeMS__Arg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PurgeMS__Arg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_PurgeMS__Arg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_purgeMS;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_purgeMS;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_PurgeMS__Arg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Purge MS invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PurgeMS__Arg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_PurgeMS__Arg(data);
 *
 *  See Also:
 *      GSMMAP_SendPurgeMS_Arg();
 *
 ****************************************************************************/
int
GSMMAP_DecodePurgeMS_Arg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(PurgeMS_Arg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_PurgeMS__Arg(pe, 1, NULL, NULL, (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PurgeMS__Arg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** SendIdentification OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Send Identification invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendIdentificationArgTmsi*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeSendIdentificationArg();
 *
 ****************************************************************************/
int
GSMMAP_SendSendIdentificationArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(SendIdentificationArgTmsi_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_SendIdentificationArgTmsi(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendIdentificationArgTmsi(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_SendIdentificationArgTmsi(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_sendIdentification;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_sendIdentification;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_SendIdentificationArgTmsi(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Send Identification invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendIdentificationArgTmsi*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_SendIdentificationArgTmsi(data);
 *
 *  See Also:
 *      GSMMAP_SendSendIdentificationArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeSendIdentificationArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(SendIdentificationArgTmsi_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_SendIdentificationArgTmsi(pe, 1, NULL, NULL,
                                                (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendIdentificationArgTmsi(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Send Identification return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendIdentificationRes*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeSendIdentificationRes();
 *
 ****************************************************************************/
int
GSMMAP_SendSendIdentificationRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(SendIdentificationRes_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_SendIdentificationRes(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendIdentificationRes(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_SendIdentificationRes(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_sendIdentification;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_SendIdentificationRes(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Send Identification return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendIdentificationRes*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_SendIdentificationRes(data);
 *
 *  See Also:
 *      GSMMAP_SendSendIdentificationRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeSendIdentificationRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(SendIdentificationRes_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_SendIdentificationRes(pe, 1, NULL, NULL,
                                            (char **)data) ==  NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendIdentificationRes(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** PerformHandover OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To Send a Perform HO invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PerformHO__Arg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodePerformHO_Arg();
 *
 ****************************************************************************/
int
GSMMAP_SendPerformHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                          void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(PerformHO_Arg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_PerformHO__Arg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PerformHO__Arg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_PerformHO__Arg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_performHandover;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_performHandover;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_PerformHO__Arg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Perform HO invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PerformHO__Arg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_PerformHO__Arg(data);
 *
 *  See Also:
 *      GSMMAP_SendPerformHO_Arg();
 *
 ****************************************************************************/
int
GSMMAP_DecodePerformHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(PerformHO_Arg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_PerformHO__Arg(pe, 1, NULL, NULL, (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PerformHO__Arg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Perform HO return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PerformHO__Res*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodePerformHO_Res();
 *
 ****************************************************************************/
int
GSMMAP_SendPerformHO_Res( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                          void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(PerformHO_Res_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_PerformHO__Res(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PerformHO__Res(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_PerformHO__Res(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_performHandover;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_PerformHO__Res(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Perform HO return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PerformHO__Res*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_PerformHO__Res(data);
 *
 *  See Also:
 *      GSMMAP_SendPerformHO_Res();
 *
 ****************************************************************************/
int
GSMMAP_DecodePerformHO_Res( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(PerformHO_Res_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_PerformHO__Res(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PerformHO__Res(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** PrepareHandover OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Prepare HO invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PrepareHO__Arg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodePrepareHO_Arg();
 *
 ****************************************************************************/
int
GSMMAP_SendPrepareHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                          void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(PrepareHO_Arg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_PrepareHO__Arg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PrepareHO__Arg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_PrepareHO__Arg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_prepareHandover;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_prepareHandover;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_PrepareHO__Arg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Prepare HO invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PrepareHO__Arg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_PrepareHO__Arg(data);
 *
 *  See Also:
 *      GSMMAP_SendPrepareHO_Arg();
 *
 ****************************************************************************/
int
GSMMAP_DecodePrepareHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(PrepareHO_Arg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_PrepareHO__Arg(pe, 1, NULL, NULL, (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PrepareHO__Arg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Prepare HO return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PrepareHO__Res*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodePrepareHO_Res();
 *
 ****************************************************************************/
int
GSMMAP_SendPrepareHO_Res( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                          void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(PrepareHO_Res_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_PrepareHO__Res(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PrepareHO__Res(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_PrepareHO__Res(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_prepareHandover;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_PrepareHO__Res(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Prepare HO return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PrepareHO__Res*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_PrepareHO__Res(data);
 *
 *  See Also:
 *      GSMMAP_SendPrepareHO_Res();
 *
 ****************************************************************************/
int
GSMMAP_DecodePrepareHO_Res( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(PrepareHO_Res_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_PrepareHO__Res(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PrepareHO__Res(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** SendEndSignal OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Send End Signal invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendEndSignalArgBss__APDU*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeSendEndSignalArg();
 *
 ****************************************************************************/
int
GSMMAP_SendSendEndSignalArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                             void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(SendEndSignalArgBss_APDU_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_SendEndSignalArgBss__APDU(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendEndSignalArgBss__APDU(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_SendEndSignalArgBss__APDU(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_sendEndSignal;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_sendEndSignal;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_SendEndSignalArgBss__APDU(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Send End Signal invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendEndSignalArgBss__APDU*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_SendEndSignalArgBss__APDU(data);
 *
 *  See Also:
 *      GSMMAP_SendSendEndSignalArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeSendEndSignalArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                               void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(SendEndSignalArgBss_APDU_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_SendEndSignalArgBss__APDU(pe, 1, NULL, NULL,
                                               (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendEndSignalArgBss__APDU(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** ProcessAccessSignalling OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Process Access Signaling invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ProcessAccessSignallingArgBss__APDU*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeProcessAccessSignallingArg();
 *
 ****************************************************************************/
int
GSMMAP_SendProcessAccessSignallingArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ProcessAccessSignallingArgBss_APDU_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ProcessAccessSignallingArgBss__APDU(&pe, 1, 0, NULL,
                                                         data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ProcessAccessSignallingArgBss__APDU(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ProcessAccessSignallingArgBss__APDU(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_processAccessSignalling;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_processAccessSignalling;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ProcessAccessSignallingArgBss__APDU(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Process Access Signalling invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ProcessAccessSignallingArgBss__APDU*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ProcessAccessSignallingArgBss__APDU(data);
 *
 *  See Also:
 *      GSMMAP_SendProcessAccessSignallingArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeProcessAccessSignallingArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ProcessAccessSignallingArgBss_APDU_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ProcessAccessSignallingArgBss__APDU(pe, 1, NULL, NULL,
                                                        (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ProcessAccessSignallingArgBss__APDU(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** ForwardAccessSignalling OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Forward Access Signalling invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ForwardAccessSignallingArgBss__APDU*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeForwardAccessSignallingArg();
 *
 ****************************************************************************/
int
GSMMAP_SendForwardAccessSignallingArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ForwardAccessSignallingArgBss_APDU_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ForwardAccessSignallingArgBss__APDU(&pe, 1, 0, NULL,
                                                         data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ForwardAccessSignallingArgBss__APDU(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ForwardAccessSignallingArgBss__APDU(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_forwardAccessSignalling;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_forwardAccessSignalling;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ForwardAccessSignallingArgBss__APDU(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Forward Access Signalling invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ForwardAccessSignallingArgBss__APDU*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ForwardAccessSignallingArgBss__APDU(data);
 *
 *  See Also:
 *      GSMMAP_SendForwardAccessSignallingArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeForwardAccessSignallingArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ForwardAccessSignallingArgBss_APDU_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ForwardAccessSignallingArgBss__APDU(pe, 1, NULL, NULL,
                                                        (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ForwardAccessSignallingArgBss__APDU(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** PerformSubsequentHandover OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Perform Subsequent HO invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PerformSubsequentHO__Arg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodedPerformSubsequentHO_Arg();
 *
 ****************************************************************************/
int
GSMMAP_SendPerformSubsequentHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(PerformSubsequentHO_Arg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_PerformSubsequentHO__Arg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PerformSubsequentHO__Arg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_PerformSubsequentHO__Arg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_performSubsequentHandover;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_performSubsequentHandover;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_PerformSubsequentHO__Arg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Perform Subsequent HO invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PerformSubsequentHO__Arg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_PerformSubsequentHO__Arg(data);
 *
 *  See Also:
 *      GSMMAP_SendPerformSubsequentHO_Arg();
 *
 ****************************************************************************/
int
GSMMAP_DecodePerformSubsequentHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(PerformSubsequentHO_Arg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_PerformSubsequentHO__Arg(pe, 1, NULL, NULL,
                                               (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PerformSubsequentHO__Arg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Perform Subsequent HO return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PerformSubsequentHOResAccessSignalInfo*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodePerformSubsequentHO_Res();
 *
 ****************************************************************************/
int
GSMMAP_SendPerformSubsequentHO_Res( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(PerformSubsequentHOResAccessSignalInfo_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_PerformSubsequentHOResAccessSignalInfo(&pe, 1, 0, NULL,
                                                             data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PerformSubsequentHOResAccessSignalInfo(pe, 1, 0, NULL,
                                                            data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_PerformSubsequentHOResAccessSignalInfo(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_performSubsequentHandover;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_PerformSubsequentHOResAccessSignalInfo(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Perform Subsequent HO return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PerformSubsequentHOResAccessSignalInfo*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_PerformSubsequentHOResAccessSignalInfo(data);
 *
 *  See Also:
 *      GSMMAP_SendPerformSubsequentHO_Res();
 *
 ****************************************************************************/
int
GSMMAP_DecodePerformSubsequentHO_Res( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(PerformSubsequentHOResAccessSignalInfo_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_PerformSubsequentHOResAccessSignalInfo(pe, 1, NULL, NULL,
                                                             (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PerformSubsequentHOResAccessSignalInfo(pe, 1, 0, NULL,
                                                            data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** PrepareSubsequentHandover OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Prepare Subsequent HO invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PrepareSubsequentHO__Arg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodePrepareSubsequentHO_Arg();
 *
 ****************************************************************************/
int
GSMMAP_SendPrepareSubsequentHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(PrepareSubsequentHO_Arg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_PrepareSubsequentHO__Arg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PrepareSubsequentHO__Arg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_PrepareSubsequentHO__Arg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_prepareSubsequentHandover;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_prepareSubsequentHandover;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_PrepareSubsequentHO__Arg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Prepare Subsequent HO invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PrepareSubsequentHO__Arg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_PrepareSubsequentHO__Arg(data);
 *
 *  See Also:
 *      GSMMAP_SendPrepareSubsequentHO_Arg();
 *
 ****************************************************************************/
int
GSMMAP_DecodePrepareSubsequentHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(PrepareSubsequentHO_Arg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_PrepareSubsequentHO__Arg(pe, 1, NULL, NULL,
                                               (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PrepareSubsequentHO__Arg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Prepare Subsequent HO return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PrepareSubsequentHOResBss__APDU*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodePrepareSubsequentHO_Res();
 *
 ****************************************************************************/
int
GSMMAP_SendPrepareSubsequentHO_Res( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(PrepareSubsequentHOResBss_APDU_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_PrepareSubsequentHOResBss__APDU(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PrepareSubsequentHOResBss__APDU(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_PrepareSubsequentHOResBss__APDU(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_prepareSubsequentHandover;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_PrepareSubsequentHOResBss__APDU(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Prepare Subsequent HO return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_PrepareSubsequentHOResBss__APDU*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_PrepareSubsequentHOResBss__APDU(data);
 *
 *  See Also:
 *      GSMMAP_SendPrepareSubsequentHO_Res()
 *
 ****************************************************************************/
int
GSMMAP_DecodePrepareSubsequentHO_Res( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(PrepareSubsequentHOResBss_APDU_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_PrepareSubsequentHOResBss__APDU(pe, 1, NULL, NULL,
                                                (char **)data) ==  NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_PrepareSubsequentHOResBss__APDU(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** SendAuthenticationInfo OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Send Authentication Info invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendAuthenticationArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeSendAuthenticationInfoArg();
 *
 ****************************************************************************/
int
GSMMAP_SendSendAuthenticationInfoArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                      TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(SendAuthenticationArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_SendAuthenticationArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendAuthenticationArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_SendAuthenticationArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_sendAuthenticationInfo;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_sendAuthenticationInfo;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_SendAuthenticationArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Send Authentication Info invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendAuthenticationArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_SendAuthenticationArg(data);
 *
 *  See Also:
 *      GSMMAP_SendSendAuthenticationInfoArg()
 *
 ****************************************************************************/
int
GSMMAP_DecodeSendAuthenticationInfoArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                        void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(SendAuthenticationArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_SendAuthenticationArg(pe, 1, NULL, NULL,
                                            (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendAuthenticationArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Send Authentification Info return result
 *      component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendAuthenticationRes*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeSendAuthenticationInfoRes()
 *
 ****************************************************************************/
int
GSMMAP_SendSendAuthenticationInfoRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                      TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(SendAuthenticationRes_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_SendAuthenticationRes(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendAuthenticationRes(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_SendAuthenticationRes(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_sendAuthenticationInfo;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_SendAuthenticationRes(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Send Authentification Info return result parameter
 *      sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendAuthenticationRes*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_SendAuthenticationRes(data);
 *
 *  See Also:
 *      GSMMAP_SendSendAuthenticationInfoRes()
 *
 *
 ****************************************************************************/
int
GSMMAP_DecodeSendAuthenticationInfoRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                        void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(SendAuthenticationRes_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_SendAuthenticationRes(pe, 1, NULL, NULL,
                                            (char **)data) ==  NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendAuthenticationRes(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** CheckIMEI OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Check IMEI invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_CheckIMEIArgImei*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeCheckIMEIArg()
 *
 ****************************************************************************/
int
GSMMAP_SendCheckIMEIArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                         void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(CheckIMEIArgImei_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_CheckIMEIArgImei(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_CheckIMEIArgImei(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_CheckIMEIArgImei(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_checkIMEI;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_checkIMEI;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_CheckIMEIArgImei(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Check IMEI invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_CheckIMEIArgImei*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_CheckIMEIArgImei(data);
 *
 *  See Also:
 *      GSMMAP_SendCheckIMEIArg()
 *
 ****************************************************************************/
int
GSMMAP_DecodeCheckIMEIArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(CheckIMEIArgImei_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_CheckIMEIArgImei(pe, 1, NULL, NULL,
                                       (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_CheckIMEIArgImei(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Check IMEI return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_CheckIMEIResEquipmentStatus*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeCheckIMEIRes()
 *
 ****************************************************************************/
int
GSMMAP_SendCheckIMEIRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                         void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(CheckIMEIResEquipmentStatus_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_CheckIMEIResEquipmentStatus(&pe, 1, 0, NULL, data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_CheckIMEIResEquipmentStatus(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_CheckIMEIResEquipmentStatus(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_checkIMEI;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_CheckIMEIResEquipmentStatus(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Check IMEI return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_CheckIMEIResEquipmentStatus*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_CheckIMEIResEquipmentStatus(data);
 *
 *  See Also:
 *      GSMMAP_SendCheckIMEIRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeCheckIMEIRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(CheckIMEIResEquipmentStatus_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_CheckIMEIResEquipmentStatus(pe, 1, NULL, NULL,
                                                  (char **)data) ==  NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_CheckIMEIResEquipmentStatus(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** SendParameters OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Send Parameter invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendParametersArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeSendParametersArg();
 *
 ****************************************************************************/
int
GSMMAP_SendSendParametersArg( ITS_HANDLE handle, ITS_HDR *hdr,
                              TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(SendParametersArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_SendParametersArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendParametersArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_SendParametersArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_sendParameters;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_sendParameters;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_SendParametersArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Send Parameter invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendParametersArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_SendParametersArg(data);
 *
 *  See Also:
 *      GSMMAP_SendSendParametersArg()
 *
 ****************************************************************************/
int
GSMMAP_DecodeSendParametersArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(SendParametersArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_SendParametersArg(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendParametersArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Send Parameter return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SentParameterList*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeSendParametersRes()
 *
 ****************************************************************************/
int
GSMMAP_SendSendParametersRes( ITS_HANDLE handle, ITS_HDR *hdr,
                              TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(SentParameterList_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_SentParameterList(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SentParameterList(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_SentParameterList(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_sendParameters;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_SentParameterList(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Send Parameter return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SentParameterList*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_SentParameterList(data);
 *
 *  See Also:
 *      GSMMAP_SendSendParametersRes()
 *
 ****************************************************************************/
int
GSMMAP_DecodeSendParametersRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(SentParameterList_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_SentParameterList(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SentParameterList(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** InsertSubscriberData OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Insert Subscriber Data invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_InsertSubscriberDataArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeInsertSubscriberDataArg();
 *
 ****************************************************************************/
int
GSMMAP_SendInsertSubscriberDataArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(InsertSubscriberDataArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_InsertSubscriberDataArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_InsertSubscriberDataArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_InsertSubscriberDataArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_insertSubscriberData;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_insertSubscriberData;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_InsertSubscriberDataArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Insert Subscriber Data invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_InsertSubscriberDataArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_InsertSubscriberDataArg(data);
 *
 *  See Also:
 *      GSMMAP_SendInsertSubscriberDataArg()
 *
 ****************************************************************************/
int
GSMMAP_DecodeInsertSubscriberDataArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(InsertSubscriberDataArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_InsertSubscriberDataArg(pe, 1, NULL, NULL,
                                              (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_InsertSubscriberDataArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Insert Subscriber Data return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_InsertSubscriberDataRes*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeInsertSubscriberDataRes()
 *
 ****************************************************************************/
int
GSMMAP_SendInsertSubscriberDataRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(InsertSubscriberDataRes_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_InsertSubscriberDataRes(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_InsertSubscriberDataRes(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_InsertSubscriberDataRes(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_insertSubscriberData;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_InsertSubscriberDataRes(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Insert Subscriber Data return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_InsertSubscriberDataRes*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_InsertSubscriberDataRes(data);
 *
 *  See Also:
 *      GSMMAP_SendInsertSubscriberDataRes()
 *
 ****************************************************************************/
int
GSMMAP_DecodeInsertSubscriberDataRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(InsertSubscriberDataRes_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_InsertSubscriberDataRes(pe, 1, NULL, NULL,
                                              (char **)data) ==  NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_InsertSubscriberDataRes(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** DeleteSubscriberData OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Delete Subscriber Data invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_DeleteSubscriberDataArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeDeleteSubscriberDataArg()
 *
 ****************************************************************************/
int
GSMMAP_SendDeleteSubscriberDataArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(DeleteSubscriberDataArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_DeleteSubscriberDataArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_DeleteSubscriberDataArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_RestoreDataArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_deleteSubscriberData;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_deleteSubscriberData;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_DeleteSubscriberDataArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Delete Subscriber Data invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_DeleteSubscriberDataArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_DeleteSubscriberDataArg(data);
 *
 *  See Also:
 *      GSMMAP_SendDeleteSubscriberDataArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeDeleteSubscriberDataArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(DeleteSubscriberDataArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_DeleteSubscriberDataArg(pe, 1, NULL, NULL,
                                              (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_DeleteSubscriberDataArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Delete Subscriber Data return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_DeleteSubscriberDataRes*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeDeleteSubscriberDataRes();
 *
 ****************************************************************************/
int
GSMMAP_SendDeleteSubscriberDataRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(DeleteSubscriberDataRes_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_DeleteSubscriberDataRes(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_DeleteSubscriberDataRes(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_DeleteSubscriberDataRes(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_deleteSubscriberData;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_DeleteSubscriberDataRes(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Delete Subscriber Data return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_DeleteSubscriberDataRes*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_DeleteSubscriberDataRes(data);
 *
 *  See Also:
 *      GSMMAP_SendDeleteSubscriberDataRes()
 *
 ****************************************************************************/
int
GSMMAP_DecodeDeleteSubscriberDataRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(DeleteSubscriberDataRes_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_DeleteSubscriberDataRes(pe, 1, NULL, NULL,
                                              (char **)data) ==  NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_DeleteSubscriberDataRes(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** Reset OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Reset invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ResetArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeResetArg();
 *
 ****************************************************************************/
int
GSMMAP_SendResetArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                     void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ResetArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ResetArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ResetArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ResetArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_reset;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_reset;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ResetArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Reset invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ResetArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ResetArg(data);
 *
 *  See Also:
 *      GSMMAP_SendResetArg()
 *
 ****************************************************************************/
int
GSMMAP_DecodeResetArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ResetArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ResetArg(pe, 1, NULL, NULL, (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ResetArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** RestoreData OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Restore Data invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RestoreDataArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeRestoreDataArg();
 *
 ****************************************************************************/
int
GSMMAP_SendRestoreDataArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                           void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(RestoreDataArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_RestoreDataArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RestoreDataArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_RestoreDataArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_restoreData;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_restoreData;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_RestoreDataArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Restore Data invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RestoreDataArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_RestoreDataArg(data);
 *
 *  See Also:
 *      GSMMAP_SendRestoreDataArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeRestoreDataArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(RestoreDataArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_RestoreDataArg(pe, 1, NULL, NULL, (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RestoreDataArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Restore Data return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RestoreDataRes*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeRestoreDataRes();
 *
 ****************************************************************************/
int
GSMMAP_SendRestoreDataRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                           void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(RestoreDataRes_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_RestoreDataRes(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RestoreDataRes(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_RestoreDataRes(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_restoreData;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_RestoreDataRes(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Restore Data return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RestoreDataRes*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_RestoreDataRes(data);
 *
 *  See Also:
 *      GSMMAP_SendRestoreDataRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeRestoreDataRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(RestoreDataRes_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_RestoreDataRes(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RestoreDataRes(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** ActivateTraceMode OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Activate Trace Mode invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ActivateTraceModeArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeActivateTraceModeArg();
 *
 ****************************************************************************/
int
GSMMAP_SendActivateTraceModeArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                 TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ActivateTraceModeArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ActivateTraceModeArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ActivateTraceModeArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ActivateTraceModeArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_activateTraceMode;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_activateTraceMode;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ActivateTraceModeArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Activate Trace Mode invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ActivateTraceModeArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ActivateTraceModeArg(data);
 *
 *  See Also:
 *      GSMMAP_SendActivateTraceModeArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeActivateTraceModeArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                   void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ActivateTraceModeArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ActivateTraceModeArg(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ActivateTraceModeArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** DeactivateTraceMode OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Deactivate Trace Mode invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_DeactivateTraceModeArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeDeactivateTraceModeArg();
 *
 ****************************************************************************/
int
GSMMAP_SendDeactivateTraceModeArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                   TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(DeactivateTraceModeArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_DeactivateTraceModeArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_DeactivateTraceModeArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_DeactivateTraceModeArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_deactivateTraceMode;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_deactivateTraceMode;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_DeactivateTraceModeArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Decativate Trace Mode invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_DeactivateTraceModeArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_DeactivateTraceModeArg(data);
 *
 *  See Also:
 *      GSMMAP_SendDeactivateTraceModeArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeDeactivateTraceModeArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                     void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(DeactivateTraceModeArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_DeactivateTraceModeArg(pe, 1, NULL, NULL,
                                             (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_DeactivateTraceModeArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** TraceSubscriberActivity OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Trace Subscriber Activity invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_TraceSubscriberActivityArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeTraceSubscriberActivityArg();
 *
 ****************************************************************************/
int
GSMMAP_SendTraceSubscriberActivityArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(TraceSubscriberActivityArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_TraceSubscriberActivityArg(&pe, 1, 0, NULL, data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_TraceSubscriberActivityArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_TraceSubscriberActivityArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_traceSubscriberActivity;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_traceSubscriberActivity;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_TraceSubscriberActivityArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Trace Subscriber Activity invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_TraceSubscriberActivityArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_TraceSubscriberActivityArg(data);
 *
 *  See Also:
 *      GSMMAP_SendTraceSubscriberActivityArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeTraceSubscriberActivityArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(TraceSubscriberActivityArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_TraceSubscriberActivityArg(pe, 1, NULL, NULL,
                                                 (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_TraceSubscriberActivityArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** NoteInternalHandover OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Note Internal HO invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_NoteInternalHO__Arg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeNoteInternalHO_Arg();
 *
 ****************************************************************************/
int
GSMMAP_SendNoteInternalHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr,
                               TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(NoteInternalHO_Arg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_NoteInternalHO__Arg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_NoteInternalHO__Arg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_NoteInternalHO__Arg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_noteInternalHandover;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_noteInternalHandover;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_NoteInternalHO__Arg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Note Internal HO invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_NoteInternalHO__Arg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_NoteInternalHO__Arg(data);
 *
 *  See Also:
 *      GSMMAP_SendNoteInternalHO_Arg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeNoteInternalHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                 void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(NoteInternalHO_Arg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_NoteInternalHO__Arg(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_NoteInternalHO__Arg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** SendIMSI OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Send IMSI invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_Msisdn*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeSendIMSIArg();
 *
 ****************************************************************************/
int
GSMMAP_SendSendIMSIArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                        void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(Msisdn_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_Msisdn(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_Msisdn(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_Msisdn(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_sendIMSI;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_sendIMSI;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_Msisdn(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Send IMSI invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_Msisdn*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_Msisdn(data);
 *
 *  See Also:
 *      GSMMAP_SendSendIMSIArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeSendIMSIArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(Msisdn_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_Msisdn(pe, 1, NULL, NULL, (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_Msisdn(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Send IMSI return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_Imsi*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeSendIMSIRes():
 *
 ****************************************************************************/
int
GSMMAP_SendSendIMSIRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                        void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(Imsi_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_Imsi(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_Imsi(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_Imsi(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_sendIMSI;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_Imsi(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Send IMSI return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_Imsi*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_Imsi(data);
 *
 *  See Also:
 *      GSMMAP_SendSendIMSIRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeSendIMSIRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(Imsi_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_Imsi(pe, 1, NULL, NULL, (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_Imsi(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** SendRoutingInfo OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Send Routing Info invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendRoutingInfoArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeSendRoutingInfoArg();
 *
 ****************************************************************************/
int
GSMMAP_SendSendRoutingInfoArg( ITS_HANDLE handle, ITS_HDR *hdr,
                               TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(SendRoutingInfoArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_SendRoutingInfoArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendRoutingInfoArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_SendRoutingInfoArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_sendRoutingInfo;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_sendRoutingInfo;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_SendRoutingInfoArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Send Routing Info invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendRoutingInfoArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_SendRoutingInfoArg(data);
 *
 *  See Also:
 *      GSMMAP_SendSendRoutingInfoArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeSendRoutingInfoArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                 void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(SendRoutingInfoArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_SendRoutingInfoArg(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendRoutingInfoArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Send Routing Info return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendRoutingInfoRes*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeSendRoutingInfoRes();
 *
 ****************************************************************************/
int
GSMMAP_SendSendRoutingInfoRes( ITS_HANDLE handle, ITS_HDR *hdr,
                               TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(SendRoutingInfoRes_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_SendRoutingInfoRes(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendRoutingInfoRes(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_SendRoutingInfoRes(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_sendRoutingInfo;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_SendRoutingInfoRes(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Send Routing Info return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_SendRoutingInfoRes*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_SendRoutingInfoRes(data);
 *
 *  See Also:
 *      GSMMAP_SendSendRoutingInfoRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeSendRoutingInfoRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                 void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(SendRoutingInfoRes_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_SendRoutingInfoRes(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_SendRoutingInfoRes(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** ProvideRoamingNumber OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Provide Roaming Number invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ProvideRoamingNumberArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeProvideRoamingNumberArg();
 *
 ****************************************************************************/
int
GSMMAP_SendProvideRoamingNumberArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ProvideRoamingNumberArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ProvideRoamingNumberArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ProvideRoamingNumberArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ProvideRoamingNumberArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_provideRoamingNumber;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_provideRoamingNumber;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ProvideRoamingNumberArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Provide Roaming Number invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ProvideRoamingNumberArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ProvideRoamingNumberArg(data);
 *
 *  See Also:
 *      GSMMAP_SendProvideRoamingNumberArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeProvideRoamingNumberArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ProvideRoamingNumberArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ProvideRoamingNumberArg(pe, 1, NULL, NULL,
                                              (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ProvideRoamingNumberArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Provide Roaming Number return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RoamingNumber*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeProvideRoamingNumberRes();
 *
 ****************************************************************************/
int
GSMMAP_SendProvideRoamingNumberRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(RoamingNumber_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_RoamingNumber(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RoamingNumber(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_RoamingNumber(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_provideRoamingNumber;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_RoamingNumber(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Provide Roaming Number return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RoamingNumber*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_RoamingNumber(data);
 *
 *  See Also:
 *      GSMMAP_SendProvideRoamingNumberRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeProvideRoamingNumberRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(RoamingNumber_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_RoamingNumber(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RoamingNumber(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** RegisterSS OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Register SS invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RegisterSS__Arg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeRegisterSSArg();
 *
 ****************************************************************************/
int
GSMMAP_SendRegisterSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                          void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(RegisterSS_Arg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_RegisterSS__Arg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RegisterSS__Arg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_RegisterSS__Arg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_registerSS;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_registerSS;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_RegisterSS__Arg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Register SS invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RegisterSS__Arg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_RegisterSS__Arg(data);
 *
 *  See Also:
 *      GSMMAP_SendRegisterSSArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeRegisterSSArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(RegisterSS_Arg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_RegisterSS__Arg(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RegisterSS__Arg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Register SS return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RegisterSSss__Info*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeRegisterSSRes();
 *
 ****************************************************************************/
int
GSMMAP_SendRegisterSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                          void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(RegisterSSss_Info_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_RegisterSSss__Info(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RegisterSSss__Info(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_RegisterSSss__Info(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_registerSS;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_RegisterSSss__Info(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Register SS return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RegisterSSss__Info*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_RegisterSSss__Info(data);
 *
 *  See Also:
 *      GSMMAP_SendRegisterSSRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeRegisterSSRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(RegisterSSss_Info_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_RegisterSSss__Info(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RegisterSSss__Info(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** EraseSS OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Erase SS invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_EraseSSss__ForBS*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeEraseSSArg();
 *
 ****************************************************************************/
int
GSMMAP_SendEraseSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                       void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(EraseSSss_ForBS_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_EraseSSss__ForBS(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_EraseSSss__ForBS(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_EraseSSss__ForBS(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_eraseSS;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_eraseSS;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_EraseSSss__ForBS(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Erase SS invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_EraseSSss__ForBS*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_EraseSSss__ForBS(data);
 *
 *  See Also:
 *      GSMMAP_SendEraseSSArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeEraseSSArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(EraseSSss_ForBS_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_EraseSSss__ForBS(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_EraseSSss__ForBS(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Erase SS return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_EraseSSss__Info*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeEraseSSRes();
 *
 ****************************************************************************/
int
GSMMAP_SendEraseSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                       void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(EraseSSss_Info_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_EraseSSss__Info(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_EraseSSss__Info(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_EraseSSss__Info(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_eraseSS;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_EraseSSss__Info(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Erase SS return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_EraseSSss__Info*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_EraseSSss__Info(data);
 *
 *  See Also:
 *      GSMMAP_SendEraseSSRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeEraseSSRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(EraseSSss_Info_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_EraseSSss__Info(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_EraseSSss__Info(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** ActivateSS OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Activate SS invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ActivateSSss__ForBS*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeActivateSSArg();
 *
 ****************************************************************************/
int
GSMMAP_SendActivateSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                          void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ActivateSSss_ForBS_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ActivateSSss__ForBS(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ActivateSSss__ForBS(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ActivateSSss__ForBS(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_activateSS;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_activateSS;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ActivateSSss__ForBS(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Activate SS invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ActivateSSss__ForBS*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ActivateSSss__ForBS(data);
 *
 *  See Also:
 *      GSMMAP_SendActivateSSArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeActivateSSArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ActivateSSss_ForBS_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ActivateSSss__ForBS(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ActivateSSss__ForBS(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Activate SS return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ActivateSSss__Info*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeActivateSSRes();
 *
 ****************************************************************************/
int
GSMMAP_SendActivateSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                          void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ActivateSSss_Info_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ActivateSSss__Info(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ActivateSSss__Info(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ActivateSSss__Info(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_activateSS;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ActivateSSss__Info(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Activate SS return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ActivateSSss__Info*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ActivateSSss__Info(data);
 *
 *  See Also:
 *      GSMMAP_SendActivateSSRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeActivateSSRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ActivateSSss_Info_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ActivateSSss__Info(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ActivateSSss__Info(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** DeactivateSS OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Deactivate SS invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_DeactivateSSss__ForBS*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeDeactivateSSArg();
 *
 ****************************************************************************/
int
GSMMAP_SendDeactivateSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                            void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(DeactivateSSss_ForBS_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_DeactivateSSss__ForBS(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_DeactivateSSss__ForBS(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_DeactivateSSss__ForBS(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_deactivateSS;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_deactivateSS;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_DeactivateSSss__ForBS(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Deactivate SS invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_DeactivateSSss__ForBS*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_DeactivateSSss__ForBS(data);
 *
 *  See Also:
 *      GSMMAP_SendDeactivateSSArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeDeactivateSSArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                              void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(DeactivateSSss_ForBS_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_DeactivateSSss__ForBS(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_DeactivateSSss__ForBS(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Deactivate SS return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_DeactivateSSss__Info*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeDeactivateSSRes();
 *
 ****************************************************************************/
int
GSMMAP_SendDeactivateSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                            void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(DeactivateSSss_Info_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_DeactivateSSss__Info(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_DeactivateSSss__Info(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_DeactivateSSss__Info(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_deactivateSS;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_DeactivateSSss__Info(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Deactivate SS return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_DeactivateSSss__Info*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_DeactivateSSss__Info(data);
 *
 *  See Also:
 *      GSMMAP_SendDeactivateSSRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeDeactivateSSRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                              void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(DeactivateSSss_Info_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_DeactivateSSss__Info(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_DeactivateSSss__Info(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** InterrogateSS OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Interrogate SS invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_InterrogateSSss__ForBS*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeInterrogateSSArg();
 *
 ****************************************************************************/
int
GSMMAP_SendInterrogateSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                             void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(InterrogateSSss_ForBS_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_InterrogateSSss__ForBS(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_InterrogateSSss__ForBS(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_InterrogateSSss__ForBS(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_interrogateSS;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_interrogateSS;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_InterrogateSSss__ForBS(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Interrogate SS invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_InterrogateSSss__ForBS*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_InterrogateSSss__ForBS(data);
 *
 *  See Also:
 *      GSMMAP_SendInterrogateSSArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeInterrogateSSArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                               void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(InterrogateSSss_ForBS_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_InterrogateSSss__ForBS(pe, 1, NULL, NULL,
                                             (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_InterrogateSSss__ForBS(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Interrogate SS return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_InterrogateSS__Res*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeInterrogateSSRes();
 *
 ****************************************************************************/
int
GSMMAP_SendInterrogateSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                             void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(InterrogateSS_Res_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_InterrogateSS__Res(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_InterrogateSS__Res(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_InterrogateSS__Res(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_interrogateSS;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_InterrogateSS__Res(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Interrogate SS return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_InterrogateSS__Res*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_InterrogateSS__Res(data);
 *
 *  See Also:
 *      GSMMAP_SendInterrogateSSRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeInterrogateSSRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                               void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(InterrogateSS_Res_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_InterrogateSS__Res(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_InterrogateSS__Res(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** ProcessUnstructuredSS-Data OERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Process Unstructured SS Data invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ProcessUnstructuredSSArgSs__UserData*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeProcessUnstructuredSS_DataArg();
 *
 ****************************************************************************/
int
GSMMAP_SendProcessUnstructuredSS_DataArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                          TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ProcessUnstructuredSSArgSs_UserData_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ProcessUnstructuredSSArgSs__UserData(&pe, 1, 0, NULL,
                                                           data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ProcessUnstructuredSSArgSs__UserData(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ProcessUnstructuredSSArgSs__UserData(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_processUnstructuredSS_Data;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_processUnstructuredSS_Data;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ProcessUnstructuredSSArgSs__UserData(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Process Unstructured SS Data invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ProcessUnstructuredSSArgSs__UserData*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ProcessUnstructuredSSArgSs__UserData(data);
 *
 *  See Also:
 *      GSMMAP_SendProcessUnstructuredSS_DataArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeProcessUnstructuredSS_DataArg( ITS_HANDLE handle,
                                            TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ProcessUnstructuredSSArgSs_UserData_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ProcessUnstructuredSSArgSs__UserData(pe, 1, NULL, NULL,
                                                       (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ProcessUnstructuredSSArgSs__UserData(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Process Unstructured SS Data return result
 *      component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ProcessUnstructuredSSResSs__UserData*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeProcessUnstructuredSS_DataRes();
 *
 ****************************************************************************/
int
GSMMAP_SendProcessUnstructuredSS_DataRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                          TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ProcessUnstructuredSSResSs_UserData_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ProcessUnstructuredSSResSs__UserData(&pe, 1, 0, NULL,
                                                           data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ProcessUnstructuredSSResSs__UserData(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ProcessUnstructuredSSResSs__UserData(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_processUnstructuredSS_Data;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ProcessUnstructuredSSResSs__UserData(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Process Unstructured SS Data return result parameter
 *      sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ProcessUnstructuredSSResSs__UserData*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ProcessUnstructuredSSResSs__UserData(data);
 *
 *  See Also:
 *      GSMMAP_SendProcessUnstructuredSS_DataRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeProcessUnstructuredSS_DataRes( ITS_HANDLE handle,
                                            TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ProcessUnstructuredSSResSs_UserData_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ProcessUnstructuredSSResSs__UserData(pe, 1, NULL, NULL,
                                                        (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ProcessUnstructuredSSResSs__UserData(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** ProcessUnstructuredSS-Request OERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Process Unstructured SS Request invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ProcessUnstructuredSSReqUssd__Arg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeProcessUnstructuredSS_RequestArg()
 *
 ****************************************************************************/
int
GSMMAP_SendProcessUnstructuredSS_RequestArg( ITS_HANDLE handle,
                                             ITS_HDR *hdr, TCAP_CPT *cpt,
                                             void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ProcessUnstructuredSSReqUssd_Arg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ProcessUnstructuredSSReqUssd__Arg(&pe, 1, 0, NULL,
                                                        data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ProcessUnstructuredSSReqUssd__Arg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ProcessUnstructuredSSReqUssd__Arg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_processUnstructuredSS_Request;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_processUnstructuredSS_Request;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ProcessUnstructuredSSReqUssd__Arg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Process Unstructured SS Request invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ProcessUnstructuredSSReqUssd__Arg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ProcessUnstructuredSSReqUssd__Arg(data);
 *
 *  See Also:
 *      GSMMAP_SendProcessUnstructuredSS_RequestArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeProcessUnstructuredSS_RequestArg( ITS_HANDLE handle,
                                               TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ProcessUnstructuredSSReqUssd_Arg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ProcessUnstructuredSSReqUssd__Arg(pe, 1, NULL, NULL,
                                                       (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ProcessUnstructuredSSReqUssd__Arg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Process Unstructured SS Request return result
 *      component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ProcessUnstructuredSSReqUssd__Res*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeProcessUnstructuredSS_RequestRes();
 *
 ****************************************************************************/
int
GSMMAP_SendProcessUnstructuredSS_RequestRes( ITS_HANDLE handle,
                                             ITS_HDR *hdr, TCAP_CPT *cpt,
                                             void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ProcessUnstructuredSSReqUssd_Res_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ProcessUnstructuredSSReqUssd__Res(&pe, 1, 0, NULL,
                                                        data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ProcessUnstructuredSSReqUssd__Res(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ProcessUnstructuredSSReqUssd__Res(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_processUnstructuredSS_Request;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ProcessUnstructuredSSReqUssd__Res(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Process Unstructured SS Request return result parameter
 *      sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ProcessUnstructuredSSReqUssd__Res*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ProcessUnstructuredSSReqUssd__Res(data);
 *
 *  See Also:
 *      GSMMAP_SendProcessUnstructuredSS_RequestRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeProcessUnstructuredSS_RequestRes( ITS_HANDLE handle,
                                               TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ProcessUnstructuredSSReqUssd_Res_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ProcessUnstructuredSSReqUssd__Res(pe, 1, NULL, NULL,
                                                        (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ProcessUnstructuredSSReqUssd__Res(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*** UnstructuredSS-Request OERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Unstructured SS Request invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_UnstructuredSSReqUssd__Arg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeUnstructuredSS_RequestArg();
 *
 ****************************************************************************/
int
GSMMAP_SendUnstructuredSS_RequestArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                          TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(UnstructuredSSReqUssd_Arg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_UnstructuredSSReqUssd__Arg(&pe, 1, 0, NULL, data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_UnstructuredSSReqUssd__Arg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_UnstructuredSSReqUssd__Arg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_unstructuredSS_Request;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_unstructuredSS_Request;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_UnstructuredSSReqUssd__Arg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Unstructured SS Request invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_UnstructuredSSReqUssd__Arg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_UnstructuredSSReqUssd__Arg(data);
 *
 *  See Also:
 *      GSMMAP_SendUnstructuredSS_RequestArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeUnstructuredSS_RequestArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                            void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(UnstructuredSSReqUssd_Arg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_UnstructuredSSReqUssd__Arg(pe, 1, NULL, NULL,
                                                 (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_UnstructuredSSReqUssd__Arg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Unstructured SS Request return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_UnstructuredSSReqUssd__Res*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeUnstructuredSS_RequestRes();
 *
 ****************************************************************************/
int
GSMMAP_SendUnstructuredSS_RequestRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                          TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(UnstructuredSSReqUssd_Res_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_UnstructuredSSReqUssd__Res(&pe, 1, 0, NULL, data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_UnstructuredSSReqUssd__Res(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_UnstructuredSSReqUssd__Res(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_unstructuredSS_Request;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_UnstructuredSSReqUssd__Res(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Unstructured SS Request return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_UnstructuredSSReqUssd__Res*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_UnstructuredSSReqUssd__Res(data);
 *
 *  See Also:
 *      GSMMAP_SendUnstructuredSS_RequestRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeUnstructuredSS_RequestRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                            void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(UnstructuredSSReqUssd_Res_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_UnstructuredSSReqUssd__Res(pe, 1, NULL, NULL,
                                                 (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_UnstructuredSSReqUssd__Res(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** UnstructuredSS-Notify OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Unstructured SS Notify invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_UnstructuredSSNotifyUssd__Arg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeUnstructuredSS_NotifyArg();
 *
 ****************************************************************************/
int
GSMMAP_SendUnstructuredSS_NotifyArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                     TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(UnstructuredSSNotifyUssd_Arg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_UnstructuredSSNotifyUssd__Arg(&pe, 1, 0, NULL, data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_UnstructuredSSNotifyUssd__Arg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_UnstructuredSSNotifyUssd__Arg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_unstructuredSS_Notify;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_unstructuredSS_Notify;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_UnstructuredSSNotifyUssd__Arg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Unstructured SS Notify invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_UnstructuredSSNotifyUssd__Arg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_UnstructuredSSNotifyUssd__Arg(data);
 *
 *  See Also:
 *      GSMMAP_SendUnstructuredSS_NotifyArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeUnstructuredSS_NotifyArg( ITS_HANDLE handle,
                                       TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(UnstructuredSSNotifyUssd_Arg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_UnstructuredSSNotifyUssd__Arg(pe, 1, NULL, NULL,
                                                    (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_UnstructuredSSNotifyUssd__Arg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/***     RegisterPassword OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Register Password invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RegisterPasswordArgSs__Code*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeRegisterPasswordArg();
 *
 ****************************************************************************/
int
GSMMAP_SendRegisterPasswordArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(RegisterPasswordArgSs_Code_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_RegisterPasswordArgSs__Code(&pe, 1, 0, NULL, data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RegisterPasswordArgSs__Code(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_RegisterPasswordArgSs__Code(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_registerPassword;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_registerPassword;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_RegisterPasswordArgSs__Code(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Register Password invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RegisterPasswordArgSs__Code*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_RegisterPasswordArgSs__Code(data);
 *
 *  See Also:
 *      GSMMAP_SendRegisterPasswordArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeRegisterPasswordArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                  void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(RegisterPasswordArgSs_Code_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_RegisterPasswordArgSs__Code(pe, 1, NULL, NULL,
                                                  (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RegisterPasswordArgSs__Code(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Register Password return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RegisterPasswordResNewPassword*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeRegisterPasswordRes();
 *
 ****************************************************************************/
int
GSMMAP_SendRegisterPasswordRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(RegisterPasswordResNewPassword_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_RegisterPasswordResNewPassword(&pe, 1, 0, NULL, data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RegisterPasswordResNewPassword(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_RegisterPasswordResNewPassword(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_registerPassword;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_RegisterPasswordResNewPassword(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Register Password return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RegisterPasswordResNewPassword*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_RegisterPasswordResNewPassword(data);
 *
 *  See Also:
 *      GSMMAP_SendRegisterPasswordRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeRegisterPasswordRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                  void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(RegisterPasswordResNewPassword_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_RegisterPasswordResNewPassword(pe, 1, NULL, NULL,
                                                     (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RegisterPasswordResNewPassword(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** GetPassword OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Get Password invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_GetPasswordArgGuidanceInfo*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeGetPasswordArg();
 *
 ****************************************************************************/
int
GSMMAP_SendGetPasswordArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                           void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(GetPasswordArgGuidanceInfo_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_GetPasswordArgGuidanceInfo(&pe, 1, 0, NULL, data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_GetPasswordArgGuidanceInfo(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_GetPasswordArgGuidanceInfo(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_getPassword;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_getPassword;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_GetPasswordArgGuidanceInfo(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Get Password invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_GetPasswordArgGuidanceInfo*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_GetPasswordArgGuidanceInfo(data);
 *
 *  See Also:
 *      GSMMAP_SendGetPasswordArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeGetPasswordArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                             void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(GetPasswordArgGuidanceInfo_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_GetPasswordArgGuidanceInfo(pe, 1, NULL, NULL,
                                                 (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_GetPasswordArgGuidanceInfo(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Get Password return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_GetPasswordResCurrentPassword*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeGetPasswordRes();
 *
 ****************************************************************************/
int
GSMMAP_SendGetPasswordRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                           void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(GetPasswordResCurrentPassword_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_GetPasswordResCurrentPassword(&pe, 1, 0, NULL, data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_GetPasswordResCurrentPassword(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_GetPasswordResCurrentPassword(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_getPassword;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_GetPasswordResCurrentPassword(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Get Password return result parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_GetPasswordResCurrentPassword*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_GetPasswordResCurrentPassword(data);
 *
 *  See Also:
 *      GSMMAP_SendGetPasswordRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeGetPasswordRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                             void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(GetPasswordResCurrentPassword_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_GetPasswordResCurrentPassword(pe, 1, NULL, NULL,
                                                    (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_GetPasswordResCurrentPassword(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** BeginSubscriberActivity OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Begin Subscriber Activity invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_BeginSubscriberActivityArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeBeginSubscriberActivityArg();
 *
 ****************************************************************************/
int
GSMMAP_SendBeginSubscriberActivityArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(BeginSubscriberActivityArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_BeginSubscriberActivityArg(&pe, 1, 0, NULL, data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_BeginSubscriberActivityArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_BeginSubscriberActivityArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_beginSubscriberActivity;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_beginSubscriberActivity;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_BeginSubscriberActivityArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Begin Subscriber Activity invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_BeginSubscriberActivityArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_BeginSubscriberActivityArg(data);
 *
 *  See Also:
 *      GSMMAP_SendBeginSubscriberActivityArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeBeginSubscriberActivityArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(BeginSubscriberActivityArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_BeginSubscriberActivityArg(pe, 1, NULL, NULL,
                                                 (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_BeginSubscriberActivityArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** SendRoutingInfoForSM OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Send Routing Info For SM invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RoutingInfoForSM__Arg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeSendRoutingInfoForSMArg();
 *
 ****************************************************************************/
int
GSMMAP_SendSendRoutingInfoForSMArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(RoutingInfoForSM_Arg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_RoutingInfoForSM__Arg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RoutingInfoForSM__Arg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_RoutingInfoForSM__Arg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_sendRoutingInfoForSM;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_sendRoutingInfoForSM;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_RoutingInfoForSM__Arg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Send Routing Info For SM invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RoutingInfoForSM__Arg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_RoutingInfoForSM__Arg(data);
 *
 *  See Also:
 *      GSMMAP_SendSendRoutingInfoForSMArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeSendRoutingInfoForSMArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(RoutingInfoForSM_Arg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_RoutingInfoForSM__Arg(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RoutingInfoForSM__Arg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Send Routing Info For SM return result component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RoutingInfoForSM__Res*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeSendRoutingInfoForSMRes();
 *
 ****************************************************************************/
int
GSMMAP_SendSendRoutingInfoForSMRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(RoutingInfoForSM_Res_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_RoutingInfoForSM__Res(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RoutingInfoForSM__Res(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_RoutingInfoForSM__Res(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_sendRoutingInfoForSM;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_RoutingInfoForSM__Res(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Send Routing Info For SM return result parameter
 *      sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_RoutingInfoForSM__Res*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_RoutingInfoForSM__Res(data);
 *
 *  See Also:
 *      GSMMAP_SendSendRoutingInfoForSMRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeSendRoutingInfoForSMRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(RoutingInfoForSM_Res_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_RoutingInfoForSM__Res(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_RoutingInfoForSM__Res(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** ForwardSM OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Forward SM invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ForwardSM__Arg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeForwardSMArg();
 *
 ****************************************************************************/
int
GSMMAP_SendForwardSMArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                         void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ForwardSM_Arg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ForwardSM__Arg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ForwardSM__Arg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ForwardSM__Arg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_forwardSM;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_forwardSM;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ForwardSM__Arg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Forward SM invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ForwardSM__Arg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ForwardSM__Arg(data);
 *
 *  See Also:
 *      GSMMAP_SendForwardSMArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeForwardSMArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ForwardSM_Arg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ForwardSM__Arg(pe, 1, NULL, NULL, (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ForwardSM__Arg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** ReportSM-DeliveryStatus OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Report SM Delivery Status invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ReportSM__DeliveryStatusArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeReportSM_DeliveryStatusArg();
 *
 ****************************************************************************/
int
GSMMAP_SendReportSM_DeliveryStatusArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ReportSM_DeliveryStatusArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ReportSM__DeliveryStatusArg(&pe, 1, 0, NULL, data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ReportSM__DeliveryStatusArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ReportSM__DeliveryStatusArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_reportSM_DeliveryStatus;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_reportSM_DeliveryStatus;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ReportSM__DeliveryStatusArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Report SM Delivery Status invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ReportSM__DeliveryStatusArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ReportSM__DeliveryStatusArg(data);
 *
 *  See Also:
 *      GSMMAP_SendReportSM_DeliveryStatusArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeReportSM_DeliveryStatusArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ReportSM_DeliveryStatusArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ReportSM__DeliveryStatusArg(pe, 1, NULL, NULL,
                                                  (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ReportSM__DeliveryStatusArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Report SM Delivery Status return result
 *      component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ReportSM__DeliveryStatusResStoredMSISDN*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeReportSM_DeliveryStatusRes();
 *
 ****************************************************************************/
int
GSMMAP_SendReportSM_DeliveryStatusRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ReportSM_DeliveryStatusResStoredMSISDN_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ReportSM__DeliveryStatusResStoredMSISDN(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ReportSM__DeliveryStatusResStoredMSISDN(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ReportSM__DeliveryStatusResStoredMSISDN(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = GSMMAP_OP_reportSM_DeliveryStatus;
#endif
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ReportSM__DeliveryStatusResStoredMSISDN(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Report SM Delivery Status return result parameter
 *      sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ReportSM__DeliveryStatusResStoredMSISDN*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ReportSM__DeliveryStatusResStoredMSISDN(data);
 *
 *  See Also:
 *      GSMMAP_SendReportSM_DeliveryStatusRes();
 *
 ****************************************************************************/
int
GSMMAP_DecodeReportSM_DeliveryStatusRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.result.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ReportSM_DeliveryStatusResStoredMSISDN_PDU,
		(char *)cpt->u.result.param.data, cpt->u.result.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ReportSM__DeliveryStatusResStoredMSISDN(pe, 1, NULL, NULL,
                                                              (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ReportSM__DeliveryStatusResStoredMSISDN(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** NoteSubscriberPresent OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Note Subscriber Present invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_NoteSubscriberPresentImsi*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeNoteSubscriberPresentArg();
 *
 ****************************************************************************/
int
GSMMAP_SendNoteSubscriberPresentArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                     TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(NoteSubscriberPresentImsi_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_NoteSubscriberPresentImsi(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_NoteSubscriberPresentImsi(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_NoteSubscriberPresentImsi(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_noteSubscriberPresent;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_noteSubscriberPresent;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_NoteSubscriberPresentImsi(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Note Subscriber Present invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_NoteSubscriberPresentImsi*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_NoteSubscriberPresentImsi(data);
 *
 *  See Also:
 *      GSMMAP_SendNoteSubscriberPresentArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeNoteSubscriberPresentArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                       void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(NoteSubscriberPresentImsi_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_NoteSubscriberPresentImsi(pe, 1, NULL, NULL,
                                                (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_NoteSubscriberPresentImsi(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}

/*** AlertServiceCentreWithoutResult OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Alert Service Centre Without Result invoke
 *      component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_AlertServiceCentreArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeAlertServiceCentreWOResult();
 *
 ****************************************************************************/
int
GSMMAP_SendAlertServiceCentreWOResult( ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(AlertServiceCentreArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_AlertServiceCentreArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_AlertServiceCentreArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_AlertServiceCentreArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_alertServiceCentreWithoutResult;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_alertServiceCentreWithoutResult;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_AlertServiceCentreArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To deocde an Alert Service Centre Without Result invoke parameter
 *      sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_AlertServiceCentreArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_AlertServiceCentreArg(data);
 *
 *  See Also:
 *      GSMMAP_SendAlertServiceCentreWOResult();
 *
 ****************************************************************************/
int
GSMMAP_DecodeAlertServiceCentreWOResult( ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(AlertServiceCentreArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_AlertServiceCentreArg(pe, 1, NULL, NULL,
                                            (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_AlertServiceCentreArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** InformServiceCentre OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Inform Service Centre invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_InformServiceCentreArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeInformServiceCentreArg();
 *
 ****************************************************************************/
int
GSMMAP_SendInformServiceCentreArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                   TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(InformServiceCentreArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_InformServiceCentreArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_InformServiceCentreArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_InformServiceCentreArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_informServiceCentre;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_informServiceCentre;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_InformServiceCentreArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Inform Service Centre invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_InformServiceCentreArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_InformServiceCentreArg(data);
 *
 *  See Also:
 *      GSMMAP_SendInformServiceCentreArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeInformServiceCentreArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                     void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(InformServiceCentreArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_InformServiceCentreArg(pe, 1, NULL, NULL,
                                             (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_InformServiceCentreArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** AlertServiceCentre OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send an Alert Service Centre invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_AlertServiceCentreArg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeAlertServiceCentreArg();
 *
 ****************************************************************************/
int
GSMMAP_SendAlertServiceCentreArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(AlertServiceCentreArg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_AlertServiceCentreArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_AlertServiceCentreArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_AlertServiceCentreArg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_alertServiceCentre;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_alertServiceCentre;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_AlertServiceCentreArg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode an Alert Service Centre invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_AlertServiceCentreArg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_AlertServiceCentreArg(data);
 *
 *  See Also:
 *      GSMMAP_SendAlertServiceCentreArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeAlertServiceCentreArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(AlertServiceCentreArg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_AlertServiceCentreArg(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_AlertServiceCentreArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*** ReadyForSM OPERATION ***/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode and send a Ready For SM invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the parameter set that will be encoded & sent.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ReadyForSM__Arg*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *  See Also:
 *      GSMMAP_DecodeReadyForSMArg();
 *
 ****************************************************************************/
int
GSMMAP_SendReadyForSMArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                          void *data )
{
    PE pe = {0};
    int len, ret;
    char *enc;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert((handle != NULL && hdr != NULL && data == NULL));
#else
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(ReadyForSM_Arg_PDU, &enc, &len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    if (encode_GSMMAP_ReadyForSM__Arg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ReadyForSM__Arg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_GSMMAP_ReadyForSM__Arg(data);
        return ITS_BADTCAPMESSAGE;
    }
#endif /* OSS_ENCODE */

#if !defined(ANSI)
    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = GSMMAP_OP_readyForSM;
#else
    cpt->u.invoke.operation.len = 4;
    cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
    cpt->u.invoke.operation.data[1] = 2;
    cpt->u.invoke.operation.data[2] = TCPPN_OF_IS41;
    cpt->u.invoke.operation.data[3] = GSMMAP_OP_readyForSM;
#endif

    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);
#ifndef OSS_ENCODE
    free_GSMMAP_ReadyForSM__Arg(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a Ready For SM invoke parameter sequence.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_ReadyForSM__Arg*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a
 *      TCAP_ReceiveComponent().  The user should free the data when finished
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_GSMMAP_ReadyForSM__Arg(data);
 *
 *  See Also:
 *      GSMMAP_SendReadyForSMArg();
 *
 ****************************************************************************/
int
GSMMAP_DecodeReadyForSMArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data )
{
    PE pe = {0};
    int ret = ITS_SUCCESS, err= 0;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (cpt->u.invoke.param.len == 0)
    {
        return ITS_BADTCAPMESSAGE;
    }
#ifdef OSS_DECODE
    ret = getDecodedPDU(ReadyForSM_Arg_PDU,
		(char *)cpt->u.invoke.param.data, cpt->u.invoke.param.len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_GSMMAP_ReadyForSM__Arg(pe, 1, NULL, NULL, (char **)data) ==
        NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_ReadyForSM__Arg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode the user info parameter, in the TCAP dialogue portion.
 *
 *  Input Parameters:
 *      data -  a pointer to the parameter set that will be encoded.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_MAP__UserInfo*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      buf - the address of a char buffer to encode the user info into.
 *
 *      len - the lenght of the encoded buffer.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The memory pointed to by *buf will need to be freed by the user.
 *
 *  See Also:
 *      GSMMAP_decodeUserInfo();
 *
 ****************************************************************************/
int
GSMMAP_EncodeUserInfo(void *data, int *len, char **buf)
{

    int ret = ITS_SUCCESS;
    PE pe = {0};


#ifdef DEBUG
#ifdef OSS_ENCODE
    assert(data == NULL && buf != NULL);
#else
    assert(data != NULL && buf != NULL);
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(MAP_UserInfo_PDU, buf, len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    ret = encode_GSMMAP_MAP__UserInfo(&pe, 1, 0, NULL, data);

    ret = pe2ssdu(pe, buf, len);

    if (ret != OK)
    {
        free_GSMMAP_MAP__UserInfo(data);
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_MAP__UserInfo(pe, 1, 0, NULL, data);
    }
#endif /* OSS_ENCODE */

#ifndef OSS_ENCODE
    free_GSMMAP_MAP__UserInfo(data);
    if (pe)
        pe_free(pe);
#endif /* !OSS_ENCODE */
    return ret;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode the user information parameter received in the dialogue
 *      of a TCAP message.
 *
 *  Input Parameters:
 *      usrInfo - a char buffer where the user Information is encoded.
 *      len -  the length of this buffer.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_MAP__UserInfo*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *
 *  See Also:
 *      GSMMAP_EncodeUserInfo();
 *
 ****************************************************************************/
int
GSMMAP_DecodeUserInfo(char *usrInfo, int len, void **data)
{

    int ret = ITS_SUCCESS, err= 0;
    PE pe = {0};

#ifdef DEBUG
    assert(usrInfo != NULL && len != 0 && data != NULL);
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_DECODE
    ret = getDecodedPDU(MAP_UserInfo_PDU, usrInfo, len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe(usrInfo, len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    ret = decode_GSMMAP_MAP__UserInfo(pe, 1, NULL, NULL, (char **)data);

    if (ret != OK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_MAP__UserInfo(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To encode the user info parameter, in the TCAP dialogue portion.
 *
 *  Input Parameters:
 *      data -  a pointer to the parameter set that will be encoded.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_MAP__DialoguePDU*.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      buf - the address of a char buffer to encode the user info into.
 *
 *      len - the lenght of the encoded buffer.
 *      pe - the encoded structure that will be use in the user information
 *           parameter of the TCAP dialogue portion.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The memory pointed to by *buf will need to be freed by the user
 *
 *  See Also:
 *      GSMMAP_DecodeDialoguePDU();
 *
 ****************************************************************************/
int
GSMMAP_EncodeDialoguePDU(PE *pe, void *data, int *len, char **buf)
{
    int ret = ITS_SUCCESS;

#ifdef DEBUG
#ifdef OSS_ENCODE
    assert(data == NULL && buf != NULL);
#else
    assert(pe != NULL && data != NULL && buf != NULL);
#endif /* OSS_ENCODE */
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_ENCODE
    ret = getEncodedPDU(MAP_DialoguePDU_PDU, buf, len);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    ret = encode_GSMMAP_MAP__DialoguePDU(pe, 1, 0, NULL, data);

    ret = pe2ssdu(*pe, buf, len);

    if (ret != OK)
    {
        free_GSMMAP_MAP__DialoguePDU(data);
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_MAP__DialoguePDU(*pe, 1, 0, NULL, data);
    }
#endif /* OSS_ENCODE */

#ifndef OSS_ENCODE
    free_GSMMAP_MAP__DialoguePDU(data);
#endif /* !OSS_ENCODE */

    return ret;

}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode the user information parameter received in the dialogue
 *      of a TCAP message.
 *
 *  Input Parameters:
 *      dlgPDU - a char buffer where the user Information is encoded.
 *      len -  the length of this buffer.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data -  the decoded parameter set.
 *              The actual type for this 'data' pointer is
 *                  struct type_GSMMAP_MAP__DialoguePDU*.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully encoded and sent
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *
 *
 *  See Also:
 *      GSMMAP_EncodeUserInfo();
 *
 ****************************************************************************/
int
GSMMAP_DecodeDialoguePDU(char *dlgPDU, int len, void **data)
{
    int ret = ITS_SUCCESS, err= 0;
    PE pe = {0};

#ifdef DEBUG
    assert(dlgPDU != NULL && len != 0 && data != NULL);
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_GSMMAP))
    {
        return (ITS_ENOLICENSE);
    }

#ifdef OSS_DECODE
    ret = getDecodedPDU(MAP_DialoguePDU_PDU, dlgPDU, len, data);
    if (ret)
        return ITS_BADTCAPMESSAGE;
#else
    pe = ssdu2pe(dlgPDU, len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    ret = decode_GSMMAP_MAP__DialoguePDU(pe, 1, NULL, NULL, (char **)data);

    if (ret != OK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (gsm_debug)
    {
        print_GSMMAP_MAP__DialoguePDU(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }
#endif /* OSS_DECODE */

    return ret;
}
