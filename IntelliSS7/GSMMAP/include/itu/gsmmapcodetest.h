/*
 * Copyright (C) 2000-2000 IntelliNet Technologies, Inc.  All rights reserved.
 *
 *
 * $Id: gsmmapcodetest.h,v 9.1 2005/03/23 12:51:24 cvsadmin Exp $
 *
 * $Log: gsmmapcodetest.h,v $
 * Revision 9.1  2005/03/23 12:51:24  cvsadmin
 * Begin PR6.5
 *
 * Revision 8.2  2005/03/21 13:49:24  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 7.1  2002/08/26 22:08:45  mmiers
 * Begin PR6.2
 *
 * Revision 6.1  2002/02/28 16:13:19  mmiers
 * Begin PR7.
 *
 * Revision 5.1  2001/08/16 20:45:17  mmiers
 * Start PR6.
 *
 * Revision 4.1  2001/05/01 00:53:02  mmiers
 * Begin PR5
 *
 * Revision 3.1  2000/08/15 23:56:36  mmiers
 *
 * Begin round 4.
 *
 * Revision 1.3  2000/04/26 18:13:34  npopov
 * Corrected typos in function names.
 *
 * Revision 1.2  2000/04/25 15:44:27  npopov
 * Fixed typos in function names.
 *
 * Revision 1.1  2000/04/12 16:03:58  npopov
 * Header for regression testing with OSS-vs.-IntelliNet-and-vice-versa cross-encoding/decoding.
 *
 */


#ifndef GSMMAPCODETEST_H
#define GSMMAPCODETEST_H


