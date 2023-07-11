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


#include <map_v13_routing_info_for_lcs_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescOctetString.h>
#include <AsnDescChoice.h>


using namespace its;
using namespace map_v13;




////////// Begin Nested Class(es) //////////


// Type ISDN_AddressString is a reference => no code generated.

// Type SubscriberIdentity is a reference => no code generated.

// Type ExtensionContainer is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* RoutingInfoForLCS_Arg::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new RoutingInfoForLCS_Arg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetMlcNumberStaticDescription();
        staticDesc._elementVect[1] = GetTargetMSStaticDescription();
        staticDesc._elementVect[2] = GetExtensionContainerStaticDescription();
        staticDesc.SetTypeName("RoutingInfoForLCS-Arg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* RoutingInfoForLCS_Arg::GetMlcNumberStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 20;
        staticDesc.SetNamedTypeName("mlcNumber");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* RoutingInfoForLCS_Arg::GetTargetMSStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._choiceList.push_back(SubscriberIdentity::GetImsiStaticDescription());
        staticDesc._choiceList.push_back(SubscriberIdentity::GetMsisdnStaticDescription());
        staticDesc.SetNamedTypeName("targetMS");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* RoutingInfoForLCS_Arg::GetExtensionContainerStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 2));
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





