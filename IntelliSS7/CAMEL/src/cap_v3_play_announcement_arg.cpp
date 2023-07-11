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


#include <cap_v3_play_announcement_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescBoolean.h>
#include <AsnDescSequenceOf.h>
#include <AsnDescChoice.h>


using namespace its;
using namespace cap_v3;




////////// Begin Nested Class(es) //////////


// Type InformationToSend is a reference => no code generated.


AsnDescObject* PlayAnnouncementArg::DisconnectFromIPForbidden::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new DisconnectFromIPForbidden(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseDefault = true;
        {
            DisconnectFromIPForbidden* cloneForDefaultFactory = new DisconnectFromIPForbidden(&staticDesc);
            cloneForDefaultFactory->SetValue(true);
            staticDesc.SetCloneForDefaultFactory(cloneForDefaultFactory);
        }
        staticDesc.SetNamedTypeName("disconnectFromIPForbidden");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}



AsnDescObject* PlayAnnouncementArg::RequestAnnouncementComplete::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new RequestAnnouncementComplete(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseDefault = true;
        {
            RequestAnnouncementComplete* cloneForDefaultFactory = new RequestAnnouncementComplete(&staticDesc);
            cloneForDefaultFactory->SetValue(true);
            staticDesc.SetCloneForDefaultFactory(cloneForDefaultFactory);
        }
        staticDesc.SetNamedTypeName("requestAnnouncementComplete");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




////////// Begin Nested Class //////////


// Type ExtensionField is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* PlayAnnouncementArg::Extensions::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequenceOf staticDesc;

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

        staticDesc.SetCloneForFactory(new Extensions(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 3));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = GetExtensionFieldStaticDescription();
        staticDesc.SetNamedTypeName("extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* PlayAnnouncementArg::Extensions::GetExtensionFieldStaticDescription()
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
        staticDesc.SetCloneForFactory(new ExtensionField(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = ExtensionField::GetTypeStaticDescription();
        staticDesc._elementVect[1] = ExtensionField::GetCriticalityStaticDescription();
        staticDesc._elementVect[2] = ExtensionField::GetValueStaticDescription();
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


////////// End Nested Class(es) //////////

AsnDescObject* PlayAnnouncementArg::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(4);

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

        staticDesc.SetCloneForFactory(new PlayAnnouncementArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetInformationToSendStaticDescription();
        staticDesc._elementVect[1] = GetDisconnectFromIPForbiddenStaticDescription();
        staticDesc._elementVect[2] = GetRequestAnnouncementCompleteStaticDescription();
        staticDesc._elementVect[3] = GetExtensionsStaticDescription();
        staticDesc.SetTypeName("PlayAnnouncementArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* PlayAnnouncementArg::GetInformationToSendStaticDescription()
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
        staticDesc.SetCloneForFactory(new InformationToSend(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._choiceList.push_back(InformationToSend::GetInbandInfoStaticDescription());
        staticDesc._choiceList.push_back(InformationToSend::GetToneStaticDescription());
        staticDesc.SetNamedTypeName("informationToSend");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* PlayAnnouncementArg::GetDisconnectFromIPForbiddenStaticDescription()
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
        staticDesc.SetCloneForFactory(new DisconnectFromIPForbidden(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseDefault = true;
        {
            DisconnectFromIPForbidden* cloneForDefaultFactory = new DisconnectFromIPForbidden(&staticDesc);
            cloneForDefaultFactory->SetValue(true);
            staticDesc.SetCloneForDefaultFactory(cloneForDefaultFactory);
        }
        staticDesc.SetNamedTypeName("disconnectFromIPForbidden");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* PlayAnnouncementArg::GetRequestAnnouncementCompleteStaticDescription()
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
        staticDesc.SetCloneForFactory(new RequestAnnouncementComplete(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseDefault = true;
        {
            RequestAnnouncementComplete* cloneForDefaultFactory = new RequestAnnouncementComplete(&staticDesc);
            cloneForDefaultFactory->SetValue(true);
            staticDesc.SetCloneForDefaultFactory(cloneForDefaultFactory);
        }
        staticDesc.SetNamedTypeName("requestAnnouncementComplete");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* PlayAnnouncementArg::GetExtensionsStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequenceOf staticDesc;

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
        staticDesc.SetCloneForFactory(new Extensions(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 3));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = Extensions::GetExtensionFieldStaticDescription();
        staticDesc.SetNamedTypeName("extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




