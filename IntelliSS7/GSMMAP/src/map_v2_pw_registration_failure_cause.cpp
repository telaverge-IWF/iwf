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


#include <map_v2_pw_registration_failure_cause.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v2;



AsnDescObject* PW_RegistrationFailureCause::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new PW_RegistrationFailureCause(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"undetermined", 0}, {"invalidFormat", 1}, {"newPasswordsMismatch", 2}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("PW-RegistrationFailureCause");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long PW_RegistrationFailureCause::Get(const std::string& valueName) const
{
    if (valueName == "undetermined")
    {
        return 0;
    }
    else if (valueName == "invalidFormat")
    {
        return 1;
    }
    else if (valueName == "newPasswordsMismatch")
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

std::string PW_RegistrationFailureCause::Get(long value) const
{
    if (value == 0)
    {
        return "undetermined";
    }
    else if (value == 1)
    {
        return "invalidFormat";
    }
    else if (value == 2)
    {
        return "newPasswordsMismatch";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string PW_RegistrationFailureCause::GetExt(long value) const
{
    return "";
}





