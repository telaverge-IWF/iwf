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


#if !defined(_MAP_V9_UNAUTHORIZED_LCS_CLIENT_PARAM_H_)
#define _MAP_V9_UNAUTHORIZED_LCS_CLIENT_PARAM_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>

#include <map_v9_unauthorized_lcs_client_diagnostic.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class UnauthorizedLCSClient_Param : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::UnauthorizedLCSClient_Diagnostic UnauthorizedLCSClient_Diagnostic;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    UnauthorizedLCSClient_Param() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    UnauthorizedLCSClient_Param(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    UnauthorizedLCSClient_Param(const UnauthorizedLCSClient_Param& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    UnauthorizedLCSClient_Param(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetUnauthorizedLCSClient_DiagnosticStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~UnauthorizedLCSClient_Param()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new UnauthorizedLCSClient_Param(*this);
    }

    virtual std::string GetName() const
    { return "UnauthorizedLCSClient_Param"; }

    void SetUnauthorizedLCSClient_Diagnostic(UnauthorizedLCSClient_Diagnostic* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetUnauthorizedLCSClient_DiagnosticStaticDescription());
        AddElement(0, element);
    }

    void SetUnauthorizedLCSClient_Diagnostic(const UnauthorizedLCSClient_Diagnostic& element)
    {
        its::AsnObject& asnObject = const_cast<UnauthorizedLCSClient_Diagnostic&>(element);
        asnObject.SetDescription(GetUnauthorizedLCSClient_DiagnosticStaticDescription());
        AddElement(0, element);
    }

    bool OptionUnauthorizedLCSClient_Diagnostic() const
    {
        return Contains(0);
    }

    const UnauthorizedLCSClient_Diagnostic& GetUnauthorizedLCSClient_Diagnostic() const
    {
        ITS_REQUIRE(OptionUnauthorizedLCSClient_Diagnostic());
        return static_cast<const UnauthorizedLCSClient_Diagnostic&> (ElementAt(0));
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

#endif    // !defined(_MAP_V9_UNAUTHORIZED_LCS_CLIENT_PARAM_H_)

