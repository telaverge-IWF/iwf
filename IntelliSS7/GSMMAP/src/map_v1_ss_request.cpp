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


#include <map_v1_ss_request.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v1;



AsnDescObject* SS_Request::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new SS_Request(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        staticDesc._valueSet.insert(5);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"registration", 0}, {"erasure", 1}, {"activation", 2}, {"deactivation", 3}, {"interrogation", 4}, {"invoke", 5}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("SS-Request");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long SS_Request::Get(const std::string& valueName) const
{
    if (valueName == "registration")
    {
        return 0;
    }
    else if (valueName == "erasure")
    {
        return 1;
    }
    else if (valueName == "activation")
    {
        return 2;
    }
    else if (valueName == "deactivation")
    {
        return 3;
    }
    else if (valueName == "interrogation")
    {
        return 4;
    }
    else if (valueName == "invoke")
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

std::string SS_Request::Get(long value) const
{
    if (value == 0)
    {
        return "registration";
    }
    else if (value == 1)
    {
        return "erasure";
    }
    else if (value == 2)
    {
        return "activation";
    }
    else if (value == 3)
    {
        return "deactivation";
    }
    else if (value == 4)
    {
        return "interrogation";
    }
    else if (value == 5)
    {
        return "invoke";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string SS_Request::GetExt(long value) const
{
    return "";
}




