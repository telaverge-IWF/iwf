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


#if !defined(_MAP_V13_ACCESS_RESTRICTION_DATA_H_)
#define _MAP_V13_ACCESS_RESTRICTION_DATA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBitString.h>



namespace map_v13 {



class AccessRestrictionData : public its::AsnBitString
{
public:

    AccessRestrictionData() : its::AsnBitString(false)
    {
        Initialize();
    }

    AccessRestrictionData(const std::vector<bool>& array) : its::AsnBitString(array, false)
    {
        Initialize();
    }

    AccessRestrictionData(its::Octets& octets) : its::AsnBitString(false)
    {
        Initialize();
        Decode(octets);
    }

    AccessRestrictionData(const AccessRestrictionData& rhs) : its::AsnBitString(rhs)
    {
        // Nothing to do.
    }

    AccessRestrictionData(its::AsnDescObject* description) : its::AsnBitString(description)
    {
        // Nothing to do.
    }

    AccessRestrictionData(its::AsnDescObject* description, const std::vector<bool>& array) : its::AsnBitString(description, array)
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

    virtual ~AccessRestrictionData()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AccessRestrictionData(*this);
    }

    virtual std::string GetName() const
    { return "AccessRestrictionData"; }

    void SetHo_toNon3GPP_AccessNotAllowed()
    { Set(5); }

    void ResetHo_toNon3GPP_AccessNotAllowed()
    { Reset(5); }

    bool IsHo_toNon3GPP_AccessNotAllowedSet() const
    { return IsSet(5); }

    bool IsHo_toNon3GPP_AccessNotAllowedDefined() const
    { return 5 < GetSize(); }

    void SetE_utranNotAllowed()
    { Set(4); }

    void ResetE_utranNotAllowed()
    { Reset(4); }

    bool IsE_utranNotAllowedSet() const
    { return IsSet(4); }

    bool IsE_utranNotAllowedDefined() const
    { return 4 < GetSize(); }

    void SetI_hspa_evolutionNotAllowed()
    { Set(3); }

    void ResetI_hspa_evolutionNotAllowed()
    { Reset(3); }

    bool IsI_hspa_evolutionNotAllowedSet() const
    { return IsSet(3); }

    bool IsI_hspa_evolutionNotAllowedDefined() const
    { return 3 < GetSize(); }

    void SetGanNotAllowed()
    { Set(2); }

    void ResetGanNotAllowed()
    { Reset(2); }

    bool IsGanNotAllowedSet() const
    { return IsSet(2); }

    bool IsGanNotAllowedDefined() const
    { return 2 < GetSize(); }

    void SetGeranNotAllowed()
    { Set(1); }

    void ResetGeranNotAllowed()
    { Reset(1); }

    bool IsGeranNotAllowedSet() const
    { return IsSet(1); }

    bool IsGeranNotAllowedDefined() const
    { return 1 < GetSize(); }

    void SetUtranNotAllowed()
    { Set(0); }

    void ResetUtranNotAllowed()
    { Reset(0); }

    bool IsUtranNotAllowedSet() const
    { return IsSet(0); }

    bool IsUtranNotAllowedDefined() const
    { return 0 < GetSize(); }

};



} // namespace.

#endif    // !defined(_MAP_V13_ACCESS_RESTRICTION_DATA_H_)

