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
//  ID: $Id: MAP_UserInfoHelper.cpp,v 9.1 2005/03/23 12:51:25 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  
//
//

#include <MAP_UserInfoHelper.h>
#include <Octets.h>
#include <Length.h>
#include <vector>
#include <EXTERNAL.h>
#include <MAP_OpenInfo.h>
#include <MAP_DialoguePDU.h>
#include <AsnSequenceOf.h>
#include <AsnException.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif    // defined(ITS_NAMESPACE)

MAP_UserInfoHelper::MAP_UserInfoHelper()    
     : hasDestinationReference(false),
       hasOriginationReference(false),
       isDecodeDone(false),
       isEncodeDone(false)
{
    std::vector<long> cptArray;    

    cptArray.push_back(OID_CPT_CCITT);
    cptArray.push_back(OID_CPT_IDEN_ORG);
    cptArray.push_back(OID_CPT_ETSI);
    cptArray.push_back(OID_CPT_MOBILE_DOMAIN);
    cptArray.push_back(OID_CPT_GSM_NETWORK);
    cptArray.push_back(OID_CPT_Q773);
    cptArray.push_back(OID_DLG);
    cptArray.push_back(OID_VERSION);

    oid = new AsnObjectIdentifier(cptArray);
}

std::vector<byte> 
MAP_UserInfoHelper::Encode()
{
    MAP_OpenInfo* mapOpenInfo = new MAP_OpenInfo();
    MAP_DialoguePDU * map_dialoguePDU = new MAP_DialoguePDU();
    EXTERNAL *external = new EXTERNAL();

    if (hasDestinationReference)
    {
        AddressString *destString = new AddressString(destinationReference);  
        mapOpenInfo->SetDestinationReference(destString);
    }

    if (hasOriginationReference)
    {
        AddressString *origString = new AddressString(originationReference);
        mapOpenInfo->SetOriginationReference(origString);  
    }              

    map_dialoguePDU->SetChoiceMap_open(mapOpenInfo);       
 
    Octets* oid_octets = oid->Encode();

    EXTERNAL::Direct_reference *dr = new EXTERNAL::Direct_reference(*oid_octets);
    EXTERNAL::Encoding *encoding = new EXTERNAL::Encoding();
    EXTERNAL::Encoding::Single_ASN1_type *sin_asn_type = 
                new EXTERNAL::Encoding::Single_ASN1_type(map_dialoguePDU);

    encoding->SetChoiceSingle_ASN1_type(sin_asn_type);
    
    external->SetDirect_reference(dr);
    external->SetEncoding(encoding);

    mui.AddElement(external);

    Octets* tmpOctets;

    try
    {
        tmpOctets = mui.Encode();    
    }
    catch(AsnEncodeError& exc)
    {        
        exc.Log();
    }

    std::vector<byte> vec;
    vec = tmpOctets->GetArray(); 

    delete tmpOctets;    

    isEncodeDone = true;

    return vec;
}

void 
MAP_UserInfoHelper::Decode(std::vector<byte>& userInfoOctets)
{
    Octets octets(userInfoOctets);

    try
    {
        mui.Decode(octets);        
    }
    catch(AsnDecodeError& exc)
    {        
        exc.Log();
    }

    for (int i = 0; i < mui.Size(); i++)
    {
        const EXTERNAL& external = mui.ElementAt(i);

        if (!external.OptionDirect_reference())
        {
            continue;
        }

        const EXTERNAL::Direct_reference& dr = external.GetDirect_reference();
        
        if (!(dr.GetArray() == (*oid).GetArray()))
        {
            continue;
        }        
        
        const EXTERNAL::Encoding& encoding = external.GetEncoding();

        if (!encoding.ChoiceSingle_ASN1_type())
        {
            continue;
        }

        const EXTERNAL::Encoding::Single_ASN1_type& single_asn1_type =
                            encoding.GetChoiceSingle_ASN1_type();
        
        Octets anyOctets = single_asn1_type.GetDecodedOctets();

        MAP_DialoguePDU map_dialoguePDU(anyOctets);

        if (!map_dialoguePDU.ChoiceMap_open())
        {
            continue;
        }

        const MAP_OpenInfo& map_openInfo = map_dialoguePDU.GetChoiceMap_open();

        if (map_openInfo.OptionDestinationReference())
        {
            const AddressString& destString = map_openInfo.GetDestinationReference();
            hasDestinationReference = true;

            destinationReference = destString.GetArray();
        }

        if (map_openInfo.OptionOriginationReference())
        {
            const AddressString& origString = map_openInfo.GetOriginationReference();
            hasOriginationReference = true;

            originationReference = origString.GetArray();
        }

        isDecodeDone = true;

        break;
    }    
}

#if defined(ITS_NAMESPACE)
}
#else
};
#endif  // defined(ITS_NAMESPACE)
