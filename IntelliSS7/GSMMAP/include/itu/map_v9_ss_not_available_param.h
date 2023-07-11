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


#if !defined(_MAP_V9_SS_NOT_AVAILABLE_PARAM_H_)
#define _MAP_V9_SS_NOT_AVAILABLE_PARAM_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>

#include <map_v9_extension_container.h>



namespace map_v9 {



class SS_NotAvailableParam : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    SS_NotAvailableParam() : its::AsnSequence(1, false)
    {
        Initialize();
    }

    SS_NotAvailableParam(its::Octets& octets) : its::AsnSequence(1, false)
    {
        Initialize();
        Decode(octets);
    }

    SS_NotAvailableParam(const SS_NotAvailableParam& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SS_NotAvailableParam(its::AsnDescObject* description) : its::AsnSequence(1, description)
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

    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~SS_NotAvailableParam()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SS_NotAvailableParam(*this);
    }

    virtual std::string GetName() const
    { return "SS_NotAvailableParam"; }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(0, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(0, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(0);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(0));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_SS_NOT_AVAILABLE_PARAM_H_)

