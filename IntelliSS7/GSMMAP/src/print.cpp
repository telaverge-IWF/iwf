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
//  ID: $Id: print.cpp,v 9.1 2005/03/23 12:51:31 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <its.h>
#include <its_pprint.h>

#include <itu/tcap.h>

#include <map_cpp.h>

#ident "$Id: print.cpp,v 9.1 2005/03/23 12:51:31 cvsadmin Exp $"

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

#include <map_v7_activate_trace_mode_arg.h>
#include <map_v7_alert_service_centre_arg.h>
#include <map_v7_any_time_interrogation_arg.h>
#include <map_v7_any_time_modification_arg.h>
#include <map_v7_any_time_subscription_interrogation_arg.h>
#include <map_v7_authentication_failure_report_arg.h>
#include <map_v7_cancel_location_arg.h>
#include <map_v7_deactivate_trace_mode_arg.h>
#include <map_v7_delete_subscriber_data_arg.h>
#include <map_v7_erase_cc_entry_arg.h>
#include <map_v7_failure_report_arg.h>
#include <map_v7_forward_access_signalling_arg.h>
#include <map_v7_forward_group_call_signalling_arg.h>
#include <map_v7_inform_service_centre_arg.h>
#include <map_v7_insert_subscriber_data_arg.h>
#include <map_v7_ist_alert_arg.h>
#include <map_v7_ist_command_arg.h>
#include <map_v7_mo_forward_sm_arg.h>
#include <map_v7_mt_forward_sm_arg.h>
#include <map_v7_note_mm_event_arg.h>
#include <map_v7_note_ms_present_for_gprs_arg.h>
#include <map_v7_note_subscriber_data_modified_arg.h>
#include <map_v7_prepare_group_call_arg.h>
#include <map_v7_prepare_ho_arg.h>
#include <map_v7_prepare_subsequent_ho_arg.h>
#include <map_v7_process_access_signalling_arg.h>
#include <map_v7_process_group_call_signalling_arg.h>
#include <map_v7_provide_roaming_number_arg.h>
#include <map_v7_provide_siwfs_number_arg.h>
#include <map_v7_provide_subscriber_info_arg.h>
#include <map_v7_provide_subscriber_location_arg.h>
#include <map_v7_purge_ms_arg.h>
#include <map_v7_ready_for_sm_arg.h>
#include <map_v7_register_cc_entry_arg.h>
#include <map_v7_register_ss_arg.h>
#include <map_v7_remote_user_free_arg.h>
#include <map_v7_report_sm_delivery_status_arg.h>
#include <map_v7_reset_arg.h>
#include <map_v7_restore_data_arg.h>
#include <map_v7_resume_call_handling_arg.h>
#include <map_v7_routing_info_for_lcs_arg.h>
#include <map_v7_routing_info_for_sm_arg.h>
#include <map_v7_secure_transport_arg.h>
#include <map_v7_send_authentication_info_arg.h>
#include <map_v7_send_end_signal_arg.h>
#include <map_v7_send_group_call_end_signal_arg.h>
#include <map_v7_send_identification_arg.h>
#include <map_v7_send_routing_info_arg.h>
#include <map_v7_send_routing_info_for_gprs_arg.h>
#include <map_v7_set_reporting_state_arg.h>
#include <map_v7_siwfs_signalling_modify_arg.h>
#include <map_v7_ss_invocation_notification_arg.h>
#include <map_v7_status_report_arg.h>
#include <map_v7_subscriber_location_report_arg.h>
#include <map_v7_update_gprs_location_arg.h>
#include <map_v7_update_location_arg.h>
#include <map_v7_ussd_arg.h>
#include <map_v7_activate_trace_mode_res.h>
#include <map_v7_any_time_interrogation_res.h>
#include <map_v7_any_time_modification_res.h>
#include <map_v7_any_time_subscription_interrogation_res.h>
#include <map_v7_authentication_failure_report_res.h>
#include <map_v7_cancel_location_res.h>
#include <map_v7_deactivate_trace_mode_res.h>
#include <map_v7_delete_subscriber_data_res.h>
#include <map_v7_erase_cc_entry_res.h>
#include <map_v7_failure_report_res.h>
#include <map_v7_insert_subscriber_data_res.h>
#include <map_v7_interrogate_ss_res.h>
#include <map_v7_ist_alert_res.h>
#include <map_v7_ist_command_res.h>
#include <map_v7_mo_forward_sm_res.h>
#include <map_v7_mt_forward_sm_res.h>
#include <map_v7_note_mm_event_res.h>
#include <map_v7_note_ms_present_for_gprs_res.h>
#include <map_v7_note_subscriber_data_modified_res.h>
#include <map_v7_prepare_group_call_res.h>
#include <map_v7_prepare_ho_res.h>
#include <map_v7_prepare_subsequent_ho_res.h>
#include <map_v7_provide_roaming_number_res.h>
#include <map_v7_provide_siwfs_number_res.h>
#include <map_v7_provide_subscriber_info_res.h>
#include <map_v7_provide_subscriber_location_res.h>
#include <map_v7_purge_ms_res.h>
#include <map_v7_ready_for_sm_res.h>
#include <map_v7_register_cc_entry_res.h>
#include <map_v7_remote_user_free_res.h>
#include <map_v7_report_sm_delivery_status_res.h>
#include <map_v7_restore_data_res.h>
#include <map_v7_resume_call_handling_res.h>
#include <map_v7_routing_info_for_lcs_res.h>
#include <map_v7_routing_info_for_sm_res.h>
#include <map_v7_secure_transport_res.h>
#include <map_v7_send_authentication_info_res.h>
#include <map_v7_send_end_signal_res.h>
#include <map_v7_send_group_call_end_signal_res.h>
#include <map_v7_send_identification_res.h>
#include <map_v7_send_routing_info_for_gprs_res.h>
#include <map_v7_send_routing_info_res.h>
#include <map_v7_set_reporting_state_res.h>
#include <map_v7_siwfs_signalling_modify_res.h>
#include <map_v7_ss_invocation_notification_res.h>
#include <map_v7_status_report_res.h>
#include <map_v7_subscriber_location_report_res.h>
#include <map_v7_update_gprs_location_res.h>
#include <map_v7_update_location_res.h>
#include <map_v7_secure_transport_error_param.h>

