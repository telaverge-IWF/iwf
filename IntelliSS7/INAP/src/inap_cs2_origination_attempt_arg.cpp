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


#include <inap_cs2_origination_attempt_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescSequenceOf.h>
#include <AsnDescOctetString.h>
#include <AsnDescChoice.h>
#include <AsnDescInteger.h>
#include <AsnDescEnumerated.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type DpSpecificCommonParameters is a reference => no code generated.

// Type CallingPartyBusinessGroupID is a reference => no code generated.

// Type CallingPartySubaddress is a reference => no code generated.

// Type FacilityGroup is a reference => no code generated.

// Type FacilityGroupMember is a reference => no code generated.

// Type Carrier is a reference => no code generated.

// Type TravellingClassMark is a reference => no code generated.



////////// Begin Nested Class //////////


// Type ExtensionField is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* OriginationAttemptArg::Extensions::GetStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 7));
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

AsnDescObject* OriginationAttemptArg::Extensions::GetExtensionFieldStaticDescription()
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


// Type ComponentType is a reference => no code generated.

// Type ComponentCorrelationID is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* OriginationAttemptArg::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(10);

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

        staticDesc.SetCloneForFactory(new OriginationAttemptArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetDpSpecificCommonParametersStaticDescription();
        staticDesc._elementVect[1] = GetCallingPartyBusinessGroupIDStaticDescription();
        staticDesc._elementVect[2] = GetCallingPartySubaddressStaticDescription();
        staticDesc._elementVect[3] = GetCallingFacilityGroupStaticDescription();
        staticDesc._elementVect[4] = GetCallingFacilityGroupMemberStaticDescription();
        staticDesc._elementVect[5] = GetCarrierStaticDescription();
        staticDesc._elementVect[6] = GetTravellingClassMarkStaticDescription();
        staticDesc._elementVect[7] = GetExtensionsStaticDescription();
        staticDesc._elementVect[8] = GetComponentTypeStaticDescription();
        staticDesc._elementVect[9] = GetComponenttCorrelationIDStaticDescription();
        staticDesc.SetTypeName("OriginationAttemptArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* OriginationAttemptArg::GetDpSpecificCommonParametersStaticDescription()
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

AsnDescObject* OriginationAttemptArg::GetCallingPartyBusinessGroupIDStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("callingPartyBusinessGroupID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* OriginationAttemptArg::GetCallingPartySubaddressStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("callingPartySubaddress");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* OriginationAttemptArg::GetCallingFacilityGroupStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescChoice staticDesc;

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
        staticDesc.SetCloneForFactory(new FacilityGroup(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 3));
        staticDesc._clauseOptional = true;
        staticDesc._choiceList.push_back(FacilityGroup::GetTrunkGroupIDStaticDescription());
        staticDesc._choiceList.push_back(FacilityGroup::GetPrivateFacilityIDStaticDescription());
        staticDesc._choiceList.push_back(FacilityGroup::GetHuntGroupStaticDescription());
        staticDesc._choiceList.push_back(FacilityGroup::GetRouteIndexStaticDescription());
        staticDesc.SetNamedTypeName("callingFacilityGroup");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* OriginationAttemptArg::GetCallingFacilityGroupMemberStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescInteger staticDesc;

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
        staticDesc.SetCloneForFactory(new FacilityGroupMember(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 4));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("callingFacilityGroupMember");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* OriginationAttemptArg::GetCarrierStaticDescription()
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
        staticDesc.SetCloneForFactory(new Carrier(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 5));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("carrier");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* OriginationAttemptArg::GetTravellingClassMarkStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 6));
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

AsnDescObject* OriginationAttemptArg::GetExtensionsStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 7));
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

AsnDescObject* OriginationAttemptArg::GetComponentTypeStaticDescription()
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
        staticDesc.SetCloneForFactory(new ComponentType(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 8));
        staticDesc._clauseOptional = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"any", 0}, {"invoke", 1}, {"rResult", 2}, {"rError", 3}, {"rReject", 4}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("componentType");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* OriginationAttemptArg::GetComponenttCorrelationIDStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescInteger staticDesc;

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
        staticDesc.SetCloneForFactory(new ComponentCorrelationID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("componenttCorrelationID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





