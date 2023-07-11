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


#if !defined(_MAP_V9_EQUIPMENT_STATUS_H_)
#define _MAP_V9_EQUIPMENT_STATUS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v9 {



class EquipmentStatus : public its::AsnEnumerated
{
public:

    EquipmentStatus() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    EquipmentStatus(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    EquipmentStatus(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    EquipmentStatus(const EquipmentStatus& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    EquipmentStatus(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    EquipmentStatus(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~EquipmentStatus()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new EquipmentStatus(*this);
    }

    virtual std::string GetName() const
    { return "EquipmentStatus"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        EQUIPMENT_STATUS_WHITE_LISTED = 0,
        EQUIPMENT_STATUS_BLACK_LISTED = 1,
        EQUIPMENT_STATUS_GREY_LISTED = 2

    };

    void SetWhiteListed()
    { _value = 0; }

    bool IsWhiteListed() const
    { return _value == 0; }

    void SetBlackListed()
    { _value = 1; }

    bool IsBlackListed() const
    { return _value == 1; }

    void SetGreyListed()
    { _value = 2; }

    bool IsGreyListed() const
    { return _value == 2; }

};



} // namespace.

#endif    // !defined(_MAP_V9_EQUIPMENT_STATUS_H_)

