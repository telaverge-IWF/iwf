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


#include <map_v9_send_authentication_info_res.h>

#include <AsnDescSequence.h>
#include <AsnDescChoice.h>


using namespace its;
using namespace map_v9;




////////// Begin Nested Class(es) //////////


// Type AuthenticationSetList is a reference => no code generated.

// Type ExtensionContainer is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* SendAuthenticationInfoRes::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new SendAuthenticationInfoRes(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 3));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetAuthenticationSetListStaticDescription();
        staticDesc._elementVect[1] = GetExtensionContainerStaticDescription();
        staticDesc.SetTypeName("SendAuthenticationInfoRes");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SendAuthenticationInfoRes::GetAuthenticationSetListStaticDescription()
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
        staticDesc.SetCloneForFactory(new AuthenticationSetList(&staticDesc));
        staticDesc._clauseOptional = true;
        staticDesc._choiceList.push_back(AuthenticationSetList::GetTripletListStaticDescription());
        staticDesc._choiceList.push_back(AuthenticationSetList::GetQuintupletListStaticDescription());
        staticDesc.SetNamedTypeName("authenticationSetList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SendAuthenticationInfoRes::GetExtensionContainerStaticDescription()
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




