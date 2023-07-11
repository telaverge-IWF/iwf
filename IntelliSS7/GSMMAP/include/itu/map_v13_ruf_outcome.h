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


#if !defined(_MAP_V13_RUF_OUTCOME_H_)
#define _MAP_V13_RUF_OUTCOME_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v13 {



class RUF_Outcome : public its::AsnEnumerated
{
public:

    RUF_Outcome() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    RUF_Outcome(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    RUF_Outcome(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    RUF_Outcome(const RUF_Outcome& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    RUF_Outcome(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    RUF_Outcome(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~RUF_Outcome()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RUF_Outcome(*this);
    }

    virtual std::string GetName() const
    { return "RUF_Outcome"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        RUF_OUTCOME_ACCEPTED = 0,
        RUF_OUTCOME_REJECTED = 1,
        RUF_OUTCOME_NO_RESPONSE_FROM_FREE_MS = 2,
        RUF_OUTCOME_NO_RESPONSE_FROM_BUSY_MS = 3,
        RUF_OUTCOME_UDUB_FROM_FREE_MS = 4,
        RUF_OUTCOME_UDUB_FROM_BUSY_MS = 5

    };

    void SetAccepted()
    { _value = 0; }

    bool IsAccepted() const
    { return _value == 0; }

    void SetRejected()
    { _value = 1; }

    bool IsRejected() const
    { return _value == 1; }

    void SetNoResponseFromFreeMS()
    { _value = 2; }

    bool IsNoResponseFromFreeMS() const
    { return _value == 2; }

    void SetNoResponseFromBusyMS()
    { _value = 3; }

    bool IsNoResponseFromBusyMS() const
    { return _value == 3; }

    void SetUdubFromFreeMS()
    { _value = 4; }

    bool IsUdubFromFreeMS() const
    { return _value == 4; }

    void SetUdubFromBusyMS()
    { _value = 5; }

    bool IsUdubFromBusyMS() const
    { return _value == 5; }

};



} // namespace.

#endif    // !defined(_MAP_V13_RUF_OUTCOME_H_)

