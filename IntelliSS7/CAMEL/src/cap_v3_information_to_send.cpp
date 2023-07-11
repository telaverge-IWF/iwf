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


#include <cap_v3_information_to_send.h>

#include <AsnDescChoice.h>
#include <AsnDescSequence.h>


using namespace its;
using namespace cap_v3;




////////// Begin Nested Class(es) //////////


// Type InbandInfo is a reference => no code generated.

// Type Tone is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* InformationToSend::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new InformationToSend(&staticDesc));
        staticDesc._choiceList.push_back(GetInbandInfoStaticDescription());
        staticDesc._choiceList.push_back(GetToneStaticDescription());
        staticDesc.SetTypeName("InformationToSend");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InformationToSend::GetInbandInfoStaticDescription()
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
        staticDesc.SetCloneForFactory(new InbandInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = InbandInfo::GetMessageIDStaticDescription();
        staticDesc._elementVect[1] = InbandInfo::GetNumberOfRepetitionsStaticDescription();
        staticDesc._elementVect[2] = InbandInfo::GetDurationStaticDescription();
        staticDesc._elementVect[3] = InbandInfo::GetIntervalStaticDescription();
        staticDesc.SetNamedTypeName("inbandInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* InformationToSend::GetToneStaticDescription()
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
        staticDesc.SetCloneForFactory(new Tone(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = Tone::GetToneIDStaticDescription();
        staticDesc._elementVect[1] = Tone::GetDurationStaticDescription();
        staticDesc.SetNamedTypeName("tone");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





