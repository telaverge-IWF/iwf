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


#if !defined(_MAP_V9_REPORT_SM_DELIVERY_STATUS_RES_H_)
#define _MAP_V9_REPORT_SM_DELIVERY_STATUS_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v9_isdn_address_string.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class ReportSM_DeliveryStatusRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::ISDN_AddressString ISDN_AddressString;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ReportSM_DeliveryStatusRes() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    ReportSM_DeliveryStatusRes(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    ReportSM_DeliveryStatusRes(const ReportSM_DeliveryStatusRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ReportSM_DeliveryStatusRes(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetStoredMSISDNStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~ReportSM_DeliveryStatusRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ReportSM_DeliveryStatusRes(*this);
    }

    virtual std::string GetName() const
    { return "ReportSM_DeliveryStatusRes"; }

    void SetStoredMSISDN(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetStoredMSISDNStaticDescription());
        AddElement(0, element);
    }

    void SetStoredMSISDN(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetStoredMSISDNStaticDescription());
        AddElement(0, element);
    }

    bool OptionStoredMSISDN() const
    {
        return Contains(0);
    }

    const ISDN_AddressString& GetStoredMSISDN() const
    {
        ITS_REQUIRE(OptionStoredMSISDN());
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
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

#endif    // !defined(_MAP_V9_REPORT_SM_DELIVERY_STATUS_RES_H_)

