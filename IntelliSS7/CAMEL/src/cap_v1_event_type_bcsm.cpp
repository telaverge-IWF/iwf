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


#include <cap_v1_event_type_bcsm.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace cap_v1;



AsnDescObject* EventTypeBCSM::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new EventTypeBCSM(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(7);
        staticDesc._valueSet.insert(9);
        staticDesc._valueSet.insert(12);
        staticDesc._valueSet.insert(15);
        staticDesc._valueSet.insert(17);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"collectedInfo", 2}, {"oAnswer", 7}, {"oDisconnect", 9}, {"termAttemptAuthorized", 12}, {"tAnswer", 15}, {"tDisconnect", 17}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("EventTypeBCSM");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long EventTypeBCSM::Get(const std::string& valueName) const
{
    if (valueName == "collectedInfo")
    {
        return 2;
    }
    else if (valueName == "oAnswer")
    {
        return 7;
    }
    else if (valueName == "oDisconnect")
    {
        return 9;
    }
    else if (valueName == "termAttemptAuthorized")
    {
        return 12;
    }
    else if (valueName == "tAnswer")
    {
        return 15;
    }
    else if (valueName == "tDisconnect")
    {
        return 17;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string EventTypeBCSM::Get(long value) const
{
    if (value == 2)
    {
        return "collectedInfo";
    }
    else if (value == 7)
    {
        return "oAnswer";
    }
    else if (value == 9)
    {
        return "oDisconnect";
    }
    else if (value == 12)
    {
        return "termAttemptAuthorized";
    }
    else if (value == 15)
    {
        return "tAnswer";
    }
    else if (value == 17)
    {
        return "tDisconnect";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string EventTypeBCSM::GetExt(long value) const
{
    return "";
}




