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


#if !defined(_MAP_V13_LOGGING_INTERVAL_H_)
#define _MAP_V13_LOGGING_INTERVAL_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v13 {



class LoggingInterval : public its::AsnEnumerated
{
public:

    LoggingInterval() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    LoggingInterval(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    LoggingInterval(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    LoggingInterval(const LoggingInterval& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    LoggingInterval(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    LoggingInterval(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~LoggingInterval()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new LoggingInterval(*this);
    }

    virtual std::string GetName() const
    { return "LoggingInterval"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        LOGGING_INTERVAL_D1DOT28 = 0,
        LOGGING_INTERVAL_D2DOT56 = 1,
        LOGGING_INTERVAL_D5DOT12 = 2,
        LOGGING_INTERVAL_D1_0DOT24 = 3,
        LOGGING_INTERVAL_D2_0DOT48 = 4,
        LOGGING_INTERVAL_D3_0DOT72 = 5,
        LOGGING_INTERVAL_D4_0DOT96 = 6,
        LOGGING_INTERVAL_D6_1DOT44 = 7

    };

    void SetD1dot28()
    { _value = 0; }

    bool IsD1dot28() const
    { return _value == 0; }

    void SetD2dot56()
    { _value = 1; }

    bool IsD2dot56() const
    { return _value == 1; }

    void SetD5dot12()
    { _value = 2; }

    bool IsD5dot12() const
    { return _value == 2; }

    void SetD10dot24()
    { _value = 3; }

    bool IsD10dot24() const
    { return _value == 3; }

    void SetD20dot48()
    { _value = 4; }

    bool IsD20dot48() const
    { return _value == 4; }

    void SetD30dot72()
    { _value = 5; }

    bool IsD30dot72() const
    { return _value == 5; }

    void SetD40dot96()
    { _value = 6; }

    bool IsD40dot96() const
    { return _value == 6; }

    void SetD61dot44()
    { _value = 7; }

    bool IsD61dot44() const
    { return _value == 7; }

};



} // namespace.

#endif    // !defined(_MAP_V13_LOGGING_INTERVAL_H_)
