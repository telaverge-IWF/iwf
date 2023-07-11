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


#if !defined(_MAP_V13_BSSMAP_SERVICE_HANDOVER_LIST_H_)
#define _MAP_V13_BSSMAP_SERVICE_HANDOVER_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v13_bssmap_service_handover_info.h>



namespace map_v13 {



class BSSMAP_ServiceHandoverList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::BSSMAP_ServiceHandoverInfo BSSMAP_ServiceHandoverInfo;


////////// End Nested Class //////////

    BSSMAP_ServiceHandoverList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    BSSMAP_ServiceHandoverList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    BSSMAP_ServiceHandoverList(const BSSMAP_ServiceHandoverList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    BSSMAP_ServiceHandoverList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetBSSMAP_ServiceHandoverInfoStaticDescription();

public:

    virtual ~BSSMAP_ServiceHandoverList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new BSSMAP_ServiceHandoverList(*this);
    }

    virtual std::string GetName() const
    { return "BSSMAP_ServiceHandoverList"; }

    void AddElement(BSSMAP_ServiceHandoverInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBSSMAP_ServiceHandoverInfoStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const BSSMAP_ServiceHandoverInfo& element)
    {
        its::AsnObject& asnObject = const_cast<BSSMAP_ServiceHandoverInfo&>(element);
        asnObject.SetDescription(GetBSSMAP_ServiceHandoverInfoStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const BSSMAP_ServiceHandoverInfo& ElementAt(int index) const
    {
        return static_cast<const BSSMAP_ServiceHandoverInfo&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_BSSMAP_SERVICE_HANDOVER_LIST_H_)

