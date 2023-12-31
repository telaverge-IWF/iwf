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


#include <cap_v2_sending_side_id.h>

#include <AsnDescChoice.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace cap_v2;




////////// Begin Nested Class(es) //////////


// Type LegType is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* SendingSideID::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new SendingSideID(&staticDesc));
        staticDesc._choiceList.push_back(GetSendingSideIDStaticDescription());
        staticDesc.SetTypeName("SendingSideID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SendingSideID::GetSendingSideIDStaticDescription()
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
        staticDesc.SetCloneForFactory(new LegType(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 1;
        staticDesc.SetNamedTypeName("sendingSideID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





