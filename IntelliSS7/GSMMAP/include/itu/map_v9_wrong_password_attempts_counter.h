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


#if !defined(_MAP_V9_WRONG_PASSWORD_ATTEMPTS_COUNTER_H_)
#define _MAP_V9_WRONG_PASSWORD_ATTEMPTS_COUNTER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v9 {



class WrongPasswordAttemptsCounter : public its::AsnInteger
{
public:

    WrongPasswordAttemptsCounter() : its::AsnInteger(false)
    {
        Initialize();
    }

    WrongPasswordAttemptsCounter(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    WrongPasswordAttemptsCounter(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    WrongPasswordAttemptsCounter(const WrongPasswordAttemptsCounter& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    WrongPasswordAttemptsCounter(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    WrongPasswordAttemptsCounter(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~WrongPasswordAttemptsCounter()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new WrongPasswordAttemptsCounter(*this);
    }

    virtual std::string GetName() const
    { return "WrongPasswordAttemptsCounter"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_WRONG_PASSWORD_ATTEMPTS_COUNTER_H_)

