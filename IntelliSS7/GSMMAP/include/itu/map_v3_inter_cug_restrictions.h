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


#if !defined(_MAP_V3_INTER_CUG_RESTRICTIONS_H_)
#define _MAP_V3_INTER_CUG_RESTRICTIONS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v3 {



class InterCUG_Restrictions : public its::AsnOctetString
{
public:

    InterCUG_Restrictions() : its::AsnOctetString(false)
    {
        Initialize();
    }

    InterCUG_Restrictions(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    InterCUG_Restrictions(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    InterCUG_Restrictions(const InterCUG_Restrictions& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    InterCUG_Restrictions(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    InterCUG_Restrictions(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~InterCUG_Restrictions()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InterCUG_Restrictions(*this);
    }

    virtual std::string GetName() const
    { return "InterCUG_Restrictions"; }

};



} // namespace.

#endif    // !defined(_MAP_V3_INTER_CUG_RESTRICTIONS_H_)
