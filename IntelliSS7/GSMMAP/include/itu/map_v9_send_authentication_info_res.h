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


#if !defined(_MAP_V9_SEND_AUTHENTICATION_INFO_RES_H_)
#define _MAP_V9_SEND_AUTHENTICATION_INFO_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnChoice.h>

#include <map_v9_authentication_set_list.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class SendAuthenticationInfoRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::AuthenticationSetList AuthenticationSetList;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    SendAuthenticationInfoRes() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    SendAuthenticationInfoRes(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    SendAuthenticationInfoRes(const SendAuthenticationInfoRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SendAuthenticationInfoRes(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetAuthenticationSetListStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~SendAuthenticationInfoRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SendAuthenticationInfoRes(*this);
    }

    virtual std::string GetName() const
    { return "SendAuthenticationInfoRes"; }

    void SetAuthenticationSetList(AuthenticationSetList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAuthenticationSetListStaticDescription());
        AddElement(0, element);
    }

    void SetAuthenticationSetList(const AuthenticationSetList& element)
    {
        its::AsnObject& asnObject = const_cast<AuthenticationSetList&>(element);
        asnObject.SetDescription(GetAuthenticationSetListStaticDescription());
        AddElement(0, element);
    }

    bool OptionAuthenticationSetList() const
    {
        return Contains(0);
    }

    const AuthenticationSetList& GetAuthenticationSetList() const
    {
        ITS_REQUIRE(OptionAuthenticationSetList());
        return static_cast<const AuthenticationSetList&> (ElementAt(0));
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

#endif    // !defined(_MAP_V9_SEND_AUTHENTICATION_INFO_RES_H_)

