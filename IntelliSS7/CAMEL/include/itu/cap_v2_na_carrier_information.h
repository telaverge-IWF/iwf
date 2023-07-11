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


#if !defined(_CAP_V2_NA_CARRIER_INFORMATION_H_)
#define _CAP_V2_NA_CARRIER_INFORMATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <cap_v2_naea_cic.h>
#include <cap_v2_na_carrier_selection_info.h>



namespace cap_v2 {



class NACarrierInformation : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v2::NAEA_CIC NAEA_CIC;


        typedef cap_v2::NACarrierSelectionInfo NACarrierSelectionInfo;


////////// End Nested Class(es) //////////

    NACarrierInformation() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    NACarrierInformation(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    NACarrierInformation(const NACarrierInformation& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    NACarrierInformation(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetNaCarrierIdStaticDescription();
    static its::AsnDescObject* GetNaCICSelectionTypeStaticDescription();

public:

    virtual ~NACarrierInformation()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new NACarrierInformation(*this);
    }

    virtual std::string GetName() const
    { return "NACarrierInformation"; }

    void SetNaCarrierId(NAEA_CIC* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNaCarrierIdStaticDescription());
        AddElement(0, element);
    }

    void SetNaCarrierId(const NAEA_CIC& element)
    {
        its::AsnObject& asnObject = const_cast<NAEA_CIC&>(element);
        asnObject.SetDescription(GetNaCarrierIdStaticDescription());
        AddElement(0, element);
    }

    bool OptionNaCarrierId() const
    {
        return Contains(0);
    }

    const NAEA_CIC& GetNaCarrierId() const
    {
        ITS_REQUIRE(OptionNaCarrierId());
        return static_cast<const NAEA_CIC&> (ElementAt(0));
    }

    void SetNaCICSelectionType(NACarrierSelectionInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNaCICSelectionTypeStaticDescription());
        AddElement(1, element);
    }

    void SetNaCICSelectionType(const NACarrierSelectionInfo& element)
    {
        its::AsnObject& asnObject = const_cast<NACarrierSelectionInfo&>(element);
        asnObject.SetDescription(GetNaCICSelectionTypeStaticDescription());
        AddElement(1, element);
    }

    bool OptionNaCICSelectionType() const
    {
        return Contains(1);
    }

    const NACarrierSelectionInfo& GetNaCICSelectionType() const
    {
        ITS_REQUIRE(OptionNaCICSelectionType());
        return static_cast<const NACarrierSelectionInfo&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_CAP_V2_NA_CARRIER_INFORMATION_H_)

