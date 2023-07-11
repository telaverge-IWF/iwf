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


#if !defined(_MAP_V13_PGW_EVENT_LIST_H_)
#define _MAP_V13_PGW_EVENT_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBitString.h>



namespace map_v13 {



class PGW_EventList : public its::AsnBitString
{
public:

    PGW_EventList() : its::AsnBitString(false)
    {
        Initialize();
    }

    PGW_EventList(const std::vector<bool>& array) : its::AsnBitString(array, false)
    {
        Initialize();
    }

    PGW_EventList(its::Octets& octets) : its::AsnBitString(false)
    {
        Initialize();
        Decode(octets);
    }

    PGW_EventList(const PGW_EventList& rhs) : its::AsnBitString(rhs)
    {
        // Nothing to do.
    }

    PGW_EventList(its::AsnDescObject* description) : its::AsnBitString(description)
    {
        // Nothing to do.
    }

    PGW_EventList(its::AsnDescObject* description, const std::vector<bool>& array) : its::AsnBitString(description, array)
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

    virtual ~PGW_EventList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PGW_EventList(*this);
    }

    virtual std::string GetName() const
    { return "PGW_EventList"; }

    void SetBearerActivationModificationDeletion()
    { Set(2); }

    void ResetBearerActivationModificationDeletion()
    { Reset(2); }

    bool IsBearerActivationModificationDeletionSet() const
    { return IsSet(2); }

    bool IsBearerActivationModificationDeletionDefined() const
    { return 2 < GetSize(); }

    void SetPdn_connectionTermination()
    { Set(1); }

    void ResetPdn_connectionTermination()
    { Reset(1); }

    bool IsPdn_connectionTerminationSet() const
    { return IsSet(1); }

    bool IsPdn_connectionTerminationDefined() const
    { return 1 < GetSize(); }

    void SetPdn_connectionCreation()
    { Set(0); }

    void ResetPdn_connectionCreation()
    { Reset(0); }

    bool IsPdn_connectionCreationSet() const
    { return IsSet(0); }

    bool IsPdn_connectionCreationDefined() const
    { return 0 < GetSize(); }

};



} // namespace.

#endif    // !defined(_MAP_V13_PGW_EVENT_LIST_H_)
