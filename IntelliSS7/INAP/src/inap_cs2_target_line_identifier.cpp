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


#include <inap_cs2_target_line_identifier.h>

#include <AsnDescChoice.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type CalledPartyNumber is a reference => no code generated.

// Type FacilityGroup is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* TargetLineIdentifier::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_INAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new TargetLineIdentifier(&staticDesc));
        staticDesc._choiceList.push_back(GetIndividualStaticDescription());
        staticDesc._choiceList.push_back(GetGroupStaticDescription());
        staticDesc.SetTypeName("TargetLineIdentifier");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TargetLineIdentifier::GetIndividualStaticDescription()
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
        staticDesc.SetCloneForFactory(new CalledPartyNumber(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 15;
        staticDesc.SetNamedTypeName("individual");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* TargetLineIdentifier::GetGroupStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._choiceList.push_back(FacilityGroup::GetTrunkGroupIDStaticDescription());
        staticDesc._choiceList.push_back(FacilityGroup::GetPrivateFacilityIDStaticDescription());
        staticDesc._choiceList.push_back(FacilityGroup::GetHuntGroupStaticDescription());
        staticDesc._choiceList.push_back(FacilityGroup::GetRouteIndexStaticDescription());
        staticDesc.SetNamedTypeName("group");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





