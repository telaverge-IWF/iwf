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


#if !defined(_MAP_V13_TRACE_RECORDING_SESSION_REFERENCE_H_)
#define _MAP_V13_TRACE_RECORDING_SESSION_REFERENCE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v13 {



class TraceRecordingSessionReference : public its::AsnOctetString
{
public:

    TraceRecordingSessionReference() : its::AsnOctetString(false)
    {
        Initialize();
    }

    TraceRecordingSessionReference(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    TraceRecordingSessionReference(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    TraceRecordingSessionReference(const TraceRecordingSessionReference& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    TraceRecordingSessionReference(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    TraceRecordingSessionReference(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~TraceRecordingSessionReference()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new TraceRecordingSessionReference(*this);
    }

    virtual std::string GetName() const
    { return "TraceRecordingSessionReference"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_TRACE_RECORDING_SESSION_REFERENCE_H_)
