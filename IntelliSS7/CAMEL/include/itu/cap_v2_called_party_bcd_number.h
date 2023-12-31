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


#if !defined(_CAP_V2_CALLED_PARTY_BCD_NUMBER_H_)
#define _CAP_V2_CALLED_PARTY_BCD_NUMBER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace cap_v2 {



class CalledPartyBCDNumber : public its::AsnOctetString
{
public:

    CalledPartyBCDNumber() : its::AsnOctetString(false)
    {
        Initialize();
    }

    CalledPartyBCDNumber(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    CalledPartyBCDNumber(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    CalledPartyBCDNumber(const CalledPartyBCDNumber& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    CalledPartyBCDNumber(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    CalledPartyBCDNumber(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~CalledPartyBCDNumber()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CalledPartyBCDNumber(*this);
    }

    virtual std::string GetName() const
    { return "CalledPartyBCDNumber"; }

};



} // namespace.

#endif    // !defined(_CAP_V2_CALLED_PARTY_BCD_NUMBER_H_)

