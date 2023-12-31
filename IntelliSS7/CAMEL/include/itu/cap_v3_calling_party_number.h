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


#if !defined(_CAP_V3_CALLING_PARTY_NUMBER_H_)
#define _CAP_V3_CALLING_PARTY_NUMBER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace cap_v3 {



class CallingPartyNumber : public its::AsnOctetString
{
public:

    CallingPartyNumber() : its::AsnOctetString(false)
    {
        Initialize();
    }

    CallingPartyNumber(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    CallingPartyNumber(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    CallingPartyNumber(const CallingPartyNumber& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    CallingPartyNumber(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    CallingPartyNumber(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~CallingPartyNumber()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CallingPartyNumber(*this);
    }

    virtual std::string GetName() const
    { return "CallingPartyNumber"; }

};



} // namespace.

#endif    // !defined(_CAP_V3_CALLING_PARTY_NUMBER_H_)

