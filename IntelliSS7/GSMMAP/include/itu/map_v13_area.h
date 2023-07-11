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


#if !defined(_MAP_V13_AREA_H_)
#define _MAP_V13_AREA_H_

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

#include <map_v13_area_type.h>
#include <map_v13_area_identification.h>



namespace map_v13 {



class Area : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::AreaType AreaType;


        typedef map_v13::AreaIdentification AreaIdentification;


////////// End Nested Class(es) //////////

    Area() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    Area(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    Area(const Area& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    Area(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetAreaTypeStaticDescription();
    static its::AsnDescObject* GetAreaIdentificationStaticDescription();

public:

    virtual ~Area()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Area(*this);
    }

    virtual std::string GetName() const
    { return "Area"; }

    void SetAreaType(AreaType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAreaTypeStaticDescription());
        AddElement(0, element);
    }

    void SetAreaType(const AreaType& element)
    {
        its::AsnObject& asnObject = const_cast<AreaType&>(element);
        asnObject.SetDescription(GetAreaTypeStaticDescription());
        AddElement(0, element);
    }

    const AreaType& GetAreaType() const
    {
        return static_cast<const AreaType&> (ElementAt(0));
    }

    void SetAreaIdentification(AreaIdentification* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAreaIdentificationStaticDescription());
        AddElement(1, element);
    }

    void SetAreaIdentification(const AreaIdentification& element)
    {
        its::AsnObject& asnObject = const_cast<AreaIdentification&>(element);
        asnObject.SetDescription(GetAreaIdentificationStaticDescription());
        AddElement(1, element);
    }

    const AreaIdentification& GetAreaIdentification() const
    {
        return static_cast<const AreaIdentification&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_AREA_H_)

