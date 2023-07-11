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


#include <map_v13_override_category.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v13;



AsnDescObject* OverrideCategory::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new OverrideCategory(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"overrideEnabled", 0}, {"overrideDisabled", 1}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("OverrideCategory");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long OverrideCategory::Get(const std::string& valueName) const
{
    if (valueName == "overrideEnabled")
    {
        return 0;
    }
    else if (valueName == "overrideDisabled")
    {
        return 1;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string OverrideCategory::Get(long value) const
{
    if (value == 0)
    {
        return "overrideEnabled";
    }
    else if (value == 1)
    {
        return "overrideDisabled";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string OverrideCategory::GetExt(long value) const
{
    return "";
}





