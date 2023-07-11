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


#if !defined(_MAP_V3_UPDATE_LOCATION_ARG_H_)
#define _MAP_V3_UPDATE_LOCATION_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v3_imsi.h>
#include <map_v3_isdn_address_string.h>
#include <map_v3_lmsi.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class UpdateLocationArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::IMSI IMSI;


        typedef map_v3::ISDN_AddressString ISDN_AddressString;


        typedef map_v3::LMSI LMSI;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    UpdateLocationArg() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    UpdateLocationArg(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    UpdateLocationArg(const UpdateLocationArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    UpdateLocationArg(its::AsnDescObject* description) : its::AsnSequence(5, description)
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
    static its::AsnDescObject* GetMsc_NumberStaticDescription();
    static its::AsnDescObject* GetVlr_NumberStaticDescription();
    static its::AsnDescObject* GetLmsiStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~UpdateLocationArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new UpdateLocationArg(*this);
    }

    virtual std::string GetName() const
    { return "UpdateLocationArg"; }

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

    const IMSI& GetImsi() const
    {
        return static_cast<const IMSI&> (ElementAt(0));
    }

    void SetMsc_Number(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsc_NumberStaticDescription());
        AddElement(1, element);
    }

    void SetMsc_Number(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMsc_NumberStaticDescription());
        AddElement(1, element);
    }

    const ISDN_AddressString& GetMsc_Number() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(1));
    }

    void SetVlr_Number(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVlr_NumberStaticDescription());
        AddElement(2, element);
    }

    void SetVlr_Number(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetVlr_NumberStaticDescription());
        AddElement(2, element);
    }

    const ISDN_AddressString& GetVlr_Number() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(2));
    }

    void SetLmsi(LMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLmsiStaticDescription());
        AddElement(3, element);
    }

    void SetLmsi(const LMSI& element)
    {
        its::AsnObject& asnObject = const_cast<LMSI&>(element);
        asnObject.SetDescription(GetLmsiStaticDescription());
        AddElement(3, element);
    }

    bool OptionLmsi() const
    {
        return Contains(3);
    }

    const LMSI& GetLmsi() const
    {
        ITS_REQUIRE(OptionLmsi());
        return static_cast<const LMSI&> (ElementAt(3));
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

#endif    // !defined(_MAP_V3_UPDATE_LOCATION_ARG_H_)

