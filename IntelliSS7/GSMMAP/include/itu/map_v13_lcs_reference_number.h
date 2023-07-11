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


#if !defined(_MAP_V13_LCS_REFERENCE_NUMBER_H_)
#define _MAP_V13_LCS_REFERENCE_NUMBER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v13 {



class LCS_ReferenceNumber : public its::AsnOctetString
{
public:

    LCS_ReferenceNumber() : its::AsnOctetString(false)
    {
        Initialize();
    }

    LCS_ReferenceNumber(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    LCS_ReferenceNumber(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    LCS_ReferenceNumber(const LCS_ReferenceNumber& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    LCS_ReferenceNumber(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    LCS_ReferenceNumber(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~LCS_ReferenceNumber()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new LCS_ReferenceNumber(*this);
    }

    virtual std::string GetName() const
    { return "LCS_ReferenceNumber"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_LCS_REFERENCE_NUMBER_H_)

