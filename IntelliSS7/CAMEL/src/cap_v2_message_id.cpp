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


#include <cap_v2_message_id.h>

#include <AsnDescChoice.h>
#include <AsnDescSequence.h>
#include <AsnDescOctetString.h>
#include <AsnDescBaseString.h>
#include <AsnDescSequenceOf.h>
#include <AsnDescInteger.h>


using namespace its;
using namespace cap_v2;




////////// Begin Nested Class(es) //////////


// Type Integer4 is a reference => no code generated.



////////// Begin Nested Class(es) //////////


// Type IA5String is a reference => no code generated.


AsnDescObject* MessageID::Text::Attributes::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new Attributes(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 2;
        staticDesc._maxSize = 10;
        staticDesc.SetNamedTypeName("attributes");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


////////// End Nested Class(es) //////////

AsnDescObject* MessageID::Text::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new Text(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._elementVect[0] = GetMessageContentStaticDescription();
        staticDesc._elementVect[1] = GetAttributesStaticDescription();
        staticDesc.SetNamedTypeName("text");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MessageID::Text::GetMessageContentStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescBaseString staticDesc;

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
        staticDesc.SetCloneForFactory(new IA5String(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc.SetNamedTypeName("messageContent");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MessageID::Text::GetAttributesStaticDescription()
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
        staticDesc.SetCloneForFactory(new Attributes(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 2;
        staticDesc._maxSize = 10;
        staticDesc.SetNamedTypeName("attributes");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




////////// Begin Nested Class //////////


// Type Integer4 is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* MessageID::ElementaryMessageIDs::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new ElementaryMessageIDs(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 29));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 5;
        staticDesc._element = GetInteger4StaticDescription();
        staticDesc.SetNamedTypeName("elementaryMessageIDs");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MessageID::ElementaryMessageIDs::GetInteger4StaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescInteger staticDesc;

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
        staticDesc.SetCloneForFactory(new Integer4(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 2));
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




////////// Begin Nested Class(es) //////////


// Type Integer4 is a reference => no code generated.



////////// Begin Nested Class //////////


// Type VariablePart is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* MessageID::VariableMessage::VariableParts::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new VariableParts(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 5;
        staticDesc._element = GetVariablePartStaticDescription();
        staticDesc.SetNamedTypeName("variableParts");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MessageID::VariableMessage::VariableParts::GetVariablePartStaticDescription()
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
        staticDesc.SetCloneForFactory(new VariablePart(&staticDesc));
        staticDesc._choiceList.push_back(VariablePart::GetIntegerStaticDescription());
        staticDesc._choiceList.push_back(VariablePart::GetNumberStaticDescription());
        staticDesc._choiceList.push_back(VariablePart::GetTimeStaticDescription());
        staticDesc._choiceList.push_back(VariablePart::GetDateStaticDescription());
        staticDesc._choiceList.push_back(VariablePart::GetPriceStaticDescription());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


////////// End Nested Class(es) //////////

AsnDescObject* MessageID::VariableMessage::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new VariableMessage(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 30));
        staticDesc._elementVect[0] = GetElementaryMessageIDStaticDescription();
        staticDesc._elementVect[1] = GetVariablePartsStaticDescription();
        staticDesc.SetNamedTypeName("variableMessage");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MessageID::VariableMessage::GetElementaryMessageIDStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescInteger staticDesc;

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
        staticDesc.SetCloneForFactory(new Integer4(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc.SetNamedTypeName("elementaryMessageID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MessageID::VariableMessage::GetVariablePartsStaticDescription()
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
        staticDesc.SetCloneForFactory(new VariableParts(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 5;
        staticDesc._element = VariableParts::GetVariablePartStaticDescription();
        staticDesc.SetNamedTypeName("variableParts");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


////////// End Nested Class(es) //////////

AsnDescObject* MessageID::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new MessageID(&staticDesc));
        staticDesc._choiceList.push_back(GetElementaryMessageIDStaticDescription());
        staticDesc._choiceList.push_back(GetTextStaticDescription());
        staticDesc._choiceList.push_back(GetElementaryMessageIDsStaticDescription());
        staticDesc._choiceList.push_back(GetVariableMessageStaticDescription());
        staticDesc.SetTypeName("MessageID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MessageID::GetElementaryMessageIDStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescInteger staticDesc;

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
        staticDesc.SetCloneForFactory(new Integer4(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc.SetNamedTypeName("elementaryMessageID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MessageID::GetTextStaticDescription()
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
        staticDesc.SetCloneForFactory(new Text(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._elementVect[0] = Text::GetMessageContentStaticDescription();
        staticDesc._elementVect[1] = Text::GetAttributesStaticDescription();
        staticDesc.SetNamedTypeName("text");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MessageID::GetElementaryMessageIDsStaticDescription()
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
        staticDesc.SetCloneForFactory(new ElementaryMessageIDs(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 29));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 5;
        staticDesc._element = ElementaryMessageIDs::GetInteger4StaticDescription();
        staticDesc.SetNamedTypeName("elementaryMessageIDs");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MessageID::GetVariableMessageStaticDescription()
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
        staticDesc.SetCloneForFactory(new VariableMessage(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 30));
        staticDesc._elementVect[0] = VariableMessage::GetElementaryMessageIDStaticDescription();
        staticDesc._elementVect[1] = VariableMessage::GetVariablePartsStaticDescription();
        staticDesc.SetNamedTypeName("variableMessage");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





