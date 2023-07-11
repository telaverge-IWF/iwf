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


#if !defined(_MAP_V13_CODEC_H_)
#define _MAP_V13_CODEC_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v13 {



class Codec : public its::AsnOctetString
{
public:

    Codec() : its::AsnOctetString(false)
    {
        Initialize();
    }

    Codec(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    Codec(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    Codec(const Codec& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    Codec(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    Codec(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~Codec()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Codec(*this);
    }

    virtual std::string GetName() const
    { return "Codec"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_CODEC_H_)

