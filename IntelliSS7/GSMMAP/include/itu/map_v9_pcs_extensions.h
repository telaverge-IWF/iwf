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


#if !defined(_MAP_V9_PCS_EXTENSIONS_H_)
#define _MAP_V9_PCS_EXTENSIONS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>



namespace map_v9 {



class PCS_Extensions : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


////////// End Nested Class(es) //////////

    PCS_Extensions() : its::AsnSequence(0, false)
    {
        Initialize();
    }

    PCS_Extensions(its::Octets& octets) : its::AsnSequence(0, false)
    {
        Initialize();
        Decode(octets);
    }

    PCS_Extensions(const PCS_Extensions& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    PCS_Extensions(its::AsnDescObject* description) : its::AsnSequence(0, description)
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

    virtual ~PCS_Extensions()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PCS_Extensions(*this);
    }

    virtual std::string GetName() const
    { return "PCS_Extensions"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_PCS_EXTENSIONS_H_)
