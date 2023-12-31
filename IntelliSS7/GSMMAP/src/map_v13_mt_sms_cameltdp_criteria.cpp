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


#include <map_v13_mt_sms_cameltdp_criteria.h>

#include <AsnDescSequence.h>
#include <AsnDescEnumerated.h>
#include <AsnDescSequenceOf.h>


using namespace its;
using namespace map_v13;




////////// Begin Nested Class(es) //////////


// Type SMS_TriggerDetectionPoint is a reference => no code generated.

// Type TPDU_TypeCriterion is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* MT_smsCAMELTDP_Criteria::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new MT_smsCAMELTDP_Criteria(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetSms_TriggerDetectionPointStaticDescription();
        staticDesc._elementVect[1] = GetTpdu_TypeCriterionStaticDescription();
        staticDesc.SetTypeName("MT-smsCAMELTDP-Criteria");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MT_smsCAMELTDP_Criteria::GetSms_TriggerDetectionPointStaticDescription()
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
        staticDesc.SetCloneForFactory(new SMS_TriggerDetectionPoint(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(1);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"sms-CollectedInfo", 1}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("sms-TriggerDetectionPoint");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MT_smsCAMELTDP_Criteria::GetTpdu_TypeCriterionStaticDescription()
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
        staticDesc.SetCloneForFactory(new TPDU_TypeCriterion(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 5;
        staticDesc._element = TPDU_TypeCriterion::GetMT_SMS_TPDU_TypeStaticDescription();
        staticDesc.SetNamedTypeName("tpdu-TypeCriterion");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





