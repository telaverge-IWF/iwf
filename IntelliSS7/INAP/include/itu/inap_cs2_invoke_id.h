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


#if !defined(_INAP_CS2_INVOKE_ID_H_)
#define _INAP_CS2_INVOKE_ID_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace inap_cs2 {



class InvokeID : public its::AsnInteger
{
public:

    InvokeID() : its::AsnInteger(false)
    {
        Initialize();
    }

    InvokeID(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    InvokeID(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    InvokeID(const InvokeID& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    InvokeID(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    InvokeID(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~InvokeID()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InvokeID(*this);
    }

    virtual std::string GetName() const
    { return "InvokeID"; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_INVOKE_ID_H_)

