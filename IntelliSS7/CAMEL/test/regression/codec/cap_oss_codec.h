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
//  ID: $Id: cap_oss_codec.h,v 9.1 2005/03/23 12:51:16 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////




int 
OSS_EncodeCAMEL_AChBillingChargingCharacteristics(
                        void *data,
			            unsigned char** encoded, 
                        size_t *size, 
                        size_t valueNumber);

int
OSS_DecodeCAMEL_AChBillingChargingCharacteristics(
                                              unsigned char* encoded, 
                                              size_t size, 
                                              void** data);


int 
OSS_EncodeCAMEL_FCIBillingChargingCharacteristics(
                                                void* data, 
                                                unsigned char** encoded, 
                                                size_t* size, 
                                                size_t valueNumber);

int 
OSS_DecodeCAMEL_FCIBillingChargingCharacteristics(
                                                unsigned char* encoded, 
                                                size_t size, 
                                                void** data);

int 
OSS_EncodeCAMEL_CallResult(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);

int 
OSS_DecodeCAMEL_CallResult(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data);


int 
OSS_EncodeCAMEL_FCIGPRSBillingChargingCharacteristics(
                                                void* data, 
                                                unsigned char** encoded, 
                                                size_t* size, 
                                                size_t valueNumber);

int 
OSS_DecodeCAMEL_FCIGPRSBillingChargingCharacteristics(
                                                unsigned char* encoded, 
                                                size_t size, 
                                                void** data);


int 
OSS_EncodeCAMEL_FCISMSBillingChargingCharacteristics(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);

int 
OSS_DecodeCAMEL_FCISMSBillingChargingCharacteristics(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data);

int OSS_EncodeCAMEL_SCIBillingChargingCharacteristics(
                                                void* data, 
                                                unsigned char** encoded, 
                                                size_t* size, 
                                                size_t valueNumber);

int OSS_DecodeCAMEL_SCIBillingChargingCharacteristics(
                                                unsigned char* encoded, 
                                                size_t size, 
                                                void** data);

int OSS_EncodeCAMEL_SCIGPRSBillingChargingCharacteristics(
                                                void* data, 
                                                unsigned char** encoded, 
                                                size_t* size, 
                                                size_t valueNumber);

int OSS_DecodeCAMEL_SCIGPRSBillingChargingCharacteristics(
                                                unsigned char* encoded, 
                                                size_t size, 
                                                void** data);


int OSS_EncodeUnavailableNetworkResource(
                                      void* data, 
                                      unsigned char** encoded, 
                                      size_t* size, 
                                      size_t valueNumber);

int OSS_DecodeUnavailableNetworkResource(
                                      unsigned char* encoded, 
                                      size_t size, 
                                      void** data);

int OSS_EncodeCancelFailed(
                          void* data, 
                          unsigned char** encoded, 
                          size_t* size, 
                          size_t valueNumber);

int OSS_DecodeCancelFailed(
                          unsigned char* encoded, 
                          size_t size, 
                          void** data);

int OSS_EncodeRequestedInfoError(
                          void* data, 
                          unsigned char** encoded, 
                          size_t* size, 
                          size_t valueNumber);

int OSS_DecodeRequestedInfoError(
                          unsigned char* encoded, 
                          size_t size, 
                          void** data);

int OSS_EncodeTaskRefused(
                          void* data, 
                          unsigned char** encoded, 
                          size_t* size, 
                          size_t valueNumber);

int OSS_DecodeTaskRefused(
                          unsigned char* encoded, 
                          size_t size, 
                          void** data);

int OSS_EncodeApplyChargingArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeApplyChargingArg(
                            unsigned char* encoded, 
                            size_t size, 
                            void** data);

int OSS_EncodeApplyChargingReportArg(
                          void* data, 
                          unsigned char** encoded, 
                          size_t* size, 
                          size_t valueNumber);

int OSS_DecodeApplyChargingReportArg(
                          unsigned char* encoded, 
                          size_t size, 
                          void** data);

int OSS_EncodeAssistRequestInstructionsArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeAssistRequestInstructionsArg(
                            unsigned char* encoded, 
                            size_t size, 
                            void** data);


int OSS_EncodeCallGapArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeCallGapArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeCallInformationReportArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeCallInformationReportArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeCallInformationRequestArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeCallInformationRequestArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeCancelArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeCancelArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeConnectArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeConnectArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeConnectToResourceArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeConnectToResourceArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeContinueWithArgumentArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeContinueWithArgumentArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeEstablishTemporaryConnectionArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeEstablishTemporaryConnectionArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeEventReportBCSMArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeEventReportBCSMArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeFurnishChargingInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeFurnishChargingInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeInitialDPArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeInitialDPArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeReleaseCallArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeReleaseCallArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeRequestReportBCSMEventArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeRequestReportBCSMEventArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeResetTimerArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeResetTimerArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeSendChargingInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeSendChargingInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodePlayAnnouncementArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodePlayAnnouncementArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodePromptAndCollectUserInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodePromptAndCollectUserInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeReceivedInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeReceivedInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeReceivedInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeReceivedInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeSpecializedResourceReportArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeSpecializedResourceReportArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeConnectSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeConnectSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeEventReportSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeEventReportSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeFurnishChargingInformationSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeFurnishChargingInformationSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeInitialDPSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeInitialDPSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeReleaseSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeReleaseSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeRequestReportSMSEventArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeRequestReportSMSEventArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeResetTimerSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeResetTimerSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeActivityTestGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeActivityTestGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeApplyChargingGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeApplyChargingGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeApplyChargingReportGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeApplyChargingReportGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeCancelGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeCancelGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeConnectGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeConnectGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeContinueGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeContinueGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeEntityReleasedGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeEntityReleasedGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeFurnishChargingInformationGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeFurnishChargingInformationGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeInitialDPGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeInitialDPGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int OSS_EncodeReleaseGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeReleaseGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeEventReportGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeEventReportGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeRequestReportGPRSEventArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeRequestReportGPRSEventArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeResetTimerGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeResetTimerGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int OSS_EncodeSendChargingInformationGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int OSS_DecodeSendChargingInformationGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


