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


#if !defined(_INAP_CS2_CALL_SEGMENT_ID_H_)
#define _INAP_CS2_CALL_SEGMENT_ID_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace inap_cs2 {



class CallSegmentID : public its::AsnInteger
{
public:

    CallSegmentID() : its::AsnInteger(false)
    {
        Initialize();
    }

    CallSegmentID(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    CallSegmentID(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    CallSegmentID(const CallSegmentID& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    CallSegmentID(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    CallSegmentID(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~CallSegmentID()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CallSegmentID(*this);
    }

    virtual std::string GetName() const
    { return "CallSegmentID"; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_CALL_SEGMENT_ID_H_)