/*
 * local namespaces in use.
 */
using namespace map_common;
using namespace map_v7;
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
        // Location registration operation codes.
        case OP_updateLocation:
            PARAM_DECODE_AND_PRINT(UpdateLocationArg, updateLocation);
            break;

        case OP_cancelLocation:
            PARAM_DECODE_AND_PRINT(CancelLocationArg, cancelLocation);
            break;

        case OP_purgeMS:
            PARAM_DECODE_AND_PRINT(PurgeMS_Arg, purgeMS);
            break;

        case OP_sendIdentification:
            PARAM_DECODE_AND_PRINT(SendIdentificationArg, sendIdentification);
            break;

        // Handover operation codes.
        case OP_prepareHandover:
            PARAM_DECODE_AND_PRINT(PrepareHO_Arg, prepareHandover);
            break;

        case OP_sendEndSignal:
            PARAM_DECODE_AND_PRINT(SendEndSignal_Arg, sendEndSignal);
            break;

        case OP_processAccessSignalling:
            PARAM_DECODE_AND_PRINT(ProcessAccessSignalling_Arg, provideAccessSignalling);
            break;

        case OP_forwardAccessSignalling:
            PARAM_DECODE_AND_PRINT(ForwardAccessSignalling_Arg, forwardAccessSignalling);
            break;

        case OP_prepareSubsequentHandover:
            PARAM_DECODE_AND_PRINT(PrepareSubsequentHO_Arg, prepareSubsequentHandover);
            break;

        // Authentication operation codes.
        case OP_sendAuthenticationInfo:
            PARAM_DECODE_AND_PRINT(SendAuthenticationInfoArg, sendAuthenticationInfo);
            break;

        case OP_authenticationFailureReport:
            PARAM_DECODE_AND_PRINT(PrepareSubsequentHO_Arg, prepareSubsequentHandover);
            break;

        // IMEI MANAGEMENT operation codes.
        case OP_checkIMEI:
            break;

        // Subscriber management operation codes.
        case OP_insertSubscriberData:
            PARAM_DECODE_AND_PRINT(InsertSubscriberDataArg, insertSubscriberData);
            break;

        case OP_deleteSubscriberData:
            PARAM_DECODE_AND_PRINT(DeleteSubscriberDataArg, deleteSubscriberData);
            break;


        // Fault recovery operation codes.
        case OP_reset:
            PARAM_DECODE_AND_PRINT(ResetArg, reset);
            break;

        case OP_forwardCheckSS_Indication:
            // FIXME: arg type?
            break;

        case OP_restoreData:
            PARAM_DECODE_AND_PRINT(RestoreDataArg, restoreData);
            break;

        // Operation and maintenance operation codes.
        case OP_activateTraceMode:
            PARAM_DECODE_AND_PRINT(ActivateTraceModeArg, activateTraceMode);
            break;

        case OP_deactivateTraceMode:
            PARAM_DECODE_AND_PRINT(DeactivateTraceModeArg, deactivateTraceMode);
            break;

        case OP_sendIMSI:
            // FIXME: arg type?
            break;

        // Call handling operation codes.
        case OP_sendRoutingInfo:
            PARAM_DECODE_AND_PRINT(SendRoutingInfoArg, sendRoutingInfo);
            break;

        case OP_provideRoamingNumber:
            PARAM_DECODE_AND_PRINT(ProvideRoamingNumberArg, provideRoamingNumber);
            break;

        case OP_resumeCallHandling:
            PARAM_DECODE_AND_PRINT(ResumeCallHandlingArg, resumeCallHandling);
            break;

        case OP_provideSIWFSNumber:
            PARAM_DECODE_AND_PRINT(ProvideSIWFSNumberArg, provideSIWFSNumber);
            break;

        case OP_sIWFSSignallingModify:
            PARAM_DECODE_AND_PRINT(SIWFSSignallingModifyArg, sIWFSSignallingModify);
            break;

        case OP_setReportingState:
            PARAM_DECODE_AND_PRINT(SetReportingStateArg, setReportingState);
            break;

        case OP_statusReport:
            PARAM_DECODE_AND_PRINT(StatusReportArg, statusReport);
            break;

        case OP_remoteUserFree:
            PARAM_DECODE_AND_PRINT(RemoteUserFreeArg, remoteUserFree);
            break;

        case OP_istAlert:
            PARAM_DECODE_AND_PRINT(IST_AlertArg, istAlert);
            break;

        case OP_istCommand:
            PARAM_DECODE_AND_PRINT(IST_CommandArg, istCommand);
            break;


        // Supplementary service handling operation codes.
        case OP_registerSS:
            PARAM_DECODE_AND_PRINT(RegisterSS_Arg, registerSS);
            break;

        case OP_eraseSS:
            // not impl: PARAM_DECODE_AND_PRINT(EraseSS_Arg, eraseSS);
            break;

        case OP_activateSS:
            // not impl: PARAM_DECODE_AND_PRINT(ActivateSS_Arg, activateSS);
            break;

        case OP_deactivateSS:
            // not impl: PARAM_DECODE_AND_PRINT(DeactivateSS_Arg, deactivateSS);
            break;

        case OP_interrogateSS:
            // not impl: PARAM_DECODE_AND_PRINT(InterrogateSS_Arg, interrogateSS);
            break;

        case OP_processUnstructuredSS_Request:
            // not impl: PARAM_DECODE_AND_PRINT(ProcessUnstructuredSS_Request_Arg,
            // not impl:                        processUnstructuredSS_Request);
            break;

        case OP_unstructuredSS_Request:
            // not impl: PARAM_DECODE_AND_PRINT(UnstructuredSS_Request_Arg,
            // not impl:                        unstructuredSS_Request);
            break;

        case OP_unstructuredSS_Notify:
            // not impl: PARAM_DECODE_AND_PRINT(UnstructuredSS_Notify_Arg,
            // not impl:                        unstructuredSS_Notify);
            break;

        case OP_registerPassword:
            // not impl: PARAM_DECODE_AND_PRINT(RegisterPasswordArg, registerPassword);
            break;

        case OP_getPassword:
            // not impl: PARAM_DECODE_AND_PRINT(GetPasswordArg, getPassword);
            break;

        case OP_registerCC_Entry:
            // not impl: PARAM_DECODE_AND_PRINT(RegisterCC_Entry_Arg, registerCC_Entry);
            break;

        case OP_eraseCC_Entry:
            // not impl: PARAM_DECODE_AND_PRINT(EraseCC_Entry_Arg, eraseCC_Entry);
            break;

        // Short message service operation codes.
        case OP_sendRoutingInfoForSM:
            PARAM_DECODE_AND_PRINT(RoutingInfoForSM_Arg, routingInfoForSM);
            break;

        case OP_mo_forwardSM:
            PARAM_DECODE_AND_PRINT(MO_ForwardSM_Arg, mO_ForwardSM);
            break;

        case OP_mt_forwardSM:
            PARAM_DECODE_AND_PRINT(MT_ForwardSM_Arg, mT_ForwardSM);
            break;

        case OP_reportSM_DeliveryStatus:
            PARAM_DECODE_AND_PRINT(ReportSM_DeliveryStatusArg, reportSM_DeliveryStatus);
            break;

        case OP_informServiceCentre:
            PARAM_DECODE_AND_PRINT(InformServiceCentreArg, informServiceCentre);
            break;

        case OP_alertServiceCentre:
            PARAM_DECODE_AND_PRINT(AlertServiceCentreArg, alertServiceCentre);
            break;

        case OP_readyForSM:
            PARAM_DECODE_AND_PRINT(ReadyForSM_Arg, readyForSM);
            break;

        // Provide subscriber info operation codes,
        case OP_provideSubscriberInfo:
            PARAM_DECODE_AND_PRINT(ProvideSubscriberInfoArg, provideSubscriberInfo);
            break;

        // Any time interrogation operation codes.
        case OP_anyTimeInterrogation:
            PARAM_DECODE_AND_PRINT(AnyTimeInterrogationArg, anyTimeInterrogation);
            break;

        // Any time information handling operation codes.
        case OP_anyTimeSubscriptionInterrogation:
            PARAM_DECODE_AND_PRINT(AnyTimeSubscriptionInterrogationArg,
                                   anyTimeSubscriptionInterrogation);
            break;

        case OP_anyTimeModification:
            PARAM_DECODE_AND_PRINT(AnyTimeModificationArg, anyTimeModification);
            break;

        // Subscriber data modification notification operation codes.
        case OP_noteSubscriberDataModified:
            PARAM_DECODE_AND_PRINT(NoteSubscriberDataModifiedArg, noteSubscriberDataModified);
            break;

        // Supplementary service invocation notification operation codes.
        case OP_ss_InvocationNotification:
            PARAM_DECODE_AND_PRINT(SS_InvocationNotificationArg, sSInvocationNotification);
            break;


        // Group Call operation codes.
        case OP_prepareGroupCall:
            PARAM_DECODE_AND_PRINT(PrepareGroupCallArg, prepareGroupCall);
            break;

        case OP_sendGroupCallEndSignal:
            PARAM_DECODE_AND_PRINT(SendGroupCallEndSignalArg, sendGroupCallEndSignal);
            break;

        case OP_processGroupCallSignalling:
            PARAM_DECODE_AND_PRINT(ProcessGroupCallSignallingArg, processGroupCallSignalling);
            break;

        case OP_forwardGroupCallSignalling:
            PARAM_DECODE_AND_PRINT(ForwardGroupCallSignallingArg, forwardGroupCallSignalling);
            break;

        // Gprs location updating operation codes.
        case OP_updateGprsLocation:
            PARAM_DECODE_AND_PRINT(UpdateGprsLocationArg, updateGPRSLocation);
            break;

        // Gprs location information retrieval operation codes.
        case OP_sendRoutingInfoForGprs:
            PARAM_DECODE_AND_PRINT(SendRoutingInfoForGprsArg, routingInfoForGPRS);
            break;

        // Failure reporting operation codes.
        case OP_failureReport:
            PARAM_DECODE_AND_PRINT(FailureReportArg, failureReport);
            break;

        // GPRS notification operation codes.
        case OP_noteMsPresentForGprs:
            PARAM_DECODE_AND_PRINT(NoteMsPresentForGprsArg, noteMSPresentForGPRS);
            break;

        // Location service operation codes.
        case OP_provideSubscriberLocation:
            PARAM_DECODE_AND_PRINT(ProvideSubscriberLocation_Arg, provideSubscriberLocation);
            break;

        case OP_sendRoutingInfoForLCS:
            PARAM_DECODE_AND_PRINT(RoutingInfoForLCS_Arg, routingInfoForLCS);
            break;

        case OP_subscriberLocationReport:
            PARAM_DECODE_AND_PRINT(SubscriberLocationReport_Arg, subscriberLocationReport);
            break;

        // Mobility Management operation codes.
        case OP_noteMM_Event:
            PARAM_DECODE_AND_PRINT(NoteMM_EventArg, noteMMEvent);
            break;


        // Secure transport operation codes.
        case OP_secureTransportClass1:
        case OP_secureTransportClass2:
        case OP_secureTransportClass3:
        case OP_secureTransportClass4:
            PARAM_DECODE_AND_PRINT(SecureTransportArg, secureTransportArg);
            break;

        // V1 operation codes (not defined by V2 and V4).   
