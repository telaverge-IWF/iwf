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


#include <map_v13_lcs_event.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v13;



AsnDescObject* LCS_Event::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new LCS_Event(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueExtSet.insert(3);
        staticDesc._valueExtSet.insert(4);
        staticDesc._valueExtSet.insert(5);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"emergencyCallOrigination", 0}, {"emergencyCallRelease", 1}, {"mo-lr", 2}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{"deferredmt-lrResponse", 3}, {"deferredmo-lrTTTPInitiation", 4}, {"emergencyCallHandover", 5}, {NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("LCS-Event");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long LCS_Event::Get(const std::string& valueName) const
{
    if (valueName == "emergencyCallOrigination")
    {
        return 0;
    }
    else if (valueName == "emergencyCallRelease")
    {
        return 1;
    }
    else if (valueName == "mo-lr")
    {
        return 2;
    }
    else if (valueName == "deferredmt-lrResponse")
    {
        return 3;
    }
    else if (valueName == "deferredmo-lrTTTPInitiation")
    {
        return 4;
    }
    else if (valueName == "emergencyCallHandover")
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

std::string LCS_Event::Get(long value) const
{
    if (value == 0)
    {
        return "emergencyCallOrigination";
    }
    else if (value == 1)
    {
        return "emergencyCallRelease";
    }
    else if (value == 2)
    {
        return "mo-lr";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string LCS_Event::GetExt(long value) const
{
    if (value == 3)
    {
        return "deferredmt-lrResponse";
    }
    else if (value == 4)
    {
        return "deferredmo-lrTTTPInitiation";
    }
    else if (value == 5)
    {
        return "emergencyCallHandover";
    }
    else
    {
        return "";
    }
}





