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


#if !defined(_MAP_V2_LMSI_H_)
#define _MAP_V2_LMSI_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v2 {



class LMSI : public its::AsnOctetString
{
public:

    LMSI() : its::AsnOctetString(false)
    {
        Initialize();
    }

    LMSI(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    LMSI(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    LMSI(const LMSI& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    LMSI(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    LMSI(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~LMSI()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new LMSI(*this);
    }

    virtual std::string GetName() const
    { return "LMSI"; }

};



} // namespace.

#endif    // !defined(_MAP_V2_LMSI_H_)

