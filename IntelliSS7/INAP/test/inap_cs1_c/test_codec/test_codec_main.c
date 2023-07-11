/*----------------------------------------------------------------------------*
 *                                                                            *
 *      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *              Manufactured in the United States of America.                 *
 *        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                            *
 *    This product and related documentation is protected by copyright and    *
 *    distributed under licenses restricting its use, copying, distribution   *
 *    and decompilation.  No part of this product or related documentation    *
 *    may be reproduced in any form by any means without prior written        *
 *    authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                            *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *    government is subject to restrictions as set forth in subparagraph      *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *
 *  ID: $Id: test_codec_main.c,v 9.1 2005/03/23 12:51:46 cvsadmin Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  INAP CS1 ASN.1 codec example.
 *
 *  This example shows how to build (create, insert data and encode) and how
 *  to interpret (decode and retrieve data) for the following INAP operation
 *  arguments:
 *
 *  o   ConnectArg.
 *
 *  o   InitialDPArg.
 *
 */ 



#include <stdio.h>

#if defined(WIN32)
#include <conio.h>
#else /* !defined(WIN32) */
#if !defined(EXIT_FAILURE)
#define EXIT_FAILURE (-1)
#endif
#if !defined(EXIT_SUCCESS)
#define EXIT_SUCCESS (0)
#endif
#endif /* defined(WIN32) */

#include <its.h>
#include <its_ss7_stubs.h>

#include <asn_common.h>
#include <asn_error.h>

#include <inap_cs1_connect_arg_c.h>
#include <inap_cs1_initial_dp_arg_c.h>
#include <inap_cs1_its_feature_class_c.h>




/*------------------------------------------------------------------------------
 *
 *  How to Build a Connect operation argument (INAP_CS1_ConnectArg):
 *
 *  o   Create a ConnectArg object.
 *
 *  o   Insert data step by step in the created ConnectArg object (i.e. populate
 *      various parameters of the Connect operation argument).
 *  
 *  o   Encode the ConnectArg object to produce a ConnectArg encoded value.
 *
 */

