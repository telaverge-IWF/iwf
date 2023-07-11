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


#include <map_v9_unknown_subscriber_diagnostic.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v9;



AsnDescObject* UnknownSubscriberDiagnostic::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new UnknownSubscriberDiagnostic(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueExtSet.insert(2);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"imsiUnknown", 0}, {"gprsSubscriptionUnknown", 1}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{"npdbMismatch", 2}, {NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("UnknownSubscriberDiagnostic");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long UnknownSubscriberDiagnostic::Get(const std::string& valueName) const
{
    if (valueName == "imsiUnknown")
    {
        return 0;
    }
    else if (valueName == "gprsSubscriptionUnknown")
    {
        return 1;
    }
    else if (valueName == "npdbMismatch")
    {
        return 2;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string UnknownSubscriberDiagnostic::Get(long value) const
{
    if (value == 0)
    {
        return "imsiUnknown";
    }
    else if (value == 1)
    {
        return "gprsSubscriptionUnknown";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string UnknownSubscriberDiagnostic::GetExt(long value) const
{
    if (value == 2)
    {
        return "npdbMismatch";
    }
    else
    {
        return "";
    }
}





