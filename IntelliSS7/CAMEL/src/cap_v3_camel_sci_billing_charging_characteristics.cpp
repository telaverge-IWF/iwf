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


#include <cap_v3_camel_sci_billing_charging_characteristics.h>

#include <AsnDescSequence.h>


using namespace its;
using namespace cap_v3;




////////// Begin Nested Class(es) //////////


// Type AOCBeforeAnswer is a reference => no code generated.

// Type AOCSubsequent is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* CAMEL_SCIBillingChargingCharacteristics::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new CAMEL_SCIBillingChargingCharacteristics(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GetAOCBeforeAnswerStaticDescription();
        staticDesc._elementVect[1] = GetAOCAfterAnswerStaticDescription();
        staticDesc.SetTypeName("CAMEL-SCIBillingChargingCharacteristics");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SCIBillingChargingCharacteristics::GetAOCBeforeAnswerStaticDescription()
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
        staticDesc.SetCloneForFactory(new AOCBeforeAnswer(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._elementVect[0] = AOCBeforeAnswer::GetAOCInitialStaticDescription();
        staticDesc._elementVect[1] = AOCBeforeAnswer::GetAOCSubsequentStaticDescription();
        staticDesc.SetNamedTypeName("aOCBeforeAnswer");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SCIBillingChargingCharacteristics::GetAOCAfterAnswerStaticDescription()
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
        staticDesc.SetCloneForFactory(new AOCSubsequent(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._elementVect[0] = AOCSubsequent::GetCAI_GSM0224StaticDescription();
        staticDesc._elementVect[1] = AOCSubsequent::GetTariffSwitchIntervalStaticDescription();
        staticDesc.SetNamedTypeName("aOCAfterAnswer");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





