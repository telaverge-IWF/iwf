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


#include <map_v13_ccbs_subscriber_status.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v13;



AsnDescObject* CCBS_SubscriberStatus::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new CCBS_SubscriberStatus(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"ccbsNotIdle", 0}, {"ccbsIdle", 1}, {"ccbsNotReachable", 2}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("CCBS-SubscriberStatus");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long CCBS_SubscriberStatus::Get(const std::string& valueName) const
{
    if (valueName == "ccbsNotIdle")
    {
        return 0;
    }
    else if (valueName == "ccbsIdle")
    {
        return 1;
    }
    else if (valueName == "ccbsNotReachable")
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

std::string CCBS_SubscriberStatus::Get(long value) const
{
    if (value == 0)
    {
        return "ccbsNotIdle";
    }
    else if (value == 1)
    {
        return "ccbsIdle";
    }
    else if (value == 2)
    {
        return "ccbsNotReachable";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string CCBS_SubscriberStatus::GetExt(long value) const
{
    return "";
}