#if 0
        case OP_updateLocationArea:
        case OP_detachIMSI:
        case OP_attachIMSI:
        case OP_sendParameters:
        case OP_invokeSS:
        case OP_forwardSsNotification:
        case OP_processUnstructuredSsData:
        case OP_sendInfoForIncomingCall:
        case OP_sendInfoForOutgoingCall:
        case OP_completeCall:
        case OP_connectToFollowingAddress:
        case OP_processCallWaiting:
        case OP_page:
        case OP_searchForMobileSubscriber:
        case OP_performHandover:
        case OP_performSubsequentHandover:
        case OP_allocateHandoverNumber:
        case OP_sendHandoverReport:
        case OP_noteInternalHandover:
        case OP_registerChargingInformation:
        case OP_authenticate:
        case OP_provideIMSI:
        case OP_forwardNewTMSI:
        case OP_setCipheringMode:
        case OP_forwardShortMessage:
        case OP_setMessageWaitingData:
        case OP_noteMSPresent:
        case OP_alertServiceCenter:
        case OP_traceSubscriberActivity:
        case OP_processAccessRequest:
        case OP_beginSubscriberActivity:
            break;
#endif
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
        // Location registration operation codes.
        case OP_updateLocation:
            PARAM_DECODE_AND_PRINT(UpdateLocationRes, updateLocation);
            break;

        case OP_cancelLocation:
            PARAM_DECODE_AND_PRINT(CancelLocationRes, cancelLocation);
            break;

        case OP_purgeMS:
            PARAM_DECODE_AND_PRINT(PurgeMS_Res, purgeMS);
            break;

        case OP_sendIdentification:
            PARAM_DECODE_AND_PRINT(SendIdentificationRes, sendIdentification);
            break;

        // Handover operation codes.
        case OP_prepareHandover:
            PARAM_DECODE_AND_PRINT(PrepareHO_Res, prepareHandover);
            break;

        case OP_sendEndSignal:
            PARAM_DECODE_AND_PRINT(SendEndSignal_Res, sendEndSignal);
            break;

        case OP_processAccessSignalling:
            // FIXME: param type?
            break;

        case OP_forwardAccessSignalling:
            // FIXME: param type?
            break;

        case OP_prepareSubsequentHandover:
            PARAM_DECODE_AND_PRINT(PrepareSubsequentHO_Res, prepareSubsequentHandover);
            break;

        // Authentication operation codes.
        case OP_sendAuthenticationInfo:
            PARAM_DECODE_AND_PRINT(SendAuthenticationInfoRes, sendAuthenticationInfo);
            break;

        case OP_authenticationFailureReport:
            PARAM_DECODE_AND_PRINT(PrepareSubsequentHO_Res, prepareSubsequentHandover);
            break;

        // IMEI MANAGEMENT operation codes.
        case OP_checkIMEI:
            break;

        // Subscriber management operation codes.
        case OP_insertSubscriberData:
            PARAM_DECODE_AND_PRINT(InsertSubscriberDataRes, insertSubscriberData);
            break;

        case OP_deleteSubscriberData:
            PARAM_DECODE_AND_PRINT(DeleteSubscriberDataRes, deleteSubscriberData);
            break;


        // Fault recovery operation codes.
        case OP_reset:
            // FIXME: param type?
            break;

        case OP_forwardCheckSS_Indication:
            // FIXME: arg type?
            break;

        case OP_restoreData:
            PARAM_DECODE_AND_PRINT(RestoreDataRes, restoreData);
            break;

        // Operation and maintenance operation codes.
        case OP_activateTraceMode:
            PARAM_DECODE_AND_PRINT(ActivateTraceModeRes, activateTraceMode);
            break;

        case OP_deactivateTraceMode:
            PARAM_DECODE_AND_PRINT(DeactivateTraceModeRes, deactivateTraceMode);
            break;

        case OP_sendIMSI:
            // FIXME: arg type?
            break;

        // Call handling operation codes.
        case OP_sendRoutingInfo:
            PARAM_DECODE_AND_PRINT(SendRoutingInfoRes, sendRoutingInfo);
            break;

        case OP_provideRoamingNumber:
            PARAM_DECODE_AND_PRINT(ProvideRoamingNumberRes, provideRoamingNumber);
            break;

        case OP_resumeCallHandling:
            PARAM_DECODE_AND_PRINT(ResumeCallHandlingRes, resumeCallHandling);
            break;

        case OP_provideSIWFSNumber:
            PARAM_DECODE_AND_PRINT(ProvideSIWFSNumberRes, provideSIWFSNumber);
            break;

        case OP_sIWFSSignallingModify:
            PARAM_DECODE_AND_PRINT(SIWFSSignallingModifyRes, sIWFSSignallingModify);
            break;

        case OP_setReportingState:
            PARAM_DECODE_AND_PRINT(SetReportingStateRes, setReportingState);
            break;

        case OP_statusReport:
            PARAM_DECODE_AND_PRINT(StatusReportRes, statusReport);
            break;

        case OP_remoteUserFree:
            PARAM_DECODE_AND_PRINT(RemoteUserFreeRes, remoteUserFree);
            break;

        case OP_istAlert:
            PARAM_DECODE_AND_PRINT(IST_AlertRes, istAlert);
            break;

        case OP_istCommand:
            PARAM_DECODE_AND_PRINT(IST_CommandRes, istCommand);
            break;


        // Supplementary service handling operation codes.
        case OP_registerSS:
            // FIXME: param type?
            break;

        case OP_eraseSS:
            // not impl: PARAM_DECODE_AND_PRINT(EraseSS_Res, eraseSS);
            break;

        case OP_activateSS:
            // not impl: PARAM_DECODE_AND_PRINT(ActivateSS_Res, activateSS);
            break;

        case OP_deactivateSS:
            // not impl: PARAM_DECODE_AND_PRINT(DeactivateSS_Res, deactivateSS);
            break;

        case OP_interrogateSS:
            // not impl: PARAM_DECODE_AND_PRINT(InterrogateSS_Res, interrogateSS);
            break;

        case OP_processUnstructuredSS_Request:
            // not impl: PARAM_DECODE_AND_PRINT(ProcessUnstructuredSS_Request_Res,
            // not impl:                        processUnstructuredSS_Request);
            break;

        case OP_unstructuredSS_Request:
            // not impl: PARAM_DECODE_AND_PRINT(UnstructuredSS_Request_Res,
            // not impl:                        unstructuredSS_Request);
            break;

        case OP_unstructuredSS_Notify:
            // not impl: PARAM_DECODE_AND_PRINT(UnstructuredSS_Notify_Res,
            // not impl:                        unstructuredSS_Notify);
            break;

        case OP_registerPassword:
            // not impl: PARAM_DECODE_AND_PRINT(RegisterPasswordRes, registerPassword);
            break;

        case OP_getPassword:
            // not impl: PARAM_DECODE_AND_PRINT(GetPasswordRes, getPassword);
            break;

        case OP_registerCC_Entry:
            // not impl: PARAM_DECODE_AND_PRINT(RegisterCC_Entry_Res, registerCC_Entry);
            break;

        case OP_eraseCC_Entry:
            // not impl: PARAM_DECODE_AND_PRINT(EraseCC_Entry_Res, eraseCC_Entry);
            break;

        // Short message service operation codes.
        case OP_sendRoutingInfoForSM:
            PARAM_DECODE_AND_PRINT(RoutingInfoForSM_Res, routingInfoForSM);
            break;

        case OP_mo_forwardSM:
            PARAM_DECODE_AND_PRINT(MO_ForwardSM_Res, mO_ForwardSM);
            break;

        case OP_mt_forwardSM:
            PARAM_DECODE_AND_PRINT(MT_ForwardSM_Res, mT_ForwardSM);
            break;

        case OP_reportSM_DeliveryStatus:
            PARAM_DECODE_AND_PRINT(ReportSM_DeliveryStatusRes, reportSM_DeliveryStatus);
            break;

        case OP_informServiceCentre:
            // FIXME: param type?
            break;

        case OP_alertServiceCentre:
            // FIXME: param type?
            break;

        case OP_readyForSM:
            PARAM_DECODE_AND_PRINT(ReadyForSM_Res, readyForSM);
            break;

        // Provide subscriber info operation codes,
        case OP_provideSubscriberInfo:
            PARAM_DECODE_AND_PRINT(ProvideSubscriberInfoRes, provideSubscriberInfo);
            break;

        // Any time interrogation operation codes.
        case OP_anyTimeInterrogation:
            PARAM_DECODE_AND_PRINT(AnyTimeInterrogationRes, anyTimeInterrogation);
            break;

        // Any time information handling operation codes.
        case OP_anyTimeSubscriptionInterrogation:
            PARAM_DECODE_AND_PRINT(AnyTimeSubscriptionInterrogationRes,
                                   anyTimeSubscriptionInterrogation);
            break;

        case OP_anyTimeModification:
            PARAM_DECODE_AND_PRINT(AnyTimeModificationRes, anyTimeModification);
            break;

        // Subscriber data modification notification operation codes.
        case OP_noteSubscriberDataModified:
            PARAM_DECODE_AND_PRINT(NoteSubscriberDataModifiedRes, noteSubscriberDataModified);
            break;

        // Supplementary service invocation notification operation codes.
        case OP_ss_InvocationNotification:
            PARAM_DECODE_AND_PRINT(SS_InvocationNotificationRes, sSInvocationNotification);
            break;


        // Group Call operation codes.
        case OP_prepareGroupCall:
            PARAM_DECODE_AND_PRINT(PrepareGroupCallRes, prepareGroupCall);
            break;

        case OP_sendGroupCallEndSignal:
            PARAM_DECODE_AND_PRINT(SendGroupCallEndSignalRes, sendGroupCallEndSignal);
            break;

        case OP_processGroupCallSignalling:
            // FIXME: param type?
            break;

        case OP_forwardGroupCallSignalling:
            // FIXME: param type?
            break;

        // Gprs location updating operation codes.
        case OP_updateGprsLocation:
            PARAM_DECODE_AND_PRINT(UpdateGprsLocationRes, updateGPRSLocation);
            break;

        // Gprs location information retrieval operation codes.
        case OP_sendRoutingInfoForGprs:
            PARAM_DECODE_AND_PRINT(SendRoutingInfoForGprsRes, routingInfoForGPRS);
            break;

        // Failure reporting operation codes.
        case OP_failureReport:
            PARAM_DECODE_AND_PRINT(FailureReportRes, failureReport);
            break;

        // GPRS notification operation codes.
        case OP_noteMsPresentForGprs:
            PARAM_DECODE_AND_PRINT(NoteMsPresentForGprsRes, noteMSPresentForGPRS);
            break;

        // Location service operation codes.
        case OP_provideSubscriberLocation:
            PARAM_DECODE_AND_PRINT(ProvideSubscriberLocation_Res, provideSubscriberLocation);
            break;

        case OP_sendRoutingInfoForLCS:
            PARAM_DECODE_AND_PRINT(RoutingInfoForLCS_Res, routingInfoForLCS);
            break;

        case OP_subscriberLocationReport:
            PARAM_DECODE_AND_PRINT(SubscriberLocationReport_Res, subscriberLocationReport);
            break;

        // Mobility Management operation codes.
        case OP_noteMM_Event:
            PARAM_DECODE_AND_PRINT(NoteMM_EventRes, noteMMEvent);
            break;


        // Secure transport operation codes.
        case OP_secureTransportClass1:
        case OP_secureTransportClass2:
        case OP_secureTransportClass3:
        case OP_secureTransportClass4:
            PARAM_DECODE_AND_PRINT(SecureTransportRes, secureTransport);
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
        // Generic error codes.
        case ERR_systemFailure:
            tmp = PPrint(rb, " --- Error code: SystemFailure ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_dataMissing:
            tmp = PPrint(rb, " --- Error code: DataMissing ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unexpectedDataValue:
            tmp = PPrint(rb, " --- Error code: UnexpectedDataValue ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_facilityNotSupported:
            tmp = PPrint(rb, " --- Error code: FacilityNotSupported ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_incompatibleTerminal:
            tmp = PPrint(rb, " --- Error code: IncompatibleTerminal ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_resourceLimitation:
            tmp = PPrint(rb, " --- Error code: ResourceLimitation ---\n");
            CHECK_RETURN(tmp, ret);
            break;


        // Identification and numbering error codes.
        case ERR_unknownSubscriber:
            tmp = PPrint(rb, " --- Error code: UnknownSubscriber ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_numberChanged:
            tmp = PPrint(rb, " --- Error code: NumberChanged ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unknownMSC:
            tmp = PPrint(rb, " --- Error code: UnknownMSC ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unidentifiedSubscriber:
            tmp = PPrint(rb, " --- Error code: UnidentifiedSubscriber ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unknownEquipment:
            tmp = PPrint(rb, " --- Error code: UnknownEquipment ---\n");
            CHECK_RETURN(tmp, ret);
            break;


        // Subscription error codes.
        case ERR_roamingNotAllowed:
            tmp = PPrint(rb, " --- Error code: RoamingNotAllowed ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_illegalSubscriber:
            tmp = PPrint(rb, " --- Error code: IllegalSubscriber ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_illegalEquipment:
            tmp = PPrint(rb, " --- Error code: IllegalEquipment ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_bearerServiceNotProvisioned:
            tmp = PPrint(rb, " --- Error code: BearerServiceNotProvisioned ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_teleserviceNotProvisioned:
            tmp = PPrint(rb, " --- Error code: TeleserviceNotProvisioned ---\n");
            CHECK_RETURN(tmp, ret);
            break;


        // Handover error codes.
        case ERR_noHandoverNumberAvailable:
            tmp = PPrint(rb, " --- Error code: NoHandoverNumberAvailable ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_subsequentHandoverFailure:
            tmp = PPrint(rb, " --- Error code: SubsequentHandoverFailure ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_targetCellOutsideGroupCallArea:
            tmp = PPrint(rb, " --- Error code: TargetOutsideGroupCallArea ---\n");
            CHECK_RETURN(tmp, ret);
            break;


        // Operation and maintenance error codes.
        case ERR_tracingBufferFull:
            tmp = PPrint(rb, " --- Error code: TracingBufferFull ---\n");
            CHECK_RETURN(tmp, ret);
            break;


        // Call handling error codes.
        case ERR_noRoamingNumberAvailable:
            tmp = PPrint(rb, " --- Error code: NoRoamingNumberAvailable ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_absentSubscriber:
            tmp = PPrint(rb, " --- Error code: AbsentSubscriber ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_busySubscriber:
            tmp = PPrint(rb, " --- Error code: BusySubscriber ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_noSubscriberReply:
            tmp = PPrint(rb, " --- Error code: NoSubscriberReply ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_callBarred:
            tmp = PPrint(rb, " --- Error code: CallBarred ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_forwardingFailed:
            tmp = PPrint(rb, " --- Error code: ForwardingFailed ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_or_NotAllowed:
            tmp = PPrint(rb, " --- Error code: OrNotAllowed ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_forwardingViolation:
            tmp = PPrint(rb, " --- Error code: ForwardingViolation ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_cug_Reject:
            tmp = PPrint(rb, " --- Error code: CUGReject ---\n");
            CHECK_RETURN(tmp, ret);
            break;


        // Any time interrogation error codes.
        case ERR_ati_NotAllowed:
            tmp = PPrint(rb, " --- Error code: ATINotAllowed ---\n");
            CHECK_RETURN(tmp, ret);
            break;


        // Any time information handling error codes.
        case ERR_atsi_NotAllowed:
            tmp = PPrint(rb, " --- Error code: ATSINotAllowed ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_atm_NotAllowed:
            tmp = PPrint(rb, " --- Error code: ATMNotAllowed ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_informationNotAvailable:
            tmp = PPrint(rb, " --- Error code: InformationNotAvailable ---\n");
            CHECK_RETURN(tmp, ret);
            break;


        // Group Call error codes
        case ERR_noGroupCallNumberAvailable:
            tmp = PPrint(rb, " --- Error code: NoGroupCallNumberAvailable ---\n");
            CHECK_RETURN(tmp, ret);
            break;


        // Supplementary service error codes.
        case ERR_illegalSS_Operation:
            tmp = PPrint(rb, " --- Error code: IllegalSSOperation ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_ss_ErrorStatus:
            tmp = PPrint(rb, " --- Error code: SSErrorStatus ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_ss_NotAvailable:
            tmp = PPrint(rb, " --- Error code: SSNotAvailable ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_ss_SubscriptionViolation:
            tmp = PPrint(rb, " --- Error code: SSSubscriptionViolation ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_ss_Incompatibility:
            tmp = PPrint(rb, " --- Error code: SSIncompatibility ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unknownAlphabet:
            tmp = PPrint(rb, " --- Error code: UnknownAlphabet ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_ussd_Busy:
            tmp = PPrint(rb, " --- Error code: USSDBusy ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_pw_RegistrationFailure:
            tmp = PPrint(rb, " --- Error code: PWRegistrationFailure ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_negativePW_Check:
            tmp = PPrint(rb, " --- Error code: NegativePWCheck ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_numberOfPW_AttemptsViolation:
            tmp = PPrint(rb, " --- Error code: NumberOfPWAttemptsViolation ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_shortTermDenial:
            tmp = PPrint(rb, " --- Error code: ShortTermDenial ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_longTermDenial:
            tmp = PPrint(rb, " --- Error code: LongTermDenial ---\n");
            CHECK_RETURN(tmp, ret);
            break;


        // Short message service error codes.
        case ERR_subscriberBusyForMT_SMS:
            tmp = PPrint(rb, " --- Error code: SubscriberBusyForMTSMS ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_sm_DeliveryFailure:
            tmp = PPrint(rb, " --- Error code: SMDeliveryFailure ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_messageWaitingListFull:
            tmp = PPrint(rb, " --- Error code: MessageWaitingListFull ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_absentsubscriberSM:
            tmp = PPrint(rb, " --- Error code: AbsentSubscriberSM ---\n");
            CHECK_RETURN(tmp, ret);
            break;


        // Location service error codes.
        case ERR_unauthorizedRequestingNetwork:
            tmp = PPrint(rb, " --- Error code: UnauthorizedRequestingNetwork ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unauthorizedLCSClient:
            tmp = PPrint(rb, " --- Error code: UnauthorizedLCSClient ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_positionMethodFailure:
            tmp = PPrint(rb, " --- Error code: PositionMethodFailure ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_unknownOrUnreachableLCSClient:
            tmp = PPrint(rb, " --- Error code: UknownOrUnreachableLCSClient ---\n");
            CHECK_RETURN(tmp, ret);
            break;


        // Mobility Management error codes.
        case ERR_mm_EventNotSupported:
            tmp = PPrint(rb, " --- Error code: MMEventNotSupported ---\n");
            CHECK_RETURN(tmp, ret);
            break;


        // Secure transport error codes.
        case ERR_secureTransportError:
            do
            {
                SecureTransportErrorParam secureTransportError;

                DecodeAndPrint(rb, tmp, ret,
                               " --- Error code: SecureTransportError ---\n",
                               " --- End of parameter ---\n",
                               secureTransportError, octets);
            }
            while (0);
            break;


        // V1 error codes (not defined by V2 and V4).
#if 0
        case ERR_unknownBaseStation:
        case ERR_unknownLocArea:
        case ERR_unallocatedRoamingNumber:
        case ERR_illegalMS:
        case ERR_insufficientBearerCapabilities:
        case ERR_invalidTargetBaseStation:
        case ERR_noRadioResourceAvailable:
        case ERR_V1_busySubscriber:
        case ERR_V1_noSubscriberReply:
        case ERR_radioCongestion:
        case ERR_impossibleCallCompletion:
        case ERR_passwordRegistrationFailure:
        case ERR_negativePasswordCheck:
#endif
            tmp = PPrint(rb, " --- Error code: Canceled ---\n");
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

