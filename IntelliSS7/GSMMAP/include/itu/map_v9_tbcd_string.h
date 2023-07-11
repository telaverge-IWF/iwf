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


#if !defined(_MAP_V9_TBCD_STRING_H_)
#define _MAP_V9_TBCD_STRING_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v9 {



class TBCD_STRING : public its::AsnOctetString
{
public:

    TBCD_STRING() : its::AsnOctetString(false)
    {
        Initialize();
    }

    TBCD_STRING(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    TBCD_STRING(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    TBCD_STRING(const TBCD_STRING& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    TBCD_STRING(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    TBCD_STRING(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~TBCD_STRING()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new TBCD_STRING(*this);
    }

    virtual std::string GetName() const
    { return "TBCD_STRING"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_TBCD_STRING_H_)

