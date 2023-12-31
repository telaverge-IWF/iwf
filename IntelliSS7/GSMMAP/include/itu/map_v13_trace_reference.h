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


#if !defined(_MAP_V13_TRACE_REFERENCE_H_)
#define _MAP_V13_TRACE_REFERENCE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v13 {



class TraceReference : public its::AsnOctetString
{
public:

    TraceReference() : its::AsnOctetString(false)
    {
        Initialize();
    }

    TraceReference(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    TraceReference(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    TraceReference(const TraceReference& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    TraceReference(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    TraceReference(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~TraceReference()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new TraceReference(*this);
    }

    virtual std::string GetName() const
    { return "TraceReference"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_TRACE_REFERENCE_H_)

