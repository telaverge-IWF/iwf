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


#include <inap_cs2_strong_credentials.h>

#include <AsnDescSet.h>
#include <AsnDescSequence.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type CertificationPath is a reference => no code generated.

// Type Token is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* StrongCredentials::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSet staticDesc(2);

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

        staticDesc.SetCloneForFactory(new StrongCredentials(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 17));
        staticDesc._elementVect[0] = GetCertification_pathStaticDescription();
        staticDesc._elementVect[1] = GetBind_tokenStaticDescription();
        staticDesc.SetTypeName("StrongCredentials");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* StrongCredentials::GetCertification_pathStaticDescription()
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
        staticDesc.SetCloneForFactory(new CertificationPath(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._clauseOptional = true;
        staticDesc._elementVect[0] = CertificationPath::GetUserCertificateStaticDescription();
        staticDesc._elementVect[1] = CertificationPath::GetTheCACertificatesStaticDescription();
        staticDesc.SetNamedTypeName("certification-path");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* StrongCredentials::GetBind_tokenStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(4);

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
        staticDesc.SetCloneForFactory(new Token(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._elementVect[0] = Token::GetAlgorithmStaticDescription();
        staticDesc._elementVect[1] = Token::GetDistinguishedNameStaticDescription();
        staticDesc._elementVect[2] = Token::GetTimeStaticDescription();
        staticDesc._elementVect[3] = Token::GetRandomStaticDescription();
        staticDesc.SetNamedTypeName("bind-token");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





