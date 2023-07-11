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


#if !defined(_MAP_V9_CUG_REJECT_PARAM_H_)
#define _MAP_V9_CUG_REJECT_PARAM_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>

#include <map_v9_cug_reject_cause.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class CUG_RejectParam : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::CUG_RejectCause CUG_RejectCause;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    CUG_RejectParam() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    CUG_RejectParam(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    CUG_RejectParam(const CUG_RejectParam& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    CUG_RejectParam(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetCug_RejectCauseStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~CUG_RejectParam()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CUG_RejectParam(*this);
    }

    virtual std::string GetName() const
    { return "CUG_RejectParam"; }

    void SetCug_RejectCause(CUG_RejectCause* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCug_RejectCauseStaticDescription());
        AddElement(0, element);
    }

    void SetCug_RejectCause(const CUG_RejectCause& element)
    {
        its::AsnObject& asnObject = const_cast<CUG_RejectCause&>(element);
        asnObject.SetDescription(GetCug_RejectCauseStaticDescription());
        AddElement(0, element);
    }

    bool OptionCug_RejectCause() const
    {
        return Contains(0);
    }

    const CUG_RejectCause& GetCug_RejectCause() const
    {
        ITS_REQUIRE(OptionCug_RejectCause());
        return static_cast<const CUG_RejectCause&> (ElementAt(0));
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

#endif    // !defined(_MAP_V9_CUG_REJECT_PARAM_H_)

