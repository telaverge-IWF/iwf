#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <its_ss7_stubs.h>

#include <asn_common.h>

#include <map_v4_its_feature_class_c.h>
#include <map_v4_insert_subscriber_data_arg_c.h>
#if defined(WIN32)

/*
 *  The following macros set and clear, respectively, given bits of the C 
 *  runtime library debug flag, as specified by a bitmask.
 */

#if defined(_DEBUG)

#define  SET_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag((a) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#define  CLEAR_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag(~(a) & _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

#else /* !defined(_DEBUG) */

#define  SET_CRT_DEBUG_FIELD(a)   ((void) 0)
#define  CLEAR_CRT_DEBUG_FIELD(a) ((void) 0)

#endif /* defined(_DEBUG) */

#endif /* defined(WIN32) */

/*------------------------------------------------------------------------------
 *
 *  How to Build a GSMMAP Insert Subscriber Data operation argument 
 *  (InsertSubscriberDataArg):
 *
 *  o   Allocate a pointer insertSubscriberDataArg to 
 *      MAP_V4_InsertSubscriberDataArg_ObjRec.
 *
 *  o   Insert data step by step in the the structure
 *  
 *  o   Return the address and size of the structure.
 *
 *------------------------------------------------------------------------------*/
int
BuildOperationInsertSubscriberDataArg(ITS_OCTET** octetArray, size_t* size)
{
    MAP_V4_InsertSubscriberDataArg insertSubscriberDataArg  = NULL;

    ITS_OCTET array1[] = { 0x01U, 0x02U, 0x03U, 0x04U };
    size_t array1Size = 4;

    ITS_OCTET array2[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U };
    size_t array2Size = 5;

    ITS_OCTET array3[] = { 0x66U };
    size_t array3Size = 1;

    ITS_OCTET array4[] = { 0xAAU };
    size_t array4Size = 1;

    ITS_OCTET array5[] = { 0xBBU };
    size_t array5Size = 1;

    ITS_OCTET array6[] = { 0xCCU };
    size_t array6Size = 1;

    ITS_OCTET array7[] = { 0xDDU };
    size_t array7Size = 1;

    ITS_OCTET array8[] = { 0xEEU };
    size_t array8Size = 1;

    ITS_OCTET array9[] = { 0x33U };
    size_t array9Size = 1;

    ITS_OCTET array10[] = { 0x44U };
    size_t array10Size = 1;

    ITS_OCTET array11[] = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };
    size_t array11Size = 8;

    ITS_OCTET array12[] = { 0x11U, 0x22U, 0x33U, 0x44U };
    size_t array12Size = 4;

    ITS_OCTET array13[] = { 0x44U, 0x33U, 0x22U, 0x11U };
    size_t array13Size = 4;

    ITS_BOOLEAN array14[] = { ITS_TRUE, ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE, 
                              ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE, ITS_FALSE,
                              ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE, ITS_FALSE };
    size_t array14Size = 15;

    ITS_BOOLEAN array15[] = { ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE };
    size_t array15Size = 4;

    /* Local variables used for encoding and decoding. */

    ASN_Octets octets                   = NULL;
    ASN_EncodeError encodeError         = NULL;
    ASN_DecodeError decodeError         = NULL;

    int res                             = ITS_SUCCESS;

    int encodeErrorCode                 = ITS_SUCCESS;
    const char* encodeErrorText         = NULL;
    const char* encodeExtendedErrorText = NULL;

    /*------------------------------------------------------------------------*/
    /* Populate ASN.1 object to encode.                                       */
    /*------------------------------------------------------------------------*/

    insertSubscriberDataArg = MAP_V4_InsertSubscriberDataArg_ConstructDefault();

    if (insertSubscriberDataArg == NULL)
    {
        return ITS_ENOMEM;
    }

    /* Set imsi. */
    {
        MAP_V4_IMSI imsi = NULL;

        imsi = MAP_V4_TBCD_STRING_ConstructWithArraySize(array1, array1Size);

        if (imsi == NULL)
        {
            return ITS_ENOMEM;
        }

        MAP_V4_InsertSubscriberDataArg_SetImsi(insertSubscriberDataArg, imsi);
    }

    /* Set category. */
    {
        MAP_V4_Category category = NULL;

        category = MAP_V4_Category_ConstructWithArraySize(
                                                        array3,
                                                        array3Size);

        if (category == NULL)
        {
            return ITS_ENOMEM;
        }

        MAP_V4_InsertSubscriberDataArg_SetCategory(
                                        insertSubscriberDataArg, 
                                        category);
    } 

    /* Set subscriberStatus. */
    {
        MAP_V4_SubscriberStatus subscriberStatus = NULL;

        subscriberStatus = MAP_V4_SubscriberStatus_ConstructDefault();

        if (subscriberStatus == NULL)
        {
            return ITS_ENOMEM;
        }

        MAP_V4_SubscriberStatus_SetServiceGranted(subscriberStatus);

        MAP_V4_InsertSubscriberDataArg_SetSubscriberStatus(
                                            insertSubscriberDataArg,
                                            subscriberStatus);
    }

    /* Set bearerServiceList. */
    {
        MAP_V4_BearerServiceList bearerServiceList = NULL;

        bearerServiceList = MAP_V4_BearerServiceList_ConstructDefault();

        if (bearerServiceList == NULL)
        {
            return ITS_ENOMEM;
        }

        /* Insert first elements (type BearerServiceCode). */
        {
            MAP_V4_Ext_BearerServiceCode bearerServiceCode1 = NULL;

            bearerServiceCode1 = 
                MAP_V4_Ext_BearerServiceCode_ConstructWithArraySize(
                                                                array4,
                                                                array4Size);

            if (bearerServiceCode1 == NULL)
            {
                return ITS_ENOMEM;
            }

            res = MAP_V4_BearerServiceList_AddElement(
                                                bearerServiceList, 
                                                bearerServiceCode1);

            if (res != ITS_SUCCESS)
            {
                return res;
            }
        }

        /* Insert second elements (type BearerServiceCode). */
        {
            MAP_V4_Ext_BearerServiceCode bearerServiceCode2 = NULL;

            bearerServiceCode2 = 
                MAP_V4_Ext_BearerServiceCode_ConstructWithArraySize(
                                                                array5,
                                                                array5Size);

            if (bearerServiceCode2 == NULL)
            {
                return ITS_ENOMEM;
            }

            res = MAP_V4_BearerServiceList_AddElement(
                                                bearerServiceList,
                                                bearerServiceCode2);

            if (res != ITS_SUCCESS)
            {
                return res;
            }
        }

        MAP_V4_InsertSubscriberDataArg_SetBearerServiceList(
                                                insertSubscriberDataArg,
                                                bearerServiceList);
    }

    /* Set teleserviceList. */
    {
        MAP_V4_TeleserviceList teleserviceList = NULL;

        teleserviceList = MAP_V4_TeleserviceList_ConstructDefault();

        if (teleserviceList == NULL)
        {
            return ITS_ENOMEM;
        }

        /* Set teleserviceCode1 */
        {
            MAP_V4_Ext_TeleserviceCode teleserviceCode1 = NULL;

            teleserviceCode1 = 
                MAP_V4_Ext_TeleserviceCode_ConstructWithArraySize(
                                                                array6,
                                                                array6Size);

            if (teleserviceCode1 == NULL)
            {
                return ITS_ENOMEM;
            }

            res = MAP_V4_TeleserviceList_AddElement(
                                                teleserviceList, 
                                                teleserviceCode1);

            if (res != ITS_SUCCESS)
            {
                return res;
            }
        }

        /* Set teleserviceCode2 */
        {
            MAP_V4_Ext_TeleserviceCode teleserviceCode2 = NULL;

            teleserviceCode2 = 
                MAP_V4_Ext_TeleserviceCode_ConstructWithArraySize(
                                                            array7,
                                                            array7Size);

            if (teleserviceCode2 == NULL)
            {
                return ITS_ENOMEM;
            }

            res = MAP_V4_TeleserviceList_AddElement(teleserviceList, teleserviceCode2);

            if (res != ITS_SUCCESS)
            {
                return res;
            }

        }

        /* Set teleserviceCode3 */
        {
            MAP_V4_Ext_TeleserviceCode teleserviceCode3 = NULL;

            teleserviceCode3 = MAP_V4_Ext_TeleserviceCode_ConstructWithArraySize(
                                                            array8,
                                                            array8Size);

            if (teleserviceCode3 == NULL)
            {
                return ITS_ENOMEM;
            }

            res = MAP_V4_TeleserviceList_AddElement(teleserviceList, teleserviceCode3);

            if (res != ITS_SUCCESS)
            {
                return res;
            }
        }

        MAP_V4_InsertSubscriberDataArg_SetTeleserviceList(
                                                    insertSubscriberDataArg,
                                                    teleserviceList);
    }

    /* Set provisionedSS (type SS_InfoList). */
    {
        MAP_V4_Ext_SS_InfoList ext_SS_InfoList = NULL;

        ext_SS_InfoList = MAP_V4_Ext_SS_InfoList_ConstructDefault();

        if (ext_SS_InfoList == NULL)
        {
            return ITS_ENOMEM;
        }

        /* Insert 2 elements (type SS_Info). */
        /* First ext_SS_Info1. */
        {
            MAP_V4_Ext_SS_Info ext_SS_Info1 = NULL;

            ext_SS_Info1 = MAP_V4_Ext_SS_Info_ConstructDefault();

            if (ext_SS_Info1 == NULL)
            {
                return ITS_ENOMEM;
            }

            /* First element choice is forwardingInfo. */
            {
                MAP_V4_Ext_ForwInfo forwardingInfo = NULL;

                forwardingInfo = MAP_V4_Ext_ForwInfo_ConstructDefault();

                if (forwardingInfo == NULL)
                {
                    return ITS_ENOMEM;
                }

                /* Set sS_Code */
                {
                    MAP_V4_SS_Code sS_Code = NULL;
                    sS_Code = MAP_V4_SS_Code_ConstructWithArraySize(
                                                                array9,
                                                                array9Size);

                    if (sS_Code == NULL)
                    {
                        return ITS_ENOMEM;
                    }

                    MAP_V4_Ext_ForwInfo_SetSs_Code(forwardingInfo, sS_Code);
                }

                /* Set forwardingFeatureList */
                {
                    MAP_V4_Ext_ForwFeatureList forwardingFeatureList = NULL;

                    forwardingFeatureList = 
                        MAP_V4_Ext_ForwFeatureList_ConstructDefault();

                    if (forwardingFeatureList == NULL)
                    {
                        return ITS_ENOMEM;
                    }
                
                    /* Insert 1 element (type ForwardingFeature). */
                    {
                        MAP_V4_Ext_ForwFeature forwardingFeature = NULL;

                        forwardingFeature = 
                            MAP_V4_Ext_ForwFeature_ConstructDefault();

                        /* Set basicServiceCode. */
                        {
                            MAP_V4_Ext_BasicServiceCode basicServiceCode 
                                                                    = NULL;
                            basicServiceCode = 
                                MAP_V4_Ext_BasicServiceCode_ConstructDefault();

                            if (basicServiceCode == NULL)
                            {
                                return ITS_ENOMEM;
                            }

                            /* Set bearerServiceCode. */
                            {
                                MAP_V4_Ext_BearerServiceCode bearerServiceCode
                                                                    = NULL;

                                bearerServiceCode = MAP_V4_Ext_BearerServiceCode_ConstructWithArraySize(
                                                array10,
                                                array10Size);

                                if (bearerServiceCode == NULL)
                                {
                                    return ITS_ENOMEM;
                                }

                                MAP_V4_Ext_BasicServiceCode_SetChoiceExt_BearerService(
                                                        basicServiceCode, 
                                                        bearerServiceCode);
                            }

                            MAP_V4_Ext_ForwFeature_SetBasicService(
                                                        forwardingFeature,
                                                        basicServiceCode);
                        }

                        /* Set ext_SS_Status */
                        {
                            MAP_V4_Ext_SS_Status ext_SS_Status = NULL;

                            ext_SS_Status = 
                                MAP_V4_Ext_SS_Status_ConstructWithArraySize(
                                                                        array10,
                                                                        array10Size);

                            if(ext_SS_Status == NULL)
                            {
                                return ITS_ENOMEM;
                            }

                            MAP_V4_Ext_ForwFeature_SetSs_Status(
                                                        forwardingFeature, 
                                                        ext_SS_Status);
                        }
                        /* Set iSDN_SubaddressString. */
                        {
                            MAP_V4_ISDN_SubaddressString iSDN_SubaddressString
                                                                    = NULL;

                            iSDN_SubaddressString = 
                                MAP_V4_ISDN_SubaddressString_ConstructWithArraySize(
                                                            array11,
                                                            array11Size);

                            if (iSDN_SubaddressString == NULL)
                            {
                                return ITS_ENOMEM;
                            }

                            MAP_V4_Ext_ForwFeature_SetForwardedToSubaddress(
                                                        forwardingFeature, 
                                                        iSDN_SubaddressString);
                        }

                        res = MAP_V4_Ext_ForwFeatureList_AddElement(
                                                                forwardingFeatureList,
                                                                forwardingFeature);

                        if (res != ITS_SUCCESS)
                        {
                            return res;
                        }
                    }

                    MAP_V4_Ext_ForwInfo_SetForwardingFeatureList(
                                                        forwardingInfo,
                                                        forwardingFeatureList);
                }

                MAP_V4_Ext_SS_Info_SetChoiceForwardingInfo(
                                                        ext_SS_Info1,
                                                        forwardingInfo);
            }

            res = MAP_V4_Ext_SS_InfoList_AddElement(
                                                ext_SS_InfoList,
                                                ext_SS_Info1);

            if (res != ITS_SUCCESS)
            {
                return res;
            }
        }
        
        /* Second element. */
        {
            MAP_V4_Ext_SS_Info ext_SS_Info2 = NULL;

            ext_SS_Info2 = MAP_V4_Ext_SS_Info_ConstructDefault();

            if (ext_SS_Info2 == NULL)
            {
                return ITS_ENOMEM;
            }

            /* Second element choice is cug-Info. */
            {
                MAP_V4_CUG_Info cUG_Info = NULL;

                cUG_Info = MAP_V4_CUG_Info_ConstructDefault();

                if (cUG_Info == NULL)
                {
                    return ITS_ENOMEM;
                }

                /* Set CUG-SubscriptionList. */
                {
                    MAP_V4_CUG_SubscriptionList cUG_SubscriptionList = NULL;

                    cUG_SubscriptionList = MAP_V4_CUG_SubscriptionList_ConstructDefault();

                    if (cUG_SubscriptionList == NULL)
                    {
                        return ITS_ENOMEM;
                    }

                    MAP_V4_CUG_Info_SetCug_SubscriptionList(
                                                        cUG_Info,
                                                        cUG_SubscriptionList);
                }

                MAP_V4_Ext_SS_Info_SetChoiceCug_Info(
                                                ext_SS_Info2,
                                                cUG_Info);
            }

            res = MAP_V4_Ext_SS_InfoList_AddElement(
                                                ext_SS_InfoList,
                                                ext_SS_Info2);

            if (res != ITS_SUCCESS)
            {
                return res;
            }
        }

        MAP_V4_InsertSubscriberDataArg_SetProvisionedSS(
                                                insertSubscriberDataArg, 
                                                ext_SS_InfoList);
    }

    /* Set odb-Data. */
    {
        MAP_V4_ODB_Data oDB_Data = NULL;

        oDB_Data = MAP_V4_ODB_Data_ConstructDefault();

        if (oDB_Data == NULL)
        {
            return ITS_ENOMEM;
        }

        /* Set oDB_GeneralData, oDB_HPLMN_Data. */
        {
            MAP_V4_ODB_GeneralData oDB_GeneralData  = NULL;
            MAP_V4_ODB_HPLMN_Data oDB_HPLMN_Data = NULL;

            oDB_GeneralData = MAP_V4_ODB_GeneralData_ConstructWithArraySize(
                                                                    array14, 
                                                                    array14Size);

            if (oDB_GeneralData == NULL)
            {
                return ITS_ENOMEM;
            }


            MAP_V4_ODB_Data_SetOdb_GeneralData(oDB_Data, oDB_GeneralData);

            oDB_HPLMN_Data = MAP_V4_ODB_HPLMN_Data_ConstructWithArraySize(
                                                            array15,
                                                            array15Size);

            if (oDB_HPLMN_Data == NULL)
            {
                return ITS_ENOMEM;
            }
        
            MAP_V4_ODB_Data_SetOdb_HPLMN_Data(oDB_Data, oDB_HPLMN_Data);

        }

        MAP_V4_InsertSubscriberDataArg_SetOdb_Data(
                                    insertSubscriberDataArg, 
                                    oDB_Data);
        }

    /*------------------------------------------------------------------------*/
    /* Encode ASN.1 object.                                                   */
    /*------------------------------------------------------------------------*/

    res = MAP_V4_InsertSubscriberDataArg_Encode(
                                insertSubscriberDataArg, 
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


        /* Retrieve and print encode error code. */

        encodeErrorCode = 
            ASN_EncodeError_GetError(encodeError);

        printf(
            "\nEncode error code is <%d>.\n\n", 
            encodeErrorCode);


        /* 
         *  Retrieve and print encode error text (freed automatically when the
         *  encodeError object is destructed).                               
         */

        encodeErrorText = 
            ASN_EncodeError_GetErrorText(encodeError);

        if (encodeErrorText == NULL)
        {
            /* Error: out of memory. */
        }

        printf(
            "\nEncode error text is <%s>.\n\n", 
            encodeErrorText);


        /* 
         *  Retrieve and print extended encode error text (freed automatically
         *  when the encodeError object is destructed).
         */

        encodeExtendedErrorText = 
            ASN_EncodeError_GetExtentedErrorText(encodeError);

        printf(
            "\nEncode error extended text is <%s>.\n\n", 
            encodeExtendedErrorText);


        /* Object encodeError must be destructed by end-user. */

        ASN_EncodeError_Destruct(encodeError);


        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

        return res;
    }
    else if (res != ITS_SUCCESS)
    {
        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

        return res;
    }

    /*------------------------------------------------------------------------*/
    /* Print contents of ASN.1 encoded value.                                 */
    /*------------------------------------------------------------------------*/

    printf("\nPrinting ASN.1 encoded value...\n\n");

    ASN_Octets_Print(octets);

    printf("\n");

    *size = ASN_Octets_GetSize(octets);

    /* return address has to be dynamically allocated */
    *octetArray = (ITS_OCTET*)calloc(ASN_Octets_GetSize(octets), sizeof(ITS_OCTET));

    if (*octetArray == NULL)
    {
        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);
        ASN_Octets_Destruct(octets);

        return ITS_ENOMEM;
    }

    memcpy(*octetArray, ASN_Octets_GetArray(octets), ASN_Octets_GetSize(octets));

    MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);
    ASN_Octets_Destruct(octets);

    return ITS_SUCCESS;
}

