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


#if !defined(_MAP_V13_NAEA_PREFERRED_CI_H_)
#define _MAP_V13_NAEA_PREFERRED_CI_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v13_naea_cic.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class NAEA_PreferredCI : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::NAEA_CIC NAEA_CIC;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    NAEA_PreferredCI() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    NAEA_PreferredCI(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    NAEA_PreferredCI(const NAEA_PreferredCI& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    NAEA_PreferredCI(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetNaea_PreferredCICStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~NAEA_PreferredCI()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new NAEA_PreferredCI(*this);
    }

    virtual std::string GetName() const
    { return "NAEA_PreferredCI"; }

    void SetNaea_PreferredCIC(NAEA_CIC* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNaea_PreferredCICStaticDescription());
        AddElement(0, element);
    }

    void SetNaea_PreferredCIC(const NAEA_CIC& element)
    {
        its::AsnObject& asnObject = const_cast<NAEA_CIC&>(element);
        asnObject.SetDescription(GetNaea_PreferredCICStaticDescription());
        AddElement(0, element);
    }

    const NAEA_CIC& GetNaea_PreferredCIC() const
    {
        return static_cast<const NAEA_CIC&> (ElementAt(0));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(1, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(1, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(1);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_NAEA_PREFERRED_CI_H_)

