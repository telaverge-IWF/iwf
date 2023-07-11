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


#if !defined(_CAP_V3_TASK_REFUSED_H_)
#define _CAP_V3_TASK_REFUSED_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace cap_v3 {



class TaskRefused : public its::AsnEnumerated
{
public:

    TaskRefused() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    TaskRefused(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    TaskRefused(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    TaskRefused(const TaskRefused& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    TaskRefused(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    TaskRefused(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~TaskRefused()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new TaskRefused(*this);
    }

    virtual std::string GetName() const
    { return "TaskRefused"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        TASK_REFUSED_GENERIC = 0,
        TASK_REFUSED_UNOBTAINABLE = 1,
        TASK_REFUSED_CONGESTION = 2

    };

    void SetGeneric()
    { _value = 0; }

    bool IsGeneric() const
    { return _value == 0; }

    void SetUnobtainable()
    { _value = 1; }

    bool IsUnobtainable() const
    { return _value == 1; }

    void SetCongestion()
    { _value = 2; }

    bool IsCongestion() const
    { return _value == 2; }

};



} // namespace.

#endif    // !defined(_CAP_V3_TASK_REFUSED_H_)
