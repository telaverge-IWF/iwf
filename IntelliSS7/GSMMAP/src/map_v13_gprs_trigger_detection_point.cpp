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


#include <map_v13_gprs_trigger_detection_point.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v13;



AsnDescObject* GPRS_TriggerDetectionPoint::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new GPRS_TriggerDetectionPoint(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(11);
        staticDesc._valueSet.insert(12);
        staticDesc._valueSet.insert(14);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"attach", 1}, {"attachChangeOfPosition", 2}, {"pdp-ContextEstablishment", 11}, {"pdp-ContextEstablishmentAcknowledgement", 12}, {"pdp-ContextChangeOfPosition", 14}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("GPRS-TriggerDetectionPoint");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long GPRS_TriggerDetectionPoint::Get(const std::string& valueName) const
{
    if (valueName == "attach")
    {
        return 1;
    }
    else if (valueName == "attachChangeOfPosition")
    {
        return 2;
    }
    else if (valueName == "pdp-ContextEstablishment")
    {
        return 11;
    }
    else if (valueName == "pdp-ContextEstablishmentAcknowledgement")
    {
        return 12;
    }
    else if (valueName == "pdp-ContextChangeOfPosition")
    {
        return 14;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string GPRS_TriggerDetectionPoint::Get(long value) const
{
    if (value == 1)
    {
        return "attach";
    }
    else if (value == 2)
    {
        return "attachChangeOfPosition";
    }
    else if (value == 11)
    {
        return "pdp-ContextEstablishment";
    }
    else if (value == 12)
    {
        return "pdp-ContextEstablishmentAcknowledgement";
    }
    else if (value == 14)
    {
        return "pdp-ContextChangeOfPosition";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string GPRS_TriggerDetectionPoint::GetExt(long value) const
{
    return "";
}