#ifdef RENAME_API
#define GSMMAP_DecodeActivateSSArg                 ioGSMMAP_DecodeActivateSSArg
#define GSMMAP_DecodeActivateSSRes                 ioGSMMAP_DecodeActivateSSRes
#define GSMMAP_DecodeActivateTraceModeArg          ioGSMMAP_DecodeActivateTraceModeArg
#define GSMMAP_DecodeAlertServiceCentreArg         ioGSMMAP_DecodeAlertServiceCentreArg
#define GSMMAP_DecodeAlertServiceCentreWOResult    ioGSMMAP_DecodeAlertServiceCentreWOResult
#define GSMMAP_DecodeBeginSubscriberActivityArg    ioGSMMAP_DecodeBeginSubscriberActivityArg
#define GSMMAP_DecodeCheckIMEIArg                  ioGSMMAP_DecodeCheckIMEIArg
#define GSMMAP_DecodeCheckIMEIRes                  ioGSMMAP_DecodeCheckIMEIRes
#define GSMMAP_DecodeDeactivateSSArg               ioGSMMAP_DecodeDeactivateSSArg
#define GSMMAP_DecodeDeactivateSSRes               ioGSMMAP_DecodeDeactivateSSRes
#define GSMMAP_DecodeDeactivateTraceModeArg        ioGSMMAP_DecodeDeactivateTraceModeArg
#define GSMMAP_DecodeDeleteSubscriberDataArg       ioGSMMAP_DecodeDeleteSubscriberDataArg
#define GSMMAP_DecodeDeleteSubscriberDataRes       ioGSMMAP_DecodeDeleteSubscriberDataRes
#define GSMMAP_DecodeDialoguePDU                   ioGSMMAP_DecodeDialoguePDU
#define GSMMAP_DecodeEraseSSArg                    ioGSMMAP_DecodeEraseSSArg
#define GSMMAP_DecodeEraseSSRes                    ioGSMMAP_DecodeEraseSSRes
#define GSMMAP_DecodeForwardAccessSignallingArg    ioGSMMAP_DecodeForwardAccessSignallingArg
#define GSMMAP_DecodeForwardSMArg                  ioGSMMAP_DecodeForwardSMArg
#define GSMMAP_DecodeGetPasswordArg                ioGSMMAP_DecodeGetPasswordArg
#define GSMMAP_DecodeGetPasswordRes                ioGSMMAP_DecodeGetPasswordRes
#define GSMMAP_DecodeInformServiceCentreArg        ioGSMMAP_DecodeInformServiceCentreArg
#define GSMMAP_DecodeInsertSubscriberDataArg       ioGSMMAP_DecodeInsertSubscriberDataArg
#define GSMMAP_DecodeInsertSubscriberDataRes       ioGSMMAP_DecodeInsertSubscriberDataRes
#define GSMMAP_DecodeInterrogateSSArg              ioGSMMAP_DecodeInterrogateSSArg
#define GSMMAP_DecodeInterrogateSSRes              ioGSMMAP_DecodeInterrogateSSRes
#define GSMMAP_DecodeNoteInternalHO_Arg            ioGSMMAP_DecodeNoteInternalHO_Arg
#define GSMMAP_DecodeNoteSubscriberPresentArg      ioGSMMAP_DecodeNoteSubscriberPresentArg
#define GSMMAP_DecodePerformHO_Arg                 ioGSMMAP_DecodePerformHO_Arg
#define GSMMAP_DecodePerformHO_Res                 ioGSMMAP_DecodePerformHO_Res
#define GSMMAP_DecodePerformSubsequentHO_Arg       ioGSMMAP_DecodePerformSubsequentHO_Arg
#define GSMMAP_DecodePerformSubsequentHO_Res       ioGSMMAP_DecodePerformSubsequentHO_Res
#define GSMMAP_DecodePrepareHO_Arg                 ioGSMMAP_DecodePrepareHO_Arg
#define GSMMAP_DecodePrepareHO_Res                 ioGSMMAP_DecodePrepareHO_Res
#define GSMMAP_DecodePrepareSubsequentHO_Arg       ioGSMMAP_DecodePrepareSubsequentHO_Arg
#define GSMMAP_DecodePrepareSubsequentHO_Res       ioGSMMAP_DecodePrepareSubsequentHO_Res
#define GSMMAP_DecodeProcessAccessSignallingArg    ioGSMMAP_DecodeProcessAccessSignallingArg
#define GSMMAP_DecodeProcessUnstructuredSS_DataArg ioGSMMAP_DecodeProcessUnstructuredSS_DataArg
#define GSMMAP_DecodeProcessUnstructuredSS_DataRes ioGSMMAP_DecodeProcessUnstructuredSS_DataRes
#define GSMMAP_DecodeProcessUnstructuredSS_RequestArg ioGSMMAP_DecodeProcessUnstructuredSS_RequestArg
#define GSMMAP_DecodeProcessUnstructuredSS_RequestRes ioGSMMAP_DecodeProcessUnstructuredSS_RequestRes
#define GSMMAP_DecodeProvideRoamingNumberArg       ioGSMMAP_DecodeProvideRoamingNumberArg
#define GSMMAP_DecodeProvideRoamingNumberRes       ioGSMMAP_DecodeProvideRoamingNumberRes
#define GSMMAP_DecodeReadyForSMArg                 ioGSMMAP_DecodeReadyForSMArg
#define GSMMAP_DecodeRegisterPasswordArg           ioGSMMAP_DecodeRegisterPasswordArg
#define GSMMAP_DecodeRegisterPasswordRes           ioGSMMAP_DecodeRegisterPasswordRes
#define GSMMAP_DecodeRegisterSSArg                 ioGSMMAP_DecodeRegisterSSArg
#define GSMMAP_DecodeRegisterSSRes                 ioGSMMAP_DecodeRegisterSSRes
#define GSMMAP_DecodeReportSM_DeliveryStatusArg    ioGSMMAP_DecodeReportSM_DeliveryStatusArg
#define GSMMAP_DecodeReportSM_DeliveryStatusRes    ioGSMMAP_DecodeReportSM_DeliveryStatusRes
#define GSMMAP_DecodeResetArg                      ioGSMMAP_DecodeResetArg
#define GSMMAP_DecodeRestoreDataArg                ioGSMMAP_DecodeRestoreDataArg
#define GSMMAP_DecodeRestoreDataRes                ioGSMMAP_DecodeRestoreDataRes
#define GSMMAP_DecodeSendAuthenticationInfoArg     ioGSMMAP_DecodeSendAuthenticationInfoArg
#define GSMMAP_DecodeSendAuthenticationInfoRes     ioGSMMAP_DecodeSendAuthenticationInfoRes
#define GSMMAP_DecodeSendEndSignalArg              ioGSMMAP_DecodeSendEndSignalArg
#define GSMMAP_DecodeSendIMSIArg                   ioGSMMAP_DecodeSendIMSIArg
#define GSMMAP_DecodeSendIMSIRes                   ioGSMMAP_DecodeSendIMSIRes
#define GSMMAP_DecodeSendIdentificationArg         ioGSMMAP_DecodeSendIdentificationArg
#define GSMMAP_DecodeSendIdentificationRes         ioGSMMAP_DecodeSendIdentificationRes
#define GSMMAP_DecodeSendParametersArg             ioGSMMAP_DecodeSendParametersArg
#define GSMMAP_DecodeSendParametersRes             ioGSMMAP_DecodeSendParametersRes
#define GSMMAP_DecodeSendRoutingInfoArg            ioGSMMAP_DecodeSendRoutingInfoArg
#define GSMMAP_DecodeSendRoutingInfoForSMRes       ioGSMMAP_DecodeSendRoutingInfoForSMRes
#define GSMMAP_DecodeSendRoutingInfoRes            ioGSMMAP_DecodeSendRoutingInfoRes
#define GSMMAP_DecodeSendRoutingInfoForSMArg       ioGSMMAP_DecodeSendRoutingInfoForSMArg
#define GSMMAP_DecodeTraceSubscriberActivityArg    ioGSMMAP_DecodeTraceSubscriberActivityArg
#define GSMMAP_DecodeUnstructuredSS_NotifyArg      ioGSMMAP_DecodeUnstructuredSS_NotifyArg
#define GSMMAP_DecodeUnstructuredSS_RequestArg     ioGSMMAP_DecodeUnstructuredSS_RequestArg
#define GSMMAP_DecodeUnstructuredSS_RequestRes     ioGSMMAP_DecodeUnstructuredSS_RequestRes
#define GSMMAP_DecodeUpdateLocationArg             ioGSMMAP_DecodeUpdateLocationArg
#define GSMMAP_DecodeUpdateLocationRes             ioGSMMAP_DecodeUpdateLocationRes
#define GSMMAP_DecodeUserInfo                      ioGSMMAP_DecodeUserInfo
#define GSMMAP_DecodeCancelLocationArg             ioGSMMAP_DecodeCancelLocationArg
#define GSMMAP_DecodePurgeMS_Arg                    ioGSMMAP_DecodePurgeMS_Arg

