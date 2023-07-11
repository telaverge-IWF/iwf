/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: IntelliSS7                                                     *
 *                                                                          *
 *     FILE: its_GSMMAP.h                                                   *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: its_GSMMAP.h,v 9.1 2005/03/23 12:51:24 cvsadmin Exp $
 *
 * LOG: $Log: its_GSMMAP.h,v $
 * LOG: Revision 9.1  2005/03/23 12:51:24  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:24  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:45  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:17  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:02  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:56:36  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/04/26 18:13:04  npopov
 * LOG: Corrected typos in function names.
 * LOG:
 * LOG: Revision 2.3  2000/04/25 15:45:15  npopov
 * LOG: Fixed typos in function names.
 * LOG:
 * LOG: Revision 2.2  2000/04/13 21:28:20  mmiers
 * LOG:
 * LOG:
 * LOG: More changes from Saritel integration.
 * LOG:
 * LOG: Revision 2.1  2000/03/31 21:27:19  omayor
 * LOG: Added function to encode/decode user_info, DialoguePDU
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:18:55  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1998/10/21 20:50:32  jpakrasi
 * LOG: Added html doc generation.
 * LOG:
 * LOG: Revision 1.2  1998/10/15 21:54:40  jpakrasi
 * LOG: Added extern "C" to enable functions to be called from C++ code.
 * LOG:
 * LOG: Revision 1.1  1998/08/26 14:54:28  jpakrasi
 * LOG: First time compile on NT.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_GSMMAP_H_
#define _ITS_GSMMAP_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * GSM MAP Messages according to OPERATIONs (43 in all).
 */

/*.interface:GSMMAP
 ****************************************************************************
 *  Interface:
 *      GSMMAP_*
 *
 *  Purpose:
 *      This interface defines the user's C programming model for GSMMAP.
 *      It corresponds to the specifications detailed below:
 *          Draft prETS 300 599: June 1995
 *          European Digital cellular telecommunications system (Phase 2);
 *                  Mobile Application Part (MAP)
 *              Specification GSM 09.02 version 4.11.0
 *
 *  Usage:
 *
 ****************************************************************************/

/*** UpdateLocation OPERATION ***/

int GSMMAP_SendUpdateLocationArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeUpdateLocationArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data );
int GSMMAP_SendUpdateLocationRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeUpdateLocationRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data );

/*** CancelLocation OPERATION ***/

int GSMMAP_SendCancelLocationArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeCancelLocationArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data );

/*** PurgeMS OPERATION ***/

int GSMMAP_SendPurgeMS_Arg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                            void *data );
int GSMMAP_DecodePurgeMS_Arg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** SendIdentification OPERATION ***/

int GSMMAP_SendSendIdentificationArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                      TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeSendIdentificationArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                        void **data );
int GSMMAP_SendSendIdentificationRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                      TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeSendIdentificationRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                        void **data );

/*** PerformHandover OPERATION ***/

int GSMMAP_SendPerformHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                              void *data );
int GSMMAP_DecodePerformHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int GSMMAP_SendPerformHO_Res( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                              void *data );
int GSMMAP_DecodePerformHO_Res( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** PrepareHandover OPERATION ***/

int GSMMAP_SendPrepareHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                              void *data );
int GSMMAP_DecodePrepareHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int GSMMAP_SendPrepareHO_Res( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                              void *data );
int GSMMAP_DecodePrepareHO_Res( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** SendEndSignal OPERATION ***/

int GSMMAP_SendSendEndSignalArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                                 void *data );
int GSMMAP_DecodeSendEndSignalArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                   void **data );

/*** ProcessAccessSignalling OPERATION ***/

int GSMMAP_SendProcessAccessSignallingArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                           TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeProcessAccessSignallingArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                             void **data );

/*** ForwardAccessSignalling OPERATION ***/

int GSMMAP_SendForwardAccessSignallingArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                           TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeForwardAccessSignallingArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                             void **data );

/*** PerformSubsequentHandover OPERATION ***/

int GSMMAP_SendPerformSubsequentHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data );
int GSMMAP_DecodePerformSubsequentHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data );
int GSMMAP_SendPerformSubsequentHO_Res( ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data );
int GSMMAP_DecodePerformSubsequentHO_Res( ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data );

/*** PrepareSubsequentHandover OPERATION ***/

int GSMMAP_SendPrepareSubsequentHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data );
int GSMMAP_DecodePrepareSubsequentHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data );
int GSMMAP_SendPrepareSubsequentHO_Res( ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data );
int GSMMAP_DecodePrepareSubsequentHO_Res( ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data );

/*** SendAuthenticationInfo OPERATION ***/

int GSMMAP_SendSendAuthenticationInfoArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                          TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeSendAuthenticationInfoArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                            void **data );
int GSMMAP_SendSendAuthenticationInfoRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                          TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeSendAuthenticationInfoRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                            void **data );

