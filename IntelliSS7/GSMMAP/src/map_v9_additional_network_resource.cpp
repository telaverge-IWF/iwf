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


#include <map_v9_additional_network_resource.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v9;



AsnDescObject* AdditionalNetworkResource::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new AdditionalNetworkResource(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        staticDesc._valueSet.insert(5);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"sgsn", 0}, {"ggsn", 1}, {"gmlc", 2}, {"gsmSCF", 3}, {"nplr", 4}, {"auc", 5}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("AdditionalNetworkResource");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long AdditionalNetworkResource::Get(const std::string& valueName) const
{
    if (valueName == "sgsn")
    {
        return 0;
    }
    else if (valueName == "ggsn")
    {
        return 1;
    }
    else if (valueName == "gmlc")
    {
        return 2;
    }
    else if (valueName == "gsmSCF")
    {
        return 3;
    }
    else if (valueName == "nplr")
    {
        return 4;
    }
    else if (valueName == "auc")
    {
        return 5;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string AdditionalNetworkResource::Get(long value) const
{
    if (value == 0)
    {
        return "sgsn";
    }
    else if (value == 1)
    {
        return "ggsn";
    }
    else if (value == 2)
    {
        return "gmlc";
    }
    else if (value == 3)
    {
        return "gsmSCF";
    }
    else if (value == 4)
    {
        return "nplr";
    }
    else if (value == 5)
    {
        return "auc";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string AdditionalNetworkResource::GetExt(long value) const
{
    return "";
}





