//
// Generated by IntelliAsnCC ASN.1 compiler (C, C++, Java).
//
// Do not edit!
//
//
//
// (C) 2000, 2001 IntelliNet Technologies Inc. All Rights Reserved.
//
//


#include <map_v13_integrity_protection_information.h>

#include <AsnDescOctetString.h>


using namespace its;
using namespace map_v13;



AsnDescObject* IntegrityProtectionInformation::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescOctetString staticDesc;

    if (initialized)
    {
        return result;
    }

    Asn::Lock();

    if (initialized)
    {
        Asn::Unlock();
        return result;
    }
    else
    {
        staticDesc.SetCloneForFactory(new IntegrityProtectionInformation(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 4));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 18;
        staticDesc._maxSize = 100;
        staticDesc.SetTypeName("IntegrityProtectionInformation");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





