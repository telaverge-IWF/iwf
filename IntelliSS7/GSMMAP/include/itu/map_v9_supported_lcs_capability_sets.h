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


#if !defined(_MAP_V9_SUPPORTED_LCS_CAPABILITY_SETS_H_)
#define _MAP_V9_SUPPORTED_LCS_CAPABILITY_SETS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBitString.h>



namespace map_v9 {



class SupportedLCS_CapabilitySets : public its::AsnBitString
{
public:

    SupportedLCS_CapabilitySets() : its::AsnBitString(false)
    {
        Initialize();
    }

    SupportedLCS_CapabilitySets(const std::vector<bool>& array) : its::AsnBitString(array, false)
    {
        Initialize();
    }

    SupportedLCS_CapabilitySets(its::Octets& octets) : its::AsnBitString(false)
    {
        Initialize();
        Decode(octets);
    }

    SupportedLCS_CapabilitySets(const SupportedLCS_CapabilitySets& rhs) : its::AsnBitString(rhs)
    {
        // Nothing to do.
    }

    SupportedLCS_CapabilitySets(its::AsnDescObject* description) : its::AsnBitString(description)
    {
        // Nothing to do.
    }

    SupportedLCS_CapabilitySets(its::AsnDescObject* description, const std::vector<bool>& array) : its::AsnBitString(description, array)
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

    virtual ~SupportedLCS_CapabilitySets()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SupportedLCS_CapabilitySets(*this);
    }

    virtual std::string GetName() const
    { return "SupportedLCS_CapabilitySets"; }

    void SetLcsCapabilitySet3()
    { Set(2); }

    void ResetLcsCapabilitySet3()
    { Reset(2); }

    bool IsLcsCapabilitySet3Set() const
    { return IsSet(2); }

    bool IsLcsCapabilitySet3Defined() const
    { return 2 < GetSize(); }

    void SetLcsCapabilitySet2()
    { Set(1); }

    void ResetLcsCapabilitySet2()
    { Reset(1); }

    bool IsLcsCapabilitySet2Set() const
    { return IsSet(1); }

    bool IsLcsCapabilitySet2Defined() const
    { return 1 < GetSize(); }

    void SetLcsCapabilitySet1()
    { Set(0); }

    void ResetLcsCapabilitySet1()
    { Reset(0); }

    bool IsLcsCapabilitySet1Set() const
    { return IsSet(0); }

    bool IsLcsCapabilitySet1Defined() const
    { return 0 < GetSize(); }

};



} // namespace.

#endif    // !defined(_MAP_V9_SUPPORTED_LCS_CAPABILITY_SETS_H_)

