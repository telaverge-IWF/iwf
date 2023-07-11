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
 *  ID: $Id: test_codec_main.c,v 9.1 2005/03/23 12:51:34 cvsadmin Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  MAP V4 ASN.1 codec example.
 *
 *  This example shows how to build (create, insert data and encode) and how
 *  to interpret (decode and retrieve data) for the following MAP operation
 *  argument:
 *
 *  o   InsertSubscriberDataArg.
 *
 *  o   ...
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

#include <map_v4_its_feature_class_c.h>
#include <map_v4_insert_subscriber_data_arg_c.h>



/*------------------------------------------------------------------------------
 *
 *  How to Build an Insert Subscriber Data operation argument 
 *  (MAP_V4_InsertSubscriberDataArg):
 *
 *  o   Create an InsertSubscriberDataArg object.
 *
 *  o   Insert data step by step in the created InsertSubscriberDataArg object
 *      (i.e. populate various parameters of the Insert Subscriber Data
 *      operation argument).
 *
 *  o   Encode the InsertSubscriberDataArg object to produce an
 *      InsertSubscriberDataArg encoded value.
 *
 */

int
BuildOperationInsertSubscriberDataArg(ITS_OCTET** octetArray, size_t* size)
{
    MAP_V4_InsertSubscriberDataArg insertSubscriberDataArg  = NULL;
    ASN_Octets octets                                       = NULL;
    int res                                                 = ITS_SUCCESS;

    /* 
     *  Sample data used for encoding. 
     */

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

    ITS_OCTET array10[] = { 0x22U, 0x22U, 0x22U };
    size_t array10Size = 3;

    ITS_OCTET array11[] = { 0x44U };
    size_t array11Size = 1;

    ITS_OCTET array12[] = { 0x01U, 0x02U, 0x03U, 0x04U,
                            0x05U, 0x06U, 0x07U, 0x08U };
    size_t array12Size = 8;

    ITS_OCTET array13[] = { 0x11U, 0x22U, 0x33U, 0x44U };
    size_t array13Size = 4;

    ITS_OCTET array14[] = { 0x44U, 0x33U, 0x22U, 0x11U };
    size_t array14Size = 4;

    ITS_OCTET array15[] = { 0x11U };
    size_t array15Size = 1;

    ITS_OCTET array16[] = { 0x22U, 0x22U };
    size_t array16Size = 2;

    ITS_BOOLEAN array17[] = { ITS_TRUE, ITS_FALSE, ITS_TRUE, ITS_FALSE, 
                              ITS_TRUE, ITS_FALSE, ITS_TRUE, ITS_FALSE,
                              ITS_TRUE, ITS_FALSE, ITS_FALSE, ITS_TRUE,
                              ITS_FALSE, ITS_TRUE, ITS_FALSE };
    size_t array17Size = 15;

    ITS_BOOLEAN array18[] = { ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE };
    size_t array18Size = 4;

    ASN_C_REQUIRE(octetArray != NULL);
    ASN_C_REQUIRE(size != NULL);
    ASN_C_REQUIRE(*octetArray == NULL);

    /*
     *  [1] Create InsertSubscriberDataArg object.
     */

    insertSubscriberDataArg = MAP_V4_InsertSubscriberDataArg_ConstructDefault();

    if (insertSubscriberDataArg == NULL)
    {
        return ITS_ENOMEM;
    }

    /*------------------------------------------------------------------------*/

    /*
     *  Memory management note: all the following parameter objects that are
     *  used to populate the InsertSubscriberDataArg object are created in the
     *  heap using the appropriate construct function. They are automatically
     *  deleted (i.e. all associated memory released) when the 
     *  InsertSubscriberDataArg object is deleted. 
     */

    /*------------------------------------------------------------------------*/

    /*
     *  [2] Populate optional parameter "imsi".
     */

    {
        /*
         *  [2-1] Create IMSI object.
         */

        MAP_V4_IMSI 
            imsi = 
                MAP_V4_IMSI_ConstructWithArraySize(array1, array1Size);

        if (imsi == NULL)
        {
            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

            return ITS_ENOMEM;
        }

        /*
         *  [2-2] Set IMSI object in InsertSubscriberDataArg object.
         */

        MAP_V4_InsertSubscriberDataArg_SetImsi(insertSubscriberDataArg, imsi);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [3] Populate optional parameter "msisdn".
     */

    {
        /*
         *  [3-1] Create ISDN_AddressString object.
         */

        MAP_V4_ISDN_AddressString 
            iSDN_AddressString =
                MAP_V4_ISDN_AddressString_ConstructWithArraySize(
                    array2,
                    array2Size);

        if (iSDN_AddressString == NULL)
        {
            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

            return ITS_ENOMEM;
        }

        /*
         *  [3-2] Set ISDN_AddressString object in InsertSubscriberDataArg
         *  object.
         */

        MAP_V4_InsertSubscriberDataArg_SetMsisdn(
            insertSubscriberDataArg, 
            iSDN_AddressString);
    }

    /*------------------------------------------------------------------------*/

    /* 
     *  [4] Populate optional parameter "category".
     */

    {
        /*
         *  [4-1] Create Category object.
         */

        MAP_V4_Category 
            category = 
                MAP_V4_Category_ConstructWithArraySize(
                    array3,
                    array3Size);

        if (category == NULL)
        {
            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

            return ITS_ENOMEM;
        }

        /* 
         *  [4-2] Set Category object in InsertSubscriberDataArg object.
         */

        MAP_V4_InsertSubscriberDataArg_SetCategory(
            insertSubscriberDataArg, 
            category);
    } 

    /*------------------------------------------------------------------------*/

    /* 
     *  [5] Populate optional parameter "subscriberStatus".
     */

    {
        /*
         *  [5-1] Create SubscriberStatus object.
         */

        MAP_V4_SubscriberStatus 
            subscriberStatus = 
                MAP_V4_SubscriberStatus_ConstructDefault();

        if (subscriberStatus == NULL)
        {
            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

            return ITS_ENOMEM;
        }

        MAP_V4_SubscriberStatus_SetServiceGranted(subscriberStatus);

        /*
         *  [5-2] Set SubscriberStatus object in InsertSubscriberDataArg object.
         */

        MAP_V4_InsertSubscriberDataArg_SetSubscriberStatus(
            insertSubscriberDataArg,
            subscriberStatus);
    }

    /*------------------------------------------------------------------------*/

    /* 
     *  [6] Populate optional parameter "bearerServiceList". 
     */

    {
        /*
         *  [6-1] Create BearerServiceList object.
         */

        MAP_V4_BearerServiceList 
            bearerServiceList = 
                MAP_V4_BearerServiceList_ConstructDefault();

        if (bearerServiceList == NULL)
        {
            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

            return ITS_ENOMEM;
        }

        /*  
         *  MAP API Note: a BearerServiceList object contains a list of 
         *  Ext_BearerServiceCode objects.
         */

        {
            /*
             *  [6-1-1] Create Ext_BearerServiceCode object.
             */

            MAP_V4_Ext_BearerServiceCode 
                bearerServiceCode =
                    MAP_V4_Ext_BearerServiceCode_ConstructWithArraySize(
                        array4,
                        array4Size);

            if (bearerServiceCode == NULL)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_BearerServiceList_Destruct(bearerServiceList);

                return ITS_ENOMEM;
            }

            /*
             *  [6-1-2] Add Ext_BearerServiceCode object to BearerServiceList
             *  object.
             */

            res = 
                MAP_V4_BearerServiceList_AddElement(
                    bearerServiceList, 
                    bearerServiceCode);

            if (res != ITS_SUCCESS)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_BearerServiceList_Destruct(bearerServiceList);
                MAP_V4_Ext_BearerServiceCode_Destruct(bearerServiceCode);

                return res;
            }
        }

        {
            /*
             *  [6-2-1] Create Ext_BearerServiceCode object. 
             */

            MAP_V4_Ext_BearerServiceCode 
                bearerServiceCode2 = 
                    MAP_V4_Ext_BearerServiceCode_ConstructWithArraySize(
                        array5,
                        array5Size);

            if (bearerServiceCode2 == NULL)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_BearerServiceList_Destruct(bearerServiceList);

                return ITS_ENOMEM;
            }

            /*
             *  [6-2-2] Add Ext_BearerServiceCode object to BearerServiceList
             *  object. 
             */

            res = 
                MAP_V4_BearerServiceList_AddElement(
                    bearerServiceList,
                    bearerServiceCode2);

            if (res != ITS_SUCCESS)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_BearerServiceList_Destruct(bearerServiceList);
                MAP_V4_Ext_BearerServiceCode_Destruct(bearerServiceCode2);

                return res;
            }
        }

        /*
         *  Set BearerServiceList object in InsertSubscriberDataArg object.
         */

        MAP_V4_InsertSubscriberDataArg_SetBearerServiceList(
            insertSubscriberDataArg,
            bearerServiceList);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [7] Populate optional parameter "teleserviceList".
     */

    {
        /*
         *  [7-1] Create TeleserviceList object.
         */

        MAP_V4_TeleserviceList 
            teleserviceList = 
                MAP_V4_TeleserviceList_ConstructDefault();

        if (teleserviceList == NULL)
        {
            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

            return ITS_ENOMEM;
        }

        /*
         *  MAP API Note: a TeleServiceList object contains a list of 
         *  Ext_TeleServiceCode objects.
         */

        {
            /*
             *  [7-1-1] Create Ext_TeleserviceCode object.
             */

            MAP_V4_Ext_TeleserviceCode 
                teleserviceCode = 
                    MAP_V4_Ext_TeleserviceCode_ConstructWithArraySize(
                        array6,
                        array6Size);

            if (teleserviceCode == NULL)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_TeleserviceList_Destruct(teleserviceList);

                return ITS_ENOMEM;
            }

            /*
             *  [7-1-2] Add Ext_TeleserviceCode object to TeleserviceList 
             *  object.
             */

            res = 
                MAP_V4_TeleserviceList_AddElement(
                    teleserviceList, 
                    teleserviceCode);

            if (res != ITS_SUCCESS)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_TeleserviceList_Destruct(teleserviceList);
                MAP_V4_Ext_TeleserviceCode_Destruct(teleserviceCode);

                return res;
            }
        }

        {
            /*
             *  [7-1-3] Create Ext_TeleserviceCode object.
             */

            MAP_V4_Ext_TeleserviceCode
                teleserviceCode = 
                    MAP_V4_Ext_TeleserviceCode_ConstructWithArraySize(
                        array7,
                        array7Size);

            if (teleserviceCode == NULL)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_TeleserviceList_Destruct(teleserviceList);

                return ITS_ENOMEM;
            }

            /*
             *  [7-1-4] Add Ext_TeleserviceCode object to TeleserviceList 
             *  object.
             */

            res = 
                MAP_V4_TeleserviceList_AddElement(
                    teleserviceList, 
                    teleserviceCode);

            if (res != ITS_SUCCESS)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_TeleserviceList_Destruct(teleserviceList);
                MAP_V4_Ext_TeleserviceCode_Destruct(teleserviceCode);

                return res;
            }

        }

        {
            /*
             *  [7-1-5] Create Ext_TeleserviceCode object.
             */

            MAP_V4_Ext_TeleserviceCode 
                teleserviceCode = 
                    MAP_V4_Ext_TeleserviceCode_ConstructWithArraySize(
                        array8,
                        array8Size);

            if (teleserviceCode == NULL)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_TeleserviceList_Destruct(teleserviceList);

                return ITS_ENOMEM;
            }

            /*
             *  [7-1-6] Add Ext_TeleserviceCode object to TeleserviceList 
             *  object.
             */

            res = 
                MAP_V4_TeleserviceList_AddElement(
                    teleserviceList, 
                    teleserviceCode);

            if (res != ITS_SUCCESS)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_TeleserviceList_Destruct(teleserviceList);
                MAP_V4_Ext_TeleserviceCode_Destruct(teleserviceCode);

                return res;
            }
        }

        /*
         *  [7-2] Set TeleserviceList object in InsertSubscriberDataArg object.
         */

        MAP_V4_InsertSubscriberDataArg_SetTeleserviceList(
            insertSubscriberDataArg,
            teleserviceList);
    }

    /*------------------------------------------------------------------------*/

    /* 
     *  [8] Populate optional parameter "provisionedSS".
     */

    {
        /*
         *  [8-1] Create Ext_SS_InfoList object.
         */

        MAP_V4_Ext_SS_InfoList 
            ext_SS_InfoList = 
                MAP_V4_Ext_SS_InfoList_ConstructDefault();

        if (ext_SS_InfoList == NULL)
        {
            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

            return ITS_ENOMEM;
        }

        /*  
         *  MAP API Note: an Ext_SS_InfoList object contains a list of 
         *  Ext_SS_Info objects.
         */

        {
            /*
             *  [8-1-1] Create Ext_SS_Info object.
             */

            MAP_V4_Ext_SS_Info 
                ext_SS_Info = 
                    MAP_V4_Ext_SS_Info_ConstructDefault();

            if (ext_SS_Info == NULL)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_Ext_SS_InfoList_Destruct(ext_SS_InfoList);

                return ITS_ENOMEM;
            }

	        /*  
             *  MAP API Note: an Ext-SS-Info object contains a choice of
	         *  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or 
             *  EMLPP-Info.
             */

            {

                /*
                 *  Choice is forwardingInfo (type Ext_ForwInfo).
                 */

                /*
                 *  [8-1-1-1] Create Ext_ForwInfo object.
                 */

                MAP_V4_Ext_ForwInfo 
                    ext_ForwInfo = 
                        MAP_V4_Ext_ForwInfo_ConstructDefault();

                if (ext_ForwInfo == NULL)
                {
                    MAP_V4_InsertSubscriberDataArg_Destruct(
                        insertSubscriberDataArg);
                    MAP_V4_Ext_SS_InfoList_Destruct(
                        ext_SS_InfoList);
                    MAP_V4_Ext_SS_Info_Destruct(
                        ext_SS_Info);

                    return ITS_ENOMEM;
                }

                {
                    /*
                     *  [8-1-1-1-1] Create SS_Code object.
                     */

                    MAP_V4_SS_Code 
                        sS_Code =
                            MAP_V4_SS_Code_ConstructWithArraySize(
                                array9,
                                array9Size);

                    if (sS_Code == NULL)
                    {
                        MAP_V4_InsertSubscriberDataArg_Destruct(
                            insertSubscriberDataArg);
                        MAP_V4_Ext_SS_InfoList_Destruct(
                            ext_SS_InfoList);
                        MAP_V4_Ext_SS_Info_Destruct(
                            ext_SS_Info);
                        MAP_V4_Ext_ForwInfo_Destruct(
                            ext_ForwInfo);

                        return ITS_ENOMEM;
                    }

                    /*
                     *  [8-1-1-1-2] Set SS_Code object in Ext_ForwInfo object.
                     */

                    MAP_V4_Ext_ForwInfo_SetSs_Code(
                        ext_ForwInfo, 
                        sS_Code);
                }

                {
                    /*
                     *  [8-1-1-1-3] Create Ext_ForwFeatureList object.
                     */

                    MAP_V4_Ext_ForwFeatureList 
                        ext_ForwFeatureList = 
                            MAP_V4_Ext_ForwFeatureList_ConstructDefault();

                    if (ext_ForwFeatureList == NULL)
                    {
                        MAP_V4_InsertSubscriberDataArg_Destruct(
                            insertSubscriberDataArg);
                        MAP_V4_Ext_SS_InfoList_Destruct(
                            ext_SS_InfoList);
                        MAP_V4_Ext_SS_Info_Destruct(
                            ext_SS_Info);
                        MAP_V4_Ext_ForwInfo_Destruct(
                            ext_ForwInfo);

                        return ITS_ENOMEM;
                    }
                
                    {
                        /*
                         *  [8-1-1-1-3-1] Create Ext_ForwFeature object.
                         */

                        MAP_V4_Ext_ForwFeature 
                            ext_ForwFeature = 
                                MAP_V4_Ext_ForwFeature_ConstructDefault();

                        if (ext_ForwFeature == NULL)
                        {
                            MAP_V4_InsertSubscriberDataArg_Destruct(
                                insertSubscriberDataArg);
                            MAP_V4_Ext_SS_InfoList_Destruct(
                                ext_SS_InfoList);
                            MAP_V4_Ext_SS_Info_Destruct(
                                ext_SS_Info);
                            MAP_V4_Ext_ForwInfo_Destruct(
                                ext_ForwInfo);
                            MAP_V4_Ext_ForwFeatureList_Destruct(
                                ext_ForwFeatureList);

                            return ITS_ENOMEM;
                        }

                        {
                            /*
                             *  [8-1-1-1-3-1-1] Create Ext_SS_Status object.
                             */

                            MAP_V4_Ext_SS_Status
                                ext_SS_Status = 
                                    MAP_V4_Ext_SS_Status_ConstructWithArraySize(
                                        array10,
                                        array10Size);

                            if(ext_SS_Status == NULL)
                            {
                                MAP_V4_InsertSubscriberDataArg_Destruct(
                                    insertSubscriberDataArg);
                                MAP_V4_Ext_SS_InfoList_Destruct(
                                    ext_SS_InfoList);
                                MAP_V4_Ext_SS_Info_Destruct(
                                    ext_SS_Info);
                                MAP_V4_Ext_ForwInfo_Destruct(
                                    ext_ForwInfo);
                                MAP_V4_Ext_ForwFeatureList_Destruct(
                                    ext_ForwFeatureList);
                                MAP_V4_Ext_ForwFeature_Destruct(
                                    ext_ForwFeature);

                                return ITS_ENOMEM;
                            }

                            /*
                             *  [8-1-1-1-3-1-2] Set Ext_SS_Status object in 
                             *  Ext_ForwFeature object.
                             */

                            MAP_V4_Ext_ForwFeature_SetSs_Status(
                                ext_ForwFeature, 
                                ext_SS_Status);
                        }

                        {
                            /*
                             *  [8-1-1-1-3-1-3] Create Ext_BasicServiceCode
                             *  object.
                             */

                            MAP_V4_Ext_BasicServiceCode 
                                ext_basicServiceCode =
                                    MAP_V4_Ext_BasicServiceCode_ConstructDefault();

                            if (ext_basicServiceCode == NULL)
                            {
                                MAP_V4_InsertSubscriberDataArg_Destruct(
                                    insertSubscriberDataArg);
                                MAP_V4_Ext_SS_InfoList_Destruct(
                                    ext_SS_InfoList);
                                MAP_V4_Ext_SS_Info_Destruct(
                                    ext_SS_Info);
                                MAP_V4_Ext_ForwInfo_Destruct(
                                    ext_ForwInfo);
                                MAP_V4_Ext_ForwFeatureList_Destruct(
                                    ext_ForwFeatureList);
                                MAP_V4_Ext_ForwFeature_Destruct(
                                    ext_ForwFeature);

                                return ITS_ENOMEM;
                            }

                            {
                                /*
                                 *  [8-1-1-1-3-1-3-1] Create 
                                 *  Ext_BearerServiceCode object.
                                 */

                                MAP_V4_Ext_BearerServiceCode 
                                    ext_bearerServiceCode =
                                        MAP_V4_Ext_BearerServiceCode_ConstructWithArraySize(
                                            array11,
                                            array11Size);

                                if (ext_bearerServiceCode == NULL)
                                {
                                    MAP_V4_InsertSubscriberDataArg_Destruct(
                                        insertSubscriberDataArg);
                                    MAP_V4_Ext_SS_InfoList_Destruct(
                                        ext_SS_InfoList);
                                    MAP_V4_Ext_SS_Info_Destruct(
                                        ext_SS_Info);
                                    MAP_V4_Ext_ForwInfo_Destruct(
                                        ext_ForwInfo);
                                    MAP_V4_Ext_ForwFeatureList_Destruct(
                                        ext_ForwFeatureList);
                                    MAP_V4_Ext_ForwFeature_Destruct(
                                        ext_ForwFeature);
                                    MAP_V4_Ext_BasicServiceCode_Destruct(
                                        ext_basicServiceCode);

                                    return ITS_ENOMEM;
                                }

                                /*
                                 *  [8-1-1-1-3-1-3-2] Set choice 
                                 *  Ext_BearerServiceCode of
                                 *  Ext_BasicServiceCode object.
                                 */

                                MAP_V4_Ext_BasicServiceCode_SetChoiceExt_BearerService(
                                    ext_basicServiceCode, 
                                    ext_bearerServiceCode);
                            }

                            /*
                             *  [8-1-1-1-3-1-4] Set Ext_BasicServiceCode object
                             *  in Ext_ForwFeature object.
                             */

                            MAP_V4_Ext_ForwFeature_SetBasicService(
                                ext_ForwFeature,
                                ext_basicServiceCode);
                        }

                        {
                            /*
                             *  [8-1-1-1-3-1-5] Create ISDN_SubaddressString 
                             *  object.
                             */

                            MAP_V4_ISDN_SubaddressString 
                                iSDN_SubaddressString =
                                    MAP_V4_ISDN_SubaddressString_ConstructWithArraySize(
                                        array12,
                                        array12Size);

                            if (iSDN_SubaddressString == NULL)
                            {
                                MAP_V4_InsertSubscriberDataArg_Destruct(
                                    insertSubscriberDataArg);
                                MAP_V4_Ext_SS_InfoList_Destruct(
                                    ext_SS_InfoList);
                                MAP_V4_Ext_SS_Info_Destruct(
                                    ext_SS_Info);
                                MAP_V4_Ext_ForwInfo_Destruct(
                                    ext_ForwInfo);
                                MAP_V4_Ext_ForwFeatureList_Destruct(
                                    ext_ForwFeatureList);
                                MAP_V4_Ext_ForwFeature_Destruct(
                                    ext_ForwFeature);

                                return ITS_ENOMEM;
                            }

                            /*
                             *  [8-1-1-1-3-1-6] Set ISDN_SubaddressString object
                             *  in Ext_ForwFeature object.
                             */

                            MAP_V4_Ext_ForwFeature_SetForwardedToSubaddress(
                                ext_ForwFeature, 
                                iSDN_SubaddressString);
                        }

                        /*
                         *  [8-1-1-1-3-2] Add Ext_ForwFeature object to 
                         *  Ext_ForwFeatureList object.
                         */

                        res = 
                            MAP_V4_Ext_ForwFeatureList_AddElement(
                                ext_ForwFeatureList,
                                ext_ForwFeature);

                        if (res != ITS_SUCCESS)
                        {
                                MAP_V4_InsertSubscriberDataArg_Destruct(
                                    insertSubscriberDataArg);
                                MAP_V4_Ext_SS_InfoList_Destruct(
                                    ext_SS_InfoList);
                                MAP_V4_Ext_SS_Info_Destruct(
                                    ext_SS_Info);
                                MAP_V4_Ext_ForwInfo_Destruct(
                                    ext_ForwInfo);
                                MAP_V4_Ext_ForwFeatureList_Destruct(
                                    ext_ForwFeatureList);
                                MAP_V4_Ext_ForwFeature_Destruct(
                                    ext_ForwFeature);

                            return res;
                        }
                    }

                    /*
                     *  [8-1-1-1-4] Set ForwardingFeatureList object in
                     *  Ext_ForwInfo object.
                     */

                    MAP_V4_Ext_ForwInfo_SetForwardingFeatureList(
                        ext_ForwInfo,
                        ext_ForwFeatureList);
                }

                /*
                 *  [8-1-1-2] Set choice ForwardingInfo of Ext_SS_Info object.
                 */

                MAP_V4_Ext_SS_Info_SetChoiceForwardingInfo(
                                                        ext_SS_Info,
                                                        ext_ForwInfo);
            }

            /*
             *  [8-1-2] Add Ext_SS_Info object to Ext_SS_InfoList object.
             */

            res = MAP_V4_Ext_SS_InfoList_AddElement(
                ext_SS_InfoList,
                ext_SS_Info);

            if (res != ITS_SUCCESS)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_Ext_SS_InfoList_Destruct(ext_SS_InfoList);

                return res;
            }
        }

        {
            /*
             *  [8-1-3] Create Ext_SS_Info object.
             */

            MAP_V4_Ext_SS_Info 
                ext_SS_Info = 
                    MAP_V4_Ext_SS_Info_ConstructDefault();

            if (ext_SS_Info == NULL)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_Ext_SS_InfoList_Destruct(ext_SS_InfoList);                

                return ITS_ENOMEM;
            }

	        /*  
             *  MAP API Note: an Ext-SS-Info object contains a choice of
	         *  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or 
             *  EMLPP-Info.
             */

            {
                /*
                 *  Choice is cug-Info.
                 */

                /*
                 *  [8-1-3-1] Create CUG_Info object.
                 */

                MAP_V4_CUG_Info 
                    cUG_Info = 
                        MAP_V4_CUG_Info_ConstructDefault();

                if (cUG_Info == NULL)
                {
                    MAP_V4_InsertSubscriberDataArg_Destruct(
                        insertSubscriberDataArg);
                    MAP_V4_Ext_SS_InfoList_Destruct(
                        ext_SS_InfoList);
                    MAP_V4_Ext_SS_Info_Destruct(
                        ext_SS_Info);

                    return ITS_ENOMEM;
                }


                {
                    /*
                     *  [8-1-3-1-1] Create CUG_SubscriptionList object.
                     */

                    MAP_V4_CUG_SubscriptionList 
                        cUG_SubscriptionList = 
                            MAP_V4_CUG_SubscriptionList_ConstructDefault();

                    if (cUG_SubscriptionList == NULL)
                    {
                        MAP_V4_InsertSubscriberDataArg_Destruct(
                            insertSubscriberDataArg);
                        MAP_V4_Ext_SS_InfoList_Destruct(
                            ext_SS_InfoList);
                        MAP_V4_Ext_SS_Info_Destruct(
                            ext_SS_Info);
                        MAP_V4_CUG_Info_Destruct(
                            cUG_Info);

                        return ITS_ENOMEM;
                    }


	                /*
                     *  MAP API Note: a CUG_SubscriptionList object contains 
                     *  a list of CUG_Subscription objects.
                     */

                    {
                        /*
                         *  [8-1-3-1-1-1] Create CUG_Subscription object.
                         */

                        MAP_V4_CUG_Subscription 
                            cUG_Subscription =
                                MAP_V4_CUG_Subscription_ConstructDefault();

                        if (cUG_Subscription == NULL)
                        {
                            MAP_V4_InsertSubscriberDataArg_Destruct(
                                insertSubscriberDataArg);
                            MAP_V4_Ext_SS_InfoList_Destruct(
                                ext_SS_InfoList);
                            MAP_V4_Ext_SS_Info_Destruct(
                                ext_SS_Info);
                            MAP_V4_CUG_Info_Destruct(
                                cUG_Info);
                            MAP_V4_CUG_SubscriptionList_Destruct(
                                cUG_SubscriptionList);

                            return ITS_ENOMEM;
                        }

                        {
                            /*
                             *  [8-1-3-1-1-1-1] Create CUG_Index object.
                             */

                            MAP_V4_CUG_Index 
                                cUG_Index = 
                                    MAP_V4_CUG_Index_ConstructWithValue(
                                        1999l);

                            if (cUG_Index == NULL)
                            {
                                MAP_V4_InsertSubscriberDataArg_Destruct(
                                    insertSubscriberDataArg);
                                MAP_V4_Ext_SS_InfoList_Destruct(
                                    ext_SS_InfoList);
                                MAP_V4_Ext_SS_Info_Destruct(
                                    ext_SS_Info);
                                MAP_V4_CUG_Info_Destruct(
                                    cUG_Info);
                                MAP_V4_CUG_SubscriptionList_Destruct(
                                    cUG_SubscriptionList);
                                MAP_V4_CUG_Subscription_Destruct(
                                    cUG_Subscription);

                                return ITS_ENOMEM;
                            }

                            /*
                             *  [8-1-3-1-1-1-2] Set CUG_Index object in 
                             *  CUG_Subscription object.
                             */

                            MAP_V4_CUG_Subscription_SetCug_Index(
                                cUG_Subscription,
                                cUG_Index);
                        }

                        {
                            /*
                             *  [8-1-3-1-1-1-3] Create CUG_Interlock object.
                             */

                            MAP_V4_CUG_Interlock
                                cUG_Interlock =
                                    MAP_V4_CUG_Interlock_ConstructWithArraySize(
                                        array13,
                                        array13Size);

                            if (cUG_Interlock == NULL)
                            {
                                MAP_V4_InsertSubscriberDataArg_Destruct(
                                    insertSubscriberDataArg);
                                MAP_V4_Ext_SS_InfoList_Destruct(
                                    ext_SS_InfoList);
                                MAP_V4_Ext_SS_Info_Destruct(
                                    ext_SS_Info);
                                MAP_V4_CUG_Info_Destruct(
                                    cUG_Info);
                                MAP_V4_CUG_SubscriptionList_Destruct(
                                    cUG_SubscriptionList);
                                MAP_V4_CUG_Subscription_Destruct(
                                    cUG_Subscription);

                                return ITS_ENOMEM;
                            }

                            /*
                             *  [8-1-3-1-1-1-4] Set CUG_Interlock object in 
                             *  CUG_Subscription object.
                             */

                            MAP_V4_CUG_Subscription_SetCug_Interlock(
                                cUG_Subscription,
                                cUG_Interlock);
                        }

                        {
                            /*
                             *  [8-1-3-1-1-1-5] Create IntraCUG_Options object.
                             */

                            MAP_V4_IntraCUG_Options
                                intraCUG_Options =
                                    MAP_V4_IntraCUG_Options_ConstructDefault();

                            if (intraCUG_Options == NULL)
                            {
                                MAP_V4_InsertSubscriberDataArg_Destruct(
                                    insertSubscriberDataArg);
                                MAP_V4_Ext_SS_InfoList_Destruct(
                                    ext_SS_InfoList);
                                MAP_V4_Ext_SS_Info_Destruct(
                                    ext_SS_Info);
                                MAP_V4_CUG_Info_Destruct(
                                    cUG_Info);
                                MAP_V4_CUG_SubscriptionList_Destruct(
                                    cUG_SubscriptionList);
                                MAP_V4_CUG_Subscription_Destruct(
                                    cUG_Subscription);

                                return ITS_ENOMEM;
                            }

                            MAP_V4_IntraCUG_Options_SetNoCUG_Restrictions(
                                intraCUG_Options);

                            /*
                             *  [8-1-3-1-1-1-6] Set IntraCUG_Options object in 
                             *  CUG_Subscription object.
                             */

                            MAP_V4_CUG_Subscription_SetIntraCUG_Options(
                                cUG_Subscription,
                                intraCUG_Options);
                        }

                        /*
                         *  [8-1-3-1-1-2] Add CUG_Subscription object to 
                         *  CUG_SubscriptionList object.
                         */

                        res = 
                            MAP_V4_CUG_SubscriptionList_AddElement(
                                cUG_SubscriptionList,
                                cUG_Subscription);

                        if (res != ITS_SUCCESS)
                        {
                            MAP_V4_InsertSubscriberDataArg_Destruct(
                                insertSubscriberDataArg);
                            MAP_V4_Ext_SS_InfoList_Destruct(
                                ext_SS_InfoList);
                            MAP_V4_Ext_SS_Info_Destruct(
                                ext_SS_Info);
                            MAP_V4_CUG_Info_Destruct(
                                cUG_Info);
                            MAP_V4_CUG_SubscriptionList_Destruct(
                                cUG_SubscriptionList);

                            return res;
                        }
                    }

                    {
                        /*
                         *  [8-1-3-1-1-3] Create CUG_Subscription object.
                         */

                        MAP_V4_CUG_Subscription 
                            cUG_Subscription =
                                MAP_V4_CUG_Subscription_ConstructDefault();

                        if (cUG_Subscription == NULL)
                        {
                            MAP_V4_InsertSubscriberDataArg_Destruct(
                                insertSubscriberDataArg);
                            MAP_V4_Ext_SS_InfoList_Destruct(
                                ext_SS_InfoList);
                            MAP_V4_Ext_SS_Info_Destruct(
                                ext_SS_Info);
                            MAP_V4_CUG_Info_Destruct(
                                cUG_Info);
                            MAP_V4_CUG_SubscriptionList_Destruct(
                                cUG_SubscriptionList);

                            return ITS_ENOMEM;
                        }

                        {
                            /*
                             *  [8-1-3-1-1-3-1] Create CUG_Index object.
                             */

                            MAP_V4_CUG_Index 
                                cUG_Index = 
                                    MAP_V4_CUG_Index_ConstructWithValue(
                                        2001l);

                            if (cUG_Index == NULL)
                            {
                                MAP_V4_InsertSubscriberDataArg_Destruct(
                                    insertSubscriberDataArg);
                                MAP_V4_Ext_SS_InfoList_Destruct(
                                    ext_SS_InfoList);
                                MAP_V4_Ext_SS_Info_Destruct(
                                    ext_SS_Info);
                                MAP_V4_CUG_Info_Destruct(
                                    cUG_Info);
                                MAP_V4_CUG_SubscriptionList_Destruct(
                                    cUG_SubscriptionList);
                                MAP_V4_CUG_Subscription_Destruct(
                                    cUG_Subscription);

                                return ITS_ENOMEM;
                            }

                            /*
                             *  [8-1-3-1-1-3-2] Set CUG_Index object in 
                             *  CUG_Subscription object.
                             */

                            MAP_V4_CUG_Subscription_SetCug_Index(
                                cUG_Subscription,
                                cUG_Index);
                        }

                        {
                            /*
                             *  [8-1-3-1-1-3-3] Create CUG_Interlock object.
                             */

                            MAP_V4_CUG_Interlock
                                cUG_Interlock =
                                    MAP_V4_CUG_Interlock_ConstructWithArraySize(
                                        array14,
                                        array14Size);

                            if (cUG_Interlock == NULL)
                            {
                                MAP_V4_InsertSubscriberDataArg_Destruct(
                                    insertSubscriberDataArg);
                                MAP_V4_Ext_SS_InfoList_Destruct(
                                    ext_SS_InfoList);
                                MAP_V4_Ext_SS_Info_Destruct(
                                    ext_SS_Info);
                                MAP_V4_CUG_Info_Destruct(
                                    cUG_Info);
                                MAP_V4_CUG_SubscriptionList_Destruct(
                                    cUG_SubscriptionList);
                                MAP_V4_CUG_Subscription_Destruct(
                                    cUG_Subscription);

                                return ITS_ENOMEM;
                            }

                            /*
                             *  [8-1-3-1-1-3-4] Set CUG_Interlock object in 
                             *  CUG_Subscription object.
                             */

                            MAP_V4_CUG_Subscription_SetCug_Interlock(
                                cUG_Subscription,
                                cUG_Interlock);
                        }

                        {
                            /*
                             *  [8-1-3-1-1-3-5] Create IntraCUG_Options object.
                             */

                            MAP_V4_IntraCUG_Options
                                intraCUG_Options =
                                    MAP_V4_IntraCUG_Options_ConstructDefault();

                            if (intraCUG_Options == NULL)
                            {
                                MAP_V4_InsertSubscriberDataArg_Destruct(
                                    insertSubscriberDataArg);
                                MAP_V4_Ext_SS_InfoList_Destruct(
                                    ext_SS_InfoList);
                                MAP_V4_Ext_SS_Info_Destruct(
                                    ext_SS_Info);
                                MAP_V4_CUG_Info_Destruct(
                                    cUG_Info);
                                MAP_V4_CUG_SubscriptionList_Destruct(
                                    cUG_SubscriptionList);
                                MAP_V4_CUG_Subscription_Destruct(
                                    cUG_Subscription);

                                return ITS_ENOMEM;
                            }

                            MAP_V4_IntraCUG_Options_SetNoCUG_Restrictions(
                                intraCUG_Options);

                            /*
                             *  [8-1-3-1-1-3-6] Set IntraCUG_Options object in 
                             *  CUG_Subscription object.
                             */

                            MAP_V4_CUG_Subscription_SetIntraCUG_Options(
                                cUG_Subscription,
                                intraCUG_Options);
                        }

                        /*
                         *  [8-1-3-1-1-4] Add CUG_Subscription object to 
                         *  CUG_SubscriptionList object.
                         */

                        res = 
                            MAP_V4_CUG_SubscriptionList_AddElement(
                                cUG_SubscriptionList,
                                cUG_Subscription);

                        if (res != ITS_SUCCESS)
                        {
                            MAP_V4_InsertSubscriberDataArg_Destruct(
                                insertSubscriberDataArg);
                            MAP_V4_Ext_SS_InfoList_Destruct(
                                ext_SS_InfoList);
                            MAP_V4_Ext_SS_Info_Destruct(
                                ext_SS_Info);
                            MAP_V4_CUG_Info_Destruct(
                                cUG_Info);
                            MAP_V4_CUG_SubscriptionList_Destruct(
                                cUG_SubscriptionList);

                            return res;
                        }
                    }

                    /*
                     *  [8-1-3-1-2] Set CUG_SubscriptinList object in CUG_Info 
                     *  object. 
                     */

                    MAP_V4_CUG_Info_SetCug_SubscriptionList(
                        cUG_Info,
                        cUG_SubscriptionList);
                }

                /*
                 *  [8-1-3-2] Set choice CUG_Info in Ext_SS_Info object.
                 */

                MAP_V4_Ext_SS_Info_SetChoiceCug_Info(
                    ext_SS_Info,
                    cUG_Info);
            }

            /*
             *  [8-1-4] Add Ext_SS_Info object to Ext_SS_InfoList object.
             */

            res = MAP_V4_Ext_SS_InfoList_AddElement(
                ext_SS_InfoList,
                ext_SS_Info);

            if (res != ITS_SUCCESS)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_Ext_SS_InfoList_Destruct(ext_SS_InfoList);

                return res;
            }
        }

        /*
         *  [8-2] Set Ext_SS_InfoList in InsertSubscriberDataArg object.
         */

        MAP_V4_InsertSubscriberDataArg_SetProvisionedSS(
            insertSubscriberDataArg, 
            ext_SS_InfoList);
    }

    /*------------------------------------------------------------------------*/

    /* 
     *  [9] Populate optional parameter "odb-Data".
     */

    {
        /*
         *  [9-1] Create ODB_Data object.
         */

        MAP_V4_ODB_Data 
            oDB_Data = 
                MAP_V4_ODB_Data_ConstructDefault();

        if (oDB_Data == NULL)
        {
            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

            return ITS_ENOMEM;
        }

        {
            /*
             *  [9-1-1] Create ODB_GeneralData object.
             */

            MAP_V4_ODB_GeneralData
                oDB_GeneralData = 
                    MAP_V4_ODB_GeneralData_ConstructWithArraySize(
                        array17, 
                        array17Size);

            if (oDB_GeneralData == NULL)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_ODB_Data_Destruct(oDB_Data);

                return ITS_ENOMEM;
            }

            /*
             *  [9-1-2] Set ODB_GeneralData object in ODB_Data object.
             */

            MAP_V4_ODB_Data_SetOdb_GeneralData(
                oDB_Data, 
                oDB_GeneralData);
        }

        {
            /*
             *  [9-1-3] Create ODB_HPLMN_Data object.
             */

            MAP_V4_ODB_HPLMN_Data
                oDB_HPLMN_Data =
                    MAP_V4_ODB_HPLMN_Data_ConstructWithArraySize(
                        array18,
                        array18Size);

            if (oDB_HPLMN_Data == NULL)
            {
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                MAP_V4_ODB_Data_Destruct(oDB_Data);

                return ITS_ENOMEM;
            }

            /*
             *  [9-1-4] Set ODB_HPLMN_Data object in ODB_Data object.
             */

            MAP_V4_ODB_Data_SetOdb_HPLMN_Data(
                oDB_Data, 
                oDB_HPLMN_Data);
        }
                    
        /*
         *  [9-2] Set ODB_Data object in InsertSubscriberDataArg object.
         */

        MAP_V4_InsertSubscriberDataArg_SetOdb_Data(
            insertSubscriberDataArg, 
            oDB_Data);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [10] Encode InsertSubscriberDataArg object.
     */

    {
        ASN_EncodeError encodeError         = NULL;
        int encodeErrorCode                 = ITS_SUCCESS;
        const char* encodeErrorText         = NULL;
        const char* encodeExtendedErrorText = NULL;


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
                MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);
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
                MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);
                ASN_EncodeError_Destruct(encodeError);

                return ITS_ENOMEM;
            }

            printf(
                "\nEncode error extended text is <%s>.\n\n", 
                encodeExtendedErrorText);

            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

            /* 
             *  Object encodeError must be destructed by end-user. 
             */

            ASN_EncodeError_Destruct(encodeError);

            return res;
        }
        else if (res != ITS_SUCCESS)
        {
            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

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

        printf("\nPrinting InsertSubscriberDataArg ASN.1 encoded value...\n\n");

        ASN_Octets_Print(octets);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [11] Retrieve InsertSubscriberData ASN.1 encoded value from octets 
     *  object and return InsertSubscriberDataArg ASN.1 encoded value through
     *  function parameters octetArray and size.
     */

    *octetArray = 
        (ITS_OCTET*)calloc(
            ASN_Octets_GetSize(octets), 
            sizeof(ITS_OCTET));

    if (*octetArray == NULL)
    {
        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);
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
     *  [12] Free all memory allocated on the heap.
     */

    /*
     *  [12-1] Delete InsertSubscriberDataArg object (and therefore all the
     *  parameter objects that have been previously set).
     */

    MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

    /*
     *  [12-2] Delete octets object created by the call to 
     *  MAP_V4_InsertSubscriberDataArg_Encode.
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
 *  How to interpret an (encoded) MAP InsertSubscriberData operation argument 
 *  (InsertSubscriberDataArg):
 *
 *  o   Decode InsertSubscriberDataArg encoded value (i.e. create 
 *      InsertSubscriberDataArg object from InsertSubscriberDataArg encoded 
 *      value).
 *
 *  o   Retrieve Data from InsertSubscriberDataArg object.
 *
 */

int 
InterpretOperationInsertSubscriberDataArg(
    const ITS_OCTET* octetArray, 
    size_t size)
{
    MAP_V4_InsertSubscriberDataArg insertSubscriberDataArg  = NULL;
    ASN_Octets octets                                       = NULL;
    int res                                                 = ITS_SUCCESS;

    ASN_C_REQUIRE(octetArray != NULL);
    ASN_C_REQUIRE(size != 0);

    /*
     *  [1] Create Octets object from InsertSubscriberDataArg ASN.1 
     *  encoded value.
     */

    octets = ASN_Octets_ConstructWithArray(octetArray, size);

    if (octets == NULL)
    {
        return ITS_ENOMEM;
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [2] Create InsertSubscriberDataArg object (used by decode phase).
     */

    insertSubscriberDataArg = MAP_V4_InsertSubscriberDataArg_ConstructDefault();

    if (insertSubscriberDataArg == NULL)
    {
        ASN_Octets_Destruct(octets);

        return ITS_ENOMEM;
    }

    /*------------------------------------------------------------------------*/

    /*  
     *  [3] Decode InsertSubscriberDataArg ASN.1 encoded value and therefore
     *  populate previously created InsertSubscriberDataArg object.
     */

    {
        ASN_DecodeError decodeError         = NULL;
        int decodeErrorCode                 = ITS_SUCCESS;
        const char* decodeErrorText         = NULL;
        const char* decodeExtendedErrorText = NULL;

        res = MAP_V4_InsertSubscriberDataArg_Decode(
                                insertSubscriberDataArg, 
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
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
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
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                ASN_DecodeError_Destruct(decodeError);

                return ITS_ENOMEM;
            }

            fprintf(
                stderr, 
                "\nDecode error extended text is <%s>.\n\n", 
                decodeExtendedErrorText);

            ASN_Octets_Destruct(octets);
            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

            /* 
             *  Object decodeError must be destructed by end-user. 
             */

            ASN_DecodeError_Destruct(decodeError);

            return res;
        }
        else if (res != ITS_SUCCESS)
        {
            ASN_Octets_Destruct(octets);
            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);
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
         *  Print decoded InsertSubscriberDataArg object.
         */

        printf("\nPrinting decoded InsertSubscriberDataArg object...\n");

        MAP_V4_InsertSubscriberDataArg_Print(insertSubscriberDataArg);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [4] Retrieve optional parameter "imsi".
     */

    if (MAP_V4_InsertSubscriberDataArg_OptionImsi(insertSubscriberDataArg))
    {
        const ITS_OCTET* array  = NULL;
        size_t arraySize        = 0;

        /*
         *  [4-1] Retrieve const pointer to IMSI object.
         */

        const MAP_V4_IMSI
            imsi =
                MAP_V4_InsertSubscriberDataArg_GetImsi(
                    insertSubscriberDataArg);

        /*
         *  [4-2] Retrieve contents of IMSI object.
         */

        array = 
            MAP_V4_IMSI_GetArray(
                imsi);

        arraySize =
            MAP_V4_IMSI_GetSize(
                imsi);

        /*
         *  Do something with array of octets...
         */

        /*
         *  [4-3] Print IMSI object.
         */

        printf("\nPrinting IMSI object...\n");

        MAP_V4_IMSI_Print(imsi);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [5] Retrieve other optional parameters: to be done.
     */

    /*------------------------------------------------------------------------*/

    /*
     *  [6] Free all memory allocated on the heap.
     */

    /*
     *  [6-1] Delete octets object.
     */

    ASN_Octets_Destruct(octets);

    /*
     *  [6-2] Delete InsertSubscriberDataArg object.
     */

    MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

    /*------------------------------------------------------------------------*/

    /*
     *  Return success.
     */

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

int 
main(int argc, char* argv[])
{
    ITS_OCTET* octetArray   = NULL;
    size_t size             = 0;
    int res                 = ITS_SUCCESS;

    printf("\nBegin MAP V4 ASN.1 codec example...\n");

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
     *  Add MAP V4 feature to IntelliSS7.
     */

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
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }
        
    /*------------------------------------------------------------------------*/

    /*
     *  [1] Call BuildOperationInsertSubscriberDataArg function.
     */

    res = BuildOperationInsertSubscriberDataArg(&octetArray, &size);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    /*
     *  [2] Call InterpretOperationInsertSubscriberDataArg function.
     */

    res = InterpretOperationInsertSubscriberDataArg(octetArray, size);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    /*
     *  [3] Free memory allocated by BuildOperationInsertSubscriberDataArg 
     *  function.
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
     *  Add MAP V4 feature to IntelliSS7.
     */

    ITS_RemFeature(itsMAP_V4_Class);


    printf("\nEnd of MAP V4 ASN.1 codec example.\n");
    
#if defined(WIN32)

    /* To stop here in console application. */

    printf("Type any key to quit...\n");

    {
        char c = getch();
    }
    
#endif /* defined(WIN32) */

    return EXIT_SUCCESS;
}

