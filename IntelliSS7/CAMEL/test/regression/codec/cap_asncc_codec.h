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
//  ID: $Id: cap_asncc_codec.h,v 9.1 2005/03/23 12:51:16 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////



int AsnCC_EncodeCAMEL_AChBillingChargingCharacteristics(
                                                void* data, 
                                                unsigned char** encoded, 
                                                size_t* size, 
                                                size_t valueNumber);

int AsnCC_DecodeCAMEL_AChBillingChargingCharacteristics(
                                                unsigned char* encoded, 
                                                size_t size, 
                                                void** data);

int AsnCC_EncodeCAMEL_FCIBillingChargingCharacteristics(
                                                void* data, 
                                                unsigned char** encoded, 
                                                size_t* size, 
                                                size_t valueNumber);

int AsnCC_DecodeCAMEL_FCIBillingChargingCharacteristics(
                                                unsigned char* encoded, 
                                                size_t size, 
                                                void** data);

int 
AsnCC_EncodeCAMEL_CallResult(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);

int 
AsnCC_DecodeCAMEL_CallResult(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data);


int AsnCC_EncodeCAMEL_FCIGPRSBillingChargingCharacteristics(
                                                void* data, 
                                                unsigned char** encoded, 
                                                size_t* size, 
                                                size_t valueNumber);

int AsnCC_DecodeCAMEL_FCIGPRSBillingChargingCharacteristics(
                                                unsigned char* encoded, 
                                                size_t size, 
                                                void** data);


int 
AsnCC_EncodeCAMEL_FCISMSBillingChargingCharacteristics(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);

int 
AsnCC_DecodeCAMEL_FCISMSBillingChargingCharacteristics(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data);

int AsnCC_EncodeCAMEL_SCIBillingChargingCharacteristics(
                                                void* data, 
                                                unsigned char** encoded, 
                                                size_t* size, 
                                                size_t valueNumber);

int AsnCC_DecodeCAMEL_SCIBillingChargingCharacteristics(
                                                unsigned char* encoded, 
                                                size_t size, 
                                                void** data);

int AsnCC_EncodeCAMEL_SCIGPRSBillingChargingCharacteristics(
                                                void* data, 
                                                unsigned char** encoded, 
                                                size_t* size, 
                                                size_t valueNumber);

int AsnCC_DecodeCAMEL_SCIGPRSBillingChargingCharacteristics(
                                                unsigned char* encoded, 
                                                size_t size, 
                                                void** data);


int AsnCC_EncodeUnavailableNetworkResource(
                                      void* data, 
                                      unsigned char** encoded, 
                                      size_t* size, 
                                      size_t valueNumber);

int AsnCC_DecodeUnavailableNetworkResource(
                                      unsigned char* encoded, 
                                      size_t size, 
                                      void** data);

int AsnCC_EncodeCancelFailed(
                          void* data, 
                          unsigned char** encoded, 
                          size_t* size, 
                          size_t valueNumber);

int AsnCC_DecodeCancelFailed(
                          unsigned char* encoded, 
                          size_t size, 
                          void** data);

int AsnCC_EncodeRequestedInfoError(
                          void* data, 
                          unsigned char** encoded, 
                          size_t* size, 
                          size_t valueNumber);

int AsnCC_DecodeRequestedInfoError(
                          unsigned char* encoded, 
                          size_t size, 
                          void** data);

int AsnCC_EncodeTaskRefused(
                          void* data, 
                          unsigned char** encoded, 
                          size_t* size, 
                          size_t valueNumber);

int AsnCC_DecodeTaskRefused(
                          unsigned char* encoded, 
                          size_t size, 
                          void** data);

int AsnCC_EncodeApplyChargingArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeApplyChargingArg(
                            unsigned char* encoded, 
                            size_t size, 
                            void** data);

int AsnCC_EncodeApplyChargingReportArg(
                          void* data, 
                          unsigned char** encoded, 
                          size_t* size, 
                          size_t valueNumber);

int AsnCC_DecodeApplyChargingReportArg(
                          unsigned char* encoded, 
                          size_t size, 
                          void** data);

int AsnCC_EncodeAssistRequestInstructionsArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeAssistRequestInstructionsArg(
                            unsigned char* encoded, 
                            size_t size, 
                            void** data);


int AsnCC_EncodeCallGapArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeCallGapArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeCallInformationReportArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeCallInformationReportArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeCallInformationRequestArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeCallInformationRequestArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeCancelArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeCancelArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeConnectArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeConnectArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeConnectToResourceArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeConnectToResourceArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeContinueWithArgumentArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeContinueWithArgumentArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeEstablishTemporaryConnectionArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeEstablishTemporaryConnectionArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeEventReportBCSMArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeEventReportBCSMArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeFurnishChargingInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeFurnishChargingInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeInitialDPArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeInitialDPArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeReleaseCallArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeReleaseCallArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeRequestReportBCSMEventArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeRequestReportBCSMEventArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeResetTimerArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeResetTimerArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeSendChargingInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeSendChargingInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodePlayAnnouncementArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodePlayAnnouncementArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodePromptAndCollectUserInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodePromptAndCollectUserInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeReceivedInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeReceivedInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeReceivedInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeReceivedInformationArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeSpecializedResourceReportArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeSpecializedResourceReportArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeConnectSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeConnectSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeEventReportSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeEventReportSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeFurnishChargingInformationSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeFurnishChargingInformationSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeInitialDPSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeInitialDPSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeReleaseSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeReleaseSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeRequestReportSMSEventArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeRequestReportSMSEventArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeResetTimerSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeResetTimerSMSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeActivityTestGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeActivityTestGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeApplyChargingGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeApplyChargingGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeApplyChargingReportGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeApplyChargingReportGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeCancelGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeCancelGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeConnectGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeConnectGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeContinueGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeContinueGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeEntityReleasedGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeEntityReleasedGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeFurnishChargingInformationGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeFurnishChargingInformationGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeInitialDPGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeInitialDPGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


int AsnCC_EncodeReleaseGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeReleaseGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeEventReportGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeEventReportGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeRequestReportGPRSEventArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeRequestReportGPRSEventArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeResetTimerGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeResetTimerGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);

int AsnCC_EncodeSendChargingInformationGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber);


int AsnCC_DecodeSendChargingInformationGPRSArg(
                      unsigned char* encoded, 
                      size_t size, 
                      void** data);


