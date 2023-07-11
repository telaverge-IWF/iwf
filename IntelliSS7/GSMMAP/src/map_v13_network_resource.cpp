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


#include <map_v13_network_resource.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v13;



AsnDescObject* NetworkResource::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new NetworkResource(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        staticDesc._valueSet.insert(5);
        staticDesc._valueSet.insert(6);
        staticDesc._valueSet.insert(7);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"plmn", 0}, {"hlr", 1}, {"vlr", 2}, {"pvlr", 3}, {"controllingMSC", 4}, {"vmsc", 5}, {"eir", 6}, {"rss", 7}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("NetworkResource");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long NetworkResource::Get(const std::string& valueName) const
{
    if (valueName == "plmn")
    {
        return 0;
    }
    else if (valueName == "hlr")
    {
        return 1;
    }
    else if (valueName == "vlr")
    {
        return 2;
    }
    else if (valueName == "pvlr")
    {
        return 3;
    }
    else if (valueName == "controllingMSC")
    {
        return 4;
    }
    else if (valueName == "vmsc")
    {
        return 5;
    }
    else if (valueName == "eir")
    {
        return 6;
    }
    else if (valueName == "rss")
    {
        return 7;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string NetworkResource::Get(long value) const
{
    if (value == 0)
    {
        return "plmn";
    }
    else if (value == 1)
    {
        return "hlr";
    }
    else if (value == 2)
    {
        return "vlr";
    }
    else if (value == 3)
    {
        return "pvlr";
    }
    else if (value == 4)
    {
        return "controllingMSC";
    }
    else if (value == 5)
    {
        return "vmsc";
    }
    else if (value == 6)
    {
        return "eir";
    }
    else if (value == 7)
    {
        return "rss";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string NetworkResource::GetExt(long value) const
{
    return "";
}





