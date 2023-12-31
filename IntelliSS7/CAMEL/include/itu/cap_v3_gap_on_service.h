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


#if !defined(_CAP_V3_GAP_ON_SERVICE_H_)
#define _CAP_V3_GAP_ON_SERVICE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnInteger.h>

#include <cap_v3_service_key.h>



namespace cap_v3 {



class GapOnService : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::ServiceKey ServiceKey;


////////// End Nested Class(es) //////////

    GapOnService() : its::AsnSequence(1, false)
    {
        Initialize();
    }

    GapOnService(its::Octets& octets) : its::AsnSequence(1, false)
    {
        Initialize();
        Decode(octets);
    }

    GapOnService(const GapOnService& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    GapOnService(its::AsnDescObject* description) : its::AsnSequence(1, description)
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

    static its::AsnDescObject* GetServiceKeyStaticDescription();

public:

    virtual ~GapOnService()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new GapOnService(*this);
    }

    virtual std::string GetName() const
    { return "GapOnService"; }

    void SetServiceKey(ServiceKey* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceKeyStaticDescription());
        AddElement(0, element);
    }

    void SetServiceKey(const ServiceKey& element)
    {
        its::AsnObject& asnObject = const_cast<ServiceKey&>(element);
        asnObject.SetDescription(GetServiceKeyStaticDescription());
        AddElement(0, element);
    }

    const ServiceKey& GetServiceKey() const
    {
        return static_cast<const ServiceKey&> (ElementAt(0));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_GAP_ON_SERVICE_H_)

