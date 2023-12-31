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


#if !defined(_MAP_V13_BMSC_EVENT_LIST_H_)
#define _MAP_V13_BMSC_EVENT_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBitString.h>



namespace map_v13 {



class BMSC_EventList : public its::AsnBitString
{
public:

    BMSC_EventList() : its::AsnBitString(false)
    {
        Initialize();
    }

    BMSC_EventList(const std::vector<bool>& array) : its::AsnBitString(array, false)
    {
        Initialize();
    }

    BMSC_EventList(its::Octets& octets) : its::AsnBitString(false)
    {
        Initialize();
        Decode(octets);
    }

    BMSC_EventList(const BMSC_EventList& rhs) : its::AsnBitString(rhs)
    {
        // Nothing to do.
    }

    BMSC_EventList(its::AsnDescObject* description) : its::AsnBitString(description)
    {
        // Nothing to do.
    }

    BMSC_EventList(its::AsnDescObject* description, const std::vector<bool>& array) : its::AsnBitString(description, array)
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

    virtual ~BMSC_EventList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new BMSC_EventList(*this);
    }

    virtual std::string GetName() const
    { return "BMSC_EventList"; }

    void SetMbmsMulticastServiceActivation()
    { Set(0); }

    void ResetMbmsMulticastServiceActivation()
    { Reset(0); }

    bool IsMbmsMulticastServiceActivationSet() const
    { return IsSet(0); }

    bool IsMbmsMulticastServiceActivationDefined() const
    { return 0 < GetSize(); }

};



} // namespace.

#endif    // !defined(_MAP_V13_BMSC_EVENT_LIST_H_)

