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


#if !defined(_MAP_V13_SM_RP_SMEA_H_)
#define _MAP_V13_SM_RP_SMEA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v13 {



class SM_RP_SMEA : public its::AsnOctetString
{
public:

    SM_RP_SMEA() : its::AsnOctetString(false)
    {
        Initialize();
    }

    SM_RP_SMEA(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    SM_RP_SMEA(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    SM_RP_SMEA(const SM_RP_SMEA& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    SM_RP_SMEA(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    SM_RP_SMEA(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~SM_RP_SMEA()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SM_RP_SMEA(*this);
    }

    virtual std::string GetName() const
    { return "SM_RP_SMEA"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_SM_RP_SMEA_H_)

