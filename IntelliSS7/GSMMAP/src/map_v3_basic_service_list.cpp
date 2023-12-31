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


#include <map_v3_basic_service_list.h>

#include <AsnDescSequenceOf.h>
#include <AsnDescChoice.h>


using namespace its;
using namespace map_v3;




////////// Begin Nested Class //////////


// Type Ext_BasicServiceCode is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* BasicServiceList::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new BasicServiceList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 70;
        staticDesc._element = GetExt_BasicServiceCodeStaticDescription();
        staticDesc.SetTypeName("BasicServiceList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* BasicServiceList::GetExt_BasicServiceCodeStaticDescription()
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
        staticDesc.SetCloneForFactory(new Ext_BasicServiceCode(&staticDesc));
        staticDesc._choiceList.push_back(Ext_BasicServiceCode::GetExt_BearerServiceStaticDescription());
        staticDesc._choiceList.push_back(Ext_BasicServiceCode::GetExt_TeleserviceStaticDescription());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





