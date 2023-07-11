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


#include <map_v13_lcs_client_internal_id.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v13;



AsnDescObject* LCSClientInternalID::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new LCSClientInternalID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"broadcastService", 0}, {"o-andM-HPLMN", 1}, {"o-andM-VPLMN", 2}, {"anonymousLocation", 3}, {"targetMSsubscribedService", 4}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("LCSClientInternalID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long LCSClientInternalID::Get(const std::string& valueName) const
{
    if (valueName == "broadcastService")
    {
        return 0;
    }
    else if (valueName == "o-andM-HPLMN")
    {
        return 1;
    }
    else if (valueName == "o-andM-VPLMN")
    {
        return 2;
    }
    else if (valueName == "anonymousLocation")
    {
        return 3;
    }
    else if (valueName == "targetMSsubscribedService")
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

std::string LCSClientInternalID::Get(long value) const
{
    if (value == 0)
    {
        return "broadcastService";
    }
    else if (value == 1)
    {
        return "o-andM-HPLMN";
    }
    else if (value == 2)
    {
        return "o-andM-VPLMN";
    }
    else if (value == 3)
    {
        return "anonymousLocation";
    }
    else if (value == 4)
    {
        return "targetMSsubscribedService";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string LCSClientInternalID::GetExt(long value) const
{
    return "";
}




