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


#if !defined(_MAP_V9_SEND_ROUTING_INFO_FOR_GPRS_RES_H_)
#define _MAP_V9_SEND_ROUTING_INFO_FOR_GPRS_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnInteger.h>

#include <map_v9_gsn_address.h>
#include <map_v9_absent_subscriber_diagnostic_sm.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class SendRoutingInfoForGprsRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::GSN_Address GSN_Address;


        typedef map_v9::AbsentSubscriberDiagnosticSM AbsentSubscriberDiagnosticSM;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    SendRoutingInfoForGprsRes() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    SendRoutingInfoForGprsRes(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    SendRoutingInfoForGprsRes(const SendRoutingInfoForGprsRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SendRoutingInfoForGprsRes(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetSgsn_AddressStaticDescription();
    static its::AsnDescObject* GetGgsn_AddressStaticDescription();
    static its::AsnDescObject* GetMobileNotReachableReasonStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~SendRoutingInfoForGprsRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SendRoutingInfoForGprsRes(*this);
    }

    virtual std::string GetName() const
    { return "SendRoutingInfoForGprsRes"; }

    void SetSgsn_Address(GSN_Address* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSgsn_AddressStaticDescription());
        AddElement(0, element);
    }

    void SetSgsn_Address(const GSN_Address& element)
    {
        its::AsnObject& asnObject = const_cast<GSN_Address&>(element);
        asnObject.SetDescription(GetSgsn_AddressStaticDescription());
        AddElement(0, element);
    }

    const GSN_Address& GetSgsn_Address() const
    {
        return static_cast<const GSN_Address&> (ElementAt(0));
    }

    void SetGgsn_Address(GSN_Address* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGgsn_AddressStaticDescription());
        AddElement(1, element);
    }

    void SetGgsn_Address(const GSN_Address& element)
    {
        its::AsnObject& asnObject = const_cast<GSN_Address&>(element);
        asnObject.SetDescription(GetGgsn_AddressStaticDescription());
        AddElement(1, element);
    }

    bool OptionGgsn_Address() const
    {
        return Contains(1);
    }

    const GSN_Address& GetGgsn_Address() const
    {
        ITS_REQUIRE(OptionGgsn_Address());
        return static_cast<const GSN_Address&> (ElementAt(1));
    }

    void SetMobileNotReachableReason(AbsentSubscriberDiagnosticSM* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMobileNotReachableReasonStaticDescription());
        AddElement(2, element);
    }

    void SetMobileNotReachableReason(const AbsentSubscriberDiagnosticSM& element)
    {
        its::AsnObject& asnObject = const_cast<AbsentSubscriberDiagnosticSM&>(element);
        asnObject.SetDescription(GetMobileNotReachableReasonStaticDescription());
        AddElement(2, element);
    }

    bool OptionMobileNotReachableReason() const
    {
        return Contains(2);
    }

    const AbsentSubscriberDiagnosticSM& GetMobileNotReachableReason() const
    {
        ITS_REQUIRE(OptionMobileNotReachableReason());
        return static_cast<const AbsentSubscriberDiagnosticSM&> (ElementAt(2));
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

#endif    // !defined(_MAP_V9_SEND_ROUTING_INFO_FOR_GPRS_RES_H_)

