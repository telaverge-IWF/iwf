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
//  ID: $Id: GSMMAPP2P.h,v 9.1 2005/03/23 12:51:24 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//   GSMMAP Phase 2+ (P2P) constants (C++ API).
//
//


#if !defined(_GSMMAPP2P_H_)
#define _GSMMAPP2P_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <its++.h>
#include <Octets.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif    // defined(ITS_NAMESPACE)

//When anyone uses this method, the user MUST free the
//Octets

std::vector<byte> 
EncodeApplicationContext(long acName, long version);

void 
DecodeApplicationContext(std::vector<byte>& encodedVec, 
                         long& acName, long& version);

//Application Context

enum
{
    OID_CPT_CCITT               = 0,
    OID_CPT_IDEN_ORG            = 4,
    OID_CPT_ETSI                = 0,
    OID_CPT_MOBILE_DOMAIN       = 0,
    OID_CPT_GSM_NETWORK         = 1,
    OID_CPT_AC_ID               = 0

};

////////////////////////////////////////////////////////////////////////////////
//
//  GSM contants.
//

#if defined(ITS_NAMESPACE)
namespace GSM
{
#else   
struct GSM
{
#endif  // defined(ITS_NAMESPACE)

    enum {
        MAP_SSN = 5,
        HLR_SSN = 6,
        VLR_SSN = 7,
        MSC_SSN = 8,
        EIR_SSN = 9,
        AC_SSN  = 10
    };

#if defined(ITS_NAMESPACE)
}
#else
};
#endif  // defined(ITS_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  GSMMAP Phase 2+ contants.
//

#if defined(ITS_NAMESPACE)
namespace GSMMAP
{
#else
struct GSMMAP
{
#endif  // defined(ITS_NAMESPACE)


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

        OP_noteMsPresentForGprs             = 26

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
        ERR_absentsubscriberSM              = 6

    };


#if defined(ITS_NAMESPACE)
}
#else
};
#endif  // defined(ITS_NAMESPACE)


#if defined(ITS_NAMESPACE)
}
#endif    // defined(ITS_NAMESPACE)


#endif  // !defined(_GSMMAPP2P_H_)
