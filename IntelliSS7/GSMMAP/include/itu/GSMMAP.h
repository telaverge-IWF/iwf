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
 *     FILE: GSMMAP.h                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * NOTE:
 *  European Digital Cellular Telecommunications System (Phase 2)
 *      GSM 09.02 version 4.11.0, June 1995
 *        Draft pr ETS 300 599
 *
 *  ID: $Id: GSMMAP.h,v 9.1 2005/03/23 12:51:24 cvsadmin Exp $
 *
 * LOG: $Log: GSMMAP.h,v $
 * LOG: Revision 9.1  2005/03/23 12:51:24  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:23  cvsadmin
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
 * LOG: Revision 2.2  2000/03/27 15:25:05  mmiers
 * LOG:
 * LOG:
 * LOG: Add the SMS stuff.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:23  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:18:54  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1998/09/11 15:43:39  jpakrasi
 * LOG: Added Class of Operation definitions.
 * LOG:
 * LOG: Revision 1.1  1998/08/26 14:54:28  jpakrasi
 * LOG: First time compile on NT.
 * LOG:
 *
 ****************************************************************************/

#ifndef _GSM_MAP_H
#define _GSM_MAP_H

/*
 * Subsystem Numbers assigned by GSM for applications.
 * Ref: GSM 9.2, Sec. 4.1.2, Pg. 41.
 * The SSN for AC (ie, 10) is reserved, under further study.
 */
#define GSM_MAP_SSN        5
#define GSM_HLR_SSN        6
#define GSM_VLR_SSN        7
#define GSM_MSC_SSN        8
#define GSM_EIR_SSN        9
#define GSM_AC_SSN         10


/*
 * Operation Codes.
 * Ref: GSM 9.2, Sec 14.5, page 254 - 257.
 * This gives the Opcode for a GSMMAP msg.
 */
/* Location Registration operation codes */
#define GSMMAP_OP_updateLocation                2
#define GSMMAP_OP_cancelLocation                3
#define GSMMAP_OP_purgeMS                       67
#define GSMMAP_OP_sendIdentification            55

/* Handover operation codes */
#define GSMMAP_OP_performHandover               28
#define GSMMAP_OP_prepareHandover               68
#define GSMMAP_OP_sendEndSignal                 29
#define GSMMAP_OP_processAccessSignalling       33
#define GSMMAP_OP_forwardAccessSignalling       34
#define GSMMAP_OP_performSubsequentHandover     30
#define GSMMAP_OP_prepareSubsequentHandover     69

/* Authentication operation codes */
#define GSMMAP_OP_sendAuthenticationInfo        56

/* IMEI Management operation codes */
#define GSMMAP_OP_checkIMEI                     43

/* Subscriber Management operation codes */
#define GSMMAP_OP_sendParameters                9
#define GSMMAP_OP_insertSubscriberData          7
#define GSMMAP_OP_deleteSubscriberData          8

/* Fault Recovery operation codes */
#define GSMMAP_OP_reset                         37
#define GSMMAP_OP_forwardCheckSS_Indication     38
#define GSMMAP_OP_restoreData                   57

/* Operation and Maintenance operation codes */
#define GSMMAP_OP_activateTraceMode             50
#define GSMMAP_OP_deactivateTraceMode           51
#define GSMMAP_OP_traceSubscriberActivity       52
#define GSMMAP_OP_noteInternalHandover          35
#define GSMMAP_OP_sendIMSI                      58

/* Call Handling operation codes */
#define GSMMAP_OP_sendRoutingInfo               22
#define GSMMAP_OP_provideRoamingNumber          4

/* SuplementaryService Handling operation codes */
#define GSMMAP_OP_registerSS                    10
#define GSMMAP_OP_eraseSS                       11
#define GSMMAP_OP_activateSS                    12
#define GSMMAP_OP_deactivateSS                  13
#define GSMMAP_OP_interrogateSS                 14
#define GSMMAP_OP_processUnstructuredSS_Data    19
#define GSMMAP_OP_processUnstructuredSS_Request 59
#define GSMMAP_OP_unstructuredSS_Request        60
#define GSMMAP_OP_unstructuredSS_Notify         61
#define GSMMAP_OP_registerPassword              17
#define GSMMAP_OP_getPassword                   18
#define GSMMAP_OP_beginSubscriberActivity       54

