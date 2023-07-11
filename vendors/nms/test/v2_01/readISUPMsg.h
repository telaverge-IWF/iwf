/****************************************************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: readISUPMsg.h,v 9.1 2005/03/23 12:56:17 cvsadmin Exp $
 *
 * LOG: $Log: readISUPMsg.h,v $
 * LOG: Revision 9.1  2005/03/23 12:56:17  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:43  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:11:10  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:15:06  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.1  2001/09/05 22:01:57  mmiers
 * LOG: Add two tests.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:36  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:07  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:11:14  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.1  2000/07/12 16:13:36  hxing
 * LOG: Reuse part of what cbascon did for Newnet to test the NMS(ISUP) vendor
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ifndef READ_ISUP_MSG_H
#define READ_ISUP_MSG_H


#include <stdio.h>

#include <itu/isup.h>
#include <ansi/isup.h>


#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/* used to get IE parameter len in Hex */
#define BASE_16            16


/*
#define BUILD_ISUP_MSG_FROM_FILE
*/

int GetOctetsFromStr(ITS_OCTET *array, int nOctets);

ITS_UINT GetUIntFromStrToken();
ITS_USHORT GetUShortFromStrToken();

int NumOfOctets4Digits(ITS_OCTET nDigits);
int ReadISUPMsg(ITS_OCTET isupMsgType, char *filename, ITS_ISUP_IE *ie,
                int *ieCount);


/*
 * Common Parameters to ANSI & CCITT
 */

int ReadMessageInPAMPar(char *buf, ITS_ISUP_IE *ie);
int ReadAccessTransportPar(char *buf, ITS_ISUP_IE *ie);
int ReadAutoCongestionLvlPar(char *buf, ITS_ISUP_IE *ie);
int ReadBackwardCallIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadCallReferencePar(char *buf, ITS_ISUP_IE *ie);
int ReadCalledPartyNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadCallingPartyNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadCallingPartyCategoryPar(char *buf, ITS_ISUP_IE *ie);
int ReadCauseInd(char *buf, ITS_ISUP_IE *ie);
int ReadChargeNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadCircuitStateIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadConnectRequestPar(char *buf, ITS_ISUP_IE *ie);
int ReadContinuityIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadEOPPar(char *buf, ITS_ISUP_IE *ie);
int ReadEventInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadForwardCallIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadGenericDigitsPar(char *buf, ITS_ISUP_IE *ie);
int ReadInfoIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadInfoReqIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadNatureOfConnectionIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadNotificationIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadOptBackwardCallIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadOrigCalledNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadRangeAndStatusPar(char *buf, ITS_ISUP_IE *ie);
int ReadRedirectingNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadRedirectionInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadServiceActivationPar(char *buf, ITS_ISUP_IE *ie);
int ReadSuspendResumeIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadTransactionReqPar(char *buf, ITS_ISUP_IE *ie);
int ReadTransitNetworkSelectionPar(char *buf, ITS_ISUP_IE *ie);
int ReadUserServiceInfoPar(char *buf, ITS_ISUP_IE *ie);


/*
 * ANSI Parameters
 */
#ifdef ANSI

int ReadBusinessGrpPar(char *buf, ITS_ISUP_IE *ie);
int ReadCarrierIdPar(char *buf, ITS_ISUP_IE *ie);
int ReadCarrierSelectionInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadCircuitGrpCharIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadCircuitGrpSupervisionMsgTypIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadCircuitIdNamePar(char *buf, ITS_ISUP_IE *ie);
int ReadCircuitValRespIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadCLLICodePar(char *buf, ITS_ISUP_IE *ie);
int ReadEgressServicePar(char *buf, ITS_ISUP_IE *ie);
int ReadGenericAddrPar(char *buf, ITS_ISUP_IE *ie);
int ReadJurisdictionInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadNetworkTransportPar(char *buf, ITS_ISUP_IE *ie);
int ReadOrigLineInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadOutgoingTrunkGrpNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadServiceCodePar(char *buf, ITS_ISUP_IE *ie);
int ReadSpecialProcessingReqPar(char *buf, ITS_ISUP_IE *ie);

#endif /* ANSI */


/*
 * CCITT Parameters
 */
#ifdef CCITT

int ReadAccessDeliveryInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadCallDiversionInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadCallHistoryInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadClosedUserGroupInterlockCodePar(char *buf, ITS_ISUP_IE *ie);
int ReadConnectedNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadEchoControlInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadFacilityIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadFreephoneIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadGenericNumberPar(char *buf, ITS_ISUP_IE *ie);
int ReadGenericNotificationPar(char *buf, ITS_ISUP_IE *ie);
int ReadGenericReferencePar(char *buf, ITS_ISUP_IE *ie);
int ReadHopCounterPar(char *buf, ITS_ISUP_IE *ie);
int ReadLocationNumberPar(char *buf, ITS_ISUP_IE *ie);
int ReadMCIDRequestIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadMCIDResponseIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadMLPPPrecedencePar(char *buf, ITS_ISUP_IE *ie);
int ReadMessageCompInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadNetworkSpecificFacilityPar(char *buf, ITS_ISUP_IE *ie);
int ReadOptionalForwardCallIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadOrigISCPointCodePar(char *buf, ITS_ISUP_IE *ie);
int ReadParamCompInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadPropagationDelayCounterPar(char *buf, ITS_ISUP_IE *ie);
int ReadRedirectionNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadRedirectionNumRestrictPar(char *buf, ITS_ISUP_IE *ie);
int ReadRemoteOperationsPar(char *buf, ITS_ISUP_IE *ie);
int ReadSignallingPointCodePar(char *buf, ITS_ISUP_IE *ie);
int ReadSubsequentNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadTransmissionMediumRequirementPar(char *buf, ITS_ISUP_IE *ie);
int ReadTransmissionMediumRequirementPrimePar(char *buf, ITS_ISUP_IE *ie);
int ReadTransmissionMediumUsedPar(char *buf, ITS_ISUP_IE *ie);
int ReadUserServiceInfoPrimePar(char *buf, ITS_ISUP_IE *ie);
int ReadUserTeleserviceInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadUserToUserIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadUserToUserInfoPar(char *buf, ITS_ISUP_IE *ie);


#endif /* CCITT */



#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */



#endif /*  READ_ISUP_MSG_H */

