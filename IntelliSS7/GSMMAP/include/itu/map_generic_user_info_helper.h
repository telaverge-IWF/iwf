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
//  ID: $Id: map_generic_user_info_helper.h,v 9.2 2007/01/10 11:14:59 yranade Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  MAP Generic User Info helper class interface (C++ API). 
//
//  Header file to be included by the following hearder files:
//
//  o map_v2_user_info_helper.h
//  o map_v3_user_info_helper.h
//  o map_v4_user_info_helper.h
//  o map_v5_user_info_helper.h
//  o map_v6_user_info_helper.h
//  o map_v7_user_info_helper.h
//  
//  o map_common_user_info_helper.h
//

//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//  Header file MUST always be included in other source file. Cannot be used
//  directly.
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  


#if !defined(_MAP_GENERIC_USER_INFO_HELPER_H_)
#define _MAP_GENERIC_USER_INFO_HELPER_H_


class MAP_UserInfoHelper
{
public:
    
    MAP_UserInfoHelper();         

    // MAP Object Identifier related.

    enum
    {
        MAP_OPEN          = 0,
        MAP_ACCEPT        = 1,
        MAP_CLOSE         = 2,
        MAP_REFUSE        = 3,
        MAP_UABORT        = 4,
        MAP_PABORT        = 5
    };        

    enum
    {
        OID_CPT_CCITT               = 0,
        OID_CPT_IDEN_ORG            = 4,
        OID_CPT_ETSI                = 0,
        OID_CPT_MOBILE_DOMAIN       = 0,
        OID_CPT_GSM_NETWORK         = 1,
        OID_CPT_Q773                = 1,
        OID_DLG                     = 1,
        OID_VERSION                 = 1
    };

    enum 
    {
        SPECIFIC_REASON     = 0,
        RESOURCE_LIMIT      = 1,
        RESOURCE_UNAVAIL    = 2,
        APP_PROC_CANCEL     = 3
    };

    virtual~MAP_UserInfoHelper()
    {
        if (oid)
        {
            delete oid;
        }
    }

    void
    SetMapDlgType(int type)
    {
        mapDlgType = type;
    }

    int GetMapDlgType() const
    {
        return mapDlgType;
    }

    void 
    SetDestinationReference(std::vector<byte>& destRefParam)
    {
        hasDestinationReference = true;
        destinationReference = destRefParam;
    }

    void 
    SetOriginationReference(std::vector<byte>& origRefParam)
    {
        hasOriginationReference = true;
        originationReference = origRefParam;
    }

    void 
    SetAbortReasonType(int reason)
    {
        abortReasonType = reason;
    }

    int
    GetAbortReasonType() const
    {
        return abortReasonType;
    }
    void 
    SetAbortReason(int reason)
    {
        abortReason = reason;
    }

    int
    GetAbortReason() const
    {
        return abortReason;
    }
    void 
    SetRefuseReason(int reason)
    {
        refuseReason = reason;
    }

    int
    GetRefuseReason() const
    {
        return refuseReason;
    }

    const std::vector<byte>& 
    GetDestinationReference() const
    {       
        ITS_ASSERT(isDecodeDone);
        return destinationReference;
    }

    const std::vector<byte>& 
    GetOriginationReference() const
    {       
        ITS_ASSERT(isDecodeDone);
        return originationReference;
    }

    const bool 
    IsDecodeDone() const
    {
        return isDecodeDone;
    }

    const bool 
    IsEncodeDone() const
    {
        return isEncodeDone;
    }

    const bool 
    HasDestinationReference() const
    {
        return hasDestinationReference;
    }

    const bool 
    HasOriginationReference() const
    {
        return hasOriginationReference;
    }

    std::vector<byte> Encode();

    void Decode(std::vector<byte>& userInfoOctets);

protected:

    int mapDlgType;

    std::vector<byte> destinationReference;
    std::vector<byte> originationReference;

    bool hasDestinationReference;
    bool hasOriginationReference; 
    bool isDecodeDone;
    bool isEncodeDone;

    int abortReasonType;
    int refuseReason;
    int abortReason;
    MAP_UserInfo mui;

    its::AsnObjectIdentifier* oid;
};

#endif // !defined(_MAP_GENERIC_USER_INFO_HELPER_H_)