/* Short Message Service operation codes */
#define GSMMAP_OP_sendRoutingInfoForSM          45
#define GSMMAP_OP_forwardSM                     46
#define GSMMAP_OP_reportSM_DeliveryStatus       47
#define GSMMAP_OP_noteSubscriberPresent         48
#define GSMMAP_OP_alertServiceCentreWithoutResult 49
#define GSMMAP_OP_informServiceCentre           63
#define GSMMAP_OP_alertServiceCentre            64
#define GSMMAP_OP_readyForSM                    66

/*
 * Error Code Definitions.
 * Ref: GSM 9.2, Sec. 14.5, pg. 258, 259.
 * These are error codes defined for GSMMAP, sent in Return Error component.
 */
/* Generic error codes */
#define GSMMAP_ERR_systemFailure                34
#define GSMMAP_ERR_dataMissing                  35
#define GSMMAP_ERR_unexpectedDataValue          36
#define GSMMAP_ERR_facilityNotSupported         21

/* Identification and Numbering error codes */
#define GSMMAP_ERR_unknownSubscriber            1
#define GSMMAP_ERR_numberChanged                44
#define GSMMAP_ERR_unknownBaseStation           2
#define GSMMAP_ERR_unknownMSC                   3
#define GSMMAP_ERR_unidentifiedSubscriber       5
#define GSMMAP_ERR_unknownEquipment             7

/* Subscription error codes */
#define GSMMAP_ERR_roamingNotAllowed            8
#define GSMMAP_ERR_illegalSubscriber            9
#define GSMMAP_ERR_illegalEquipment             12
#define GSMMAP_ERR_bearerServiceNotProvisioned  10
#define GSMMAP_ERR_teleserviceNotProvisioned    11

/* Handover error codes */
#define GSMMAP_ERR_invalidTargetBaseStation     23
#define GSMMAP_ERR_noRadioResourceAvailable     24
#define GSMMAP_ERR_noHandoverNumberAvailable    25
#define GSMMAP_ERR_subsequentHandoverFailure    26

/* Operation and Maintenance error codes */
#define GSMMAP_ERR_tracingBufferFull            40

/* Call Handling error codes */
#define GSMMAP_ERR_noRoamingNumberAvailable     39
#define GSMMAP_ERR_absentSubscriber             27
#define GSMMAP_ERR_callBarred                   13
#define GSMMAP_ERR_forwardingViolation          14
#define GSMMAP_ERR_cug_Reject                   15

/* Supplementary Service error codes */
#define GSMMAP_ERR_illegalSS_Operation          16
#define GSMMAP_ERR_ss_ErrorStatus               17
#define GSMMAP_ERR_ss_NotAvailable              18
#define GSMMAP_ERR_ss_SubscriptionViolation     19
#define GSMMAP_ERR_ss_Incompatibility           20
#define GSMMAP_ERR_unknownAlphabet              71
#define GSMMAP_ERR_ussd_Busy                    72
#define GSMMAP_ERR_pw_RegistrationFailure       37
#define GSMMAP_ERR_negativePW_Check             38
#define GSMMAP_ERR_numberOfPw_AttemptsViolation 43

/* Short Message Service error codes */
#define GSMMAP_ERR_subscriberBusyForMT_SMS      31
#define GSMMAP_ERR_sm_DeliveryFailure           32
#define GSMMAP_ERR_messageWaitingListFull       33


/*
 * Class of Operation.
 * Ref: GSM 9.2, Sec 14.6.1 - 14.6.5, page 260 - 277.
 * This gives the Class of Operation for a GSMMAP invoke msg.
 *      Class 1 - Both success and failure are reported.
 *      Class 2 - Only failure is reported.
 *      Class 3 - Only success is reported.
 *      Class 4 - Neither success or failure is reported.
 */
