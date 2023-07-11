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


#include <cap_v3_charging_result.h>

#include <AsnDescChoice.h>


using namespace its;
using namespace cap_v3;




////////// Begin Nested Class(es) //////////


// Type TransferredVolume is a reference => no code generated.

// Type ElapsedTime is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* ChargingResult::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new ChargingResult(&staticDesc));
        staticDesc._choiceList.push_back(GetTransferredVolumeStaticDescription());
        staticDesc._choiceList.push_back(GetElapsedTimeStaticDescription());
        staticDesc.SetTypeName("ChargingResult");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ChargingResult::GetTransferredVolumeStaticDescription()
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
        staticDesc.SetCloneForFactory(new TransferredVolume(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._choiceList.push_back(TransferredVolume::GetVolumeIfNoTariffSwitchStaticDescription());
        staticDesc._choiceList.push_back(TransferredVolume::GetVolumeIfTariffSwitchStaticDescription());
        staticDesc.SetNamedTypeName("transferredVolume");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ChargingResult::GetElapsedTimeStaticDescription()
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
        staticDesc.SetCloneForFactory(new ElapsedTime(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._choiceList.push_back(ElapsedTime::GetTimeGPRSIfNoTariffSwitchStaticDescription());
        staticDesc._choiceList.push_back(ElapsedTime::GetTimeGPRSIfTariffSwitchStaticDescription());
        staticDesc.SetNamedTypeName("elapsedTime");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




