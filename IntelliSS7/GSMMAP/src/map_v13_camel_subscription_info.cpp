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


#include <map_v13_camel_subscription_info.h>

#include <AsnDescSequence.h>
#include <AsnDescNull.h>
#include <AsnDescSequenceOf.h>
#include <AsnDescBitString.h>


using namespace its;
using namespace map_v13;




////////// Begin Nested Class(es) //////////


// Type O_CSI is a reference => no code generated.

// Type O_BcsmCamelTDPCriteriaList is a reference => no code generated.

// Type D_CSI is a reference => no code generated.

// Type T_CSI is a reference => no code generated.

// Type T_BCSM_CAMEL_TDP_CriteriaList is a reference => no code generated.

// Type T_CSI is a reference => no code generated.

// Type T_BCSM_CAMEL_TDP_CriteriaList is a reference => no code generated.


AsnDescObject* CAMEL_SubscriptionInfo::Tif_CSI::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescNull staticDesc;

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
        staticDesc.SetCloneForFactory(new Tif_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 7));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("tif-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}



AsnDescObject* CAMEL_SubscriptionInfo::Tif_CSI_NotificationToCSE::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescNull staticDesc;

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
        staticDesc.SetCloneForFactory(new Tif_CSI_NotificationToCSE(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 8));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("tif-CSI-NotificationToCSE");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


// Type GPRS_CSI is a reference => no code generated.

// Type SMS_CSI is a reference => no code generated.

// Type SS_CSI is a reference => no code generated.

// Type M_CSI is a reference => no code generated.

// Type ExtensionContainer is a reference => no code generated.

// Type SpecificCSI_Withdraw is a reference => no code generated.

// Type SMS_CSI is a reference => no code generated.

// Type MT_smsCAMELTDP_CriteriaList is a reference => no code generated.

// Type MG_CSI is a reference => no code generated.

// Type O_CSI is a reference => no code generated.

// Type O_BcsmCamelTDPCriteriaList is a reference => no code generated.

// Type D_CSI is a reference => no code generated.

// Type T_CSI is a reference => no code generated.

// Type T_BCSM_CAMEL_TDP_CriteriaList is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* CAMEL_SubscriptionInfo::GetStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetO_CSIStaticDescription();
        staticDesc._elementVect[1] = GetO_BcsmCamelTDP_CriteriaListStaticDescription();
        staticDesc._elementVect[2] = GetD_CSIStaticDescription();
        staticDesc._elementVect[3] = GetT_CSIStaticDescription();
        staticDesc._elementVect[4] = GetT_BCSM_CAMEL_TDP_CriteriaListStaticDescription();
        staticDesc._elementVect[5] = GetVt_CSIStaticDescription();
        staticDesc._elementVect[6] = GetVt_BCSM_CAMEL_TDP_CriteriaListStaticDescription();
        staticDesc._elementVect[7] = GetTif_CSIStaticDescription();
        staticDesc._elementVect[8] = GetTif_CSI_NotificationToCSEStaticDescription();
        staticDesc._elementVect[9] = GetGprs_CSIStaticDescription();
        staticDesc._elementVect[10] = GetMo_sms_CSIStaticDescription();
        staticDesc._elementVect[11] = GetSs_CSIStaticDescription();
        staticDesc._elementVect[12] = GetM_CSIStaticDescription();
        staticDesc._elementVect[13] = GetExtensionContainerStaticDescription();
        staticDesc._elementVect[14] = GetSpecificCSIDeletedListStaticDescription();
        staticDesc._elementVect[15] = GetMt_sms_CSIStaticDescription();
        staticDesc._elementVect[16] = GetMt_smsCAMELTDP_CriteriaListStaticDescription();
        staticDesc._elementVect[17] = GetMg_csiStaticDescription();
        staticDesc._elementVect[18] = GetO_IM_CSIStaticDescription();
        staticDesc._elementVect[19] = GetO_IM_BcsmCamelTDP_CriteriaListStaticDescription();
        staticDesc._elementVect[20] = GetD_IM_CSIStaticDescription();
        staticDesc._elementVect[21] = GetVt_IM_CSIStaticDescription();
        staticDesc._elementVect[22] = GetVt_IM_BCSM_CAMEL_TDP_CriteriaListStaticDescription();
        staticDesc.SetTypeName("CAMEL-SubscriptionInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetO_CSIStaticDescription()
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
        staticDesc.SetCloneForFactory(new O_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = O_CSI::GetO_BcsmCamelTDPDataListStaticDescription();
        staticDesc._elementVect[1] = O_CSI::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[2] = O_CSI::GetCamelCapabilityHandlingStaticDescription();
        staticDesc._elementVect[3] = O_CSI::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[4] = O_CSI::GetCsiActiveStaticDescription();
        staticDesc.SetNamedTypeName("o-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetO_BcsmCamelTDP_CriteriaListStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = O_BcsmCamelTDPCriteriaList::GetO_BcsmCamelTDP_CriteriaStaticDescription();
        staticDesc.SetNamedTypeName("o-BcsmCamelTDP-CriteriaList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetD_CSIStaticDescription()
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
        staticDesc.SetCloneForFactory(new D_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 2));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = D_CSI::GetDp_AnalysedInfoCriteriaListStaticDescription();
        staticDesc._elementVect[1] = D_CSI::GetCamelCapabilityHandlingStaticDescription();
        staticDesc._elementVect[2] = D_CSI::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[3] = D_CSI::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[4] = D_CSI::GetCsi_ActiveStaticDescription();
        staticDesc.SetNamedTypeName("d-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetT_CSIStaticDescription()
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
        staticDesc.SetCloneForFactory(new T_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 3));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = T_CSI::GetT_BcsmCamelTDPDataListStaticDescription();
        staticDesc._elementVect[1] = T_CSI::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[2] = T_CSI::GetCamelCapabilityHandlingStaticDescription();
        staticDesc._elementVect[3] = T_CSI::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[4] = T_CSI::GetCsi_ActiveStaticDescription();
        staticDesc.SetNamedTypeName("t-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetT_BCSM_CAMEL_TDP_CriteriaListStaticDescription()
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
        staticDesc.SetCloneForFactory(new T_BCSM_CAMEL_TDP_CriteriaList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 4));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = T_BCSM_CAMEL_TDP_CriteriaList::GetT_BCSM_CAMEL_TDP_CriteriaStaticDescription();
        staticDesc.SetNamedTypeName("t-BCSM-CAMEL-TDP-CriteriaList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetVt_CSIStaticDescription()
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
        staticDesc.SetCloneForFactory(new T_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 5));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = T_CSI::GetT_BcsmCamelTDPDataListStaticDescription();
        staticDesc._elementVect[1] = T_CSI::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[2] = T_CSI::GetCamelCapabilityHandlingStaticDescription();
        staticDesc._elementVect[3] = T_CSI::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[4] = T_CSI::GetCsi_ActiveStaticDescription();
        staticDesc.SetNamedTypeName("vt-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetVt_BCSM_CAMEL_TDP_CriteriaListStaticDescription()
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
        staticDesc.SetCloneForFactory(new T_BCSM_CAMEL_TDP_CriteriaList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 6));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = T_BCSM_CAMEL_TDP_CriteriaList::GetT_BCSM_CAMEL_TDP_CriteriaStaticDescription();
        staticDesc.SetNamedTypeName("vt-BCSM-CAMEL-TDP-CriteriaList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetTif_CSIStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescNull staticDesc;

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
        staticDesc.SetCloneForFactory(new Tif_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 7));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("tif-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetTif_CSI_NotificationToCSEStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescNull staticDesc;

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
        staticDesc.SetCloneForFactory(new Tif_CSI_NotificationToCSE(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 8));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("tif-CSI-NotificationToCSE");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetGprs_CSIStaticDescription()
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
        staticDesc.SetCloneForFactory(new GPRS_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 9));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GPRS_CSI::GetGprs_CamelTDPDataListStaticDescription();
        staticDesc._elementVect[1] = GPRS_CSI::GetCamelCapabilityHandlingStaticDescription();
        staticDesc._elementVect[2] = GPRS_CSI::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[3] = GPRS_CSI::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[4] = GPRS_CSI::GetCsi_ActiveStaticDescription();
        staticDesc.SetNamedTypeName("gprs-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetMo_sms_CSIStaticDescription()
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
        staticDesc.SetCloneForFactory(new SMS_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 10));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = SMS_CSI::GetSms_CAMEL_TDP_DataListStaticDescription();
        staticDesc._elementVect[1] = SMS_CSI::GetCamelCapabilityHandlingStaticDescription();
        staticDesc._elementVect[2] = SMS_CSI::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[3] = SMS_CSI::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[4] = SMS_CSI::GetCsi_ActiveStaticDescription();
        staticDesc.SetNamedTypeName("mo-sms-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetSs_CSIStaticDescription()
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
        staticDesc.SetCloneForFactory(new SS_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 11));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = SS_CSI::GetSs_CamelDataStaticDescription();
        staticDesc._elementVect[1] = SS_CSI::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[2] = SS_CSI::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[3] = SS_CSI::GetCsi_ActiveStaticDescription();
        staticDesc.SetNamedTypeName("ss-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetM_CSIStaticDescription()
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
        staticDesc.SetCloneForFactory(new M_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 12));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = M_CSI::GetMobilityTriggersStaticDescription();
        staticDesc._elementVect[1] = M_CSI::GetServiceKeyStaticDescription();
        staticDesc._elementVect[2] = M_CSI::GetGsmSCF_AddressStaticDescription();
        staticDesc._elementVect[3] = M_CSI::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[4] = M_CSI::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[5] = M_CSI::GetCsi_ActiveStaticDescription();
        staticDesc.SetNamedTypeName("m-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetExtensionContainerStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 13));
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

AsnDescObject* CAMEL_SubscriptionInfo::GetSpecificCSIDeletedListStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescBitString staticDesc;

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
        staticDesc.SetCloneForFactory(new SpecificCSI_Withdraw(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 14));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 8;
        staticDesc._maxSize = 32;
        staticDesc.SetNamedTypeName("specificCSIDeletedList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetMt_sms_CSIStaticDescription()
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
        staticDesc.SetCloneForFactory(new SMS_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 15));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = SMS_CSI::GetSms_CAMEL_TDP_DataListStaticDescription();
        staticDesc._elementVect[1] = SMS_CSI::GetCamelCapabilityHandlingStaticDescription();
        staticDesc._elementVect[2] = SMS_CSI::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[3] = SMS_CSI::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[4] = SMS_CSI::GetCsi_ActiveStaticDescription();
        staticDesc.SetNamedTypeName("mt-sms-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetMt_smsCAMELTDP_CriteriaListStaticDescription()
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
        staticDesc.SetCloneForFactory(new MT_smsCAMELTDP_CriteriaList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = MT_smsCAMELTDP_CriteriaList::GetMT_smsCAMELTDP_CriteriaStaticDescription();
        staticDesc.SetNamedTypeName("mt-smsCAMELTDP-CriteriaList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetMg_csiStaticDescription()
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
        staticDesc.SetCloneForFactory(new MG_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 17));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = MG_CSI::GetMobilityTriggersStaticDescription();
        staticDesc._elementVect[1] = MG_CSI::GetServiceKeyStaticDescription();
        staticDesc._elementVect[2] = MG_CSI::GetGsmSCF_AddressStaticDescription();
        staticDesc._elementVect[3] = MG_CSI::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[4] = MG_CSI::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[5] = MG_CSI::GetCsi_ActiveStaticDescription();
        staticDesc.SetNamedTypeName("mg-csi");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetO_IM_CSIStaticDescription()
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
        staticDesc.SetCloneForFactory(new O_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 18));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = O_CSI::GetO_BcsmCamelTDPDataListStaticDescription();
        staticDesc._elementVect[1] = O_CSI::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[2] = O_CSI::GetCamelCapabilityHandlingStaticDescription();
        staticDesc._elementVect[3] = O_CSI::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[4] = O_CSI::GetCsiActiveStaticDescription();
        staticDesc.SetNamedTypeName("o-IM-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetO_IM_BcsmCamelTDP_CriteriaListStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 19));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = O_BcsmCamelTDPCriteriaList::GetO_BcsmCamelTDP_CriteriaStaticDescription();
        staticDesc.SetNamedTypeName("o-IM-BcsmCamelTDP-CriteriaList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetD_IM_CSIStaticDescription()
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
        staticDesc.SetCloneForFactory(new D_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 20));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = D_CSI::GetDp_AnalysedInfoCriteriaListStaticDescription();
        staticDesc._elementVect[1] = D_CSI::GetCamelCapabilityHandlingStaticDescription();
        staticDesc._elementVect[2] = D_CSI::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[3] = D_CSI::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[4] = D_CSI::GetCsi_ActiveStaticDescription();
        staticDesc.SetNamedTypeName("d-IM-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetVt_IM_CSIStaticDescription()
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
        staticDesc.SetCloneForFactory(new T_CSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 21));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = T_CSI::GetT_BcsmCamelTDPDataListStaticDescription();
        staticDesc._elementVect[1] = T_CSI::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[2] = T_CSI::GetCamelCapabilityHandlingStaticDescription();
        staticDesc._elementVect[3] = T_CSI::GetNotificationToCSEStaticDescription();
        staticDesc._elementVect[4] = T_CSI::GetCsi_ActiveStaticDescription();
        staticDesc.SetNamedTypeName("vt-IM-CSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CAMEL_SubscriptionInfo::GetVt_IM_BCSM_CAMEL_TDP_CriteriaListStaticDescription()
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
        staticDesc.SetCloneForFactory(new T_BCSM_CAMEL_TDP_CriteriaList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 22));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = T_BCSM_CAMEL_TDP_CriteriaList::GetT_BCSM_CAMEL_TDP_CriteriaStaticDescription();
        staticDesc.SetNamedTypeName("vt-IM-BCSM-CAMEL-TDP-CriteriaList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





