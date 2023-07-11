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


#if !defined(_MAP_V2_PERFORM_HO_RES_H_)
#define _MAP_V2_PERFORM_HO_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v2_isdn_address_string.h>
#include <map_v2_external_signal_info.h>



namespace map_v2 {



class PerformHO_Res : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v2::ISDN_AddressString ISDN_AddressString;


        typedef map_v2::ExternalSignalInfo ExternalSignalInfo;


////////// End Nested Class(es) //////////

    PerformHO_Res() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    PerformHO_Res(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    PerformHO_Res(const PerformHO_Res& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    PerformHO_Res(its::AsnDescObject* description) : its::AsnSequence(2, description)
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
    static its::AsnDescObject* GetAccessSignalInfoStaticDescription();

public:

    virtual ~PerformHO_Res()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PerformHO_Res(*this);
    }

    virtual std::string GetName() const
    { return "PerformHO_Res"; }

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

    const ISDN_AddressString& GetHandoverNumber() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetAccessSignalInfo(ExternalSignalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAccessSignalInfoStaticDescription());
        AddElement(1, element);
    }

    void SetAccessSignalInfo(const ExternalSignalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<ExternalSignalInfo&>(element);
        asnObject.SetDescription(GetAccessSignalInfoStaticDescription());
        AddElement(1, element);
    }

    const ExternalSignalInfo& GetAccessSignalInfo() const
    {
        return static_cast<const ExternalSignalInfo&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_PERFORM_HO_RES_H_)
