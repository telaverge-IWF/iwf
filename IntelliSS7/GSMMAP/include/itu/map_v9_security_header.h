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


#if !defined(_MAP_V9_SECURITY_HEADER_H_)
#define _MAP_V9_SECURITY_HEADER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnChoice.h>

#include <map_v9_security_parameters_index.h>
#include <map_v9_original_component_identifier.h>
#include <map_v9_initialisation_vector.h>



namespace map_v9 {



class SecurityHeader : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::SecurityParametersIndex SecurityParametersIndex;


        typedef map_v9::OriginalComponentIdentifier OriginalComponentIdentifier;


        typedef map_v9::InitialisationVector InitialisationVector;


////////// End Nested Class(es) //////////

    SecurityHeader() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    SecurityHeader(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    SecurityHeader(const SecurityHeader& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SecurityHeader(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetSecurityParametersIndexStaticDescription();
    static its::AsnDescObject* GetOriginalComponentIdentifierStaticDescription();
    static its::AsnDescObject* GetInitialisationVectorStaticDescription();

public:

    virtual ~SecurityHeader()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SecurityHeader(*this);
    }

    virtual std::string GetName() const
    { return "SecurityHeader"; }

    void SetSecurityParametersIndex(SecurityParametersIndex* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSecurityParametersIndexStaticDescription());
        AddElement(0, element);
    }

    void SetSecurityParametersIndex(const SecurityParametersIndex& element)
    {
        its::AsnObject& asnObject = const_cast<SecurityParametersIndex&>(element);
        asnObject.SetDescription(GetSecurityParametersIndexStaticDescription());
        AddElement(0, element);
    }

    const SecurityParametersIndex& GetSecurityParametersIndex() const
    {
        return static_cast<const SecurityParametersIndex&> (ElementAt(0));
    }

    void SetOriginalComponentIdentifier(OriginalComponentIdentifier* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOriginalComponentIdentifierStaticDescription());
        AddElement(1, element);
    }

    void SetOriginalComponentIdentifier(const OriginalComponentIdentifier& element)
    {
        its::AsnObject& asnObject = const_cast<OriginalComponentIdentifier&>(element);
        asnObject.SetDescription(GetOriginalComponentIdentifierStaticDescription());
        AddElement(1, element);
    }

    const OriginalComponentIdentifier& GetOriginalComponentIdentifier() const
    {
        return static_cast<const OriginalComponentIdentifier&> (ElementAt(1));
    }

    void SetInitialisationVector(InitialisationVector* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetInitialisationVectorStaticDescription());
        AddElement(2, element);
    }

    void SetInitialisationVector(const InitialisationVector& element)
    {
        its::AsnObject& asnObject = const_cast<InitialisationVector&>(element);
        asnObject.SetDescription(GetInitialisationVectorStaticDescription());
        AddElement(2, element);
    }

    bool OptionInitialisationVector() const
    {
        return Contains(2);
    }

    const InitialisationVector& GetInitialisationVector() const
    {
        ITS_REQUIRE(OptionInitialisationVector());
        return static_cast<const InitialisationVector&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_SECURITY_HEADER_H_)
