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


#include <cap_v3_connect_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescSequenceOf.h>
#include <AsnDescNull.h>
#include <AsnDescOctetString.h>
#include <AsnDescSetOf.h>


using namespace its;
using namespace cap_v3;




////////// Begin Nested Class(es) //////////


// Type DestinationRoutingAddress is a reference => no code generated.

// Type AlertingPattern is a reference => no code generated.

// Type OriginalCalledPartyID is a reference => no code generated.



////////// Begin Nested Class //////////


// Type ExtensionField is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* ConnectArg::Extensions::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new Extensions(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 10));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = GetExtensionFieldStaticDescription();
        staticDesc.SetNamedTypeName("extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::Extensions::GetExtensionFieldStaticDescription()
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


// Type Carrier is a reference => no code generated.

// Type CallingPartysCategory is a reference => no code generated.

// Type RedirectingPartyID is a reference => no code generated.

// Type RedirectionInformation is a reference => no code generated.

// Type GenericNumbers is a reference => no code generated.

// Type ServiceInteractionIndicatorsTwo is a reference => no code generated.

// Type ChargeNumber is a reference => no code generated.

// Type CUG_Interlock is a reference => no code generated.


AsnDescObject* ConnectArg::Cug_OutgoingAccess::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescNull staticDesc;

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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new Cug_OutgoingAccess(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 32));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("cug-OutgoingAccess");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


// Type SuppressionOfAnnouncement is a reference => no code generated.

// Type OCSIApplicable is a reference => no code generated.

// Type NA_Info is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* ConnectArg::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(16);

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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new ConnectArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetDestinationRoutingAddressStaticDescription();
        staticDesc._elementVect[1] = GetAlertingPatternStaticDescription();
        staticDesc._elementVect[2] = GetOriginalCalledPartyIDStaticDescription();
        staticDesc._elementVect[3] = GetExtensionsStaticDescription();
        staticDesc._elementVect[4] = GetCarrierStaticDescription();
        staticDesc._elementVect[5] = GetCallingPartysCategoryStaticDescription();
        staticDesc._elementVect[6] = GetRedirectingPartyIDStaticDescription();
        staticDesc._elementVect[7] = GetRedirectionInformationStaticDescription();
        staticDesc._elementVect[8] = GetGenericNumbersStaticDescription();
        staticDesc._elementVect[9] = GetServiceInteractionIndicatorsTwoStaticDescription();
        staticDesc._elementVect[10] = GetChargeNumberStaticDescription();
        staticDesc._elementVect[11] = GetCug_InterlockStaticDescription();
        staticDesc._elementVect[12] = GetCug_OutgoingAccessStaticDescription();
        staticDesc._elementVect[13] = GetSuppressionOfAnnouncementStaticDescription();
        staticDesc._elementVect[14] = GetOCSIApplicableStaticDescription();
        staticDesc._elementVect[15] = GetNa_InfoStaticDescription();
        staticDesc.SetTypeName("ConnectArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetDestinationRoutingAddressStaticDescription()
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
        staticDesc.SetCloneForFactory(new DestinationRoutingAddress(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 1;
        staticDesc._element = DestinationRoutingAddress::GetCalledPartyNumberStaticDescription();
        staticDesc.SetNamedTypeName("destinationRoutingAddress");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetAlertingPatternStaticDescription()
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
        staticDesc.SetCloneForFactory(new AlertingPattern(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 3;
        staticDesc._maxSize = 3;
        staticDesc.SetNamedTypeName("alertingPattern");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetOriginalCalledPartyIDStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 6));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 2;
        staticDesc._maxSize = 10;
        staticDesc.SetNamedTypeName("originalCalledPartyID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetExtensionsStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 10));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = Extensions::GetExtensionFieldStaticDescription();
        staticDesc.SetNamedTypeName("extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetCarrierStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 11));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 4;
        staticDesc._maxSize = 4;
        staticDesc.SetNamedTypeName("carrier");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetCallingPartysCategoryStaticDescription()
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
        staticDesc.SetCloneForFactory(new CallingPartysCategory(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 28));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 1;
        staticDesc.SetNamedTypeName("callingPartysCategory");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetRedirectingPartyIDStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 29));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 2;
        staticDesc._maxSize = 10;
        staticDesc.SetNamedTypeName("redirectingPartyID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetRedirectionInformationStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 30));
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

AsnDescObject* ConnectArg::GetGenericNumbersStaticDescription()
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
        staticDesc.SetCloneForFactory(new GenericNumbers(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 14));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 5;
        staticDesc._element = GenericNumbers::GetGenericNumberStaticDescription();
        staticDesc.SetNamedTypeName("genericNumbers");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetServiceInteractionIndicatorsTwoStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(8);

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
        staticDesc.SetCloneForFactory(new ServiceInteractionIndicatorsTwo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 15));
        staticDesc._clauseOptional = true;
        staticDesc._elementVect[0] = ServiceInteractionIndicatorsTwo::GetForwardServiceInteractionIndStaticDescription();
        staticDesc._elementVect[1] = ServiceInteractionIndicatorsTwo::GetBackwardServiceInteractionsIndStaticDescription();
        staticDesc._elementVect[2] = ServiceInteractionIndicatorsTwo::GetBothwayThroughConnectionIndStaticDescription();
        staticDesc._elementVect[3] = ServiceInteractionIndicatorsTwo::GetConnectedNumberTreatmentIndStaticDescription();
        staticDesc._elementVect[4] = ServiceInteractionIndicatorsTwo::GetNonCUGCallStaticDescription();
        staticDesc._elementVect[5] = ServiceInteractionIndicatorsTwo::GetHoldTreatmentIndicatorStaticDescription();
        staticDesc._elementVect[6] = ServiceInteractionIndicatorsTwo::GetCwTreatmentIndicatorStaticDescription();
        staticDesc._elementVect[7] = ServiceInteractionIndicatorsTwo::GetEctTreatmentIndicatorStaticDescription();
        staticDesc.SetNamedTypeName("serviceInteractionIndicatorsTwo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetChargeNumberStaticDescription()
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
        staticDesc.SetCloneForFactory(new ChargeNumber(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 19));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 2;
        staticDesc._maxSize = 10;
        staticDesc.SetNamedTypeName("chargeNumber");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetCug_InterlockStaticDescription()
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
        staticDesc.SetCloneForFactory(new CUG_Interlock(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 31));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 4;
        staticDesc._maxSize = 4;
        staticDesc.SetNamedTypeName("cug-Interlock");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetCug_OutgoingAccessStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescNull staticDesc;

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
        staticDesc.SetCloneForFactory(new Cug_OutgoingAccess(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 32));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("cug-OutgoingAccess");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetSuppressionOfAnnouncementStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescNull staticDesc;

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
        staticDesc.SetCloneForFactory(new SuppressionOfAnnouncement(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 55));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("suppressionOfAnnouncement");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetOCSIApplicableStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescNull staticDesc;

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
        staticDesc.SetCloneForFactory(new OCSIApplicable(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 56));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("oCSIApplicable");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ConnectArg::GetNa_InfoStaticDescription()
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
        staticDesc.SetCloneForFactory(new NA_Info(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 57));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = NA_Info::GetNaCarrierInformationStaticDescription();
        staticDesc._elementVect[1] = NA_Info::GetNaOliInfoStaticDescription();
        staticDesc._elementVect[2] = NA_Info::GetNaChargeNumberStaticDescription();
        staticDesc.SetNamedTypeName("na-Info");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