#define GSMMAP_EncodeDialoguePDU                   ioGSMMAP_EncodeDialoguePDU
#define GSMMAP_EncodeUserInfo                      ioGSMMAP_EncodeUserInfo
#define GSMMAP_SendActivateSSArg                   ioGSMMAP_SendActivateSSArg
#define GSMMAP_SendActivateSSRes                   ioGSMMAP_SendActivateSSRes
#define GSMMAP_SendActivateTraceModeArg            ioGSMMAP_SendActivateTraceModeArg
#define GSMMAP_SendAlertServiceCentreArg           ioGSMMAP_SendAlertServiceCentreArg
#define GSMMAP_SendAlertServiceCentreWOResult      ioGSMMAP_SendAlertServiceCentreWOResult
#define GSMMAP_SendBeginSubscriberActivityArg      ioGSMMAP_SendBeginSubscriberActivityArg
#define GSMMAP_SendCancelLocationArg               ioGSMMAP_SendCancelLocationArg
#define GSMMAP_SendCheckIMEIArg                    ioGSMMAP_SendCheckIMEIArg
#define GSMMAP_SendCheckIMEIRes                    ioGSMMAP_SendCheckIMEIRes
#define GSMMAP_SendDeactivateSSArg                 ioGSMMAP_SendDeactivateSSArg
#define GSMMAP_SendDeactivateSSRes                 ioGSMMAP_SendDeactivateSSRes
#define GSMMAP_SendDeactivateTraceModeArg          ioGSMMAP_SendDeactivateTraceModeArg
#define GSMMAP_SendDeleteSubscriberDataArg         ioGSMMAP_SendDeleteSubscriberDataArg
#define GSMMAP_SendDeleteSubscriberDataRes         ioGSMMAP_SendDeleteSubscriberDataRes
#define GSMMAP_SendEraseSSArg                      ioGSMMAP_SendEraseSSArg
#define GSMMAP_SendEraseSSRes                      ioGSMMAP_SendEraseSSRes
#define GSMMAP_SendForwardAccessSignallingArg      ioGSMMAP_SendForwardAccessSignallingArg
#define GSMMAP_SendForwardSMArg                    ioGSMMAP_SendForwardSMArg
#define GSMMAP_SendGetPasswordArg                  ioGSMMAP_SendGetPasswordArg
#define GSMMAP_SendGetPasswordRes                  ioGSMMAP_SendGetPasswordRes
#define GSMMAP_SendInformServiceCentreArg          ioGSMMAP_SendInformServiceCentreArg
#define GSMMAP_SendInsertSubscriberDataArg         ioGSMMAP_SendInsertSubscriberDataArg
#define GSMMAP_SendInsertSubscriberDataRes         ioGSMMAP_SendInsertSubscriberDataRes
#define GSMMAP_SendInterrogateSSArg                ioGSMMAP_SendInterrogateSSArg
#define GSMMAP_SendInterrogateSSRes                ioGSMMAP_SendInterrogateSSRes
#define GSMMAP_SendNoteInternalHO_Arg              ioGSMMAP_SendNoteInternalHO_Arg
#define GSMMAP_SendNoteSubscriberPresentArg        ioGSMMAP_SendNoteSubscriberPresentArg
#define GSMMAP_SendPerformHO_Arg                   ioGSMMAP_SendPerformHO_Arg
#define GSMMAP_SendPerformHO_Res                   ioGSMMAP_SendPerformHO_Res
#define GSMMAP_SendPerformSubsequentHO_Arg         ioGSMMAP_SendPerformSubsequentHO_Arg
#define GSMMAP_SendPerformSubsequentHO_Res         ioGSMMAP_SendPerformSubsequentHO_Res
#define GSMMAP_SendPrepareHO_Arg                   ioGSMMAP_SendPrepareHO_Arg
#define GSMMAP_SendPrepareHO_Res                   ioGSMMAP_SendPrepareHO_Res
#define GSMMAP_SendPrepareSubsequentHO_Arg         ioGSMMAP_SendPrepareSubsequentHO_Arg
#define GSMMAP_SendPrepareSubsequentHO_Res         ioGSMMAP_SendPrepareSubsequentHO_Res
#define GSMMAP_SendProcessAccessSignallingArg      ioGSMMAP_SendProcessAccessSignallingArg
#define GSMMAP_SendProcessUnstructuredSS_DataArg   ioGSMMAP_SendProcessUnstructuredSS_DataArg
#define GSMMAP_SendProcessUnstructuredSS_RequestArg ioGSMMAP_SendProcessUnstructuredSS_RequestArg
#define GSMMAP_SendProcessUnstructuredSS_DataRes   ioGSMMAP_SendProcessUnstructuredSS_DataRes
#define GSMMAP_SendProcessUnstructuredSS_RequestRes ioGSMMAP_SendProcessUnstructuredSS_RequestRes
#define GSMMAP_SendProvideRoamingNumberArg         ioGSMMAP_SendProvideRoamingNumberArg
#define GSMMAP_SendProvideRoamingNumberRes         ioGSMMAP_SendProvideRoamingNumberRes
#define GSMMAP_SendPurgeMS_Arg                     ioGSMMAP_SendPurgeMS_Arg
#define GSMMAP_SendReadyForSMArg                   ioGSMMAP_SendReadyForSMArg
#define GSMMAP_SendRegisterPasswordArg             ioGSMMAP_SendRegisterPasswordArg
#define GSMMAP_SendRegisterPasswordRes             ioGSMMAP_SendRegisterPasswordRes
#define GSMMAP_SendRegisterSSArg                   ioGSMMAP_SendRegisterSSArg
#define GSMMAP_SendRegisterSSRes                   ioGSMMAP_SendRegisterSSRes
#define GSMMAP_SendReportSM_DeliveryStatusArg      ioGSMMAP_SendReportSM_DeliveryStatusArg
#define GSMMAP_SendReportSM_DeliveryStatusRes      ioGSMMAP_SendReportSM_DeliveryStatusRes
#define GSMMAP_SendResetArg                        ioGSMMAP_SendResetArg
#define GSMMAP_SendRestoreDataArg                  ioGSMMAP_SendRestoreDataArg
#define GSMMAP_SendRestoreDataRes                  ioGSMMAP_SendRestoreDataRes
#define GSMMAP_SendSendAuthenticationInfoArg       ioGSMMAP_SendSendAuthenticationInfoArg
#define GSMMAP_SendSendAuthenticationInfoRes       ioGSMMAP_SendSendAuthenticationInfoRes
#define GSMMAP_SendSendEndSignalArg                ioGSMMAP_SendSendEndSignalArg
#define GSMMAP_SendSendIMSIArg                     ioGSMMAP_SendSendIMSIArg
#define GSMMAP_SendSendIMSIRes                     ioGSMMAP_SendSendIMSIRes
#define GSMMAP_SendSendIdentificationArg           ioGSMMAP_SendSendIdentificationArg
#define GSMMAP_SendSendIdentificationRes           ioGSMMAP_SendSendIdentificationRes
#define GSMMAP_SendSendParametersArg               ioGSMMAP_SendSendParametersArg
#define GSMMAP_SendSendParametersRes               ioGSMMAP_SendSendParametersRes
#define GSMMAP_SendSendRoutingInfoArg              ioGSMMAP_SendSendRoutingInfoArg
#define GSMMAP_SendSendRoutingInfoForSMArg         ioGSMMAP_SendSendRoutingInfoForSMArg
#define GSMMAP_SendSendRoutingInfoForSMRes         ioGSMMAP_SendSendRoutingInfoForSMRes
#define GSMMAP_SendSendRoutingInfoRes              ioGSMMAP_SendSendRoutingInfoRes
#define GSMMAP_SendTraceSubscriberActivityArg      ioGSMMAP_SendTraceSubscriberActivityArg
#define GSMMAP_SendUnstructuredSS_NotifyArg        ioGSMMAP_SendUnstructuredSS_NotifyArg
#define GSMMAP_SendUnstructuredSS_RequestArg       ioGSMMAP_SendUnstructuredSS_RequestArg
#define GSMMAP_SendUnstructuredSS_RequestRes       ioGSMMAP_SendUnstructuredSS_RequestRes
#define GSMMAP_SendUpdateLocationArg               ioGSMMAP_SendUpdateLocationArg
#define GSMMAP_SendUpdateLocationRes               ioGSMMAP_SendUpdateLocationRes

