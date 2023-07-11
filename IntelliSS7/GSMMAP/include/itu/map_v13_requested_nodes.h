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


#if !defined(_MAP_V13_REQUESTED_NODES_H_)
#define _MAP_V13_REQUESTED_NODES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBitString.h>



namespace map_v13 {



class RequestedNodes : public its::AsnBitString
{
public:

    RequestedNodes() : its::AsnBitString(false)
    {
        Initialize();
    }

    RequestedNodes(const std::vector<bool>& array) : its::AsnBitString(array, false)
    {
        Initialize();
    }

    RequestedNodes(its::Octets& octets) : its::AsnBitString(false)
    {
        Initialize();
        Decode(octets);
    }

    RequestedNodes(const RequestedNodes& rhs) : its::AsnBitString(rhs)
    {
        // Nothing to do.
    }

    RequestedNodes(its::AsnDescObject* description) : its::AsnBitString(description)
    {
        // Nothing to do.
    }

    RequestedNodes(its::AsnDescObject* description, const std::vector<bool>& array) : its::AsnBitString(description, array)
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

    virtual ~RequestedNodes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RequestedNodes(*this);
    }

    virtual std::string GetName() const
    { return "RequestedNodes"; }

    void SetSgsn()
    { Set(1); }

    void ResetSgsn()
    { Reset(1); }

    bool IsSgsnSet() const
    { return IsSet(1); }

    bool IsSgsnDefined() const
    { return 1 < GetSize(); }

    void SetMme()
    { Set(0); }

    void ResetMme()
    { Reset(0); }

    bool IsMmeSet() const
    { return IsSet(0); }

    bool IsMmeDefined() const
    { return 0 < GetSize(); }

};



} // namespace.

#endif    // !defined(_MAP_V13_REQUESTED_NODES_H_)
