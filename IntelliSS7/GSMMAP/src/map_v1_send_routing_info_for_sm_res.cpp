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


#include <map_v1_send_routing_info_for_sm_res.h>

#include <AsnDescSequence.h>
#include <AsnDescChoice.h>
#include <AsnDescOctetString.h>
#include <AsnDescBoolean.h>


using namespace its;
using namespace map_v1;




////////// Begin Nested Class(es) //////////


// Type IMSI is a reference => no code generated.



////////// Begin Nested Class(es) //////////




////////// Begin Nested Class(es) //////////


// Type LocationInfo is a reference => no code generated.

// Type LMsId is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* SendRoutingInfoForSMRes::LocInfoOrForwData::LocInfo::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new LocInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._elementVect[0] = GetLocationInfoStaticDescription();
        staticDesc._elementVect[1] = GetLMsIdStaticDescription();
        staticDesc.SetNamedTypeName("locInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SendRoutingInfoForSMRes::LocInfoOrForwData::LocInfo::GetLocationInfoStaticDescription()
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
        staticDesc.SetCloneForFactory(new LocationInfo(&staticDesc));
        staticDesc._choiceList.push_back(LocationInfo::GetRoamingNumberStaticDescription());
        staticDesc._choiceList.push_back(LocationInfo::GetMscNumberStaticDescription());
        staticDesc.SetNamedTypeName("locationInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SendRoutingInfoForSMRes::LocInfoOrForwData::LocInfo::GetLMsIdStaticDescription()
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
        staticDesc.SetCloneForFactory(new LMsId(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 4));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 4;
        staticDesc._maxSize = 4;
        staticDesc.SetNamedTypeName("lMsId");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


// Type ForwardingData is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* SendRoutingInfoForSMRes::LocInfoOrForwData::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new LocInfoOrForwData(&staticDesc));
        staticDesc._choiceList.push_back(GetLocInfoStaticDescription());
        staticDesc._choiceList.push_back(GetForwardingDataStaticDescription());
        staticDesc.SetNamedTypeName("locInfoOrForwData");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SendRoutingInfoForSMRes::LocInfoOrForwData::GetLocInfoStaticDescription()
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
        staticDesc.SetCloneForFactory(new LocInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._elementVect[0] = LocInfo::GetLocationInfoStaticDescription();
        staticDesc._elementVect[1] = LocInfo::GetLMsIdStaticDescription();
        staticDesc.SetNamedTypeName("locInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SendRoutingInfoForSMRes::LocInfoOrForwData::GetForwardingDataStaticDescription()
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
        staticDesc.SetCloneForFactory(new ForwardingData(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._elementVect[0] = ForwardingData::GetForwardedToNumberStaticDescription();
        staticDesc._elementVect[1] = ForwardingData::GetForwardingOptionsStaticDescription();
        staticDesc.SetNamedTypeName("forwardingData");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}



AsnDescObject* SendRoutingInfoForSMRes::Mwd_Set::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescBoolean staticDesc;

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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new Mwd_Set(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("mwd-Set");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


////////// End Nested Class(es) //////////

AsnDescObject* SendRoutingInfoForSMRes::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new SendRoutingInfoForSMRes(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GetImsiStaticDescription();
        staticDesc._elementVect[1] = GetLocInfoOrForwDataStaticDescription();
        staticDesc._elementVect[2] = GetMwd_SetStaticDescription();
        staticDesc.SetTypeName("SendRoutingInfoForSMRes");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SendRoutingInfoForSMRes::GetImsiStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 4));
        staticDesc.SetNamedTypeName("imsi");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SendRoutingInfoForSMRes::GetLocInfoOrForwDataStaticDescription()
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
        staticDesc.SetCloneForFactory(new LocInfoOrForwData(&staticDesc));
        staticDesc._choiceList.push_back(LocInfoOrForwData::GetLocInfoStaticDescription());
        staticDesc._choiceList.push_back(LocInfoOrForwData::GetForwardingDataStaticDescription());
        staticDesc.SetNamedTypeName("locInfoOrForwData");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SendRoutingInfoForSMRes::GetMwd_SetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescBoolean staticDesc;

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
        staticDesc.SetCloneForFactory(new Mwd_Set(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("mwd-Set");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




