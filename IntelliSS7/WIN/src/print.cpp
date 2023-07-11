////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1999 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
//  ID: $Id: print.cpp,v 9.1 2005/03/23 12:52:43 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <its.h>
#include <its_pprint.h>

#include <ansi/tcap.h>

#include <win_cpp.h>

#ident "$Id: print.cpp,v 9.1 2005/03/23 12:52:43 cvsadmin Exp $"

/*
 *  * shorthand
 *   */
#define CHECK_RETURN(r, cnt)    \
    if ((r) < 0)                \
    {                           \
        return (cnt);           \
    }                           \
    else                        \
    {                           \
        (cnt) += (r);           \
    }

#include <win_analyzed_information_il.h>
#include <win_connection_failure_report_il.h>
#include <win_connect_resource_il.h>
#include <win_facility_selected_and_available_il.h>
#include <win_feature_request_il.h>
#include <win_inter_system_page_il.h>
#include <win_inter_system_setup_il.h>
#include <win_location_request_il.h>
#include <win_modify_il.h>
#include <win_origination_request_il.h>
#include <win_qualification_request_il.h>
#include <win_registration_notification_il.h>
#include <win_routing_request_il.h>
#include <win_search_il.h>
#include <win_seize_resource_il.h>
#include <win_service_request_il.h>
#include <win_srf_directive_il.h>
#include <win_tbusy_il.h>
#include <win_t_no_answer_il.h>
#include <win_transfer_to_number_request_il.h>
#include <win_analyzed_information_rrl.h>
#include <win_facility_selected_and_available_rrl.h>
#include <win_feature_request_rrl.h>
#include <win_location_request_rrl.h>
#include <win_modify_rrl.h>
#include <win_origination_request_rrl.h>
#include <win_search_rrl.h>
#include <win_seize_resource_rrl.h>
#include <win_service_request_rrl.h>
#include <win_srf_directive_rrl.h>
#include <win_t_busy_rrl.h>
#include <win_t_no_answer_rrl.h>
#include <win_unsolicited_response_rrl.h>

/*
 * local namespaces in use.
 */
using namespace win;
using namespace std;
using namespace its;

/*
 * A helper for decode and print
 */
static inline int
DecodeAndPrint(RINGBUF_Manager *rb, int& tmp, int& ret,
               const char *startText, const char *endText,
               AsnObject& obj, Octets& octets)
{
    tmp = PPrint(rb, startText);
    CHECK_RETURN(tmp, ret);
    RINGBUF_Flush(rb);
    std::strstream outputStream;
    char* buffer;
    ITS_UINT length = 0;

    try
    {
        obj.Decode(octets);
    }
    catch (GenericException &ex)
    {
        cout << "Caught decode exception." << endl;
        cout << ex.GetDescription() << endl;
    }
    catch (exception &sex)
    {
        cout << "Caught Exception." << endl;
        cout << sex.what() << endl;
    }

    outputStream << obj << std::ends;
    outputStream.seekg (0, ios::end);
    length = outputStream.tellg();
    outputStream.seekg (0, ios::beg);
    buffer = (ITS_CHAR*)malloc(length*sizeof(ITS_CHAR));
    outputStream.read(buffer, length);
    tmp = PPrint(rb,buffer);
    free (buffer);

    tmp = PPrint(rb, endText);
    CHECK_RETURN(tmp, ret);

    return (ret);
}

/*
 * Another helper.  Note that we take advantage of fixed
 * variable names.
 */
#define PARAM_DECODE_AND_PRINT(t,v) \
    do                                                       \
    {                                                        \
        t v;                                                 \
        DecodeAndPrint(rb, tmp, ret,                         \
                       " --- Operation code: " #t " ---\n",  \
                       " --- End of parameter ---\n",        \
                       v, octets);                           \
    }                                                        \
    while (0)


/*
 * parameter printer
 */
