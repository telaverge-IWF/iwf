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


#include <map_v13_absent_subscriber_reason.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v13;



AsnDescObject* AbsentSubscriberReason::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new AbsentSubscriberReason(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueExtSet.insert(3);
        staticDesc._valueExtSet.insert(4);
        staticDesc._valueExtSet.insert(5);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"imsiDetach", 0}, {"restrictedArea", 1}, {"noPageResponse", 2}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{"purgedMS", 3}, {"mtRoamingRetry", 4}, {"busySubscriber", 5}, {NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("AbsentSubscriberReason");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long AbsentSubscriberReason::Get(const std::string& valueName) const
{
    if (valueName == "imsiDetach")
    {
        return 0;
    }
    else if (valueName == "restrictedArea")
    {
        return 1;
    }
    else if (valueName == "noPageResponse")
    {
        return 2;
    }
    else if (valueName == "purgedMS")
    {
        return 3;
    }
    else if (valueName == "mtRoamingRetry")
    {
        return 4;
    }
    else if (valueName == "busySubscriber")
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

std::string AbsentSubscriberReason::Get(long value) const
{
    if (value == 0)
    {
        return "imsiDetach";
    }
    else if (value == 1)
    {
        return "restrictedArea";
    }
    else if (value == 2)
    {
        return "noPageResponse";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string AbsentSubscriberReason::GetExt(long value) const
{
    if (value == 3)
    {
        return "purgedMS";
    }
    else if (value == 4)
    {
        return "mtRoamingRetry";
    }
    else if (value == 5)
    {
        return "busySubscriber";
    }
    else
    {
        return "";
    }
}





