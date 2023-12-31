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


#include <map_v3_ext_call_bar_feature_list.h>

#include <AsnDescSequenceOf.h>
#include <AsnDescSequence.h>


using namespace its;
using namespace map_v3;




////////// Begin Nested Class //////////


// Type Ext_CallBarringFeature is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* Ext_CallBarFeatureList::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new Ext_CallBarFeatureList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 32;
        staticDesc._element = GetExt_CallBarringFeatureStaticDescription();
        staticDesc.SetTypeName("Ext-CallBarFeatureList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* Ext_CallBarFeatureList::GetExt_CallBarringFeatureStaticDescription()
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
        staticDesc.SetCloneForFactory(new Ext_CallBarringFeature(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = Ext_CallBarringFeature::GetBasicServiceStaticDescription();
        staticDesc._elementVect[1] = Ext_CallBarringFeature::GetSs_StatusStaticDescription();
        staticDesc._elementVect[2] = Ext_CallBarringFeature::GetExtensionContainerStaticDescription();
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





