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
 *  ID: $Id: printISUPMsg.c,v 9.2 2006/01/09 06:40:06 omayor Exp $
 *
 * LOG: $Log: printISUPMsg.c,v $
 * LOG: Revision 9.2  2006/01/09 06:40:06  omayor
 * LOG: Added support for ITU ISUP 99.(skatta)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:07  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:54:19  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.1.6.1  2004/02/12 13:31:13  sjaddu
 * LOG: Handling state change event in app.
 * LOG:
 * LOG: Revision 7.3.2.1  2003/05/07 11:10:03  ssingh
 * LOG: Conformation Indication related code removed. Not in Use.
 * LOG:
 * LOG: Revision 7.3  2003/01/29 12:11:17  ssingh
 * LOG: Changed ISUP_ReceiveMsg function for VCIC offset increment.
 * LOG:
 * LOG: Revision 7.2  2003/01/17 16:24:44  sjaddu
 * LOG: vcic changes.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:38  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.4  2002/08/01 16:01:46  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.3.2.8  2002/07/31 19:13:27  ssingh
 * LOG: Changes done to support ANSI95 related new params.
 * LOG:
 * LOG: Revision 1.3.2.7  2002/07/25 21:15:00  ssingh
 * LOG: Indication Handling in ISUP_ReceiveMsg.
 * LOG:
 * LOG: Revision 1.3.2.6  2002/07/06 06:16:21  hbalimid
 * LOG: Took care of all the warnings.
 * LOG:
 * LOG: Revision 1.3.2.5  2002/07/04 23:33:23  hbalimid
 * LOG: FAC Inidication taken care of.
 * LOG:
 * LOG: Revision 1.3.2.4  2002/07/04 20:50:00  hbalimid
 * LOG: correct version of printISUPMsg.c
 * LOG:
 * LOG: Revision 1.3  2002/06/23 23:27:27  hbalimid
 * LOG: ITU97 specific parameters in Place.
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:48  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/04/06 22:43:29  ssharma
 * LOG: reorganized and added files for xml based ISUP Functional test
 * LOG:
 * LOG: Revision 1.4  2002/02/26 23:53:57  ssharma
 * LOG: Handle timer and error indications.
 * LOG:
 * LOG: Revision 1.3  2002/02/22 22:37:37  ssharma
 * LOG: Minor modifications.
 * LOG:
 * LOG: Revision 1.2  2002/02/05 20:19:53  ssharma
 * LOG: IntelliNet ISUP stack test directory.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/29 20:32:12  ssharma
 * LOG: Functional test for IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/23 18:14:44  ssharma
 * LOG: Interactive functional test for IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:08  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 1.3  2001/02/05 16:06:16  hxing
 * LOG: Remove warnings
 * LOG:
 * LOG: Revision 1.2  2000/12/12 16:49:09  hxing
 * LOG: testing
 * LOG:
 * LOG: Revision 1.1  2000/12/11 23:14:38  hxing
 * LOG: Add testing files
 * LOG:
 * LOG: Revision 3.2  2000/10/19 14:26:57  labuser
 * LOG: Debug in Solaris
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:11:12  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.8  2000/08/08 17:03:45  hxing
 * LOG: More testing for ANSI
 * LOG:
 * LOG: Revision 1.7  2000/07/27 23:00:19  hxing
 * LOG: Testing with more optional IEs
 * LOG:
 * LOG: Revision 1.6  2000/07/24 21:24:06  hxing
 * LOG: Fix bug with ie translation
 * LOG:
 * LOG: Revision 1.5  2000/07/21 21:18:22  hxing
 * LOG: Add print routing label
 * LOG:
 * LOG: Revision 1.4  2000/07/20 23:07:47  hxing
 * LOG: IAM is sent out correctly.
 * LOG:
 * LOG: Revision 1.3  2000/07/17 20:17:21  hxing
 * LOG: Testing
 * LOG:
 * LOG: Revision 1.2  2000/07/14 22:50:41  hxing
 * LOG: Add more print
 * LOG:
 * LOG: Revision 1.1  2000/07/12 16:13:35  hxing
 * LOG: Reuse part of what cbascon did for Newnet to test the NMS(ISUP) vendor
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>

#include <its.h>
#include <its_redundancy.h>

#if defined(CCITT)
#include <itu/isup.h>
#include <itu/mtp3.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#include <ansi/mtp3.h>
#endif

