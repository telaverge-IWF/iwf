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
//  ID: $Id: cap_cpp.h,v 9.1.96.1.6.2 2014/03/17 10:10:47 jsarvesh Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  IntelliSS7 CAP C++ API common header (all versions of CAP).
//
//  o   Constant declarations.
//  


#if !defined(_CAP_CPP_H_)
#define _CAP_CPP_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <its++.h>

#include <Asn.h>

#if defined(ITS_NAMESPACE)
namespace cap
{
#else // !defined(ITS_NAMESPACE)
//
// Alternative approach if namespaces are not supported by the C++ compiler.
//  
struct cap
{
#endif  // defined(ITS_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  CAP protocol constants.
//

//////////////////////////////////////////////
//
//  Operation codes (V2 and V3).
//

enum {

    // gsmSCF activation ASE/Package.

    OP_initialDP                        = 0,


    // gsmSCF/gsmSRF activation of assist ASE/Package.

    OP_assistRequestInstructions        = 16,


    // Assist connection establishment ASE/Package. 

    OP_establishTemporaryConnection     = 17,


    // Generic disconnect resource ASE/Package.

    OP_disconnectForwardConnection      = 18,


    // Non-assisted connection establishment ASE/Package. 

    OP_connectToResource                = 19,


    // Connect (elementary gsmSSF function) ASE/Package.

    OP_connect                          = 20,


    // Call handling (elementary gsmSSF function) ASE/Package.

    OP_releaseCall                      = 22,


    // BCSM Event handling ASE/Package.

    OP_requestReportBCSMEvent           = 23,
    OP_eventReportBCSM                  = 24,


    // gsmSSF call processing ASE/Package.

    OP_continue                         = 31,
    OP_continueWithArgument             = 56, // V3 only.


    // Timer ASE/Package.

    OP_resetTimer                       = 33,


    // Billing ASE/Package.

    OP_furnishChargingInformation       = 34,


    // Charging ASE/Package.

    OP_applyCharging                    = 35,
    OP_applyChargingReport              = 36,


    // Traffic Management Package. 

    OP_callGap                          = 41, // V3 only.


    // Call report ASE/Package.

    OP_callInformationReport            = 44,
    OP_callInformationRequest           = 45,


    // Signalling control ASE/Package.

    OP_sendChargingInformation          = 46,


    // Specialized resource control ASE/Package.

    OP_playAnnouncement                 = 47,
    OP_promptAndCollectUserInformation  = 48,
    OP_specializedResourceReport        = 49,


    // Cancel ASE/Package.

    OP_cancel                           = 53, // V3 only.


    // Activity Test ASE/Package.

    OP_activityTest                     = 55, // V3 only.


    // Sms Activation Package.

    OP_initialDPSMS                     = 60, // V3 only.


    // Sms Activity Test Package.
    //NOTE: This ENUM is wrongly defined.
    //OP_activityTestSMS                  = 61, // V3 only.


    // Sms Billing Package.

    OP_furnishChargingInformationSMS    = 61, // V3 only.


    // Sms Connect Package.

    OP_connectSMS                       = 62, // V3 only.


    // Sms Event Handling Package. 

    OP_requestReportSMSEvent            = 63, // V3 only.
    OP_eventReportSMS                   = 64, // V3 only.


    // Sms Processing Package.

    OP_continueSMS                      = 65, // V3 only.


    // Sms Release Package.  

    OP_releaseSMS                       = 66, // V3 only.


    // Sms Timer Package. 

    OP_resetTimerSMS                    = 67, // V3 only.


    // Gprs Activity Test Package.

    OP_activityTestGPRS                 = 70, // V3 only.


    // Gprs Charging Package.

    OP_applyChargingGPRS                = 71, // V3 only.
    OP_applyChargingReportGPRS          = 72, // V3 only.


    // Gprs Cancel Package.

    OP_cancelGPRS                       = 73, // V3 only.


    // Gprs Connect Package.

    OP_connectGPRS                      = 74, // V3 only.


    // Gprs Processing Package.

    OP_continueGPRS                     = 75, // V3 only.


    // Gprs Exception Information Package.

    OP_entityReleasedGPRS               = 76, // V3 only.


    // Gprs Billing Package.

    OP_furnishChargingInformationGPRS   = 77, // V3 only.


    // Gprs Scf Activation Package.

    OP_initialDPGPRS                    = 78, // V3 only.


    // Gprs Release Package. 

    OP_releaseGPRS                      = 79, // V3 only.


    // Gprs Event Handling Package.

    OP_eventReportGPRS                  = 80, // V3 only.
    OP_requestReportGPRSEvent           = 81, // V3 only.


    // Gprs Timer Package.

