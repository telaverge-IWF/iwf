/*
 * Copyright (C) 2000-2000 IntelliNet Technologies, Inc.  All rights reserved.
 *
 *
 * $Id: getv3pdu.c,v 9.1 2005/03/23 12:51:13 cvsadmin Exp $
 *
 * $Log: getv3pdu.c,v $
 * Revision 9.1  2005/03/23 12:51:13  cvsadmin
 * Begin PR6.5
 *
 * Revision 8.2  2005/03/21 13:49:17  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 7.1  2002/08/26 22:08:40  mmiers
 * Begin PR6.2
 *
 * Revision 6.1  2002/02/28 16:13:18  mmiers
 * Begin PR7.
 *
 * Revision 5.1  2001/08/16 20:45:14  mmiers
 * Start PR6.
 *
 * Revision 4.1  2001/05/01 00:53:01  mmiers
 * Begin PR5
 *
 * Revision 3.1  2000/08/15 23:56:28  mmiers
 *
 * Begin round 4.
 *
 * Revision 1.1  2000/06/22 19:35:52  npopov
 * This file is an OSS interface for testing.
 *
 *
 */





#include "cap_v3_lrfvn.h"	/* OSS-generated header */
int getEncodedPDU(int pduNum, char **encodedPDU, int *encodedPDULength, int);
int getDecodedPDU(int pduNum, char *encodedPDU,
				int encodedPDULength, void **decodedPDU);