extern "C"
int
ParamPrint(RINGBUF_Manager *rb, ITS_UINT *bCount,
           ITS_OCTET cType,
           ITS_OCTET opFamily, ITS_OCTET opCode,
           ITS_OCTET *pdu, ITS_USHORT clen)
{
    int tmp, ret = 0;
    vector<byte> array;
    Octets octets;
    ITS_OCTET *start = pdu;
    ITS_USHORT len = clen;

    /* dump raw bytes */
    tmp = PPrint(rb, " --- Component parameter raw data ---\n");
    do
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         " Param Data = %d\n",
                     *bCount, *pdu,
                     *pdu, *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        clen--;
        pdu++;
    }
    while (clen > 0);

    /* set up ASN decode */
    pdu = start;
    clen = len;
    array.erase(array.begin(), array.end());
    array.assign(pdu, pdu + clen);
    octets.SetArray(array);

    /* determine if we know how to print it */
    switch (cType)
    {
    case TCAP_PT_TC_INVOKE_ANSI:
    case TCAP_PT_TC_INVOKE_NL_ANSI:
        tmp = PPrint(rb, " --- Invoke parameter ---\n");
        CHECK_RETURN(tmp, ret);

        switch (opFamily)
        {
        // Request Notification.
        case TCAP_OF_IS41_ANSI:
            tmp = PPrint(rb, " --- Operation family: Request Notification ---\n");
            CHECK_RETURN(tmp, ret);

            switch (opCode)
            {
            case OP_QualificationRequest:      
                PARAM_DECODE_AND_PRINT(QualificationRequestIL, qualReq);
                break;

            case OP_RegistrationNotification:   
                PARAM_DECODE_AND_PRINT(RegistrationNotificationIL, regNot);
                break;

            case OP_LocationRequest:
                PARAM_DECODE_AND_PRINT(LocationRequestIL, locReq);
                break;

            case OP_RoutingRequest:
                PARAM_DECODE_AND_PRINT(RoutingRequestIL, routeReq);
                break;

            case OP_FeatureRequest:
                PARAM_DECODE_AND_PRINT(FeatureRequestIL, featReq);
                break;

            // Reserved value: 18.
            // Reserved value: 19.
            // Reserved value: 21.
            case OP_TransferToNumberRequest:
                PARAM_DECODE_AND_PRINT(TransferToNumberRequestIL, tranTo);
                break;

            case OP_InterSystemPage:
                PARAM_DECODE_AND_PRINT(InterSystemPageIL, interSysPage);
                break;

            // Reserved value: 41.
            case OP_InterSystemSetup:
                PARAM_DECODE_AND_PRINT(InterSystemSetupIL, interSysSetup);
                break;

            case OP_OriginationRequest:
                PARAM_DECODE_AND_PRINT(OriginationRequestIL, orReq);
                break;

            case OP_AnalyzedInformation:
                PARAM_DECODE_AND_PRINT(AnalyzedInformationIL, analInf);
                break;

            case OP_ConnectionFailureReport:
                PARAM_DECODE_AND_PRINT(ConnectionFailureReportIL, conFailRep);
                break;

            case OP_ConnectResource:
                PARAM_DECODE_AND_PRINT(ConnectResourceIL, connRes);
                break;

            case OP_DisconnectResource:
                // FIXME: arg type?
                break;

            case OP_FacilitySelectedAndAvailable:
                PARAM_DECODE_AND_PRINT(FacilitySelectedAndAvailableIL, facSel);
                break;

            case OP_InstructionRequest:
                // FIXME: arg type?
                break;

            case OP_Modify:
                PARAM_DECODE_AND_PRINT(ModifyIL, mod);
                break;

            case OP_ResetTimer:
                // FIXME: arg type?
                break;

            case OP_Search:
                PARAM_DECODE_AND_PRINT(SearchIL, search);
                break;

            case OP_SeizeResource:
                PARAM_DECODE_AND_PRINT(SeizeResourceIL, seizeRes);
                break;

            case OP_SRFDirective:
                PARAM_DECODE_AND_PRINT(SRFDirectiveIL, srfDir);
                break;

            case OP_TBusy:
                PARAM_DECODE_AND_PRINT(TbusyIL, tBusy);
                break;

            case OP_TNoAnswer:
                PARAM_DECODE_AND_PRINT(TNoAnswerIL, tNoAnswer);
                break;

            case OP_ServiceRequest:
                PARAM_DECODE_AND_PRINT(ServiceRequestIL, servReq);
                break;

            default:
                tmp = PPrint(rb, " --- Operation code: UNKNOWN ---\n");
                CHECK_RETURN(tmp, ret);
                tmp = PPrint(rb, " --- Decode not attempted ---\n");
                CHECK_RETURN(tmp, ret);
                break;
            }
            break;
        }
        break;

    case TCAP_PT_TC_RESULT_L_ANSI:
    case TCAP_PT_TC_RESULT_NL_ANSI:
        tmp = PPrint(rb, " --- Operation code: UNKNOWN ---\n");
        CHECK_RETURN(tmp, ret);
        tmp = PPrint(rb, " --- Decode not attempted ---\n");
        CHECK_RETURN(tmp, ret);
        break;

    case TCAP_PT_TC_ERROR_ANSI:
        switch (opCode)
        {
        case ERR_UnrecognizedMIN:
            tmp = PPrint(rb, " --- Error code: UnrecognizedMIN ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_UnrecognizedESN:
            tmp = PPrint(rb, " --- Error code: UnrecognizedESN ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_MIN_HLRMismatch:
            tmp = PPrint(rb, " --- Error code: HLRMismatch ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_OperationSequenceProblem:
            tmp = PPrint(rb, " --- Error code: OperationSequenceProblem ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_ResourceShortage:
            tmp = PPrint(rb, " --- Error code: ResourceShortage ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_OperationNotSupported:
            tmp = PPrint(rb, " --- Error code: OperationNotSupported ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_TrunkUnavailable:
            tmp = PPrint(rb, " --- Error code: TrunkAvailable ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_ParameterError:
            tmp = PPrint(rb, " --- Error code: ParameterError ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_SystemFailure:
            tmp = PPrint(rb, " --- Error code: SystemFailure ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_UnrecognizedParameterValue:
            tmp = PPrint(rb, " --- Error code: UnrecognizedParameterValue ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_FeatureInactive:
            tmp = PPrint(rb, " --- Error code: MissingParameter ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        case ERR_MissingParameter:
            tmp = PPrint(rb, " --- Error code: MissingParameter ---\n");
            CHECK_RETURN(tmp, ret);
            break;

        default:
            tmp = PPrint(rb, " --- Error code: UNKNOWN ---\n");
            CHECK_RETURN(tmp, ret);
            tmp = PPrint(rb, " --- Decode not attempted ---\n");
            CHECK_RETURN(tmp, ret);
            break;
        }
        break;

    default:
        break;
    }

    return (ret);
}

