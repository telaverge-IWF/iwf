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


#if !defined(_INAP_CS2_ATTRIBUTE_TYPE_H_)
#define _INAP_CS2_ATTRIBUTE_TYPE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnObjectIdentifier.h>



namespace inap_cs2 {



class AttributeType : public its::AsnObjectIdentifier
{
public:

    AttributeType() : its::AsnObjectIdentifier(false)
    {
        Initialize();
    }

    AttributeType(const std::vector<long>& array) : its::AsnObjectIdentifier(array, false)
    {
        Initialize();
    }

    AttributeType(its::Octets& octets) : its::AsnObjectIdentifier(false)
    {
        Initialize();
        Decode(octets);
    }

    AttributeType(const AttributeType& rhs) : its::AsnObjectIdentifier(rhs)
    {
        // Nothing to do.
    }

    AttributeType(its::AsnDescObject* description) : its::AsnObjectIdentifier(description)
    {
        // Nothing to do.
    }

    AttributeType(its::AsnDescObject* description, const std::vector<long>& array) : its::AsnObjectIdentifier(description, array)
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

    virtual ~AttributeType()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AttributeType(*this);
    }

    virtual std::string GetName() const
    { return "AttributeType"; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_ATTRIBUTE_TYPE_H_)

