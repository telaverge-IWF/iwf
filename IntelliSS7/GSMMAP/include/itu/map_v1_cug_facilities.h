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


#if !defined(_MAP_V1_CUG_FACILITIES_H_)
#define _MAP_V1_CUG_FACILITIES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v1 {



class CUG_Facilities : public its::AsnOctetString
{
public:

    CUG_Facilities() : its::AsnOctetString(false)
    {
        Initialize();
    }

    CUG_Facilities(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    CUG_Facilities(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    CUG_Facilities(const CUG_Facilities& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    CUG_Facilities(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    CUG_Facilities(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~CUG_Facilities()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CUG_Facilities(*this);
    }

    virtual std::string GetName() const
    { return "CUG_Facilities"; }

};



} // namespace.

#endif    // !defined(_MAP_V1_CUG_FACILITIES_H_)
