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


#if !defined(_MAP_V13_REPORT_INTERVAL_H_)
#define _MAP_V13_REPORT_INTERVAL_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v13 {



class ReportInterval : public its::AsnEnumerated
{
public:

    ReportInterval() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    ReportInterval(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    ReportInterval(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    ReportInterval(const ReportInterval& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    ReportInterval(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    ReportInterval(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~ReportInterval()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ReportInterval(*this);
    }

    virtual std::string GetName() const
    { return "ReportInterval"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        REPORT_INTERVAL_UMTS25_0MS = 0,
        REPORT_INTERVAL_UMTS50_0MS = 1,
        REPORT_INTERVAL_UMTS100_0MS = 2,
        REPORT_INTERVAL_UMTS200_0MS = 3,
        REPORT_INTERVAL_UMTS300_0MS = 4,
        REPORT_INTERVAL_UMTS400_0MS = 5,
        REPORT_INTERVAL_UMTS600_0MS = 6,
        REPORT_INTERVAL_UMTS800_0MS = 7,
        REPORT_INTERVAL_UMTS1200_0MS = 8,
        REPORT_INTERVAL_UMTS1600_0MS = 9,
        REPORT_INTERVAL_UMTS2000_0MS = 10,
        REPORT_INTERVAL_UMTS2400_0MS = 11,
        REPORT_INTERVAL_UMTS2800_0MS = 12,
        REPORT_INTERVAL_UMTS3200_0MS = 13,
        REPORT_INTERVAL_UMTS6400_0MS = 14,
        REPORT_INTERVAL_LTE12_0MS = 15,
        REPORT_INTERVAL_LTE24_0MS = 16,
        REPORT_INTERVAL_LTE48_0MS = 17,
        REPORT_INTERVAL_LTE64_0MS = 18,
        REPORT_INTERVAL_LTE102_4MS = 19,
        REPORT_INTERVAL_LTE204_8MS = 20,
        REPORT_INTERVAL_LTE512_0MS = 21,
        REPORT_INTERVAL_LTE1024_0MS = 22,
        REPORT_INTERVAL_LTE1MIN = 23,
        REPORT_INTERVAL_LTE6MIN = 24,
        REPORT_INTERVAL_LTE1_2MIN = 25,
        REPORT_INTERVAL_LTE3_0MIN = 26,
        REPORT_INTERVAL_LTE6_0MIN = 27

    };

    void SetUmts250ms()
    { _value = 0; }

    bool IsUmts250ms() const
    { return _value == 0; }

    void SetUmts500ms()
    { _value = 1; }

    bool IsUmts500ms() const
    { return _value == 1; }

    void SetUmts1000ms()
    { _value = 2; }

    bool IsUmts1000ms() const
    { return _value == 2; }

    void SetUmts2000ms()
    { _value = 3; }

    bool IsUmts2000ms() const
    { return _value == 3; }

    void SetUmts3000ms()
    { _value = 4; }

    bool IsUmts3000ms() const
    { return _value == 4; }

    void SetUmts4000ms()
    { _value = 5; }

    bool IsUmts4000ms() const
    { return _value == 5; }

    void SetUmts6000ms()
    { _value = 6; }

    bool IsUmts6000ms() const
    { return _value == 6; }

    void SetUmts8000ms()
    { _value = 7; }

    bool IsUmts8000ms() const
    { return _value == 7; }

    void SetUmts12000ms()
    { _value = 8; }

    bool IsUmts12000ms() const
    { return _value == 8; }

    void SetUmts16000ms()
    { _value = 9; }

    bool IsUmts16000ms() const
    { return _value == 9; }

    void SetUmts20000ms()
    { _value = 10; }

    bool IsUmts20000ms() const
    { return _value == 10; }

    void SetUmts24000ms()
    { _value = 11; }

    bool IsUmts24000ms() const
    { return _value == 11; }

    void SetUmts28000ms()
    { _value = 12; }

    bool IsUmts28000ms() const
    { return _value == 12; }

    void SetUmts32000ms()
    { _value = 13; }

    bool IsUmts32000ms() const
    { return _value == 13; }

    void SetUmts64000ms()
    { _value = 14; }

    bool IsUmts64000ms() const
    { return _value == 14; }

    void SetLte120ms()
    { _value = 15; }

    bool IsLte120ms() const
    { return _value == 15; }

    void SetLte240ms()
    { _value = 16; }

    bool IsLte240ms() const
    { return _value == 16; }

    void SetLte480ms()
    { _value = 17; }

    bool IsLte480ms() const
    { return _value == 17; }

    void SetLte640ms()
    { _value = 18; }

    bool IsLte640ms() const
    { return _value == 18; }

    void SetLte1024ms()
    { _value = 19; }

    bool IsLte1024ms() const
    { return _value == 19; }

    void SetLte2048ms()
    { _value = 20; }

    bool IsLte2048ms() const
    { return _value == 20; }

    void SetLte5120ms()
    { _value = 21; }

    bool IsLte5120ms() const
    { return _value == 21; }

    void SetLte10240ms()
    { _value = 22; }

    bool IsLte10240ms() const
    { return _value == 22; }

    void SetLte1min()
    { _value = 23; }

    bool IsLte1min() const
    { return _value == 23; }

    void SetLte6min()
    { _value = 24; }

    bool IsLte6min() const
    { return _value == 24; }

    void SetLte12min()
    { _value = 25; }

    bool IsLte12min() const
    { return _value == 25; }

    void SetLte30min()
    { _value = 26; }

    bool IsLte30min() const
    { return _value == 26; }

    void SetLte60min()
    { _value = 27; }

    bool IsLte60min() const
    { return _value == 27; }

};



} // namespace.

#endif    // !defined(_MAP_V13_REPORT_INTERVAL_H_)
