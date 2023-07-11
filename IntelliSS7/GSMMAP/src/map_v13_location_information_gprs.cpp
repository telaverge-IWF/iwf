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


#include <map_v13_location_information_gprs.h>

#include <AsnDescSequence.h>
#include <AsnDescNull.h>
#include <AsnDescChoice.h>
#include <AsnDescOctetString.h>
#include <AsnDescInteger.h>


using namespace its;
using namespace map_v13;




////////// Begin Nested Class(es) //////////


// Type CellGlobalIdOrServiceAreaIdOrLAI is a reference => no code generated.

// Type RAIdentity is a reference => no code generated.

// Type GeographicalInformation is a reference => no code generated.

// Type ISDN_AddressString is a reference => no code generated.

// Type LSAIdentity is a reference => no code generated.

// Type ExtensionContainer is a reference => no code generated.


AsnDescObject* LocationInformationGPRS::Sai_Present::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new Sai_Present(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 6));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("sai-Present");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


// Type GeodeticInformation is a reference => no code generated.


AsnDescObject* LocationInformationGPRS::CurrentLocationRetrieved::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new CurrentLocationRetrieved(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 8));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("currentLocationRetrieved");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


// Type AgeOfLocationInformation is a reference => no code generated.

// Type UserCSGInformation is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* LocationInformationGPRS::GetStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetCellGlobalIdOrServiceAreaIdOrLAIStaticDescription();
        staticDesc._elementVect[1] = GetRouteingAreaIdentityStaticDescription();
        staticDesc._elementVect[2] = GetGeographicalInformationStaticDescription();
        staticDesc._elementVect[3] = GetSgsn_NumberStaticDescription();
        staticDesc._elementVect[4] = GetSelectedLSAIdentityStaticDescription();
        staticDesc._elementVect[5] = GetExtensionContainerStaticDescription();
        staticDesc._elementVect[6] = GetSai_PresentStaticDescription();
        staticDesc._elementVect[7] = GetGeodeticInformationStaticDescription();
        staticDesc._elementVect[8] = GetCurrentLocationRetrievedStaticDescription();
        staticDesc._elementVect[9] = GetAgeOfLocationInformationStaticDescription();
        staticDesc._elementVect[10] = GetUserCSGInformationStaticDescription();
        staticDesc.SetTypeName("LocationInformationGPRS");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* LocationInformationGPRS::GetCellGlobalIdOrServiceAreaIdOrLAIStaticDescription()
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
        staticDesc.SetCloneForFactory(new CellGlobalIdOrServiceAreaIdOrLAI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseOptional = true;
        staticDesc._choiceList.push_back(CellGlobalIdOrServiceAreaIdOrLAI::GetCellGlobalIdOrServiceAreaIdFixedLengthStaticDescription());
        staticDesc._choiceList.push_back(CellGlobalIdOrServiceAreaIdOrLAI::GetLaiFixedLengthStaticDescription());
        staticDesc.SetNamedTypeName("cellGlobalIdOrServiceAreaIdOrLAI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* LocationInformationGPRS::GetRouteingAreaIdentityStaticDescription()
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
        staticDesc.SetCloneForFactory(new RAIdentity(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 6;
        staticDesc._maxSize = 6;
        staticDesc.SetNamedTypeName("routeingAreaIdentity");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* LocationInformationGPRS::GetGeographicalInformationStaticDescription()
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
        staticDesc.SetCloneForFactory(new GeographicalInformation(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 8;
        staticDesc._maxSize = 8;
        staticDesc.SetNamedTypeName("geographicalInformation");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* LocationInformationGPRS::GetSgsn_NumberStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 3));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 20;
        staticDesc.SetNamedTypeName("sgsn-Number");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* LocationInformationGPRS::GetSelectedLSAIdentityStaticDescription()
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
        staticDesc.SetCloneForFactory(new LSAIdentity(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 4));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 3;
        staticDesc._maxSize = 3;
        staticDesc.SetNamedTypeName("selectedLSAIdentity");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* LocationInformationGPRS::GetExtensionContainerStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 5));
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

AsnDescObject* LocationInformationGPRS::GetSai_PresentStaticDescription()
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
        staticDesc.SetCloneForFactory(new Sai_Present(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 6));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("sai-Present");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* LocationInformationGPRS::GetGeodeticInformationStaticDescription()
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
        staticDesc.SetCloneForFactory(new GeodeticInformation(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 7));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 10;
        staticDesc._maxSize = 10;
        staticDesc.SetNamedTypeName("geodeticInformation");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* LocationInformationGPRS::GetCurrentLocationRetrievedStaticDescription()
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
        staticDesc.SetCloneForFactory(new CurrentLocationRetrieved(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 8));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("currentLocationRetrieved");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* LocationInformationGPRS::GetAgeOfLocationInformationStaticDescription()
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
        staticDesc.SetCloneForFactory(new AgeOfLocationInformation(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 9));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("ageOfLocationInformation");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* LocationInformationGPRS::GetUserCSGInformationStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(4);

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
        staticDesc.SetCloneForFactory(new UserCSGInformation(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 10));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = UserCSGInformation::GetCsg_IdStaticDescription();
        staticDesc._elementVect[1] = UserCSGInformation::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[2] = UserCSGInformation::GetAccessModeStaticDescription();
        staticDesc._elementVect[3] = UserCSGInformation::GetCmiStaticDescription();
        staticDesc.SetNamedTypeName("userCSGInformation");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





