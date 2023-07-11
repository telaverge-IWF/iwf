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


#if !defined(_MAP_V1_CATEGORY_H_)
#define _MAP_V1_CATEGORY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v1 {



class Category : public its::AsnOctetString
{
public:

    Category() : its::AsnOctetString(false)
    {
        Initialize();
    }

    Category(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    Category(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    Category(const Category& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    Category(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    Category(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~Category()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Category(*this);
    }

    virtual std::string GetName() const
    { return "Category"; }

};



} // namespace.

#endif    // !defined(_MAP_V1_CATEGORY_H_)

