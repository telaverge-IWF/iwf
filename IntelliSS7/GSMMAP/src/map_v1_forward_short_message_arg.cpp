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


#include <map_v1_forward_short_message_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescChoice.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace map_v1;




////////// Begin Nested Class(es) //////////


// Type SM_RP_DA is a reference => no code generated.

// Type SM_RP_OA is a reference => no code generated.

// Type SM_RP_UI is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* ForwardShortMessageArg::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new ForwardShortMessageArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GetSm_RP_DAStaticDescription();
        staticDesc._elementVect[1] = GetSm_RP_OAStaticDescription();
        staticDesc._elementVect[2] = GetSm_RP_UIStaticDescription();
        staticDesc.SetTypeName("ForwardShortMessageArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ForwardShortMessageArg::GetSm_RP_DAStaticDescription()
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
        staticDesc.SetCloneForFactory(new SM_RP_DA(&staticDesc));
        staticDesc._choiceList.push_back(SM_RP_DA::GetImsiStaticDescription());
        staticDesc._choiceList.push_back(SM_RP_DA::GetLMsIdStaticDescription());
        staticDesc._choiceList.push_back(SM_RP_DA::GetRoamingNumberStaticDescription());
        staticDesc._choiceList.push_back(SM_RP_DA::GetServiceCenterAddressStaticDescription());
        staticDesc.SetNamedTypeName("sm-RP-DA");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ForwardShortMessageArg::GetSm_RP_OAStaticDescription()
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
        staticDesc.SetCloneForFactory(new SM_RP_OA(&staticDesc));
        staticDesc._choiceList.push_back(SM_RP_OA::GetMsIsdnStaticDescription());
        staticDesc._choiceList.push_back(SM_RP_OA::GetServiceCenterAddressStaticDescription());
        staticDesc.SetNamedTypeName("sm-RP-OA");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ForwardShortMessageArg::GetSm_RP_UIStaticDescription()
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
        staticDesc.SetCloneForFactory(new SM_RP_UI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 4));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 200;
        staticDesc.SetNamedTypeName("sm-RP-UI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





