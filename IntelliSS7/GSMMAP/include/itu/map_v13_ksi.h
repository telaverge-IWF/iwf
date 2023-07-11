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


#if !defined(_MAP_V13_KSI_H_)
#define _MAP_V13_KSI_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v13 {



class KSI : public its::AsnOctetString
{
public:

    KSI() : its::AsnOctetString(false)
    {
        Initialize();
    }

    KSI(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    KSI(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    KSI(const KSI& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    KSI(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    KSI(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~KSI()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new KSI(*this);
    }

    virtual std::string GetName() const
    { return "KSI"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_KSI_H_)

