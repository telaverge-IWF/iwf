////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
//  ID: $Id: cap_oss_codec.cpp,v 9.1 2005/03/23 12:51:16 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////


#include <its++.h>

#include <iostream>

#include <cap_oss_codec.h>
#include <cap_oss_api.h>

#include <Asn.h>
#include <AsnException.h>


#include <cap_v3_lrfvn.h>

using namespace std;
using namespace its;




int 
OSS_EncodeCAMEL_AChBillingChargingCharacteristics(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        CAMEL_AChBillingChargingCharacteristics_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeCAMEL_AChBillingChargingCharacteristics(
                                              unsigned char* encoded, 
                                              size_t size, 
                                              void** data)
{
    int res = OSS_GetDecodedPDU(
                        CAMEL_AChBillingChargingCharacteristics_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeCAMEL_CallResult(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        CAMEL_CallResult_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeCAMEL_CallResult(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        CAMEL_CallResult_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}


int 
OSS_EncodeCAMEL_FCIBillingChargingCharacteristics(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        CAMEL_FCIBillingChargingCharacteristics_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeCAMEL_FCIBillingChargingCharacteristics(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        CAMEL_FCIBillingChargingCharacteristics_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeCAMEL_FCIGPRSBillingChargingCharacteristics(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        CAMEL_FCIGPRSBillingChargingCharacteristics_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeCAMEL_FCIGPRSBillingChargingCharacteristics(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        CAMEL_FCIGPRSBillingChargingCharacteristics_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeCAMEL_FCISMSBillingChargingCharacteristics(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        CAMEL_FCISMSBillingChargingCharacteristics_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeCAMEL_FCISMSBillingChargingCharacteristics(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        CAMEL_FCISMSBillingChargingCharacteristics_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeCAMEL_SCIBillingChargingCharacteristics(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        CAMEL_SCIBillingChargingCharacteristics_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeCAMEL_SCIBillingChargingCharacteristics(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        CAMEL_SCIBillingChargingCharacteristics_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeCAMEL_SCIGPRSBillingChargingCharacteristics(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        CAMEL_SCIGPRSBillingChargingCharacteristics_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeCAMEL_SCIGPRSBillingChargingCharacteristics(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        CAMEL_SCIGPRSBillingChargingCharacteristics_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeUnavailableNetworkResource(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        UnavailableNetworkResource_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeUnavailableNetworkResource(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        UnavailableNetworkResource_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeCancelFailed(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        CancelFailed_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeCancelFailed(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        CancelFailed_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeRequestedInfoError(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        RequestedInfoError_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeRequestedInfoError(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        RequestedInfoError_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeTaskRefused(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        TaskRefused_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeTaskRefused(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        TaskRefused_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeApplyChargingArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ApplyChargingArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeApplyChargingArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ApplyChargingArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeApplyChargingReportArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ApplyChargingReportArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeApplyChargingReportArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ApplyChargingReportArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeAssistRequestInstructionsArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        AssistRequestInstructionsArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeAssistRequestInstructionsArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        AssistRequestInstructionsArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeCallGapArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        CallGapArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeCallGapArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        CallGapArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeCallInformationReportArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        CallInformationReportArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeCallInformationReportArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        CallInformationReportArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeCallInformationRequestArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        CallInformationRequestArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeCallInformationRequestArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        CallInformationRequestArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeCancelArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        CancelArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeCancelArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        CancelArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeConnectArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ConnectArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeConnectArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ConnectArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeConnectToResourceArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ConnectToResourceArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeConnectToResourceArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ConnectToResourceArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeContinueWithArgumentArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ContinueWithArgumentArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeContinueWithArgumentArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ContinueWithArgumentArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeEstablishTemporaryConnectionArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        EstablishTemporaryConnectionArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeEstablishTemporaryConnectionArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        EstablishTemporaryConnectionArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeEventReportBCSMArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        EventReportBCSMArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeEventReportBCSMArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        EventReportBCSMArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeFurnishChargingInformationArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        FurnishChargingInformationArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeFurnishChargingInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        FurnishChargingInformationArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeInitialDPArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        InitialDPArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeInitialDPArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        InitialDPArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeReleaseCallArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ReleaseCallArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeReleaseCallArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ReleaseCallArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeRequestReportBCSMEventArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        RequestReportBCSMEventArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeRequestReportBCSMEventArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        RequestReportBCSMEventArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeResetTimerArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ResetTimerArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeResetTimerArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ResetTimerArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeSendChargingInformationArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        SendChargingInformationArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeSendChargingInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        SendChargingInformationArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodePlayAnnouncementArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        PlayAnnouncementArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodePlayAnnouncementArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        PlayAnnouncementArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodePromptAndCollectUserInformationArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        PromptAndCollectUserInformationArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodePromptAndCollectUserInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        PromptAndCollectUserInformationArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeReceivedInformationArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ReceivedInformationArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeReceivedInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ReceivedInformationArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeSpecializedResourceReportArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        SpecializedResourceReportArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeSpecializedResourceReportArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        SpecializedResourceReportArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeConnectSMSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ConnectSMSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeConnectSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ConnectSMSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeEventReportSMSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        EventReportSMSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeEventReportSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        EventReportSMSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeFurnishChargingInformationSMSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        FurnishChargingInformationSMSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeFurnishChargingInformationSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        FurnishChargingInformationSMSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeInitialDPSMSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        InitialDPSMSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeInitialDPSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        InitialDPSMSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeReleaseSMSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ReleaseSMSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeReleaseSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ReleaseSMSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeRequestReportSMSEventArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        RequestReportSMSEventArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeRequestReportSMSEventArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        RequestReportSMSEventArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeResetTimerSMSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ResetTimerSMSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeResetTimerSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ResetTimerSMSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeActivityTestGPRSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ActivityTestGPRSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeActivityTestGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ActivityTestGPRSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeApplyChargingGPRSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ApplyChargingGPRSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeApplyChargingGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ApplyChargingGPRSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeApplyChargingReportGPRSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ApplyChargingReportGPRSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeApplyChargingReportGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ApplyChargingReportGPRSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeCancelGPRSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        CancelGPRSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeCancelGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        CancelGPRSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeConnectGPRSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ConnectGPRSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeConnectGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ConnectGPRSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeContinueGPRSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ContinueGPRSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeContinueGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ContinueGPRSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeEntityReleasedGPRSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        EntityReleasedGPRSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeEntityReleasedGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        EntityReleasedGPRSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeFurnishChargingInformationGPRSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        FurnishChargingInformationGPRSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeFurnishChargingInformationGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        FurnishChargingInformationGPRSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeInitialDPGPRSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        InitialDPGPRSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeInitialDPGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        InitialDPGPRSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}

int 
OSS_EncodeReleaseGPRSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ReleaseGPRSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeReleaseGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ReleaseGPRSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}


int 
OSS_EncodeEventReportGPRSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        EventReportGPRSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeEventReportGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        EventReportGPRSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}


int 
OSS_EncodeRequestReportGPRSEventArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        RequestReportGPRSEventArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeRequestReportGPRSEventArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        RequestReportGPRSEventArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}


int 
OSS_EncodeResetTimerGPRSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        ResetTimerGPRSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeResetTimerGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        ResetTimerGPRSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}


int 
OSS_EncodeSendChargingInformationGPRSArg(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber)
{
    int res = OSS_GetEncodedPDU(
                        SendChargingInformationGPRSArg_PDU, 
                        encoded, 
                        size, 
                        valueNumber);

	return res;
}



int
OSS_DecodeSendChargingInformationGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data)
{
    int res = OSS_GetDecodedPDU(
                        SendChargingInformationGPRSArg_PDU, 
                        encoded, 
                        size, 
                        data);

    return res;
}


