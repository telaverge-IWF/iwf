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


#include <map_v9_subscriber_data.h>

#include <AsnDescSequence.h>
#include <AsnDescNull.h>
#include <AsnDescOctetString.h>
#include <AsnDescEnumerated.h>
#include <AsnDescSequenceOf.h>


using namespace its;
using namespace map_v9;




////////// Begin Nested Class(es) //////////


// Type ISDN_AddressString is a reference => no code generated.

// Type Category is a reference => no code generated.

// Type SubscriberStatus is a reference => no code generated.

// Type BearerServiceList is a reference => no code generated.

// Type TeleserviceList is a reference => no code generated.

// Type Ext_SS_InfoList is a reference => no code generated.

// Type ODB_Data is a reference => no code generated.


AsnDescObject* SubscriberData::RoamingRestrictionDueToUnsupportedFeature::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new RoamingRestrictionDueToUnsupportedFeature(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 9));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("roamingRestrictionDueToUnsupportedFeature");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


// Type ZoneCodeList is a reference => no code generated.

// Type VBSDataList is a reference => no code generated.

// Type VGCSDataList is a reference => no code generated.

// Type VlrCamelSubscriptionInfo is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* SubscriberData::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(12);

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

        staticDesc.SetCloneForFactory(new SubscriberData(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GetMsisdnStaticDescription();
        staticDesc._elementVect[1] = GetCategoryStaticDescription();
        staticDesc._elementVect[2] = GetSubscriberStatusStaticDescription();
        staticDesc._elementVect[3] = GetBearerServiceListStaticDescription();
        staticDesc._elementVect[4] = GetTeleserviceListStaticDescription();
        staticDesc._elementVect[5] = GetProvisionedSSStaticDescription();
        staticDesc._elementVect[6] = GetOdb_DataStaticDescription();
        staticDesc._elementVect[7] = GetRoamingRestrictionDueToUnsupportedFeatureStaticDescription();
        staticDesc._elementVect[8] = GetRegionalSubscriptionDataStaticDescription();
        staticDesc._elementVect[9] = GetVbsSubscriptionDataStaticDescription();
        staticDesc._elementVect[10] = GetVgcsSubscriptionDataStaticDescription();
        staticDesc._elementVect[11] = GetVlrCamelSubscriptionInfoStaticDescription();
        staticDesc.SetTypeName("SubscriberData");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SubscriberData::GetMsisdnStaticDescription()
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
        staticDesc.SetCloneForFactory(new ISDN_AddressString(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 20;
        staticDesc.SetNamedTypeName("msisdn");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SubscriberData::GetCategoryStaticDescription()
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
        staticDesc.SetCloneForFactory(new Category(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 1;
        staticDesc.SetNamedTypeName("category");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SubscriberData::GetSubscriberStatusStaticDescription()
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
        staticDesc.SetCloneForFactory(new SubscriberStatus(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 3));
        staticDesc._clauseOptional = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"serviceGranted", 0}, {"operatorDeterminedBarring", 1}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("subscriberStatus");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SubscriberData::GetBearerServiceListStaticDescription()
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
        staticDesc.SetCloneForFactory(new BearerServiceList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 4));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 50;
        staticDesc._element = BearerServiceList::GetExt_BearerServiceCodeStaticDescription();
        staticDesc.SetNamedTypeName("bearerServiceList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SubscriberData::GetTeleserviceListStaticDescription()
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
        staticDesc.SetCloneForFactory(new TeleserviceList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 6));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 20;
        staticDesc._element = TeleserviceList::GetExt_TeleserviceCodeStaticDescription();
        staticDesc.SetNamedTypeName("teleserviceList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SubscriberData::GetProvisionedSSStaticDescription()
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
        staticDesc.SetCloneForFactory(new Ext_SS_InfoList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 7));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 30;
        staticDesc._element = Ext_SS_InfoList::GetExt_SS_InfoStaticDescription();
        staticDesc.SetNamedTypeName("provisionedSS");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SubscriberData::GetOdb_DataStaticDescription()
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
        staticDesc.SetCloneForFactory(new ODB_Data(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 8));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ODB_Data::GetOdb_GeneralDataStaticDescription();
        staticDesc._elementVect[1] = ODB_Data::GetOdb_HPLMN_DataStaticDescription();
        staticDesc._elementVect[2] = ODB_Data::GetExtensionContainerStaticDescription();
        staticDesc.SetNamedTypeName("odb-Data");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SubscriberData::GetRoamingRestrictionDueToUnsupportedFeatureStaticDescription()
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
        staticDesc.SetCloneForFactory(new RoamingRestrictionDueToUnsupportedFeature(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 9));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("roamingRestrictionDueToUnsupportedFeature");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SubscriberData::GetRegionalSubscriptionDataStaticDescription()
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
        staticDesc.SetCloneForFactory(new ZoneCodeList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 10));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = ZoneCodeList::GetZoneCodeStaticDescription();
        staticDesc.SetNamedTypeName("regionalSubscriptionData");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SubscriberData::GetVbsSubscriptionDataStaticDescription()
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
        staticDesc.SetCloneForFactory(new VBSDataList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 11));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 50;
        staticDesc._element = VBSDataList::GetVoiceBroadcastDataStaticDescription();
        staticDesc.SetNamedTypeName("vbsSubscriptionData");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SubscriberData::GetVgcsSubscriptionDataStaticDescription()
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
        staticDesc.SetCloneForFactory(new VGCSDataList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 12));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 50;
        staticDesc._element = VGCSDataList::GetVoiceGroupCallDataStaticDescription();
        staticDesc.SetNamedTypeName("vgcsSubscriptionData");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SubscriberData::GetVlrCamelSubscriptionInfoStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(12);

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
        staticDesc.SetCloneForFactory(new VlrCamelSubscriptionInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 13));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = VlrCamelSubscriptionInfo::GetO_CSIStaticDescription();
        staticDesc._elementVect[1] = VlrCamelSubscriptionInfo::GetExtensionContainerStaticDescription();
        staticDesc._elementVect[2] = VlrCamelSubscriptionInfo::GetSs_CSIStaticDescription();
        staticDesc._elementVect[3] = VlrCamelSubscriptionInfo::GetO_BcsmCamelTDP_CriteriaListStaticDescription();
        staticDesc._elementVect[4] = VlrCamelSubscriptionInfo::GetTif_CSIStaticDescription();
        staticDesc._elementVect[5] = VlrCamelSubscriptionInfo::GetM_CSIStaticDescription();
        staticDesc._elementVect[6] = VlrCamelSubscriptionInfo::GetMo_sms_CSIStaticDescription();
        staticDesc._elementVect[7] = VlrCamelSubscriptionInfo::GetVt_CSIStaticDescription();
        staticDesc._elementVect[8] = VlrCamelSubscriptionInfo::GetT_BCSM_CAMEL_TDP_CriteriaListStaticDescription();
        staticDesc._elementVect[9] = VlrCamelSubscriptionInfo::GetD_CSIStaticDescription();
        staticDesc._elementVect[10] = VlrCamelSubscriptionInfo::GetMt_sms_CSIStaticDescription();
        staticDesc._elementVect[11] = VlrCamelSubscriptionInfo::GetMt_smsCAMELTDP_CriteriaListStaticDescription();
        staticDesc.SetNamedTypeName("vlrCamelSubscriptionInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





