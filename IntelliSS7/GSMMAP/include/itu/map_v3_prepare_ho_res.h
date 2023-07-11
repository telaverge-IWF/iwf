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


#if !defined(_MAP_V3_PREPARE_HO_RES_H_)
#define _MAP_V3_PREPARE_HO_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v3_isdn_address_string.h>
#include <map_v3_external_signal_info.h>



namespace map_v3 {



class PrepareHO_Res : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::ISDN_AddressString ISDN_AddressString;


        typedef map_v3::ExternalSignalInfo ExternalSignalInfo;


////////// End Nested Class(es) //////////

    PrepareHO_Res() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    PrepareHO_Res(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    PrepareHO_Res(const PrepareHO_Res& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    PrepareHO_Res(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetHandoverNumberStaticDescription();
    static its::AsnDescObject* GetBss_APDUStaticDescription();

public:

    virtual ~PrepareHO_Res()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PrepareHO_Res(*this);
    }

    virtual std::string GetName() const
    { return "PrepareHO_Res"; }

    void SetHandoverNumber(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetHandoverNumberStaticDescription());
        AddElement(0, element);
    }

    void SetHandoverNumber(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetHandoverNumberStaticDescription());
        AddElement(0, element);
    }

    bool OptionHandoverNumber() const
    {
        return Contains(0);
    }

    const ISDN_AddressString& GetHandoverNumber() const
    {
        ITS_REQUIRE(OptionHandoverNumber());
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetBss_APDU(ExternalSignalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBss_APDUStaticDescription());
        AddElement(1, element);
    }

    void SetBss_APDU(const ExternalSignalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<ExternalSignalInfo&>(element);
        asnObject.SetDescription(GetBss_APDUStaticDescription());
        AddElement(1, element);
    }

    bool OptionBss_APDU() const
    {
        return Contains(1);
    }

    const ExternalSignalInfo& GetBss_APDU() const
    {
        ITS_REQUIRE(OptionBss_APDU());
        return static_cast<const ExternalSignalInfo&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_PREPARE_HO_RES_H_)

