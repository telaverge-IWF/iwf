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


#include <cap_v3_establish_temporary_connection_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescSequenceOf.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace cap_v3;




////////// Begin Nested Class(es) //////////


// Type AssistingSSPIPRoutingAddress is a reference => no code generated.

// Type CorrelationID is a reference => no code generated.

// Type ScfID is a reference => no code generated.



////////// Begin Nested Class //////////


// Type ExtensionField is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* EstablishTemporaryConnectionArg::Extensions::GetStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 4));
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

AsnDescObject* EstablishTemporaryConnectionArg::Extensions::GetExtensionFieldStaticDescription()
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

// Type ServiceInteractionIndicatorsTwo is a reference => no code generated.

// Type NA_Info is a reference => no code generated.

// Type ChargeNumber is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* EstablishTemporaryConnectionArg::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new EstablishTemporaryConnectionArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetAssistingSSPIPRoutingAddressStaticDescription();
        staticDesc._elementVect[1] = GetCorrelationIDStaticDescription();
        staticDesc._elementVect[2] = GetScfIDStaticDescription();
        staticDesc._elementVect[3] = GetExtensionsStaticDescription();
        staticDesc._elementVect[4] = GetCarrierStaticDescription();
        staticDesc._elementVect[5] = GetServiceInteractionIndicatorsTwoStaticDescription();
        staticDesc._elementVect[6] = GetNa_InfoStaticDescription();
        staticDesc._elementVect[7] = GetChargeNumberStaticDescription();
        staticDesc.SetTypeName("EstablishTemporaryConnectionArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* EstablishTemporaryConnectionArg::GetAssistingSSPIPRoutingAddressStaticDescription()
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
        staticDesc.SetCloneForFactory(new AssistingSSPIPRoutingAddress(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 2;
        staticDesc._maxSize = 16;
        staticDesc.SetNamedTypeName("assistingSSPIPRoutingAddress");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* EstablishTemporaryConnectionArg::GetCorrelationIDStaticDescription()
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
        staticDesc.SetCloneForFactory(new CorrelationID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 2;
        staticDesc._maxSize = 16;
        staticDesc.SetNamedTypeName("correlationID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* EstablishTemporaryConnectionArg::GetScfIDStaticDescription()
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
        staticDesc.SetCloneForFactory(new ScfID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 3));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 2;
        staticDesc._maxSize = 10;
        staticDesc.SetNamedTypeName("scfID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* EstablishTemporaryConnectionArg::GetExtensionsStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 4));
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

AsnDescObject* EstablishTemporaryConnectionArg::GetCarrierStaticDescription()
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

AsnDescObject* EstablishTemporaryConnectionArg::GetServiceInteractionIndicatorsTwoStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 6));
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

AsnDescObject* EstablishTemporaryConnectionArg::GetNa_InfoStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 50));
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

AsnDescObject* EstablishTemporaryConnectionArg::GetChargeNumberStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 51));
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





