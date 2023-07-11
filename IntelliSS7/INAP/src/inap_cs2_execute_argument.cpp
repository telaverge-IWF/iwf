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


#include <inap_cs2_execute_argument.h>

#include <AsnDescSet.h>
#include <AsnDescObjectIdentifier.h>
#include <AsnDescSequenceOf.h>
#include <AsnDescSequence.h>
#include <AsnDescChoice.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type Name is a reference => no code generated.


AsnDescObject* ExecuteArgument::Method_id::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescObjectIdentifier staticDesc;

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

        staticDesc.SetCloneForFactory(new Method_id(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc.SetNamedTypeName("method-id");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




////////// Begin Nested Class //////////


// Type AttributeTypeAndValue is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* ExecuteArgument::Input_assertions::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_INAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new Input_assertions(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 2));
        staticDesc._clauseOptional = true;
        staticDesc._element = GetAttributeTypeAndValueStaticDescription();
        staticDesc.SetNamedTypeName("input-assertions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ExecuteArgument::Input_assertions::GetAttributeTypeAndValueStaticDescription()
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
        staticDesc.SetCloneForFactory(new AttributeTypeAndValue(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = AttributeTypeAndValue::GetTypeStaticDescription();
        staticDesc._elementVect[1] = AttributeTypeAndValue::GetValueStaticDescription();
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


// Type SpecificInput is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* ExecuteArgument::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSet staticDesc(4);

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

        staticDesc.SetCloneForFactory(new ExecuteArgument(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 17));
        staticDesc._elementVect[0] = GetObjectStaticDescription();
        staticDesc._elementVect[1] = GetMethod_idStaticDescription();
        staticDesc._elementVect[2] = GetInput_assertionsStaticDescription();
        staticDesc._elementVect[3] = GetSpecific_inputStaticDescription();
        staticDesc.SetTypeName("ExecuteArgument");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ExecuteArgument::GetObjectStaticDescription()
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
        staticDesc.SetCloneForFactory(new Name(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._choiceList.push_back(Name::GetRdnSequenceStaticDescription());
        staticDesc.SetNamedTypeName("object");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ExecuteArgument::GetMethod_idStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescObjectIdentifier staticDesc;

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
        staticDesc.SetCloneForFactory(new Method_id(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc.SetNamedTypeName("method-id");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ExecuteArgument::GetInput_assertionsStaticDescription()
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
        staticDesc.SetCloneForFactory(new Input_assertions(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 2));
        staticDesc._clauseOptional = true;
        staticDesc._element = Input_assertions::GetAttributeTypeAndValueStaticDescription();
        staticDesc.SetNamedTypeName("input-assertions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ExecuteArgument::GetSpecific_inputStaticDescription()
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
        staticDesc.SetCloneForFactory(new SpecificInput(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 3));
        staticDesc._clauseOptional = true;
        staticDesc._element = SpecificInput::GetAttributeValueStaticDescription();
        staticDesc.SetNamedTypeName("specific-input");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





