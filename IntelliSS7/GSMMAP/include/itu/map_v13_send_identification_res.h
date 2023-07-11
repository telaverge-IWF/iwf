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


#if !defined(_MAP_V13_SEND_IDENTIFICATION_RES_H_)
#define _MAP_V13_SEND_IDENTIFICATION_RES_H_

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

#include <map_v13_imsi.h>
#include <map_v13_authentication_set_list.h>
#include <map_v13_current_security_context.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class SendIdentificationRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::IMSI IMSI;


        typedef map_v13::AuthenticationSetList AuthenticationSetList;


        typedef map_v13::CurrentSecurityContext CurrentSecurityContext;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    SendIdentificationRes() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    SendIdentificationRes(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    SendIdentificationRes(const SendIdentificationRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SendIdentificationRes(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetAuthenticationSetListStaticDescription();
    static its::AsnDescObject* GetCurrentSecurityContextStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~SendIdentificationRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SendIdentificationRes(*this);
    }

    virtual std::string GetName() const
    { return "SendIdentificationRes"; }

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    bool OptionImsi() const
    {
        return Contains(0);
    }

    const IMSI& GetImsi() const
    {
        ITS_REQUIRE(OptionImsi());
        return static_cast<const IMSI&> (ElementAt(0));
    }

    void SetAuthenticationSetList(AuthenticationSetList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAuthenticationSetListStaticDescription());
        AddElement(1, element);
    }

    void SetAuthenticationSetList(const AuthenticationSetList& element)
    {
        its::AsnObject& asnObject = const_cast<AuthenticationSetList&>(element);
        asnObject.SetDescription(GetAuthenticationSetListStaticDescription());
        AddElement(1, element);
    }

    bool OptionAuthenticationSetList() const
    {
        return Contains(1);
    }

    const AuthenticationSetList& GetAuthenticationSetList() const
    {
        ITS_REQUIRE(OptionAuthenticationSetList());
        return static_cast<const AuthenticationSetList&> (ElementAt(1));
    }

    void SetCurrentSecurityContext(CurrentSecurityContext* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCurrentSecurityContextStaticDescription());
        AddElement(2, element);
    }

    void SetCurrentSecurityContext(const CurrentSecurityContext& element)
    {
        its::AsnObject& asnObject = const_cast<CurrentSecurityContext&>(element);
        asnObject.SetDescription(GetCurrentSecurityContextStaticDescription());
        AddElement(2, element);
    }

    bool OptionCurrentSecurityContext() const
    {
        return Contains(2);
    }

    const CurrentSecurityContext& GetCurrentSecurityContext() const
    {
        ITS_REQUIRE(OptionCurrentSecurityContext());
        return static_cast<const CurrentSecurityContext&> (ElementAt(2));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(3, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(3, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(3);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SEND_IDENTIFICATION_RES_H_)

