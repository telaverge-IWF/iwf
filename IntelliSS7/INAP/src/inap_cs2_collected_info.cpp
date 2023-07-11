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


#include <inap_cs2_collected_info.h>

#include <AsnDescChoice.h>
#include <AsnDescBoolean.h>
#include <AsnDescSequence.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type CollectedDigits is a reference => no code generated.


AsnDescObject* CollectedInfo::IA5Information::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_INAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new IA5Information(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc.SetNamedTypeName("iA5Information");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


////////// End Nested Class(es) //////////

AsnDescObject* CollectedInfo::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new CollectedInfo(&staticDesc));
        staticDesc._choiceList.push_back(GetCollectedDigitsStaticDescription());
        staticDesc._choiceList.push_back(GetIA5InformationStaticDescription());
        staticDesc.SetTypeName("CollectedInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CollectedInfo::GetCollectedDigitsStaticDescription()
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
        staticDesc.SetCloneForFactory(new CollectedDigits(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._elementVect[0] = CollectedDigits::GetMinimumNbOfDigitsStaticDescription();
        staticDesc._elementVect[1] = CollectedDigits::GetMaximumNbOfDigitsStaticDescription();
        staticDesc._elementVect[2] = CollectedDigits::GetEndOfReplyDigitStaticDescription();
        staticDesc._elementVect[3] = CollectedDigits::GetCancelDigitStaticDescription();
        staticDesc._elementVect[4] = CollectedDigits::GetStartDigitStaticDescription();
        staticDesc._elementVect[5] = CollectedDigits::GetFirstDigitTimeOutStaticDescription();
        staticDesc._elementVect[6] = CollectedDigits::GetInterDigitTimeOutStaticDescription();
        staticDesc._elementVect[7] = CollectedDigits::GetErrorTreatmentStaticDescription();
        staticDesc._elementVect[8] = CollectedDigits::GetInterruptableAnnIndStaticDescription();
        staticDesc._elementVect[9] = CollectedDigits::GetVoiceInformationStaticDescription();
        staticDesc._elementVect[10] = CollectedDigits::GetVoiceBackStaticDescription();
        staticDesc.SetNamedTypeName("collectedDigits");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CollectedInfo::GetIA5InformationStaticDescription()
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
        staticDesc.SetCloneForFactory(new IA5Information(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc.SetNamedTypeName("iA5Information");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