/* Location Registration class of operation */
#define GSMMAP_CO_updateLocation                1
#define GSMMAP_CO_cancelLocation                1
#define GSMMAP_CO_purgeMS                       3
#define GSMMAP_CO_sendIdentification            1

/* Handover class of operation */
#define GSMMAP_CO_performHandover               1
#define GSMMAP_CO_prepareHandover               1
#define GSMMAP_CO_sendEndSignal                 3
#define GSMMAP_CO_processAccessSignalling       4
#define GSMMAP_CO_forwardAccessSignalling       4
#define GSMMAP_CO_performSubsequentHandover     1
#define GSMMAP_CO_prepareSubsequentHandover     1

/* Authentication class of operation */
#define GSMMAP_CO_sendAuthenticationInfo        1

/* IMEI Management class of operation */
#define GSMMAP_CO_checkIMEI                     1

/* Subscriber Management class of operation */
#define GSMMAP_CO_sendParameters                1
#define GSMMAP_CO_insertSubscriberData          1
#define GSMMAP_CO_deleteSubscriberData          1

/* Fault Recovery class of operation */
#define GSMMAP_CO_reset                         4
#define GSMMAP_CO_forwardCheckSS_Indication     4
#define GSMMAP_CO_restoreData                   1

/* Operation and Maintenance class of operation */
#define GSMMAP_CO_activateTraceMode             1
#define GSMMAP_CO_deactivateTraceMode           1
#define GSMMAP_CO_traceSubscriberActivity       4
#define GSMMAP_CO_noteInternalHandover          4
#define GSMMAP_CO_sendIMSI                      1

/* Call Handling class of operation */
#define GSMMAP_CO_sendRoutingInfo               1
#define GSMMAP_CO_provideRoamingNumber          1

/* SuplementaryService Handling class of operation */
#define GSMMAP_CO_registerSS                    1
#define GSMMAP_CO_eraseSS                       1
#define GSMMAP_CO_activateSS                    1
#define GSMMAP_CO_deactivateSS                  1
#define GSMMAP_CO_interrogateSS                 1
#define GSMMAP_CO_processUnstructuredSS_Data    1
#define GSMMAP_CO_processUnstructuredSS_Request 1
#define GSMMAP_CO_unstructuredSS_Request        1
#define GSMMAP_CO_unstructuredSS_Notify         1
#define GSMMAP_CO_registerPassword              1
#define GSMMAP_CO_getPassword                   3
#define GSMMAP_CO_beginSubscriberActivity       4

/* Short Message Service class of operation */
#define GSMMAP_CO_sendRoutingInfoForSM          1
#define GSMMAP_CO_forwardSM                     1
#define GSMMAP_CO_reportSM_DeliveryStatus       1
#define GSMMAP_CO_noteSubscriberPresent         4
#define GSMMAP_CO_alertServiceCentreWithoutResult 4
#define GSMMAP_CO_informServiceCentre           1
#define GSMMAP_CO_alertServiceCentre            4
#define GSMMAP_CO_readyForSM                    1



/*
 * Parameters required for first demo (27 of 99).
 *  Authentication set list -- made up of other params below
 *  Bearer Service
 *  Call Barring Info
 *  Category
 *  CUG Info
 *  Forwarding Information
 *  HLR number
 *  IMSI
 *  LMSI
 *  MS ISDN
 *  ODB General Data
 *  ODB HPLMN Specific Data
 *  OMC Id
 *  Provider Error -- Error Codes
 *  Rand
 *  Regional Subscription Data
 *  Regional Subscription Response
 *  Roaming Restriction Due to Unsupported Feature
 *  Sres
 *  SS-Code
 *  SS-Data
 *  Subscriber Status
 *  Teleservice
 *  TMSI
 *  Trace reference
 *  Trace type
 *  User error -- Error codes
 */

/*
 * Application contexts.  Taken from 4.17.1.  Use these arrays
 * as arguments to oid_cpy
 */
#if !defined(TANDEM)

