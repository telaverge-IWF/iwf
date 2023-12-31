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


#include <map_v13_location_area.h>

#include <AsnDescChoice.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace map_v13;




////////// Begin Nested Class(es) //////////


// Type LAIFixedLength is a reference => no code generated.

// Type LAC is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* LocationArea::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescChoice staticDesc;

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
        staticDesc.SetCloneForFactory(new LocationArea(&staticDesc));
        staticDesc._choiceList.push_back(GetLaiFixedLengthStaticDescription());
        staticDesc._choiceList.push_back(GetLacStaticDescription());
        staticDesc.SetTypeName("LocationArea");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* LocationArea::GetLaiFixedLengthStaticDescription()
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
        staticDesc.SetCloneForFactory(new LAIFixedLength(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 5;
        staticDesc._maxSize = 5;
        staticDesc.SetNamedTypeName("laiFixedLength");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* LocationArea::GetLacStaticDescription()
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
        staticDesc.SetCloneForFactory(new LAC(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 2;
        staticDesc._maxSize = 2;
        staticDesc.SetNamedTypeName("lac");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





