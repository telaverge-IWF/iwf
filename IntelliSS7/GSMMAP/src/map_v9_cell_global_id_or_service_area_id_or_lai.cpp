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


#include <map_v9_cell_global_id_or_service_area_id_or_lai.h>

#include <AsnDescChoice.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace map_v9;




////////// Begin Nested Class(es) //////////


// Type CellGlobalIdOrServiceAreaIdFixedLength is a reference => no code generated.

// Type LAIFixedLength is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* CellGlobalIdOrServiceAreaIdOrLAI::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new CellGlobalIdOrServiceAreaIdOrLAI(&staticDesc));
        staticDesc._choiceList.push_back(GetCellGlobalIdOrServiceAreaIdFixedLengthStaticDescription());
        staticDesc._choiceList.push_back(GetLaiFixedLengthStaticDescription());
        staticDesc.SetTypeName("CellGlobalIdOrServiceAreaIdOrLAI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CellGlobalIdOrServiceAreaIdOrLAI::GetCellGlobalIdOrServiceAreaIdFixedLengthStaticDescription()
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
        staticDesc.SetCloneForFactory(new CellGlobalIdOrServiceAreaIdFixedLength(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 7;
        staticDesc._maxSize = 7;
        staticDesc.SetNamedTypeName("cellGlobalIdOrServiceAreaIdFixedLength");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* CellGlobalIdOrServiceAreaIdOrLAI::GetLaiFixedLengthStaticDescription()
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
        staticDesc.SetCloneForFactory(new LAIFixedLength(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 5;
        staticDesc._maxSize = 5;
        staticDesc.SetNamedTypeName("laiFixedLength");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





