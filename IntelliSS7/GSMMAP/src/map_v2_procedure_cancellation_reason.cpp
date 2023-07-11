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


#include <map_v2_procedure_cancellation_reason.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v2;



AsnDescObject* ProcedureCancellationReason::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new ProcedureCancellationReason(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        staticDesc._valueSet.insert(5);
        staticDesc._valueSet.insert(6);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"handoverCancellation", 0}, {"radioChannelRelease", 1}, {"networkPathRelease", 2}, {"callRelease", 3}, {"associatedProcedureFailure", 4}, {"tandemDialogueRelease", 5}, {"remoteOperationsFailure", 6}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("ProcedureCancellationReason");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long ProcedureCancellationReason::Get(const std::string& valueName) const
{
    if (valueName == "handoverCancellation")
    {
        return 0;
    }
    else if (valueName == "radioChannelRelease")
    {
        return 1;
    }
    else if (valueName == "networkPathRelease")
    {
        return 2;
    }
    else if (valueName == "callRelease")
    {
        return 3;
    }
    else if (valueName == "associatedProcedureFailure")
    {
        return 4;
    }
    else if (valueName == "tandemDialogueRelease")
    {
        return 5;
    }
    else if (valueName == "remoteOperationsFailure")
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

std::string ProcedureCancellationReason::Get(long value) const
{
    if (value == 0)
    {
        return "handoverCancellation";
    }
    else if (value == 1)
    {
        return "radioChannelRelease";
    }
    else if (value == 2)
    {
        return "networkPathRelease";
    }
    else if (value == 3)
    {
        return "callRelease";
    }
    else if (value == 4)
    {
        return "associatedProcedureFailure";
    }
    else if (value == 5)
    {
        return "tandemDialogueRelease";
    }
    else if (value == 6)
    {
        return "remoteOperationsFailure";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string ProcedureCancellationReason::GetExt(long value) const
{
    return "";
}





