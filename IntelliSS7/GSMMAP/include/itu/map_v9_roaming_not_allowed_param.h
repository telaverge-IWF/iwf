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


#if !defined(_MAP_V9_ROAMING_NOT_ALLOWED_PARAM_H_)
#define _MAP_V9_ROAMING_NOT_ALLOWED_PARAM_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>

#include <map_v9_roaming_not_allowed_cause.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class RoamingNotAllowedParam : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::RoamingNotAllowedCause RoamingNotAllowedCause;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    RoamingNotAllowedParam() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    RoamingNotAllowedParam(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    RoamingNotAllowedParam(const RoamingNotAllowedParam& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    RoamingNotAllowedParam(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetRoamingNotAllowedCauseStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~RoamingNotAllowedParam()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RoamingNotAllowedParam(*this);
    }

    virtual std::string GetName() const
    { return "RoamingNotAllowedParam"; }

    void SetRoamingNotAllowedCause(RoamingNotAllowedCause* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRoamingNotAllowedCauseStaticDescription());
        AddElement(0, element);
    }

    void SetRoamingNotAllowedCause(const RoamingNotAllowedCause& element)
    {
        its::AsnObject& asnObject = const_cast<RoamingNotAllowedCause&>(element);
        asnObject.SetDescription(GetRoamingNotAllowedCauseStaticDescription());
        AddElement(0, element);
    }

    const RoamingNotAllowedCause& GetRoamingNotAllowedCause() const
    {
        return static_cast<const RoamingNotAllowedCause&> (ElementAt(0));
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

#endif    // !defined(_MAP_V9_ROAMING_NOT_ALLOWED_PARAM_H_)

