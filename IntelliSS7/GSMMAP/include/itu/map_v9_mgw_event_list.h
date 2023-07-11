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


#if !defined(_MAP_V9_MGW_EVENT_LIST_H_)
#define _MAP_V9_MGW_EVENT_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBitString.h>



namespace map_v9 {



class MGW_EventList : public its::AsnBitString
{
public:

    MGW_EventList() : its::AsnBitString(false)
    {
        Initialize();
    }

    MGW_EventList(const std::vector<bool>& array) : its::AsnBitString(array, false)
    {
        Initialize();
    }

    MGW_EventList(its::Octets& octets) : its::AsnBitString(false)
    {
        Initialize();
        Decode(octets);
    }

    MGW_EventList(const MGW_EventList& rhs) : its::AsnBitString(rhs)
    {
        // Nothing to do.
    }

    MGW_EventList(its::AsnDescObject* description) : its::AsnBitString(description)
    {
        // Nothing to do.
    }

    MGW_EventList(its::AsnDescObject* description, const std::vector<bool>& array) : its::AsnBitString(description, array)
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

    virtual ~MGW_EventList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MGW_EventList(*this);
    }

    virtual std::string GetName() const
    { return "MGW_EventList"; }

    void SetContext()
    { Set(0); }

    void ResetContext()
    { Reset(0); }

    bool IsContextSet() const
    { return IsSet(0); }

    bool IsContextDefined() const
    { return 0 < GetSize(); }

};



} // namespace.

#endif    // !defined(_MAP_V9_MGW_EVENT_LIST_H_)
