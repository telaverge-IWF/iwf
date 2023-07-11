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
//  ID: $Id: map_cpp.cpp,v 9.2 2007/01/10 11:14:59 yranade Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  IntelliSS7 GSM MAP C++ API common source (all versions of GSM MAP).
//
//  o   Application Context Helper function implementations.
//  


#include <map_cpp.h>

#include <Octets.h>
#include <Length.h>
#include <AsnObjectIdentifier.h>
#include <AsnException.h>

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
#endif // defined(ITS_NAMESPACE)

vector<byte>
map_common::EncodeApplicationContext(map_common::MAP_AC acName)
{
    vector<long> cptArray;

    cptArray.push_back(OID_CPT_CCITT);
    cptArray.push_back(OID_CPT_IDEN_ORG);
    cptArray.push_back(OID_CPT_ETSI);
    cptArray.push_back(OID_CPT_MOBILE_DOMAIN);
    cptArray.push_back(OID_CPT_GSM_NETWORK);
    cptArray.push_back(OID_CPT_AC_ID);

    switch (acName)
    {
        case networkLocUpContext_v1:
            cptArray.push_back(OID_NETWORK_lOC_UP_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case locationCancellationContext_v1:
            cptArray.push_back(OID_LOCATION_CANCELLATION);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case roamingNumberEnquiryContext_v1:
            cptArray.push_back(OID_ROAMING_NUMBER_ENQUIRY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case locationInfoRetrievalContext_v1:
            cptArray.push_back(OID_LOCATION_INFO_RETRIEVAL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case resetContext_v1:
            cptArray.push_back(OID_RESET_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case handoverControlContext_v1:
            cptArray.push_back(OID_HANDOVER_CONTROL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case equipmentMngtContext_v1:
            cptArray.push_back(OID_EQUIPMENT_MNGT_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case infoRetrievalContext_v1:
            cptArray.push_back(OID_INFO_RETRIEVAL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case subscriberDataMngtContext_v1:
            cptArray.push_back(OID_SUBSCRIBER_DATA_MNGT_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case tracingContext_v1:
            cptArray.push_back(OID_TRACING_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case networkFunctionalSsContext_v1:
            cptArray.push_back(OID_NETWORK_FUNCTIONAL_SS_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case shortMsgGatewayContext_v1:
            cptArray.push_back(OID_SHORT_MSG_GATEWAY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case shortMsg_RelayContext_v1:
            cptArray.push_back(OID_SHORT_MSG_RELAY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case shortMsgAlertContext_v1:
            cptArray.push_back(OID_SHORT_MSG_ALERT_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;
        case mwdMngtContext_v1:
            cptArray.push_back(OID_MWD_MNGT_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION1);
            break;

        case networkLocUpContext_v2:
            cptArray.push_back(OID_NETWORK_lOC_UP_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case locationCancellationContext_v2:
            cptArray.push_back(OID_LOCATION_CANCELLATION);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case roamingNumberEnquiryContext_v2:
            cptArray.push_back(OID_ROAMING_NUMBER_ENQUIRY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case locationInfoRetrievalContext_v2:
            cptArray.push_back(OID_LOCATION_INFO_RETRIEVAL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case resetContext_v2:
            cptArray.push_back(OID_RESET_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case handoverControlContext_v2:
            cptArray.push_back(OID_HANDOVER_CONTROL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case equipmentMngtContext_v2:
            cptArray.push_back(OID_EQUIPMENT_MNGT_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case infoRetrievalContext_v2:
            cptArray.push_back(OID_INFO_RETRIEVAL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case interVlrInfoRetrievalContext_v2:
            cptArray.push_back(OID_INTER_VLR_INFO_RETRIEVAL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case subscriberDataMngtContext_v2:
            cptArray.push_back(OID_SUBSCRIBER_DATA_MNGT_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case tracingContext_v2:
            cptArray.push_back(OID_TRACING_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case networkFunctionalSsContext_v2:
            cptArray.push_back(OID_NETWORK_FUNCTIONAL_SS_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case networkUnstructuredSsContext_v2:
            cptArray.push_back(OID_NETWORK_UNSTRUCTURED_SS_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case shortMsgGatewayContext_v2:
            cptArray.push_back(OID_SHORT_MSG_GATEWAY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case shortMsgMO_RelayContext_v2:
            cptArray.push_back(OID_SHORT_MSG_RELAY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case shortMsgAlertContext_v2:
            cptArray.push_back(OID_SHORT_MSG_ALERT_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case mwdMngtContext_v2:
            cptArray.push_back(OID_MWD_MNGT_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case shortMsgMT_RelayContext_v2:
            cptArray.push_back(OID_SHORT_MSG_MT_RELAY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case imsiRetrievalContext_v2:
            cptArray.push_back(OID_IMSI_RETRIEVAL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;
        case msPurgingContext_v2:
            cptArray.push_back(OID_MS_PURGING_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION2);
            break;

        case networkLocUpContext_v3:
            cptArray.push_back(OID_NETWORK_lOC_UP_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case locationCancellationContext_v3:
            cptArray.push_back(OID_LOCATION_CANCELLATION);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case roamingNumberEnquiryContext_v3:
            cptArray.push_back(OID_ROAMING_NUMBER_ENQUIRY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case istAlertingContext_v3:
            cptArray.push_back(OID_IST_ALERTING_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case locationInfoRetrievalContext_v3:
            cptArray.push_back(OID_LOCATION_INFO_RETRIEVAL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case callControlTransferContext_v3:
            cptArray.push_back(OID_CALL_CONTROL_TRANSFER_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case reportingContext_v3:
            cptArray.push_back(OID_REPORTING_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case callCompletionContext_v3:
            cptArray.push_back(OID_CALL_COMPLETION_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case serviceTerminationContext_v3:
            cptArray.push_back(OID_SERVICE_TERMINATION_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case handoverControlContext_v3:
            cptArray.push_back(OID_HANDOVER_CONTROL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case sIWFSAllocationContext_v3:
            cptArray.push_back(OID_SIWFS_ALLOCATION_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case infoRetrievalContext_v3:
            cptArray.push_back(OID_INFO_RETRIEVAL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case interVlrInfoRetrievalContext_v3:
            cptArray.push_back(OID_INTER_VLR_INFO_RETRIEVAL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case subscriberDataMngtContext_v3:
            cptArray.push_back(OID_SUBSCRIBER_DATA_MNGT_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case tracingContext_v3:
            cptArray.push_back(OID_TRACING_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case shortMsgGatewayContext_v3:
            cptArray.push_back(OID_SHORT_MSG_GATEWAY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case shortMsgMO_RelayContext_v3:
            cptArray.push_back(OID_SHORT_MSG_RELAY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case subscriberDataModificationNotificationContext_v3:
            cptArray.push_back(OID_SUBSCRIBER_DATA_MODIFICATION_NOTIFICATION_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case mwdMngtContext_v3:
            cptArray.push_back(OID_MWD_MNGT_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case shortMsgMT_RelayContext_v3:
            cptArray.push_back(OID_SHORT_MSG_MT_RELAY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case msPurgingContext_v3:
            cptArray.push_back(OID_MS_PURGING_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case subscriberInfoEnquiryContext_v3:
            cptArray.push_back(OID_SUBSCRIBER_INFO_ENQUIRY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case anyTimeInfoEnquiryContext_v3:
            cptArray.push_back(OID_ANYTIME_INFO_ENQUIRY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case groupCallControlContext_v3:
            cptArray.push_back(OID_GROUP_CALL_CONTROL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case gprsLocationUpdateContext_v3:
            cptArray.push_back(OID_GPRS_LOCATION_UPDATE_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case gprsLocationInfoRetrievalContext_v3:
            cptArray.push_back(OID_GPRS_LOCATION_INFO_RETRIEVAL_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case failureReportContext_v3:
            cptArray.push_back(OID_FAILURE_REPORT_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case gprsNotifyContext_v3:
            cptArray.push_back(OID_GPRS_NOTIFY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case ss_InvocationNotificationContext_v3:
            cptArray.push_back(OID_SS_INVOCATION_NOTIFICATION_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case locationSvcGatewayContext_v3:
            cptArray.push_back(OID_LOCATION_SVC_GATEWAY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case locationSvcEnquiryContext_v3:
            cptArray.push_back(OID_LOCATION_SVC_ENQUIRY_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case authenticationFailureReportContext_v3:
            cptArray.push_back(OID_AUTHENTICATION_FAILURE_REPORT_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case SecureTransportHandlingContext_v3:
            cptArray.push_back(OID_SECURE_TRANSPORT_HANDLING_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case mm_EventReportingContext_v3:
            cptArray.push_back(OID_MM_EVENT_REPORTING_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;
        case anyTimeInfohandlingContext_v3:
            cptArray.push_back(OID_ANY_TIME_INFO_HANDLING_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION3);
            break;

        case callControlTransferContext_v4:
            cptArray.push_back(OID_CALL_CONTROL_TRANSFER_CONTEXT);
            cptArray.push_back(OID_CPT_VERSION4);
            break;
     
        default:
            cptArray.clear();
            break;
    } 

    vector<byte> result;

    try
    {
        AsnObjectIdentifier objectIdentifier;

        objectIdentifier.SetArray(cptArray);

        Octets* octets = objectIdentifier.Encode();
        Tag tag(*octets);
        Length length(*octets);
        result = octets->GetArrayWithOffset();
        delete octets;
    }
    catch (its::AsnEncodeError& err)
    {
        result.clear();
    }

    return result;
}

map_common::MAP_AC
map_common::DecodeApplicationContext(vector<byte>& encodedVec)
{
    map_common::MAP_AC acName = UNKNOWN;

    Tag* tag = NULL;
    Octets* tagOctets = NULL;
    Octets* lengthOctets = NULL;
    Octets* octets = NULL;

    std::vector<long> result;

    try
    {
        Octets valOctets(encodedVec);

        tag = AsnObjectIdentifier::GetUniversalTag();
        tagOctets = tag->Encode();

        Length length(valOctets.GetLength());
        lengthOctets = length.Encode();

        octets = new Octets();

        *octets += *tagOctets;
        *octets += *lengthOctets;
        *octets += valOctets;

        AsnObjectIdentifier objectIdentifier;
        objectIdentifier.Decode(*octets);

        result = objectIdentifier.GetArray();
    }
    catch (its::AsnDecodeError& err)
    {
        result.clear();

        if (octets)
            delete octets;
        if (lengthOctets)
            delete lengthOctets;
        if (tagOctets)
            delete tagOctets;
        if (tag)
            delete tag;
    }

    ITS_INT count = 0;
    ITS_UINT rec = 0;

    if (result.size() < 8)
    {
        return acName;
    }

    if ((result[0] == OID_CPT_CCITT)         &&
        (result[1] == OID_CPT_IDEN_ORG)      &&
        (result[2] == OID_CPT_ETSI)          &&
        (result[3] == OID_CPT_MOBILE_DOMAIN) &&
        (result[4] == OID_CPT_GSM_NETWORK)   &&
        (result[5] == OID_CPT_AC_ID))
    {
        switch (result[6])
        {
            case OID_NETWORK_lOC_UP_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = networkLocUpContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = networkLocUpContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = networkLocUpContext_v3;
                }
                break;
            case OID_LOCATION_CANCELLATION:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = locationCancellationContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = locationCancellationContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = locationCancellationContext_v3;
                }
                break;
            case OID_ROAMING_NUMBER_ENQUIRY_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = roamingNumberEnquiryContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = roamingNumberEnquiryContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = roamingNumberEnquiryContext_v3;
                }
                break;
            case OID_IST_ALERTING_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = istAlertingContext_v3;
                }
                break;
            case OID_LOCATION_INFO_RETRIEVAL_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = locationInfoRetrievalContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = locationInfoRetrievalContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = locationInfoRetrievalContext_v3;
                }
                break;
            case OID_CALL_CONTROL_TRANSFER_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = callControlTransferContext_v3;
                }
                else if (result[7] == OID_CPT_VERSION4)
                {
                    acName = callControlTransferContext_v4;
                }
                break;
            case OID_REPORTING_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = reportingContext_v3;
                }
                break;
            case OID_CALL_COMPLETION_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = callCompletionContext_v3;
                }
                break;
            case OID_SERVICE_TERMINATION_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = serviceTerminationContext_v3;
                }
                break;
            case OID_RESET_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = resetContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = resetContext_v2;
                }
                break;
            case OID_HANDOVER_CONTROL_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = handoverControlContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = handoverControlContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = handoverControlContext_v3;
                }
                break;
            case OID_SIWFS_ALLOCATION_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = sIWFSAllocationContext_v3;
                }
                break;
            case OID_EQUIPMENT_MNGT_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = equipmentMngtContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = equipmentMngtContext_v2;
                }
                break;
            case OID_INFO_RETRIEVAL_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = infoRetrievalContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = infoRetrievalContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = infoRetrievalContext_v3;
                }
                break;
            case OID_INTER_VLR_INFO_RETRIEVAL_CONTEXT:
                if (result[7] == OID_CPT_VERSION2)
                {
                    acName = interVlrInfoRetrievalContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = interVlrInfoRetrievalContext_v3;
                }
                break;
            case OID_SUBSCRIBER_DATA_MNGT_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = subscriberDataMngtContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = subscriberDataMngtContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = subscriberDataMngtContext_v3;
                }
                break;
            case OID_TRACING_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = tracingContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = tracingContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = tracingContext_v3;
                }
                break;
            case OID_NETWORK_FUNCTIONAL_SS_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = networkFunctionalSsContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = networkFunctionalSsContext_v2;
                }
                break;
            case OID_NETWORK_UNSTRUCTURED_SS_CONTEXT:
                if (result[7] == OID_CPT_VERSION2)
                {
                    acName = networkUnstructuredSsContext_v2;
                }
                break;
            case OID_SHORT_MSG_GATEWAY_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = shortMsgGatewayContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = shortMsgGatewayContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = shortMsgGatewayContext_v3;
                }
                break;
            case OID_SHORT_MSG_RELAY_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = shortMsg_RelayContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = shortMsgMO_RelayContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = shortMsgMO_RelayContext_v3;
                }
                break;
            case OID_SUBSCRIBER_DATA_MODIFICATION_NOTIFICATION_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = subscriberDataModificationNotificationContext_v3;
                }
                break;
            case OID_SHORT_MSG_ALERT_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = shortMsgAlertContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = shortMsgAlertContext_v2;
                }
                break;
            case OID_MWD_MNGT_CONTEXT:
                if (result[7] == OID_CPT_VERSION1)
                {
                    acName = mwdMngtContext_v1;
                }
                else if (result[7] == OID_CPT_VERSION2)
                {
                    acName = mwdMngtContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = mwdMngtContext_v3;
                }
                break;
            case OID_SHORT_MSG_MT_RELAY_CONTEXT:
                if (result[7] == OID_CPT_VERSION2)
                {
                    acName = shortMsgMT_RelayContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = shortMsgMT_RelayContext_v3;
                }
                break;
            case OID_IMSI_RETRIEVAL_CONTEXT:
                if (result[7] == OID_CPT_VERSION2)
                {
                    acName = imsiRetrievalContext_v2;
                }
                break; 
            case OID_MS_PURGING_CONTEXT:
                if (result[7] == OID_CPT_VERSION2)
                {
                    acName = msPurgingContext_v2;
                }
                else if (result[7] == OID_CPT_VERSION3)
                {
                    acName = msPurgingContext_v3;
                }
                break;
            case OID_SUBSCRIBER_INFO_ENQUIRY_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = subscriberInfoEnquiryContext_v3;
                }
                break;
            case OID_ANYTIME_INFO_ENQUIRY_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = anyTimeInfoEnquiryContext_v3;
                }
                break;
            case OID_GROUP_CALL_CONTROL_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = groupCallControlContext_v3;
                }
                break;
            case OID_GPRS_LOCATION_UPDATE_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = gprsLocationUpdateContext_v3;
                }
                break;
            case OID_GPRS_LOCATION_INFO_RETRIEVAL_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = gprsLocationInfoRetrievalContext_v3;
                }
                break;
            case OID_FAILURE_REPORT_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = failureReportContext_v3;
                }
                break;
            case OID_GPRS_NOTIFY_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = gprsNotifyContext_v3;
                }
                break;
            case OID_SS_INVOCATION_NOTIFICATION_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = ss_InvocationNotificationContext_v3;
                }
                break;
            case OID_LOCATION_SVC_GATEWAY_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = locationSvcGatewayContext_v3;
                }
                break;
            case OID_LOCATION_SVC_ENQUIRY_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = locationSvcEnquiryContext_v3;
                }
                break;
            case OID_AUTHENTICATION_FAILURE_REPORT_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = authenticationFailureReportContext_v3;
                }
                break;
            case OID_SECURE_TRANSPORT_HANDLING_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = SecureTransportHandlingContext_v3;
                }
                break;
            case OID_MM_EVENT_REPORTING_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = mm_EventReportingContext_v3;
                }
                break;
            case OID_ANY_TIME_INFO_HANDLING_CONTEXT:
                if (result[7] == OID_CPT_VERSION3)
                {
                    acName = anyTimeInfohandlingContext_v3;
                }
                break;
        }
    }

    return acName;

}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode the given Application context vector.
 *
 *  Input Parameters:
 *      vector<long> - List of values specified in the standard.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      vector<byte> - Application context Encoded bytes.
 *
 ****************************************************************************/

std::vector<byte>
map_common::EncodeApplicationContextVector(vector<long>& ac)
{
    vector<byte> result;

    if (ac.size() == 0)
    {
        return result;
    }

    try
    {
        AsnObjectIdentifier objectIdentifier;
        objectIdentifier.SetArray(ac);
        Octets* octets = objectIdentifier.Encode();
        Tag tag(*octets);
        Length length(*octets);
        result = octets->GetArrayWithOffset();
        delete octets;
    }
    catch(its::AsnEncodeError& err)
    {
        result.clear();
    }

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Decode the given Application context Encoded bytes and returns
 *      the vector of values as specified in the standard.
 *
 *  Input Parameters:
 *      vector<byte> - Application context Encoded bytes.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      vector<long> - List of values specified in the standard.
 *
 ****************************************************************************/

vector<long>
map_common::DecodeApplicationContextVector(vector<byte>& ac)
{
    Tag* tag = NULL;
    Octets* tagOctets = NULL;
    Octets* lengthOctets = NULL;
    Octets* octets = NULL;

    std::vector<long> result;

    try
    {
        Octets valOctets(ac);

        tag = AsnObjectIdentifier::GetUniversalTag();
        tagOctets = tag->Encode();

        Length length(valOctets.GetLength());
        lengthOctets = length.Encode();

        octets = new Octets();

        *octets += *tagOctets;
        *octets += *lengthOctets;
        *octets += valOctets;

        AsnObjectIdentifier objectIdentifier;
        objectIdentifier.Decode(*octets);

        result = objectIdentifier.GetArray();
    }
    catch (its::AsnDecodeError& err)
    {
        result.clear();
        if (octets)
            delete octets;
        if (lengthOctets)
            delete lengthOctets;
        if (tagOctets)
            delete tagOctets;
        if (tag)
            delete tag;
    }

    return result;
}
void
map_common::DecodeApplicationContext(
                    vector<byte>& encodedVec,
                    long& acName,
                    long& version)
{
    Octets valOctets(encodedVec);

    Tag* tag = AsnObjectIdentifier::GetUniversalTag();

    Octets* tagOctets = tag->Encode();

    Length length(valOctets.GetLength());

    Octets* lengthOctets = length.Encode();

    Octets* octets = new Octets();

    *octets += *tagOctets;
    *octets += *lengthOctets;
    *octets += valOctets;

    AsnObjectIdentifier objectIdentifier;

    objectIdentifier.Decode(*octets);

    acName = objectIdentifier.GetArray()[6];
    version = objectIdentifier.GetArray()[7];

    delete octets;
    delete lengthOctets;
    delete tagOctets;
    delete tag;
}