#define NetworkLocUpV2Value           ioNetworkLocUpV2Value
#define GSMMAPNetworkLocUpV2          ioGSMMAPNetworkLocUpV2
#define NetworkLocUpV1Value           ioNetworkLocUpV1Value
#define GSMMAPNetworkLocUpV1          ioGSMMAPNetworkLocUpV1
#define LocationCancelV2Value         ioLocationCancelV2Value
#define GSMMAPLocationCancelV2        ioGSMMAPLocationCancelV2
#define LocationCancelV1Value         ioLocationCancelV1Value
#define GSMMAPLocationCancelV1io      ioGSMMAPLocationCancelV1
#define RoamingNbEnquiryV2Value       ioRoamingNbEnquiryV2Value
#define GSMMAPRoamingNbEnquiryV2      ioGSMMAPRoamingNbEnquiryV2
#define RoamingNbEnquiryV1Value       ioRoamingNbEnquiryV1Value
#define GSMMAPRoamingNbEnquiryV1      ioGSMMAPRoamingNbEnquiryV1
#define LocationInfoRetrievalV2Value  ioLocationInfoRetrievalV2Value
#define GSMMAPLocationInfoRetrievalV2 ioGSMMAPLocationInfoRetrievalV2
#define LocationInfoRetrievalV1Value  ioLocationInfoRetrievalV1Value
#define GSMMAPLocationInfoRetrievalV1 ioGSMMAPLocationInfoRetrievalV1
#define ResetContextV2Value           ioResetContextV2Value
#define GSMMAPResetContextV2          ioGSMMAPResetContextV2
#define ResetContextV1Value           ioResetContextV1Value
#define GSMMAPResetContextV1          ioGSMMAPResetContextV1
#define HandoverControlV2Value        ioHandoverControlV2Value
#define GSMMAPHandoverControlV2       ioGSMMAPHandoverControlV2
#define HandoverControlV1Value        ioHandoverControlV1Value
#define GSMMAPHandoverControlV1       ioGSMMAPHandoverControlV1
#define EquipmentMngtV2Value          ioEquipmentMngtV2Value
#define GSMMAPEquipmentMngtV2         ioGSMMAPEquipmentMngtV2
#define EquipmentMngtV1Value          ioEquipmentMngtV1Value
#define GSMMAPEquipmentMngtV1         ioGSMMAPEquipmentMngtV1
#define InfoRetrievalV2Value          ioInfoRetrievalV2Value
#define GSMMAPInfoRetrievalV2         ioGSMMAPInfoRetrievalV2
#define InfoRetrievalV1Value          ioInfoRetrievalV1Value
#define GSMMAPInfoRetrievalV1         ioGSMMAPInfoRetrievalV1
#define VLRInfoRetrievalV2Value       ioVLRInfoRetrievalV2Value
#define GSMMAPVLRInfoRetrievalV2      ioGSMMAPVLRInfoRetrievalV2
#define SubscriberDataMngtV2Value     ioSubscriberDataMngtV2Value
#define GSMMAPSubscriberDataMngtV2    ioGSMMAPSubscriberDataMngtV2
#define SubscriberDataMngtV1Value     ioSubscriberDataMngtV1Value
#define GSMMAPSubscriberDataMngtV1    ioGSMMAPSubscriberDataMngtV1
#define TracingContextV2Value         ioTracingContextV2Value
#define GSMMAPTracingContextV2        ioGSMMAPTracingContextV2
#define TracingContextV1Value         ioTracingContextV1Value
#define GSMMAPTracingContextV1        ioGSMMAPTracingContextV1
#define NetworkFunctionalSSV2Value    ioNetworkFunctionalSSV2Value
#define GSMMAPNetworkFunctionalSSV2   ioGSMMAPNetworkFunctionalSSV2
#define NetworkFunctionalSSV1Value    ioNetworkFunctionalSSV1Value
#define GSMMAPNetworkFunctionalSSV1   ioGSMMAPNetworkFunctionalSSV1
#define NetworkUnstructuredSSV2Value  ioNetworkUnstructuredSSV2Value
#define GSMMAPNetworkUnstructuredSSV2 ioGSMMAPNetworkUnstructuredSSV2
#define ShortMsgGatewayV2Value        ioShortMsgGatewayV2Value
#define GSMMAPShortMsgGatewayV        ioGSMMAPShortMsgGatewayV2
#define ShortMsgGatewayV1Value        ioShortMsgGatewayV1Value
#define GSMMAPShortMsgGatewayV1       ioGSMMAPShortMsgGatewayV1
#define ShortMsgMORelayV2Value        ioShortMsgMORelayV2Value
#define GSMMAPShortMsgMORelayV2       ioGSMMAPShortMsgMORelayV2
#define ShortMsgMORelayV1Value        ioShortMsgMORelayV1Value
#define GSMMAPShortMsgMORelayV1       ioGSMMAPShortMsgMORelayV1
#define ShortMsgAlertV2Value          ioShortMsgAlertV2Value
#define GSMMAPShortMsgAlertV2         ioGSMMAPShortMsgAlertV2
#define ShortMsgAlertV1Value          ioShortMsgAlertV1Value
#define GSMMAPShortMsgAlertV1         ioGSMMAPShortMsgAlertV1
#define MWDMngtV2Value                ioMWDMngtV2Value
#define GSMMAPMWDMngtV2               ioGSMMAPMWDMngtV2
#define MWDMngtV1Value                ioMWDMngtV1Value
#define GSMMAPMWDMngtV1               ioGSMMAPMWDMngtV1
#define ShortMsgMTV2Value             ioShortMsgMTV2Value
#define GSMMAPShortMsgMTV2            ioGSMMAPShortMsgMTV2
#define IMSIRetrievalV2Value          ioIMSIRetrievalV2Value
#define GSMMAPIMSIRetrievalV2         ioGSMMAPIMSIRetrievalV2
#define MSPurgingV2Value              ioMSPurgingV2Value
#define GSMMAPMSPurgingV2             ioGSMMAPMSPurgingV2
#define GSMMAPShortMsgGatewayV2       ioGSMMAPShortMsgGatewayV2
#define GSMMAPLocationCancelV1        ioGSMMAPLocationCancelV1
#endif /* RENAME_API */

