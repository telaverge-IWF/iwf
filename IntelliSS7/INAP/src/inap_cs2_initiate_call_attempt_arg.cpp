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


#include <inap_cs2_initiate_call_attempt_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescSequenceOf.h>
#include <AsnDescOctetString.h>
#include <AsnDescChoice.h>
#include <AsnDescInteger.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type DestinationRoutingAddress is a reference => no code generated.

// Type AlertingPattern is a reference => no code generated.

// Type ISDNAccessRelatedInformation is a reference => no code generated.

// Type TravellingClassMark is a reference => no code generated.



////////// Begin Nested Class //////////


// Type ExtensionField is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* InitiateCallAttemptArg::Extensions::GetStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 4));
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

AsnDescObject* InitiateCallAttemptArg::Extensions::GetExtensionFieldStaticDescription()
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


// Type ServiceInteractionIndicators is a reference => no code generated.

// Type CallingPartyNumber is a reference => no code generated.

// Type LegID is a reference => no code generated.

// Type CallSegmentID is a reference => no code generated.

// Type INServiceCompatibilityResponse is a reference => no code generated.

// Type ServiceInteractionIndicatorsTwo is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* InitiateCallAttemptArg::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new InitiateCallAttemptArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetDestinationRoutingAddressStaticDescription();
        staticDesc._elementVect[1] = GetAlertingPatternStaticDescription();
        staticDesc._elementVect[2] = GetISDNAccessRelatedInformationStaticDescription();
        staticDesc._elementVect[3] = GetTravellingClassMarkStaticDescription();
        staticDesc._elementVect[4] = GetExtensionsStaticDescription();
        staticDesc._elementVect[5] = GetServiceInteractionIndicatorsStaticDescription();
        staticDesc._elementVect[6] = GetCallingPartyNumberStaticDescription();
        staticDesc._elementVect[7] = GetLegToBeCreatedStaticDescription();
        staticDesc._elementVect[8] = GetNewCallSegmentStaticDescription();
        staticDesc._elementVect[9] = GetINServiceCompatibilityResponseStaticDescription();
        staticDesc._elementVect[10] = GetServiceInteractionIndicatorsTwoStaticDescription();
        staticDesc.SetTypeName("InitiateCallAttemptArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InitiateCallAttemptArg::GetDestinationRoutingAddressStaticDescription()
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
        staticDesc._maxSize = 3;
        staticDesc._element = DestinationRoutingAddress::GetCalledPartyNumberStaticDescription();
        staticDesc.SetNamedTypeName("destinationRoutingAddress");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InitiateCallAttemptArg::GetAlertingPatternStaticDescription()
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

AsnDescObject* InitiateCallAttemptArg::GetISDNAccessRelatedInformationStaticDescription()
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
        staticDesc.SetCloneForFactory(new ISDNAccessRelatedInformation(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("iSDNAccessRelatedInformation");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InitiateCallAttemptArg::GetTravellingClassMarkStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 3));
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

AsnDescObject* InitiateCallAttemptArg::GetExtensionsStaticDescription()
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
        staticDesc._maxSize = 2;
        staticDesc._element = Extensions::GetExtensionFieldStaticDescription();
        staticDesc.SetNamedTypeName("extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InitiateCallAttemptArg::GetServiceInteractionIndicatorsStaticDescription()
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
        staticDesc.SetCloneForFactory(new ServiceInteractionIndicators(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 29));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 15;
        staticDesc.SetNamedTypeName("serviceInteractionIndicators");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InitiateCallAttemptArg::GetCallingPartyNumberStaticDescription()
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
        staticDesc.SetCloneForFactory(new CallingPartyNumber(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 30));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 15;
        staticDesc.SetNamedTypeName("callingPartyNumber");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InitiateCallAttemptArg::GetLegToBeCreatedStaticDescription()
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
        staticDesc.SetCloneForFactory(new LegID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 5));
        staticDesc._clauseDefault = true;
        {
            LegID* legId = new LegID(&staticDesc);
            std::vector<byte> array;
            array.push_back(0x01U);
            LegType* legType = new LegType(array);
            legId->SetChoiceSendingSideID(legType);
            staticDesc.SetCloneForDefaultFactory(legId);
        }
        staticDesc._choiceList.push_back(LegID::GetSendingSideIDStaticDescription());
        staticDesc._choiceList.push_back(LegID::GetReceivingSideIDStaticDescription());
        staticDesc.SetNamedTypeName("legToBeCreated");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InitiateCallAttemptArg::GetNewCallSegmentStaticDescription()
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
        staticDesc.SetCloneForFactory(new CallSegmentID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 6));
        staticDesc._clauseDefault = true;
        {
            CallSegmentID* cloneForDefaultFactory = new CallSegmentID(&staticDesc);
            cloneForDefaultFactory->SetValue((long)1);
            staticDesc.SetCloneForDefaultFactory(cloneForDefaultFactory);
        }
        staticDesc.SetNamedTypeName("newCallSegment");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InitiateCallAttemptArg::GetINServiceCompatibilityResponseStaticDescription()
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
        staticDesc.SetCloneForFactory(new INServiceCompatibilityResponse(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 7));
        staticDesc._clauseOptional = true;
        staticDesc._choiceList.push_back(INServiceCompatibilityResponse::GetAgreementsStaticDescription());
        staticDesc._choiceList.push_back(INServiceCompatibilityResponse::GetNetworkSpecificStaticDescription());
        staticDesc.SetNamedTypeName("iNServiceCompatibilityResponse");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InitiateCallAttemptArg::GetServiceInteractionIndicatorsTwoStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(9);

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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 8));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ServiceInteractionIndicatorsTwo::GetForwardServiceInteractionIndStaticDescription();
        staticDesc._elementVect[1] = ServiceInteractionIndicatorsTwo::GetBackwardServiceInteractionIndStaticDescription();
        staticDesc._elementVect[2] = ServiceInteractionIndicatorsTwo::GetBothwayThroughConnectionIndStaticDescription();
        staticDesc._elementVect[3] = ServiceInteractionIndicatorsTwo::GetSuspendTimerStaticDescription();
        staticDesc._elementVect[4] = ServiceInteractionIndicatorsTwo::GetConnectedNumberTreatmentIndStaticDescription();
        staticDesc._elementVect[5] = ServiceInteractionIndicatorsTwo::GetSuppressCallDiversionNotificationStaticDescription();
        staticDesc._elementVect[6] = ServiceInteractionIndicatorsTwo::GetSuppressCallTransferNotificationStaticDescription();
        staticDesc._elementVect[7] = ServiceInteractionIndicatorsTwo::GetAllowCdINNoPresentationIndStaticDescription();
        staticDesc._elementVect[8] = ServiceInteractionIndicatorsTwo::GetUserDialogueDurationIndStaticDescription();
        staticDesc.SetNamedTypeName("serviceInteractionIndicatorsTwo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





