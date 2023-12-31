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


#if !defined(_CAP_V2_REQUESTED_INFORMATION_H_)
#define _CAP_V2_REQUESTED_INFORMATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>
#include <AsnChoice.h>

#include <cap_v2_requested_information_type.h>
#include <cap_v2_requested_information_value.h>



namespace cap_v2 {



class RequestedInformation : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v2::RequestedInformationType RequestedInformationType;


        typedef cap_v2::RequestedInformationValue RequestedInformationValue;


////////// End Nested Class(es) //////////

    RequestedInformation() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    RequestedInformation(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    RequestedInformation(const RequestedInformation& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    RequestedInformation(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetRequestedInformationTypeStaticDescription();
    static its::AsnDescObject* GetRequestedInformationValueStaticDescription();

public:

    virtual ~RequestedInformation()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RequestedInformation(*this);
    }

    virtual std::string GetName() const
    { return "RequestedInformation"; }

    void SetRequestedInformationType(RequestedInformationType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRequestedInformationTypeStaticDescription());
        AddElement(0, element);
    }

    void SetRequestedInformationType(const RequestedInformationType& element)
    {
        its::AsnObject& asnObject = const_cast<RequestedInformationType&>(element);
        asnObject.SetDescription(GetRequestedInformationTypeStaticDescription());
        AddElement(0, element);
    }

    const RequestedInformationType& GetRequestedInformationType() const
    {
        return static_cast<const RequestedInformationType&> (ElementAt(0));
    }

    void SetRequestedInformationValue(RequestedInformationValue* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRequestedInformationValueStaticDescription());
        AddElement(1, element);
    }

    void SetRequestedInformationValue(const RequestedInformationValue& element)
    {
        its::AsnObject& asnObject = const_cast<RequestedInformationValue&>(element);
        asnObject.SetDescription(GetRequestedInformationValueStaticDescription());
        AddElement(1, element);
    }

    const RequestedInformationValue& GetRequestedInformationValue() const
    {
        return static_cast<const RequestedInformationValue&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_CAP_V2_REQUESTED_INFORMATION_H_)