/*** UpdateLocation OPERATION ***/

int ioGSMMAP_SendUpdateLocationArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                  TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeUpdateLocationArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                    void **data );
int ioGSMMAP_SendUpdateLocationRes( ITS_HANDLE handle, ITS_HDR *hdr, 
                                  TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeUpdateLocationRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                    void **data );

/*** CancelLocation OPERATION ***/

int ioGSMMAP_SendCancelLocationArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                  TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeCancelLocationArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                    void **data );

/*** PurgeMS OPERATION ***/

int ioGSMMAP_SendPurgeMS_Arg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                            void *data );
int ioGSMMAP_DecodePurgeMS_Arg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** SendIdentification OPERATION ***/

int ioGSMMAP_SendSendIdentificationArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                      TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeSendIdentificationArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                        void **data );
int ioGSMMAP_SendSendIdentificationRes( ITS_HANDLE handle, ITS_HDR *hdr, 
                                      TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeSendIdentificationRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                        void **data );

/*** PerformHandover OPERATION ***/

int ioGSMMAP_SendPerformHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                              void *data );
int ioGSMMAP_DecodePerformHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int ioGSMMAP_SendPerformHO_Res( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                              void *data );
int ioGSMMAP_DecodePerformHO_Res( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** PrepareHandover OPERATION ***/

int ioGSMMAP_SendPrepareHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                              void *data );
int ioGSMMAP_DecodePrepareHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int ioGSMMAP_SendPrepareHO_Res( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                              void *data );
int ioGSMMAP_DecodePrepareHO_Res( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** SendEndSignal OPERATION ***/

int ioGSMMAP_SendSendEndSignalArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                                 void *data );
int ioGSMMAP_DecodeSendEndSignalArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                   void **data );

