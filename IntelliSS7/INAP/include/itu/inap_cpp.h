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
//  ID: $Id: inap_cpp.h,v 9.4 2005/07/01 06:54:27 mmanikandan Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  IntelliSS7 INAP C++ API common header (all versions of INAP). 
//
//  o   Constant declarations.
//

#if !defined(_INAP_CPP_H_)
#define _INAP_CPP_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <its++.h>

#include <Asn.h>

#if defined(ITS_NAMESPACE)
namespace inap  
{
#else // !defined(ITS_NAMESPACE)
//
// Alternative approach if namespaces are not supported by the C++ compiler.
//  
struct inap
{
#endif  // defined(ITS_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  INAP protocol constants.
//

//////////////////////////////////////////////
//
//  Operation codes.
//

enum {

        OP_initialDP                           = 0,
        OP_originationAttemptAuthorized        = 1,
        OP_collectedInformation                = 2,
        OP_analysedInformation                 = 3,
        OP_routeSelectFailure                  = 4,
        OP_oCalledPartyBusy                    = 5,
        OP_oNoAnswer                           = 6,
        OP_oAnswer                             = 7,
        OP_oDisconnect                         = 8,
        OP_termAttemptAuthorized               = 9,
        OP_tBusy                               = 10,
        OP_tNoAnswer                           = 11,
        OP_tAnswer                             = 12,
        OP_tDisconnect                         = 13,
        OP_oMidCall                            = 14,
        OP_tMidCall                            = 15,
        OP_assistRequestInstructions           = 16,
        OP_establishTemporaryConnection        = 17,
        OP_disconnectForwardConnection         = 18,
        OP_connectToResource                   = 19,
        OP_connect                             = 20,
        OP_holdCallInNetwork                   = 21,
        OP_releaseCall                         = 22,
        OP_requestReportBCSMEvent              = 23,
        OP_eventReportBCSM                     = 24,
        OP_requestNotificationChargingEvent    = 25,
        OP_eventNotificationCharging           = 26,
        OP_collectInformation                  = 27,
        OP_analyseInformation                  = 28,
        OP_selectRoute                         = 29,
        OP_selectFacility                      = 30,
        OP_continue                            = 31,
        OP_initiateCallAttempt                 = 32,
        OP_resetTimer                          = 33,
        OP_furnishChargingInformation          = 34,
        OP_applyCharging                       = 35,
        OP_applyChargingReport                 = 36,
        OP_requestCurrentStatusReport          = 37,
        OP_requestEveryStatusChangeReport      = 38,
        OP_requestFirstStatusMatchReport       = 39,
        OP_statusReport                        = 40,
        OP_callGap                             = 41,
        OP_activateServiceFiltering            = 42,
        OP_serviceFilteringResponse            = 43,
        OP_callInformationReport               = 44,
        OP_callInformationRequest              = 45,
        OP_sendChargingInformation             = 46,
        OP_playAnnouncement                    = 47,
        OP_promptAndCollectUserInformation     = 48,
        OP_specializedResourceReport           = 49,
        OP_cancel                              = 53,
        OP_cancelStatusReportRequest           = 54,
        OP_activityTest                        = 55,
        OP_requestCurrentStatusReportResult    = 56

};

// SCD - SDF Interface Operations

enum {
    OP_search  = 5,
    OP_addEntry = 6,
    OP_removeEntry = 7,
    OP_modifyEntry = 8,
    OP_execute = 10
};


//////////////////////////////////////////////
//
//  Error codes.
//

enum {

