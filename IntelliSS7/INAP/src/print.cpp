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
//  ID: $Id: print.cpp,v 9.1.90.1 2013/02/18 05:56:50 jvikas Exp $
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <its.h>
#include <its_pprint.h>

#include <itu/tcap.h>

#include <inap_cpp.h>

#ident "$Id: print.cpp,v 9.1.90.1 2013/02/18 05:56:50 jvikas Exp $"

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

#include <inap_cs2_activate_service_filtering_arg.h>
#include <inap_cs2_analysed_information_arg.h>
#include <inap_cs2_analyse_information_arg.h>
#include <inap_cs2_apply_charging_arg.h>
#include <inap_cs2_apply_charging_report_arg.h>
#include <inap_cs2_assist_request_instructions_arg.h>
#include <inap_cs2_authorize_termination_arg.h>
#include <inap_cs2_call_gap_arg.h>
#include <inap_cs2_call_information_report_arg.h>
#include <inap_cs2_call_information_request_arg.h>
#include <inap_cs2_cancel_arg.h>
#include <inap_cs2_cancel_status_report_request_arg.h>
#include <inap_cs2_collected_information_arg.h>
#include <inap_cs2_collect_information_arg.h>
#include <inap_cs2_connect_arg.h>
#include <inap_cs2_connect_to_resource_arg.h>
#include <inap_cs2_continue_with_argument_arg.h>
#include <inap_cs2_disconnect_forward_connection_with_argument_arg.h>
#include <inap_cs2_disconnect_leg_arg.h>
#include <inap_cs2_entity_released_arg.h>
#include <inap_cs2_establish_temporary_connection_arg.h>
#include <inap_cs2_event_notification_charging_arg.h>
#include <inap_cs2_event_report_bcsm_arg.h>
#include <inap_cs2_event_report_facility_arg.h>
#include <inap_cs2_facility_selected_and_available_arg.h>
#include <inap_cs2_furnish_charging_information_arg.h>
#include <inap_cs2_hold_call_in_network_arg.h>
#include <inap_cs2_initial_dp_arg.h>
#include <inap_cs2_initiate_call_attempt_arg.h>
#include <inap_cs2_manage_trigger_data_arg.h>
#include <inap_cs2_manage_trigger_data_result_arg.h>
#include <inap_cs2_merge_call_segments_arg.h>
#include <inap_cs2_message_received_arg.h>
#include <inap_cs2_mid_call_arg.h>
#include <inap_cs2_move_call_segments_arg.h>
#include <inap_cs2_move_leg_arg.h>
#include <inap_cs2_o_abandon_arg.h>
#include <inap_cs2_o_answer_arg.h>
#include <inap_cs2_o_called_party_busy_arg.h>
#include <inap_cs2_o_disconnect_arg.h>
#include <inap_cs2_o_no_answer_arg.h>
#include <inap_cs2_origination_attempt_arg.h>
#include <inap_cs2_origination_attempt_authorized_arg.h>
#include <inap_cs2_o_suspended_arg.h>
#include <inap_cs2_play_announcement_arg.h>
#include <inap_cs2_prompt_and_collect_user_information_arg.h>
#include <inap_cs2_prompt_and_receive_message_arg.h>
#include <inap_cs2_received_information_arg.h>
#include <inap_cs2_reconnect_arg.h>
#include <inap_cs2_release_call_arg.h>
#include <inap_cs2_report_utsi_arg.h>
#include <inap_cs2_request_current_status_report_arg.h>
#include <inap_cs2_request_current_status_report_result_arg.h>
#include <inap_cs2_request_every_status_change_report_arg.h>
#include <inap_cs2_request_first_status_match_report_arg.h>
#include <inap_cs2_request_notification_charging_event_arg.h>
#include <inap_cs2_request_report_bcsm_event_arg.h>
#include <inap_cs2_request_report_facility_event_arg.h>
#include <inap_cs2_request_report_utsi_arg.h>
#include <inap_cs2_reset_timer_arg.h>
#include <inap_cs2_route_select_failure_arg.h>
#include <inap_cs2_select_facility_arg.h>
#include <inap_cs2_select_route_arg.h>
#include <inap_cs2_send_charging_information_arg.h>
#include <inap_cs2_send_facility_information_arg.h>
#include <inap_cs2_send_stui_arg.h>
#include <inap_cs2_service_filtering_response_arg.h>
#include <inap_cs2_split_leg_arg.h>
#include <inap_cs2_status_report_arg.h>
#include <inap_cs2_t_answer_arg.h>
#include <inap_cs2_t_busy_arg.h>
#include <inap_cs2_t_disconnect_arg.h>
#include <inap_cs2_term_attempt_authorized_arg.h>
#include <inap_cs2_termination_attempt_arg.h>
#include <inap_cs2_t_no_answer_arg.h>
#include <inap_cs2_t_suspended_arg.h>

