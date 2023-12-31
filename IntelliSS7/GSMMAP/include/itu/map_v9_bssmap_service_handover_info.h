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


#if !defined(_MAP_V9_BSSMAP_SERVICE_HANDOVER_INFO_H_)
#define _MAP_V9_BSSMAP_SERVICE_HANDOVER_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnInteger.h>

#include <map_v9_bssmap_service_handover.h>
#include <map_v9_rab_id.h>



namespace map_v9 {



class BSSMAP_ServiceHandoverInfo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::BSSMAP_ServiceHandover BSSMAP_ServiceHandover;


        typedef map_v9::RAB_Id RAB_Id;


////////// End Nested Class(es) //////////

    BSSMAP_ServiceHandoverInfo() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    BSSMAP_ServiceHandoverInfo(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    BSSMAP_ServiceHandoverInfo(const BSSMAP_ServiceHandoverInfo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    BSSMAP_ServiceHandoverInfo(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetBssmap_ServiceHandoverStaticDescription();
    static its::AsnDescObject* GetRab_IdStaticDescription();

public:

    virtual ~BSSMAP_ServiceHandoverInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new BSSMAP_ServiceHandoverInfo(*this);
    }

    virtual std::string GetName() const
    { return "BSSMAP_ServiceHandoverInfo"; }

    void SetBssmap_ServiceHandover(BSSMAP_ServiceHandover* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBssmap_ServiceHandoverStaticDescription());
        AddElement(0, element);
    }

    void SetBssmap_ServiceHandover(const BSSMAP_ServiceHandover& element)
    {
        its::AsnObject& asnObject = const_cast<BSSMAP_ServiceHandover&>(element);
        asnObject.SetDescription(GetBssmap_ServiceHandoverStaticDescription());
        AddElement(0, element);
    }

    const BSSMAP_ServiceHandover& GetBssmap_ServiceHandover() const
    {
        return static_cast<const BSSMAP_ServiceHandover&> (ElementAt(0));
    }

    void SetRab_Id(RAB_Id* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRab_IdStaticDescription());
        AddElement(1, element);
    }

    void SetRab_Id(const RAB_Id& element)
    {
        its::AsnObject& asnObject = const_cast<RAB_Id&>(element);
        asnObject.SetDescription(GetRab_IdStaticDescription());
        AddElement(1, element);
    }

    const RAB_Id& GetRab_Id() const
    {
        return static_cast<const RAB_Id&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_BSSMAP_SERVICE_HANDOVER_INFO_H_)

