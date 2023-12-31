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


#if !defined(_MAP_V9_GGSN_INTERFACE_LIST_H_)
#define _MAP_V9_GGSN_INTERFACE_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBitString.h>



namespace map_v9 {



class GGSN_InterfaceList : public its::AsnBitString
{
public:

    GGSN_InterfaceList() : its::AsnBitString(false)
    {
        Initialize();
    }

    GGSN_InterfaceList(const std::vector<bool>& array) : its::AsnBitString(array, false)
    {
        Initialize();
    }

    GGSN_InterfaceList(its::Octets& octets) : its::AsnBitString(false)
    {
        Initialize();
        Decode(octets);
    }

    GGSN_InterfaceList(const GGSN_InterfaceList& rhs) : its::AsnBitString(rhs)
    {
        // Nothing to do.
    }

    GGSN_InterfaceList(its::AsnDescObject* description) : its::AsnBitString(description)
    {
        // Nothing to do.
    }

    GGSN_InterfaceList(its::AsnDescObject* description, const std::vector<bool>& array) : its::AsnBitString(description, array)
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

    virtual ~GGSN_InterfaceList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new GGSN_InterfaceList(*this);
    }

    virtual std::string GetName() const
    { return "GGSN_InterfaceList"; }

    void SetGmb()
    { Set(2); }

    void ResetGmb()
    { Reset(2); }

    bool IsGmbSet() const
    { return IsSet(2); }

    bool IsGmbDefined() const
    { return 2 < GetSize(); }

    void SetGi()
    { Set(1); }

    void ResetGi()
    { Reset(1); }

    bool IsGiSet() const
    { return IsSet(1); }

    bool IsGiDefined() const
    { return 1 < GetSize(); }

    void SetGn()
    { Set(0); }

    void ResetGn()
    { Reset(0); }

    bool IsGnSet() const
    { return IsSet(0); }

    bool IsGnDefined() const
    { return 0 < GetSize(); }

};



} // namespace.

#endif    // !defined(_MAP_V9_GGSN_INTERFACE_LIST_H_)