#include "printISUPMsg.h"

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintTimeout(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Timeout Data \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("Timer Id: 0x%04x \n", ie->param_data.timerData.timerId);
    printf("SIO: 0x%04x \n", ie->param_data.timerData.sio);
    printf("CIC: 0x%04x \n", ie->param_data.timerData.cic);
    printf("OPC: 0x%04x \n", ie->param_data.timerData.opc);
    printf("DPC: 0x%04x \n", ie->param_data.timerData.dpc);
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintError(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Error Data \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("Error Id: 0x%04x \n", ie->param_data.errorData.errorId);
    printf("SIO: 0x%04x \n", ie->param_data.errorData.sio);
    printf("CIC: 0x%04x \n", ie->param_data.errorData.cic);
    printf("OPC: 0x%04x \n", ie->param_data.errorData.opc);
    printf("DPC: 0x%04x \n", ie->param_data.errorData.dpc);
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the given ISUP IE array
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
PrintISUPMsg(const ITS_ISUP_IE *ie, int ieCount)
{
    int i;
    int result = ITS_SUCCESS;

    /* Make sure ieCount > 0 */
    if (ieCount <= 0)
    {
        printf("PrintISUPMsg: No IEs for this message \n");
        
        return result;
    }

    if ( ie == NULL)
    {
        printf("PrintISUPMsg: Error, IE Array = NULL \n");

        return (!ITS_SUCCESS);
    }

    for (i = 0; i < ieCount; ++i)
    {
        switch ( (int)ie[i].param_id )
        {
        case ISUP_PRM_ACCESS_TRANSPORT:
            PrintAccessTransportPar(&ie[i]);
            break;

        case ISUP_PRM_AUTO_CONGEST_LEVEL:
            PrintAutoCongestionLvlPar(&ie[i]);
            break;

        case ISUP_PRM_BKWD_CALL_INDICATORS:
            PrintBackwardCallIndPar(&ie[i]);
            break;

        case ISUP_PRM_CALL_REF:
            PrintCallRefPar(&ie[i]);
            break;

        case ISUP_PRM_CALLED_PARTY_NUM:
            PrintCalledPartyNumPar(&ie[i]);
            break;

        case ISUP_PRM_CALLING_PARTY_CATEGORY:
            PrintCallingPartyCategoryPar(&ie[i]);
            break;

        case ISUP_PRM_CALLING_PARTY_NUM:
            PrintCallingPartyNumPar(&ie[i]);
            break;

        case ISUP_PRM_CAUSE_INDICATORS:
            PrintCauseIndPar(&ie[i]);
            break;

        case ISUP_PRM_CONNECTION_REQ:
            PrintConnectRequestPar(&ie[i]);
            break;

        case ISUP_PRM_CONTINUITY_INDICATORS:
            PrintContinuityIndPar(&ie[i]);
            break;

        case ISUP_PRM_CKT_GRP_SUPRVN_MT_IND:
            PrintCircuitGrpSupervisionMsgTypIndPar(&ie[i]);
            break;

        case ISUP_PRM_CKT_STATE_INDICATOR:
            PrintCircuitStateIndPar(&ie[i]);
            break;

        case ISUP_PRM_EOP:
            PrintEOPPar(&ie[i]);
            break;

        case ISUP_PRM_EVENT_INFO:
            PrintEventInfoPar(&ie[i]);
            break;

        case ISUP_PRM_FWD_CALL_INDICATORS:
            PrintForwCallIndPar(&ie[i]);
            break;

        case ISUP_PRM_GENERIC_DIGITS:
            PrintGenericDigitsPar(&ie[i]);
            break;

        case ISUP_PRM_INFO_INDICATORS:
            PrintInfoIndPar(&ie[i]);
            break;

        case ISUP_PRM_INFO_REQ_INDICATORS:
            PrintInfoReqIndPar(&ie[i]);
            break;

        case ISUP_PRM_NATURE_CONN_INDICATORS:
            PrintNatureOfConnectionIndPar(&ie[i]);
            break;

        case ISUP_PRM_OPT_BKWD_CALL_INDICATORS:
            PrintOptBackwardCallIndPar(&ie[i]);
            break;

        case ISUP_PRM_ORIG_CALLED_NUM:
            PrintOrigCalledNumPar(&ie[i]);
            break;

        case ISUP_PRM_RANGE_STATUS:
            PrintRangeAndStatusPar(&ie[i]);
            break;

        case ISUP_PRM_REDIRECTING_NUM:
            PrintRedirectingNumPar(&ie[i]);
            break;

        case ISUP_PRM_REDIRECTION_INFO:
            PrintRedirectionInfoPar(&ie[i]);
            break;

        case ISUP_PRM_SERVICE_ACTIVATION:
            PrintServiceActivationPar(&ie[i]);
            break;

        case ISUP_PRM_SUSP_RESUM_INDICATORS:
            PrintSuspendResumeIndPar(&ie[i]);
            break;

        case ISUP_PRM_TRANSIT_NTWK_SELECT:
            PrintTransitNetworkSelectionPar(&ie[i]);
            break;

        case ISUP_PRM_USER_SERVICE_INFO:
            PrintUserServiceInfoPar(&ie[i]);
            break;
        
        case ISUP_PRM_ROUTING_LABEL:
            PrintRoutingLabel(&ie[i]);
            break;

        case ISUP_PRM_MSG_IN_PAM:
            PrintMessageInPAMPar(&ie[i]);
            break;

/* ANSI Specific Parameters */
#if defined(ANSI)
        case ISUP_PRM_BUSINESS_GROUP:
            PrintBusinessGrpPar(&ie[i]);
            break;

        case ISUP_PRM_CARRIER_ID:
            PrintCarrierIdPar(&ie[i]);
            break;

        case ISUP_PRM_CARRIER_SELECTION_INFO:
            PrintCarrierSelectionInfoPar(&ie[i]);
            break;

        case ISUP_PRM_CHARGE_NUMBER:
            PrintChargeNumPar(&ie[i]);
            break;

        case ISUP_PRM_CKT_VALIDATION_RESP:
            PrintCircuitValRespIndPar(&ie[i]);
            break;

        case ISUP_PRM_CKT_GRP_CHARACTERISTIC:
            PrintCircuitGrpCharIndPar(&ie[i]);
            break;

        case ISUP_PRM_CKT_IDENTIFICATION_NAME:
            PrintCircuitIdNamePar(&ie[i]);
            break;

        case ISUP_PRM_CLLI_CODE:
            PrintCLLICodePar(&ie[i]);
            break;

        case ISUP_PRM_EGRESS_SERVICE:
            PrintEgressServicePar(&ie[i]);
            break;

        case ISUP_PRM_GENERIC_ADDR:
            PrintGenericAddrPar(&ie[i]);
            break;

        case ISUP_PRM_JURISDICTION:
            PrintJurisdictionPar(&ie[i]);
            break;

        case ISUP_PRM_NTWK_TRANSPORT:
            PrintNetworkTransportPar(&ie[i]);
            break;

        case ISUP_PRM_NOTIFICATION:
            PrintNotificationIndPar(&ie[i]);
            break;

        case ISUP_PRM_ORIG_LINE_INFO:
            PrintOrigLineInfoPar(&ie[i]);
            break;

        case ISUP_PRM_OUTGOING_TRUNK_GRP_NUM:
            PrintOutgoingTrunkGrpNumPar(&ie[i]);
            break;

        case ISUP_PRM_SERVICE_CODE:
            PrintServiceCodePar(&ie[i]);
            break;

        case ISUP_PRM_SPECIAL_PROCESS_REQUEST:
            PrintSpecialProcessReqPar(&ie[i]);
            break;

        case ISUP_PRM_TRANSACTION_REQUEST:
            PrintTransactionReqPar(&ie[i]);
            break;

#endif /* ANSI specific parameter Names */


/* ITU Specific Parameters */
#if defined(CCITT)
        case ISUP_PRM_ACCESS_DELIVERY_INFO:
            PrintAccessDeliveryInfoPar(&ie[i]);
            break;

        case ISUP_PRM_CALL_DIVERSION_INFO:
            PrintCallDiversionInfoPar(&ie[i]);
            break;

        case ISUP_PRM_CALL_HISTORY_INFO:
            PrintCallHistoryInfoPar(&ie[i]);
            break;

        case ISUP_PRM_CONNECTED_NUM:
            PrintConnectedNumPar(&ie[i]);
            break;

        case ISUP_PRM_CLOSED_USR_GRP_INTRLCK_CODE:
            PrintClosedUserGrpIntrlckCodePar(&ie[i]);
            break;

        case ISUP_PRM_ECHO_CTRL_INFO:
            PrintEchoControlInfoPar(&ie[i]);
            break;

        case ISUP_PRM_NTWK_SPECIFIC_FACILITIES:
            PrintNetworkSpecificFacilityPar(&ie[i]);
            break;

        case ISUP_PRM_FACILITY_INDICATOR:
            PrintFacilityIndPar(&ie[i]);
            break;

        case ISUP_PRM_FREEPHONE_INDICATORS:
            PrintAccessTransportPar(&ie[i]);
            break;

        case ISUP_PRM_GENERIC_NOTIFICATION:
            PrintGenericNotificationIndPar(&ie[i]);
            break;

        case ISUP_PRM_GENERIC_NUM:
            PrintGenericNumberPar(&ie[i]);
            break;

        case ISUP_PRM_GENERIC_REF:
            PrintGenericReferencPar(&ie[i]);
            break;

#if 0
        /* The Hop Counter parameter format is not provided at the */
        /* current time.                                           */
        /* Hop Counter Param Definition is not in ITU93;
         * defined in ITU97 only */
        case ISUP_PRM_HOP_COUNTER:
            PrintHopCounterPar(&ie[i]);
            break;
#endif

        case ISUP_PRM_LOCATION_NUM:
            PrintLocationNumberPar(&ie[i]);
            break;

        case ISUP_PRM_MCID_REQ_INDICATOR:
            PrintMCIDRequestIndPar(&ie[i]);
            break;

        case ISUP_PRM_MCID_RESP_INDICATOR:
            PrintMCIDResponseIndPar(&ie[i]);
            break;

        case ISUP_PRM_MLPP_PRECEDENCE:
            PrintMLPPPrecedencePar(&ie[i]);
            break;

        case ISUP_PRM_MSG_COMPAT_INFO:
            PrintMsgCompatibiltyInfoPar(&ie[i]);
            break;

        case ISUP_PRM_OPT_FWD_CALL_INDICATORS:
            PrintOptForwardCallIndPar(&ie[i]);
            break;

        case ISUP_PRM_ORIG_ISC_PC:
            PrintOrigISCPointCodePar(&ie[i]);
            break;

        case ISUP_PRM_PARAM_COMPAT_INFO:
            PrintParamCompInfoPar(&ie[i]);
            break;

        case ISUP_PRM_PROP_DELAY_COUNTER:
            PrintPropDelayCounterPar(&ie[i]);
            break;

        case ISUP_PRM_REDIRECTION_NUM:
            PrintRedirectionNumPar(&ie[i]);
            break;

        case ISUP_PRM_REDIRECTION_NUM_RESTRICT:
            PrintRedirectionNumRestrictPar(&ie[i]);
            break;

        case ISUP_PRM_REMOTE_OPS:
            PrintRemoteOperationsPar(&ie[i]);
            break;

        case ISUP_PRM_SIGNALLING_POINT_CODE:
            PrintSignallingPointCodePar(&ie[i]);
            break;

        case ISUP_PRM_SUBSEQUENT_NUM:
            PrintSubsequentNumPar(&ie[i]);
            break;

        case ISUP_PRM_TX_MEDIUM_REQMNT:
            PrintTXMediumRequirementPar(&ie[i]);
            break;

        case ISUP_PRM_TX_MEDIUM_REQMNT_PRIME:
            PrintTXMediumRequirementPrimePar(&ie[i]);
            break;

        case ISUP_PRM_TX_MEDIUM_USED:
            PrintTXMediumUsedPar(&ie[i]);
            break;

        case ISUP_PRM_USER_SERVICE_INFO_PRIME:
            PrintUserServiceInfoPrimePar(&ie[i]);
            break;

        case ISUP_PRM_USER_TELESERVICE_INFO:
            PrintUserTeleserviceInfoPar(&ie[i]);
            break;

        case ISUP_PRM_USER_TO_USER_INDICATORS:
            PrintUserToUserIndPar(&ie[i]);
            break;

        case ISUP_PRM_USER_TO_USER_INFO:
            PrintUserToUserInfoPar(&ie[i]);
            break;

#endif /* ITU specific parameter Names */

#if defined(CCITT) && defined(ITU_ISUP_97)

        case ISUP_PRM_BACKWARD_GVNS:
            PrintBackwardGVNSPar(&ie[i]);
            break;

        case ISUP_PRM_CCSS:
            PrintCCSSPar(&ie[i]);
            break;

        case ISUP_PRM_CALL_TRANSFER_NUMBER:
            PrintCallTransferNumberPar(&ie[i]);
            break;

        case ISUP_PRM_CALL_TRANSFER_REFERENCE:
            PrintCallTransferReferencePar(&ie[i]);
            break;

        case ISUP_PRM_FORWARD_GVNS:
            PrintForwardGVNSPar(&ie[i]);
            break;

        case ISUP_PRM_LOOP_PREVENTION_INDICATORS:
            PrintLoopPreventionIndPar(&ie[i]);
            break;

        case ISUP_PRM_NETWORK_MANAGEMENT_CONTROLS:
            PrintNetworkManagementCtrlsPar(&ie[i]);
            break;

        case ISUP_PRM_CIRCUIT_ASSIGNMENT_MAP:
            PrintCircuitAssignmentMapPar(&ie[i]);
            break;

        case ISUP_PRM_CORRELATION_ID:
            PrintCorrelationIdPar(&ie[i]);
            break;

        case ISUP_PRM_SCF_ID:
            PrintSCFIdPar(&ie[i]);
            break;

        case ISUP_PRM_CALL_DIV_TREAT_INDICATORS:
            PrintCallDiversionTreatmentIndPar(&ie[i]);
            break;

        case ISUP_PRM_CALLED_IN_NUMBER:
            PrintCalledINNumberPar(&ie[i]);
            break;

        case ISUP_PRM_CALL_OFF_TREAT_INDICATORS:
            PrintCallOfferingTreatmentIndPar(&ie[i]);
            break;

        case ISUP_PRM_CHARGED_PARTY_IDENTIFICATION:
            PrintChargedPartyIdentificationPar(&ie[i]);
            break;

        case ISUP_PRM_CONF_TREAT_INDICATORS:
            PrintConferenceTreatmentIndPar(&ie[i]);
            break;

        case ISUP_PRM_DISPLAY_INFORMATION:
            PrintDisplayInformationPar(&ie[i]);
            break;

        case ISUP_PRM_UID_ACTION_INDICATORS:
            PrintUIDActionIndPar(&ie[i]);
            break;

        case ISUP_PRM_UID_CAPABILITY_INDICATORS:
            PrintUIDCapabilityIndPar(&ie[i]);
            break;

        case ISUP_PRM_HOP_COUNTER:
            PrintHopCounterPar(&ie[i]);
            break;

        case ISUP_PRM_COLLECT_CALL_REQUEST:
            PrintCollectCallRequestPar(&ie[i]);
            break;

#endif /* ITU_ISUP_97 */

#if defined(CCITT)
            /* ITU_ISUP_99 Start */
        case ISUP_PRM_APPLLICATION_TRANSPORT:
            PrintApplicationTransportPar(&ie[i]);
            break;

        case ISUP_PRM_CCNR_POSSIBLE_IND:
            PrintCcnrPossibleIndPar(&ie[i]);
            break;
        
        case ISUP_PRM_PIVOT_CAPABILITY:
             PrintPivotCapabilityPar(&ie[i]);
             break;

        case ISUP_PRM_PIVOT_ROUTING_IND:
             PrintPivotRoutingIndPar(&ie[i]);
             break;

        case ISUP_PRM_CALLED_DIR_NUM:
             PrintCalledDirNumPar(&ie[i]);
             break;

        case ISUP_PRM_ORIGINAL_CALLED_IN_NUM:
             PrintOriginalCalledInNumPar(&ie[i]);
             break;
        
        case ISUP_PRM_CALLING_GEODETIC_LOCATION:
             PrintCalledGeodeticLocationPar(&ie[i]);
             break;

        case ISUP_PRM_HTR_INFORMATION:
             PrintHtrInfoPar(&ie[i]);
             break;

        case ISUP_PRM_NETWORK_ROUTING_NUM:
             PrintNetworkRoutingNumPar(&ie[i]);
             break;
        
        case ISUP_PRM_QUERY_ON_RELEASE_CAPABILITY:
             PrintQueryOnReleaseCapabilityPar(&ie[i]);
             break;
        
        case ISUP_PRM_PIVOT_STATUS:
             PrintPivotStatusPar(&ie[i]);
             break;

        case ISUP_PRM_PIVOT_COUNTER:
             PrintPivotCounterPar(&ie[i]);
            break;

        case ISUP_PRM_PIVOT_ROUTING_FRWD_INFO:
             PrintPivotRoutingFrwdInfoPar(&ie[i]);
             break;
        
        case ISUP_PRM_PIVOT_ROUTING_BKWD_INFO:
             PrintPivotRoutingBkwdInfoPar(&ie[i]);
            break;

        case ISUP_PRM_REDIRECT_CAPABILITY:
             PrintRedirectCapabilityPar(&ie[i]);
             break;

        case ISUP_PRM_REDIRECT_COUNTER:
             PrintRedirectCounterPar(&ie[i]);
             break;

        case ISUP_PRM_REDIRECT_STATUS:
             PrintRedirectStatusPar(&ie[i]);
             break;

        case ISUP_PRM_REDIRECT_FRWD_INFO:
             PrintRedirectFrwdInfoPar(&ie[i]);
             break;

        case ISUP_PRM_REDIRECT_BKWD_INFO:
             PrintRedirectBkwdInfoPar(&ie[i]);
             break;

        case ISUP_PRM_NUM_PORTABILTY_FRWD_INFO:
             PrintNumPortabilityFrwdInfoPar(&ie[i]);
             break;
#endif /* ITU_ISUP_99 End */


#if defined(ANSI) && defined(ANSI_ISUP_95)

        case ISUP_PRM_CIRCUIT_ASSIGN_MAP:
            PrintCircuitAssignMap(&ie[i]);
            break;

        case ISUP_PRM_GENERIC_NAME:
            PrintGenericName(&ie[i]);
            break;

        case ISUP_PRM_HOP_CTR:
            PrintHopCouner(&ie[i]);
            break;

        case ISUP_PRM_OPERATOR_SERVICES_INFO:
            PrintOperatorServInfo(&ie[i]);
            break;

        case ISUP_PRM_PRECEDENCE:
            PrintPrecedence(&ie[i]);
            break;

        case ISUP_PRM_REMOTE_OPERATIONS:
            PrintRemoteOperations(&ie[i]);
            break;

        case ISUP_PRM_TRANSMISSION_MEDIUM_USED:
            PrintTransMediumUsed(&ie[i]);
            break;

        case ISUP_PRM_USER_SERVICE_INFORM_PRIME:
            PrintUserServInfoPrime(&ie[i]);
            break;

        case ISUP_PRM_USER_TO_USER_INDS:
            PrintUserToUserIndicators(&ie[i]);
            break;

        case ISUP_PRM_USER_TO_USER_INFORM:
            PrintUserToUserInfo(&ie[i]);
            break;

#endif /* ANSI_ISUP_95 */

        case ISUP_PRM_TIMEOUT_DATA:
            PrintTimeout(&ie[i]);
            break;

        case ISUP_PRM_ERROR_DATA:
            PrintError(&ie[i]);
            break;

        case ISUP_PRM_INDICATION_DATA:
            PrintIndication(&ie[i]);
            break;

        default:
            printf("PrintISUPMsg: Unrecognized Parameter Tag: 0x%02x \n",
                   ie[i].param_id);
            result = !ITS_SUCCESS;
        }
    }
    printf("\n");

    return result;
} /* PrintISUPMsg */


void
PrintRoutingLabel(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Routing Label \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("SIO: 0x%02x \n", ie->param_data.routingLabel.sio);

    printf("Label: ");
#if defined (CCITT)
    for ( i = 0; i < 4; ++i )
    {
        printf(" 0x%02x", ie->param_data.routingLabel.label.data[i]);
    }
#endif /* CCITT */

#if defined (ANSI)
    printf("DPC: ");
    for ( i = 0; i < 3; ++i )
    {
        printf(" 0x%02x", ie->param_data.routingLabel.label.dpc.data[i]);
    }

    printf(" OPC: ");
    for ( i = 0; i < 3; ++i )
    {
        printf(" 0x%02x", ie->param_data.routingLabel.label.opc.data[i]);
    }

    printf(" SLS: 0x%02x", ie->param_data.routingLabel.label.sls);
#endif /* ANSI */

    printf("\n");
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintMessageInPAMPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: MessageInPam \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("msgTypeInPAM: 0x%02x \n", ie->param_data.msgTypeInPAM);
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintAccessDeliveryInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: AccessDeliveryInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("info: 0x%02x \n", ie->param_data.accessDeliveryInfo.info);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintAccessTransportPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int maxplen = 128;

    printf("\n");
    printf("Parameter: AccessTransport \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    if ((int)ie->param_length > maxplen)
    {
        printf("Error: AccessTransport no. of info elements > %d \n",
               maxplen);
    }

    printf("acc_transport[%d] =", ie->param_length);
    for ( i = 0; i < ie->param_length; ++i )
    {
        printf(" 0x%02x", ie->param_data.accessTransport.acc_transport[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintAutoCongestionLvlPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: AutomaticCongestionLevel \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("level: 0x%02x \n", ie->param_data.autoCongestionLevel.level);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintBackwardCallIndPar(const ITS_ISUP_IE *ie)
{
    int i;
    int plen = 2;

    printf("\n");
    printf("Parameter: BackwardCallIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
   
    printf("bkwd_ci[%d]:", ie->param_length);
    for (i = 0; i < plen; ++i)
    {
        printf(" 0x%02x", ie->param_data.backwardCallIndicators.bkwd_ci[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintCallDiversionInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CallDiversionInfo \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("div_info: 0x%02x \n", ie->param_data.callDiversionInfo.div_info);
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintCallingPartyCategoryPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CallingPartyCategory \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("cat: 0x%02x \n", ie->param_data.callingPartyCategory.cat);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintCalledPartyNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: CalledPartyNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.calledPartyNum.addr_ind);
    printf("num_plan: 0x%02x \n", ie->param_data.calledPartyNum.num_plan);

    printf("dgts[%d]: ", ie->param_length - 2);
    for (i = 0; i < (ie->param_length - 2); ++i)
    {
        printf("0x%02x ", ie->param_data.calledPartyNum.dgts[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintCallHistoryInfoPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nOctets = 2;

    printf("\n");
    printf("Parameter: CallHistoryInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("delay[%d]: ", nOctets);
    for (i = 0; i < nOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.callHistoryInfo.prop_delay[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintCallingPartyNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: CallingPartyNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.callingPartyNum.addr_ind);
    printf("subfields4: 0x%02x \n", ie->param_data.callingPartyNum.subfields4);

    printf("dgts[%d]:", ie->param_length - 2);
    for (i = 0; i < (ie->param_length - 2); ++i )
    {
        printf("0x%02x ", ie->param_data.callingPartyNum.dgts[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintCallRefPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nCIOctets = 3;
    int nPCOctets;

    printf("\n");
    printf("Parameter: CallReference \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

#ifdef ANSI
    nPCOctets = 3;
#endif

#ifdef CCITT
    nPCOctets = 2;
#endif

    printf("call_ident: ");
    for (i = 0; i < nCIOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.callRef.call_ident[i]);
    }
  
    printf("\n");
    printf("point_code: ");
    for (i = 0; i < nPCOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.callRef.point_code.data[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintCauseIndPar(const ITS_ISUP_IE *ie)
{
    int        i = 0;
    ITS_OCTET  nDiagnostics = 0x00;

    printf("\n");
    printf("Parameter: CauseIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("subfields4: 0x%02x \n", ie->param_data.causeIndicator.subfields4);
    printf("cause_val: 0x%02x \n", ie->param_data.causeIndicator.cause_val);

    nDiagnostics = ie->param_length - 2;
    printf("diagnostics[%d]: ", nDiagnostics);
    for (i = 0; i < nDiagnostics; ++i)
    {
        printf("0x%02x ", ie->param_data.causeIndicator.diagnostics[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintChargeNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: ChargeNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.chargeNumber.addr_ind);
    printf("num_plan: 0x%02x \n", ie->param_data.chargeNumber.num_plan);
  
    printf("dgts[%d]: ", ie->param_length - 2);
    for (i = 0; i < (ie->param_length - 2); ++i)
    {
        printf("0x%02x ", ie->param_data.chargeNumber.dgts[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintCircuitStateIndPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nStates = 0;

    printf("\n");
    printf("Parameter: CircuitStateIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("states[%d]: ", nStates);
    for (i = 0; i < ie->param_length; ++i)
    {
        printf("0x%02x ", ie->param_data.circuitStateIndicators.states[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintClosedUserGrpIntrlckCodePar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nDigitsOctets = 2;
    int nCodeOctets = 2;

    printf("\n");
    printf("Parameter: ClosedUserGroupInterlockCode \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    if ((int)ie->param_length != nDigitsOctets + nCodeOctets)
    {
        printf("Error: ClosedUserGroupInterlockCode plen != %d \n",
               nDigitsOctets + nCodeOctets);
    }

    printf("digits[%d]: ", nDigitsOctets);
    for (i = 0; i < nDigitsOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.interlockCode.digits[i]);
    }
    printf("\n");

    printf("code[%d]: ", nCodeOctets);
    for (i = 0; i < nCodeOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.interlockCode.code[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintConnectedNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: ConnectedNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("addr_ind: 0x%02x \n", ie->param_data.connectedNum.addr_ind);
    printf("subfields4: 0x%02x \n", ie->param_data.connectedNum.subfields4);

    printf("dgts[%d]:", ie->param_length - 2);
    for (i = 0; i < (ie->param_length - 2); ++i )
    {
        printf("0x%02x ", ie->param_data.connectedNum.dgts[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintConnectRequestPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nCIOctets = 3;
    int nPCOctets = 0;

    printf("\n");
    printf("Parameter: ConnectionRequest \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("call_ident[%d]: ", nCIOctets);
    for (i = 0; i < nCIOctets; ++ i)
    {
        printf("0x%02x ", ie->param_data.connectionRequest.call_ident[i]);
    }
    printf("\n");

#ifdef ANSI
    nPCOctets = 3;
#endif
#ifdef CCITT
    nPCOctets = 2;
#endif

    printf("point_code[%d]: ", nPCOctets);
    for (i = 0; i < nCIOctets; ++ i)
    {
        printf("0x%02x ", ie->param_data.connectionRequest.point_code.data[i]);
    }
    printf("\n");

    printf("protocol_class: 0x%02x \n",
           ie->param_data.connectionRequest.protocol_class);
    printf("credit: 0x%02x \n", ie->param_data.connectionRequest.credit);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintContinuityIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: ContinuityIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("indicators: 0x%02x \n",
           ie->param_data.continuityIndicators.indicators);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintEchoControlInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: EchoControlInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("info: 0x%02x \n", ie->param_data.echoControlInfo.info);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintEOPPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: EOP \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintEventInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: EventInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("evt_info: 0x%02x \n", ie->param_data.eventInfo.evt_info);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintFacilityIndPar( const ITS_ISUP_IE *ie )
{
    printf( "\n" );
    printf( "Parameter: FacilityIndicator \n" );
    printf( "Parameter Id: 0x%02x \n", ie->param_id );
    printf( "Length: %d octets \n", ie->param_length );
    printf( "fac_ind: 0x%02x\n", ie->param_data.facilityIndicator.fac_ind);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintForwCallIndPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int plen = 2;

    printf("\n");
    printf("Parameter: ForwardCallIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("fwd_ci[%d]: ", plen);
    for (i = 0; i < plen; ++i)
    {
        printf("0x%02x ", ie->param_data.forwardCallIndicators.fwd_ci[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintGenericAddrPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    
    printf("\n");
    printf("Parameter: GenericAddress \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.genericAddress.addr_ind);
    printf("subfields4: 0x%02x \n", ie->param_data.genericAddress.subfields4);
    printf("type_of_addr: 0x%02x \n",
           ie->param_data.genericAddress.type_of_addr);

    printf("dgts[%d]: ", ie->param_length - 3);
    for (i = 0; i < ie->param_length - 3; ++i )
    {
        printf("0x%02x ", ie->param_data.genericAddress.dgts[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintGenericDigitsPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: GenericDigits \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("type_scheme: 0x%02x \n", ie->param_data.genericDigits.type_scheme);
    
    printf("digits[%d]: ", ie->param_length - 1);
    for (i = 0; i < (ie->param_length - 1); ++i)
    {
        printf("0x%02x ", ie->param_data.genericDigits.digits[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintGenericNotificationIndPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: GenericNotificationIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("indicators[%d]: ", ie->param_length);
    for (i = 0; i < ie->param_length; ++i)
    {
        printf("0x%02x ",
               ie->param_data.genericNotificationIndicator.indicators[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintGenericNumberPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nQOctets = 1;       /* qualifier octet len */
    int nNOctets = 1;       /* nature octet len */
    int nSOctets = 1;       /* subfields4 octet len */
    int nDigitsOctets = 0;  /* digits octet len */

    printf("\n");
    printf("Parameter: GenericNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("qualifier: 0x%02x \n", ie->param_data.genericNumber.qualifier);
    printf("nature: 0x%02x \n", ie->param_data.genericNumber.nature);
    printf("subfields4: 0x%02x \n", ie->param_data.genericNumber.subfields4);
    
    nDigitsOctets = (int)ie->param_length - nQOctets - nNOctets - nSOctets;

    printf("digits[%d]: ", nDigitsOctets);
    for (i = 0; i < nDigitsOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.genericDigits.digits[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      In Q.763 this GenericReference is a reserved parameter.
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintGenericReferencPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nQualOctets = 1;
    int nOctetsToPrint = 0;
    int entryIndex = 0;
    int nRefOctets = 0;
    int nLROctets = 

    printf("\n");
    printf("Parameter: GenericReference \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    nOctetsToPrint = ie->param_length;

#if 0
    while (nOctetsToPrint > 0)
    {
        nRefOctets = 0;

        /* qualifier */
        printf("qualifier: 0x%02x \n",
               ie->param_data.genericReference.entries[entryIndex].qualifier);

        /* length of reference [1, 4] inclusive */
        printf("refCount: 0x%02x \n",
               ie->param_data.genericReference.entries[entryIndex].refCount);
        
        nRefOctets = 
            (int)ie->param_data.genericReference.entries[entryIndex].refCount;

        /* references */
        printf("refs[%d]: " , nRefOctets);
        for (i = 0; i < nRefOctets; ++i)
        {
            printf("0x%02x ",
                ie->param_data.genericReference.entries[entryIndex]. \
                refs[i]);
        }

        /* Read N octets from file */
        nOctetsToPrint -= nQualOctets - nLROctets - (int)nRefOctets;

        ++entryIndex;
    }
#endif

        nRefOctets = 0;

        /* qualifier */
        printf("qualifier: 0x%02x \n",
               ie->param_data.genericReference.entries[entryIndex].qualifier);

        /* length of reference [1, 4] inclusive */
        printf("refCount: 0x%02x \n",
               ie->param_data.genericReference.entries[entryIndex].refCount);
        
        nRefOctets = 
            (int)ie->param_data.genericReference.entries[entryIndex].refCount;

        /* references */
        printf("refs[%d]: " , nRefOctets);
        for (i = 0; i < nRefOctets; ++i)
        {
            printf("0x%02x ",
                ie->param_data.genericReference.entries[entryIndex].refs[i]);
        }

        printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintInfoIndPar(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter: InformationIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    
    printf("indics[%d]: ", ie->param_length);
    for (i = 0; i < ie->param_length; ++i)
    {
        printf("0x%02x ", ie->param_data.informationIndicators.indics[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintInfoReqIndPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nOctets = 2;

    printf("\n");
    printf("Parameter: InformationRequestIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("indics[%d]: ", nOctets);
    for (i = 0; i < nOctets; ++i)
    {
        printf("0x%02x ",
               ie->param_data.informationRequestIndicators.indics[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintJurisdictionPar(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter: Jurisdiction \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("digits[%d]: ", ie->param_length);
    for (i = 0; i < ie->param_length; ++i)
    {
        printf("0x%02x ", ie->param_data.jurisdiction.digits[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      Same format for ANSI & CCITT.
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintLocationNumberPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: LocationNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("addr_ind: 0x%02x \n", ie->param_data.locationNumber.addr_ind);
    printf("subfields4: 0x%02x \n", ie->param_data.locationNumber.subfields4);

    printf("dgts[%d]:", ie->param_length - 2);
    for (i = 0; i < (ie->param_length - 2); ++i )
    {
        printf("0x%02x ", ie->param_data.locationNumber.dgts[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintMCIDRequestIndPar( const ITS_ISUP_IE *ie )
{
    printf("\n");
    printf("Parameter: MCIDRequestIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("mcid_rqst_ind: %d octets \n",
           ie->param_data.mcidRequestIndicators.indics);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintMCIDResponseIndPar( const ITS_ISUP_IE *ie )
{
    printf("\n");
    printf("Parameter: MCIDResponseIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("mcid_rspnse_ind: %d octets \n",
           ie->param_data.mcidResponseIndicators.indics);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      Same format for ANSI & CCITT.
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintMLPPPrecedencePar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nNILen = 2;
    int nDomainLen = 3;

    printf("\n");
    printf("Parameter: MLPPPrecedence \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    
    printf("lfbLevel: 0x%02x \n", ie->param_data.mlppPrecedence.lfbLevel);

    printf("ni[%d]: ", nNILen);
    for (i = 0; i < nNILen; ++i)
    {
        printf("0x%02x ", ie->param_data.mlppPrecedence.ni[i]);
    }
    printf("\n");
    
    printf("ni[%d]: ", nDomainLen);
    for (i = 0; i < nDomainLen; ++i)
    {
        printf("0x%02x ", ie->param_data.mlppPrecedence.domain[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintMsgCompatibiltyInfoPar( const ITS_ISUP_IE *ie )
{
    int i;
    int nDigitsOctets = 0;
    printf( "\n" );
    printf( "Parameter: MessageCompatibilityInformation \n" );
    printf( "Parameter Id: 0x%02x \n", ie->param_id );
    printf( "Length: %d octets \n", ie->param_length );
    nDigitsOctets = (int)ie->param_length ;
    printf( "msg_compatibility_info:\n   " );

    for (i = 0; i < nDigitsOctets; i++)
    {
        printf( "0x%02x ",
                ie->param_data.msgCompatibilityInfo.data[i] );
        if ( i % 10 == 0 )
        {
            printf( "\n" );
        }
    }
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      Same format for ANSI & CCITT.
 *
 *  See Also:
 ****************************************************************************/
void
PrintNatureOfConnectionIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: NatureOfConnectionIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("subfields4: 0x%02x \n",
           ie->param_data.connectionIndicator.subfields4);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintNetworkSpecificFacilityPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nwIdLen = 0, netFaclen = 0;

    printf("\n");
    printf("Parameter: NetworkSpecificFalicities \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    nwIdLen = ie->param_data.networkSpecificFacility.length_ofNtwrkId;
    printf("networkID_len: 0x%02x \n", nwIdLen);

    if (nwIdLen > 0)
    {
        printf("ntwrk_type_plan: 0x%02x \n",
               ie->param_data.networkSpecificFacility.ntwrk_type_plan);

        printf("networkID:\n");
        for (i = 0; i < nwIdLen; i++)
        {
            printf("0x%02x ", ie->param_data.networkSpecificFacility.ntwrk_id[i]);
            if (i % 10 == 0)
            {
                printf("\n   ");
            }
        }
        printf("\n");

        /* if nwIdLen != 0, two fixed octets at the beginning */
        netFaclen = ie->param_length - nwIdLen - 2;
    }

    if (nwIdLen == 0)
    {
        /* if nwIdLen == 0, one fixed octets at the beginning */
        netFaclen = ie->param_length - 1;
    }

    if ( netFaclen > 0)
    {
        printf("ntwrk_facility:\n");
        for ( i = 0; i < netFaclen; i++ )
        {
            printf("0x%02x ",
                   ie->param_data.networkSpecificFacility.ntwrk_facility[i]);
            if (i % 10 == 0)
            {
                printf("\n");
            }
        }
        printf("\n");
    }
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintNotificationIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: NotificationIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("indicator: 0x%02x \n", ie->param_data.notification.indicator);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintOptBackwardCallIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: OptionalBackwardCallIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("obkwd_ind: 0x%02x \n",
           ie->param_data.optBkwdCallIndicators.obkwd_ind);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintOptForwardCallIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: OptionalForwardCallIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("indics: 0x%02x \n", ie->param_data.optFwdCallIndicators.indics);
}
#endif

                                                                                                                             
/************************ ISUP_ITU_99 Parameters Start ***********************/
                                                                                                                             
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Application Transport Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
                                                                                                                             
#if defined(CCITT)
void
PrintApplicationTransportPar(const ITS_ISUP_IE *ie)
{   int i,plen = 1;
    printf("\n");
    printf("Parameter   : Application Transport \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       :\n" );
    printf("Appl Contx Iden : 0x%02x \n", ie->param_data.applicationTransport.appl_cntx_ident);
    if(ie->param_length ==  plen)
    return;
    printf("RCI       : 0x%01x \n", (ie->param_data.applicationTransport.sni_rci)&(0x01));
    printf("SNI       : 0x%01x \n", (ie->param_data.applicationTransport.sni_rci)&(0x02));
    if(ie->param_length ==  plen+1)
    return;
    printf("APM Seg Ind : 0x%02x \n", (ie->param_data.applicationTransport.apm_seg_ind)&(0x3F));
    printf("SI : 0x%01x \n", (ie->param_data.applicationTransport.apm_seg_ind)&(0x40));
    if(ie->param_length ==  plen+2)
    return;
    printf("Sigm local ref : 0x%02x \n", (ie->param_data.applicationTransport.seg_local_ref)&(0x7F));
    if(ie->param_length ==  plen+3)
    return;
    printf("Info : ");
    for (i = 0; i < (ie->param_length-4); i++)
    {
       printf("0x%02x ", ie->param_data.applicationTransport.enc_appl_info[i]);
    }
    printf("\n");
    return;
}
#endif
                                                                                                                             
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the CCNR Possible Indicator Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/ 
#if defined(CCITT)                                                                                                          
void
PrintCcnrPossibleIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : CCNR Possible Indicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : 0x%02x \n", ie->param_data.ccnrPossibleInd.posbl_ind);
                                                                                                                             
    printf("\n");
    return;
}
#endif

                                                                                                                             
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Pivot Capability Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintPivotCapabilityPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : Pivot Capability \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : 0x%02x \n", ie->param_data.pivotCapability.pvt_cablt);
                                                                                                                             
    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Pivot routing indicator Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ******************************************************************************/
#if defined(CCITT)
void
PrintPivotRoutingIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : Pivot routing indicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : 0x%02x \n", ie->param_data.pivotRoutingInd.pvt_rt_ind);
                                                                                                                             
    printf("\n");
    return;
}
#endif
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Called directory number Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintCalledDirNumPar(const ITS_ISUP_IE *ie)
{   int i;
    printf("\n");
    printf("Parameter   : Called directory number\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : \n");
    printf("Nature of Addr Ind : 0x%02x \n", (ie->param_data.calledDirNum.nature_addr_ind)&(0x7F));
    printf("Num plan Ind : 0x%02x \n", (ie->param_data.calledDirNum.num_plan_ind)&(0x70));
    printf("Addr signal: ");
    for(i=0;i < (ie->param_length-2);i++)
    {
        printf("0x%02x ",ie->param_data.calledDirNum.addr_signal[i] );
    }
    printf("\n");
    return;
}
#endif
                                                                                                                             
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Original Called IN number Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintOriginalCalledInNumPar(const ITS_ISUP_IE *ie)
{   int i;
    printf("\n");
    printf("Parameter   : Original Called IN number\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : \n");
    printf("Nature of Addr Ind : 0x%02x \n", (ie->param_data.originalCalledInNum.addr_ind)&(0x7F));
    printf("Addr presnt Ind : 0x%02x \n", (ie->param_data.originalCalledInNum.subfields4)&(0x0C));
    printf("Num plan Ind : 0x%02x \n", (ie->param_data.originalCalledInNum.subfields4)&(0x70));
    printf("Addr signal: ");
    for(i = 0; i < (ie->param_length-2);i++)
    {
        printf("0x%02x ", ie->param_data.originalCalledInNum.dgts[i]);
    }
    printf("\n");
    return;
}
#endif
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Calling  geodetic location Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintCalledGeodeticLocationPar(const ITS_ISUP_IE *ie)
{   int i,plen = 1;
    printf("\n");
    printf("Parameter   : Calling  geodetic location\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : \n");
    printf("Screening : 0x%02x \n", (ie->param_data.calledGeodeticLocation.lpri_screen)&(0x03));
    printf("LPRI : 0x%02x \n", (ie->param_data.calledGeodeticLocation.lpri_screen)&(0x0C));
    if(ie->param_length == plen)
    return;
    printf("Shape type : 0x%02x \n", (ie->param_data.calledGeodeticLocation.type_shape)&(0x7F));
    printf("Shape Desc : ");
    for(i = 0; i < (ie->param_length-2);i++)
    {
        printf("0x%02x ", ie->param_data.calledGeodeticLocation.shape_desc[i]);
    }
    printf("\n");
    return;
}
#endif
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the HTR Information Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)                                                                                                          
void
PrintHtrInfoPar(const ITS_ISUP_IE *ie)
{   int i;
    printf("\n");
    printf("Parameter   : HTR Information\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : \n");
    printf("Nature of Addr Ind : 0x%02x \n", (ie->param_data.htrInfo.nature_addr_ind)&(0x7F));
    printf("Num plan Ind : 0x%02x \n", (ie->param_data.htrInfo.num_plan_ind)&(0x70));
    printf("Addr signal: ");
    for(i = 0; i < (ie->param_length-2);i++)
    {
        printf("0x%02x ", ie->param_data.htrInfo.addr_signal[i]);
    }
    printf("\n");
    return;
}
#endif
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Network routing number Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintNetworkRoutingNumPar(const ITS_ISUP_IE *ie)
{   int i;
    printf("\n");
    printf("Parameter   : Network routing number\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : \n");
    printf("Indicators : 0x%02x \n", (ie->param_data.networkRoutingNum.indicators)&(0x7F));
    printf("Addr signal: ");
    for(i = 0; i < (ie->param_length-1);i++)
    {
        printf("0x%02x ", ie->param_data.networkRoutingNum.addr_signal[i]);
    }
    printf("\n");
    return;
}
#endif
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Query On Release Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintQueryOnReleaseCapabilityPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : Query on Release \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : 0x%02x \n", ie->param_data.queryOnReleaseCapability.qor_cap);
                                                                                                                             
    printf("\n");
    return;
}
#endif 
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Pivot Status Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintPivotStatusPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : Pivot Status \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : 0x%02x \n", ie->param_data.pivotStatus.pvt_stat);
                                                                                                                             
    printf("\n");
    return;
}
#endif
                                                                                                                             
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Pivot Counter Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintPivotCounterPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : Pivot Counter \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : 0x%02x \n", ie->param_data.pivotCounter.pvt_cntr);
                                                                                                                             
    printf("\n");
    return;
}
#endif 
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Pivot routing forward information Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintPivotRoutingFrwdInfoPar(const ITS_ISUP_IE *ie)
{   int i;
    printf("\n");
    printf("Parameter   : Pivot routing forward information \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("value : ");
    printf("0x%02x ", ie->param_data.pivotRoutingFrwdInfo.info[0].type_tag);
    if(ie->param_length == 1)
    return;
    printf("0x%02x ", ie->param_data.pivotRoutingFrwdInfo.info[0].type_len);
    for(i = 0; i < ie->param_data.pivotRoutingFrwdInfo.info[0].type_len; i++)
    {
        printf("0x%02x\n", ie->param_data.pivotRoutingFrwdInfo.info[0].type_val[i]);
    }
    printf("\n");
    return;
}
#endif
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Pivot routing Backward information Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintPivotRoutingBkwdInfoPar(const ITS_ISUP_IE *ie)
{   int i;
    printf("\n");
    printf("Parameter   : Pivot routing backward information \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("value : ");
    printf("0x%02x ", ie->param_data.pivotRoutingBkwdInfo.info[0].type_tag);
    if(ie->param_length == 1)
    return;
    printf("0x%02x ", ie->param_data.pivotRoutingBkwdInfo.info[0].type_len);
    for(i = 0; i < ie->param_data.pivotRoutingBkwdInfo.info[0].type_len; i++)
    {
        printf("0x%02x\n", ie->param_data.pivotRoutingBkwdInfo.info[0].type_val[i]);
    }
    printf("\n");
    return;
}
#endif
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Redirect Capability Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintRedirectCapabilityPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : Redirect Capability \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : 0x%02x \n", ie->param_data.redirectCapability.rd_cap);
                                                                                                                             
    printf("\n");
    return;
}
#endif
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Redirect Counter Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintRedirectCounterPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : Redirect Capability \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : 0x%02x \n", ie->param_data.redirectCounter.rd_cntr);
                                                                                                                             
    printf("\n");
    return;
}
#endif 
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Redirect Status Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintRedirectStatusPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : Redirect Status \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : 0x%02x \n", ie->param_data.redirectStatus.rd_stat);
                                                                                                                             
    printf("\n");
    return;
}
#endif
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Redirect Forward Info Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintRedirectFrwdInfoPar(const ITS_ISUP_IE *ie)
{   int i;
    printf("\n");
    printf("Parameter   : Redirect Forward Info \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : ");
    printf("0x%02x ", ie->param_data.redirectFrwdInfo.info[0].type_tag);
    if(ie->param_length == 1)
    return;
    printf("0x%02x ", ie->param_data.redirectFrwdInfo.info[0].type_len);
    for(i = 0; i < ie->param_data.redirectFrwdInfo.info[0].type_len; i++)
    {
        printf("0x%02x\n", ie->param_data.redirectFrwdInfo.info[0].type_val[i]);
    }
    printf("\n");
    return;
}
#endif
                                                                                                                             
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Redirect Backward Info Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintRedirectBkwdInfoPar(const ITS_ISUP_IE *ie)
{   int i;
    printf("\n");
    printf("Parameter   : Redirect backward Info \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value : ");
    printf("0x%02x ", ie->param_data.redirectBkwdInfo.info[0].type_tag);
    if(ie->param_length == 1)
    return;
    printf("0x%02x ", ie->param_data.redirectBkwdInfo.info[0].type_len);
    for(i = 0; i < ie->param_data.redirectBkwdInfo.info[0].type_len; i++)
    {
        printf("0x%02x\n", ie->param_data.redirectBkwdInfo.info[0].type_val[i]);
    }
    printf("\n");
    return;
}
#endif 
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Number portabilityForward Info Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined( CCITT )
void
PrintNumPortabilityFrwdInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : Num Port Frwd Info \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    if(ie->param_length == 1)
    {
        printf("Value : 0x%02x \n", ie->param_data.numPortabilityFrwdInfo.num_port_fwd_inf);
    }                                                                                                                              
    printf("\n");
    return;
}
#endif
                                                                                                                             
/*ITU99 Parameter functions end here*/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintOrigCalledNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: OriginalCalledNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.origCalledNum.addr_ind);
    printf("subfields4: 0x%02x \n", ie->param_data.origCalledNum.subfields4);

    printf("dgts[%d]: ", ie->param_length - 2);
    for (i = 0; i < ie->param_length - 2; ++i)
    {
        printf("0x%02x ", ie->param_data.origCalledNum.dgts[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintOutgoingTrunkGrpNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nOctets = 0;

    printf("\n");
    printf("Parameter: OutgoingTrunkGroupNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    nOctets = (int)ie->param_length;

    printf("digits[%d]: ", nOctets);
    for (i = 0; i < nOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.outgoingTrunkNum.digits[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintPropDelayCounterPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nOctets = 2;

    printf("\n");
    printf("Parameter: PropagationDelayCounter \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("delay[%d]: ", nOctets);
    for (i = 0; i < nOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.propDelayCounter.delay[i]);
    }
    printf("\n");
}
#endif


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintRangeAndStatusPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nStatusOctets = 0;

    printf("\n");
    printf("Parameter: RangeAndStatus \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("range: 0x%02x \n", ie->param_data.rangeAndStatus.range);

#ifdef ANSI
    nStatusOctets = 4;
#endif
#ifdef CCITT
    nStatusOctets = 32;
#endif

    if (ie->param_length > 1)
    {
        printf("status[%d]: ", nStatusOctets);
        for (i = 0; i < ie->param_length - 1; ++i)
        {
            printf("0x%02x ", ie->param_data.rangeAndStatus.status[i]);
        }
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintRedirectingNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: RedirectingNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.redirectingNum.addr_ind);
    printf("subfields4: 0x%02x \n", ie->param_data.redirectingNum.subfields4);

    printf("dgts[%d]: ", ie->param_length - 2);
    for (i = 0; i < (ie->param_length - 2); ++i)
    {
        printf("0x%02x ", ie->param_data.redirectingNum.dgts[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintRedirectionInfoPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nOctets = 2;

    printf("\n");
    printf("Parameter: RedirectionInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    if ((int)ie->param_length != nOctets)
    {
        printf("Error: RedirectionInformation plen != %d \n", nOctets);
    }

    printf("red_info[%d]: ", ie->param_length);
    for (i = 0; i < nOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.redirectionInfo.red_info[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintServiceActivationPar(const ITS_ISUP_IE *ie)
{
    int i;
    int maxNOctets = 0;

    printf("\n");
    printf("Parameter: ServiceActivation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

#ifdef ANSI
    maxNOctets  = 64;
#endif
#ifdef CCITT
    maxNOctets = 128;
#endif

    if (ie->param_length <= maxNOctets)
    {
        printf("data[%d]: ", ie->param_length);
        for (i = 0; i < ie->param_length; ++i)
        {
            printf("0x%02x ", ie->param_data.servactivation.data[i]);
        }
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintSignallingPointCodePar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: SignallingPointCode \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("data[%d]: ", (int)ie->param_length);
    for (i = 0; i < (int)ie->param_length; ++i)
    {
        printf("0x%02x ", ie->param_data.signallingPointCode.data[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintSuspendResumeIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: SuspendResumeIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("sus_res: 0x%02x \n", ie->param_data.suspendResumeInd.sus_res);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintTransactionReqPar(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter: TransactionRequest \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("transaction_id: sizeof() = %d \n", 
            sizeof(ie->param_data.transactionRequest.transaction_id) );

    for (i = 0; i < 4; i++)
    {
        printf("0x%02x ", ie->param_data.transactionRequest.transaction_id[i]);
    }

    printf("SCCP_addr len: %d \n",
           ie->param_data.transactionRequest.SCCP_addr.len);

    printf("SCCP_addr data[%d]: ",
           ie->param_data.transactionRequest.SCCP_addr.len);
    for (i = 0; i < ie->param_data.transactionRequest.SCCP_addr.len; ++i)
    {
        printf("0x%02x ", ie->param_data.transactionRequest.SCCP_addr.data[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintTransitNetworkSelectionPar(const ITS_ISUP_IE *ie)
{

#if defined(CCITT)
    int i = 0;
#endif

    printf("\n");
    printf("Parameter: TransitNetworkSelection \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("network: 0x%02x \n",
           ie->param_data.transitNetworkSelection.network);

#ifdef CCITT
    printf("network_id[%d]: ", ie->param_length - 1);
    for (i = 0; i < ie->param_length - 1; ++i)
    {
        printf("0x%02x ",
               ie->param_data.transitNetworkSelection.network_id[i]);
    }
    printf("\n");
#endif
#ifdef ANSI
    printf("digit2and1: 0x%02x \n",
           ie->param_data.transitNetworkSelection.digit2and1);
    printf("digit4and3: 0x%02x \n",
           ie->param_data.transitNetworkSelection.digit4and3);
    printf("code: 0x%02x \n", ie->param_data.transitNetworkSelection.code);
#endif
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintBusinessGrpPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nbgidOctets = 3;
    int nsgidOctets = 2;

    printf("\n");
    printf("\nParameter: BusinessGroup");
    printf("\nParameter Id: 0x%02x", ie->param_id);
    printf("\nLength: %d octets", ie->param_length);

    printf("\nparty_selector: 0x%02x",
           ie->param_data.businessGroup.party_selector);
    
    printf("\nline_privileges: 0x%02x",
           ie->param_data.businessGroup.line_privileges);

    printf("\nbusiness_group_ident[%d]: ", nbgidOctets);
    for (i = 0; i < nbgidOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.businessGroup.business_group_ident[i]);
    }

    printf("\nsub_group_ident[%d]: ", nsgidOctets);
    for (i = 0; i < nsgidOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.businessGroup.sub_group_ident[i]);
    }
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintCarrierIdPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CarrierIdentification \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets", ie->param_length);

    printf("network: 0x%02x \n", ie->param_data.carrierIdentification.network);
    
    printf("digit2and1: 0x%02x \n",
           ie->param_data.carrierIdentification.digit2and1);
    
    printf("digit4and3: 0x%02x \n",
           ie->param_data.carrierIdentification.digit4and3);
}
#endif /* ANSI */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintCarrierSelectionInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CarrierSelectionInfo \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("information: 0x%02x \n",
           ie->param_data.carrierSelectionInfo.information);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintCircuitGrpCharIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CircuitGroupCharacteristicsIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("indicator: 0x%02x \n",
           ie->param_data.circuitGrpCharacteristic.indicator);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintCircuitGrpSupervisionMsgTypIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CircuitGroupSupervisionMessageTypeIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("sup_mt: 0x%02x \n", ie->param_data.supervisionMsgType.sup_mt);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintCircuitIdNamePar(const ITS_ISUP_IE *ie)
{
    int i;
    int nTrunkNumOctets = 4;
    int nOfficeAOctets = 11;
    int nOfficeZOctets = 11;

    printf("\n");
    printf("Parameter: CircuitIdentificationName \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("trunkNum[%d]: ", nTrunkNumOctets);
    for (i = 0; i < nTrunkNumOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.circuitIdName.trunkNum[i]);
    }
    printf("\n");

    printf("clliCode_officeA[%d]:", nOfficeAOctets);
    for (i = 0; i < nOfficeAOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.circuitIdName.clliCode_officeA[i]);
    }
    printf("\n");

    printf("clliCode_officeZ[%d]:", nOfficeZOctets);
    for (i = 0; i < nOfficeZOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.circuitIdName.clliCode_officeZ[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintCircuitValRespIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CircuitValidationResponseIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("indicator: 0x%02x \n",
           ie->param_data.circuitValidationResponse.indicator);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintCLLICodePar(const ITS_ISUP_IE *ie)
{
    int i;
    int nTownOctets = 4;
    int nStateOctets = 2;
    int nBuildingOctets = 2;
    int nBuildingSubdivOctets = 3;

    printf("\n");
    printf("Parameter: CLLICode \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("town[%d]: ", nTownOctets);
    for (i = 0; i < nTownOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.clliCode.town[i]);
    }
    printf("\n");

    printf("state[%d]: ", nStateOctets);
    for (i = 0; i < nStateOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.clliCode.state[i]);
    }
    printf("\n");

    printf("building[%d]: ", nBuildingOctets);
    for (i = 0; i < nBuildingOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.clliCode.building[i]);
    }
    printf("\n");

    printf("buildingSubdiv[%d]: ", nBuildingSubdivOctets);
    for (i = 0; i < nBuildingSubdivOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.clliCode.buildingSubdiv[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintEgressServicePar(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter: EgressService \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("data[%d]: ", ie->param_length);
    for (i = 0; i < ie->param_length; ++i)
    {
        printf("0x%02x ", ie->param_data.egressService.data[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintNetworkTransportPar(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter: NetworkTransport \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    
    printf("data[%d]: ", ie->param_length);
    for (i = 0; i < ie->param_length; ++i)
    {
        printf("0x%02x ", ie->param_data.networkTransport.data[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintOrigISCPointCodePar(const ITS_ISUP_IE *ie)
{
    int i;
    int nPCOctets = 2;

    printf("\n");
    printf("Parameter: OriginatingISCPointCode \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("data[%d]: ", nPCOctets);
    for (i = 0; i < nPCOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.origIscPointCode.data[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintOrigLineInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: OriginatingLineInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("data: 0x%02x \n", ie->param_data.origLineInfo.data);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintParamCompInfoPar(const ITS_ISUP_IE *ie)
{
    int i = 0, j = 0;
    int nInstOctets = 2;
    int moduloN = 3;      /* used to check maxplen divisible by 3 */

    /* Set IE information */
    printf("\n");
    printf("\nParameter: ParameterCompatibilityInformation");
    printf("\nParameter Id: 0x%02x", ie->param_id);
    printf("\nLength: %d octets", ie->param_length);

    for (i = 0; i < ( (int)( ie->param_length/moduloN ) ); ++i)
    {
        /* upgraded parameter */
        printf("\nparamName: 0x%02x \n",
               ie->param_data.paramCompatInfo.param_info[i].paramName);

        /* instruction indicators */
        printf("instructions[%d]: ", nInstOctets);
        for (j = 0; j < nInstOctets; ++j)
        {
            printf("0x%02x ", ie->param_data.paramCompatInfo.param_info[i].instructions[j]);
        }
    }

    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintRedirectionNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nDigitsOctets = 0;
    int aiLen = 1;
    int npLen = 1;

    printf("\n");
    printf("Parameter: RedirectionNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.redirectionNum.addr_ind);
    printf("num_plan: 0x%02x \n", ie->param_data.redirectionNum.num_plan);

    /* digits */
    nDigitsOctets = (int)ie->param_length - aiLen - npLen;

    printf("dgts[%d]: ", nDigitsOctets);
    for (i = 0; i < nDigitsOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.redirectionNum.dgts[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintRedirectionNumRestrictPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: RedirectionNumberRestriction \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("data: 0x%02x \n", ie->param_data.redirectionRestriction.bits);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintRemoteOperationsPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nProtProfileOctets = 1;
    int nCptOctets = 0;

    printf("\n");
    printf("Parameter: RemoteOperations \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("protocol_profile: 0x%02x \n",
           ie->param_data.remoteOperation.protocol_profile);

    nCptOctets = (int)ie->param_length - nProtProfileOctets;

    printf("components[%d]: ", nCptOctets);
    for (i = 0; i < nCptOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.remoteOperation.protocol_profile);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void
PrintServiceCodePar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: ServiceCode \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("code: 0x%02x \n", ie->param_data.serviceCode.code);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
void PrintSpecialProcessReqPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: SpecialProcessingRequest \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("data: 0x%02x \n", ie->param_data.specialProcessing.data);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintSubsequentNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int aiLen = 1;
    int nDigitsOctets = 0;

    printf("\n");
    printf("Parameter: SubsequentNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.subsequentNum.addr_ind);

    nDigitsOctets = (int)ie->param_length - aiLen;
    printf("dgts[%d]: ", nDigitsOctets);
    for (i = 0; i < nDigitsOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.subsequentNum.dgts[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintTXMediumRequirementPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: TransmissionMediumRequirement \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("tmr: 0x%02x \n", ie->param_data.txMediumRequirement.tmr);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintTXMediumRequirementPrimePar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: TransmissionMediumRequirementPrime \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("tmr: 0x%02x \n", ie->param_data.txMediumRequirementPrime.tmr);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintTXMediumUsedPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: TransmissionMediumUsed \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("tmr: 0x%02x \n", ie->param_data.txMediumUsed.tmr);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintUserServiceInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: UserServiceInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("coding: 0x%02x \n", ie->param_data.userServiceInfo.coding);
    printf("trans_mode: 0x%02x \n", ie->param_data.userServiceInfo.trans_mode);
    printf("config: 0x%02x \n", ie->param_data.userServiceInfo.config);
    printf("symmetry: 0x%02x \n", ie->param_data.userServiceInfo.symmetry);

#ifdef ANSI
    printf("rate_multiplier: 0x%02x \n",
        ie->param_data.userServiceInfo.rate_multiplier);
#endif

    printf("layer1: 0x%02x \n", ie->param_data.userServiceInfo.layer1);

#ifdef ANSI
    printf("layer1_ext_user_rate: 0x%02x \n",
           ie->param_data.userServiceInfo.layer1_ext_user_rate);
    
    printf("layer1_ext_rate_adaption_3b: 0x%02x \n",
           ie->param_data.userServiceInfo.layer1_ext_rate_adaption_3b);

    printf("layer1_ext_parity: 0x%02x \n",
           ie->param_data.userServiceInfo.layer1_ext_parity);

    printf("layer1_ext_modem_type: 0x%02x \n",
           ie->param_data.userServiceInfo.layer1_ext_modem_type);
#endif

    printf("layer2: 0x%02x \n", ie->param_data.userServiceInfo.layer2);
    printf("layer3: 0x%02x \n", ie->param_data.userServiceInfo.layer3);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintUserServiceInfoPrimePar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: UserServiceInformationPrime \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("coding: 0x%02x \n", ie->param_data.userServiceInfoPrime.coding);
    printf("trans_mode: 0x%02x \n",
           ie->param_data.userServiceInfoPrime.trans_mode);
    printf("config: 0x%02x \n", ie->param_data.userServiceInfoPrime.config);
    printf("symmetry: 0x%02x \n",
           ie->param_data.userServiceInfoPrime.symmetry);
    printf("layer1: 0x%02x \n", ie->param_data.userServiceInfoPrime.layer1);
    printf("layer2: 0x%02x \n", ie->param_data.userServiceInfoPrime.layer2);
    printf("layer3: 0x%02x \n", ie->param_data.userServiceInfoPrime.layer3);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintUserTeleserviceInfoPar(const ITS_ISUP_IE *ie)
{
    printf( "\n" );
    printf( "Parameter: UserTeleserviceInfo \n" );
    printf( "Parameter Id: 0x%02x \n", ie->param_id );
    printf( "Length: %d octets \n", ie->param_length );

/* TBD: Fix me */
#if 0
    printf( "subfields3: 0x%02x\n",
             ie->param_data.userTeleServiceInfo.subfields3 );
    printf( "hlayer_char_id: 0x%02x\n",
             ie->param_data.userTeleServiceInfo.hlayer_char_id );
    printf( "ext_hlayer_char_id: 0x%02x\n",
             ie->param_data.userTeleServiceInfo.ext_hlayer_char_id );
#endif
}
#endif   /* CCITT */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintUserToUserIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: UserToUserIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("utu_ind: 0x%02x \n", ie->param_data.userToUserIndicators.utu_ind);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintUserToUserInfoPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nProtDiscOctets = 1;

    printf("\n");
    printf("Parameter: UserToUserInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("prot_disc: 0x%02x \n", ie->param_data.userToUserInfo.prot_disc);

    printf("utu_info[%d]: ", ((int)ie->param_length - nProtDiscOctets));
    for (i = 0; i < (int)ie->param_length - nProtDiscOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.userToUserInfo.utu_info[i]);
    }
    printf("\n");
}
#endif

/* --------------------------------------------------
 * ITU97 specific parameters' functions:
 * --------------------------------------------------
 * PrintBackwardGVNSPar
 * PrintCCSSPar
 * PrintCallTransferNumberPar
 * PrintCallTransferReferencePar
 * PrintForwardGVNSPar
 * PrintLoopPreventionIndPar
 * PrintNetworkManagementCtrlsPar
 * PrintCircuitAssignmentMapPar
 * PrintCorrelationIdPar
 * PrintSCFIdPar
 * PrintCallDiversionTreatmentIndPar
 * PrintCalledINNumberPar
 * PrintCallOfferingTreatmentIndPar
 * PrintChargedPartyIdentificationPar
 * PrintConferenceTreatmentIndPar
 * PrintDisplayInformationPar
 * PrintUIDActionIndPar
 * PrintUIDCapabilityIndPar
 * PrintHopCounterPar
 * PrintCollectCallRequestPar
 * --------------------------------------------------
 */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Backward GVNS Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintBackwardGVNSPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : Backward GVNS\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : follows...");

    for ( i = 0; i < ie->param_length; i++)
    {
        printf(" 0x%02x", ie->param_data.backwardGvns.backward_gvns[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the CCSS Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintCCSSPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : CCSS \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : 0x%02x \n", ie->param_data.ccss.ccssInd);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Call Transfer Number Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintCallTransferNumberPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : Call Transfer Number\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : follows...");

    printf("Nature of Address Indicator : 0x%02x \n", ie->param_data.callTransferNumber.nature_addr_ind);
    printf("Screeing Indicator : 0x%01x \n", (ie->param_data.callTransferNumber.indicators)&(0x03));
    printf("Addr Prest Restr Ind : 0x%01x \n", (ie->param_data.callTransferNumber.indicators)&(0x0C));
    printf("Numbering Plan Ind : 0x%01x \n", (ie->param_data.callTransferNumber.indicators)&(0x70));
    for ( i = 0; i < ( ie->param_length - 2 ); i++)
    {
        printf(" 0x%02x", ie->param_data.callTransferNumber.addr_signals[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Call Transfer Reference Parameter
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintCallTransferReferencePar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : Call Transfer Reference \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : 0x%02x \n", 
            ie->param_data.callTransferReference.call_trans_identity);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Forward GVNS Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintForwardGVNSPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;
    ushort tnrn_len = 0;

    printf("\n");
    printf("Parameter   : Forward GVNS\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : follows...");

    printf("OPSP        : Originating Participating Service Provider\n");
    printf("OPSP Len Ind: 0x%02x \n", ie->param_data.forwardGvns.opsp.opsp_len_ind);
    for ( i = 0; i < ie->param_data.forwardGvns.opsp.opsp_len_ind; i++)
    {
        printf(" 0x%02x", ie->param_data.forwardGvns.opsp.digits[i]);
    }

    printf("GUG        : GVNS User Group\n");
    printf("GUG Len Ind: 0x%02x \n", ie->param_data.forwardGvns.gug.gug_len_ind);
    for ( i = 0; i < ie->param_data.forwardGvns.gug.gug_len_ind; i++)
    {
        printf(" 0x%02x", ie->param_data.forwardGvns.opsp.digits[i]);
    }

    printf("TNRN        : Terminating Network Routing Number\n");
    tnrn_len = (ie->param_data.forwardGvns.tnrn.tnrn_indicators)&(0x0F);
    printf("TNRN Len Ind: 0x%01x \n", (ie->param_data.forwardGvns.tnrn.tnrn_indicators)&(0x0F));
    printf("TNRN Num Plan Ind: 0x%01x \n", (ie->param_data.forwardGvns.tnrn.tnrn_indicators)&(0x70));
    for ( i = 0; i < tnrn_len; i++)
    {
        printf(" 0x%02x", ie->param_data.forwardGvns.tnrn.digits[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Loop Preventition Indicators Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintLoopPreventionIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : Loop Preventition Indicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : 0x%02x \n", ie->param_data.loopPreventionIndicators.loop_prev_ind);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the PrintNetworkManagementCtrlsPar
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintNetworkManagementCtrlsPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : Network Management Controls\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : ");

    for ( i = 0; i < ie->param_length; i++)
    {
        printf(" 0x%02x", ie->param_data.networkManagementControls.nw_mgt_ctrls[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Circuit Assignment Map Par
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintCircuitAssignmentMapPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : Circuit Assignment Map\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : follows...");
    printf("Map Type    : 0x%02x \n", ie->param_data.circuitAssignmentMap.map_type);
    printf("Map Format  : ");

    for ( i = 0; i < ( ie->param_length - 1 ); i++)
    {
        printf(" 0x%02x", ie->param_data.circuitAssignmentMap.map_format[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Correlation Id Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintCorrelationIdPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : Correlation Id\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : ");

    for ( i = 0; i < ie->param_length; i++)
    {
        printf(" 0x%02x", ie->param_data.correlationId.corr_Id[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the SCF Id parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintSCFIdPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : SCF Id\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : ");

    for ( i = 0; i < ie->param_length; i++)
    {
        printf(" 0x%02x", ie->param_data.scfId.scf_Id[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Call Diversion Treatment Indicators Param
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintCallDiversionTreatmentIndPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : Call Diversion Treatment Indicators\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : ");

    for ( i = 0; i < ie->param_length; i++)
    {
        printf(" 0x%02x", ie->param_data.callDivTreatIndicators.call_div_treat_ind[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Called IN Number Parameter
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintCalledINNumberPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : Called IN Number\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);

    /* value same as Calling Party Number */

    printf("addr_ind: 0x%02x \n", ie->param_data.callingPartyNum.addr_ind);
    printf("subfields4: 0x%02x \n", ie->param_data.callingPartyNum.subfields4);

    printf("dgts[%d]:", ie->param_length - 2);
    for (i = 0; i < (ie->param_length - 2); ++i )
    {
        printf("0x%02x ", ie->param_data.callingPartyNum.dgts[i]);
    }
    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Call Offering Treatment Ind Param
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintCallOfferingTreatmentIndPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : Call Offering Treatment Indicators\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : ");

    for ( i = 0; i < ie->param_length; i++)
    {
        printf(" 0x%02x", ie->param_data.callOffTreatIndicators.call_off_treat_ind[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Charged Party Identification Param
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintChargedPartyIdentificationPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : Charged Party Identification\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : ");

    for ( i = 0; i < ie->param_length; i++)
    {
        printf(" 0x%02x", ie->param_data.chargedPartyIdentification.charged_party_iden[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Conference Treatment Indicators Param
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintConferenceTreatmentIndPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : Conference Treatment Indicators\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : ");

    for ( i = 0; i < ie->param_length; i++)
    {
        printf(" 0x%02x", ie->param_data.confTreatIndicators.conf_treat[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Display Information Param
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintDisplayInformationPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : Display Information\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : ");

    for ( i = 0; i < ie->param_length; i++)
    {
        printf(" 0x%02x", ie->param_data.displayInformation.disp_info[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the UID Action Indicators Param
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintUIDActionIndPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : UID Action Indicators\n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : ");

    for ( i = 0; i < ie->param_length; i++)
    {
        printf(" 0x%02x", ie->param_data.uidActionIndicators.uid_action[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the UID Capability Indicators Param
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintUIDCapabilityIndPar(const ITS_ISUP_IE *ie)
{
    ushort i = 0;

    printf("\n");
    printf("Parameter   : UID Capability Indicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : ");

    for ( i = 0; i < ie->param_length; i++)
    {
        printf(" 0x%02x", ie->param_data.uidCapabilityIndicators.uid_cap_ind[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Hop Counter Param
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintHopCounterPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : Hop Counter \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : 0x%02x \n", ie->param_data.hopCounter.hop_counter);

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints the Collect Call Request Param
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined (CCITT) && defined(ITU_ISUP_97)
void
PrintCollectCallRequestPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter   : Collect Call Request \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length      : %d octets \n", ie->param_length);
    printf("Value       : 0x%02x \n", ie->param_data.collectCallRequest.collect_call_req);

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function prints the Circuit Assignment Map Parameter
 *
 *  Input Parameters:
 *      ie - a pointer to an information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

void
PrintCircuitAssignMap(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter            : Circuit Assignment Map \n");
    printf("Parameter Id         : 0x%02x \n", ie->param_id);
    printf("Length               : %d octets \n", ie->param_length);
    printf("Map Type             : 0x%02x \n", ie->param_data.circuitAssignmentMap.map_type);
    printf("Map Format           : ");

    for ( i = 0; i < ( ie->param_length - 1 ); i++)
    {
        printf(" 0x%02x", ie->param_data.circuitAssignmentMap.map_format[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function prints the Generic Name parameter
 *
 *  Input Parameters:
 *      ie - a pointer to an information element 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

void
PrintGenericName(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter            : Generic Name \n");
    printf("Parameter Id         : 0x%02x \n", ie->param_id);
    printf("Length               : %d octets \n", ie->param_length);
    printf("Presentation Avail   : 0x%02x \n", ie->param_data.genericName.pres_avail_name);
    printf("Name Information     : ");

    for ( i = 0; i < ( ie->param_length - 1 ); i++)
    {
        printf(" 0x%02x", ie->param_data.genericName.character[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function prints the Hop Counter parameter
 *
 *  Input Parameters:
 *      ie - a pointer to an information element 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

void
PrintHopCouner(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter            : Hop Counter \n");
    printf("Parameter Id         : 0x%02x \n", ie->param_id);
    printf("Length               : %d octets \n", ie->param_length);
    printf("Hop Counter          : 0x%02x \n", ie->param_data.hopCounter.hop_counter);

    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function prints the Operator Service Info parameter
 *
 *  Input Parameters:
 *      ie - a pointer to an information element 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

void
PrintOperatorServInfo(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter            : Operator Services Info \n");
    printf("Parameter Id         : 0x%02x \n", ie->param_id);
    printf("Length               : %d octets \n", ie->param_length);
    printf("Info Type and Value  : 0x%02x \n", ie->param_data.operServicesInfo.type_value);
    printf("\n");

    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function prints the Precedence parameter
 *
 *  Input Parameters:
 *      ie - a pointer to an information element 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

void
PrintPrecedence(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter            : Precedence \n");
    printf("Parameter Id         : 0x%02x \n", ie->param_id);
    printf("Length               : %d octets \n", ie->param_length);
    printf("LFB level            : 0x%02x \n", ie->param_data.precedence.lfb_level);
    printf("1st and 2nd NI digits: 0x%02x \n", ie->param_data.precedence.first_second_ni_digits);
    printf("3rd and 4th NI digits: 0x%02x \n", ie->param_data.precedence.third_fourth_ni_digits);

    printf("MLPP Service         : ");

    for ( i = 0; i < ( ie->param_length - 3 ); i++)
    {
        printf(" 0x%02x", ie->param_data.precedence.mlpp_service[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function prints the Remote Operations parameter
 *
 *  Input Parameters:
 *      ie - a pointer to an information element 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

void
PrintRemoteOperations(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter            : Remote Operations \n");
    printf("Parameter Id         : 0x%02x \n", ie->param_id);
    printf("Length               : %d octets \n", ie->param_length);
    printf("Protocol Profile     : 0x%02x \n", ie->param_data.remoteOperations.protocol_profile);

    printf("Components           : ");

    for ( i = 0; i < ( ie->param_length - 1 ); i++)
    {
        printf(" 0x%02x", ie->param_data.remoteOperations.components[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function prints the Transmission medium Used parameter
 *
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

void
PrintTransMediumUsed(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter            : Transmission Medium Used \n");
    printf("Parameter Id         : 0x%02x \n", ie->param_id);
    printf("Length               : %d octets \n", ie->param_length);
    printf("Trans medium used    : 0x%02x \n", ie->param_data.transMediumUsed.trans_med_used);

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the User Service Information Prime parameter
 *
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

void
PrintUserServInfoPrime(const ITS_ISUP_IE *ie)
{
   /*FIXME:
    */
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the User to user indicators parameter
 *
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

void
PrintUserToUserIndicators(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter            : User To User Indicators \n");
    printf("Parameter Id         : 0x%02x \n", ie->param_id);
    printf("Length               : %d octets \n", ie->param_length);
    printf("User indicators      : 0x%02x \n", ie->param_data.userToUserInd.indicator);
    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the User to user information parameter
 *
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

void
PrintUserToUserInfo(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter            : User To User Info \n");
    printf("Parameter Id         : 0x%02x \n", ie->param_id);
    printf("Length               : %d octets \n", ie->param_length);
    printf("User Info            : ");

    for ( i = 0; i< ie->param_length; i++)
    {
        printf(" 0x%02x", ie->param_data.userToUserInfo.userinfo[i]);
    }

    printf("\n");
    return;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will receive and decode an ISUP message.
 *
 *  Input Parameters:
 *      handle - the transport associated with the event
 *      event - pointer to an IntelliSS7 event
 *      hdr - header associated with the event
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned on decode success.
 *      Any other value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ISUP_ReceiveMsg(ITS_HANDLE handle, ITS_EVENT *event)

{
    //hrtime_t end;
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];    
    int          offset = 0;
    ITS_CTXT     vcic=0;
    ITS_USHORT   cic=0;
    MTP3_HEADER  mtp3;
    MTP3_ROUTING_LABEL label;
    int          recvResult = 0;
    ITS_HDR      hdr;

#if defined (CCITT) || ( defined (ANSI) && defined (ANSI_ISUP_95) )
    TCAP_CPT     cpt; /* for FAC Ind Function */
#endif

    memset((char *)&ies, 0, ITS_MAX_ISUP_IES * sizeof(ITS_ISUP_IE));
    memset((void*) &mtp3, 0, sizeof(MTP3_HEADER));
    memset((void*) &label, 0, sizeof(MTP3_ROUTING_LABEL));

    /* special handling for stat chage event */
    if (event->data[0] == ITS_STATE_CHANGE_EVENT)
    {
        printf("\n");
        printf("State change event received from stack \n");
        if (event->data[1] == ITS_STATE_PRIMARY) 
            printf("Request  received to become PRIMARY\n");
        else
            printf("Request  received to become BACKUP\n");
    
        printf("Application changing the STATE \n");
        printf("\n");
        return ITS_SUCCESS; 
    }
        
            

#if defined (CCITT)
    printf("\n");
    printf("--------------------------------------------------------------\n");
    printf("| ISUP_MSG | VCIC | CIC | SIO | MTP3_ROUTING_LABEL | Mesg Parm|\n");
    printf("--------------------------------------------------------------\n");
    printf("byte: 0      1-2    3-4    5     6-9                10..Params\n\n");
#elif defined (ANSI)
    printf("\n");
    printf("--------------------------------------------------------------\n");
    printf("| ISUP_MSG | VCIC | CIC | SIO | DPC | OPC | SLS | Mesg Parm|\n");
    printf("--------------------------------------------------------------\n");
    printf("byte: 0      1-2    3-4    5    6-8   9-11   12  13..Params\n\n");
#endif

    offset = 0;
    printf("App: Msg Type = %d\n", event->data[offset++]);

    vcic = ITS_GET_CTXT(&event->data[offset]);
    offset += sizeof(ITS_CTXT);
    
    printf("App: Vcic (virtual) = %d\n", vcic);

    cic = ((event->data[offset++]) & 0x00FF);
    cic |= ((event->data[offset++] << 8) & 0xFF00);

    printf("App: Cic (Real) = %d\n", cic);

    memcpy((void*)&mtp3, &event->data[offset], sizeof(MTP3_HEADER));
    
    printf("App: Sio = %d\n", MTP3_HDR_GET_SIO(mtp3));

    memcpy(&label, &mtp3.label, sizeof(MTP3_ROUTING_LABEL));

    printf("App: Opc  = %d\n", MTP3_RL_GET_OPC_VALUE(label));
    printf("App: Dpc  = %d\n", MTP3_RL_GET_DPC_VALUE(label));
    printf("App: Sls  = 0x%01x\n", MTP3_RL_GET_SLS(label));

    /*
     * Determine which ISUP message is packaged inside event structure
     */
    switch ( event->data[0] )
    {
    case ISUP_MSG_ACM:
        printf("\nReceived message::: ACM \n");
        recvResult = ISUP_ReceiveACMIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_ANM:
        printf("\nReceived message::: ANM \n");
        recvResult = ISUP_ReceiveANMIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_BLO:
        printf("\nReceived message::: BLO \n");
        recvResult = ISUP_ReceiveBLOIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_BLA:
        printf("\nReceived message::: BLA \n");
        recvResult = ISUP_ReceiveBLAIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_CCR:
        printf("\nReceived message::: CCR \n");
        recvResult = ISUP_ReceiveCCRIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_CFN:
        printf("\nReceived message::: CFN \n");
        recvResult = ISUP_ReceiveCFNIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_CGB:
        printf("\nReceived message::: CGB \n");
        recvResult = ISUP_ReceiveCGBIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_CGBA:
        printf("\nReceived message::: CGBA \n");
        recvResult = ISUP_ReceiveCGBAIndication(handle, event, &hdr, ies,
                                                &ieCount);
        break;

    case ISUP_MSG_CGU:
        printf("\nReceived message::: CGU \n");
        recvResult = ISUP_ReceiveCGUIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_CGUA:
        printf("\nReceived message::: CGUA \n");
        recvResult = ISUP_ReceiveCGUAIndication(handle, event, &hdr, ies,
                                                &ieCount);
        break;

    case ISUP_MSG_COT:
        printf("\nReceived message::: COT \n");
        recvResult = ISUP_ReceiveCOTIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_CPG:
        printf("\nReceived message::: CPG \n");
        recvResult = ISUP_ReceiveCPGIndication(handle, event, &hdr, ies,
                                               &ieCount);
        printf("CPG, ieCount = %d", ieCount);
        break;

    case ISUP_MSG_CQM:
        printf("\nReceived message::: CQM \n");
        recvResult = ISUP_ReceiveCQMIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_CQR:
        printf("\nReceived message::: CQR \n");
        recvResult = ISUP_ReceiveCQRIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

#ifdef ANSI
    case ISUP_MSG_CRA:
        printf("\nReceived message::: CRA \n");
        recvResult = ISUP_ReceiveCRAIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_CRM:
        printf("\nReceived message::: CRM \n");
        recvResult = ISUP_ReceiveCRMIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_CVR:
        printf("\nReceived message::: CVR \n");
        recvResult = ISUP_ReceiveCVRIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_CVT:
        printf("\nReceived message::: CVT \n");
        recvResult = ISUP_ReceiveCVTIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_EXM:
        printf("\nReceived message::: EXM \n");
        recvResult = ISUP_ReceiveEXMIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;
#endif

    case ISUP_MSG_FOT:
        printf("\nReceived message::: FOT \n");
        recvResult = ISUP_ReceiveFOTIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

#if defined (CCITT) || ( defined (ANSI) && defined (ANSI_ISUP_95) )
    case ISUP_MSG_FAC:
        printf("\nReceived message::: FAC \n");
        recvResult = ISUP_ReceiveFACIndication(handle, event, &hdr, ies,
                                               &ieCount, &cpt);
        break;
#endif

    case ISUP_MSG_GRA:
        printf("\nReceived message::: GRA \n");
        recvResult = ISUP_ReceiveGRAIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_GRS:
        printf("\nReceived message::: GRS \n");
        recvResult = ISUP_ReceiveGRSIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_IAM:
        {
        printf("\nReceived message::: IAM \n");
        recvResult = ISUP_ReceiveIAMIndication(handle, event, &hdr, ies,
                                               &ieCount);
        //end = gethrtime();
        //printf("&&&&&&&&&&&  END Timer %lld \n",end);
        }
        break;

    case ISUP_MSG_INF:
        printf("\nReceived message::: INF \n");
        recvResult = ISUP_ReceiveINFIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_INR:
        printf("\nReceived message::: INR \n");
        recvResult = ISUP_ReceiveINRIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_LPA:
        printf("\nReceived message::: LPA \n");
        recvResult = ISUP_ReceiveLPAIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_PAM:
        printf("\nReceived message::: PAM \n");
        recvResult = ISUP_ReceivePAMIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_REL:
        printf("\nReceived message::: REL \n");
        recvResult = ISUP_ReceiveRELIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_RES:
        printf("\nReceived message::: RES \n");
        recvResult = ISUP_ReceiveRESIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_RLC:
        printf("\nReceived message::: RLC \n");
        recvResult = ISUP_ReceiveRLCIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_RSC:
        printf("\nReceived message::: RSC \n");
        recvResult = ISUP_ReceiveRSCIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_SUS:
        printf("\nReceived message::: SUS \n");
        recvResult = ISUP_ReceiveSUSIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_UBA:
        printf("\nReceived message::: UBA \n");
        recvResult = ISUP_ReceiveUBAIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_UBL:
        printf("\nReceived message::: UBL \n");
        recvResult = ISUP_ReceiveUBLIndication(handle, event, &hdr, ies,
                                              &ieCount);
        break;

    case ISUP_MSG_UCIC:
        printf("\nReceived message::: UCIC \n");
        recvResult = ISUP_ReceiveUCICIndication(handle, event, &hdr, ies,
                                                &ieCount);
        break;


#ifdef CCITT
    case ISUP_MSG_CON:
        printf("\nReceived message::: CON \n");
        recvResult = ISUP_ReceiveCONIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_FAA:
        printf("\nReceived message::: FAA \n");
        recvResult = ISUP_ReceiveFAAIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_FAR:
        printf("\nReceived message::: FAR \n");
        recvResult = ISUP_ReceiveFARIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_FRJ:
        printf("\nReceived message::: FRJ \n");
        recvResult = ISUP_ReceiveFRJIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_IDR:
        printf("\nReceived message::: IDR \n");
        recvResult = ISUP_ReceiveIDRIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_IRS:
        printf("\nReceived message::: IRS \n");
        recvResult = ISUP_ReceiveIRSIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_NRM:
        printf("\nReceived message::: NRM \n");
        recvResult = ISUP_ReceiveNRMIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_OLM:
        printf("\nReceived message::: OLM \n");
        recvResult = ISUP_ReceiveOLMIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_SAM:
        printf("\nReceived message::: SAM \n");
        recvResult = ISUP_ReceiveSAMIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_SGM:
        printf("\nReceived message::: SGM \n");
        recvResult = ISUP_ReceiveSGMIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_UPA:
        printf("\nReceived message::: UPA \n");
        recvResult = ISUP_ReceiveUPAIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_UPT:
        printf("\nReceived message::: UPT \n");
        recvResult = ISUP_ReceiveUPTIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

    case ISUP_MSG_USR:
        printf("\nReceived message::: USR \n");
        recvResult = ISUP_ReceiveUSRIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;
#endif

#if defined (CCITT) && defined (ITU_ISUP_97)

    case ISUP_MSG_LOP:
        printf("\nReceived message::: LOP \n");
        recvResult = ISUP_ReceiveLOPIndication(handle, event, &hdr, ies,
                                               &ieCount);
        break;

#endif

#ifdef CCITT
    /* ITU99 Msgs */
    case ISUP_MSG_APM:
         printf("\nReceived message::: APM \n");
         recvResult = ISUP_ReceiveAPMIndication(handle, event, &hdr, ies,
                                                &ieCount);
         break;

    case ISUP_MSG_PRI:
         printf("\nReceived message::: PRI \n");
         recvResult = ISUP_ReceivePRIIndication(handle, event, &hdr, ies,
                                                &ieCount);
         break;

    case ISUP_MSG_SDM:
         printf("\nReceived message::: SDM \n");
         recvResult = ISUP_ReceiveSDMIndication(handle, event, &hdr, ies,
                                                &ieCount);
         break;
#endif

    case ISUP_MSG_TIM:
        printf("\nReceived Timeout Indication \n");
        recvResult = ISUP_ReceiveTimeoutIndication(handle, event, &hdr,
                                               ies, &ieCount);
        break;

    case ISUP_MSG_ERR:
        printf("\nReceived Error Indication \n");
        recvResult = ISUP_ReceiveErrorIndication(handle, event, &hdr,
                                               ies, &ieCount);
        break;

    case ISUP_MSG_IND:
        printf("\nReceived Request/Status Indication \n");
        recvResult = ISUP_ReceiveIndication(handle, event, &hdr,
                                               ies, &ieCount);
        break;

    default:
        printf("Unrecognized msg: 0x%02x \n", event->data[offset]);
        
        return !ITS_SUCCESS;
    }

    printf("Output Cic from Receive Indication = %d\n", hdr.context.cic);

    /*
     * Now Print the ISUP Message
     *
     */

    return (PrintISUPMsg(ies, ieCount));

}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints
 *
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
PrintIndication(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Indication Data \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("Indication Id: 0x%04x \n", ie->param_data.indData.indId);
    printf("SIO: 0x%04x \n", ie->param_data.indData.sio);
    printf("CIC: 0x%04x \n", ie->param_data.indData.cic);
    printf("OPC: 0x%04x \n", ie->param_data.indData.opc);
    printf("DPC: 0x%04x \n", ie->param_data.indData.dpc);
    printf("\n");
}

/****************************************************************************/
