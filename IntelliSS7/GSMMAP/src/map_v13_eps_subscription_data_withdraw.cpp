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


#include <map_v13_eps_subscription_data_withdraw.h>

#include <AsnDescChoice.h>
#include <AsnDescNull.h>
#include <AsnDescSequenceOf.h>


using namespace its;
using namespace map_v13;




////////// Begin Nested Class(es) //////////



AsnDescObject* EPS_SubscriptionDataWithdraw::AllEPS_Data::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new AllEPS_Data(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 5));
        staticDesc.SetNamedTypeName("allEPS-Data");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


// Type ContextIdList is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* EPS_SubscriptionDataWithdraw::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new EPS_SubscriptionDataWithdraw(&staticDesc));
        staticDesc._choiceList.push_back(GetAllEPS_DataStaticDescription());
        staticDesc._choiceList.push_back(GetContextIdListStaticDescription());
        staticDesc.SetTypeName("EPS-SubscriptionDataWithdraw");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* EPS_SubscriptionDataWithdraw::GetAllEPS_DataStaticDescription()
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
        staticDesc.SetCloneForFactory(new AllEPS_Data(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 5));
        staticDesc.SetNamedTypeName("allEPS-Data");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* EPS_SubscriptionDataWithdraw::GetContextIdListStaticDescription()
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
        staticDesc.SetCloneForFactory(new ContextIdList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 50;
        staticDesc._element = ContextIdList::GetContextIdStaticDescription();
        staticDesc.SetNamedTypeName("contextIdList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





