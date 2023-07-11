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


#if !defined(_MAP_V9_INITIALISATION_VECTOR_H_)
#define _MAP_V9_INITIALISATION_VECTOR_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v9 {



class InitialisationVector : public its::AsnOctetString
{
public:

    InitialisationVector() : its::AsnOctetString(false)
    {
        Initialize();
    }

    InitialisationVector(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    InitialisationVector(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    InitialisationVector(const InitialisationVector& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    InitialisationVector(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    InitialisationVector(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~InitialisationVector()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InitialisationVector(*this);
    }

    virtual std::string GetName() const
    { return "InitialisationVector"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_INITIALISATION_VECTOR_H_)

