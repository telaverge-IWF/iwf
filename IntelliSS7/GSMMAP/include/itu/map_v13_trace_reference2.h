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


#if !defined(_MAP_V13_TRACE_REFERENCE2_H_)
#define _MAP_V13_TRACE_REFERENCE2_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v13 {



class TraceReference2 : public its::AsnOctetString
{
public:

    TraceReference2() : its::AsnOctetString(false)
    {
        Initialize();
    }

    TraceReference2(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    TraceReference2(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    TraceReference2(const TraceReference2& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    TraceReference2(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    TraceReference2(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~TraceReference2()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new TraceReference2(*this);
    }

    virtual std::string GetName() const
    { return "TraceReference2"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_TRACE_REFERENCE2_H_)

