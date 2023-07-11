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


#if !defined(_MAP_V9_MGW_INTERFACE_LIST_H_)
#define _MAP_V9_MGW_INTERFACE_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBitString.h>



namespace map_v9 {



class MGW_InterfaceList : public its::AsnBitString
{
public:

    MGW_InterfaceList() : its::AsnBitString(false)
    {
        Initialize();
    }

    MGW_InterfaceList(const std::vector<bool>& array) : its::AsnBitString(array, false)
    {
        Initialize();
    }

    MGW_InterfaceList(its::Octets& octets) : its::AsnBitString(false)
    {
        Initialize();
        Decode(octets);
    }

    MGW_InterfaceList(const MGW_InterfaceList& rhs) : its::AsnBitString(rhs)
    {
        // Nothing to do.
    }

    MGW_InterfaceList(its::AsnDescObject* description) : its::AsnBitString(description)
    {
        // Nothing to do.
    }

    MGW_InterfaceList(its::AsnDescObject* description, const std::vector<bool>& array) : its::AsnBitString(description, array)
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

    virtual ~MGW_InterfaceList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MGW_InterfaceList(*this);
    }

    virtual std::string GetName() const
    { return "MGW_InterfaceList"; }

    void SetIu_up()
    { Set(2); }

    void ResetIu_up()
    { Reset(2); }

    bool IsIu_upSet() const
    { return IsSet(2); }

    bool IsIu_upDefined() const
    { return 2 < GetSize(); }

    void SetNb_up()
    { Set(1); }

    void ResetNb_up()
    { Reset(1); }

    bool IsNb_upSet() const
    { return IsSet(1); }

    bool IsNb_upDefined() const
    { return 1 < GetSize(); }

    void SetMc()
    { Set(0); }

    void ResetMc()
    { Reset(0); }

    bool IsMcSet() const
    { return IsSet(0); }

    bool IsMcDefined() const
    { return 0 < GetSize(); }

};



} // namespace.

#endif    // !defined(_MAP_V9_MGW_INTERFACE_LIST_H_)

