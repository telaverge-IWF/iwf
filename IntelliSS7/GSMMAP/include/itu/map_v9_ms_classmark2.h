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


#if !defined(_MAP_V9_MS_CLASSMARK2_H_)
#define _MAP_V9_MS_CLASSMARK2_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v9 {



class MS_Classmark2 : public its::AsnOctetString
{
public:

    MS_Classmark2() : its::AsnOctetString(false)
    {
        Initialize();
    }

    MS_Classmark2(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    MS_Classmark2(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    MS_Classmark2(const MS_Classmark2& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    MS_Classmark2(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    MS_Classmark2(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~MS_Classmark2()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MS_Classmark2(*this);
    }

    virtual std::string GetName() const
    { return "MS_Classmark2"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_MS_CLASSMARK2_H_)