/*** CheckIMEI OPERATION ***/

int GSMMAP_SendCheckIMEIArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                             void *data );
int GSMMAP_DecodeCheckIMEIArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int GSMMAP_SendCheckIMEIRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                             void *data );
int GSMMAP_DecodeCheckIMEIRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** SendParameters OPERATION ***/

int GSMMAP_SendSendParametersArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeSendParametersArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data );
int GSMMAP_SendSendParametersRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeSendParametersRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data );

/*** InsertSubscriberData OPERATION ***/

int GSMMAP_SendInsertSubscriberDataArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeInsertSubscriberDataArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data );
int GSMMAP_SendInsertSubscriberDataRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeInsertSubscriberDataRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data );

/*** DeleteSubscriberData OPERATION ***/

int GSMMAP_SendDeleteSubscriberDataArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeDeleteSubscriberDataArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data );
int GSMMAP_SendDeleteSubscriberDataRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeDeleteSubscriberDataRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data );

/*** Reset OPERATION ***/

int GSMMAP_SendResetArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                         void *data );
int GSMMAP_DecodeResetArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** RestoreData OPERATION ***/

int GSMMAP_SendRestoreDataArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                               void *data );
int GSMMAP_DecodeRestoreDataArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int GSMMAP_SendRestoreDataRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                               void *data );
int GSMMAP_DecodeRestoreDataRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** ActivateTraceMode OPERATION ***/

int GSMMAP_SendActivateTraceModeArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                     TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeActivateTraceModeArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                       void **data );

/*** DeactivateTraceMode OPERATION ***/

int GSMMAP_SendDeactivateTraceModeArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeDeactivateTraceModeArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data );

/*** TraceSubscriberActivity OPERATION ***/

int GSMMAP_SendTraceSubscriberActivityArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                           TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeTraceSubscriberActivityArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                             void **data );

/*** NoteInternalHandover OPERATION ***/

int GSMMAP_SendNoteInternalHO_Arg( ITS_HANDLE handle, ITS_HDR *hdr,
                                   TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeNoteInternalHO_Arg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                     void **data );

/*** SendIMSI OPERATION ***/

int GSMMAP_SendSendIMSIArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                            void *data );
int GSMMAP_DecodeSendIMSIArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int GSMMAP_SendSendIMSIRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                            void *data );
int GSMMAP_DecodeSendIMSIRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** SendRoutingInfo OPERATION ***/

int GSMMAP_SendSendRoutingInfoArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                   TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeSendRoutingInfoArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                     void **data );
int GSMMAP_SendSendRoutingInfoRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                   TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeSendRoutingInfoRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                     void **data );

/*** ProvideRoamingNumber OPERATION ***/

int GSMMAP_SendProvideRoamingNumberArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeProvideRoamingNumberArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data );
int GSMMAP_SendProvideRoamingNumberRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeProvideRoamingNumberRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data );

/*** RegisterSS OPERATION ***/

int GSMMAP_SendRegisterSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                              void *data );
int GSMMAP_DecodeRegisterSSArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int GSMMAP_SendRegisterSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                              void *data );
int GSMMAP_DecodeRegisterSSRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** EraseSS OPERATION ***/

int GSMMAP_SendEraseSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                           void *data );
int GSMMAP_DecodeEraseSSArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int GSMMAP_SendEraseSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                           void *data );
int GSMMAP_DecodeEraseSSRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** ActivateSS OPERATION ***/

int GSMMAP_SendActivateSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                              void *data );
int GSMMAP_DecodeActivateSSArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );
int GSMMAP_SendActivateSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                              void *data );
int GSMMAP_DecodeActivateSSRes( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** DeactivateSS OPERATION ***/

int GSMMAP_SendDeactivateSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                                void *data );
int GSMMAP_DecodeDeactivateSSArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                  void **data );
int GSMMAP_SendDeactivateSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                                void *data );
int GSMMAP_DecodeDeactivateSSRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                  void **data );

/*** InterrogateSS OPERATION ***/

int GSMMAP_SendInterrogateSSArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                                 void *data );
int GSMMAP_DecodeInterrogateSSArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                   void **data );
int GSMMAP_SendInterrogateSSRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                                 void *data );
int GSMMAP_DecodeInterrogateSSRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                   void **data );

/*** ProcessUnstructuredSS-Data OERATION ***/

int GSMMAP_SendProcessUnstructuredSS_DataArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                              TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeProcessUnstructuredSS_DataArg( ITS_HANDLE handle,
                                                TCAP_CPT *cpt, void **data );
int GSMMAP_SendProcessUnstructuredSS_DataRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                              TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeProcessUnstructuredSS_DataRes( ITS_HANDLE handle,
                                                TCAP_CPT *cpt, void **data );

