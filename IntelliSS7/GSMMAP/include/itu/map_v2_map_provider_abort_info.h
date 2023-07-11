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


#if !defined(_MAP_V2_MAP_PROVIDER_ABORT_INFO_H_)
#define _MAP_V2_MAP_PROVIDER_ABORT_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>

#include <map_v2_map_provider_abort_reason.h>



namespace map_v2 {



class MAP_ProviderAbortInfo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v2::MAP_ProviderAbortReason MAP_ProviderAbortReason;


////////// End Nested Class(es) //////////

    MAP_ProviderAbortInfo() : its::AsnSequence(1, false)
    {
        Initialize();
    }

    MAP_ProviderAbortInfo(its::Octets& octets) : its::AsnSequence(1, false)
    {
        Initialize();
        Decode(octets);
    }

    MAP_ProviderAbortInfo(const MAP_ProviderAbortInfo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    MAP_ProviderAbortInfo(its::AsnDescObject* description) : its::AsnSequence(1, description)
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

    static its::AsnDescObject* GetMap_ProviderAbortReasonStaticDescription();

public:

    virtual ~MAP_ProviderAbortInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MAP_ProviderAbortInfo(*this);
    }

    virtual std::string GetName() const
    { return "MAP_ProviderAbortInfo"; }

    void SetMap_ProviderAbortReason(MAP_ProviderAbortReason* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMap_ProviderAbortReasonStaticDescription());
        AddElement(0, element);
    }

    void SetMap_ProviderAbortReason(const MAP_ProviderAbortReason& element)
    {
        its::AsnObject& asnObject = const_cast<MAP_ProviderAbortReason&>(element);
        asnObject.SetDescription(GetMap_ProviderAbortReasonStaticDescription());
        AddElement(0, element);
    }

    const MAP_ProviderAbortReason& GetMap_ProviderAbortReason() const
    {
        return static_cast<const MAP_ProviderAbortReason&> (ElementAt(0));
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_MAP_PROVIDER_ABORT_INFO_H_)
