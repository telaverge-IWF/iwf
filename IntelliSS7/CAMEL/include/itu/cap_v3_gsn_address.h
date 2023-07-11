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


#if !defined(_CAP_V3_GSN_ADDRESS_H_)
#define _CAP_V3_GSN_ADDRESS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace cap_v3 {



class GSN_Address : public its::AsnOctetString
{
public:

    GSN_Address() : its::AsnOctetString(false)
    {
        Initialize();
    }

    GSN_Address(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    GSN_Address(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    GSN_Address(const GSN_Address& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    GSN_Address(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    GSN_Address(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~GSN_Address()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new GSN_Address(*this);
    }

    virtual std::string GetName() const
    { return "GSN_Address"; }

};



} // namespace.

#endif    // !defined(_CAP_V3_GSN_ADDRESS_H_)

