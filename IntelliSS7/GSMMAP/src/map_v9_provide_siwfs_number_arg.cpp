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


#include <map_v9_provide_siwfs_number_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace map_v9;




////////// Begin Nested Class(es) //////////


// Type ExternalSignalInfo is a reference => no code generated.

// Type ExternalSignalInfo is a reference => no code generated.

// Type CallDirection is a reference => no code generated.

// Type ISDN_AddressString is a reference => no code generated.

// Type ExternalSignalInfo is a reference => no code generated.

// Type ExternalSignalInfo is a reference => no code generated.

// Type ExternalSignalInfo is a reference => no code generated.

// Type ExtensionContainer is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* ProvideSIWFSNumberArg::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(8);

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

        staticDesc.SetCloneForFactory(new ProvideSIWFSNumberArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetGsm_BearerCapabilityStaticDescription();
        staticDesc._elementVect[1] = GetIsdn_BearerCapabilityStaticDescription();
        staticDesc._elementVect[2] = GetCall_DirectionStaticDescription();
        staticDesc._elementVect[3] = GetB_Subscriber_AddressStaticDescription();
        staticDesc._elementVect[4] = GetChosenChannelStaticDescription();
        staticDesc._elementVect[5] = GetLowerLayerCompatibilityStaticDescription();
        staticDesc._elementVect[6] = GetHighLayerCompatibilityStaticDescription();
        staticDesc._elementVect[7] = GetExtensionContainerStaticDescription();
        staticDesc.SetTypeName("ProvideSIWFSNumberArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ProvideSIWFSNumberArg::GetGsm_BearerCapabilityStaticDescription()
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
        staticDesc.SetCloneForFactory(new ExternalSignalInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ExternalSignalInfo::GetProtocolIdStaticDescription();
        staticDesc._elementVect[1] = ExternalSignalInfo::GetSignalInfoStaticDescription();
        staticDesc._elementVect[2] = ExternalSignalInfo::GetExtensionContainerStaticDescription();
        staticDesc.SetNamedTypeName("gsm-BearerCapability");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ProvideSIWFSNumberArg::GetIsdn_BearerCapabilityStaticDescription()
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
        staticDesc.SetCloneForFactory(new ExternalSignalInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ExternalSignalInfo::GetProtocolIdStaticDescription();
        staticDesc._elementVect[1] = ExternalSignalInfo::GetSignalInfoStaticDescription();
        staticDesc._elementVect[2] = ExternalSignalInfo::GetExtensionContainerStaticDescription();
        staticDesc.SetNamedTypeName("isdn-BearerCapability");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ProvideSIWFSNumberArg::GetCall_DirectionStaticDescription()
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
        staticDesc.SetCloneForFactory(new CallDirection(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 1;
        staticDesc.SetNamedTypeName("call-Direction");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ProvideSIWFSNumberArg::GetB_Subscriber_AddressStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 3));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 20;
        staticDesc.SetNamedTypeName("b-Subscriber-Address");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ProvideSIWFSNumberArg::GetChosenChannelStaticDescription()
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
        staticDesc.SetCloneForFactory(new ExternalSignalInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 4));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ExternalSignalInfo::GetProtocolIdStaticDescription();
        staticDesc._elementVect[1] = ExternalSignalInfo::GetSignalInfoStaticDescription();
        staticDesc._elementVect[2] = ExternalSignalInfo::GetExtensionContainerStaticDescription();
        staticDesc.SetNamedTypeName("chosenChannel");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ProvideSIWFSNumberArg::GetLowerLayerCompatibilityStaticDescription()
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
        staticDesc.SetCloneForFactory(new ExternalSignalInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 5));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ExternalSignalInfo::GetProtocolIdStaticDescription();
        staticDesc._elementVect[1] = ExternalSignalInfo::GetSignalInfoStaticDescription();
        staticDesc._elementVect[2] = ExternalSignalInfo::GetExtensionContainerStaticDescription();
        staticDesc.SetNamedTypeName("lowerLayerCompatibility");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ProvideSIWFSNumberArg::GetHighLayerCompatibilityStaticDescription()
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
        staticDesc.SetCloneForFactory(new ExternalSignalInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 6));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ExternalSignalInfo::GetProtocolIdStaticDescription();
        staticDesc._elementVect[1] = ExternalSignalInfo::GetSignalInfoStaticDescription();
        staticDesc._elementVect[2] = ExternalSignalInfo::GetExtensionContainerStaticDescription();
        staticDesc.SetNamedTypeName("highLayerCompatibility");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ProvideSIWFSNumberArg::GetExtensionContainerStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 7));
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





