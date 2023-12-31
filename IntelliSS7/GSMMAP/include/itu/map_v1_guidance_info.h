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


#if !defined(_MAP_V1_GUIDANCE_INFO_H_)
#define _MAP_V1_GUIDANCE_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v1 {



class GuidanceInfo : public its::AsnEnumerated
{
public:

    GuidanceInfo() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    GuidanceInfo(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    GuidanceInfo(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    GuidanceInfo(const GuidanceInfo& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    GuidanceInfo(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    GuidanceInfo(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~GuidanceInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new GuidanceInfo(*this);
    }

    virtual std::string GetName() const
    { return "GuidanceInfo"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        GUIDANCE_INFO_GUIDANCE0 = 0,
        GUIDANCE_INFO_GUIDANCE1 = 1,
        GUIDANCE_INFO_GUIDANCE2 = 2,
        GUIDANCE_INFO_GUIDANCE3 = 3,
        GUIDANCE_INFO_GUIDANCE4 = 4

    };

    void SetGuidance0()
    { _value = 0; }

    bool IsGuidance0() const
    { return _value == 0; }

    void SetGuidance1()
    { _value = 1; }

    bool IsGuidance1() const
    { return _value == 1; }

    void SetGuidance2()
    { _value = 2; }

    bool IsGuidance2() const
    { return _value == 2; }

    void SetGuidance3()
    { _value = 3; }

    bool IsGuidance3() const
    { return _value == 3; }

    void SetGuidance4()
    { _value = 4; }

    bool IsGuidance4() const
    { return _value == 4; }

};



} // namespace.

#endif    // !defined(_MAP_V1_GUIDANCE_INFO_H_)

