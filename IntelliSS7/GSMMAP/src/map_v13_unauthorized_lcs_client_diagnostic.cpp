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


#include <map_v13_unauthorized_lcs_client_diagnostic.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v13;



AsnDescObject* UnauthorizedLCSClient_Diagnostic::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new UnauthorizedLCSClient_Diagnostic(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        staticDesc._valueExtSet.insert(5);
        staticDesc._valueExtSet.insert(6);
        staticDesc._valueExtSet.insert(7);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"noAdditionalInformation", 0}, {"clientNotInMSPrivacyExceptionList", 1}, {"callToClientNotSetup", 2}, {"privacyOverrideNotApplicable", 3}, {"disallowedByLocalRegulatoryRequirements", 4}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{"unauthorizedPrivacyClass", 5}, {"unauthorizedCallSessionUnrelatedExternalClient", 6}, {"unauthorizedCallSessionRelatedExternalClient", 7}, {NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("UnauthorizedLCSClient-Diagnostic");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long UnauthorizedLCSClient_Diagnostic::Get(const std::string& valueName) const
{
    if (valueName == "noAdditionalInformation")
    {
        return 0;
    }
    else if (valueName == "clientNotInMSPrivacyExceptionList")
    {
        return 1;
    }
    else if (valueName == "callToClientNotSetup")
    {
        return 2;
    }
    else if (valueName == "privacyOverrideNotApplicable")
    {
        return 3;
    }
    else if (valueName == "disallowedByLocalRegulatoryRequirements")
    {
        return 4;
    }
    else if (valueName == "unauthorizedPrivacyClass")
    {
        return 5;
    }
    else if (valueName == "unauthorizedCallSessionUnrelatedExternalClient")
    {
        return 6;
    }
    else if (valueName == "unauthorizedCallSessionRelatedExternalClient")
    {
        return 7;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string UnauthorizedLCSClient_Diagnostic::Get(long value) const
{
    if (value == 0)
    {
        return "noAdditionalInformation";
    }
    else if (value == 1)
    {
        return "clientNotInMSPrivacyExceptionList";
    }
    else if (value == 2)
    {
        return "callToClientNotSetup";
    }
    else if (value == 3)
    {
        return "privacyOverrideNotApplicable";
    }
    else if (value == 4)
    {
        return "disallowedByLocalRegulatoryRequirements";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string UnauthorizedLCSClient_Diagnostic::GetExt(long value) const
{
    if (value == 5)
    {
        return "unauthorizedPrivacyClass";
    }
    else if (value == 6)
    {
        return "unauthorizedCallSessionUnrelatedExternalClient";
    }
    else if (value == 7)
    {
        return "unauthorizedCallSessionRelatedExternalClient";
    }
    else
    {
        return "";
    }
}




