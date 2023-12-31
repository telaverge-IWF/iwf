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


#include <map_v9_dp_analysed_info_criteria_list.h>

#include <AsnDescSequenceOf.h>
#include <AsnDescSequence.h>


using namespace its;
using namespace map_v9;




////////// Begin Nested Class //////////


// Type DP_AnalysedInfoCriterium is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* DP_AnalysedInfoCriteriaList::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new DP_AnalysedInfoCriteriaList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = GetDP_AnalysedInfoCriteriumStaticDescription();
        staticDesc.SetTypeName("DP-AnalysedInfoCriteriaList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* DP_AnalysedInfoCriteriaList::GetDP_AnalysedInfoCriteriumStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(5);

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
        staticDesc.SetCloneForFactory(new DP_AnalysedInfoCriterium(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = DP_AnalysedInfoCriterium::GetDialledNumberStaticDescription();
        staticDesc._elementVect[1] = DP_AnalysedInfoCriterium::GetServiceKeyStaticDescription();
        staticDesc._elementVect[2] = DP_AnalysedInfoCriterium::GetGsmSCF_AddressStaticDescription();
        staticDesc._elementVect[3] = DP_AnalysedInfoCriterium::GetDefaultCallHandlingStaticDescription();
        staticDesc._elementVect[4] = DP_AnalysedInfoCriterium::GetExtensionContainerStaticDescription();
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





