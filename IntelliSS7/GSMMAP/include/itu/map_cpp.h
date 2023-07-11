////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1999 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: map_cpp.h,v 9.2 2007/01/10 11:14:59 yranade Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  IntelliSS7 GSM MAP C++ API common header (all versions of GSM MAP). 
//
//  o   Constant declarations.
//
//  o   Application Context Helper function declarations.
//  


#if !defined(_MAP_CPP_H_)
#define _MAP_CPP_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <its++.h>

#include <Asn.h>

#if defined(ITS_NAMESPACE)
namespace map_common
{
#else // !defined(ITS_NAMESPACE)
//
// Alternative approach if namespaces are not supported by the C++ compiler.
//  
struct map_common
{
#endif  // defined(ITS_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  MAP general constants.
//


enum {
    MAP_SSN = 5,
    HLR_SSN = 6,
    VLR_SSN = 7,
    MSC_SSN = 8,
    EIR_SSN = 9,
    AC_SSN  = 10
};


////////////////////////////////////////////////////////////////////////////////
//
//  MAP protocol constants.
//

//////////////////////////////////////////////
//
//  Operation codes.
//

enum {

    // Location registration operation codes.

    OP_updateLocation                   = 2,
    OP_cancelLocation                   = 3,
    OP_purgeMS                          = 67,
    OP_sendIdentification               = 55,

    // Handover operation codes.

    OP_prepareHandover                  = 68,
    OP_sendEndSignal                    = 29,
    OP_processAccessSignalling          = 33,
    OP_forwardAccessSignalling          = 34,
    OP_prepareSubsequentHandover        = 69,

    // Authentication operation codes.

    OP_sendAuthenticationInfo           = 56,
    OP_authenticationFailureReport      = 15,


    // IMEI MANAGEMENT operation codes.

    OP_checkIMEI                        = 43,


    // Subscriber management operation codes.

    OP_insertSubscriberData             = 7,
    OP_deleteSubscriberData             = 8,


    // Fault recovery operation codes.

    OP_reset                            = 37,
    OP_forwardCheckSS_Indication        = 38,
    OP_restoreData                      = 57,


    // Operation and maintenance operation codes.

    OP_activateTraceMode                = 50,
    OP_deactivateTraceMode              = 51,
    OP_sendIMSI                         = 58,


    // Call handling operation codes.

    OP_sendRoutingInfo                  = 22,
    OP_provideRoamingNumber             = 4,
    OP_resumeCallHandling               = 6,
    OP_provideSIWFSNumber               = 31,
    OP_sIWFSSignallingModify            = 32,
    OP_setReportingState                = 73,
    OP_statusReport                     = 74,
    OP_remoteUserFree                   = 75,
    OP_istAlert                         = 87,
    OP_istCommand                       = 88,


    // Supplementary service handling operation codes.

    OP_registerSS                       = 10,
    OP_eraseSS                          = 11,
    OP_activateSS                       = 12,
    OP_deactivateSS                     = 13,
    OP_interrogateSS                    = 14,
    OP_processUnstructuredSS_Request    = 59,
    OP_unstructuredSS_Request           = 60,
    OP_unstructuredSS_Notify            = 61,
    OP_registerPassword                 = 17,
    OP_getPassword                      = 18,
    OP_registerCC_Entry                 = 76,
    OP_eraseCC_Entry                    = 77,


    // Short message service operation codes.

    OP_sendRoutingInfoForSM             = 45,
    OP_mo_forwardSM                     = 46,
    OP_mt_forwardSM                     = 44,
    OP_reportSM_DeliveryStatus          = 47,
    OP_informServiceCentre              = 63,
    OP_alertServiceCentre               = 64,
    OP_readyForSM                       = 66,


    // Provide subscriber info operation codes,

    OP_provideSubscriberInfo            = 70,


    // Any time interrogation operation codes.

    OP_anyTimeInterrogation             = 71,


    // Any time information handling operation codes.

    OP_anyTimeSubscriptionInterrogation = 62,
    OP_anyTimeModification              = 65,


    // Subscriber data modification notification operation codes.

    OP_noteSubscriberDataModified       = 5,


    // Supplementary service invocation notification operation codes.

    OP_ss_InvocationNotification        = 72,


    // Group Call operation codes.

    OP_prepareGroupCall                 = 39,
    OP_sendGroupCallEndSignal           = 40,
    OP_processGroupCallSignalling       = 41,
    OP_forwardGroupCallSignalling       = 42,


    // Gprs location updating operation codes.

    OP_updateGprsLocation               = 23,


    // Gprs location information retrieval operation codes.

    OP_sendRoutingInfoForGprs           = 24,


    // Failure reporting operation codes.

    OP_failureReport                    = 25,


    // GPRS notification operation codes.

    OP_noteMsPresentForGprs             = 26,


