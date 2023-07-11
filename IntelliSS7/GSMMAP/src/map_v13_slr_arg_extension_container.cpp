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


#include <map_v13_slr_arg_extension_container.h>

#include <AsnDescSequence.h>
#include <AsnDescSequenceOf.h>


using namespace its;
using namespace map_v13;




////////// Begin Nested Class(es) //////////


// Type PrivateExtensionList is a reference => no code generated.

// Type SLR_Arg_PCS_Extensions is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* SLR_ArgExtensionContainer::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new SLR_ArgExtensionContainer(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetPrivateExtensionListStaticDescription();
        staticDesc._elementVect[1] = GetSlr_Arg_PCS_ExtensionsStaticDescription();
        staticDesc.SetTypeName("SLR-ArgExtensionContainer");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SLR_ArgExtensionContainer::GetPrivateExtensionListStaticDescription()
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
        staticDesc.SetCloneForFactory(new PrivateExtensionList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = PrivateExtensionList::GetPrivateExtensionStaticDescription();
        staticDesc.SetNamedTypeName("privateExtensionList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SLR_ArgExtensionContainer::GetSlr_Arg_PCS_ExtensionsStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(1);

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
        staticDesc.SetCloneForFactory(new SLR_Arg_PCS_Extensions(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = SLR_Arg_PCS_Extensions::GetNa_ESRK_RequestStaticDescription();
        staticDesc.SetNamedTypeName("slr-Arg-PCS-Extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




