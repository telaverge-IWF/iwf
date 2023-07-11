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


#include <map_v1_sm_delivery_failure_error_arg.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v1;



AsnDescObject* SM_DeliveryFailureErrorArg::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new SM_DeliveryFailureErrorArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        staticDesc._valueSet.insert(5);
        staticDesc._valueSet.insert(6);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"memoryCapacityExceeded", 0}, {"msProtocolError", 1}, {"msNotEquiped", 2}, {"unknownServiceCenter", 3}, {"scCongestion", 4}, {"invalidSmcAddress", 5}, {"msNotScSubscriber", 6}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("SM-DeliveryFailureErrorArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long SM_DeliveryFailureErrorArg::Get(const std::string& valueName) const
{
    if (valueName == "memoryCapacityExceeded")
    {
        return 0;
    }
    else if (valueName == "msProtocolError")
    {
        return 1;
    }
    else if (valueName == "msNotEquiped")
    {
        return 2;
    }
    else if (valueName == "unknownServiceCenter")
    {
        return 3;
    }
    else if (valueName == "scCongestion")
    {
        return 4;
    }
    else if (valueName == "invalidSmcAddress")
    {
        return 5;
    }
    else if (valueName == "msNotScSubscriber")
    {
        return 6;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string SM_DeliveryFailureErrorArg::Get(long value) const
{
    if (value == 0)
    {
        return "memoryCapacityExceeded";
    }
    else if (value == 1)
    {
        return "msProtocolError";
    }
    else if (value == 2)
    {
        return "msNotEquiped";
    }
    else if (value == 3)
    {
        return "unknownServiceCenter";
    }
    else if (value == 4)
    {
        return "scCongestion";
    }
    else if (value == 5)
    {
        return "invalidSmcAddress";
    }
    else if (value == 6)
    {
        return "msNotScSubscriber";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string SM_DeliveryFailureErrorArg::GetExt(long value) const
{
    return "";
}




