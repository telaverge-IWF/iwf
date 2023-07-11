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


#if !defined(_MAP_V9_EXT_FORW_OPTIONS_H_)
#define _MAP_V9_EXT_FORW_OPTIONS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v9 {



class Ext_ForwOptions : public its::AsnOctetString
{
public:

    Ext_ForwOptions() : its::AsnOctetString(false)
    {
        Initialize();
    }

    Ext_ForwOptions(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    Ext_ForwOptions(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    Ext_ForwOptions(const Ext_ForwOptions& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    Ext_ForwOptions(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    Ext_ForwOptions(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~Ext_ForwOptions()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Ext_ForwOptions(*this);
    }

    virtual std::string GetName() const
    { return "Ext_ForwOptions"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_EXT_FORW_OPTIONS_H_)

