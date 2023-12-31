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


#include <map_v9_notification_to_ms_user.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v9;



AsnDescObject* NotificationToMSUser::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new NotificationToMSUser(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueExtSet.insert(3);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"notifyLocationAllowed", 0}, {"notifyAndVerify-LocationAllowedIfNoResponse", 1}, {"notifyAndVerify-LocationNotAllowedIfNoResponse", 2}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{"locationNotAllowed", 3}, {NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("NotificationToMSUser");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long NotificationToMSUser::Get(const std::string& valueName) const
{
    if (valueName == "notifyLocationAllowed")
    {
        return 0;
    }
    else if (valueName == "notifyAndVerify-LocationAllowedIfNoResponse")
    {
        return 1;
    }
    else if (valueName == "notifyAndVerify-LocationNotAllowedIfNoResponse")
    {
        return 2;
    }
    else if (valueName == "locationNotAllowed")
    {
        return 3;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string NotificationToMSUser::Get(long value) const
{
    if (value == 0)
    {
        return "notifyLocationAllowed";
    }
    else if (value == 1)
    {
        return "notifyAndVerify-LocationAllowedIfNoResponse";
    }
    else if (value == 2)
    {
        return "notifyAndVerify-LocationNotAllowedIfNoResponse";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string NotificationToMSUser::GetExt(long value) const
{
    if (value == 3)
    {
        return "locationNotAllowed";
    }
    else
    {
        return "";
    }
}





