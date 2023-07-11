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


#include <map_v9_supported_codecs_list.h>

#include <AsnDescSequence.h>


using namespace its;
using namespace map_v9;




////////// Begin Nested Class(es) //////////


// Type CodecList is a reference => no code generated.

// Type CodecList is a reference => no code generated.

// Type ExtensionContainer is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* SupportedCodecsList::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new SupportedCodecsList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetUtranCodecListStaticDescription();
        staticDesc._elementVect[1] = GetGeranCodecListStaticDescription();
        staticDesc._elementVect[2] = GetExtensionContainerStaticDescription();
        staticDesc.SetTypeName("SupportedCodecsList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SupportedCodecsList::GetUtranCodecListStaticDescription()
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
        staticDesc.SetCloneForFactory(new CodecList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = CodecList::GetCodec1StaticDescription();
        staticDesc._elementVect[1] = CodecList::GetCodec2StaticDescription();
        staticDesc._elementVect[2] = CodecList::GetCodec3StaticDescription();
        staticDesc._elementVect[3] = CodecList::GetCodec4StaticDescription();
        staticDesc._elementVect[4] = CodecList::GetCodec5StaticDescription();
        staticDesc._elementVect[5] = CodecList::GetCodec6StaticDescription();
        staticDesc._elementVect[6] = CodecList::GetCodec7StaticDescription();
        staticDesc._elementVect[7] = CodecList::GetCodec8StaticDescription();
        staticDesc._elementVect[8] = CodecList::GetExtensionContainerStaticDescription();
        staticDesc.SetNamedTypeName("utranCodecList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SupportedCodecsList::GetGeranCodecListStaticDescription()
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
        staticDesc.SetCloneForFactory(new CodecList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = CodecList::GetCodec1StaticDescription();
        staticDesc._elementVect[1] = CodecList::GetCodec2StaticDescription();
        staticDesc._elementVect[2] = CodecList::GetCodec3StaticDescription();
        staticDesc._elementVect[3] = CodecList::GetCodec4StaticDescription();
        staticDesc._elementVect[4] = CodecList::GetCodec5StaticDescription();
        staticDesc._elementVect[5] = CodecList::GetCodec6StaticDescription();
        staticDesc._elementVect[6] = CodecList::GetCodec7StaticDescription();
        staticDesc._elementVect[7] = CodecList::GetCodec8StaticDescription();
        staticDesc._elementVect[8] = CodecList::GetExtensionContainerStaticDescription();
        staticDesc.SetNamedTypeName("geranCodecList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SupportedCodecsList::GetExtensionContainerStaticDescription()
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





