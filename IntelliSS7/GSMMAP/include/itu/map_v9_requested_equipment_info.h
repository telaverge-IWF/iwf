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


#if !defined(_MAP_V9_REQUESTED_EQUIPMENT_INFO_H_)
#define _MAP_V9_REQUESTED_EQUIPMENT_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBitString.h>



namespace map_v9 {



class RequestedEquipmentInfo : public its::AsnBitString
{
public:

    RequestedEquipmentInfo() : its::AsnBitString(false)
    {
        Initialize();
    }

    RequestedEquipmentInfo(const std::vector<bool>& array) : its::AsnBitString(array, false)
    {
        Initialize();
    }

    RequestedEquipmentInfo(its::Octets& octets) : its::AsnBitString(false)
    {
        Initialize();
        Decode(octets);
    }

    RequestedEquipmentInfo(const RequestedEquipmentInfo& rhs) : its::AsnBitString(rhs)
    {
        // Nothing to do.
    }

    RequestedEquipmentInfo(its::AsnDescObject* description) : its::AsnBitString(description)
    {
        // Nothing to do.
    }

    RequestedEquipmentInfo(its::AsnDescObject* description, const std::vector<bool>& array) : its::AsnBitString(description, array)
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

    virtual ~RequestedEquipmentInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RequestedEquipmentInfo(*this);
    }

    virtual std::string GetName() const
    { return "RequestedEquipmentInfo"; }

    void SetBmuef()
    { Set(1); }

    void ResetBmuef()
    { Reset(1); }

    bool IsBmuefSet() const
    { return IsSet(1); }

    bool IsBmuefDefined() const
    { return 1 < GetSize(); }

    void SetEquipmentStatus()
    { Set(0); }

    void ResetEquipmentStatus()
    { Reset(0); }

    bool IsEquipmentStatusSet() const
    { return IsSet(0); }

    bool IsEquipmentStatusDefined() const
    { return 0 < GetSize(); }

};



} // namespace.

#endif    // !defined(_MAP_V9_REQUESTED_EQUIPMENT_INFO_H_)
