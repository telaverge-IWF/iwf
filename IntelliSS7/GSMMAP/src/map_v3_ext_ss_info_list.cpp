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


#include <map_v3_ext_ss_info_list.h>

#include <AsnDescSequenceOf.h>
#include <AsnDescChoice.h>


using namespace its;
using namespace map_v3;




////////// Begin Nested Class //////////


// Type Ext_SS_Info is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* Ext_SS_InfoList::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new Ext_SS_InfoList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 30;
        staticDesc._element = GetExt_SS_InfoStaticDescription();
        staticDesc.SetTypeName("Ext-SS-InfoList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* Ext_SS_InfoList::GetExt_SS_InfoStaticDescription()
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
        staticDesc.SetCloneForFactory(new Ext_SS_Info(&staticDesc));
        staticDesc._choiceList.push_back(Ext_SS_Info::GetForwardingInfoStaticDescription());
        staticDesc._choiceList.push_back(Ext_SS_Info::GetCallBarringInfoStaticDescription());
        staticDesc._choiceList.push_back(Ext_SS_Info::GetCug_InfoStaticDescription());
        staticDesc._choiceList.push_back(Ext_SS_Info::GetSs_DataStaticDescription());
        staticDesc._choiceList.push_back(Ext_SS_Info::GetEmlpp_InfoStaticDescription());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





