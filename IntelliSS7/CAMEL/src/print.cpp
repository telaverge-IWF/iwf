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
//  ID: $Id: print.cpp,v 9.1 2005/03/23 12:51:14 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <its.h>
#include <its_pprint.h>

#include <itu/tcap.h>

#include <cap_cpp.h>

#ident "$Id: print.cpp,v 9.1 2005/03/23 12:51:14 cvsadmin Exp $"

/*
 *  * shorthand
 *   */
#define CHECK_RETURN(r, cnt)    \
    if ((r) < 0)                \
    {                           \
        return (cnt);           \
    }                           \
    else                        \
    {                           \
        (cnt) += (r);           \
    }

#include <cap_v4_initial_dp_arg.h>
#include <cap_v4_assist_request_instructions_arg.h>
#include <cap_v4_establish_temporary_connection_arg.h>
#include <cap_v4_disconnect_forward_connection_with_argument_arg.h>
#include <cap_v4_connect_to_resource_arg.h>
#include <cap_v4_connect_arg.h>
#include <cap_v4_release_call_arg.h>
#include <cap_v4_request_report_bcsm_event_arg.h>
#include <cap_v4_event_report_bcsm_arg.h>
#include <cap_v4_continue_with_argument_arg.h>
#include <cap_v4_continue_with_argument_arg.h>
#include <cap_v4_reset_timer_arg.h>
#include <cap_v4_furnish_charging_information_arg.h>
#include <cap_v4_apply_charging_arg.h>
#include <cap_v4_apply_charging_report_arg.h>
#include <cap_v4_call_gap_arg.h>
#include <cap_v4_call_information_report_arg.h>
#include <cap_v4_call_information_request_arg.h>
#include <cap_v4_send_charging_information_arg.h>
#include <cap_v4_play_announcement_arg.h>
#include <cap_v4_prompt_and_collect_user_information_arg.h>
#include <cap_v4_specialized_resource_report_arg.h>
#include <cap_v4_cancel_arg.h>
#include <cap_v4_initial_dpsms_arg.h>
#include <cap_v4_furnish_charging_information_sms_arg.h>
#include <cap_v4_connect_sms_arg.h>
#include <cap_v4_request_report_sms_event_arg.h>
#include <cap_v4_event_report_sms_arg.h>
#include <cap_v4_release_sms_arg.h>
#include <cap_v4_reset_timer_sms_arg.h>
#include <cap_v4_apply_charging_gprs_arg.h>
#include <cap_v4_apply_charging_report_gprs_arg.h>
#include <cap_v4_cancel_gprs_arg.h>
#include <cap_v4_connect_gprs_arg.h>
#include <cap_v4_continue_gprs_arg.h>
#include <cap_v4_entity_released_gprs_arg.h>
#include <cap_v4_furnish_charging_information_gprs_arg.h>
#include <cap_v4_initial_dpgprs_arg.h>
#include <cap_v4_release_gprs_arg.h>
#include <cap_v4_event_report_gprs_arg.h>
#include <cap_v4_request_report_gprs_event_arg.h>
#include <cap_v4_reset_timer_gprs_arg.h>
#include <cap_v4_send_charging_information_gprs_arg.h>

/*
 * local namespaces in use.
 */
using namespace cap_v4;
using namespace cap;
using namespace std;
using namespace its;

/*
 * A helper for decode and print
 */
static inline int
DecodeAndPrint(RINGBUF_Manager *rb, int& tmp, int& ret,
               const char *startText, const char *endText,
               AsnObject& obj, Octets& octets)
{
    tmp = PPrint(rb, startText);
    CHECK_RETURN(tmp, ret);
    RINGBUF_Flush(rb);
    std::strstream outputStream;
    char* buffer;
    ITS_UINT length = 0;

    try
    {
        obj.Decode(octets);
    }
    catch (GenericException &ex)
    {
        cout << "Caught decode exception." << endl;
        cout << ex.GetDescription() << endl;
    }
    catch (exception &sex)
    {
        cout << "Caught Exception." << endl;
        cout << sex.what() << endl;
    }

    outputStream << obj << std::ends;
    outputStream.seekg (0, ios::end);
    length = outputStream.tellg();
    outputStream.seekg (0, ios::beg);
    buffer = (ITS_CHAR*)malloc(length*sizeof(ITS_CHAR));
    outputStream.read(buffer, length);
    tmp = PPrint(rb,buffer);
    free (buffer);

    tmp = PPrint(rb, endText);
    CHECK_RETURN(tmp, ret);

    return (ret);
}