/*** ProcessAccessSignalling OPERATION ***/

int ioGSMMAP_SendProcessAccessSignallingArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                           TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeProcessAccessSignallingArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                             void **data );

/*** ForwardAccessSignalling OPERATION ***/

int ioGSMMAP_SendForwardAccessSignallingArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                           TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeForwardAccessSignallingArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                             void **data );

/*** PerformSubsequentHandover OPERATION ***/

int ioGSMMAP_SendPerformSubsequentHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                        TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodePerformSubsequentHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                          void **data );
int ioGSMMAP_SendPerformSubsequentHO_Res( ITS_HANDLE handle, ITS_HDR *hdr, 
                                        TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodePerformSubsequentHO_Res( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                          void **data );

/*** PrepareSubsequentHandover OPERATION ***/

int ioGSMMAP_SendPrepareSubsequentHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                        TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodePrepareSubsequentHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                          void **data );
int ioGSMMAP_SendPrepareSubsequentHO_Res( ITS_HANDLE handle, ITS_HDR *hdr, 
                                        TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodePrepareSubsequentHO_Res( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                          void **data );

/*** SendAuthenticationInfo OPERATION ***/

int ioGSMMAP_SendSendAuthenticationInfoArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                          TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeSendAuthenticationInfoArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                            void **data );
int ioGSMMAP_SendSendAuthenticationInfoRes( ITS_HANDLE handle, ITS_HDR *hdr, 
                                          TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeSendAuthenticationInfoRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                            void **data );

/*** CheckIMEI OPERATION ***/

int ioGSMMAP_SendCheckIMEIArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                             void *data );
int ioGSMMAP_DecodeCheckIMEIArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int ioGSMMAP_SendCheckIMEIRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                             void *data );
int ioGSMMAP_DecodeCheckIMEIRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** SendParameters OPERATION ***/

int ioGSMMAP_SendSendParametersArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                  TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeSendParametersArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                    void **data );
int ioGSMMAP_SendSendParametersRes( ITS_HANDLE handle, ITS_HDR *hdr, 
                                  TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeSendParametersRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                    void **data );

/*** InsertSubscriberData OPERATION ***/

