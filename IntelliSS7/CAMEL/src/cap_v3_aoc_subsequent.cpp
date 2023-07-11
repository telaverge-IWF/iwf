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


#include <cap_v3_aoc_subsequent.h>

#include <AsnDescSequence.h>
#include <AsnDescInteger.h>


using namespace its;
using namespace cap_v3;




////////// Begin Nested Class(es) //////////


// Type CAI_GSM0224 is a reference => no code generated.


AsnDescObject* AOCSubsequent::TariffSwitchInterval::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new TariffSwitchInterval(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("tariffSwitchInterval");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


////////// End Nested Class(es) //////////

AsnDescObject* AOCSubsequent::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new AOCSubsequent(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GetCAI_GSM0224StaticDescription();
        staticDesc._elementVect[1] = GetTariffSwitchIntervalStaticDescription();
        staticDesc.SetTypeName("AOCSubsequent");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* AOCSubsequent::GetCAI_GSM0224StaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(7);

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
        staticDesc.SetCloneForFactory(new CAI_GSM0224(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._elementVect[0] = CAI_GSM0224::GetE1StaticDescription();
        staticDesc._elementVect[1] = CAI_GSM0224::GetE2StaticDescription();
        staticDesc._elementVect[2] = CAI_GSM0224::GetE3StaticDescription();
        staticDesc._elementVect[3] = CAI_GSM0224::GetE4StaticDescription();
        staticDesc._elementVect[4] = CAI_GSM0224::GetE5StaticDescription();
        staticDesc._elementVect[5] = CAI_GSM0224::GetE6StaticDescription();
        staticDesc._elementVect[6] = CAI_GSM0224::GetE7StaticDescription();
        staticDesc.SetNamedTypeName("cAI-GSM0224");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* AOCSubsequent::GetTariffSwitchIntervalStaticDescription()
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
        staticDesc.SetCloneForFactory(new TariffSwitchInterval(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("tariffSwitchInterval");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




