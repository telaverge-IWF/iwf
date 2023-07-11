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


#include <inap_cs2_requested_information_type.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace inap_cs2;



AsnDescObject* RequestedInformationType::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new RequestedInformationType(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(30);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"callAttemptElapsedTime", 0}, {"callStopTime", 1}, {"callConnectedElapsedTime", 2}, {"calledAddress", 3}, {"releaseCause", 30}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("RequestedInformationType");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long RequestedInformationType::Get(const std::string& valueName) const
{
    if (valueName == "callAttemptElapsedTime")
    {
        return 0;
    }
    else if (valueName == "callStopTime")
    {
        return 1;
    }
    else if (valueName == "callConnectedElapsedTime")
    {
        return 2;
    }
    else if (valueName == "calledAddress")
    {
        return 3;
    }
    else if (valueName == "releaseCause")
    {
        return 30;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string RequestedInformationType::Get(long value) const
{
    if (value == 0)
    {
        return "callAttemptElapsedTime";
    }
    else if (value == 1)
    {
        return "callStopTime";
    }
    else if (value == 2)
    {
        return "callConnectedElapsedTime";
    }
    else if (value == 3)
    {
        return "calledAddress";
    }
    else if (value == 30)
    {
        return "releaseCause";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string RequestedInformationType::GetExt(long value) const
{
    return "";
}





