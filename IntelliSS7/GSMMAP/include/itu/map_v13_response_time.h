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


#if !defined(_MAP_V13_RESPONSE_TIME_H_)
#define _MAP_V13_RESPONSE_TIME_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>

#include <map_v13_response_time_category.h>



namespace map_v13 {



class ResponseTime : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::ResponseTimeCategory ResponseTimeCategory;


////////// End Nested Class(es) //////////

    ResponseTime() : its::AsnSequence(1, false)
    {
        Initialize();
    }

    ResponseTime(its::Octets& octets) : its::AsnSequence(1, false)
    {
        Initialize();
        Decode(octets);
    }

    ResponseTime(const ResponseTime& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ResponseTime(its::AsnDescObject* description) : its::AsnSequence(1, description)
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

    static its::AsnDescObject* GetResponseTimeCategoryStaticDescription();

public:

    virtual ~ResponseTime()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ResponseTime(*this);
    }

    virtual std::string GetName() const
    { return "ResponseTime"; }

    void SetResponseTimeCategory(ResponseTimeCategory* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetResponseTimeCategoryStaticDescription());
        AddElement(0, element);
    }

    void SetResponseTimeCategory(const ResponseTimeCategory& element)
    {
        its::AsnObject& asnObject = const_cast<ResponseTimeCategory&>(element);
        asnObject.SetDescription(GetResponseTimeCategoryStaticDescription());
        AddElement(0, element);
    }

    const ResponseTimeCategory& GetResponseTimeCategory() const
    {
        return static_cast<const ResponseTimeCategory&> (ElementAt(0));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_RESPONSE_TIME_H_)
