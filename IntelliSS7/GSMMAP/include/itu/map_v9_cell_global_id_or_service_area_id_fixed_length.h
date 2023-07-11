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


#if !defined(_MAP_V9_CELL_GLOBAL_ID_OR_SERVICE_AREA_ID_FIXED_LENGTH_H_)
#define _MAP_V9_CELL_GLOBAL_ID_OR_SERVICE_AREA_ID_FIXED_LENGTH_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v9 {



class CellGlobalIdOrServiceAreaIdFixedLength : public its::AsnOctetString
{
public:

    CellGlobalIdOrServiceAreaIdFixedLength() : its::AsnOctetString(false)
    {
        Initialize();
    }

    CellGlobalIdOrServiceAreaIdFixedLength(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    CellGlobalIdOrServiceAreaIdFixedLength(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    CellGlobalIdOrServiceAreaIdFixedLength(const CellGlobalIdOrServiceAreaIdFixedLength& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    CellGlobalIdOrServiceAreaIdFixedLength(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    CellGlobalIdOrServiceAreaIdFixedLength(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~CellGlobalIdOrServiceAreaIdFixedLength()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CellGlobalIdOrServiceAreaIdFixedLength(*this);
    }

    virtual std::string GetName() const
    { return "CellGlobalIdOrServiceAreaIdFixedLength"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_CELL_GLOBAL_ID_OR_SERVICE_AREA_ID_FIXED_LENGTH_H_)

