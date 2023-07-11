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


#if !defined(_MAP_V9_BASIC_SERVICE_CRITERIA_H_)
#define _MAP_V9_BASIC_SERVICE_CRITERIA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnChoice.h>

#include <map_v9_ext_basic_service_code.h>



namespace map_v9 {



class BasicServiceCriteria : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v9::Ext_BasicServiceCode Ext_BasicServiceCode;


////////// End Nested Class //////////

    BasicServiceCriteria() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    BasicServiceCriteria(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    BasicServiceCriteria(const BasicServiceCriteria& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    BasicServiceCriteria(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetExt_BasicServiceCodeStaticDescription();

public:

    virtual ~BasicServiceCriteria()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new BasicServiceCriteria(*this);
    }

    virtual std::string GetName() const
    { return "BasicServiceCriteria"; }

    void AddElement(Ext_BasicServiceCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExt_BasicServiceCodeStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const Ext_BasicServiceCode& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_BasicServiceCode&>(element);
        asnObject.SetDescription(GetExt_BasicServiceCodeStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const Ext_BasicServiceCode& ElementAt(int index) const
    {
        return static_cast<const Ext_BasicServiceCode&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_BASIC_SERVICE_CRITERIA_H_)

