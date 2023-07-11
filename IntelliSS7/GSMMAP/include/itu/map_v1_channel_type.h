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


#if !defined(_MAP_V1_CHANNEL_TYPE_H_)
#define _MAP_V1_CHANNEL_TYPE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v1 {



class ChannelType : public its::AsnOctetString
{
public:

    ChannelType() : its::AsnOctetString(false)
    {
        Initialize();
    }

    ChannelType(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    ChannelType(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    ChannelType(const ChannelType& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    ChannelType(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    ChannelType(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~ChannelType()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ChannelType(*this);
    }

    virtual std::string GetName() const
    { return "ChannelType"; }

};



} // namespace.

#endif    // !defined(_MAP_V1_CHANNEL_TYPE_H_)
