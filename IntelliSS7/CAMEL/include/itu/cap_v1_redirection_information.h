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


#if !defined(_CAP_V1_REDIRECTION_INFORMATION_H_)
#define _CAP_V1_REDIRECTION_INFORMATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace cap_v1 {



class RedirectionInformation : public its::AsnOctetString
{
public:

    RedirectionInformation() : its::AsnOctetString(false)
    {
        Initialize();
    }

    RedirectionInformation(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    RedirectionInformation(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    RedirectionInformation(const RedirectionInformation& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    RedirectionInformation(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    RedirectionInformation(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~RedirectionInformation()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RedirectionInformation(*this);
    }

    virtual std::string GetName() const
    { return "RedirectionInformation"; }

};



} // namespace.

#endif    // !defined(_CAP_V1_REDIRECTION_INFORMATION_H_)