    OP_resetTimerGPRS                   = 82, // V3 only.


    // Gprs Charge Advice Package.

    OP_sendChargingInformationGPRS      = 83  // V3 only.

};


//////////////////////////////////////////////
//
//  Error codes (V2 and V3).
//

enum {

    ERR_canceled                        = 0,
    ERR_cancelFailed                    = 1,
    ERR_eTCFailed                       = 3,
    ERR_improperCallerResponse          = 4,
    ERR_missingCustomerRecord           = 6,
    ERR_missingParameter                = 7,
    ERR_parameterOutOfRange             = 8,
    ERR_requestedInfoError              = 10,
    ERR_systemFailure                   = 11,
    ERR_taskRefused                     = 12,
    ERR_unavailableResource             = 13,
    ERR_unexpectedComponentSequence     = 14,
    ERR_unexpectedDataValue             = 15,
    ERR_unexpectedParameter             = 16,
    ERR_unknownLegID                    = 17,
    ERR_unknownPDPID                    = 18, // V3 only.
    ERR_unknownGPRSReference            = 19, // V3 only.
    ERR_overlappingDialogue             = 20  // V3 only.

};


////////////////////////////////////////////////////////////////////////////////
//
//  CAP Application Context constants.
//

enum
{
    OID_CPT_CCITT                 = 0,
    OID_CPT_IDEN_ORG              = 4,
    OID_CPT_ETSI                  = 0,
    OID_CPT_MOBILE_DOMAIN         = 0,
    OID_CPT_UMTS_NETWORK          = 1,

    OID_CPT_CAP1_AC               = 0,
    OID_CPT_CAP2_AC               = 0,

    CAPV1_GSMSSF_TO_GSMSCF        = 50,
    CAPV1_VERSION                 = 0,

    CAPV2_GSMSSF_TO_GSMSCF        = 50,
    CAPV2_ASSIST_GSMSSF_TO_GSMSCF = 51,
    CAPV2_GSMSRF_TO_GSMSCF        = 52,
    CAPV2_VERSION                 = 1,

    OID_CPT_CAP3                  = 20,
    OID_CPT_CAP3OE                = 21,
    OID_CPT_CAP4                  = 22,
    OID_CPT_CAP4OE                = 23,

    CAP_AC_ID_AC                  = 3,
    CAP_AC_ID_ACE                 = 3,

    CAPV3_CAPSSF_SCFGENERIC       = 4,
    CAPV3_CAPSSF_SCFASSISTHO      = 6,
    CAPV3_GSMSRF_GSMSCF           = 14,
    CAPV3_SMS                     = 61,
    CAPV3_GPRSSSF_GSMSCF          = 50,
    CAPV3_GSMSCF_GPRSSSF          = 51, 

    CAPV4_CAPSSF_SCFGENERIC       = 4,
    CAPV4_CAPSSF_SCFASSISTHO      = 6,
    CAPV4_CAPSCF_SSFGENERIC       = 8,
    CAPV4_GSMSRF_GSMSCF           = 14,
    CAPV4_SMS                     = 61
};

typedef enum
{
    UNKNOWN = 0,

    CAPV1_gsmSSF_to_gsmSCF_AC          = 1,

    CAPV2_gsmSSF_to_gsmSCF_AC          = 2,
    CAPV2_assist_gsmSSF_to_gsmSCF_AC   = 3,
    CAPV2_gsmSRF_to_gsmSCF_AC          = 4,

    CAPV3_capssf_scfGeneric_AC         = 5,
    CAPV3_capssf_scfAssistHandoff_AC   = 6,
    CAPV3_gsmSRF_gsmSCF_AC             = 7,
    CAPV3_cap3_sms_AC                  = 8,
    CAPV3_cap3_gprsSSF_gsmSCF_AC       = 9,
    CAPV3_cap3_gsmSCF_gprsSSF_AC       = 10,
    
    CAPV4_capssf_scfGeneric_AC         = 11,
    CAPV4_capssf_scfAssistHandoff_AC   = 12,
    CAPV4_capscf_ssfGeneric_AC         = 13,
    CAPV4_gsmSRF_gsmSCF_AC             = 14,
    CAPV4_cap4_sms_AC                  = 15

}CAP_AC;


#if !defined(ITS_NAMESPACE)
};
#endif // defined(ITS_NAMESPACE)

CAP_AC DecodeApplicationContext(std::vector<byte>& encodedVec);

std::vector<byte> EncodeApplicationContext(CAP_AC acName);

std::vector<byte> EncodeApplicationContextVector(std::vector<long>& ac);

std::vector<long> DecodeApplicationContextVector(std::vector<byte>& ac);

#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


#endif // !defined(_CAP_CPP_H_)
