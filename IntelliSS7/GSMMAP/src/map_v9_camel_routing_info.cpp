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


#include <map_v9_camel_routing_info.h>

#include <AsnDescSequence.h>


using namespace its;
using namespace map_v9;




////////// Begin Nested Class(es) //////////


// Type ForwardingData is a reference => no code generated.

// Type GmscCamelSubscriptionInfo is a reference => no code generated.

// Type ExtensionContainer is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* CamelRoutingInfo::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new CamelRoutingInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetForwardingDataStaticDescription();
        staticDesc._elementVect[1] = GetGmscCamelSubscriptionInfoStaticDescription();
        staticDesc._elementVect[2] = GetExtensionContainerStaticDescription();
        staticDesc.SetTypeName("CamelRoutingInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CamelRoutingInfo::GetForwardingDataStaticDescription()
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
        staticDesc.SetCloneForFactory(new ForwardingData(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ForwardingData::GetForwardedToNumberStaticDescription();
        staticDesc._elementVect[1] = ForwardingData::GetForwardedToSubaddressStaticDescription();
        staticDesc._elementVect[2] = ForwardingData::GetForwardingOptionsStaticDescription();
        staticDesc._elementVect[3] = ForwardingData::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[4] = ForwardingData::GetLongForwardedToNumberStaticDescription();
        staticDesc.SetNamedTypeName("forwardingData");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CamelRoutingInfo::GetGmscCamelSubscriptionInfoStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(6);

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
        staticDesc.SetCloneForFactory(new GmscCamelSubscriptionInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GmscCamelSubscriptionInfo::GetT_CSIStaticDescription();
        staticDesc._elementVect[1] = GmscCamelSubscriptionInfo::GetO_CSIStaticDescription();
        staticDesc._elementVect[2] = GmscCamelSubscriptionInfo::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[3] = GmscCamelSubscriptionInfo::GetO_BcsmCamelTDP_CriteriaListStaticDescription();
        staticDesc._elementVect[4] = GmscCamelSubscriptionInfo::GetT_BCSM_CAMEL_TDP_CriteriaListStaticDescription();
        staticDesc._elementVect[5] = GmscCamelSubscriptionInfo::GetD_csiStaticDescription();
        staticDesc.SetNamedTypeName("gmscCamelSubscriptionInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CamelRoutingInfo::GetExtensionContainerStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
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





