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


#if !defined(_MAP_V9_MM_CODE_H_)
#define _MAP_V9_MM_CODE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v9 {



class MM_Code : public its::AsnOctetString
{
public:

    MM_Code() : its::AsnOctetString(false)
    {
        Initialize();
    }

    MM_Code(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    MM_Code(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    MM_Code(const MM_Code& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    MM_Code(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    MM_Code(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~MM_Code()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MM_Code(*this);
    }

    virtual std::string GetName() const
    { return "MM_Code"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_MM_CODE_H_)

