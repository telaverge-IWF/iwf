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


#if !defined(_MAP_V9_GPRS_TRIGGER_DETECTION_POINT_H_)
#define _MAP_V9_GPRS_TRIGGER_DETECTION_POINT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v9 {



class GPRS_TriggerDetectionPoint : public its::AsnEnumerated
{
public:

    GPRS_TriggerDetectionPoint() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    GPRS_TriggerDetectionPoint(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    GPRS_TriggerDetectionPoint(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    GPRS_TriggerDetectionPoint(const GPRS_TriggerDetectionPoint& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    GPRS_TriggerDetectionPoint(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    GPRS_TriggerDetectionPoint(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~GPRS_TriggerDetectionPoint()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new GPRS_TriggerDetectionPoint(*this);
    }

    virtual std::string GetName() const
    { return "GPRS_TriggerDetectionPoint"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        GPRS_TRIGGER_DETECTION_POINT_ATTACH = 1,
        GPRS_TRIGGER_DETECTION_POINT_ATTACH_CHANGE_OF_POSITION = 2,
        GPRS_TRIGGER_DETECTION_POINT_PDP_CONTEXT_ESTABLISHMENT = 11,
        GPRS_TRIGGER_DETECTION_POINT_PDP_CONTEXT_ESTABLISHMENT_ACKNOWLEDGEMENT = 12,
        GPRS_TRIGGER_DETECTION_POINT_PDP_CONTEXT_CHANGE_OF_POSITION = 14

    };

    void SetAttach()
    { _value = 1; }

    bool IsAttach() const
    { return _value == 1; }

    void SetAttachChangeOfPosition()
    { _value = 2; }

    bool IsAttachChangeOfPosition() const
    { return _value == 2; }

    void SetPdp_ContextEstablishment()
    { _value = 11; }

    bool IsPdp_ContextEstablishment() const
    { return _value == 11; }

    void SetPdp_ContextEstablishmentAcknowledgement()
    { _value = 12; }

    bool IsPdp_ContextEstablishmentAcknowledgement() const
    { return _value == 12; }

    void SetPdp_ContextChangeOfPosition()
    { _value = 14; }

    bool IsPdp_ContextChangeOfPosition() const
    { return _value == 14; }

};



} // namespace.

#endif    // !defined(_MAP_V9_GPRS_TRIGGER_DETECTION_POINT_H_)
