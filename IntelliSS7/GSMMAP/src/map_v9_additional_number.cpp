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


#include <map_v9_additional_number.h>

#include <AsnDescChoice.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace map_v9;




////////// Begin Nested Class(es) //////////


// Type ISDN_AddressString is a reference => no code generated.

// Type ISDN_AddressString is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* Additional_Number::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new Additional_Number(&staticDesc));
        staticDesc._choiceList.push_back(GetMsc_NumberStaticDescription());
        staticDesc._choiceList.push_back(GetSgsn_NumberStaticDescription());
        staticDesc.SetTypeName("Additional-Number");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* Additional_Number::GetMsc_NumberStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 20;
        staticDesc.SetNamedTypeName("msc-Number");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* Additional_Number::GetSgsn_NumberStaticDescription()
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
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 20;
        staticDesc.SetNamedTypeName("sgsn-Number");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





