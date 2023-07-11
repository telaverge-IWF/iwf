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


#if !defined(_MAP_V3_EXT_NO_REP_COND_TIME_H_)
#define _MAP_V3_EXT_NO_REP_COND_TIME_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v3 {



class Ext_NoRepCondTime : public its::AsnInteger
{
public:

    Ext_NoRepCondTime() : its::AsnInteger(false)
    {
        Initialize();
    }

    Ext_NoRepCondTime(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    Ext_NoRepCondTime(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    Ext_NoRepCondTime(const Ext_NoRepCondTime& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    Ext_NoRepCondTime(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    Ext_NoRepCondTime(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~Ext_NoRepCondTime()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Ext_NoRepCondTime(*this);
    }

    virtual std::string GetName() const
    { return "Ext_NoRepCondTime"; }

};



} // namespace.

#endif    // !defined(_MAP_V3_EXT_NO_REP_COND_TIME_H_)

