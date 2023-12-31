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


#include <inap_cs2_user_information.h>

#include <AsnDescSequence.h>
#include <AsnDescChoice.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type InfoToSend is a reference => no code generated.

// Type Constraints is a reference => no code generated.

// Type InfoToSend is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* UserInformation::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new UserInformation(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GetInfoToSendStaticDescription();
        staticDesc._elementVect[1] = GetConstraintsStaticDescription();
        staticDesc._elementVect[2] = GetErrorInfoStaticDescription();
        staticDesc.SetTypeName("UserInformation");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* UserInformation::GetInfoToSendStaticDescription()
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
        staticDesc.SetCloneForFactory(new InfoToSend(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._choiceList.push_back(InfoToSend::GetMessageIDStaticDescription());
        staticDesc._choiceList.push_back(InfoToSend::GetToneIdStaticDescription());
        staticDesc._choiceList.push_back(InfoToSend::GetDisplayInformationStaticDescription());
        staticDesc.SetNamedTypeName("infoToSend");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* UserInformation::GetConstraintsStaticDescription()
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
        staticDesc.SetCloneForFactory(new Constraints(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._elementVect[0] = Constraints::GetMaximumNumberOfDigitsStaticDescription();
        staticDesc._elementVect[1] = Constraints::GetMinimumNumberOfDigitsStaticDescription();
        staticDesc._elementVect[2] = Constraints::GetTypeOfRequestedInfoStaticDescription();
        staticDesc._elementVect[3] = Constraints::GetNumberOfAllowedRetriesStaticDescription();
        staticDesc.SetNamedTypeName("constraints");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* UserInformation::GetErrorInfoStaticDescription()
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
        staticDesc.SetCloneForFactory(new InfoToSend(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 2));
        staticDesc._clauseOptional = true;
        staticDesc._choiceList.push_back(InfoToSend::GetMessageIDStaticDescription());
        staticDesc._choiceList.push_back(InfoToSend::GetToneIdStaticDescription());
        staticDesc._choiceList.push_back(InfoToSend::GetDisplayInformationStaticDescription());
        staticDesc.SetNamedTypeName("errorInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





