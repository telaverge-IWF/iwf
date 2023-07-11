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


#if !defined(_INAP_CS2_DIRECTORY_BIND_ARGUMENT_H_)
#define _INAP_CS2_DIRECTORY_BIND_ARGUMENT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSet.h>
#include <AsnChoice.h>
#include <AsnBitString.h>

#include <inap_cs2_credentials.h>
#include <inap_cs2_versions.h>



namespace inap_cs2 {



class DirectoryBindArgument : public its::AsnSet
{
public:


////////// Begin Nested Class(es) //////////


        typedef inap_cs2::Credentials Credentials;


        typedef inap_cs2::Versions Versions;


////////// End Nested Class(es) //////////

    DirectoryBindArgument() : its::AsnSet(2, false)
    {
        Initialize();
    }

    DirectoryBindArgument(its::Octets& octets) : its::AsnSet(2, false)
    {
        Initialize();
        Decode(octets);
    }

    DirectoryBindArgument(const DirectoryBindArgument& rhs) : its::AsnSet(rhs)
    {
        // Nothing to do.
    }

    DirectoryBindArgument(its::AsnDescObject* description) : its::AsnSet(2, description)
    {
        // Nothing to do.
    }

protected:

    void Initialize()
    {
        _description = GetStaticDescription();
    }

public:

    static its::AsnDescObject* GetStaticDescription();

    static its::AsnDescObject* GetCredentialsStaticDescription();
    static its::AsnDescObject* GetVersionsStaticDescription();

public:

    virtual ~DirectoryBindArgument()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new DirectoryBindArgument(*this);
    }

    virtual std::string GetName() const
    { return "DirectoryBindArgument"; }

    void SetCredentials(Credentials* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCredentialsStaticDescription());
        AddElement(0, element);
    }

    void SetCredentials(const Credentials& element)
    {
        its::AsnObject& asnObject = const_cast<Credentials&>(element);
        asnObject.SetDescription(GetCredentialsStaticDescription());
        AddElement(0, element);
}

    bool OptionCredentials() const
    {
        return Contains(0);
    }

    const Credentials& GetCredentials() const
    {
        ITS_REQUIRE(OptionCredentials());
        return static_cast<const Credentials&> (ElementAt(0));
    }

    void SetVersions(Versions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVersionsStaticDescription());
        AddElement(1, element);
    }

    void SetVersions(const Versions& element)
    {
        its::AsnObject& asnObject = const_cast<Versions&>(element);
        asnObject.SetDescription(GetVersionsStaticDescription());
        AddElement(1, element);
}

    bool OptionVersions() const
    {
        return Contains(1);
    }

    const Versions& GetVersions() const
    {
        ITS_REQUIRE(OptionVersions());
        return static_cast<const Versions&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_DIRECTORY_BIND_ARGUMENT_H_)

