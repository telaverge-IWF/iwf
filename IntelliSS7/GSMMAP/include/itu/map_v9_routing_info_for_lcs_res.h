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


#if !defined(_MAP_V9_ROUTING_INFO_FOR_LCS_RES_H_)
#define _MAP_V9_ROUTING_INFO_FOR_LCS_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnChoice.h>
#include <AsnOctetString.h>

#include <map_v9_subscriber_identity.h>
#include <map_v9_lcs_location_info.h>
#include <map_v9_extension_container.h>
#include <map_v9_gsn_address.h>



namespace map_v9 {



class RoutingInfoForLCS_Res : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::SubscriberIdentity SubscriberIdentity;


        typedef map_v9::LCSLocationInfo LCSLocationInfo;


        typedef map_v9::ExtensionContainer ExtensionContainer;


        typedef map_v9::GSN_Address GSN_Address;


////////// End Nested Class(es) //////////

    RoutingInfoForLCS_Res() : its::AsnSequence(7, false)
    {
        Initialize();
    }

    RoutingInfoForLCS_Res(its::Octets& octets) : its::AsnSequence(7, false)
    {
        Initialize();
        Decode(octets);
    }

    RoutingInfoForLCS_Res(const RoutingInfoForLCS_Res& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    RoutingInfoForLCS_Res(its::AsnDescObject* description) : its::AsnSequence(7, description)
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

    static its::AsnDescObject* GetTargetMSStaticDescription();
    static its::AsnDescObject* GetLcsLocationInfoStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetV_gmlc_AddressStaticDescription();
    static its::AsnDescObject* GetH_gmlc_AddressStaticDescription();
    static its::AsnDescObject* GetPpr_AddressStaticDescription();
    static its::AsnDescObject* GetAdditional_v_gmlc_AddressStaticDescription();

public:

    virtual ~RoutingInfoForLCS_Res()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RoutingInfoForLCS_Res(*this);
    }

    virtual std::string GetName() const
    { return "RoutingInfoForLCS_Res"; }

    void SetTargetMS(SubscriberIdentity* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTargetMSStaticDescription());
        AddElement(0, element);
    }

    void SetTargetMS(const SubscriberIdentity& element)
    {
        its::AsnObject& asnObject = const_cast<SubscriberIdentity&>(element);
        asnObject.SetDescription(GetTargetMSStaticDescription());
        AddElement(0, element);
    }

    const SubscriberIdentity& GetTargetMS() const
    {
        return static_cast<const SubscriberIdentity&> (ElementAt(0));
    }

    void SetLcsLocationInfo(LCSLocationInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLcsLocationInfoStaticDescription());
        AddElement(1, element);
    }

    void SetLcsLocationInfo(const LCSLocationInfo& element)
    {
        its::AsnObject& asnObject = const_cast<LCSLocationInfo&>(element);
        asnObject.SetDescription(GetLcsLocationInfoStaticDescription());
        AddElement(1, element);
    }

    const LCSLocationInfo& GetLcsLocationInfo() const
    {
        return static_cast<const LCSLocationInfo&> (ElementAt(1));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(2);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(2));
    }

    void SetV_gmlc_Address(GSN_Address* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetV_gmlc_AddressStaticDescription());
        AddElement(3, element);
    }

    void SetV_gmlc_Address(const GSN_Address& element)
    {
        its::AsnObject& asnObject = const_cast<GSN_Address&>(element);
        asnObject.SetDescription(GetV_gmlc_AddressStaticDescription());
        AddElement(3, element);
    }

    bool OptionV_gmlc_Address() const
    {
        return Contains(3);
    }

    const GSN_Address& GetV_gmlc_Address() const
    {
        ITS_REQUIRE(OptionV_gmlc_Address());
        return static_cast<const GSN_Address&> (ElementAt(3));
    }

    void SetH_gmlc_Address(GSN_Address* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetH_gmlc_AddressStaticDescription());
        AddElement(4, element);
    }

    void SetH_gmlc_Address(const GSN_Address& element)
    {
        its::AsnObject& asnObject = const_cast<GSN_Address&>(element);
        asnObject.SetDescription(GetH_gmlc_AddressStaticDescription());
        AddElement(4, element);
    }

    bool OptionH_gmlc_Address() const
    {
        return Contains(4);
    }

    const GSN_Address& GetH_gmlc_Address() const
    {
        ITS_REQUIRE(OptionH_gmlc_Address());
        return static_cast<const GSN_Address&> (ElementAt(4));
    }

    void SetPpr_Address(GSN_Address* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPpr_AddressStaticDescription());
        AddElement(5, element);
    }

    void SetPpr_Address(const GSN_Address& element)
    {
        its::AsnObject& asnObject = const_cast<GSN_Address&>(element);
        asnObject.SetDescription(GetPpr_AddressStaticDescription());
        AddElement(5, element);
    }

    bool OptionPpr_Address() const
    {
        return Contains(5);
    }

    const GSN_Address& GetPpr_Address() const
    {
        ITS_REQUIRE(OptionPpr_Address());
        return static_cast<const GSN_Address&> (ElementAt(5));
    }

    void SetAdditional_v_gmlc_Address(GSN_Address* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAdditional_v_gmlc_AddressStaticDescription());
        AddElement(6, element);
    }

    void SetAdditional_v_gmlc_Address(const GSN_Address& element)
    {
        its::AsnObject& asnObject = const_cast<GSN_Address&>(element);
        asnObject.SetDescription(GetAdditional_v_gmlc_AddressStaticDescription());
        AddElement(6, element);
    }

    bool OptionAdditional_v_gmlc_Address() const
    {
        return Contains(6);
    }

    const GSN_Address& GetAdditional_v_gmlc_Address() const
    {
        ITS_REQUIRE(OptionAdditional_v_gmlc_Address());
        return static_cast<const GSN_Address&> (ElementAt(6));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_ROUTING_INFO_FOR_LCS_RES_H_)

