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


#if !defined(_MAP_V9_MNP_INFO_RES_H_)
#define _MAP_V9_MNP_INFO_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnEnumerated.h>

#include <map_v9_routeing_number.h>
#include <map_v9_imsi.h>
#include <map_v9_isdn_address_string.h>
#include <map_v9_number_portability_status.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class MNPInfoRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::RouteingNumber RouteingNumber;


        typedef map_v9::IMSI IMSI;


        typedef map_v9::ISDN_AddressString ISDN_AddressString;


        typedef map_v9::NumberPortabilityStatus NumberPortabilityStatus;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    MNPInfoRes() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    MNPInfoRes(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    MNPInfoRes(const MNPInfoRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    MNPInfoRes(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

    static its::AsnDescObject* GetRouteingNumberStaticDescription();
    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetMsisdnStaticDescription();
    static its::AsnDescObject* GetNumberPortabilityStatusStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~MNPInfoRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MNPInfoRes(*this);
    }

    virtual std::string GetName() const
    { return "MNPInfoRes"; }

    void SetRouteingNumber(RouteingNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRouteingNumberStaticDescription());
        AddElement(0, element);
    }

    void SetRouteingNumber(const RouteingNumber& element)
    {
        its::AsnObject& asnObject = const_cast<RouteingNumber&>(element);
        asnObject.SetDescription(GetRouteingNumberStaticDescription());
        AddElement(0, element);
    }

    bool OptionRouteingNumber() const
    {
        return Contains(0);
    }

    const RouteingNumber& GetRouteingNumber() const
    {
        ITS_REQUIRE(OptionRouteingNumber());
        return static_cast<const RouteingNumber&> (ElementAt(0));
    }

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(1, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(1, element);
    }

    bool OptionImsi() const
    {
        return Contains(1);
    }

    const IMSI& GetImsi() const
    {
        ITS_REQUIRE(OptionImsi());
        return static_cast<const IMSI&> (ElementAt(1));
    }

    void SetMsisdn(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsisdnStaticDescription());
        AddElement(2, element);
    }

    void SetMsisdn(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMsisdnStaticDescription());
        AddElement(2, element);
    }

    bool OptionMsisdn() const
    {
        return Contains(2);
    }

    const ISDN_AddressString& GetMsisdn() const
    {
        ITS_REQUIRE(OptionMsisdn());
        return static_cast<const ISDN_AddressString&> (ElementAt(2));
    }

    void SetNumberPortabilityStatus(NumberPortabilityStatus* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNumberPortabilityStatusStaticDescription());
        AddElement(3, element);
    }

    void SetNumberPortabilityStatus(const NumberPortabilityStatus& element)
    {
        its::AsnObject& asnObject = const_cast<NumberPortabilityStatus&>(element);
        asnObject.SetDescription(GetNumberPortabilityStatusStaticDescription());
        AddElement(3, element);
    }

    bool OptionNumberPortabilityStatus() const
    {
        return Contains(3);
    }

    const NumberPortabilityStatus& GetNumberPortabilityStatus() const
    {
        ITS_REQUIRE(OptionNumberPortabilityStatus());
        return static_cast<const NumberPortabilityStatus&> (ElementAt(3));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(4, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(4, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(4);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(4));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_MNP_INFO_RES_H_)
