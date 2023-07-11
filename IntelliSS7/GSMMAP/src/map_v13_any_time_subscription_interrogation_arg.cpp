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


#include <map_v13_any_time_subscription_interrogation_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescNull.h>
#include <AsnDescChoice.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace map_v13;




////////// Begin Nested Class(es) //////////


// Type SubscriberIdentity is a reference => no code generated.

// Type RequestedSubscriptionInfo is a reference => no code generated.

// Type ISDN_AddressString is a reference => no code generated.

// Type ExtensionContainer is a reference => no code generated.


AsnDescObject* AnyTimeSubscriptionInterrogationArg::LongFTN_Supported::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescNull staticDesc;

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
        staticDesc.SetCloneForFactory(new LongFTN_Supported(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 4));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("longFTN-Supported");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


////////// End Nested Class(es) //////////

AsnDescObject* AnyTimeSubscriptionInterrogationArg::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(5);

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
        staticDesc.SetCloneForFactory(new AnyTimeSubscriptionInterrogationArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetSubscriberIdentityStaticDescription();
        staticDesc._elementVect[1] = GetRequestedSubscriptionInfoStaticDescription();
        staticDesc._elementVect[2] = GetGsmSCF_AddressStaticDescription();
        staticDesc._elementVect[3] = GetExtensionContainerStaticDescription();
        staticDesc._elementVect[4] = GetLongFTN_SupportedStaticDescription();
        staticDesc.SetTypeName("AnyTimeSubscriptionInterrogationArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* AnyTimeSubscriptionInterrogationArg::GetSubscriberIdentityStaticDescription()
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
        staticDesc.SetCloneForFactory(new SubscriberIdentity(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._choiceList.push_back(SubscriberIdentity::GetImsiStaticDescription());
        staticDesc._choiceList.push_back(SubscriberIdentity::GetMsisdnStaticDescription());
        staticDesc.SetNamedTypeName("subscriberIdentity");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* AnyTimeSubscriptionInterrogationArg::GetRequestedSubscriptionInfoStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(14);

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
        staticDesc.SetCloneForFactory(new RequestedSubscriptionInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = RequestedSubscriptionInfo::GetRequestedSS_InfoStaticDescription();
        staticDesc._elementVect[1] = RequestedSubscriptionInfo::GetOdbStaticDescription();
        staticDesc._elementVect[2] = RequestedSubscriptionInfo::GetRequestedCAMEL_SubscriptionInfoStaticDescription();
        staticDesc._elementVect[3] = RequestedSubscriptionInfo::GetSupportedVLR_CAMEL_PhasesStaticDescription();
        staticDesc._elementVect[4] = RequestedSubscriptionInfo::GetSupportedSGSN_CAMEL_PhasesStaticDescription();
        staticDesc._elementVect[5] = RequestedSubscriptionInfo::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[6] = RequestedSubscriptionInfo::GetAdditionalRequestedCAMEL_SubscriptionInfoStaticDescription();
        staticDesc._elementVect[7] = RequestedSubscriptionInfo::GetMsisdn_BS_ListStaticDescription();
        staticDesc._elementVect[8] = RequestedSubscriptionInfo::GetCsg_SubscriptionDataRequestedStaticDescription();
        staticDesc._elementVect[9] = RequestedSubscriptionInfo::GetCw_InfoStaticDescription();
        staticDesc._elementVect[10] = RequestedSubscriptionInfo::GetClip_InfoStaticDescription();
        staticDesc._elementVect[11] = RequestedSubscriptionInfo::GetClir_InfoStaticDescription();
        staticDesc._elementVect[12] = RequestedSubscriptionInfo::GetHold_InfoStaticDescription();
        staticDesc._elementVect[13] = RequestedSubscriptionInfo::GetEct_InfoStaticDescription();
        staticDesc.SetNamedTypeName("requestedSubscriptionInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* AnyTimeSubscriptionInterrogationArg::GetGsmSCF_AddressStaticDescription()
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
        staticDesc.SetCloneForFactory(new ISDN_AddressString(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 20;
        staticDesc.SetNamedTypeName("gsmSCF-Address");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* AnyTimeSubscriptionInterrogationArg::GetExtensionContainerStaticDescription()
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
        staticDesc.SetCloneForFactory(new ExtensionContainer(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 3));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ExtensionContainer::GetPrivateExtensionListStaticDescription();
        staticDesc._elementVect[1] = ExtensionContainer::GetPcs_ExtensionsStaticDescription();
        staticDesc.SetNamedTypeName("extensionContainer");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* AnyTimeSubscriptionInterrogationArg::GetLongFTN_SupportedStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescNull staticDesc;

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
        staticDesc.SetCloneForFactory(new LongFTN_Supported(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 4));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("longFTN-Supported");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





