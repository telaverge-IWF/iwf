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


#include <map_v2_sent_parameter.h>

#include <AsnDescChoice.h>
#include <AsnDescOctetString.h>
#include <AsnDescSequence.h>


using namespace its;
using namespace map_v2;




////////// Begin Nested Class(es) //////////


// Type IMSI is a reference => no code generated.

// Type AuthenticationSet is a reference => no code generated.

// Type SubscriberData is a reference => no code generated.

// Type Ki is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* SentParameter::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new SentParameter(&staticDesc));
        staticDesc._choiceList.push_back(GetImsiStaticDescription());
        staticDesc._choiceList.push_back(GetAuthenticationSetStaticDescription());
        staticDesc._choiceList.push_back(GetSubscriberDataStaticDescription());
        staticDesc._choiceList.push_back(GetKiStaticDescription());
        staticDesc.SetTypeName("SentParameter");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SentParameter::GetImsiStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc.SetNamedTypeName("imsi");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SentParameter::GetAuthenticationSetStaticDescription()
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
        staticDesc.SetCloneForFactory(new AuthenticationSet(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = AuthenticationSet::GetRandStaticDescription();
        staticDesc._elementVect[1] = AuthenticationSet::GetSresStaticDescription();
        staticDesc._elementVect[2] = AuthenticationSet::GetKcStaticDescription();
        staticDesc.SetNamedTypeName("authenticationSet");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SentParameter::GetSubscriberDataStaticDescription()
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
        staticDesc.SetCloneForFactory(new SubscriberData(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 2));
        staticDesc._elementVect[0] = SubscriberData::GetMsisdnStaticDescription();
        staticDesc._elementVect[1] = SubscriberData::GetCategoryStaticDescription();
        staticDesc._elementVect[2] = SubscriberData::GetSubscriberStatusStaticDescription();
        staticDesc._elementVect[3] = SubscriberData::GetBearerServiceListStaticDescription();
        staticDesc._elementVect[4] = SubscriberData::GetTeleserviceListStaticDescription();
        staticDesc._elementVect[5] = SubscriberData::GetProvisionedSSStaticDescription();
        staticDesc._elementVect[6] = SubscriberData::GetOdb_DataStaticDescription();
        staticDesc._elementVect[7] = SubscriberData::GetRoamingRestrictionDueToUnsupportedFeatureStaticDescription();
        staticDesc._elementVect[8] = SubscriberData::GetRegionalSubscriptionDataStaticDescription();
        staticDesc.SetNamedTypeName("subscriberData");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SentParameter::GetKiStaticDescription()
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
        staticDesc.SetCloneForFactory(new Ki(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 4));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 16;
        staticDesc._maxSize = 16;
        staticDesc.SetNamedTypeName("ki");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