/*
 * local namespaces in use.
 */
using namespace inap;
using namespace inap_cs2;
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
    std::stringstream outputStream;
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
#define PARAM_DECODE_AND_PRINT(t,v) \
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
/*    tmp = PPrint(rb, " --- Component parameter raw data ---\n");
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
    while (clen > 0);*/

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
        case OP_initialDP:
            PARAM_DECODE_AND_PRINT(InitialDPArg, initialDP);
            break;

        case OP_originationAttemptAuthorized:
            PARAM_DECODE_AND_PRINT(OriginationAttemptAuthorizedArg,
                                   originationAttemptAuthorized);
            break;

        case OP_collectedInformation:
            PARAM_DECODE_AND_PRINT(CollectedInformationArg, collectedInformation);
            break;

        case OP_analysedInformation:
            PARAM_DECODE_AND_PRINT(AnalysedInformationArg, analysedInformation);
            break;

        case OP_routeSelectFailure:
            PARAM_DECODE_AND_PRINT(RouteSelectFailureArg, routeSelectFailure);
            break;

        case OP_oCalledPartyBusy:
            PARAM_DECODE_AND_PRINT(OCalledPartyBusyArg, oCalledPartyBusy);
            break;

        case OP_oNoAnswer:
            PARAM_DECODE_AND_PRINT(ONoAnswerArg, oNoAnswer);
            break;

        case OP_oAnswer:
            PARAM_DECODE_AND_PRINT(OAnswerArg, oAnswer);
            break;

        case OP_oDisconnect:
            PARAM_DECODE_AND_PRINT(ODisconnectArg, oDisconnect);
            break;

        case OP_termAttemptAuthorized:
            PARAM_DECODE_AND_PRINT(TermAttemptAuthorizedArg, termAttemptAuthorized);
            break;

        case OP_tBusy:
            PARAM_DECODE_AND_PRINT(TBusyArg, tBusy);
            break;

        case OP_tNoAnswer:
            PARAM_DECODE_AND_PRINT(TNoAnswerArg, tNoAnswer);
            break;

        case OP_tAnswer:
            PARAM_DECODE_AND_PRINT(TAnswerArg, tAnswer);
            break;

        case OP_tDisconnect:
            PARAM_DECODE_AND_PRINT(TDisconnectArg, tDisconnect);
            break;

        case OP_oMidCall:
            PARAM_DECODE_AND_PRINT(MidCallArg, midCall);
            break;

        case OP_tMidCall:
            PARAM_DECODE_AND_PRINT(MidCallArg, midCallArg);
            break;

        case OP_assistRequestInstructions:
            PARAM_DECODE_AND_PRINT(AssistRequestInstructionsArg,
                                   assistRequestInstructions);
            break;

        case OP_establishTemporaryConnection:
            PARAM_DECODE_AND_PRINT(EstablishTemporaryConnectionArg,
                                   establishTemporaryConnection);
            break;

        case OP_disconnectForwardConnection:
            PARAM_DECODE_AND_PRINT(DisconnectForwardConnectionWithArgumentArg,
                                   disconnectForwardConnection);
            break;

        case OP_connectToResource:
            PARAM_DECODE_AND_PRINT(ConnectToResourceArg, connectToResource);
            break;

        case OP_connect:
            PARAM_DECODE_AND_PRINT(ConnectArg, connect);
            break;

        case OP_holdCallInNetwork:
            PARAM_DECODE_AND_PRINT(HoldCallInNetworkArg, holdCallInNetwork);
            break;

        case OP_releaseCall:
            PARAM_DECODE_AND_PRINT(ReleaseCallArg, releaseCall);
            break;

        case OP_requestReportBCSMEvent:
            PARAM_DECODE_AND_PRINT(RequestReportBCSMEventArg, requestReportBCSMEvent);
            break;

        case OP_eventReportBCSM:
            PARAM_DECODE_AND_PRINT(EventReportBCSMArg, eventReportBCSM);
            break;

        case OP_requestNotificationChargingEvent:
            PARAM_DECODE_AND_PRINT(RequestNotificationChargingEventArg,
                                   requestNotificationChargingEvent);
            break;

        case OP_eventNotificationCharging:
            PARAM_DECODE_AND_PRINT(EventNotificationChargingArg,
                                   eventNotificationCharging);
            break;

        case OP_collectInformation:
            PARAM_DECODE_AND_PRINT(CollectInformationArg, collectInformation);
            break;

        case OP_analyseInformation:
            PARAM_DECODE_AND_PRINT(AnalyseInformationArg, analyseInformation);
            break;

        case OP_selectRoute:
            PARAM_DECODE_AND_PRINT(SelectRouteArg, selectRoute);
            break;

        case OP_selectFacility:
            PARAM_DECODE_AND_PRINT(SelectFacilityArg, selectFacility);
            break;

        case OP_continue:
            PARAM_DECODE_AND_PRINT(ContinueWithArgumentArg, contin);
            break;

        case OP_initiateCallAttempt:
            PARAM_DECODE_AND_PRINT(InitiateCallAttemptArg, initiateCallAttempt);
            break;

        case OP_resetTimer:
            PARAM_DECODE_AND_PRINT(ResetTimerArg, resetTimer);
            break;

        case OP_furnishChargingInformation:
            PARAM_DECODE_AND_PRINT(FurnishChargingInformationArg,
                                   furnishChargingInformation);
            break;

        case OP_applyCharging:
            PARAM_DECODE_AND_PRINT(ApplyChargingArg, applyCharging);
            break;

        case OP_applyChargingReport:
            PARAM_DECODE_AND_PRINT(ApplyChargingReportArg, applyChargingReport);
            break;

        case OP_requestCurrentStatusReport:
            PARAM_DECODE_AND_PRINT(RequestCurrentStatusReportArg,
                                   requestCurrentStatusReport);
            break;

        case OP_requestEveryStatusChangeReport:
            PARAM_DECODE_AND_PRINT(RequestEveryStatusChangeReportArg,
                                   requestEveryStatusChangeReport);
            break;

        case OP_requestFirstStatusMatchReport:
            PARAM_DECODE_AND_PRINT(RequestFirstStatusMatchReportArg,
                                   requestFirstStatusMatchReport);
            break;

        case OP_statusReport:
            PARAM_DECODE_AND_PRINT(StatusReportArg, statusReport);
            break;

        case OP_callGap:
            PARAM_DECODE_AND_PRINT(CallGapArg, callGap);
            break;

        case OP_activateServiceFiltering:
            PARAM_DECODE_AND_PRINT(ActivateServiceFilteringArg,
                                   activateServiceFiltering);
            break;

        case OP_serviceFilteringResponse:
            PARAM_DECODE_AND_PRINT(ServiceFilteringResponseArg,
                                   serviceFilteringResponse);
            break;

        case OP_callInformationReport:
            PARAM_DECODE_AND_PRINT(CallInformationReportArg,
                                   callInformationReport);
            break;

        case OP_callInformationRequest:
            PARAM_DECODE_AND_PRINT(CallInformationRequestArg,
                                   callInformationRequest);
            break;

        case OP_sendChargingInformation:
            PARAM_DECODE_AND_PRINT(SendChargingInformationArg,
                                   sendChargingInformation);
            break;

        case OP_playAnnouncement:
            PARAM_DECODE_AND_PRINT(PlayAnnouncementArg, playAnnouncement);
            break;

        case OP_promptAndCollectUserInformation:
            PARAM_DECODE_AND_PRINT(PromptAndCollectUserInformationArg,
                                   pcui);
            break;

        case OP_specializedResourceReport:
            // FIXME: arg type?
            break;

        case OP_cancel:
            PARAM_DECODE_AND_PRINT(CancelArg, cancel);
            break;

        case OP_cancelStatusReportRequest:
            PARAM_DECODE_AND_PRINT(CancelStatusReportRequestArg,
                                   cancelStatusReportRequest);
            break;

        case OP_activityTest:
            // FIXME: arg type?
            break;

        case OP_requestCurrentStatusReportResult:
            PARAM_DECODE_AND_PRINT(RequestCurrentStatusReportResultArg,
                                   requestCurrentStatusReportResult);
            break;

        default:
            tmp = PPrint(rb, " --- Operation code: UNKNOWN ---\n");
            CHECK_RETURN(tmp, ret);
            tmp = PPrint(rb, " --- Decode not attempted ---\n");
            CHECK_RETURN(tmp, ret);
            break;
        }
        break;

    case TCAP_PT_TC_RESULT_L_CCITT:
    case TCAP_PT_TC_RESULT_NL_CCITT:
        tmp = PPrint(rb, " --- Result parameter ---\n");
        CHECK_RETURN(tmp, ret);

        switch (opCode)
        {
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
        case ERR_cancelled:
            tmp = PPrint(rb, " --- Error code: Cancelled ---\n");
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
            tmp = PPrint(rb, " --- Error code: UknownLegID ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unknownResource:
            tmp = PPrint(rb, " --- Error code: UnknownResource ---\n");
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
