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


#include <map_v3_sm_delivery_outcome.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v3;



AsnDescObject* SM_DeliveryOutcome::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new SM_DeliveryOutcome(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"memoryCapacityExceeded", 0}, {"absentSubscriber", 1}, {"successfulTransfer", 2}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("SM-DeliveryOutcome");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long SM_DeliveryOutcome::Get(const std::string& valueName) const
{
    if (valueName == "memoryCapacityExceeded")
    {
        return 0;
    }
    else if (valueName == "absentSubscriber")
    {
        return 1;
    }
    else if (valueName == "successfulTransfer")
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

std::string SM_DeliveryOutcome::Get(long value) const
{
    if (value == 0)
    {
        return "memoryCapacityExceeded";
    }
    else if (value == 1)
    {
        return "absentSubscriber";
    }
    else if (value == 2)
    {
        return "successfulTransfer";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string SM_DeliveryOutcome::GetExt(long value) const
{
    return "";
}




