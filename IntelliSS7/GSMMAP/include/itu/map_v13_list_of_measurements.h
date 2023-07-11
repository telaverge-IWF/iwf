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


#if !defined(_MAP_V13_LIST_OF_MEASUREMENTS_H_)
#define _MAP_V13_LIST_OF_MEASUREMENTS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v13 {



class ListOfMeasurements : public its::AsnOctetString
{
public:

    ListOfMeasurements() : its::AsnOctetString(false)
    {
        Initialize();
    }

    ListOfMeasurements(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    ListOfMeasurements(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    ListOfMeasurements(const ListOfMeasurements& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    ListOfMeasurements(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    ListOfMeasurements(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~ListOfMeasurements()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ListOfMeasurements(*this);
    }

    virtual std::string GetName() const
    { return "ListOfMeasurements"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_LIST_OF_MEASUREMENTS_H_)

