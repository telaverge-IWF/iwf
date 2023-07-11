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


#include <map_v9_any_time_modification_res.h>

#include <AsnDescSequence.h>
#include <AsnDescChoice.h>


using namespace its;
using namespace map_v9;




////////// Begin Nested Class(es) //////////


// Type Ext_SS_InfoFor_CSE is a reference => no code generated.

// Type CAMEL_SubscriptionInfo is a reference => no code generated.

// Type ExtensionContainer is a reference => no code generated.

// Type ODB_Info is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* AnyTimeModificationRes::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new AnyTimeModificationRes(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetSs_InfoFor_CSEStaticDescription();
        staticDesc._elementVect[1] = GetCamel_SubscriptionInfoStaticDescription();
        staticDesc._elementVect[2] = GetExtensionContainerStaticDescription();
        staticDesc._elementVect[3] = GetOdb_InfoStaticDescription();
        staticDesc.SetTypeName("AnyTimeModificationRes");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* AnyTimeModificationRes::GetSs_InfoFor_CSEStaticDescription()
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
        staticDesc.SetCloneForFactory(new Ext_SS_InfoFor_CSE(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseOptional = true;
        staticDesc._choiceList.push_back(Ext_SS_InfoFor_CSE::GetForwardingInfoFor_CSEStaticDescription());
        staticDesc._choiceList.push_back(Ext_SS_InfoFor_CSE::GetCallBarringInfoFor_CSEStaticDescription());
        staticDesc.SetNamedTypeName("ss-InfoFor-CSE");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* AnyTimeModificationRes::GetCamel_SubscriptionInfoStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(23);

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
        staticDesc.SetCloneForFactory(new CAMEL_SubscriptionInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = CAMEL_SubscriptionInfo::GetO_CSIStaticDescription();
        staticDesc._elementVect[1] = CAMEL_SubscriptionInfo::GetO_BcsmCamelTDP_CriteriaListStaticDescription();
        staticDesc._elementVect[2] = CAMEL_SubscriptionInfo::GetD_CSIStaticDescription();
        staticDesc._elementVect[3] = CAMEL_SubscriptionInfo::GetT_CSIStaticDescription();
        staticDesc._elementVect[4] = CAMEL_SubscriptionInfo::GetT_BCSM_CAMEL_TDP_CriteriaListStaticDescription();
        staticDesc._elementVect[5] = CAMEL_SubscriptionInfo::GetVt_CSIStaticDescription();
        staticDesc._elementVect[6] = CAMEL_SubscriptionInfo::GetVt_BCSM_CAMEL_TDP_CriteriaListStaticDescription();
        staticDesc._elementVect[7] = CAMEL_SubscriptionInfo::GetTif_CSIStaticDescription();
        staticDesc._elementVect[8] = CAMEL_SubscriptionInfo::GetTif_CSI_NotificationToCSEStaticDescription();
        staticDesc._elementVect[9] = CAMEL_SubscriptionInfo::GetGprs_CSIStaticDescription();
        staticDesc._elementVect[10] = CAMEL_SubscriptionInfo::GetMo_sms_CSIStaticDescription();
        staticDesc._elementVect[11] = CAMEL_SubscriptionInfo::GetSs_CSIStaticDescription();
        staticDesc._elementVect[12] = CAMEL_SubscriptionInfo::GetM_CSIStaticDescription();
        staticDesc._elementVect[13] = CAMEL_SubscriptionInfo::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[14] = CAMEL_SubscriptionInfo::GetSpecificCSIDeletedListStaticDescription();
        staticDesc._elementVect[15] = CAMEL_SubscriptionInfo::GetMt_sms_CSIStaticDescription();
        staticDesc._elementVect[16] = CAMEL_SubscriptionInfo::GetMt_smsCAMELTDP_CriteriaListStaticDescription();
        staticDesc._elementVect[17] = CAMEL_SubscriptionInfo::GetMg_csiStaticDescription();
        staticDesc._elementVect[18] = CAMEL_SubscriptionInfo::GetO_IM_CSIStaticDescription();
        staticDesc._elementVect[19] = CAMEL_SubscriptionInfo::GetO_IM_BcsmCamelTDP_CriteriaListStaticDescription();
        staticDesc._elementVect[20] = CAMEL_SubscriptionInfo::GetD_IM_CSIStaticDescription();
        staticDesc._elementVect[21] = CAMEL_SubscriptionInfo::GetVt_IM_CSIStaticDescription();
        staticDesc._elementVect[22] = CAMEL_SubscriptionInfo::GetVt_IM_BCSM_CAMEL_TDP_CriteriaListStaticDescription();
        staticDesc.SetNamedTypeName("camel-SubscriptionInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* AnyTimeModificationRes::GetExtensionContainerStaticDescription()
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

AsnDescObject* AnyTimeModificationRes::GetOdb_InfoStaticDescription()
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
        staticDesc.SetCloneForFactory(new ODB_Info(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 3));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ODB_Info::GetOdb_DataStaticDescription();
        staticDesc._elementVect[1] = ODB_Info::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[2] = ODB_Info::GetExtensionContainerStaticDescription();
        staticDesc.SetNamedTypeName("odb-Info");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




