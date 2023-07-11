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


#if !defined(_MAP_V13_ISR_INFORMATION_H_)
#define _MAP_V13_ISR_INFORMATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBitString.h>



namespace map_v13 {



class ISR_Information : public its::AsnBitString
{
public:

    ISR_Information() : its::AsnBitString(false)
    {
        Initialize();
    }

    ISR_Information(const std::vector<bool>& array) : its::AsnBitString(array, false)
    {
        Initialize();
    }

    ISR_Information(its::Octets& octets) : its::AsnBitString(false)
    {
        Initialize();
        Decode(octets);
    }

    ISR_Information(const ISR_Information& rhs) : its::AsnBitString(rhs)
    {
        // Nothing to do.
    }

    ISR_Information(its::AsnDescObject* description) : its::AsnBitString(description)
    {
        // Nothing to do.
    }

    ISR_Information(its::AsnDescObject* description, const std::vector<bool>& array) : its::AsnBitString(description, array)
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

    virtual ~ISR_Information()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ISR_Information(*this);
    }

    virtual std::string GetName() const
    { return "ISR_Information"; }

    void SetInitialAttachIndicator()
    { Set(2); }

    void ResetInitialAttachIndicator()
    { Reset(2); }

    bool IsInitialAttachIndicatorSet() const
    { return IsSet(2); }

    bool IsInitialAttachIndicatorDefined() const
    { return 2 < GetSize(); }

    void SetCancelSGSN()
    { Set(1); }

    void ResetCancelSGSN()
    { Reset(1); }

    bool IsCancelSGSNSet() const
    { return IsSet(1); }

    bool IsCancelSGSNDefined() const
    { return 1 < GetSize(); }

    void SetUpdateMME()
    { Set(0); }

    void ResetUpdateMME()
    { Reset(0); }

    bool IsUpdateMMESet() const
    { return IsSet(0); }

    bool IsUpdateMMEDefined() const
    { return 0 < GetSize(); }

};



} // namespace.

#endif    // !defined(_MAP_V13_ISR_INFORMATION_H_)