        ERR_cancelled                      = 0,
        ERR_cancelFailed                   = 1,
        ERR_eTCFailed                      = 3,
        ERR_improperCallerResponse         = 4,
        ERR_missingCustomerRecord          = 6,
        ERR_missingParameter               = 7,
        ERR_parameterOutOfRange            = 8,
        ERR_requestedInfoError             = 10,
        ERR_systemFailure                  = 11,
        ERR_taskRefused                    = 12,
        ERR_unavailableResource            = 13,
        ERR_unexpectedComponentSequence    = 14,
        ERR_unexpectedDataValue            = 15,
        ERR_unexpectedParameter            = 16,
        ERR_unknownLegID                   = 17,
        ERR_unknownResource                = 18

};

// SCD - SDF Interface Errors

enum {
    ERR_attributeError = 1,
    ERR_nameError      = 2,
    ERR_serviceError   = 3,
    ERR_referral       = 4,
    ERR_securityError  = 6,
    ERR_updateError    = 8,
    ERR_executionError = 10
};

enum
{
    OID_CPT_CCITT           = 0,
    OID_CPT_RECOMMENDATION  = 0,
    OID_CPT_Q               = 17,
    OID_CPT_Q1228           = 1228,
    OID_CPT_Q1218           = 1218,
    OID_CPT_CS2             = 2,
    OID_SCF_SSF_SRF_OBJECTS = 1,
    OID_CPT_SDF_OBJECTS     = 10,
    OID_CPT_AC              = 3,

    OID_VERSION             = 0,

    CS1_START               = 1,
    CS2_START               = 50,
    CS1_MAX                 = 11,
    CS2_MAX                 = 77
};

typedef enum
{
    UNKNOWN = 0,

    IN_CS1_SSF_to_SCF_Generic_AC             = 1,
    IN_CS1_SSF_to_SCF_DPspecific_AC          = 2,
    IN_CS1_assist_handoff_SSF_to_SCF_AC      = 3,
    IN_CS1_SRF_to_SCF_AC                     = 4,
    IN_CS1_SCF_to_SSF_Generic_AC             = 5,
    IN_CS1_SCF_to_SSF_DPspecific_AC          = 6,
    IN_CS1_SCF_to_SSF_traffic_management_AC  = 7,
    IN_CS1_SCF_to_SSF_service_management_AC  = 8,
    IN_CS1_SSF_to_SCF_service_management_AC  = 9,
    IN_CS1_SCF_to_SSF_status_reporting_AC    = 10,

    id_ac_directoryAccessAC                  = 11,

    id_ac_indirectoryAccessAC                = 51,
    id_ac_indirectoryAccessWith3seAC         = 52,
    id_ac_inExtendedDirectoryAccessAC        = 53,

    id_ac_cs2_ssf_scfGenericAC               = 54,
    id_ac_cs2_ssf_scfDPSpecificAC            = 55,
    id_ac_cs2_ssf_scfAssistHandoffAC         = 56,
    id_ac_cs2_ssf_scfServiceManagementAC     = 57,
    id_ac_cs2_scf_ssfGenericAC               = 58,
    id_ac_cs2_scf_ssfDPSpecificAC            = 59,
    id_ac_cs2_scf_ssfTrafficManagementAC     = 60,
    id_ac_cs2_scf_ssfServiceManagementAC     = 61,
    id_ac_cs2_scf_ssfStatusReportingAC       = 62,
    id_ac_cs2_scf_ssfTriggerManagementAC     = 63,

    id_ac_srf_scf                            = 64,

    id_ac_indirectorySystemAC                = 65,
    id_ac_inShadowSupplierInitiatedAC        = 66,
    id_ac_inShadowConsumerInitiatedAC        = 67,
    id_ac_indirectorySystemWith3seAC         = 68,
    id_ac_inShadowSupplierInitiatedWith3seAC = 69,
    id_ac_inShadowConsumerInitiatedWith3seAC = 70,

    id_ac_scf_scfOperationsAC                = 71,
    id_ac_distributedSCFSystemAC             = 72,
    id_ac_scf_scfOperationsWith3seAC         = 73,
    id_ac_distributedSCFSystemWith3seAC      = 74,
    id_ac_scf_cusf                           = 75,
    id_ac_cusf_scf                           = 76,

    id_ac_inExtendedDirectoryAccessWith3seAC = 77 

}INAP_AC;

#if !defined(ITS_NAMESPACE)
};
#endif // defined(ITS_NAMESPACE)

INAP_AC DecodeApplicationContext(std::vector<byte>& encodedVec);

std::vector<byte> EncodeApplicationContext(INAP_AC acName);

std::vector<byte> EncodeApplicationContextVector(std::vector<long>& ac);

std::vector<long> DecodeApplicationContextVector(std::vector<byte>& ac);

#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_INAP_CPP_H_)

