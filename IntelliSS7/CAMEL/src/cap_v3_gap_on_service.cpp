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


#include <cap_v3_gap_on_service.h>

#include <AsnDescSequence.h>
#include <AsnDescInteger.h>


using namespace its;
using namespace cap_v3;




////////// Begin Nested Class(es) //////////


// Type ServiceKey is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* GapOnService::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(1);

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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new GapOnService(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetServiceKeyStaticDescription();
        staticDesc.SetTypeName("GapOnService");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* GapOnService::GetServiceKeyStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescInteger staticDesc;

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
        staticDesc.SetCloneForFactory(new ServiceKey(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc.SetNamedTypeName("serviceKey");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





