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


#include <cap_v3_gprs_qo_s.h>

#include <AsnDescChoice.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace cap_v3;




////////// Begin Nested Class(es) //////////


// Type QoS_Subscribed is a reference => no code generated.

// Type Ext_QoS_Subscribed is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* GPRS_QoS::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new GPRS_QoS(&staticDesc));
        staticDesc._choiceList.push_back(GetShort_QoS_formatStaticDescription());
        staticDesc._choiceList.push_back(GetLong_QoS_formatStaticDescription());
        staticDesc.SetTypeName("GPRS-QoS");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* GPRS_QoS::GetShort_QoS_formatStaticDescription()
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
        staticDesc.SetCloneForFactory(new QoS_Subscribed(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 3;
        staticDesc._maxSize = 3;
        staticDesc.SetNamedTypeName("short-QoS-format");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* GPRS_QoS::GetLong_QoS_formatStaticDescription()
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
        staticDesc.SetCloneForFactory(new Ext_QoS_Subscribed(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 9;
        staticDesc.SetNamedTypeName("long-QoS-format");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





