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


#include <map_v2_regional_subscription_response.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v2;



AsnDescObject* RegionalSubscriptionResponse::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new RegionalSubscriptionResponse(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"msc-AreaRestricted", 0}, {"tooManyZoneCodes", 1}, {"zoneCodesConflict", 2}, {"regionalSubscNotSupported", 3}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("RegionalSubscriptionResponse");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long RegionalSubscriptionResponse::Get(const std::string& valueName) const
{
    if (valueName == "msc-AreaRestricted")
    {
        return 0;
    }
    else if (valueName == "tooManyZoneCodes")
    {
        return 1;
    }
    else if (valueName == "zoneCodesConflict")
    {
        return 2;
    }
    else if (valueName == "regionalSubscNotSupported")
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

std::string RegionalSubscriptionResponse::Get(long value) const
{
    if (value == 0)
    {
        return "msc-AreaRestricted";
    }
    else if (value == 1)
    {
        return "tooManyZoneCodes";
    }
    else if (value == 2)
    {
        return "zoneCodesConflict";
    }
    else if (value == 3)
    {
        return "regionalSubscNotSupported";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string RegionalSubscriptionResponse::GetExt(long value) const
{
    return "";
}