int  
BuildOperationConnectArg(ITS_OCTET** octetArray, size_t* size)
{
    INAP_CS1_ConnectArg connectArg  = NULL;
    ASN_Octets octets               = NULL;
    int res                         = ITS_SUCCESS;

    ASN_C_REQUIRE(octetArray != NULL);
    ASN_C_REQUIRE(size != NULL);
    ASN_C_REQUIRE(*octetArray == NULL);

    /*  
     *  [1] Create ConnectArg object. 
     */

    connectArg = INAP_CS1_ConnectArg_ConstructDefault();

    if (connectArg == NULL)
    {
        return ITS_ENOMEM;
    }

    /*------------------------------------------------------------------------*/

    /*
     *  Memory management note: all the following parameter objects that are
     *  used to populate the connectArg object are created in the heap using 
     *  the appropriate construct function. They are automatically deleted 
     *  (i.e. all associated memory released) when the connectArg object is
     *  deleted. 
     */

    /*------------------------------------------------------------------------*/

    /*  
     *  [2] Populate mandatory parameter "destinationRoutingAddress". 
     */

    {
        /*  
         *  [2-1] Create DestinationRoutingAddress object. 
         */

        INAP_CS1_DestinationRoutingAddress 
            destinationRoutingAddress = 
                INAP_CS1_DestinationRoutingAddress_ConstructDefault();

        if (destinationRoutingAddress == NULL)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return ITS_ENOMEM;
        }
    
        /*
         *  INAP API Note: a DestinationRoutingAddress object contains a list of
         *  CalledPartyNumber objects.
         */

        {
            /*  
             *  [2-1-1] Create CalledPartyNumber object. 
             */

            ITS_OCTET fixedArray1[] = 
                { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

            size_t fixedArray1Size = 7;

            INAP_CS1_CalledPartyNumber 
                calledPartyNumber =
                    INAP_CS1_CalledPartyNumber_ConstructWithArraySize(
                        fixedArray1,
                        fixedArray1Size);

            if (calledPartyNumber == NULL)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_DestinationRoutingAddress_Destruct(
                    destinationRoutingAddress);

                return ITS_ENOMEM;
            }

            /*
             *  [2-1-2] Add CalledPartyNumber object to 
             *  DestinationRoutingAddress object. 
             */

            res = 
                INAP_CS1_DestinationRoutingAddress_AddElement(
                    destinationRoutingAddress,
                    calledPartyNumber);

            if (res != ITS_SUCCESS)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_DestinationRoutingAddress_Destruct(
                    destinationRoutingAddress);

                return ITS_ENOMEM;
            }
        }

        /*
         *  [2-2] Set DestinationRoutingAddress object in ConnectArg object.
         */

        INAP_CS1_ConnectArg_SetDestinationRoutingAddress(
            connectArg,
            destinationRoutingAddress);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [3] Populate optional parameter "alertingPattern".
     */

    {
        /*
         *  [3-1] Create AlertingPattern object.
         */

        ITS_OCTET fixedArray2[] = { 0x20, 0x21, 0x22 };

        size_t fixedArray2Size = 3;

        INAP_CS1_AlertingPattern
            alertingPattern =
                INAP_CS1_AlertingPattern_ConstructWithArraySize(
                    fixedArray2,
                    fixedArray2Size);

        if (alertingPattern == NULL)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return ITS_ENOMEM;
        }

        /*
         *  [3-2] Set AlertingPattern object in ConnectArg object.
         */

        INAP_CS1_ConnectArg_SetAlertingPattern(
            connectArg,
            alertingPattern);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [4] Populate optional parameter "correlationID".
     */

    {
        /*
         *  [4-1] Create CorrelationID object.
         */

        ITS_OCTET fixedArray3[] = { 0x30, 0x31, 0x32, 0x33, 0x34 };

        size_t fixedArray3Size = 5;

        INAP_CS1_CorrelationID
            correlationID =
                INAP_CS1_CorrelationID_ConstructWithArraySize(
                    fixedArray3,
                    fixedArray3Size);

        if (correlationID == NULL)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return ITS_ENOMEM;
        }

        /*
         *  [4-2] Set CorrelationID object in ConnectArg object.
         */

        INAP_CS1_ConnectArg_SetCorrelationID(
            connectArg,
            correlationID);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [5] Populate optional parameter "forwardingCondition".
     */

    {
        /*
         *  [5-1] Create ForwardingCondition object.
         */

        INAP_CS1_ForwardingCondition
            forwardingCondition =
                INAP_CS1_ForwardingCondition_ConstructDefault();

        if (forwardingCondition == NULL)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return ITS_ENOMEM;
        }

        INAP_CS1_ForwardingCondition_SetAny(forwardingCondition);

        /*
         *  [5-2] Set ForwardingCondition object in ConnectArg object.
         */

        INAP_CS1_ConnectArg_SetForwardingCondition(
            connectArg,
            forwardingCondition);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [6] Populate optional parameter "routeList".
     */

    {
        /*
         *  [6-1] Create RouteList object.
         */

        INAP_CS1_RouteList 
            routeList = 
                INAP_CS1_RouteList_ConstructDefault();

        if (routeList == NULL)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return ITS_ENOMEM;
        }

        /*
         *  INAP API Note: a RouteList object contains a list of 
         *  RouteList_OCTETSTRING objects.
         */

        {
            /*
             *  [6-1-1] Create RouteList_OCTETSTRING object.
             */

            ITS_OCTET fixedArray4[] = { 0x01, 0x02, 0x03 };

            size_t fixedArray4Size = 3;

            INAP_CS1_RouteList_OCTETSTRING
                routeListOCTETSTRING1 =
                    INAP_CS1_RouteList_OCTETSTRING_ConstructWithArraySize(
                        fixedArray4,
                        fixedArray4Size);

            if (routeListOCTETSTRING1 == NULL)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_RouteList_Destruct(routeList);

                return ITS_ENOMEM;
            }

            /*
             *  [6-1-2] Add RouteList_OCTETSTRING object to RouteList object.
             */

            res =
                INAP_CS1_RouteList_AddElement(
                    routeList,
                    routeListOCTETSTRING1);

            if (res != ITS_SUCCESS)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_RouteList_Destruct(routeList);
                INAP_CS1_RouteList_OCTETSTRING_Destruct(routeListOCTETSTRING1);

                return ITS_ENOMEM;
            }
        }

        {
            /*
             *  [6-1-3] Create RouteList_OCTETSTRING object.
             */

            ITS_OCTET fixedArray5[] = { 0x11, 0x22, 0x33, 0x44 };

            size_t fixedArray5Size = 4;

            INAP_CS1_RouteList_OCTETSTRING
                routeListOCTETSTRING2 =
                    INAP_CS1_RouteList_OCTETSTRING_ConstructWithArraySize(
                        fixedArray5,
                        fixedArray5Size);

            if (routeListOCTETSTRING2 == NULL)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_RouteList_Destruct(routeList);

                return ITS_ENOMEM;
            }

            /*
             *  [6-1-4] Add RouteList_OCTETSTRING object to RouteList object.
             */

            res =
                INAP_CS1_RouteList_AddElement(
                    routeList,
                    routeListOCTETSTRING2);

            if (res != ITS_SUCCESS)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_RouteList_Destruct(routeList);
                INAP_CS1_RouteList_OCTETSTRING_Destruct(routeListOCTETSTRING2);

                return ITS_ENOMEM;
            }
        }

        {
            /*
             *  [6-1-5] Create RouteList_OCTETSTRING object.
             */

            ITS_OCTET fixedArray6[] = { 0x10, 0x20, 0x30, 0x40, 0x50 };

            size_t fixedArray6Size = 5;

            INAP_CS1_RouteList_OCTETSTRING
                routeListOCTETSTRING3 =
                    INAP_CS1_RouteList_OCTETSTRING_ConstructWithArraySize(
                        fixedArray6,
                        fixedArray6Size);

            if (routeListOCTETSTRING3 == NULL)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_RouteList_Destruct(routeList);

                return ITS_ENOMEM;
            }

            /*  
             *  [6-1-6] Add RouteList_OCTETSTRING object to RouteList object.
             */

            res =
                INAP_CS1_RouteList_AddElement(
                    routeList,
                    routeListOCTETSTRING3);

            if (res != ITS_SUCCESS)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_RouteList_Destruct(routeList);
                INAP_CS1_RouteList_OCTETSTRING_Destruct(routeListOCTETSTRING3);

                return ITS_ENOMEM;
            }
        }

        /*
         *  [6-2] Set RouteList object in ConnectArg object.
         */

        INAP_CS1_ConnectArg_SetRouteList(connectArg, routeList);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [7] Populate optional parameter "callingPartyNumber".
     */

    {
        /*
         *  [7-1] Create CallingPartyNumber object.
         */

        ITS_OCTET fixedArray7[] = { 0x07, 0x07, 0x08, 0x09, 0x09, 0x08, 0x04 };

        size_t fixedArray7Size = 7;

        INAP_CS1_CallingPartyNumber
            callingPartyNumber =
                INAP_CS1_CallingPartyNumber_ConstructWithArraySize(
                    fixedArray7,
                    fixedArray7Size);

        if (callingPartyNumber == NULL)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return ITS_ENOMEM;
        }

        /*
         *  [7-2] Set CallingPartyNumber object in ConnectArg object.
         */

        INAP_CS1_ConnectArg_SetCallingPartyNumber(
            connectArg, 
            callingPartyNumber);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [8] Encode ConnectArg object.
     */

    {
        ASN_EncodeError encodeError         = NULL;
        int encodeErrorCode                 = ITS_SUCCESS;
        const char* encodeErrorText         = NULL;
        const char* encodeExtendedErrorText = NULL;


        res = INAP_CS1_ConnectArg_Encode(
                connectArg, 
                &octets, 
                &encodeError);

        if (res == ITS_E_ASN_ENCODE_ERROR)
        {
            /*  
             *  Status:                                              
             *                                                       
             *  octets == NULL.                                      
             *  encodeError != NULL. Must be destructed by end-user. 
             */


            /* 
             * Retrieve and print encode error code. 
             */

            encodeErrorCode = 
                ASN_EncodeError_GetError(
                    encodeError);

            printf(
                "\nEncode error code is <%d>.\n\n", 
                encodeErrorCode);

            /* 
             *  Retrieve and print encode error text (freed automatically when
             *  encodeError object is destructed).                               
             */

            encodeErrorText = 
                ASN_EncodeError_GetErrorText(encodeError);

            if (encodeErrorText == NULL)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                ASN_EncodeError_Destruct(encodeError);

                return ITS_ENOMEM;
            }

            printf(
                "\nEncode error text is <%s>.\n\n", 
                encodeErrorText);

            /* 
             *  Retrieve and print extended encode error text (freed 
             *  automatically when encodeError object is destructed).
             */

            encodeExtendedErrorText = 
                ASN_EncodeError_GetExtendedErrorText(
                    encodeError);

            if (encodeExtendedErrorText == NULL)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                ASN_EncodeError_Destruct(encodeError);

                return ITS_ENOMEM;
            }

            printf(
                "\nEncode error extended text is <%s>.\n\n", 
                encodeExtendedErrorText);

            INAP_CS1_ConnectArg_Destruct(connectArg);

            /* 
             *  Object encodeError must be destructed by end-user. 
             */

            ASN_EncodeError_Destruct(encodeError);

            return res;
        }
        else if (res != ITS_SUCCESS)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return res;
        }
        else
        {
            /* 
             *  res == ITS_SUCCESS. Nothing to do. Continue processing. 
             */
        }

        /*
         *  Print contents of ASN.1 encoded value.
         */

        printf("\nPrinting ConnectArg ASN.1 encoded value...\n\n");

        ASN_Octets_Print(octets);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [9] Retrieve ConnectArg ASN.1 encoded value from octets object and
     *  return ConnectArg ASN.1 encoded value through the function parameters
     *  octetArray and size.
     */

    *octetArray = 
        (ITS_OCTET*)calloc(
            ASN_Octets_GetSize(octets), 
            sizeof(ITS_OCTET));

    if (*octetArray == NULL)
    {
        INAP_CS1_ConnectArg_Destruct(connectArg);
        ASN_Octets_Destruct(octets);

        return ITS_ENOMEM;
    }

    memcpy(
        *octetArray, 
        ASN_Octets_GetArray(octets), 
        ASN_Octets_GetSize(octets));

    *size = ASN_Octets_GetSize(octets);

    /*------------------------------------------------------------------------*/

    /*
     *  [10] Free all memory allocated on the heap.
     */

    /*
     *  [10-1] Delete ConnectArg object (and therefore all the parameter 
     *  objects that have been previously set).
     */

    INAP_CS1_ConnectArg_Destruct(connectArg);

    /*
     *  [10-2] Delete Octets object created by the call to 
     *  INAP_CS1_ConnectArg_Encode.
     */

    ASN_Octets_Destruct(octets);

    /*------------------------------------------------------------------------*/

    /*
     *  Return success.
     */

    return ITS_SUCCESS;
}


