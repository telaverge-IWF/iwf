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


#include <cap_v3_not_reachable_reason.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace cap_v3;



AsnDescObject* NotReachableReason::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new NotReachableReason(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"msPurged", 0}, {"imsiDetached", 1}, {"restrictedArea", 2}, {"notRegistered", 3}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("NotReachableReason");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long NotReachableReason::Get(const std::string& valueName) const
{
    if (valueName == "msPurged")
    {
        return 0;
    }
    else if (valueName == "imsiDetached")
    {
        return 1;
    }
    else if (valueName == "restrictedArea")
    {
        return 2;
    }
    else if (valueName == "notRegistered")
    {
        return 3;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string NotReachableReason::Get(long value) const
{
    if (value == 0)
    {
        return "msPurged";
    }
    else if (value == 1)
    {
        return "imsiDetached";
    }
    else if (value == 2)
    {
        return "restrictedArea";
    }
    else if (value == 3)
    {
        return "notRegistered";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string NotReachableReason::GetExt(long value) const
{
    return "";
}