    // Location service operation codes.

    OP_provideSubscriberLocation        = 83,
    OP_sendRoutingInfoForLCS            = 85,
    OP_subscriberLocationReport         = 86,


    // Mobility Management operation codes.

    OP_noteMM_Event                     = 89,


    // Secure transport operation codes.

    OP_secureTransportClass1            = 78,
    OP_secureTransportClass2            = 79,
    OP_secureTransportClass3            = 80,
    OP_secureTransportClass4            = 81,


    // V1 operation codes (not defined by V2 and V4).   

    OP_updateLocationArea               = 1,
    OP_detachIMSI                       = 5,
    OP_attachIMSI                       = 6,
    OP_sendParameters                   = 9,
    OP_invokeSS                         = 15,
    OP_forwardSsNotification            = 16,
    OP_processUnstructuredSsData        = 19,
    OP_sendInfoForIncomingCall          = 20,
    OP_sendInfoForOutgoingCall          = 21,
    OP_completeCall                     = 23,
    OP_connectToFollowingAddress        = 24,
    OP_processCallWaiting               = 25,
    OP_page                             = 26,
    OP_searchForMobileSubscriber        = 27,
    OP_performHandover                  = 28,
    OP_performSubsequentHandover        = 30,
    OP_allocateHandoverNumber           = 31,
    OP_sendHandoverReport               = 32,
    OP_noteInternalHandover             = 35,
    OP_registerChargingInformation      = 36,
    OP_authenticate                     = 39,
    OP_provideIMSI                      = 40,
    OP_forwardNewTMSI                   = 41,
    OP_setCipheringMode                 = 42,
    OP_forwardShortMessage              = 46,
    OP_setMessageWaitingData            = 47,
    OP_noteMSPresent                    = 48,
    OP_alertServiceCenter               = 49,
    OP_traceSubscriberActivity          = 52,
    OP_processAccessRequest             = 53,
    OP_beginSubscriberActivity          = 54

};


//////////////////////////////////////////////
//
//  Error codes.
//

enum {

    // Generic error codes.

    ERR_systemFailure                   = 34,
    ERR_dataMissing                     = 35,
    ERR_unexpectedDataValue             = 36,
    ERR_facilityNotSupported            = 21,
    ERR_incompatibleTerminal            = 28,
    ERR_resourceLimitation              = 51,


    // Identification and numbering error codes.

    ERR_unknownSubscriber               = 1,
    ERR_numberChanged                   = 44,
    ERR_unknownMSC                      = 3,
    ERR_unidentifiedSubscriber          = 5,
    ERR_unknownEquipment                = 7,


    // Subscription error codes.

    ERR_roamingNotAllowed               = 8,
    ERR_illegalSubscriber               = 9,
    ERR_illegalEquipment                = 12,
    ERR_bearerServiceNotProvisioned     = 10,
    ERR_teleserviceNotProvisioned       = 11,


    // Handover error codes.

    ERR_noHandoverNumberAvailable       = 25,
    ERR_subsequentHandoverFailure       = 26,
    ERR_targetCellOutsideGroupCallArea  = 42,


    // Operation and maintenance error codes.

    ERR_tracingBufferFull               = 40,


    // Call handling error codes.

    ERR_noRoamingNumberAvailable        = 39,
    ERR_absentSubscriber                = 27,
    ERR_busySubscriber                  = 45,
    ERR_noSubscriberReply               = 46,
    ERR_callBarred                      = 13,
    ERR_forwardingFailed                = 47,
    ERR_or_NotAllowed                   = 48,
    ERR_forwardingViolation             = 14,
    ERR_cug_Reject                      = 15,


    // Any time interrogation error codes.
    
    ERR_ati_NotAllowed                  = 49,


    // Any time information handling error codes.

    ERR_atsi_NotAllowed                 = 60,
    ERR_atm_NotAllowed                  = 61,
    ERR_informationNotAvailable         = 62,


    // Group Call error codes

    ERR_noGroupCallNumberAvailable      = 50,


    // Supplementary service error codes.

    ERR_illegalSS_Operation             = 16,
    ERR_ss_ErrorStatus                  = 17,
    ERR_ss_NotAvailable                 = 18,
    ERR_ss_SubscriptionViolation        = 19,
    ERR_ss_Incompatibility              = 20,
    ERR_unknownAlphabet                 = 71,
    ERR_ussd_Busy                       = 72,
    ERR_pw_RegistrationFailure          = 37,
    ERR_negativePW_Check                = 38,
    ERR_numberOfPW_AttemptsViolation    = 43,
    ERR_shortTermDenial                 = 29,
    ERR_longTermDenial                  = 30,


    // Short message service error codes.

    ERR_subscriberBusyForMT_SMS         = 31,
    ERR_sm_DeliveryFailure              = 32,
    ERR_messageWaitingListFull          = 33,
    ERR_absentsubscriberSM              = 6,


