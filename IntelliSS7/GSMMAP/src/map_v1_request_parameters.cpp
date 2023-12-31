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


#include <map_v1_request_parameters.h>

#include <AsnDescSequenceOf.h>
#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v1;




////////// Begin Nested Class //////////


// Type RequestParameter is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* RequestParameters::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequenceOf staticDesc;

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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new RequestParameters(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 2;
        staticDesc._element = GetRequestParameterStaticDescription();
        staticDesc.SetTypeName("RequestParameters");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* RequestParameters::GetRequestParameterStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescEnumerated staticDesc;

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
        staticDesc.SetCloneForFactory(new RequestParameter(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"request-IMSI", 0}, {"request-AuthenticationSet", 1}, {"request-SubscriberData", 2}, {"request-CUG-Information", 3}, {"request-Ki", 4}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





