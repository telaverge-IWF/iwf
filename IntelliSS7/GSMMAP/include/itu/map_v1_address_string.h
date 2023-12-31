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


#if !defined(_MAP_V1_ADDRESS_STRING_H_)
#define _MAP_V1_ADDRESS_STRING_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v1 {



class AddressString : public its::AsnOctetString
{
public:

    AddressString() : its::AsnOctetString(false)
    {
        Initialize();
    }

    AddressString(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    AddressString(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    AddressString(const AddressString& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    AddressString(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    AddressString(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~AddressString()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AddressString(*this);
    }

    virtual std::string GetName() const
    { return "AddressString"; }

};



} // namespace.

#endif    // !defined(_MAP_V1_ADDRESS_STRING_H_)

