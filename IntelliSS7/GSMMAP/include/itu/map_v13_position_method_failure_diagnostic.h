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


#if !defined(_MAP_V13_POSITION_METHOD_FAILURE_DIAGNOSTIC_H_)
#define _MAP_V13_POSITION_METHOD_FAILURE_DIAGNOSTIC_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v13 {



class PositionMethodFailure_Diagnostic : public its::AsnEnumerated
{
public:

    PositionMethodFailure_Diagnostic() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    PositionMethodFailure_Diagnostic(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    PositionMethodFailure_Diagnostic(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    PositionMethodFailure_Diagnostic(const PositionMethodFailure_Diagnostic& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    PositionMethodFailure_Diagnostic(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    PositionMethodFailure_Diagnostic(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~PositionMethodFailure_Diagnostic()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PositionMethodFailure_Diagnostic(*this);
    }

    virtual std::string GetName() const
    { return "PositionMethodFailure_Diagnostic"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        POSITION_METHOD_FAILURE_DIAGNOSTIC_CONGESTION = 0,
        POSITION_METHOD_FAILURE_DIAGNOSTIC_INSUFFICIENT_RESOURCES = 1,
        POSITION_METHOD_FAILURE_DIAGNOSTIC_INSUFFICIENT_MEASUREMENT_DATA = 2,
        POSITION_METHOD_FAILURE_DIAGNOSTIC_INCONSISTENT_MEASUREMENT_DATA = 3,
        POSITION_METHOD_FAILURE_DIAGNOSTIC_LOCATION_PROCEDURE_NOT_COMPLETED = 4,
        POSITION_METHOD_FAILURE_DIAGNOSTIC_LOCATION_PROCEDURE_NOT_SUPPORTED_BY_TARGET_MS = 5,
        POSITION_METHOD_FAILURE_DIAGNOSTIC_QO_S_NOT_ATTAINABLE = 6,
        POSITION_METHOD_FAILURE_DIAGNOSTIC_POSITION_METHOD_NOT_AVAILABLE_IN_NETWORK = 7,
        POSITION_METHOD_FAILURE_DIAGNOSTIC_POSITION_METHOD_NOT_AVAILABLE_IN_LOCATION_AREA = 8

    };

    void SetCongestion()
    { _value = 0; }

    bool IsCongestion() const
    { return _value == 0; }

    void SetInsufficientResources()
    { _value = 1; }

    bool IsInsufficientResources() const
    { return _value == 1; }

    void SetInsufficientMeasurementData()
    { _value = 2; }

    bool IsInsufficientMeasurementData() const
    { return _value == 2; }

    void SetInconsistentMeasurementData()
    { _value = 3; }

    bool IsInconsistentMeasurementData() const
    { return _value == 3; }

    void SetLocationProcedureNotCompleted()
    { _value = 4; }

    bool IsLocationProcedureNotCompleted() const
    { return _value == 4; }

    void SetLocationProcedureNotSupportedByTargetMS()
    { _value = 5; }

    bool IsLocationProcedureNotSupportedByTargetMS() const
    { return _value == 5; }

    void SetQoSNotAttainable()
    { _value = 6; }

    bool IsQoSNotAttainable() const
    { return _value == 6; }

    void SetPositionMethodNotAvailableInNetwork()
    { _value = 7; }

    bool IsPositionMethodNotAvailableInNetwork() const
    { return _value == 7; }

    void SetPositionMethodNotAvailableInLocationArea()
    { _value = 8; }

    bool IsPositionMethodNotAvailableInLocationArea() const
    { return _value == 8; }

};



} // namespace.

#endif    // !defined(_MAP_V13_POSITION_METHOD_FAILURE_DIAGNOSTIC_H_)