int getEncodedPDU(int pduNum, char **encodedPDU,
				int *encodedPDULength, int valueNumber)
{


    OssGlobal	w, *world = &w;
    OssBuf	buffer = {0};
    int		rc = 0;
    void	*data = NULL;
    unsigned char otv[] = {0x05, 0x00};


    if (rc = ossinit(world, cap_v3_lrfvn)) {
	printf("Failed to initialize the encoder with an error code of %d\n.", rc);
	return  rc;
    }

    switch (pduNum) {
#ifdef xxx
	case UpdateLocationArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &updateLocationArg1;
	(((*((*(((updateLocationArg1).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((updateLocationArg1).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((updateLocationArg1).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((updateLocationArg1).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((updateLocationArg1).vlr_Capability).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((updateLocationArg1).vlr_Capability).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((updateLocationArg1).vlr_Capability).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((updateLocationArg1).vlr_Capability).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
		    break;
		case 2:
		    data = &updateLocationArg2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded UpdateLocationArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding UpdateLocationArg...\n");
	    break;
	case UpdateLocationRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &updateLocationRes1;
		    break;
		case 2:
		    data = &updateLocationRes2;
	(((*((*(((updateLocationRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((updateLocationRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((updateLocationRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((updateLocationRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded UpdateLocationRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding UpdateLocationRes...\n");
	    break;
	case CancelLocationArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &cancelLocationArg1;
		    break;
		case 2:
		    data = &cancelLocationArg2;
		    break;
		case 3:
		    data = &cancelLocationArg3;
	(((*(((cancelLocationArg3).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((cancelLocationArg3).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((cancelLocationArg3).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((cancelLocationArg3).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded CancelLocationArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding CancelLocationArg...\n");
	    break;
	case CancelLocationRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &cancelLocationRes1;
		    break;
		case 2:
		    data = &cancelLocationRes2;
	(((*(((cancelLocationRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((cancelLocationRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((cancelLocationRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((cancelLocationRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded CancelLocationRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding CancelLocationRes...\n");
	    break;
	case PurgeMS_Arg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &purgeMS_Arg1;
		    break;
		case 2:
		    data = &purgeMS_Arg2;
	(((*((*(((purgeMS_Arg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((purgeMS_Arg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((purgeMS_Arg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((purgeMS_Arg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded PurgeMS_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PurgeMS_Arg...\n");
	    break;
	case PurgeMS_Res_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &purgeMS_Res1;
		    break;
		case 2:
		    data = &purgeMS_Res2;
	(((*((*(((purgeMS_Res2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((purgeMS_Res2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((purgeMS_Res2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((purgeMS_Res2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded PurgeMS_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PurgeMS_Res...\n");
	    break;
	case SendIdentificationRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sendIdentificationRes1;
		    break;
		case 2:
		    data = &sendIdentificationRes2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SendIdentificationRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendIdentificationRes...\n");
	    break;
	case UpdateGprsLocationArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &updateGprsLocationArg1;
		    break;
		case 2:
		    data = &updateGprsLocationArg2;
	(((*((*(((updateGprsLocationArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((updateGprsLocationArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((updateGprsLocationArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((updateGprsLocationArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded UpdateGprsLocationArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding UpdateGprsLocationArg...\n");
	    break;
	case UpdateGprsLocationRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &updateGprsLocationRes1;
		    break;
		case 2:
		    data = &updateGprsLocationRes2;
	(((*((*(((updateGprsLocationRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((updateGprsLocationRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((updateGprsLocationRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((updateGprsLocationRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded UpdateGprsLocationRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding UpdateGprsLocationRes...\n");
	    break;
	case PrepareHO_Arg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &prepareHO_Arg1;
		    break;
		case 2:
		    data = &prepareHO_Arg2;
	(((*((((prepareHO_Arg2).bss_APDU).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((prepareHO_Arg2).bss_APDU).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((prepareHO_Arg2).bss_APDU).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((prepareHO_Arg2).bss_APDU).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded PrepareHO_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PrepareHO_Arg...\n");
	    break;
	case PrepareHO_Res_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &prepareHO_Res1;
		    break;
		case 2:
		    data = &prepareHO_Res2;
	(((*((((prepareHO_Res2).bss_APDU).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((prepareHO_Res2).bss_APDU).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((prepareHO_Res2).bss_APDU).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((prepareHO_Res2).bss_APDU).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded PrepareHO_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PrepareHO_Res...\n");
	    break;
	case PrepareSubsequentHO_Arg_PDU:
	    data = &prepareSubsequentHO_Arg1;
	(((*((((prepareSubsequentHO_Arg1).bss_APDU).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((prepareSubsequentHO_Arg1).bss_APDU).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((prepareSubsequentHO_Arg1).bss_APDU).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((prepareSubsequentHO_Arg1).bss_APDU).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    ossPrint(world, "\n\tOSS-Printing unencoded PrepareSubsequentHO_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PrepareSubsequentHO_Arg...\n");
	    break;
	case SendAuthenticationInfoArg_PDU:
	    data = &sendAuthenticationInfoArg1;
	    ossPrint(world, "\n\tOSS-Printing unencoded SendAuthenticationInfoArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendAuthenticationInfoArg...\n");
	    break;
	case SendAuthenticationInfoRes_PDU:
	    data = &sendAuthenticationInfoRes1;
	    ossPrint(world, "\n\tOSS-Printing unencoded SendAuthenticationInfoRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendAuthenticationInfoRes...\n");
	    break;
	case EquipmentStatus_PDU:
	    data = &equipmentStatus1;
	    ossPrint(world, "\n\tOSS-Printing unencoded EquipmentStatus PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding EquipmentStatus...\n");
	    break;
	case InsertSubscriberDataArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &insertSubscriberDataArg1;
		    break;
		case 2:
		    data = &insertSubscriberDataArg2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded InsertSubscriberDataArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding InsertSubscriberDataArg...\n");
	    break;
	case InsertSubscriberDataRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &insertSubscriberDataRes1;
		    break;
		case 2:
		    data = &insertSubscriberDataRes2;
	(((*(((insertSubscriberDataRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((insertSubscriberDataRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((insertSubscriberDataRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((insertSubscriberDataRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded InsertSubscriberDataRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding InsertSubscriberDataRes...\n");
	    break;
	case DeleteSubscriberDataArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &deleteSubscriberDataArg1;
		    break;
		case 2:
		    data = &deleteSubscriberDataArg2;
	(((*(((deleteSubscriberDataArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((deleteSubscriberDataArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((deleteSubscriberDataArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((deleteSubscriberDataArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
		    break;
		case 3:
		    data = &deleteSubscriberDataArg3;
	(((*(((deleteSubscriberDataArg3).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((deleteSubscriberDataArg3).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((deleteSubscriberDataArg3).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((deleteSubscriberDataArg3).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded DeleteSubscriberDataArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding DeleteSubscriberDataArg...\n");
	    break;
	case DeleteSubscriberDataRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &deleteSubscriberDataRes1;
		    break;
		case 2:
		    data = &deleteSubscriberDataRes2;
	(((*(((deleteSubscriberDataRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((deleteSubscriberDataRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((deleteSubscriberDataRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((deleteSubscriberDataRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded DeleteSubscriberDataRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding DeleteSubscriberDataRes...\n");
	    break;
	case SendRoutingInfoForGprsArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sendRoutingInfoForGprsArg1;
		    break;
		case 2:
		    data = &sendRoutingInfoForGprsArg2;
	(((*(((sendRoutingInfoForGprsArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sendRoutingInfoForGprsArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sendRoutingInfoForGprsArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sendRoutingInfoForGprsArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SendRoutingInfoForGprsArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendRoutingInfoForGprsArg...\n");
	    break;
	case SendRoutingInfoForGprsRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sendRoutingInfoForGprsRes1;
		    break;
		case 2:
		    data = &sendRoutingInfoForGprsRes2;
	(((*(((sendRoutingInfoForGprsRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sendRoutingInfoForGprsRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sendRoutingInfoForGprsRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sendRoutingInfoForGprsRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SendRoutingInfoForGprsRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendRoutingInfoForGprsRes...\n");
	    break;
	case FailureReportArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &failureReportArg1;
		    break;
		case 2:
		    data = &failureReportArg2;
	(((*(((failureReportArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((failureReportArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((failureReportArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((failureReportArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded FailureReportArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding FailureReportArg...\n");
	    break;
	case FailureReportRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &failureReportRes1;
		    break;
		case 2:
		    data = &failureReportRes2;
	(((*(((failureReportRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((failureReportRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((failureReportRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((failureReportRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded FailureReportRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding FailureReportRes...\n");
	    break;
	case NoteMsPresentForGprsArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &noteMsPresentForGprsArg1;
		    break;
		case 2:
		    data = &noteMsPresentForGprsArg2;
	(((*(((noteMsPresentForGprsArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((noteMsPresentForGprsArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((noteMsPresentForGprsArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((noteMsPresentForGprsArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded NoteMsPresentForGprsArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding NoteMsPresentForGprsArg...\n");
	    break;
	case NoteMsPresentForGprsRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &noteMsPresentForGprsRes1;
		    break;
		case 2:
		    data = &noteMsPresentForGprsRes2;
	(((*(((noteMsPresentForGprsRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((noteMsPresentForGprsRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((noteMsPresentForGprsRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((noteMsPresentForGprsRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded NoteMsPresentForGprsRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding NoteMsPresentForGprsRes...\n");
	    break;
	case ResetArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &resetArg1;
		    break;
		case 2:
		    data = &resetArg2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ResetArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ResetArg...\n");
	    break;
	case RestoreDataArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &restoreDataArg1;
		    break;
		case 2:
		    data = &restoreDataArg2;
	(((*(((restoreDataArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((restoreDataArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((restoreDataArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((restoreDataArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((restoreDataArg2).vlr_Capability).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((restoreDataArg2).vlr_Capability).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((restoreDataArg2).vlr_Capability).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((restoreDataArg2).vlr_Capability).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded RestoreDataArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RestoreDataArg...\n");
	    break;
	case RestoreDataRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &restoreDataRes1;
		    break;
		case 2:
		    data = &restoreDataRes2;
	(((*(((restoreDataRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((restoreDataRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((restoreDataRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((restoreDataRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded RestoreDataRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RestoreDataRes...\n");
	    break;
	case ProvideSubscriberInfoArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &provideSubscriberInfoArg1;
		    break;
		case 2:
		    data = &provideSubscriberInfoArg2;
	(((*((((provideSubscriberInfoArg2).requestedInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((provideSubscriberInfoArg2).requestedInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((provideSubscriberInfoArg2).requestedInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((provideSubscriberInfoArg2).requestedInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
		    break;
		case 3:
		    data = &provideSubscriberInfoArg3;
	(((*((((provideSubscriberInfoArg3).requestedInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((provideSubscriberInfoArg3).requestedInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((provideSubscriberInfoArg3).requestedInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((provideSubscriberInfoArg3).requestedInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((provideSubscriberInfoArg3).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((provideSubscriberInfoArg3).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((provideSubscriberInfoArg3).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((provideSubscriberInfoArg3).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ProvideSubscriberInfoArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProvideSubscriberInfoArg...\n");
	    break;
	case ProvideSubscriberInfoRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &provideSubscriberInfoRes1;
		    break;
		case 2:
		    data = &provideSubscriberInfoRes2;
	(((*(((provideSubscriberInfoRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((provideSubscriberInfoRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((provideSubscriberInfoRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((provideSubscriberInfoRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((provideSubscriberInfoRes2).subscriberInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((provideSubscriberInfoRes2).subscriberInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((provideSubscriberInfoRes2).subscriberInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((provideSubscriberInfoRes2).subscriberInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((((provideSubscriberInfoRes2).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((((provideSubscriberInfoRes2).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((((provideSubscriberInfoRes2).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((((provideSubscriberInfoRes2).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ProvideSubscriberInfoRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProvideSubscriberInfoRes...\n");
	    break;
	case AnyTimeInterrogationArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &anyTimeInterrogationArg1;
		    break;
		case 2:
		    data = &anyTimeInterrogationArg2;
	(((*(((anyTimeInterrogationArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((anyTimeInterrogationArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((anyTimeInterrogationArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((anyTimeInterrogationArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((anyTimeInterrogationArg2).requestedInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((anyTimeInterrogationArg2).requestedInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((anyTimeInterrogationArg2).requestedInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((anyTimeInterrogationArg2).requestedInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded AnyTimeInterrogationArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding AnyTimeInterrogationArg...\n");
	    break;
	case AnyTimeInterrogationRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &anyTimeInterrogationRes1;
		    break;
		case 2:
		    data = &anyTimeInterrogationRes2;
	(((*(((anyTimeInterrogationRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((anyTimeInterrogationRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((anyTimeInterrogationRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((anyTimeInterrogationRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((anyTimeInterrogationRes2).subscriberInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((anyTimeInterrogationRes2).subscriberInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((anyTimeInterrogationRes2).subscriberInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((anyTimeInterrogationRes2).subscriberInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((((anyTimeInterrogationRes2).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((((anyTimeInterrogationRes2).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((((anyTimeInterrogationRes2).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((((anyTimeInterrogationRes2).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded AnyTimeInterrogationRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding AnyTimeInterrogationRes...\n");
	    break;
	case ActivateTraceModeArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &activateTraceModeArg1;
		    break;
		case 2:
		    data = &activateTraceModeArg2;
	(((*(((activateTraceModeArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((activateTraceModeArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((activateTraceModeArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((activateTraceModeArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ActivateTraceModeArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ActivateTraceModeArg...\n");
	    break;
	case ActivateTraceModeRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &activateTraceModeRes1;
		    break;
		case 2:
		    data = &activateTraceModeRes2;
	(((*(((activateTraceModeRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((activateTraceModeRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((activateTraceModeRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((activateTraceModeRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ActivateTraceModeRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ActivateTraceModeRes...\n");
	    break;
	case DeactivateTraceModeArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &deactivateTraceModeArg1;
		    break;
		case 2:
		    data = &deactivateTraceModeArg2;
	(((*(((deactivateTraceModeArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((deactivateTraceModeArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((deactivateTraceModeArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((deactivateTraceModeArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded DeactivateTraceModeArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding DeactivateTraceModeArg...\n");
	    break;
	case DeactivateTraceModeRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &deactivateTraceModeRes1;
		    break;
		case 2:
		    data = &deactivateTraceModeRes2;
	(((*(((deactivateTraceModeRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((deactivateTraceModeRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((deactivateTraceModeRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((deactivateTraceModeRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded DeactivateTraceModeRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding DeactivateTraceModeRes...\n");
	    break;
	case SendRoutingInfoArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sendRoutingInfoArg1;
		    break;
		case 2:
		    data = &sendRoutingInfoArg2;
	(((*(((sendRoutingInfoArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sendRoutingInfoArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sendRoutingInfoArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sendRoutingInfoArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sendRoutingInfoArg2).networkSignalInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoArg2).networkSignalInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoArg2).networkSignalInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoArg2).networkSignalInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sendRoutingInfoArg2).cug_CheckInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoArg2).cug_CheckInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoArg2).cug_CheckInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoArg2).cug_CheckInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
		    break;
		case 3:
		    data = &sendRoutingInfoArg3;
	(((*(((sendRoutingInfoArg3).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sendRoutingInfoArg3).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sendRoutingInfoArg3).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sendRoutingInfoArg3).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sendRoutingInfoArg3).networkSignalInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoArg3).networkSignalInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoArg3).networkSignalInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoArg3).networkSignalInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sendRoutingInfoArg3).cug_CheckInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoArg3).cug_CheckInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoArg3).cug_CheckInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoArg3).cug_CheckInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sendRoutingInfoArg3).camelInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoArg3).camelInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoArg3).camelInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoArg3).camelInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sendRoutingInfoArg3).networkSignalInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoArg3).networkSignalInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoArg3).networkSignalInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoArg3).networkSignalInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SendRoutingInfoArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendRoutingInfoArg...\n");
	    break;
	case SendRoutingInfoRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sendRoutingInfoRes1;
		    break;
		case 2:
		    data = &sendRoutingInfoRes2;
	(((*((((sendRoutingInfoRes2).cug_CheckInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoRes2).cug_CheckInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoRes2).cug_CheckInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoRes2).cug_CheckInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((sendRoutingInfoRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sendRoutingInfoRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sendRoutingInfoRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sendRoutingInfoRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
		    break;
		case 3:
		    data = &sendRoutingInfoRes3;
	(((*((((sendRoutingInfoRes3).ccbs_Indicators).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoRes3).ccbs_Indicators).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoRes3).ccbs_Indicators).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoRes3).ccbs_Indicators).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((sendRoutingInfoRes3).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sendRoutingInfoRes3).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sendRoutingInfoRes3).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sendRoutingInfoRes3).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sendRoutingInfoRes3).subscriberInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoRes3).subscriberInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoRes3).subscriberInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoRes3).subscriberInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((((sendRoutingInfoRes3).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((((sendRoutingInfoRes3).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((((sendRoutingInfoRes3).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((((sendRoutingInfoRes3).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sendRoutingInfoRes3).cug_CheckInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoRes3).cug_CheckInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoRes3).cug_CheckInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoRes3).cug_CheckInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((((sendRoutingInfoRes3).extendedRoutingInfo).u).forwardingData).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((((sendRoutingInfoRes3).extendedRoutingInfo).u).forwardingData).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((((sendRoutingInfoRes3).extendedRoutingInfo).u).forwardingData).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((((sendRoutingInfoRes3).extendedRoutingInfo).u).forwardingData).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sendRoutingInfoRes3).naea_PreferredCI).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoRes3).naea_PreferredCI).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoRes3).naea_PreferredCI).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoRes3).naea_PreferredCI).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
		    break;
		case 4:
		    data = &sendRoutingInfoRes4;
	(((*((((sendRoutingInfoRes4).ccbs_Indicators).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoRes4).ccbs_Indicators).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoRes4).ccbs_Indicators).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoRes4).ccbs_Indicators).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((sendRoutingInfoRes4).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sendRoutingInfoRes4).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sendRoutingInfoRes4).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sendRoutingInfoRes4).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sendRoutingInfoRes4).subscriberInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoRes4).subscriberInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoRes4).subscriberInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoRes4).subscriberInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((((sendRoutingInfoRes4).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((((sendRoutingInfoRes4).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((((sendRoutingInfoRes4).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((((sendRoutingInfoRes4).subscriberInfo).locationInformation).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sendRoutingInfoRes4).cug_CheckInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoRes4).cug_CheckInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoRes4).cug_CheckInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoRes4).cug_CheckInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sendRoutingInfoRes4).naea_PreferredCI).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sendRoutingInfoRes4).naea_PreferredCI).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sendRoutingInfoRes4).naea_PreferredCI).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sendRoutingInfoRes4).naea_PreferredCI).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((((sendRoutingInfoRes3).extendedRoutingInfo).u).forwardingData).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((((sendRoutingInfoRes3).extendedRoutingInfo).u).forwardingData).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((((sendRoutingInfoRes3).extendedRoutingInfo).u).forwardingData).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((((sendRoutingInfoRes3).extendedRoutingInfo).u).forwardingData).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).forwardingData).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).forwardingData).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).forwardingData).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).forwardingData).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).value).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).value).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((*((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((*((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((*((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((*((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((*((*((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((*((*((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((*((*((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((*((*((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((*((*((*((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((*((*((*((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((*((*((*((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((*((*((*((*((*((*((*((*((*((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).t_CSI).t_BcsmCamelTDPDataList)).next)).next)).next)).next)).next)).next)).next)).next)).next)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).o_CSI).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).o_CSI).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).o_CSI).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).o_CSI).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).o_CSI).o_BcsmCamelTDPDataList)).value).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).o_CSI).o_BcsmCamelTDPDataList)).value).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).o_CSI).o_BcsmCamelTDPDataList)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((*(((((((sendRoutingInfoRes4).extendedRoutingInfo).u).camelRoutingInfo).gmscCamelSubscriptionInfo).o_CSI).o_BcsmCamelTDPDataList)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SendRoutingInfoRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendRoutingInfoRes...\n");
	    break;
	case RoutingInfo_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &routingInfo1;
		    break;
		case 2:
		    data = &routingInfo2;
		    break;
		case 3:
		    data = &routingInfo3;
	(((*(((((routingInfo3).u).forwardingData).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((((routingInfo3).u).forwardingData).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((((routingInfo3).u).forwardingData).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((((routingInfo3).u).forwardingData).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded RoutingInfo PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RoutingInfo...\n");
	    break;
	case ProvideRoamingNumberArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &provideRoamingNumberArg1;
		    break;
		case 2:
		    data = &provideRoamingNumberArg2;
	(((*(((provideRoamingNumberArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((provideRoamingNumberArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((provideRoamingNumberArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((provideRoamingNumberArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((provideRoamingNumberArg2).networkSignalInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((provideRoamingNumberArg2).networkSignalInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((provideRoamingNumberArg2).networkSignalInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((provideRoamingNumberArg2).networkSignalInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((provideRoamingNumberArg2).gsm_BearerCapability).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((provideRoamingNumberArg2).gsm_BearerCapability).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((provideRoamingNumberArg2).gsm_BearerCapability).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((provideRoamingNumberArg2).gsm_BearerCapability).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ProvideRoamingNumberArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProvideRoamingNumberArg...\n");
	    break;
	case ProvideRoamingNumberRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &provideRoamingNumberRes1;
		    break;
		case 2:
		    data = &provideRoamingNumberRes2;
	(((*(((provideRoamingNumberRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((provideRoamingNumberRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((provideRoamingNumberRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((provideRoamingNumberRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ProvideRoamingNumberRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProvideRoamingNumberRes...\n");
	    break;
	case ResumeCallHandlingArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &resumeCallHandlingArg1;
	(((*((((resumeCallHandlingArg1).forwardingData).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((resumeCallHandlingArg1).forwardingData).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((resumeCallHandlingArg1).forwardingData).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((resumeCallHandlingArg1).forwardingData).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
		    break;
		case 2:
		    data = &resumeCallHandlingArg2;
	(((*(((resumeCallHandlingArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((resumeCallHandlingArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((resumeCallHandlingArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((resumeCallHandlingArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((resumeCallHandlingArg2).o_CSI).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((resumeCallHandlingArg2).o_CSI).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((resumeCallHandlingArg2).o_CSI).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((resumeCallHandlingArg2).o_CSI).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((*(((resumeCallHandlingArg2).o_CSI).o_BcsmCamelTDPDataList)).value).extensionContainer).privateExtensionList)).value).extensionType).value = otv;;
	(((*((((*(((resumeCallHandlingArg2).o_CSI).o_BcsmCamelTDPDataList)).value).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((*(((resumeCallHandlingArg2).o_CSI).o_BcsmCamelTDPDataList)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((*(((resumeCallHandlingArg2).o_CSI).o_BcsmCamelTDPDataList)).value).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((resumeCallHandlingArg2).cug_CheckInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((resumeCallHandlingArg2).cug_CheckInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((resumeCallHandlingArg2).cug_CheckInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((resumeCallHandlingArg2).cug_CheckInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((resumeCallHandlingArg2).forwardingData).extensionContainer).privateExtensionList)).value).extensionType).value = otv;;
	(((*((((resumeCallHandlingArg2).forwardingData).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((resumeCallHandlingArg2).forwardingData).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((resumeCallHandlingArg2).forwardingData).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ResumeCallHandlingArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ResumeCallHandlingArg...\n");
	    break;
	case ResumeCallHandlingRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &resumeCallHandlingRes1;
		    break;
		case 2:
		    data = &resumeCallHandlingRes2;
	(((*(((resumeCallHandlingRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((resumeCallHandlingRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((resumeCallHandlingRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((resumeCallHandlingRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ResumeCallHandlingRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ResumeCallHandlingRes...\n");
	    break;
	case ProvideSIWFSNumberArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &provideSIWFSNumberArg1;
	(((*((((provideSIWFSNumberArg1).chosenChannel).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((provideSIWFSNumberArg1).chosenChannel).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((provideSIWFSNumberArg1).chosenChannel).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((provideSIWFSNumberArg1).chosenChannel).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((provideSIWFSNumberArg1).isdn_BearerCapability).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((provideSIWFSNumberArg1).isdn_BearerCapability).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((provideSIWFSNumberArg1).isdn_BearerCapability).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((provideSIWFSNumberArg1).isdn_BearerCapability).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((provideSIWFSNumberArg1).gsm_BearerCapability).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((provideSIWFSNumberArg1).gsm_BearerCapability).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((provideSIWFSNumberArg1).gsm_BearerCapability).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((provideSIWFSNumberArg1).gsm_BearerCapability).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
		    break;
		case 2:
		    data = &provideSIWFSNumberArg2;
	(((*(((provideSIWFSNumberArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((provideSIWFSNumberArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((provideSIWFSNumberArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((provideSIWFSNumberArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((provideSIWFSNumberArg2).highLayerCompatibility).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((provideSIWFSNumberArg2).highLayerCompatibility).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((provideSIWFSNumberArg2).highLayerCompatibility).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((provideSIWFSNumberArg2).highLayerCompatibility).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((provideSIWFSNumberArg2).lowerLayerCompatibility).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((provideSIWFSNumberArg2).lowerLayerCompatibility).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((provideSIWFSNumberArg2).lowerLayerCompatibility).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((provideSIWFSNumberArg2).lowerLayerCompatibility).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((provideSIWFSNumberArg2).chosenChannel).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((provideSIWFSNumberArg2).chosenChannel).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((provideSIWFSNumberArg2).chosenChannel).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((provideSIWFSNumberArg2).chosenChannel).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((provideSIWFSNumberArg2).isdn_BearerCapability).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((provideSIWFSNumberArg2).isdn_BearerCapability).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((provideSIWFSNumberArg2).isdn_BearerCapability).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((provideSIWFSNumberArg2).isdn_BearerCapability).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((provideSIWFSNumberArg2).gsm_BearerCapability).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((provideSIWFSNumberArg2).gsm_BearerCapability).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((provideSIWFSNumberArg2).gsm_BearerCapability).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((provideSIWFSNumberArg2).gsm_BearerCapability).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ProvideSIWFSNumberArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProvideSIWFSNumberArg...\n");
	    break;
	case ProvideSIWFSNumberRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &provideSIWFSNumberRes1;
		    break;
		case 2:
		    data = &provideSIWFSNumberRes2;
	(((*(((provideSIWFSNumberRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((provideSIWFSNumberRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((provideSIWFSNumberRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((provideSIWFSNumberRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ProvideSIWFSNumberRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProvideSIWFSNumberRes...\n");
	    break;
	case SIWFSSignallingModifyArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sIWFSSignallingModifyArg1;
		    break;
		case 2:
		    data = &sIWFSSignallingModifyArg2;
	(((*(((sIWFSSignallingModifyArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sIWFSSignallingModifyArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sIWFSSignallingModifyArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sIWFSSignallingModifyArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((sIWFSSignallingModifyArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sIWFSSignallingModifyArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((((sIWFSSignallingModifyArg2).chosenChannel).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sIWFSSignallingModifyArg2).chosenChannel).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sIWFSSignallingModifyArg2).chosenChannel).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sIWFSSignallingModifyArg2).chosenChannel).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sIWFSSignallingModifyArg2).channelType).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sIWFSSignallingModifyArg2).channelType).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sIWFSSignallingModifyArg2).channelType).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sIWFSSignallingModifyArg2).channelType).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SIWFSSignallingModifyArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SIWFSSignallingModifyArg...\n");
	    break;
	case SIWFSSignallingModifyRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sIWFSSignallingModifyRes1;
		    break;
		case 2:
		    data = &sIWFSSignallingModifyRes2;
	(((*(((sIWFSSignallingModifyRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sIWFSSignallingModifyRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sIWFSSignallingModifyRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sIWFSSignallingModifyRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((sIWFSSignallingModifyRes2).chosenChannel).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((sIWFSSignallingModifyRes2).chosenChannel).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((sIWFSSignallingModifyRes2).chosenChannel).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((sIWFSSignallingModifyRes2).chosenChannel).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SIWFSSignallingModifyRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SIWFSSignallingModifyRes...\n");
	    break;
	case SetReportingStateArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &setReportingStateArg1;
		    break;
		case 2:
		    data = &setReportingStateArg2;
	(((*(((setReportingStateArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((setReportingStateArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((setReportingStateArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((setReportingStateArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SetReportingStateArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SetReportingStateArg...\n");
	    break;
	case SetReportingStateRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &setReportingStateRes1;
		    break;
		case 2:
		    data = &setReportingStateRes2;
	(((*(((setReportingStateRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((setReportingStateRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((setReportingStateRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((setReportingStateRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SetReportingStateRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SetReportingStateRes...\n");
	    break;
	case StatusReportArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &statusReportArg1;
		    break;
		case 2:
		    data = &statusReportArg2;
	(((*(((statusReportArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((statusReportArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((statusReportArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((statusReportArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((statusReportArg2).callReportdata).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((statusReportArg2).callReportdata).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((statusReportArg2).callReportdata).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((statusReportArg2).callReportdata).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((statusReportArg2).eventReportData).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((statusReportArg2).eventReportData).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((statusReportArg2).eventReportData).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((statusReportArg2).eventReportData).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded StatusReportArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding StatusReportArg...\n");
	    break;
	case StatusReportRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &statusReportRes1;
		    break;
		case 2:
		    data = &statusReportRes2;
	(((*(((statusReportRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((statusReportRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((statusReportRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((statusReportRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded StatusReportRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding StatusReportRes...\n");
	    break;
	case RemoteUserFreeArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &remoteUserFreeArg1;
	(((*((((remoteUserFreeArg1).callInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((remoteUserFreeArg1).callInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((remoteUserFreeArg1).callInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((remoteUserFreeArg1).callInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
		    break;
		case 2:
		    data = &remoteUserFreeArg2;
	(((*(((remoteUserFreeArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((remoteUserFreeArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((remoteUserFreeArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((remoteUserFreeArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((remoteUserFreeArg2).callInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((remoteUserFreeArg2).callInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((remoteUserFreeArg2).callInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((remoteUserFreeArg2).callInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded RemoteUserFreeArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RemoteUserFreeArg...\n");
	    break;
	case RemoteUserFreeRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &remoteUserFreeRes1;
		    break;
		case 2:
		    data = &remoteUserFreeRes2;
	(((*(((remoteUserFreeRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((remoteUserFreeRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((remoteUserFreeRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((remoteUserFreeRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded RemoteUserFreeRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RemoteUserFreeRes...\n");
	    break;
	case RegisterSS_Arg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &registerSS_Arg1;
		    break;
		case 2:
		    data = &registerSS_Arg2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded RegisterSS_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RegisterSS_Arg...\n");
	    break;
	case SS_ForBS_Code_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sS_ForBS_Code1;
		    break;
		case 2:
		    data = &sS_ForBS_Code2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SS_ForBS_Code PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SS_ForBS_Code...\n");
	    break;
	case InterrogateSS_Res_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &interrogateSS_Res1;
		    break;
		case 2:
		    data = &interrogateSS_Res2;
		    break;
		case 3:
		    data = &interrogateSS_Res3;
		    break;
		case 4:
		    data = &interrogateSS_Res4;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded InterrogateSS_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding InterrogateSS_Res...\n");
	    break;
	case USSD_Arg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &uSSD_Arg1;
		    break;
		case 2:
		    data = &uSSD_Arg2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded USSD_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding USSD_Arg...\n");
	    break;
	case USSD_Res_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &uSSD_Res1;
		    break;
		case 2:
		    data = &uSSD_Res2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded USSD_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding USSD_Res...\n");
	    break;
	case Password_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &password;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded Password PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding Password...\n");
	    break;
	case GuidanceInfo_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &guidanceInfo;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded GuidanceInfo PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding GuidanceInfo...\n");
	    break;
	case SS_InfoList_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sS_InfoList;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SS_InfoList PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SS_InfoList...\n");
	    break;
	case SS_InvocationNotificationArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sS_InvocationNotificationArg1;
		    break;
		case 2:
		    data = &sS_InvocationNotificationArg2;
	(((*(((sS_InvocationNotificationArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sS_InvocationNotificationArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sS_InvocationNotificationArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sS_InvocationNotificationArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SS_InvocationNotificationArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SS_InvocationNotificationArg...\n");
	    break;
	case SS_InvocationNotificationRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sS_InvocationNotificationRes1;
		    break;
		case 2:
		    data = &sS_InvocationNotificationRes2;
	(((*(((sS_InvocationNotificationRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sS_InvocationNotificationRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sS_InvocationNotificationRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sS_InvocationNotificationRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SS_InvocationNotificationRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SS_InvocationNotificationRes...\n");
	    break;
	case RegisterCC_EntryArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &registerCC_EntryArg1;
		    break;
		case 2:
		    data = &registerCC_EntryArg2;
	(((*(((((registerCC_EntryArg2).ccbs_Data).networkSignalInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((((registerCC_EntryArg2).ccbs_Data).networkSignalInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((((registerCC_EntryArg2).ccbs_Data).networkSignalInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((((registerCC_EntryArg2).ccbs_Data).networkSignalInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*(((((registerCC_EntryArg2).ccbs_Data).callInfo).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((((registerCC_EntryArg2).ccbs_Data).callInfo).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((((registerCC_EntryArg2).ccbs_Data).callInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((((registerCC_EntryArg2).ccbs_Data).callInfo).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded RegisterCC_EntryArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RegisterCC_EntryArg...\n");
	    break;
	case RegisterCC_EntryRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &registerCC_EntryRes1;
		    break;
		case 2:
		    data = &registerCC_EntryRes2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded RegisterCC_EntryRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RegisterCC_EntryRes...\n");
	    break;
	case EraseCC_EntryArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &eraseCC_EntryArg1;
		    break;
		case 2:
		    data = &eraseCC_EntryArg2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded EraseCC_EntryArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding EraseCC_EntryArg...\n");
	    break;
	case EraseCC_EntryRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &eraseCC_EntryRes1;
		    break;
		case 2:
		    data = &eraseCC_EntryRes2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded EraseCC_EntryRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding EraseCC_EntryRes...\n");
	    break;
	case RoutingInfoForSM_Arg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &routingInfoForSM_Arg1;
		    break;
		case 2:
		    data = &routingInfoForSM_Arg2;
	(((*(((routingInfoForSM_Arg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((routingInfoForSM_Arg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((routingInfoForSM_Arg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((routingInfoForSM_Arg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((routingInfoForSM_Res2).locationInfoWithLMSI).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((routingInfoForSM_Res2).locationInfoWithLMSI).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((routingInfoForSM_Res2).locationInfoWithLMSI).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((routingInfoForSM_Res2).locationInfoWithLMSI).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded RoutingInfoForSM_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RoutingInfoForSM_Arg...\n");
	    break;
	case RoutingInfoForSM_Res_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &routingInfoForSM_Res1;
		    break;
		case 2:
		    data = &routingInfoForSM_Res2;
	(((*(((routingInfoForSM_Res2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((routingInfoForSM_Res2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((routingInfoForSM_Res2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((routingInfoForSM_Res2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	(((*((((routingInfoForSM_Res2).locationInfoWithLMSI).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*((((routingInfoForSM_Res2).locationInfoWithLMSI).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*((((routingInfoForSM_Res2).locationInfoWithLMSI).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*((((routingInfoForSM_Res2).locationInfoWithLMSI).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded RoutingInfoForSM_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RoutingInfoForSM_Res...\n");
	    break;
	case MO_ForwardSM_Arg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &mO_ForwardSM_Arg1;
		    break;
		case 2:
		    data = &mO_ForwardSM_Arg2;
		    break;
		case 3:
		    data = &mO_ForwardSM_Arg3;
	(((*(((mO_ForwardSM_Arg3).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((mO_ForwardSM_Arg3).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((mO_ForwardSM_Arg3).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((mO_ForwardSM_Arg3).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded MO_ForwardSM_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding MO_ForwardSM_Arg...\n");
	    break;
	case MO_ForwardSM_Res_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &mO_ForwardSM_Res1;
		    break;
		case 2:
		    data = &mO_ForwardSM_Res2;
	(((*(((mO_ForwardSM_Res2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((mO_ForwardSM_Res2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((mO_ForwardSM_Res2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((mO_ForwardSM_Res2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded MO_ForwardSM_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding MO_ForwardSM_Res...\n");
	    break;
	case MT_ForwardSM_Arg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &mT_ForwardSM_Arg1;
		    break;
		case 2:
		    data = &mT_ForwardSM_Arg2;
	(((*(((mT_ForwardSM_Arg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((mT_ForwardSM_Arg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((mT_ForwardSM_Arg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((mT_ForwardSM_Arg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded MT_ForwardSM_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding MT_ForwardSM_Arg...\n");
	    break;
	case MT_ForwardSM_Res_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &mT_ForwardSM_Res1;
		    break;
		case 2:
		    data = &mT_ForwardSM_Res2;
	(((*(((mT_ForwardSM_Res2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((mT_ForwardSM_Res2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((mT_ForwardSM_Res2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((mT_ForwardSM_Res2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded MT_ForwardSM_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding MT_ForwardSM_Res...\n");
	    break;
	case ReportSM_DeliveryStatusArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &reportSM_DeliveryStatusArg1;
		    break;
		case 2:
		    data = &reportSM_DeliveryStatusArg2;
	(((*(((reportSM_DeliveryStatusArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((reportSM_DeliveryStatusArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((reportSM_DeliveryStatusArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((reportSM_DeliveryStatusArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ReportSM_DeliveryStatusArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ReportSM_DeliveryStatusArg...\n");
	    break;
	case ReportSM_DeliveryStatusRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &reportSM_DeliveryStatusRes1;
		    break;
		case 2:
		    data = &reportSM_DeliveryStatusRes2;
	(((*(((reportSM_DeliveryStatusRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((reportSM_DeliveryStatusRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((reportSM_DeliveryStatusRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((reportSM_DeliveryStatusRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ReportSM_DeliveryStatusRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ReportSM_DeliveryStatusRes...\n");
	    break;
	case AlertServiceCentreArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &alertServiceCentreArg;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded AlertServiceCentreArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding AlertServiceCentreArg...\n");
	    break;
	case InformServiceCentreArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &informServiceCentreArg1;
		    break;
		case 2:
		    data = &informServiceCentreArg2;
	(((*(((informServiceCentreArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((informServiceCentreArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((informServiceCentreArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((informServiceCentreArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded InformServiceCentreArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding InformServiceCentreArg...\n");
	    break;
	case ReadyForSM_Arg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &readyForSM_Arg1;
		    break;
		case 2:
		    data = &readyForSM_Arg2;
	(((*(((readyForSM_Arg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((readyForSM_Arg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((readyForSM_Arg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((readyForSM_Arg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ReadyForSM_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ReadyForSM_Arg...\n");
	    break;
	case ReadyForSM_Res_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &readyForSM_Res;
	(((*(((readyForSM_Res).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((readyForSM_Res).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((readyForSM_Res).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((readyForSM_Res).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ReadyForSM_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ReadyForSM_Res...\n");
	    break;
	case RoamingNotAllowedParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &roamingNotAllowedParam1;
		    break;
		case 2:
		    data = &roamingNotAllowedParam2;
	(((*(((roamingNotAllowedParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((roamingNotAllowedParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((roamingNotAllowedParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((roamingNotAllowedParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded RoamingNotAllowedParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RoamingNotAllowedParam...\n");
	    break;
	case CallBarredParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &callBarredParam1;
		    break;
		case 2:
		    data = &callBarredParam2;
		    break;
		case 3:
		    data = &callBarredParam3;
	(((*(((((callBarredParam3).u).extensibleCallBarredParam).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((((callBarredParam3).u).extensibleCallBarredParam).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((((callBarredParam3).u).extensibleCallBarredParam).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((((callBarredParam3).u).extensibleCallBarredParam).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded CallBarredParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding CallBarredParam...\n");
	    break;
	case CUG_RejectParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &cUG_RejectParam1;
		    break;
		case 2:
		    data = &cUG_RejectParam2;
	(((*(((cUG_RejectParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((cUG_RejectParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((cUG_RejectParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((cUG_RejectParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded CUG_RejectParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding CUG_RejectParam...\n");
	    break;
	case SS_IncompatibilityCause_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sS_IncompatibilityCause1;
		    break;
		case 2:
		    data = &sS_IncompatibilityCause2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SS_IncompatibilityCause PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SS_IncompatibilityCause...\n");
	    break;
	case PW_RegistrationFailureCause_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &pW_RegistrationFailureCause;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded PW_RegistrationFailureCause PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PW_RegistrationFailureCause...\n");
	    break;
	case SM_DeliveryFailureCause_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sM_DeliveryFailureCause1;
		    break;
		case 2:
		    data = &sM_DeliveryFailureCause2;
	(((*(((sM_DeliveryFailureCause2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sM_DeliveryFailureCause2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sM_DeliveryFailureCause2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sM_DeliveryFailureCause2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SM_DeliveryFailureCause PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SM_DeliveryFailureCause...\n");
	    break;
	case AbsentSubscriberSM_Param_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &absentSubscriberSM_Param1;
		    break;
		case 2:
		    data = &absentSubscriberSM_Param2;
	(((*(((absentSubscriberSM_Param2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((absentSubscriberSM_Param2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((absentSubscriberSM_Param2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((absentSubscriberSM_Param2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded AbsentSubscriberSM_Param PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding AbsentSubscriberSM_Param...\n");
	    break;
	case SystemFailureParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &systemFailureParam1;
		    break;
		case 2:
		    data = &systemFailureParam2;
		    break;
		case 3:
		    data = &systemFailureParam3;
	(((*(((((systemFailureParam3).u).extensibleSystemFailureParam).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((((systemFailureParam3).u).extensibleSystemFailureParam).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((((systemFailureParam3).u).extensibleSystemFailureParam).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((((systemFailureParam3).u).extensibleSystemFailureParam).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SystemFailureParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SystemFailureParam...\n");
	    break;
	case DataMissingParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &dataMissingParam1;
		    break;
		case 2:
		    data = &dataMissingParam2;
	(((*(((dataMissingParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((dataMissingParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((dataMissingParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((dataMissingParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded DataMissingParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding DataMissingParam...\n");
	    break;
	case UnexpectedDataParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &unexpectedDataParam1;
		    break;
		case 2:
		    data = &unexpectedDataParam2;
	(((*(((unexpectedDataParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((unexpectedDataParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((unexpectedDataParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((unexpectedDataParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded UnexpectedDataParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding UnexpectedDataParam...\n");
	    break;
	case FacilityNotSupParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &facilityNotSupParam1;
		    break;
		case 2:
		    data = &facilityNotSupParam2;
	(((*(((facilityNotSupParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((facilityNotSupParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((facilityNotSupParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((facilityNotSupParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded FacilityNotSupParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding FacilityNotSupParam...\n");
	    break;
	case OR_NotAllowedParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &oR_NotAllowedParam1;
		    break;
		case 2:
		    data = &oR_NotAllowedParam2;
	(((*(((oR_NotAllowedParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((oR_NotAllowedParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((oR_NotAllowedParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((oR_NotAllowedParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded OR_NotAllowedParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding OR_NotAllowedParam...\n");
	    break;
	case UnknownSubscriberParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &unknownSubscriberParam1;
		    break;
		case 2:
		    data = &unknownSubscriberParam2;
	(((*(((unknownSubscriberParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((unknownSubscriberParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((unknownSubscriberParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((unknownSubscriberParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded UnknownSubscriberParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding UnknownSubscriberParam...\n");
	    break;
	case NumberChangedParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &numberChangedParam1;
		    break;
		case 2:
		    data = &numberChangedParam2;
	(((*(((numberChangedParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((numberChangedParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((numberChangedParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((numberChangedParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded NumberChangedParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding NumberChangedParam...\n");
	    break;
	case UnidentifiedSubParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &unidentifiedSubParam1;
		    break;
		case 2:
		    data = &unidentifiedSubParam2;
	(((*(((unidentifiedSubParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((unidentifiedSubParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((unidentifiedSubParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((unidentifiedSubParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded UnidentifiedSubParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding UnidentifiedSubParam...\n");
	    break;
	case IllegalSubscriberParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &illegalSubscriberParam1;
		    break;
		case 2:
		    data = &illegalSubscriberParam2;
	(((*(((illegalSubscriberParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((illegalSubscriberParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((illegalSubscriberParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((illegalSubscriberParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded IllegalSubscriberParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding IllegalSubscriberParam...\n");
	    break;
	case IllegalEquipmentParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &illegalEquipmentParam1;
		    break;
		case 2:
		    data = &illegalEquipmentParam2;
	(((*(((illegalEquipmentParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((illegalEquipmentParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((illegalEquipmentParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((illegalEquipmentParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded IllegalEquipmentParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding IllegalEquipmentParam...\n");
	    break;
	case BearerServNotProvParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &bearerServNotProvParam1;
		    break;
		case 2:
		    data = &bearerServNotProvParam2;
	(((*(((bearerServNotProvParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((bearerServNotProvParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((bearerServNotProvParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((bearerServNotProvParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded BearerServNotProvParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding BearerServNotProvParam...\n");
	    break;
	case TeleservNotProvParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &teleservNotProvParam1;
		    break;
		case 2:
		    data = &teleservNotProvParam2;
	(((*(((teleservNotProvParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((teleservNotProvParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((teleservNotProvParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((teleservNotProvParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded TeleservNotProvParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding TeleservNotProvParam...\n");
	    break;
	case TracingBufferFullParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &tracingBufferFullParam1;
		    break;
		case 2:
		    data = &tracingBufferFullParam2;
	(((*(((tracingBufferFullParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((tracingBufferFullParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((tracingBufferFullParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((tracingBufferFullParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded TracingBufferFullParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding TracingBufferFullParam...\n");
	    break;
	case NoRoamingNbParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &noRoamingNbParam1;
		    break;
		case 2:
		    data = &noRoamingNbParam2;
	(((*(((noRoamingNbParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((noRoamingNbParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((noRoamingNbParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((noRoamingNbParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded NoRoamingNbParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding NoRoamingNbParam...\n");
	    break;
	case AbsentSubscriberParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &absentSubscriberParam1;
		    break;
		case 2:
		    data = &absentSubscriberParam2;
	(((*(((absentSubscriberParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((absentSubscriberParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((absentSubscriberParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((absentSubscriberParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded AbsentSubscriberParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding AbsentSubscriberParam...\n");
	    break;
	case BusySubscriberParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &busySubscriberParam1;
		    break;
		case 2:
		    data = &busySubscriberParam2;
	(((*(((busySubscriberParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((busySubscriberParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((busySubscriberParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((busySubscriberParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded BusySubscriberParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding BusySubscriberParam...\n");
	    break;
	case NoSubscriberReplyParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &noSubscriberReplyParam1;
		    break;
		case 2:
		    data = &noSubscriberReplyParam2;
	(((*(((noSubscriberReplyParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((noSubscriberReplyParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((noSubscriberReplyParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((noSubscriberReplyParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded NoSubscriberReplyParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding NoSubscriberReplyParam...\n");
	    break;
	case ForwardingViolationParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &forwardingViolationParam1;
		    break;
		case 2:
		    data = &forwardingViolationParam2;
	(((*(((forwardingViolationParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((forwardingViolationParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((forwardingViolationParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((forwardingViolationParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ForwardingViolationParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ForwardingViolationParam...\n");
	    break;
	case ForwardingFailedParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &forwardingFailedParam1;
		    break;
		case 2:
		    data = &forwardingFailedParam2;
	(((*(((forwardingFailedParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((forwardingFailedParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((forwardingFailedParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((forwardingFailedParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ForwardingFailedParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ForwardingFailedParam...\n");
	    break;
	case ATI_NotAllowedParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &aTI_NotAllowedParam1;
		    break;
		case 2:
		    data = &aTI_NotAllowedParam2;
	(((*(((aTI_NotAllowedParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((aTI_NotAllowedParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((aTI_NotAllowedParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((aTI_NotAllowedParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ATI_NotAllowedParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ATI_NotAllowedParam...\n");
	    break;
	case SubBusyForMT_SMS_Param_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &subBusyForMT_SMS_Param1;
		    break;
		case 2:
		    data = &subBusyForMT_SMS_Param2;
	(((*(((subBusyForMT_SMS_Param2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((subBusyForMT_SMS_Param2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((subBusyForMT_SMS_Param2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((subBusyForMT_SMS_Param2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SubBusyForMT_SMS_Param PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SubBusyForMT_SMS_Param...\n");
	    break;
	case MessageWaitListFullParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &messageWaitListFullParam1;
		    break;
		case 2:
		    data = &messageWaitListFullParam2;
	(((*(((messageWaitListFullParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((messageWaitListFullParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((messageWaitListFullParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((messageWaitListFullParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded MessageWaitListFullParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding MessageWaitListFullParam...\n");
	    break;
	case ResourceLimitationParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &resourceLimitationParam1;
		    break;
		case 2:
		    data = &resourceLimitationParam2;
	(((*(((resourceLimitationParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((resourceLimitationParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((resourceLimitationParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((resourceLimitationParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ResourceLimitationParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ResourceLimitationParam...\n");
	    break;
	case NoGroupCallNbParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &noGroupCallNbParam1;
		    break;
		case 2:
		    data = &noGroupCallNbParam2;
	(((*(((noGroupCallNbParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((noGroupCallNbParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((noGroupCallNbParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((noGroupCallNbParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded NoGroupCallNbParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding NoGroupCallNbParam...\n");
	    break;
	case IncompatibleTerminalParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &incompatibleTerminalParam1;
		    break;
		case 2:
		    data = &incompatibleTerminalParam2;
	(((*(((incompatibleTerminalParam2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((incompatibleTerminalParam2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((incompatibleTerminalParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((incompatibleTerminalParam2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded IncompatibleTerminalParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding IncompatibleTerminalParam...\n");
	    break;
	case ShortTermDenialParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &shortTermDenialParam;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ShortTermDenialParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ShortTermDenialParam...\n");
	    break;
	case LongTermDenialParam_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &longTermDenialParam;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded LongTermDenialParam PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding LongTermDenialParam...\n");
	    break;
	case SubscriberId_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &subscriberId1;
		    break;
		case 2:
		    data = &subscriberId2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SubscriberId PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SubscriberId...\n");
	    break;
	case IMEI_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &iMEI;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded IMEI PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding IMEI...\n");
	    break;
	case PrepareGroupCallArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &prepareGroupCallArg1;
		    break;
		case 2:
		    data = &prepareGroupCallArg2;
	(((*(((prepareGroupCallArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((prepareGroupCallArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((prepareGroupCallArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((prepareGroupCallArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded PrepareGroupCallArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PrepareGroupCallArg...\n");
	    break;
	case PrepareGroupCallRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &prepareGroupCallRes1;
		    break;
		case 2:
		    data = &prepareGroupCallRes2;
	(((*(((prepareGroupCallRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((prepareGroupCallRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((prepareGroupCallRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((prepareGroupCallRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded PrepareGroupCallRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PrepareGroupCallRes...\n");
	    break;
	case SendGroupCallEndSignalArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sendGroupCallEndSignalArg1;
		    break;
		case 2:
		    data = &sendGroupCallEndSignalArg2;
	(((*(((sendGroupCallEndSignalArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sendGroupCallEndSignalArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sendGroupCallEndSignalArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sendGroupCallEndSignalArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SendGroupCallEndSignalArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendGroupCallEndSignalArg...\n");
	    break;
	case SendGroupCallEndSignalRes_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &sendGroupCallEndSignalRes1;
		    break;
		case 2:
		    data = &sendGroupCallEndSignalRes2;
	(((*(((sendGroupCallEndSignalRes2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((sendGroupCallEndSignalRes2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((sendGroupCallEndSignalRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((sendGroupCallEndSignalRes2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded SendGroupCallEndSignalRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendGroupCallEndSignalRes...\n");
	    break;
	case ForwardGroupCallSignallingArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &forwardGroupCallSignallingArg1;
		    break;
		case 2:
		    data = &forwardGroupCallSignallingArg2;
	(((*(((forwardGroupCallSignallingArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((forwardGroupCallSignallingArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((forwardGroupCallSignallingArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((forwardGroupCallSignallingArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ForwardGroupCallSignallingArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ForwardGroupCallSignallingArg...\n");
	    break;
	case ProcessGroupCallSignallingArg_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &processGroupCallSignallingArg1;
		    break;
		case 2:
		    data = &processGroupCallSignallingArg2;
	(((*(((processGroupCallSignallingArg2).extensionContainer).privateExtensionList)).value).extensionType).value = otv;
	(((*(((processGroupCallSignallingArg2).extensionContainer).privateExtensionList)).value).extensionType).length = 2;
	(((*((*(((processGroupCallSignallingArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).value = otv;
	(((*((*(((processGroupCallSignallingArg2).extensionContainer).privateExtensionList)).next)).value).extensionType).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded ProcessGroupCallSignallingArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProcessGroupCallSignallingArg...\n");
	    break;
	case MAP_UserInfo_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &mAP_UserInfo1;
		    break;
		case 2:
		    data = &mAP_UserInfo2;
		    break;
		case 3:
		    data = &mAP_UserInfo3;
	(((((*mAP_UserInfo3).value).encoding).u).single_ASN1_type).encoded = &otv;
	(((((*mAP_UserInfo3).value).encoding).u).single_ASN1_type).length = 2;
	(((((*((*mAP_UserInfo3).next)).value).encoding).u).single_ASN1_type).encoded = &otv;
	(((((*((*mAP_UserInfo3).next)).value).encoding).u).single_ASN1_type).length = 2;
	(((((*((*((*mAP_UserInfo3).next)).next)).value).encoding).u).single_ASN1_type).encoded = &otv;
	(((((*((*((*mAP_UserInfo3).next)).next)).value).encoding).u).single_ASN1_type).length = 2;
	(((((*((*((*((*mAP_UserInfo3).next)).next)).next)).value).encoding).u).single_ASN1_type).encoded = &otv;
	(((((*((*((*((*mAP_UserInfo3).next)).next)).next)).value).encoding).u).single_ASN1_type).length = 2;
	(((((*((*((*((*((*mAP_UserInfo3).next)).next)).next)).next)).value).encoding).u).single_ASN1_type).encoded = &otv;
	(((((*((*((*((*((*mAP_UserInfo3).next)).next)).next)).next)).value).encoding).u).single_ASN1_type).length = 2;
	(((((*((*((*((*((*((*mAP_UserInfo3).next)).next)).next)).next)).next)).value).encoding).u).single_ASN1_type).encoded = &otv;
	(((((*((*((*((*((*((*mAP_UserInfo3).next)).next)).next)).next)).next)).value).encoding).u).single_ASN1_type).length = 2;
		    break;
		case 4:
		    data = &mAP_UserInfo4;
	(((((*mAP_UserInfo4).value).encoding).u).single_ASN1_type).encoded = &otv;
	(((((*mAP_UserInfo4).value).encoding).u).single_ASN1_type).length = 2;
	(((((*((*mAP_UserInfo4).next)).value).encoding).u).single_ASN1_type).encoded = &otv;
	(((((*((*mAP_UserInfo4).next)).value).encoding).u).single_ASN1_type).length = 2;
	(((((*((*((*mAP_UserInfo4).next)).next)).value).encoding).u).single_ASN1_type).encoded = &otv;
	(((((*((*((*mAP_UserInfo4).next)).next)).value).encoding).u).single_ASN1_type).length = 2;
	(((((*((*((*((*mAP_UserInfo4).next)).next)).next)).value).encoding).u).single_ASN1_type).encoded = &otv;
	(((((*((*((*((*mAP_UserInfo4).next)).next)).next)).value).encoding).u).single_ASN1_type).length = 2;
	(((((*((*((*((*((*mAP_UserInfo4).next)).next)).next)).next)).value).encoding).u).single_ASN1_type).encoded = &otv;
	(((((*((*((*((*((*mAP_UserInfo4).next)).next)).next)).next)).value).encoding).u).single_ASN1_type).length = 2;
	(((((*((*((*((*((*((*mAP_UserInfo4).next)).next)).next)).next)).next)).value).encoding).u).single_ASN1_type).encoded = &otv;
	(((((*((*((*((*((*((*mAP_UserInfo4).next)).next)).next)).next)).next)).value).encoding).u).single_ASN1_type).length = 2;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded MAP_UserInfo PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding MAP_UserInfo...\n");
	    break;
	case MAP_DialoguePDU_PDU:
	    switch (valueNumber) {
		case 1:
		    data = &mAP_DialoguePDU1;
		    break;
		case 2:
		    data = &mAP_DialoguePDU2;
		    break;
		case 3:
		    data = &mAP_DialoguePDU3;
		    break;
		case 4:
		    data = &mAP_DialoguePDU4;
		    break;
		case 5:
		    data = &mAP_DialoguePDU5;
		    break;
		case 6:
		    data = &mAP_DialoguePDU6;
		    break;
		case 7:
		    data = &mAP_DialoguePDU7;
		    break;
		case 8:
		    data = &mAP_DialoguePDU8;
		    break;
		case 9:
		    data = &mAP_DialoguePDU9;
		    break;
		case 10:
		    data = &mAP_DialoguePDU10;
		    break;
		case 11:
		    data = &mAP_DialoguePDU11;
		    break;
		case 12:
		    data = &mAP_DialoguePDU12;
	    }
	    ossPrint(world, "\n\tOSS-Printing unencoded MAP_DialoguePDU PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding MAP_DialoguePDU...\n");
#endif /* xxx */
    }
    ossSetEncodingFlags(world, DEFINITE+DEBUGPDU);
    rc = ossEncode(world, pduNum, data, &buffer);
    if (!rc) {
	*encodedPDULength = buffer.length;
	*encodedPDU = malloc(buffer.length);
	if (*encodedPDU) {
	    memcpy(*encodedPDU, buffer.value, buffer.length);
	    ossFreeBuf(world, buffer.value);
	    ossPrintHex(world, *encodedPDU, *encodedPDULength);
	}
	else
	    rc = -1;
    }
    ossterm(world);
    return rc;
}



int getDecodedPDU(int pduNum, char *encodedPDU,
				int encodedPDULength, void **decodedPDU)
{


    OssGlobal	w, *world = &w;
    OssBuf	buffer = {0};
    int		rc = 0;
#define BLOCK_SIZE 10240


    if (rc = ossinit(world, cap_v3_lrfvn)) {
	printf("Failed to initialize the encoder with an error code of %d\n.", rc);
	return  rc;
    }

    ossSetDecodingFlags(world, DEFINITE+DEBUGPDU);
    buffer.value = encodedPDU;
    buffer.length = encodedPDULength;
    ossPrint(world, "\n\tOSS-Printing undecoded PDU...\n");
    ossPrintHex(world, encodedPDU, encodedPDULength);
    ossPrint(world, "\n\tOSS-Decoding the PDU...\n");
    *decodedPDU = malloc(BLOCK_SIZE);
    if (!*decodedPDU)
	return -1;
    ossSetDecodingLength(world, BLOCK_SIZE);
    rc = ossDecode(world, &pduNum, &buffer, decodedPDU);
    if (rc)
	return rc;

    switch (pduNum) {
#ifdef xxx
	case UpdateLocationArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded UpdateLocationArg PDU...\n");
	    break;
	case UpdateLocationRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded UpdateLocationRes PDU...\n");
	    break;
	case CancelLocationArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded CancelLocationArg PDU...\n");
	    break;
	case CancelLocationRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded CancelLocationRes PDU...\n");
	    break;
	case PurgeMS_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PurgeMS_Arg PDU...\n");
	    break;
	case PurgeMS_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PurgeMS_Res PDU...\n");
	    break;
	case SendIdentificationRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendIdentificationRes PDU...\n");
	    break;
	case UpdateGprsLocationArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded UpdateGprsLocationArg PDU...\n");
	    break;
	case UpdateGprsLocationRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded UpdateGprsLocationRes PDU...\n");
	    break;
	case PrepareHO_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PrepareHO_Arg PDU...\n");
	    break;
	case PrepareHO_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PrepareHO_Res PDU...\n");
	    break;
	case PrepareSubsequentHO_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PrepareSubsequentHO_Arg PDU...\n");
	    break;
	case SendAuthenticationInfoArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendAuthenticationInfoArg PDU...\n");
	    break;
	case SendAuthenticationInfoRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendAuthenticationInfoRes PDU...\n");
	    break;
	case EquipmentStatus_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded EquipmentStatus PDU...\n");
	    break;
	case InsertSubscriberDataArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded InsertSubscriberDataArg PDU...\n");
	    break;
	case InsertSubscriberDataRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded InsertSubscriberDataRes PDU...\n");
	    break;
	case DeleteSubscriberDataArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded DeleteSubscriberDataArg PDU...\n");
	    break;
	case DeleteSubscriberDataRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded DeleteSubscriberDataRes PDU...\n");
	    break;
	case SendRoutingInfoForGprsArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendRoutingInfoForGprsArg PDU...\n");
	    break;
	case SendRoutingInfoForGprsRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendRoutingInfoForGprsRes PDU...\n");
	    break;
	case FailureReportArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded FailureReportArg PDU...\n");
	    break;
	case FailureReportRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded FailureReportRes PDU...\n");
	    break;
	case NoteMsPresentForGprsArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded NoteMsPresentForGprsArg PDU...\n");
	    break;
	case NoteMsPresentForGprsRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded NoteMsPresentForGprsRes PDU...\n");
	    break;
	case ResetArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ResetArg PDU...\n");
	    break;
	case RestoreDataArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RestoreDataArg PDU...\n");
	    break;
	case RestoreDataRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RestoreDataRes PDU...\n");
	    break;
	case ProvideSubscriberInfoArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProvideSubscriberInfoArg PDU...\n");
	    break;
	case ProvideSubscriberInfoRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProvideSubscriberInfoRes PDU...\n");
	    break;
	case AnyTimeInterrogationArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded AnyTimeInterrogationArg PDU...\n");
	    break;
	case AnyTimeInterrogationRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded AnyTimeInterrogationRes PDU...\n");
	    break;
	case ActivateTraceModeArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ActivateTraceModeArg PDU...\n");
	    break;
	case ActivateTraceModeRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ActivateTraceModeRes PDU...\n");
	    break;
	case DeactivateTraceModeArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded DeactivateTraceModeArg PDU...\n");
	    break;
	case DeactivateTraceModeRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded DeactivateTraceModeRes PDU...\n");
	    break;
	case SendRoutingInfoArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendRoutingInfoArg PDU...\n");
	    break;
	case SendRoutingInfoRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendRoutingInfoRes PDU...\n");
	    break;
	case RoutingInfo_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RoutingInfo PDU...\n");
	    break;
	case ProvideRoamingNumberArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProvideRoamingNumberArg PDU...\n");
	    break;
	case ProvideRoamingNumberRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProvideRoamingNumberRes PDU...\n");
	    break;
	case ResumeCallHandlingArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ResumeCallHandlingArg PDU...\n");
	    break;
	case ResumeCallHandlingRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ResumeCallHandlingRes PDU...\n");
	    break;
	case ProvideSIWFSNumberArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProvideSIWFSNumberArg PDU...\n");
	    break;
	case ProvideSIWFSNumberRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProvideSIWFSNumberRes PDU...\n");
	    break;
	case SIWFSSignallingModifyArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SIWFSSignallingModifyArg PDU...\n");
	    break;
	case SIWFSSignallingModifyRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SIWFSSignallingModifyRes PDU...\n");
	    break;
	case SetReportingStateArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SetReportingStateArg PDU...\n");
	    break;
	case SetReportingStateRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SetReportingStateRes PDU...\n");
	    break;
	case StatusReportArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded StatusReportArg PDU...\n");
	    break;
	case StatusReportRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded StatusReportRes PDU...\n");
	    break;
	case RemoteUserFreeArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RemoteUserFreeArg PDU...\n");
	    break;
	case RemoteUserFreeRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RemoteUserFreeRes PDU...\n");
	    break;
	case RegisterSS_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RegisterSS_Arg PDU...\n");
	    break;
	case SS_ForBS_Code_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SS_ForBS_Code PDU...\n");
	    break;
	case InterrogateSS_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded InterrogateSS_Res PDU...\n");
	    break;
	case USSD_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded USSD_Arg PDU...\n");
	    break;
	case USSD_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded USSD_Res PDU...\n");
	    break;
	case Password_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded Password PDU...\n");
	    break;
	case GuidanceInfo_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded GuidanceInfo PDU...\n");
	    break;
	case SS_InfoList_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SS_InfoList PDU...\n");
	    break;
	case SS_InvocationNotificationArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SS_InvocationNotificationArg PDU...\n");
	    break;
	case SS_InvocationNotificationRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SS_InvocationNotificationRes PDU...\n");
	    break;
	case RegisterCC_EntryArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RegisterCC_EntryArg PDU...\n");
	    break;
	case RegisterCC_EntryRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RegisterCC_EntryRes PDU...\n");
	    break;
	case EraseCC_EntryArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded EraseCC_EntryArg PDU...\n");
	    break;
	case EraseCC_EntryRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded EraseCC_EntryRes PDU...\n");
	    break;
	case RoutingInfoForSM_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RoutingInfoForSM_Arg PDU...\n");
	    break;
	case RoutingInfoForSM_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RoutingInfoForSM_Res PDU...\n");
	    break;
	case MO_ForwardSM_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded MO_ForwardSM_Arg PDU...\n");
	    break;
	case MO_ForwardSM_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded MO_ForwardSM_Res PDU...\n");
	    break;
	case MT_ForwardSM_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded MT_ForwardSM_Arg PDU...\n");
	    break;
	case MT_ForwardSM_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded MT_ForwardSM_Res PDU...\n");
	    break;
	case ReportSM_DeliveryStatusArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ReportSM_DeliveryStatusArg PDU...\n");
	    break;
	case ReportSM_DeliveryStatusRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ReportSM_DeliveryStatusRes PDU...\n");
	    break;
	case AlertServiceCentreArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded AlertServiceCentreArg PDU...\n");
	    break;
	case InformServiceCentreArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded InformServiceCentreArg PDU...\n");
	    break;
	case ReadyForSM_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ReadyForSM_Arg PDU...\n");
	    break;
	case ReadyForSM_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ReadyForSM_Res PDU...\n");
	    break;
	case RoamingNotAllowedParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RoamingNotAllowedParam PDU...\n");
	    break;
	case CallBarredParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded CallBarredParam PDU...\n");
	    break;
	case CUG_RejectParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded CUG_RejectParam PDU...\n");
	    break;
	case SS_IncompatibilityCause_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SS_IncompatibilityCause PDU...\n");
	    break;
	case PW_RegistrationFailureCause_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PW_RegistrationFailureCause PDU...\n");
	    break;
	case SM_DeliveryFailureCause_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SM_DeliveryFailureCause PDU...\n");
	    break;
	case AbsentSubscriberSM_Param_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded AbsentSubscriberSM_Param PDU...\n");
	    break;
	case SystemFailureParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SystemFailureParam PDU...\n");
	    break;
	case DataMissingParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded DataMissingParam PDU...\n");
	    break;
	case UnexpectedDataParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded UnexpectedDataParam PDU...\n");
	    break;
	case FacilityNotSupParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded FacilityNotSupParam PDU...\n");
	    break;
	case OR_NotAllowedParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded OR_NotAllowedParam PDU...\n");
	    break;
	case UnknownSubscriberParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded UnknownSubscriberParam PDU...\n");
	    break;
	case NumberChangedParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded NumberChangedParam PDU...\n");
	    break;
	case UnidentifiedSubParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded UnidentifiedSubParam PDU...\n");
	    break;
	case IllegalSubscriberParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded IllegalSubscriberParam PDU...\n");
	    break;
	case IllegalEquipmentParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded IllegalEquipmentParam PDU...\n");
	    break;
	case BearerServNotProvParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded BearerServNotProvParam PDU...\n");
	    break;
	case TeleservNotProvParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded TeleservNotProvParam PDU...\n");
	    break;
	case TracingBufferFullParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded TracingBufferFullParam PDU...\n");
	    break;
	case NoRoamingNbParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded NoRoamingNbParam PDU...\n");
	    break;
	case AbsentSubscriberParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded AbsentSubscriberParam PDU...\n");
	    break;
	case BusySubscriberParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded BusySubscriberParam PDU...\n");
	    break;
	case NoSubscriberReplyParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded NoSubscriberReplyParam PDU...\n");
	    break;
	case ForwardingViolationParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ForwardingViolationParam PDU...\n");
	    break;
	case ForwardingFailedParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ForwardingFailedParam PDU...\n");
	    break;
	case ATI_NotAllowedParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ATI_NotAllowedParam PDU...\n");
	    break;
	case SubBusyForMT_SMS_Param_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SubBusyForMT_SMS_Param PDU...\n");
	    break;
	case MessageWaitListFullParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded MessageWaitListFullParam PDU...\n");
	    break;
	case ResourceLimitationParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ResourceLimitationParam PDU...\n");
	    break;
	case NoGroupCallNbParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded NoGroupCallNbParam PDU...\n");
	    break;
	case IncompatibleTerminalParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded IncompatibleTerminalParam PDU...\n");
	    break;
	case ShortTermDenialParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ShortTermDenialParam PDU...\n");
	    break;
	case LongTermDenialParam_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded LongTermDenialParam PDU...\n");
	    break;
	case SubscriberId_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SubscriberId PDU...\n");
	    break;
	case IMEI_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded IMEI PDU...\n");
	    break;
	case PrepareGroupCallArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PrepareGroupCallArg PDU...\n");
	    break;
	case PrepareGroupCallRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PrepareGroupCallRes PDU...\n");
	    break;
	case SendGroupCallEndSignalArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendGroupCallEndSignalArg PDU...\n");
	    break;
	case SendGroupCallEndSignalRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendGroupCallEndSignalRes PDU...\n");
	    break;
	case ForwardGroupCallSignallingArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ForwardGroupCallSignallingArg PDU...\n");
	    break;
	case ProcessGroupCallSignallingArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProcessGroupCallSignallingArg PDU...\n");
	    break;
	case MAP_UserInfo_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded MAP_UserInfo PDU...\n");
	    break;
	case MAP_DialoguePDU_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded MAP_DialoguePDU PDU...\n");
#endif /* xxx */
    }
    ossPrintPDU(world, pduNum, *decodedPDU);
    ossterm(world);
    return rc;
}


