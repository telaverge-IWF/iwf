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


#if !defined(_CAP_V3_ACTIVITY_TEST_GPRS_ARG_H_)
#define _CAP_V3_ACTIVITY_TEST_GPRS_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>

#include <cap_v3_gprs_reference_number.h>



namespace cap_v3 {



class ActivityTestGPRSArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::GPRS_ReferenceNumber GPRS_ReferenceNumber;


////////// End Nested Class(es) //////////

    ActivityTestGPRSArg() : its::AsnSequence(1, false)
    {
        Initialize();
    }

    ActivityTestGPRSArg(its::Octets& octets) : its::AsnSequence(1, false)
    {
        Initialize();
        Decode(octets);
    }

    ActivityTestGPRSArg(const ActivityTestGPRSArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ActivityTestGPRSArg(its::AsnDescObject* description) : its::AsnSequence(1, description)
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

    static its::AsnDescObject* GetGPRS_ReferenceNumberStaticDescription();

public:

    virtual ~ActivityTestGPRSArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ActivityTestGPRSArg(*this);
    }

    virtual std::string GetName() const
    { return "ActivityTestGPRSArg"; }

    void SetGPRS_ReferenceNumber(GPRS_ReferenceNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGPRS_ReferenceNumberStaticDescription());
        AddElement(0, element);
    }

    void SetGPRS_ReferenceNumber(const GPRS_ReferenceNumber& element)
    {
        its::AsnObject& asnObject = const_cast<GPRS_ReferenceNumber&>(element);
        asnObject.SetDescription(GetGPRS_ReferenceNumberStaticDescription());
        AddElement(0, element);
    }

    const GPRS_ReferenceNumber& GetGPRS_ReferenceNumber() const
    {
        return static_cast<const GPRS_ReferenceNumber&> (ElementAt(0));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_ACTIVITY_TEST_GPRS_ARG_H_)

