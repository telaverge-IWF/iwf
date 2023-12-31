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


#include <map_v13_call_barred_param.h>

#include <AsnDescChoice.h>
#include <AsnDescEnumerated.h>
#include <AsnDescSequence.h>


using namespace its;
using namespace map_v13;




////////// Begin Nested Class(es) //////////


// Type CallBarringCause is a reference => no code generated.

// Type ExtensibleCallBarredParam is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* CallBarredParam::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new CallBarredParam(&staticDesc));
        staticDesc._choiceList.push_back(GetCallBarringCauseStaticDescription());
        staticDesc._choiceList.push_back(GetExtensibleCallBarredParamStaticDescription());
        staticDesc.SetTypeName("CallBarredParam");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CallBarredParam::GetCallBarringCauseStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescEnumerated staticDesc;

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
        staticDesc.SetCloneForFactory(new CallBarringCause(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"barringServiceActive", 0}, {"operatorBarring", 1}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("callBarringCause");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CallBarredParam::GetExtensibleCallBarredParamStaticDescription()
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
        staticDesc.SetCloneForFactory(new ExtensibleCallBarredParam(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ExtensibleCallBarredParam::GetCallBarringCauseStaticDescription();
        staticDesc._elementVect[1] = ExtensibleCallBarredParam::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[2] = ExtensibleCallBarredParam::GetUnauthorisedMessageOriginatorStaticDescription();
        staticDesc.SetNamedTypeName("extensibleCallBarredParam");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





