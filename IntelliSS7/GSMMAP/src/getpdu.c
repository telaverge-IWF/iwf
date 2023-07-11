/*
 * Copyright (C) 2000-2000 IntelliNet Technologies, Inc.  All rights reserved.
 *
 *
 * $Id: getpdu.c,v 9.1 2005/03/23 12:51:25 cvsadmin Exp $
 *
 * $Log: getpdu.c,v $
 * Revision 9.1  2005/03/23 12:51:25  cvsadmin
 * Begin PR6.5
 *
 * Revision 8.2  2005/03/21 13:49:26  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 7.1  2002/08/26 22:08:45  mmiers
 * Begin PR6.2
 *
 * Revision 6.1  2002/02/28 16:13:19  mmiers
 * Begin PR7.
 *
 * Revision 5.1  2001/08/16 20:45:18  mmiers
 * Start PR6.
 *
 * Revision 4.1  2001/05/01 00:53:03  mmiers
 * Begin PR5
 *
 * Revision 3.1  2000/08/15 23:56:45  mmiers
 *
 * Begin round 4.
 *
 * Revision 1.9  2000/04/27 16:42:31  npopov
 * Added all the values for regression testing.
 *
 * Revision 1.8  2000/04/26 18:13:57  npopov
 * Added more PDU values for regression testing.
 *
 * Revision 1.7  2000/04/25 17:06:16  npopov
 * Added more PDUs for regression testing.
 *
 * Revision 1.5  2000/04/20 16:09:08  npopov
 * Added more PDUs for regression testing.
 *
 * Revision 1.4  2000/04/19 15:31:10  npopov
 * Added new GSMMAP PDUs for regression testing.
 *
 * Revision 1.3  2000/04/18 15:31:59  npopov
 * Changes related to cross-encoding/decoding testing.
 *
 * Revision 1.2  2000/04/17 14:14:47  npopov
 * Changes related to cross-encoding/decoding regression testing.
 *
 * Revision 1.1  2000/04/12 15:56:29  npopov
 * Code that calls OSS APIs for regression testing.
 *
 */





#include "gsmmapvn.h"			/* OSS-generated header */
int getEncodedPDU(int pduNum, char **encodedPDU, int *encodedPDULength);
int getDecodedPDU(int pduNum, char *encodedPDU,
				int encodedPDULength, void **decodedPDU);


