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


#if !defined(_MAP_V1_UPDATE_LOCATION_ARG_H_)
#define _MAP_V1_UPDATE_LOCATION_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnChoice.h>

#include <map_v1_imsi.h>
#include <map_v1_location_info.h>
#include <map_v1_isdn_address_string.h>
#include <map_v1_l_ms_id.h>



namespace map_v1 {



class UpdateLocationArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v1::IMSI IMSI;


        typedef map_v1::LocationInfo LocationInfo;


        typedef map_v1::ISDN_AddressString ISDN_AddressString;


        typedef map_v1::LMsId LMsId;


////////// End Nested Class(es) //////////

    UpdateLocationArg() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    UpdateLocationArg(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    UpdateLocationArg(const UpdateLocationArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    UpdateLocationArg(its::AsnDescObject* description) : its::AsnSequence(4, description)
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
    static its::AsnDescObject* GetLocationInfoStaticDescription();
    static its::AsnDescObject* GetVlrNumberStaticDescription();
    static its::AsnDescObject* GetLmsidStaticDescription();

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

    void SetLocationInfo(LocationInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLocationInfoStaticDescription());
        AddElement(1, element);
    }

    void SetLocationInfo(const LocationInfo& element)
    {
        its::AsnObject& asnObject = const_cast<LocationInfo&>(element);
        asnObject.SetDescription(GetLocationInfoStaticDescription());
        AddElement(1, element);
    }

    const LocationInfo& GetLocationInfo() const
    {
        return static_cast<const LocationInfo&> (ElementAt(1));
    }

    void SetVlrNumber(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVlrNumberStaticDescription());
        AddElement(2, element);
    }

    void SetVlrNumber(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetVlrNumberStaticDescription());
        AddElement(2, element);
    }

    const ISDN_AddressString& GetVlrNumber() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(2));
    }

    void SetLmsid(LMsId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLmsidStaticDescription());
        AddElement(3, element);
    }

    void SetLmsid(const LMsId& element)
    {
        its::AsnObject& asnObject = const_cast<LMsId&>(element);
        asnObject.SetDescription(GetLmsidStaticDescription());
        AddElement(3, element);
    }

    bool OptionLmsid() const
    {
        return Contains(3);
    }

    const LMsId& GetLmsid() const
    {
        ITS_REQUIRE(OptionLmsid());
        return static_cast<const LMsId&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_UPDATE_LOCATION_ARG_H_)