/*------------------------------------------------------------------------------
 *
 *  o   Allocate a pointer insertSubscriberDataArg to 
 *      MAP_V4_InsertSubscriberDataArg_ObjRec.
 *
 *  o   Construct an ASN_Octets object from the array.
 *
 *  o   Decode the ASN_Octets object into parameter list 
 *      -> insertSubscriberDataArgAfter
 *
 *  o   Printf the decoded object
 *
 *------------------------------------------------------------------------------*/
int
InterpretOperationInsertSubscriberDataArg(ITS_OCTET** octetArray, size_t* size)
{
    ASN_EncodeError encodeError         = NULL;
    ASN_DecodeError decodeError         = NULL;
    const char* encodeErrorText         = NULL;
    const char* encodeExtendedErrorText = NULL;
    const char* decodeErrorText         = NULL;
    const char* decodeExtendedErrorText = NULL;
    ASN_Octets octets                   = NULL;
    int res                             = ITS_SUCCESS;
    int encodeErrorCode                 = ITS_SUCCESS;
    int decodeErrorCode                 = ITS_SUCCESS;

    MAP_V4_InsertSubscriberDataArg insertSubscriberDataArgAfter = NULL;

    octets = ASN_Octets_ConstructWithArray(*octetArray, *size);

    insertSubscriberDataArgAfter = MAP_V4_InsertSubscriberDataArg_ConstructDefault();

    if (insertSubscriberDataArgAfter == NULL)
    {
        return ITS_ENOMEM;
    }

    res = MAP_V4_InsertSubscriberDataArg_Decode(
                                insertSubscriberDataArgAfter, 
                                octets, 
                                &decodeError);

    if (res == ITS_E_ASN_DECODE_ERROR)
    {
        /* 
         *  Status:                                                   
         *                                                            
         *  encodeError != NULL. Must be destructed by end-user.       
         */


        /* Retrieve and print decode error code. */

        decodeErrorCode = 
            ASN_DecodeError_GetError(decodeError);

        fprintf(
            stderr, 
            "\nDecode error code is <%d>.\n\n", 
            decodeErrorCode);


        /* 
         *  Retrieve and print decode error text (freed automatically when the
         *  decodeError object is destructed).                             
         */

        decodeErrorText = 
            ASN_DecodeError_GetErrorText(decodeError);

        if (decodeErrorText == NULL)
        {
            /* Error: out of memory. */
        }

        fprintf(
            stderr, 
            "\nDecode error text is <%s>.\n\n", 
            decodeErrorText);


        /* 
         *  Retrieve and print extended decode error text (freed automatically
         *  when the decodeError object is destructed).                       
         */

        decodeExtendedErrorText = 
            ASN_DecodeError_GetExtentedErrorText(decodeError);

        fprintf(
            stderr, 
            "\nDecode error extended text is <%s>.\n\n", 
            decodeExtendedErrorText);


        /* Object decodeError must be destructed by end-user. */

        ASN_DecodeError_Destruct(decodeError);


        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArgAfter);

        ASN_Octets_Destruct(octets);

        return res;
    }
    else if (res != ITS_SUCCESS)
    {
        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArgAfter);

        ASN_Octets_Destruct(octets);

        return res;
    }
    else
    {
        /* res == ITS_SUCCESS. Nothing to do. Continue processing. */
    }


    /*------------------------------------------------------------------------*/
    /* Show how to retrieve data from ASN.1 decoded object.                   */
    /*------------------------------------------------------------------------*/

    /* To be done. */


    /*------------------------------------------------------------------------*/
    /* Print contents of ASN.1 decoded object.                                */
    /*------------------------------------------------------------------------*/

    printf("\nPrinting decoded InsertSubscriberDataArg...\n\n");

    MAP_V4_InsertSubscriberDataArg_Print(insertSubscriberDataArgAfter);

    printf("\n");


    /*------------------------------------------------------------------------*/
    /* Release all the memory.                                                */
    /*------------------------------------------------------------------------*/

    MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArgAfter);

    ASN_Octets_Destruct(octets);

    return ITS_SUCCESS;
}


