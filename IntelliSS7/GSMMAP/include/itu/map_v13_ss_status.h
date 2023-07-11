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


#if !defined(_MAP_V13_SS_STATUS_H_)
#define _MAP_V13_SS_STATUS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v13 {



class SS_Status : public its::AsnOctetString
{
public:

    SS_Status() : its::AsnOctetString(false)
    {
        Initialize();
    }

    SS_Status(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    SS_Status(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    SS_Status(const SS_Status& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    SS_Status(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    SS_Status(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~SS_Status()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SS_Status(*this);
    }

    virtual std::string GetName() const
    { return "SS_Status"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_SS_STATUS_H_)
