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


#include <inap_cs2_connected_number_treatment_ind.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace inap_cs2;



AsnDescObject* ConnectedNumberTreatmentInd::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new ConnectedNumberTreatmentInd(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"noINImpact", 0}, {"presentationRestricted", 1}, {"presentCalledINNumber", 2}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("ConnectedNumberTreatmentInd");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long ConnectedNumberTreatmentInd::Get(const std::string& valueName) const
{
    if (valueName == "noINImpact")
    {
        return 0;
    }
    else if (valueName == "presentationRestricted")
    {
        return 1;
    }
    else if (valueName == "presentCalledINNumber")
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

std::string ConnectedNumberTreatmentInd::Get(long value) const
{
    if (value == 0)
    {
        return "noINImpact";
    }
    else if (value == 1)
    {
        return "presentationRestricted";
    }
    else if (value == 2)
    {
        return "presentCalledINNumber";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string ConnectedNumberTreatmentInd::GetExt(long value) const
{
    return "";
}





