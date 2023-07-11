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


#if !defined(_MAP_V9_MT_SMS_TPDU_TYPE_H_)
#define _MAP_V9_MT_SMS_TPDU_TYPE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v9 {



class MT_SMS_TPDU_Type : public its::AsnEnumerated
{
public:

    MT_SMS_TPDU_Type() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    MT_SMS_TPDU_Type(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    MT_SMS_TPDU_Type(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    MT_SMS_TPDU_Type(const MT_SMS_TPDU_Type& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    MT_SMS_TPDU_Type(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    MT_SMS_TPDU_Type(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~MT_SMS_TPDU_Type()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MT_SMS_TPDU_Type(*this);
    }

    virtual std::string GetName() const
    { return "MT_SMS_TPDU_Type"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        MT_SMS_TPDU_TYPE_SMS_DELIVER = 0,
        MT_SMS_TPDU_TYPE_SMS_SUBMIT_REPORT = 1,
        MT_SMS_TPDU_TYPE_SMS_STATUS_REPORT = 2

    };

    void SetSms_DELIVER()
    { _value = 0; }

    bool IsSms_DELIVER() const
    { return _value == 0; }

    void SetSms_SUBMIT_REPORT()
    { _value = 1; }

    bool IsSms_SUBMIT_REPORT() const
    { return _value == 1; }

    void SetSms_STATUS_REPORT()
    { _value = 2; }

    bool IsSms_STATUS_REPORT() const
    { return _value == 2; }

};



} // namespace.

#endif    // !defined(_MAP_V9_MT_SMS_TPDU_TYPE_H_)
