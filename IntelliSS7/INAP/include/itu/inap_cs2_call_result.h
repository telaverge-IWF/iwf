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


#if !defined(_INAP_CS2_CALL_RESULT_H_)
#define _INAP_CS2_CALL_RESULT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace inap_cs2 {



class CallResult : public its::AsnOctetString
{
public:

    CallResult() : its::AsnOctetString(false)
    {
        Initialize();
    }

    CallResult(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    CallResult(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    CallResult(const CallResult& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    CallResult(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    CallResult(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~CallResult()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CallResult(*this);
    }

    virtual std::string GetName() const
    { return "CallResult"; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_CALL_RESULT_H_)
