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


#if !defined(_MAP_V1_EQUIP_STATUS_H_)
#define _MAP_V1_EQUIP_STATUS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v1 {



class EquipStatus : public its::AsnEnumerated
{
public:

    EquipStatus() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    EquipStatus(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    EquipStatus(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    EquipStatus(const EquipStatus& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    EquipStatus(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    EquipStatus(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~EquipStatus()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new EquipStatus(*this);
    }

    virtual std::string GetName() const
    { return "EquipStatus"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        EQUIP_STATUS_WHITE_LISTED = 0,
        EQUIP_STATUS_BLACK_LISTED = 1,
        EQUIP_STATUS_GREY_LISTED = 2

    };

    void SetWhite_listed()
    { _value = 0; }

    bool IsWhite_listed() const
    { return _value == 0; }

    void SetBlack_listed()
    { _value = 1; }

    bool IsBlack_listed() const
    { return _value == 1; }

    void SetGrey_listed()
    { _value = 2; }

    bool IsGrey_listed() const
    { return _value == 2; }

};



} // namespace.

#endif    // !defined(_MAP_V1_EQUIP_STATUS_H_)