int getEncodedPDU(int pduNum, char **encodedPDU, int *encodedPDULength)
{


    OssGlobal	w, *world = &w;
    OssBuf	buffer = {0};
    int		rc = 0;
    void	*data = NULL;


    if (rc = ossinit(world, gsmmapvn)) {
	printf("Failed to initialize the encoder with an error code of %d\n.", rc);
	return  rc;
    }

    switch (pduNum) {
	case UpdateLocationArg_PDU:
	    data = &updateLocationArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded UpdateLocationArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding UpdateLocationArg...\n");
	    break;
	case UpdateLocationRes_PDU:
	    data = &updateLocationRes;
	    ossPrint(world, "\n\tOSS-Printing unencoded UpdateLocationRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding UpdateLocationRes...\n");
	    break;
	case CancelLocationArg_PDU:
	    data = &cancelLocationArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded CancelLocationArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding CancelLocationArg...\n");
	    break;
	case PurgeMS_Arg_PDU:
	    data = &purgeMS_Arg;
	    ossPrint(world, "\n\tOSS-Printing unencoded PurgeMS_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PurgeMS_Arg...\n");
	    break;
	case SendIdentificationArgTmsi_PDU:
	    data = &sendIdentificationArgTmsi;
	    ossPrint(world, "\n\tOSS-Printing unencoded SendIdentificationArgTmsi PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendIdentificationArgTmsi...\n");
	    break;
	case SendIdentificationRes_PDU:
	    data = &sendIdentificationRes;
	    ossPrint(world, "\n\tOSS-Printing unencoded SendIdentificationRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendIdentificationRes...\n");
	    break;
	case PerformHO_Arg_PDU:
	    data = &performHO_Arg;
	    ossPrint(world, "\n\tOSS-Printing unencoded PerformHO_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PerformHO_Arg...\n");
	    break;
	case PerformHO_Res_PDU:
	    data = &performHO_Res;
	    ossPrint(world, "\n\tOSS-Printing unencoded PerformHO_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PerformHO_Res...\n");
	    break;
	case PrepareHO_Arg_PDU:
	    data = &prepareHO_Arg;
	    ossPrint(world, "\n\tOSS-Printing unencoded PrepareHO_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PrepareHO_Arg...\n");
	    break;
	case PrepareHO_Res_PDU:
	    data = &prepareHO_Res;
	    ossPrint(world, "\n\tOSS-Printing unencoded PrepareHO_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PrepareHO_Res...\n");
	    break;
	case SendEndSignalArgBss_APDU_PDU:
	    data = &sendEndSignalArgBss_APDU;
	    ossPrint(world, "\n\tOSS-Printing unencoded SendEndSignalArgBss_APDU PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendEndSignalArgBss_APDU...\n");
	    break;
	case ProcessAccessSignallingArgBss_APDU_PDU:
	    data = &processAccessSignallingArgBss_APDU;
	    ossPrint(world, "\n\tOSS-Printing unencoded ProcessAccessSignallingArgBss_APDU PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProcessAccessSignallingArgBss_APDU...\n");
	    break;
	case ForwardAccessSignallingArgBss_APDU_PDU:
	    data = &forwardAccessSignallingArgBss_APDU;
	    ossPrint(world, "\n\tOSS-Printing unencoded ForwardAccessSignallingArgBss_APDU PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ForwardAccessSignallingArgBss_APDU...\n");
	    break;
	case PerformSubsequentHO_Arg_PDU:
	    data = &performSubsequentHO_Arg;
	    ossPrint(world, "\n\tOSS-Printing unencoded PerformSubsequentHO_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PerformSubsequentHO_Arg...\n");
	    break;
	case PerformSubsequentHOResAccessSignalInfo_PDU:
	    data = &performSubsequentHOResAccessSignalInfo;
	    ossPrint(world, "\n\tOSS-Printing unencoded PerformSubsequentHOResAccessSignalInfo PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PerformSubsequentHOResAccessSignalInfo...\n");
	    break;
	case PrepareSubsequentHO_Arg_PDU:
	    data = &prepareSubsequentHO_Arg;
	    ossPrint(world, "\n\tOSS-Printing unencoded PrepareSubsequentHO_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PrepareSubsequentHO_Arg...\n");
	    break;
	case PrepareSubsequentHOResBss_APDU_PDU:
	    data = &prepareSubsequentHOResBss_APDU;
	    ossPrint(world, "\n\tOSS-Printing unencoded PrepareSubsequentHOResBss_APDU PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding PrepareSubsequentHOResBss_APDU...\n");
	    break;
	case SendAuthenticationArg_PDU:
	    data = &sendAuthenticationArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded SendAuthenticationArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendAuthenticationArg...\n");
	    break;
	case SendAuthenticationRes_PDU:
	    data = &sendAuthenticationRes;
	    ossPrint(world, "\n\tOSS-Printing unencoded SendAuthenticationRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendAuthenticationRes...\n");
	    break;
	case CheckIMEIArgImei_PDU:
	    data = &checkIMEIArgImei;
	    ossPrint(world, "\n\tOSS-Printing unencoded CheckMEIArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding CheckMEIArg...\n");
	    break;
	case CheckIMEIResEquipmentStatus_PDU:
	    data = &checkIMEIResEquipmentStatus;
	    ossPrint(world, "\n\tOSS-Printing unencoded CheckMEIRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding CheckMEIRes...\n");
	    break;
	case SendParametersArg_PDU:
	    data = &sendParametersArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded SendParametersArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendParametersArg...\n");
	    break;
	case SentParameterList_PDU:
	    data = &sentParameterList;
	    ossPrint(world, "\n\tOSS-Printing unencoded SendParametersRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendParametersRes...\n");
	    break;
	case InsertSubscriberDataArg_PDU:
	    data = &insertSubscriberDataArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded InsertSubscriberDataArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding InsertSubscriberDataArg...\n");
	    break;
	case InsertSubscriberDataRes_PDU:
	    data = &insertSubscriberDataRes;
	    ossPrint(world, "\n\tOSS-Printing unencoded InsertSubscriberDataRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding InsertSubscriberDataRes...\n");
	    break;
	case DeleteSubscriberDataArg_PDU:
	    data = &deleteSubscriberDataArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded DeleteSubscriberDataArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding DeleteSubscriberDataArg...\n");
	    break;
	case DeleteSubscriberDataRes_PDU:
	    data = &deleteSubscriberDataRes;
	    ossPrint(world, "\n\tOSS-Printing unencoded DeleteSubscriberDataRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding DeleteSubscriberDataRes...\n");
	    break;
	case ResetArg_PDU:
	    data = &resetArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded ResetArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ResetArg...\n");
	    break;
	case RestoreDataArg_PDU:
	    data = &restoreDataArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded RestoreDataArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RestoreDataArg...\n");
	    break;
	case RestoreDataRes_PDU:
	    data = &restoreDataRes;
	    ossPrint(world, "\n\tOSS-Printing unencoded RestoreDataRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RestoreDataRes...\n");
	    break;
	case ActivateTraceModeArg_PDU:
	    data = &activateTraceModeArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded ActivateTraceModeArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ActivateTraceModeArg...\n");
	    break;
	case DeactivateTraceModeArg_PDU:
	    data = &deactivateTraceModeArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded DeactivateTraceModeArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding DeactivateTraceModeArg...\n");
	    break;
	case TraceSubscriberActivityArg_PDU:
	    data = &traceSubscriberActivityArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded TraceSubscriberActivityArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding TraceSubscriberActivityArg...\n");
	    break;
	case NoteInternalHO_Arg_PDU:
	    data = &noteInternalHO_Arg;
	    ossPrint(world, "\n\tOSS-Printing unencoded NoteInternalHO_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding NoteInternalHO_Arg...\n");
	    break;
	case Msisdn_PDU:
	    data = &msisdn;
	    ossPrint(world, "\n\tOSS-Printing unencoded MsisdnArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding MsisdnArg...\n");
	    break;
	case Imsi_PDU:
	    data = &imsi;
	    ossPrint(world, "\n\tOSS-Printing unencoded ImsiRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ImsiRes...\n");
	    break;
	case SendRoutingInfoArg_PDU:
	    data = &sendRoutingInfoArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded SendRoutingInfoArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendRoutingInfoArg...\n");
	    break;
	case SendRoutingInfoRes_PDU:
	    data = &sendRoutingInfoRes;
	    ossPrint(world, "\n\tOSS-Printing unencoded SendRoutingInfoRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding SendRoutingInfoRes...\n");
	    break;
	case ProvideRoamingNumberArg_PDU:
	    data = &provideRoamingNumberArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded ProvideRoamingNumberArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProvideRoamingNumberArg...\n");
	    break;
	case RoamingNumber_PDU:
	    data = &roamingNumber;
	    ossPrint(world, "\n\tOSS-Printing unencoded ProvideRoamingNumberRes PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProvideRoamingNumberRes...\n");
	    break;
	case RegisterSS_Arg_PDU:
	    data = &registerSS_Arg;
	    ossPrint(world, "\n\tOSS-Printing unencoded RegisterSS_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RegisterSS_Arg...\n");
	    break;
	case RegisterSSss_Info_PDU:
	    data = &registerSSss_Info;
	    ossPrint(world, "\n\tOSS-Printing unencoded RegisterSS_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RegisterSS_Res...\n");
	    break;
	case EraseSSss_ForBS_PDU:
	    data = &eraseSSss_ForBS;
	    ossPrint(world, "\n\tOSS-Printing unencoded EraseSSss_ForBS PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding EraseSSss_ForBS...\n");
	    break;
	case EraseSSss_Info_PDU:
	    data = &eraseSSss_Info;
	    ossPrint(world, "\n\tOSS-Printing unencoded EraseSSss_Info PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding EraseSSss_Info...\n");
	    break;
	case ActivateSSss_ForBS_PDU:
	    data = &activateSSss_ForBS;
	    ossPrint(world, "\n\tOSS-Printing unencoded ActivateSSss_ForBS PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ActivateSSss_ForBS...\n");
	    break;
	case ActivateSSss_Info_PDU:
	    data = &activateSSss_Info;
	    ossPrint(world, "\n\tOSS-Printing unencoded ActivateSSss_Info PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ActivateSSss_Info...\n");
	    break;
	case DeactivateSSss_ForBS_PDU:
	    data = &deactivateSSss_ForBS;
	    ossPrint(world, "\n\tOSS-Printing unencoded DeactivateSSss_ForBS PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding DeactivateSSss_ForBS...\n");
	    break;
	case DeactivateSSss_Info_PDU:
	    data = &deactivateSSss_Info;
	    ossPrint(world, "\n\tOSS-Printing unencoded DeactivateSSss_Info PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding DeactivateSSss_Info...\n");
	    break;
	case InterrogateSSss_ForBS_PDU:
	    data = &interrogateSSss_ForBS;
	    ossPrint(world, "\n\tOSS-Printing unencoded InterrogateSSss_ForBS PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding InterrogateSSss_ForBS...\n");
	    break;
	case InterrogateSS_Res_PDU:
	    data = &interrogateSS_Res;
	    ossPrint(world, "\n\tOSS-Printing unencoded InterrogateSS_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding InterrogateSS_Res...\n");
	    break;
	case ProcessUnstructuredSSArgSs_UserData_PDU:
	    data = &processUnstructuredSSArgSs_UserData;
	    ossPrint(world, "\n\tOSS-Printing unencoded ProcessUnstructuredSSArgSs_UserData PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProcessUnstructuredSSArgSs_UserData...\n");
	    break;
	case ProcessUnstructuredSSResSs_UserData_PDU:
	    data = &processUnstructuredSSResSs_UserData;
	    ossPrint(world, "\n\tOSS-Printing unencoded ProcessUnstructuredSSResSs_UserData PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProcessUnstructuredSSResSs_UserData...\n");
	    break;
	case ProcessUnstructuredSSReqUssd_Arg_PDU:
	    data = &processUnstructuredSSReqUssd_Arg;
	    ossPrint(world, "\n\tOSS-Printing unencoded ProcessUnstructuredSSReqUssd_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProcessUnstructuredSSReqUssd_Arg...\n");
	    break;
	case ProcessUnstructuredSSReqUssd_Res_PDU:
	    data = &processUnstructuredSSReqUssd_Res;
	    ossPrint(world, "\n\tOSS-Printing unencoded ProcessUnstructuredSSReqUssd_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ProcessUnstructuredSSReqUssd_Res...\n");
	    break;
	case UnstructuredSSReqUssd_Arg_PDU:
	    data = &unstructuredSSReqUssd_Arg;
	    ossPrint(world, "\n\tOSS-Printing unencoded UnstructuredSSReqUssd_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding UnstructuredSSReqUssd_Arg...\n");
	    break;
	case UnstructuredSSReqUssd_Res_PDU:
	    data = &unstructuredSSReqUssd_Res;
	    ossPrint(world, "\n\tOSS-Printing unencoded UnstructuredSSReqUssd_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding UnstructuredSSReqUssd_Res...\n");
	    break;
	case UnstructuredSSNotifyUssd_Arg_PDU:
	    data = &unstructuredSSNotifyUssd_Arg;
	    ossPrint(world, "\n\tOSS-Printing unencoded UnstructuredSSNotifyUssd_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding UnstructuredSSNotifyUssd_Arg...\n");
	    break;
	case RegisterPasswordArgSs_Code_PDU:
	    data = &registerPasswordArgSs_Code;
	    ossPrint(world, "\n\tOSS-Printing unencoded RegisterPasswordArgSs_Code PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RegisterPasswordArgSs_Code...\n");
	    break;
	case RegisterPasswordResNewPassword_PDU:
	    data = &registerPasswordResNewPassword;
	    ossPrint(world, "\n\tOSS-Printing unencoded RegisterPasswordResNewPassword PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RegisterPasswordResNewPassword...\n");
	    break;
	case GetPasswordArgGuidanceInfo_PDU:
	    data = &getPasswordArgGuidanceInfo;
	    ossPrint(world, "\n\tOSS-Printing unencoded GetPasswordArgGuidanceInfo PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding GetPasswordArgGuidanceInfo...\n");
	    break;
	case GetPasswordResCurrentPassword_PDU:
	    data = &getPasswordResCurrentPassword;
	    ossPrint(world, "\n\tOSS-Printing unencoded GetPasswordResCurrentPassword PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding GetPasswordResCurrentPassword...\n");
	    break;
	case BeginSubscriberActivityArg_PDU:
	    data = &beginSubscriberActivityArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded BeginSubscriberActivityArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding BeginSubscriberActivityArg...\n");
	    break;
	case RoutingInfoForSM_Arg_PDU:
	    data = &routingInfoForSM_Arg;
	    ossPrint(world, "\n\tOSS-Printing unencoded RoutingInfoForSM_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RoutingInfoForSM_Arg...\n");
	    break;
	case RoutingInfoForSM_Res_PDU:
	    data = &routingInfoForSM_Res;
	    ossPrint(world, "\n\tOSS-Printing unencoded RoutingInfoForSM_Res PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding RoutingInfoForSM_Res...\n");
	    break;
	case ForwardSM_Arg_PDU:
	    data = &forwardSM_Arg;
	    ossPrint(world, "\n\tOSS-Printing unencoded ForwardSM_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ForwardSM_Arg...\n");
	    break;
	case ReportSM_DeliveryStatusArg_PDU:
	    data = &reportSM_DeliveryStatusArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded ReportSM_DeliveryStatusArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ReportSM_DeliveryStatusArg...\n");
	    break;
	case ReportSM_DeliveryStatusResStoredMSISDN_PDU:
	    data = &reportSM_DeliveryStatusResStoredMSISDN;
	    ossPrint(world, "\n\tOSS-Printing unencoded ReportSM_DeliveryStatusResStoredMSISDN PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ReportSM_DeliveryStatusResStoredMSISDN...\n");
	    break;
	case NoteSubscriberPresentImsi_PDU:
	    data = &noteSubscriberPresentImsi;
	    ossPrint(world, "\n\tOSS-Printing unencoded NoteSubscriberPresentImsi PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding NoteSubscriberPresentImsi...\n");
	    break;
	case AlertServiceCentreArg_PDU:
	    data = &alertServiceCentreArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded AlertServiceCentreArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding AlertServiceCentreArg...\n");
	    break;
	case InformServiceCentreArg_PDU:
	    data = &informServiceCentreArg;
	    ossPrint(world, "\n\tOSS-Printing unencoded InformServiceCentreArg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding InformServiceCentreArg...\n");
	    break;
	case ReadyForSM_Arg_PDU:
	    data = &readyForSM_Arg;
	    ossPrint(world, "\n\tOSS-Printing unencoded ReadyForSM_Arg PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding ReadyForSM_Arg...\n");
	    break;
	case MAP_UserInfo_PDU:
	    data = &mAP_UserInfo;
	    ossPrint(world, "\n\tOSS-Printing unencoded MAP_UserInfo PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding MAP_UserInfo...\n");
	    break;
	case MAP_DialoguePDU_PDU:
	    data = &mAP_DialoguePDU;
	    ossPrint(world, "\n\tOSS-Printing unencoded MAP_DialoguePDU PDU...\n");
	    ossPrintPDU(world, pduNum, data);
	    ossPrint(world, "\n\tOSS-Encoding MAP_DialoguePDU...\n");
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


    if (rc = ossinit(world, gsmmapvn)) {
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
	case UpdateLocationArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded UpdateLocationArg PDU...\n");
	    break;
	case UpdateLocationRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded UpdateLocationRes PDU...\n");
	    break;
	case CancelLocationArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded CancelLocationArg PDU...\n");
	    break;
	case PurgeMS_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PurgeMS_Arg PDU...\n");
	    break;
	case SendIdentificationArgTmsi_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendIdentificationArgTmsi PDU...\n");
	    break;
	case SendIdentificationRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendIdentificationRes PDU...\n");
	    break;
	case PerformHO_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PerformHO_Arg PDU...\n");
	    break;
	case PerformHO_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PerformHO_Res PDU...\n");
	    break;
	case PrepareHO_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PrepareHO_Arg PDU...\n");
	    break;
	case PrepareHO_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PrepareHO_Res PDU...\n");
	    break;
	case SendEndSignalArgBss_APDU_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendEndSignalArgBss_APDU PDU...\n");
	    break;
	case ProcessAccessSignallingArgBss_APDU_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProcessAccessSignallingArgBss_APDU PDU...\n");
	    break;
	case ForwardAccessSignallingArgBss_APDU_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ForwardAccessSignallingArgBss_APDU PDU...\n");
	    break;
	case PerformSubsequentHO_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PerformSubsequentHO_Arg PDU...\n");
	    break;
	case PerformSubsequentHOResAccessSignalInfo_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PerformSubsequentHOResAccessSignalInfo PDU...\n");
	    break;
	case PrepareSubsequentHO_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PrepareSubsequentHO_Arg PDU...\n");
	    break;
	case PrepareSubsequentHOResBss_APDU_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded PrepareSubsequentHOResBss_APDU PDU...\n");
	    break;
	case SendAuthenticationArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendAuthenticationArg PDU...\n");
	    break;
	case SendAuthenticationRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendAuthenticationRes PDU...\n");
	    break;
	case CheckIMEIArgImei_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded CheckIMEIArg PDU...\n");
	    break;
	case CheckIMEIResEquipmentStatus_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded CheckIMEIRes PDU...\n");
	    break;
	case SendParametersArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendParametersArg PDU...\n");
	    break;
	case SentParameterList_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendParametersRes PDU...\n");
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
	case ResetArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ResetArg PDU...\n");
	    break;
	case RestoreDataArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RestoreDataArg PDU...\n");
	    break;
	case RestoreDataRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RestoreDataRes PDU...\n");
	    break;
	case ActivateTraceModeArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ActivateTraceModeArg PDU...\n");
	    break;
	case DeactivateTraceModeArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded DeactivateTraceModeArg PDU...\n");
	    break;
	case TraceSubscriberActivityArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded TraceSubscriberActivityArg PDU...\n");
	    break;
	case NoteInternalHO_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded NoteInternalHO_Arg PDU...\n");
	    break;
	case Msisdn_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded MsisdnArg PDU...\n");
	    break;
	case Imsi_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ImsiRes PDU...\n");
	    break;
	case SendRoutingInfoArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendRoutingInfoArg PDU...\n");
	    break;
	case SendRoutingInfoRes_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded SendRoutingInfoRes PDU...\n");
	    break;
	case ProvideRoamingNumberArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProvideRoamingNumberArg PDU...\n");
	    break;
	case RoamingNumber_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProvideRoamingNumberRes PDU...\n");
	    break;
	case RegisterSS_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RegisterSS_Arg PDU...\n");
	    break;
	case RegisterSSss_Info_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RegisterSS_Res PDU...\n");
	    break;
	case EraseSSss_ForBS_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded EraseSSss_ForBS PDU...\n");
	    break;
	case EraseSSss_Info_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded EraseSSss_Info PDU...\n");
	    break;
	case ActivateSSss_ForBS_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ActivateSSss_ForBS PDU...\n");
	    break;
	case ActivateSSss_Info_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ActivateSSss_Info PDU...\n");
	    break;
	case DeactivateSSss_ForBS_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded DeactivateSSss_ForBS PDU...\n");
	    break;
	case DeactivateSSss_Info_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded DeactivateSSss_Info PDU...\n");
	    break;
	case InterrogateSSss_ForBS_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded InterrogateSSss_ForBS PDU...\n");
	    break;
	case InterrogateSS_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded InterrogateSS_Res PDU...\n");
	    break;
	case ProcessUnstructuredSSArgSs_UserData_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProcessUnstructuredSSArgSs_UserData PDU...\n");
	    break;
	case ProcessUnstructuredSSResSs_UserData_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProcessUnstructuredSSResSs_UserData PDU...\n");
	    break;
	case ProcessUnstructuredSSReqUssd_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProcessUnstructuredSSReqUssd_Arg PDU...\n");
	    break;
	case ProcessUnstructuredSSReqUssd_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ProcessUnstructuredSSReqUssd_Res PDU...\n");
	    break;
	case UnstructuredSSReqUssd_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded UnstructuredSSReqUssd_Arg PDU...\n");
	    break;
	case UnstructuredSSReqUssd_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded UnstructuredSSReqUssd_Res PDU...\n");
	    break;
	case UnstructuredSSNotifyUssd_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded UnstructuredSSNotifyUssd_Arg PDU...\n");
	    break;
	case RegisterPasswordArgSs_Code_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RegisterPasswordArgSs_Code PDU...\n");
	    break;
	case RegisterPasswordResNewPassword_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RegisterPasswordResNewPassword PDU...\n");
	    break;
	case GetPasswordArgGuidanceInfo_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded GetPasswordArgGuidanceInfo PDU...\n");
	    break;
	case GetPasswordResCurrentPassword_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded GetPasswordResCurrentPassword PDU...\n");
	    break;
	case BeginSubscriberActivityArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded BeginSubscriberActivityArg PDU...\n");
	    break;
	case RoutingInfoForSM_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RoutingInfoForSM_Arg PDU...\n");
	    break;
	case RoutingInfoForSM_Res_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded RoutingInfoForSM_Res PDU...\n");
	    break;
	case ForwardSM_Arg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ForwardSM_Arg PDU...\n");
	    break;
	case ReportSM_DeliveryStatusArg_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ReportSM_DeliveryStatusArg PDU...\n");
	    break;
	case ReportSM_DeliveryStatusResStoredMSISDN_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded ReportSM_DeliveryStatusResStoredMSISDN PDU...\n");
	    break;
	case NoteSubscriberPresentImsi_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded NoteSubscriberPresentImsi PDU...\n");
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
	case MAP_UserInfo_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded MAP_UserInfo PDU...\n");
	    break;
	case MAP_DialoguePDU_PDU:
	    ossPrint(world, "\n\tOSS-Printing decoded MAP_DialoguePDU PDU...\n");
    }
    ossPrintPDU(world, pduNum, *decodedPDU);
    ossterm(world);
    return rc;
}


