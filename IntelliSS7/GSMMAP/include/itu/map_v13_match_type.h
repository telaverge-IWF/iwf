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


#if !defined(_MAP_V13_MATCH_TYPE_H_)
#define _MAP_V13_MATCH_TYPE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v13 {



class MatchType : public its::AsnEnumerated
{
public:

    MatchType() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    MatchType(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    MatchType(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    MatchType(const MatchType& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    MatchType(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    MatchType(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~MatchType()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MatchType(*this);
    }

    virtual std::string GetName() const
    { return "MatchType"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        MATCH_TYPE_INHIBITING = 0,
        MATCH_TYPE_ENABLING = 1

    };

    void SetInhibiting()
    { _value = 0; }

    bool IsInhibiting() const
    { return _value == 0; }

    void SetEnabling()
    { _value = 1; }

    bool IsEnabling() const
    { return _value == 1; }

};



} // namespace.

#endif    // !defined(_MAP_V13_MATCH_TYPE_H_)

