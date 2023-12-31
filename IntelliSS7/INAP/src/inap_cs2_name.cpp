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


#include <inap_cs2_name.h>

#include <AsnDescChoice.h>
#include <AsnDescSequenceOf.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type RDNSequence is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* Name::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_INAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new Name(&staticDesc));
        staticDesc._choiceList.push_back(GetRdnSequenceStaticDescription());
        staticDesc.SetTypeName("Name");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* Name::GetRdnSequenceStaticDescription()
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
        staticDesc.SetCloneForFactory(new RDNSequence(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._element = RDNSequence::GetRelativeDistinguishedNameStaticDescription();
        staticDesc.SetNamedTypeName("rdnSequence");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





