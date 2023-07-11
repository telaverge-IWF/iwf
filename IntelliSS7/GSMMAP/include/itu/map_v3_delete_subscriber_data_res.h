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


#if !defined(_MAP_V3_DELETE_SUBSCRIBER_DATA_RES_H_)
#define _MAP_V3_DELETE_SUBSCRIBER_DATA_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>

#include <map_v3_regional_subscription_response.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class DeleteSubscriberDataRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::RegionalSubscriptionResponse RegionalSubscriptionResponse;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    DeleteSubscriberDataRes() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    DeleteSubscriberDataRes(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    DeleteSubscriberDataRes(const DeleteSubscriberDataRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    DeleteSubscriberDataRes(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetRegionalSubscriptionResponseStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~DeleteSubscriberDataRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new DeleteSubscriberDataRes(*this);
    }

    virtual std::string GetName() const
    { return "DeleteSubscriberDataRes"; }

    void SetRegionalSubscriptionResponse(RegionalSubscriptionResponse* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRegionalSubscriptionResponseStaticDescription());
        AddElement(0, element);
    }

    void SetRegionalSubscriptionResponse(const RegionalSubscriptionResponse& element)
    {
        its::AsnObject& asnObject = const_cast<RegionalSubscriptionResponse&>(element);
        asnObject.SetDescription(GetRegionalSubscriptionResponseStaticDescription());
        AddElement(0, element);
    }

    bool OptionRegionalSubscriptionResponse() const
    {
        return Contains(0);
    }

    const RegionalSubscriptionResponse& GetRegionalSubscriptionResponse() const
    {
        ITS_REQUIRE(OptionRegionalSubscriptionResponse());
        return static_cast<const RegionalSubscriptionResponse&> (ElementAt(0));
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

#endif    // !defined(_MAP_V3_DELETE_SUBSCRIBER_DATA_RES_H_)
