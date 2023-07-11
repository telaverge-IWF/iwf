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


#include <map_v1_hunt_group_access_selection_order.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v1;



AsnDescObject* HuntGroupAccessSelectionOrder::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new HuntGroupAccessSelectionOrder(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"random", 0}, {"sequential", 1}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("HuntGroupAccessSelectionOrder");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long HuntGroupAccessSelectionOrder::Get(const std::string& valueName) const
{
    if (valueName == "random")
    {
        return 0;
    }
    else if (valueName == "sequential")
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

std::string HuntGroupAccessSelectionOrder::Get(long value) const
{
    if (value == 0)
    {
        return "random";
    }
    else if (value == 1)
    {
        return "sequential";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string HuntGroupAccessSelectionOrder::GetExt(long value) const
{
    return "";
}




