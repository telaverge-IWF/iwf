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


#if !defined(_MAP_V9_APN_H_)
#define _MAP_V9_APN_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v9 {



class APN : public its::AsnOctetString
{
public:

    APN() : its::AsnOctetString(false)
    {
        Initialize();
    }

    APN(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    APN(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    APN(const APN& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    APN(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    APN(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~APN()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new APN(*this);
    }

    virtual std::string GetName() const
    { return "APN"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_APN_H_)

