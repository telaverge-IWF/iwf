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


#if !defined(_MAP_V2_USSD_STRING_H_)
#define _MAP_V2_USSD_STRING_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v2 {



class USSD_String : public its::AsnOctetString
{
public:

    USSD_String() : its::AsnOctetString(false)
    {
        Initialize();
    }

    USSD_String(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    USSD_String(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    USSD_String(const USSD_String& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    USSD_String(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    USSD_String(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~USSD_String()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new USSD_String(*this);
    }

    virtual std::string GetName() const
    { return "USSD_String"; }

};



} // namespace.

#endif    // !defined(_MAP_V2_USSD_STRING_H_)

