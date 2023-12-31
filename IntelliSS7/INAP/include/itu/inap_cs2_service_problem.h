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


#if !defined(_INAP_CS2_SERVICE_PROBLEM_H_)
#define _INAP_CS2_SERVICE_PROBLEM_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace inap_cs2 {



class ServiceProblem : public its::AsnInteger
{
public:

    ServiceProblem() : its::AsnInteger(false)
    {
        Initialize();
    }

    ServiceProblem(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    ServiceProblem(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    ServiceProblem(const ServiceProblem& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    ServiceProblem(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    ServiceProblem(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

public:

    virtual ~ServiceProblem()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ServiceProblem(*this);
    }

    virtual std::string GetName() const
    { return "ServiceProblem"; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_SERVICE_PROBLEM_H_)

