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


#if !defined(_MAP_V13_LCS_CLIENT_INTERNAL_ID_H_)
#define _MAP_V13_LCS_CLIENT_INTERNAL_ID_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v13 {



class LCSClientInternalID : public its::AsnEnumerated
{
public:

    LCSClientInternalID() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    LCSClientInternalID(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    LCSClientInternalID(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    LCSClientInternalID(const LCSClientInternalID& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    LCSClientInternalID(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    LCSClientInternalID(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~LCSClientInternalID()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new LCSClientInternalID(*this);
    }

    virtual std::string GetName() const
    { return "LCSClientInternalID"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        LCS_CLIENT_INTERNAL_ID_BROADCAST_SERVICE = 0,
        LCS_CLIENT_INTERNAL_ID_O_AND_M_HPLMN = 1,
        LCS_CLIENT_INTERNAL_ID_O_AND_M_VPLMN = 2,
        LCS_CLIENT_INTERNAL_ID_ANONYMOUS_LOCATION = 3,
        LCS_CLIENT_INTERNAL_ID_TARGET_M_SSUBSCRIBED_SERVICE = 4

    };

    void SetBroadcastService()
    { _value = 0; }

    bool IsBroadcastService() const
    { return _value == 0; }

    void SetO_andM_HPLMN()
    { _value = 1; }

    bool IsO_andM_HPLMN() const
    { return _value == 1; }

    void SetO_andM_VPLMN()
    { _value = 2; }

    bool IsO_andM_VPLMN() const
    { return _value == 2; }

    void SetAnonymousLocation()
    { _value = 3; }

    bool IsAnonymousLocation() const
    { return _value == 3; }

    void SetTargetMSsubscribedService()
    { _value = 4; }

    bool IsTargetMSsubscribedService() const
    { return _value == 4; }

};



} // namespace.

#endif    // !defined(_MAP_V13_LCS_CLIENT_INTERNAL_ID_H_)
