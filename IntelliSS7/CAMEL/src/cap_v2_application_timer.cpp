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


#include <cap_v2_application_timer.h>

#include <AsnDescInteger.h>


using namespace its;
using namespace cap_v2;



AsnDescObject* ApplicationTimer::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new ApplicationTimer(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 2));
        staticDesc.SetTypeName("ApplicationTimer");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