/*
 * Another helper.  Note that we take advantage of fixed
 * variable names.
 */
#define INVOKE_DECODE_AND_PRINT(t,v) \
    do                                                       \
    {                                                        \
        t v;                                                 \
        DecodeAndPrint(rb, tmp, ret,                         \
                       " --- Operation code: " #t " ---\n",  \
                       " --- End of parameter ---\n",        \
                       v, octets);                           \
    }                                                        \
    while (0)


/*
 * parameter printer
 */
extern "C"
int
ParamPrint(RINGBUF_Manager *rb, ITS_UINT *bCount,
           ITS_OCTET cType,
           ITS_OCTET opFamily, ITS_OCTET opCode,
           ITS_OCTET *pdu, ITS_USHORT clen)
{
    int tmp, ret = 0;
    vector<byte> array;
    Octets octets;
    ITS_OCTET *start = pdu;
    ITS_USHORT len = clen;

    /* dump raw bytes */
    tmp = PPrint(rb, " --- Component parameter raw data ---\n");
    do
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         " Param Data = %d\n",
                     *bCount, *pdu,
                     *pdu, *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        clen--;
        pdu++;
    }
    while (clen > 0);

    /* set up ASN decode */
    pdu = start;
    clen = len;
    array.erase(array.begin(), array.end());
    array.assign(pdu, pdu + clen);
    octets.SetArray(array);

    /* determine if we know how to print it */
    switch (cType)
    {
    case TCAP_PT_TC_INVOKE_CCITT:
        tmp = PPrint(rb, " --- Invoke parameter ---\n");
        CHECK_RETURN(tmp, ret);

        switch (opCode)
        {
        // gsmSCF activation ASE/Package.
        case OP_initialDP:
            INVOKE_DECODE_AND_PRINT(InitialDPArg, initialDP);
            break;

        // gsmSCF/gsmSRF activation of assist ASE/Package.
        case OP_assistRequestInstructions:
            INVOKE_DECODE_AND_PRINT(AssistRequestInstructionsArg,
                                    assistRequestInstructions);
            break;

        // Assist connection establishment ASE/Package. 
        case OP_establishTemporaryConnection:
            INVOKE_DECODE_AND_PRINT(EstablishTemporaryConnectionArg,
                                    establishTemporaryConnection);
            break;

        // Generic disconnect resource ASE/Package.
        case OP_disconnectForwardConnection:
            INVOKE_DECODE_AND_PRINT(DisconnectForwardConnectionWithArgumentArg,
                                    disconnectForwardConnectionWithArgument);
            break;

        // Non-assisted connection establishment ASE/Package. 
        case OP_connectToResource: 
            INVOKE_DECODE_AND_PRINT(ConnectToResourceArg, connectToResource);
            break;

        // Connect (elementary gsmSSF function) ASE/Package.
        case OP_connect:
            INVOKE_DECODE_AND_PRINT(ConnectArg, connect);
            break;

        // Call handling (elementary gsmSSF function) ASE/Package.
        case OP_releaseCall:
            INVOKE_DECODE_AND_PRINT(ReleaseCallArg, releaseCall);
            break;

        // BCSM Event handling ASE/Package.
        case OP_requestReportBCSMEvent:
            INVOKE_DECODE_AND_PRINT(RequestReportBCSMEventArg,
                                    requestReportBCSMEvent);
            break;

        case OP_eventReportBCSM:
            INVOKE_DECODE_AND_PRINT(EventReportBCSMArg, eventReportBCSM);
            break;

        // gsmSSF call processing ASE/Package.
        case OP_continue:
            // FIXME: Arg type?
            break;

        case OP_continueWithArgument:
            INVOKE_DECODE_AND_PRINT(ContinueWithArgumentArg, cont2);
            break;

        // Timer ASE/Package.
        case OP_resetTimer:
            INVOKE_DECODE_AND_PRINT(ResetTimerArg, resetTimer);
            break;

        // Billing ASE/Package.
        case OP_furnishChargingInformation:
            INVOKE_DECODE_AND_PRINT(FurnishChargingInformationArg,
                                    furnishChargingInformation);
            break;

        // Charging ASE/Package.
        case OP_applyCharging:
            INVOKE_DECODE_AND_PRINT(ApplyChargingArg, applyCharging);
            break;

        case OP_applyChargingReport:
            INVOKE_DECODE_AND_PRINT(ApplyChargingReportArg,
                                    applyChargingReport);
            break;

        // Traffic Management Package. 
        case OP_callGap:
            INVOKE_DECODE_AND_PRINT(CallGapArg, callGap);
            break;

        // Call report ASE/Package.
        case OP_callInformationReport:
            INVOKE_DECODE_AND_PRINT(CallInformationReportArg,
                                    callInformationReport);
            break;
        case OP_callInformationRequest:
            INVOKE_DECODE_AND_PRINT(CallInformationRequestArg,
                                    callInformationRequest);
            break;

        // Signalling control ASE/Package.
        case OP_sendChargingInformation:
            INVOKE_DECODE_AND_PRINT(SendChargingInformationArg,
                                    sendChargingInformation);
            break;

        // Specialized resource control ASE/Package.
        case OP_playAnnouncement:
            INVOKE_DECODE_AND_PRINT(PlayAnnouncementArg,
                                    playAnnouncement);
            break;
        case OP_promptAndCollectUserInformation:
            INVOKE_DECODE_AND_PRINT(PromptAndCollectUserInformationArg,
                                    promptAndCollectUserInformation);
            break;
        case OP_specializedResourceReport:
            INVOKE_DECODE_AND_PRINT(SpecializedResourceReportArg,
                                    specializedResourceReport);
            break;

        // Cancel ASE/Package.
        case OP_cancel:
            INVOKE_DECODE_AND_PRINT(CancelArg, cancel);
            break;

        // Activity Test ASE/Package.
        case OP_activityTest:
            // FIXME: arg type?
            break;

        // Sms Activation Package.
        case OP_initialDPSMS:
            INVOKE_DECODE_AND_PRINT(InitialDPSMSArg, initialDPSMS);
            break;

        // Sms Activity Test Package.
        //        case OP_activityTestSMS                  = 61,  

        // Sms Billing Package.
        case OP_furnishChargingInformationSMS:
            INVOKE_DECODE_AND_PRINT(FurnishChargingInformationSMSArg,
                                    furnishChargingInformationSMS);
            break;

        // Sms Connect Package.
        case OP_connectSMS:
            INVOKE_DECODE_AND_PRINT(ConnectSMSArg, connectSMS);
            break;

        // Sms Event Handling Package. 
        case OP_requestReportSMSEvent:
            INVOKE_DECODE_AND_PRINT(RequestReportSMSEventArg,
                                    requestReportSMSEvent);
            break;
        case OP_eventReportSMS:
            INVOKE_DECODE_AND_PRINT(EventReportSMSArg, eventReportSMS);
            break;

        // Sms Processing Package.
        case OP_continueSMS:
            // FIXME: arg type?
            break;

        // Sms Release Package.  
        case OP_releaseSMS:
            INVOKE_DECODE_AND_PRINT(ReleaseSMSArg, releaseSMS);
            break;

        // Sms Timer Package. 
        case OP_resetTimerSMS:
            INVOKE_DECODE_AND_PRINT(ResetTimerSMSArg, resetTimerSMS);
            break;

        // Gprs Activity Test Package.
        case OP_activityTestGPRS:
            // FIXME: arg type?
            break;

        // Gprs Charging Package.
        case OP_applyChargingGPRS:
            INVOKE_DECODE_AND_PRINT(ApplyChargingGPRSArg, applyChargingGPRS);
            break;
        case OP_applyChargingReportGPRS:
            INVOKE_DECODE_AND_PRINT(ApplyChargingReportGPRSArg,
                                    applyChargingReportGPRS);
            break;

        // Gprs Cancel Package.
        case OP_cancelGPRS:
            INVOKE_DECODE_AND_PRINT(CancelGPRSArg, cancelGPRS);
            break;

        // Gprs Connect Package.
        case OP_connectGPRS:
            INVOKE_DECODE_AND_PRINT(ConnectGPRSArg, connectGPRS);
            break;

        // Gprs Processing Package.
        case OP_continueGPRS:
            INVOKE_DECODE_AND_PRINT(ContinueGPRSArg, continueGPRS);
            break;

        // Gprs Exception Information Package.
        case OP_entityReleasedGPRS:
            INVOKE_DECODE_AND_PRINT(EntityReleasedGPRSArg, entityReleasedGPRS);
            break;

        // Gprs Billing Package.
        case OP_furnishChargingInformationGPRS:
            INVOKE_DECODE_AND_PRINT(FurnishChargingInformationGPRSArg,
                                    furnishChargingInformationGPRS);
            break;

        // Gprs Scf Activation Package.
        case OP_initialDPGPRS:
            INVOKE_DECODE_AND_PRINT(InitialDPGPRSArg, initialDPGPRS);
            break;

        // Gprs Release Package. 
        case OP_releaseGPRS:
            INVOKE_DECODE_AND_PRINT(ReleaseGPRSArg, releaseGPRS);
            break;

        // Gprs Event Handling Package.
        case OP_eventReportGPRS:
            INVOKE_DECODE_AND_PRINT(EventReportGPRSArg, eventReportGPRS);
            break;
        case OP_requestReportGPRSEvent:
            INVOKE_DECODE_AND_PRINT(RequestReportGPRSEventArg,
                                    requestReportGPRSEvent);
            break;

        // Gprs Timer Package.
        case OP_resetTimerGPRS:
            INVOKE_DECODE_AND_PRINT(ResetTimerGPRSArg, resetTimerGPRS);
            break;

        // Gprs Charge Advice Package.
        case OP_sendChargingInformationGPRS:
            INVOKE_DECODE_AND_PRINT(SendChargingInformationGPRSArg,
                                    sendChargingInformationGPRS);
            break;

        default:
            tmp = PPrint(rb, " --- Operation code: UNKNOWN ---\n");
            CHECK_RETURN(tmp, ret);
            tmp = PPrint(rb, " --- Decode not attempted ---\n");
            CHECK_RETURN(tmp, ret);
            break;
        }
        break;


    case TCAP_PT_TC_U_ERROR_CCITT:
        switch (opCode)
        {
        case ERR_canceled:
            tmp = PPrint(rb, " --- Error code: Canceled ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_cancelFailed:
            tmp = PPrint(rb, " --- Error code: CancelFailed ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_eTCFailed:
            tmp = PPrint(rb, " --- Error code: ETCFailed ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_improperCallerResponse:
            tmp = PPrint(rb, " --- Error code: ImproperCallerResponse ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_missingCustomerRecord:
            tmp = PPrint(rb, " --- Error code: MissingCustomerRecord ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_missingParameter:
            tmp = PPrint(rb, " --- Error code: MissingParameter ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_parameterOutOfRange:
            tmp = PPrint(rb, " --- Error code: ParameterOutOfRange ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_requestedInfoError:
            tmp = PPrint(rb, " --- Error code: RequestedInfoError ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_systemFailure:
            tmp = PPrint(rb, " --- Error code: SystemFailure ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_taskRefused:
            tmp = PPrint(rb, " --- Error code: TaskRefused ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unavailableResource:
            tmp = PPrint(rb, " --- Error code: UnavailableResource ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unexpectedComponentSequence:
            tmp = PPrint(rb, " --- Error code: UnexpectedComponentSequence ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unexpectedDataValue:
            tmp = PPrint(rb, " --- Error code: UnexpectedDataValue ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unexpectedParameter:
            tmp = PPrint(rb, " --- Error code: UnexpectedParameter ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unknownLegID:
            tmp = PPrint(rb, " --- Error code: UnknownLegID ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unknownPDPID:
            tmp = PPrint(rb, " --- Error code: UnknownPDPID ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unknownGPRSReference:
            tmp = PPrint(rb, " --- Error code: UnknownGPRSReference ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_overlappingDialogue:
            tmp = PPrint(rb, " --- Error code: OverlappingDialogue ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        default:
            tmp = PPrint(rb, " --- Error code: UNKNOWN ---\n");
            CHECK_RETURN(tmp, ret);
            tmp = PPrint(rb, " --- Decode not attempted ---\n");
            CHECK_RETURN(tmp, ret);
            break;
        }
        break;

    default:
        break;
    }

    return (ret);
}

