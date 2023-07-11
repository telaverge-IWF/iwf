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


#include <map_v13_bssmap_service_handover_info.h>

#include <AsnDescSequence.h>
#include <AsnDescOctetString.h>
#include <AsnDescInteger.h>


using namespace its;
using namespace map_v13;




////////// Begin Nested Class(es) //////////


// Type BSSMAP_ServiceHandover is a reference => no code generated.

// Type RAB_Id is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* BSSMAP_ServiceHandoverInfo::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new BSSMAP_ServiceHandoverInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetBssmap_ServiceHandoverStaticDescription();
        staticDesc._elementVect[1] = GetRab_IdStaticDescription();
        staticDesc.SetTypeName("BSSMAP-ServiceHandoverInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* BSSMAP_ServiceHandoverInfo::GetBssmap_ServiceHandoverStaticDescription()
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
        staticDesc.SetCloneForFactory(new BSSMAP_ServiceHandover(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 4));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 1;
        staticDesc.SetNamedTypeName("bssmap-ServiceHandover");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* BSSMAP_ServiceHandoverInfo::GetRab_IdStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescInteger staticDesc;

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
        staticDesc.SetCloneForFactory(new RAB_Id(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 2));
        staticDesc.SetNamedTypeName("rab-Id");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




