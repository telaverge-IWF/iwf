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


#include <inap_cs2_service_filtering_response_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescSequenceOf.h>
#include <AsnDescChoice.h>
#include <AsnDescEnumerated.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type CountersValue is a reference => no code generated.

// Type FilteringCriteria is a reference => no code generated.



////////// Begin Nested Class //////////


// Type ExtensionField is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* ServiceFilteringResponseArg::Extensions::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new Extensions(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 2));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 2;
        staticDesc._element = GetExtensionFieldStaticDescription();
        staticDesc.SetNamedTypeName("extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ServiceFilteringResponseArg::Extensions::GetExtensionFieldStaticDescription()
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


// Type ResponseCondition is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* ServiceFilteringResponseArg::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_INAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new ServiceFilteringResponseArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetCountersValueStaticDescription();
        staticDesc._elementVect[1] = GetFilteringCriteriaStaticDescription();
        staticDesc._elementVect[2] = GetExtensionsStaticDescription();
        staticDesc._elementVect[3] = GetResponseConditionStaticDescription();
        staticDesc.SetTypeName("ServiceFilteringResponseArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ServiceFilteringResponseArg::GetCountersValueStaticDescription()
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
        staticDesc.SetCloneForFactory(new CountersValue(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 0;
        staticDesc._maxSize = 100;
        staticDesc._element = CountersValue::GetCounterAndValueStaticDescription();
        staticDesc.SetNamedTypeName("countersValue");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ServiceFilteringResponseArg::GetFilteringCriteriaStaticDescription()
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
        staticDesc.SetCloneForFactory(new FilteringCriteria(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._choiceList.push_back(FilteringCriteria::GetDialledNumberStaticDescription());
        staticDesc._choiceList.push_back(FilteringCriteria::GetCallingLineIDStaticDescription());
        staticDesc._choiceList.push_back(FilteringCriteria::GetServiceKeyStaticDescription());
        staticDesc._choiceList.push_back(FilteringCriteria::GetAddressAndServiceStaticDescription());
        staticDesc.SetNamedTypeName("filteringCriteria");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ServiceFilteringResponseArg::GetExtensionsStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 2));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 2;
        staticDesc._element = Extensions::GetExtensionFieldStaticDescription();
        staticDesc.SetNamedTypeName("extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ServiceFilteringResponseArg::GetResponseConditionStaticDescription()
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
        staticDesc.SetCloneForFactory(new ResponseCondition(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 3));
        staticDesc._clauseOptional = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"intermediateResponse", 0}, {"lastResponse", 1}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("responseCondition");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