    // Location service error codes.

    ERR_unauthorizedRequestingNetwork   = 52,
    ERR_unauthorizedLCSClient           = 53,
    ERR_positionMethodFailure           = 54,
    ERR_unknownOrUnreachableLCSClient   = 58,

    
    // Mobility Management error codes.

    ERR_mm_EventNotSupported            = 59,


    // Secure transport error codes.

    ERR_secureTransportError            = 4,




    // V1 error codes (not defined by V2 and V4).

    ERR_unknownBaseStation              = 2,
    ERR_unknownLocArea                  = 4,
    ERR_unallocatedRoamingNumber        = 6,
    ERR_illegalMS                       = 9,
    ERR_insufficientBearerCapabilities  = 12,
    ERR_invalidTargetBaseStation        = 23,
    ERR_noRadioResourceAvailable        = 24,
    ERR_V1_busySubscriber               = 28,
    ERR_V1_noSubscriberReply            = 29,
    ERR_radioCongestion                 = 30,
    ERR_impossibleCallCompletion        = 31,
    ERR_passwordRegistrationFailure     = 37,
    ERR_negativePasswordCheck           = 38

};


////////////////////////////////////////////////////////////////////////////////
//
//  MAP Application Context constants.
//

enum
{
    OID_CPT_CCITT               = 0,
    OID_CPT_IDEN_ORG            = 4,
    OID_CPT_ETSI                = 0,
    OID_CPT_MOBILE_DOMAIN       = 0,
    OID_CPT_GSM_NETWORK         = 1,
    OID_CPT_AC_ID               = 0,

    OID_NETWORK_lOC_UP_CONTEXT                            = 1,
    OID_LOCATION_CANCELLATION                             = 2,
    OID_ROAMING_NUMBER_ENQUIRY_CONTEXT                    = 3,
    OID_IST_ALERTING_CONTEXT                              = 4,
    OID_LOCATION_INFO_RETRIEVAL_CONTEXT                   = 5,
    OID_CALL_CONTROL_TRANSFER_CONTEXT                     = 6,
    OID_REPORTING_CONTEXT                                 = 7,
    OID_CALL_COMPLETION_CONTEXT                           = 8,
    OID_SERVICE_TERMINATION_CONTEXT                       = 9,
    OID_RESET_CONTEXT                                     = 10,
    OID_HANDOVER_CONTROL_CONTEXT                          = 11,
    OID_SIWFS_ALLOCATION_CONTEXT                          = 12,
    OID_EQUIPMENT_MNGT_CONTEXT                            = 13,
    OID_INFO_RETRIEVAL_CONTEXT                            = 14,
    OID_INTER_VLR_INFO_RETRIEVAL_CONTEXT                  = 15,
    OID_SUBSCRIBER_DATA_MNGT_CONTEXT                      = 16,
    OID_TRACING_CONTEXT                                   = 17,
    OID_NETWORK_FUNCTIONAL_SS_CONTEXT                     = 18,
    OID_NETWORK_UNSTRUCTURED_SS_CONTEXT                   = 19,
    OID_SHORT_MSG_GATEWAY_CONTEXT                         = 20,
    OID_SHORT_MSG_RELAY_CONTEXT                           = 21,
    OID_SUBSCRIBER_DATA_MODIFICATION_NOTIFICATION_CONTEXT = 22,
    OID_SHORT_MSG_ALERT_CONTEXT                           = 23,
    OID_MWD_MNGT_CONTEXT                                  = 24,
    OID_SHORT_MSG_MT_RELAY_CONTEXT                        = 25,
    OID_IMSI_RETRIEVAL_CONTEXT                            = 26,
    OID_MS_PURGING_CONTEXT                                = 27,
    OID_SUBSCRIBER_INFO_ENQUIRY_CONTEXT                   = 28,
    OID_ANYTIME_INFO_ENQUIRY_CONTEXT                      = 29,
    OID_GROUP_CALL_CONTROL_CONTEXT                        = 31,
    OID_GPRS_LOCATION_UPDATE_CONTEXT                      = 32,
    OID_GPRS_LOCATION_INFO_RETRIEVAL_CONTEXT              = 33,
    OID_FAILURE_REPORT_CONTEXT                            = 34,
    OID_GPRS_NOTIFY_CONTEXT                               = 35,
    OID_SS_INVOCATION_NOTIFICATION_CONTEXT                = 36,
    OID_LOCATION_SVC_GATEWAY_CONTEXT                      = 37,
    OID_LOCATION_SVC_ENQUIRY_CONTEXT                      = 38,
    OID_AUTHENTICATION_FAILURE_REPORT_CONTEXT             = 39,
    OID_SECURE_TRANSPORT_HANDLING_CONTEXT                 = 40,
    OID_MM_EVENT_REPORTING_CONTEXT                        = 42,
    OID_ANY_TIME_INFO_HANDLING_CONTEXT                    = 43,
 
