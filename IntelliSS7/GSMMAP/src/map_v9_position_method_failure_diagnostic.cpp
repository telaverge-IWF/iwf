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


#include <map_v9_position_method_failure_diagnostic.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v9;



AsnDescObject* PositionMethodFailure_Diagnostic::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new PositionMethodFailure_Diagnostic(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        staticDesc._valueSet.insert(5);
        staticDesc._valueSet.insert(6);
        staticDesc._valueSet.insert(7);
        staticDesc._valueSet.insert(8);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"congestion", 0}, {"insufficientResources", 1}, {"insufficientMeasurementData", 2}, {"inconsistentMeasurementData", 3}, {"locationProcedureNotCompleted", 4}, {"locationProcedureNotSupportedByTargetMS", 5}, {"qoSNotAttainable", 6}, {"positionMethodNotAvailableInNetwork", 7}, {"positionMethodNotAvailableInLocationArea", 8}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("PositionMethodFailure-Diagnostic");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long PositionMethodFailure_Diagnostic::Get(const std::string& valueName) const
{
    if (valueName == "congestion")
    {
        return 0;
    }
    else if (valueName == "insufficientResources")
    {
        return 1;
    }
    else if (valueName == "insufficientMeasurementData")
    {
        return 2;
    }
    else if (valueName == "inconsistentMeasurementData")
    {
        return 3;
    }
    else if (valueName == "locationProcedureNotCompleted")
    {
        return 4;
    }
    else if (valueName == "locationProcedureNotSupportedByTargetMS")
    {
        return 5;
    }
    else if (valueName == "qoSNotAttainable")
    {
        return 6;
    }
    else if (valueName == "positionMethodNotAvailableInNetwork")
    {
        return 7;
    }
    else if (valueName == "positionMethodNotAvailableInLocationArea")
    {
        return 8;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string PositionMethodFailure_Diagnostic::Get(long value) const
{
    if (value == 0)
    {
        return "congestion";
    }
    else if (value == 1)
    {
        return "insufficientResources";
    }
    else if (value == 2)
    {
        return "insufficientMeasurementData";
    }
    else if (value == 3)
    {
        return "inconsistentMeasurementData";
    }
    else if (value == 4)
    {
        return "locationProcedureNotCompleted";
    }
    else if (value == 5)
    {
        return "locationProcedureNotSupportedByTargetMS";
    }
    else if (value == 6)
    {
        return "qoSNotAttainable";
    }
    else if (value == 7)
    {
        return "positionMethodNotAvailableInNetwork";
    }
    else if (value == 8)
    {
        return "positionMethodNotAvailableInLocationArea";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string PositionMethodFailure_Diagnostic::GetExt(long value) const
{
    return "";
}




