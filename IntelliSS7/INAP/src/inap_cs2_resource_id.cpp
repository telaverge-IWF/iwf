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


#include <inap_cs2_resource_id.h>

#include <AsnDescChoice.h>
#include <AsnDescInteger.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type Digits is a reference => no code generated.

// Type FacilityGroup is a reference => no code generated.


AsnDescObject* ResourceID::FacilityGroupMemberID::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_INAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new FacilityGroupMemberID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc.SetNamedTypeName("facilityGroupMemberID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}



AsnDescObject* ResourceID::TrunkGroupID::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_INAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new TrunkGroupID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 3));
        staticDesc.SetNamedTypeName("trunkGroupID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


////////// End Nested Class(es) //////////

AsnDescObject* ResourceID::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new ResourceID(&staticDesc));
        staticDesc._choiceList.push_back(GetLineIDStaticDescription());
        staticDesc._choiceList.push_back(GetFacilityGroupIDStaticDescription());
        staticDesc._choiceList.push_back(GetFacilityGroupMemberIDStaticDescription());
        staticDesc._choiceList.push_back(GetTrunkGroupIDStaticDescription());
        staticDesc.SetTypeName("ResourceID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ResourceID::GetLineIDStaticDescription()
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
        staticDesc.SetCloneForFactory(new Digits(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 0;
        staticDesc._maxSize = 20;
        staticDesc.SetNamedTypeName("lineID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ResourceID::GetFacilityGroupIDStaticDescription()
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
        staticDesc.SetNamedTypeName("facilityGroupID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ResourceID::GetFacilityGroupMemberIDStaticDescription()
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
        staticDesc.SetCloneForFactory(new FacilityGroupMemberID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc.SetNamedTypeName("facilityGroupMemberID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ResourceID::GetTrunkGroupIDStaticDescription()
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
        staticDesc.SetCloneForFactory(new TrunkGroupID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 3));
        staticDesc.SetNamedTypeName("trunkGroupID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