/*------------------------------------------------------------------------------
 *
 *  Entry point:
 *
 *  o   Initialize IntelliSS7.
 *
 *  o   Call BuildOperationInsertSubscriberDataArg function.
 *  
 *  o   Call EncodeParameter function.
 *  
 *  o   Call InterpretOperationInsertSubscriberDataArg function.
 *
 *  o   Terminate IntelliSS7.
 *
 *------------------------------------------------------------------------------*/
int 
main(int argc, char** argv)
{
    int res = ITS_SUCCESS;
    size_t size = 0;
    ITS_OCTET *encodedInsertSubscriberDataArg = NULL;

    printf("\nBegin GSM MAP ASN.1 codec example...\n");

    res = ITS_AddFeature(itsASN_C_RUNTIME_Class);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    res = ITS_AddFeature(itsMAP_V4_Class);

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
        printf("\nITS_GlobalStart() failed!");
        exit(0);
    }

    /*  [1] Call BuildOperationInsertSubscriberDataArg function. */
  
    printf("\nBuild & Encode Operation InsertSubscriberData.\n\n");
    BuildOperationInsertSubscriberDataArg(&encodedInsertSubscriberDataArg, &size);

    /*  [2] Call InterpretOperationInsertSubscriberDataArg function. */

    printf("\nDecode Operation InsertSubscriberData.\n\n");
    InterpretOperationInsertSubscriberDataArg(&encodedInsertSubscriberDataArg, &size);

    // IntelliSS7 termination.

    ITS_GlobalStop();

    ITS_RemFeature(itsASN_C_RUNTIME_Class);

    ITS_RemFeature(itsMAP_V4_Class);

    printf("\nEnd of GSM MAP ASN.1 codec example.\n");
    

    // To stop here in console application.

    printf("\nPress Enter to quit...\n");

    getchar();

    return EXIT_SUCCESS;
}
