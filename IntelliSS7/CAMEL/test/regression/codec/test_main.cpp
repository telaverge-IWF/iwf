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
//  ID: $Id: test_main.cpp,v 9.1 2005/03/23 12:51:16 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

#include <its++.h>
#include <its_ss7_stubs.h>

#include <cap_asncc_codec.h>
#include <cap_oss_codec.h>

typedef struct {
    char	*name;
    int		(*encode)(void *, unsigned char **, size_t *, size_t);
    int		(*decode)(unsigned char *, size_t, void **);
} PARAMS;

// Local function declarations.

static int EncodeAndDecode(PARAMS *, void **, int);


int main(int argc, char** argv)
{
    void	*decoded_pdu = NULL;
    PARAMS	params;
    int	i, rc, count = 0;

    rc = ITS_GlobalStart(0);

    if (rc != ITS_SUCCESS) 
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(rc));

        return rc;
    }


    params.name = "ApplyChargingArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeApplyChargingArg;
	    params.decode  = AsnCC_DecodeApplyChargingArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeApplyChargingArg;
	        params.decode = OSS_DecodeApplyChargingArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "CAMEL_AChBillingChargingCharacteristics";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeCAMEL_AChBillingChargingCharacteristics;
	    params.decode  = AsnCC_DecodeCAMEL_AChBillingChargingCharacteristics;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeCAMEL_AChBillingChargingCharacteristics;
	        params.decode = OSS_DecodeCAMEL_AChBillingChargingCharacteristics;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "CAMEL_CallResult";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeCAMEL_CallResult;
	    params.decode  = AsnCC_DecodeCAMEL_CallResult;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeCAMEL_CallResult;
	        params.decode = OSS_DecodeCAMEL_CallResult;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }


    params.name = "CAMEL_FCIBillingChargingCharacteristics";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeCAMEL_FCIBillingChargingCharacteristics;
	    params.decode  = AsnCC_DecodeCAMEL_FCIBillingChargingCharacteristics;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeCAMEL_FCIBillingChargingCharacteristics;
	        params.decode = OSS_DecodeCAMEL_FCIBillingChargingCharacteristics;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }


    params.name = "CAMEL_FCIGPRSBillingChargingCharacteristics";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeCAMEL_FCIGPRSBillingChargingCharacteristics;
	    params.decode  = AsnCC_DecodeCAMEL_FCIGPRSBillingChargingCharacteristics;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeCAMEL_FCIGPRSBillingChargingCharacteristics;
	        params.decode = OSS_DecodeCAMEL_FCIGPRSBillingChargingCharacteristics;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }
    

    params.name = "CAMEL_FCISMSBillingChargingCharacteristics";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeCAMEL_FCISMSBillingChargingCharacteristics;
	    params.decode  = AsnCC_DecodeCAMEL_FCISMSBillingChargingCharacteristics;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeCAMEL_FCISMSBillingChargingCharacteristics;
	        params.decode = OSS_DecodeCAMEL_FCISMSBillingChargingCharacteristics;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }


    params.name = "CAMEL_SCIBillingChargingCharacteristics";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeCAMEL_SCIBillingChargingCharacteristics;
	    params.decode  = AsnCC_DecodeCAMEL_SCIBillingChargingCharacteristics;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeCAMEL_SCIBillingChargingCharacteristics;
	        params.decode = OSS_DecodeCAMEL_SCIBillingChargingCharacteristics;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }
    
    params.name = "CAMEL_SCIGPRSBillingChargingCharacteristics";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeCAMEL_SCIGPRSBillingChargingCharacteristics;
	    params.decode  = AsnCC_DecodeCAMEL_SCIGPRSBillingChargingCharacteristics;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeCAMEL_SCIGPRSBillingChargingCharacteristics;
	        params.decode = OSS_DecodeCAMEL_SCIGPRSBillingChargingCharacteristics;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    
    
    params.name = "UnavailableNetworkResource";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeUnavailableNetworkResource;
	    params.decode  = AsnCC_DecodeUnavailableNetworkResource;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeUnavailableNetworkResource;
	        params.decode = OSS_DecodeUnavailableNetworkResource;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "CancelFailed";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeCancelFailed;
	    params.decode  = AsnCC_DecodeCancelFailed;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeCancelFailed;
	        params.decode = OSS_DecodeCancelFailed;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "RequestedInfoError";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeRequestedInfoError;
	    params.decode  = AsnCC_DecodeRequestedInfoError;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeRequestedInfoError;
	        params.decode = OSS_DecodeRequestedInfoError;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "TaskRefused";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeTaskRefused;
	    params.decode  = AsnCC_DecodeTaskRefused;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeTaskRefused;
	        params.decode = OSS_DecodeTaskRefused;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "ApplyChargingReportArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeApplyChargingReportArg;
	    params.decode  = AsnCC_DecodeApplyChargingReportArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeApplyChargingReportArg;
	        params.decode = OSS_DecodeApplyChargingReportArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "AssistRequestInstructionsArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeAssistRequestInstructionsArg;
	    params.decode  = AsnCC_DecodeAssistRequestInstructionsArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeAssistRequestInstructionsArg;
	        params.decode = OSS_DecodeAssistRequestInstructionsArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "CallGapArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeCallGapArg;
	    params.decode  = AsnCC_DecodeCallGapArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeCallGapArg;
	        params.decode = OSS_DecodeCallGapArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }


    params.name = "CallInformationReportArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeCallInformationReportArg;
	    params.decode  = AsnCC_DecodeCallInformationReportArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeCallInformationReportArg;
	        params.decode = OSS_DecodeCallInformationReportArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "CallInformationRequestArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeCallInformationRequestArg;
	    params.decode  = AsnCC_DecodeCallInformationRequestArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeCallInformationRequestArg;
	        params.decode = OSS_DecodeCallInformationRequestArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "CancelArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeCancelArg;
	    params.decode  = AsnCC_DecodeCancelArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeCancelArg;
	        params.decode = OSS_DecodeCancelArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

     params.name = "ConnectArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeConnectArg;
	    params.decode  = AsnCC_DecodeConnectArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeConnectArg;
	        params.decode = OSS_DecodeConnectArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

     params.name = "ConnectToResourceArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeConnectToResourceArg;
	    params.decode  = AsnCC_DecodeConnectToResourceArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeConnectToResourceArg;
	        params.decode = OSS_DecodeConnectToResourceArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }


     params.name = "ContinueWithArgumentArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeContinueWithArgumentArg;
	    params.decode  = AsnCC_DecodeContinueWithArgumentArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeContinueWithArgumentArg;
	        params.decode = OSS_DecodeContinueWithArgumentArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }


     params.name = "EstablishTemporaryConnectionArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeEstablishTemporaryConnectionArg;
	    params.decode  = AsnCC_DecodeEstablishTemporaryConnectionArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeEstablishTemporaryConnectionArg;
	        params.decode = OSS_DecodeEstablishTemporaryConnectionArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }


     params.name = "EventReportBCSMArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeEventReportBCSMArg;
	    params.decode  = AsnCC_DecodeEventReportBCSMArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeEventReportBCSMArg;
	        params.decode = OSS_DecodeEventReportBCSMArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "FurnishChargingInformationArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeFurnishChargingInformationArg;
	    params.decode  = AsnCC_DecodeFurnishChargingInformationArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeFurnishChargingInformationArg;
	        params.decode = OSS_DecodeFurnishChargingInformationArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "InitialDPArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeInitialDPArg;
	    params.decode  = AsnCC_DecodeInitialDPArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeInitialDPArg;
	        params.decode = OSS_DecodeInitialDPArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "ReleaseCallArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeReleaseCallArg;
	    params.decode  = AsnCC_DecodeReleaseCallArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeReleaseCallArg;
	        params.decode = OSS_DecodeReleaseCallArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }

    params.name = "RequestReportBCSMEventArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeRequestReportBCSMEventArg;
	    params.decode  = AsnCC_DecodeRequestReportBCSMEventArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeRequestReportBCSMEventArg;
	        params.decode = OSS_DecodeRequestReportBCSMEventArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "ResetTimerArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeResetTimerArg;
	    params.decode  = AsnCC_DecodeResetTimerArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeResetTimerArg;
	        params.decode = OSS_DecodeResetTimerArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "SendChargingInformationArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeSendChargingInformationArg;
	    params.decode  = AsnCC_DecodeSendChargingInformationArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeSendChargingInformationArg;
	        params.decode = OSS_DecodeSendChargingInformationArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "PlayAnnouncementArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodePlayAnnouncementArg;
	    params.decode  = AsnCC_DecodePlayAnnouncementArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodePlayAnnouncementArg;
	        params.decode = OSS_DecodePlayAnnouncementArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "PromptAndCollectUserInformationArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodePromptAndCollectUserInformationArg;
	    params.decode  = AsnCC_DecodePromptAndCollectUserInformationArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodePromptAndCollectUserInformationArg;
	        params.decode = OSS_DecodePromptAndCollectUserInformationArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "ReceivedInformationArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeReceivedInformationArg;
	    params.decode  = AsnCC_DecodeReceivedInformationArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeReceivedInformationArg;
	        params.decode = OSS_DecodeReceivedInformationArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "SpecializedResourceReportArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeSpecializedResourceReportArg;
	    params.decode  = AsnCC_DecodeSpecializedResourceReportArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeSpecializedResourceReportArg;
	        params.decode = OSS_DecodeSpecializedResourceReportArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  


    params.name = "ConnectSMSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeConnectSMSArg;
	    params.decode  = AsnCC_DecodeConnectSMSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeConnectSMSArg;
	        params.decode = OSS_DecodeConnectSMSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  
    
    params.name = "EventReportSMSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeEventReportSMSArg;
	    params.decode  = AsnCC_DecodeEventReportSMSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeEventReportSMSArg;
	        params.decode = OSS_DecodeEventReportSMSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "FurnishChargingInformationSMSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeFurnishChargingInformationSMSArg;
	    params.decode  = AsnCC_DecodeFurnishChargingInformationSMSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeFurnishChargingInformationSMSArg;
	        params.decode = OSS_DecodeFurnishChargingInformationSMSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "InitialDPSMSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeInitialDPSMSArg;
	    params.decode  = AsnCC_DecodeInitialDPSMSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeInitialDPSMSArg;
	        params.decode = OSS_DecodeInitialDPSMSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "ReleaseSMSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeReleaseSMSArg;
	    params.decode  = AsnCC_DecodeReleaseSMSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeReleaseSMSArg;
	        params.decode = OSS_DecodeReleaseSMSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "RequestReportSMSEventArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeRequestReportSMSEventArg;
	    params.decode  = AsnCC_DecodeRequestReportSMSEventArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeRequestReportSMSEventArg;
	        params.decode = OSS_DecodeRequestReportSMSEventArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "ResetTimerSMSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeResetTimerSMSArg;
	    params.decode  = AsnCC_DecodeResetTimerSMSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeResetTimerSMSArg;
	        params.decode = OSS_DecodeResetTimerSMSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "ActivityTestGPRSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeActivityTestGPRSArg;
	    params.decode  = AsnCC_DecodeActivityTestGPRSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeActivityTestGPRSArg;
	        params.decode = OSS_DecodeActivityTestGPRSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "ApplyChargingGPRSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeApplyChargingGPRSArg;
	    params.decode  = AsnCC_DecodeApplyChargingGPRSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeApplyChargingGPRSArg;
	        params.decode = OSS_DecodeApplyChargingGPRSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }*/

    params.name = "ApplyChargingReportGPRSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeApplyChargingReportGPRSArg;
	    params.decode  = AsnCC_DecodeApplyChargingReportGPRSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeApplyChargingReportGPRSArg;
	        params.decode = OSS_DecodeApplyChargingReportGPRSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "CancelGPRSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeCancelGPRSArg;
	    params.decode  = AsnCC_DecodeCancelGPRSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeCancelGPRSArg;
	        params.decode = OSS_DecodeCancelGPRSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "ConnectGPRSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeConnectGPRSArg;
	    params.decode  = AsnCC_DecodeConnectGPRSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeConnectGPRSArg;
	        params.decode = OSS_DecodeConnectGPRSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "ContinueGPRSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeContinueGPRSArg;
	    params.decode  = AsnCC_DecodeContinueGPRSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeContinueGPRSArg;
	        params.decode = OSS_DecodeContinueGPRSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "EntityReleasedGPRSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeEntityReleasedGPRSArg;
	    params.decode  = AsnCC_DecodeEntityReleasedGPRSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeEntityReleasedGPRSArg;
	        params.decode = OSS_DecodeEntityReleasedGPRSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "FurnishChargingInformationGPRSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeFurnishChargingInformationGPRSArg;
	    params.decode  = AsnCC_DecodeFurnishChargingInformationGPRSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeFurnishChargingInformationGPRSArg;
	        params.decode = OSS_DecodeFurnishChargingInformationGPRSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "InitialDPGPRSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeInitialDPGPRSArg;
	    params.decode  = AsnCC_DecodeInitialDPGPRSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeInitialDPGPRSArg;
	        params.decode = OSS_DecodeInitialDPGPRSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "ReleaseGPRSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeReleaseGPRSArg;
	    params.decode  = AsnCC_DecodeReleaseGPRSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeReleaseGPRSArg;
	        params.decode = OSS_DecodeReleaseGPRSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "EventReportGPRSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeEventReportGPRSArg;
	    params.decode  = AsnCC_DecodeEventReportGPRSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeEventReportGPRSArg;
	        params.decode = OSS_DecodeEventReportGPRSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "RequestReportGPRSEventArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeRequestReportGPRSEventArg;
	    params.decode  = AsnCC_DecodeRequestReportGPRSEventArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeRequestReportGPRSEventArg;
	        params.decode = OSS_DecodeRequestReportGPRSEventArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "ResetTimerGPRSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeResetTimerGPRSArg;
	    params.decode  = AsnCC_DecodeResetTimerGPRSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeResetTimerGPRSArg;
	        params.decode = OSS_DecodeResetTimerGPRSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  

    params.name = "SendChargingInformationGPRSArg";

    for (i = 1; i <= 1; i++) 
    {
	    printf("\n===== Testing %s as OSS-->IntelliNet =====\n", params.name);

	    params.encode  = OSS_EncodeSendChargingInformationGPRSArg;
	    params.decode  = AsnCC_DecodeSendChargingInformationGPRSArg;

	    decoded_pdu = NULL;

	    if (rc = EncodeAndDecode(&params, &decoded_pdu, i)) 
        {
	        printf("Failed to encode/decode %s.\n", params.name);
	        count++;
	    }
	    else 
        {
	        printf("\n===== Testing %s as IntelliNet-->OSS =====\n", params.name);

	        params.encode = AsnCC_EncodeSendChargingInformationGPRSArg;
	        params.decode = OSS_DecodeSendChargingInformationGPRSArg;

	        if (rc = EncodeAndDecode(&params, &decoded_pdu, i))
            {
		        printf("Failed to encode/decode %s.\n", params.name);
		        count++;
	        }
	        else 
            {
		        //
		        // The OSS decoder was provided with block of memory to use
		        // for decoding PDUs.  So now we can free the block allocated
		        // in cap_oss_api.cpp.
		        //

		        if (decoded_pdu)
                {
		            free(decoded_pdu);
                }
	        }
	    }
    }  


    ITS_GlobalStop();

    return EXIT_SUCCESS;
}


int 
EncodeAndDecode(PARAMS *params, void **pdu, int valueNumber)
{
    int		rc = 0;
    size_t		size;
    unsigned char *encoded;


    printf("\n\tEncoding %s PDU for value #%d...\n", params->name, valueNumber);

    if (rc = params->encode(*pdu, &encoded, &size, valueNumber))
    {
	    printf("Failed to encode %s.\n", params->name);
    }
    else 
    {
	    printf("\nDecoding %s PDU for value #%d...\n", params->name, valueNumber);
	    *pdu = NULL;
	    rc = params->decode(encoded, size, pdu);

	    if (rc)
        {
	        printf("Decoding failed with error code = %d\n", rc);
        }
	    else
        {
	        printf("Message encoded and decoded successfully.\n");
        }
    }

    return rc;
}

