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


#include <map_v13_absent_subscriber_diagnostic_sm.h>

#include <AsnDescInteger.h>


using namespace its;
using namespace map_v13;



AsnDescObject* AbsentSubscriberDiagnosticSM::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new AbsentSubscriberDiagnosticSM(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 2));
        staticDesc.SetTypeName("AbsentSubscriberDiagnosticSM");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





