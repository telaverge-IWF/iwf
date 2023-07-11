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


#include <cap_v3_quality_of_service.h>

#include <AsnDescSequence.h>
#include <AsnDescChoice.h>


using namespace its;
using namespace cap_v3;




////////// Begin Nested Class(es) //////////


// Type GPRS_QoS is a reference => no code generated.

// Type GPRS_QoS is a reference => no code generated.

// Type GPRS_QoS is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* QualityOfService::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new QualityOfService(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetRequested_QoSStaticDescription();
        staticDesc._elementVect[1] = GetSubscribed_QoSStaticDescription();
        staticDesc._elementVect[2] = GetNegotiated_QoSStaticDescription();
        staticDesc.SetTypeName("QualityOfService");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* QualityOfService::GetRequested_QoSStaticDescription()
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
        staticDesc.SetCloneForFactory(new GPRS_QoS(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseOptional = true;
        staticDesc._choiceList.push_back(GPRS_QoS::GetShort_QoS_formatStaticDescription());
        staticDesc._choiceList.push_back(GPRS_QoS::GetLong_QoS_formatStaticDescription());
        staticDesc.SetNamedTypeName("requested-QoS");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* QualityOfService::GetSubscribed_QoSStaticDescription()
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
        staticDesc.SetCloneForFactory(new GPRS_QoS(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseOptional = true;
        staticDesc._choiceList.push_back(GPRS_QoS::GetShort_QoS_formatStaticDescription());
        staticDesc._choiceList.push_back(GPRS_QoS::GetLong_QoS_formatStaticDescription());
        staticDesc.SetNamedTypeName("subscribed-QoS");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* QualityOfService::GetNegotiated_QoSStaticDescription()
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
        staticDesc.SetCloneForFactory(new GPRS_QoS(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 2));
        staticDesc._clauseOptional = true;
        staticDesc._choiceList.push_back(GPRS_QoS::GetShort_QoS_formatStaticDescription());
        staticDesc._choiceList.push_back(GPRS_QoS::GetLong_QoS_formatStaticDescription());
        staticDesc.SetNamedTypeName("negotiated-QoS");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





