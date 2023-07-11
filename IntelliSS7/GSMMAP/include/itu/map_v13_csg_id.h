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


#if !defined(_MAP_V13_CSG_ID_H_)
#define _MAP_V13_CSG_ID_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBitString.h>



namespace map_v13 {



class CSG_Id : public its::AsnBitString
{
public:

    CSG_Id() : its::AsnBitString(false)
    {
        Initialize();
    }

    CSG_Id(const std::vector<bool>& array) : its::AsnBitString(array, false)
    {
        Initialize();
    }

    CSG_Id(its::Octets& octets) : its::AsnBitString(false)
    {
        Initialize();
        Decode(octets);
    }

    CSG_Id(const CSG_Id& rhs) : its::AsnBitString(rhs)
    {
        // Nothing to do.
    }

    CSG_Id(its::AsnDescObject* description) : its::AsnBitString(description)
    {
        // Nothing to do.
    }

    CSG_Id(its::AsnDescObject* description, const std::vector<bool>& array) : its::AsnBitString(description, array)
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

    virtual ~CSG_Id()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CSG_Id(*this);
    }

    virtual std::string GetName() const
    { return "CSG_Id"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_CSG_ID_H_)

