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


#if !defined(_MAP_V2_PROTOCOL_ID_H_)
#define _MAP_V2_PROTOCOL_ID_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v2 {



class ProtocolId : public its::AsnEnumerated
{
public:

    ProtocolId() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    ProtocolId(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    ProtocolId(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    ProtocolId(const ProtocolId& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    ProtocolId(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    ProtocolId(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~ProtocolId()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ProtocolId(*this);
    }

    virtual std::string GetName() const
    { return "ProtocolId"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        PROTOCOL_ID_GSM_0408 = 1,
        PROTOCOL_ID_GSM_0806 = 2,
        PROTOCOL_ID_GSM_BSSMAP = 3,
        PROTOCOL_ID_ETS_300102_1 = 4

    };

    void SetGsm_0408()
    { _value = 1; }

    bool IsGsm_0408() const
    { return _value == 1; }

    void SetGsm_0806()
    { _value = 2; }

    bool IsGsm_0806() const
    { return _value == 2; }

    void SetGsm_BSSMAP()
    { _value = 3; }

    bool IsGsm_BSSMAP() const
    { return _value == 3; }

    void SetEts_300102_1()
    { _value = 4; }

    bool IsEts_300102_1() const
    { return _value == 4; }

};



} // namespace.

#endif    // !defined(_MAP_V2_PROTOCOL_ID_H_)