    OID_CPT_VERSION1 = 1,
    OID_CPT_VERSION2 = 2,
    OID_CPT_VERSION3 = 3, 
    OID_CPT_VERSION4 = 4 

};

typedef enum
{
    UNKNOWN                                          = 0,

    networkLocUpContext_v1                           = 1,
    locationCancellationContext_v1                   = 2,
    roamingNumberEnquiryContext_v1                   = 3,
    locationInfoRetrievalContext_v1                  = 4,
    resetContext_v1                                  = 5,
    handoverControlContext_v1                        = 6,
    equipmentMngtContext_v1                          = 7,
    infoRetrievalContext_v1                          = 8,
    subscriberDataMngtContext_v1                     = 9,
    tracingContext_v1                                = 10,
    networkFunctionalSsContext_v1                    = 11,
    shortMsgGatewayContext_v1                        = 12,
    shortMsg_RelayContext_v1                         = 13,
    shortMsgAlertContext_v1                          = 14,
    mwdMngtContext_v1                                = 15,

    networkLocUpContext_v2                           = 16,
    locationCancellationContext_v2                   = 17,
    roamingNumberEnquiryContext_v2                   = 18,
    locationInfoRetrievalContext_v2                  = 19,
    resetContext_v2                                  = 20,
    handoverControlContext_v2                        = 21,
    equipmentMngtContext_v2                          = 22,
    infoRetrievalContext_v2                          = 23,
    interVlrInfoRetrievalContext_v2                  = 24,
    subscriberDataMngtContext_v2                     = 25,
    tracingContext_v2                                = 26,
    networkFunctionalSsContext_v2                    = 27,
    networkUnstructuredSsContext_v2                  = 28,
    shortMsgGatewayContext_v2                        = 29,
    shortMsgMO_RelayContext_v2                       = 30,
    shortMsgAlertContext_v2                          = 31,
    mwdMngtContext_v2                                = 32,
    shortMsgMT_RelayContext_v2                       = 33,
    imsiRetrievalContext_v2                          = 34,
    msPurgingContext_v2                              = 35,

    networkLocUpContext_v3                           = 36,
    locationCancellationContext_v3                   = 37,
    roamingNumberEnquiryContext_v3                   = 38,
    istAlertingContext_v3                            = 39,
    locationInfoRetrievalContext_v3                  = 40,
    callControlTransferContext_v3                    = 41,
    reportingContext_v3                              = 42,
    callCompletionContext_v3                         = 43,
    serviceTerminationContext_v3                     = 44,
    handoverControlContext_v3                        = 45,
    sIWFSAllocationContext_v3                        = 46,
    infoRetrievalContext_v3                          = 47,
    interVlrInfoRetrievalContext_v3                  = 48,
    subscriberDataMngtContext_v3                     = 49,
    tracingContext_v3                                = 50,
    shortMsgGatewayContext_v3                        = 51,
    shortMsgMO_RelayContext_v3                       = 52,
    subscriberDataModificationNotificationContext_v3 = 53,
    mwdMngtContext_v3                                = 54,
    shortMsgMT_RelayContext_v3                       = 55,
    msPurgingContext_v3                              = 56,
    subscriberInfoEnquiryContext_v3                  = 57,
    anyTimeInfoEnquiryContext_v3                     = 58,
    groupCallControlContext_v3                       = 59,
    gprsLocationUpdateContext_v3                     = 60,
    gprsLocationInfoRetrievalContext_v3              = 61,
    failureReportContext_v3                          = 62,
    gprsNotifyContext_v3                             = 63,
    ss_InvocationNotificationContext_v3              = 64,
    locationSvcGatewayContext_v3                     = 65,
    locationSvcEnquiryContext_v3                     = 66,
    authenticationFailureReportContext_v3            = 67,
    SecureTransportHandlingContext_v3                = 68,
    mm_EventReportingContext_v3                      = 69,
    anyTimeInfohandlingContext_v3                    = 70,

    callControlTransferContext_v4                    = 71
}
MAP_AC;

#if !defined(ITS_NAMESPACE)
};
#endif // defined(ITS_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  MAP Application Context helper functions.
//

MAP_AC DecodeApplicationContext(std::vector<byte>& encodedVec);

std::vector<byte> EncodeApplicationContext(MAP_AC acName);

std::vector<byte> EncodeApplicationContextVector(std::vector<long>& ac);

std::vector<long> DecodeApplicationContextVector(std::vector<byte>& ac);

void DecodeApplicationContext( std::vector<byte>& encodedVec, long& acName, long
& version);


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


#endif // !defined(_MAP_CPP_H_)
