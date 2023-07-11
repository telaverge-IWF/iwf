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


#if !defined(_MAP_V3_CUG_INTERLOCK_H_)
#define _MAP_V3_CUG_INTERLOCK_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v3 {



class CUG_Interlock : public its::AsnOctetString
{
public:

    CUG_Interlock() : its::AsnOctetString(false)
    {
        Initialize();
    }

    CUG_Interlock(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    CUG_Interlock(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    CUG_Interlock(const CUG_Interlock& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    CUG_Interlock(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    CUG_Interlock(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~CUG_Interlock()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CUG_Interlock(*this);
    }

    virtual std::string GetName() const
    { return "CUG_Interlock"; }

};



} // namespace.

#endif    // !defined(_MAP_V3_CUG_INTERLOCK_H_)

