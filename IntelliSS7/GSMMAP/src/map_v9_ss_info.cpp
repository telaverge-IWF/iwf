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


#include <map_v9_ss_info.h>

#include <AsnDescChoice.h>
#include <AsnDescSequence.h>


using namespace its;
using namespace map_v9;




////////// Begin Nested Class(es) //////////


// Type ForwardingInfo is a reference => no code generated.

// Type CallBarringInfo is a reference => no code generated.

// Type SS_Data is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* SS_Info::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new SS_Info(&staticDesc));
        staticDesc._choiceList.push_back(GetForwardingInfoStaticDescription());
        staticDesc._choiceList.push_back(GetCallBarringInfoStaticDescription());
        staticDesc._choiceList.push_back(GetSs_DataStaticDescription());
        staticDesc.SetTypeName("SS-Info");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SS_Info::GetForwardingInfoStaticDescription()
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
        staticDesc.SetCloneForFactory(new ForwardingInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ForwardingInfo::GetSs_CodeStaticDescription();
        staticDesc._elementVect[1] = ForwardingInfo::GetForwardingFeatureListStaticDescription();
        staticDesc.SetNamedTypeName("forwardingInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SS_Info::GetCallBarringInfoStaticDescription()
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
        staticDesc.SetCloneForFactory(new CallBarringInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = CallBarringInfo::GetSs_CodeStaticDescription();
        staticDesc._elementVect[1] = CallBarringInfo::GetCallBarringFeatureListStaticDescription();
        staticDesc.SetNamedTypeName("callBarringInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SS_Info::GetSs_DataStaticDescription()
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
        staticDesc.SetCloneForFactory(new SS_Data(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 3));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = SS_Data::GetSs_CodeStaticDescription();
        staticDesc._elementVect[1] = SS_Data::GetSs_StatusStaticDescription();
        staticDesc._elementVect[2] = SS_Data::GetSs_SubscriptionOptionStaticDescription();
        staticDesc._elementVect[3] = SS_Data::GetBasicServiceGroupListStaticDescription();
        staticDesc._elementVect[4] = SS_Data::GetDefaultPriorityStaticDescription();
        staticDesc._elementVect[5] = SS_Data::GetNbrUserStaticDescription();
        staticDesc.SetNamedTypeName("ss-Data");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





