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


#if !defined(_MAP_V13_SUPPRESS_MTSS_H_)
#define _MAP_V13_SUPPRESS_MTSS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBitString.h>



namespace map_v13 {



class SuppressMTSS : public its::AsnBitString
{
public:

    SuppressMTSS() : its::AsnBitString(false)
    {
        Initialize();
    }

    SuppressMTSS(const std::vector<bool>& array) : its::AsnBitString(array, false)
    {
        Initialize();
    }

    SuppressMTSS(its::Octets& octets) : its::AsnBitString(false)
    {
        Initialize();
        Decode(octets);
    }

    SuppressMTSS(const SuppressMTSS& rhs) : its::AsnBitString(rhs)
    {
        // Nothing to do.
    }

    SuppressMTSS(its::AsnDescObject* description) : its::AsnBitString(description)
    {
        // Nothing to do.
    }

    SuppressMTSS(its::AsnDescObject* description, const std::vector<bool>& array) : its::AsnBitString(description, array)
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

    virtual ~SuppressMTSS()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SuppressMTSS(*this);
    }

    virtual std::string GetName() const
    { return "SuppressMTSS"; }

    void SetSuppressCCBS()
    { Set(1); }

    void ResetSuppressCCBS()
    { Reset(1); }

    bool IsSuppressCCBSSet() const
    { return IsSet(1); }

    bool IsSuppressCCBSDefined() const
    { return 1 < GetSize(); }

    void SetSuppressCUG()
    { Set(0); }

    void ResetSuppressCUG()
    { Reset(0); }

    bool IsSuppressCUGSet() const
    { return IsSet(0); }

    bool IsSuppressCUGDefined() const
    { return 0 < GetSize(); }

};



} // namespace.

#endif    // !defined(_MAP_V13_SUPPRESS_MTSS_H_)

