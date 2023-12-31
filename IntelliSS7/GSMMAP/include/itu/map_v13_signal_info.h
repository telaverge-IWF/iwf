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


#if !defined(_MAP_V13_SIGNAL_INFO_H_)
#define _MAP_V13_SIGNAL_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v13 {



class SignalInfo : public its::AsnOctetString
{
public:

    SignalInfo() : its::AsnOctetString(false)
    {
        Initialize();
    }

    SignalInfo(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    SignalInfo(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    SignalInfo(const SignalInfo& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    SignalInfo(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    SignalInfo(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~SignalInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SignalInfo(*this);
    }

    virtual std::string GetName() const
    { return "SignalInfo"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_SIGNAL_INFO_H_)

