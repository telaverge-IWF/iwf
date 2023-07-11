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


#if !defined(_MAP_V9_SERVICE_TYPE_LIST_H_)
#define _MAP_V9_SERVICE_TYPE_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v9_service_type.h>



namespace map_v9 {



class ServiceTypeList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v9::ServiceType ServiceType;


////////// End Nested Class //////////

    ServiceTypeList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    ServiceTypeList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    ServiceTypeList(const ServiceTypeList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    ServiceTypeList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetServiceTypeStaticDescription();

public:

    virtual ~ServiceTypeList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ServiceTypeList(*this);
    }

    virtual std::string GetName() const
    { return "ServiceTypeList"; }

    void AddElement(ServiceType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceTypeStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const ServiceType& element)
    {
        its::AsnObject& asnObject = const_cast<ServiceType&>(element);
        asnObject.SetDescription(GetServiceTypeStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const ServiceType& ElementAt(int index) const
    {
        return static_cast<const ServiceType&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_SERVICE_TYPE_LIST_H_)

