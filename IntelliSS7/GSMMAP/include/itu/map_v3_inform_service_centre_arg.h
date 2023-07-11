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


#if !defined(_MAP_V3_INFORM_SERVICE_CENTRE_ARG_H_)
#define _MAP_V3_INFORM_SERVICE_CENTRE_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnBitString.h>

#include <map_v3_isdn_address_string.h>
#include <map_v3_mw_status.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class InformServiceCentreArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::ISDN_AddressString ISDN_AddressString;


        typedef map_v3::MW_Status MW_Status;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    InformServiceCentreArg() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    InformServiceCentreArg(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    InformServiceCentreArg(const InformServiceCentreArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    InformServiceCentreArg(its::AsnDescObject* description) : its::AsnSequence(3, description)
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
    static its::AsnDescObject* GetMw_StatusStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~InformServiceCentreArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InformServiceCentreArg(*this);
    }

    virtual std::string GetName() const
    { return "InformServiceCentreArg"; }

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

    void SetMw_Status(MW_Status* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMw_StatusStaticDescription());
        AddElement(1, element);
    }

    void SetMw_Status(const MW_Status& element)
    {
        its::AsnObject& asnObject = const_cast<MW_Status&>(element);
        asnObject.SetDescription(GetMw_StatusStaticDescription());
        AddElement(1, element);
    }

    bool OptionMw_Status() const
    {
        return Contains(1);
    }

    const MW_Status& GetMw_Status() const
    {
        ITS_REQUIRE(OptionMw_Status());
        return static_cast<const MW_Status&> (ElementAt(1));
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

};



} // namespace.

#endif    // !defined(_MAP_V3_INFORM_SERVICE_CENTRE_ARG_H_)