#include <asn-c/AsnC.h>

#else /* TANDEM */

#include <AsnCh>

#endif /* TANDEM */

/*
 * FYI: map-ac OBJECT IDENTIFIER ::= {gsm-NetworkId ac-Id}
 */
#define GSMMAP_OID_CPT_CCITT               0
#define GSMMAP_OID_CPT_IDEN_ORG            4
#define GSMMAP_OID_CPT_ETSI                0
#define GSMMAP_OID_CPT_MOBILE_DOMAIN       0
#define GSMMAP_OID_CPT_GSM_NETWORK         1
#define GSMMAP_OID_CPT_AC_ID               0

#define GSMMAP_OID_CPT_MAP_V1           1
#define GSMMAP_OID_CPT_MAP_V2           2

/*
 * 
 * networkLocUpContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac networkLocUp(1) version2(2)}
 * networkLocUpContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac networkLocUp(1) version1(1)}
 */
#define GSMMAP_OID_CPT_NETWORK_LOC_UP           1

extern OIDentifier GSMMAPNetworkLocUpV2;
extern OIDentifier GSMMAPNetworkLocUpV1;

/*
 *
 * locationCancellation-v2 OBJECT IDENTIFIER ::=
 *   {map-ac locationCancel(2) version2(2)}
 * locationCancellation-v1 OBJECT IDENTIFIER ::=
 *   {map-ac locationCancel(2) version1(1)}
 */
#define GSMMAP_OID_CPT_LOCATION_CANCEL          2

extern OIDentifier GSMMAPLocationCancelV2;
extern OIDentifier GSMMAPLocationCancelV1;

/*
 * roamingNumberEnquiryContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac roamingNbEnquiry(3) version2(2)}
 * roamingNumberEnquiryContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac roamingNbEnquiry(3) version1(1)}
 */
#define GSMMAP_OID_CPT_ROAMING_NB_INQ           3

extern OIDentifier GSMMAPRoamingNbEnquiryV2;
extern OIDentifier GSMMAPRoamingNbEnquiryV1;

/*
 * locationInfoRetrievalContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac locInfoRetrieval(5) version2(2)}
 * locationInfoRetrievalContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac locInfoRetrieval(5) version1(1)}
 */
#define GSMMAP_OID_CPT_LOCATION_INFO_RETRIEVAL  5

extern OIDentifier GSMMAPLocationInfoRetrievalV2;
extern OIDentifier GSMMAPLocationInfoRetrievalV1;

/*
 * resetContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac reset(10) version2(2)}
 * resetContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac reset(10) version1(1)}
 */
#define GSMMAP_OID_CPT_RESET                    10

extern OIDentifier GSMMAPResetContextV2;
extern OIDentifier GSMMAPResetContextV1;

/*
 * handoverControlContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac handoverControl(11) version2(2)}
 * handoverControlContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac handoverControl(11) version1(1)}
 */
#define GSMMAP_OID_CPT_HANDOVER_CONTROL         11

extern OIDentifier GSMMAPHandoverControlV2;
extern OIDentifier GSMMAPHandoverControlV1;

/*
 * equipmentMngtContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac equipmentMngt(13) version2(2)}
 * equipmentMngtContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac equipmentMngt(13) version1(1)}
 */
#define GSMMAP_OID_CPT_EQUIPMENT_MNGT           13

extern OIDentifier GSMMAPEquipmentMngtV2;
extern OIDentifier GSMMAPEquipmentMngtV1;

/*
 * infoRetrievalContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac infoRetrieval(14) version2(2)}
 * infoRetrievalContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac infoRetrieval(14) version1(1)}
 */
#define GSMMAP_OID_CPT_INFO_RETRIEVAL           14

extern OIDentifier GSMMAPInfoRetrievalV2;
extern OIDentifier GSMMAPInfoRetrievalV2;

/*
 * interVlrInfoRetrievalContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac interVlrInfoRetrieval(15) version2(2)}
 */