int ioGSMMAP_SendInsertSubscriberDataArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                        TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeInsertSubscriberDataArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                          void **data );
int ioGSMMAP_SendInsertSubscriberDataRes( ITS_HANDLE handle, ITS_HDR *hdr, 
                                        TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeInsertSubscriberDataRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                          void **data );

/*** DeleteSubscriberData OPERATION ***/

int ioGSMMAP_SendDeleteSubscriberDataArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                        TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeDeleteSubscriberDataArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                          void **data );
int ioGSMMAP_SendDeleteSubscriberDataRes( ITS_HANDLE handle, ITS_HDR *hdr, 
                                        TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeDeleteSubscriberDataRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                          void **data );

/*** Reset OPERATION ***/

int ioGSMMAP_SendResetArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                         void *data );
int ioGSMMAP_DecodeResetArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** RestoreData OPERATION ***/

int ioGSMMAP_SendRestoreDataArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                               void *data );
int ioGSMMAP_DecodeRestoreDataArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int ioGSMMAP_SendRestoreDataRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                               void *data );
int ioGSMMAP_DecodeRestoreDataRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** ActivateTraceMode OPERATION ***/

int ioGSMMAP_SendActivateTraceModeArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                     TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeActivateTraceModeArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                       void **data );

/*** DeactivateTraceMode OPERATION ***/

int ioGSMMAP_SendDeactivateTraceModeArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                       TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeDeactivateTraceModeArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                         void **data );

/*** TraceSubscriberActivity OPERATION ***/

int ioGSMMAP_SendTraceSubscriberActivityArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                           TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeTraceSubscriberActivityArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                             void **data );

/*** NoteInternalHandover OPERATION ***/

int ioGSMMAP_SendNoteInternalHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                   TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeNoteInternalHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                     void **data );

/*** SendIMSI OPERATION ***/

int ioGSMMAP_SendSendIMSIArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                            void *data );
int ioGSMMAP_DecodeSendIMSIArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int ioGSMMAP_SendSendIMSIRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                            void *data );
int ioGSMMAP_DecodeSendIMSIRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** SendRoutingInfo OPERATION ***/

int ioGSMMAP_SendSendRoutingInfoArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                   TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeSendRoutingInfoArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                     void **data );
int ioGSMMAP_SendSendRoutingInfoRes( ITS_HANDLE handle, ITS_HDR *hdr, 
                                   TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeSendRoutingInfoRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                     void **data );

/*** ProvideRoamingNumber OPERATION ***/

int ioGSMMAP_SendProvideRoamingNumberArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                        TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeProvideRoamingNumberArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                          void **data );
int ioGSMMAP_SendProvideRoamingNumberRes( ITS_HANDLE handle, ITS_HDR *hdr, 
                                        TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeProvideRoamingNumberRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                          void **data );

/*** RegisterSS OPERATION ***/

int ioGSMMAP_SendRegisterSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                              void *data );
int ioGSMMAP_DecodeRegisterSSArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int ioGSMMAP_SendRegisterSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                              void *data );
int ioGSMMAP_DecodeRegisterSSRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** EraseSS OPERATION ***/

int ioGSMMAP_SendEraseSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                           void *data );
int ioGSMMAP_DecodeEraseSSArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int ioGSMMAP_SendEraseSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                           void *data );
int ioGSMMAP_DecodeEraseSSRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** ActivateSS OPERATION ***/

int ioGSMMAP_SendActivateSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                              void *data );
int ioGSMMAP_DecodeActivateSSArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int ioGSMMAP_SendActivateSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                              void *data );
int ioGSMMAP_DecodeActivateSSRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** DeactivateSS OPERATION ***/

int ioGSMMAP_SendDeactivateSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                                void *data );
int ioGSMMAP_DecodeDeactivateSSArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                  void **data );
int ioGSMMAP_SendDeactivateSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                                void *data );
int ioGSMMAP_DecodeDeactivateSSRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                  void **data );

/*** InterrogateSS OPERATION ***/

int ioGSMMAP_SendInterrogateSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                                 void *data );
int ioGSMMAP_DecodeInterrogateSSArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                   void **data );
int ioGSMMAP_SendInterrogateSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                                 void *data );
int ioGSMMAP_DecodeInterrogateSSRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                   void **data );

/*** ProcessUnstructuredSS-Data OERATION ***/

int ioGSMMAP_SendProcessUnstructuredSS_DataArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                              TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeProcessUnstructuredSS_DataArg( ITS_HANDLE handle, 
                                                TCAP_CPT *cpt, void **data );
