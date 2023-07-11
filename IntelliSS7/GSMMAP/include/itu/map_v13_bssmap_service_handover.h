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


#if !defined(_MAP_V13_BSSMAP_SERVICE_HANDOVER_H_)
#define _MAP_V13_BSSMAP_SERVICE_HANDOVER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v13 {



class BSSMAP_ServiceHandover : public its::AsnOctetString
{
public:

    BSSMAP_ServiceHandover() : its::AsnOctetString(false)
    {
        Initialize();
    }

    BSSMAP_ServiceHandover(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    BSSMAP_ServiceHandover(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    BSSMAP_ServiceHandover(const BSSMAP_ServiceHandover& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    BSSMAP_ServiceHandover(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    BSSMAP_ServiceHandover(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~BSSMAP_ServiceHandover()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new BSSMAP_ServiceHandover(*this);
    }

    virtual std::string GetName() const
    { return "BSSMAP_ServiceHandover"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_BSSMAP_SERVICE_HANDOVER_H_)
