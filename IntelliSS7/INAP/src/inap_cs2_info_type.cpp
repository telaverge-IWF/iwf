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


#include <inap_cs2_info_type.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace inap_cs2;



AsnDescObject* InfoType::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_INAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new InfoType(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"numericString", 0}, {"characterString", 1}, {"iA5String", 2}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("InfoType");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long InfoType::Get(const std::string& valueName) const
{
    if (valueName == "numericString")
    {
        return 0;
    }
    else if (valueName == "characterString")
    {
        return 1;
    }
    else if (valueName == "iA5String")
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

std::string InfoType::Get(long value) const
{
    if (value == 0)
    {
        return "numericString";
    }
    else if (value == 1)
    {
        return "characterString";
    }
    else if (value == 2)
    {
        return "iA5String";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string InfoType::GetExt(long value) const
{
    return "";
}




