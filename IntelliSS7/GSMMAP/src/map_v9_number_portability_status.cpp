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


#include <map_v9_number_portability_status.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v9;



AsnDescObject* NumberPortabilityStatus::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new NumberPortabilityStatus(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueExtSet.insert(4);
        staticDesc._valueExtSet.insert(5);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"notKnownToBePorted", 0}, {"ownNumberPortedOut", 1}, {"foreignNumberPortedToForeignNetwork", 2}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{"ownNumberNotPortedOut", 4}, {"foreignNumberPortedIn", 5}, {NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("NumberPortabilityStatus");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long NumberPortabilityStatus::Get(const std::string& valueName) const
{
    if (valueName == "notKnownToBePorted")
    {
        return 0;
    }
    else if (valueName == "ownNumberPortedOut")
    {
        return 1;
    }
    else if (valueName == "foreignNumberPortedToForeignNetwork")
    {
        return 2;
    }
    else if (valueName == "ownNumberNotPortedOut")
    {
        return 4;
    }
    else if (valueName == "foreignNumberPortedIn")
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

std::string NumberPortabilityStatus::Get(long value) const
{
    if (value == 0)
    {
        return "notKnownToBePorted";
    }
    else if (value == 1)
    {
        return "ownNumberPortedOut";
    }
    else if (value == 2)
    {
        return "foreignNumberPortedToForeignNetwork";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string NumberPortabilityStatus::GetExt(long value) const
{
    if (value == 4)
    {
        return "ownNumberNotPortedOut";
    }
    else if (value == 5)
    {
        return "foreignNumberPortedIn";
    }
    else
    {
        return "";
    }
}





