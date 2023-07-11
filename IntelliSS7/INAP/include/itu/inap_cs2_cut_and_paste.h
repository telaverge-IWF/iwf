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


#if !defined(_INAP_CS2_CUT_AND_PASTE_H_)
#define _INAP_CS2_CUT_AND_PASTE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace inap_cs2 {



class CutAndPaste : public its::AsnInteger
{
public:

    CutAndPaste() : its::AsnInteger(false)
    {
        Initialize();
    }

    CutAndPaste(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    CutAndPaste(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    CutAndPaste(const CutAndPaste& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    CutAndPaste(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    CutAndPaste(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~CutAndPaste()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CutAndPaste(*this);
    }

    virtual std::string GetName() const
    { return "CutAndPaste"; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_CUT_AND_PASTE_H_)

