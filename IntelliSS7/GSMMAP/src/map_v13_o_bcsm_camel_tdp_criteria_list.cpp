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


#include <map_v13_o_bcsm_camel_tdp_criteria_list.h>

#include <AsnDescSequenceOf.h>
#include <AsnDescSequence.h>


using namespace its;
using namespace map_v13;




////////// Begin Nested Class //////////


// Type O_BcsmCamelTDP_Criteria is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* O_BcsmCamelTDPCriteriaList::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new O_BcsmCamelTDPCriteriaList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = GetO_BcsmCamelTDP_CriteriaStaticDescription();
        staticDesc.SetTypeName("O-BcsmCamelTDPCriteriaList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* O_BcsmCamelTDPCriteriaList::GetO_BcsmCamelTDP_CriteriaStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(6);

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
        staticDesc.SetCloneForFactory(new O_BcsmCamelTDP_Criteria(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = O_BcsmCamelTDP_Criteria::GetO_BcsmTriggerDetectionPointStaticDescription();
        staticDesc._elementVect[1] = O_BcsmCamelTDP_Criteria::GetDestinationNumberCriteriaStaticDescription();
        staticDesc._elementVect[2] = O_BcsmCamelTDP_Criteria::GetBasicServiceCriteriaStaticDescription();
        staticDesc._elementVect[3] = O_BcsmCamelTDP_Criteria::GetCallTypeCriteriaStaticDescription();
        staticDesc._elementVect[4] = O_BcsmCamelTDP_Criteria::GetO_CauseValueCriteriaStaticDescription();
        staticDesc._elementVect[5] = O_BcsmCamelTDP_Criteria::GetExtensionContainerStaticDescription();
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





