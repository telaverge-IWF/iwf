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


#include <map_v13_long_term_denial_param.h>

#include <AsnDescSequence.h>


using namespace its;
using namespace map_v13;




////////// Begin Nested Class(es) //////////


////////// End Nested Class(es) //////////

AsnDescObject* LongTermDenialParam::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(0);

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
        staticDesc.SetCloneForFactory(new LongTermDenialParam(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc.SetTypeName("LongTermDenialParam");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





