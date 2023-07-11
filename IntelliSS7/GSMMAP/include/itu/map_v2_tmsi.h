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


#if !defined(_MAP_V2_TMSI_H_)
#define _MAP_V2_TMSI_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v2 {



class TMSI : public its::AsnOctetString
{
public:

    TMSI() : its::AsnOctetString(false)
    {
        Initialize();
    }

    TMSI(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    TMSI(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    TMSI(const TMSI& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    TMSI(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    TMSI(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~TMSI()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new TMSI(*this);
    }

    virtual std::string GetName() const
    { return "TMSI"; }

};



} // namespace.

#endif    // !defined(_MAP_V2_TMSI_H_)

