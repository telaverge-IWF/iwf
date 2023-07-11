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


#if !defined(_MAP_V1_ABSENT_SUBSCRIBER_ERROR_ARG_H_)
#define _MAP_V1_ABSENT_SUBSCRIBER_ERROR_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBoolean.h>



namespace map_v1 {



class AbsentSubscriberErrorArg : public its::AsnBoolean
{
public:

    AbsentSubscriberErrorArg(bool value) : its::AsnBoolean(value, false)
    {
        Initialize();
    }

    AbsentSubscriberErrorArg(its::Octets& octets) : its::AsnBoolean(false, false)
    {
        Initialize();
        Decode(octets);
    }

    AbsentSubscriberErrorArg(const AbsentSubscriberErrorArg& rhs) : its::AsnBoolean(rhs)
    {
        // Nothing to do.
    }

    AbsentSubscriberErrorArg(its::AsnDescObject* description) : its::AsnBoolean(description)
    {
        // Nothing to do.
    }

    AbsentSubscriberErrorArg(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

    virtual ~AbsentSubscriberErrorArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AbsentSubscriberErrorArg(*this);
    }

    virtual std::string GetName() const
    { return "AbsentSubscriberErrorArg"; }

};



} // namespace.

#endif    // !defined(_MAP_V1_ABSENT_SUBSCRIBER_ERROR_ARG_H_)

