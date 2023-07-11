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


#if !defined(_MAP_V2_NO_REPLY_CONDITION_TIME_H_)
#define _MAP_V2_NO_REPLY_CONDITION_TIME_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v2 {



class NoReplyConditionTime : public its::AsnInteger
{
public:

    NoReplyConditionTime() : its::AsnInteger(false)
    {
        Initialize();
    }

    NoReplyConditionTime(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    NoReplyConditionTime(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    NoReplyConditionTime(const NoReplyConditionTime& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    NoReplyConditionTime(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    NoReplyConditionTime(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~NoReplyConditionTime()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new NoReplyConditionTime(*this);
    }

    virtual std::string GetName() const
    { return "NoReplyConditionTime"; }

};



} // namespace.

#endif    // !defined(_MAP_V2_NO_REPLY_CONDITION_TIME_H_)

