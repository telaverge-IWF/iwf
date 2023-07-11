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


#if !defined(_INAP_CS2_NAME_RESOLUTION_PHASE_H_)
#define _INAP_CS2_NAME_RESOLUTION_PHASE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace inap_cs2 {



class NameResolutionPhase : public its::AsnEnumerated
{
public:

    NameResolutionPhase() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    NameResolutionPhase(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    NameResolutionPhase(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    NameResolutionPhase(const NameResolutionPhase& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    NameResolutionPhase(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    NameResolutionPhase(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~NameResolutionPhase()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new NameResolutionPhase(*this);
    }

    virtual std::string GetName() const
    { return "NameResolutionPhase"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        NAME_RESOLUTION_PHASE_NOT_STARTED = 1,
        NAME_RESOLUTION_PHASE_PROCEEDING = 2,
        NAME_RESOLUTION_PHASE_COMPLETED = 3

    };

    void SetNotStarted()
    { _value = 1; }

    bool IsNotStarted() const
    { return _value == 1; }

    void SetProceeding()
    { _value = 2; }

    bool IsProceeding() const
    { return _value == 2; }

    void SetCompleted()
    { _value = 3; }

    bool IsCompleted() const
    { return _value == 3; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_NAME_RESOLUTION_PHASE_H_)

