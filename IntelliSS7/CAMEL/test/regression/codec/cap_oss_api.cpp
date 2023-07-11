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
//  ID: $Id: cap_oss_api.cpp,v 9.1 2005/03/23 12:51:16 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////


#include <cap_oss_api.h>
#include <cap_v3_lrfvn.h>


int 
OSS_GetEncodedPDU(
                int pduNum, 
                unsigned char **encodedPDU,
                size_t *encodedPDULength, 
                int valueNumber)
{
    OssGlobal w, *world = &w;
    OssBuf buffer = {0};
    int rc = 0;
    void *data = NULL;
    unsigned char otv[] = {0x05, 0x00};


    if (rc = ossinit(world, cap_v3_lrfvn)) 
    {
        printf("Failed to initialize the encoder with an error code of %d\n.", rc);
        return  rc;
    }

    switch (pduNum) {
	
    case ApplyChargingArg_PDU:
        data = &applyChargingArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ApplyChargingArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ApplyChargingArg...\n");
        break;

    case CAMEL_AChBillingChargingCharacteristics_PDU:
        
        data = &camel_AChBillingChargingCharacteristics1;
        ossPrint(world, "\n\tOSS-Printing unencoded CAMEL_AChBillingChargingCharacteristics PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding CAMEL_AChBillingChargingCharacteristics...\n");
        break;
    case CAMEL_CallResult_PDU:
        data = &camel_CallResult1;
        ossPrint(world, "\n\tOSS-Printing unencoded CAMEL_CallResult PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding CAMEL_CallResult...\n");
        break;
    case CAMEL_FCIBillingChargingCharacteristics_PDU:
        data = &camel_FCIBillingChargingCharacteristics1;
        ossPrint(world, "\n\tOSS-Printing unencoded CAMEL_FCIBillingChargingCharacteristics PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding CAMEL_FCIBillingChargingCharacteristics...\n");
        break;

    case CAMEL_FCIGPRSBillingChargingCharacteristics_PDU:
        data = &camel_FCIGPRSBillingChargingCharacteristics1;
        ossPrint(world, "\n\tOSS-Printing unencoded CAMEL_FCIGPRSBillingChargingCharacteristics PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding CAMEL_FCIGPRSBillingChargingCharacteristics...\n");
        break;
    case CAMEL_FCISMSBillingChargingCharacteristics_PDU:
        data = &camel_FCISMSBillingChargingCharacteristics1;
        ossPrint(world, "\n\tOSS-Printing unencoded CAMEL_FCISMSBillingChargingCharacteristics PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding CAMEL_FCISMSBillingChargingCharacteristics...\n");
        break;
    case CAMEL_SCIBillingChargingCharacteristics_PDU:
        data = &camel_SCIBillingChargingCharacteristics1;
        ossPrint(world, "\n\tOSS-Printing unencoded CAMEL_SCIBillingChargingCharacteristics PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding CAMEL_SCIBillingChargingCharacteristics...\n");
        break;
    case CAMEL_SCIGPRSBillingChargingCharacteristics_PDU:
        data = &camel_SCIGPRSBillingChargingCharacteristics1;
        ossPrint(world, "\n\tOSS-Printing unencoded CAMEL_SCIGPRSBillingChargingCharacteristics PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding CAMEL_SCIGPRSBillingChargingCharacteristics...\n");
        break;
    case UnavailableNetworkResource_PDU:
        data = &unavailableNetworkResource1;
        ossPrint(world, "\n\tOSS-Printing unencoded UnavailableNetworkResource PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding UnavailableNetworkResource...\n");
        break;
    case CancelFailed_PDU:
        data = &cancelFailed1;
        ossPrint(world, "\n\tOSS-Printing unencoded CancelFailed PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding CancelFailed...\n");
        break;
    case RequestedInfoError_PDU:
        data = &requestedInfoError1;
        ossPrint(world, "\n\tOSS-Printing unencoded RequestedInfoError PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding RequestedInfoError...\n");
        break;
    case TaskRefused_PDU:
        data = &taskRefused1;
        ossPrint(world, "\n\tOSS-Printing unencoded TaskRefused PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding TaskRefused...\n");
        break;
    case ApplyChargingReportArg_PDU:
        data = &applyChargingReportArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ApplyChargingReportArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ApplyChargingReportArg...\n");
        break;
    case AssistRequestInstructionsArg_PDU:
        data = &assistRequestInstructionsArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded AssistRequestInstructionsArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding AssistRequestInstructionsArg...\n");
        break;
    case CallGapArg_PDU:
        data = &callGapArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded CallGapArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding CallGapArg...\n");
        break;
    case CallInformationReportArg_PDU:
        data = &callInformationReportArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded CallInformationReportArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding CallInformationReportArg...\n");
        break;
    case CallInformationRequestArg_PDU:
        data = &callInformationRequestArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded CallInformationRequestArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding CallInformationRequestArg...\n");
        break;
    case CancelArg_PDU:
        data = &cancelArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded CancelArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding CancelArg...\n");
        break;
    case ConnectArg_PDU:
        data = &connectArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ConnectArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ConnectArg...\n");
        break;
    case ConnectToResourceArg_PDU:
        data = &connectToResourceArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ConnectToResourceArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ConnectToResourceArg...\n");
        break;
    case ContinueWithArgumentArg_PDU:
        data = &continueWithArgumentArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ContinueWithArgumentArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ContinueWithArgumentArg...\n");
        break;
    case EstablishTemporaryConnectionArg_PDU:
        data = &establishTemporaryConnectionArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded EstablishTemporaryConnectionArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding EstablishTemporaryConnectionArg...\n");
        break;
    case EventReportBCSMArg_PDU:
        data = &eventReportBCSMArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded EventReportBCSMArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding EventReportBCSMArg...\n");
        break;
    case FurnishChargingInformationArg_PDU:
        data = &furnishChargingInformationArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded FurnishChargingInformationArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding FurnishChargingInformationArg...\n");
        break;
    case InitialDPArg_PDU:
        data = &initialDPArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded InitialDPArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding InitialDPArg...\n");
        break;
    case ReleaseCallArg_PDU:
        data = &releaseCallArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ReleaseCallArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ReleaseCallArg...\n");
        break;
    case RequestReportBCSMEventArg_PDU:
        data = &requestReportBCSMEventArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded RequestReportBCSMEventArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding RequestReportBCSMEventArg...\n");
        break;
    case ResetTimerArg_PDU:
        data = &resetTimerArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ResetTimerArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ResetTimerArg...\n");
        break;
    case SendChargingInformationArg_PDU:
        data = &sendChargingInformationArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded SendChargingInformationArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding SendChargingInformationArg...\n");
        break;
    case PlayAnnouncementArg_PDU:
        data = &playAnnouncementArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded PlayAnnouncementArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding PlayAnnouncementArg...\n");
        break;
    case PromptAndCollectUserInformationArg_PDU:
        data = &promptAndCollectUserInformationArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded PromptAndCollectUserInformationArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding PromptAndCollectUserInformationArg...\n");
        break;
    case ReceivedInformationArg_PDU:
        data = &receivedInformationArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ReceivedInformationArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ReceivedInformationArg...\n");
        break;
    case SpecializedResourceReportArg_PDU:
        data = &specializedResourceReportArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded SpecializedResourceReportArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding SpecializedResourceReportArg...\n");
        break;
    case ConnectSMSArg_PDU:
        data = &connectSMSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ConnectSMSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ConnectSMSArg...\n");
        break;
    case EventReportSMSArg_PDU:
        data = &eventReportSMSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded EventReportSMSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding EventReportSMSArg...\n");
        break;
    case FurnishChargingInformationSMSArg_PDU:
        data = &furnishChargingInformationSMSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded FurnishChargingInformationSMSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding FurnishChargingInformationSMSArg...\n");
        break;
    case InitialDPSMSArg_PDU:
        data = &initialDPSMSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded InitialDPSMSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding InitialDPSMSArg...\n");
        break;
    case ReleaseSMSArg_PDU:
        data = &releaseSMSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ReleaseSMSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ReleaseSMSArg...\n");
        break;
    case RequestReportSMSEventArg_PDU:
        data = &requestReportSMSEventArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded RequestReportSMSEventArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding RequestReportSMSEventArg...\n");
        break;
    case ResetTimerSMSArg_PDU:
        data = &resetTimerSMSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ResetTimerSMSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ResetTimerSMSArg...\n");
        break;
    case ActivityTestGPRSArg_PDU:
        data = &activityTestGPRSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ActivityTestGPRSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ActivityTestGPRSArg...\n");
        break;
    case ApplyChargingGPRSArg_PDU:
        data = &applyChargingGPRSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ApplyChargingGPRSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ApplyChargingGPRSArg...\n");
        break;
    case ApplyChargingReportGPRSArg_PDU:
        data = &applyChargingReportGPRSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ApplyChargingReportGPRSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ApplyChargingReportGPRSArg...\n");
        break;
    case CancelGPRSArg_PDU:
        data = &cancelGPRSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded CancelGPRSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding CancelGPRSArg...\n");
        break;
    case ConnectGPRSArg_PDU:
        data = &connectGPRSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ConnectGPRSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ConnectGPRSArg...\n");
        break;
    case ContinueGPRSArg_PDU:
        data = &continueGPRSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ContinueGPRSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ContinueGPRSArg...\n");
        break;
    case EntityReleasedGPRSArg_PDU:
        data = &entityReleasedGPRSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded EntityReleasedGPRSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding EntityReleasedGPRSArg...\n");
        break;
    case FurnishChargingInformationGPRSArg_PDU:
        data = &furnishChargingInformationGPRSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded FurnishChargingInformationGPRSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding FurnishChargingInformationGPRSArg...\n");
        break;
    case InitialDPGPRSArg_PDU:
        data = &initialDPGPRSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded InitialDPGPRSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding InitialDPGPRSArg...\n");
        break;
    case ReleaseGPRSArg_PDU:
        data = &releaseGPRSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ReleaseGPRSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ReleaseGPRSArg...\n");
        break;
    case EventReportGPRSArg_PDU:
        data = &eventReportGPRSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded EventReportGPRSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding EventReportGPRSArg...\n");
        break;
    case RequestReportGPRSEventArg_PDU:
        data = &requestReportGPRSEventArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded RequestReportGPRSEventArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding RequestReportGPRSEventArg...\n");
        break;
    case ResetTimerGPRSArg_PDU:
        data = &resetTimerGPRSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded ResetTimerGPRSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding ResetTimerGPRSArg...\n");
        break;
    case SendChargingInformationGPRSArg_PDU:
        data = &sendChargingInformationGPRSArg1;
        ossPrint(world, "\n\tOSS-Printing unencoded SendChargingInformationGPRSArg PDU...\n");
        ossPrintPDU(world, pduNum, data);
        ossPrint(world, "\n\tOSS-Encoding SendChargingInformationGPRSArg...\n");
        break;
    
    }

        
    ossSetEncodingFlags(world, DEFINITE+DEBUGPDU);
    rc = ossEncode(world, pduNum, data, &buffer);

    if (!rc) 
    {
        *encodedPDULength = buffer.length;
        *encodedPDU = (unsigned char*)malloc(buffer.length);

        if (*encodedPDU) 
        {
            memcpy(*encodedPDU, buffer.value, buffer.length);
            ossFreeBuf(world, buffer.value);
            ossPrintHex(world, (char*)*encodedPDU, *encodedPDULength);
        }
        else
        {
            rc = -1;
        }
    }


    ossterm(world);

    return rc;
}

