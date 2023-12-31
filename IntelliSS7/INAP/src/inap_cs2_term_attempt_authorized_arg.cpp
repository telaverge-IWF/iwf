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


#include <inap_cs2_term_attempt_authorized_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescSequenceOf.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type DpSpecificCommonParameters is a reference => no code generated.

// Type CalledPartyBusinessGroupID is a reference => no code generated.

// Type CalledPartySubaddress is a reference => no code generated.

// Type CallingPartyBusinessGroupID is a reference => no code generated.

// Type OriginalCalledPartyID is a reference => no code generated.

// Type RedirectingPartyID is a reference => no code generated.

// Type RedirectionInformation is a reference => no code generated.

// Type RouteList is a reference => no code generated.

// Type TravellingClassMark is a reference => no code generated.



////////// Begin Nested Class //////////


// Type ExtensionField is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* TermAttemptAuthorizedArg::Extensions::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_INAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new Extensions(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 9));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 2;
        staticDesc._element = GetExtensionFieldStaticDescription();
        staticDesc.SetNamedTypeName("extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TermAttemptAuthorizedArg::Extensions::GetExtensionFieldStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(3);

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
        staticDesc.SetCloneForFactory(new ExtensionField(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = ExtensionField::GetTypeStaticDescription();
        staticDesc._elementVect[1] = ExtensionField::GetCriticalityStaticDescription();
        staticDesc._elementVect[2] = ExtensionField::GetValueStaticDescription();
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


// Type CallingPartySubaddress is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* TermAttemptAuthorizedArg::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(11);

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

        staticDesc.SetCloneForFactory(new TermAttemptAuthorizedArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetDpSpecificCommonParametersStaticDescription();
        staticDesc._elementVect[1] = GetCalledPartyBusinessGroupIDStaticDescription();
        staticDesc._elementVect[2] = GetCalledPartySubaddressStaticDescription();
        staticDesc._elementVect[3] = GetCallingPartyBusinessGroupIDStaticDescription();
        staticDesc._elementVect[4] = GetOriginalCalledPartyIDStaticDescription();
        staticDesc._elementVect[5] = GetRedirectingPartyIDStaticDescription();
        staticDesc._elementVect[6] = GetRedirectionInformationStaticDescription();
        staticDesc._elementVect[7] = GetRouteListStaticDescription();
        staticDesc._elementVect[8] = GetTravellingClassMarkStaticDescription();
        staticDesc._elementVect[9] = GetExtensionsStaticDescription();
        staticDesc._elementVect[10] = GetCallingPartySubaddressStaticDescription();
        staticDesc.SetTypeName("TermAttemptAuthorizedArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TermAttemptAuthorizedArg::GetDpSpecificCommonParametersStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(22);

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
        staticDesc.SetCloneForFactory(new DpSpecificCommonParameters(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = DpSpecificCommonParameters::GetServiceAddressInformationStaticDescription();
        staticDesc._elementVect[1] = DpSpecificCommonParameters::GetBearerCapabilityStaticDescription();
        staticDesc._elementVect[2] = DpSpecificCommonParameters::GetCalledPartyNumberStaticDescription();
        staticDesc._elementVect[3] = DpSpecificCommonParameters::GetCallingPartyNumberStaticDescription();
        staticDesc._elementVect[4] = DpSpecificCommonParameters::GetCallingPartysCategoryStaticDescription();
        staticDesc._elementVect[5] = DpSpecificCommonParameters::GetIPSSPCapabilitiesStaticDescription();
        staticDesc._elementVect[6] = DpSpecificCommonParameters::GetIPAvailableStaticDescription();
        staticDesc._elementVect[7] = DpSpecificCommonParameters::GetISDNAccessRelatedInformationStaticDescription();
        staticDesc._elementVect[8] = DpSpecificCommonParameters::GetCGEncounteredStaticDescription();
        staticDesc._elementVect[9] = DpSpecificCommonParameters::GetLocationNumberStaticDescription();
        staticDesc._elementVect[10] = DpSpecificCommonParameters::GetServiceProfileIdentifierStaticDescription();
        staticDesc._elementVect[11] = DpSpecificCommonParameters::GetTerminalTypeStaticDescription();
        staticDesc._elementVect[12] = DpSpecificCommonParameters::GetExtensionsStaticDescription();
        staticDesc._elementVect[13] = DpSpecificCommonParameters::GetChargeNumberStaticDescription();
        staticDesc._elementVect[14] = DpSpecificCommonParameters::GetServingAreaIDStaticDescription();
        staticDesc._elementVect[15] = DpSpecificCommonParameters::GetServiceInteractionIndicatorsStaticDescription();
        staticDesc._elementVect[16] = DpSpecificCommonParameters::GetINServiceCompatibilityIndicationStaticDescription();
        staticDesc._elementVect[17] = DpSpecificCommonParameters::GetServiceInteractionIndicatorsTwoStaticDescription();
        staticDesc._elementVect[18] = DpSpecificCommonParameters::GetUSIServiceIndicatorStaticDescription();
        staticDesc._elementVect[19] = DpSpecificCommonParameters::GetUSIInformationStaticDescription();
        staticDesc._elementVect[20] = DpSpecificCommonParameters::GetForwardGVNSStaticDescription();
        staticDesc._elementVect[21] = DpSpecificCommonParameters::GetCreatedCallSegmentAssociationStaticDescription();
        staticDesc.SetNamedTypeName("dpSpecificCommonParameters");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TermAttemptAuthorizedArg::GetCalledPartyBusinessGroupIDStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescOctetString staticDesc;

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
        staticDesc.SetCloneForFactory(new CalledPartyBusinessGroupID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("calledPartyBusinessGroupID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TermAttemptAuthorizedArg::GetCalledPartySubaddressStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescOctetString staticDesc;

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
        staticDesc.SetCloneForFactory(new CalledPartySubaddress(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("calledPartySubaddress");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TermAttemptAuthorizedArg::GetCallingPartyBusinessGroupIDStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescOctetString staticDesc;

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
        staticDesc.SetCloneForFactory(new CallingPartyBusinessGroupID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 3));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("callingPartyBusinessGroupID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TermAttemptAuthorizedArg::GetOriginalCalledPartyIDStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescOctetString staticDesc;

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
        staticDesc.SetCloneForFactory(new OriginalCalledPartyID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 4));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 15;
        staticDesc.SetNamedTypeName("originalCalledPartyID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TermAttemptAuthorizedArg::GetRedirectingPartyIDStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescOctetString staticDesc;

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
        staticDesc.SetCloneForFactory(new RedirectingPartyID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 5));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 15;
        staticDesc.SetNamedTypeName("redirectingPartyID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TermAttemptAuthorizedArg::GetRedirectionInformationStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescOctetString staticDesc;

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
        staticDesc.SetCloneForFactory(new RedirectionInformation(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 6));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 2;
        staticDesc._maxSize = 2;
        staticDesc.SetNamedTypeName("redirectionInformation");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TermAttemptAuthorizedArg::GetRouteListStaticDescription()
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
        staticDesc.SetCloneForFactory(new RouteList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 7));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 3;
        staticDesc._element = RouteList::GetOCTETSTRINGStaticDescription();
        staticDesc.SetNamedTypeName("routeList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TermAttemptAuthorizedArg::GetTravellingClassMarkStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescOctetString staticDesc;

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
        staticDesc.SetCloneForFactory(new TravellingClassMark(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 8));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 15;
        staticDesc.SetNamedTypeName("travellingClassMark");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TermAttemptAuthorizedArg::GetExtensionsStaticDescription()
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
        staticDesc.SetCloneForFactory(new Extensions(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 9));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 2;
        staticDesc._element = Extensions::GetExtensionFieldStaticDescription();
        staticDesc.SetNamedTypeName("extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TermAttemptAuthorizedArg::GetCallingPartySubaddressStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescOctetString staticDesc;

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
        staticDesc.SetCloneForFactory(new CallingPartySubaddress(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("callingPartySubaddress");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





