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


#if !defined(_MAP_V13_REMOTE_USER_FREE_RES_H_)
#define _MAP_V13_REMOTE_USER_FREE_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>

#include <map_v13_ruf_outcome.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class RemoteUserFreeRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::RUF_Outcome RUF_Outcome;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    RemoteUserFreeRes() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    RemoteUserFreeRes(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    RemoteUserFreeRes(const RemoteUserFreeRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    RemoteUserFreeRes(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetRuf_OutcomeStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~RemoteUserFreeRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RemoteUserFreeRes(*this);
    }

    virtual std::string GetName() const
    { return "RemoteUserFreeRes"; }

    void SetRuf_Outcome(RUF_Outcome* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRuf_OutcomeStaticDescription());
        AddElement(0, element);
    }

    void SetRuf_Outcome(const RUF_Outcome& element)
    {
        its::AsnObject& asnObject = const_cast<RUF_Outcome&>(element);
        asnObject.SetDescription(GetRuf_OutcomeStaticDescription());
        AddElement(0, element);
    }

    const RUF_Outcome& GetRuf_Outcome() const
    {
        return static_cast<const RUF_Outcome&> (ElementAt(0));
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

#endif    // !defined(_MAP_V13_REMOTE_USER_FREE_RES_H_)

