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


#include <map_v13_used_rat_type.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v13;



AsnDescObject* Used_RAT_Type::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new Used_RAT_Type(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"utran", 0}, {"geran", 1}, {"gan", 2}, {"i-hspa-evolution", 3}, {"e-utran", 4}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("Used-RAT-Type");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long Used_RAT_Type::Get(const std::string& valueName) const
{
    if (valueName == "utran")
    {
        return 0;
    }
    else if (valueName == "geran")
    {
        return 1;
    }
    else if (valueName == "gan")
    {
        return 2;
    }
    else if (valueName == "i-hspa-evolution")
    {
        return 3;
    }
    else if (valueName == "e-utran")
    {
        return 4;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string Used_RAT_Type::Get(long value) const
{
    if (value == 0)
    {
        return "utran";
    }
    else if (value == 1)
    {
        return "geran";
    }
    else if (value == 2)
    {
        return "gan";
    }
    else if (value == 3)
    {
        return "i-hspa-evolution";
    }
    else if (value == 4)
    {
        return "e-utran";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string Used_RAT_Type::GetExt(long value) const
{
    return "";
}





