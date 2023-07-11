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


#if !defined(_MAP_V1_RESET_ARG_H_)
#define _MAP_V1_RESET_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>
#include <AsnOctetString.h>
#include <AsnSequenceOf.h>

#include <map_v1_network_resource.h>
#include <map_v1_isdn_address_string.h>
#include <map_v1_hlr_list.h>



namespace map_v1 {



class ResetArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v1::NetworkResource NetworkResource;


        typedef map_v1::ISDN_AddressString ISDN_AddressString;


        typedef map_v1::HlrList HlrList;


////////// End Nested Class(es) //////////

    ResetArg() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    ResetArg(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    ResetArg(const ResetArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ResetArg(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetNetworkResourceStaticDescription();
    static its::AsnDescObject* GetOriginatingEntityNumberStaticDescription();
    static its::AsnDescObject* GetHlrIdStaticDescription();

public:

    virtual ~ResetArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ResetArg(*this);
    }

    virtual std::string GetName() const
    { return "ResetArg"; }

    void SetNetworkResource(NetworkResource* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNetworkResourceStaticDescription());
        AddElement(0, element);
    }

    void SetNetworkResource(const NetworkResource& element)
    {
        its::AsnObject& asnObject = const_cast<NetworkResource&>(element);
        asnObject.SetDescription(GetNetworkResourceStaticDescription());
        AddElement(0, element);
    }

    const NetworkResource& GetNetworkResource() const
    {
        return static_cast<const NetworkResource&> (ElementAt(0));
    }

    void SetOriginatingEntityNumber(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOriginatingEntityNumberStaticDescription());
        AddElement(1, element);
    }

    void SetOriginatingEntityNumber(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetOriginatingEntityNumberStaticDescription());
        AddElement(1, element);
    }

    const ISDN_AddressString& GetOriginatingEntityNumber() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(1));
    }

    void SetHlrId(HlrList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetHlrIdStaticDescription());
        AddElement(2, element);
    }

    void SetHlrId(const HlrList& element)
    {
        its::AsnObject& asnObject = const_cast<HlrList&>(element);
        asnObject.SetDescription(GetHlrIdStaticDescription());
        AddElement(2, element);
    }

    bool OptionHlrId() const
    {
        return Contains(2);
    }

    const HlrList& GetHlrId() const
    {
        ITS_REQUIRE(OptionHlrId());
        return static_cast<const HlrList&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_RESET_ARG_H_)