#define GSMMAP_OID_CPT_INTER_VLR_INFO_RETRIEVAL 15

extern OIDentifier GSMMAPInterVLRInfoRetrievalV2;

/*
 * subscriberDataMngtContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac subscriberDataMngt(16) version2(2)}
 * subscriberDataMngtContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac subscriberDataMngt(16) version1(1)}
 */
#define GSMMAP_OID_CPT_SUBSCRIBER_DATA_MNGT     16

extern OIDentifier GSMMAPSubscriberDataMngtV2;
extern OIDentifier GSMMAPSubscriberDataMngtV1;

/*
 * tracingContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac tracing(17) version2(2)}
 * tracingContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac tracing(17) version1(1)}
 */
#define GSMMAP_OID_CPT_TRACING_CONTEXT          17

extern OIDentifier GSMMAPTracingContextV2;
extern OIDentifier GSMMAPTracingContextV1;

/*
 * networkFunctionalSsContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac networkFunctionalSs(18) version2(2)}
 * networkFunctionalSsContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac networkFunctionalSs(18) version1(1)}
 */
#define GSMMAP_OID_CPT_NETWORK_FUNCTIONAL_SS    18

extern OIDentifier GSMMAPNetworkFunctionalSSV2;
extern OIDentifier GSMMAPNetworkFunctionalSSV1;

/*
 * networkUnstructuredSsContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac networkUnstructuredSs(19) version2(2)}
 */
#define GSMMAP_OID_CPT_NETWORK_UNSTRUCTURED_SS  19

extern OIDentifier GSMMAPNetworkUnstructuredSSV2;

/*
 * shortMsgGatewayContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac shortMsgGateway(20) version2(2)}
 * shortMsgGatewayContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac shortMsgGateway(20) version1(1)}
 */
#define GSMMAP_OID_CPT_SHORT_MSG_GATEWAY        20

extern OIDentifier GSMMAPShortMsgGatewayV2;
extern OIDentifier GSMMAPShortMsgGatewayV1;

/*
 * shortMsgMO-RelayContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac shortMsgMO-Relay(21) version2(2)}
 * shortMsgRelayContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac --shortMsgRelay--21 version1(1)}
 */
#define GSMMAP_OID_CPT_SHORT_MSG_MO_RELAY       21

extern OIDentifier GSMMAPShortMsgMORelayV2;
extern OIDentifier GSMMAPShortMsgMORelayV1;

/*
 * shortMsgAlertContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac shortMsgAlert(23) version2(2)}
 * shortMsgAlertContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac shortMsgAlert(23) version1(1)}
 */
#define GSMMAP_OID_CPT_SHORT_MSG_ALERT          23

extern OIDentifier GSMMAPShortMsgAlertV2;
extern OIDentifier GSMMAPShortMsgAlertV1;

/*
 * mwdMngtContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac mwdMngt(24) version2(2)}
 * mwdMngtContext-v1 OBJECT IDENTIFIER ::=
 *   {map-ac mwdMngt(24) version1(1)}
 */
#define GSMMAP_OID_CPT_MWD_MNGT                 24

extern OIDentifier GSMMAPMWDMngtV2;
extern OIDentifier GSMMAPMWDMngtV1;

/*
 * shortMsgMT-RelayContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac shortMsgMT-Relay(25) version2(2)}
 */
#define GSMMAP_OID_CPT_SHORT_MSG_MT             25

extern OIDentifier GSMMAPShortMsgMTV2;

/*
 * imsiRetrievalContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac imsiRetrieval(26) version2(2)}
 */
#define GSMMAP_OID_CPT_IMSI_RETRIEVAL           26

extern OIDentifier GSMMAPIMSIRetrievalV2;

/*
 * msPurgingContext-v2 OBJECT IDENTIFIER ::=
 *   {map-ac msPurging(27) version2(2)}
 */
#define GSMMAP_OID_CPT_MS_PURGING               27

extern OIDentifier GSMMAPMSPurgingV2;

#endif
