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
//  ID: $Id: GSMMAPP2P.cpp,v 9.1 2005/03/23 12:51:25 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//   GSMMAP Phase 2+ (P2P) constants (C++ API).
//
//

#include <GSMMAPP2P.h>
#include <Octets.h>
#include <Length.h>
#include <vector>
#include <AsnObjectIdentifier.h>

#if defined(ITS_NAMESPACE)
using namespace std;
#endif // defined(ITS_NAMESPACE)


#if defined(ITS_NAMESPACE)
namespace its
{
#endif    // defined(ITS_NAMESPACE)

vector<byte> 
EncodeApplicationContext(long acName, long version)
{
    vector<long> cptArray;    

    cptArray.push_back(OID_CPT_CCITT);
    cptArray.push_back(OID_CPT_IDEN_ORG);
    cptArray.push_back(OID_CPT_ETSI);
    cptArray.push_back(OID_CPT_MOBILE_DOMAIN);
    cptArray.push_back(OID_CPT_GSM_NETWORK);
    cptArray.push_back(OID_CPT_AC_ID);
    cptArray.push_back(acName);
    cptArray.push_back(version);
 
    AsnObjectIdentifier objectIdentifier;

    objectIdentifier.SetArray(cptArray);
     
    Octets* octets = objectIdentifier.Encode();

    Tag tag(*octets);

    Length length(*octets);

    vector<byte> result;

    result = octets->GetArrayWithOffset(); 

    delete octets;

    return result;
}

void 
DecodeApplicationContext(vector<byte>& encodedVec, 
                         long& acName, long& version)
{
    Octets valOctets(encodedVec);
   
    Tag* tag = AsnObjectIdentifier::GetUniversalTag();
     
    Octets* tagOctets = tag->Encode();

    Length length(valOctets.GetLength());

    Octets* lengthOctets = length.Encode();

    Octets* octets = new Octets();

    *octets += *tagOctets;
    *octets += *lengthOctets;
    *octets += valOctets;

    AsnObjectIdentifier objectIdentifier;

    objectIdentifier.Decode(*octets);

    acName = objectIdentifier.GetArray()[6];
    version = objectIdentifier.GetArray()[7];

    delete octets;
    delete lengthOctets;
    delete tagOctets;    
    delete tag;     
}

#if defined(ITS_NAMESPACE)
}
#else
};
#endif  // defined(ITS_NAMESPACE)
