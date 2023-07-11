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


#include <inap_cs2_service_address_information.h>

#include <AsnDescSequence.h>
#include <AsnDescInteger.h>
#include <AsnDescEnumerated.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type ServiceKey is a reference => no code generated.

// Type MiscCallInfo is a reference => no code generated.

// Type TriggerType is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* ServiceAddressInformation::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_INAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new ServiceAddressInformation(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GetServiceKeyStaticDescription();
        staticDesc._elementVect[1] = GetMiscCallInfoStaticDescription();
        staticDesc._elementVect[2] = GetTriggerTypeStaticDescription();
        staticDesc.SetTypeName("ServiceAddressInformation");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ServiceAddressInformation::GetServiceKeyStaticDescription()
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
        staticDesc.SetCloneForFactory(new ServiceKey(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("serviceKey");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ServiceAddressInformation::GetMiscCallInfoStaticDescription()
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
        staticDesc.SetCloneForFactory(new MiscCallInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._elementVect[0] = MiscCallInfo::GetMessageTypeStaticDescription();
        staticDesc._elementVect[1] = MiscCallInfo::GetDpAssignmentStaticDescription();
        staticDesc.SetNamedTypeName("miscCallInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ServiceAddressInformation::GetTriggerTypeStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescEnumerated staticDesc;

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
        staticDesc.SetCloneForFactory(new TriggerType(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseOptional = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(12);
        staticDesc._valueSet.insert(13);
        staticDesc._valueSet.insert(14);
        staticDesc._valueSet.insert(17);
        staticDesc._valueSet.insert(18);
        staticDesc._valueSet.insert(25);
        staticDesc._valueSet.insert(26);
        staticDesc._valueSet.insert(27);
        staticDesc._valueSet.insert(29);
        staticDesc._valueSet.insert(30);
        staticDesc._valueSet.insert(31);
        staticDesc._valueSet.insert(32);
        staticDesc._valueSet.insert(33);
        staticDesc._valueSet.insert(34);
        staticDesc._valueSet.insert(35);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"featureActivation", 0}, {"verticalServiceCode", 1}, {"customizedAccess", 2}, {"customizedIntercom", 3}, {"emergencyService", 12}, {"aFR", 13}, {"sharedIOTrunk", 14}, {"offHookDelay", 17}, {"channelSetupPRI", 18}, {"tNoAnswer", 25}, {"tBusy", 26}, {"oCalledPartyBusy", 27}, {"oNoAnswer", 29}, {"originationAttemptAuthorized", 30}, {"oAnswer", 31}, {"oDisconnect", 32}, {"termAttemptAuthorized", 33}, {"tAnswer", 34}, {"tDisconnect", 35}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("triggerType");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