/*** ProcessUnstructuredSS-Request OERATION ***/

int GSMMAP_SendProcessUnstructuredSS_RequestArg( ITS_HANDLE handle,
                                                 ITS_HDR *hdr, TCAP_CPT *cpt,
                                                 void *data );
int GSMMAP_DecodeProcessUnstructuredSS_RequestArg( ITS_HANDLE handle,
                                                   TCAP_CPT *cpt, void **data );
int GSMMAP_SendProcessUnstructuredSS_RequestRes( ITS_HANDLE handle,
                                                 ITS_HDR *hdr, TCAP_CPT *cpt,
                                                 void *data );
int GSMMAP_DecodeProcessUnstructuredSS_RequestRes( ITS_HANDLE handle,
                                                   TCAP_CPT *cpt, void **data );

/*** UnstructuredSS-Request OERATION ***/

int GSMMAP_SendUnstructuredSS_RequestArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                          TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeUnstructuredSS_RequestArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                            void **data );
int GSMMAP_SendUnstructuredSS_RequestRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                          TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeUnstructuredSS_RequestRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                            void **data );


/*** UnstructuredSS-Notify OERATION ***/

int GSMMAP_SendUnstructuredSS_NotifyArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                         TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeUnstructuredSS_NotifyArg( ITS_HANDLE handle,
                                           TCAP_CPT *cpt, void **data );

/***    RegisterPassword OPERATION ***/

int GSMMAP_SendRegisterPasswordArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeRegisterPasswordArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data );
int GSMMAP_SendRegisterPasswordRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeRegisterPasswordRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data );

/*** GetPassword OPERATION ***/

int GSMMAP_SendGetPasswordArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                               void *data );
int GSMMAP_DecodeGetPasswordArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                 void **data );
int GSMMAP_SendGetPasswordRes( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                               void *data );
int GSMMAP_DecodeGetPasswordRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                 void **data );

/*** BeginSubscriberActivity OPERATION ***/

int GSMMAP_SendBeginSubscriberActivityArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                           TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeBeginSubscriberActivityArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                             void **data );

/*** SendRoutingInfoForSM OPERATION ***/

int GSMMAP_SendSendRoutingInfoForSMArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeSendRoutingInfoForSMArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data );
int GSMMAP_SendSendRoutingInfoForSMRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeSendRoutingInfoForSMRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data );

/*** ForwardSM OPERATION ***/

int GSMMAP_SendForwardSMArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                             void *data );
int GSMMAP_DecodeForwardSMArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** ReportSM-DeliveryStatus OPERATION ***/

int GSMMAP_SendReportSM_DeliveryStatusArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                           TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeReportSM_DeliveryStatusArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                             void **data );
int GSMMAP_SendReportSM_DeliveryStatusRes( ITS_HANDLE handle, ITS_HDR *hdr,
                                           TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeReportSM_DeliveryStatusRes( ITS_HANDLE handle, TCAP_CPT *cpt,
                                             void **data );

/*** NoteSubscriberPresent OPERATION ***/

int GSMMAP_SendNoteSubscriberPresentArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                         TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeNoteSubscriberPresentArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                           void **data );

/*** AlertServiceCentreWithoutResult OPERATION ***/

int GSMMAP_SendAlertServiceCentreWOResult( ITS_HANDLE handle, ITS_HDR *hdr,
                                           TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeAlertServiceCentreWOResult( ITS_HANDLE handle, TCAP_CPT *cpt,
                                             void **data );


/*** InformServiceCentre OPERATION ***/

int GSMMAP_SendInformServiceCentreArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeInformServiceCentreArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data );

/*** AlertServiceCentre OPERATION ***/

int GSMMAP_SendAlertServiceCentreArg( ITS_HANDLE handle, ITS_HDR *hdr,
                                      TCAP_CPT *cpt, void *data );
int GSMMAP_DecodeAlertServiceCentreArg( ITS_HANDLE handle, TCAP_CPT *cpt,
                                        void **data );

/*** ReadyForSM OPERATION ***/

int GSMMAP_SendReadyForSMArg( ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt,
                              void *data );
int GSMMAP_DecodeReadyForSMArg( ITS_HANDLE handle, TCAP_CPT *cpt, void **data );

/*** UserInfo OPERATION ***/

int GSMMAP_EncodeUserInfo(void *data, int *len, char **buf);

int GSMMAP_DecodeUserInfo(char *usrInfo, int len, void **data);

/*** DialoguePDU OPERATION ***/

int GSMMAP_EncodeDialoguePDU(PE *pe, void *data, int *len, char **buf);

int GSMMAP_DecodeDialoguePDU(char *dlgPDU, int len, void **data);

/* To turn on or off the gsm printout */
extern int gsm_debug;

#ifdef __cplusplus
}
#endif

#endif /* _ITS_GSMMAP_H_ */
