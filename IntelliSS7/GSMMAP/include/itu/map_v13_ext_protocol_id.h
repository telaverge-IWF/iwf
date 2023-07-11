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


#if !defined(_MAP_V13_EXT_PROTOCOL_ID_H_)
#define _MAP_V13_EXT_PROTOCOL_ID_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v13 {



class Ext_ProtocolId : public its::AsnEnumerated
{
public:

    Ext_ProtocolId() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    Ext_ProtocolId(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    Ext_ProtocolId(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    Ext_ProtocolId(const Ext_ProtocolId& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    Ext_ProtocolId(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    Ext_ProtocolId(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~Ext_ProtocolId()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Ext_ProtocolId(*this);
    }

    virtual std::string GetName() const
    { return "Ext_ProtocolId"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        EXT_PROTOCOL_ID_ETS_300356 = 1

    };

    void SetEts_300356()
    { _value = 1; }

    bool IsEts_300356() const
    { return _value == 1; }

};



} // namespace.

#endif    // !defined(_MAP_V13_EXT_PROTOCOL_ID_H_)

