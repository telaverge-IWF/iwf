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


#if !defined(_CAP_V3_BOTHWAY_THROUGH_CONNECTION_IND_H_)
#define _CAP_V3_BOTHWAY_THROUGH_CONNECTION_IND_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace cap_v3 {



class BothwayThroughConnectionInd : public its::AsnEnumerated
{
public:

    BothwayThroughConnectionInd() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    BothwayThroughConnectionInd(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    BothwayThroughConnectionInd(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    BothwayThroughConnectionInd(const BothwayThroughConnectionInd& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    BothwayThroughConnectionInd(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    BothwayThroughConnectionInd(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~BothwayThroughConnectionInd()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new BothwayThroughConnectionInd(*this);
    }

    virtual std::string GetName() const
    { return "BothwayThroughConnectionInd"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        BOTHWAY_THROUGH_CONNECTION_IND_BOTHWAY_PATH_REQUIRED = 0,
        BOTHWAY_THROUGH_CONNECTION_IND_BOTHWAY_PATH_NOT_REQUIRED = 1

    };

    void SetBothwayPathRequired()
    { _value = 0; }

    bool IsBothwayPathRequired() const
    { return _value == 0; }

    void SetBothwayPathNotRequired()
    { _value = 1; }

    bool IsBothwayPathNotRequired() const
    { return _value == 1; }

};



} // namespace.

#endif    // !defined(_CAP_V3_BOTHWAY_THROUGH_CONNECTION_IND_H_)

