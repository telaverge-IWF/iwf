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


#include <cap_v2_camel_a_ch_billing_charging_characteristics.h>

#include <AsnDescChoice.h>
#include <AsnDescSequence.h>
#include <AsnDescInteger.h>


using namespace its;
using namespace cap_v2;




////////// Begin Nested Class(es) //////////




////////// Begin Nested Class(es) //////////



AsnDescObject* CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::MaxCallPeriodDuration::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new MaxCallPeriodDuration(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc.SetNamedTypeName("maxCallPeriodDuration");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


// Type ReleaseIfDurationExceeded is a reference => no code generated.


AsnDescObject* CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::TariffSwitchInterval::GetStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("tariffSwitchInterval");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


////////// End Nested Class(es) //////////

AsnDescObject* CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new TimeDurationCharging(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._elementVect[0] = GetMaxCallPeriodDurationStaticDescription();
        staticDesc._elementVect[1] = GetReleaseIfdurationExceededStaticDescription();
        staticDesc._elementVect[2] = GetTariffSwitchIntervalStaticDescription();
        staticDesc.SetNamedTypeName("timeDurationCharging");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::GetMaxCallPeriodDurationStaticDescription()
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
        staticDesc.SetCloneForFactory(new MaxCallPeriodDuration(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc.SetNamedTypeName("maxCallPeriodDuration");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::GetReleaseIfdurationExceededStaticDescription()
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
        staticDesc.SetCloneForFactory(new ReleaseIfDurationExceeded(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ReleaseIfDurationExceeded::GetToneStaticDescription();
        staticDesc._elementVect[1] = ReleaseIfDurationExceeded::GetExtensionsStaticDescription();
        staticDesc.SetNamedTypeName("releaseIfdurationExceeded");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::GetTariffSwitchIntervalStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("tariffSwitchInterval");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


////////// End Nested Class(es) //////////

AsnDescObject* CAMEL_AChBillingChargingCharacteristics::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new CAMEL_AChBillingChargingCharacteristics(&staticDesc));
        staticDesc._choiceList.push_back(GetTimeDurationChargingStaticDescription());
        staticDesc.SetTypeName("CAMEL-AChBillingChargingCharacteristics");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_AChBillingChargingCharacteristics::GetTimeDurationChargingStaticDescription()
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
        staticDesc.SetCloneForFactory(new TimeDurationCharging(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._elementVect[0] = TimeDurationCharging::GetMaxCallPeriodDurationStaticDescription();
        staticDesc._elementVect[1] = TimeDurationCharging::GetReleaseIfdurationExceededStaticDescription();
        staticDesc._elementVect[2] = TimeDurationCharging::GetTariffSwitchIntervalStaticDescription();
        staticDesc.SetNamedTypeName("timeDurationCharging");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





