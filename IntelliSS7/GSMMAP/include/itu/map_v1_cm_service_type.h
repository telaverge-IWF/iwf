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


#if !defined(_MAP_V1_CM_SERVICE_TYPE_H_)
#define _MAP_V1_CM_SERVICE_TYPE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v1 {



class CmServiceType : public its::AsnEnumerated
{
public:

    CmServiceType() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    CmServiceType(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    CmServiceType(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    CmServiceType(const CmServiceType& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    CmServiceType(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    CmServiceType(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~CmServiceType()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CmServiceType(*this);
    }

    virtual std::string GetName() const
    { return "CmServiceType"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        CM_SERVICE_TYPE_MODILE_ORIGINATING_CALL = 1,
        CM_SERVICE_TYPE_EMERGENCY_CALL_ESTABLISHMENT = 2,
        CM_SERVICE_TYPE_SHORT_MESSAGE_SERVICE = 3,
        CM_SERVICE_TYPE_SS_REQUEST = 4,
        CM_SERVICE_TYPE_MOBILE_ORIGINATING_CALL_RE_ESTABLISHMENT = 5,
        CM_SERVICE_TYPE_MOBILE_TERMINATING_CALL = 10

    };

    void SetModileOriginatingCall()
    { _value = 1; }

    bool IsModileOriginatingCall() const
    { return _value == 1; }

    void SetEmergencyCallEstablishment()
    { _value = 2; }

    bool IsEmergencyCallEstablishment() const
    { return _value == 2; }

    void SetShortMessageService()
    { _value = 3; }

    bool IsShortMessageService() const
    { return _value == 3; }

    void SetSs_request()
    { _value = 4; }

    bool IsSs_request() const
    { return _value == 4; }

    void SetMobileOriginatingCallRe_establishment()
    { _value = 5; }

    bool IsMobileOriginatingCallRe_establishment() const
    { return _value == 5; }

    void SetMobileTerminatingCall()
    { _value = 10; }

    bool IsMobileTerminatingCall() const
    { return _value == 10; }

};



} // namespace.

#endif    // !defined(_MAP_V1_CM_SERVICE_TYPE_H_)