/*------------------------------------------------------------------------------
 *
 *  How to interpret an (encoded) INAP Connect operation argument (ConnectArg):
 *
 *  o   Decode a ConnectArg encoded value (i.e. create a ConnectArg object from
 *      a ConnectArg encoded value).
 *
 *  o   Retrieve Data from a ConnectArg object.
 *
 */

int 
InterpretOperationConnectArg(const ITS_OCTET* octetArray, size_t size)
{
    INAP_CS1_ConnectArg connectArg  = NULL;
    ASN_Octets octets               = NULL;
    int res                         = ITS_SUCCESS;

    ASN_C_REQUIRE(octetArray != NULL);
    ASN_C_REQUIRE(size != 0);

    /*
     *  [1] Create Octets object from ConnectArg ASN.1 encoded value.
     */

    octets = ASN_Octets_ConstructWithArray(octetArray, size);

    if (octets == NULL)
    {
        return ITS_ENOMEM;
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [2] Create ConnectArg object (used by decode phase).
     */

    connectArg = INAP_CS1_ConnectArg_ConstructDefault();

    if (connectArg == NULL)
    {
        ASN_Octets_Destruct(octets);

        return ITS_ENOMEM;
    }

    /*------------------------------------------------------------------------*/

    /*  
     *  [3] Decode ConnectArg ASN.1 encoded value and therefore populate 
     *  previously created ConnectArg object.
     */

    {
        ASN_DecodeError decodeError         = NULL;
        int decodeErrorCode                 = ITS_SUCCESS;
        const char* decodeErrorText         = NULL;
        const char* decodeExtendedErrorText = NULL;

        res = INAP_CS1_ConnectArg_Decode(
                                connectArg, 
                                octets, 
                                &decodeError);

        if (res == ITS_E_ASN_DECODE_ERROR)
        {
            /* 
             *  Status:                                                   
             *                                                            
             *  decodeError != NULL. Must be destructed by end-user.       
             */


            /* 
             *  Retrieve and print decode error code. 
             */

            decodeErrorCode = 
                ASN_DecodeError_GetError(decodeError);

            fprintf(
                stderr, 
                "\nDecode error code is <%d>.\n\n", 
                decodeErrorCode);

            /* 
             *  Retrieve and print decode error text (freed automatically when
             *  decodeError object is destructed).                             
             */

            decodeErrorText = 
                ASN_DecodeError_GetErrorText(decodeError);

            if (decodeErrorText == NULL)
            {
                ASN_Octets_Destruct(octets);
                INAP_CS1_ConnectArg_Destruct(connectArg);
                ASN_DecodeError_Destruct(decodeError);

                return ITS_ENOMEM;
            }

            fprintf(
                stderr, 
                "\nDecode error text is <%s>.\n\n", 
                decodeErrorText);

            /* 
             *  Retrieve and print extended decode error text (freed 
             *  automatically when decodeError object is destructed).
             */

            decodeExtendedErrorText = 
                ASN_DecodeError_GetExtendedErrorText(decodeError);

            if (decodeExtendedErrorText == NULL)
            {
                ASN_Octets_Destruct(octets);
                INAP_CS1_ConnectArg_Destruct(connectArg);
                ASN_DecodeError_Destruct(decodeError);

                return ITS_ENOMEM;
            }

            fprintf(
                stderr, 
                "\nDecode error extended text is <%s>.\n\n", 
                decodeExtendedErrorText);

            ASN_Octets_Destruct(octets);
            INAP_CS1_ConnectArg_Destruct(connectArg);

            /* 
             *  Object decodeError must be destructed by end-user. 
             */

            ASN_DecodeError_Destruct(decodeError);

            return res;
        }
        else if (res != ITS_SUCCESS)
        {
            ASN_Octets_Destruct(octets);
            INAP_CS1_ConnectArg_Destruct(connectArg);
            ASN_DecodeError_Destruct(decodeError);

            return res;
        }
        else
        {
            /* 
             *  res == ITS_SUCCESS. Nothing to do. Continue processing. 
             */
        }

        /*
         *  Print decoded ConnectArg object.
         */

        printf("\nPrinting decoded ConnectArg object...\n");

        INAP_CS1_ConnectArg_Print(connectArg);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [4] Retrieve mandatory parameter "destinationRoutingAddress".
     */

    {
        size_t i            = 0;
        size_t paramSize    = 0;

        /*
         *  [4-1] Retrieve const pointer to DestinationRoutingAddress object.
         */

        const INAP_CS1_DestinationRoutingAddress
            destinationRoutingAddress =
                INAP_CS1_ConnectArg_GetDestinationRoutingAddress(
                    connectArg);

        /*
         *  INAP API Note: a DestinationRoutingAddress object contains a list of
         *  CalledPartyNumber objects.
         */

        /*
         *  [4-2] Retrieve contents of DestinationRoutingAddress object.
         */

        paramSize = 
            INAP_CS1_DestinationRoutingAddress_GetSize(
                destinationRoutingAddress);

        for (i = 0; i < paramSize; i++)
        {
            const ITS_OCTET* array  = NULL;
            size_t arraySize        = 0;

            /*
             *  [4-2-1] Retrieve const pointer to CalledPartyNumber object.
             */

            const INAP_CS1_CalledPartyNumber
                calledPartyNumber =
                    INAP_CS1_DestinationRoutingAddress_GetElementAt(
                        destinationRoutingAddress,
                        i);

            /*
             *  [4-2-2] Retrieve contents of CalledPartyNumber object.
             */

            array = 
                INAP_CS1_CalledPartyNumber_GetArray(
                    calledPartyNumber);

            arraySize =
                INAP_CS1_CalledPartyNumber_GetSize(
                    calledPartyNumber);

            /*
             *  Do something with array of octets...
             */

            /*
             *  [4-2-3] Print CalledPartyNumber object.
             */

            printf("\nPrinting CalledPartyNumber object...\n");

            INAP_CS1_CalledPartyNumber_Print(calledPartyNumber);

            printf("\n");
        }

        /*
         *  [4-3] Print DestinationRoutingAddress object.
         */

        printf("\nPrinting DestinationRoutingAddress object...\n");

        INAP_CS1_DestinationRoutingAddress_Print(
            destinationRoutingAddress);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [5] Retrieve optional parameter "alertingPattern".
     */

    if (INAP_CS1_ConnectArg_OptionAlertingPattern(connectArg))
    {
        const ITS_OCTET* array  = NULL;
        size_t arraySize        = 0;

        /*
         *  [5-1] Retrieve const pointer to AlertingPattern object.
         */

        const INAP_CS1_AlertingPattern
            alertingPattern =
                INAP_CS1_ConnectArg_GetAlertingPattern(
                    connectArg);

        /*
         *  [5-2] Retrieve contents of AlertingPattern object.
         */

        array = 
            INAP_CS1_AlertingPattern_GetArray(
                alertingPattern);

        arraySize =
            INAP_CS1_AlertingPattern_GetSize(
                alertingPattern);

        /*
         *  Do something with array of octets...
         */

        /*
         *  [5-3] Print AlertingPattern object.
         */

        printf("\nPrinting AlertingPattern object...\n");

        INAP_CS1_AlertingPattern_Print(alertingPattern);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [6] Retrieve optional parameter "correlationID".
     */

    if (INAP_CS1_ConnectArg_OptionCorrelationID(connectArg))
    {
        const ITS_OCTET* array  = NULL;
        size_t arraySize        = 0;

        /*
         *  [6-1] Retrieve const pointer to CorrelationID object.
         */

        const INAP_CS1_CorrelationID
            correlationID = 
                INAP_CS1_ConnectArg_GetCorrelationID(connectArg);

        /*
         *  [6-2] Retrieve contents of CorrelationID object.
         */

        array = 
            INAP_CS1_CorrelationID_GetArray(correlationID);

        arraySize = 
            INAP_CS1_CorrelationID_GetSize(correlationID);

        /*
         *  Do something with array of octets...
         */

        /*
         *  [6-3] Print CorrelationID object.
         */

        printf("\nPrinting CorrelationID object...\n");

        INAP_CS1_CorrelationID_Print(correlationID);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [7] Retrieve optional parameter "forwardingCondition".
     */

    if (INAP_CS1_ConnectArg_OptionForwardingCondition(connectArg))
    {
        /*
         *  [7-1] Retrieve reference to ForwardingCondition object.
         */

        const INAP_CS1_ForwardingCondition
            forwardingCondition =
                INAP_CS1_ConnectArg_GetForwardingCondition(
                    connectArg);

        /*
         *  [7-2] Retrieve contents of ForwardingCondition object.
         */

        if (INAP_CS1_ForwardingCondition_IsBusy(forwardingCondition))
        {
            /*
             *  Do something...
             */
        }
        else if (INAP_CS1_ForwardingCondition_IsNoanswer(forwardingCondition))
        {
            /*
             *  Do something...
             */
        }
        else if (INAP_CS1_ForwardingCondition_IsAny(forwardingCondition))
        {
            /*
             *  Do something...
             */
        }
        else
        {
            /*
             *  Not reached (AsnDecodeError has been thrown previously).
             */
        }

        /*
         *  [7-3] Print ForwardingCondition object.
         */

        printf("\nPrinting ForwardingCondition object...\n");
        
        INAP_CS1_ForwardingCondition_Print(forwardingCondition);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [8] Retrieve optional parameter "routeList".
     */

    if (INAP_CS1_ConnectArg_OptionRouteList(connectArg))
    {
        size_t i            = 0;
        size_t paramSize    = 0;

        /*
         *  [8-1] Retrieve const pointer to RouteList object.
         */

        const INAP_CS1_RouteList
            routeList =
                INAP_CS1_ConnectArg_GetRouteList(
                    connectArg);

        /*
         *  INAP API Note: a RouteList object contains a list of 
         *  RouteList_OCTETSTRING objects.
         */

        /*
         *  [8-2] Retrieve contents of RouteList object.
         */

        paramSize = 
            INAP_CS1_RouteList_GetSize(
                routeList);

        for (i = 0; i < paramSize; i++)
        {
            const ITS_OCTET* array  = NULL;
            size_t arraySize        = 0;

            /*
             *  [8-2-1] Retrieve const pointer to RouteList_OCTETSTRING object.
             */

            const INAP_CS1_RouteList_OCTETSTRING
                routeListOCTETSTRING =
                    INAP_CS1_RouteList_GetElementAt(
                        routeList,
                        i);

            /*
             *  [8-2-2] Retrieve contents of RouteList_OCTETSTRING object.
             */

            array =
                INAP_CS1_RouteList_OCTETSTRING_GetArray(
                    routeListOCTETSTRING);

            arraySize =
                INAP_CS1_RouteList_OCTETSTRING_GetSize(
                    routeListOCTETSTRING);

            /*
             *  Do something with array of octets...
             */

            /*
             *  [8-2-3] Print RouteList_OCTETSTRING object.
             */

            printf("\nPrinting RouteList_OCTETSTRING object...\n");

            INAP_CS1_RouteList_OCTETSTRING_Print(routeListOCTETSTRING);

            printf("\n");
        }

        /*
         *  [8-3] Print RouteList object.
         */

        printf("\nPrinting RouteList object...\n");

        INAP_CS1_RouteList_Print(routeList);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [9] Retrieve optional parameter "callingPartyNumber".
     */

    if (INAP_CS1_ConnectArg_OptionCallingPartyNumber(connectArg))
    {
        const ITS_OCTET* array  = NULL;
        size_t arraySize        = 0;

        /*
         *  [9-1] Retrieve const pointer to CallingPartyNumber object.
         */

        const INAP_CS1_CallingPartyNumber
            callingPartyNumber = 
                INAP_CS1_ConnectArg_GetCallingPartyNumber(
                    connectArg);

        /*
         *  [9-2] Retrieve contents of CallingPartyNumber object.
         */

        array = 
            INAP_CS1_CallingPartyNumber_GetArray(
                callingPartyNumber);

        arraySize =
            INAP_CS1_CallingPartyNumber_GetSize(
                callingPartyNumber);

        /*
         *  Do something with array of octets...
         */

        /*
         *  [9-3] Print CallingPartyNumber object.
         */

        printf("\nPrinting CallingPartyNumber object...\n");
        
        INAP_CS1_CallingPartyNumber_Print(callingPartyNumber);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [10] Free all memory allocated on the heap.
     */

    /*
     *  [10-1] Delete octets object.
     */

    ASN_Octets_Destruct(octets);

    /*
     *  [10-2] Delete ConnectArg object.
     */

    INAP_CS1_ConnectArg_Destruct(connectArg);

    /*------------------------------------------------------------------------*/

    /*
     *  Return success.
     */

    return ITS_SUCCESS;
}


/*------------------------------------------------------------------------------
 *
 *  How to Build an INAP InitialDP operation argument (InitialDPArg):
 *
 *  o   Create an InitialDPArg object.
 *
 *  o   Insert data step by step in the created InitialDPArg object (i.e. 
 *      populate various parameters of the InitialDP operation argument).
 *  
 *  o   Encode the InitialDPArg object.
 *
 */

int  
BuildOperationInitialDPArg(ITS_OCTET** octetArray, size_t* size)
{
    INAP_CS1_InitialDPArg initialDPArg  = NULL;
    ASN_Octets octets                   = NULL;
    int res                             = ITS_SUCCESS;

    ASN_C_REQUIRE(octetArray != NULL);
    ASN_C_REQUIRE(size != NULL);
    ASN_C_REQUIRE(*octetArray == NULL);

    /* TODO: to be implemented. */

    return ITS_SUCCESS;
}


/*------------------------------------------------------------------------------
 *
 *  How to interpret an (encoded) INAP InitialDP operation argument 
 *  (InitialDPArg):
 *
 *  o   Decode an InitialDPArg encoded value (i.e. create an InitialDPArg object
 *      from an InitialDPArg encoded value).
 *
 *  o   Retrieve Data from an InitialDPArg object.
 *
 */

int
InterpretOperationInitialDPArg(const ITS_OCTET* octetArray, size_t size)
{
    /* TODO: to be implemented. */

    return ITS_SUCCESS;
}



/*------------------------------------------------------------------------------
 *
 *  Entry point:
 *
 *  o   Initialize IntelliSS7.
 *
 *  o   Call BuildOperationConnectArg function.
 *  
 *  o   Call InterpretOperationConnectArg function.
 *
 *  o   Call BuildOperationInitialDPArg function.
 *
 *  o   Call InterpretOperationInitialDPArg function.
 *  
 *  o   Terminate IntelliSS7.
 *
 */

int main(int argc, char* argv[])
{
    ITS_OCTET* octetArray   = NULL;
    size_t size             = 0;
    int res                 = ITS_SUCCESS;

    printf("\nBegin INAP CS1 ASN.1 codec example...\n");

    /*
     *  Add ASN.1 C runtime feature to IntelliSS7.
     */

    res = ITS_AddFeature(itsASN_C_RUNTIME_Class);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    /*
     *  Add INAP CS1 feature to IntelliSS7.
     */

    res = ITS_AddFeature(itsINAP_CS1_Class);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    /*
     *  IntelliSS7 initialization (including licensing).
     */

    res = ITS_GlobalStart(0);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }
        
    /*------------------------------------------------------------------------*/

    /*
     *  [1] Call BuildOperationConnectArg function.
     */

    res = BuildOperationConnectArg(&octetArray, &size);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    /*
     *  [2] Call InterpretOperationConnectArg function.
     */

    res = InterpretOperationConnectArg(octetArray, size);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    /*
     *  [3] Free memory allocated by BuildOperationConnectArg function.
     */

    free(octetArray);

    octetArray = NULL;
    size = 0;

    /*------------------------------------------------------------------------*/

    /*
     *  [4] Call BuildOperationInitialDPArg function.
     */

    res = BuildOperationInitialDPArg(&octetArray, &size);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    /*
     *  [5] Call InterpretOperationInitialDPArg function.
     */

    res = InterpretOperationInitialDPArg(octetArray, size);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    /*
     *  [6] Free memory allocated by BuildOperationInitialDPArg function.
     */

    free(octetArray);

    octetArray = NULL;
    size = 0;

    /*------------------------------------------------------------------------*/

    /*
     *  IntelliSS7 termination.
     */

    ITS_GlobalStop();

    /*
     *  Remove ASN.1 C runtime feature from IntelliSS7.
     */

    ITS_RemFeature(itsASN_C_RUNTIME_Class);

    /*
     *  Add INAP CS1 feature to IntelliSS7.
     */

    ITS_RemFeature(itsINAP_CS1_Class);


    printf("\nEnd of INAP CS1 ASN.1 codec example.\n");
    
#if defined(WIN32)

    /* To stop here in console application. */

    printf("Type any key to quit...\n");

    {
        char c = getch();
    }
    
#endif /* defined(WIN32) */

    return EXIT_SUCCESS;
}

