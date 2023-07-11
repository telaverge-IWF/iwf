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
//  ID: $Id: MAP_UserInfoHelper.h,v 9.1 2005/03/23 12:51:24 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//   GSMMAP Phase 2+ (P2P) UserInformation class
//
//


#if !defined(_MAP_USERINFO_H_)
#define _MAP_USERINFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <its++.h>
#include <Octets.h>
#include <MAP_UserInfo.h>
#include <AsnObjectIdentifier.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif    // defined(ITS_NAMESPACE)

class MAP_UserInfoHelper
{
    
public:
    
    MAP_UserInfoHelper();         

    //Object Identifier

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

    virtual~MAP_UserInfoHelper()
    {
        if (oid)
        {
            delete oid;
        }
    }

    void SetDestinationReference(std::vector<byte>& destRefParam)
    {
        hasDestinationReference = true;
        destinationReference = destRefParam;
    }

    void SetOriginationReference(std::vector<byte>& origRefParam)
    {
        hasOriginationReference = true;
        originationReference = origRefParam;
    }

    const std::vector<byte>& GetDestinationReference() const
    {       
        ITS_ASSERT(isDecodeDone);
        return destinationReference;
    }

    const std::vector<byte>& GetOriginationReference() const
    {       
        ITS_ASSERT(isDecodeDone);
        return originationReference;
    }

    const bool IsDecodeDone() const
    {
        return isDecodeDone;
    }

    const bool IsEncodeDone() const
    {
        return isEncodeDone;
    }

    const bool HasDestinationReference() const
    {
        return hasDestinationReference;
    }

    const bool HasOriginationReference() const
    {
        return hasOriginationReference;
    }

    std::vector<byte> Encode();

    void Decode(std::vector<byte>& userInfoOctets);

protected:

    std::vector<byte> destinationReference;
    std::vector<byte> originationReference;    

    bool hasDestinationReference;
    bool hasOriginationReference; 
    bool isDecodeDone;
    bool isEncodeDone;

    MAP_UserInfo mui;
    AsnObjectIdentifier* oid;
};

#if defined(ITS_NAMESPACE)
}
#endif    // defined(ITS_NAMESPACE)


#endif  // !defined(_MAP_USERINFO_H_)
