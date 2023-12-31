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


#if !defined(_MAP_V2_REQUEST_PARAMETER_LIST_H_)
#define _MAP_V2_REQUEST_PARAMETER_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnEnumerated.h>

#include <map_v2_request_parameter.h>



namespace map_v2 {



class RequestParameterList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v2::RequestParameter RequestParameter;


////////// End Nested Class //////////

    RequestParameterList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    RequestParameterList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    RequestParameterList(const RequestParameterList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    RequestParameterList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetRequestParameterStaticDescription();

public:

    virtual ~RequestParameterList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RequestParameterList(*this);
    }

    virtual std::string GetName() const
    { return "RequestParameterList"; }

    void AddElement(RequestParameter* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRequestParameterStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const RequestParameter& element)
    {
        its::AsnObject& asnObject = const_cast<RequestParameter&>(element);
        asnObject.SetDescription(GetRequestParameterStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const RequestParameter& ElementAt(int index) const
    {
        return static_cast<const RequestParameter&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_REQUEST_PARAMETER_LIST_H_)

