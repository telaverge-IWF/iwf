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
//  ID: $Id: cap_cpp_v4.h,v 9.1 2005/03/23 12:51:11 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  IntelliSS7 CAP C++ API common header (all versions of CAP).
//
//  o   Constant declarations.
//  


#if !defined(_CAP_CPP_V4_H_)
#define _CAP_CPP_V4_H_

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
    OP_continueWithArgument             = 56,  


    // Timer ASE/Package.

    OP_resetTimer                       = 33,


    // Billing ASE/Package.

    OP_furnishChargingInformation       = 34,


    // Charging ASE/Package.

    OP_applyCharging                    = 35,
    OP_applyChargingReport              = 36,


    // Traffic Management Package. 

    OP_callGap                          = 41,  


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

    OP_cancel                           = 53,  


    // Activity Test ASE/Package.

    OP_activityTest                     = 55,  


    // Sms Activation Package.

    OP_initialDPSMS                     = 60,  


    // Sms Activity Test Package.

    //OP_activityTestSMS                  = 61,  


    // Sms Billing Package.

    OP_furnishChargingInformationSMS    = 61,  


    // Sms Connect Package.

    OP_connectSMS                       = 62,  


    // Sms Event Handling Package. 

    OP_requestReportSMSEvent            = 63,  
    OP_eventReportSMS                   = 64,  


    // Sms Processing Package.

    OP_continueSMS                      = 65,  


    // Sms Release Package.  

    OP_releaseSMS                       = 66,  


    // Sms Timer Package. 

    OP_resetTimerSMS                    = 67,  


    // Gprs Activity Test Package.

    OP_activityTestGPRS                 = 70,  


    // Gprs Charging Package.

    OP_applyChargingGPRS                = 71,  
    OP_applyChargingReportGPRS          = 72,  


    // Gprs Cancel Package.

    OP_cancelGPRS                       = 73,  


    // Gprs Connect Package.

    OP_connectGPRS                      = 74,  


    // Gprs Processing Package.

    OP_continueGPRS                     = 75,  


    // Gprs Exception Information Package.

    OP_entityReleasedGPRS               = 76,  


    // Gprs Billing Package.

    OP_furnishChargingInformationGPRS   = 77,  


    // Gprs Scf Activation Package.

    OP_initialDPGPRS                    = 78,   


    // Gprs Release Package. 

    OP_releaseGPRS                      = 79,  


    // Gprs Event Handling Package.

    OP_eventReportGPRS                  = 80,  
    OP_requestReportGPRSEvent           = 81,  


    // Gprs Timer Package.

    OP_resetTimerGPRS                   = 82,  


    // Gprs Charge Advice Package.

    OP_sendChargingInformationGPRS      = 83   

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
    ERR_unknownPDPID                    = 18,  
    ERR_unknownGPRSReference            = 19,  
    ERR_overlappingDialogue             = 20   

};


////////////////////////////////////////////////////////////////////////////////
//
//  CAP Application Context constants.
//

enum
{
    OID_CPT_CCITT               = 0,
    OID_CPT_IDEN_ORG            = 4,
    OID_CPT_ETSI                = 0,
    OID_CPT_MOBILE_DOMAIN       = 0,
    OID_CPT_GSM_NETWORK         = 1

};


#if !defined(ITS_NAMESPACE)
};
#endif // defined(ITS_NAMESPACE)


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


#endif // !defined(_CAP_CPP_H_)
