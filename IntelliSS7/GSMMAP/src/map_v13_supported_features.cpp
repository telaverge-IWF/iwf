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


#include <map_v13_supported_features.h>

#include <AsnDescBitString.h>


using namespace its;
using namespace map_v13;



AsnDescObject* SupportedFeatures::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescBitString staticDesc;

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
        staticDesc.SetCloneForFactory(new SupportedFeatures(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 3));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 26;
        staticDesc._maxSize = 40;
        staticDesc.SetTypeName("SupportedFeatures");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