int ioGSMMAP_SendProcessUnstructuredSS_DataRes( ITS_HANDLE handle, ITS_HDR *hdr, 
                                              TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeProcessUnstructuredSS_DataRes( ITS_HANDLE handle, 
                                                TCAP_CPT *cpt, void **data );

/*** ProcessUnstructuredSS-Request OERATION ***/

int ioGSMMAP_SendProcessUnstructuredSS_RequestArg( ITS_HANDLE handle, 
                                                 ITS_HDR *hdr, TCAP_CPT *cpt, 
                                                 void *data );
int ioGSMMAP_DecodeProcessUnstructuredSS_RequestArg( ITS_HANDLE handle, 
                                                   TCAP_CPT *cpt, void **data );
int ioGSMMAP_SendProcessUnstructuredSS_RequestRes( ITS_HANDLE handle, 
                                                 ITS_HDR *hdr, TCAP_CPT *cpt, 
                                                 void *data );
int ioGSMMAP_DecodeProcessUnstructuredSS_RequestRes( ITS_HANDLE handle, 
                                                   TCAP_CPT *cpt, void **data );

/*** UnstructuredSS-Request OERATION ***/

int ioGSMMAP_SendUnstructuredSS_RequestArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                          TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeUnstructuredSS_RequestArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                            void **data );
int ioGSMMAP_SendUnstructuredSS_RequestRes( ITS_HANDLE handle, ITS_HDR *hdr, 
                                          TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeUnstructuredSS_RequestRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                            void **data );


/*** UnstructuredSS-Notify OERATION ***/

int ioGSMMAP_SendUnstructuredSS_NotifyArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                         TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeUnstructuredSS_NotifyArg( ITS_HANDLE handle, 
                                           TCAP_CPT *cpt, void **data );

/*** 	RegisterPassword OPERATION ***/

int ioGSMMAP_SendRegisterPasswordArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                    TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeRegisterPasswordArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                      void **data );
int ioGSMMAP_SendRegisterPasswordRes( ITS_HANDLE handle, ITS_HDR *hdr, 
                                    TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeRegisterPasswordRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                      void **data );

/*** GetPassword OPERATION ***/

int ioGSMMAP_SendGetPasswordArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                               void *data );
int ioGSMMAP_DecodeGetPasswordArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                 void **data );
int ioGSMMAP_SendGetPasswordRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                               void *data );
int ioGSMMAP_DecodeGetPasswordRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                 void **data );

/*** BeginSubscriberActivity OPERATION ***/

int ioGSMMAP_SendBeginSubscriberActivityArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                           TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeBeginSubscriberActivityArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                             void **data );

/*** SendRoutingInfoForSM OPERATION ***/

int ioGSMMAP_SendSendRoutingInfoForSMArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                        TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeSendRoutingInfoForSMArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                          void **data );
int ioGSMMAP_SendSendRoutingInfoForSMRes( ITS_HANDLE handle, ITS_HDR *hdr, 
                                        TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeSendRoutingInfoForSMRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                          void **data );

/*** ForwardSM OPERATION ***/

int ioGSMMAP_SendForwardSMArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                             void *data );
int ioGSMMAP_DecodeForwardSMArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** ReportSM-DeliveryStatus OPERATION ***/

int ioGSMMAP_SendReportSM_DeliveryStatusArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                           TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeReportSM_DeliveryStatusArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                             void **data );
int ioGSMMAP_SendReportSM_DeliveryStatusRes( ITS_HANDLE handle, ITS_HDR *hdr, 
                                           TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeReportSM_DeliveryStatusRes( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                             void **data );

/*** NoteSubscriberPresent OPERATION ***/

int ioGSMMAP_SendNoteSubscriberPresentArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                         TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeNoteSubscriberPresentArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                           void **data );

/*** AlertServiceCentreWithoutResult OPERATION ***/

int ioGSMMAP_SendAlertServiceCentreWOResult( ITS_HANDLE handle, ITS_HDR *hdr, 
                                           TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeAlertServiceCentreWOResult( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                             void **data );


/*** InformServiceCentre OPERATION ***/

int ioGSMMAP_SendInformServiceCentreArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                       TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeInformServiceCentreArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                         void **data );

/*** AlertServiceCentre OPERATION ***/

int ioGSMMAP_SendAlertServiceCentreArg( ITS_HANDLE handle, ITS_HDR *hdr, 
                                      TCAP_CPT *cpt, void *data );
int ioGSMMAP_DecodeAlertServiceCentreArg( ITS_HANDLE handle, TCAP_CPT *cpt, 
                                        void **data );

/*** ReadyForSM OPERATION ***/

int ioGSMMAP_SendReadyForSMArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, 
                              void *data );
int ioGSMMAP_DecodeReadyForSMArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** UserInfo OPERATION ***/

int ioGSMMAP_EncodeUserInfo(void *data, int *len, char **buf);

int ioGSMMAP_DecodeUserInfo(char *usrInfo, int len, void **data);

/*** DialoguePDU OPERATION ***/

int ioGSMMAP_EncodeDialoguePDU(PE *pe, void *data, int *len, char **buf);

int ioGSMMAP_DecodeDialoguePDU(char *dlgPDU, int len, void **data);

#endif /* GSMMAPCODETEST_H */
