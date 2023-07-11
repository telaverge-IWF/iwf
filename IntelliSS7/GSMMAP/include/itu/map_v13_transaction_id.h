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


#if !defined(_MAP_V13_TRANSACTION_ID_H_)
#define _MAP_V13_TRANSACTION_ID_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v13 {



class TransactionId : public its::AsnOctetString
{
public:

    TransactionId() : its::AsnOctetString(false)
    {
        Initialize();
    }

    TransactionId(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    TransactionId(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    TransactionId(const TransactionId& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    TransactionId(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    TransactionId(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~TransactionId()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new TransactionId(*this);
    }

    virtual std::string GetName() const
    { return "TransactionId"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_TRANSACTION_ID_H_)

