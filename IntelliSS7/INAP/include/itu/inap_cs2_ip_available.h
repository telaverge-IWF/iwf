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


#if !defined(_INAP_CS2_IP_AVAILABLE_H_)
#define _INAP_CS2_IP_AVAILABLE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace inap_cs2 {



class IPAvailable : public its::AsnOctetString
{
public:

    IPAvailable() : its::AsnOctetString(false)
    {
        Initialize();
    }

    IPAvailable(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    IPAvailable(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    IPAvailable(const IPAvailable& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    IPAvailable(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    IPAvailable(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~IPAvailable()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new IPAvailable(*this);
    }

    virtual std::string GetName() const
    { return "IPAvailable"; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_IP_AVAILABLE_H_)
