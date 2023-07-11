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


#include <inap_cs2_in_common_arguments.h>

#include <AsnDescSet.h>
#include <AsnDescSetOf.h>
#include <AsnDescSequenceOf.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type InServiceControls is a reference => no code generated.

// Type SecurityParameters is a reference => no code generated.

// Type DistinguishedName is a reference => no code generated.

// Type OperationProgress is a reference => no code generated.



////////// Begin Nested Class //////////


// Type Extension is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* InCommonArguments::Extensions::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSetOf staticDesc;

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

        staticDesc.SetCloneForFactory(new Extensions(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 25));
        staticDesc._clauseOptional = true;
        staticDesc._element = GetExtensionStaticDescription();
        staticDesc.SetNamedTypeName("extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InCommonArguments::Extensions::GetExtensionStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSet staticDesc(3);

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
        staticDesc.SetCloneForFactory(new Extension(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 17));
        staticDesc._elementVect[0] = Extension::GetIdentifierStaticDescription();
        staticDesc._elementVect[1] = Extension::GetCriticalStaticDescription();
        staticDesc._elementVect[2] = Extension::GetItemStaticDescription();
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


////////// End Nested Class(es) //////////

AsnDescObject* InCommonArguments::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSet staticDesc(5);

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

        staticDesc.SetCloneForFactory(new InCommonArguments(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 17));
        staticDesc._elementVect[0] = GetServiceControlsStaticDescription();
        staticDesc._elementVect[1] = GetSecurityParametersStaticDescription();
        staticDesc._elementVect[2] = GetRequestorStaticDescription();
        staticDesc._elementVect[3] = GetOperationProgressStaticDescription();
        staticDesc._elementVect[4] = GetExtensionsStaticDescription();
        staticDesc.SetTypeName("InCommonArguments");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InCommonArguments::GetServiceControlsStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSet staticDesc(2);

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
        staticDesc.SetCloneForFactory(new InServiceControls(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 30));
        staticDesc._clauseOptional = true;
        staticDesc._elementVect[0] = InServiceControls::GetOptionsStaticDescription();
        staticDesc._elementVect[1] = InServiceControls::GetPriorityStaticDescription();
        staticDesc.SetNamedTypeName("serviceControls");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InCommonArguments::GetSecurityParametersStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSet staticDesc(5);

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
        staticDesc.SetCloneForFactory(new SecurityParameters(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 29));
        staticDesc._clauseOptional = true;
        staticDesc._elementVect[0] = SecurityParameters::GetCertification_pathStaticDescription();
        staticDesc._elementVect[1] = SecurityParameters::GetDistinguishedNameStaticDescription();
        staticDesc._elementVect[2] = SecurityParameters::GetTimeStaticDescription();
        staticDesc._elementVect[3] = SecurityParameters::GetRandomStaticDescription();
        staticDesc._elementVect[4] = SecurityParameters::GetTargetStaticDescription();
        staticDesc.SetNamedTypeName("securityParameters");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InCommonArguments::GetRequestorStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequenceOf staticDesc;

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
        staticDesc.SetCloneForFactory(new DistinguishedName(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 28));
        staticDesc._clauseOptional = true;
        staticDesc._element = DistinguishedName::GetRelativeDistinguishedNameStaticDescription();
        staticDesc.SetNamedTypeName("requestor");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InCommonArguments::GetOperationProgressStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSet staticDesc(2);

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
        staticDesc.SetCloneForFactory(new OperationProgress(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 27));
        staticDesc._clauseOptional = true;
        staticDesc._elementVect[0] = OperationProgress::GetNameResolutionPhaseStaticDescription();
        staticDesc._elementVect[1] = OperationProgress::GetNextRDNToBeResolvedStaticDescription();
        staticDesc.SetNamedTypeName("operationProgress");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InCommonArguments::GetExtensionsStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSetOf staticDesc;

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
        staticDesc.SetCloneForFactory(new Extensions(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 25));
        staticDesc._clauseOptional = true;
        staticDesc._element = Extensions::GetExtensionStaticDescription();
        staticDesc.SetNamedTypeName("extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