int 
OSS_GetDecodedPDU(
                int pduNum, 
                unsigned char *encodedPDU,
                size_t encodedPDULength, 
                void **decodedPDU)
{
    OssGlobal   w, *world = &w;
    OssBuf  buffer = {0};
    int     rc = 0;

#define BLOCK_SIZE 10240


    if (rc = ossinit(world, cap_v3_lrfvn)) 
    {
        printf("Failed to initialize the encoder with an error code of %d\n.", rc);
        return  rc;
    }

    ossSetDecodingFlags(world, DEFINITE+DEBUGPDU);
    buffer.value = (unsigned char*)encodedPDU;
    buffer.length = encodedPDULength;
    ossPrint(world, "\n\tOSS-Printing undecoded PDU...\n");
    ossPrintHex(world, (char*)encodedPDU, encodedPDULength);
    ossPrint(world, "\n\tOSS-Decoding the PDU...\n");

    *decodedPDU = malloc(BLOCK_SIZE);

    if (!*decodedPDU)
    {
        return -1;
    }

    ossSetDecodingLength(world, BLOCK_SIZE);
    rc = ossDecode(world, &pduNum, &buffer, decodedPDU);

    if (rc)
    {
        return rc;
    }

    switch (pduNum) {
	case ApplyChargingArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ApplyChargingArg PDU...\n");
	    break;
    case CAMEL_AChBillingChargingCharacteristics_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded CAMEL_AChBillingChargingCharacteristics PDU...\n");
        break;
    case CAMEL_CallResult_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded CAMEL_CallResult PDU...\n");
        break;
    case CAMEL_FCIBillingChargingCharacteristics_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded CAMEL_FCIBillingChargingCharacteristics PDU...\n");
        break; 
    case CAMEL_FCIGPRSBillingChargingCharacteristics_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded CAMEL_FCIGPRSBillingChargingCharacteristics PDU...\n");
        break; 
    case CAMEL_FCISMSBillingChargingCharacteristics_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded CAMEL_FCISMSBillingChargingCharacteristics PDU...\n");
        break; 
    case CAMEL_SCIBillingChargingCharacteristics_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded CAMEL_SCIBillingChargingCharacteristics PDU...\n");
        break; 
    case CAMEL_SCIGPRSBillingChargingCharacteristics_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded CAMEL_SCIGPRSBillingChargingCharacteristics PDU...\n");
        break; 
    case UnavailableNetworkResource_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded UnavailableNetworkResource PDU...\n");
        break; 
    case CancelFailed_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded CancelFailed PDU...\n");
        break; 
    case RequestedInfoError_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded RequestedInfoError PDU...\n");
        break; 
    case TaskRefused_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded TaskRefused PDU...\n");
        break; 
    case ApplyChargingReportArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ApplyChargingReportArg PDU...\n");
        break; 
    case AssistRequestInstructionsArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded AssistRequestInstructionsArg PDU...\n");
        break; 
    case CallGapArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded CallGapArg PDU...\n");
        break; 
    case CallInformationReportArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded CallInformationReportArg PDU...\n");
        break; 
    case CallInformationRequestArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded CallInformationRequestArg PDU...\n");
        break; 
    case CancelArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded CancelArg PDU...\n");
        break; 
    case ConnectArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ConnectArg PDU...\n");
        break; 
    case ConnectToResourceArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ConnectToResourceArg PDU...\n");
        break; 
    case ContinueWithArgumentArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ContinueWithArgumentArg PDU...\n");
        break; 
    case EstablishTemporaryConnectionArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded EstablishTemporaryConnectionArg PDU...\n");
        break; 
    case EventReportBCSMArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded EventReportBCSMArg PDU...\n");
        break; 
    case FurnishChargingInformationArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded FurnishChargingInformationArg PDU...\n");
        break; 
    case InitialDPArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded InitialDPArg PDU...\n");
        break; 
    case ReleaseCallArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ReleaseCallArg PDU...\n");
        break; 
    case RequestReportBCSMEventArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded RequestReportBCSMEventArg PDU...\n");
        break; 
    case ResetTimerArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ResetTimerArg PDU...\n");
        break; 
    case SendChargingInformationArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded SendChargingInformationArg PDU...\n");
        break; 
    case PlayAnnouncementArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded PlayAnnouncementArg PDU...\n");
        break; 
    case PromptAndCollectUserInformationArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded PromptAndCollectUserInformationArg PDU...\n");
        break; 
    case ReceivedInformationArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ReceivedInformationArg PDU...\n");
        break; 
    case SpecializedResourceReportArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded SpecializedResourceReportArg PDU...\n");
        break; 
    case ConnectSMSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ConnectSMSArg PDU...\n");
        break; 
    case EventReportSMSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded EventReportSMSArg PDU...\n");
        break; 
    case FurnishChargingInformationSMSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded FurnishChargingInformationSMSArg PDU...\n");
        break; 
    case InitialDPSMSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded InitialDPSMSArg PDU...\n");
        break; 
    case ReleaseSMSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ReleaseSMSArg PDU...\n");
        break; 
    case RequestReportSMSEventArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded RequestReportSMSEventArg PDU...\n");
        break; 
    case ResetTimerSMSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ResetTimerSMSArg PDU...\n");
        break; 
    case ActivityTestGPRSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ActivityTestGPRSArg PDU...\n");
        break; 
    case ApplyChargingGPRSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ApplyChargingGPRSArg PDU...\n");
        break; 
    case ApplyChargingReportGPRSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ApplyChargingReportGPRSArg PDU...\n");
        break; 
    case CancelGPRSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded CancelGPRSArg PDU...\n");
        break; 
    case ConnectGPRSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ConnectGPRSArg PDU...\n");
        break; 
    case ContinueGPRSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ContinueGPRSArg PDU...\n");
        break; 
    case EntityReleasedGPRSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded EntityReleasedGPRSArg PDU...\n");
        break; 
    case FurnishChargingInformationGPRSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded FurnishChargingInformationGPRSArg PDU...\n");
        break; 
    case InitialDPGPRSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded InitialDPGPRSArg PDU...\n");
        break; 
    case ReleaseGPRSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ReleaseGPRSArg PDU...\n");
        break; 
    case EventReportGPRSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded EventReportGPRSArg PDU...\n");
        break; 
    case RequestReportGPRSEventArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded RequestReportGPRSEventArg PDU...\n");
        break; 
    case ResetTimerGPRSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded ResetTimerGPRSArg PDU...\n");
        break; 
    case SendChargingInformationGPRSArg_PDU:
        ossPrint(world, "\n\tOSS-Printing decoded SendChargingInformationGPRSArg PDU...\n");
        break; 
    
    }

    ossPrintPDU(world, pduNum, *decodedPDU);
    ossterm(world);
    return rc;
}