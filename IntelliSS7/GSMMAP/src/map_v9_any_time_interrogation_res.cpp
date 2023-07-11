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


#include <map_v9_any_time_interrogation_res.h>

#include <AsnDescSequence.h>


using namespace its;
using namespace map_v9;




////////// Begin Nested Class(es) //////////


// Type SubscriberInfo is a reference => no code generated.

// Type ExtensionContainer is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* AnyTimeInterrogationRes::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new AnyTimeInterrogationRes(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetSubscriberInfoStaticDescription();
        staticDesc._elementVect[1] = GetExtensionContainerStaticDescription();
        staticDesc.SetTypeName("AnyTimeInterrogationRes");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* AnyTimeInterrogationRes::GetSubscriberInfoStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(9);

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
        staticDesc.SetCloneForFactory(new SubscriberInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = SubscriberInfo::GetLocationInformationStaticDescription();
        staticDesc._elementVect[1] = SubscriberInfo::GetSubscriberStateStaticDescription();
        staticDesc._elementVect[2] = SubscriberInfo::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[3] = SubscriberInfo::GetLocationInformationGPRSStaticDescription();
        staticDesc._elementVect[4] = SubscriberInfo::GetPs_SubscriberStateStaticDescription();
        staticDesc._elementVect[5] = SubscriberInfo::GetImeiStaticDescription();
        staticDesc._elementVect[6] = SubscriberInfo::GetMs_Classmark2StaticDescription();
        staticDesc._elementVect[7] = SubscriberInfo::GetGprs_MS_ClassStaticDescription();
        staticDesc._elementVect[8] = SubscriberInfo::GetMnpInfoResStaticDescription();
        staticDesc.SetNamedTypeName("subscriberInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* AnyTimeInterrogationRes::GetExtensionContainerStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
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




