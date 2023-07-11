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


#include <map_v13_note_mm_event_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescInteger.h>
#include <AsnDescOctetString.h>
#include <AsnDescBitString.h>


using namespace its;
using namespace map_v13;




////////// Begin Nested Class(es) //////////


// Type ServiceKey is a reference => no code generated.

// Type MM_Code is a reference => no code generated.

// Type IMSI is a reference => no code generated.

// Type ISDN_AddressString is a reference => no code generated.

// Type LocationInformation is a reference => no code generated.

// Type SupportedCamelPhases is a reference => no code generated.

// Type ExtensionContainer is a reference => no code generated.

// Type LocationInformationGPRS is a reference => no code generated.

// Type OfferedCamel4Functionalities is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* NoteMM_EventArg::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new NoteMM_EventArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetServiceKeyStaticDescription();
        staticDesc._elementVect[1] = GetEventMetStaticDescription();
        staticDesc._elementVect[2] = GetImsiStaticDescription();
        staticDesc._elementVect[3] = GetMsisdnStaticDescription();
        staticDesc._elementVect[4] = GetLocationInformationStaticDescription();
        staticDesc._elementVect[5] = GetSupportedCAMELPhasesStaticDescription();
        staticDesc._elementVect[6] = GetExtensionContainerStaticDescription();
        staticDesc._elementVect[7] = GetLocationInformationGPRSStaticDescription();
        staticDesc._elementVect[8] = GetOfferedCamel4FunctionalitiesStaticDescription();
        staticDesc.SetTypeName("NoteMM-EventArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* NoteMM_EventArg::GetServiceKeyStaticDescription()
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
        staticDesc.SetCloneForFactory(new ServiceKey(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 2));
        staticDesc.SetNamedTypeName("serviceKey");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* NoteMM_EventArg::GetEventMetStaticDescription()
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
        staticDesc.SetCloneForFactory(new MM_Code(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 1;
        staticDesc.SetNamedTypeName("eventMet");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* NoteMM_EventArg::GetImsiStaticDescription()
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
        staticDesc.SetCloneForFactory(new IMSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc.SetNamedTypeName("imsi");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* NoteMM_EventArg::GetMsisdnStaticDescription()
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
        staticDesc.SetCloneForFactory(new ISDN_AddressString(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 20;
        staticDesc.SetNamedTypeName("msisdn");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* NoteMM_EventArg::GetLocationInformationStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(13);

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
        staticDesc.SetCloneForFactory(new LocationInformation(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 3));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = LocationInformation::GetAgeOfLocationInformationStaticDescription();
        staticDesc._elementVect[1] = LocationInformation::GetGeographicalInformationStaticDescription();
        staticDesc._elementVect[2] = LocationInformation::GetVlr_numberStaticDescription();
        staticDesc._elementVect[3] = LocationInformation::GetLocationNumberStaticDescription();
        staticDesc._elementVect[4] = LocationInformation::GetCellGlobalIdOrServiceAreaIdOrLAIStaticDescription();
        staticDesc._elementVect[5] = LocationInformation::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[6] = LocationInformation::GetSelectedLSA_IdStaticDescription();
        staticDesc._elementVect[7] = LocationInformation::GetMsc_NumberStaticDescription();
        staticDesc._elementVect[8] = LocationInformation::GetGeodeticInformationStaticDescription();
        staticDesc._elementVect[9] = LocationInformation::GetCurrentLocationRetrievedStaticDescription();
        staticDesc._elementVect[10] = LocationInformation::GetSai_PresentStaticDescription();
        staticDesc._elementVect[11] = LocationInformation::GetLocationInformationEPSStaticDescription();
        staticDesc._elementVect[12] = LocationInformation::GetUserCSGInformationStaticDescription();
        staticDesc.SetNamedTypeName("locationInformation");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* NoteMM_EventArg::GetSupportedCAMELPhasesStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescBitString staticDesc;

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
        staticDesc.SetCloneForFactory(new SupportedCamelPhases(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 5));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 16;
        staticDesc.SetNamedTypeName("supportedCAMELPhases");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* NoteMM_EventArg::GetExtensionContainerStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(2);

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
        staticDesc.SetCloneForFactory(new ExtensionContainer(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 6));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ExtensionContainer::GetPrivateExtensionListStaticDescription();
        staticDesc._elementVect[1] = ExtensionContainer::GetPcs_ExtensionsStaticDescription();
        staticDesc.SetNamedTypeName("extensionContainer");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* NoteMM_EventArg::GetLocationInformationGPRSStaticDescription()
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
        staticDesc.SetCloneForFactory(new LocationInformationGPRS(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 7));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = LocationInformationGPRS::GetCellGlobalIdOrServiceAreaIdOrLAIStaticDescription();
        staticDesc._elementVect[1] = LocationInformationGPRS::GetRouteingAreaIdentityStaticDescription();
        staticDesc._elementVect[2] = LocationInformationGPRS::GetGeographicalInformationStaticDescription();
        staticDesc._elementVect[3] = LocationInformationGPRS::GetSgsn_NumberStaticDescription();
        staticDesc._elementVect[4] = LocationInformationGPRS::GetSelectedLSAIdentityStaticDescription();
        staticDesc._elementVect[5] = LocationInformationGPRS::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[6] = LocationInformationGPRS::GetSai_PresentStaticDescription();
        staticDesc._elementVect[7] = LocationInformationGPRS::GetGeodeticInformationStaticDescription();
        staticDesc._elementVect[8] = LocationInformationGPRS::GetCurrentLocationRetrievedStaticDescription();
        staticDesc._elementVect[9] = LocationInformationGPRS::GetAgeOfLocationInformationStaticDescription();
        staticDesc._elementVect[10] = LocationInformationGPRS::GetUserCSGInformationStaticDescription();
        staticDesc.SetNamedTypeName("locationInformationGPRS");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* NoteMM_EventArg::GetOfferedCamel4FunctionalitiesStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescBitString staticDesc;

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
        staticDesc.SetCloneForFactory(new OfferedCamel4Functionalities(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 8));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 15;
        staticDesc._maxSize = 64;
        staticDesc.SetNamedTypeName("offeredCamel4Functionalities");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





